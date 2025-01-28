module test(
  clk);
  input clk;

  logic [6:0][7:0] dummy_A8;
  logic [6:0][7:0] dummy_B8;
  logic [7:0] inA;
  logic [7:0] inB;
  logic [7:0] inC;
  logic [7:0] inD;

  wire [7:0] clkX={8{clk}};
  wire [7:0] pwr=8'h3f;
  logic [7:0] val=8'b11zzzzzz;

  cellA #(.PRECHARHE(12'h100)) 
    mycellA(clk,{dummy_A8,pwr,clkX,inA,inB,val});
  cellA #(.PRECHARHE(12'h100)) 
    mycellB(clk,{dummy_B8,pwr,clkX,inC,inD,val});

  always begin
    @(posedge clk) begin inA=0; inB=0; inC=0; inD=0; end
    @(posedge clk) begin inA=0; inB=0; inC=0; inD=0; end
    @(posedge clk) begin inA=0; inB=0; inC=0; inD=0; $display(val); end
    @(posedge clk) begin inA=0; inB=1; inC=0; inD=0; $display(val); end
    @(posedge clk) begin inA=1; inB=1; inC=0; inD=0; $display(val); end
    @(posedge clk) begin inA=0; inB=0; inC=1; inD=1; $display(val); end
    @(posedge clk) begin inA=0; inB=1; inC=1; inD=0; $display(val); end
    @(posedge clk) begin inA=1; inB=0; inC=1; inD=1; $display(val); end
  end
endmodule
