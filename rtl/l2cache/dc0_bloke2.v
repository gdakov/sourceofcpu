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



module dcache2_block2(
  clk,
  rst,
  read_en,read_odd,
  read_data,read_dataX,
  read_dataPTR,read_dataPTRx,
  write0_clkEn,write0_passthrough,
  write_addrE0, write_hitE0,
  write_addrO0, write_hitO0,
  write_bankEn0,write_pbit0, 
  write_begin0,write_end0,
  write_bBen0,write_enBen0,
  write_odd0,write_split0,
  write_data0,
  write_d128_0,
  write1_clkEn,write1_passthrough,
  write_addrE1, write_hitE1,
  write_addrO1, write_hitO1,
  write_bankEn1,write_pbit1,
  write_begin1,write_end1,
  write_bBen1,write_enBen1,
  write_odd1,write_split1,
  write_data1,
  write_d128_1,
  busIns_data,
  busIns_dataPTR,
  insBus_A,
  insBus_B,
//  ins_hit,
  insert,
  insert_excl,insert_dirty,insert_dupl,
  hit_LRU,read_LRU,hit_any,immoral_some,read_dir,read_excl,read_expAddrOut,
  read_expAddr_en,
  expun_cc_addr,
  expun_cc_en,
  expun_dc_addr,
  expun_dc_en
// init
  );
  localparam ADDR_WIDTH=36;
  localparam DATA_WIDTH=32;
  parameter [1:0] ID=0;
/*verilator hier_block*/ 

  input clk;
  input rst;
  input read_en; 
  input read_odd;
  output reg [32*DATA_WIDTH-1:0] read_data;
  output reg [32*DATA_WIDTH-1:0] read_dataX;
  output reg [15:0] read_dataPTR;
  output reg [15:0] read_dataPTRx;

  input write0_passthrough;
  input write1_passthrough;

  input write0_clkEn;
  input [ADDR_WIDTH-1:0] write_addrE0;
  input write_hitE0; 
  input [ADDR_WIDTH-1:0] write_addrO0;
  input write_hitO0; 
  input [31:0] write_bankEn0;
  input [4:0] write_begin0;
  input [4:0] write_end0;
  input [3:0] write_bBen0;
  input [3:0] write_enBen0;
  input [1:0] write_pbit0;
  input       write_d128_0;
  input write_odd0,write_split0;
  input [159:0] write_data0;
  input write1_clkEn;
  input [ADDR_WIDTH-1:0] write_addrE1;
  input write_hitE1; 
  input [ADDR_WIDTH-1:0] write_addrO1;
  input write_hitO1; 
  input [31:0] write_bankEn1;
  input [4:0] write_begin1;
  input [4:0] write_end1;
  input [3:0] write_bBen1;
  input [3:0] write_enBen1;
  input [1:0] write_pbit1;
  input       write_d128_1;
  input write_odd1,write_split1;
  input [159:0] write_data1;
  input [511:0] busIns_data;
  input [7:0] busIns_dataPTR;
  input insBus_A,insBus_B;
//  output ins_hit;
  input insert;
  input insert_excl;
  input insert_dirty;
  input insert_dupl;
  input [4:0] hit_LRU;
  output reg [4:0] read_LRU;
  output reg hit_any;
  output reg immoral_some;
  output reg read_dir;
  output reg read_excl;
  output reg [36:0] read_expAddrOut;
  input read_expAddr_en;
  input [36:0] expun_cc_addr;
  input expun_cc_en;
  input [36:0] expun_dc_addr;
  input expun_dc_en;

  wire [8:0] read_hit_way;
  reg [8:0] read_hit_way_reg;
  wire [8:0] read_imm_way;
  reg [8:0] read_imm_way_reg;
  wire read_hit_any;
  wire [32*DATA_WIDTH-1:0] read_dataP[8:-1];
  wire [32*DATA_WIDTH-1:0] read_dataxP[8:-1];
  wire [15:0] read_dataPtrP[8:-1];
  wire [15:0] read_dataPtrxP[8:-1];
  wire [4:0] read_LRUp[8:-1];
  reg read_en_reg,read_en_reg2,read_en_reg3;
  reg [4:0] write_begin0_reg;
  reg [4:0] write_begin1_reg;
  reg [31:0] write_bankEn0_reg;
  reg [31:0] write_bankEn1_reg;
  reg write0_clkEn_reg,write1_clkEn_reg;
  wire [1023:0] write_data;
  reg [1023:0] write_data_reg;
  wire [7+1:0] ins_hit;
  reg [159:0] write_data0_reg;
  reg [159:0] write_data1_reg;
  reg [511:0] busIns_data_reg;
  reg insBus_A_reg,insBus_B_reg;
  reg [8:0] ins_hit_reg;
  reg ins_hit_reg2;
  wire read_immoral_some;
