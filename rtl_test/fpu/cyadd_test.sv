`include "../../rtl/common.sv"

module fcadd_test();
  reg clk=1;
  reg rst=1;
  reg [23:0] addr;
  real my_res,my_A,my_B;
  real cor_res;
  wire [63:0] res;
  wire [80:0] result;
  reg [63:0] res_reg;
  reg [63:0] res_reg2;
  reg [63:0] res_reg3;
  reg [63:0] A_reg;
  reg [63:0] A_reg2;
  reg [63:0] A_reg3;
  reg [63:0] B_reg;
  reg [63:0] B_reg2;
  reg [63:0] B_reg3;
  wire [63:0] A;
  wire [63:0] B;
  wire sub;
  wire dmatch;
  
  function [6:0] fswap;
    input [63:0] fnum;
    integer k;
    for(k=0;k<64;k=k+1) fswap[k]=fnum[63-k];
  endfunction

  always #(50) clk<=~clk;
  always @(negedge clk) rst<=1'b0;
  
  fpucadd fmul_mod(
  .clk(clk),
  .rst(rst),
  .A({A[62],16'b0,A[63],~A[62],A[61:0]}),
  .B({B[62],16'b0,B[63],~B[62],B[61:0]}),
  .and1(1'b0),
  .or1(1'b1),
  .copyA(1'b0),
  .invExcpt(1'b0),
  .rmode(3'd2),
  .en(1'b1),
  .res(result),
  .isDBL(1'b1)
  );

  fcadd_test_data mem_mod(
  clk,
  rst,
  addr,
  A,B,res,sub);

  assign dmatch={result[63],result[80],result[61:0]}==res_reg3[63:0];

  always @(negedge clk) begin
    if (rst)addr<=24'b0;
    else addr<=addr+1;
    res_reg<=res;
    res_reg2<=res_reg;
    res_reg3<=res_reg2;
    A_reg<=A;
    A_reg2<=A_reg;
    A_reg3<=A_reg2;
    B_reg<=B;
    B_reg2<=B_reg;
    B_reg3<=B_reg2;
    if (addr>4&&!dmatch) $finish();
  end

  always @* begin
    cor_res=fswap(res_reg);
    my_res=fswap(result);
    my_A=fswap(A_reg);
    my_B=fswap(B_reg);
  end
endmodule

module fcadd_test_data(
  clk,
  rst,
  addr,
  A,B,res,sub);
  input clk;
  input rst;
  input [23:0] addr;
  output [63:0] A;
  output [63:0] B;
  output [63:0] res;
  output sub;

  reg [3*64:0] ram[2048*1024-1:0];
  reg [23:0] addr_reg;

  assign {sub,res,B,A}=ram[addr_reg];
  always @(negedge clk) begin
    if (rst) addr_reg<=0;
    else addr_reg<=addr;
  end
  initial
    $readmemh("/home/goran/heptane/test/fpu/cyadd16.memh",ram);
endmodule
