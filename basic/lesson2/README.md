Lesson 2: A VGA image viewer
--------------------------

This builds on lesson 1, but adds an image viewer. The image is stored in the 332 format, and is saved as an intel hex file and loaded as a ROM in quartus.


The top level is in Lesson2.sv and this pulls in the MiSTer framework. 
soc.v is introduced as a small bit of logic that copies data from the ROM into video memory.  The vga controller could read directly from this ROM instead. I ported this from MiST without much understanding at the time.
vga.v is in the rtl folder, and it contains the timing information to make the pulses that VGA relies on.  This also has the logic to both copy data into the video memory, and read the video memory for the display output.



[![Lesson 2 Video](http://img.youtube.com/vi/97o_aMsqumY/0.jpg)](http://www.youtube.com/watch?v=97o_aMsqumY "Lesson 2 Video")


# Step one build existing code

Load this project into quartus and build it. The RBF will be in the output_files folder, copy it to your MiSTer and see if you can run it.

![](lesson2.png)



# Modification

Let's modify the code and simplify it so that we can use the OSD to load another image. 


We will simplify the code to use a VHDL dpram module we can grab from another MiSTer project. Be aware that the different dpram modules often have different parameters, and work slightly differently. 

DPRAM stands for Dual Ported RAM. The FPGA is natively Dual Port, which means you can read and write to it at the same time with two interfaces, at the same or different clocks. Because all of the BRAM on the FPGA is dual ported, it doesn't use any more memory resources to hook it up this way.

This [DPRAM from SMS](https://github.com/MiSTer-devel/SMS_MiSTer/blob/ca668d96ac3e3c020f5e2046b9089d94218baffb/rtl/dpram.vhd) has a good interface and will allow us to pass in a mif file.

Download the dpram.vhd and put it in the rtl folder. Edit files.qip  - in MiSTer we don't use the quartus UI to add and remove files from the project. We put them into files.qip, so we can easily replace the Lesson2.qsf when there is a new MiSTer framework release. Before we used the files.qip include it took a lot of energy to upgrade the framework.

files.qip:
```
set_global_assignment -name SYSTEMVERILOG_FILE Lesson2.sv
set_global_assignment -name QIP_FILE sys/sys.qip
set_global_assignment -name VERILOG_FILE rtl/vga.v
set_global_assignment -name VERILOG_FILE rtl/soc.v
set_global_assignment -name VHDL_FILE rtl/dpram.vhd
```

Now that we have removed the ROM and added the DPRAM, we are going to need to delete a bunch of code and simplify things. We will start in the VGA module and work our way back to the top.

## vga.v

Remove the vmem array, and replace it with the DPRAM block.
```verilog
// 16000 bytes of internal video memory for 160x100 pixel at 8 Bit (RGB 332)
//reg [7:0] vmem [160*100-1:0];

dpram #( .init_file("image.hex"),.widthad_a(14),.width_a(8)) vmem
(
	.clock_a(pclk),
	.address_a(video_counter),
	.wren_a(1'b0),
	.q_a(pixel),
	
	.clock_b(pclk),
	.wren_b(ioctl_wr),
	.address_b(ioctl_addr),
	.data_b(ioctl_data)
);

```

remove this: it used to copy the data from the ROM into RAM.
```verilog
// write VRAM via CPU interface
//always @(posedge cpu_clk)
//	if(cpu_wr) 
//		vmem[cpu_addr] <= cpu_data;
```


Originally the next block would count through the pixels and generate an address, and set the pixel. Instead that chunk of code should just generate the address, and the DPRAM block will place the image data onto the pixel wire itself. We should change the pixel type, and remove it from the second block.



```verilog
wire [7:0] pixel;
```

```verilog
always@(posedge pclk) begin
        // The video counter is being reset at the begin of each vsync.
        // Otherwise it's increased every fourth pixel in the visible area.
        // At the end of the first three of four lines the counter is
        // decreased by the total line length to display the same contents
        // for four lines so 100 different lines are displayed on the 400
        // VGA lines.

	// visible area?
	if((v_cnt < V) && (h_cnt < H)) begin
		if(h_cnt[1:0] == 2'b11)
			video_counter <= video_counter + 14'd1;
		de<=1;
	end else begin
		if(h_cnt == H+HFP) begin
			if(v_cnt == V+VFP)
				video_counter <= 14'd0;
			else if((v_cnt < V) && (v_cnt[1:0] != 2'b11))
				video_counter <= video_counter - 14'd160;
		de<=0;
		end
	end
end
```

At the top of vga.v change the inputs so we can send the ioctl_data to the DPRAM:
```verilog
module vga (
   // pixel clock
   input  pclk,
	
	// CPU interface (write only!)
   input  ioctl_wr,
   input [13:0] ioctl_addr,
   input [7:0] ioctl_data,

		
   // VGA output
   output reg	hs,
   output reg 	vs,
   output [7:0] r,
   output [7:0] g,
   output [7:0] b,
	output VGA_DE
);
```



The soc.v file needs to be simplified:  We probably don't need it at all since it isn't doing anything but passing the signals to the vga module. 

```verilog// A simple system-on-a-chip (SoC) for the MiST
// (c) 2015 Till Harbaum

module soc (
   input  pixel_clock,
   input  ioctl_wr,
   input [13:0] ioctl_addr,
   input [7:0] ioctl_data,
   output reg progress,
   output VGA_HS,
   output VGA_VS,
   output [7:0] VGA_R,
   output [7:0] VGA_G,
   output [7:0] VGA_B,
   output VGA_DE
);



vga vga (
	 .pclk  (pixel_clock),
	 
	 .ioctl_wr   ( ioctl_wr ),
	 .ioctl_addr ( ioctl_addr    ),
	 .ioctl_data ( ioctl_data             ),

	 .hs    (VGA_HS),
	 .vs    (VGA_VS),
	 .r     (VGA_R),
	 .g     (VGA_G),
	 .b     (VGA_B),
	 .VGA_DE(VGA_DE)
);
				

			


endmodule
```


In the top emu module in Lesson2.sv we need to hook up the rom loading from the hps module, and tell the OSD we want to be able to load images.

In the CONF_STR we need to add this line:  F means file, 1 means put it into ioctl_index 1 (which we won't use here), and BIN means just show files that end in BIN.
```verilog
	"F1,BIN;",

```

Because the files are loaded in the linux side, they appear to the core through the hps module. 

We will add the ioctl signals that we need to the hps_io and define wires to route the data to the soc module:

```verilog
//
// HPS is the module that communicates between the linux and fpga
//
wire [31:0] status;
wire        ioctl_download;
wire  [7:0] ioctl_dout;
wire        ioctl_wr;
wire [26:0] ioctl_addr;

hps_io #(.STRLEN(($size(CONF_STR)>>3)) , .PS2DIV(1000), .WIDE(0)) hps_io
(
	.clk_sys(clk_sys),
	.HPS_BUS(HPS_BUS),
	.status(status),
	.ioctl_download(ioctl_download),
	.ioctl_wr(ioctl_wr),
	.ioctl_addr(ioctl_addr),
	.ioctl_dout(ioctl_dout),

	.conf_str(CONF_STR)

);
```

Finally, route the ioctl data to the soc module.  We only want to write to the rom when ioctl_wr and ioctl_download are set. If we had more than one file command, or had roms like in an arcade, we would also check to see that ioctl_index == 1.  1 because we set it to 1 using F1 in the CONF_STR.

```verilog
soc soc(
   .pixel_clock(CLK_VIDEO), // wrong
   .progress(copy_in_progress),
   .ioctl_wr   ( ioctl_wr & ioctl_download),
   .ioctl_addr ( ioctl_addr    ),
   .ioctl_data ( ioctl_dout    ),

   .VGA_HS(VGA_HS),
   .VGA_VS(VGA_VS),
   .VGA_R(VGA_R),
   .VGA_G(VGA_G),
   .VGA_B(VGA_B),
   .VGA_DE(VGA_DE)
);
```


## Bugs I ran into while putting the demo together

1) I accidentally must have copied and pasted an hps_io where WIDE was set to 1.  When WIDE is set to 1, ioctl_dout and the other data lines are 16bits instead of 8. This is faster, but when dealing with 8 bit cores often 8 is easier. If it is set to 16, you will miss half the bytes and the ioctl_addr will increment by 2 instead of 1.
2) This DPRAM module needs wren_a and wren_b either passed in a wire, or set to 0. For some reason it defaults to 1, which means allow a write. So on the a side of the DPRAM we had wren_a set to 1 (without realizing it) which meant it kept writing 0's into the ram, and the display was black ('h00)
