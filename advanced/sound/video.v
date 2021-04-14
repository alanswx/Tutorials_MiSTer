

module video_gen(
   // pixel clock
   input  pclk,
   input  reset,
		
   // VGA output
   output reg	hs,
   output reg 	vs,
   output [7:0] r,
   output [7:0] g,
   output [7:0] b,
   output VGA_HBLANK,
   output VGA_VBLANK,
   output VGA_DE
);
					
// 640x400 70HZ VESA according to  http://tinyvga.com/vga-timing/640x400@70Hz
/*
parameter H   = 640;    // width of visible area
parameter HFP = 16;     // unused time before hsync
parameter HS  = 96;     // width of hsync
parameter HBP = 48;     // unused time after hsync

parameter V   = 400;    // height of visible area
parameter VFP = 12;     // unused time before vsync
parameter VS  = 2;      // width of vsync
parameter VBP = 35;     // unused time after vsync
*/

// 640x400 70HZ VESA according to  http://tinyvga.com/vga-timing/640x400@70Hz
/*
parameter H   = 256;    // width of visible area
parameter HFP = 64;     // unused time before hsync
parameter HS  = 24;     // width of hsync
parameter HBP = 11;     // unused time after hsync

parameter V   = 224;    // height of visible area
parameter VFP = 38;     // unused time before vsync
parameter VS  = 8;      // width of vsync
parameter VBP = 35;     // unused time after vsync
*/
/* 320x240 1.5Mhz pixel clock 15khz video */
/*
parameter H   = 320;    // width of visible area
parameter HFP = 8;     // unused time before hsync
parameter HS  = 32;     // width of hsync
parameter HBP = 40;     // unused time after hsync

parameter V   = 260;    // height of visible area
parameter VFP = 3;     // unused time before vsync
parameter VS  = 10;      // width of vsync
parameter VBP = 6;     // unused time after vsync
*/
/*SXGA (Mode 101) Signal 640 x 480 @ 85 Hz timing*/
/*
* Screen refresh rate	85 Hz
Vertical refresh	43.269230769231 kHz
Pixel freq.	36.0 MHz
http://tinyvga.com/vga-timing/640x480@85Hz
*/
/*
parameter H   = 640;    // width of visible area
parameter HFP = 56;     // unused time before hsync
parameter HS  = 56;     // width of hsync
parameter HBP = 80;     // unused time after hsync

parameter V   = 480;    // height of visible area
parameter VFP = 1;     // unused time before vsync
parameter VS  = 3;      // width of vsync
parameter VBP = 25;     // unused time after vsync
*/
/*
parameter H   = 320;    // width of visible area
parameter HFP = 48;     // unused time before hsync
parameter HS  = 32;     // width of hsync
parameter HBP = 80;     // unused time after hsync

parameter V   = 200;    // height of visible area
parameter VFP = 3;     // unused time before vsync
parameter VS  = 6;      // width of vsync
parameter VBP = 6;     // unused time after vsync
*/
/*
https://www.mythtv.org/wiki/Working_with_Modelines
https://github.com/SailorSat/soft-15khz/blob/master/docs/modelines.txt
modeline '320x256' 6,68 320 340 372 416 256 257 260 268 -hsync -vsync
Modeline syntax: pclk hdisp hsyncstart hsyncend htotal vdisp vsyncstart vsyncend vtotal [flags]
*/

parameter H   = 256;    // width of visible area
parameter V   = 224;    // height of visible area
parameter HFP = 5;
parameter VFP = 17;

reg[9:0]  hs_cnt;       
reg[9:0]  vs_cnt;        
reg[9:0]  h_cnt;        // horizontal pixel counter
reg[9:0]  v_cnt;        // vertical pixel counter

reg[9:0]  x_pos;       
reg[9:0]  y_pos;        

reg hblank;
reg vblank;
reg hsync0;
reg vsync;
reg top_frame;
/*
---------------------------------------
-- Video scanner  384x264 @6.083 MHz --
-- display 256x224                   --
--                                   --
-- line  : 63.13us -> 15.84kHz       --
-- frame : 16.67ms -> 60.00Hz        --
---------------------------------------
*/

