//============================================================================
// Sound sample player.
// 
// Author: gaz68 (https://github.com/gaz68)
// October 2019
// Adapted by alanswx to parse the wave
//
//============================================================================

module wave_sound #(parameter SYSCLOCK = 40000000)
(
	input         I_CLK,
	input         I_RST,

	input  [27:0] I_BASE_ADDR,
	input         I_LOOP,
	input         I_PAUSE,
	
	output [27:0] O_ADDR, // output address to wave ROM
	output        O_READ, // read a byte
	input   [7:0] I_DATA,  // Data coming back from wave ROM
	input         I_READY, // data is ready

	output [15:0] O_PCM
);

reg [27:0] W_DMA_ADDR;
reg [27:0] END_ADDR;
reg        W_DMA_EN;
reg        inheader;
reg [15:0] num_channels;
reg [31:0] sample_rate;
reg [31:0] byte_rate;
reg [15:0] block_align;
reg [15:0] bits_per_sample;
reg [31:0] data_size;
reg [27:0] START_ADDR;

reg  [7:0] W_SAMPL_LSB;
reg [15:0] W_SAMPL;

reg [31:0] sum;
wire[31:0] sum_next = sum + sample_rate;

reg ce_sample;
always @(posedge I_CLK) begin
	ce_sample <= 0;
	sum <= sum_next;
	if(sum_next >= SYSCLOCK) begin
		sum <= sum_next - SYSCLOCK;
		ce_sample <= 1;
	end
end

reg read_done = 0;
always@(posedge I_CLK) begin

	if(I_RST)begin
		W_DMA_ADDR <= I_BASE_ADDR;
		W_DMA_EN	  <= 1;
		O_READ     <= 0;
		inheader   <= 1;
		read_done  <= 0;
	end
	else if (W_DMA_EN) begin
		if (I_READY) O_READ <= 0;

		if (I_READY & !O_READ & ~read_done) begin
			if (inheader) begin
				O_READ <= 1;
				case (W_DMA_ADDR[5:0])
					00: ; // R
					01: ; // I
					02: ; // F
					03: ; // F
					//22: num_channels[7:0]   <= I_DATA;
					//23: num_channels[15:8]  <= I_DATA;
					24: sample_rate[7:0]      <= I_DATA;
					25: sample_rate[15:8]     <= I_DATA;
					26: sample_rate[23:16]    <= I_DATA;
					27: sample_rate[31:24]    <= I_DATA;
					//28: byte_rate[7:0]      <= I_DATA;
					//29: byte_rate[15:8]     <= I_DATA;
					//30: byte_rate[23:16]    <= I_DATA;
					//31: byte_rate[31:24]    <= I_DATA;
					//32: block_align[7:0]    <= I_DATA;
					//33: block_align[15:8]   <= I_DATA;
					34: bits_per_sample[7:0]  <= I_DATA;
					35: bits_per_sample[15:8] <= I_DATA;
					40: data_size[7:0]        <= I_DATA;
					41: data_size[15:8]       <= I_DATA;
					42: data_size[23:16]      <= I_DATA;
					43: begin 
							data_size[31:24] <= I_DATA; 
							//$display("num_channels %x %d\n",num_channels,num_channels);
							$display("sample_rate %x %d\n",sample_rate,sample_rate);
							//$display("byte_rate %x %d\n",byte_rate,byte_rate);
							//$display("block_align%x %d\n",block_align,block_align);
							$display("bits_per_sample %x %d\n",bits_per_sample,bits_per_sample);
							$display("data_size %x %d\n",data_size,data_size);
							$display("data_size %x %d\n",data_size,data_size);
							$display("data_size %x %d\n",data_size[15:0],data_size[15:0]);
							END_ADDR <= W_DMA_ADDR + data_size[27:0] + 16'd44;
							START_ADDR <= W_DMA_ADDR + 1'd1;
							inheader <= 0;
							O_READ <= 0;
							read_done <= 1;
						end
				endcase
			end
			else if (bits_per_sample != 16) begin
				W_SAMPL     <= {I_DATA,I_DATA};
				read_done   <= 1;
			end
			else if (!W_DMA_ADDR[0]) begin
				W_SAMPL_LSB <= I_DATA;
				O_READ      <= 1;
			end
			else begin
				W_SAMPL     <= {I_DATA,W_SAMPL_LSB};
				read_done   <= 1;
			end
			
			W_DMA_ADDR <= W_DMA_ADDR + 1'd1;
		end

		if(read_done && ce_sample && !I_PAUSE) begin
			read_done <= 0;
			O_READ    <= 1;
			W_DMA_EN  <= ~(W_DMA_ADDR >= END_ADDR);
			if (W_DMA_ADDR >= END_ADDR && I_LOOP) begin
				W_DMA_EN   <= 1;
				W_DMA_ADDR <= START_ADDR;
			end
		end
	end

	if(I_RST || I_PAUSE || !W_DMA_EN) W_SAMPL <= 0;
end

assign O_ADDR = W_DMA_ADDR;
assign O_PCM  = W_SAMPL;

endmodule
