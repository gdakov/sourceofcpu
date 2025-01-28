`include "../../rtl/common.sv"


module fr_test4;
  localparam PHYS_WIDTH=44;
  localparam VIRT_WIDTH=64;
  localparam IP_WIDTH=48;
  localparam [31:0] INIT_IP=32'h20;
  localparam BUS_BANK=32;
  localparam BUS_WIDTH=BUS_BANK*16;
  localparam DATA_WIDTH=65*4;
  localparam INSTR_WIDTH=80;
  localparam IN_REG_WIDTH=6;
  localparam OPERATION_WIDTH=`operation_width;
  localparam PORT_WIDTH=4;
  localparam RS_WIDTH=64;
  localparam REQ_WIDTH=10;
 
 // reg [63:0] r02_data;
 // reg r02_en;
  wire [5:0] wrtII=bck_mod.PSTQ_en[0] ? bck_mod.PSTQ_data[0][117:112] : bck_mod.PSTQ_data[1][117:112];
  wire [5:0] dataAII=bck_mod.LSQ_dataA0[117:112];
  reg [63:0] wdata_reg[1:0];
  reg [63:0] wdata_reg2[1:0];
  reg [63:0] wdata_reg3[1:0];

  reg clk=1'b0;
  reg clkX=1'b1;
  reg rst=1'b1;
  reg fstall=1'b0;
  wire [BUS_WIDTH-1:0] bus_data;
  wire [7:0] bus_slot;
  wire bus_en;
  
  wire [36:0] req_addr;
  wire [7:0] req_slot;
  wire req_en;
  wire req_tlbEn;

  wire [`ctlbData_width-1:0] bus_tlb_data;
  reg [7:0] bus_tlb_slot;
  wire bus_tlb_en;

  wire [DATA_WIDTH-1:0] read_data;
  wire instrFed;
  wire [255:0] read_data_strip;
  
  wire except;
  
  wire [VIRT_WIDTH-2:0] exceptIP;

  wire exceptThread;
  wire exceptBoth;
  wire [5:0] exceptTrceAddr=6'b0;
  wire [4:0] exceptTrceAddrLow=5'b0;
  wire except_due_jump;
  wire [7:0] except_ght;
  wire except_flag;
  wire jupd0_en;//jupd
  wire jupdt0_en;
  wire jupd0_ght_en;
  wire [15:0] jupd0_addr;
  wire [12:0] jupd0_baddr;
  wire [1:0] jupd0_sc;
  wire jupd0_tk;
  wire jupd1_en;
  wire jupdt1_en;
  wire jupd1_ght_en;
  wire [15:0] jupd1_addr;
  wire [12:0] jupd1_baddr;
  wire [1:0] jupd1_sc;
  wire jupd1_tk;

  reg jupd_reg,jupd_reg2;

  wire [`ctlbData_width-1:0] bus_tlb_data_d;

  wire [INSTR_WIDTH-1:0] instr0;
  wire [INSTR_WIDTH-1:0] instr1;
  wire [INSTR_WIDTH-1:0] instr2;
  wire [INSTR_WIDTH-1:0] instr3;
  wire [INSTR_WIDTH-1:0] instr4;
  wire [INSTR_WIDTH-1:0] instr5;
  wire [INSTR_WIDTH-1:0] instr6;
  wire [INSTR_WIDTH-1:0] instr7;
  wire [INSTR_WIDTH-1:0] instr8;
  wire [INSTR_WIDTH-1:0] instr9;

  wire [`instrQ_width-1:0] extra0;
  wire [`instrQ_width-1:0] extra1;
  wire [`instrQ_width-1:0] extra2;
  wire [`instrQ_width-1:0] extra3;
  wire [`instrQ_width-1:0] extra4;
  wire [`instrQ_width-1:0] extra5;
  wire [`instrQ_width-1:0] extra6;
  wire [`instrQ_width-1:0] extra7;
  wire [`instrQ_width-1:0] extra8;
  wire [`instrQ_width-1:0] extra9;


  wire [9:0] instrEn;
  wire [9:0] iAvail;
  wire stall;

  wire [2:0] btbl_step;
  wire [IP_WIDTH-2:0] btbl_IP0;
  wire [IP_WIDTH-2:0] btbl_IP1;

  
  wire [9:0] iUsed;
  
  
  wire halt;
  
  wire bundleFeed;
  

  wire [IN_REG_WIDTH-1:0] rs0i0_rA;
  wire rs0i0_rA_use;
  wire rs0i0_rA_useF;
  wire rs0i0_rA_isV;
  wire rs0i0_rA_isAnyV;
  wire [IN_REG_WIDTH-1:0] rs0i0_rB;
  wire rs0i0_rB_use;
  wire rs0i0_rB_useF;
  wire rs0i0_rB_isV;
  wire rs0i0_rB_isAnyV;
  wire rs0i0_useBConst;
  wire [IN_REG_WIDTH-1:0] rs0i0_rT;
  wire rs0i0_rT_use;
  wire rs0i0_rT_useF;
  wire rs0i0_rT_isV;
  wire [PORT_WIDTH-1:0] rs0i0_port;
  wire [OPERATION_WIDTH-1:0] rs0i0_operation;
  wire rs0i0_en;
  wire [RS_WIDTH-1:0] rs0i0_const;
  wire [3:0] rs0i0_index;
  wire rs0i0_IPRel;
  wire rs0i0_afterTaken;
  wire rs0i0_alt;
