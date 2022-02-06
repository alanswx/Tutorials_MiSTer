// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


//======================

void Vtop::traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vtop* t = (Vtop*)userthis;
    Vtop__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (vlSymsp->getClearActivity()) {
        t->traceChgThis(vlSymsp, vcdp, code);
    }
}

//======================


void Vtop::traceChgThis(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    if (false && vcdp) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
                               | (vlTOPp->__Vm_traceActivity 
                                  >> 1U))))) {
            vlTOPp->traceChgThis__2(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
                               | (vlTOPp->__Vm_traceActivity 
                                  >> 2U))))) {
            vlTOPp->traceChgThis__3(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((1U & ((vlTOPp->__Vm_traceActivity 
                                | (vlTOPp->__Vm_traceActivity 
                                   >> 2U)) | (vlTOPp->__Vm_traceActivity 
                                              >> 7U))))) {
            vlTOPp->traceChgThis__4(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
                               | (vlTOPp->__Vm_traceActivity 
                                  >> 3U))))) {
            vlTOPp->traceChgThis__5(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
                               | (vlTOPp->__Vm_traceActivity 
                                  >> 4U))))) {
            vlTOPp->traceChgThis__6(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
                               | (vlTOPp->__Vm_traceActivity 
                                  >> 5U))))) {
            vlTOPp->traceChgThis__7(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
                               | (vlTOPp->__Vm_traceActivity 
                                  >> 6U))))) {
            vlTOPp->traceChgThis__8(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
                               | (vlTOPp->__Vm_traceActivity 
                                  >> 7U))))) {
            vlTOPp->traceChgThis__9(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
                               | (vlTOPp->__Vm_traceActivity 
                                  >> 8U))))) {
            vlTOPp->traceChgThis__10(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((2U & vlTOPp->__Vm_traceActivity))) {
            vlTOPp->traceChgThis__11(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((4U & vlTOPp->__Vm_traceActivity))) {
            vlTOPp->traceChgThis__12(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((1U & ((vlTOPp->__Vm_traceActivity 
                                >> 2U) | (vlTOPp->__Vm_traceActivity 
                                          >> 3U))))) {
            vlTOPp->traceChgThis__13(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((1U & ((vlTOPp->__Vm_traceActivity 
                                >> 2U) | (vlTOPp->__Vm_traceActivity 
                                          >> 4U))))) {
            vlTOPp->traceChgThis__14(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((8U & vlTOPp->__Vm_traceActivity))) {
            vlTOPp->traceChgThis__15(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((0x10U & vlTOPp->__Vm_traceActivity))) {
            vlTOPp->traceChgThis__16(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((0x20U & vlTOPp->__Vm_traceActivity))) {
            vlTOPp->traceChgThis__17(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((0x80U & vlTOPp->__Vm_traceActivity))) {
            vlTOPp->traceChgThis__18(vlSymsp, vcdp, code);
        }
        vlTOPp->traceChgThis__19(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vtop::traceChgThis__2(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+1);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgCData(oldp+0,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Prefix),2);
        vcdp->chgBit(oldp+1,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ExchangeDH));
        vcdp->chgBit(oldp+2,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ExchangeRp));
        vcdp->chgBit(oldp+3,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ExchangeRS));
        vcdp->chgBit(oldp+4,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SetDI));
        vcdp->chgBit(oldp+5,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SetEI));
        vcdp->chgBit(oldp+6,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Halt));
        vcdp->chgCData(oldp+7,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__BitMask),8);
    }
}

void Vtop::traceChgThis__3(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+9);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgCData(oldp+0,(vlTOPp->top__DOT__soc__DOT__cpu_reset_cnt),8);
        vcdp->chgBit(oldp+1,((0xffU != (IData)(vlTOPp->top__DOT__soc__DOT__cpu_reset_cnt))));
    }
}

