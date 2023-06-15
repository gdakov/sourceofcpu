/*
Copyright 2022 Goran Dakov

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/


`include "../struct.sv"
`include "../fpoperations.sv"
`include "../csrss_no.sv"

module fun_fpu_BOTH(
  clk,
  rst,
  fpcsr,
  u1_A0,u1_B0,u1_A1,u1_B1,u1_en,u1_op,
  u1_fufwd_A,u1_fuufwd_A,u1_fufwd_B,u1_fuufwd_B,
  u1_ret,u1_ret_en,
  u3_A0,u3_B0,u3_A1,u3_B1,u3_en,u3_op,
  u3_fufwd_A,u3_fuufwd_A,u3_fufwd_B,u3_fuufwd_B,
  u3_ret,u3_ret_en,
  u5_A0,u5_B0,u5_A1,u5_B1,u5_en,u5_op,
  u5_fufwd_A,u5_fuufwd_A,u5_fufwd_B,u5_fuufwd_B,
  u5_ret,u5_ret_en,
  FUFH0,FUFH1,FUFH2,
  FUFH3,FUFH4,FUFH5,
  FUFH6,FUFH7,FUFH8,
  FUFH9,
  FUFL0,FUFL1,FUFL2,
  FUFL3,FUFL4,FUFL5,
  FUFL6,FUFL7,FUFL8,
  FUFL9,
  FUFH0_n,FUFH1_n,FUFH2_n,FUFH3_n,FUFH4_n,FUFH5_n,
  FUFL0_m,FUFL1_m,FUFL2_m,FUFL3_m,FUFL4_m,FUFL5_m,
  FUFH6_n,FUFH7_n,FUFH8_n,FUFH9_n,
  FUFL6_m,FUFL7_m,FUFL8_m,FUFL9_m,
  ALTDATAH0,ALTDATAH1,
  ALTDATAL0,ALTDATAL1,
  ALT_INP,
  FUS_alu0,FUS_alu1,
  FUS_alu2,FUS_alu3,
  FUS_alu4,FUS_alu5,
  ex_alu0,ex_alu1,
  ex_alu2,ex_alu3,
  ex_alu4,ex_alu5,
  fxFADD0_raise_s,
  fxFCADD1_raise_s,
  fxFADD2_raise_s,
  fxFCADD3_raise_s,
  fxFADD4_raise_s,
  fxFCADD5_raise_s,
  FUS0,FUS1,FUS2,
  FOOSL0,FOOSL1,FOOSL2,
  XI_dataS,
  fxFRT_alten_reg3,
  daltX,
  FUCVT1,
  outAH,outBH,
  outAL,outBL
  );
  localparam [0:0] H=1'b1;
  localparam SIMD_WIDTH=68; //half width
/*verilator hier_block*/
  input clk;
  input rst;
  input [31:0] fpcsr;
  input [16+67:0] u1_A0;
  input [16+67:0] u1_B0;
  input [67:0]    u1_A1;
  input [67:0]    u1_B1;
  input [3:0] u1_en;
  input [12:0] u1_op;
  input [3:0] u1_fufwd_A;
  input [3:0] u1_fuufwd_A;
  input [3:0] u1_fufwd_B;
  input [3:0] u1_fuufwd_B;
  output [13:0] u1_ret;
  output u1_ret_en;

  input [16+67:0] u3_A0;
  input [16+67:0] u3_B0;
  input [67:0]    u3_A1;
  input [67:0]    u3_B1;
  input [3:0] u3_en;
  input [12:0] u3_op;
  input [3:0] u3_fufwd_A;
  input [3:0] u3_fuufwd_A;
  input [3:0] u3_fufwd_B;
  input [3:0] u3_fuufwd_B;
  output [13:0] u3_ret;
  output u3_ret_en;

  input [16+67:0] u5_A0;
  input [16+67:0] u5_B0;
  input [67:0]    u5_A1;
  input [67:0]    u5_B1;
  input [3:0] u5_en;
  input [12:0] u5_op;
  input [3:0] u5_fufwd_A;
  input [3:0] u5_fuufwd_A;
  input [3:0] u5_fufwd_B;
  input [3:0] u5_fuufwd_B;
  output [13:0] u5_ret;
  output u5_ret_en;


  input [67:0] FUFH0;
  input [67:0] FUFH1;
  input [67:0] FUFH2;
  input [67:0] FUFH3;
  output [67:0] FUFH4;
  output [67:0] FUFH5;
  output [67:0] FUFH6;
  output [67:0] FUFH7;
  output [67:0] FUFH8;
  output [67:0] FUFH9;
  
  input [16+67:0] FUFL0;
  input [16+67:0] FUFL1;
  input [16+67:0] FUFL2;
  input [16+67:0] FUFL3;
  output [16+67:0] FUFL4;
  output [16+67:0] FUFL5;
  output [16+67:0] FUFL6;
  output [16+67:0] FUFL7;
  output [16+67:0] FUFL8;
  output [16+67:0] FUFL9;
  input [1:0] ALT_INP;
  input [16+67:0] ALTDATAL0;
  input [16+67:0] ALTDATAL1;
  input [67:0] ALTDATAH0;
  input [67:0] ALTDATAH1;
  
  input [67:0] FUFH0_n;
  input [67:0] FUFH1_n;
  input [67:0] FUFH2_n;
  input [67:0] FUFH3_n;
  input [16+67:0] FUFL0_m;
  input [16+67:0] FUFL1_m;
  input [16+67:0] FUFL2_m;
  input [16+67:0] FUFL3_m;
  output [16+67:0] FUFL4_m;
  output [16+67:0] FUFL5_m;
  output [67:0] FUFH4_n;
  output [67:0] FUFH5_n;

  output [67:0] FUFH6_n;
  output [67:0] FUFH7_n;
  output [67:0] FUFH8_n;
  output [67:0] FUFH9_n;
  output [16+67:0] FUFL6_m;
  output [16+67:0] FUFL7_m;
  output [16+67:0] FUFL8_m;
  output [16+67:0] FUFL9_m;

  input [5:0] FUS_alu0;
  input [5:0] FUS_alu1;
  input [5:0] FUS_alu2;
  input [5:0] FUS_alu3;
  input [5:0] FUS_alu4;
  input [5:0] FUS_alu5;
  input [2:0] ex_alu0;
  input [2:0] ex_alu1;
  input [2:0] ex_alu2;
  input [2:0] ex_alu3;
  input [2:0] ex_alu4;
  input [2:0] ex_alu5;
  input [10:0] fxFADD0_raise_s;
  input [10:0] fxFCADD1_raise_s;
  input [10:0] fxFADD2_raise_s;
  input [10:0] fxFCADD3_raise_s;
  input [10:0] fxFADD4_raise_s;
  input [10:0] fxFCADD5_raise_s;

  output [5:0] FUS0;
  output [5:0] FUS1;
  output [5:0] FUS2;

  input [5:0] FOOSL0;
  input [5:0] FOOSL1;
  input [5:0] FOOSL2;
  
  input [67:0] XI_dataS;
  input fxFRT_alten_reg3;
  output daltX;
  output [63:0] FUCVT1;
  
  output [67:0] outAH;
  output [67:0] outBH;
  output [16+67:0] outAL;
  output [16+67:0] outBL;

  wire [67:0] u1_Ax;
  wire [67:0] u1_Bx;
  wire [67:0] u2_Ax;
  wire [67:0] u2_Bx;
  wire [67:0] u3_Ax;
  wire [67:0] u3_Bx;
  wire [67:0] u4_Ax;
  wire [67:0] u4_Bx;
  wire [67:0] u5_Ax;
  wire [67:0] u5_Bx;
  wire [67:0] u6_Ax;
  wire [67:0] u6_Bx;

  wire [13:0] u1_retH;
  wire u1_ret_enH;
  wire [13:0] u2_retH;
  wire u2_ret_enH;
  wire [13:0] u3_retH;
  wire u3_ret_enH;
  wire [13:0] u4_retH;
  wire u4_ret_enH;
  wire [13:0] u5_retH;
  wire u5_ret_enH;
  wire [13:0] u6_retH;
  wire u6_ret_enH;
  wire [13:0] u1_retL;
  wire u1_ret_enL;
  wire [13:0] u2_retL;
  wire u2_ret_enL;
  wire [13:0] u3_retL;
  wire u3_ret_enL;
  wire [13:0] u4_retL;
  wire u4_ret_enL;
  wire [13:0] u5_retL;
  wire u5_ret_enL;
  wire [13:0] u6_retL;
  wire u6_ret_enL;

  wire [5:0] LFOOSH0;
  wire [5:0] LFOOSH1;
  wire [5:0] LFOOSH2;

  wire [5:0] HFOOSH0;
  wire [5:0] HFOOSH1;
  wire [5:0] HFOOSH2;

  reg [12:0] u1_op_reg;
  reg [12:0] u1_op_reg2;
  reg [12:0] u1_op_reg3;
  reg [12:0] u1_op_reg4;
  reg [12:0] u3_op_reg;
  reg [12:0] u3_op_reg2;
  reg [12:0] u3_op_reg3;
  reg [12:0] u3_op_reg4;
  reg [12:0] u5_op_reg;
  reg [12:0] u5_op_reg2;
  reg [12:0] u5_op_reg3;
  reg [12:0] u5_op_reg4;

  assign u1_ret=u1_retL|u1_retH;
  assign u1_ret_en=u1_ret_enL| u1_ret_enH;
  assign u3_ret=u3_retL|u3_retH;
  assign u3_ret_en=u3_ret_enL| u3_ret_enH;
  assign u5_ret=u5_retL|u5_retH;
  assign u5_ret_en=u5_ret_enL| u5_ret_enH;

  fun_fpuH hf_mod(
  clk,
  rst,
  fpcsr,
  u1_A1,u1_B1,u1_Ax,u1_Bx,u1_en,u1_op,
  u1_fufwd_A,u1_fuufwd_A,u1_fufwd_B,u1_fuufwd_B,
  u1_retH,u1_ret_enH,
  u3_A1,u3_B1,u3_Ax,u3_Bx,u3_en,u3_op,
  u3_fufwd_A,u3_fuufwd_A,u3_fufwd_B,u3_fuufwd_B,
  u3_retH,u3_ret_enH,
  u5_A1,u5_B1,u5_Ax,u5_Bx,u5_en,u5_op,
  u5_fufwd_A,u5_fuufwd_A,u5_fufwd_B,u5_fuufwd_B,
  u5_retH,u5_ret_enH,
  FUFH0,FUFH1,FUFH2,
  FUFH3,FUFH4,FUFH5,
  FUFH6,FUFH7,FUFH8,
  FUFH9,
  FUFH0_n,FUFH1_n,FUFH2_n,FUFH3_n,FUFH4_n,FUFH5_n,
  FUFH6_n,FUFH7_n,FUFH8_n,FUFH9_n,
  ALTDATAH0,ALTDATAH1,
  ALT_INP,
  FUS_alu0,FUS_alu1,
  FUS_alu2,FUS_alu3,
  FUS_alu4,FUS_alu5,
  ex_alu0,ex_alu1,
  ex_alu2,ex_alu3,
  ex_alu4,ex_alu5,
  fxFADD0_raise_s,
  fxFCADD1_raise_s,
  fxFADD2_raise_s,
  fxFCADD3_raise_s,
  fxFADD4_raise_s,
  fxFCADD5_raise_s,
  FOOSL0, HFOOSH0,
  FOOSL1, HFOOSH1,
  FOOSL2, HFOOSH2,
  outAH,outBH
  ); 

  fun_fpuL lfpc_mod(
  clk,
  rst,
  fpcsr,
  u1_A0,u1_B0,u1_Bx,u1_Ax,u1_en,u1_op,
  u1_fufwd_A,u1_fuufwd_A,u1_fufwd_B,u1_fuufwd_B,
  u1_retL,u1_ret_enL,
  u3_A0,u3_B0,u3_Bx,u3_Ax,u3_en,u3_op,
  u3_fufwd_A,u3_fuufwd_A,u3_fufwd_B,u3_fuufwd_B,
  u3_retL,u3_ret_enL,
  u5_A0,u5_B0,u5_Bx,u5_Ax,u5_en,u5_op,
  u5_fufwd_A,u5_fuufwd_A,u5_fufwd_B,u5_fuufwd_B,
  u5_retL,u5_ret_enL,
  FUFL0,FUFL1,FUFL2,
  FUFL3,FUFL4,FUFL5,
  FUFL6,FUFL7,FUFL8,
  FUFL9,
  FUFL0_m,FUFL1_m,FUFL2_m,FUFL3_m,FUFL4_m,FUFL5_m,
  FUFL6_m,FUFL7_m,FUFL8_m,FUFL9_m,
  ALTDATAL0,ALTDATAL1,
  ALT_INP,
  FUS_alu0,FUS_alu1,
  FUS_alu2,FUS_alu3,
  FUS_alu4,FUS_alu5,
  ex_alu0,ex_alu1,
  ex_alu2,ex_alu3,
  ex_alu4,ex_alu5,
  fxFADD0_raise_s,
  fxFCADD1_raise_s,
  fxFADD2_raise_s,
  fxFCADD3_raise_s,
  fxFADD4_raise_s,
  fxFCADD5_raise_s,
  FOOSL0, LFOOSH0,
  FOOSL1, LFOOSH1,
  FOOSL2, LFOOSH2,
  XI_dataS,
  fxFRT_alten_reg3,
  daltX,
  FUCVT1,
  outAL,outBL
  );

  assign FUS0=u1_op_reg4[7:0]==`fop_cmpDH  ? HFOOSH0 : LFOOSH0; 
  assign FUS1=u3_op_reg4[7:0]==`fop_cmpDH  ? HFOOSH1 : LFOOSH1; 
  assign FUS2=u5_op_reg4[7:0]==`fop_cmpDH  ? HFOOSH2 : LFOOSH2; 

  always @(posedge clk) begin
      u1_op_reg<=u1_op;
      u1_op_reg2<=u1_op_reg;
      u1_op_reg3<=u1_op_reg2;
      u1_op_reg4<=u1_op_reg3;
      u3_op_reg<=u3_op;
      u3_op_reg2<=u3_op_reg;
      u3_op_reg3<=u3_op_reg2;
      u3_op_reg4<=u3_op_reg3;
      u5_op_reg<=u5_op;
      u5_op_reg2<=u5_op_reg;
      u5_op_reg3<=u5_op_reg2;
      u5_op_reg4<=u5_op_reg3;
  end
endmodule