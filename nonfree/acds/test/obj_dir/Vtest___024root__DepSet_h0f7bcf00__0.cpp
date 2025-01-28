// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtest.h for the primary calling header

#include "Vtest__pch.h"
#include "Vtest___024root.h"

VlCoroutine Vtest___024root___eval_initial__TOP__Vtiming__0(Vtest___024root* vlSelf);

void Vtest___024root___eval_initial(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___eval_initial\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtest___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_INLINE_OPT VlCoroutine Vtest___024root___eval_initial__TOP__Vtiming__0(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___eval_initial__TOP__Vtiming__0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (1U) {
        co_await vlSelfRef.__VtrigSched_hc7eb0d31__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge clk)", 
                                                             "test.v", 
                                                             22);
        vlSelfRef.test__DOT__inA__strong__out13 = 0U;
        vlSelfRef.test__DOT__inB__strong__out22 = 0U;
        vlSelfRef.test__DOT__inC__strong__out32 = 0U;
        vlSelfRef.test__DOT__inD__strong__out41 = 0U;
        co_await vlSelfRef.__VtrigSched_hc7eb0d31__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge clk)", 
                                                             "test.v", 
                                                             23);
        vlSelfRef.test__DOT__inA__strong__out14 = 0U;
        vlSelfRef.test__DOT__inB__strong__out23 = 0U;
        vlSelfRef.test__DOT__inC__strong__out33 = 0U;
        vlSelfRef.test__DOT__inD__strong__out42 = 0U;
        co_await vlSelfRef.__VtrigSched_hc7eb0d31__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge clk)", 
                                                             "test.v", 
                                                             24);
        vlSelfRef.test__DOT__inA__strong__out15 = 0U;
        vlSelfRef.test__DOT__inB__strong__out24 = 0U;
        vlSelfRef.test__DOT__inC__strong__out34 = 0U;
        vlSelfRef.test__DOT__inD__strong__out43 = 0U;
        VL_WRITEF_NX("%3#\n",0,8,vlSelfRef.test__DOT__val);
        co_await vlSelfRef.__VtrigSched_hc7eb0d31__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge clk)", 
                                                             "test.v", 
                                                             25);
        vlSelfRef.test__DOT__inA__strong__out16 = 0U;
        vlSelfRef.test__DOT__inB__strong__out25 = 1U;
        vlSelfRef.test__DOT__inC__strong__out35 = 0U;
        vlSelfRef.test__DOT__inD__strong__out44 = 0U;
        VL_WRITEF_NX("%3#\n",0,8,vlSelfRef.test__DOT__val);
        co_await vlSelfRef.__VtrigSched_hc7eb0d31__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge clk)", 
                                                             "test.v", 
                                                             26);
        vlSelfRef.test__DOT__inA__strong__out17 = 1U;
        vlSelfRef.test__DOT__inB__strong__out26 = 1U;
        vlSelfRef.test__DOT__inC__strong__out36 = 0U;
        vlSelfRef.test__DOT__inD__strong__out45 = 0U;
        VL_WRITEF_NX("%3#\n",0,8,vlSelfRef.test__DOT__val);
        co_await vlSelfRef.__VtrigSched_hc7eb0d31__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge clk)", 
                                                             "test.v", 
                                                             27);
        vlSelfRef.test__DOT__inA__strong__out18 = 0U;
        vlSelfRef.test__DOT__inB__strong__out27 = 0U;
        vlSelfRef.test__DOT__inC__strong__out37 = 1U;
        vlSelfRef.test__DOT__inD__strong__out46 = 1U;
        VL_WRITEF_NX("%3#\n",0,8,vlSelfRef.test__DOT__val);
        co_await vlSelfRef.__VtrigSched_hc7eb0d31__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge clk)", 
                                                             "test.v", 
                                                             28);
        vlSelfRef.test__DOT__inA__strong__out19 = 0U;
        vlSelfRef.test__DOT__inB__strong__out28 = 1U;
        vlSelfRef.test__DOT__inC__strong__out38 = 1U;
        vlSelfRef.test__DOT__inD__strong__out47 = 0U;
        VL_WRITEF_NX("%3#\n",0,8,vlSelfRef.test__DOT__val);
        co_await vlSelfRef.__VtrigSched_hc7eb0d31__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge clk)", 
                                                             "test.v", 
                                                             29);
        vlSelfRef.test__DOT__inA__strong__out20 = 1U;
        vlSelfRef.test__DOT__inB__strong__out29 = 0U;
        vlSelfRef.test__DOT__inC__strong__out39 = 1U;
        vlSelfRef.test__DOT__inD__strong__out48 = 1U;
        VL_WRITEF_NX("%3#\n",0,8,vlSelfRef.test__DOT__val);
    }
}

