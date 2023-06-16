
module alu_block();
`define aluneg
  alu alu0(clk,rst,except,except_thread,thread,operation[0],cond[0],sub[0],cary_invert[0],dataEn[0],nDataAlt[0],retData[0],retEn[0],
    val1,val2,valS,valRes,valRes_N);
  alu_shift shf0(clk,rst,except,except_thread,operation[0],cond[0],sz[0],bit_en[0],arith[0],dir[0],dataEn[0],nDataAlt[0],
    retData[0], valS, val1, val2, valRes);
`undef aluneg
  alu alu1(clk,rst,except,except_thread,thread,operation_reg[1],cond_reg[1],sub_reg[1],cary_invert_reg[1],dataEn_reg[1],
    nDataAlt_reg[1],retData[1],retEn[1], val1X,val2X,valSX,valResX,valResX_N);
  alu_shift shf1(clk,rst,except,except_thread,operation_reg[1],cond_reg[1],sz_reg[1],bit_en_reg[1],arith_reg[1],dir_reg[1],
   dataEn_reg[1],nDataAlt_reg[1], retData[1], valSX, val1X, val2X, valResX);

  always @(negedge clk) begin
    if (A_dep_alu[1]) val1X<=valRes;
    else if (A_dep_ld0[1]) val1X<=valLD0;
    else if (A_dep_ld1[1]) val1X<=valLD1;
    else val1X<=dataA1;
    if (B_dep_alu[1]) val2X<=valRes;
    else if (B_dep_ld0[1]) val2X<=valLD0;
    else if (B_dep_ld1[1]) val2X<=valLD1;
    else val2X<=dataB1;
    valSX<=S_dep_alu[1] ? retData[0][8:3] : valS;
  end
  always @(posedge clk) begin
    if (A_dep_alu[0]) val1<=valResX;
    else if (A_dep_ld0[0]) val1<=valLD0;
    else if (A_dep_ld1[0]) val1<=valLD1;
    else val1<=dataA0;
    if (B_dep_alu[0]) val2<=valResX;
    else if (B_dep_ld0[0]) val2<=valLD0;
    else if (B_dep_ld1[0]) val2<=valLD1;
    else val2<=dataB0;
    valS<=S_dep_alu[0] ? retData[1][8:3] : valSX;
  end

  alu_regfile regf(
  clk,
  rst,
  stall,
  readA0_addr,dataA0,
  readA1_addr,dataA1,
  readB0_addr,dataB0,
  readB1_addr,dataB1,
  write0_addr,valResX,write0_wen,
  write1_addr,valRes,write1_wen,
  write2_addr,valLD0,write2_wen,
  write3_addr,valLD1,write3_wen);

endmodule

module alu_regfile(
  clk,
  rst,
  stall,
  readA0_addr,readA0_data,
  readA1_addr,readA1_data,
  readB0_addr,readB0_data,
  readB1_addr,readB1_data,
  write0_addr,write0_data,write0_wen,
  write1_addr,write1_data,write1_wen,
  write2_addr,write2_data,write2_wen,
  write3_addr,write3_data,write3_wen);

  input clk;
  input rst;
  input stall;
  input [4:0]   readA0_addr;
  output [64:0] readA0_data;
  input [4:0]   readA1_addr;
  output [64:0] readA1_data;
  input [4:0]   readB0_addr;
  output [64:0] readB0_data;
  input [4:0]   readB1_addr;
  output [64:0] readB1_data;
  input [4:0]   write0_addr;
  input  [64:0] write0_data;
  input         write0_wen;
  input [4:0]   write1_addr;
  input  [64:0] write1_data;
  input         write1_wen;
  input [4:0]   write2_addr;
  input  [64:0] write2_data;
  input         write2_wen;
  input [4:0]   write3_addr;
  input  [64:0] write3_data;
  input         write3_wen;

  reg [64:0] ram[19:0];

  reg [4:0] readA0_addr_reg;
  reg [4:0] readB0_addr_reg;
  
  always @(posedge clk) begin
      if (!stall) begin
          readA0_addr_reg<=readA0_addr;
          readB0_addr_reg<=readB0_addr;
      end
      if (write1_wen) ram[write1_addr]<=write1_data;
      if (write2_wen) ram[write2_addr]<=write2_data;
      if (write3_wen) ram[write3_addr]<=write3_data;
  end
  always @(negedge clk) begin
      if (!stall) begin
          readA1_addr_reg<=readA1_addr;
          readB1_addr_reg<=readB1_addr;
      end
      if (write0_wen) ram[write0_addr]<=write0_data;
  end
endmodule