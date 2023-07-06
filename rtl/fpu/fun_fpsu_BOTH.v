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

module fun_fpsu_BOTH(
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
  MRKAH,MRKBH,MRKAL,BRKBL,
  ALTDATAH0,ALTDATAH1,
  ALTDATAL0,ALTDATAL1,
  ALT_INP,
  FOOFL0,FOOFL1,FOOFL2,
  XI_dataS
  );
  localparam [0:0] H=1'b1;
  localparam SIMD_WIDTH=68; //half width
/*verilator hier_block*/
  input clk;
  input rst;
  input [31:0] fpcsr;
  (* bus=SIMDL bus_spacing=8 bus_off=0 *) input [67:0] u1_A0;
  (* bus=SIMDL bus_spacing=8 bus_off=0 *) input [67:0] u1_B0;
  (* bus=SIMDH bus_spacing=8 bus_off=0 *) input [67:0]    u1_A1;
  (* bus=SIMDH bus_spacing=8 bus_off=0 *) input [67:0]    u1_B1;
  input [3:0] u1_en;
  input [12:0] u1_op;
  input [3:0] u1_fufwd_A;
  input [3:0] u1_fuufwd_A;
  input [3:0] u1_fufwd_B;
  input [3:0] u1_fuufwd_B;
  output [13:0] u1_ret;
  output u1_ret_en;

  (* bus=SIMDL bus_spacing=8 bus_off=1 *) input [67:0] u3_A0;
  (* bus=SIMDL bus_spacing=8 bus_off=1 *) input [67:0] u3_B0;
  (* bus=SIMDH bus_spacing=8 bus_off=1 *) input [67:0]    u3_A1;
  (* bus=SIMDH bus_spacing=8 bus_off=1 *) input [67:0]    u3_B1;
  input [3:0] u3_en;
  input [12:0] u3_op;
  input [3:0] u3_fufwd_A;
  input [3:0] u3_fuufwd_A;
  input [3:0] u3_fufwd_B;
  input [3:0] u3_fuufwd_B;
  output [13:0] u3_ret;
  output u3_ret_en;

  (* bus=SIMDL bus_spacing=8 bus_off=2 *) input [67:0] u5_A0;
  (* bus=SIMDL bus_spacing=8 bus_off=2 *) input [67:0] u5_B0;
  (* bus=SIMDH bus_spacing=8 bus_off=2 *) input [67:0]    u5_A1;
  (* bus=SIMDH bus_spacing=8 bus_off=2 *) input [67:0]    u5_B1;
  input [3:0] u5_en;
  input [12:0] u5_op;
  input [3:0] u5_fufwd_A;
  input [3:0] u5_fuufwd_A;
  input [3:0] u5_fufwd_B;
  input [3:0] u5_fuufwd_B;
  output [13:0] u5_ret;
  output u5_ret_en;


  (* register equiload *) (* bus=SIMDH bus_spacing=8 bus_rpl=3 *) input [67:0] FUFH0;
  (* register equiload *) (* bus=SIMDH bus_spacing=8 bus_rpl=3 *) input [67:0] FUFH1;
  (* register equiload *) (* bus=SIMDH bus_spacing=8 bus_rpl=3 *) input [67:0] FUFH2;
  (* register equiload *) (* bus=SIMDH bus_spacing=8 bus_rpl=3 *) input [67:0] FUFH3;
  (* register equiload *) (* bus=SIMDH bus_spacing=8 bus_rpl=3 *) output [67:0] FUFH4;
  (* register equiload *) (* bus=SIMDH bus_spacing=8 bus_rpl=3 *) output [67:0] FUFH5;
  (* register equiload *) (* bus=SIMDH bus_spacing=8 bus_rpl=3 *) output [67:0] FUFH6;
  (* register equiload *) (* bus=SIMDH bus_spacing=8 bus_rpl=3 *) output [67:0] FUFH7;
  (* register equiload *) (* bus=SIMDH bus_spacing=8 bus_rpl=3 *) output [67:0] FUFH8;
  (* register equiload *) (* bus=SIMDH bus_spacing=8 bus_rpl=3 *) output [67:0] FUFH9;
  
  (* register equiload *) (* bus=SIMDL bus_spacing=8 bus_rpl=3 *) input [67:0] FUFL0;
  (* register equiload *) (* bus=SIMDL bus_spacing=8 bus_rpl=3 *) input [67:0] FUFL1;
  (* register equiload *) (* bus=SIMDL bus_spacing=8 bus_rpl=3 *) input [67:0] FUFL2;
  (* register equiload *) (* bus=SIMDL bus_spacing=8 bus_rpl=3 *) input [67:0] FUFL3;
  (* register equiload *) (* bus=SIMDL bus_spacing=8 bus_rpl=3 *) output [67:0] FUFL4;
  (* register equiload *) (* bus=SIMDL bus_spacing=8 bus_rpl=3 *) output [67:0] FUFL5;
  (* register equiload *) (* bus=SIMDL bus_spacing=8 bus_rpl=3 *) output [67:0] FUFL6;
  (* register equiload *) (* bus=SIMDL bus_spacing=8 bus_rpl=3 *) output [67:0] FUFL7;
  (* register equiload *) (* bus=SIMDL bus_spacing=8 bus_rpl=3 *) output [67:0] FUFL8;
  (* register equiload *) (* bus=SIMDL bus_spacing=8 bus_rpl=3 *) output [67:0] FUFL9;
  input [1:0] ALT_INP;
  (* bus=SIMDL bus_spacing=8 *) input [67:0] ALTDATAL0;
  (* bus=SIMDL bus_spacing=8 *) input [67:0] ALTDATAL1;
  (* bus=SIMDH bus_spacing=8 *) input [67:0] ALTDATAH0;
  (* bus=SIMDH bus_spacing=8 *) input [67:0] ALTDATAH1;

  (* register equiload *) output [5:0] FOOFL0;
  (* register equiload *) output [5:0] FOOFL1;
  (* register equiload *) output [5:0] FOOFL2;
  
  (* register equiload *) (* bus=SIMDH bus_spacing=8 *)output [67:0] MRKAH;
  (* register equiload *) (* bus=SIMDH bus_spacing=8 *)output [67:0] MRKBH;
  (* register equiload *) (* bus=SIMDL bus_spacing=8 *) output [67:0] MRKAL;
  (* register equiload *) (* bus=SIMDL bus_spacing=8 *) output [67:0] BRKBL;

  output [67:0] XI_dataS;
  
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
  
  /*wire  [67:0] FUFH4X;
  wire  [67:0] FUFH5X;
  wire  [67:0] FUFH6X;
  wire  [67:0] FUFH7X;
  wire  [67:0] FUFH8X;
  wire  [67:0] FUFH9X;

  assign FUFH4=FUFH4X;
  assign FUFH5=FUFH5X;
  assign FUFH6=FUFH6X;
  assign FUFH7=FUFH7X;
  assign FUFH8=FUFH8X;
  assign FUFH9=FUFH9X;

  wire  [67:0] FUFL4X;
  wire  [67:0] FUFL5X;
  wire  [67:0] FUFL6X;
  wire  [67:0] FUFL7X;
  wire  [67:0] FUFL8X;
  wire  [67:0] FUFL9X;

  assign FUFL4=FUFL4X;
  assign FUFL5=FUFL5X;
  assign FUFL6=FUFL6X;
  assign FUFL7=FUFL7X;
  assign FUFL8=FUFL8X;
  assign FUFL9=FUFL9X;
*/
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

  assign u1_ret=u1_retL|u1_retH;
  assign u1_ret_en=u1_ret_enL| u1_ret_enH;
  assign u3_ret=u3_retL|u3_retH;
  assign u3_ret_en=u3_ret_enL| u3_ret_enH;
  assign u5_ret=u5_retL|u5_retH;
  assign u5_ret_en=u5_ret_enL| u5_ret_enH;

  fun_fpuSL hf_mod(
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
  ALTDATAH0,ALTDATAH1,
  ALT_INP,,,,,MRKAH,MRKBH
  );

  fun_fpuSL lfpc_mod(
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
  ALTDATAL0,ALTDATAL1,
  ALT_INP,
  FOOFL0,FOOFL1,FOOFL2,
  XI_dataS,
  MRKAL,BRKBL
  );

endmodule