void Vtop::traceChgThis__4(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+11);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgCData(oldp+0,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH
                               [vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrB]),8);
        vcdp->chgCData(oldp+1,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL
                               [vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrA]),8);
        vcdp->chgCData(oldp+2,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL
                               [vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrB]),8);
        vcdp->chgCData(oldp+3,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH
                               [vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrA]),8);
    }
}

void Vtop::traceChgThis__5(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+15);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgIData(oldp+0,(vlTOPp->top__DOT__soc__DOT__pos),24);
        vcdp->chgIData(oldp+1,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__inc_pos),24);
    }
}

void Vtop::traceChgThis__6(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+17);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(oldp+0,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__JumpXY));
        vcdp->chgBit(oldp+1,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__LDSPHL));
        vcdp->chgCData(oldp+2,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Special_LD),3);
        vcdp->chgBit(oldp+3,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ExchangeAF));
        vcdp->chgBit(oldp+4,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_CPL));
        vcdp->chgBit(oldp+5,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_CCF));
        vcdp->chgBit(oldp+6,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_SCF));
        vcdp->chgCData(oldp+7,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IMode),2);
        vcdp->chgBit(oldp+8,(vlTOPp->top__DOT__soc__DOT____Vcellinp__ram__wren_a));
    }
}

void Vtop::traceChgThis__7(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+26);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgSData(oldp+0,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegBusC),16);
    }
}

void Vtop::traceChgThis__8(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+27);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(oldp+0,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__charmap_a));
    }
}

void Vtop::traceChgThis__9(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+28);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(oldp+0,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__no_read));
        vcdp->chgBit(oldp+1,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__write));
        vcdp->chgBit(oldp+2,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__iorq_i));
        vcdp->chgBit(oldp+3,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_DJNZ));
        vcdp->chgCData(oldp+4,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegDIH),8);
        vcdp->chgCData(oldp+5,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegDIL),8);
        vcdp->chgSData(oldp+6,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegBusA),16);
        vcdp->chgSData(oldp+7,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegBusB),16);
        vcdp->chgCData(oldp+8,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrA),3);
        vcdp->chgCData(oldp+9,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrB),3);
        vcdp->chgBit(oldp+10,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegWEH));
        vcdp->chgBit(oldp+11,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegWEL));
        vcdp->chgSData(oldp+12,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ID16),16);
        vcdp->chgCData(oldp+13,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Save_Mux),8);
        vcdp->chgBit(oldp+14,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__last_mcycle));
        vcdp->chgBit(oldp+15,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__last_tstate));
        vcdp->chgBit(oldp+16,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__last_tstate));
        vcdp->chgBit(oldp+17,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__NextIs_XY_Fetch));
        vcdp->chgBit(oldp+18,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Auto_Wait));
        vcdp->chgCData(oldp+19,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ALU_Q),8);
        vcdp->chgCData(oldp+20,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__F_Out),8);
        vcdp->chgCData(oldp+21,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__mcycles_d),3);
        vcdp->chgCData(oldp+22,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__tstates),3);
        vcdp->chgBit(oldp+23,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Inc_PC));
        vcdp->chgBit(oldp+24,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Inc_WZ));
        vcdp->chgCData(oldp+25,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IncDec_16),4);
        vcdp->chgBit(oldp+26,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Read_To_Acc));
        vcdp->chgBit(oldp+27,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Read_To_Reg));
        vcdp->chgCData(oldp+28,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Set_BusB_To),4);
        vcdp->chgCData(oldp+29,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Set_BusA_To),4);
        vcdp->chgCData(oldp+30,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ALU_Op),4);
        vcdp->chgBit(oldp+31,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Save_ALU));
        vcdp->chgBit(oldp+32,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__PreserveC));
        vcdp->chgBit(oldp+33,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Arith16));
        vcdp->chgCData(oldp+34,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Set_Addr_To),3);
        vcdp->chgBit(oldp+35,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Jump));
        vcdp->chgBit(oldp+36,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__JumpE));
        vcdp->chgBit(oldp+37,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Call));
        vcdp->chgBit(oldp+38,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RstP));
        vcdp->chgBit(oldp+39,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__LDZ));
        vcdp->chgBit(oldp+40,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__LDW));
        vcdp->chgBit(oldp+41,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_RETN));
        vcdp->chgBit(oldp+42,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_BT));
        vcdp->chgBit(oldp+43,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_BC));
        vcdp->chgBit(oldp+44,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_BTR));
        vcdp->chgBit(oldp+45,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_RLD));
        vcdp->chgBit(oldp+46,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_RRD));
        vcdp->chgBit(oldp+47,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_INRC));
        vcdp->chgSData(oldp+48,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__PC16),16);
        vcdp->chgSData(oldp+49,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__PC16_B),16);
        vcdp->chgSData(oldp+50,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SP16),16);
        vcdp->chgSData(oldp+51,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SP16_A),16);
        vcdp->chgSData(oldp+52,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SP16_B),16);
        vcdp->chgSData(oldp+53,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ID16_B),16);
        vcdp->chgCData(oldp+54,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__DDD),3);
        vcdp->chgCData(oldp+55,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__SSS),3);
        vcdp->chgCData(oldp+56,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__DPAIR),2);
        vcdp->chgBit(oldp+57,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__UseCarry));
        vcdp->chgBit(oldp+58,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__Carry7_v));
        vcdp->chgBit(oldp+59,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__OverFlow_v));
        vcdp->chgBit(oldp+60,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__HalfCarry_v));
        vcdp->chgBit(oldp+61,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__Carry_v));
        vcdp->chgCData(oldp+62,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__Q_v),8);
        vcdp->chgCData(oldp+63,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__Q_t),8);
        vcdp->chgSData(oldp+64,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__DAA_Q),9);
    }
}

