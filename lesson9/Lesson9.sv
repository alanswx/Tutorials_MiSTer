//============================================================================
//  Lesson9 port to MiSTer
//  Copyright (c) 2019 alanswx
//
//  This is a port from mist of the ninth lesson - 
//============================================================================

module emu
(
	//Master input clock
	input         CLK_50M,

	//Async reset from top-level module.
	//Can be used as initial reset.
	input         RESET,

	//Must be passed to hps_io module
	inout  [44:0] HPS_BUS,

	//Base video clock. Usually equals to CLK_SYS.
	output        CLK_VIDEO,

	//Multiple resolutions are supported using different CE_PIXEL rates.
	//Must be based on CLK_VIDEO
	output        CE_PIXEL,

	//Video aspect ratio for HDMI. Most retro systems have ratio 4:3.
	output  [7:0] VIDEO_ARX,
	output  [7:0] VIDEO_ARY,

	output  [7:0] VGA_R,
	output  [7:0] VGA_G,
	output  [7:0] VGA_B,
	output        VGA_HS,
	output        VGA_VS,
	output        VGA_DE,    // = ~(VBlank | HBlank)
	output        VGA_F1,
	output [1:0]  VGA_SL,

	output        LED_USER,  // 1 - ON, 0 - OFF.

	// b[1]: 0 - LED status is system status OR'd with b[0]
	//       1 - LED status is controled solely by b[0]
	// hint: supply 2'b00 to let the system control the LED.
	output  [1:0] LED_POWER,
	output  [1:0] LED_DISK,

	output [15:0] AUDIO_L,
	output [15:0] AUDIO_R,
	output        AUDIO_S, // 1 - signed audio samples, 0 - unsigned
	output  [1:0] AUDIO_MIX, // 0 - no mix, 1 - 25%, 2 - 50%, 3 - 100% (mono)
	input         TAPE_IN,

	// SD-SPI
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

	input         UART_CTS,
	output        UART_RTS,
	input         UART_RXD,
	output        UART_TXD,
	output        UART_DTR,
	input         UART_DSR
);

//`define SOUND_DBG
assign VGA_SL=0;

assign VGA_F1=0;
assign CE_PIXEL=1;

assign {UART_RTS, UART_TXD, UART_DTR} = 0;
assign {SD_SCK, SD_MOSI, SD_CS} = 'Z;
//assign {SDRAM_DQ, SDRAM_A, SDRAM_BA, SDRAM_CLK, SDRAM_CKE, SDRAM_DQML, SDRAM_DQMH, SDRAM_nWE, SDRAM_nCAS, SDRAM_nRAS, SDRAM_nCS} = 'Z;

//assign VIDEO_ARX = status[9] ? 8'd16 : 8'd4;
//assign VIDEO_ARY = status[9] ? 8'd9  : 8'd3;


assign VIDEO_ARX = 4;
assign VIDEO_ARY = 3;

assign AUDIO_S = 0;
assign AUDIO_MIX = 0;

assign LED_DISK  = mouse_x[0];
assign LED_POWER = 1;
assign LED_USER  = ioctl_download|mouse_b[0]|mouse_b[1];

`include "build_id.v"
localparam CONF_STR = {
	"Lesson9;;",
	"-;",
	"-;",
	"-;",
	"-;",
	"-;",
	"V,v",`BUILD_DATE
};


wire [31:0] status;
wire  [1:0] buttons;
wire [15:0] joystick_0;
wire [15:0] joystick_1;
wire        ioctl_download;
wire        ioctl_wr;
wire [24:0] ioctl_addr;
wire [7:0] ioctl_data;
wire  [7:0] ioctl_index;
reg         ioctl_wait=0;

reg  [31:0] sd_lba;
reg         sd_rd = 0;
reg         sd_wr = 0;
wire        sd_ack;
wire  [7:0] sd_buff_addr;
wire  [15:0] sd_buff_dout;
wire  [15:0] sd_buff_din;
wire        sd_buff_wr;
wire        img_mounted;
wire        img_readonly;
wire [63:0] img_size;

wire        forced_scandoubler;
wire [10:0] ps2_key;
wire [24:0] ps2_mouse;