//  wire rs0i0_both;
  wire rs0i0_alloc;
  wire rs0i0_allocF;
  wire rs0i0_allocR;
  wire [5:0] rs0i0_lsi;
  wire rs0i0_ldst_flag;
  
  wire [IN_REG_WIDTH-1:0] rs0i1_rA;
  wire rs0i1_rA_use;
  wire rs0i1_rA_useF;
  wire rs0i1_rA_isV;
  wire rs0i1_rA_isAnyV;
  wire [IN_REG_WIDTH-1:0] rs0i1_rB;
  wire rs0i1_rB_use;
  wire rs0i1_rB_useF;
  wire rs0i1_rB_isV;
  wire rs0i1_rB_isAnyV;
  wire rs0i1_useBConst;
  wire [IN_REG_WIDTH-1:0] rs0i1_rT;
  wire rs0i1_rT_use;
  wire rs0i1_rT_useF;
  wire rs0i1_rT_isV;
  wire [PORT_WIDTH-1:0] rs0i1_port;
  wire [OPERATION_WIDTH-1:0] rs0i1_operation;
  wire rs0i1_en;
  wire [RS_WIDTH-1:0] rs0i1_const;
  wire [3:0] rs0i1_index;
  wire rs0i1_IPRel;
  wire rs0i1_afterTaken;
  wire rs0i1_alloc;
  wire rs0i1_allocF;
  wire rs0i1_allocR;
  wire [3:0] rs0i1_flagDep;
  wire rs0i1_lastFl;
  wire [5:0] rs0i1_lsi;
  wire rs0i1_ldst_flag;
  
  wire [IN_REG_WIDTH-1:0] rs0i2_rA;
  wire rs0i2_rA_use;
  wire rs0i2_rA_useF;
  wire rs0i2_rA_isV;
  wire rs0i2_rA_isAnyV;
  wire [IN_REG_WIDTH-1:0] rs0i2_rB;
  wire rs0i2_rB_use;
  wire rs0i2_rB_useF;
  wire rs0i2_rB_isV;
  wire rs0i2_rB_isAnyV;
  wire rs0i2_useBConst;
  wire [IN_REG_WIDTH-1:0] rs0i2_rT;
  wire rs0i2_rT_use;
  wire rs0i2_rT_useF;
  wire rs0i2_rT_isV;
  wire [PORT_WIDTH-1:0] rs0i2_port;
  wire [OPERATION_WIDTH-1:0] rs0i2_operation;
  wire rs0i2_en;
  wire [RS_WIDTH-1:0] rs0i2_const;
  wire [3:0] rs0i2_index;
  wire rs0i2_IPRel;
  wire rs0i2_afterTaken;
  wire rs0i2_alloc;
  wire rs0i2_allocF;
  wire rs0i2_allocR;
  wire [3:0] rs0i2_flagDep;
  wire rs0i2_lastFl;
  
  wire [IN_REG_WIDTH-1:0] rs1i0_rA;
  wire rs1i0_rA_use;
  wire rs1i0_rA_useF;
  wire rs1i0_rA_isV;
  wire rs1i0_rA_isAnyV;
  wire [IN_REG_WIDTH-1:0] rs1i0_rB;
  wire rs1i0_rB_use;
  wire rs1i0_rB_useF;
  wire rs1i0_rB_isV;
  wire rs1i0_rB_isAnyV;
  wire rs1i0_useBConst;
  wire [IN_REG_WIDTH-1:0] rs1i0_rT;
  wire rs1i0_rT_use;
  wire rs1i0_rT_useF;
  wire rs1i0_rT_isV;
  wire [PORT_WIDTH-1:0] rs1i0_port;
  wire [OPERATION_WIDTH-1:0] rs1i0_operation;
  wire rs1i0_en;
  wire [RS_WIDTH-1:0] rs1i0_const;
  wire [3:0] rs1i0_index;
  wire rs1i0_IPRel;
  wire rs1i0_afterTaken;
  wire rs1i0_alt;
//  wire rs1i0_both;
  wire rs1i0_alloc;
  wire rs1i0_allocF;
  wire rs1i0_allocR;
  wire [5:0] rs1i0_lsi;
  wire rs1i0_ldst_flag;
  
  wire [IN_REG_WIDTH-1:0] rs1i1_rA;
  wire rs1i1_rA_use;
  wire rs1i1_rA_useF;
  wire rs1i1_rA_isV;
  wire rs1i1_rA_isAnyV;
  wire [IN_REG_WIDTH-1:0] rs1i1_rB;
  wire rs1i1_rB_use;
  wire rs1i1_rB_useF;
  wire rs1i1_rB_isV;
  wire rs1i1_rB_isAnyV;
  wire rs1i1_useBConst;
  wire [IN_REG_WIDTH-1:0] rs1i1_rT;
  wire rs1i1_rT_use;
  wire rs1i1_rT_useF;
  wire rs1i1_rT_isV;
  wire [PORT_WIDTH-1:0] rs1i1_port;
  wire [OPERATION_WIDTH-1:0] rs1i1_operation;
  wire rs1i1_en;
  wire [RS_WIDTH-1:0] rs1i1_const;
  wire [3:0] rs1i1_index;
  wire rs1i1_IPRel;
  wire rs1i1_afterTaken;
  wire rs1i1_alloc;
  wire rs1i1_allocF;
  wire rs1i1_allocR;
  wire [3:0] rs1i1_flagDep;
  wire rs1i1_lastFl;
  wire [5:0] rs1i1_lsi;
  wire rs1i1_ldst_flag;

  wire [IN_REG_WIDTH-1:0] rs1i2_rA;
  wire rs1i2_rA_use;
  wire rs1i2_rA_useF;
  wire rs1i2_rA_isV;
  wire rs1i2_rA_isAnyV;
  wire [IN_REG_WIDTH-1:0] rs1i2_rB;
  wire rs1i2_rB_use;
  wire rs1i2_rB_useF;
  wire rs1i2_rB_isV;
  wire rs1i2_rB_isAnyV;
  wire rs1i2_useBConst;
  wire [IN_REG_WIDTH-1:0] rs1i2_rT;
  wire rs1i2_rT_use;
  wire rs1i2_rT_useF;
  wire rs1i2_rT_isV;
  wire [PORT_WIDTH-1:0] rs1i2_port;
  wire [OPERATION_WIDTH-1:0] rs1i2_operation;
  wire rs1i2_en;
  wire [RS_WIDTH-1:0] rs1i2_const;
  wire [3:0] rs1i2_index;
  wire rs1i2_IPRel;
  wire rs1i2_afterTaken;
  wire rs1i2_alloc;
  wire rs1i2_allocF;
  wire rs1i2_allocR;
  wire [3:0] rs1i2_flagDep;
  wire rs1i2_lastFl;

  wire [IN_REG_WIDTH-1:0] rs2i0_rA;
  wire rs2i0_rA_use;
  wire rs2i0_rA_useF;
  wire rs2i0_rA_isV;
  wire rs2i0_rA_isAnyV;
  wire [IN_REG_WIDTH-1:0] rs2i0_rB;
  wire rs2i0_rB_use;
  wire rs2i0_rB_useF;
  wire rs2i0_rB_isV;
  wire rs2i0_rB_isAnyV;
  wire rs2i0_useBConst;
  wire [IN_REG_WIDTH-1:0] rs2i0_rT;
  wire rs2i0_rT_use;
  wire rs2i0_rT_useF;
  wire rs2i0_rT_isV;
  wire [PORT_WIDTH-1:0] rs2i0_port;
  wire [OPERATION_WIDTH-1:0] rs2i0_operation;
  wire rs2i0_en;
  wire [RS_WIDTH-1:0] rs2i0_const;
  wire [3:0] rs2i0_index;
  wire rs2i0_IPRel;
  wire rs2i0_afterTaken;
  wire rs2i0_alt;
