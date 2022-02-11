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
   output VGA_DE,
   input  reset,

   input        ioctl_download,
   input        ioctl_wr,
   input [24:0] ioctl_addr,
   input [7:0] ioctl_dout,
   input [7:0]  ioctl_index
   
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
wire [23:0] tape_end= 24'd1023*24'd24;
reg [23:0] pos='d0;


reg [12:0]div;
always @(posedge pixel_clock)
begin
	div<=div+13'd1;
	if (div=='d6666)
		div<=0;

	if (div==0)
          pos<=pos+24'd1;

  	if (pos==tape_end)
		pos<='d0;
	
end

// Char index RAM - 0x9800 - 0x9FFF (0x0800 / 2048 bytes)
cas_dpram #(.widthad_a(15),.width_a(8)) tape_ram
(
        .clock_a(clk_sys),
        .address_a(ioctl_addr[14:0]),
        .wren_a(ioctl_wr & ioctl_download),
        .data_a(ioctl_dout),
        .q_a(),

        .clock_b(clk_sys),
        .address_b(pos),
        .wren_b(1'b0),
        .data_b(),
        .q_b(tape_data)
);

wire [7:0] tape_data;

overlay overlay
(
    .reset(reset),
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
    .pos(pos),
    .tape_data(tape_data)
);


// include VGA controller
vga vga (
	.pclk     ( pixel_clock),
	 
	.cpu_clk  ( clk_sys        ),

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






endmodule