void Vtop::traceChgThis__10(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+93);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(oldp+0,(vlTOPp->top__DOT__soc__DOT____Vcellinp__T80x__reset_n));
    }
}

void Vtop::traceChgThis__11(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+94);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(oldp+0,(vlTOPp->top__DOT__soc__DOT__cpu_rd_n));
        vcdp->chgBit(oldp+1,(vlTOPp->top__DOT__soc__DOT__cpu_mreq_n));
        vcdp->chgBit(oldp+2,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__m1_n));
        vcdp->chgBit(oldp+3,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__iorq_n));
        vcdp->chgBit(oldp+4,((1U & (~ (IData)(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Halt_FF)))));
        vcdp->chgBit(oldp+5,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IntE_FF1));
        vcdp->chgCData(oldp+6,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IR),8);
        vcdp->chgCData(oldp+7,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ISet),2);
        vcdp->chgBit(oldp+8,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Halt_FF));
        vcdp->chgBit(oldp+9,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BusReq_s));
        vcdp->chgBit(oldp+10,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__NMI_s));
        vcdp->chgBit(oldp+11,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__INT_s));
        vcdp->chgCData(oldp+12,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Pre_XY_F_M),3);
        vcdp->chgBit(oldp+13,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__No_BTR));
        vcdp->chgBit(oldp+14,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BTR_r));
        vcdp->chgBit(oldp+15,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Auto_Wait_t2));
        vcdp->chgBit(oldp+16,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Arith16_r));
        vcdp->chgBit(oldp+17,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Z16_r));
        vcdp->chgCData(oldp+18,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__mcycles),3);
        vcdp->chgBit(oldp+19,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Oldnmi_n));
        vcdp->chgCData(oldp+20,((0x3fU & (IData)(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IR))),6);
    }
}

