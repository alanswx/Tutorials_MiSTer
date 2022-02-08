`timescale 1ns / 1ps
//
// top end ff for verilator
//

//`define sdl_display
`define USE_VGA
//`define USE_CGA

module top(VGA_R,VGA_B,VGA_G,VGA_HS,VGA_VS,VGA_HB,VGA_VB,reset,clk_sys,clk_vid,ioctl_download,ioctl_addr,ioctl_dout,ioctl_index,ioctl_wait,ioctl_wr);

   input clk_sys/*verilator public_flat*/;
   input clk_vid/*verilator public_flat*/;
   input reset/*verilator public_flat*/;

   output [7:0] VGA_R/*verilator public_flat*/;
   output [7:0] VGA_G/*verilator public_flat*/;
   output [7:0] VGA_B/*verilator public_flat*/;
   
   output VGA_HS;
   output VGA_VS;
   
   output VGA_HB;
   output VGA_VB;
   
   input        ioctl_download;
   input        ioctl_wr;
   input [24:0] ioctl_addr;
   input [7:0] ioctl_dout;
   input [7:0]  ioctl_index;
   output  reg     ioctl_wait=1'b0;
   
   

wire VGA_DE;
soc soc(
   .reset(reset),
   .clk_sys(clk_sys), // wrong
   .pixel_clock(clk_vid), // wrong
   .VGA_HS(VGA_HS),
   .VGA_VS(VGA_VS),
   .VGA_R(VGA_R),
   .VGA_G(VGA_G),
   .VGA_B(VGA_B),
   .VGA_HB(VGA_HB),
   .VGA_VB(VGA_VB),
   .VGA_DE(VGA_DE)
);


endmodule 

