
//=========================================================
//  DDR Background
//
//  This core will display raw image data using DDR
//  onto the framebuffer
//
//                        Copyright (c) 2021 alanswx
//=========================================================

module emu
(
	//Master input clock
	input         CLK_50M,

	//Async reset from top-level module.
	//Can be used as initial reset.
	input         RESET,

	//Must be passed to hps_io module
	inout  [45:0] HPS_BUS,

	//Base video clock. Usually equals to CLK_SYS.
	output        CLK_VIDEO,

	//Multiple resolutions are supported using different CE_PIXEL rates.
	//Must be based on CLK_VIDEO
	output        CE_PIXEL,

	//Video aspect ratio for HDMI. Most retro systems have ratio 4:3.
	output [11:0] VIDEO_ARX,
	output [11:0] VIDEO_ARY,

	output  [7:0] VGA_R,
	output  [7:0] VGA_G,
	output  [7:0] VGA_B,
	output        VGA_HS,
	output        VGA_VS,
	output        VGA_DE,    // = ~(VBlank | HBlank)
	output        VGA_F1,
	output [1:0]  VGA_SL,
	output        VGA_SCALER, // Force VGA scaler

	input  [11:0] HDMI_WIDTH,
	input  [11:0] HDMI_HEIGHT,

	// Use framebuffer from DDRAM (USE_FB=1 in qsf)
	// FB_FORMAT:
	//    [2:0] : 011=8bpp(palette) 100=16bpp 101=24bpp 110=32bpp
	//    [3]   : 0=16bits 565 1=16bits 1555
	//    [4]   : 0=RGB  1=BGR (for 16/24/32 modes)
	//
	// FB_STRIDE either 0 (rounded to 256 bytes) or multiple of 16 bytes.
	output        FB_EN,
	output  [4:0] FB_FORMAT,
	output [11:0] FB_WIDTH,
	output [11:0] FB_HEIGHT,
	output [31:0] FB_BASE,
	output [13:0] FB_STRIDE,
	input         FB_VBL,
	input         FB_LL,
	output        FB_FORCE_BLANK,

	// Palette control for 8bit modes.
	// Ignored for other video modes.
	output        FB_PAL_CLK,
	output  [7:0] FB_PAL_ADDR,
	output [23:0] FB_PAL_DOUT,
	input  [23:0] FB_PAL_DIN,
	output        FB_PAL_WR,

	output        LED_USER,  // 1 - ON, 0 - OFF.

	// b[1]: 0 - LED status is system status OR'd with b[0]
	//       1 - LED status is controled solely by b[0]
	// hint: supply 2'b00 to let the system control the LED.
	output  [1:0] LED_POWER,
	output  [1:0] LED_DISK,

	input         CLK_AUDIO, // 24.576 MHz
	output [15:0] AUDIO_L,
	output [15:0] AUDIO_R,
	output        AUDIO_S,    // 1 - signed audio samples, 0 - unsigned

	//High latency DDR3 RAM interface
	//Use for non-critical time purposes
	output        DDRAM_CLK,
	input         DDRAM_BUSY,
	output  [7:0] DDRAM_BURSTCNT,
	output [28:0] DDRAM_ADDR,
	input  [63:0] DDRAM_DOUT,
	input         DDRAM_DOUT_READY,
	output        DDRAM_RD,
	output [63:0] DDRAM_DIN,
	output  [7:0] DDRAM_BE,
	output        DDRAM_WE,

	// Open-drain User port.
	// 0 - D+/RX
	// 1 - D-/TX
	// 2..6 - USR2..USR6
	// Set USER_OUT to 1 to read from USER_IN.
	input   [6:0] USER_IN,
	output  [6:0] USER_OUT
);


assign VGA_F1    = 0;
assign USER_OUT  = '1;
assign VGA_SCALER= 0;
assign LED_USER  = ioctl_download;
assign LED_DISK  = 0;
assign LED_POWER = 0;

wire [1:0] ar = status[15:14];

assign VIDEO_ARX = (!ar) ?  8'd4  : (ar - 1'd1);
assign VIDEO_ARY = (!ar) ?  8'd3  : 12'd0;