hps_io #(.STRLEN(($size(CONF_STR)>>3) )/*, .PS2DIV(1000), .WIDE(0)*/) hps_io
(
	.clk_sys(cpu_clock/*clk_sys*/),
	.HPS_BUS(HPS_BUS),

	.conf_str(CONF_STR),
	.joystick_0(joystick_0),
	.joystick_1(joystick_1),
	.buttons(buttons),
	.forced_scandoubler(forced_scandoubler),
	.new_vmode(new_vmode),

	.status(status),
	.status_in({status[31:8],region_req,status[5:0]}),
	.status_set(region_set),

	.ioctl_download(ioctl_download),
	.ioctl_index(ioctl_index),
	.ioctl_wr(ioctl_wr),
	.ioctl_addr(ioctl_addr),
	.ioctl_dout(ioctl_data),
	.ioctl_wait(ioctl_wait),

	.sd_lba(sd_lba),
	.sd_rd(sd_rd),
	.sd_wr(sd_wr),
	.sd_ack(sd_ack),
	.sd_buff_addr(sd_buff_addr),
	.sd_buff_dout(sd_buff_dout),
	.sd_buff_din(sd_buff_din),
	.sd_buff_wr(sd_buff_wr),
	.img_mounted(img_mounted),
	.img_readonly(img_readonly),
	.img_size(img_size),

	
	

		.ps2_kbd_clk_out    ( ps2_kbd_clk    ),
		.ps2_kbd_data_out   ( ps2_kbd_data   ),

		.ps2_mouse_clk_out  ( ps2_mouse_clk  ),
		.ps2_mouse_data_out ( ps2_mouse_data ),

	
	.ps2_key(ps2_key),
	.ps2_mouse(ps2_mouse)
);


///////////////////////////////////////////////////
//wire clk_sys, clk_ram, clk_ram2, clk_pixel, locked;
wire clk_sys,locked;




// the MiST emulates a PS2 keyboard and mouse
wire ps2_kbd_clk, ps2_kbd_data;
wire ps2_mouse_clk, ps2_mouse_data;

