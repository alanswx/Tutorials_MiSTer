module spram #(
    parameter data_width = 8,
    parameter addr_width = 10
) (
    // Port A
    input   wire                clock,
    input   wire                wren,
    input   wire    [addr_width-1:0]  address,
    input   wire    [data_width-1:0]  data,
    output  reg     [data_width-1:0]  q,
     
    input wire cs
);
 
// Shared memory
reg [data_width-1:0] mem [(2**addr_width)-1:0];
 
// Port A
always @(posedge clock) begin
    q      <= mem[address];
    if(wren) begin
        q      <= data;
        mem[address] <= data;
    end
end
 
 
endmodule
