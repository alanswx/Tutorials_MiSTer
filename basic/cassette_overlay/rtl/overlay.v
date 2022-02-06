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

	output reg [7:0] o_r,
	output reg [7:0] o_g,
	output reg [7:0] o_b,

	input ena,

	input [23:0] max,
	input [23:0] pos

);


wire [7:0]	charmap_r;
wire [7:0]	charmap_g;
wire [7:0]	charmap_b;
wire		charmap_a;
// Casval - character map
wire [11:0] chram_addr;
wire [11:0] chrom_addr;
wire [7:0] chrom_data_out;
wire [7:0] chmap_data_out;

assign o_r= (charmap_a & ena) ? RGB[23:16] : i_r;
assign o_g= (charmap_a & ena) ? RGB[15:8] : i_g;
assign o_b= (charmap_a & ena) ? RGB[7:0]: i_b;

reg [23:0] pos_r;
reg [11:0] wr_addr;
reg [7:0] wr_data;
reg wheel_state;
reg [1:0] state;

// this is an increment / 16 -- we have 10 now, so 
// we need to make the bar 6 wider - AJS TODO
wire [23:0] increment={4'b0000,max[23:4]};
reg [23:0] inc_pos='d0;
reg [4:0] blocks;
reg [4:0] cur_block;


// a6 -- unfilled
// 7f -- filled bar
reg wr_ena;

always @(posedge i_pix)
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
	if (pos!=pos_r) 
	begin
		//$display("pos: %d pos_r %d blocks %d inc_pos %d increment %d\n",pos,pos_r,blocks,inc_pos,increment);
		inc_pos<=inc_pos+'d1;
		if (inc_pos==increment)
		begin
			inc_pos<='d0;
			blocks<=blocks+'d1;
		end

		// do this afterwards, because we need to reset
		// blocks
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
				wr_ena<=1'b1;
				wr_addr<='d331;
				if (wheel_state)
					wr_data<='h2A;
				else
					wr_data<='h96;
				state<=2'b01;
			end
		end
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
		2'b10: 
		begin
			// draw the progress bar - 16 segments
			if (cur_block=='d15)
				state<=2'b11;

			wr_ena<=1'b1;
			wr_addr<='d136+cur_block;
			if (cur_block>blocks)
				wr_data<='hA6; // empty bar
			else
				wr_data<='h7F; // filled bar
			cur_block<=cur_block+'d1;
			//$display("cur_block: %d blocks: %d pos: %d max: %d increment: %d\n",cur_block,blocks,pos,max,increment);
		end
		2'b11:
		begin
			state<=2'b00;
		end
	endcase
		

end

charmap casval
(
	.clk(i_clk),
	.reset(reset),
	.hcnt(hcnt),
	.vcnt(vcnt),
	.chrom_data_out(chrom_data_out),
	.chmap_data_out(chmap_data_out),
	.chram_addr(chram_addr),
	.chrom_addr(chrom_addr),
	.a(charmap_a)
);

// Char ROM - 0x9000 - 0x97FF (0x0800 / 2048 bytes)
dpram #(.widthad_a(11),.width_a(8), .init_file("font.hex")) chrom
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
dpram #(.widthad_a(11),.width_a(8), .init_file("background.hex")) chram
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
