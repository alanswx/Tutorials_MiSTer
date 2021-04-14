`ifndef __TINY_SYNTH_CLOCK_DIVIDER__
`define __TINY_SYNTH_CLOCK_DIVIDER__

function integer rtoi;
    input integer x;


    begin
        rtoi = x;
    end
endfunction


module clock_divider #(
  parameter DIVISOR = 2
)
(
  input wire cin,
  output wire cout
);

localparam FULL_SCALE = 2 ** 28;
localparam [27:0] INCREMENT = rtoi(FULL_SCALE / DIVISOR);

reg [27:0] counter;

initial begin
  counter = 0;
end

always @(posedge cin)
begin
  counter = counter + INCREMENT;
end

assign cout = counter[27];

endmodule
/*
// fpga4student.com: FPGA projects, VHDL projects, Verilog projects
// Verilog project: Verilog code for clock divider on FPGA
// Top level Verilog code for clock divider on FPGA
module Clock_divider(cin,cout
    );
input cin; // input clock on FPGA
output cout; // output clock after dividing the input clock by divisor
reg[27:0] counter=28'd0;
parameter DIVISOR = 28'd2;
// The frequency of the output clk_out
//  = The frequency of the input clk_in divided by DIVISOR
// For example: Fclk_in = 50Mhz, if you want to get 1Hz signal to blink LEDs
// You will modify the DIVISOR parameter value to 28'd50.000.000
// Then the frequency of the output clk_out = 50Mhz/50.000.000 = 1Hz
always @(posedge cin)
begin
 counter <= counter + 28'd1;
 if(counter>=(DIVISOR-1))
  counter <= 28'd0;
end
assign cout = (counter<DIVISOR/2)?1'b0:1'b1;
endmodule
*/
`endif
