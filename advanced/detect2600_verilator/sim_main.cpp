#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include <verilated.h>
#include "Vtop.h"

// Instantiation of module.
Vtop* top = NULL;
vluint64_t main_time = 0;       // Current simulation time.


FILE *ioctl_file=NULL;
int ioctl_next_addr = 0x0;


void ioctl_download_before_eval(void);
void ioctl_download_after_eval(void);


int verilate() {
static int clkdiv=3;

	if (!Verilated::gotFinish()) {
		if (main_time < 48) {
			top->reset = 1;   	// Assert reset (active HIGH)
		}
		if (main_time == 48) {	// Do == here, so we can still reset it in the main loop.
			top->reset = 0;		// Deassert reset.
		}
		if ((main_time & 1) == 0) {
//			top->clk_sys = 0;       // Toggle clock
			if (!clkdiv) {
			}
				top->clk_sys=0;
			top->clk_vid = 0;				
		}
		if ((main_time & 1) == 1) {
//			top->clk_sys = 1;
			if (!clkdiv) {
				clkdiv=3;
			}
			clkdiv--;
			top->clk_sys=1;
			top->clk_vid = 1;



			}


	if (top->clk_sys ) 
		ioctl_download_before_eval();
	else if (ioctl_file)
		printf("skipping download this cycle %d\n",top->clk_sys);



		top->eval();            // Evaluate model!

	if (top->clk_sys ) 
		ioctl_download_after_eval();




		main_time++;            // Time passes...

		return 1;
	}
	// Stop Verilating...
	top->final();
	delete top;
	exit(0);
	return 0;
}

void ioctl_download_setfile(char *file, int index)
{
	ioctl_next_addr = -1;
	top->ioctl_addr=ioctl_next_addr;
	top->ioctl_index = index;
    ioctl_file=fopen(file,"rb");
    if (!ioctl_file) printf("error opening %s\n",file);
}
int nextchar = 0;
void ioctl_download_before_eval()
{
	if (ioctl_file) {
printf("ioctl_download_before_eval %x\n",top->ioctl_addr);
	    if (top->ioctl_wait==0) {
	    top->ioctl_download=1;
	    top->ioctl_wr = 1;
	    
	    if (feof(ioctl_file)) {
		    fclose(ioctl_file);
		    ioctl_file=NULL;
			top->ioctl_download=0;
	    	top->ioctl_wr = 0;
			printf("finished upload\n");

	    }
	    	if (ioctl_file) {
	    		int curchar = fgetc(ioctl_file);
		
	    		if (curchar!=EOF) {
	    		//top->ioctl_dout=(char)curchar;
	    		nextchar=curchar;
printf("ioctl_download_before_eval: dout %x \n",top->ioctl_dout);
	    		ioctl_next_addr++;
	    		}
	    	}
		}
	}
	else {
	top->ioctl_download=0;
	top->ioctl_wr=0;
	}

}
void ioctl_download_after_eval()
{
    top->ioctl_addr=ioctl_next_addr;
   top->ioctl_dout=(unsigned char)nextchar;
if (ioctl_file) printf("ioctl_download_after_eval %x wr %x dl %x\n",top->ioctl_addr,top->ioctl_wr,top->ioctl_download);
}

void start_load_rom() {
printf("load rom here\n");
 ioctl_download_setfile("../release-WIP/boot.rom",0);

}

void start_load_cart() {
printf("load cart here\n");
 ioctl_download_setfile("../release-WIP/asteroids.a78",1);
}
void start_load_cart_3() {
printf("load cart here\n");
 ioctl_download_setfile("../release-WIP/DiagCart2.a78",1);
}
void start_load_cart_2() {
printf("load cart here 2\n");
 ioctl_download_setfile("../release-WIP/PolePositionII.a78",1);
}



int main(int argc, char *argv[]) 
{
 	top = new Vtop();
        Verilated::commandArgs(argc, argv);
	fprintf(stderr,"main\n");
 	ioctl_download_setfile("tron.bin",1);
        while(!top->done)
        	for (int step = 0; step < 1024; step++) verilate();     // Simulates MUCH faster if it's done in batches.

	fprintf(stderr,"result: %x\n",top->bs);
}