//  wire rs2i0_both;
  wire rs2i0_alloc;
  wire rs2i0_allocF;
  wire rs2i0_allocR;
  wire [5:0] rs2i0_lsi;
  wire rs2i0_ldst_flag;
  
  wire [IN_REG_WIDTH-1:0] rs2i1_rA;
  wire rs2i1_rA_use;
  wire rs2i1_rA_useF;
  wire rs2i1_rA_isV;
  wire rs2i1_rA_isAnyV;
  wire [IN_REG_WIDTH-1:0] rs2i1_rB;
  wire rs2i1_rB_use;
  wire rs2i1_rB_useF;
  wire rs2i1_rB_isV;
  wire rs2i1_rB_isAnyV;
  wire rs2i1_useBConst;
  wire [IN_REG_WIDTH-1:0] rs2i1_rT;
  wire rs2i1_rT_use;
  wire rs2i1_rT_useF;
  wire rs2i1_rT_isV;
  wire [PORT_WIDTH-1:0] rs2i1_port;
  wire [OPERATION_WIDTH-1:0] rs2i1_operation;
  wire rs2i1_en;
  wire [RS_WIDTH-1:0] rs2i1_const;
  wire [3:0] rs2i1_index;
  wire rs2i1_IPRel;
  wire rs2i1_afterTaken;
  wire rs2i1_alloc;
  wire rs2i1_allocF;
  wire rs2i1_allocR;
  wire [3:0] rs2i1_flagDep;
  wire rs2i1_lastFl;
  wire [5:0] rs2i1_lsi;
  wire rs2i1_ldst_flag;

  wire [IN_REG_WIDTH-1:0] rs2i2_rA;
  wire rs2i2_rA_use;
  wire rs2i2_rA_useF;
  wire rs2i2_rA_isV;
  wire rs2i2_rA_isAnyV;
  wire [IN_REG_WIDTH-1:0] rs2i2_rB;
  wire rs2i2_rB_use;
  wire rs2i2_rB_useF;
  wire rs2i2_rB_isV;
  wire rs2i2_rB_isAnyV;
  wire rs2i2_useBConst;
  wire [IN_REG_WIDTH-1:0] rs2i2_rT;
  wire rs2i2_rT_use;
  wire rs2i2_rT_useF;
  wire rs2i2_rT_isV;
  wire [PORT_WIDTH-1:0] rs2i2_port;
  wire [OPERATION_WIDTH-1:0] rs2i2_operation;
  wire rs2i2_en;
  wire [RS_WIDTH-1:0] rs2i2_const;
  wire [3:0] rs2i2_index;
  wire rs2i2_IPRel;
  wire rs2i2_afterTaken;
  wire rs2i2_alloc;
  wire rs2i2_allocF;
  wire rs2i2_allocR;
  wire [3:0] rs2i2_flagDep;
  wire rs2i2_lastFl;


  wire [IN_REG_WIDTH-1:0] instr0_rT;
  wire instr0_en;
  wire instr0_wren;
  wire [12:0] instr0_IPOff;
  wire instr0_afterTaken;
  wire instr0_rT_useF;
  wire instr0_rT_isV;
  wire [PORT_WIDTH-1:0] instr0_port;
  wire [3:0] instr0_magic;
  wire instr0_last;
  
  wire [IN_REG_WIDTH-1:0] instr1_rT;
  wire instr1_en;
  wire instr1_wren;
  wire [12:0] instr1_IPOff;
  wire instr1_afterTaken;
  wire instr1_rT_useF;
  wire instr1_rT_isV;
  wire [PORT_WIDTH-1:0] instr1_port;
  wire [3:0] instr1_magic;
  wire instr1_last;
  
  wire [IN_REG_WIDTH-1:0] instr2_rT;
  wire instr2_en;
  wire instr2_wren;
  wire [12:0] instr2_IPOff;
  wire instr2_afterTaken;
  wire instr2_rT_useF;
  wire instr2_rT_isV;
  wire [PORT_WIDTH-1:0] instr2_port;
  wire [3:0] instr2_magic;
  wire instr2_last;
  
  wire [IN_REG_WIDTH-1:0] instr3_rT;
  wire instr3_en;
  wire instr3_wren;
  wire [12:0] instr3_IPOff;
  wire instr3_afterTaken;
  wire instr3_rT_useF;
  wire instr3_rT_isV;
  wire [PORT_WIDTH-1:0] instr3_port;
  wire [3:0] instr3_magic;
  wire instr3_last;
  
  wire [IN_REG_WIDTH-1:0] instr4_rT;
  wire instr4_en;
  wire instr4_wren;
  wire [12:0] instr4_IPOff;
  wire instr4_afterTaken;
  wire instr4_rT_useF;
  wire instr4_rT_isV;
  wire [PORT_WIDTH-1:0] instr4_port;
  wire [3:0] instr4_magic;
  wire instr4_last;
  
  wire [IN_REG_WIDTH-1:0] instr5_rT;
  wire instr5_en;
  wire instr5_wren;
  wire [12:0] instr5_IPOff;
  wire instr5_afterTaken;
  wire instr5_rT_useF;
  wire instr5_rT_isV;
  wire [PORT_WIDTH-1:0] instr5_port;
  wire [3:0] instr5_magic;
  wire instr5_last;

  wire [IN_REG_WIDTH-1:0] instr6_rT;
  wire instr6_en;
  wire instr6_wren;
  wire [12:0] instr6_IPOff;
  wire instr6_afterTaken;
  wire instr6_rT_useF;
  wire instr6_rT_isV;
  wire [PORT_WIDTH-1:0] instr6_port;
  wire [3:0] instr6_magic;
  wire instr6_last;

  wire [IN_REG_WIDTH-1:0] instr7_rT;
  wire instr7_en;
  wire instr7_wren;
  wire [12:0] instr7_IPOff;
  wire instr7_afterTaken;
  wire instr7_rT_useF;
  wire instr7_rT_isV;
  wire [PORT_WIDTH-1:0] instr7_port;
  wire [3:0] instr7_magic;
  wire instr7_last;

  wire [IN_REG_WIDTH-1:0] instr8_rT;
  wire instr8_en;
  wire instr8_wren;
  wire [12:0] instr8_IPOff;
  wire instr8_afterTaken;
  wire instr8_rT_useF;
  wire instr8_rT_isV;
  wire [PORT_WIDTH-1:0] instr8_port;
  wire [3:0] instr8_magic;
  wire instr8_last;

  wire [IN_REG_WIDTH-1:0] instr9_rT;
  wire instr9_en;
  wire instr9_wren;
  wire [12:0] instr9_IPOff;
  wire instr9_afterTaken;
  wire instr9_rT_useF;
  wire instr9_rT_isV;
  wire [PORT_WIDTH-1:0] instr9_port;
  wire [3:0] instr9_magic;
  wire instr9_last;

  wire [4:0] jump0Type;
  wire [3:0] jump0Pos;
  wire jump0Taken;
  wire [4:0] jump1Type;
  wire [3:0] jump1Pos;
  wire jump1Taken;
  wire [2:0] jump0BtbWay;
  wire [1:0] jump0JmpInd;
  wire [7:0] jump0GHT;
  wire [2:0] jump1BtbWay;
  wire [1:0] jump1JmpInd;
  wire [7:0] jump1GHT;
  wire [1:0] jump0SC;
  wire jump0Miss;
  wire jump0TbufOnly;
  wire [1:0] jump1SC;
  wire jump1Miss;
  wire jump1TbufOnly;
  wire [9:0] instr_trce;
  wire [9:0] instr_fsimd;
  wire [46:0] traceIP0;
  wire [46:0] traceIP1;
  wire [46:0] baseIP;
  wire [5:0] wrt0;
  wire [5:0] wrt1;
  wire [5:0] wrt2;

  wire insBus_en;
  wire [REQ_WIDTH-1:0] insBus_req;
  wire insBus_dirty;
  wire insBus_exclusive;
  wire [511:0] insBus_data;

  wire reqBus_en;
  wire [43:7] reqBus_addr;
  wire [REQ_WIDTH-1:0] reqBus_req;
  wire reqBus_want_excl;

  reg ret_ebx_en;
  reg [63:0] ret_ebx_data;
  
  reg ret_r8d_en;
  reg [63:0] ret_r8d_data;
  
  assign bus_tlb_data_d[`ctlbData_sys]=1'b1;
  assign bus_tlb_data_d[`ctlbData_na]=1'b0;
  assign bus_tlb_data_d[`ctlbData_ne]=1'b0;
  assign bus_tlb_data_d[`ctlbData_phys]=req_addr[31:0];
  
  assign read_data_strip={read_data[258:195],read_data[193:130],read_data[128:65],read_data[63:0]};
  