always@(posedge pclk) begin
	if (reset) begin
		h_cnt<= 0;
		v_cnt<= 0;
	end
	
	
	h_cnt<=h_cnt+1;
	if (h_cnt == 511) h_cnt <= 10'd128;
	if (h_cnt == 128+8+8)	 begin
		v_cnt<=v_cnt +1;
		if (v_cnt==10'd263) begin
			v_cnt<=0;
			top_frame<=!top_frame;
		end
	end
	// set syncs position 
	if (h_cnt == 170) begin
	    // tune screen H position here
            hs_cnt <= 0;
	    if (v_cnt == 0) begin
		    vsync <= 0; 
	    end

	    if (v_cnt == 3 ) begin
		    vsync <= 1; 
	    end
	    if (v_cnt == 248) begin // tune screen V position here
                    vs_cnt <=0;
	    end else begin
                    vs_cnt <= vs_cnt +1;
            end

	 end else begin
            hs_cnt <= hs_cnt + 1;
	 end

	 if (hs_cnt == 0) begin 
		 hsync0 <= 0;
	end else if (hs_cnt == 29) hsync0 <= 1;


        hblank<= 1;
        vblank<= 1;
	if ((h_cnt >= 256+9-5) || (h_cnt < 128+9-5)) begin 
          hblank<= 0;
        end 
	//if ((h_cnt >= 256+9-5) || (h_cnt < 128+9-5)) begin 
        //  hblank<= 0;
        //end 
	//if ((h_cnt < 256+9-5) && (h_cnt >= 128+9-5)) begin 
	//if ((h_cnt < 512+9-5) && (h_cnt >= 128+9-5)) begin 
	/*
	if (h_cnt > 128+8+8) begin
          hblank<= 0;
        end 
	*/
	if (v_cnt >= 17 && v_cnt < 241) begin
          vblank<= 0;
        end 
     end


// read VRAM
reg [13:0] video_counter;
reg [7:0] pixel;
reg de;

always@(posedge pclk) begin
        // The video counter is being reset at the begin of each vsync.
        // Otherwise it's increased every fourth pixel in the visible area.
        // At the end of the first three of four lines the counter is
        // decreased by the total line length to display the same contents
        // for four lines so 100 different lines are displayed on the 400
        // VGA lines.

	 
	// visible area?
	//if((v_cnt < V) && (h_cnt < H)) begin
	if(hblank==0 && vblank==0) begin
		if(h_cnt[1:0] == 2'b11)
			video_counter <= video_counter + 14'd1;
		pixel <= (v_cnt[2] ^ h_cnt[2])?8'h00:8'hff;    // checkboard
		//pixel <= video_counter[7:0];                // color pattern
	end  else begin

			if(v_cnt == V+VFP)
				video_counter <= 14'd0;
	end
		/*
	if((v_cnt < V) && (h_cnt < H)) begin
		if(h_cnt[1:0] == 2'b11)
			video_counter <= video_counter + 14'd1;
		
		pixel <= (v_cnt[2] ^ h_cnt[2])?8'h00:8'hff;    // checkboard
		// pixel <= video_counter[7:0];                // color pattern
		de<=1;
	end else begin
		if(h_cnt == H+HFP) begin
			if(v_cnt == V+VFP)
				video_counter <= 14'd0;
			else if((v_cnt < V) && (v_cnt[1:0] != 2'b11))
				video_counter <= video_counter - 14'd112;
		de<=0;
		end
			
		pixel <= 8'h00;   // black
	end
	*/
end

// seperate 8 bits into three colors (332)

assign r = { pixel[7:5],  3'b00000 };
assign g = { pixel[4:2],  3'b00000 };
assign b = { pixel[1:0], 4'b000000 };
/*
assign r = 8'h00;
assign g = 8'hff;
assign b = 8'h00;
*/
assign VGA_DE  = ~(hblank | vblank);
//assign VGA_DE = de;
assign VGA_HBLANK= hblank;
assign VGA_VBLANK = vblank;
assign hs = hsync0;
assign vs = vsync;
endmodule
