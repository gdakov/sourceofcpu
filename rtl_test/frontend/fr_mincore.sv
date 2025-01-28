`include "../../rtl/common.sv"


module mincore(
  clk,
  rst,
  stall,
  iAvail,
  instr,
  instrQ,
  except,
  exceptIP
  );
  
  input clk;
  input rst;
  output stall;
  input iAvail;
  input [79:0] instr;
  input [`instrQ_width-1:0] instrQ;
  output except;
  output [IP_WIDTH-1:0] exceptIP;
  
  reg [IP_WIDTH-1:5] baseIP;
  reg [OPERATION_WIDTH-1:0] operation_reg;
  reg rA_use_reg;
  reg rB_use_reg;
  reg rC_use_reg;
  reg rT_use_reg;
  reg useBConst_reg;
  wire [64:0] rA_data;
  wire [64:0] rB_data;
  wire [64:0] rC_data;
  wire [64:0] write_data;
  reg [2:0] port_reg;
  reg isJump_reg,isJump_reg2;
  reg [5:0] flags_q;
  wire [5:0] flags;
  wire [`except_width-1:0] ret_data;
  reg [4:0] jumpType_reg;
  
  wire [OPERATION_WIDTH-1:0] operation;
  wire [REG_WIDTH-1:0] rA;
  wire rA_use;
  wire [REG_WIDTH-1:0] rB;
  wire rB_use;
  wire [REG_WIDTH-1:0] rC;
  wire rC_use;
  wire useCRet;
  wire useBConst;
  wire [63:0] constant;
  wire [9:0] smallConst;
  wire smallConst_use;
  wire [REG_WIDTH-1:0] rT;
  wire rT_use;
  wire [2:0] port;
  wire useRs;
  wire rA_useF,rB_useF,rT_useF,rC_useF,useRsF;
  wire rA_cross,rB_cross,
  wire [REG_WIDTH-1:0] rAx;
  wire rAx_use,rAx_cross;
  wire [REG_WIDTH-1:0] rBx;
  wire rBx_use,rBx_cross;
  wire [REG_WIDTH-1:0] rTx;
  wire rTx_use,clr64,clr128,useRsX,chain;
  wire flags_use;
  wire halt;
  
  wire pushCallStack;
  wire popCallStack;
  wire [4:0] jumpType;
  wire [IP_WIDTH-1:0] IP;
  
  reg prevSpecLoad;
  wire thisSpecLoad;
  reg prevSpecAlu;
  wire thisSpecAlu;
  wire isIPRel;
  wire isBigConst;
  wire isPrevBigConst;
  
  wire isJump;
  wire jumpTaken;
  wire jumpBtbHit;
  wire jumpIndir;

  wire [5:0] flags;
  wire setsFlags;
  reg [4:0] jumpType_reg;
  reg [4:0] jumpType_reg2;
  
  reg [IP_WIDTH-1:0] IP_next;
  
  assign flags=(clsALU_reg2 || clsShift_reg2) & setsFlags ? ret_data[`except_flags] : flags_q;
  assign setsFlags=ret_data[`except_setsFlags];
  
  assign except=clsJump_reg2 | clsIndir_reg2 && (jumpTaken_reg2 ^ doJump);
  
  assign exceptIP=doJump & clsJump_reg2 ? IP_reg2+const_reg2 : {IP_WIDTH{1'BZ}};
  assign exceptIP=~doJump & clsJump_reg2 ? IP_next_reg2 : {IP_WIDTH{1'BZ}};
  assign exceptIP=clsIndir_reg2 ? write_data_reg : {IP_WIDTH{1'BZ}};
  assign exceptIP=~clsJump_reg2 & ~clsIndir_reg2 ? {IP_WIDTH{1'b0}} : {IP_WIDTH{1'BZ}};
  
  smallInstr_decoder(
  clk,
  rst,
  baseIP,
  iAvail,
  instrQ,
  instr,
  operation,
  rA,rA_use,
  rB,rB_use,useBConst,
  rC,rC_use,useCRet,
  constant,smallConst,
  smallConst_use,
  rT,rT_use,
  port,
  useRs,
  rA_useF,rB_useF,rT_useF,rC_useF,
  rA_cross,rB_cross,
  useRsF,
  rAx,rAx_use,rAx_cross,
  rBx,rBx_use,rBx_cross,
  rTx,rTx_use,
  useRsX,
  clr64,clr128,
  chain,
  flags_use,
  halt,
  
  pushCallStack,
  popCallStack,
  isJump,
  jumpTaken,
  jumpType,
  jumpBtbHit,
  jumpIndir,
  IP,
  prevSpecLoad,
  thisSpecLoad,
  prevSpecAlu,
  thisSpecAlu,
  isIPRel,
  isBigConst,
  isPrevBigConst
  );
  
  mincore_regfile rf_mod(
  clk,
  rst,
  iAvail,
  rA,rA_data,
  rB,rB_data,
  rC,rC_data,
  rT_use_reg,
  rT_reg,write_data
  );

  alu alu_mod(
  .clk(~clk),
  .rst(rst),
  .except(except),
  .operation(operation_reg),
  .dataEn(1'b1),
  .nDataAlt(clsALU | clsShift),
  .retData(ret_data),
  .val1(rA_data&{65{rA_use_reg}}),
  .val2(useBConst_reg ? constant_reg : rB_data),
  .valS(flags),
  .valRes(write_data)
  );
  
  alu_shift shift_mod(
  .clk(clk),
  .rst(rst),
  .except(except),
  .operation(operation_reg),
  .dataEn(1'b1),
  .nDataAlt(clsALU | clsShift),
  .retData(ret_data),
  .val1(rA_data),
  .val2(useBConst ? constant_reg : rB_data),
  .valRes(write_data)
  );
  
  mincore_jump_cmp cmp_mod(
  flags_d,
  jumpType_reg2,
  doJump
  );
  
  always @* begin
    if (~magic[0]) IP_next=IP+2;
    if (magic[1:0]==2'b01) IP_next=IP+4;
    if (magic[2:0]==3'b011) IP_next=IP+6;
    if (magic[3:0]==2'b0111) IP_next=IP+8;
    if (magic[3:0]==2'b1111) IP_next=IP+12;
  end
  
  always @(posedge clk) begin
      if (rst) begin
          flags_q<=6'b0;
      end else begin
          flags_q<=flags;
      end
  end
endmodule


module mincore_regfile(
  clk,
  rst,
  read_clkEn,
  readA_addr,readA_data,
  readB_addr,readB_data,
  readC_addr,readC_data,
  write_wen,
  write_addr,write_data
  );
  input clk;
  input rst;
  input read_clkEn;
  input [4:0] readA_addr;
  output [64:0] readA_data;
  input [4:0] readB_addr;
  output [64:0] readB_data;
  input [4:0] readC_addr;
  output [64:0] readC_data;
  input write_wen;
  input [4:0] write_addr;
  input [64:0] write_data;
  
  reg [64:0] ram[31:0];
  reg [4:0] readA_addr_reg;
  reg [4:0] readB_addr_reg;
  reg [4:0] readC_addr_reg;
  integer k;
  
  assign readA_data=ram[readA_addr_reg];
  assign readB_data=ram[readB_addr_reg];
  assign readC_data=ram[readC_addr_reg];
  
  always @(posedge clk) begin
      if (rst) begin
          for (k=0;k<32;k=k+1) ram[k]<=65'b0;
          readA_addr_reg<=0;
          readB_addr_reg<=0;
          readC_addr_reg<=0;
      end else begin
          if (read_clkEn) begin
              readA_addr_reg<=readA_addr;
              readB_addr_reg<=readB_addr;
              readC_addr_reg<=readC_addr;
          end
          if (write_wen) ram[write_addr]<=write_data;
      end
  end
  
endmodule



module mincore_jump_cmp(
  flags,
  jumpType,
  doJump
  );
  parameter JUMP_TYPE_WIDTH=5;
  parameter FLAGS_WIDTH=`flags_width;

  input [FLAGS_WIDTH-1:0] flags;
  input [JUMP_TYPE_WIDTH-1:0] jumpType;
  output reg doJump;

  wire C;
  wire O;
  wire A;
  wire S;
  wire Z;
  wire P;

  assign {C,O,A,S,Z,P}=flags;

  always @(*)
    begin
      case(jumpType)
        `jump_Z:	doJump=Z;
        `jump_nZ:	doJump=~Z;
        `jump_S:	doJump=S;
        `jump_nS:	doJump=~S;
        `jump_uGT:	doJump=~(C | Z);
        `jump_uLE:	doJump=C | Z;
        `jump_uGE:	doJump=~C;
        `jump_uLT:	doJump=C;
        `jump_sGT:	doJump=~((S^O)|Z);
        `jump_sLE:	doJump=(S^O)|Z;
        `jump_sGE:	doJump=~S^O;
        `jump_sLT:	doJump=S^O;
        `jump_O:	doJump=O;
        `jump_nO:	doJump=~O;
        `jump_P:	doJump=P;
        `jump_nP:	doJump=~P;
        default:	doJump=1;
      endcase
    end
endmodule
