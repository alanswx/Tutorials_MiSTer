//============================================================================
//  Arcade: Zaxxon
//
//  Port to MiSTer
//  Copyright (C) 2017 Sorgelig
//
//  This program is free software; you can redistribute it and/or modify it
//  under the terms of the GNU General Public License as published by the Free
//  Software Foundation; either version 2 of the License, or (at your option)
//  any later version.
//
//  This program is distributed in the hope that it will be useful, but WITHOUT
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
//  more details.
//
//  You should have received a copy of the GNU General Public License along
//  with this program; if not, write to the Free Software Foundation, Inc.,
//  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//============================================================================

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
	output        VGA_CLK,

	//Multiple resolutions are supported using different VGA_CE rates.
	//Must be based on CLK_VIDEO
	output        VGA_CE,

	output  [7:0] VGA_R,
	output  [7:0] VGA_G,
	output  [7:0] VGA_B,
	output        VGA_HS,
	output        VGA_VS,
	output        VGA_DE,    // = ~(VBlank | HBlank)
	output        VGA_F1,

	//Base video clock. Usually equals to CLK_SYS.
	output        HDMI_CLK,

	//Multiple resolutions are supported using different HDMI_CE rates.
	//Must be based on CLK_VIDEO
	output        HDMI_CE,

	output  [7:0] HDMI_R,
	output  [7:0] HDMI_G,
	output  [7:0] HDMI_B,
	output        HDMI_HS,
	output        HDMI_VS,
	output        HDMI_DE,   // = ~(VBlank | HBlank)
	output  [1:0] HDMI_SL,   // scanlines fx

	//Video aspect ratio for HDMI. Most retro systems have ratio 4:3.
	output  [7:0] HDMI_ARX,
	output  [7:0] HDMI_ARY,

	output        LED_USER,  // 1 - ON, 0 - OFF.

	// b[1]: 0 - LED status is system status OR'd with b[0]
	//       1 - LED status is controled solely by b[0]
	// hint: supply 2'b00 to let the system control the LED.
	output  [1:0] LED_POWER,
	output  [1:0] LED_DISK,

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
assign LED_USER  = disk_light;//ioctl_download;
assign LED_DISK  = disk_light;
assign LED_POWER = 0;
wire disk_light;

assign HDMI_ARX = status[1] ? 8'd16 : 8'd4;
assign HDMI_ARY = status[1] ? 8'd9  : 8'd3;


