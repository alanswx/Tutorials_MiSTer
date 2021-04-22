//
// top end ff for verilator
//

//`define sdl_display
`define USE_VGA
//`define USE_CGA

module top(VGA_R,VGA_B,VGA_G,VGA_HS,VGA_VS,reset,clk_sys,clk_vid,ioctl_download,ioctl_addr,ioctl_dout,ioctl_index,ioctl_wait,ioctl_wr,done, bs);

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
  
   output reg done;


   output reg [3:0] bs;


wire [3:0] force_bs;
wire sc;


logic [31:0] cart_size;
logic [7:0] cart_data;
wire [12:0] cart_addr;

detect2600 detect2600
(
	.reset(reset),
	.clk(clk_sys),
	.addr(ioctl_addr[12:0]),
	.enable(ioctl_wr & ioctl_download),
	.data(ioctl_dout),
	.force_bs(force_bs),
	.cart_size(cart_size),
	.sc(sc)
);

reg last_ioctl_download;
always_ff @(posedge clk_sys) begin
        if (reset)
		done<=0;
        last_ioctl_download <= ioctl_download;
	if (ioctl_download && ioctl_wr) begin
		cart_size <= ioctl_addr  + 1'b1; // 32 bit 1
        	$display("cart_download: writing x's %b @ %x", ioctl_dout, ioctl_addr);
	end
        if (last_ioctl_download==1 && ioctl_download==0) begin
        	$display("forcebs: %x cart_size: %x sc %x",force_bs,cart_size,sc);
		done<=1;
		bs<=force_bs;
	end
end
 
   




   
endmodule // ff_cpu_test