// a very simple keyboard implementation which only decodes
// a few keys (SPACE, S, ...)
wire kbd_sel = !cpu_iorq_n && cpu_m1_n && ({ cpu_addr[7:1], 1'b0} == 8'h20 );
wire [7:0] keys;
keyboard keyboard (
	.reset    ( cpu_reset    ),
	.clk      ( cpu_clock    ),

	.ps2_clk  ( ps2_kbd_clk  ),
	.ps2_data ( ps2_kbd_data ),
	
	.keys     ( keys         )
);

// a very simple mouse implementation. It accumulates mouse movement 
// internally until the cpu reads the values which in turn clears the
// hardware counters
wire [7:0] mouse_dout = 
	(cpu_addr[1:0]==2'd0)?mouse_x:
	(cpu_addr[1:0]==2'd1)?mouse_y:
	{6'b000000, mouse_b};
wire [7:0] mouse_x;
wire [7:0] mouse_y;
wire [1:0] mouse_b;
wire mouse_sel = !cpu_iorq_n && cpu_m1_n && ({ cpu_addr[7:2], 2'b00} == 8'h30 );

mouse mouse (
	.reset    ( cpu_reset      ),
	.clk      ( cpu_clock      ),

	.ps2_mouse(ps2_mouse),

	//.ps2_clk  ( ps2_mouse_clk  ),
	//.ps2_data ( ps2_mouse_data ),
	
	.x        ( mouse_x        ),
	.clr_x    ( mouse_sel && !cpu_rd_n && (cpu_addr[1:0] == 2'd0)),
	.y        ( mouse_y        ),
	.clr_y    ( mouse_sel && !cpu_rd_n && (cpu_addr[1:0] == 2'd1)),
	.b        ( mouse_b        )
);





///////////////////////////////////////////////////
wire [3:0] r, g, b;
wire vs,hs;
wire ce_pix;
wire hblank, vblank;
wire interlace;
wire copy_in_progress;

//assign DDRAM_CLK = clk_ram;
//wire reset = RESET |` status[0] | buttons[1] | region_set | bk_loading;
wire clk_pixel;
assign CLK_VIDEO = clk_pixel;

wire [15:0] audio_l, audio_r;

// de-activate unused SDRAM
//assign SDRAM_nCS = 1;

// include VGA controller
vga vga (
   .reset ( cpu_reset),
	.pclk     ( clk_pixel ),
	 
	.cpu_clk  ( cpu_clock        ),
	.cpu_wr   ( !cpu_wr_n && !cpu_mreq_n && !cpu_addr[15] ),
	.cpu_addr ( cpu_addr[13:0]   ),
	.cpu_data ( cpu_dout         ),


        // video output as fed into the VGA outputs
	.hs    (VGA_HS),
	.vs    (VGA_VS),
	.r     (VGA_R),
	.g     (VGA_G),
	.b     (VGA_B),
	.VGA_DE(VGA_DE)

);


// The CPU is kept in reset for further 256 cycles after the PLL is generating stable clocks
// to make sure things like the SDRAM have some time to initialize
// status 0 is arm controller power up reset, status 2 is reset entry in OSD
reg [7:0] cpu_reset_cnt = 8'h00;
wire cpu_reset = (cpu_reset_cnt != 255);
always @(posedge cpu_clock) begin
	if(!locked /*|| status[0] || status[2] */|| ioctl_download)
		cpu_reset_cnt <= 8'd0;
	else 
		if(cpu_reset_cnt != 255)
			cpu_reset_cnt <= cpu_reset_cnt + 8'd1;
end



// SDRAM control signals
wire ram_clock;
assign SDRAM_CKE = 1'b1;

// during ROM download ioctl_io writes the ram. Otherwise the CPU
wire [7:0] sdram_din = ioctl_download?ioctl_data:cpu_dout;
wire [24:0] sdram_addr = ioctl_download?ioctl_addr:{ 9'd0, cpu_addr[15:0] };
wire sdram_wr = ioctl_download?ioctl_wr:(!cpu_wr_n && !cpu_mreq_n && cpu_addr[15]);
wire sdram_oe = ioctl_download?1'b1:(!cpu_rd_n && !cpu_mreq_n);

sdram sdram (
	// interface to the MT48LC16M16 chip
   .sd_data        ( SDRAM_DQ                  ),
   .sd_addr        ( SDRAM_A                   ),
   .sd_dqm         ( {SDRAM_DQMH, SDRAM_DQML}  ),
   .sd_cs          ( SDRAM_nCS                 ),
   .sd_ba          ( SDRAM_BA                  ),
   .sd_we          ( SDRAM_nWE                 ),
   .sd_ras         ( SDRAM_nRAS                ),
   .sd_cas         ( SDRAM_nCAS                ),

   // system interface
   .clk            ( ram_clock                 ),
   .clkref         ( cpu_clock                 ),
   .init           ( !locked               ),

   // cpu/chipset interface
   .din            ( sdram_din                  ),
   .addr           ( sdram_addr                ),
   .we             ( sdram_wr                  ),
   .oe         	 ( sdram_oe                  ),
   .dout           ( ram_data_out              )
);

wire [15:0] cpu_addr;
wire [7:0] cpu_din;
wire [7:0] cpu_dout;
wire cpu_rd_n;
wire cpu_wr_n;
wire cpu_mreq_n;
wire cpu_m1_n;
wire cpu_iorq_n;





// include Z80 CPU
T80s T80s (
	.RESET_n  ( !cpu_reset    ),
	.CLK    ( cpu_clock     ),
	.WAIT_n   ( 1'b1          ),
	.INT_n    ( 1'b1 /*irq_n */         ),
	.NMI_n    ( 1'b1          ),
	.BUSRQ_n  ( 1'b1          ),
	.MREQ_n   ( cpu_mreq_n    ),
	.M1_n     ( cpu_m1_n      ),
	.IORQ_n   ( cpu_iorq_n    ),
	.RD_n     ( cpu_rd_n      ), 
	.WR_n     ( cpu_wr_n      ),
	.A        ( cpu_addr      ),
	.DI       ( cpu_din       ),
	.DO       ( cpu_dout      )
);



// de-multiplex the IO data sources
wire [7:0] io_dout = 
	kbd_sel?keys:
	mouse_sel?mouse_dout:
	8'h00;

// map 32k SDRAM into upper half od the address space (A15=1)
// and ROM into the lower half (A15=0)
wire [7:0] ram_data_out;
//assign cpu_din = ram_data_out;
assign cpu_din = (!cpu_iorq_n)?io_dout:ram_data_out;


	
// derive 4Mhz cpu clock and 15kHz ps2 clock from 32Mhz sdram clock
wire ps2_clock = clk_div[13];
wire cpu_clock = clk_div[2];
reg [13:0] clk_div;
always @(posedge ram_clock)
        clk_div <= clk_div + 14'd1;
	
	
//assign SDRAM_CLK=ram_clock;
pll pll (
	 .refclk ( CLK_50M   ),
	 .rst(0),
	 .locked ( locked    ),        // PLL is running stable
	 .outclk_0    (clk_sys),
	 .outclk_1     ( clk_pixel   ),        // 25.175 MHz
	 .outclk_2     ( ram_clock     ),        // 32 MHz
	 .outclk_3     ( SDRAM_CLK     ),         // slightly phase shifted 32 MHz
    .outclk_4 (cpu_clock_2) //4mhz clock not shifted
	 );

endmodule
