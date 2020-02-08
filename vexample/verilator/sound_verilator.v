//
// top end ff for verilator
//

//`define sdl_display
`define USE_VGA
//`define USE_CGA

module top(VGA_R,VGA_B,VGA_G,VGA_HS,VGA_VS,reset,clk_sys,clk_vid,ioctl_download,ioctl_addr,ioctl_dout,ioctl_index,ioctl_wait,ioctl_wr,start);

   input clk_sys/*verilator public_flat*/;
   input clk_vid/*verilator public_flat*/;
   input reset/*verilator public_flat*/;

   output [7:0] VGA_R/*verilator public_flat*/;
   output [7:0] VGA_G/*verilator public_flat*/;
   output [7:0] VGA_B/*verilator public_flat*/;
   
   output VGA_HS;
   output VGA_VS;
   
   input        ioctl_download;
   input        ioctl_wr;
   input [24:0] ioctl_addr;
   input [7:0] ioctl_dout;
   input [7:0]  ioctl_index;
   output  reg     ioctl_wait=1'b0;
   input        start;
 
   

   
   //-------------------------------------------------------------------

wire cart_download = ioctl_download & (ioctl_index != 8'd0);
wire bios_download = ioctl_download & (ioctl_index == 8'd0);


reg old_cart_download;
reg initial_pause = 1'b1;

always @(posedge clk_sys) begin
	old_cart_download <= cart_download;
	if (old_cart_download & ~cart_download) initial_pause <= 1'b0;
end

////////////////////////////  HPS I/O  //////////////////////////////////

wire  [1:0] buttons;
wire [31:0] status;
wire        img_mounted;
wire        img_readonly;
wire [63:0] img_size;
wire        ioctl_download;
wire [24:0] ioctl_addr;
wire [7:0] ioctl_dout;
wire        ioctl_wr;
wire [7:0]  ioctl_index;

wire [15:0] joy0,joy1;

wire[9:0] hcnt;
soc soc (
   .reset(reset),
   .pixel_clock(clk_vid),
   .hcnt(hcnt),
   .VGA_HS(VGA_HS),
   .VGA_VS(VGA_VS),
   .VGA_R(VGA_R),
   .VGA_G(VGA_G),
   .VGA_B(VGA_B),
   .VGA_DE(),
   .VGA_HBLANK(),
   .VGA_VBLANK()
);

wire [7:0] ld;


////////////////////////////  MEMORY  ///////////////////////////////////
reg    [16:0]rom_a_two;
wire   [7:0]rom_d_two;

wave_sound wave_sound
(
        .I_CLK(clk_sys),
        .I_CLK_SPEED('d2000000),
        .I_RSTn(~reset),
        .I_H_CNT(4'b0001), // used to interleave data reads
        .I_DMA_TRIG(start),
        .I_DMA_STOP(1'b0),
        .I_DMA_CHAN(3'b0), // 8 channels
        .I_DMA_ADDR(17'b0),
        .I_DMA_DATA(rom_d_two), // Data coming back from wave ROM
        .O_DMA_ADDR(rom_a_two), // output address to wave ROM
        .O_SND()
);

dpram_dc #(8,17) rom
(
        .clock_a(clk_sys),
        .wren_a(ioctl_wr),
        .address_a(ioctl_addr[16:0]),
        .data_a(ioctl_dout),
	.byteena_a(1'b1),
	.q_a(),

        .clock_b(clk_sys),
        .wren_b(),
	.data_b(),
        .address_b(rom_a_two),
	.byteena_b(1'b1),
        .q_b(rom_d_two)
);



endmodule // ff_cpu_test

