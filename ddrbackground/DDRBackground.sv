
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
assign LED_USER  = disk_light;//ioctl_download;
assign LED_DISK  = disk_light;
assign LED_POWER = 0;
wire disk_light;

wire [1:0] ar = status[15:14];

assign VIDEO_ARX = (!ar) ?  8'd4  : (ar - 1'd1);
assign VIDEO_ARY = (!ar) ?  8'd3  : 12'd0;




`include "build_id.v" 
localparam CONF_STR = {
	"IMAGE;;",
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

wire clk_sys, clk_36, clk_48;
wire pll_locked;

pll pll
(
	.refclk(CLK_50M),
	.rst(0),
	.outclk_0(clk_48),
	.outclk_1(clk_36), // 36
	.outclk_2(clk_sys),  //24
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
wire  [15:0] ioctl_dout;

wire [10:0] ps2_key;

wire [15:0] joy1 =  (joy1a | joy2a);
wire [15:0] joy2 =  (joy1a | joy2a);
wire [15:0] joy1a;
wire [15:0] joy2a;

wire [21:0] gamma_bus;

hps_io #(.STRLEN($size(CONF_STR)>>3), .WIDE(1)) hps_io
(
	.clk_sys(clk_48),
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
always @(posedge clk_48) begin
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


reg [9:0] difficulty;
always @(posedge clk_48) begin
	if (btn3_up) begin
		difficulty <= difficulty-1;

	end
	if (btn4_up) begin
		difficulty <= difficulty+1;

	end
end

  wire btn3_state, btn3_dn, btn3_up;
    debounce d_btn3 (
      .clk(clk_48),
      .i_btn(btn_left),
        .o_state(btn3_state),
        .o_ondn(btn3_dn),
        .o_onup(btn3_up)
    );
  wire btn4_state, btn4_dn, btn4_up;
    debounce d_btn4 (
      .clk(clk_48),
      .i_btn(btn_right),
        .o_state(btn4_state),
        .o_ondn(btn4_dn),
        .o_onup(btn4_up)
    );


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

wire m_cheat    = btn_cheat | joy1[8] | joy2[8];

wire hblank, vblank;
wire ohblank, ovblank;
wire hs, vs;
wire ohs, ovs;
wire [7:0] r,g,b;
wire [7:0] rr,gg,bb;
wire [7:0] outr,outg,outb;
/*
reg ce_pix;
always @(posedge clk_48) begin
       ce_pix <= !ce_pix;
end
*/

// should be 1.5MHZ
reg ce_pix;
always @(posedge clk_48) begin
        reg [2:0] div;
        div <= div + 1'd1;
        ce_pix <= !div;
end


arcade_video #(256,24) arcade_video
(
	.*,

	.clk_video(clk_48),

	.RGB_in({outr,outg,outb}),
	.HBlank(ohblank),
	.VBlank(ovblank),
	.HSync(ohs),
	.VSync(ovs),

	.forced_scandoubler(0),
	.fx(status[5:3])
);





wire [7:0] debug;
wire [44:0] probe_0= {
   1'b0,img_addr[27:24],
   1'b0,img_addr[23:20],
   1'b0,img_addr[19:16],
   1'b0,img_addr[15:12],
   1'b0,img_addr[11:8],
   1'b0,img_addr[7:4],
	1'b0,img_addr[3:0],
	5'h10,
	toggle_switch? 5'h12:5'h13
	};
	
//wire [9:0] probe_1= {2'b0,rom_d};
wire [45:0] probe_1= {36'b0,1'b0,debug[7:4],1'b0,debug[3:0]};

wire de;

ovo #(.COLS(9), .LINES(2), .RGB(24'hFF00FF)) diff (
        .i_r(r),
        .i_g(g),
        .i_b(b),
        .i_hs(~hs),
        .i_vs(~vs),
        .i_de(de),
        .i_hblank(hblank),
        .i_vblank(vblank),
        .i_en(ce_pix),
        .i_clk(clk_48),

        .o_r(outr),
        .o_g(outg),
        .o_b(outb),
        .o_hs(ohs),
        .o_vs(ovs),
        .o_de(ode),
        .o_hblank(ohblank),
        .o_vblank(ovblank),

        .ena(1'b1),

        .in0(probe_0),
        .in1(probe_1)
);

wire [9:0] hcnt;

soc soc(
   .pixel_clock(ce_pix), // wrong
   .reset(reset), // wrong
   .VGA_HS(hs),
   .VGA_VS(vs),
   .VGA_R(rr),
   .VGA_G(gg),
   .VGA_B(bb),
   .VGA_HBLANK(hblank),
   .VGA_VBLANK(vblank),
   .VGA_DE(de),
   .hcnt(hcnt)
);



reg toggle_switch=1'b1;
  
 always @(posedge clk_48) begin
   if (btn1_up==1'b1) 
    toggle_switch<=~toggle_switch;
 end
  
  wire btn0_state, btn0_dn, btn0_up;
    debounce d_btn0 (
      .clk(clk_48),
      .i_btn(btn_up),
        .o_state(btn0_state),
        .o_ondn(btn0_dn),
        .o_onup(btn0_up)
    );

  wire btn1_state, btn1_dn, btn1_up;
    debounce d_btn1 (
      .clk(clk_48),
      .i_btn(btn_fire),
        .o_state(btn1_state),
        .o_ondn(btn1_dn),
        .o_onup(btn1_up)
    );

wire reset = status[0] | buttons[1] ; 



wire [15:0] audio_l, audio_r;
assign AUDIO_S = 1;
assign AUDIO_L =  0  ;
assign AUDIO_R =  0  ;




////////////////////////////  MEMORY  ///////////////////////////////////
//
//

////////////////////////////  DDRAM  ///////////////////////////////////
//
//
wire img_load = ioctl_download && (ioctl_index == 1);

wire img_data_ready;
assign DDRAM_CLK = clk_48;


wire img_save_data_ready;
wire [31:0] img_data_to_bram;
reg img_data_to_bram_req=1;
wire img_load_data_ready;

ddram ddram
(
	.*,

	// use two 8 bit values to do a write.. 
	.ch1_addr({1'b0,ioctl_addr[26:1]}),
	.ch1_din(ioctl_dout), // 16 bits
	.ch1_dout(), // 64 bits
	.ch1_req(img_wr  ),
	.ch1_rnw(~img_wr ),
	.ch1_ready(img_save_data_ready),

	.ch2_addr(img_addr[27:1]),
	.ch2_din(32'b0), // 32 bits
	.ch2_dout(img_data_to_bram), // 32 bits
	.ch2_req(img_data_to_bram_req),
	.ch2_rnw(1'b1), // read only
	.ch2_ready(img_load_data_ready),

	.ch3_addr(25'b0),
	.ch3_din(16'b0),  // 16 bits
	.ch3_dout(),  // 16 bits
	.ch3_req(1'b0),
	.ch3_rnw(1'b1),
	.ch3_ready(),

	.ch4_addr(27'b0),
	.ch4_din(64'b0),  // 64 bits
	.ch4_dout(),  // 64 bits
	.ch4_req(1'b0),
	.ch4_rnw(1'b1),
	.ch4_ready(),
   
   .ch5_addr(27'b0),
   .ch5_din(64'b0),  // always writes -- 64bits
   .ch5_req(1'b0),
   .ch5_ready()
   
);



//
//  signals for DDRAM
//
// NOTE: the img_wr (we) line doesn't want to stay high. It needs to be high to start, and then can't go high until wav_data_ready
// we hold the ioctl_wait high (stop the data from HPS) until we get waV_data_ready

reg img_wr;
always @(posedge clk_48) begin
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
always @(posedge clk_48) begin
        reg old_load;

        old_load <= img_load;
        if(old_load & ~img_load) img_loaded <= 1;
end





reg  [27:0]  img_addr=28'b0;

reg start_img_load = 1'b1;


// width is 256, make it 2 lines big
wire [31:0] pic_data;

dpram #(.addr_width_g(9),.data_width_g(32))
address_table(
	.clock_a(clk_48),
	.address_a(img_addr[10:2]),
	.data_a(img_data_to_bram), 
	.wren_a(img_load_data_ready),
	
	// read from our line buffer and output to screen
	.clock_b(clk_48),
	.address_b(pic_addr[8:0]),
	.q_b(pic_data)
);

//
//  we need to load a line of bram with the output of DDR
//

// 32 bits





assign r = bg_r;
assign g = bg_g;
assign b = bg_b;

reg        pic_req;
reg [24:0] pic_addr;
reg  [7:0] bg_r,bg_g,bg_b,bg_a;


reg [1:0] state = 2'b0;


always @(posedge clk_48) begin
        reg old_vs;
        reg use_bg = 0;


        pic_req <= 0;
		  
		  
		  
		  
		  case (state)
			2'b00:  // IDLE
			begin
				img_data_to_bram_req<=0;
				// start loading ram at the end of a line
				if (pic_addr[8:0]=='d255)   
					state<=2'b01;
            else if (pic_addr[8:0]=='d511) 
					state<=2'b01;
			end
			2'b01:  // SETUP READ
			begin
				img_addr<=img_addr+'d4;
				img_data_to_bram_req<=1;
				state <= 2'b10;
			end
			2'b10:  // WAIT
			begin
				if (img_load_data_ready) begin  // if data isn't ready, sit and spin in this state
					
				   if (img_addr[9:0]==10'b1111111100) begin  // if we have read in 255 bytes, we go back to idle
						state<=2'b00;
						img_data_to_bram_req<=0;
					end
					else begin
						//img_addr<=img_addr+'d4;
						//img_data_to_bram_req<=1;
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
                        {bg_a,bg_r,bg_g,bg_b} <= pic_data;
                        if(~(hblank|vblank)) begin
                                pic_addr <= pic_addr + 2'd1;
                                pic_req <= 1;
                        end

                        if(~old_vs & vs) begin
                                pic_addr <= 0;
										  img_addr<=0;
                                pic_req <= 1;
                        end
                end
        end
        else begin
                {bg_a,bg_b,bg_g,bg_r} <= 0;
        end
end



endmodule


module debounce(
    input clk,
    input i_btn,
    output reg o_state,
    output o_ondn,
    output o_onup
    );

    // sync with clock and combat metastability
    reg sync_0, sync_1;
    always @(posedge clk) sync_0 <= i_btn;
    always @(posedge clk) sync_1 <= sync_0;

    // 2.6 ms counter at 100 MHz
  reg [9:0] counter;
    wire idle = (o_state == sync_1);
    wire max = &counter;

    always @(posedge clk)
    begin
        if (idle)
            counter <= 0;
        else
        begin
            counter <= counter + 1;
            if (max)
                o_state <= ~o_state;
        end
    end

    assign o_ondn = ~idle & max & ~o_state;
    assign o_onup = ~idle & max & o_state;
endmodule

