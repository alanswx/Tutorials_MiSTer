///----------------------------------------------------------------------------
//
//  Copyright 2021 Darren Olafson
//
//  MiSTer Copyright (C) 2017 Sorgelig
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
//
//----------------------------------------------------------------------------

`default_nettype none

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
	//if VIDEO_ARX[12] or VIDEO_ARY[12] is set then [11:0] contains scaled size instead of aspect ratio.
	output [12:0] VIDEO_ARX,
	output [12:0] VIDEO_ARY,

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

`ifdef MISTER_FB
	// Use framebuffer in DDRAM (USE_FB=1 in qsf)
	// FB_FORMAT:
	//    [2:0] : 011=8bpp(palette) 100=16bpp 101=24bpp 110=32bpp
	//    [3]   : 0=16bits 565 1=16bits 1555
	//    [4]   : 0=RGB  1=BGR (for 16/24/32 modes)
	//
	// FB_STRIDE either 0 (rounded to 256 bytes) or multiple of pixel size (in bytes)
	output        FB_EN,
	output  [4:0] FB_FORMAT,
	output [11:0] FB_WIDTH,
	output [11:0] FB_HEIGHT,
	output [31:0] FB_BASE,
	output [13:0] FB_STRIDE,
	input         FB_VBL,
	input         FB_LL,
	output        FB_FORCE_BLANK,

`ifdef MISTER_FB_PALETTE
	// Palette control for 8bit modes.
	// Ignored for other video modes.
	output        FB_PAL_CLK,
	output  [7:0] FB_PAL_ADDR,
	output [23:0] FB_PAL_DOUT,
	input  [23:0] FB_PAL_DIN,
	output        FB_PAL_WR,
`endif
`endif

	output        LED_USER,  // 1 - ON, 0 - OFF.

	// b[1]: 0 - LED status is system status OR'd with b[0]
	//       1 - LED status is controled solely by b[0]
	// hint: supply 2'b00 to let the system control the LED.
	output  [1:0] LED_POWER,
	output  [1:0] LED_DISK,

	// I/O board button press simulation (active high)
	// b[1]: user button
	// b[0]: osd button
	output  [1:0] BUTTONS,

	input         CLK_AUDIO, // 24.576 MHz
	output [15:0] AUDIO_L,
	output [15:0] AUDIO_R,
	output        AUDIO_S,   // 1 - signed audio samples, 0 - unsigned
	output  [1:0] AUDIO_MIX, // 0 - no mix, 1 - 25%, 2 - 50%, 3 - 100% (mono)

	//ADC
	inout   [3:0] ADC_BUS,

	//SD-SPI
	output        SD_SCK,
	output        SD_MOSI,
	input         SD_MISO,
	output        SD_CS,
	input         SD_CD,

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

	//SDRAM interface with lower latency
	output        SDRAM_CLK,
	output        SDRAM_CKE,
	output [12:0] SDRAM_A,
	output  [1:0] SDRAM_BA,
	inout  [15:0] SDRAM_DQ,
	output        SDRAM_DQML,
	output        SDRAM_DQMH,
	output        SDRAM_nCS,
	output        SDRAM_nCAS,
	output        SDRAM_nRAS,
	output        SDRAM_nWE,

`ifdef MISTER_DUAL_SDRAM
	//Secondary SDRAM
	//Set all output SDRAM_* signals to Z ASAP if SDRAM2_EN is 0
	input         SDRAM2_EN,
	output        SDRAM2_CLK,
	output [12:0] SDRAM2_A,
	output  [1:0] SDRAM2_BA,
	inout  [15:0] SDRAM2_DQ,
	output        SDRAM2_nCS,
	output        SDRAM2_nCAS,
	output        SDRAM2_nRAS,
	output        SDRAM2_nWE,