//  reg ins_hit_reg3;
  wire [1:0] read_dirP[8:-1];
  wire [1:0] read_exclP[8:-1];
  wire [36:0] read_expAddrP[8:-1];
  reg [7:0] write_dataPTR_reg;
  reg [15:0] write_dataPTR_reg2;
  generate
      genvar k,b,q;
      for(k=0;k<8;k=k+1) begin : ways_gen
          dcache2_way #(k,ID+3)  way_mod(
          clk,
          rst,
          read_en,
          read_odd,
          read_dataP[k],
          read_dataP[k-1],
          read_dataxP[k],
          read_dataxP[k-1],
          read_dataPtrP[k],
          read_dataPtrP[k-1],
          read_dataPtrxP[k],
          read_dataPtrxP[k-1],
          read_hit_way[k],
	  read_imm_way[k],
          write0_clkEn,
          write_addrE0, write_hitE0,
          write_addrO0, write_hitO0,
          write_bankEn0,write_pbit0, 
          write_begin0,write_end0,
          write_bBen0,write_enBen0,
          write_odd0,write_split0,
	  write_d128_0,
          write1_clkEn,
          write_addrE1, write_hitE1,
          write_addrO1, write_hitO1,
          write_bankEn1,write_pbit1,
          write_begin1,write_end1,
          write_bBen1,write_enBen1,
          write_odd1,write_split1,
	  write_d128_1,
          write_data_reg,
          write_dataPTR_reg2,
          ins_hit[k],
          insert,
          insert_excl,insert_dirty,insert_dupl,
          hit_LRU,
	  read_LRUp[k],read_dirP[k],read_exclP[k],read_expAddrP[k],
	  read_LRUp[k-1],read_dirP[k-1],read_exclP[k-1],read_expAddrP[k-1],
          read_expAddr_en,
          expun_cc_addr,
          expun_cc_en,
          expun_dc_addr,
          expun_dc_en
          );
      end
      for(b=0;b<32;b=b+1) begin : bank_gen
          wire [4:0] wr0;
          wire [4:0] wr1;
          for(q=0;q<5;q=q+1) begin : wroff_gen
              assign wr0[q]=((b-q)&5'h1f)==write_begin0_reg && write0_clkEn_reg && write_bankEn0_reg[b];
              assign wr1[q]=((b-q)&5'h1f)==write_begin1_reg && write1_clkEn_reg && write_bankEn1_reg[b];
              assign write_data[b*32+:32]=wr0[q] ? write_data0_reg[q*32+:32] : 32'BZ;
              assign write_data[b*32+:32]=wr1[q] ? write_data1_reg[q*32+:32] : 32'BZ;
          end
          assign  write_data[b*32+:32]=(|{wr0,wr1}) ? 32'BZ : 
            busIns_data_reg[(b%16)*32+:32];
     end
  endgenerate

  assign read_dataP[0]={1024{write0_clkEn_reg2|write1_clkEn_reg2}}&
          {write0_clkEn&write0_passthrough, write_addrE0, write_hitE0, write_addrO0, write_hitO0,
          write_bankEn0,write_pbit0, write_begin0,write_end0, write_bBen0,write_enBen0, write_odd0,write_split0, write_d128_0,
          write1_clkEn&write1_passthrough, write_addrE1, write_hitE1, write_addrO1, write_hitO1,
          write_bankEn1,write_pbit1, write_begin1,write_end1, write_bBen1,write_enBen1,write_odd1,write_split1,  write_d128_1,
          '0};

  assign read_dataP[-1][511:0]=512'b0;
  assign read_dataP[-1][1023:512]=512'b0;
  assign read_dataxP[-1][511:0]=512'b0;
  assign read_dataxP[-1][1023:512]=512'b0;
  assign read_LRUp[-1]={ID,3'b0};
  assign read_dirP[-1]=2'b0;
  assign read_exclP[-1]=2'b0;
  assign read_expAddrP[-1]=37'b0;
  assign read_hit_any=|read_hit_way_reg;
  assign read_immoral_some=|read_imm_way_reg;

  always @(posedge clk) begin
      if (rst) begin
          write_data0_reg<=160'b0;
          write_data1_reg<=160'b0;
          write_data_reg<=1024'b0;
	  write_dataPTR_reg<=8'b0;
	  write_dataPTR_reg2<=16'b0;
          busIns_data_reg<=512'b0;
          insBus_A_reg<=1'b0;
          insBus_B_reg<=1'b0;
          write_begin0_reg<=5'd0;
          write_begin1_reg<=5'd0;
          write0_clkEn_reg<=1'b0;
          write1_clkEn_reg<=1'b0;
          write_bankEn0_reg<=32'b0;
          write_bankEn1_reg<=32'b0;
          
        //  read_hit_any<=1'b0;
          read_data<=1024'b0;
          read_dataX<=1024'b0;
          read_LRU<=5'h0;
          read_en_reg<=1'b0;
          read_en_reg2<=1'b0;
          read_en_reg3<=1'b0;
          ins_hit_reg<=9'b0;
          ins_hit_reg2<=1'b0;
  //        ins_hit_reg3<=1'b0;
          read_hit_way_reg<=9'b0;
          hit_any<=1'b0;
          immoral_some<=1'b0;
          read_dir<=1'b0;
          read_excl<=1'b0;
          read_expAddrOut<=37'b0;
          read_imm_way_reg<=9'b0;
      end else begin
          write_data0_reg<=write_data0;
          write_data1_reg<=write_data1;
          if (~insBus_B_reg) write_data_reg[511:0]<=write_data[511:0];
          if (~insBus_A_reg) write_data_reg[1023:512]<=write_data[1023:512];
          if (~insBus_B_reg) write_dataPTR_reg2[7:0]<=write_dataPTR_reg;
          if (~insBus_A_reg) write_dataPTR_reg2[15:8]<=write_dataPTR_reg;
	  write_dataPTR_reg<=busIns_dataPTR;
          busIns_data_reg<=busIns_data;
          insBus_A_reg<=insBus_A;
          insBus_B_reg<=insBus_B;
          write_begin0_reg<=write_begin0;
          write_begin1_reg<=write_begin1;
 //         write0_clkEn_reg<=write0_clkEn;
 //         write1_clkEn_reg<=write1_clkEn;
          write_bankEn0_reg<=write_bankEn0;
          write_bankEn1_reg<=write_bankEn1;
          
        //  read_hit_any<=(|read_hit_way) && ~ins_hit_reg;
          read_data<=~read_dataP[8];
          read_dataX<=~read_dataxP[8];
          read_LRU<=~read_LRUp[8];
          read_en_reg<=read_en;
          read_en_reg2<=read_en_reg;
          read_en_reg3<=read_en_reg2;
          ins_hit_reg<=ins_hit;
          ins_hit_reg2<=|ins_hit_reg;
    //      ins_hit_reg3<=ins_hit_reg2;
          read_hit_way_reg<=read_hit_way;
          read_imm_way_reg<=read_imm_way;
          hit_any<=(|read_hit_way_reg);
          immoral_some<=(|read_imm_way_reg);
          read_dir<=~read_dirP[8][0];
          read_excl<=~read_exclP[8][0];
          read_expAddrOut<=~read_expAddrP[8];
      end
  end
endmodule
