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

//main modules in file: rat

module rat_buf(
  clk,
  rst,
  read_clkEn,
  //from here addr is retirement register
  read0_addr,read0_data,read0_retired,read0_fun,
  read1_addr,read1_data,read1_retired,read1_fun,
  read2_addr,read2_data,read2_retired,read2_fun,
  read3_addr,read3_data,read3_retired,read3_fun,
  read4_addr,read4_data,read4_retired,read4_fun,
  read5_addr,read5_data,read5_retired,read5_fun,
  read6_addr,read6_data,read6_retired,read6_fun,
  read7_addr,read7_data,read7_retired,read7_fun,
  read8_addr,read8_data,read8_retired,read8_fun,

  writeNew0_addr,writeNew0_data,writeNew0_fun,writeNew0_wen,
  writeNew1_addr,writeNew1_data,writeNew1_fun,writeNew1_wen,
  writeNew2_addr,writeNew2_data,writeNew2_fun,writeNew2_wen,
  writeNew3_addr,writeNew3_data,writeNew3_fun,writeNew3_wen,
  writeNew4_addr,writeNew4_data,writeNew4_fun,writeNew4_wen,
  writeNew5_addr,writeNew5_data,writeNew5_fun,writeNew5_wen,
  writeNew6_addr,writeNew6_data,writeNew6_fun,writeNew6_wen,
  writeNew7_addr,writeNew7_data,writeNew7_fun,writeNew7_wen,
  writeNew8_addr,writeNew8_data,writeNew8_fun,writeNew8_wen,
//from here addr is free register
  writeRet0_addr,writeRet0_wen,
  writeRet1_addr,writeRet1_wen,
  writeRet2_addr,writeRet2_wen,
  writeRet3_addr,writeRet3_wen,
  writeRet4_addr,writeRet4_wen,
  writeRet5_addr,writeRet5_wen,
  writeRet6_addr,writeRet6_wen,
  writeRet7_addr,writeRet7_wen,
  writeRet8_addr,writeRet8_wen,
  retireAll,retireAll_thread,
  read_thread,write_thread,ret_thread
  );

