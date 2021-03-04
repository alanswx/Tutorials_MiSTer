module top_sync_vg_pattern
(	
	input wire clk_27m,
	input wire clk_40m,
	input wire clk_74m,
	input wire clk_148m,
	
	input wire resetb,
	
	output reg adv7513_hs_n, 		// HS output to adv7513
	output reg adv7513_vs_n, 		// VS output to adv7513
	
	output wire adv7513_clk, 		// adv7513: CLK
	
	output reg [23:0] adv7513_d, 	// data
	
	output reg adv7513_de, 			// adv7513: DE
	
	output wire [11:0] x_out,
	output wire [11:0] y_out,
	
	output wire [7:0] r_out,
	output wire [7:0] g_out,
	output wire [7:0] b_out

);

/* ************************************* */
/* SELECT ONE OF MODES: */
//`define MODE_240p
//`define MODE_480p
`define MODE_800x600
//`define MODE_720p
//`define MODE_1080i
//`define MODE_1080p


//parameter PATTERN_TYPE = 8'd1; // BORDER.
//parameter PATTERN_TYPE = 8'd2; // moireX
//parameter PATTERN_TYPE = 8'd3; // moireY
//parameter PATTERN_TYPE = 8'd4; // RAMP.
parameter PATTERN_TYPE = 8'd5; // XOR.



`ifdef MODE_1080p /* FORMAT 16 - Pixel Clock = 148.500 MHz */
wire clk_in = clk_148m;
parameter INTERLACED = 1'b0;
parameter V_TOTAL_0 = 12'd1125;
parameter V_FP_0 = 12'd4;
parameter V_BP_0 = 12'd36;
parameter V_SYNC_0 = 12'd5;
parameter V_TOTAL_1 = 12'd0;
parameter V_FP_1 = 12'd0;
parameter V_BP_1 = 12'd0;
parameter V_SYNC_1 = 12'd0;
parameter H_TOTAL = 12'd2200;
parameter H_FP = 12'd88;
parameter H_BP = 12'd148;
parameter H_SYNC = 12'd44;
parameter HV_OFFSET_0 = 12'd0;
parameter HV_OFFSET_1 = 12'd0;
parameter PATTERN_RAMP_STEP = 20'h0222;
`endif

`ifdef MODE_1080i /* FORMAT 5 - Pixel Clock = 74.250 MHz */
wire clk_in = clk_74m;
parameter INTERLACED = 1'b1;
parameter V_TOTAL_0 = 12'd562;
parameter V_FP_0 = 12'd2;
parameter V_BP_0 = 12'd15;
parameter V_SYNC_0 = 12'd5;
parameter V_TOTAL_1 = 12'd563;
parameter V_FP_1 = 12'd2;
parameter V_BP_1 = 12'd16;
parameter V_SYNC_1 = 12'd5;
parameter H_TOTAL = 12'd2200;
parameter H_FP = 12'd88;
parameter H_BP = 12'd148;
parameter H_SYNC = 12'd44;
parameter HV_OFFSET_0 = 12'd0;
parameter HV_OFFSET_1 = 12'd1100;
parameter PATTERN_RAMP_STEP = 20'h0222; // 20'hFFFFF / 1920 act_pixels per line = 20'h0222
`endif

`ifdef MODE_720p /* FORMAT 4 - Pixel Clock = 74.250 MHz */
wire clk_in = clk_74m;
parameter INTERLACED = 1'b0;
parameter V_TOTAL_0 = 12'd750;
parameter V_FP_0 = 12'd5;
parameter V_BP_0 = 12'd20;
parameter V_SYNC_0 = 12'd5;
parameter V_TOTAL_1 = 12'd0;
parameter V_FP_1 = 12'd0;
parameter V_BP_1 = 12'd0;
parameter V_SYNC_1 = 12'd0;
parameter H_TOTAL = 12'd1650;
parameter H_FP = 12'd110;
parameter H_BP = 12'd220;
parameter H_SYNC = 12'd40;
parameter HV_OFFSET_0 = 12'd0;
parameter HV_OFFSET_1 = 12'd0;
parameter PATTERN_RAMP_STEP = 20'h0333; // 20'hFFFFF / 1280 act_pixels per line = 20'h0333
`endif

`ifdef MODE_800x600 /* Pixel Clock = 40 MHz */
wire clk_in = clk_40m;
parameter INTERLACED = 1'b0;
parameter V_TOTAL_0 = 12'd628;
parameter V_FP_0 = 12'd1;
parameter V_BP_0 = 12'd23;
parameter V_SYNC_0 = 12'd4;
parameter V_TOTAL_1 = 12'd0;
parameter V_FP_1 = 12'd0;
parameter V_BP_1 = 12'd0;
parameter V_SYNC_1 = 12'd0;
parameter H_TOTAL = 12'd1056;
parameter H_FP = 12'd40;
parameter H_BP = 12'd88;
parameter H_SYNC = 12'd128;
parameter HV_OFFSET_0 = 12'd0;
parameter HV_OFFSET_1 = 12'd0;
parameter PATTERN_RAMP_STEP = 20'h0333; // 20'hFFFFF / 1280 act_pixels per line = 20'h0333
`endif

