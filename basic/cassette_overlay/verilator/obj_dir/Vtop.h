// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VTOP_H_
#define _VTOP_H_  // guard

#include "verilated_heavy.h"
#include "Vtop__Dpi.h"

//==========

class Vtop__Syms;
class Vtop_VerilatedVcd;


//----------

VL_MODULE(Vtop) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk_sys,0,0);
    VL_IN8(clk_vid,0,0);
    VL_IN8(reset,0,0);
    VL_OUT8(VGA_R,7,0);
    VL_OUT8(VGA_G,7,0);
    VL_OUT8(VGA_B,7,0);
    VL_OUT8(VGA_HS,0,0);
    VL_OUT8(VGA_VS,0,0);
    VL_OUT8(VGA_HB,0,0);
    VL_OUT8(VGA_VB,0,0);
    VL_IN8(ioctl_download,0,0);
    VL_IN8(ioctl_wr,0,0);
    VL_IN8(ioctl_dout,7,0);
    VL_IN8(ioctl_index,7,0);
    VL_OUT8(ioctl_wait,0,0);
    VL_IN(ioctl_addr,24,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ top__DOT__clk_sys;
        CData/*0:0*/ top__DOT__clk_vid;
        CData/*0:0*/ top__DOT__reset;
        CData/*7:0*/ top__DOT__VGA_R;
        CData/*7:0*/ top__DOT__VGA_G;
        CData/*7:0*/ top__DOT__VGA_B;
        CData/*0:0*/ top__DOT__soc__DOT__vs;
        CData/*0:0*/ top__DOT__soc__DOT__hs;
        CData/*0:0*/ top__DOT__soc__DOT__ce_pix;
        CData/*0:0*/ top__DOT__soc__DOT__hblank;
        CData/*0:0*/ top__DOT__soc__DOT__vblank;
        CData/*0:0*/ top__DOT__soc__DOT__interlace;
        CData/*7:0*/ top__DOT__soc__DOT__cpu_reset_cnt;
        CData/*7:0*/ top__DOT__soc__DOT__cpu_dout;
        CData/*0:0*/ top__DOT__soc__DOT__cpu_rd_n;
        CData/*0:0*/ top__DOT__soc__DOT__cpu_wr_n;
        CData/*0:0*/ top__DOT__soc__DOT__cpu_mreq_n;
        CData/*7:0*/ top__DOT__soc__DOT__ram_data_out;
        CData/*7:0*/ top__DOT__soc__DOT__rom_data_out;
        CData/*0:0*/ top__DOT__soc__DOT__overlay__DOT__reset;
        CData/*7:0*/ top__DOT__soc__DOT__overlay__DOT__charmap_r;
        CData/*7:0*/ top__DOT__soc__DOT__overlay__DOT__charmap_g;
        CData/*7:0*/ top__DOT__soc__DOT__overlay__DOT__charmap_b;
        CData/*0:0*/ top__DOT__soc__DOT__overlay__DOT__charmap_a;
        CData/*7:0*/ top__DOT__soc__DOT__overlay__DOT__chrom_data_out;
        CData/*7:0*/ top__DOT__soc__DOT__overlay__DOT__chmap_data_out;
        CData/*7:0*/ top__DOT__soc__DOT__overlay__DOT__wr_data;
        CData/*0:0*/ top__DOT__soc__DOT__overlay__DOT__wheel_state;
        CData/*1:0*/ top__DOT__soc__DOT__overlay__DOT__state;
        CData/*3:0*/ top__DOT__soc__DOT__overlay__DOT__blocks;
        CData/*3:0*/ top__DOT__soc__DOT__overlay__DOT__cur_block;
        CData/*0:0*/ top__DOT__soc__DOT__overlay__DOT__wr_ena;
        CData/*7:0*/ top__DOT__soc__DOT__overlay__DOT__chrom__DOT__data_a;
        CData/*0:0*/ top__DOT__soc__DOT__overlay__DOT__chrom__DOT__wren_b;
        CData/*7:0*/ top__DOT__soc__DOT__overlay__DOT__chrom__DOT__data_b;
        CData/*7:0*/ top__DOT__soc__DOT__overlay__DOT__chrom__DOT__q_b;
        CData/*0:0*/ top__DOT__soc__DOT__overlay__DOT__chrom__DOT__byteena_a;
        CData/*0:0*/ top__DOT__soc__DOT__overlay__DOT__chrom__DOT__byteena_b;
        CData/*7:0*/ top__DOT__soc__DOT__overlay__DOT__chram__DOT__q_a;
        CData/*7:0*/ top__DOT__soc__DOT__overlay__DOT__chram__DOT__data_b;
        CData/*0:0*/ top__DOT__soc__DOT__overlay__DOT__chram__DOT__byteena_a;
        CData/*0:0*/ top__DOT__soc__DOT__overlay__DOT__chram__DOT__byteena_b;
        CData/*0:0*/ top__DOT__soc__DOT__vga__DOT__hblank;
        CData/*0:0*/ top__DOT__soc__DOT__vga__DOT__vblank;
        CData/*7:0*/ top__DOT__soc__DOT__vga__DOT__pixel;
        CData/*0:0*/ top__DOT__soc__DOT__vga__DOT__de;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__m1_n;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__iorq_n;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__no_read;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__write;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__di_reg;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ACC;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__F;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Ap;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Fp;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegDIH;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegDIL;
        CData/*2:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrA_r;
        CData/*2:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrA;
        CData/*2:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrB_r;
        CData/*2:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrB;
        CData/*2:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrC;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegWEH;
    };
    struct {
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegWEL;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Alternate;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IR;
        CData/*1:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ISet;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Save_Mux;
        CData/*6:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__tstate;
        CData/*6:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__mcycle;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__last_mcycle;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__last_tstate;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IntE_FF1;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IntE_FF2;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Halt_FF;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BusReq_s;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BusAck;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__NMI_s;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__INT_s;
        CData/*1:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IStatus;
        CData/*1:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__XY_State;
        CData/*2:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Pre_XY_F_M;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__NextIs_XY_Fetch;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__XY_Ind;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__No_BTR;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BTR_r;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Auto_Wait;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Auto_Wait_t1;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Auto_Wait_t2;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IncDecZ;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BusB;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BusA;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ALU_Q;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__F_Out;
        CData/*4:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Read_To_Reg_r;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Arith16_r;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Z16_r;
        CData/*3:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ALU_Op_r;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Save_ALU_r;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__PreserveC_r;
        CData/*2:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__mcycles;
        CData/*2:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__mcycles_d;
        CData/*2:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__tstates;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IntCycle;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__NMICycle;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Inc_PC;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Inc_WZ;
        CData/*3:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IncDec_16;
        CData/*1:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Prefix;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Read_To_Acc;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Read_To_Reg;
        CData/*3:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Set_BusB_To;
        CData/*3:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Set_BusA_To;
        CData/*3:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ALU_Op;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Save_ALU;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__PreserveC;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Arith16;
        CData/*2:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Set_Addr_To;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Jump;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__JumpE;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__JumpXY;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Call;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RstP;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__LDZ;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__LDW;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__LDSPHL;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__iorq_i;
    };
    struct {
        CData/*2:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Special_LD;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ExchangeDH;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ExchangeRp;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ExchangeAF;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ExchangeRS;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_DJNZ;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_CPL;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_CCF;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_SCF;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_RETN;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_BT;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_BC;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_BTR;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_RLD;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_RRD;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_INRC;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SetDI;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SetEI;
        CData/*1:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IMode;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Halt;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Oldnmi_n;
        CData/*2:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__DDD;
        CData/*2:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__SSS;
        CData/*1:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__DPAIR;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__UseCarry;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__Carry7_v;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__OverFlow_v;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__HalfCarry_v;
        CData/*0:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__Carry_v;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__Q_v;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__BitMask;
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__Q_t;
        CData/*7:0*/ top__DOT__soc__DOT__rom__DOT__data_a;
        CData/*7:0*/ top__DOT__soc__DOT__rom__DOT__data_b;
        CData/*7:0*/ top__DOT__soc__DOT__rom__DOT__q_b;
        CData/*0:0*/ top__DOT__soc__DOT__rom__DOT__byteena_a;
        CData/*0:0*/ top__DOT__soc__DOT__rom__DOT__byteena_b;
        CData/*7:0*/ top__DOT__soc__DOT__ram__DOT__data_b;
        CData/*7:0*/ top__DOT__soc__DOT__ram__DOT__q_b;
        CData/*0:0*/ top__DOT__soc__DOT__ram__DOT__byteena_a;
        CData/*0:0*/ top__DOT__soc__DOT__ram__DOT__byteena_b;
        SData/*12:0*/ top__DOT__soc__DOT__div;
        SData/*15:0*/ top__DOT__soc__DOT__cpu_addr;
        SData/*11:0*/ top__DOT__soc__DOT__overlay__DOT__wr_addr;
        SData/*10:0*/ top__DOT__soc__DOT__overlay__DOT__chrom__DOT__address_b;
        SData/*9:0*/ top__DOT__soc__DOT__vga__DOT__h_cnt;
        SData/*9:0*/ top__DOT__soc__DOT__vga__DOT__v_cnt;
        SData/*13:0*/ top__DOT__soc__DOT__vga__DOT__video_counter;
        SData/*15:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SP;
        SData/*15:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__PC;
        SData/*15:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegBusA;
        SData/*15:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegBusB;
        SData/*15:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegBusC;
        SData/*15:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__TmpAddr;
        SData/*15:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegBusA_r;
        SData/*15:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ID16;
        SData/*15:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__PC16;
        SData/*15:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__PC16_B;
        SData/*15:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SP16;
        SData/*15:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SP16_A;
        SData/*15:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SP16_B;
        SData/*15:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ID16_B;
        SData/*8:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__DAA_Q;
        SData/*11:0*/ top__DOT__soc__DOT__rom__DOT__address_b;
    };
    struct {
        IData/*23:0*/ top__DOT__soc__DOT__pos;
        IData/*23:0*/ top__DOT__soc__DOT__overlay__DOT__pos_r;
        CData/*7:0*/ top__DOT__soc__DOT__overlay__DOT__chrom__DOT__mem[2048];
        CData/*7:0*/ top__DOT__soc__DOT__overlay__DOT__chram__DOT__mem[2048];
        CData/*7:0*/ top__DOT__soc__DOT__vga__DOT__vmem[16000];
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[8];
        CData/*7:0*/ top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[8];
        CData/*7:0*/ top__DOT__soc__DOT__rom__DOT__mem[4096];
        CData/*7:0*/ top__DOT__soc__DOT__ram__DOT__mem[4096];
    };
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ top__DOT__soc__DOT____Vcellinp__T80x__reset_n;
        CData/*0:0*/ top__DOT__soc__DOT____Vcellinp__ram__wren_a;
        CData/*7:0*/ top__DOT__soc__DOT__vga__DOT____Vlvbound1;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__2__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__2__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__2__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__3__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__3__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__3__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__4__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__4__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__4__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__5__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__5__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__5__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__6__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__6__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__6__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__7__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__7__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__7__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__8__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__8__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__8__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__9__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__9__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__9__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__10__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__10__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__10__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__11__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__11__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__11__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__12__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__12__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__12__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__13__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__13__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__13__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__14__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__14__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__14__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__15__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__15__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__15__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__16__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__16__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__16__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__17__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__17__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__17__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__18__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__18__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__18__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__19__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__19__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__19__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__20__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__20__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__20__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__21__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__21__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__21__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__22__Vfuncout;
    };
    struct {
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__22__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__22__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__23__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__23__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__23__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__24__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__24__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__24__cc;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__25__Vfuncout;
        CData/*7:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__25__FF;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__is_cc_true__25__cc;
        CData/*4:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub4__26__Vfuncout;
        CData/*3:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub4__26__A;
        CData/*3:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub4__26__B;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub4__26__Sub;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub4__26__Carry_In;
        CData/*4:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub4__27__Vfuncout;
        CData/*3:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub4__27__A;
        CData/*3:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub4__27__B;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub4__27__Sub;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub4__27__Carry_In;
        CData/*3:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub3__28__Vfuncout;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub3__28__A;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub3__28__B;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub3__28__Sub;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub3__28__Carry_In;
        CData/*3:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub3__29__Vfuncout;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub3__29__A;
        CData/*2:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub3__29__B;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub3__29__Sub;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub3__29__Carry_In;
        CData/*1:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub1__30__Vfuncout;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub1__30__A;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub1__30__B;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub1__30__Sub;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub1__30__Carry_In;
        CData/*1:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub1__31__Vfuncout;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub1__31__A;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub1__31__B;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub1__31__Sub;
        CData/*0:0*/ __Vfunc_top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__AddSub1__31__Carry_In;
        CData/*7:0*/ __Vdlyvval__top__DOT__soc__DOT__vga__DOT__vmem__v0;
        CData/*0:0*/ __Vdlyvset__top__DOT__soc__DOT__vga__DOT__vmem__v0;
        CData/*7:0*/ __Vdly__top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ACC;
        CData/*7:0*/ __Vdly__top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__F;
        CData/*0:0*/ __Vdly__top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Alternate;
        CData/*0:0*/ __Vdly__top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Auto_Wait_t1;
        CData/*0:0*/ __Vdly__top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IntE_FF2;
        CData/*0:0*/ __Vdly__top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BusAck;
        CData/*6:0*/ __Vdly__top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__tstate;
        CData/*6:0*/ __Vdly__top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__mcycle;
        CData/*0:0*/ __Vdly__top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IntCycle;
        CData/*0:0*/ __Vdly__top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__NMICycle;
        CData/*0:0*/ __VinpClk__TOP__top__DOT__soc__DOT____Vcellinp__T80x__reset_n;
        CData/*0:0*/ __Vclklast__TOP__clk_sys;
        CData/*0:0*/ __Vclklast__TOP____VinpClk__TOP__top__DOT__soc__DOT____Vcellinp__T80x__reset_n;
        CData/*0:0*/ __Vclklast__TOP__clk_vid;
        CData/*0:0*/ __Vchglast__TOP__top__DOT__soc__DOT____Vcellinp__T80x__reset_n;
        SData/*13:0*/ __Vdlyvdim0__top__DOT__soc__DOT__vga__DOT__vmem__v0;
        SData/*15:0*/ __Vdly__top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__PC;
        SData/*15:0*/ __Vdly__top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SP;
        IData/*31:0*/ __Vm_traceActivity;
    };
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vtop__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vtop);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vtop(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vtop();
    /// Trace signals in the model; called by application code
    void trace(VerilatedVcdC* tfp, int levels, int options = 0);
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vtop__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vtop__Syms* symsp, bool first);
  private:
    static QData _change_request(Vtop__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__2(Vtop__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vtop__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _multiclk__TOP__9(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__10(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__11(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__4(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__5(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__6(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__7(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__8(Vtop__Syms* __restrict vlSymsp);
    static void _settle__TOP__3(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void traceChgThis(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__10(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__11(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__12(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__13(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__14(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__15(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__16(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__17(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__18(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__19(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__2(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__3(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__4(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__5(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__6(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__7(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__8(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__9(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceFullThis(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) VL_ATTR_COLD;
    static void traceFullThis__1(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) VL_ATTR_COLD;
    static void traceInitThis(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) VL_ATTR_COLD;
    static void traceInitThis__1(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) VL_ATTR_COLD;
    static void traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
