`include "../../rtl/struct.sv"


module dummyL2_Qram(
  clk,
  rst,
  read_clkEn,
  read_addr,
  read_data,
  write_addr,
  write_data,
  write_wen
  );
  localparam ADDR_WIDTH=4+680;
  localparam DATA_WIDTH=5+37+1;
  localparam ADDR_COUNT=16;
  
  input clk;
  input rst;
  input read_clkEn;
  input [ADDR_WIDTH-1:0] read_addr;
  output [DATA_WIDTH-1:0] read_data;
  input [ADDR_WIDTH-1:0] write_addr;
  input [DATA_WIDTH-1:0] write_data;
  input write_wen;

  reg [DATA_WIDTH-1:0] ram [ADDR_COUNT-1:0];
  reg [ADDR_WIDTH-1:0] read_addr_reg;
  integer l;
  
  assign read_data=ram[read_addr_reg];

  always @(posedge clk)
    begin
      if (rst) read_addr_reg<={ADDR_WIDTH{1'b0}};
      else if (read_clkEn) read_addr_reg<=read_addr;
      if (write_wen) ram[write_addr]<=write_data;
      if (rst) for (l=0;l<16;l=l+1) ram[l]<={DATA_WIDTH{1'B0}};
    end

endmodule

module dummyL2_ram(
  clk,
  rst,
  read_clkEn,
  read_addr,
  read_data,
  write_addr,
  write_data,
  write_wen
  );
  localparam ADDR_WIDTH=684;
  localparam DATA_WIDTH=256;
  localparam ADDR_COUNT=65536;
  
  input clk;
  input rst;
  input read_clkEn;
  input [ADDR_WIDTH-2:0] read_addr;
  output [2*DATA_WIDTH-1:0] read_data;
  input [ADDR_WIDTH-1:0] write_addr;
  input [DATA_WIDTH-1:0] write_data;
  input write_wen;

  reg [DATA_WIDTH-1:0] ram [ADDR_COUNT-1:0];
  reg [ADDR_WIDTH-2:0] read_addr_reg;
  
  assign read_data={ram[{read_addr_reg,1'b1}],ram[{read_addr_reg,1'b0}]};

  always @(posedge clk)
    begin
      if (rst) read_addr_reg<={ADDR_WIDTH-1{1'b0}};
      else if (read_clkEn) read_addr_reg<=read_addr;
      if (write_wen) ram[write_addr]<=write_data;
    end

      
  initial
  begin
      $readmemh("/home/goran/heptane/test/frontend/fpu.memh",ram);
  end

endmodule


module dummyL2(
  clk,
  rst,
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
  localparam BUS_WIDTH=512;
  
  input clk;
  input rst;
  output insBus_en;
  output [4:0] insBus_req;
  output insBus_dirty;
  output insBus_exclusive;
  output [BUS_WIDTH-1:0] insBus_data;

  input reqBus_en;
  input [43:7] reqBus_addr;
  input [4:0] reqBus_req;
  input reqBus_want_excl;
  
  reg [3:0] wrAddrQ=0;
  reg [3:0] rdAddrQ=0;
  reg [3:0] countQ=0;
  
  reg [4:0] Qreq;
  reg [36:0] Qaddr;
  reg Qexcl;

  reg [4:0] Qreq_reg[9:1];
  reg [36:0] Qaddr_reg[9:1];
  reg Qexcl_reg[9:1];
  reg [11:1] en_reg;
  reg cnt=0;
  wire rdinc;
  reg [36:0] QaddrD;
  
  wire [511:0] bus_data;
  integer m;
/*
  dummyL2_Qram queue_mod(
  .clk(clk),
  .rst(rst),
  .read_clkEn(1'b1),
  .read_addr(rdAddrQ),
  .read_data({Qexcl,Qreq,Qaddr}),
  .write_addr(wrAddrQ),
  .write_data({reqBus_want_excl,reqBus_req[4:0],reqBus_addr}),
  .write_wen(reqBus_en)
  );
  */
  dummyL2_ram data_mod(
  .clk(clk),
  .rst(rst),
  .read_clkEn(|en_reg[10:7]),
  .read_addr({QaddrD[13:0],cnt}),
  .read_data(bus_data),
  .write_addr(16'b0),
  .write_data(256'b0),
  .write_wen(1'b0)
  );
  
  assign insBus_dirty=1'b0;
  assign insBus_exclusive=Qexcl_reg[8];
  assign insBus_en=en_reg[8];
  assign insBus_data=bus_data;
  assign insBus_req=en_reg[8] ? Qreq_reg[8] : Qreq_reg[9];
  
  assign rdinc=(countQ!=0 && !en_reg[1]);
  
  always @(posedge clk) begin
      if (reqBus_en) wrAddrQ<=wrAddrQ+1;
      if (rdinc) rdAddrQ<=rdAddrQ+1;
      countQ<=reqBus_en&~rst;
      if (rst) begin
          for(m=1;m<=9;m=m+1) begin
              Qreq_reg[m]<=4'b0;
              Qaddr_reg[m]<=37'b0;
          end
          QaddrD<=37'b0;
          en_reg<=0;
	  Qreq<=4'b0;
	  Qaddr<=37'b0;
	  Qexcl<=1'b0;
      end else begin
	Qreq<=reqBus_req[4:0];
	Qaddr<=reqBus_addr;
	Qexcl<=reqBus_want_excl;
        Qreq_reg[1]<=Qreq;
        Qaddr_reg[1]<=Qaddr;
        Qexcl_reg[1]<=Qexcl;
        en_reg<={en_reg[10:1],countQ[0]};
        for(m=2;m<=9;m=m+1) begin
            Qreq_reg[m]<=Qreq_reg[m-1];
            Qaddr_reg[m]<=Qaddr_reg[m-1];
            Qexcl_reg[m]<=Qexcl_reg[m-1];
        end
        if (en_reg[6]) QaddrD<=Qaddr_reg[6];
      end
      if (rst|en_reg[6]) cnt<=1'd0;
      else cnt<=cnt+1;
  end
  
endmodule

