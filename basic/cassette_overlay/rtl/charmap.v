`timescale 1ns / 1ps
/*============================================================================
	Aznable (custom 8-bit computer system) - Casval (character map)

	Author: Jim Gregory - https://github.com/JimmyStones/
	Version: 1.0
	Date: 2021-10-20

	This program is free software; you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3 of the License, or (at your option)
	any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program. If not, see <http://www.gnu.org/licenses/>.
===========================================================================*/

module charmap (
	input	clk,
	input	reset,
	input	[9:0] hcnt,
	input	[9:0] vcnt,
	input	[7:0] chrom_data_out,
	input	[7:0] chmap_data_out,
	output [11:0] chram_addr,
	output [11:0] chrom_addr,
	output 		  a
);

// Character map
wire [2:0] chpos_x = 3'd7 - hcnt[2:0];
wire [2:0] chpos_y = vcnt[2:0];
wire [5:0] chram_x = hcnt[8:3];
wire [5:0] chram_y = vcnt[8:3];
assign a = hcnt > 'd511 ? 1'b0 : vcnt > 'd255 ? 1'b0 : chrom_data_out[chpos_x[2:0]];
//assign a = chrom_data_out[chpos_x[2:0]];
assign chram_addr = {chram_y, chram_x};
assign chrom_addr = {1'b0, chmap_data_out[7:0], chpos_y};


endmodule