void Vtop::traceChgThis__12(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+115);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgCData(oldp+0,(vlTOPp->top__DOT__soc__DOT__ram_data_out),8);
        vcdp->chgCData(oldp+1,(vlTOPp->top__DOT__soc__DOT__rom_data_out),8);
        vcdp->chgCData(oldp+2,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chrom_data_out),8);
        vcdp->chgCData(oldp+3,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chmap_data_out),8);
        vcdp->chgCData(oldp+4,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chrom__DOT__q_b),8);
        vcdp->chgCData(oldp+5,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chram__DOT__q_a),8);
        vcdp->chgCData(oldp+6,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrA_r),3);
        vcdp->chgCData(oldp+7,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrB_r),3);
        vcdp->chgCData(oldp+8,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrC),3);
        vcdp->chgSData(oldp+9,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegBusA_r),16);
        vcdp->chgCData(oldp+10,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL
                                [vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrC]),8);
        vcdp->chgCData(oldp+11,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH
                                [vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrC]),8);
        vcdp->chgCData(oldp+12,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[0]),8);
        vcdp->chgCData(oldp+13,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[1]),8);
        vcdp->chgCData(oldp+14,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[2]),8);
        vcdp->chgCData(oldp+15,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[3]),8);
        vcdp->chgCData(oldp+16,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[4]),8);
        vcdp->chgCData(oldp+17,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[5]),8);
        vcdp->chgCData(oldp+18,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[6]),8);
        vcdp->chgCData(oldp+19,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[7]),8);
        vcdp->chgCData(oldp+20,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[0]),8);
        vcdp->chgCData(oldp+21,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[1]),8);
        vcdp->chgCData(oldp+22,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[2]),8);
        vcdp->chgCData(oldp+23,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[3]),8);
        vcdp->chgCData(oldp+24,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[4]),8);
        vcdp->chgCData(oldp+25,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[5]),8);
        vcdp->chgCData(oldp+26,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[6]),8);
        vcdp->chgCData(oldp+27,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[7]),8);
        vcdp->chgCData(oldp+28,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH
                                [0U]),8);
        vcdp->chgCData(oldp+29,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL
                                [0U]),8);
        vcdp->chgCData(oldp+30,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH
                                [1U]),8);
        vcdp->chgCData(oldp+31,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL
                                [1U]),8);
        vcdp->chgCData(oldp+32,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH
                                [2U]),8);
        vcdp->chgCData(oldp+33,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL
                                [2U]),8);
        vcdp->chgSData(oldp+34,(((vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH
                                  [3U] << 8U) | vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL
                                 [3U])),16);
        vcdp->chgSData(oldp+35,(((vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH
                                  [7U] << 8U) | vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL
                                 [7U])),16);
        vcdp->chgCData(oldp+36,(vlTOPp->top__DOT__soc__DOT__rom__DOT__q_b),8);
        vcdp->chgCData(oldp+37,(vlTOPp->top__DOT__soc__DOT__ram__DOT__q_b),8);
    }
}

void Vtop::traceChgThis__13(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+153);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgSData(oldp+0,((((IData)(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chmap_data_out) 
                                 << 3U) | (7U & (IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__v_cnt)))),12);
        vcdp->chgSData(oldp+1,((((IData)(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chmap_data_out) 
                                 << 3U) | (7U & (IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__v_cnt)))),11);
    }
}

void Vtop::traceChgThis__14(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+155);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgCData(oldp+0,(((0x8000U & (IData)(vlTOPp->top__DOT__soc__DOT__cpu_addr))
                                 ? (IData)(vlTOPp->top__DOT__soc__DOT__ram_data_out)
                                 : (IData)(vlTOPp->top__DOT__soc__DOT__rom_data_out))),8);
    }
}

