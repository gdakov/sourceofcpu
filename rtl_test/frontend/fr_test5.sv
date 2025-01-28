`include "../../rtl/struct.sv"


module fr_test5;
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
  wire [5:0] wrtII=core_mod.bck_mod.PSTQ_en[0] ? core_mod.bck_mod.PSTQ_data[0][117:112] : core_mod.bck_mod.PSTQ_data[1][117:112];
  wire [5:0] dataAII=core_mod.bck_mod.LSQ_dataA0[117:112];
  reg [63:0] wdata_reg[1:0];
  reg [63:0] wdata_reg2[1:0];
  reg [63:0] wdata_reg3[1:0];

  reg clk=1'b0;
//  reg clkX=1'b1;
  reg rst=1'b1;

  wire [`rbus_width-1:0] rbusIn_signals;
  wire [9:0] rbusIn_src_req;
  wire [9:0] rbusIn_dst_req;
  wire [36:0] rbusIn_address;
  wire [`rbus_width-1:0] rbusOut_signals;
  wire [9:0] rbusOut_src_req;
  wire [9:0] rbusOut_dst_req;
  wire [36:0] rbusOut_address;
  wire rbusOut_want;
  wire rbusOut_can;
  wire [4:0] rbusOut_sz;
  wire [4:0] rbusOut_bank0;
  wire [1:0] rbusOut_low;
  wire [`rbusD_width-1:0] rbusDIn_signals;
  wire [9:0] rbusDIn_src_req;
  wire [9:0] rbusDIn_dst_req;
  wire [511:0] rbusDIn_data;
  wire [`rbusD_width-1:0] rbusDOut_signals;
  wire [9:0] rbusDOut_src_req;
  wire [9:0] rbusDOut_dst_req;
  wire [511:0] rbusDOut_data;
  wire rbusDOut_can;
  wire rbusDOut_want;
  
  wire insBus_en;
  reg insBus_en_reg;

  reg ret_ebx_en;
  reg [63:0] ret_ebx_data;
  
  reg ret_r8d_en;
  reg [63:0] ret_r8d_data;
  
  reg ret_xmm3_en;
  reg [131:0] ret_xmm3_data;
  
  reg ret_xmm4_en;
  reg [131:0] ret_xmm4_data;
  
  reg ret_xmm5_en;
  reg [131:0] ret_xmm5_data;
  
  reg ret_xmmf8_en;
  reg [63:0] ret_xmmf8_data;
  
  integer ind;
  
  dummyL2 l2_mo(
  .clk(clk),
  .rst(rst),
  .insBus_en(insBus_en),
  .insBus_req(rbusDIn_dst_req[4:0]),
  .insBus_dirty(rbusDIn_signals[`rbusD_dirty]),
  .insBus_exclusive(rbusDIn_signals[`rbusD_excl]),
  .insBus_data(rbusDIn_data),
  .reqBus_en(rbusOut_want&rbusOut_can),
  .reqBus_addr(rbusOut_address),
  .reqBus_req(rbusOut_src_req[4:0]),
  .reqBus_want_excl(~rbusOut_signals[`rbus_code])
  );
  

  
  heptane_core #(0) core_mod(
  clk,
  rst,
  rbusIn_signals,rbusIn_src_req,rbusIn_dst_req,rbusIn_address,
  rbusOut_signals,rbusOut_src_req,rbusOut_dst_req,rbusOut_address,rbusOut_can,rbusOut_want,rbusOut_sz,rbusOut_bank0,rbusOut_low,
  rbusDIn_signals,rbusDIn_src_req,rbusDIn_dst_req,rbusDIn_data,
  rbusDOut_signals,rbusDOut_src_req,rbusDOut_dst_req,rbusDOut_data,rbusDOut_can,rbusDOut_want
  );

  assign rbusOut_can=1'b1;
  
  assign rbusDIn_dst_req[9:5]=5'd0;
  assign rbusDIn_src_req=10'h3ff;
  assign rbusDIn_signals[`rbusD_used]=insBus_en|insBus_en_reg;
  assign rbusDIn_signals[`rbusD_second]=insBus_en_reg;
  assign rbusDIn_signals[`rbusD_mem_reply]=1'b1;
  assign rbusDIn_signals[`rbusD_cc_reply]=1'b0;
  assign rbusDIn_signals[`rbusD_write_back]=1'b0;
  assign rbusDIn_signals[`rbusD_bcast]=1'b0;

  assign rbusIn_signals={`rbus_width{1'b0}};
  assign rbusIn_src_req=10'h3ff;
  assign rbusIn_dst_req=10'h3ff;
  assign rbusIn_address=10'h3ff;

  function [63:0] fextr;
    input [65:0] din;
    begin
        fextr={din[64],din[65],din[62:53],din[52:33],din[31:0]};
	if ({din[65],din[63:53]}<(1023-53)) fextr=64'b0;
    end
  endfunction
   
  
  
//  assign instrFed=core_mod.front_mod.instrFed;
//  assign read_data=core_mod.front_mod.read_data;
  
  always #50 begin
      clk=~clk;
  end

  initial begin
      $monitor("produce bundle(%d): $%H",core_mod.instrFed,core_mod.read_data_strip);
  //    $monitor("instr(%d) : $%H",iAvail[0],instr0);
      $dumpfile("dump.lxt");
      $dumpvars(0,core_mod.bck_mod);
      for(ind=0;ind<10;ind=ind+1) begin
	  $dumpvars(0,core_mod.bck_mod.FU[ind]);
	  $dumpvars(0,core_mod.bck_mod.FUreg[ind]);
	  $dumpvars(0,core_mod.bck_mod.FUwen[ind]);
	  $dumpvars(0,core_mod.bck_mod.FUFH[ind]);
	  $dumpvars(0,core_mod.bck_mod.FUFL[ind]);
	  $dumpvars(0,core_mod.bck_mod.FUVH[ind]);
	  $dumpvars(0,core_mod.bck_mod.FUVL[ind]);
      end
      #200000 $finish();
  end
  always @(core_mod.req_tlbEn) #0  if (core_mod.req_tlbEn) $display("get tlb: $%H",{core_mod.req_addr[31:0],12'b0});
  always @(core_mod.req_en)  #0 if (core_mod.req_en) begin
      $display("fetch  : $%H",{core_mod.req_addr,7'b0});
  end
  always @(core_mod.insBus_en)  #0 if (core_mod.insBus_en) begin
      $display("fetch data   : $%H",core_mod.insBus_data);
  end
  always @(core_mod.except,core_mod.exceptIP) begin
     #0 if (core_mod.except) $display("except $%H",{core_mod.exceptIP,1'b0}); 
  end

  always @(posedge clk) begin
      wdata_reg[0]<=core_mod.bck_mod.dc_wdata[0];
      wdata_reg[1]<=core_mod.bck_mod.dc_wdata[1];
      wdata_reg2[0]<=wdata_reg[0];
      wdata_reg2[1]<=wdata_reg[1];
      wdata_reg3[0]<=wdata_reg2[0];
      wdata_reg3[1]<=wdata_reg2[1];
  end
  always @(core_mod.bck_mod.FU0Hit) #0 $display("FU0Hit=%d",core_mod.bck_mod.FU0Hit);
  always @(core_mod.bck_mod.FU1Hit) #0 $display("FU1Hit=%d",core_mod.bck_mod.FU1Hit);
  always @(core_mod.bck_mod.FU2Hit) #0 $display("FU2Hit=%d",core_mod.bck_mod.FU2Hit);
  always @(core_mod.bck_mod.FU3Hit) #0 $display("FU3Hit=%d",core_mod.bck_mod.FU3Hit);
  

  always @* begin
    ret_ebx_en=0;
    if (core_mod.bck_mod.retire0_enG && core_mod.bck_mod.retire0_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=core_mod.bck_mod.ret_dataA[0]; end
    if (core_mod.bck_mod.retire1_enG && core_mod.bck_mod.retire1_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=core_mod.bck_mod.ret_dataA[1]; end
    if (core_mod.bck_mod.retire2_enG && core_mod.bck_mod.retire2_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=core_mod.bck_mod.ret_dataA[2]; end
    if (core_mod.bck_mod.retire3_enG && core_mod.bck_mod.retire3_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=core_mod.bck_mod.ret_dataA[3]; end
    if (core_mod.bck_mod.retire4_enG && core_mod.bck_mod.retire4_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=core_mod.bck_mod.ret_dataA[4]; end
    if (core_mod.bck_mod.retire5_enG && core_mod.bck_mod.retire5_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=core_mod.bck_mod.ret_dataA[5]; end
    if (core_mod.bck_mod.retire6_enG && core_mod.bck_mod.retire6_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=core_mod.bck_mod.ret_dataA[6]; end
    if (core_mod.bck_mod.retire7_enG && core_mod.bck_mod.retire7_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=core_mod.bck_mod.ret_dataA[7]; end
    if (core_mod.bck_mod.retire8_enG && core_mod.bck_mod.retire8_rT==6'd2) begin ret_ebx_en=1'b1; ret_ebx_data=core_mod.bck_mod.ret_dataA[8]; end
  end
 
  always @* begin
    ret_r8d_en=0;
    if (core_mod.bck_mod.retire0_enG && core_mod.bck_mod.retire0_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=core_mod.bck_mod.ret_dataA[0]; end
    if (core_mod.bck_mod.retire1_enG && core_mod.bck_mod.retire1_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=core_mod.bck_mod.ret_dataA[1]; end
    if (core_mod.bck_mod.retire2_enG && core_mod.bck_mod.retire2_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=core_mod.bck_mod.ret_dataA[2]; end
    if (core_mod.bck_mod.retire3_enG && core_mod.bck_mod.retire3_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=core_mod.bck_mod.ret_dataA[3]; end
    if (core_mod.bck_mod.retire4_enG && core_mod.bck_mod.retire4_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=core_mod.bck_mod.ret_dataA[4]; end
    if (core_mod.bck_mod.retire5_enG && core_mod.bck_mod.retire5_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=core_mod.bck_mod.ret_dataA[5]; end
    if (core_mod.bck_mod.retire6_enG && core_mod.bck_mod.retire6_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=core_mod.bck_mod.ret_dataA[6]; end
    if (core_mod.bck_mod.retire7_enG && core_mod.bck_mod.retire7_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=core_mod.bck_mod.ret_dataA[7]; end
    if (core_mod.bck_mod.retire8_enG && core_mod.bck_mod.retire8_rT==6'd9) begin ret_r8d_en=1'b1; ret_r8d_data=core_mod.bck_mod.ret_dataA[8]; end
  end

  always @* begin
    ret_xmm3_en=0;
    if (core_mod.bck_mod.retire0_enV_reg && core_mod.bck_mod.retire0_rT_reg==6'h13) 
      begin ret_xmm3_en=1'b1; ret_xmm3_data={core_mod.bck_mod.ret_dataAVH[0],core_mod.bck_mod.ret_dataAVL[0]}; end
    if (core_mod.bck_mod.retire1_enV_reg && core_mod.bck_mod.retire1_rT_reg==6'h13) 
      begin ret_xmm3_en=1'b1; ret_xmm3_data={core_mod.bck_mod.ret_dataAVH[1],core_mod.bck_mod.ret_dataAVL[1]}; end
    if (core_mod.bck_mod.retire2_enV_reg && core_mod.bck_mod.retire2_rT_reg==6'h13) 
      begin ret_xmm3_en=1'b1; ret_xmm3_data={core_mod.bck_mod.ret_dataAVH[2],core_mod.bck_mod.ret_dataAVL[2]}; end
    if (core_mod.bck_mod.retire3_enV_reg && core_mod.bck_mod.retire3_rT_reg==6'h13) 
      begin ret_xmm3_en=1'b1; ret_xmm3_data={core_mod.bck_mod.ret_dataAVH[3],core_mod.bck_mod.ret_dataAVL[3]}; end
    if (core_mod.bck_mod.retire4_enV_reg && core_mod.bck_mod.retire4_rT_reg==6'h13) 
      begin ret_xmm3_en=1'b1; ret_xmm3_data={core_mod.bck_mod.ret_dataAVH[4],core_mod.bck_mod.ret_dataAVL[4]}; end
    if (core_mod.bck_mod.retire5_enV_reg && core_mod.bck_mod.retire5_rT_reg==6'h13) 
      begin ret_xmm3_en=1'b1; ret_xmm3_data={core_mod.bck_mod.ret_dataAVH[5],core_mod.bck_mod.ret_dataAVL[5]}; end
    if (core_mod.bck_mod.retire6_enV_reg && core_mod.bck_mod.retire6_rT_reg==6'h13) 
      begin ret_xmm3_en=1'b1; ret_xmm3_data={core_mod.bck_mod.ret_dataAVH[6],core_mod.bck_mod.ret_dataAVL[6]}; end
    if (core_mod.bck_mod.retire7_enV_reg && core_mod.bck_mod.retire7_rT_reg==6'h13) 
      begin ret_xmm3_en=1'b1; ret_xmm3_data={core_mod.bck_mod.ret_dataAVH[7],core_mod.bck_mod.ret_dataAVL[7]}; end
    if (core_mod.bck_mod.retire8_enV_reg && core_mod.bck_mod.retire8_rT_reg==6'h13) 
      begin ret_xmm3_en=1'b1; ret_xmm3_data={core_mod.bck_mod.ret_dataAVH[8],core_mod.bck_mod.ret_dataAVL[8]}; end
  end

  always @* begin
    ret_xmm4_en=0;
    if (core_mod.bck_mod.retire0_enV_reg && core_mod.bck_mod.retire0_rT_reg==6'h14) 
      begin ret_xmm4_en=1'b1; ret_xmm4_data={core_mod.bck_mod.ret_dataAVH[0],core_mod.bck_mod.ret_dataAVL[0]}; end
    if (core_mod.bck_mod.retire1_enV_reg && core_mod.bck_mod.retire1_rT_reg==6'h14) 
      begin ret_xmm4_en=1'b1; ret_xmm4_data={core_mod.bck_mod.ret_dataAVH[1],core_mod.bck_mod.ret_dataAVL[1]}; end
    if (core_mod.bck_mod.retire2_enV_reg && core_mod.bck_mod.retire2_rT_reg==6'h14) 
      begin ret_xmm4_en=1'b1; ret_xmm4_data={core_mod.bck_mod.ret_dataAVH[2],core_mod.bck_mod.ret_dataAVL[2]}; end
    if (core_mod.bck_mod.retire3_enV_reg && core_mod.bck_mod.retire3_rT_reg==6'h14) 
      begin ret_xmm4_en=1'b1; ret_xmm4_data={core_mod.bck_mod.ret_dataAVH[3],core_mod.bck_mod.ret_dataAVL[3]}; end
    if (core_mod.bck_mod.retire4_enV_reg && core_mod.bck_mod.retire4_rT_reg==6'h14) 
      begin ret_xmm4_en=1'b1; ret_xmm4_data={core_mod.bck_mod.ret_dataAVH[4],core_mod.bck_mod.ret_dataAVL[4]}; end
    if (core_mod.bck_mod.retire5_enV_reg && core_mod.bck_mod.retire5_rT_reg==6'h14) 
      begin ret_xmm4_en=1'b1; ret_xmm4_data={core_mod.bck_mod.ret_dataAVH[5],core_mod.bck_mod.ret_dataAVL[5]}; end
    if (core_mod.bck_mod.retire6_enV_reg && core_mod.bck_mod.retire6_rT_reg==6'h14) 
      begin ret_xmm4_en=1'b1; ret_xmm4_data={core_mod.bck_mod.ret_dataAVH[6],core_mod.bck_mod.ret_dataAVL[6]}; end
    if (core_mod.bck_mod.retire7_enV_reg && core_mod.bck_mod.retire7_rT_reg==6'h14) 
      begin ret_xmm4_en=1'b1; ret_xmm4_data={core_mod.bck_mod.ret_dataAVH[7],core_mod.bck_mod.ret_dataAVL[7]}; end
    if (core_mod.bck_mod.retire8_enV_reg && core_mod.bck_mod.retire8_rT_reg==6'h14) 
      begin ret_xmm4_en=1'b1; ret_xmm4_data={core_mod.bck_mod.ret_dataAVH[8],core_mod.bck_mod.ret_dataAVL[8]}; end
  end

  always @* begin
    ret_xmm5_en=0;
    if (core_mod.bck_mod.retire0_enV_reg && core_mod.bck_mod.retire0_rT_reg==6'h15) 
      begin ret_xmm5_en=1'b1; ret_xmm5_data={core_mod.bck_mod.ret_dataAVH[0],core_mod.bck_mod.ret_dataAVL[0]}; end
    if (core_mod.bck_mod.retire1_enV_reg && core_mod.bck_mod.retire1_rT_reg==6'h15) 
      begin ret_xmm5_en=1'b1; ret_xmm5_data={core_mod.bck_mod.ret_dataAVH[1],core_mod.bck_mod.ret_dataAVL[1]}; end
    if (core_mod.bck_mod.retire2_enV_reg && core_mod.bck_mod.retire2_rT_reg==6'h15) 
      begin ret_xmm5_en=1'b1; ret_xmm5_data={core_mod.bck_mod.ret_dataAVH[2],core_mod.bck_mod.ret_dataAVL[2]}; end
    if (core_mod.bck_mod.retire3_enV_reg && core_mod.bck_mod.retire3_rT_reg==6'h15) 
      begin ret_xmm5_en=1'b1; ret_xmm5_data={core_mod.bck_mod.ret_dataAVH[3],core_mod.bck_mod.ret_dataAVL[3]}; end
    if (core_mod.bck_mod.retire4_enV_reg && core_mod.bck_mod.retire4_rT_reg==6'h15) 
      begin ret_xmm5_en=1'b1; ret_xmm5_data={core_mod.bck_mod.ret_dataAVH[4],core_mod.bck_mod.ret_dataAVL[4]}; end
    if (core_mod.bck_mod.retire5_enV_reg && core_mod.bck_mod.retire5_rT_reg==6'h15) 
      begin ret_xmm5_en=1'b1; ret_xmm5_data={core_mod.bck_mod.ret_dataAVH[5],core_mod.bck_mod.ret_dataAVL[5]}; end
    if (core_mod.bck_mod.retire6_enV_reg && core_mod.bck_mod.retire6_rT_reg==6'h15) 
      begin ret_xmm5_en=1'b1; ret_xmm5_data={core_mod.bck_mod.ret_dataAVH[6],core_mod.bck_mod.ret_dataAVL[6]}; end
    if (core_mod.bck_mod.retire7_enV_reg && core_mod.bck_mod.retire7_rT_reg==6'h15) 
      begin ret_xmm5_en=1'b1; ret_xmm5_data={core_mod.bck_mod.ret_dataAVH[7],core_mod.bck_mod.ret_dataAVL[7]}; end
    if (core_mod.bck_mod.retire8_enV_reg && core_mod.bck_mod.retire8_rT_reg==6'h15) 
      begin ret_xmm5_en=1'b1; ret_xmm5_data={core_mod.bck_mod.ret_dataAVH[8],core_mod.bck_mod.ret_dataAVL[8]}; end
  end
  
  always @* begin
    ret_xmmf8_en=0;
    if (core_mod.bck_mod.retire0_enF_reg2 && core_mod.bck_mod.retire0_rT_reg2==6'h18) 
      begin ret_xmmf8_en=1'b1; ret_xmmf8_data=fextr(core_mod.bck_mod.ret_dataAFL[0]); end
    if (core_mod.bck_mod.retire1_enF_reg2 && core_mod.bck_mod.retire1_rT_reg2==6'h18) 
      begin ret_xmmf8_en=1'b1; ret_xmmf8_data=fextr(core_mod.bck_mod.ret_dataAFL[1]); end
    if (core_mod.bck_mod.retire2_enF_reg2 && core_mod.bck_mod.retire2_rT_reg2==6'h18) 
      begin ret_xmmf8_en=1'b1; ret_xmmf8_data=fextr(core_mod.bck_mod.ret_dataAFL[2]); end
    if (core_mod.bck_mod.retire3_enF_reg2 && core_mod.bck_mod.retire3_rT_reg2==6'h18) 
      begin ret_xmmf8_en=1'b1; ret_xmmf8_data=fextr(core_mod.bck_mod.ret_dataAFL[3]); end
    if (core_mod.bck_mod.retire4_enF_reg2 && core_mod.bck_mod.retire4_rT_reg2==6'h18) 
      begin ret_xmmf8_en=1'b1; ret_xmmf8_data=fextr(core_mod.bck_mod.ret_dataAFL[4]); end
    if (core_mod.bck_mod.retire5_enF_reg2 && core_mod.bck_mod.retire5_rT_reg2==6'h18) 
      begin ret_xmmf8_en=1'b1; ret_xmmf8_data=fextr(core_mod.bck_mod.ret_dataAFL[5]); end
    if (core_mod.bck_mod.retire6_enF_reg2 && core_mod.bck_mod.retire6_rT_reg2==6'h18) 
      begin ret_xmmf8_en=1'b1; ret_xmmf8_data=fextr(core_mod.bck_mod.ret_dataAFL[6]); end
    if (core_mod.bck_mod.retire7_enF_reg2 && core_mod.bck_mod.retire7_rT_reg2==6'h18) 
      begin ret_xmmf8_en=1'b1; ret_xmmf8_data=fextr(core_mod.bck_mod.ret_dataAFL[7]); end
    if (core_mod.bck_mod.retire8_enF_reg2 && core_mod.bck_mod.retire8_rT_reg2==6'h18) 
      begin ret_xmmf8_en=1'b1; ret_xmmf8_data=fextr(core_mod.bck_mod.ret_dataAFL[8]); end
  end
  
  always @(posedge clk)
  begin
      rst<=1'b0;
      if (rst) insBus_en_reg<=1'b0;
      else insBus_en_reg<=insBus_en;
  end
endmodule