`ifdef MODE_480p /* Pixel Clock 27.027 MHz */
wire clk_in = clk_27m;
parameter INTERLACED = 1'b0;
parameter V_TOTAL_0 = 12'd525;
parameter V_FP_0 = 12'd9;
parameter V_SYNC_0 = 12'd6;
parameter V_BP_0 = 12'd30;
parameter V_TOTAL_1 = 12'd0;
parameter V_FP_1 = 12'd0;
parameter V_SYNC_1 = 12'd0;
parameter V_BP_1 = 12'd0;
parameter H_TOTAL = 12'd858;
parameter H_FP = 12'd16;
parameter H_SYNC = 12'd62;
parameter H_BP = 12'd60;
parameter HV_OFFSET_0 = 12'd0;
parameter HV_OFFSET_1 = 12'd0;
parameter PATTERN_RAMP_STEP = 20'h0333; // 20'hFFFFF / 1280 act_pixels per line = 20'h0333
`endif

`ifdef MODE_240p
wire clk_in = clk_27m;
parameter INTERLACED = 1'b0;
parameter V_TOTAL_0 = 12'd262;
parameter V_FP_0 = 12'd5;
parameter V_SYNC_0 = 12'd5;
parameter V_BP_0 = 12'd20;
parameter V_TOTAL_1 = 12'd0;
parameter V_FP_1 = 12'd0;
parameter V_SYNC_1 = 12'd0;
parameter V_BP_1 = 12'd0;
parameter H_TOTAL = 12'd1716;
parameter H_FP = 12'd110;
parameter H_SYNC = 12'd40;
parameter H_BP = 12'd220;
parameter HV_OFFSET_0 = 12'd0;
parameter HV_OFFSET_1 = 12'd0;
parameter PATTERN_RAMP_STEP = 20'h0333; // 20'hFFFFF / 1280 act_pixels per line = 20'h0333
`endif


wire reset = !resetb;

//wire [11:0] x_out;
//wire [11:0] y_out;
//wire [7:0] r_out;
//wire [7:0] g_out;
//wire [7:0] b_out;

/* ********************* */
sync_vg #(.X_BITS(12), .Y_BITS(12)) sync_vg
(
	.clk(clk_in),
	.reset(reset),
	.interlaced(INTERLACED),
	.clk_out(), // inverted output clock - unconnected
	.v_total_0(V_TOTAL_0),
	.v_fp_0(V_FP_0),
	.v_bp_0(V_BP_0),
	.v_sync_0(V_SYNC_0),
	.v_total_1(V_TOTAL_1),
	.v_fp_1(V_FP_1),
	.v_bp_1(V_BP_1),
	.v_sync_1(V_SYNC_1),
	.h_total(H_TOTAL),
	.h_fp(H_FP),
	.h_bp(H_BP),
	.h_sync(H_SYNC),
	.hv_offset_0(HV_OFFSET_0),
	.hv_offset_1(HV_OFFSET_1),
	.de_out(de),
	.vs_out(vs),
	.v_count_out(),
	.h_count_out(),
	.x_out(x_out),
	.y_out(y_out),
	.hs_out(hs),
	.field_out(field)
);

wire de;
wire vs;
wire hs;
wire field;

pattern_vg #(
	.B(8), // Bits per channel
	.X_BITS(12),
	.Y_BITS(12),
	.FRACTIONAL_BITS(12)) // Number of fractional bits for ramp pattern

pattern_vg (
	.reset(reset),
	.clk_in(clk_in),
	.x(x_out),
	.y(y_out[11:0]),
	.vn_in(vs),
	.hn_in(hs),
	.dn_in(de),
	.r_in(8'h0), // default red channel value
	.g_in(8'h0), // default green channel value
	.b_in(8'h0), // default blue channel value
	.vn_out(vs_out),
	.hn_out(hs_out),
	.den_out(de_out),
	.r_out(r_out),
	.g_out(g_out),
	.b_out(b_out),
	.total_active_pix(H_TOTAL - (H_FP + H_BP + H_SYNC)), // (1920) // h_total - (h_fp+h_bp+h_sync)
	.total_active_lines(INTERLACED ? (V_TOTAL_0 - (V_FP_0 + V_BP_0 + V_SYNC_0)) + (V_TOTAL_1 - (V_FP_1 + V_BP_1 + V_SYNC_1)) : (V_TOTAL_0 - (V_FP_0 + V_BP_0 + V_SYNC_0))), // originally: 13'd480
	.pattern(PATTERN_TYPE),
	.ramp_step(PATTERN_RAMP_STEP));

wire vs_out;
wire hs_out;
wire de_out;
	

assign adv7513_clk = ~clk_in;


always @(posedge clk_in)
	begin
		adv7513_d[23:0] <= { r_out, g_out, b_out };
		adv7513_hs_n <= !hs_out;
		adv7513_vs_n <= !vs_out;
		adv7513_de <= de_out;
	end
	
endmodule