void Vtest___024root___ico_sequent__TOP__0(Vtest___024root* vlSelf);

void Vtest___024root___eval_ico(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___eval_ico\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vtest___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtest___024root___ico_sequent__TOP__0(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___ico_sequent__TOP__0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
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

void Vtest___024root___eval_triggers__ico(Vtest___024root* vlSelf);

bool Vtest___024root___eval_phase__ico(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___eval_phase__ico\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtest___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vtest___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtest___024root___act_sequent__TOP__0(Vtest___024root* vlSelf);

void Vtest___024root___eval_act(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___eval_act\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtest___024root___act_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtest___024root___act_sequent__TOP__0(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___act_sequent__TOP__0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
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

void Vtest___024root___nba_sequent__TOP__0(Vtest___024root* vlSelf);

void Vtest___024root___eval_nba(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___eval_nba\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtest___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtest___024root___act_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtest___024root___nba_sequent__TOP__0(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___nba_sequent__TOP__0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlWide<3>/*95:0*/ __Vtemp_1;
    VlWide<3>/*95:0*/ __Vtemp_3;
    VlWide<3>/*95:0*/ __Vtemp_5;
    VlWide<3>/*95:0*/ __Vtemp_7;
    VlWide<3>/*95:0*/ __Vtemp_9;
    VlWide<3>/*95:0*/ __Vtemp_11;
    VlWide<3>/*95:0*/ __Vtemp_13;
    VlWide<3>/*95:0*/ __Vtemp_15;
    VlWide<3>/*95:0*/ __Vtemp_17;
    VlWide<3>/*95:0*/ __Vtemp_19;
    VlWide<3>/*95:0*/ __Vtemp_21;
    VlWide<3>/*95:0*/ __Vtemp_23;
    VlWide<3>/*95:0*/ __Vtemp_25;
    VlWide<3>/*95:0*/ __Vtemp_27;
    VlWide<3>/*95:0*/ __Vtemp_29;
    VlWide<3>/*95:0*/ __Vtemp_31;
    VlWide<3>/*95:0*/ __Vtemp_33;
    VlWide<3>/*95:0*/ __Vtemp_35;
    VlWide<3>/*95:0*/ __Vtemp_36;
    VlWide<3>/*95:0*/ __Vtemp_38;
    VlWide<3>/*95:0*/ __Vtemp_40;
    VlWide<3>/*95:0*/ __Vtemp_42;
    VlWide<3>/*95:0*/ __Vtemp_44;
    VlWide<3>/*95:0*/ __Vtemp_46;
    VlWide<3>/*95:0*/ __Vtemp_48;
    VlWide<3>/*95:0*/ __Vtemp_50;
    VlWide<3>/*95:0*/ __Vtemp_52;
    VlWide<3>/*95:0*/ __Vtemp_54;
    VlWide<3>/*95:0*/ __Vtemp_56;
    VlWide<3>/*95:0*/ __Vtemp_58;
    VlWide<3>/*95:0*/ __Vtemp_60;
    VlWide<3>/*95:0*/ __Vtemp_62;
    VlWide<3>/*95:0*/ __Vtemp_64;
    VlWide<3>/*95:0*/ __Vtemp_66;
    VlWide<3>/*95:0*/ __Vtemp_68;
    VlWide<3>/*95:0*/ __Vtemp_70;
    VlWide<3>/*95:0*/ __Vtemp_71;
    VlWide<3>/*95:0*/ __Vtemp_72;
    VlWide<3>/*95:0*/ __Vtemp_74;
    VlWide<3>/*95:0*/ __Vtemp_75;
    // Body
    if ((1U & (~ (IData)(vlSelfRef.clk)))) {
        vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out0[2U] 
            = (0xc0U | (0xffffff00U & vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out0[2U]));
        vlSelfRef.test__DOT__mycellA__DOT__b = 0xcU;
        vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out0[2U] 
            = (0xc0U | (0xffffff00U & vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out0[2U]));
        vlSelfRef.test__DOT__mycellB__DOT__b = 0xcU;
    }
    if (vlSelfRef.clk) {
        vlSelfRef.test__DOT__mycellA__DOT__b = 0xcU;
        vlSelfRef.test__DOT__mycellB__DOT__b = 0xcU;
        VL_SHIFTL_WWI(96,96,32, __Vtemp_1, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 8U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_3, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 8U);
        VL_SHIFTL_WWI(96,96,32, __Vtemp_5, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 0x10U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_7, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 0x10U);
        VL_SHIFTL_WWI(96,96,32, __Vtemp_9, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 0x18U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_11, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 0x18U);
        VL_SHIFTL_WWI(96,96,32, __Vtemp_13, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 0x20U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_15, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 0x20U);
        VL_SHIFTL_WWI(96,96,32, __Vtemp_17, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 0x28U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_19, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 0x28U);
        VL_SHIFTL_WWI(96,96,32, __Vtemp_21, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 0x30U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_23, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 0x30U);
        VL_SHIFTL_WWI(96,96,32, __Vtemp_25, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 0x38U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_27, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 0x38U);
        VL_SHIFTL_WWI(96,96,32, __Vtemp_29, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 0x40U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_31, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 0x40U);
        VL_SHIFTL_WWI(96,96,32, __Vtemp_33, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 0x48U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_35, vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2, 0x48U);
        vlSelfRef.test__DOT__mycellA__DOT__iow[0U] 
            = ((((((((((((((((((vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2[0U] 
                                | __Vtemp_1[0U]) | 
                               __Vtemp_3[0U]) | __Vtemp_5[0U]) 
                             | __Vtemp_7[0U]) | __Vtemp_9[0U]) 
                           | __Vtemp_11[0U]) | __Vtemp_13[0U]) 
                         | __Vtemp_15[0U]) | __Vtemp_17[0U]) 
                       | __Vtemp_19[0U]) | __Vtemp_21[0U]) 
                     | __Vtemp_23[0U]) | __Vtemp_25[0U]) 
                   | __Vtemp_27[0U]) | __Vtemp_29[0U]) 
                 | __Vtemp_31[0U]) | __Vtemp_33[0U]) 
               | __Vtemp_35[0U]);
        vlSelfRef.test__DOT__mycellA__DOT__iow[1U] 
            = ((((((((((((((((((vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2[1U] 
                                | __Vtemp_1[1U]) | 
                               __Vtemp_3[1U]) | __Vtemp_5[1U]) 
                             | __Vtemp_7[1U]) | __Vtemp_9[1U]) 
                           | __Vtemp_11[1U]) | __Vtemp_13[1U]) 
                         | __Vtemp_15[1U]) | __Vtemp_17[1U]) 
                       | __Vtemp_19[1U]) | __Vtemp_21[1U]) 
                     | __Vtemp_23[1U]) | __Vtemp_25[1U]) 
                   | __Vtemp_27[1U]) | __Vtemp_29[1U]) 
                 | __Vtemp_31[1U]) | __Vtemp_33[1U]) 
               | __Vtemp_35[1U]);
        vlSelfRef.test__DOT__mycellA__DOT__iow[2U] 
            = ((((((((((((((((((vlSelfRef.test__DOT____Vcellinpt__mycellA____pinNumber2[2U] 
                                | __Vtemp_1[2U]) | 
                               __Vtemp_3[2U]) | __Vtemp_5[2U]) 
                             | __Vtemp_7[2U]) | __Vtemp_9[2U]) 
                           | __Vtemp_11[2U]) | __Vtemp_13[2U]) 
                         | __Vtemp_15[2U]) | __Vtemp_17[2U]) 
                       | __Vtemp_19[2U]) | __Vtemp_21[2U]) 
                     | __Vtemp_23[2U]) | __Vtemp_25[2U]) 
                   | __Vtemp_27[2U]) | __Vtemp_29[2U]) 
                 | __Vtemp_31[2U]) | __Vtemp_33[2U]) 
               | __Vtemp_35[2U]);
        vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ vlSelfRef.test__DOT__mycellA__DOT__iow[0U]) 
                         << 6U)) | (0x3fU & vlSelfRef.test__DOT__mycellA__DOT__iow[0U]));
        vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[0U] 
            = ((0xffffff00U & vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[0U]) 
               | (IData)(vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0));
        vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellA__DOT__iow[0U] 
                              << 0x18U) | (vlSelfRef.test__DOT__mycellA__DOT__iow[0U] 
                                           >> 8U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellA__DOT__iow[0U] 
                                             >> 8U)));
        vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[0U] 
            = ((0xffff00ffU & vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[0U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0) 
                  << 8U));
        vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellA__DOT__iow[0U] 
                              << 0x10U) | (vlSelfRef.test__DOT__mycellA__DOT__iow[0U] 
                                           >> 0x10U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellA__DOT__iow[0U] 
                                             >> 0x10U)));
        vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[0U] 
            = ((0xff00ffffU & vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[0U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0) 
                  << 0x10U));
        vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellA__DOT__iow[0U] 
                              << 8U) | (vlSelfRef.test__DOT__mycellA__DOT__iow[0U] 
                                        >> 0x18U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellA__DOT__iow[0U] 
                                             >> 0x18U)));
        vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[0U] 
            = ((0xffffffU & vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[0U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0) 
                  << 0x18U));
        vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ vlSelfRef.test__DOT__mycellA__DOT__iow[1U]) 
                         << 6U)) | (0x3fU & vlSelfRef.test__DOT__mycellA__DOT__iow[1U]));
        vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[1U] 
            = ((0xffffff00U & vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[1U]) 
               | (IData)(vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0));
        vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellA__DOT__iow[1U] 
                              << 0x18U) | (vlSelfRef.test__DOT__mycellA__DOT__iow[1U] 
                                           >> 8U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellA__DOT__iow[1U] 
                                             >> 8U)));
        vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[1U] 
            = ((0xffff00ffU & vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[1U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0) 
                  << 8U));
        vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellA__DOT__iow[1U] 
                              << 0x10U) | (vlSelfRef.test__DOT__mycellA__DOT__iow[1U] 
                                           >> 0x10U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellA__DOT__iow[1U] 
                                             >> 0x10U)));
        vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[1U] 
            = ((0xff00ffffU & vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[1U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0) 
                  << 0x10U));
        vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellA__DOT__iow[1U] 
                              << 8U) | (vlSelfRef.test__DOT__mycellA__DOT__iow[1U] 
                                        >> 0x18U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellA__DOT__iow[1U] 
                                             >> 0x18U)));
        vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[1U] 
            = ((0xffffffU & vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[1U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0) 
                  << 0x18U));
        vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ vlSelfRef.test__DOT__mycellA__DOT__iow[2U]) 
                         << 6U)) | (0x3fU & vlSelfRef.test__DOT__mycellA__DOT__iow[2U]));
        vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[2U] 
            = ((0xffffff00U & vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[2U]) 
               | (IData)(vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0));
        vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellA__DOT__iow[2U] 
                              << 0x18U) | (vlSelfRef.test__DOT__mycellA__DOT__iow[2U] 
                                           >> 8U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellA__DOT__iow[2U] 
                                             >> 8U)));
        vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[2U] 
            = ((0xffff00ffU & vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[2U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0) 
                  << 8U));
        vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellA__DOT__iow[2U] 
                              << 0x10U) | (vlSelfRef.test__DOT__mycellA__DOT__iow[2U] 
                                           >> 0x10U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellA__DOT__iow[2U] 
                                             >> 0x10U)));
        vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[2U] 
            = ((0xff00ffffU & vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[2U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0) 
                  << 0x10U));
        vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellA__DOT__iow[2U] 
                              << 8U) | (vlSelfRef.test__DOT__mycellA__DOT__iow[2U] 
                                        >> 0x18U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellA__DOT__iow[2U] 
                                             >> 0x18U)));
        vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[2U] 
            = ((0xffffffU & vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[2U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellA__DOT____Vlvbound_h25c0fa5b__0) 
                  << 0x18U));
        VL_SHIFTL_WWI(96,96,32, __Vtemp_36, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 8U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_38, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 8U);
        VL_SHIFTL_WWI(96,96,32, __Vtemp_40, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 0x10U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_42, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 0x10U);
        VL_SHIFTL_WWI(96,96,32, __Vtemp_44, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 0x18U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_46, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 0x18U);
        VL_SHIFTL_WWI(96,96,32, __Vtemp_48, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 0x20U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_50, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 0x20U);
        VL_SHIFTL_WWI(96,96,32, __Vtemp_52, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 0x28U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_54, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 0x28U);
        VL_SHIFTL_WWI(96,96,32, __Vtemp_56, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 0x30U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_58, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 0x30U);
        VL_SHIFTL_WWI(96,96,32, __Vtemp_60, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 0x38U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_62, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 0x38U);
        VL_SHIFTL_WWI(96,96,32, __Vtemp_64, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 0x40U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_66, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 0x40U);
        VL_SHIFTL_WWI(96,96,32, __Vtemp_68, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 0x48U);
        VL_SHIFTR_WWI(96,96,32, __Vtemp_70, vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2, 0x48U);
        vlSelfRef.test__DOT__mycellB__DOT__iow[0U] 
            = ((((((((((((((((((vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2[0U] 
                                | __Vtemp_36[0U]) | 
                               __Vtemp_38[0U]) | __Vtemp_40[0U]) 
                             | __Vtemp_42[0U]) | __Vtemp_44[0U]) 
                           | __Vtemp_46[0U]) | __Vtemp_48[0U]) 
                         | __Vtemp_50[0U]) | __Vtemp_52[0U]) 
                       | __Vtemp_54[0U]) | __Vtemp_56[0U]) 
                     | __Vtemp_58[0U]) | __Vtemp_60[0U]) 
                   | __Vtemp_62[0U]) | __Vtemp_64[0U]) 
                 | __Vtemp_66[0U]) | __Vtemp_68[0U]) 
               | __Vtemp_70[0U]);
        vlSelfRef.test__DOT__mycellB__DOT__iow[1U] 
            = ((((((((((((((((((vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2[1U] 
                                | __Vtemp_36[1U]) | 
                               __Vtemp_38[1U]) | __Vtemp_40[1U]) 
                             | __Vtemp_42[1U]) | __Vtemp_44[1U]) 
                           | __Vtemp_46[1U]) | __Vtemp_48[1U]) 
                         | __Vtemp_50[1U]) | __Vtemp_52[1U]) 
                       | __Vtemp_54[1U]) | __Vtemp_56[1U]) 
                     | __Vtemp_58[1U]) | __Vtemp_60[1U]) 
                   | __Vtemp_62[1U]) | __Vtemp_64[1U]) 
                 | __Vtemp_66[1U]) | __Vtemp_68[1U]) 
               | __Vtemp_70[1U]);
        vlSelfRef.test__DOT__mycellB__DOT__iow[2U] 
            = ((((((((((((((((((vlSelfRef.test__DOT____Vcellinpt__mycellB____pinNumber2[2U] 
                                | __Vtemp_36[2U]) | 
                               __Vtemp_38[2U]) | __Vtemp_40[2U]) 
                             | __Vtemp_42[2U]) | __Vtemp_44[2U]) 
                           | __Vtemp_46[2U]) | __Vtemp_48[2U]) 
                         | __Vtemp_50[2U]) | __Vtemp_52[2U]) 
                       | __Vtemp_54[2U]) | __Vtemp_56[2U]) 
                     | __Vtemp_58[2U]) | __Vtemp_60[2U]) 
                   | __Vtemp_62[2U]) | __Vtemp_64[2U]) 
                 | __Vtemp_66[2U]) | __Vtemp_68[2U]) 
               | __Vtemp_70[2U]);
        vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ vlSelfRef.test__DOT__mycellB__DOT__iow[0U]) 
                         << 6U)) | (0x3fU & vlSelfRef.test__DOT__mycellB__DOT__iow[0U]));
        vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[0U] 
            = ((0xffffff00U & vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[0U]) 
               | (IData)(vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0));
        vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellB__DOT__iow[0U] 
                              << 0x18U) | (vlSelfRef.test__DOT__mycellB__DOT__iow[0U] 
                                           >> 8U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellB__DOT__iow[0U] 
                                             >> 8U)));
        vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[0U] 
            = ((0xffff00ffU & vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[0U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0) 
                  << 8U));
        vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellB__DOT__iow[0U] 
                              << 0x10U) | (vlSelfRef.test__DOT__mycellB__DOT__iow[0U] 
                                           >> 0x10U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellB__DOT__iow[0U] 
                                             >> 0x10U)));
        vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[0U] 
            = ((0xff00ffffU & vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[0U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0) 
                  << 0x10U));
        vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellB__DOT__iow[0U] 
                              << 8U) | (vlSelfRef.test__DOT__mycellB__DOT__iow[0U] 
                                        >> 0x18U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellB__DOT__iow[0U] 
                                             >> 0x18U)));
        vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[0U] 
            = ((0xffffffU & vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[0U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0) 
                  << 0x18U));
        vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ vlSelfRef.test__DOT__mycellB__DOT__iow[1U]) 
                         << 6U)) | (0x3fU & vlSelfRef.test__DOT__mycellB__DOT__iow[1U]));
        vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[1U] 
            = ((0xffffff00U & vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[1U]) 
               | (IData)(vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0));
        vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellB__DOT__iow[1U] 
                              << 0x18U) | (vlSelfRef.test__DOT__mycellB__DOT__iow[1U] 
                                           >> 8U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellB__DOT__iow[1U] 
                                             >> 8U)));
        vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[1U] 
            = ((0xffff00ffU & vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[1U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0) 
                  << 8U));
        vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellB__DOT__iow[1U] 
                              << 0x10U) | (vlSelfRef.test__DOT__mycellB__DOT__iow[1U] 
                                           >> 0x10U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellB__DOT__iow[1U] 
                                             >> 0x10U)));
        vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[1U] 
            = ((0xff00ffffU & vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[1U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0) 
                  << 0x10U));
        vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellB__DOT__iow[1U] 
                              << 8U) | (vlSelfRef.test__DOT__mycellB__DOT__iow[1U] 
                                        >> 0x18U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellB__DOT__iow[1U] 
                                             >> 0x18U)));
        vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[1U] 
            = ((0xffffffU & vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[1U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0) 
                  << 0x18U));
        vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ vlSelfRef.test__DOT__mycellB__DOT__iow[2U]) 
                         << 6U)) | (0x3fU & vlSelfRef.test__DOT__mycellB__DOT__iow[2U]));
        vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[2U] 
            = ((0xffffff00U & vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[2U]) 
               | (IData)(vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0));
        vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellB__DOT__iow[2U] 
                              << 0x18U) | (vlSelfRef.test__DOT__mycellB__DOT__iow[2U] 
                                           >> 8U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellB__DOT__iow[2U] 
                                             >> 8U)));
        vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[2U] 
            = ((0xffff00ffU & vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[2U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0) 
                  << 8U));
        vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellB__DOT__iow[2U] 
                              << 0x10U) | (vlSelfRef.test__DOT__mycellB__DOT__iow[2U] 
                                           >> 0x10U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellB__DOT__iow[2U] 
                                             >> 0x10U)));
        vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[2U] 
            = ((0xff00ffffU & vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[2U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0) 
                  << 0x10U));
        vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0 
            = ((0xc0U & ((~ ((vlSelfRef.test__DOT__mycellB__DOT__iow[2U] 
                              << 8U) | (vlSelfRef.test__DOT__mycellB__DOT__iow[2U] 
                                        >> 0x18U))) 
                         << 6U)) | (0x3fU & (vlSelfRef.test__DOT__mycellB__DOT__iow[2U] 
                                             >> 0x18U)));
        vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[2U] 
            = ((0xffffffU & vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[2U]) 
               | ((IData)(vlSelfRef.test__DOT__mycellB__DOT____Vlvbound_h25c0fa5b__0) 
                  << 0x18U));
    }
    __Vtemp_71[0U] = 0xc0U;
    __Vtemp_71[1U] = 0U;
    __Vtemp_71[2U] = 0U;
    VL_SHIFTL_WWI(96,96,7, __Vtemp_72, __Vtemp_71, 
                  (0x7fU & VL_SHIFTL_III(7,7,32, vlSelfRef.test__DOT__mycellA__DOT__b, 3U)));
    vlSelfRef.test__DOT____Vcelloutt__mycellA__io__out[0U] 
        = ((vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out0[0U] 
            & __Vtemp_72[0U]) | vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[0U]);
    vlSelfRef.test__DOT____Vcelloutt__mycellA__io__out[1U] 
        = ((vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out0[1U] 
            & __Vtemp_72[1U]) | vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[1U]);
    vlSelfRef.test__DOT____Vcelloutt__mycellA__io__out[2U] 
        = ((vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out0[2U] 
            & __Vtemp_72[2U]) | vlSelfRef.test__DOT__mycellA__DOT__io__out__strong__out1[2U]);
    __Vtemp_74[0U] = 0xc0U;
    __Vtemp_74[1U] = 0U;
    __Vtemp_74[2U] = 0U;
    VL_SHIFTL_WWI(96,96,7, __Vtemp_75, __Vtemp_74, 
                  (0x7fU & VL_SHIFTL_III(7,7,32, vlSelfRef.test__DOT__mycellB__DOT__b, 3U)));
    vlSelfRef.test__DOT____Vcelloutt__mycellB__io__out[0U] 
        = ((vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out0[0U] 
            & __Vtemp_75[0U]) | vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[0U]);
    vlSelfRef.test__DOT____Vcelloutt__mycellB__io__out[1U] 
        = ((vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out0[1U] 
            & __Vtemp_75[1U]) | vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[1U]);
    vlSelfRef.test__DOT____Vcelloutt__mycellB__io__out[2U] 
        = ((vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out0[2U] 
            & __Vtemp_75[2U]) | vlSelfRef.test__DOT__mycellB__DOT__io__out__strong__out1[2U]);
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
}

