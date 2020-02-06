module spram #(parameter addr_width=8, parameter data_width=8) 
   (
	input logic clock,
	input logic wren,
	input logic [(data_width-1):0] data,
	input logic cs,
	input logic [(addr_width-1):0] address,
	output logic [(data_width-1):0] q
);

	logic [(data_width-1):0] mem [(2**addr_width-1):0];
	
	always_ff @(posedge clock)
	 begin
		if (wren) mem[address] <= data;
	//$display("data=%h addr=%h word=%h",data, addr, addr[31:2]);
	end

	assign q= cs ? mem[address] : {data_width{1'b1}};

endmodule: spram
