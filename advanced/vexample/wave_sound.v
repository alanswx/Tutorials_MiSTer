//============================================================================
// Sound sample player.
// 
// Author: gaz68 (https://github.com/gaz68)
// October 2019
// Adapted by alanswx to parse the wave
//
//============================================================================

module wave_sound
(
	input		I_CLK,
	input    [31:0] I_CLK_SPEED,
	input		I_RSTn,
	input		[3:0]I_H_CNT, // used to interleave data reads
	input		I_DMA_TRIG,
	input		I_DMA_STOP,
	input		[2:0]I_DMA_CHAN, // 8 channels
	input		[16:0]I_DMA_ADDR,
	input		[7:0]I_DMA_DATA, // Data coming back from wave ROM

	output	[16:0]O_DMA_ADDR, // output address to wave ROM
	output   [7:0] debug,
	output	signed [15:0]O_SND
);

reg [7:0] byte_0;
reg [11:0]W_DIV;
reg [16:0]W_DMA_ADDR;
reg [16:0]W_DMA_LEN;
reg signed [7:0]W_DMA_DATA;
reg signed [7:0]W_SAMPLE_TOP;
reg [16:0]W_DMA_CNT;
reg W_DMA_EN = 1'b0;
reg [11:0]sample;
reg W_DMA_TRIG;
reg signed [15:0]W_SAMPL;
reg inheader = 1'b1;
reg [15:0] num_channels;
reg [31:0] sample_rate;
reg [31:0] byte_rate;
reg [15:0] block_align;
reg [15:0] bits_per_sample;
reg [31:0] data_size;

reg div;

assign debug=byte_0;

