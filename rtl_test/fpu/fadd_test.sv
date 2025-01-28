`include "../../rtl/common.sv"

`define extended

module fadd_test();
`ifdef extended
  localparam WIDTH=80;
`else
  localparam WIDTH=64;
`endif
  reg clk=1;
  reg rst=1;
  reg [23:0] addr;
  real my_res,my_A,my_B;
  real cor_res;
  wire [WIDTH-1:0] res;
  wire [WIDTH-1:0] result;
  reg [WIDTH-1:0] res_reg;
  reg [WIDTH-1:0] res_reg2;
  reg [WIDTH-1:0] A_reg;
  reg [WIDTH-1:0] A_reg2;
  reg [WIDTH-1:0] B_reg;
  reg [WIDTH-1:0] B_reg2;
  wire [WIDTH-1:0] A;
  wire [WIDTH-1:0] B;
  wire sub;
  wire dmatch;
  
  function [6:0] fswap;
    input [63:0] fnum;
    integer k;
    for(k=0;k<64;k=k+1) fswap[k]=fnum[63-k];
  endfunction

  always #(50) clk<=~clk;
  always @(negedge clk) rst<=1'b0;
  fadd fadd_mod(
  .clk(clk),
  .rst(rst),
`ifdef extended
  .A({1'b1,A}),
  .B({1'b1,B}),
`else  
  .A({1'b1,16'b0,A}),
  .B({1'b1,16'b0,B}),
`endif
`ifdef extended
  .isDBL(1'b0),
`else
  .isDBL(1'b1),
`endif
  .isSub(sub),//inclusive of isRSub
//  .isRSub(1'b0),
  .rmode(3'd2), 
  .invExcpt(1'b0),
  .res(result)
  );

  fadd_test_data mem_mod(
  clk,
  rst,
  addr,
  A,B,res,sub);

  assign dmatch=result[WIDTH-1:0]==res_reg[WIDTH-1:0];

  always @(negedge clk) begin
    if (rst)addr<=24'b0;
    else addr<=addr+1;
    res_reg<=res;
    res_reg2<=res_reg;
    A_reg<=A;
    A_reg2<=A_reg;
    B_reg<=B;
    B_reg2<=B_reg;
    if (addr>2&&!(dmatch===1)) $finish();
  end

  always @* begin
    cor_res=fswap(res_reg);
    my_res=fswap(result);
    my_A=fswap(A_reg);
    my_B=fswap(B_reg);
  end
endmodule

module fadd_test_data(
  clk,
  rst,
  addr,
  A,B,res,sub);
`ifdef extended
    localparam WIDTH=80;
`else
    localparam WIDTH=64;
`endif
  
  input clk;
  input rst;
  input [23:0] addr;
  output [WIDTH-1:0] A;
  output [WIDTH-1:0] B;
  output [WIDTH-1:0] res;
  output sub;

  reg [3*WIDTH:0] ram[2048*1024-1:0];
  reg [23:0] addr_reg;

  assign {sub,res,B,A}=ram[addr_reg];
  always @(negedge clk) begin
    if (rst) addr_reg<=0;
    else addr_reg<=addr;
  end
  initial
  `ifdef extended
    $readmemh("/home/goran/heptane/test/fpu/fadd16e.memh",ram);
  `else
    $readmemh("/home/goran/heptane/test/fpu/fadd16.memh",ram);
  `endif
endmodule
