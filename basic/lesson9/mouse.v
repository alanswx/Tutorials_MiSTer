// http://www.computer-engineering.org/ps2mouse/
/*
 * PS2 mouse protocol
 * Bit       7    6    5    4    3    2    1    0  
 * Byte 0: YOVR XOVR YSGN XSGN   1   MBUT RBUT LBUT
 * Byte 1:                 XMOVE
 * Byte 2:                 YMOVE
 */
 
  
module mouse ( 
	input clk,
	input reset,

	// ps2 interface	
	//input ps2_clk,
	//input ps2_data,
	input [24:0] ps2_mouse,

	// decodes keys
	output [7:0] x,
	input clr_x,
	output [7:0] y,
	input clr_y,
	output reg [1:0] b
);



// look at the change in mouse byte as a new mouse motion
wire valid = (old_stb != ps2_mouse[24]);
reg  old_stb = 0;
always @(posedge clk) old_stb <= ps2_mouse[24];




assign x = x_pos[9:2];
assign y = y_pos[9:2];
reg [9:0] x_pos;
reg [9:0] y_pos;


reg clr_x_reg;
reg clr_y_reg;


wire error;



always @(posedge clk) begin
	   if (clr_x_reg) begin
		   x_pos[9:2] <= 8'd0;
		   clr_x_reg=0;
		end
		if (clr_y_reg) begin
		   y_pos[9:2] <= 8'd0;
			clr_y_reg=0;
		end

	if(reset) begin
		x_pos <= 10'd0;
		y_pos <= 10'd0;
	end else begin
		// ps2 decoder has received a valid byte
		if(valid) begin
				// bit 3 must be 1. Stay in state 0 otherwise
				if(ps2_mouse[3]) begin
				    b <= ps2_mouse[1:0];
				    // the ps2 packet contains a 9 bit value. We only use the upper 
				    // 7. Otherwise the mouse would be too fast for our low resolution
				    x_pos <= x_pos + { {2{ps2_mouse[4]}}, ps2_mouse[15:8]};
				    y_pos <= y_pos + { {2{ps2_mouse[5]}},  ps2_mouse[23:16]};
				end
		end
		
		// only the upper 8 bits of the 10 bit mouse position are reported back to the
		// cpu
		if(clr_x) clr_x_reg = 1;
		if(clr_y) clr_y_reg = 1;
	end
end



endmodule
