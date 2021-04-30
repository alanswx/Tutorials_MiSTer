`timescale 1ns / 1ps

module dpram #(
    parameter width_a = 8,
    parameter widthad_a = 10,
    parameter init_file= ""
) (
    // Port A
    input   wire                clock_a,
    input   wire                wren_a,
    input   wire    [widthad_a-1:0]  address_a,
    input   wire    [width_a-1:0]  data_a,
    output  reg     [width_a-1:0]  q_a,
     
    // Port B
    input   wire                clock_b,
    input   wire                wren_b,
    input   wire    [widthad_a-1:0]  address_b,
    input   wire    [width_a-1:0]  data_b,
    output  reg     [width_a-1:0]  q_b,

    input wire byteena_a,
    input wire byteena_b
);

    initial begin
        $display("Loading rom.");
        $display(init_file);
        if (init_file>0)
        	$readmemh(init_file, mem);
    end

 
// Shared memory
reg [width_a-1:0] mem [(2**widthad_a)-1:0];
// Port A
always @(posedge clock_a) begin
    q_a      <= mem[address_a];
    if(wren_a) begin
        q_a      <= data_a;
        mem[address_a] <= data_a;
    end
end
 
// Port B
always @(posedge clock_b) begin
    q_b      <= mem[address_b];
    if(wren_b) begin
        q_b      <= data_b;
        mem[address_b] <= data_b;
    end
end
 
endmodule