//  assign stall=1'b0;
  
//  assign except=1'b0;//iAvail[0] && instr0[15:0]==16'h0023;

  frontend1 front_mod(
  clk,
  rst,
  except,
  exceptIP[46:0],
//
  exceptThread,
  except_due_jump,
  except_ght,
  except_flag,
  jupd0_en,jupdt0_en,jupd0_ght_en,jupd0_addr,jupd0_baddr,jupd0_sc,jupd0_tk,
  jupd1_en,jupdt1_en,jupd1_ght_en,jupd1_addr,jupd1_baddr,jupd1_sc,jupd1_tk,
//
  bus_data,
  bus_slot,
  bus_en,
  req_addr,
  req_slot,
  req_en,
  req_tlbEn,
  bus_tlb_data,
  bus_tlb_slot,
  bus_tlb_en,
  instr0,instr1,instr2,instr3,
  instr4,instr5,instr6,instr7,
  instr8,instr9,
  extra0,extra1,extra2,extra3,
  extra4,extra5,extra6,extra7,
  extra8,extra9,
  instrEn,
  iAvail,
  stall,
  btbl_step,
  btbl_IP0,
  btbl_IP1
  );
  

  
  dummyL2 l2I_mo(
  clk,
  rst,
  bus_en,
  bus_slot[2:0],
  ,
  ,
  bus_data,
  req_en,
  req_addr,
  req_slot,
  1'b0
  );

  assign bus_slot[7:3]=5'b0;
  
  decoder dec_mod(
  clk,
  rst,
  stall,
  except,
  {exceptIP[46:0],1'b0},
  
  btbl_step,
  
  iAvail,
  instrEn,
  instr0,extra0,
  instr1,extra1,
  instr2,extra2,
  instr3,extra3,
  instr4,extra4,
  instr5,extra5,
  instr6,extra6,
  instr7,extra7,
  instr8,extra8,
  instr9,extra9,
  
  btbl_IP0,
  btbl_IP1,
  
  halt,
  

  bundleFeed,
//begin instructions ordered by rs input port
  rs0i0_rA,rs0i0_rA_use,rs0i0_rA_useF,rs0i0_rA_isV,rs0i0_rA_isAnyV,
  rs0i0_rB,rs0i0_rB_use,rs0i0_rB_useF,rs0i0_rB_isV,rs0i0_rB_isAnyV,rs0i0_useBConst,
  rs0i0_rT,rs0i0_rT_use,rs0i0_rT_useF,rs0i0_rT_isV, 
  rs0i0_port,
  rs0i0_operation,
  rs0i0_en,
  rs0i0_const,
  rs0i0_index,
  rs0i0_IPRel,
  rs0i0_afterTaken,
  rs0i0_alt,
  rs0i0_alloc,
  rs0i0_allocF,
  rs0i0_allocR,
  rs0i0_lsi,
  rs0i0_ldst_flag,

  rs0i1_rA,rs0i1_rA_use,rs0i1_rA_useF,rs0i1_rA_isV,rs0i1_rA_isAnyV,
  rs0i1_rB,rs0i1_rB_use,rs0i1_rB_useF,rs0i1_rB_isV,rs0i1_rB_isAnyV,rs0i1_useBConst,
  rs0i1_rT,rs0i1_rT_use,rs0i1_rT_useF,rs0i1_rT_isV,
  rs0i1_port,
  rs0i1_operation,
  rs0i1_en,
  rs0i1_const,
  rs0i1_index,
  rs0i1_IPRel,
  rs0i1_afterTaken,
  rs0i1_alloc,
  rs0i1_allocF,
  rs0i1_allocR,
  rs0i1_flagDep,
  rs0i1_lastFl,
  rs0i1_lsi,
  rs0i1_ldst_flag,

  rs0i2_rA,rs0i2_rA_use,rs0i2_rA_useF,rs0i2_rA_isV,rs0i2_rA_isAnyV,
  rs0i2_rB,rs0i2_rB_use,rs0i2_rB_useF,rs0i2_rB_isV,rs0i2_rB_isAnyV,rs0i2_useBConst,
  rs0i2_rT,rs0i2_rT_use,rs0i2_rT_useF,rs0i2_rT_isV,
  rs0i2_port,
  rs0i2_operation,
  rs0i2_en,
  rs0i2_const,
  rs0i2_index,
  rs0i2_IPRel,
  rs0i2_afterTaken,
  rs0i2_alloc,
  rs0i2_allocF,
  rs0i2_allocR,
  rs0i2_flagDep,
  rs0i2_lastFl,

  rs1i0_rA,rs1i0_rA_use,rs1i0_rA_useF,rs1i0_rA_isV,rs1i0_rA_isAnyV,
  rs1i0_rB,rs1i0_rB_use,rs1i0_rB_useF,rs1i0_rB_isV,rs1i0_rB_isAnyV,rs1i0_useBConst,
  rs1i0_rT,rs1i0_rT_use,rs1i0_rT_useF,rs1i0_rT_isV,
  rs1i0_port,
  rs1i0_operation,
  rs1i0_en,
  rs1i0_const,
  rs1i0_index,
  rs1i0_IPRel,
  rs1i0_afterTaken,
  rs1i0_alt,
  rs1i0_alloc,
  rs1i0_allocF,
  rs1i0_allocR,
  rs1i0_lsi,
  rs1i0_ldst_flag,

  rs1i1_rA,rs1i1_rA_use,rs1i1_rA_useF,rs1i1_rA_isV,rs1i1_rA_isAnyV,
  rs1i1_rB,rs1i1_rB_use,rs1i1_rB_useF,rs1i1_rB_isV,rs1i1_rB_isAnyV,rs1i1_useBConst,
  rs1i1_rT,rs1i1_rT_use,rs1i1_rT_useF,rs1i1_rT_isV,
  rs1i1_port,
  rs1i1_operation,
  rs1i1_en,
  rs1i1_const,
  rs1i1_index,
  rs1i1_IPRel,
  rs1i1_afterTaken,
  rs1i1_alloc,
  rs1i1_allocF,
  rs1i1_allocR,
  rs1i1_flagDep,
  rs1i1_lastFl,
  rs1i1_lsi,
  rs1i1_ldst_flag,

  rs1i2_rA,rs1i2_rA_use,rs1i2_rA_useF,rs1i2_rA_isV,rs1i2_rA_isAnyV,
  rs1i2_rB,rs1i2_rB_use,rs1i2_rB_useF,rs1i2_rB_isV,rs1i2_rB_isAnyV,rs1i2_useBConst,
  rs1i2_rT,rs1i2_rT_use,rs1i2_rT_useF,rs1i2_rT_isV,
  rs1i2_port,
  rs1i2_operation,
  rs1i2_en,
  rs1i2_const,
  rs1i2_index,
  rs1i2_IPRel,
  rs1i2_afterTaken,
  rs1i2_alloc,
  rs1i2_allocF,
  rs1i2_allocR,
  rs1i2_flagDep,
  rs1i2_lastFl,

  rs2i0_rA,rs2i0_rA_use,rs2i0_rA_useF,rs2i0_rA_isV,rs2i0_rA_isAnyV,
  rs2i0_rB,rs2i0_rB_use,rs2i0_rB_useF,rs2i0_rB_isV,rs2i0_rB_isAnyV,rs2i0_useBConst,
  rs2i0_rT,rs2i0_rT_use,rs2i0_rT_useF,rs2i0_rT_isV,
  rs2i0_port,
  rs2i0_operation,
  rs2i0_en,
  rs2i0_const,
  rs2i0_index,
  rs2i0_IPRel,
  rs2i0_afterTaken,
  rs2i0_alt,
  rs2i0_alloc,
  rs2i0_allocF,
  rs2i0_allocR,
  rs2i0_lsi,
  rs2i0_ldst_flag,
  
  rs2i1_rA,rs2i1_rA_use,rs2i1_rA_useF,rs2i1_rA_isV,rs2i1_rA_isAnyV,
  rs2i1_rB,rs2i1_rB_use,rs2i1_rB_useF,rs2i1_rB_isV,rs2i1_rB_isAnyV,rs2i1_useBConst,
  rs2i1_rT,rs2i1_rT_use,rs2i1_rT_useF,rs2i1_rT_isV,
  rs2i1_port,
  rs2i1_operation,
  rs2i1_en,
  rs2i1_const,
  rs2i1_index,
  rs2i1_IPRel,
  rs2i1_afterTaken,
  rs2i1_alloc,
  rs2i1_allocF,
  rs2i1_allocR,
  rs2i1_flagDep,
  rs2i1_lastFl,
  rs2i1_lsi,
  rs2i1_ldst_flag,

  rs2i2_rA,rs2i2_rA_use,rs2i2_rA_useF,rs2i2_rA_isV,rs2i2_rA_isAnyV,
  rs2i2_rB,rs2i2_rB_use,rs2i2_rB_useF,rs2i2_rB_isV,rs2i2_rB_isAnyV,rs2i2_useBConst,
  rs2i2_rT,rs2i2_rT_use,rs2i2_rT_useF,rs2i2_rT_isV,
  rs2i2_port,
  rs2i2_operation,
  rs2i2_en,
  rs2i2_const,
  rs2i2_index,
  rs2i2_IPRel,
  rs2i2_afterTaken,
  rs2i2_alloc,
  rs2i2_allocF,
  rs2i2_allocR,
  rs2i2_flagDep,
  rs2i2_lastFl,

//end reordered small instructions
//begin instructions in program order
  instr0_rT, 
  instr0_en,
  instr0_wren, 
  instr0_IPOff,
  instr0_afterTaken,
  instr0_rT_useF,
  instr0_rT_isV,
  instr0_port,
  instr0_magic,
  instr0_last,
  
  instr1_rT,
  instr1_en,
  instr1_wren,
  instr1_IPOff,
  instr1_afterTaken,
  instr1_rT_useF,
  instr1_rT_isV,
  instr1_port,
  instr1_magic,
  instr1_last,
    
  instr2_rT,
  instr2_en,
  instr2_wren,
  instr2_IPOff,
  instr2_afterTaken,
  instr2_rT_useF,
  instr2_rT_isV,
  instr2_port,
  instr2_magic,
  instr2_last,
  
  instr3_rT,
  instr3_en,
  instr3_wren,
  instr3_IPOff,
  instr3_afterTaken,
  instr3_rT_useF,
  instr3_rT_isV,
  instr3_port,
  instr3_magic,
  instr3_last,
  
  instr4_rT,
  instr4_en,
  instr4_wren,
  instr4_IPOff,
  instr4_afterTaken,
  instr4_rT_useF,
  instr4_rT_isV,
  instr4_port,
  instr4_magic,
  instr4_last,
  
  instr5_rT,
  instr5_en,
  instr5_wren,
  instr5_IPOff,
  instr5_afterTaken,
  instr5_rT_useF,
  instr5_rT_isV,
  instr5_port,
  instr5_magic,
  instr5_last,

  instr6_rT,
  instr6_en,
  instr6_wren,
  instr6_IPOff,
  instr6_afterTaken,
  instr6_rT_useF,
  instr6_rT_isV,
  instr6_port,
  instr6_magic,
  instr6_last,

  instr7_rT,
  instr7_en,
  instr7_wren,
  instr7_IPOff,
  instr7_afterTaken,
  instr7_rT_useF,
  instr7_rT_isV,
  instr7_port,
  instr7_magic,
  instr7_last,

  instr8_rT,
  instr8_en,
  instr8_wren,
  instr8_IPOff,
  instr8_afterTaken,
  instr8_rT_useF,
  instr8_rT_isV,
  instr8_port,
  instr8_magic,
  instr8_last,

  instr9_rT,
  instr9_en,
  instr9_wren,
  instr9_IPOff,
  instr9_afterTaken,
  instr9_rT_useF,
  instr9_rT_isV,
  instr9_port,
  instr9_magic,
  instr9_last,
  jump0Type,jump0Pos,jump0Taken,
  jump1Type,jump1Pos,jump1Taken,
  jump0BtbWay,jump0JmpInd,jump0GHT,
  jump1BtbWay,jump1JmpInd,jump1GHT,
  jump0SC,jump0Miss,jump0TbufOnly,
  jump1SC,jump1Miss,jump1TbufOnly,
  instr_fsimd,
  baseIP,
  wrt0,wrt1,wrt2
  );

  backend bck_mod(
  clk,
  clkX,
  rst,
  stall,

  1'b0,
  bundleFeed,
  except,
  exceptIP,
  exceptThread,
  exceptBoth,
  except_due_jump,
  except_flag,
  except_ght,
  
  req_addr,
  req_tlbEn,
  bus_tlb_data,
  bus_tlb_en,
  
  rs0i0_rA,rs0i0_rA_use,rs0i0_rA_useF,rs0i0_rA_isV,rs0i0_rA_isAnyV,
  rs0i0_rB,rs0i0_rB_use,rs0i0_rB_useF,rs0i0_rB_isV,rs0i0_rB_isAnyV,rs0i0_useBConst,
  rs0i0_rT,rs0i0_rT_use,rs0i0_rT_useF,rs0i0_rT_isV, 
  rs0i0_port,
  rs0i0_operation,
  rs0i0_en,
  rs0i0_const,
  rs0i0_index,
  rs0i0_IPRel,
  rs0i0_afterTaken,
  rs0i0_alt,
  rs0i0_alloc,
  rs0i0_allocF,
  rs0i0_allocR,
  rs0i0_lsi,
  rs0i0_ldst_flag,

  rs0i1_rA,rs0i1_rA_use,rs0i1_rA_useF,rs0i1_rA_isV,rs0i1_rA_isAnyV,
  rs0i1_rB,rs0i1_rB_use,rs0i1_rB_useF,rs0i1_rB_isV,rs0i1_rB_isAnyV,rs0i1_useBConst,
  rs0i1_rT,rs0i1_rT_use,rs0i1_rT_useF,rs0i1_rT_isV,
  rs0i1_port,
  rs0i1_operation,
  rs0i1_en,
  rs0i1_const,
  rs0i1_index,
  rs0i1_IPRel,
  rs0i1_afterTaken,
  rs0i1_alloc,
  rs0i1_allocF,
  rs0i1_allocR,
  rs0i1_flagDep,
  rs0i1_lastFl,
  rs0i1_lsi,
  rs0i1_ldst_flag,

  rs0i2_rA,rs0i2_rA_use,rs0i2_rA_useF,rs0i2_rA_isV,rs0i2_rA_isAnyV,
  rs0i2_rB,rs0i2_rB_use,rs0i2_rB_useF,rs0i2_rB_isV,rs0i2_rB_isAnyV,rs0i2_useBConst,
  rs0i2_rT,rs0i2_rT_use,rs0i2_rT_useF,rs0i2_rT_isV,
  rs0i2_port,
  rs0i2_operation,
  rs0i2_en,
  rs0i2_const,
  rs0i2_index,
  rs0i2_IPRel,
  rs0i2_afterTaken,
  rs0i2_alloc,
  rs0i2_allocF,
  rs0i2_allocR,
  rs0i2_flagDep,
  rs0i2_lastFl,

  rs1i0_rA,rs1i0_rA_use,rs1i0_rA_useF,rs1i0_rA_isV,rs1i0_rA_isAnyV,
  rs1i0_rB,rs1i0_rB_use,rs1i0_rB_useF,rs1i0_rB_isV,rs1i0_rB_isAnyV,rs1i0_useBConst,
  rs1i0_rT,rs1i0_rT_use,rs1i0_rT_useF,rs1i0_rT_isV,
  rs1i0_port,
  rs1i0_operation,
  rs1i0_en,
  rs1i0_const,
  rs1i0_index,
  rs1i0_IPRel,
  rs1i0_afterTaken,
  rs1i0_alt,
  rs1i0_alloc,
  rs1i0_allocF,
  rs1i0_allocR,
  rs1i0_lsi,
  rs1i0_ldst_flag,

  rs1i1_rA,rs1i1_rA_use,rs1i1_rA_useF,rs1i1_rA_isV,rs1i1_rA_isAnyV,
  rs1i1_rB,rs1i1_rB_use,rs1i1_rB_useF,rs1i1_rB_isV,rs1i1_rB_isAnyV,rs1i1_useBConst,
  rs1i1_rT,rs1i1_rT_use,rs1i1_rT_useF,rs1i1_rT_isV,
  rs1i1_port,
  rs1i1_operation,
  rs1i1_en,
  rs1i1_const,
  rs1i1_index,
  rs1i1_IPRel,
  rs1i1_afterTaken,
  rs1i1_alloc,
  rs1i1_allocF,
  rs1i1_allocR,
  rs1i1_flagDep,
  rs1i1_lastFl,
  rs1i1_lsi,
  rs1i1_ldst_flag,

  rs1i2_rA,rs1i2_rA_use,rs1i2_rA_useF,rs1i2_rA_isV,rs1i2_rA_isAnyV,
  rs1i2_rB,rs1i2_rB_use,rs1i2_rB_useF,rs1i2_rB_isV,rs1i2_rB_isAnyV,rs1i2_useBConst,
  rs1i2_rT,rs1i2_rT_use,rs1i2_rT_useF,rs1i2_rT_isV,
  rs1i2_port,
  rs1i2_operation,
  rs1i2_en,
  rs1i2_const,
  rs1i2_index,
  rs1i2_IPRel,
  rs1i2_afterTaken,
  rs1i2_alloc,
  rs1i2_allocF,
  rs1i2_allocR,
  rs1i2_flagDep,
  rs1i2_lastFl,

  rs2i0_rA,rs2i0_rA_use,rs2i0_rA_useF,rs2i0_rA_isV,rs2i0_rA_isAnyV,
  rs2i0_rB,rs2i0_rB_use,rs2i0_rB_useF,rs2i0_rB_isV,rs2i0_rB_isAnyV,rs2i0_useBConst,
  rs2i0_rT,rs2i0_rT_use,rs2i0_rT_useF,rs2i0_rT_isV,
  rs2i0_port,
  rs2i0_operation,
  rs2i0_en,
  rs2i0_const,
  rs2i0_index,
  rs2i0_IPRel,
  rs2i0_afterTaken,
  rs2i0_alt,
  rs2i0_alloc,
  rs2i0_allocF,
  rs2i0_allocR,
  rs2i0_lsi,
  rs2i0_ldst_flag,

  rs2i1_rA,rs2i1_rA_use,rs2i1_rA_useF,rs2i1_rA_isV,rs2i1_rA_isAnyV,
  rs2i1_rB,rs2i1_rB_use,rs2i1_rB_useF,rs2i1_rB_isV,rs2i1_rB_isAnyV,rs2i1_useBConst,
  rs2i1_rT,rs2i1_rT_use,rs2i1_rT_useF,rs2i1_rT_isV,
  rs2i1_port,
  rs2i1_operation,
  rs2i1_en,
  rs2i1_const,
  rs2i1_index,
  rs2i1_IPRel,
  rs2i1_afterTaken,
  rs2i1_alloc,
  rs2i1_allocF,
  rs2i1_allocR,
  rs2i1_flagDep,
  rs2i1_lastFl,
  rs2i1_lsi,
  rs2i1_ldst_flag,

  rs2i2_rA,rs2i2_rA_use,rs2i2_rA_useF,rs2i2_rA_isV,rs2i2_rA_isAnyV,
  rs2i2_rB,rs2i2_rB_use,rs2i2_rB_useF,rs2i2_rB_isV,rs2i2_rB_isAnyV,rs2i2_useBConst,
  rs2i2_rT,rs2i2_rT_use,rs2i2_rT_useF,rs2i2_rT_isV,
  rs2i2_port,
  rs2i2_operation,
  rs2i2_en,
  rs2i2_const,
  rs2i2_index,
  rs2i2_IPRel,
  rs2i2_afterTaken,
  rs2i2_alloc,
  rs2i2_allocF,
  rs2i2_allocR,
  rs2i2_flagDep,
  rs2i2_lastFl,

//end reordered small instructions
//begin instructions in program order
  instr0_rT, 
  instr0_en,
  instr0_wren, 
  instr0_IPOff,
  instr0_afterTaken,
  instr0_rT_useF,
  instr0_rT_isV,
  instr0_port,
  instr0_magic,
  instr0_last,
  
  instr1_rT,
  instr1_en,
  instr1_wren,
  instr1_IPOff,
  instr1_afterTaken,
  instr1_rT_useF,
  instr1_rT_isV,
  instr1_port,
  instr1_magic,
  instr1_last,
    
  instr2_rT,
  instr2_en,
  instr2_wren,
  instr2_IPOff,
  instr2_afterTaken,
  instr2_rT_useF,
  instr2_rT_isV,
  instr2_port,
  instr2_magic,
  instr2_last,
  
  instr3_rT,
  instr3_en,
  instr3_wren,
  instr3_IPOff,
  instr3_afterTaken,
  instr3_rT_useF,
  instr3_rT_isV,
  instr3_port,
  instr3_magic,
  instr3_last,
  
  instr4_rT,
  instr4_en,
  instr4_wren,
  instr4_IPOff,
  instr4_afterTaken,
  instr4_rT_useF,
  instr4_rT_isV,
  instr4_port,
  instr4_magic,
  instr4_last,
  
  instr5_rT,
  instr5_en,
  instr5_wren,
  instr5_IPOff,
  instr5_afterTaken,
  instr5_rT_useF,
  instr5_rT_isV,
  instr5_port,
  instr5_magic,
  instr5_last,

  instr6_rT,
  instr6_en,
  instr6_wren,
  instr6_IPOff,
  instr6_afterTaken,
  instr6_rT_useF,
  instr6_rT_isV,
  instr6_port,
  instr6_magic,
  instr6_last,

  instr7_rT,
  instr7_en,
  instr7_wren,
  instr7_IPOff,
  instr7_afterTaken,
  instr7_rT_useF,
  instr7_rT_isV,
  instr7_port,
  instr7_magic,
  instr7_last,

  instr8_rT,
  instr8_en,
  instr8_wren,
  instr8_IPOff,
  instr8_afterTaken,
  instr8_rT_useF,
  instr8_rT_isV,
  instr8_port,
  instr8_magic,
  instr8_last,

  instr9_rT,
  instr9_en,
  instr9_wren,
  instr9_IPOff,
  instr9_afterTaken,
  instr9_rT_useF,
  instr9_rT_isV,
  instr9_port,
  instr9_magic,
  instr9_last,

  jump0Type,jump0Pos,jump0Taken,btbl_IP0,
  jump1Type,jump1Pos,jump1Taken,btbl_IP1,
  jump0BtbWay,jump0JmpInd,jump0GHT,
  jump1BtbWay,jump1JmpInd,jump1GHT,
  jump0SC,jump0Miss,jump0TbufOnly,
  jump1SC,jump1Miss,jump1TbufOnly,
  instr_fsimd,
  baseIP,
  wrt0,wrt1,wrt2,

  jupd0_en,jupdt0_en,jupd0_ght_en,jupd0_addr,jupd0_baddr,jupd0_sc,jupd0_tk,
  jupd1_en,jupdt1_en,jupd1_ght_en,jupd1_addr,jupd1_baddr,jupd1_sc,jupd1_tk,

  insBus_en,
  insBus_req,
  insBus_dirty,
  insBus_exclusive,
  insBus_data,
  reqBus_en,
  reqBus_addr,
  reqBus_req,
  reqBus_want_excl
  );
  
  dummyL2 l2_mo(
  clk,
  rst,
  insBus_en,
  insBus_req[3:0],
  insBus_dirty,
  insBus_exclusive,
  insBus_data,
  reqBus_en,
  reqBus_addr,
  reqBus_req[3:0],
  reqBus_want_excl
  );
  
  assign instrFed=front_mod.instrFed;
  assign read_data=front_mod.read_data;
  assign insBus_req[9:4]=6'b0;
  
  always #50 begin
      clk=~clk;
  end

  always #25 begin
      clkX=~clkX;
      #25;
  end
  initial begin
      $monitor("produce bundle(%d): $%H",instrFed,read_data_strip);
      $monitor("instr(%d) : $%H",iAvail[0],instr0);
  end
  always @(req_tlbEn) #0  if (req_tlbEn) $display("get tlb: $%H",{req_addr[31:0],12'b0});
  always @(req_en)  #0 if (req_en) begin
      $display("fetch  : $%H",{req_addr,7'b0});
      //    $display("fetch data   : $%H",bus_data_strip);
  end
  always @(except,exceptIP) begin
     #0 if (except) $display("except $%H",{exceptIP,1'b0}); 
  end

  always @(posedge clk) begin
      wdata_reg[0]<=bck_mod.dc_wdata[0];
      wdata_reg[1]<=bck_mod.dc_wdata[1];
      wdata_reg2[0]<=wdata_reg[0];
      wdata_reg2[1]<=wdata_reg[1];
      wdata_reg3[0]<=wdata_reg2[0];
      wdata_reg3[1]<=wdata_reg2[1];
  end
  always @(bck_mod.FU0Hit) #0 $display("FU0Hit=%d",bck_mod.FU0Hit);
  always @(bck_mod.FU1Hit) #0 $display("FU1Hit=%d",bck_mod.FU1Hit);
  always @(bck_mod.FU2Hit) #0 $display("FU2Hit=%d",bck_mod.FU2Hit);
  always @(bck_mod.FU3Hit) #0 $display("FU3Hit=%d",bck_mod.FU3Hit);
  
  always @(bck_mod.FUwen[0],bck_mod.FUreg[0]) begin
      #0
      if (bck_mod.FUwen[0]) begin
          $display("FU0[%h]",bck_mod.FUreg[0]);
      end
  end
  always @(bck_mod.FUwen[1],bck_mod.FUreg[1]) begin
      #0
      if (bck_mod.FUwen[1]) begin
          $display("FU1[%h]",bck_mod.FUreg[1]);
      end
  end
  always @(bck_mod.FUwen[2],bck_mod.FUreg[2]) begin
      #0
      if (bck_mod.FUwen[2]) begin
          $display("FU2[%h]",bck_mod.FUreg[2]);
      end
  end
  always @(bck_mod.FUwen[3],bck_mod.FUreg[3]) begin
      #0
      if (bck_mod.FUwen[3]) begin
          $display("FU3[%h]",bck_mod.FUreg[3]);
      end
  end

  always @(bck_mod.FUwen[4],bck_mod.FUreg[4]) begin
      #0
      if (bck_mod.FUwen[4]) begin
          $display("FU4[%h]",bck_mod.FUreg[4]);
      end
  end

  always @(bck_mod.FUwen[5],bck_mod.FUreg[5]) begin
      #0
      if (bck_mod.FUwen[5]) begin
          $display("FU5[%h]",bck_mod.FUreg[5]);
      end
  end

  always @(bck_mod.FUwen[6],bck_mod.FUreg[6]) begin
      #0
      if (bck_mod.FUwen[6]) begin
          $display("FU6[%h]",bck_mod.FUreg[6]);
      end
  end

  always @(bck_mod.FUwen[7],bck_mod.FUreg[7]) begin
      #0
      if (bck_mod.FUwen[7]) begin
          $display("FU7[%h]",bck_mod.FUreg[7]);
      end
  end

  always @(bck_mod.FUwen[8],bck_mod.FUreg[8]) begin
      #0
      if (bck_mod.FUwen[8]) begin
          $display("FU8[%h]",bck_mod.FUreg[8]);
      end
  end

  always @(bck_mod.FUwen[9],bck_mod.FUreg[9]) begin
      #0
      if (bck_mod.FUwen[9]) begin
          $display("FU9[%h]",bck_mod.FUreg[9]);
      end
  end

  always @* begin
    ret_ebx_en=0;
    if (bck_mod.retire0_enG && bck_mod.retire0_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=bck_mod.ret_dataA[0]; end
    if (bck_mod.retire1_enG && bck_mod.retire1_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=bck_mod.ret_dataA[1]; end
    if (bck_mod.retire2_enG && bck_mod.retire2_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=bck_mod.ret_dataA[2]; end
    if (bck_mod.retire3_enG && bck_mod.retire3_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=bck_mod.ret_dataA[3]; end
    if (bck_mod.retire4_enG && bck_mod.retire4_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=bck_mod.ret_dataA[4]; end
    if (bck_mod.retire5_enG && bck_mod.retire5_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=bck_mod.ret_dataA[5]; end
    if (bck_mod.retire6_enG && bck_mod.retire6_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=bck_mod.ret_dataA[6]; end
    if (bck_mod.retire7_enG && bck_mod.retire7_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=bck_mod.ret_dataA[7]; end
    if (bck_mod.retire8_enG && bck_mod.retire8_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=bck_mod.ret_dataA[8]; end
  end
 
  always @* begin
    ret_r8d_en=0;
    if (bck_mod.retire0_enG && bck_mod.retire0_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=bck_mod.ret_dataA[0]; end
    if (bck_mod.retire1_enG && bck_mod.retire1_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=bck_mod.ret_dataA[1]; end
    if (bck_mod.retire2_enG && bck_mod.retire2_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=bck_mod.ret_dataA[2]; end
    if (bck_mod.retire3_enG && bck_mod.retire3_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=bck_mod.ret_dataA[3]; end
    if (bck_mod.retire4_enG && bck_mod.retire4_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=bck_mod.ret_dataA[4]; end
    if (bck_mod.retire5_enG && bck_mod.retire5_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=bck_mod.ret_dataA[5]; end
    if (bck_mod.retire6_enG && bck_mod.retire6_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=bck_mod.ret_dataA[6]; end
    if (bck_mod.retire7_enG && bck_mod.retire7_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=bck_mod.ret_dataA[7]; end
    if (bck_mod.retire8_enG && bck_mod.retire8_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=bck_mod.ret_dataA[8]; end
  end

  
  always @(posedge clk)
  begin
    rst<=1'b0;
    
    if (rst) begin
   //     bus_tlb_data<=37'b0;
        bus_tlb_slot<=8'b0;
   //     bus_tlb_en<=1'b0;
    end else begin
        if (req_tlbEn) begin
     //       bus_tlb_data<=bus_tlb_data_d;
            bus_tlb_slot<=req_slot;
     //       bus_tlb_en<=1'b1;
       // end else begin
         //   bus_tlb_en<=1'b0;
        end
        //if (req_en) bus_slot<=req_slot;
    end
  end
endmodule



