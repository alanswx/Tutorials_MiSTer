`timescale 1ns / 1ps

module overlay #(
    parameter [23:0] RGB = 24'hFFFFFF
) (
	input reset,

	input [7:0] i_r,
	input [7:0] i_g,
	input [7:0] i_b,

	input i_clk,
	input i_pix,

	input [9:0] hcnt,
	input [9:0] vcnt,

	output  [7:0] o_r,
	output  [7:0] o_g,
	output  [7:0] o_b,

	input ena,

	input [24:0] max,
	input [24:0] pos,
	input [7:0] tape_data 

);


wire [9:0] new_h = hcnt - 'd150;
wire [9:0] new_v = vcnt - 'd100;


wire		charmap_a;
// Casval - character map
wire [11:0] chram_addr;
wire [11:0] chrom_addr;
wire [7:0] chrom_data_out;
wire [7:0] chmap_data_out;

// 22 wide
// 11 high

wire in_box = new_h > 'd8*'d5 && new_h < 'd8*('d24+'d3) && new_v > 'd8*1 && new_v < 'd8*'d12; 

// height - 96-8 -> 84
//
// Mix the colors, we use the RGB constant, but we darken the background by shifting it right
//
assign o_r = o_r_a | meter_red;
reg [7:0] o_r_a;
assign o_g = o_g_a | meter_green;
reg [7:0] o_g_a;
assign o_r_a= ~ena | ~in_box ? i_r : (charmap_a ) ? RGB[23:16] : i_r >> 2;
assign o_g_a= ~ena | ~in_box ? i_g : (charmap_a ) ? RGB[15:8]  : i_g >> 2;
assign o_b= ~ena | ~in_box ? i_b : (charmap_a ) ? RGB[7:0]   : i_b >> 2;

reg [24:0] pos_r;
reg [11:0] wr_addr;
reg [7:0] wr_data;
reg wheel_state;
reg [1:0] state;

// this is an increment / 16  
// our inc_pos will count up to the increment each time
// this way we don't need a division
wire [24:0] increment={4'b0000,max[23:4]};
reg [24:0] inc_pos='d0;
reg [4:0] blocks;
reg [4:0] cur_block;


// a6 -- unfilled
// 7f -- filled bar
reg wr_ena;

always @(posedge i_clk)
begin
	if (reset)
	begin
		state<=2'b0;
		blocks<='d0;
	end


	// when the pos changes, we need to 
	// increment the tape gears
	wr_ena<=1'b0;
	pos_r<=pos;
	
	//
	// Each time we get a new position, we increment our inc_pos counter
	// if we reach the "increment size" - increment_size is one character in the progress bar
	// then we need to increase "blocks"
	//
	if (pos!=pos_r) 
	begin
		$display("pos: %d tape_data %x",pos,tape_data);
		//$display("pos: %d pos_r %d blocks %d inc_pos %d increment %d\n",pos,pos_r,blocks,inc_pos,increment);
		inc_pos<=inc_pos+25'd1;
		if (inc_pos==increment)
		begin
			inc_pos<='d0;
			blocks<=blocks+5'd1;
		end

		// do this afterwards, because we need to reset
		// blocks
		// if the tape is rewound, we need to reset our variables
		if (pos=='d0)
		begin
			//$display("pos is 0\n");
			inc_pos<='d0;
			blocks<='d0;
		end
		cur_block<='d0;
	end
	case (state)
		2'b00: 
		begin
			if (pos!=pos_r) 
			begin
				//$display("pos: %d \n",pos);
				// swap characters on the left tape gear and increment to the next
				// state so we can swap characters on that gear
				wr_ena<=1'b1;
				wr_addr<='d331;
				if (wheel_state)
					wr_data<='h2A;
				else
					wr_data<='h96;
				state<=2'b01;
			end
		end
		// swap characters on the right tape gear and increment to the next state
		2'b01: 
		begin
			wr_ena<=1'b1;
			wr_addr<='d340;
			if (wheel_state)
				wr_data<='h96;
			else
				wr_data<='h2A;
			wheel_state<=~wheel_state;
			state<=2'b10;
		end
		// stay in this state for 16 cycles so we can draw each segment of the progress bar
		// we check the block we are setting in vram vs the "blocks" so we know whether to
		// draw it filled or empty

		2'b10: 
		begin
			// draw the progress bar - 16 segments
			if (cur_block=='d15)
				state<=2'b11;

			wr_ena<=1'b1;
			wr_addr<=12'd136+cur_block;
			if (cur_block>blocks)
				wr_data<='hA6; // empty bar
			else
				wr_data<='h7F; // filled bar
			cur_block<=cur_block+5'd1;
			//$display("cur_block: %d blocks: %d pos: %d max: %d increment: %d\n",cur_block,blocks,pos,max,increment);
		end
		2'b11:
		begin
			state<=2'b00;
		end
	endcase
end

//
//  some code to draw a waveform
//
reg [255:0] seq;
wire [7:0] meter_red;
wire [7:0] meter_green;
//assign color = ena & vcnt > 480-db[7:1] ? 8'h80 : 0;
//255,127, - 84
assign meter_green = ena & in_box & new_v > 'd88 - db[7:2]  & new_v > 'd40  ? 8'h80: 8'h00;
assign meter_red   = ena & in_box & new_v > 'd88 - db[7:2]  & new_v < 'd60  ? 8'h80: 8'h00;
//assign meter_red  = 8'h00;//ena & in_box & new_v > db[7:1]  - 'd40& new_v < db[7:1]  - 'd20  ? 8'h80: 0;
//wire [6:0] idx = hcnt[10:4] - 7'd11;
wire [6:0] idx = new_h[10:4] ;
wire [7:0] db = seq >> { idx, 2'b0 };

always @(posedge i_pix)
begin
	if (vcnt==0)
  		seq <= { seq[247:0], tape_data};
end

//
// The charmap code takes the VRAM, CHAR ROM, and current hcnt/vcnt and outputs 
// The correct alpha - 1 for draw a char, 0 for background
//
charmap casval
(
	.clk(i_pix),
	.reset(reset),
	.hcnt(new_h),
	.vcnt(new_v),
	.chrom_data_out(chrom_data_out),
	.chmap_data_out(chmap_data_out),
	.chram_addr(chram_addr),
	.chrom_addr(chrom_addr),
	.a(charmap_a)
);

// Char ROM - 0x9000 - 0x97FF (0x0800 / 2048 bytes)
cas_dpram #(.widthad_a(11),.width_a(8), .init_file("font.hex")) chrom
(
	.clock_a(i_clk),
	.address_a(chrom_addr[10:0]),
	.wren_a(1'b0),
	.data_a(),
	.q_a(chrom_data_out),

	.clock_b(i_clk),
	.address_b(),
	.wren_b(),
	.data_b(),
	.q_b()
);

// Char index RAM - 0x9800 - 0x9FFF (0x0800 / 2048 bytes)
cas_dpram #(.widthad_a(11),.width_a(8), .init_file("background.hex")) chram
(
	.clock_a(i_clk),
	.address_a(wr_addr[10:0]),
	.wren_a(wr_ena),
	.data_a(wr_data),
	.q_a(),

	.clock_b(i_clk),
	.address_b(chram_addr[10:0]),
	.wren_b(1'b0),
	.data_b(),
	.q_b(chmap_data_out)
);

endmodule
