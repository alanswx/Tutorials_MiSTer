
module dpram_dc #(parameter widthad_a=8, parameter width_a=8)
(
	input logic clock_a,
	input logic clock_b,
	input logic wren_a,
	input logic [(width_a-1):0] data_a,
	input logic byteena_a,
	input logic [(widthad_a-1):0] address_a,
	output logic [(width_a-1):0] q_a,
	
	input logic wren_b,
	input logic [(width_a-1):0] data_b,
	input logic byteena_b,
	input logic [(widthad_a-1):0] address_b,
	output logic [(width_a-1):0] q_b
);

	reg [(width_a-1):0] mem [(2**widthad_a-1):0];
	
	always @(posedge clock_a)
	begin
		q_a= byteena_a ? mem[address_a] : {width_a{1'b1}};
		if (wren_a) 
		begin
			mem[address_a] <= data_a;
			q_a= byteena_a ? data_a : {width_a{1'b1}};
		end
	//$display("a: data=%h addr=%h ",q_a, address_a );
	end
	always @(posedge clock_b)
	begin
		q_b= byteena_b ? mem[address_b] : {width_a{1'b1}};
		if (wren_b) 
		begin
			mem[address_b] <= data_b;
			q_b= byteena_b ? data_b : {width_a{1'b1}};
		end
	//$display("b: data=%h addr=%h ",q_b, address_b );
	end
	


endmodule: dpram_dc