`include "build_id.v" 
localparam CONF_STR = {
	"SOUND;;",
	"F1,wav;",
	"H0O1,Aspect Ratio,Original,Wide;",
	"H0O2,Orientation,Vert,Horz;",
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
wire [24:0] ioctl_addr;
wire  [7:0] ioctl_data;

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
	.ioctl_dout(ioctl_data),
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


reg [9:0] difficulty;
always @(posedge clk_sys) begin
	if (btn3_up) begin
		difficulty <= difficulty-1;

	end
	if (btn4_up) begin
		difficulty <= difficulty+1;

	end
end

  wire btn3_state, btn3_dn, btn3_up;
    debounce d_btn3 (
      .clk(clk_sys),
      .i_btn(btn_left),
        .o_state(btn3_state),
        .o_ondn(btn3_dn),
        .o_onup(btn3_up)
    );
  wire btn4_state, btn4_dn, btn4_up;
    debounce d_btn4 (
      .clk(clk_sys),
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
wire [7:0] r,g;
wire [7:0] b;
wire [7:0] outr,outg;
wire [7:0] outb;
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


arcade_video #(256,224,24) arcade_video
(
	.*,

	.clk_video(clk_48),

	.RGB_in({outr,outg,outb}),
	.HBlank(ohblank),
	.VBlank(ovblank),
	.HSync(ohs),
	.VSync(ovs),

	.forced_scandoubler(0),
	.no_rotate(1),
	.rotate_ccw(0),
	.fx(status[5:3])
);




wire [15:0] audio_l;
wire [15:0] audio_r;
assign AUDIO_L = audio_l;
assign AUDIO_R = audio_r;
assign AUDIO_S = 1; 

wire [7:0] debug;
wire [44:0] probe_0= {
   1'b0,wav_addr[27:24],
   1'b0,wav_addr[23:20],
   1'b0,wav_addr[19:16],
   1'b0,wav_addr[15:12],
   1'b0,wav_addr[11:8],
   1'b0,wav_addr[7:4],
	1'b0,wav_addr[3:0],
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
   .VGA_R(r),
   .VGA_G(g),
   .VGA_B(b),
   .VGA_HBLANK(hblank),
   .VGA_VBLANK(vblank),
   .VGA_DE(de),
   .hcnt(hcnt)
);



reg toggle_switch=1'b1;
  
 always @(posedge clk_sys) begin
   if (btn1_up==1'b1) 
    toggle_switch<=~toggle_switch;
 end
  
  wire btn0_state, btn0_dn, btn0_up;
    debounce d_btn0 (
      .clk(clk_sys),
      .i_btn(btn_up),
        .o_state(btn0_state),
        .o_ondn(btn0_dn),
        .o_onup(btn0_up)
    );

  wire btn1_state, btn1_dn, btn1_up;
    debounce d_btn1 (
      .clk(clk_sys),
      .i_btn(btn_fire),
        .o_state(btn1_state),
        .o_ondn(btn1_dn),
        .o_onup(btn1_up)
    );

wire reset = status[0] | buttons[1] ; 



wire [15:0] short_audio;
assign audio_l  = short_audio;
assign audio_r = audio_l;




////////////////////////////  MEMORY  ///////////////////////////////////
//
//

////////////////////////////  DDRAM  ///////////////////////////////////
//
//


wire       wav_load = (ioctl_index == 1);

assign DDRAM_CLK = clk_sys;
ddram ddram
(
	.*,
	.addr((ioctl_download & wav_load) ? ioctl_addr :   wav_addr),
	.dout(wav_data),
	.din(ioctl_data),
	.we(wav_wr),
	.rd(wav_want_byte),
	.ready(wav_data_ready)
);



//
//  signals for DDRAM
//
// NOTE: the wav_wr (we) line doesn't want to stay high. It needs to be high to start, and then can't go high until wav_data_ready
// we hold the ioctl_wait high (stop the data from HPS) until we get waV_data_ready



reg wav_wr;
always @(posedge clk_sys) begin
	reg old_reset;

	old_reset <= reset;
	if(~old_reset && reset) ioctl_wait <= 0;

	wav_wr <= 0;
	if(ioctl_wr & wav_load) begin
		ioctl_wait <= 1;
		wav_wr <= 1;
	end
	else if(~wav_wr & ioctl_wait & wav_data_ready) begin
		ioctl_wait <= 0;
	end
end



		
reg    [27:0]wav_addr;
wire   [7:0]wav_data;
wire wav_want_byte;

wave_sound wave_sound
(
        .I_CLK(clk_sys),
        .I_CLK_SPEED('d24000000),
        .I_RSTn(~reset),
        .I_H_CNT(hcnt[3:0]), // used to interleave data reads
        .I_DMA_TRIG(btn0_up),
        .I_DMA_STOP(ioctl_download),
        .I_DMA_CHAN(3'b1), // 8 channels
        .I_DMA_ADDR(16'b0),
        .I_DMA_DATA(wav_data), // Data coming back from wave ROM
		  .I_PAUSE(~toggle_switch),
        .O_DMA_ADDR(wav_addr), // output address to wave ROM
        .O_DMA_READ(wav_want_byte), // read a byte
        .I_DMA_READY(wav_data_ready), // read a byte
		  .I_LOOP(status[7]),
        .debug(debug),
        .O_SND(short_audio)
);


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

module wav_player(
    input CLK,
    input switch_play,
  output reg [7:0] audio_out,
  output reg [13:0]rom_a,
  input [7:0]rom_d,
  output reg play
    );

wire s_start=switch_play;
//reg play = 0;
reg [11:0] prescaler=0; 
reg [13:0] address=0;
reg [7:0] value;

reg [15:0] data;

always @(posedge CLK)
begin
  if (play)
  begin
    prescaler <= prescaler + 1;
    /*if (prescaler == 12'd1)  
    begin
    end
    */
    if (prescaler == 12'd2177)  // 8kHz x 256 steps = 2.048 MHz
    begin
      prescaler <= 0;
      rom_a<=address;
      audio_out <= rom_d;
      address <= address + 1;
      if (address == 14'h3fff )
      begin
        play <= 0;
        address <= 0;
      end			  
    end
  end
  if (s_start)
  begin
    play <= 1;
  end	 
end

endmodule 