`include "build_id.v" 



localparam CONF_STR = {
	"IMAGE512;;",
	"F1,img;",
	"H0OEF,Aspect ratio,Original,Full Screen,[ARC1],[ARC2];",
	"O35,Scandoubler Fx,None,HQ2x,CRT 25%,CRT 50%,CRT 75%;",
	"-;",
	"O7,Loop,No,Yes;",
	"-;",
	"R0,Reset;",
	"J1,Fire,Start 1P,Start 2P,Coin,Cheat;",
	"jn,A,Start,Select,R,L;",
	"V,v",`BUILD_DATE
};

////////////////////   CLOCKS   ///////////////////

wire clk_79,clk_39,clk_19,clk_10;
wire clk_sys = clk_79;
wire pll_locked;

pll pll
(
	.refclk(CLK_50M),
	.rst(0),
	.outclk_0(clk_79), // 79.48
	.outclk_1(clk_39), // 39.74
	.outclk_2(clk_19), // 19.87
	.outclk_3(clk_10), // 9.935
	.locked(pll_locked)
);


///////////////////////////////////////////////////

wire [31:0] status;
wire  [1:0] buttons;
wire        forced_scandoubler;
wire        direct_video;

wire        ioctl_download;
wire  [7:0] ioctl_index;
wire        ioctl_wr;
wire        ioctl_wait;
wire [26:0] ioctl_addr;
wire  [7:0] ioctl_dout;

wire [10:0] ps2_key;

wire [15:0] joy1 =  (joy1a | joy2a);
wire [15:0] joy2 =  (joy1a | joy2a);
wire [15:0] joy1a;
wire [15:0] joy2a;

wire [21:0] gamma_bus;

hps_io #(.STRLEN($size(CONF_STR)>>3), .WIDE(0)) hps_io
(
	.clk_sys(clk_sys),
	.HPS_BUS(HPS_BUS),

	.conf_str(CONF_STR),

	.buttons(buttons),
	.status(status),
	.status_menumask(direct_video),
	.forced_scandoubler(forced_scandoubler),
	.gamma_bus(gamma_bus),
	.direct_video(direct_video),

	.ioctl_download(ioctl_download),
	.ioctl_wr(ioctl_wr),
	.ioctl_addr(ioctl_addr),
	.ioctl_dout(ioctl_dout),
	.ioctl_index(ioctl_index),
	.ioctl_wait(ioctl_wait),

	.joystick_0(joy1a),
	.joystick_1(joy2a),
	.ps2_key(ps2_key)
);


wire       pressed = ps2_key[9];
wire [8:0] code    = ps2_key[8:0];
always @(posedge clk_sys) begin
	reg old_state;
	old_state <= ps2_key[10];
	
	if(old_state != ps2_key[10]) begin
		casex(code)
			'hX75: btn_up          <= pressed; // up
			'hX72: btn_down        <= pressed; // down
			'hX6B: btn_left        <= pressed; // left
			'hX74: btn_right       <= pressed; // right
			'h029: btn_fire        <= pressed; // space
			'h014: btn_fire        <= pressed; // ctrl

			'h005: btn_start_1     <= pressed; // F1
			'h006: btn_start_2     <= pressed; // F2
			'h004: btn_coin        <= pressed; // F3
			'h00C: btn_cheat       <= pressed; // F4

			// JPAC/IPAC/MAME Style Codes
			'h016: btn_start_1     <= pressed; // 1
			'h01E: btn_start_2     <= pressed; // 2
			'h02E: btn_coin_1      <= pressed; // 5
			'h036: btn_coin_2      <= pressed; // 6
			'h02D: btn_up_2        <= pressed; // R
			'h02B: btn_down_2      <= pressed; // F
			'h023: btn_left_2      <= pressed; // D
			'h034: btn_right_2     <= pressed; // G
			'h01C: btn_fire_2      <= pressed; // A
		endcase
	end
end

reg btn_up    = 0;
reg btn_down  = 0;
reg btn_right = 0;
reg btn_left  = 0;
reg btn_coin  = 0;
reg btn_fire  = 0;
reg btn_cheat = 0;

reg btn_start_1=0;
reg btn_start_2=0;
reg btn_coin_1=0;
reg btn_coin_2=0;
reg btn_up_2=0;
reg btn_down_2=0;
reg btn_left_2=0;
reg btn_right_2=0;
reg btn_fire_2=0;

