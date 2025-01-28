
module cellA(
  clkPHASE,
  precharge_signal,
  io);
  parameter WIDTH=1;
  parameter ANHOR_X=0;
  parameter ANHOR_Y=0;
  parameter X_step=12;//min 9x gates if using ~2.5 electron per gate;otherwise can be minimum 6
  parameter Y_step=1;
  parameter X_mod=1000000;
  parameter Y_mod=1000000;
  parameter [11:0] PRECHARHE;
  parameter [11:0] INP;
  input logic clkPHASE;
  inout logic [11:0][WIDTH-1:0][7:0] io;

  integer a,b,c;

  logic [11:0] [WIDTH-1:0] [7:0] iow;

  always @* begin
      if (clkPHASE==0) for(a=0;a<WIDTH;a=a+1) begin
          for(b=0;b<12;b=b+1) begin
            if (INP[b]) io[b][a]=8'bzz;
            else if (PRECHARHE[b]) io[b][a]=precharge_signal;
          end
      end
      if (clkPHASE==1) begin
              iow=io|(io<<(WIDTH*8*1))|(io>>(WIDTH*8*1))|
                (io<<(WIDTH*8*2))|(io>>(WIDTH*8*2))|
                (io<<(WIDTH*8*3))|(io>>(WIDTH*8*3))|
                (io<<(WIDTH*8*4))|(io>>(WIDTH*8*4))|
                (io<<(WIDTH*8*5))|(io>>(WIDTH*8*5))|
                (io<<(WIDTH*8*6))|(io>>(WIDTH*8*6))|
                (io<<(WIDTH*8*7))|(io>>(WIDTH*8*7))|
                (io<<(WIDTH*8*8))|(io>>(WIDTH*8*8))|
                (io<<(WIDTH*8*9))|(io>>(WIDTH*8*9));
      end
  end
endmodule

