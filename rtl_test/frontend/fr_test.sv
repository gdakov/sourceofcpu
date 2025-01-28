`include "../../rtl/common.sv"


module fr_test;
  localparam PHYS_WIDTH=44;
  localparam VIRT_WIDTH=64;
  localparam IP_WIDTH=48;
  localparam [31:0] INIT_IP=32'h20;
  localparam BUS_BANK=`dcache1_data_width;
  localparam BUS_WIDTH=BUS_BANK*8;
  localparam DATA_WIDTH=65*4;
  localparam INSTR_WIDTH=80;

  reg clk=1'b0;
  reg rst=1'b1;
  reg fstall=1'b0;
  wire [BUS_WIDTH-1:0] bus_data;
  reg [7:0] bus_slot=8'B0;
  wire bus_en;
  wire jupd;
  
  wire [36:0] req_addr;
  wire [7:0] req_slot;
  wire req_en;
  wire req_tlbEn;

  reg [`ctlbData_width-1:0] bus_tlb_data;
  reg [7:0] bus_tlb_slot;
  reg bus_tlb_en;

  wire [DATA_WIDTH-1:0] read_data;
  wire instrFed;
  wire [255:0] read_data_strip;
  
  wire except;
  
  reg had_except;
  
  reg [VIRT_WIDTH-2:0] exceptIP=INIT_IP>>1;

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

  wire exceptThread=1'b0;
  wire [5:0] exceptTrceAddr=6'b0;
  wire [4:0] exceptTrceAddrLow=5'b0;
  wire jupd0_en=jupd;
  wire jupdt0_en=1'b0;
  wire jupd0_ght_en=1'b1;
  wire [15:0] jupd0_addr=16'b0;
  wire [12:0] jupd0_baddr={2'd0,8'h01,extra0[`instrQ_btb_way]};
  wire [1:0] jupd0_sc=2'b11;
  wire jupd0_tk=1'b1;
  wire jupd1_en=1'b0;
  wire jupdt1_en=1'b0;
  wire jupd1_ght_en=1'b0;
  wire [15:0] jupd1_addr=16'b0;
  wire [12:0] jupd1_baddr=13'b0;
  wire [1:0] jupd1_sc=2'b0;
  wire jupd1_tk=1'b0;

  reg jupd_reg,jupd_reg2;
  
  assign bus_tlb_data_d[`ctlbData_sys]=1'b1;
  assign bus_tlb_data_d[`ctlbData_na]=1'b0;
  assign bus_tlb_data_d[`ctlbData_ne]=1'b0;
  assign bus_tlb_data_d[`ctlbData_phys]=req_addr[31:0];
  
  assign read_data_strip={read_data[258:195],read_data[193:130],read_data[128:65],read_data[63:0]};
  
  assign stall=1'b0;
  assign instrEn[9:1]=9'b0;
  assign instrEn[0]=iAvail[0];
  
  assign jupd=iAvail[0] && instr0[15:0]==16'hf3a1 & ~had_except;
  
  assign except=jupd_reg2;

  frontend1 front_mod(
  clk,
  rst,
  except,
  exceptIP,
//
  exceptThread,
  exceptTrceAddr,
  exceptTrceAddrLow,
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
  stall
  );
  
  teh_mem mem_mod(
  .clk(clk),
  .rst(rst),
  .read_clkEn(req_en),
  .addr(req_addr),
  .data(bus_data),
  .bus_en(bus_en)
  );
  
  assign instrFed=front_mod.instrFed;
  assign read_data=front_mod.read_data;
  
  always #50
    clk=~clk;

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

  always @(posedge clk)
  begin
    rst<=1'b0;
    
    if (rst) begin
        bus_tlb_data<=37'b0;
        bus_tlb_slot<=8'b0;
        bus_tlb_en<=1'b0;
        had_except<=1'b0;
        jupd_reg<=1'b0;
        jupd_reg2<=1'b0;
    end else begin
        if (req_tlbEn) begin
            bus_tlb_data<=bus_tlb_data_d;
            bus_tlb_slot<=req_slot;
            bus_tlb_en<=1'b1;
        end else begin
            bus_tlb_en<=1'b0;
        end
        if (req_en) bus_slot<=req_slot;
        had_except<=had_except|jupd;
        jupd_reg<=jupd;
        jupd_reg2<=jupd_reg;
    end
  end
endmodule


module teh_mem(
  clk,
  rst,
  read_clkEn,
  addr,
  data,
  bus_en
  );
  localparam BUS_BANK=`dcache1_data_width;
  localparam BUS_WIDTH=BUS_BANK*8;
  localparam RAM_WIDTH=8;
  localparam RAM_COUNT=256;
 
  input clk;
  input rst;
  input read_clkEn;
  input [44-8:0] addr;
  output [BUS_WIDTH-1:0] data;
  output reg bus_en;
  
  reg [255:0] ram [RAM_COUNT-1:0];
  
  reg [44-8:0] addr_reg;
  reg [44-8:0] addr_save;
  reg saved;
  
  wire [255:0] data_ram;
  
  reg [1:0] cnt;
  reg in_flight;

  generate
      genvar k;
      for (k=0;k<8;k=k+1) begin : ecc_gen
          hamingGet32 ham_mod(data_ram[32*k+:32],data[39*k+:38]);
          assign data[39*k+38]=^data[39*k+:38];
      end
  endgenerate
  
  assign data_ram=ram[{addr_reg[10:0],cnt}];
  always @(posedge clk)
  begin
      if (rst) begin
          addr_reg<=37'b0;
          cnt<=2'b0;
          in_flight<=1'b0;
          saved<=1'b0;
          bus_en<=1'b0;
      end else begin
          if (read_clkEn & ~in_flight) begin
              addr_reg<=addr; 
              cnt<=2'b0;
              in_flight<=1'b1;
              bus_en<=1'b1;
          end else begin
              if (cnt!=2'd3) cnt<=cnt+1;
              if (cnt==2'd2) in_flight<=1'b0;
              if (in_flight & read_clkEn) begin
                  addr_save<=addr;
                  saved<=1'b1;
              end
              if (~in_flight & ~read_clkEn & saved) begin
                   saved=1'b0;
                   addr_reg<=addr_save;
                   cnt<=2'b0;
                   in_flight<=1'b1;
                   bus_en<=1'b1;
              end else begin
                  bus_en<=1'b0;
              end
          end 
      end
  end
  
  initial
  begin
      $readmemh("/home/goran/heptane/test/frontend/memsum.memh",ram);
  end
endmodule
