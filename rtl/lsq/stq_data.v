`include "../struct.sv"
/*
Copyright 2022-2024 Goran Dakov, D.O.B. 11 January 1983, lives in Bristol UK in 2024

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
module stq_data(
  clk,
  rst,
  wrt0_en,wrt0_data,
  wrt1_en,wrt1_data,
  chk0_en,chk0_data,
  chk1_en,chk1_data,
  chk2_en,chk2_data,
  chk3_en,chk3_data,
  chk4_en,chk4_data,
  chk5_en,chk5_data,
  chk6_en,chk6_data,
  chk7_en,chk7_data
  );
  parameter WIDTH=32;
  input clk;
  input rst;
  input wrt0_en;
  input [WIDTH-1:0] wrt0_data;
  input wrt1_en;
  input [WIDTH-1:0] wrt1_data;
  input chk0_en;
  output [WIDTH-1:0] chk0_data;
  input chk1_en;
  output [WIDTH-1:0] chk1_data;
  input chk2_en;
  output [WIDTH-1:0] chk2_data;
  input chk3_en;
  output [WIDTH-1:0] chk3_data;
  input chk4_en;
  output [WIDTH-1:0] chk4_data;
  input chk5_en;
  output [WIDTH-1:0] chk5_data;
  input chk6_en;
  output [WIDTH-1:0] chk6_data;
  input chk7_en;
  output [WIDTH-1:0] chk7_data;
 
  reg [WIDTH-1:0] data;

  assign chk0_data=chk0_en ? data : 'z;
  assign chk1_data=chk1_en ? data : 'z;
  assign chk2_data=chk2_en ? data : 'z;
  assign chk3_data=chk3_en ? data : 'z;
  assign chk4_data=chk4_en ? data : 'z;
  assign chk5_data=chk5_en ? data : 'z;
  assign chk6_data=chk6_en ? data : 'z;
  assign chk7_data=chk7_en ? data : 'z;
  
  always @(posedge clk) begin
      if (wrt0_en) data<=wrt0_data;
      if (wrt1_en) data<=wrt1_data;
  end
  
endmodule  
  

module stq_data_array(
  clk,
  rst,
  wrt0_en,wrt0_data,
  wrt1_en,wrt1_data,
  chk0_en,chk0_data,chk0_pre0,chk0_pre1,
  chk1_en,chk1_data,chk1_pre0,chk1_pre1,
  chk2_en,chk2_data,chk2_pre0,chk2_pre1,
  chk3_en,chk3_data,chk3_pre0,chk3_pre1,
  chk4_en,chk4_data,chk4_pre0,chk4_pre1,
  chk5_en,chk5_data,chk5_pre0,chk5_pre1,
  chk6_en,chk6_data,
  chk7_en,chk7_data
  );
  parameter WIDTH=32;
  localparam BUF_COUNT=64;
  input clk;
  input rst;
  input [BUF_COUNT-1:0] wrt0_en;
  input [WIDTH-1:0] wrt0_data;
  input [BUF_COUNT-1:0] wrt1_en;
  input [WIDTH-1:0] wrt1_data;
  input [BUF_COUNT-1:0] chk0_en;
  output reg [WIDTH-1:0] chk0_data;
  input [BUF_COUNT-1:0] chk1_en;
  input chk0_pre0,chk0_pre1;
  output reg [WIDTH-1:0] chk1_data;
  input chk1_pre0,chk1_pre1;
  input [BUF_COUNT-1:0] chk2_en;
  output reg [WIDTH-1:0] chk2_data;
  input chk2_pre0,chk2_pre1;
  input [BUF_COUNT-1:0] chk3_en;
  output reg [WIDTH-1:0] chk3_data;
  input chk3_pre0,chk3_pre1;
  input [BUF_COUNT-1:0] chk4_en;
  output reg [WIDTH-1:0] chk4_data;
  input chk4_pre0,chk4_pre1;
  input [BUF_COUNT-1:0] chk5_en;
  output reg [WIDTH-1:0] chk5_data;
  input chk5_pre0,chk5_pre1;
  input [BUF_COUNT-1:0] chk6_en;
  output reg [WIDTH-1:0] chk6_data;
  input [BUF_COUNT-1:0] chk7_en;
  output reg [WIDTH-1:0] chk7_data;
  
  wire [WIDTH-1:0] chk0_data0;
  wire [WIDTH-1:0] chk1_data0;
  wire [WIDTH-1:0] chk2_data0;
  wire [WIDTH-1:0] chk3_data0;
  wire [WIDTH-1:0] chk4_data0;
  wire [WIDTH-1:0] chk5_data0;
  wire [WIDTH-1:0] chk6_data0;
  wire [WIDTH-1:0] chk7_data0;
  
  wire [WIDTH-1:0] chk0_data1;
  wire [WIDTH-1:0] chk1_data1;
  wire [WIDTH-1:0] chk2_data1;
  wire [WIDTH-1:0] chk3_data1;
  wire [WIDTH-1:0] chk4_data1;
  wire [WIDTH-1:0] chk5_data1;
  generate
    genvar bank,row;
    for(bank=0;bank<8;bank=bank+1) begin : bnk_gen
        wire [WIDTH-1:0] chk0_dataK;
        wire [WIDTH-1:0] chk1_dataK;
        wire [WIDTH-1:0] chk2_dataK;
        wire [WIDTH-1:0] chk3_dataK;
        wire [WIDTH-1:0] chk4_dataK;
        wire [WIDTH-1:0] chk5_dataK;
        wire [WIDTH-1:0] chk6_dataK;
        wire [WIDTH-1:0] chk7_dataK;
        for(row=0;row<8;row=row+1) begin : row_gen
            stq_data #(WIDTH) buf_mod(
            clk,
            rst,
            wrt0_en[bank*8+row],wrt0_data,
            wrt1_en[bank*8+row],wrt1_data,
            chk0_en[bank*8+row],chk0_dataK,
            chk1_en[bank*8+row],chk1_dataK,
            chk2_en[bank*8+row],chk2_dataK,
            chk3_en[bank*8+row],chk3_dataK,
            chk4_en[bank*8+row],chk4_dataK,
            chk5_en[bank*8+row],chk5_dataK,
            chk6_en[bank*8+row],chk6_dataK,
            chk7_en[bank*8+row],chk7_dataK
            );
        end
        assign chk0_dataK=(|chk0_en[bank*8+:8]) ? 'z : {WIDTH{1'B0}};
        assign chk1_dataK=(|chk1_en[bank*8+:8]) ? 'z : {WIDTH{1'B0}};
        assign chk2_dataK=(|chk2_en[bank*8+:8]) ? 'z : {WIDTH{1'B0}};
        assign chk3_dataK=(|chk3_en[bank*8+:8]) ? 'z : {WIDTH{1'B0}};
        assign chk4_dataK=(|chk4_en[bank*8+:8]) ? 'z : {WIDTH{1'B0}};
        assign chk5_dataK=(|chk5_en[bank*8+:8]) ? 'z : {WIDTH{1'B0}};
        assign chk6_dataK=(|chk6_en[bank*8+:8]) ? 'z : {WIDTH{1'B0}};
        assign chk7_dataK=(|chk7_en[bank*8+:8]) ? 'z : {WIDTH{1'B0}};

        assign chk0_data0=(|chk0_en[bank*8+:8]) ? chk0_dataK : 'z;
        assign chk1_data0=(|chk1_en[bank*8+:8]) ? chk1_dataK : 'z;
        assign chk2_data0=(|chk2_en[bank*8+:8]) ? chk2_dataK : 'z;
        assign chk3_data0=(|chk3_en[bank*8+:8]) ? chk3_dataK : 'z;
        assign chk4_data0=(|chk4_en[bank*8+:8]) ? chk4_dataK : 'z;
        assign chk5_data0=(|chk5_en[bank*8+:8]) ? chk5_dataK : 'z;
        assign chk6_data0=(|chk6_en[bank*8+:8]) ? chk6_dataK : 'z;
        assign chk7_data0=(|chk7_en[bank*8+:8]) ? chk7_dataK : 'z;
    end
  endgenerate
  assign chk0_data0=(chk0_en!=64'b0) ? 'z : chk0_data1;
  assign chk1_data0=(chk1_en!=64'b0) ? 'z : chk1_data1;
  assign chk2_data0=(chk2_en!=64'b0) ? 'z : chk2_data1;
  assign chk3_data0=(chk3_en!=64'b0) ? 'z : chk3_data1;
  assign chk4_data0=(chk4_en!=64'b0) ? 'z : chk4_data1;
  assign chk5_data0=(chk5_en!=64'b0) ? 'z : chk5_data1;
  assign chk6_data0=(chk6_en!=64'b0) ? 'z : {WIDTH{1'B0}};
  assign chk7_data0=(chk7_en!=64'b0) ? 'z : {WIDTH{1'B0}};

  assign chk0_data1=chk0_pre1 ?               chk7_data0 : 'z;
  assign chk0_data1=chk0_pre0 & ~chk0_pre1 ?  chk6_data0 : 'z;
  assign chk0_data1=~chk0_pre0 & ~chk0_pre1 ? {WIDTH{1'B0}} : 'z;

  assign chk1_data1=chk1_pre1 ?               chk7_data0 : 'z;
  assign chk1_data1=chk1_pre0 & ~chk1_pre1 ?  chk6_data0 : 'z;
  assign chk1_data1=~chk1_pre0 & ~chk1_pre1 ? {WIDTH{1'B0}} : 'z;

  assign chk2_data1=chk2_pre1 ?               chk7_data0 : 'z;
  assign chk2_data1=chk2_pre0 & ~chk2_pre1 ?  chk6_data0 : 'z;
  assign chk2_data1=~chk2_pre0 & ~chk2_pre1 ? {WIDTH{1'B0}} : 'z;

  assign chk3_data1=chk3_pre1 ?               chk7_data0 : 'z;
  assign chk3_data1=chk3_pre0 & ~chk3_pre1 ?  chk6_data0 : 'z;
  assign chk3_data1=~chk3_pre0 & ~chk3_pre1 ? {WIDTH{1'B0}} : 'z;

  assign chk4_data1=chk4_pre1 ?               chk7_data0 : 'z;
  assign chk4_data1=chk4_pre0 & ~chk4_pre1 ?  chk6_data0 : 'z;
  assign chk4_data1=~chk4_pre0 & ~chk4_pre1 ? {WIDTH{1'B0}} : 'z;

  assign chk5_data1=chk5_pre1 ?               chk7_data0 : 'z;
  assign chk5_data1=chk5_pre0 & ~chk5_pre1 ?  chk6_data0 : 'z;
  assign chk5_data1=~chk5_pre0 & ~chk5_pre1 ? {WIDTH{1'B0}} : 'z;

  always @* begin
      chk0_data=chk0_data0;
      chk1_data=chk1_data0;
      chk2_data=chk2_data0;
      chk3_data=chk3_data0;
      chk4_data=chk4_data0;
      chk5_data=chk5_data0;
  end
endmodule  