//override index with physical register number
  parameter INDEX=0;
  localparam RAT_ADDR_WIDTH=3;
  localparam ROB_ADDR_WIDTH=`reg_addr_width;
  localparam FN_WIDTH=10;

  input clk;
  input rst;

  input read_clkEn;

  input [RAT_ADDR_WIDTH-1:0] read0_addr;
  output [ROB_ADDR_WIDTH-1:0] read0_data;
  output read0_retired;
  output [FN_WIDTH-1:0] read0_fun;
  input [RAT_ADDR_WIDTH-1:0] read1_addr;
  output [ROB_ADDR_WIDTH-1:0] read1_data;
  output read1_retired;
  output [FN_WIDTH-1:0] read1_fun;
  input [RAT_ADDR_WIDTH-1:0] read2_addr;
  output [ROB_ADDR_WIDTH-1:0] read2_data;
  output read2_retired;
  output [FN_WIDTH-1:0] read2_fun;
  input [RAT_ADDR_WIDTH-1:0] read3_addr;
  output [ROB_ADDR_WIDTH-1:0] read3_data;
  output read3_retired;
  output [FN_WIDTH-1:0] read3_fun;
  input [RAT_ADDR_WIDTH-1:0] read4_addr;
  output [ROB_ADDR_WIDTH-1:0] read4_data;
  output read4_retired;
  output [FN_WIDTH-1:0] read4_fun;
  input [RAT_ADDR_WIDTH-1:0] read5_addr;
  output [ROB_ADDR_WIDTH-1:0] read5_data;
  output read5_retired;
  output [FN_WIDTH-1:0] read5_fun;
  input [RAT_ADDR_WIDTH-1:0] read6_addr;
  output [ROB_ADDR_WIDTH-1:0] read6_data;
  output read6_retired;
  output [FN_WIDTH-1:0] read6_fun;
  input [RAT_ADDR_WIDTH-1:0] read7_addr;
  output [ROB_ADDR_WIDTH-1:0] read7_data;
  output read7_retired;
  output [FN_WIDTH-1:0] read7_fun;
  input [RAT_ADDR_WIDTH-1:0] read8_addr;
  output [ROB_ADDR_WIDTH-1:0] read8_data;
  output read8_retired;
  output [FN_WIDTH-1:0] read8_fun;

  input [RAT_ADDR_WIDTH-1:0] writeNew0_addr;
  input [ROB_ADDR_WIDTH-1:0] writeNew0_data;
  input [FN_WIDTH-1:0] writeNew0_fun;
  input writeNew0_wen;
  input [RAT_ADDR_WIDTH-1:0] writeNew1_addr;
  input [ROB_ADDR_WIDTH-1:0] writeNew1_data;
  input [FN_WIDTH-1:0] writeNew1_fun;
  input writeNew1_wen;
  input [RAT_ADDR_WIDTH-1:0] writeNew2_addr;
  input [ROB_ADDR_WIDTH-1:0] writeNew2_data;
  input [FN_WIDTH-1:0] writeNew2_fun;
  input writeNew2_wen;
  input [RAT_ADDR_WIDTH-1:0] writeNew3_addr;
  input [ROB_ADDR_WIDTH-1:0] writeNew3_data;
  input [FN_WIDTH-1:0] writeNew3_fun;
  input writeNew3_wen;
  input [RAT_ADDR_WIDTH-1:0] writeNew4_addr;
  input [ROB_ADDR_WIDTH-1:0] writeNew4_data;
  input [FN_WIDTH-1:0] writeNew4_fun;
  input writeNew4_wen;
  input [RAT_ADDR_WIDTH-1:0] writeNew5_addr;
  input [ROB_ADDR_WIDTH-1:0] writeNew5_data;
  input [FN_WIDTH-1:0] writeNew5_fun;
  input writeNew5_wen;
  input [RAT_ADDR_WIDTH-1:0] writeNew6_addr;
  input [ROB_ADDR_WIDTH-1:0] writeNew6_data;
  input [FN_WIDTH-1:0] writeNew6_fun;
  input writeNew6_wen;
  input [RAT_ADDR_WIDTH-1:0] writeNew7_addr;
  input [ROB_ADDR_WIDTH-1:0] writeNew7_data;
  input [FN_WIDTH-1:0] writeNew7_fun;
  input writeNew7_wen;
  input [RAT_ADDR_WIDTH-1:0] writeNew8_addr;
  input [ROB_ADDR_WIDTH-1:0] writeNew8_data;
  input [FN_WIDTH-1:0] writeNew8_fun;
  input writeNew8_wen;

  input [ROB_ADDR_WIDTH-1:0] writeRet0_addr;
  input writeRet0_wen;
  input [ROB_ADDR_WIDTH-1:0] writeRet1_addr;
  input writeRet1_wen;
  input [ROB_ADDR_WIDTH-1:0] writeRet2_addr;
  input writeRet2_wen;
  input [ROB_ADDR_WIDTH-1:0] writeRet3_addr;
  input writeRet3_wen;
  input [ROB_ADDR_WIDTH-1:0] writeRet4_addr;
  input writeRet4_wen;
  input [ROB_ADDR_WIDTH-1:0] writeRet5_addr;
  input writeRet5_wen;
  input [ROB_ADDR_WIDTH-1:0] writeRet6_addr;
  input writeRet6_wen;
  input [ROB_ADDR_WIDTH-1:0] writeRet7_addr;
  input writeRet7_wen;
  input [ROB_ADDR_WIDTH-1:0] writeRet8_addr;
  input writeRet8_wen;

  input retireAll;
  input retireAll_thread;
  
  input read_thread;
  input write_thread;
  input ret_thread;
  
  reg [ROB_ADDR_WIDTH-1:0] robAddr[1:0];
  reg retired[1:0];
  reg [FN_WIDTH-1:0] funit[1:0];

  wire [ROB_ADDR_WIDTH-1:0] robAddr_rd;
  wire [ROB_ADDR_WIDTH-1:0] robAddr_ret;
  wire retired_rd;
  wire [FN_WIDTH-1:0] funit_rd;
  
  wire match_new0;  
  wire match_new1;  
  wire match_new2;  
  wire match_new3;  
  wire match_new4;  
  wire match_new5;
  wire match_new6;
  wire match_new7;
  wire match_new8;

  wire match_new;

  wire match_ret0;  
  wire match_ret1;  
  wire match_ret2;  
  wire match_ret3;  
  wire match_ret4;  
  wire match_ret5;
  wire match_ret6;
  wire match_ret7;
  wire match_ret8;

  wire match_ret;

  wire [ROB_ADDR_WIDTH-1:0] robAddr_d;

  wire [FN_WIDTH-1:0] funit_d;
  
  wire retired_d[1:0];

  wire match_rd0;
  wire match_rd1;
  wire match_rd2;
  wire match_rd3;
  wire match_rd4;
  wire match_rd5;
  wire match_rd6;
  wire match_rd7;
  wire match_rd8;
  
  assign match_new0=(writeNew0_addr==INDEX) & writeNew0_wen;    
  assign match_new1=(writeNew1_addr==INDEX) & writeNew1_wen;    
  assign match_new2=(writeNew2_addr==INDEX) & writeNew2_wen;    
  assign match_new3=(writeNew3_addr==INDEX) & writeNew3_wen;    
  assign match_new4=(writeNew4_addr==INDEX) & writeNew4_wen;    
  assign match_new5=(writeNew5_addr==INDEX) & writeNew5_wen;    
  assign match_new6=(writeNew6_addr==INDEX) & writeNew6_wen;    
  assign match_new7=(writeNew7_addr==INDEX) & writeNew7_wen;    
  assign match_new8=(writeNew8_addr==INDEX) & writeNew8_wen;    

  assign match_new=|{match_new0,match_new1,match_new2,match_new3,match_new4,match_new5
    ,match_new6,match_new7,match_new8};

  assign match_ret0=(~writeRet0_addr==robAddr_ret) & writeRet0_wen;    
  assign match_ret1=(~writeRet1_addr==robAddr_ret) & writeRet1_wen;    
  assign match_ret2=(~writeRet2_addr==robAddr_ret) & writeRet2_wen;    
  assign match_ret3=(~writeRet3_addr==robAddr_ret) & writeRet3_wen;    
  assign match_ret4=(~writeRet4_addr==robAddr_ret) & writeRet4_wen;    
  assign match_ret5=(~writeRet5_addr==robAddr_ret) & writeRet5_wen;    
  assign match_ret6=(~writeRet6_addr==robAddr_ret) & writeRet6_wen;    
  assign match_ret7=(~writeRet7_addr==robAddr_ret) & writeRet7_wen;    
  assign match_ret8=(~writeRet8_addr==robAddr_ret) & writeRet8_wen;    

  assign match_ret=|{match_ret0,match_ret1,match_ret2,match_ret3,
    match_ret4,match_ret5,match_ret6,match_ret7,match_ret8};

  
  assign match_rd0=read0_addr==INDEX;
  assign match_rd1=read1_addr==INDEX;
  assign match_rd2=read2_addr==INDEX;
  assign match_rd3=read3_addr==INDEX;
  assign match_rd4=read4_addr==INDEX;
  assign match_rd5=read5_addr==INDEX;
  assign match_rd6=read6_addr==INDEX;
  assign match_rd7=read7_addr==INDEX;
  assign match_rd8=read8_addr==INDEX;


  assign robAddr_d=(match_new0 & ~rst) ? ~writeNew0_data : 'z;
  assign robAddr_d=(match_new1 & ~rst) ? ~writeNew1_data : 'z;
  assign robAddr_d=(match_new2 & ~rst) ? ~writeNew2_data : 'z;
  assign robAddr_d=(match_new3 & ~rst) ? ~writeNew3_data : 'z;
  assign robAddr_d=(match_new4 & ~rst) ? ~writeNew4_data : 'z;
  assign robAddr_d=(match_new5 & ~rst) ? ~writeNew5_data : 'z;
  assign robAddr_d=(match_new6 & ~rst) ? ~writeNew6_data : 'z;
  assign robAddr_d=(match_new7 & ~rst) ? ~writeNew7_data : 'z;
  assign robAddr_d=(match_new8 & ~rst) ? ~writeNew8_data : 'z;

  assign robAddr_d=(rst | ~match_new) ? {ROB_ADDR_WIDTH{1'b1}} : 'z;

  assign retired_d[0]=~(match_ret & ~ret_thread & ~(match_new & read_clkEn) || rst || retireAll & ~retireAll_thread); 
  assign retired_d[1]=~(match_ret & ret_thread & ~(match_new & read_clkEn) || rst || retireAll & retireAll_thread); 

  assign funit_d=(match_new0 & ~rst) ? ~writeNew0_fun : 'z;
  assign funit_d=(match_new1 & ~rst) ? ~writeNew1_fun : 'z;
  assign funit_d=(match_new2 & ~rst) ? ~writeNew2_fun : 'z;
  assign funit_d=(match_new3 & ~rst) ? ~writeNew3_fun : 'z;
  assign funit_d=(match_new4 & ~rst) ? ~writeNew4_fun : 'z;
  assign funit_d=(match_new5 & ~rst) ? ~writeNew5_fun : 'z;
  assign funit_d=(match_new6 & ~rst) ? ~writeNew6_fun : 'z;
  assign funit_d=(match_new7 & ~rst) ? ~writeNew7_fun : 'z;
  assign funit_d=(match_new8 & ~rst) ? ~writeNew8_fun : 'z;

  assign funit_d=(rst | ~match_new) ? 10'b0111111111 : 'z;

  assign read0_data=match_rd0 ? ~robAddr_rd : 'z;  
  assign read1_data=match_rd1 ? ~robAddr_rd : 'z;  
  assign read2_data=match_rd2 ? ~robAddr_rd : 'z;  
  assign read3_data=match_rd3 ? ~robAddr_rd : 'z;  
  assign read4_data=match_rd4 ? ~robAddr_rd : 'z;  
  assign read5_data=match_rd5 ? ~robAddr_rd : 'z;  
  assign read6_data=match_rd6 ? ~robAddr_rd : 'z;  
  assign read7_data=match_rd7 ? ~robAddr_rd : 'z;  
  assign read8_data=match_rd8 ? ~robAddr_rd : 'z;  

  assign read0_fun=match_rd0 ? ~funit_rd : 'z;  
  assign read1_fun=match_rd1 ? ~funit_rd : 'z;  
  assign read2_fun=match_rd2 ? ~funit_rd : 'z;  
  assign read3_fun=match_rd3 ? ~funit_rd : 'z;  
  assign read4_fun=match_rd4 ? ~funit_rd : 'z;  
  assign read5_fun=match_rd5 ? ~funit_rd : 'z;  
  assign read6_fun=match_rd6 ? ~funit_rd : 'z;  
  assign read7_fun=match_rd7 ? ~funit_rd : 'z;  
  assign read8_fun=match_rd8 ? ~funit_rd : 'z;  

  assign read0_retired=match_rd0 ? ~retired_rd : 1'bz;  
  assign read1_retired=match_rd1 ? ~retired_rd : 1'bz;  
  assign read2_retired=match_rd2 ? ~retired_rd : 1'bz;  
  assign read3_retired=match_rd3 ? ~retired_rd : 1'bz;  
  assign read4_retired=match_rd4 ? ~retired_rd : 1'bz;  
  assign read5_retired=match_rd5 ? ~retired_rd : 1'bz;  
  assign read6_retired=match_rd6 ? ~retired_rd : 1'bz;  
  assign read7_retired=match_rd7 ? ~retired_rd : 1'bz;  
  assign read8_retired=match_rd8 ? ~retired_rd : 1'bz;
  
  assign robAddr_rd=robAddr[read_thread];
  assign robAddr_ret=robAddr[ret_thread];  
  assign funit_rd=funit[read_thread];  
  assign retired_rd=retired[read_thread];  

  always @(posedge clk)
    begin
      if (rst) begin
          robAddr[0]<=9'h1ff;
          robAddr[1]<=9'h1ff;
          funit[0]<=10'b0111111111;
          funit[1]<=10'b0111111111;
      end else begin
          if (~write_thread & match_new) robAddr[0]<=robAddr_d;
          if ( write_thread & match_new) robAddr[1]<=robAddr_d;
          if (~write_thread & match_new) funit[0]<=funit_d;
          if ( write_thread & match_new) funit[1]<=funit_d;
      end
      if (match_ret & ~ret_thread || match_new & ~write_thread 
	    || retireAll & ~retireAll_thread || rst) retired[0]<=retired_d[0];
      if (match_ret & ret_thread || match_new & write_thread 
	    || retireAll & retireAll_thread || rst) retired[1]<=retired_d[1];
    end   
endmodule




module rat_dep(
  addr,
  data,
  retired,
  funit,
  isDep,
  rs0i0_index,rs0i1_index,rs0i2_index,
  rs1i0_index,rs1i1_index,rs1i2_index,
  rs2i0_index,rs2i1_index,rs2i2_index,
  newR0,newR1,newR2,newR3,newR4,newR5,newR6,newR7,newR8,
  newU0,newU1,newU2,newU3,newU4,newU5,newU6,newU7,newU8
  );


  localparam RAT_ADDR_WIDTH=6;
  localparam ROB_ADDR_WIDTH=`reg_addr_width;
  localparam FN_WIDTH=10;

  input [RAT_ADDR_WIDTH-1:0] addr;
  output [ROB_ADDR_WIDTH-1:0] data;
  output retired;
  output [FN_WIDTH-1:0] funit;
  output isDep;
  
  input [3:0] rs0i0_index;
  input [3:0] rs0i1_index;
  input [3:0] rs0i2_index;
  input [3:0] rs1i0_index;
  input [3:0] rs1i1_index;
  input [3:0] rs1i2_index;
  input [3:0] rs2i0_index;
  input [3:0] rs2i1_index;
  input [3:0] rs2i2_index;

  input [ROB_ADDR_WIDTH-1:0] newR0;
  input [ROB_ADDR_WIDTH-1:0] newR1;
  input [ROB_ADDR_WIDTH-1:0] newR2;
  input [ROB_ADDR_WIDTH-1:0] newR3;
  input [ROB_ADDR_WIDTH-1:0] newR4;
  input [ROB_ADDR_WIDTH-1:0] newR5;
  input [ROB_ADDR_WIDTH-1:0] newR6;
  input [ROB_ADDR_WIDTH-1:0] newR7;
  input [ROB_ADDR_WIDTH-1:0] newR8;

  input [FN_WIDTH-1:0] newU0;
  input [FN_WIDTH-1:0] newU1;
  input [FN_WIDTH-1:0] newU2;
  input [FN_WIDTH-1:0] newU3;
  input [FN_WIDTH-1:0] newU4;
  input [FN_WIDTH-1:0] newU5;
  input [FN_WIDTH-1:0] newU6;
  input [FN_WIDTH-1:0] newU7;
  input [FN_WIDTH-1:0] newU8;


  assign data=(addr=={2'b11,rs0i0_index})? newR0 : 'z;
  assign data=(addr=={2'b11,rs0i1_index})? newR1 : 'z;
  assign data=(addr=={2'b11,rs0i2_index})? newR2 : 'z;
  assign data=(addr=={2'b11,rs1i0_index})? newR3 : 'z;
  assign data=(addr=={2'b11,rs1i1_index})? newR4 : 'z;
  assign data=(addr=={2'b11,rs1i2_index})? newR5 : 'z;
  assign data=(addr=={2'b11,rs2i0_index})? newR6 : 'z;
  assign data=(addr=={2'b11,rs2i1_index})? newR7 : 'z;
  assign data=(addr=={2'b11,rs2i2_index})? newR8 : 'z;

  assign retired=addr[5:4]==2'b11 ? 1'b0 : 1'bz;
  assign isDep=addr[5:4]==2'b11;

  assign funit=(addr=={2'b11,rs0i0_index})? newU0 : 'z;
  assign funit=(addr=={2'b11,rs0i1_index})? newU1 : 'z;
  assign funit=(addr=={2'b11,rs0i2_index})? newU2 : 'z;
  assign funit=(addr=={2'b11,rs1i0_index})? newU3 : 'z;
  assign funit=(addr=={2'b11,rs1i1_index})? newU4 : 'z;
  assign funit=(addr=={2'b11,rs1i2_index})? newU5 : 'z;
  assign funit=(addr=={2'b11,rs2i0_index})? newU6 : 'z;
  assign funit=(addr=={2'b11,rs2i1_index})? newU7 : 'z;
  assign funit=(addr=={2'b11,rs2i2_index})? newU8 : 'z;
  
endmodule





module rat(
  clk,
  rst,
  read_clkEn,
  newR0,newR1,newR2,newR3,newR4,newR5,newR6,newR7,newR8,
  newU0,newU1,newU2,newU3,newU4,newU5,newU6,newU7,newU8,
  //from here addr is retirement register
  read0_addr,read0_data,read0_retired,read0_isDep,read0_fun,
  read1_addr,read1_data,read1_retired,read1_isDep,read1_fun,
  read2_addr,read2_data,read2_retired,read2_isDep,read2_fun,
  read3_addr,read3_data,read3_retired,read3_isDep,read3_fun,
  read4_addr,read4_data,read4_retired,read4_isDep,read4_fun,
  read5_addr,read5_data,read5_retired,read5_isDep,read5_fun,
  read6_addr,read6_data,read6_retired,read6_isDep,read6_fun,
  read7_addr,read7_data,read7_retired,read7_isDep,read7_fun,
  read8_addr,read8_data,read8_retired,read8_isDep,read8_fun,

  writeNew0_addr,writeNew0_wen,
  writeNew1_addr,writeNew1_wen,
  writeNew2_addr,writeNew2_wen,
  writeNew3_addr,writeNew3_wen,
  writeNew4_addr,writeNew4_wen,
  writeNew5_addr,writeNew5_wen,
  writeNew6_addr,writeNew6_wen,
  writeNew7_addr,writeNew7_wen,
  writeNew8_addr,writeNew8_wen,
//from here addr is free register
  writeRet0_addr,writeRet0_wen,
  writeRet1_addr,writeRet1_wen,
  writeRet2_addr,writeRet2_wen,
  writeRet3_addr,writeRet3_wen,
  writeRet4_addr,writeRet4_wen,
  writeRet5_addr,writeRet5_wen,
  writeRet6_addr,writeRet6_wen,
  writeRet7_addr,writeRet7_wen,
  writeRet8_addr,writeRet8_wen,
  retireAll,retireAll_thread,

  rs0i0_index,rs0i1_index,rs0i2_index,
  rs1i0_index,rs1i1_index,rs1i2_index,
  rs2i0_index,rs2i1_index,rs2i2_index,
  read_thread,ret_thread
  );

  localparam RAT_ADDR_WIDTH=6;
  localparam ROB_ADDR_WIDTH=`reg_addr_width;
//  localparam BUF_COUNT=`rat_count;
  localparam FN_WIDTH=10;
  parameter [0:0] EXTRA=1'b0;
  input clk;
  input rst;
  input read_clkEn;

  input [ROB_ADDR_WIDTH-1:0] newR0;
  input [ROB_ADDR_WIDTH-1:0] newR1;
  input [ROB_ADDR_WIDTH-1:0] newR2;
  input [ROB_ADDR_WIDTH-1:0] newR3;
  input [ROB_ADDR_WIDTH-1:0] newR4;
  input [ROB_ADDR_WIDTH-1:0] newR5;
  input [ROB_ADDR_WIDTH-1:0] newR6;
  input [ROB_ADDR_WIDTH-1:0] newR7;
  input [ROB_ADDR_WIDTH-1:0] newR8;

  input [FN_WIDTH-1:0] newU0;
  input [FN_WIDTH-1:0] newU1;
  input [FN_WIDTH-1:0] newU2;
  input [FN_WIDTH-1:0] newU3;
  input [FN_WIDTH-1:0] newU4;
  input [FN_WIDTH-1:0] newU5;
  input [FN_WIDTH-1:0] newU6;
  input [FN_WIDTH-1:0] newU7;
  input [FN_WIDTH-1:0] newU8;

  input [RAT_ADDR_WIDTH-1:0] read0_addr;
  output [ROB_ADDR_WIDTH-1:0] read0_data;
  output read0_retired;
  output read0_isDep;
  output [FN_WIDTH-1:0] read0_fun;
  input [RAT_ADDR_WIDTH-1:0] read1_addr;
  output [ROB_ADDR_WIDTH-1:0] read1_data;
  output read1_retired;
  output read1_isDep;
  output [FN_WIDTH-1:0] read1_fun;
  input [RAT_ADDR_WIDTH-1:0] read2_addr;
  output [ROB_ADDR_WIDTH-1:0] read2_data;
  output read2_retired;
  output read2_isDep;
  output [FN_WIDTH-1:0] read2_fun;
  input [RAT_ADDR_WIDTH-1:0] read3_addr;
  output [ROB_ADDR_WIDTH-1:0] read3_data;
  output read3_retired;
  output read3_isDep;
  output [FN_WIDTH-1:0] read3_fun;
  input [RAT_ADDR_WIDTH-1:0] read4_addr;
  output [ROB_ADDR_WIDTH-1:0] read4_data;
  output read4_retired;
  output read4_isDep;
  output [FN_WIDTH-1:0] read4_fun;
  input [RAT_ADDR_WIDTH-1:0] read5_addr;
  output [ROB_ADDR_WIDTH-1:0] read5_data;
  output read5_retired;
  output read5_isDep;
  output [FN_WIDTH-1:0] read5_fun;
  input [RAT_ADDR_WIDTH-1:0] read6_addr;
  output [ROB_ADDR_WIDTH-1:0] read6_data;
  output read6_retired;
  output read6_isDep;
  output [FN_WIDTH-1:0] read6_fun;
  input [RAT_ADDR_WIDTH-1:0] read7_addr;
  output [ROB_ADDR_WIDTH-1:0] read7_data;
  output read7_retired;
  output read7_isDep;
  output [FN_WIDTH-1:0] read7_fun;
  input [RAT_ADDR_WIDTH-1:0] read8_addr;
  output [ROB_ADDR_WIDTH-1:0] read8_data;
  output read8_retired;
  output read8_isDep;
  output [FN_WIDTH-1:0] read8_fun;

  input [RAT_ADDR_WIDTH-1:0] writeNew0_addr;
  input writeNew0_wen;
  input [RAT_ADDR_WIDTH-1:0] writeNew1_addr;
  input writeNew1_wen;
  input [RAT_ADDR_WIDTH-1:0] writeNew2_addr;
  input writeNew2_wen;
  input [RAT_ADDR_WIDTH-1:0] writeNew3_addr;
  input writeNew3_wen;
  input [RAT_ADDR_WIDTH-1:0] writeNew4_addr;
  input writeNew4_wen;
  input [RAT_ADDR_WIDTH-1:0] writeNew5_addr;
  input writeNew5_wen;
  input [RAT_ADDR_WIDTH-1:0] writeNew6_addr;
  input writeNew6_wen;
  input [RAT_ADDR_WIDTH-1:0] writeNew7_addr;
  input writeNew7_wen;
  input [RAT_ADDR_WIDTH-1:0] writeNew8_addr;
  input writeNew8_wen;

  input [ROB_ADDR_WIDTH-1:0] writeRet0_addr;
  input writeRet0_wen;
  input [ROB_ADDR_WIDTH-1:0] writeRet1_addr;
  input writeRet1_wen;
  input [ROB_ADDR_WIDTH-1:0] writeRet2_addr;
  input writeRet2_wen;
  input [ROB_ADDR_WIDTH-1:0] writeRet3_addr;
  input writeRet3_wen;
  input [ROB_ADDR_WIDTH-1:0] writeRet4_addr;
  input writeRet4_wen;
  input [ROB_ADDR_WIDTH-1:0] writeRet5_addr;
  input writeRet5_wen;
  input [ROB_ADDR_WIDTH-1:0] writeRet6_addr;
  input writeRet6_wen;
  input [ROB_ADDR_WIDTH-1:0] writeRet7_addr;
  input writeRet7_wen;
  input [ROB_ADDR_WIDTH-1:0] writeRet8_addr;
  input writeRet8_wen;

  input retireAll;
  input retireAll_thread;

  input [3:0] rs0i0_index;
  input [3:0] rs0i1_index;
  input [3:0] rs0i2_index;
  input [3:0] rs1i0_index;
  input [3:0] rs1i1_index;
  input [3:0] rs1i2_index;
  input [3:0] rs2i0_index;
  input [3:0] rs2i1_index;
  input [3:0] rs2i2_index;
  input read_thread;
  input ret_thread;

  reg [RAT_ADDR_WIDTH-1:0] read_addr_reg[8:0];



  genvar i,k,l;


  wire [8:0][ROB_ADDR_WIDTH-1:0] read_data;
  wire [8:0]read_retired;
  wire [8:0]read_isDep;
  wire [8:0][FN_WIDTH-1:0] read_fun;

  reg read_thread_reg;
  
  assign read0_data=read_data[0];
  assign read1_data=read_data[1];
  assign read2_data=read_data[2];
  assign read3_data=read_data[3];
  assign read4_data=read_data[4];
  assign read5_data=read_data[5];
  assign read6_data=read_data[6];
  assign read7_data=read_data[7];
  assign read8_data=read_data[8];

  assign read0_retired=read_retired[0];
  assign read1_retired=read_retired[1];
  assign read2_retired=read_retired[2];
  assign read3_retired=read_retired[3];
  assign read4_retired=read_retired[4];
  assign read5_retired=read_retired[5];
  assign read6_retired=read_retired[6];
  assign read7_retired=read_retired[7];
  assign read8_retired=read_retired[8];

  assign read0_isDep=read_isDep[0];
  assign read1_isDep=read_isDep[1];
  assign read2_isDep=read_isDep[2];
  assign read3_isDep=read_isDep[3];
  assign read4_isDep=read_isDep[4];
  assign read5_isDep=read_isDep[5];
  assign read6_isDep=read_isDep[6];
  assign read7_isDep=read_isDep[7];
  assign read8_isDep=read_isDep[8];

  assign read0_fun=read_fun[0];
  assign read1_fun=read_fun[1];
  assign read2_fun=read_fun[2];
  assign read3_fun=read_fun[3];
  assign read4_fun=read_fun[4];
  assign read5_fun=read_fun[5];
  assign read6_fun=read_fun[6];
  assign read7_fun=read_fun[7];
  assign read8_fun=read_fun[8];

  generate
    for (l=0;l<5;l=l+1) begin : tile_gen
        wire [8:0][ROB_ADDR_WIDTH-1:0] read_dataA;
        wire [8:0] read_retiredA;
        wire [8:0][FN_WIDTH-1:0] read_funA;
    for (i=0;i<8;i=i+1) begin : buffers
        rat_buf #(i) buf_mod(
          clk,
          rst,
          read_clkEn,

          read_addr_reg[0][2:0],read_dataA[0],read_retiredA[0],read_funA[0],
          read_addr_reg[1][2:0],read_dataA[1],read_retiredA[1],read_funA[1],
          read_addr_reg[2][2:0],read_dataA[2],read_retiredA[2],read_funA[2],
          read_addr_reg[3][2:0],read_dataA[3],read_retiredA[3],read_funA[3],
          read_addr_reg[4][2:0],read_dataA[4],read_retiredA[4],read_funA[4],
          read_addr_reg[5][2:0],read_dataA[5],read_retiredA[5],read_funA[5],
          read_addr_reg[6][2:0],read_dataA[6],read_retiredA[6],read_funA[6],
          read_addr_reg[7][2:0],read_dataA[7],read_retiredA[7],read_funA[7],
          read_addr_reg[8][2:0],read_dataA[8],read_retiredA[8],read_funA[8],

          writeNew0_addr[2:0],newR0,newU0,writeNew0_wen && writeNew0_addr[4:3]==l && read_clkEn,
          writeNew1_addr[2:0],newR1,newU1,writeNew1_wen && writeNew1_addr[4:3]==l && read_clkEn,
          writeNew2_addr[2:0],newR2,newU2,writeNew2_wen && writeNew2_addr[4:3]==l && read_clkEn,
          writeNew3_addr[2:0],newR3,newU3,writeNew3_wen && writeNew3_addr[4:3]==l && read_clkEn,
          writeNew4_addr[2:0],newR4,newU4,writeNew4_wen && writeNew4_addr[4:3]==l && read_clkEn,
          writeNew5_addr[2:0],newR5,newU5,writeNew5_wen && writeNew5_addr[4:3]==l && read_clkEn,
          writeNew6_addr[2:0],newR6,newU6,writeNew6_wen && writeNew6_addr[4:3]==l && read_clkEn,
          writeNew7_addr[2:0],newR7,newU7,writeNew7_wen && writeNew7_addr[4:3]==l && read_clkEn,
          writeNew8_addr[2:0],newR8,newU8,writeNew8_wen && writeNew8_addr[4:3]==l && read_clkEn,

          writeRet0_addr,writeRet0_wen,
          writeRet1_addr,writeRet1_wen,
          writeRet2_addr,writeRet2_wen,
          writeRet3_addr,writeRet3_wen,
          writeRet4_addr,writeRet4_wen,
          writeRet5_addr,writeRet5_wen,
          writeRet6_addr,writeRet6_wen,
          writeRet7_addr,writeRet7_wen,
          writeRet8_addr,writeRet8_wen,
          retireAll,retireAll_thread,
	  read_thread_reg,
	  read_thread_reg,
	  ret_thread
        );
    end
        assign read_data[0]=(read_addr_reg[0][5:3]==l) ? read_dataA[0] : 'z;
        assign read_data[1]=(read_addr_reg[1][5:3]==l) ? read_dataA[1] : 'z;
        assign read_data[2]=(read_addr_reg[2][5:3]==l) ? read_dataA[2] : 'z;
        assign read_data[3]=(read_addr_reg[3][5:3]==l) ? read_dataA[3] : 'z;
        assign read_data[4]=(read_addr_reg[4][5:3]==l) ? read_dataA[4] : 'z;
        assign read_data[5]=(read_addr_reg[5][5:3]==l) ? read_dataA[5] : 'z;
        assign read_data[6]=(read_addr_reg[6][5:3]==l) ? read_dataA[6] : 'z;
        assign read_data[7]=(read_addr_reg[7][5:3]==l) ? read_dataA[7] : 'z;
        assign read_data[8]=(read_addr_reg[8][5:3]==l) ? read_dataA[8] : 'z;

        assign read_retired[0]=(read_addr_reg[0][5:3]==l) ? read_retiredA[0] : 1'BZ;
        assign read_retired[1]=(read_addr_reg[1][5:3]==l) ? read_retiredA[1] : 1'BZ;
        assign read_retired[2]=(read_addr_reg[2][5:3]==l) ? read_retiredA[2] : 1'BZ;
        assign read_retired[3]=(read_addr_reg[3][5:3]==l) ? read_retiredA[3] : 1'BZ;
        assign read_retired[4]=(read_addr_reg[4][5:3]==l) ? read_retiredA[4] : 1'BZ;
        assign read_retired[5]=(read_addr_reg[5][5:3]==l) ? read_retiredA[5] : 1'BZ;
        assign read_retired[6]=(read_addr_reg[6][5:3]==l) ? read_retiredA[6] : 1'BZ;
        assign read_retired[7]=(read_addr_reg[7][5:3]==l) ? read_retiredA[7] : 1'BZ;
        assign read_retired[8]=(read_addr_reg[8][5:3]==l) ? read_retiredA[8] : 1'BZ;

        assign read_fun[0]=(read_addr_reg[0][5:3]==l) ? read_funA[0] : 'z;
        assign read_fun[1]=(read_addr_reg[1][5:3]==l) ? read_funA[1] : 'z;
        assign read_fun[2]=(read_addr_reg[2][5:3]==l) ? read_funA[2] : 'z;
        assign read_fun[3]=(read_addr_reg[3][5:3]==l) ? read_funA[3] : 'z;
        assign read_fun[4]=(read_addr_reg[4][5:3]==l) ? read_funA[4] : 'z;
        assign read_fun[5]=(read_addr_reg[5][5:3]==l) ? read_funA[5] : 'z;
        assign read_fun[6]=(read_addr_reg[6][5:3]==l) ? read_funA[6] : 'z;
        assign read_fun[7]=(read_addr_reg[7][5:3]==l) ? read_funA[7] : 'z;
        assign read_fun[8]=(read_addr_reg[8][5:3]==l) ? read_funA[8] : 'z;
        
    end
    for (k=0;k<=8;k=k+1)
      begin : deps
        rat_dep dep_mod(
          read_addr_reg[k],
          read_data[k],
          read_retired[k],
          read_fun[k],
          read_isDep[k],
          rs0i0_index,rs0i1_index,rs0i2_index,
          rs1i0_index,rs1i1_index,rs1i2_index,
          rs2i0_index,rs2i1_index,rs2i2_index,
          newR0,newR1,newR2,newR3,newR4,newR5,newR6,newR7,newR8,
          newU0,newU1,newU2,newU3,newU4,newU5,newU6,newU7,newU8
          );
      end

  endgenerate



  always @(posedge clk)
    begin
      if (rst)
        begin
          read_addr_reg[0]<={RAT_ADDR_WIDTH{1'b0}};
          read_addr_reg[1]<={RAT_ADDR_WIDTH{1'b0}};
          read_addr_reg[2]<={RAT_ADDR_WIDTH{1'b0}};
          read_addr_reg[3]<={RAT_ADDR_WIDTH{1'b0}};
          read_addr_reg[4]<={RAT_ADDR_WIDTH{1'b0}};
          read_addr_reg[5]<={RAT_ADDR_WIDTH{1'b0}};
          read_addr_reg[6]<={RAT_ADDR_WIDTH{1'b0}};
          read_addr_reg[7]<={RAT_ADDR_WIDTH{1'b0}};
          read_addr_reg[8]<={RAT_ADDR_WIDTH{1'b0}};
		  
	  read_thread_reg<=1'b0;
        end
      else if (read_clkEn)
        begin
          read_addr_reg[0]<=read0_addr;
          read_addr_reg[1]<=read1_addr;
          read_addr_reg[2]<=read2_addr;
          read_addr_reg[3]<=read3_addr;
          read_addr_reg[4]<=read4_addr;
          read_addr_reg[5]<=read5_addr;
          read_addr_reg[6]<=read6_addr;
          read_addr_reg[7]<=read7_addr;
          read_addr_reg[8]<=read8_addr;
		  
	  read_thread_reg<=read_thread;
        end
    end //always

endmodule

