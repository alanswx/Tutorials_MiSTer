
module sound_rom(input clk,
	   input 	reset,
	   input [13:0] a,
	   output [7:0] dout
	   );

   reg [7:0] q;
   
always @(posedge clk or posedge reset)
  if (reset)
    q = 0;
  else
//`include "../roms/extract/rom_code_case.v"
`include "dk_wave.v"

  assign dout = q;

   
endmodule // rom
