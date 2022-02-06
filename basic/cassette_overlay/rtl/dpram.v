/*============================================================================
	Generic dual-port RAM module

	Author: Jim Gregory - https://github.com/JimmyStones/
	Version: 1.0
	Date: 2021-07-03

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

module dpram #(
	parameter address_width = 10,
	parameter data_width = 8,
    parameter init_file= ""
) (
	input	wire						clock_a,
	input	wire						wren_a,
	input	wire	[address_width-1:0]	address_a,
	input	wire	[data_width-1:0]	data_a,
	output	reg		[data_width-1:0]	q_a,

	input	wire						clock_b,
	input	wire						wren_b,
	input	wire	[address_width-1:0]	address_b,
	input	wire	[data_width-1:0]	data_b,
	output	reg		[data_width-1:0]	q_b
);

initial begin
	if (init_file>0)
	begin
		// $display("Loading dpram from file:");
		// $display(init_file);
		$readmemh(init_file, mem);
	end
end

localparam ramLength = (2**address_width);
reg [data_width-1:0] mem [ramLength-1:0];

always @(posedge clock_a) begin
	q_a <= mem[address_a];
	if(wren_a) begin
		q_a <= data_a;
		mem[address_a] <= data_a;
	end
end

always @(posedge clock_b) begin
	q_b <= mem[address_b];
	if(wren_b) begin
		q_b <= data_b;
		mem[address_b] <= data_b;
	end
end

endmodule