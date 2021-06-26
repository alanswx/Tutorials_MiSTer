
module video_timing
(
	input       clk,
	input       reset,
	
    output reg [9:0] hc,
    output reg [9:0] vc,

	output reg  hbl,
	output reg  hsync,
	output reg  vbl,
	output reg  vsync
);

// 320x240 timings

localparam HBSTART = 320;   // horz blank begin
localparam HSSTART = 350;   // horz sync begin
localparam HSEND   = 370;   // horz sync end
localparam HTOTAL  = 450;   // horz total clocks
localparam HBEND   = 0;     // horz blank end

localparam VBSTART = 240;
localparam VSSTART = 254;
localparam VSEND   = 256;
localparam VBEND   = 0;
localparam VTOTAL  = 270;

always @ (posedge clk) begin

	if (reset) begin
		hc <= 0;
		vc <= 0;
	end	else begin
        // counter
		if (hc == HTOTAL) begin
			hc <= 0;
			if (vc == VTOTAL) begin 
				vc <= 0;
			end else begin
				vc <= vc + 1'd1;
			end
		end else begin
			hc <= hc + 1'd1;
		end

        // h signals
        if ( hc == HBSTART ) begin
            hbl <= 1;
        end else if ( hc == HSSTART ) begin
            hsync <= 0;
        end else if ( hc == HSEND ) begin
            hsync <= 1;
        end else if ( hc == HBEND ) begin
            hbl <= 0;
        end

        // v signals
        if ( vc == VBSTART ) begin
            vbl <= 1;
        end else if ( vc == VSSTART ) begin
            vsync <= 0;
        end else if ( vc == VSEND ) begin
            vsync <= 1;
        end else if ( vc == VBEND) begin
            vbl <= 0;
        end
    end
end

endmodule
