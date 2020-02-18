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

reg clk_snd_00;
reg [2:0] cnt_snd_00=0;

always @(posedge clk_sys or posedge reset)
begin
        if(reset)begin
		divider<=17'd0;
		clk_300<=1'd0;
		clk_600<=1'd0;
		clk_1150<=1'd0;
		clk_2450<=1'd0;
		clk_snd_00<=1'd0;
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
	if (divider==17'd59259) begin
		clk_snd_00<=~clk_snd_00;
	end
end
end

reg signed [15:0] snd_00;
always @(posedge clk_snd_00) 
begin
	case (cnt_snd_00)
		'd00:  snd_00<= 16'd13107;
		'd01:  snd_00<= 16'd11468;
		'd02:  snd_00<= 16'd9830;
		'd03:  snd_00<= -16'd13107;
		'd04:  snd_00<= -16'd11468;
		'd05:  snd_00<= -16'd9830;
	endcase
	cnt_snd_00 <= ( cnt_snd_00 == 5) ? 0 : (cnt_snd_00+1);	


end

//assign short_audio = clk_300 ? 16'd15000:0;
assign short_audio = snd_00;

endmodule

