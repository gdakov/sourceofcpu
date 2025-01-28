// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtest.h for the primary calling header

#ifndef VERILATED_VTEST___024ROOT_H_
#define VERILATED_VTEST___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtest__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtest___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    CData/*7:0*/ test__DOT__clkX;
    CData/*7:0*/ test__DOT__val;
    VlWide<3>/*95:0*/ test__DOT____Vcellinpt__mycellA____pinNumber2;
    VlWide<3>/*95:0*/ test__DOT____Vcelloutt__mycellA__io__out;
    VlWide<3>/*95:0*/ test__DOT____Vcellinpt__mycellB____pinNumber2;
    VlWide<3>/*95:0*/ test__DOT____Vcelloutt__mycellB__io__out;
    CData/*7:0*/ test__DOT__inA__strong__out13;
    CData/*7:0*/ test__DOT__inA__strong__out14;
    CData/*7:0*/ test__DOT__inA__strong__out15;
    CData/*7:0*/ test__DOT__inA__strong__out16;
    CData/*7:0*/ test__DOT__inA__strong__out17;
    CData/*7:0*/ test__DOT__inA__strong__out18;
    CData/*7:0*/ test__DOT__inA__strong__out19;
    CData/*7:0*/ test__DOT__inA__strong__out20;
    CData/*7:0*/ test__DOT__inB__strong__out22;
    CData/*7:0*/ test__DOT__inB__strong__out23;
    CData/*7:0*/ test__DOT__inB__strong__out24;
    CData/*7:0*/ test__DOT__inB__strong__out25;
    CData/*7:0*/ test__DOT__inB__strong__out26;
    CData/*7:0*/ test__DOT__inB__strong__out27;
    CData/*7:0*/ test__DOT__inB__strong__out28;
    CData/*7:0*/ test__DOT__inB__strong__out29;
    CData/*7:0*/ test__DOT__inC__strong__out32;
    CData/*7:0*/ test__DOT__inC__strong__out33;
    CData/*7:0*/ test__DOT__inC__strong__out34;
    CData/*7:0*/ test__DOT__inC__strong__out35;
    CData/*7:0*/ test__DOT__inC__strong__out36;
    CData/*7:0*/ test__DOT__inC__strong__out37;
    CData/*7:0*/ test__DOT__inC__strong__out38;
    CData/*7:0*/ test__DOT__inC__strong__out39;
    CData/*7:0*/ test__DOT__inD__strong__out41;
    CData/*7:0*/ test__DOT__inD__strong__out42;
    CData/*7:0*/ test__DOT__inD__strong__out43;
    CData/*7:0*/ test__DOT__inD__strong__out44;
    CData/*7:0*/ test__DOT__inD__strong__out45;
    CData/*7:0*/ test__DOT__inD__strong__out46;
    CData/*7:0*/ test__DOT__inD__strong__out47;
    CData/*7:0*/ test__DOT__inD__strong__out48;
    VlWide<3>/*95:0*/ test__DOT__mycellA__DOT__iow;
    VlWide<3>/*95:0*/ test__DOT__mycellA__DOT__io__out__strong__out0;
    VlWide<3>/*95:0*/ test__DOT__mycellA__DOT__io__out__strong__out1;
    CData/*7:0*/ test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0;
    VlWide<3>/*95:0*/ test__DOT__mycellB__DOT__iow;
    VlWide<3>/*95:0*/ test__DOT__mycellB__DOT__io__out__strong__out0;
    VlWide<3>/*95:0*/ test__DOT__mycellB__DOT__io__out__strong__out1;
    CData/*7:0*/ test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ test__DOT__mycellA__DOT__b;
    IData/*31:0*/ test__DOT__mycellB__DOT__b;
    IData/*31:0*/ __VactIterCount;
    VlTriggerScheduler __VtrigSched_hc7eb0d31__0;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtest__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtest___024root(Vtest__Syms* symsp, const char* v__name);
    ~Vtest___024root();
    VL_UNCOPYABLE(Vtest___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