wire no_rotate = status[2];
wire m_fire     = btn_fire    | joy1[4];
wire m_fire_2   = btn_fire_2  | joy2[4];
wire m_start    = btn_start_1 | joy1[5] | joy2[5];
wire m_start_2  = btn_start_2 | joy1[6] | joy2[6];
wire m_coin     = btn_coin    | joy1[7] | joy2[7] | btn_coin_1 | btn_coin_2;
wire m_right = btn_right | joy1[0];
wire m_left = btn_left | joy1[1];
wire m_cheat    = btn_cheat | joy1[8] | joy2[8];

wire hblank, vblank;
wire hs, vs;
wire [7:0] r,g,b;




assign VGA_HS=hs;
assign VGA_VS=vs;
assign VGA_R=r;
assign VGA_G=g;
assign VGA_B=b;
assign VGA_DE = ~(hblank|vblank);
assign CLK_VIDEO = clk_sys;

assign CE_PIXEL =  ce_pix;

reg ce_pix;
always @(posedge clk_sys) begin
        reg [2:0] div;
        div <= div + 1'd1;
        ce_pix <= !div;
end


video video(
  .clk_vid(ce_pix),
  .hsync(hs),
  .vsync(vs),
  .hblank(hblank),
  .vblank(vblank),
  .hpos(hpos),
  .vpos(vpos)
);











reg toggle_switch=1'b1;
  


wire reset = status[0] | buttons[1] ; 



wire [15:0] audio_l, audio_r;
assign AUDIO_S = 1;
assign AUDIO_L =  0  ;
assign AUDIO_R =  0  ;


////////////////////////////  IMAGE INFO  ///////////////////////////////
//
//    [ pointer ]                                [64 bits]
//    [width] [height] [ # of frames ]           [16 bits][16 bits][32 bits]
//    [ palette ]                                [32 bits * 256 -> 1024 bytes]
//    [img - frame 0]                            [512 bytes * 240 bytes -> 122880 ]
//    [img - frame 1]
//    etc


//
//  At VBlank -- load the pointer
//  Load the header
//  jump to image and load palette
//  after vblank - start loading image data as is..
//

////////////////////////////  MEMORY  ///////////////////////////////////
//
//

////////////////////////////  DDRAM  ///////////////////////////////////
//
//
wire img_load = ioctl_download && (ioctl_index == 1);

wire img_data_ready;
assign DDRAM_CLK = clk_sys;


wire [63:0] img_data_to_bram;
reg img_data_to_bram_req=1;
wire img_load_data_ready;

// we can change this to do burst, and get a line at a time
// if we do that, we need to change the state machine because
// it will ask for the start address of the line, then it will give us "ready" 8 times - the 
// ddram module would need another state to handle this

