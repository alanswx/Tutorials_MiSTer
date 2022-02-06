`timescale 1ns / 1ps
module soc (
   input  clk_sys,
   input  pixel_clock,
   output VGA_HS,
   output VGA_VS,
   output [7:0] VGA_R,
   output [7:0] VGA_G,
   output [7:0] VGA_B,
   output VGA_HB,
   output VGA_VB,
   output VGA_DE
);        

///////////////////////////////////////////////////
wire vs,hs;
wire ce_pix;
wire hblank, vblank;
wire interlace;

wire [7:0] r;
wire [7:0] g;
wire [7:0] b;

wire [9:0] hcount;
wire [9:0] vcount;

//wire [23:0] tape_end= 'd1024*'d12;
wire [23:0] tape_end= 'd1023;
reg [23:0] pos='d0;


reg [12:0]div;
always @(posedge pixel_clock)
begin
	div<=div+'d1;
	if (div=='d6666)
		div<=0;

	if (div==0)
          pos<=pos+1;

  	if (pos==tape_end)
		pos<='d0;
	
end

overlay overlay
(
    .i_r(r),
    .i_g(g),
    .i_b(b),
    .i_clk(clk_sys),
    .i_pix(pixel_clock),

    .hcnt(hcount[9:0]),
    .vcnt(vcount[9:0]),

    .o_r(VGA_R),
    .o_g(VGA_G),
    .o_b(VGA_B),
    .ena(1'b1),

    .max(tape_end),
    .pos(pos)
);


// include VGA controller
vga vga (
	.pclk     ( pixel_clock),
	 
	.cpu_clk  ( cpu_clock        ),
	.cpu_wr   ( !cpu_wr_n && !cpu_addr[15] ),
	.cpu_addr ( cpu_addr[13:0]   ),
	.cpu_data ( cpu_dout         ),

        // video output as fed into the VGA outputs
	.hs    (VGA_HS),
	.vs    (VGA_VS),
	.r     (r),
	.g     (g),
	.b     (b),
	.VGA_HB(VGA_HB),
	.VGA_VB(VGA_VB),
	.VGA_DE(VGA_DE),
	.hcount(hcount),
	.vcount(vcount)

);


// The CPU is kept in reset for 256 cycles after power on
reg [7:0] cpu_reset_cnt = 8'h00;
wire cpu_reset = (cpu_reset_cnt != 255);
always @(posedge cpu_clock)
	if(cpu_reset_cnt != 255)
		cpu_reset_cnt <= cpu_reset_cnt + 8'd1;

// CPU control signals
wire cpu_clock = clk_sys;
wire [15:0] cpu_addr;
wire [7:0] cpu_din;
wire [7:0] cpu_dout;
wire cpu_rd_n;
wire cpu_wr_n;
wire cpu_mreq_n;

// include Z80 CPU
/*
T80s T80s (
	.RESET_n  ( !cpu_reset    ),
	.CLK    ( cpu_clock     ),
	.WAIT_n   ( 1'b1          ),
	.INT_n    ( 1'b1          ),
	.NMI_n    ( 1'b1          ),
	.BUSRQ_n  ( 1'b1          ),
	.MREQ_n   ( cpu_mreq_n    ),
	.RD_n     ( cpu_rd_n      ), 
	.WR_n     ( cpu_wr_n      ),
	.A        ( cpu_addr      ),
	.DI       ( cpu_din       ),
	.DO       ( cpu_dout      )
);
*/

tv80s T80x  (
	.reset_n   ( !cpu_reset    ),
	.clk       ( cpu_clock     ),
	.wait_n    ( 1'b0          ),
	.int_n     ( 1'b1          ),
	.nmi_n     ( 1'b1          ),
	.busrq_n   ( 1'b1          ),
	.mreq_n    ( cpu_mreq_n    ),
	.rd_n      ( cpu_rd_n      ), 
	.wr_n      ( cpu_wr_n      ),
	.A         ( cpu_addr      ),
	.di        ( cpu_din       ),
	.dout      ( cpu_dout      )
  );

  
// map 4k RAM into upper half of the address space (A15=1)
// and 4k ROM into the lower half (A15=0)
wire [7:0] ram_data_out, rom_data_out;
assign cpu_din = cpu_addr[15]?ram_data_out:rom_data_out;

// include 4k program code from boot_rom

dpram #( .init_file("rom.hex"),.widthad_a(12),.width_a(8)) rom
(
        .clock_a(cpu_clock),
        .address_a(cpu_addr[11:0]),
        .wren_a(1'b0),
        .q_a(rom_data_out),
        .clock_b(cpu_clock),
        .wren_b(1'b0)

);


dpram #( .init_file(""),.widthad_a(12),.width_a(8)) ram
(
        .clock_a(cpu_clock),
        .address_a(cpu_addr[11:0]),
        .wren_a(!cpu_wr_n && cpu_addr[15]),
        .q_a(ram_data_out),
        .data_a(cpu_dout),

        .clock_b(cpu_clock),
        .address_b(cpu_addr[11:0]),
        .wren_b(1'b0),
        .q_b(),
        .data_b(),

);





endmodule
