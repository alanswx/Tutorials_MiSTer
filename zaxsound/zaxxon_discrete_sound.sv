module zaxxon_discrete_sound (
        input         clk_sys,
        input         reset,
        input [7:0] trig,
        output signed [15:0] short_audio

);

reg [16:0]divider;
reg clk_300;
reg clk_600;
reg clk_1150;
reg clk_2450;

always @(posedge clk_sys or posedge reset)
begin
        if(reset)begin
		divider<=17'd0;
		clk_300<=1'd0;
		clk_600<=1'd0;
		clk_1150<=1'd0;
		clk_2450<=1'd0;
	end else begin

	divider<=divider+1'b1;

	if  (divider==17'd80000) begin
		clk_300<=~clk_300;
	end
	if  (divider==17'd40000) begin
		clk_600<=~clk_600;
	end
	if  (divider==17'd20870) begin
		clk_1150<=~clk_1150;
	end
	if  (divider==17'd9796) begin
		clk_2450<=~clk_2450;
	end
end
end

assign short_audio = clk_300 ? 16'd15000:0;

endmodule