always@(posedge I_CLK or negedge I_RSTn)
begin
  
	if(! I_RSTn)begin

		W_DMA_EN		<= 1'b0;
		W_DMA_CNT		<= 0;
		W_DMA_DATA		<= 0;
		W_DMA_ADDR		<= 0;
		W_DMA_TRIG		<= 0;
		sample			<= 0;
		inheader <= 1'b1;
		div<=0;
	 
	end else begin

		// Check for DMA trigger and enable DMA.
		W_DMA_TRIG <= I_DMA_TRIG;

		if(~W_DMA_TRIG & I_DMA_TRIG) begin
			$display("sound trigger\n");

			W_DMA_ADDR  <= I_DMA_ADDR;
			W_DMA_CNT	<= 0;
			W_DMA_EN	<= 1'b1;
			W_DMA_DATA	<= 0;
			W_SAMPLE_TOP <=0;
			sample		<= 0;
			inheader <= 1'b1;
			byte_0 <=0;
			div<=0;

		end else if (W_DMA_EN == 1'b1) begin


			// Prefetch sample.
			if (I_H_CNT == {I_DMA_CHAN,1'b1}) begin
				div<=~div;
				if (div) begin
				
				if (inheader==1'b1) begin
				
					W_DMA_DATA <= I_DMA_DATA ;
					$display("W_DMA_CNT %x W_DMA_DATA %x %c\n",W_DMA_CNT,W_DMA_DATA,W_DMA_DATA);
					case (W_DMA_CNT)
						'd01: ; // R
						'd02: ; // I
						'd03: ; // F
						'd04: ; // F
						'd23: num_channels[7:0]  <= W_DMA_DATA ;
						'd24: num_channels[15:8] <= W_DMA_DATA;
						'd25: sample_rate[7:0]   <= W_DMA_DATA;
						'd26: sample_rate[15:8]  <= W_DMA_DATA;
						'd27: sample_rate[23:16] <= W_DMA_DATA;
						'd28: sample_rate[31:24] <= W_DMA_DATA;
						'd29: byte_rate[7:0]   <= W_DMA_DATA;
						'd30: byte_rate[15:8]  <= W_DMA_DATA;
						'd31: byte_rate[23:16] <= W_DMA_DATA;
						'd32: byte_rate[31:24] <= W_DMA_DATA;
						'd33: block_align[7:0]  <= W_DMA_DATA ;
						'd34: block_align[15:8] <= W_DMA_DATA;
						'd35: bits_per_sample[7:0]  <= W_DMA_DATA ;
						'd36: bits_per_sample[15:8] <= W_DMA_DATA;
						'd41: data_size[7:0]  <= W_DMA_DATA;
						'd42: data_size[15:8] <= W_DMA_DATA;
						'd43: data_size[23:16] <= W_DMA_DATA;
						'd44: 
							begin 
								data_size[31:24] <= W_DMA_DATA; 
								$display("num_channels %x %d\n",num_channels,num_channels);
								$display("sample_rate %x %d\n",sample_rate,sample_rate);
								$display("byte_rate %x %d\n",byte_rate,byte_rate);
								$display("block_align%x %d\n",block_align,block_align);
								$display("bits_per_sample %x %d\n",bits_per_sample,bits_per_sample);
								$display("data_size %x %d\n",data_size,data_size);
								$display("data_size %x %d\n",data_size,data_size);
								$display("data_size %x %d\n",data_size[15:0],data_size[15:0]);
								W_DMA_LEN<=data_size[16:0]+16'd45; // needs to be odd 
								W_DMA_ADDR <= W_DMA_ADDR - 2'd2;
								inheader <= 1'b0;
								byte_0 <= bits_per_sample[7:0];
								// for 24Mhz -- we should lookup the clock as well
								//W_DIV <= I_CLK_SPEED / sample_rate; -- dont' divide in verilog
								case (sample_rate)
									'd44100: W_DIV<=12'd544;
									'd48000: W_DIV<=12'd535;
									'd32000: W_DIV<=12'd750;
									'd22050: W_DIV<=12'd1088;
									'd11025: W_DIV<=12'd2177;
									'd8000:  W_DIV<=12'd3000;
									default: W_DIV<=12'd3000;
								endcase
							end
					endcase
					W_DMA_CNT <= W_DMA_CNT + 1'd1;
					W_DMA_ADDR <= W_DMA_ADDR + 1'd1;
				end
				else if ( bits_per_sample==16'd16 && W_DMA_ADDR[0]==1'b0)
				begin
					W_SAMPLE_TOP<=I_DMA_DATA;
$display("W_DMA_CNT %d W_DMA_LEN %d W_DIV %d W_DMA_EN %x ",W_DMA_CNT,W_DMA_LEN,W_DIV,W_DMA_EN);
$display("grab top %x %x %x",W_SAMPLE_TOP,W_DMA_ADDR,I_DMA_DATA);
					W_DMA_CNT <= W_DMA_CNT + 1'd1;
					W_DMA_ADDR <= W_DMA_ADDR + 1'd1;
				end else begin
//$display("grab dms_data %x %x %x %x %d",W_DMA_ADDR,I_DMA_DATA,sample,W_DIV,bits_per_sample);
					W_DMA_DATA<= I_DMA_DATA ;
				end

			end
			end
			
			if(inheader==0) begin	
			

				sample <= (sample == W_DIV-1) ? 12'b0 : sample + 1'b1;
		
				if (sample == W_DIV-1) begin
					//W_SAMPL <= W_DMA_DATA[23:8];
					if (bits_per_sample==16) begin
						//W_SAMPL <= {W_SAMPLE_TOP,W_DMA_DATA};
						W_SAMPL <= {W_DMA_DATA,W_SAMPLE_TOP};
					end else begin
						W_SAMPL <= {8'b0,W_DMA_DATA[7:0]};
					end
				$display("w_SAMPL: %x addr %x",W_SAMPL,W_DMA_ADDR);	
					W_DMA_ADDR <= W_DMA_ADDR + 1'd1;
					W_DMA_CNT <= W_DMA_CNT + 1'd1;
					W_DMA_EN <= (W_DMA_CNT==W_DMA_LEN) || I_DMA_STOP ? 1'b0 : 1'b1;
				end
			end  
			
		end else begin

			W_DMA_ADDR	<= 0;
			W_SAMPL		<= 0;

		end
	end
		
  
end

assign O_DMA_ADDR	= W_DMA_ADDR;
/* verilator lint_off WIDTH */ 
assign O_SND      = W_SAMPL;
/* verilator lint_on WIDTH */

endmodule