void Vtest___024root___timing_commit(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___timing_commit\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((! (2ULL & vlSelfRef.__VactTriggered.word(0U)))) {
        vlSelfRef.__VtrigSched_hc7eb0d31__0.commit(
                                                   "@(posedge clk)");
    }
}

void Vtest___024root___timing_resume(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___timing_resume\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        vlSelfRef.__VtrigSched_hc7eb0d31__0.resume(
                                                   "@(posedge clk)");
    }
}

void Vtest___024root___eval_triggers__act(Vtest___024root* vlSelf);

bool Vtest___024root___eval_phase__act(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___eval_phase__act\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtest___024root___eval_triggers__act(vlSelf);
    Vtest___024root___timing_commit(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vtest___024root___timing_resume(vlSelf);
        Vtest___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtest___024root___eval_phase__nba(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___eval_phase__nba\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtest___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtest___024root___dump_triggers__ico(Vtest___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtest___024root___dump_triggers__nba(Vtest___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtest___024root___dump_triggers__act(Vtest___024root* vlSelf);
#endif  // VL_DEBUG

void Vtest___024root___eval(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___eval\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            Vtest___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("test.v", 1, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vtest___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vtest___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("test.v", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelfRef.__VactIterCount))) {
#ifdef VL_DEBUG
                Vtest___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("test.v", 1, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vtest___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vtest___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtest___024root___eval_debug_assertions(Vtest___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtest__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest___024root___eval_debug_assertions\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY((vlSelfRef.clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
}
#endif  // VL_DEBUG