ddram ddram
(
	.*,

	.ch1_addr(img_addr[27:1]),
	.ch1_dout(img_data_to_bram),
	.ch1_din(64'b0),
	.ch1_rnw(1'b1),
	.ch1_req(img_data_to_bram_req),
	.ch1_ready(img_load_data_ready)
	
);

wire img_save_data_ready = img_load ? img_load_data_ready :0;




//
//  signals for DDRAM
//
// NOTE: the img_wr (we) line doesn't want to stay high. It needs to be high to start, and then can't go high until wav_data_ready
// we hold the ioctl_wait high (stop the data from HPS) until we get waV_data_ready

reg img_wr;
always @(posedge clk_sys) begin
        reg old_reset;

        old_reset <= reset;
        if(~old_reset && reset) ioctl_wait <= 0;

        img_wr <= 0;
        if(ioctl_wr & img_load) begin
                ioctl_wait <= 1;
                img_wr <= 1;
        end
        else if(~img_wr & ioctl_wait & img_save_data_ready) begin
                ioctl_wait <= 0;
        end
end


reg img_loaded = 0;
always @(posedge clk_sys) begin
        reg old_load;

        old_load <= img_load;
        if(old_load & ~img_load) img_loaded <= 1;
end


wire [10:0] hpos;
wire [9:0] vpos;


reg  [27:0]  frame_start=28'b0;
reg  [27:0]  offset_start=0;
reg  [27:0]  img_addr={18'b0,10'b0111111000};
reg  [10:0]  img_local_addr='d0;


 pal_ram pal_ram(
	.wrclock(clk_sys),
	.data(img_data_to_bram), // 64 bit
	.wraddress(pal_addr[9:3]), // 6:0
	.wren(img_load_data_ready),


	.rdclock(clk_sys), // 
	.rdaddress(pic_data), 
	.q(rgb_data) // 32 bit

);



ram64_8 lineram 
(
	.wrclock(clk_sys),
	.data(img_data_to_bram), // 64 bit
	.wraddress(img_addr[9:3]), // 6:0
	.wren(img_load_data_ready),
	.rdclock(clk_sys), // 
	.rdaddress(pic_addr[9:0]), // 9:0
	.q(pic_data) // 8 bit
);
/*
module ram64_8 (
	data,
	rdaddress,
	rdclock,
	wraddress,
	wrclock,
	wren,
	q);

	input	[63:0]  data;
	input	[8:0]  rdaddress;
	input	  rdclock;
	input	[5:0]  wraddress;
	input	  wrclock;
	input	  wren;
	output	[7:0]  q;
	*/

reg start_img_load = 1'b1;


// width is 256, make it 2 lines big
wire [7:0] pic_data;
/*
dpram #(.addr_width_g(10),.data_width_g(8))
address_table(
	.clock_a(clk_sys),
	.address_a(img_addr[9:0]),
	.data_a(img_data_to_bram), 
	.wren_a(img_load_data_ready),
	
	// read from our line buffer and output to screen
	.clock_b(clk_sys),
	.address_b(pic_addr[9:0]),
	.q_b(pic_data)
);
*/
//
//  we need to load a line of bram with the output of DDR
//

// 32 bits




// 3 3 2
assign r = {bg_r,bg_r,bg_r[1:0]};
assign g = {bg_g,bg_g,bg_g[1:0]};
assign b = {bg_b,bg_b,bg_b,bg_b};

reg        pic_req;
reg [24:0] pic_addr;
reg  [2:0] bg_r,bg_g;
reg  [1:0] bg_b;

reg [16:0] frame;
reg [1:0] state = 2'b01;


reg m_fire_r;


reg m_right_r;
reg m_left_r;
always @(posedge clk_sys) begin
        reg old_vs;
        reg use_bg = 0;

        pic_req <= 0;
		  
		  

			if (m_fire && (offset_start==0) && ~m_fire_r) 
			begin
			  offset_start<='hF00000;
			  frame<=127;
			end
			else if (m_fire && ~m_fire_r) begin
			  offset_start<=0;
			  frame<=127;
			end

  
  

		  
		  if (m_right && ~m_right_r) begin
				frame_start <= frame_start + 'h1E000;
		  end
		  if (m_left && ~m_left_r) begin
				frame_start <= frame_start - 'h1E000;
		  end
		  
		  
		  case (state)
			2'b00:  // IDLE
			begin
				img_data_to_bram_req<=0;
				// start loading ram at the end of a line
				if (pic_addr[9:0]=='d511)   
					state<=2'b01;
            else if (pic_addr[9:0]=='d1023) 
					state<=2'b01;
			end
			2'b01:  // SETUP READ
			begin
				img_addr<=img_addr+'d8;
				img_data_to_bram_req<=1;
				state <= 2'b10;
			end
			2'b10:  // WAIT
			begin
				if (img_load_data_ready) begin  // if data isn't ready, sit and spin in this state
					
				   if (img_addr[8:0]==9'b111111000) begin  // if we have read in 511 bytes, we go back to idle
					                       
						state<=2'b00;
						img_data_to_bram_req<=0;
					end
					else begin
						state<=2'b01;
						img_data_to_bram_req<=0;
					end
				end
			end
			default:
			begin
			end
		  endcase
		  
        if(img_loaded) begin
                if(ce_pix) begin
                        old_vs <= vs;
                        {bg_r,bg_g,bg_b} <= pic_data;
                        if(~(hblank|vblank)) begin
                                pic_addr <= pic_addr + 2'd1;
                                pic_req <= 1;
                        end

                        if(~old_vs & vs) begin
                                pic_addr <= 0;
										  
										  
										  if (status[7]) begin
										  
												frame_start<=frame_start+ 'h1E000;
												frame<=frame+1;
												img_addr<=frame_start+'h1E000;
												
												if (frame=='d127) begin
													img_addr<=0;
													frame_start<=offset_start;
													img_addr<=offset_start;
													frame<=0;
												end
											end else begin
												img_addr<=frame_start;
										  end
                                pic_req <= 1;
                        end
                end
        end
        else begin
                {bg_b,bg_g,bg_r} <= 0;
        end
		  
		  
		  m_right_r<=m_right;
		  m_left_r<=m_left;
		  m_fire_r<=m_fire;  

 end


endmodule



