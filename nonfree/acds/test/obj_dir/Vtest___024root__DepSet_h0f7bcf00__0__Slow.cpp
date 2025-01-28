// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtest.h for the primary calling header

#include "Vtest__pch.h"
#include "Vtest___024root.h"

VL_ATTR_COLD void Vtest___024root___eval_static(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___eval_static\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtest___024root___eval_final(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___eval_final\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtest___024root___dump_triggers__stl(Vtest___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtest___024root___eval_phase__stl(Vtest___024root* vlSelf);

VL_ATTR_COLD void Vtest___024root___eval_settle(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___eval_settle\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vtest___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("test.v", 1, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vtest___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtest___024root___dump_triggers__stl(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___dump_triggers__stl\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtest___024root___stl_sequent__TOP__0(Vtest___024root* vlSelf);

VL_ATTR_COLD void Vtest___024root___eval_stl(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___eval_stl\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtest___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vtest___024root___stl_sequent__TOP__0(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___stl_sequent__TOP__0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlWide<3>/*95:0*/ __Vtemp_1;
    VlWide<3>/*95:0*/ __Vtemp_2;
    VlWide<3>/*95:0*/ __Vtemp_4;
    VlWide<3>/*95:0*/ __Vtemp_5;
    // Body
    __Vtemp_1[0U] = 0xc0U;
    __Vtemp_1[1U] = 0U;
    __Vtemp_1[2U] = 0U;
    VL_SHIFTL_WWI(96,96,7, __Vtemp_2, __Vtemp_1, (0x7fU 
                                                  & VL_SHIFTL_III(7,7,32, vlSelfRef.test__DOT__mycellA__DOT__b, 3U)));
    vlSelfRef.test__DOT____Vcelloutt__mycellA__io__out[0U] 
        = ((vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out0[0U] 
            & __Vtemp_2[0U]) | vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[0U]);
    vlSelfRef.test__DOT____Vcelloutt__mycellA__io__out[1U] 
        = ((vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out0[1U] 
            & __Vtemp_2[1U]) | vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[1U]);
    vlSelfRef.test__DOT____Vcelloutt__mycellA__io__out[2U] 
        = ((vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out0[2U] 
            & __Vtemp_2[2U]) | vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[2U]);
    __Vtemp_4[0U] = 0xc0U;
    __Vtemp_4[1U] = 0U;
    __Vtemp_4[2U] = 0U;
    VL_SHIFTL_WWI(96,96,7, __Vtemp_5, __Vtemp_4, (0x7fU 
                                                  & VL_SHIFTL_III(7,7,32, vlSelfRef.test__DOT__mycellB__DOT__b, 3U)));
    vlSelfRef.test__DOT____Vcelloutt__mycellB__io__out[0U] 
        = ((vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out0[0U] 
            & __Vtemp_5[0U]) | vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[0U]);
    vlSelfRef.test__DOT____Vcelloutt__mycellB__io__out[1U] 
        = ((vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out0[1U] 
            & __Vtemp_5[1U]) | vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[1U]);
    vlSelfRef.test__DOT____Vcelloutt__mycellB__io__out[2U] 
        = ((vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out0[2U] 
            & __Vtemp_5[2U]) | vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[2U]);
    vlSelfRef.test__DOT__val = (0xffU & (0xc0U | (vlSelfRef.test__DOT____Vcelloutt__mycellA__io__out[0U] 
                                                  | vlSelfRef.test__DOT____Vcelloutt__mycellB__io__out[0U])));
    vlSelfRef.test__DOT__clkX = (0xffU & ((- (IData)((IData)(vlSelfRef.clk))) 
                                          | (((vlSelfRef.test__DOT____Vcelloutt__mycellA__io__out[0U] 
                                               << 8U) 
                                              | (vlSelfRef.test__DOT____Vcelloutt__mycellA__io__out[0U] 
                                                 >> 0x18U)) 
                                             | ((vlSelfRef.test__DOT____Vcelloutt__mycellB__io__out[0U] 
                                                 << 8U) 
                                                | (vlSelfRef.test__DOT____Vcelloutt__mycellB__io__out[0U] 
                                                   >> 0x18U)))));
    vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2[0U] 
        = (((IData)(vlSelfRef.test__DOT__clkX) << 0x18U) 
           | ((0xff0000U & ((0xffff0000U & vlSelfRef.test__DOT____Vcelloutt__mycellA__io__out[0U]) 
                            | (((IData)(vlSelfRef.test__DOT__inA__strong__out13) 
                                | ((IData)(vlSelfRef.test__DOT__inA__strong__out14) 
                                   | ((IData)(vlSelfRef.test__DOT__inA__strong__out15) 
                                      | ((IData)(vlSelfRef.test__DOT__inA__strong__out16) 
                                         | ((IData)(vlSelfRef.test__DOT__inA__strong__out17) 
                                            | ((IData)(vlSelfRef.test__DOT__inA__strong__out18) 
                                               | ((IData)(vlSelfRef.test__DOT__inA__strong__out19) 
                                                  | (IData)(vlSelfRef.test__DOT__inA__strong__out20)))))))) 
                               << 0x10U))) | ((0xff00U 
                                               & ((0xffffff00U 
                                                   & vlSelfRef.test__DOT____Vcelloutt__mycellA__io__out[0U]) 
                                                  | (((IData)(vlSelfRef.test__DOT__inB__strong__out22) 
                                                      | ((IData)(vlSelfRef.test__DOT__inB__strong__out23) 
                                                         | ((IData)(vlSelfRef.test__DOT__inB__strong__out24) 
                                                            | ((IData)(vlSelfRef.test__DOT__inB__strong__out25) 
                                                               | ((IData)(vlSelfRef.test__DOT__inB__strong__out26) 
                                                                  | ((IData)(vlSelfRef.test__DOT__inB__strong__out27) 
                                                                     | ((IData)(vlSelfRef.test__DOT__inB__strong__out28) 
                                                                        | (IData)(vlSelfRef.test__DOT__inB__strong__out29)))))))) 
                                                     << 8U))) 
                                              | (IData)(vlSelfRef.test__DOT__val))));
    vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2[1U] 
        = (IData)((0x3fULL | (0xffffffffffffff00ULL 
                              & (((QData)((IData)(vlSelfRef.test__DOT____Vcelloutt__mycellA__io__out[2U])) 
                                  << 0x20U) | (0xffffffffffffff00ULL 
                                               & (QData)((IData)(
                                                                 vlSelfRef.test__DOT____Vcelloutt__mycellA__io__out[1U])))))));
    vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2[2U] 
        = (IData)(((0x3fULL | (0xffffffffffffff00ULL 
                               & (((QData)((IData)(
                                                   vlSelfRef.test__DOT____Vcelloutt__mycellA__io__out[2U])) 
                                   << 0x20U) | (0xffffffffffffff00ULL 
                                                & (QData)((IData)(
                                                                  vlSelfRef.test__DOT____Vcelloutt__mycellA__io__out[1U])))))) 
                   >> 0x20U));
    vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2[0U] 
        = (((IData)(vlSelfRef.test__DOT__clkX) << 0x18U) 
           | ((0xff0000U & ((0xffff0000U & vlSelfRef.test__DOT____Vcelloutt__mycellB__io__out[0U]) 
                            | (((IData)(vlSelfRef.test__DOT__inC__strong__out32) 
                                | ((IData)(vlSelfRef.test__DOT__inC__strong__out33) 
                                   | ((IData)(vlSelfRef.test__DOT__inC__strong__out34) 
                                      | ((IData)(vlSelfRef.test__DOT__inC__strong__out35) 
                                         | ((IData)(vlSelfRef.test__DOT__inC__strong__out36) 
                                            | ((IData)(vlSelfRef.test__DOT__inC__strong__out37) 
                                               | ((IData)(vlSelfRef.test__DOT__inC__strong__out38) 
                                                  | (IData)(vlSelfRef.test__DOT__inC__strong__out39)))))))) 
                               << 0x10U))) | ((0xff00U 
                                               & ((0xffffff00U 
                                                   & vlSelfRef.test__DOT____Vcelloutt__mycellB__io__out[0U]) 
                                                  | (((IData)(vlSelfRef.test__DOT__inD__strong__out41) 
                                                      | ((IData)(vlSelfRef.test__DOT__inD__strong__out42) 
                                                         | ((IData)(vlSelfRef.test__DOT__inD__strong__out43) 
                                                            | ((IData)(vlSelfRef.test__DOT__inD__strong__out44) 
                                                               | ((IData)(vlSelfRef.test__DOT__inD__strong__out45) 
                                                                  | ((IData)(vlSelfRef.test__DOT__inD__strong__out46) 
                                                                     | ((IData)(vlSelfRef.test__DOT__inD__strong__out47) 
                                                                        | (IData)(vlSelfRef.test__DOT__inD__strong__out48)))))))) 
                                                     << 8U))) 
                                              | (IData)(vlSelfRef.test__DOT__val))));
    vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2[1U] 
        = (IData)((0x3fULL | (0xffffffffffffff00ULL 
                              & (((QData)((IData)(vlSelfRef.test__DOT____Vcelloutt__mycellB__io__out[2U])) 
                                  << 0x20U) | (0xffffffffffffff00ULL 
                                               & (QData)((IData)(
                                                                 vlSelfRef.test__DOT____Vcelloutt__mycellB__io__out[1U])))))));
    vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2[2U] 
        = (IData)(((0x3fULL | (0xffffffffffffff00ULL 
                               & (((QData)((IData)(
                                                   vlSelfRef.test__DOT____Vcelloutt__mycellB__io__out[2U])) 
                                   << 0x20U) | (0xffffffffffffff00ULL 
                                                & (QData)((IData)(
                                                                  vlSelfRef.test__DOT____Vcelloutt__mycellB__io__out[1U])))))) 
                   >> 0x20U));
}

VL_ATTR_COLD void Vtest___024root___eval_triggers__stl(Vtest___024root* vlSelf);

VL_ATTR_COLD bool Vtest___024root___eval_phase__stl(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___eval_phase__stl\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtest___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vtest___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtest___024root___dump_triggers__ico(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___dump_triggers__ico\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtest___024root___dump_triggers__act(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___dump_triggers__act\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(edge clk)\n");
    }
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtest___024root___dump_triggers__nba(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___dump_triggers__nba\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(edge clk)\n");
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtest___024root___ctor_var_reset(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___ctor_var_reset\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->test__DOT__clkX = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__val = VL_RAND_RESET_I(8);
    VL_RAND_RESET_W(96, vlSelf->test__DOT____Vcellinpt__mycellA____pinNumber2);
    VL_RAND_RESET_W(96, vlSelf->test__DOT____Vcelloutt__mycellA__io__out);
    VL_RAND_RESET_W(96, vlSelf->test__DOT____Vcellinpt__mycellB____pinNumber2);
    VL_RAND_RESET_W(96, vlSelf->test__DOT____Vcelloutt__mycellB__io__out);
    vlSelf->test__DOT__inA__strong__out13 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inA__strong__out14 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inA__strong__out15 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inA__strong__out16 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inA__strong__out17 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inA__strong__out18 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inA__strong__out19 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inA__strong__out20 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inB__strong__out22 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inB__strong__out23 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inB__strong__out24 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inB__strong__out25 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inB__strong__out26 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inB__strong__out27 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inB__strong__out28 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inB__strong__out29 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inC__strong__out32 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inC__strong__out33 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inC__strong__out34 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inC__strong__out35 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inC__strong__out36 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inC__strong__out37 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inC__strong__out38 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inC__strong__out39 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inD__strong__out41 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inD__strong__out42 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inD__strong__out43 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inD__strong__out44 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inD__strong__out45 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inD__strong__out46 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inD__strong__out47 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__inD__strong__out48 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__mycellA__DOT__b = VL_RAND_RESET_I(32);
    VL_RAND_RESET_W(96, vlSelf->test__DOT__mycellA__DOT__iow);
    VL_RAND_RESET_W(96, vlSelf->test__DOT__mycellA__DOT__io__out__strong__out0);
    VL_RAND_RESET_W(96, vlSelf->test__DOT__mycellA__DOT__io__out__strong__out1);
    vlSelf->test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0 = VL_RAND_RESET_I(8);
    vlSelf->test__DOT__mycellB__DOT__b = VL_RAND_RESET_I(32);
    VL_RAND_RESET_W(96, vlSelf->test__DOT__mycellB__DOT__iow);
    VL_RAND_RESET_W(96, vlSelf->test__DOT__mycellB__DOT__io__out__strong__out0);
    VL_RAND_RESET_W(96, vlSelf->test__DOT__mycellB__DOT__io__out__strong__out1);
    vlSelf->test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0 = VL_RAND_RESET_I(8);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
}
