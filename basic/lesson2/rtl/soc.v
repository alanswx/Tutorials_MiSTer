`timescale 1ns / 1ps
// (c) 2015 Till Harbaum

module soc (
   input  pixel_clock,
   input  ioctl_wr,
   input [13:0] ioctl_addr,
   input [7:0] ioctl_data,
   output reg progress,
   output VGA_HS,
   output VGA_VS,
   output [7:0] VGA_R,
   output [7:0] VGA_G,
   output [7:0] VGA_B,
   output VGA_DE
);



vga vga (
	 .pclk  (pixel_clock),
	 
	 .ioctl_wr   ( ioctl_wr ),
	 .ioctl_addr ( ioctl_addr    ),
	 .ioctl_data ( ioctl_data             ),

	 .hs    (VGA_HS),
	 .vs    (VGA_VS),
	 .r     (VGA_R),
	 .g     (VGA_G),
	 .b     (VGA_B),
	 .VGA_DE(VGA_DE)
);
				

			


endmodule