void Vtop::traceChgThis__15(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+156);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(oldp+0,(vlTOPp->top__DOT__soc__DOT__vga__DOT__de));
        vcdp->chgCData(oldp+1,(((0xe0U & (IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel)) 
                                | ((0x1cU & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel) 
                                             >> 3U)) 
                                   | (3U & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel) 
                                            >> 6U))))),8);
        vcdp->chgCData(oldp+2,(((0xe0U & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel) 
                                          << 3U)) | 
                                ((0x1cU & (IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel)) 
                                 | (3U & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel) 
                                          >> 3U))))),8);
        vcdp->chgCData(oldp+3,(((0xc0U & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel) 
                                          << 6U)) | 
                                ((0x30U & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel) 
                                           << 4U)) 
                                 | ((0xcU & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel) 
                                             << 2U)) 
                                    | (3U & (IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel)))))),8);
        vcdp->chgSData(oldp+4,(vlTOPp->top__DOT__soc__DOT__vga__DOT__h_cnt),10);
        vcdp->chgSData(oldp+5,(vlTOPp->top__DOT__soc__DOT__vga__DOT__v_cnt),10);
        vcdp->chgSData(oldp+6,(vlTOPp->top__DOT__soc__DOT__div),13);
        vcdp->chgSData(oldp+7,(((0xfc0U & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__v_cnt) 
                                           << 3U)) 
                                | (0x3fU & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__h_cnt) 
                                            >> 3U)))),12);
        vcdp->chgIData(oldp+8,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__pos_r),24);
        vcdp->chgSData(oldp+9,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__wr_addr),12);
        vcdp->chgCData(oldp+10,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__wr_data),8);
        vcdp->chgBit(oldp+11,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__wheel_state));
        vcdp->chgCData(oldp+12,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__state),2);
        vcdp->chgCData(oldp+13,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__blocks),5);
        vcdp->chgCData(oldp+14,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__cur_block),5);
        vcdp->chgBit(oldp+15,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__wr_ena));
        vcdp->chgCData(oldp+16,((7U & ((IData)(7U) 
                                       - (IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__h_cnt)))),3);
        vcdp->chgCData(oldp+17,((7U & (IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__v_cnt))),3);
        vcdp->chgCData(oldp+18,((0x3fU & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__h_cnt) 
                                          >> 3U))),6);
        vcdp->chgCData(oldp+19,((0x3fU & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__v_cnt) 
                                          >> 3U))),6);
        vcdp->chgSData(oldp+20,((0x7ffU & (IData)(vlTOPp->top__DOT__soc__DOT__overlay__DOT__wr_addr))),11);
        vcdp->chgSData(oldp+21,(((0x7c0U & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__v_cnt) 
                                            << 3U)) 
                                 | (0x3fU & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__h_cnt) 
                                             >> 3U)))),11);
        vcdp->chgSData(oldp+22,(vlTOPp->top__DOT__soc__DOT__vga__DOT__video_counter),14);
        vcdp->chgCData(oldp+23,(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel),8);
    }
}

void Vtop::traceChgThis__16(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+180);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgSData(oldp+0,(vlTOPp->top__DOT__soc__DOT__cpu_addr),16);
        vcdp->chgCData(oldp+1,(vlTOPp->top__DOT__soc__DOT__cpu_dout),8);
        vcdp->chgBit(oldp+2,(vlTOPp->top__DOT__soc__DOT__cpu_wr_n));
        vcdp->chgBit(oldp+3,((1U & ((~ (IData)(vlTOPp->top__DOT__soc__DOT__cpu_wr_n)) 
                                    & (~ ((IData)(vlTOPp->top__DOT__soc__DOT__cpu_addr) 
                                          >> 0xfU))))));
        vcdp->chgSData(oldp+4,((0x3fffU & (IData)(vlTOPp->top__DOT__soc__DOT__cpu_addr))),14);
        vcdp->chgBit(oldp+5,((1U & (~ (IData)(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IntCycle)))));
        vcdp->chgCData(oldp+6,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Ap),8);
        vcdp->chgCData(oldp+7,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Fp),8);
        vcdp->chgCData(oldp+8,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I),8);
        vcdp->chgBit(oldp+9,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Alternate));
        vcdp->chgSData(oldp+10,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__TmpAddr),16);
        vcdp->chgBit(oldp+11,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IntE_FF2));
        vcdp->chgCData(oldp+12,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IStatus),2);
        vcdp->chgCData(oldp+13,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__XY_State),2);
        vcdp->chgBit(oldp+14,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__XY_Ind));
        vcdp->chgBit(oldp+15,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Auto_Wait_t1));
        vcdp->chgCData(oldp+16,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Read_To_Reg_r),5);
        vcdp->chgCData(oldp+17,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ALU_Op_r),4);
        vcdp->chgBit(oldp+18,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__PreserveC_r));
        vcdp->chgBit(oldp+19,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IntCycle));
        vcdp->chgBit(oldp+20,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__NMICycle));
        vcdp->chgSData(oldp+21,((0xfffU & (IData)(vlTOPp->top__DOT__soc__DOT__cpu_addr))),12);
    }
}

