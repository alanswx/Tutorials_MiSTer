//============================================================================
// Sound sample player.
// 
// Author: gaz68 (https://github.com/gaz68)
// October 2019
//
// Up to 8 channels. 16-bit signed samples.
// For DKJ analogue sounds.
//============================================================================

module dkongjr_wav_sound
(
	input		I_CLK,
	input		I_RSTn,
	input		[3:0]I_H_CNT,
	input		[11:0]I_DIV,
	input		[3:0]I_VOL,
	input		I_DMA_TRIG,
	input		I_DMA_STOP,
	input		[2:0]I_DMA_CHAN, // 8 channels
	input		[15:0]I_DMA_ADDR,
	input		[15:0]I_DMA_LEN,
	input		signed [15:0]I_DMA_DATA, // Data coming back from wave ROM

	output	[15:0]O_DMA_ADDR, // output address to wave ROM
	output	signed [15:0]O_SND
);


reg [15:0]W_DMA_ADDR;
reg signed [23:0]W_DMA_DATA;
reg [15:0]W_DMA_CNT;
reg W_DMA_EN = 1'b0;
reg [11:0]sample;
reg W_DMA_TRIG;
reg signed [15:0]W_SAMPL;
reg signed[8:0]W_VOL;

always@(posedge I_CLK or negedge I_RSTn)
begin
  
	if(! I_RSTn)begin

		W_DMA_EN			<= 1'b0;
		W_DMA_CNT		<= 0;
		W_DMA_DATA		<= 0;
		W_DMA_ADDR		<= 0;
		W_DMA_TRIG		<= 0;
		W_VOL				<= 0;
		sample			<= 0;
	 
	end else begin

		// Check for DMA trigger and enable DMA.
		W_DMA_TRIG <= I_DMA_TRIG;

		if(~W_DMA_TRIG & I_DMA_TRIG) begin

			W_DMA_ADDR  <= I_DMA_ADDR;
			W_DMA_CNT	<= 0;
			W_DMA_EN		<= 1'b1;
			W_DMA_DATA	<= 0;
			sample		<= 0;

		end else if (W_DMA_EN == 1'b1) begin

			case(I_VOL)
				4: W_VOL <= 9'sd0;		// OFF
				5: W_VOL <= 9'sd26;		// 10%
				6: W_VOL <= 9'sd52;		// 20%
				7: W_VOL <= 9'sd79;		// 30%
				8: W_VOL <= 9'sd104;		// 40%
				9: W_VOL <= 9'sd130;		// 50%
				10: W_VOL <= 9'sd156;	// 60%
				0: W_VOL <= 9'sd182;		// 70%
				1: W_VOL <= 9'sd208;		// 80%
				2: W_VOL <= 9'sd234;		// 90%
				3: W_VOL <= 9'sd255;		// 100%
				default: W_VOL <= 9'sd255;
			endcase 

			// Prefetch sample.
			if (I_H_CNT == {I_DMA_CHAN,1'b1}) begin
				//W_DMA_DATA <= I_DMA_DATA * W_VOL;
				W_DMA_DATA <= I_DMA_DATA ;
			end
			
			sample <= (sample == I_DIV-1) ? 1'b0 : sample + 1'b1;
		
			if (sample == I_DIV-1) begin
				//W_SAMPL <= W_DMA_DATA[23:8];
				W_SAMPL <= W_DMA_DATA[7:0];
				W_DMA_ADDR <= W_DMA_ADDR + 1'd1;
				W_DMA_CNT <= W_DMA_CNT + 1'd1;
				W_DMA_EN <= (W_DMA_CNT==I_DMA_LEN) || I_DMA_STOP ? 1'b0 : 1'b1;
			end
			
		end else begin

			W_DMA_ADDR	<= 0;
			W_SAMPL		<= 0;

		end
		
	end  
  
end

assign O_DMA_ADDR	= W_DMA_ADDR;
assign O_SND      = W_SAMPL;

endmodule