`endif

	input         UART_CTS,
	output        UART_RTS,
	input         UART_RXD,
	output        UART_TXD,
	output        UART_DTR,
	input         UART_DSR,

	// Open-drain User port.
	// 0 - D+/RX
	// 1 - D-/TX
	// 2..6 - USR2..USR6
	// Set USER_OUT to 1 to read from USER_IN.
	input   [6:0] USER_IN,
	output  [6:0] USER_OUT,

	input         OSD_STATUS
);


assign {UART_RTS, UART_TXD, UART_DTR} = 0;

assign VGA_F1    = 0;
assign VGA_SCALER= 0;

assign USER_OUT  = '1;
assign AUDIO_MIX = 0;
assign LED_USER  = ioctl_download ;
assign LED_DISK  = 0;
assign LED_POWER = 0;
assign BUTTONS = 0;

wire [1:0] aspect_ratio = status[2:1];
wire orientation = ~status[3];
wire [2:0] scan_lines = status[6:4];

assign VIDEO_ARX = (!aspect_ratio) ? (orientation  ? 8'd4 : 8'd3) : (aspect_ratio - 1'd1);
assign VIDEO_ARY = (!aspect_ratio) ? (orientation  ? 8'd3 : 8'd4) : 12'd0;

`include "build_id.v" 
localparam CONF_STR = {
	"A. Demo68k;;",
	"O12,Aspect ratio,Original,Full Screen,[ARC1],[ARC2];",
	"O3,Orientation,Horz,Vert;",
	"O46,Scandoubler Fx,None,HQ2x,CRT 25%,CRT 50%,CRT 75%;",
    "-;",
	"R0,Reset;",
	"J1,Jump,Start 1P,Start 2P,Coin,Pause;",
	"jn,A,Start,Select,R,L;",
	"V,v",`BUILD_DATE
};

// CLOCKS

wire pll_locked;

wire clk_sys;
reg  clk_7M;
reg  clk_10M;

pll pll
(
	.refclk(CLK_50M),
	.rst(0),
    .outclk_0(clk_sys),     // 28
//	.outclk_1(clk_7M),      // 7    pixel clock generated from /4 system clock
    .outclk_2(clk_10M),     // 10
	.locked(pll_locked)
);

reg [5:0] clk10_count;
reg [5:0] clk7_count;

always @ (posedge clk_sys ) begin
    clk7_count <= clk7_count + 1;
    clk_7M <= clk7_count[1];
end

// 8 dip switches of 8 bits
reg [7:0] sw[8];
always @(posedge clk_sys) begin
    if (ioctl_wr && (ioctl_index==254) && !ioctl_addr[24:3]) begin
        sw[ioctl_addr[2:0]] <= ioctl_dout;
    end
end

wire [31:0] status;
wire  [1:0] buttons;
wire        forced_scandoubler;
wire        direct_video;

wire        ioctl_download;
wire        ioctl_upload;
wire        ioctl_wr;
wire  [7:0]	ioctl_index;
wire [24:0] ioctl_addr;
wire  [7:0] ioctl_dout;
wire  [7:0] ioctl_din;

wire [15:0] joystick_0, joystick_1;
wire [15:0] joy = joystick_0 | joystick_1;

wire [21:0] gamma_bus;

wire b_up      = joy[3];
wire b_down    = joy[2];
wire b_left    = joy[1];
wire b_right   = joy[0];
wire b_fire    = joy[4];

wire b_up_2    = joy[3];
wire b_down_2  = joy[2];
wire b_left_2  = joy[1];
wire b_right_2 = joy[0];
wire b_fire_2  = joy[4];

wire b_start1  = joy[5];
wire b_start2  = joy[6];
wire b_coin    = joy[7];
wire b_pause   = joy[8];

// PAUSE SYSTEM
reg				pause;									// Pause signal (active-high)
reg				pause_toggle = 1'b0;					// User paused (active-high)
reg [31:0]		pause_timer;							// Time since pause
reg [31:0]		pause_timer_dim = 31'h11E1A300;	// Time until screen dim (10 seconds @ 48Mhz)
reg 			dim_video = 1'b0;						// Dim video output (active-high)

// Pause when highscore module requires access, user has pressed pause, or OSD is open and option is set
assign pause =  pause_toggle | (OSD_STATUS && ~status[7]);
assign dim_video = (pause_timer >= pause_timer_dim);

always @(posedge clk_sys) begin
	reg old_pause;
	old_pause <= b_pause;
	if (~old_pause & b_pause) begin
        pause_toggle <= ~pause_toggle;
    end
	if (pause_toggle) begin
		if (pause_timer < pause_timer_dim)
		begin
			pause_timer <= pause_timer + 1'b1;
		end
	end	else begin
		pause_timer <= 1'b0;
	end
end

hps_io #(.STRLEN($size(CONF_STR)>>3)) hps_io
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
	.ioctl_upload(ioctl_upload),
	.ioctl_wr(ioctl_wr),
	.ioctl_addr(ioctl_addr),
	.ioctl_dout(ioctl_dout),
	.ioctl_din(ioctl_din),
	.ioctl_index(ioctl_index),

	.joystick_0(joystick_0),
	.joystick_1(joystick_1)
);


// ram memory address used by video refresh
always @ (posedge clk_7M) begin
    if ( hbl & vbl ) begin
        vramAddr <= 0;
    end else if ( ~hbl ) begin
        vramAddr <= vramAddr + 1;
    end
end


reg ce_pix;

wire hbl;
wire vbl;

wire hsync;
wire vsync;

wire [7:0] hc;
wire [7:0] vc;

wire no_rotate = orientation | direct_video;
//wire rotate_ccw = 1;
//screen_rotate screen_rotate (.*);

arcade_video #(320,12) arcade_video
(
        .*,

        .clk_video(clk_sys),
        .ce_pix(clk_7M),

        .RGB_in(rgb_out[11:0]),
        
        .HBlank(hbl),
        .VBlank(vbl),
        .HSync(hsync),
        .VSync(vsync),

        .fx(scan_lines)
);

wire reset;
assign reset = RESET | status[0] | ioctl_download | buttons[1];
wire rom_download = ioctl_download && !ioctl_index;

video_timing video_timing (
    .clk(clk_7M),       // pixel clock
    .reset(reset),      // reset

    .hc(hc),  
    .vc(vc),  

    .hbl(hbl),
    .vbl(vbl),
    
    .hsync(hsync),     
    .vsync(vsync)   
    );
    
wire [31:0] cpu_addr;
wire [15:0] cpu_data_out;
wire [15:0] cpu_data_in;
wire cpu_wr;

wire [15:0] rgb_out;
reg  [16:0] vramAddr ;

reg  [16:0] vram_Waddr ;
reg  [11:0] vram_Wdata ;


wire pwr_up_reset_n = !reset; /*synthesis keep*/

// ===============================================================
// 68000 CPU
// ===============================================================

// clock generation
reg  fx68_phi1 = 0; 
wire fx68_phi2 = !fx68_phi1;

// phases for 68k clock
always @(posedge clk_10M) begin
    fx68_phi1 <= ~fx68_phi1;
end

// CPU outputs
wire cpu_rw;        /*synthesis keep*/      // Read = 1, Write = 0
wire cpu_as_n;      /*synthesis keep*/      // Address strobe
wire cpu_lds_n;     /*synthesis keep*/      // Lower byte strobe
wire cpu_uds_n;     /*synthesis keep*/      // Upper byte strobe
wire cpu_E;         
wire vma_n;         /*synthesis keep*/      // Valid peripheral memory address
wire [2:0]cpu_fc;   /*synthesis keep*/      // Processor state
wire cpu_reset_n_o; /*synthesis keep*/      // Reset output signal
wire cpu_halted_n;                          // Halt output
wire bg_n;                                  // Bus grant

// CPU busses
wire [15:0] cpu_dout;  /*synthesis keep*/     
wire [23:0] cpu_a;     /*synthesis keep*/     
wire [15:0] cpu_din;   /*synthesis keep*/          

// CPU inputs
wire berr_n = 1'b1;            // Bus error (never error)
wire dtack_n = !vpa_n;         // Data transfer ack (always ready)
wire vpa_n;                    // Valid peripheral address detected
reg  cpu_br_n = 1'b1;          // Bus request
reg  bgack_n = 1'b1;           // Bus grant ack
reg  ipl0_n = 1'b1;            // Interrupt request signals
reg  ipl1_n = 1'b1;
reg  ipl2_n = 1'b1;

assign cpu_a[0] = 0;           // odd memory address should cause cpu exception

fx68k fx68k (
    // input
    .clk( clk_10M),
    .enPhi1(fx68_phi1),
    .enPhi2(fx68_phi2),
    .extReset(!pwr_up_reset_n),
    .pwrUp(!pwr_up_reset_n),
    .HALTn(pwr_up_reset_n),

    // output
    .eRWn(cpu_rw),
    .ASn( cpu_as_n),
    .LDSn(cpu_lds_n),
    .UDSn(cpu_uds_n),
    .E(cpu_E),
    .VMAn(vma_n),
    .FC0(cpu_fc[0]),
    .FC1(cpu_fc[1]),
    .FC2(cpu_fc[2]),
    .BGn(bg_n),
    .oRESETn(cpu_reset_n_o),
    .oHALTEDn(cpu_halted_n),

    // input
    .VPAn(vpa_n),         
    .DTACKn(dtack_n), 
    .BERRn(berr_n), 
    .BRn(cpu_br_n),  
    .BGACKn(bgack_n),
    .IPL0n(ipl0_n),
    .IPL1n(ipl1_n),
    .IPL2n(ipl2_n),

    // busses
    .iEdb(cpu_din),
    .oEdb(cpu_dout),
    .eab(cpu_a[23:1])
);

wire rom_csn =  !(cpu_a[23:18]==6'b000000) | cpu_as_n;
wire ram_csn =  !(cpu_a[23:18]==6'b000100) | cpu_as_n;  // $10_00_00
wire vram_csn = !(cpu_a[23:18]==6'b100000) | cpu_as_n;  // $80_00_00


assign vpa_n =  !(cpu_a[23:18]==6'b011000) | cpu_as_n;


vram vram_inst (
	.inclock ( clk_10M ),
	.wren_a ( ~vram_csn ),
	.address_a ( cpu_a[17:1] ),
	.data_a ( cpu_dout[15:0] ),
	.q_a ( ),
    
	.outclock ( clk_7M ),
	.address_b ( vramAddr ),
	.data_b ( 0 ),
	.wren_b ( 0 ),
	.q_b ( rgb_out )
	);  
    
wire [15:0] rom_do;
wire [15:0] ram_do;

// select cpu data input based on what is active 
assign cpu_din = !rom_csn ? rom_do :
                 !ram_csn ? ram_do :
                 16'd0;

rom8kx16 rom8kx16_inst (
	.clock ( clk_10M ),
	.address ( cpu_a[13:1] ),  
//	.data (  ),
	.wren ( 0 ),
	.q ( rom_do ) 
	);

ram8kx16 ram8kx16_inst (
	.clock ( clk_10M ),
	.address ( cpu_a[13:1] ),
	.data ( cpu_dout ),
	.wren ( !cpu_rw & !ram_csn),
	.q ( ram_do )
	);


endmodule

