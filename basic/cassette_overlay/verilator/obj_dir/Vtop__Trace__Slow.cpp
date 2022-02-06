// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


//======================

void Vtop::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addCallback(&Vtop::traceInit, &Vtop::traceFull, &Vtop::traceChg, this);
}
void Vtop::traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->open()
    Vtop* t = (Vtop*)userthis;
    Vtop__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vcdp->scopeEscape(' ');
    t->traceInitThis(vlSymsp, vcdp, code);
    vcdp->scopeEscape('.');
}
void Vtop::traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vtop* t = (Vtop*)userthis;
    Vtop__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    t->traceFullThis(vlSymsp, vcdp, code);
}

//======================


void Vtop::traceInitThis(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    if (false && vcdp) {}  // Prevent unused
    vcdp->module(vlSymsp->name());  // Setup signal names
    // Body
    {
        vlTOPp->traceInitThis__1(vlSymsp, vcdp, code);
    }
}

void Vtop::traceFullThis(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    if (false && vcdp) {}  // Prevent unused
    // Body
    {
        vlTOPp->traceFullThis__1(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vtop::traceInitThis__1(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (false && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->declBit(c+215,"clk_sys", false,-1);
        vcdp->declBit(c+216,"clk_vid", false,-1);
        vcdp->declBit(c+217,"reset", false,-1);
        vcdp->declBus(c+218,"VGA_R", false,-1, 7,0);
        vcdp->declBus(c+219,"VGA_G", false,-1, 7,0);
        vcdp->declBus(c+220,"VGA_B", false,-1, 7,0);
        vcdp->declBit(c+221,"VGA_HS", false,-1);
        vcdp->declBit(c+222,"VGA_VS", false,-1);
        vcdp->declBit(c+223,"VGA_HB", false,-1);
        vcdp->declBit(c+224,"VGA_VB", false,-1);
        vcdp->declBit(c+225,"ioctl_download", false,-1);
        vcdp->declBit(c+226,"ioctl_wr", false,-1);
        vcdp->declBus(c+227,"ioctl_addr", false,-1, 24,0);
        vcdp->declBus(c+228,"ioctl_dout", false,-1, 7,0);
        vcdp->declBus(c+229,"ioctl_index", false,-1, 7,0);
        vcdp->declBit(c+230,"ioctl_wait", false,-1);
        vcdp->declBit(c+231,"top clk_sys", false,-1);
        vcdp->declBit(c+232,"top clk_vid", false,-1);
        vcdp->declBit(c+233,"top reset", false,-1);
        vcdp->declBus(c+234,"top VGA_R", false,-1, 7,0);
        vcdp->declBus(c+235,"top VGA_G", false,-1, 7,0);
        vcdp->declBus(c+236,"top VGA_B", false,-1, 7,0);
        vcdp->declBit(c+221,"top VGA_HS", false,-1);
        vcdp->declBit(c+222,"top VGA_VS", false,-1);
        vcdp->declBit(c+223,"top VGA_HB", false,-1);
        vcdp->declBit(c+224,"top VGA_VB", false,-1);
        vcdp->declBit(c+225,"top ioctl_download", false,-1);
        vcdp->declBit(c+226,"top ioctl_wr", false,-1);
        vcdp->declBus(c+227,"top ioctl_addr", false,-1, 24,0);
        vcdp->declBus(c+228,"top ioctl_dout", false,-1, 7,0);
        vcdp->declBus(c+229,"top ioctl_index", false,-1, 7,0);
        vcdp->declBit(c+230,"top ioctl_wait", false,-1);
        vcdp->declBit(c+156,"top VGA_DE", false,-1);
        vcdp->declBit(c+231,"top soc clk_sys", false,-1);
        vcdp->declBit(c+232,"top soc pixel_clock", false,-1);
        vcdp->declBit(c+221,"top soc VGA_HS", false,-1);
        vcdp->declBit(c+222,"top soc VGA_VS", false,-1);
        vcdp->declBus(c+234,"top soc VGA_R", false,-1, 7,0);
        vcdp->declBus(c+235,"top soc VGA_G", false,-1, 7,0);
        vcdp->declBus(c+236,"top soc VGA_B", false,-1, 7,0);
        vcdp->declBit(c+223,"top soc VGA_HB", false,-1);
        vcdp->declBit(c+224,"top soc VGA_VB", false,-1);
        vcdp->declBit(c+156,"top soc VGA_DE", false,-1);
        vcdp->declBit(c+237,"top soc vs", false,-1);
        vcdp->declBit(c+238,"top soc hs", false,-1);
        vcdp->declBit(c+239,"top soc ce_pix", false,-1);
        vcdp->declBit(c+240,"top soc hblank", false,-1);
        vcdp->declBit(c+241,"top soc vblank", false,-1);
        vcdp->declBit(c+242,"top soc interlace", false,-1);
        vcdp->declBus(c+157,"top soc r", false,-1, 7,0);
        vcdp->declBus(c+158,"top soc g", false,-1, 7,0);
        vcdp->declBus(c+159,"top soc b", false,-1, 7,0);
        vcdp->declBus(c+160,"top soc hcount", false,-1, 9,0);
        vcdp->declBus(c+161,"top soc vcount", false,-1, 9,0);
        vcdp->declBus(c+243,"top soc tape_end", false,-1, 23,0);
        vcdp->declBus(c+15,"top soc pos", false,-1, 23,0);
        vcdp->declBus(c+162,"top soc div", false,-1, 12,0);
        vcdp->declBus(c+9,"top soc cpu_reset_cnt", false,-1, 7,0);
        vcdp->declBit(c+10,"top soc cpu_reset", false,-1);
        vcdp->declBit(c+215,"top soc cpu_clock", false,-1);
        vcdp->declBus(c+180,"top soc cpu_addr", false,-1, 15,0);
        vcdp->declBus(c+155,"top soc cpu_din", false,-1, 7,0);
        vcdp->declBus(c+181,"top soc cpu_dout", false,-1, 7,0);
        vcdp->declBit(c+94,"top soc cpu_rd_n", false,-1);
        vcdp->declBit(c+182,"top soc cpu_wr_n", false,-1);
        vcdp->declBit(c+95,"top soc cpu_mreq_n", false,-1);
        vcdp->declBus(c+115,"top soc ram_data_out", false,-1, 7,0);
        vcdp->declBus(c+116,"top soc rom_data_out", false,-1, 7,0);
        vcdp->declBus(c+244,"top soc overlay RGB", false,-1, 23,0);
        vcdp->declBit(c+245,"top soc overlay reset", false,-1);
        vcdp->declBus(c+157,"top soc overlay i_r", false,-1, 7,0);
        vcdp->declBus(c+158,"top soc overlay i_g", false,-1, 7,0);
        vcdp->declBus(c+159,"top soc overlay i_b", false,-1, 7,0);
        vcdp->declBit(c+231,"top soc overlay i_clk", false,-1);
        vcdp->declBit(c+232,"top soc overlay i_pix", false,-1);
        vcdp->declBus(c+160,"top soc overlay hcnt", false,-1, 9,0);
        vcdp->declBus(c+161,"top soc overlay vcnt", false,-1, 9,0);
        vcdp->declBus(c+234,"top soc overlay o_r", false,-1, 7,0);
        vcdp->declBus(c+235,"top soc overlay o_g", false,-1, 7,0);
        vcdp->declBus(c+236,"top soc overlay o_b", false,-1, 7,0);
        vcdp->declBit(c+246,"top soc overlay ena", false,-1);
        vcdp->declBus(c+243,"top soc overlay max", false,-1, 23,0);
        vcdp->declBus(c+15,"top soc overlay pos", false,-1, 23,0);
        vcdp->declBus(c+247,"top soc overlay charmap_r", false,-1, 7,0);
        vcdp->declBus(c+248,"top soc overlay charmap_g", false,-1, 7,0);
        vcdp->declBus(c+249,"top soc overlay charmap_b", false,-1, 7,0);
        vcdp->declBit(c+27,"top soc overlay charmap_a", false,-1);
        vcdp->declBus(c+163,"top soc overlay chram_addr", false,-1, 11,0);
        vcdp->declBus(c+153,"top soc overlay chrom_addr", false,-1, 11,0);
        vcdp->declBus(c+117,"top soc overlay chrom_data_out", false,-1, 7,0);
        vcdp->declBus(c+118,"top soc overlay chmap_data_out", false,-1, 7,0);
        vcdp->declBus(c+164,"top soc overlay pos_r", false,-1, 23,0);
        vcdp->declBus(c+165,"top soc overlay wr_addr", false,-1, 11,0);
        vcdp->declBus(c+166,"top soc overlay wr_data", false,-1, 7,0);
        vcdp->declBit(c+167,"top soc overlay wheel_state", false,-1);
        vcdp->declBus(c+168,"top soc overlay state", false,-1, 1,0);
        vcdp->declBus(c+250,"top soc overlay increment", false,-1, 23,0);
        vcdp->declBus(c+16,"top soc overlay inc_pos", false,-1, 23,0);
        vcdp->declBus(c+169,"top soc overlay blocks", false,-1, 4,0);
        vcdp->declBus(c+170,"top soc overlay cur_block", false,-1, 4,0);
        vcdp->declBit(c+171,"top soc overlay wr_ena", false,-1);
        vcdp->declBit(c+231,"top soc overlay casval clk", false,-1);
        vcdp->declBit(c+245,"top soc overlay casval reset", false,-1);
        vcdp->declBus(c+160,"top soc overlay casval hcnt", false,-1, 9,0);
        vcdp->declBus(c+161,"top soc overlay casval vcnt", false,-1, 9,0);
        vcdp->declBus(c+117,"top soc overlay casval chrom_data_out", false,-1, 7,0);
        vcdp->declBus(c+118,"top soc overlay casval chmap_data_out", false,-1, 7,0);
        vcdp->declBus(c+163,"top soc overlay casval chram_addr", false,-1, 11,0);
        vcdp->declBus(c+153,"top soc overlay casval chrom_addr", false,-1, 11,0);
        vcdp->declBit(c+27,"top soc overlay casval a", false,-1);
        vcdp->declBus(c+172,"top soc overlay casval chpos_x", false,-1, 2,0);
        vcdp->declBus(c+173,"top soc overlay casval chpos_y", false,-1, 2,0);
        vcdp->declBus(c+174,"top soc overlay casval chram_x", false,-1, 5,0);
        vcdp->declBus(c+175,"top soc overlay casval chram_y", false,-1, 5,0);
        vcdp->declBus(c+251,"top soc overlay chrom width_a", false,-1, 31,0);
        vcdp->declBus(c+252,"top soc overlay chrom widthad_a", false,-1, 31,0);
        vcdp->declQuad(c+253,"top soc overlay chrom init_file", false,-1, 63,0);
        vcdp->declBit(c+231,"top soc overlay chrom clock_a", false,-1);
        vcdp->declBit(c+255,"top soc overlay chrom wren_a", false,-1);
        vcdp->declBus(c+154,"top soc overlay chrom address_a", false,-1, 10,0);
        vcdp->declBus(c+256,"top soc overlay chrom data_a", false,-1, 7,0);
        vcdp->declBus(c+117,"top soc overlay chrom q_a", false,-1, 7,0);
        vcdp->declBit(c+231,"top soc overlay chrom clock_b", false,-1);
        vcdp->declBit(c+257,"top soc overlay chrom wren_b", false,-1);
        vcdp->declBus(c+258,"top soc overlay chrom address_b", false,-1, 10,0);
        vcdp->declBus(c+259,"top soc overlay chrom data_b", false,-1, 7,0);
        vcdp->declBus(c+119,"top soc overlay chrom q_b", false,-1, 7,0);
        vcdp->declBit(c+260,"top soc overlay chrom byteena_a", false,-1);
        vcdp->declBit(c+261,"top soc overlay chrom byteena_b", false,-1);
        vcdp->declBus(c+251,"top soc overlay chram width_a", false,-1, 31,0);
        vcdp->declBus(c+252,"top soc overlay chram widthad_a", false,-1, 31,0);
        vcdp->declArray(c+262,"top soc overlay chram init_file", false,-1, 111,0);
        vcdp->declBit(c+231,"top soc overlay chram clock_a", false,-1);
        vcdp->declBit(c+171,"top soc overlay chram wren_a", false,-1);
        vcdp->declBus(c+176,"top soc overlay chram address_a", false,-1, 10,0);
        vcdp->declBus(c+166,"top soc overlay chram data_a", false,-1, 7,0);
        vcdp->declBus(c+120,"top soc overlay chram q_a", false,-1, 7,0);
        vcdp->declBit(c+231,"top soc overlay chram clock_b", false,-1);
        vcdp->declBit(c+255,"top soc overlay chram wren_b", false,-1);
        vcdp->declBus(c+177,"top soc overlay chram address_b", false,-1, 10,0);
        vcdp->declBus(c+266,"top soc overlay chram data_b", false,-1, 7,0);
        vcdp->declBus(c+118,"top soc overlay chram q_b", false,-1, 7,0);
        vcdp->declBit(c+267,"top soc overlay chram byteena_a", false,-1);
        vcdp->declBit(c+268,"top soc overlay chram byteena_b", false,-1);
        vcdp->declBit(c+232,"top soc vga pclk", false,-1);
        vcdp->declBit(c+215,"top soc vga cpu_clk", false,-1);
        vcdp->declBit(c+183,"top soc vga cpu_wr", false,-1);
        vcdp->declBus(c+184,"top soc vga cpu_addr", false,-1, 13,0);
        vcdp->declBus(c+181,"top soc vga cpu_data", false,-1, 7,0);
        vcdp->declBit(c+221,"top soc vga hs", false,-1);
        vcdp->declBit(c+222,"top soc vga vs", false,-1);
        vcdp->declBus(c+157,"top soc vga r", false,-1, 7,0);
        vcdp->declBus(c+158,"top soc vga g", false,-1, 7,0);
        vcdp->declBus(c+159,"top soc vga b", false,-1, 7,0);
        vcdp->declBit(c+223,"top soc vga VGA_HB", false,-1);
        vcdp->declBit(c+224,"top soc vga VGA_VB", false,-1);
        vcdp->declBit(c+156,"top soc vga VGA_DE", false,-1);
        vcdp->declBus(c+160,"top soc vga hcount", false,-1, 9,0);
        vcdp->declBus(c+161,"top soc vga vcount", false,-1, 9,0);
        vcdp->declBus(c+269,"top soc vga H", false,-1, 31,0);
        vcdp->declBus(c+270,"top soc vga HFP", false,-1, 31,0);
        vcdp->declBus(c+271,"top soc vga HS", false,-1, 31,0);
        vcdp->declBus(c+272,"top soc vga HBP", false,-1, 31,0);
        vcdp->declBus(c+273,"top soc vga V", false,-1, 31,0);
        vcdp->declBus(c+274,"top soc vga VFP", false,-1, 31,0);
        vcdp->declBus(c+275,"top soc vga VS", false,-1, 31,0);
        vcdp->declBus(c+276,"top soc vga VBP", false,-1, 31,0);
        vcdp->declBus(c+160,"top soc vga h_cnt", false,-1, 9,0);
        vcdp->declBus(c+161,"top soc vga v_cnt", false,-1, 9,0);
        vcdp->declBit(c+277,"top soc vga hblank", false,-1);
        vcdp->declBit(c+278,"top soc vga vblank", false,-1);
        vcdp->declBus(c+178,"top soc vga video_counter", false,-1, 13,0);
        vcdp->declBus(c+179,"top soc vga pixel", false,-1, 7,0);
        vcdp->declBit(c+156,"top soc vga de", false,-1);
        vcdp->declBus(c+279,"top soc T80x Mode", false,-1, 31,0);
        vcdp->declBus(c+280,"top soc T80x T2Write", false,-1, 31,0);
        vcdp->declBus(c+280,"top soc T80x IOWait", false,-1, 31,0);
        vcdp->declBit(c+93,"top soc T80x reset_n", false,-1);
        vcdp->declBit(c+215,"top soc T80x clk", false,-1);
        vcdp->declBit(c+255,"top soc T80x wait_n", false,-1);
        vcdp->declBit(c+246,"top soc T80x int_n", false,-1);
        vcdp->declBit(c+246,"top soc T80x nmi_n", false,-1);
        vcdp->declBit(c+246,"top soc T80x busrq_n", false,-1);
        vcdp->declBit(c+96,"top soc T80x m1_n", false,-1);
        vcdp->declBit(c+95,"top soc T80x mreq_n", false,-1);
        vcdp->declBit(c+97,"top soc T80x iorq_n", false,-1);
        vcdp->declBit(c+94,"top soc T80x rd_n", false,-1);
        vcdp->declBit(c+182,"top soc T80x wr_n", false,-1);
        vcdp->declBit(c+246,"top soc T80x rfsh_n", false,-1);
        vcdp->declBit(c+98,"top soc T80x halt_n", false,-1);
        vcdp->declBit(c+205,"top soc T80x busak_n", false,-1);
        vcdp->declBus(c+180,"top soc T80x A", false,-1, 15,0);
        vcdp->declBus(c+155,"top soc T80x di", false,-1, 7,0);
        vcdp->declBus(c+181,"top soc T80x dout", false,-1, 7,0);
        vcdp->declBit(c+246,"top soc T80x cen", false,-1);
        vcdp->declBit(c+185,"top soc T80x intcycle_n", false,-1);
        vcdp->declBit(c+28,"top soc T80x no_read", false,-1);
        vcdp->declBit(c+29,"top soc T80x write", false,-1);
        vcdp->declBit(c+30,"top soc T80x iorq", false,-1);
        vcdp->declBus(c+206,"top soc T80x di_reg", false,-1, 7,0);
        vcdp->declBus(c+207,"top soc T80x mcycle", false,-1, 6,0);
        vcdp->declBus(c+208,"top soc T80x tstate", false,-1, 6,0);
        vcdp->declBus(c+279,"top soc T80x i_tv80_core Mode", false,-1, 31,0);
        vcdp->declBus(c+280,"top soc T80x i_tv80_core IOWait", false,-1, 31,0);
        vcdp->declBus(c+279,"top soc T80x i_tv80_core Flag_C", false,-1, 31,0);
        vcdp->declBus(c+280,"top soc T80x i_tv80_core Flag_N", false,-1, 31,0);
        vcdp->declBus(c+275,"top soc T80x i_tv80_core Flag_P", false,-1, 31,0);
        vcdp->declBus(c+281,"top soc T80x i_tv80_core Flag_X", false,-1, 31,0);
        vcdp->declBus(c+282,"top soc T80x i_tv80_core Flag_H", false,-1, 31,0);
        vcdp->declBus(c+283,"top soc T80x i_tv80_core Flag_Y", false,-1, 31,0);
        vcdp->declBus(c+284,"top soc T80x i_tv80_core Flag_Z", false,-1, 31,0);
        vcdp->declBus(c+285,"top soc T80x i_tv80_core Flag_S", false,-1, 31,0);
        vcdp->declBit(c+93,"top soc T80x i_tv80_core reset_n", false,-1);
        vcdp->declBit(c+215,"top soc T80x i_tv80_core clk", false,-1);
        vcdp->declBit(c+246,"top soc T80x i_tv80_core cen", false,-1);
        vcdp->declBit(c+255,"top soc T80x i_tv80_core wait_n", false,-1);
        vcdp->declBit(c+246,"top soc T80x i_tv80_core int_n", false,-1);
        vcdp->declBit(c+246,"top soc T80x i_tv80_core nmi_n", false,-1);
        vcdp->declBit(c+246,"top soc T80x i_tv80_core busrq_n", false,-1);
        vcdp->declBit(c+96,"top soc T80x i_tv80_core m1_n", false,-1);
        vcdp->declBit(c+30,"top soc T80x i_tv80_core iorq", false,-1);
        vcdp->declBit(c+28,"top soc T80x i_tv80_core no_read", false,-1);
        vcdp->declBit(c+29,"top soc T80x i_tv80_core write", false,-1);
        vcdp->declBit(c+246,"top soc T80x i_tv80_core rfsh_n", false,-1);
        vcdp->declBit(c+98,"top soc T80x i_tv80_core halt_n", false,-1);
        vcdp->declBit(c+205,"top soc T80x i_tv80_core busak_n", false,-1);
        vcdp->declBus(c+180,"top soc T80x i_tv80_core A", false,-1, 15,0);
        vcdp->declBus(c+155,"top soc T80x i_tv80_core dinst", false,-1, 7,0);
        vcdp->declBus(c+206,"top soc T80x i_tv80_core di", false,-1, 7,0);
        vcdp->declBus(c+181,"top soc T80x i_tv80_core dout", false,-1, 7,0);
        vcdp->declBus(c+207,"top soc T80x i_tv80_core mc", false,-1, 6,0);
        vcdp->declBus(c+208,"top soc T80x i_tv80_core ts", false,-1, 6,0);
        vcdp->declBit(c+185,"top soc T80x i_tv80_core intcycle_n", false,-1);
        vcdp->declBit(c+99,"top soc T80x i_tv80_core IntE", false,-1);
        vcdp->declBit(c+31,"top soc T80x i_tv80_core stop", false,-1);
        vcdp->declBus(c+286,"top soc T80x i_tv80_core aNone", false,-1, 2,0);
        vcdp->declBus(c+287,"top soc T80x i_tv80_core aBC", false,-1, 2,0);
        vcdp->declBus(c+288,"top soc T80x i_tv80_core aDE", false,-1, 2,0);
        vcdp->declBus(c+289,"top soc T80x i_tv80_core aXY", false,-1, 2,0);
        vcdp->declBus(c+290,"top soc T80x i_tv80_core aIOA", false,-1, 2,0);
        vcdp->declBus(c+291,"top soc T80x i_tv80_core aSP", false,-1, 2,0);
        vcdp->declBus(c+292,"top soc T80x i_tv80_core aZI", false,-1, 2,0);
        vcdp->declBus(c+209,"top soc T80x i_tv80_core ACC", false,-1, 7,0);
        vcdp->declBus(c+210,"top soc T80x i_tv80_core F", false,-1, 7,0);
        vcdp->declBus(c+186,"top soc T80x i_tv80_core Ap", false,-1, 7,0);
        vcdp->declBus(c+187,"top soc T80x i_tv80_core Fp", false,-1, 7,0);
        vcdp->declBus(c+188,"top soc T80x i_tv80_core I", false,-1, 7,0);
        vcdp->declBus(c+211,"top soc T80x i_tv80_core SP", false,-1, 15,0);
        vcdp->declBus(c+212,"top soc T80x i_tv80_core PC", false,-1, 15,0);
        vcdp->declBus(c+32,"top soc T80x i_tv80_core RegDIH", false,-1, 7,0);
        vcdp->declBus(c+33,"top soc T80x i_tv80_core RegDIL", false,-1, 7,0);
        vcdp->declBus(c+34,"top soc T80x i_tv80_core RegBusA", false,-1, 15,0);
        vcdp->declBus(c+35,"top soc T80x i_tv80_core RegBusB", false,-1, 15,0);
        vcdp->declBus(c+26,"top soc T80x i_tv80_core RegBusC", false,-1, 15,0);
        vcdp->declBus(c+121,"top soc T80x i_tv80_core RegAddrA_r", false,-1, 2,0);
        vcdp->declBus(c+36,"top soc T80x i_tv80_core RegAddrA", false,-1, 2,0);
        vcdp->declBus(c+122,"top soc T80x i_tv80_core RegAddrB_r", false,-1, 2,0);
        vcdp->declBus(c+37,"top soc T80x i_tv80_core RegAddrB", false,-1, 2,0);
        vcdp->declBus(c+123,"top soc T80x i_tv80_core RegAddrC", false,-1, 2,0);
        vcdp->declBit(c+38,"top soc T80x i_tv80_core RegWEH", false,-1);
        vcdp->declBit(c+39,"top soc T80x i_tv80_core RegWEL", false,-1);
        vcdp->declBit(c+189,"top soc T80x i_tv80_core Alternate", false,-1);
        vcdp->declBus(c+190,"top soc T80x i_tv80_core TmpAddr", false,-1, 15,0);
        vcdp->declBus(c+100,"top soc T80x i_tv80_core IR", false,-1, 7,0);
        vcdp->declBus(c+101,"top soc T80x i_tv80_core ISet", false,-1, 1,0);
        vcdp->declBus(c+124,"top soc T80x i_tv80_core RegBusA_r", false,-1, 15,0);
        vcdp->declBus(c+40,"top soc T80x i_tv80_core ID16", false,-1, 15,0);
        vcdp->declBus(c+41,"top soc T80x i_tv80_core Save_Mux", false,-1, 7,0);
        vcdp->declBus(c+208,"top soc T80x i_tv80_core tstate", false,-1, 6,0);
        vcdp->declBus(c+207,"top soc T80x i_tv80_core mcycle", false,-1, 6,0);
        vcdp->declBit(c+42,"top soc T80x i_tv80_core last_mcycle", false,-1);
        vcdp->declBit(c+43,"top soc T80x i_tv80_core last_tstate", false,-1);
        vcdp->declBit(c+99,"top soc T80x i_tv80_core IntE_FF1", false,-1);
        vcdp->declBit(c+191,"top soc T80x i_tv80_core IntE_FF2", false,-1);
        vcdp->declBit(c+102,"top soc T80x i_tv80_core Halt_FF", false,-1);
        vcdp->declBit(c+103,"top soc T80x i_tv80_core BusReq_s", false,-1);
        vcdp->declBit(c+213,"top soc T80x i_tv80_core BusAck", false,-1);
        vcdp->declBit(c+205,"top soc T80x i_tv80_core ClkEn", false,-1);
        vcdp->declBit(c+104,"top soc T80x i_tv80_core NMI_s", false,-1);
        vcdp->declBit(c+105,"top soc T80x i_tv80_core INT_s", false,-1);
        vcdp->declBus(c+192,"top soc T80x i_tv80_core IStatus", false,-1, 1,0);
        vcdp->declBus(c+206,"top soc T80x i_tv80_core DI_Reg", false,-1, 7,0);
        vcdp->declBit(c+44,"top soc T80x i_tv80_core T_Res", false,-1);
        vcdp->declBus(c+193,"top soc T80x i_tv80_core XY_State", false,-1, 1,0);
        vcdp->declBus(c+106,"top soc T80x i_tv80_core Pre_XY_F_M", false,-1, 2,0);
        vcdp->declBit(c+45,"top soc T80x i_tv80_core NextIs_XY_Fetch", false,-1);
        vcdp->declBit(c+194,"top soc T80x i_tv80_core XY_Ind", false,-1);
        vcdp->declBit(c+107,"top soc T80x i_tv80_core No_BTR", false,-1);
        vcdp->declBit(c+108,"top soc T80x i_tv80_core BTR_r", false,-1);
        vcdp->declBit(c+46,"top soc T80x i_tv80_core Auto_Wait", false,-1);
        vcdp->declBit(c+195,"top soc T80x i_tv80_core Auto_Wait_t1", false,-1);
        vcdp->declBit(c+109,"top soc T80x i_tv80_core Auto_Wait_t2", false,-1);
        vcdp->declBit(c+202,"top soc T80x i_tv80_core IncDecZ", false,-1);
        vcdp->declBus(c+203,"top soc T80x i_tv80_core BusB", false,-1, 7,0);
        vcdp->declBus(c+204,"top soc T80x i_tv80_core BusA", false,-1, 7,0);
        vcdp->declBus(c+47,"top soc T80x i_tv80_core ALU_Q", false,-1, 7,0);
        vcdp->declBus(c+48,"top soc T80x i_tv80_core F_Out", false,-1, 7,0);
        vcdp->declBus(c+196,"top soc T80x i_tv80_core Read_To_Reg_r", false,-1, 4,0);
        vcdp->declBit(c+110,"top soc T80x i_tv80_core Arith16_r", false,-1);
        vcdp->declBit(c+111,"top soc T80x i_tv80_core Z16_r", false,-1);
        vcdp->declBus(c+197,"top soc T80x i_tv80_core ALU_Op_r", false,-1, 3,0);
        vcdp->declBit(c+214,"top soc T80x i_tv80_core Save_ALU_r", false,-1);
        vcdp->declBit(c+198,"top soc T80x i_tv80_core PreserveC_r", false,-1);
        vcdp->declBus(c+112,"top soc T80x i_tv80_core mcycles", false,-1, 2,0);
        vcdp->declBus(c+49,"top soc T80x i_tv80_core mcycles_d", false,-1, 2,0);
        vcdp->declBus(c+50,"top soc T80x i_tv80_core tstates", false,-1, 2,0);
        vcdp->declBit(c+199,"top soc T80x i_tv80_core IntCycle", false,-1);
        vcdp->declBit(c+200,"top soc T80x i_tv80_core NMICycle", false,-1);
        vcdp->declBit(c+51,"top soc T80x i_tv80_core Inc_PC", false,-1);
        vcdp->declBit(c+52,"top soc T80x i_tv80_core Inc_WZ", false,-1);
        vcdp->declBus(c+53,"top soc T80x i_tv80_core IncDec_16", false,-1, 3,0);
        vcdp->declBus(c+1,"top soc T80x i_tv80_core Prefix", false,-1, 1,0);
        vcdp->declBit(c+54,"top soc T80x i_tv80_core Read_To_Acc", false,-1);
        vcdp->declBit(c+55,"top soc T80x i_tv80_core Read_To_Reg", false,-1);
        vcdp->declBus(c+56,"top soc T80x i_tv80_core Set_BusB_To", false,-1, 3,0);
        vcdp->declBus(c+57,"top soc T80x i_tv80_core Set_BusA_To", false,-1, 3,0);
        vcdp->declBus(c+58,"top soc T80x i_tv80_core ALU_Op", false,-1, 3,0);
        vcdp->declBit(c+59,"top soc T80x i_tv80_core Save_ALU", false,-1);
        vcdp->declBit(c+60,"top soc T80x i_tv80_core PreserveC", false,-1);
        vcdp->declBit(c+61,"top soc T80x i_tv80_core Arith16", false,-1);
        vcdp->declBus(c+62,"top soc T80x i_tv80_core Set_Addr_To", false,-1, 2,0);
        vcdp->declBit(c+63,"top soc T80x i_tv80_core Jump", false,-1);
        vcdp->declBit(c+64,"top soc T80x i_tv80_core JumpE", false,-1);
        vcdp->declBit(c+17,"top soc T80x i_tv80_core JumpXY", false,-1);
        vcdp->declBit(c+65,"top soc T80x i_tv80_core Call", false,-1);
        vcdp->declBit(c+66,"top soc T80x i_tv80_core RstP", false,-1);
        vcdp->declBit(c+67,"top soc T80x i_tv80_core LDZ", false,-1);
        vcdp->declBit(c+68,"top soc T80x i_tv80_core LDW", false,-1);
        vcdp->declBit(c+18,"top soc T80x i_tv80_core LDSPHL", false,-1);
        vcdp->declBit(c+30,"top soc T80x i_tv80_core iorq_i", false,-1);
        vcdp->declBus(c+19,"top soc T80x i_tv80_core Special_LD", false,-1, 2,0);
        vcdp->declBit(c+2,"top soc T80x i_tv80_core ExchangeDH", false,-1);
        vcdp->declBit(c+3,"top soc T80x i_tv80_core ExchangeRp", false,-1);
        vcdp->declBit(c+20,"top soc T80x i_tv80_core ExchangeAF", false,-1);
        vcdp->declBit(c+4,"top soc T80x i_tv80_core ExchangeRS", false,-1);
        vcdp->declBit(c+31,"top soc T80x i_tv80_core I_DJNZ", false,-1);
        vcdp->declBit(c+21,"top soc T80x i_tv80_core I_CPL", false,-1);
        vcdp->declBit(c+22,"top soc T80x i_tv80_core I_CCF", false,-1);
        vcdp->declBit(c+23,"top soc T80x i_tv80_core I_SCF", false,-1);
        vcdp->declBit(c+69,"top soc T80x i_tv80_core I_RETN", false,-1);
        vcdp->declBit(c+70,"top soc T80x i_tv80_core I_BT", false,-1);
        vcdp->declBit(c+71,"top soc T80x i_tv80_core I_BC", false,-1);
        vcdp->declBit(c+72,"top soc T80x i_tv80_core I_BTR", false,-1);
        vcdp->declBit(c+73,"top soc T80x i_tv80_core I_RLD", false,-1);
        vcdp->declBit(c+74,"top soc T80x i_tv80_core I_RRD", false,-1);
        vcdp->declBit(c+75,"top soc T80x i_tv80_core I_INRC", false,-1);
        vcdp->declBit(c+5,"top soc T80x i_tv80_core SetDI", false,-1);
        vcdp->declBit(c+6,"top soc T80x i_tv80_core SetEI", false,-1);
        vcdp->declBus(c+24,"top soc T80x i_tv80_core IMode", false,-1, 1,0);
        vcdp->declBit(c+7,"top soc T80x i_tv80_core Halt", false,-1);
        vcdp->declBus(c+76,"top soc T80x i_tv80_core PC16", false,-1, 15,0);
        vcdp->declBus(c+77,"top soc T80x i_tv80_core PC16_B", false,-1, 15,0);
        vcdp->declBus(c+78,"top soc T80x i_tv80_core SP16", false,-1, 15,0);
        vcdp->declBus(c+79,"top soc T80x i_tv80_core SP16_A", false,-1, 15,0);
        vcdp->declBus(c+80,"top soc T80x i_tv80_core SP16_B", false,-1, 15,0);
        vcdp->declBus(c+81,"top soc T80x i_tv80_core ID16_B", false,-1, 15,0);
        vcdp->declBit(c+113,"top soc T80x i_tv80_core Oldnmi_n", false,-1);
        vcdp->declBus(c+279,"top soc T80x i_tv80_core i_mcode Mode", false,-1, 31,0);
        vcdp->declBus(c+279,"top soc T80x i_tv80_core i_mcode Flag_C", false,-1, 31,0);
        vcdp->declBus(c+280,"top soc T80x i_tv80_core i_mcode Flag_N", false,-1, 31,0);
        vcdp->declBus(c+275,"top soc T80x i_tv80_core i_mcode Flag_P", false,-1, 31,0);
        vcdp->declBus(c+281,"top soc T80x i_tv80_core i_mcode Flag_X", false,-1, 31,0);
        vcdp->declBus(c+282,"top soc T80x i_tv80_core i_mcode Flag_H", false,-1, 31,0);
        vcdp->declBus(c+283,"top soc T80x i_tv80_core i_mcode Flag_Y", false,-1, 31,0);
        vcdp->declBus(c+284,"top soc T80x i_tv80_core i_mcode Flag_Z", false,-1, 31,0);
        vcdp->declBus(c+285,"top soc T80x i_tv80_core i_mcode Flag_S", false,-1, 31,0);
        vcdp->declBus(c+100,"top soc T80x i_tv80_core i_mcode IR", false,-1, 7,0);
        vcdp->declBus(c+101,"top soc T80x i_tv80_core i_mcode ISet", false,-1, 1,0);
        vcdp->declBus(c+207,"top soc T80x i_tv80_core i_mcode MCycle", false,-1, 6,0);
        vcdp->declBus(c+210,"top soc T80x i_tv80_core i_mcode F", false,-1, 7,0);
        vcdp->declBit(c+200,"top soc T80x i_tv80_core i_mcode NMICycle", false,-1);
        vcdp->declBit(c+199,"top soc T80x i_tv80_core i_mcode IntCycle", false,-1);
        vcdp->declBus(c+49,"top soc T80x i_tv80_core i_mcode MCycles", false,-1, 2,0);
        vcdp->declBus(c+50,"top soc T80x i_tv80_core i_mcode TStates", false,-1, 2,0);
        vcdp->declBus(c+1,"top soc T80x i_tv80_core i_mcode Prefix", false,-1, 1,0);
        vcdp->declBit(c+51,"top soc T80x i_tv80_core i_mcode Inc_PC", false,-1);
        vcdp->declBit(c+52,"top soc T80x i_tv80_core i_mcode Inc_WZ", false,-1);
        vcdp->declBus(c+53,"top soc T80x i_tv80_core i_mcode IncDec_16", false,-1, 3,0);
        vcdp->declBit(c+55,"top soc T80x i_tv80_core i_mcode Read_To_Reg", false,-1);
        vcdp->declBit(c+54,"top soc T80x i_tv80_core i_mcode Read_To_Acc", false,-1);
        vcdp->declBus(c+57,"top soc T80x i_tv80_core i_mcode Set_BusA_To", false,-1, 3,0);
        vcdp->declBus(c+56,"top soc T80x i_tv80_core i_mcode Set_BusB_To", false,-1, 3,0);
        vcdp->declBus(c+58,"top soc T80x i_tv80_core i_mcode ALU_Op", false,-1, 3,0);
        vcdp->declBit(c+59,"top soc T80x i_tv80_core i_mcode Save_ALU", false,-1);
        vcdp->declBit(c+60,"top soc T80x i_tv80_core i_mcode PreserveC", false,-1);
        vcdp->declBit(c+61,"top soc T80x i_tv80_core i_mcode Arith16", false,-1);
        vcdp->declBus(c+62,"top soc T80x i_tv80_core i_mcode Set_Addr_To", false,-1, 2,0);
        vcdp->declBit(c+30,"top soc T80x i_tv80_core i_mcode IORQ", false,-1);
        vcdp->declBit(c+63,"top soc T80x i_tv80_core i_mcode Jump", false,-1);
        vcdp->declBit(c+64,"top soc T80x i_tv80_core i_mcode JumpE", false,-1);
        vcdp->declBit(c+17,"top soc T80x i_tv80_core i_mcode JumpXY", false,-1);
        vcdp->declBit(c+65,"top soc T80x i_tv80_core i_mcode Call", false,-1);
        vcdp->declBit(c+66,"top soc T80x i_tv80_core i_mcode RstP", false,-1);
        vcdp->declBit(c+67,"top soc T80x i_tv80_core i_mcode LDZ", false,-1);
        vcdp->declBit(c+68,"top soc T80x i_tv80_core i_mcode LDW", false,-1);
        vcdp->declBit(c+18,"top soc T80x i_tv80_core i_mcode LDSPHL", false,-1);
        vcdp->declBus(c+19,"top soc T80x i_tv80_core i_mcode Special_LD", false,-1, 2,0);
        vcdp->declBit(c+2,"top soc T80x i_tv80_core i_mcode ExchangeDH", false,-1);
        vcdp->declBit(c+3,"top soc T80x i_tv80_core i_mcode ExchangeRp", false,-1);
        vcdp->declBit(c+20,"top soc T80x i_tv80_core i_mcode ExchangeAF", false,-1);
        vcdp->declBit(c+4,"top soc T80x i_tv80_core i_mcode ExchangeRS", false,-1);
        vcdp->declBit(c+31,"top soc T80x i_tv80_core i_mcode I_DJNZ", false,-1);
        vcdp->declBit(c+21,"top soc T80x i_tv80_core i_mcode I_CPL", false,-1);
        vcdp->declBit(c+22,"top soc T80x i_tv80_core i_mcode I_CCF", false,-1);
        vcdp->declBit(c+23,"top soc T80x i_tv80_core i_mcode I_SCF", false,-1);
        vcdp->declBit(c+69,"top soc T80x i_tv80_core i_mcode I_RETN", false,-1);
        vcdp->declBit(c+70,"top soc T80x i_tv80_core i_mcode I_BT", false,-1);
        vcdp->declBit(c+71,"top soc T80x i_tv80_core i_mcode I_BC", false,-1);
        vcdp->declBit(c+72,"top soc T80x i_tv80_core i_mcode I_BTR", false,-1);
        vcdp->declBit(c+73,"top soc T80x i_tv80_core i_mcode I_RLD", false,-1);
        vcdp->declBit(c+74,"top soc T80x i_tv80_core i_mcode I_RRD", false,-1);
        vcdp->declBit(c+75,"top soc T80x i_tv80_core i_mcode I_INRC", false,-1);
        vcdp->declBit(c+5,"top soc T80x i_tv80_core i_mcode SetDI", false,-1);
        vcdp->declBit(c+6,"top soc T80x i_tv80_core i_mcode SetEI", false,-1);
        vcdp->declBus(c+24,"top soc T80x i_tv80_core i_mcode IMode", false,-1, 1,0);
        vcdp->declBit(c+7,"top soc T80x i_tv80_core i_mcode Halt", false,-1);
        vcdp->declBit(c+28,"top soc T80x i_tv80_core i_mcode NoRead", false,-1);
        vcdp->declBit(c+29,"top soc T80x i_tv80_core i_mcode Write", false,-1);
        vcdp->declBus(c+286,"top soc T80x i_tv80_core i_mcode aNone", false,-1, 2,0);
        vcdp->declBus(c+287,"top soc T80x i_tv80_core i_mcode aBC", false,-1, 2,0);
        vcdp->declBus(c+288,"top soc T80x i_tv80_core i_mcode aDE", false,-1, 2,0);
        vcdp->declBus(c+289,"top soc T80x i_tv80_core i_mcode aXY", false,-1, 2,0);
        vcdp->declBus(c+290,"top soc T80x i_tv80_core i_mcode aIOA", false,-1, 2,0);
        vcdp->declBus(c+291,"top soc T80x i_tv80_core i_mcode aSP", false,-1, 2,0);
        vcdp->declBus(c+292,"top soc T80x i_tv80_core i_mcode aZI", false,-1, 2,0);
        vcdp->declBus(c+82,"top soc T80x i_tv80_core i_mcode DDD", false,-1, 2,0);
        vcdp->declBus(c+83,"top soc T80x i_tv80_core i_mcode SSS", false,-1, 2,0);
        vcdp->declBus(c+84,"top soc T80x i_tv80_core i_mcode DPAIR", false,-1, 1,0);
        vcdp->declBus(c+279,"top soc T80x i_tv80_core i_alu Mode", false,-1, 31,0);
        vcdp->declBus(c+279,"top soc T80x i_tv80_core i_alu Flag_C", false,-1, 31,0);
        vcdp->declBus(c+280,"top soc T80x i_tv80_core i_alu Flag_N", false,-1, 31,0);
        vcdp->declBus(c+275,"top soc T80x i_tv80_core i_alu Flag_P", false,-1, 31,0);
        vcdp->declBus(c+281,"top soc T80x i_tv80_core i_alu Flag_X", false,-1, 31,0);
        vcdp->declBus(c+282,"top soc T80x i_tv80_core i_alu Flag_H", false,-1, 31,0);
        vcdp->declBus(c+283,"top soc T80x i_tv80_core i_alu Flag_Y", false,-1, 31,0);
        vcdp->declBus(c+284,"top soc T80x i_tv80_core i_alu Flag_Z", false,-1, 31,0);
        vcdp->declBus(c+285,"top soc T80x i_tv80_core i_alu Flag_S", false,-1, 31,0);
        vcdp->declBit(c+110,"top soc T80x i_tv80_core i_alu Arith16", false,-1);
        vcdp->declBit(c+111,"top soc T80x i_tv80_core i_alu Z16", false,-1);
        vcdp->declBus(c+197,"top soc T80x i_tv80_core i_alu ALU_Op", false,-1, 3,0);
        vcdp->declBus(c+114,"top soc T80x i_tv80_core i_alu IR", false,-1, 5,0);
        vcdp->declBus(c+101,"top soc T80x i_tv80_core i_alu ISet", false,-1, 1,0);
        vcdp->declBus(c+204,"top soc T80x i_tv80_core i_alu BusA", false,-1, 7,0);
        vcdp->declBus(c+203,"top soc T80x i_tv80_core i_alu BusB", false,-1, 7,0);
        vcdp->declBus(c+210,"top soc T80x i_tv80_core i_alu F_In", false,-1, 7,0);
        vcdp->declBus(c+47,"top soc T80x i_tv80_core i_alu Q", false,-1, 7,0);
        vcdp->declBus(c+48,"top soc T80x i_tv80_core i_alu F_Out", false,-1, 7,0);
        vcdp->declBit(c+85,"top soc T80x i_tv80_core i_alu UseCarry", false,-1);
        vcdp->declBit(c+86,"top soc T80x i_tv80_core i_alu Carry7_v", false,-1);
        vcdp->declBit(c+87,"top soc T80x i_tv80_core i_alu OverFlow_v", false,-1);
        vcdp->declBit(c+88,"top soc T80x i_tv80_core i_alu HalfCarry_v", false,-1);
        vcdp->declBit(c+89,"top soc T80x i_tv80_core i_alu Carry_v", false,-1);
        vcdp->declBus(c+90,"top soc T80x i_tv80_core i_alu Q_v", false,-1, 7,0);
        vcdp->declBus(c+8,"top soc T80x i_tv80_core i_alu BitMask", false,-1, 7,0);
        vcdp->declBus(c+91,"top soc T80x i_tv80_core i_alu Q_t", false,-1, 7,0);
        vcdp->declBus(c+92,"top soc T80x i_tv80_core i_alu DAA_Q", false,-1, 8,0);
        vcdp->declBus(c+123,"top soc T80x i_tv80_core i_reg AddrC", false,-1, 2,0);
        vcdp->declBus(c+11,"top soc T80x i_tv80_core i_reg DOBH", false,-1, 7,0);
        vcdp->declBus(c+36,"top soc T80x i_tv80_core i_reg AddrA", false,-1, 2,0);
        vcdp->declBus(c+37,"top soc T80x i_tv80_core i_reg AddrB", false,-1, 2,0);
        vcdp->declBus(c+32,"top soc T80x i_tv80_core i_reg DIH", false,-1, 7,0);
        vcdp->declBus(c+12,"top soc T80x i_tv80_core i_reg DOAL", false,-1, 7,0);
        vcdp->declBus(c+125,"top soc T80x i_tv80_core i_reg DOCL", false,-1, 7,0);
        vcdp->declBus(c+33,"top soc T80x i_tv80_core i_reg DIL", false,-1, 7,0);
        vcdp->declBus(c+13,"top soc T80x i_tv80_core i_reg DOBL", false,-1, 7,0);
        vcdp->declBus(c+126,"top soc T80x i_tv80_core i_reg DOCH", false,-1, 7,0);
        vcdp->declBus(c+14,"top soc T80x i_tv80_core i_reg DOAH", false,-1, 7,0);
        vcdp->declBit(c+215,"top soc T80x i_tv80_core i_reg clk", false,-1);
        vcdp->declBit(c+205,"top soc T80x i_tv80_core i_reg CEN", false,-1);
        vcdp->declBit(c+38,"top soc T80x i_tv80_core i_reg WEH", false,-1);
        vcdp->declBit(c+39,"top soc T80x i_tv80_core i_reg WEL", false,-1);
        {int i; for (i=0; i<8; i++) {
                vcdp->declBus(c+127+i*1,"top soc T80x i_tv80_core i_reg RegsH", true,(i+0), 7,0);}}
        {int i; for (i=0; i<8; i++) {
                vcdp->declBus(c+135+i*1,"top soc T80x i_tv80_core i_reg RegsL", true,(i+0), 7,0);}}
        vcdp->declBus(c+143,"top soc T80x i_tv80_core i_reg B", false,-1, 7,0);
        vcdp->declBus(c+144,"top soc T80x i_tv80_core i_reg C", false,-1, 7,0);
        vcdp->declBus(c+145,"top soc T80x i_tv80_core i_reg D", false,-1, 7,0);
        vcdp->declBus(c+146,"top soc T80x i_tv80_core i_reg E", false,-1, 7,0);
        vcdp->declBus(c+147,"top soc T80x i_tv80_core i_reg H", false,-1, 7,0);
        vcdp->declBus(c+148,"top soc T80x i_tv80_core i_reg L", false,-1, 7,0);
        vcdp->declBus(c+149,"top soc T80x i_tv80_core i_reg IX", false,-1, 15,0);
        vcdp->declBus(c+150,"top soc T80x i_tv80_core i_reg IY", false,-1, 15,0);
        vcdp->declBus(c+251,"top soc rom width_a", false,-1, 31,0);
        vcdp->declBus(c+274,"top soc rom widthad_a", false,-1, 31,0);
        vcdp->declQuad(c+293,"top soc rom init_file", false,-1, 55,0);
        vcdp->declBit(c+215,"top soc rom clock_a", false,-1);
        vcdp->declBit(c+255,"top soc rom wren_a", false,-1);
        vcdp->declBus(c+201,"top soc rom address_a", false,-1, 11,0);
        vcdp->declBus(c+295,"top soc rom data_a", false,-1, 7,0);
        vcdp->declBus(c+116,"top soc rom q_a", false,-1, 7,0);
        vcdp->declBit(c+215,"top soc rom clock_b", false,-1);
        vcdp->declBit(c+255,"top soc rom wren_b", false,-1);
        vcdp->declBus(c+296,"top soc rom address_b", false,-1, 11,0);
        vcdp->declBus(c+297,"top soc rom data_b", false,-1, 7,0);
        vcdp->declBus(c+151,"top soc rom q_b", false,-1, 7,0);
        vcdp->declBit(c+298,"top soc rom byteena_a", false,-1);
        vcdp->declBit(c+299,"top soc rom byteena_b", false,-1);
        vcdp->declBus(c+251,"top soc ram width_a", false,-1, 31,0);
        vcdp->declBus(c+274,"top soc ram widthad_a", false,-1, 31,0);
        vcdp->declBus(c+300,"top soc ram init_file", false,-1, 0,0);
        vcdp->declBit(c+215,"top soc ram clock_a", false,-1);
        vcdp->declBit(c+25,"top soc ram wren_a", false,-1);
        vcdp->declBus(c+201,"top soc ram address_a", false,-1, 11,0);
        vcdp->declBus(c+181,"top soc ram data_a", false,-1, 7,0);
        vcdp->declBus(c+115,"top soc ram q_a", false,-1, 7,0);
        vcdp->declBit(c+215,"top soc ram clock_b", false,-1);
        vcdp->declBit(c+255,"top soc ram wren_b", false,-1);
        vcdp->declBus(c+201,"top soc ram address_b", false,-1, 11,0);
        vcdp->declBus(c+301,"top soc ram data_b", false,-1, 7,0);
        vcdp->declBus(c+152,"top soc ram q_b", false,-1, 7,0);
        vcdp->declBit(c+302,"top soc ram byteena_a", false,-1);
        vcdp->declBit(c+303,"top soc ram byteena_b", false,-1);
    }
}

void Vtop::traceFullThis__1(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* oldp = vcdp->oldp(code+1);
    if (false && vcdp && oldp) {}  // Prevent unused
    // Variables
    WData/*127:0*/ __Vtemp11[4];
    // Body
    {
        vcdp->fullCData(oldp+0,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Prefix),2);
        vcdp->fullBit(oldp+1,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ExchangeDH));
        vcdp->fullBit(oldp+2,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ExchangeRp));
        vcdp->fullBit(oldp+3,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ExchangeRS));
        vcdp->fullBit(oldp+4,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SetDI));
        vcdp->fullBit(oldp+5,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SetEI));
        vcdp->fullBit(oldp+6,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Halt));
        vcdp->fullCData(oldp+7,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__BitMask),8);
        vcdp->fullCData(oldp+8,(vlTOPp->top__DOT__soc__DOT__cpu_reset_cnt),8);
        vcdp->fullBit(oldp+9,((0xffU != (IData)(vlTOPp->top__DOT__soc__DOT__cpu_reset_cnt))));
        vcdp->fullCData(oldp+10,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH
                                 [vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrB]),8);
        vcdp->fullCData(oldp+11,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL
                                 [vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrA]),8);
        vcdp->fullCData(oldp+12,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL
                                 [vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrB]),8);
        vcdp->fullCData(oldp+13,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH
                                 [vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrA]),8);
        vcdp->fullIData(oldp+14,(vlTOPp->top__DOT__soc__DOT__pos),24);
        vcdp->fullIData(oldp+15,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__inc_pos),24);
        vcdp->fullBit(oldp+16,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__JumpXY));
        vcdp->fullBit(oldp+17,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__LDSPHL));
        vcdp->fullCData(oldp+18,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Special_LD),3);
        vcdp->fullBit(oldp+19,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ExchangeAF));
        vcdp->fullBit(oldp+20,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_CPL));
        vcdp->fullBit(oldp+21,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_CCF));
        vcdp->fullBit(oldp+22,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_SCF));
        vcdp->fullCData(oldp+23,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IMode),2);
        vcdp->fullBit(oldp+24,(vlTOPp->top__DOT__soc__DOT____Vcellinp__ram__wren_a));
        vcdp->fullSData(oldp+25,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegBusC),16);
        vcdp->fullBit(oldp+26,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__charmap_a));
        vcdp->fullBit(oldp+27,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__no_read));
        vcdp->fullBit(oldp+28,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__write));
        vcdp->fullBit(oldp+29,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__iorq_i));
        vcdp->fullBit(oldp+30,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_DJNZ));
        vcdp->fullCData(oldp+31,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegDIH),8);
        vcdp->fullCData(oldp+32,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegDIL),8);
        vcdp->fullSData(oldp+33,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegBusA),16);
        vcdp->fullSData(oldp+34,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegBusB),16);
        vcdp->fullCData(oldp+35,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrA),3);
        vcdp->fullCData(oldp+36,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrB),3);
        vcdp->fullBit(oldp+37,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegWEH));
        vcdp->fullBit(oldp+38,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegWEL));
        vcdp->fullSData(oldp+39,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ID16),16);
        vcdp->fullCData(oldp+40,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Save_Mux),8);
        vcdp->fullBit(oldp+41,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__last_mcycle));
        vcdp->fullBit(oldp+42,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__last_tstate));
        vcdp->fullBit(oldp+43,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__last_tstate));
        vcdp->fullBit(oldp+44,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__NextIs_XY_Fetch));
        vcdp->fullBit(oldp+45,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Auto_Wait));
        vcdp->fullCData(oldp+46,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ALU_Q),8);
        vcdp->fullCData(oldp+47,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__F_Out),8);
        vcdp->fullCData(oldp+48,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__mcycles_d),3);
        vcdp->fullCData(oldp+49,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__tstates),3);
        vcdp->fullBit(oldp+50,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Inc_PC));
        vcdp->fullBit(oldp+51,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Inc_WZ));
        vcdp->fullCData(oldp+52,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IncDec_16),4);
        vcdp->fullBit(oldp+53,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Read_To_Acc));
        vcdp->fullBit(oldp+54,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Read_To_Reg));
        vcdp->fullCData(oldp+55,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Set_BusB_To),4);
        vcdp->fullCData(oldp+56,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Set_BusA_To),4);
        vcdp->fullCData(oldp+57,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ALU_Op),4);
        vcdp->fullBit(oldp+58,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Save_ALU));
        vcdp->fullBit(oldp+59,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__PreserveC));
        vcdp->fullBit(oldp+60,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Arith16));
        vcdp->fullCData(oldp+61,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Set_Addr_To),3);
        vcdp->fullBit(oldp+62,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Jump));
        vcdp->fullBit(oldp+63,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__JumpE));
        vcdp->fullBit(oldp+64,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Call));
        vcdp->fullBit(oldp+65,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RstP));
        vcdp->fullBit(oldp+66,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__LDZ));
        vcdp->fullBit(oldp+67,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__LDW));
        vcdp->fullBit(oldp+68,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_RETN));
        vcdp->fullBit(oldp+69,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_BT));
        vcdp->fullBit(oldp+70,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_BC));
        vcdp->fullBit(oldp+71,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_BTR));
        vcdp->fullBit(oldp+72,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_RLD));
        vcdp->fullBit(oldp+73,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_RRD));
        vcdp->fullBit(oldp+74,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I_INRC));
        vcdp->fullSData(oldp+75,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__PC16),16);
        vcdp->fullSData(oldp+76,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__PC16_B),16);
        vcdp->fullSData(oldp+77,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SP16),16);
        vcdp->fullSData(oldp+78,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SP16_A),16);
        vcdp->fullSData(oldp+79,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SP16_B),16);
        vcdp->fullSData(oldp+80,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ID16_B),16);
        vcdp->fullCData(oldp+81,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__DDD),3);
        vcdp->fullCData(oldp+82,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__SSS),3);
        vcdp->fullCData(oldp+83,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_mcode__DOT__DPAIR),2);
        vcdp->fullBit(oldp+84,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__UseCarry));
        vcdp->fullBit(oldp+85,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__Carry7_v));
        vcdp->fullBit(oldp+86,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__OverFlow_v));
        vcdp->fullBit(oldp+87,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__HalfCarry_v));
        vcdp->fullBit(oldp+88,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__Carry_v));
        vcdp->fullCData(oldp+89,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__Q_v),8);
        vcdp->fullCData(oldp+90,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__Q_t),8);
        vcdp->fullSData(oldp+91,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_alu__DOT__DAA_Q),9);
        vcdp->fullBit(oldp+92,(vlTOPp->top__DOT__soc__DOT____Vcellinp__T80x__reset_n));
        vcdp->fullBit(oldp+93,(vlTOPp->top__DOT__soc__DOT__cpu_rd_n));
        vcdp->fullBit(oldp+94,(vlTOPp->top__DOT__soc__DOT__cpu_mreq_n));
        vcdp->fullBit(oldp+95,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__m1_n));
        vcdp->fullBit(oldp+96,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__iorq_n));
        vcdp->fullBit(oldp+97,((1U & (~ (IData)(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Halt_FF)))));
        vcdp->fullBit(oldp+98,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IntE_FF1));
        vcdp->fullCData(oldp+99,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IR),8);
        vcdp->fullCData(oldp+100,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ISet),2);
        vcdp->fullBit(oldp+101,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Halt_FF));
        vcdp->fullBit(oldp+102,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BusReq_s));
        vcdp->fullBit(oldp+103,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__NMI_s));
        vcdp->fullBit(oldp+104,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__INT_s));
        vcdp->fullCData(oldp+105,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Pre_XY_F_M),3);
        vcdp->fullBit(oldp+106,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__No_BTR));
        vcdp->fullBit(oldp+107,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BTR_r));
        vcdp->fullBit(oldp+108,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Auto_Wait_t2));
        vcdp->fullBit(oldp+109,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Arith16_r));
        vcdp->fullBit(oldp+110,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Z16_r));
        vcdp->fullCData(oldp+111,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__mcycles),3);
        vcdp->fullBit(oldp+112,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Oldnmi_n));
        vcdp->fullCData(oldp+113,((0x3fU & (IData)(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IR))),6);
        vcdp->fullCData(oldp+114,(vlTOPp->top__DOT__soc__DOT__ram_data_out),8);
        vcdp->fullCData(oldp+115,(vlTOPp->top__DOT__soc__DOT__rom_data_out),8);
        vcdp->fullCData(oldp+116,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chrom_data_out),8);
        vcdp->fullCData(oldp+117,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chmap_data_out),8);
        vcdp->fullCData(oldp+118,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chrom__DOT__q_b),8);
        vcdp->fullCData(oldp+119,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chram__DOT__q_a),8);
        vcdp->fullCData(oldp+120,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrA_r),3);
        vcdp->fullCData(oldp+121,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrB_r),3);
        vcdp->fullCData(oldp+122,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrC),3);
        vcdp->fullSData(oldp+123,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegBusA_r),16);
        vcdp->fullCData(oldp+124,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL
                                  [vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrC]),8);
        vcdp->fullCData(oldp+125,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH
                                  [vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__RegAddrC]),8);
        vcdp->fullCData(oldp+126,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[0]),8);
        vcdp->fullCData(oldp+127,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[1]),8);
        vcdp->fullCData(oldp+128,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[2]),8);
        vcdp->fullCData(oldp+129,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[3]),8);
        vcdp->fullCData(oldp+130,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[4]),8);
        vcdp->fullCData(oldp+131,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[5]),8);
        vcdp->fullCData(oldp+132,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[6]),8);
        vcdp->fullCData(oldp+133,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH[7]),8);
        vcdp->fullCData(oldp+134,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[0]),8);
        vcdp->fullCData(oldp+135,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[1]),8);
        vcdp->fullCData(oldp+136,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[2]),8);
        vcdp->fullCData(oldp+137,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[3]),8);
        vcdp->fullCData(oldp+138,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[4]),8);
        vcdp->fullCData(oldp+139,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[5]),8);
        vcdp->fullCData(oldp+140,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[6]),8);
        vcdp->fullCData(oldp+141,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL[7]),8);
        vcdp->fullCData(oldp+142,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH
                                  [0U]),8);
        vcdp->fullCData(oldp+143,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL
                                  [0U]),8);
        vcdp->fullCData(oldp+144,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH
                                  [1U]),8);
        vcdp->fullCData(oldp+145,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL
                                  [1U]),8);
        vcdp->fullCData(oldp+146,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH
                                  [2U]),8);
        vcdp->fullCData(oldp+147,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL
                                  [2U]),8);
        vcdp->fullSData(oldp+148,(((vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH
                                    [3U] << 8U) | vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL
                                   [3U])),16);
        vcdp->fullSData(oldp+149,(((vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsH
                                    [7U] << 8U) | vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__i_reg__DOT__RegsL
                                   [7U])),16);
        vcdp->fullCData(oldp+150,(vlTOPp->top__DOT__soc__DOT__rom__DOT__q_b),8);
        vcdp->fullCData(oldp+151,(vlTOPp->top__DOT__soc__DOT__ram__DOT__q_b),8);
        vcdp->fullSData(oldp+152,((((IData)(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chmap_data_out) 
                                    << 3U) | (7U & (IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__v_cnt)))),12);
        vcdp->fullSData(oldp+153,((((IData)(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chmap_data_out) 
                                    << 3U) | (7U & (IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__v_cnt)))),11);
        vcdp->fullCData(oldp+154,(((0x8000U & (IData)(vlTOPp->top__DOT__soc__DOT__cpu_addr))
                                    ? (IData)(vlTOPp->top__DOT__soc__DOT__ram_data_out)
                                    : (IData)(vlTOPp->top__DOT__soc__DOT__rom_data_out))),8);
        vcdp->fullBit(oldp+155,(vlTOPp->top__DOT__soc__DOT__vga__DOT__de));
        vcdp->fullCData(oldp+156,(((0xe0U & (IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel)) 
                                   | ((0x1cU & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel) 
                                                >> 3U)) 
                                      | (3U & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel) 
                                               >> 6U))))),8);
        vcdp->fullCData(oldp+157,(((0xe0U & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel) 
                                             << 3U)) 
                                   | ((0x1cU & (IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel)) 
                                      | (3U & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel) 
                                               >> 3U))))),8);
        vcdp->fullCData(oldp+158,(((0xc0U & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel) 
                                             << 6U)) 
                                   | ((0x30U & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel) 
                                                << 4U)) 
                                      | ((0xcU & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel) 
                                                  << 2U)) 
                                         | (3U & (IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel)))))),8);
        vcdp->fullSData(oldp+159,(vlTOPp->top__DOT__soc__DOT__vga__DOT__h_cnt),10);
        vcdp->fullSData(oldp+160,(vlTOPp->top__DOT__soc__DOT__vga__DOT__v_cnt),10);
        vcdp->fullSData(oldp+161,(vlTOPp->top__DOT__soc__DOT__div),13);
        vcdp->fullSData(oldp+162,(((0xfc0U & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__v_cnt) 
                                              << 3U)) 
                                   | (0x3fU & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__h_cnt) 
                                               >> 3U)))),12);
        vcdp->fullIData(oldp+163,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__pos_r),24);
        vcdp->fullSData(oldp+164,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__wr_addr),12);
        vcdp->fullCData(oldp+165,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__wr_data),8);
        vcdp->fullBit(oldp+166,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__wheel_state));
        vcdp->fullCData(oldp+167,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__state),2);
        vcdp->fullCData(oldp+168,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__blocks),5);
        vcdp->fullCData(oldp+169,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__cur_block),5);
        vcdp->fullBit(oldp+170,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__wr_ena));
        vcdp->fullCData(oldp+171,((7U & ((IData)(7U) 
                                         - (IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__h_cnt)))),3);
        vcdp->fullCData(oldp+172,((7U & (IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__v_cnt))),3);
        vcdp->fullCData(oldp+173,((0x3fU & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__h_cnt) 
                                            >> 3U))),6);
        vcdp->fullCData(oldp+174,((0x3fU & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__v_cnt) 
                                            >> 3U))),6);
        vcdp->fullSData(oldp+175,((0x7ffU & (IData)(vlTOPp->top__DOT__soc__DOT__overlay__DOT__wr_addr))),11);
        vcdp->fullSData(oldp+176,(((0x7c0U & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__v_cnt) 
                                              << 3U)) 
                                   | (0x3fU & ((IData)(vlTOPp->top__DOT__soc__DOT__vga__DOT__h_cnt) 
                                               >> 3U)))),11);
        vcdp->fullSData(oldp+177,(vlTOPp->top__DOT__soc__DOT__vga__DOT__video_counter),14);
        vcdp->fullCData(oldp+178,(vlTOPp->top__DOT__soc__DOT__vga__DOT__pixel),8);
        vcdp->fullSData(oldp+179,(vlTOPp->top__DOT__soc__DOT__cpu_addr),16);
        vcdp->fullCData(oldp+180,(vlTOPp->top__DOT__soc__DOT__cpu_dout),8);
        vcdp->fullBit(oldp+181,(vlTOPp->top__DOT__soc__DOT__cpu_wr_n));
        vcdp->fullBit(oldp+182,((1U & ((~ (IData)(vlTOPp->top__DOT__soc__DOT__cpu_wr_n)) 
                                       & (~ ((IData)(vlTOPp->top__DOT__soc__DOT__cpu_addr) 
                                             >> 0xfU))))));
        vcdp->fullSData(oldp+183,((0x3fffU & (IData)(vlTOPp->top__DOT__soc__DOT__cpu_addr))),14);
        vcdp->fullBit(oldp+184,((1U & (~ (IData)(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IntCycle)))));
        vcdp->fullCData(oldp+185,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Ap),8);
        vcdp->fullCData(oldp+186,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Fp),8);
        vcdp->fullCData(oldp+187,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__I),8);
        vcdp->fullBit(oldp+188,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Alternate));
        vcdp->fullSData(oldp+189,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__TmpAddr),16);
        vcdp->fullBit(oldp+190,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IntE_FF2));
        vcdp->fullCData(oldp+191,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IStatus),2);
        vcdp->fullCData(oldp+192,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__XY_State),2);
        vcdp->fullBit(oldp+193,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__XY_Ind));
        vcdp->fullBit(oldp+194,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Auto_Wait_t1));
        vcdp->fullCData(oldp+195,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Read_To_Reg_r),5);
        vcdp->fullCData(oldp+196,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ALU_Op_r),4);
        vcdp->fullBit(oldp+197,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__PreserveC_r));
        vcdp->fullBit(oldp+198,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IntCycle));
        vcdp->fullBit(oldp+199,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__NMICycle));
        vcdp->fullSData(oldp+200,((0xfffU & (IData)(vlTOPp->top__DOT__soc__DOT__cpu_addr))),12);
        vcdp->fullBit(oldp+201,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__IncDecZ));
        vcdp->fullCData(oldp+202,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BusB),8);
        vcdp->fullCData(oldp+203,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BusA),8);
        vcdp->fullBit(oldp+204,((1U & (~ (IData)(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BusAck)))));
        vcdp->fullCData(oldp+205,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__di_reg),8);
        vcdp->fullCData(oldp+206,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__mcycle),7);
        vcdp->fullCData(oldp+207,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__tstate),7);
        vcdp->fullCData(oldp+208,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__ACC),8);
        vcdp->fullCData(oldp+209,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__F),8);
        vcdp->fullSData(oldp+210,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__SP),16);
        vcdp->fullSData(oldp+211,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__PC),16);
        vcdp->fullBit(oldp+212,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__BusAck));
        vcdp->fullBit(oldp+213,(vlTOPp->top__DOT__soc__DOT__T80x__DOT__i_tv80_core__DOT__Save_ALU_r));
        vcdp->fullBit(oldp+214,(vlTOPp->clk_sys));
        vcdp->fullBit(oldp+215,(vlTOPp->clk_vid));
        vcdp->fullBit(oldp+216,(vlTOPp->reset));
        vcdp->fullCData(oldp+217,(vlTOPp->VGA_R),8);
        vcdp->fullCData(oldp+218,(vlTOPp->VGA_G),8);
        vcdp->fullCData(oldp+219,(vlTOPp->VGA_B),8);
        vcdp->fullBit(oldp+220,(vlTOPp->VGA_HS));
        vcdp->fullBit(oldp+221,(vlTOPp->VGA_VS));
        vcdp->fullBit(oldp+222,(vlTOPp->VGA_HB));
        vcdp->fullBit(oldp+223,(vlTOPp->VGA_VB));
        vcdp->fullBit(oldp+224,(vlTOPp->ioctl_download));
        vcdp->fullBit(oldp+225,(vlTOPp->ioctl_wr));
        vcdp->fullIData(oldp+226,(vlTOPp->ioctl_addr),25);
        vcdp->fullCData(oldp+227,(vlTOPp->ioctl_dout),8);
        vcdp->fullCData(oldp+228,(vlTOPp->ioctl_index),8);
        vcdp->fullBit(oldp+229,(vlTOPp->ioctl_wait));
        vcdp->fullBit(oldp+230,(vlTOPp->top__DOT__clk_sys));
        vcdp->fullBit(oldp+231,(vlTOPp->top__DOT__clk_vid));
        vcdp->fullBit(oldp+232,(vlTOPp->top__DOT__reset));
        vcdp->fullCData(oldp+233,(vlTOPp->top__DOT__VGA_R),8);
        vcdp->fullCData(oldp+234,(vlTOPp->top__DOT__VGA_G),8);
        vcdp->fullCData(oldp+235,(vlTOPp->top__DOT__VGA_B),8);
        vcdp->fullBit(oldp+236,(vlTOPp->top__DOT__soc__DOT__vs));
        vcdp->fullBit(oldp+237,(vlTOPp->top__DOT__soc__DOT__hs));
        vcdp->fullBit(oldp+238,(vlTOPp->top__DOT__soc__DOT__ce_pix));
        vcdp->fullBit(oldp+239,(vlTOPp->top__DOT__soc__DOT__hblank));
        vcdp->fullBit(oldp+240,(vlTOPp->top__DOT__soc__DOT__vblank));
        vcdp->fullBit(oldp+241,(vlTOPp->top__DOT__soc__DOT__interlace));
        vcdp->fullIData(oldp+242,(0x3ffU),24);
        vcdp->fullIData(oldp+243,(0xffffffU),24);
        vcdp->fullBit(oldp+244,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__reset));
        vcdp->fullBit(oldp+245,(1U));
        vcdp->fullCData(oldp+246,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__charmap_r),8);
        vcdp->fullCData(oldp+247,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__charmap_g),8);
        vcdp->fullCData(oldp+248,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__charmap_b),8);
        vcdp->fullIData(oldp+249,(0x3fU),24);
        vcdp->fullIData(oldp+250,(8U),32);
        vcdp->fullIData(oldp+251,(0xbU),32);
        vcdp->fullQData(oldp+252,(VL_ULL(0x666f6e742e686578)),64);
        vcdp->fullBit(oldp+254,(0U));
        vcdp->fullCData(oldp+255,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chrom__DOT__data_a),8);
        vcdp->fullBit(oldp+256,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chrom__DOT__wren_b));
        vcdp->fullSData(oldp+257,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chrom__DOT__address_b),11);
        vcdp->fullCData(oldp+258,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chrom__DOT__data_b),8);
        vcdp->fullBit(oldp+259,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chrom__DOT__byteena_a));
        vcdp->fullBit(oldp+260,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chrom__DOT__byteena_b));
        __Vtemp11[0U] = 0x2e686578U;
        __Vtemp11[1U] = 0x6f756e64U;
        __Vtemp11[2U] = 0x636b6772U;
        __Vtemp11[3U] = 0x6261U;
        vcdp->fullWData(oldp+261,(__Vtemp11),112);
        vcdp->fullCData(oldp+265,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chram__DOT__data_b),8);
        vcdp->fullBit(oldp+266,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chram__DOT__byteena_a));
        vcdp->fullBit(oldp+267,(vlTOPp->top__DOT__soc__DOT__overlay__DOT__chram__DOT__byteena_b));
        vcdp->fullIData(oldp+268,(0x280U),32);
        vcdp->fullIData(oldp+269,(0x10U),32);
        vcdp->fullIData(oldp+270,(0x60U),32);
        vcdp->fullIData(oldp+271,(0x30U),32);
        vcdp->fullIData(oldp+272,(0x190U),32);
        vcdp->fullIData(oldp+273,(0xcU),32);
        vcdp->fullIData(oldp+274,(2U),32);
        vcdp->fullIData(oldp+275,(0x23U),32);
        vcdp->fullBit(oldp+276,(vlTOPp->top__DOT__soc__DOT__vga__DOT__hblank));
        vcdp->fullBit(oldp+277,(vlTOPp->top__DOT__soc__DOT__vga__DOT__vblank));
        vcdp->fullIData(oldp+278,(0U),32);
        vcdp->fullIData(oldp+279,(1U),32);
        vcdp->fullIData(oldp+280,(3U),32);
        vcdp->fullIData(oldp+281,(4U),32);
        vcdp->fullIData(oldp+282,(5U),32);
        vcdp->fullIData(oldp+283,(6U),32);
        vcdp->fullIData(oldp+284,(7U),32);
        vcdp->fullCData(oldp+285,(7U),3);
        vcdp->fullCData(oldp+286,(0U),3);
        vcdp->fullCData(oldp+287,(1U),3);
        vcdp->fullCData(oldp+288,(2U),3);
        vcdp->fullCData(oldp+289,(4U),3);
        vcdp->fullCData(oldp+290,(5U),3);
        vcdp->fullCData(oldp+291,(6U),3);
        vcdp->fullQData(oldp+292,(VL_ULL(0x726f6d2e686578)),56);
        vcdp->fullCData(oldp+294,(vlTOPp->top__DOT__soc__DOT__rom__DOT__data_a),8);
        vcdp->fullSData(oldp+295,(vlTOPp->top__DOT__soc__DOT__rom__DOT__address_b),12);
        vcdp->fullCData(oldp+296,(vlTOPp->top__DOT__soc__DOT__rom__DOT__data_b),8);
        vcdp->fullBit(oldp+297,(vlTOPp->top__DOT__soc__DOT__rom__DOT__byteena_a));
        vcdp->fullBit(oldp+298,(vlTOPp->top__DOT__soc__DOT__rom__DOT__byteena_b));
        vcdp->fullBit(oldp+299,(0U));
        vcdp->fullCData(oldp+300,(vlTOPp->top__DOT__soc__DOT__ram__DOT__data_b),8);
        vcdp->fullBit(oldp+301,(vlTOPp->top__DOT__soc__DOT__ram__DOT__byteena_a));
        vcdp->fullBit(oldp+302,(vlTOPp->top__DOT__soc__DOT__ram__DOT__byteena_b));
    }
}
