// A simple system-on-a-chip (SoC) for the MiST
// (c) 2015 Till Harbaum

module soc (
   input  pixel_clock,
   output SDRAM_nCS,
   output VGA_HS,
   output VGA_VS,
   output [7:0] VGA_R,
   output [7:0] VGA_G,
   output [7:0] VGA_B,
   output VGA_DE,
   output VGA_HBLANK,
   output VGA_VBLANK
);

// de-activate unused SDRAM
assign SDRAM_nCS = 1;


vga vga (
	 .pclk  (pixel_clock),
	 .hs    (VGA_HS),
	 .vs    (VGA_VS),
	 .r     (VGA_R),
	 .g     (VGA_G),
	 .b     (VGA_B),
	 .VGA_HBLANK(VGA_HBLANK),
	 .VGA_VBLANK(VGA_VBLANK),
	 .VGA_DE(VGA_DE)
);
					


endmodule