void Vtop::traceChgThis__17(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+202);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(oldp+0,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IncDecZ));
        vcdp->chgCData(oldp+1,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BusB),8);
        vcdp->chgCData(oldp+2,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BusA),8);
    }
}

void Vtop::traceChgThis__18(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+205);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(oldp+0,((1U & (~ (IData)(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BusAck)))));
        vcdp->chgCData(oldp+1,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__di_reg),8);
        vcdp->chgCData(oldp+2,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__mcycle),7);
        vcdp->chgCData(oldp+3,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__tstate),7);
        vcdp->chgCData(oldp+4,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ACC),8);
        vcdp->chgCData(oldp+5,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__F),8);
        vcdp->chgSData(oldp+6,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SP),16);
        vcdp->chgSData(oldp+7,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__PC),16);
        vcdp->chgBit(oldp+8,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BusAck));
        vcdp->chgBit(oldp+9,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Save_ALU_r));
    }
}

void Vtop::traceChgThis__19(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+215);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(oldp+0,(vlTOPp->clk_sys));
        vcdp->chgBit(oldp+1,(vlTOPp->clk_vid));
        vcdp->chgBit(oldp+2,(vlTOPp->reset));
        vcdp->chgCData(oldp+3,(vlTOPp->VGA_R),8);
        vcdp->chgCData(oldp+4,(vlTOPp->VGA_G),8);
        vcdp->chgCData(oldp+5,(vlTOPp->VGA_B),8);
        vcdp->chgBit(oldp+6,(vlTOPp->VGA_HS));
        vcdp->chgBit(oldp+7,(vlTOPp->VGA_VS));
        vcdp->chgBit(oldp+8,(vlTOPp->VGA_HB));
        vcdp->chgBit(oldp+9,(vlTOPp->VGA_VB));
        vcdp->chgBit(oldp+10,(vlTOPp->ioctl_download));
        vcdp->chgBit(oldp+11,(vlTOPp->ioctl_wr));
        vcdp->chgIData(oldp+12,(vlTOPp->ioctl_addr),25);
        vcdp->chgCData(oldp+13,(vlTOPp->ioctl_dout),8);
        vcdp->chgCData(oldp+14,(vlTOPp->ioctl_index),8);
        vcdp->chgBit(oldp+15,(vlTOPp->ioctl_wait));
        vcdp->chgBit(oldp+16,(vlTOPp->top__DOT__clk_sys));
        vcdp->chgBit(oldp+17,(vlTOPp->top__DOT__clk_vid));
        vcdp->chgBit(oldp+18,(vlTOPp->top__DOT__reset));
        vcdp->chgCData(oldp+19,(vlTOPp->top__DOT__VGA_R),8);
        vcdp->chgCData(oldp+20,(vlTOPp->top__DOT__VGA_G),8);
        vcdp->chgCData(oldp+21,(vlTOPp->top__DOT__VGA_B),8);
    }
}
