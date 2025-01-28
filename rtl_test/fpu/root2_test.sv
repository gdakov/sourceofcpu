`include "../../rtl/common.sv"

module root2_test();
  reg clk=0;
  reg rst=1;
  reg [23:0] addr;
  real my_res,my_A,my_B;
  real cor_res;
  wire [63:0] res;
  wire [80:0] result;
  reg [63:0] res_reg;
  //reg [63:0] res_reg2;
  //reg [63:0] res_reg3;
  reg [63:0] A_reg;
  //reg [63:0] A_reg2;
  //reg [63:0] A_reg3;
  //reg [63:0] B_reg;
  //reg [63:0] B_reg2;
  //reg [63:0] B_reg3;
  wire [63:0] A;
  wire [63:0] B;
  wire sub;
  wire dmatch;
  wire [16:0] expA;
  wire [16:0] expA_p;
  wire [63:-1] normA;
  wire [16:0] expB;
  wire [16:0] expB_p;
  wire [63:-1] normB;
  wire rdy; 
  wire out_en;
  
  function [6:0] fswap;
    input [63:0] fnum;
    integer k;
    for(k=0;k<64;k=k+1) fswap[k]=fnum[63-k];
  endfunction

  always #(50) clk<=~clk;
  always @(posedge clk) rst<=1'b0;
 
  assign normA=~expA[0]|~sub ? {1'b1,A[51:0],12'b0} : {2'b1,A[51:0],11'b0}; 
  assign expA=A[62:52];
  assign expA_p={1'b0,A[62],{5{~A[62]}},A[61:52]};
  assign normB={1'b1,B[51:0],12'b0}; 
  assign expB=B[62:52];
  assign expB_p={1'b0,B[62],{5{~B[62]}},B[61:52]};

  rt2_fp root2_mod(
  .clk(clk),
  .rst(rst),
  .rdy(rdy),
  .start_process(rdy),
  .step_cnt(5'd13),
  .type(3'b0),
  .rmode(3'd2),
  .is_root(sub),
  .normA(normA),
  .expA(expA_p),
  .nsignA(~A[63]),
  .normB(normB),
  .expB(expB_p),
  .nsignB(~B[63]),
  .result(result),
  .out_en(out_en),
  .out_can(1'b1)
  );

  root2_test_data mem_mod(
  clk,
  rst,
  rdy,
  addr,
  A,B,res,sub);

  assign dmatch={result[63],result[80],result[61:0]}==res_reg[63:0];

  always @(posedge clk) begin
    if (rst)addr<=24'b0;
    else if (rdy) addr<=addr+1;
    if (rdy) res_reg<=res;
//    res_reg2<=res_reg;
//    res_reg3<=res_reg2;
    if (rdy) A_reg<=A;
//    A_reg2<=A_reg;
//    A_reg3<=A_reg2;
//    B_reg<=B;
//    B_reg2<=B_reg;
//    B_reg3<=B_reg2;
   if (addr>0&&~dmatch&&out_en) $finish();
  end

  always @* begin
    cor_res=fswap(res_reg);
    my_res=fswap(result);
    my_A=fswap(A_reg);
    //my_B=fswap(B_reg);
  end
endmodule

module root2_test_data(
  clk,
  rst,
  read_clkEn,
  addr,
  A,B,res,sub);
  input clk;
  input rst;
  input read_clkEn;
  input [23:0] addr;
  output [63:0] A;
  output [63:0] B;
  output [63:0] res;
  output sub;

  reg [3*64:0] ram[2048*1024-1:0];
  reg [23:0] addr_reg;

  assign {sub,res,B,A}=ram[addr_reg];
  always @(posedge clk) begin
    if (rst) addr_reg<=0;
    else if (read_clkEn) addr_reg<=addr;
  end
  initial
    $readmemh("/home/goran/heptane/test/fpu/root2_16.memh",ram);
endmodule
