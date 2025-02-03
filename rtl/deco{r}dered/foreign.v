
module foreign_imul(
  clk,
  rst,
  dataEn,
  subreg_dataEn,
  A,B,res);
  input clk;
  input rst;
  input dataEn;
  input subreg_dataEn,
  input [64:0] A;
  input [64:0] B;
  output [64:0] res;

  function [20:0] mask_insn;
     input [7:0] byte;
     input [7:0] byte_prev;
     input level;
     input is64;
     begin
         mask_insn[15:0]=0;
         if ((byte==8'h66 || byte==8'h3e || byte==8'h3f) && ~level) 
            mask_insn[11:10]=2'b01;
         if ((byte==8'hf2 || byte==8'h67) && ~level) mask_insn[11:10]=2'b10;
         if ((byte==8'hf3 || byte==8'hf0) && ~level) mask_insn[11:10]=2'b11;
         if (byte[7:4]==4'b0100 && byte_prev[7:4]!=4'b0100 && is64 && ~level) mask_insn[15:12]=byte[3:0];
         if (byte[7:4]==4'b0100 && byte_prev[7:4]==4'b0100 && is64 && ~level) mask_insn[20:16]={1'b1,byte[3:0]}; //third register operand
         if (~level && byte==8'hf) mask_insn[9:8]=2'b01;
         if (level && byte==8'h38) mask_insn[9:8]=2'b10;
         if (level && byte==8'h3a) mask_insn[9:8]=2'b11;
     end
  endfunction
  wire [20:0] res0;
  reg [44:0] res0_reg;
  wire [6:0][20:0] prfx_nolevel;
  wire [6:0][20:0] prfx;
  wire [6:0] lads;
  wire [6:0] lvl;
  wire [2:0] opind;
  wire [7:1] opcode_pos; 
  wire opcode_has_prfx;
  reg [13:0] subreg_need; //only xx and 0f xx supported with subreg!; second half=imm8 for 1 and imm32 for 0
  wire [63:0] AB={B[15:0],A[63:16]};
  generate
    genvar pos;
    for(pos=0;pos<7;pos=pos+1) begin : pfx_dtct
        assign prfx_nolevel[pos]=mask_insn(A[8*pos+:pos],
          pos ? A[8*pos-8+:8] : 8'b0,1'b0,1'b1);
        assign lvl[pos]=prfx_nolevel[pos][9:8]==2'b01;
        if (pos) assign prfx[pos]=mask_insn(A[8*pos+:pos],
          pos ? A[8*pos-8+:8] : 8'b0,|lvl[pos-1:0],1'b1);
        else assign prfx[pos]=prfx_nolevel[pos];
        assign lads[pos]=|prfx[pos];
        assign opcode=opcode_pos[pos] ? A[8*pos+:8] : 8'bz;
        assign sib=opcode_pos[pos] ? AB[8*pos+:8] : 8'bz;
        assign modrm=opcode_pos[pos] ? A[8*pos+8+:8] : 8'bz;
        assign pfx[pos]=prfx[pos] & {21{~opcode_pos0[pos+1]}};
        assign opind=opcode_pos[pos] ? pos[2:0] : 8'bz;
    end
  endgenerate
  bit_find_first_bit #(7) find_mod(~lads,opcode_pos,opcode_has_prfx);
  bit_find_first_bit_tail #(7) find_mod(~lads,opcode_pos0,opcode_has_prfx0);

  assign opcode=opcode_has_prfx ? 8'bz : A[63:56];
  assign sib=opcode_has_prfx ? 8'bz : AB[63:56];
  assign modrm=opcode_has_prfx ? 8'bz : B[7:0];
  assign res0[7:0]=opcode;
  assign res0[20:8]=pfx[0][20:8] | pfx[1][20:8] | pfx[2][20:8] |
    pfx[3][20:8] | pfx[4][20:8] | pfx[5][20:8] |pfx[6][20:8];
  assign opind=opcode_has_prfx ? 3'bz : 3'h7;

  always @(posedge clk) begin
    if (rst) begin
        subreg_need<=0;
    end else if (subreg_dataEn) begin
        subreg_need[b[7:0]*64+:64]=A[63:0];
    end
    if (rst) begin
        res0_reg<=0;
    end else begin
        res0_reg<={3'b0,sib,2'b0,modrm,1'b0,res0[20:12],1'b0,res0[11:0]};
        if (subreg_need[2'b0,res0[11:0]]) begin //has reg subcode
            res0_reg[12]=1'b1;
            res0_reg[22]=res0[11:0]==2'b01; //not fed into table! slow path! or bigger table to include 0x66 + reg subcode.
            res0_reg[11:9]=modrm[5:3];
            res0_reg[25:23]=3'b0; //xmm0/ymm0 or rax/eax/ax/al
        end
        if (modrm[2:0]==2'b100) begin
            res0_reg[25:23]=sib[2:0];
            res0_reg[30]=1'b1;
            if (modrm[7:6]==2'b00 && sib[2:0]==3'b101) begin
                res0_reg[40]=1'b1;//32 bit disp instead of 8; no index
            end
            if (sib[5:3]==3'b100) begin 
                res0_reg[41]=1'b1; //no base
            end
        end else if (modrm[2:0]=2'b101) begin
            res0_reg[31]=1'b1;//RIP relative/32 disp in 32 bit mode
        end
        if (subreg_need[{2'b1,res0[11:0]}]) begin
            res0_reg[42]=1'b1;//imm size 8/32
        end 
        if (subreg_need[{2'b10,res0[11:0]}]) begin
            res0_reg[43]=1'b1; //imm present
        end 
        if (subreg_need[{2'b1,res0[11:0]}]) begin
            res0_reg[44]=1'b1; //modrm present
        end 
    end
  end
  assign res={11'b0,4'b1+{3'b0,res0_reg[30]}+{3'b0,res0_reg[44]}+{res0_reg[43]&~res0_reg[42]&res0_reg[44],1'b0,res0_reg[43]&res0_reg[42]&res0_reg[44]},
    res0_reg[29:28]==2'b0 && res0_reg[31] ? 3'b100 : 
    res0_reg[29],1'b0,res0_reg[28],~opind,res0_reg};
endmodule

module fastpath_ram(
    clk,
    rst,
    read_addr,read_data,
    write_addr,write_data,write_wen);

    input clk;
    input rst;
    input [4:0][11:0] read_addr;
    output [7:0] read_data;
    input [11:0] write_addr;
    input [7:0] write_data;
    input write_wen;

    reg [7:0] optab[4095:0];

    integer p;
    always @(posedge clk) begin
        for(p=0;p<5;p=p+1) begin
            read_data[p]=optab[read_addr[p]];
        end
        if (write_wen) optab[write_addr]<=write_data;
    end
endmodule

module transl_dah_bundelaya(
    clk,
    rst,
    data_in,
    data_in_en,
    data_in_en_to_follow,
    data_out,
    data_out_en,
    data_out_error);

    input clk;
    input rst;
    input [511:0] data_in;
    input data_in_en;
    output data_in_en_to_follow;
    output [511:0] data_out;
    output data_out_en;
    output data_out_error;

    wire [63:0] pfres[15:0];
    generate
      genvar pfoff;
      for(pfoff=0;pfoff<32;pfoff++) begin : sizedeker
          foreign_imul(
          clk,
          rst,
          dataEn,
          subreg_dataEn,
          data_in_reg[pfoff*8+:64],data_in_reg[pfoff*8+64+:64],pfres[pfoff]);
          assign pfoffset[pfoff][0]=pfoff;
          assign pfoffset[pfoff][1]=pfres_reg[off_in][`pfoff_size]+pfoff;
          assign pfoffset[pfoff][2]=pfres_reg[pfoffset[1][4:0]][`pfoff_size]+pfoffset[1][4:0];
          assign pfoffset[pfoff][3]=pfres_reg[pfoffset[2][4:0]][`pfoff_size]+pfoffset[2][4:0];
          bit_find_fist_bit #(3) first_mod({pfoffset[pfoff][3][5],pfoffset[pfoff][2][5],pfoffset[pfoff][1][5],pfoffset[pfoff][0][5]},pffirst[pfoff],pfhas[pfoff]);
          assign pfshift[pfoff]=pffirst[pfoff][0] ? {data_in,data_in_reg}>>(8*(pfoff+0)) : 'z;
          assign pfshift[pfoff]=pffirst[pfoff][1] ? {data_in,data_in_reg}>>(8*(pfoff+1)) : 'z;
          assign pfshift[pfoff]=pffirst[pfoff][2] ? {data_in,data_in_reg}>>(8*(pfoff+2)) : 'z;
          assign pfshift[pfoff]=pffirst[pfoff][3] ? {data_in,data_in_reg}>>(8*(pfoff+3)) : 'z;
          assign pfshitf2=pff_first[0] ? pfshift_reg[pfoffset[1]] : 'z;
          assign pfshitf2=pff_first[1] ? pfshift_reg[pfoffset[2]] : 'z;
          assign pfshitf2=pff_first[2] ? pfshift_reg[pfoffset[3]] : 'z;
          assign pfshitf2=pff_first[3] ? pfshift_reg[pfoffset[4]] : 'z;
      end
    endgenerate
    assign pfoffset2[0]=0;
    assign pfoffset2[1]=pfres_reg2[0][`pfoff_size2]+0;
    assign pfoffset2[2]=pfres_reg2[pfoffset2[1]][`pfoff_size2]+pfoffset2[1];
    assign pfoffset2[3]=pfres_reg2[pfoffset2[2]][`pfoff_size2]+pfoffset2[2];
    assign pfoffset2[4]=pfres_reg2[pfoffset2[3]][`pfoff_size2]+pfoffset2[3];
    bit_find_first_bit #(4) first_mod({pfhas[pfoffset[3]],pfhas[pfoffset[2]],pfhas[pfoffset[1]],pfhas[0]},pff_first,pff_has);
    always @(posedge clk) begin
        off_in<=pfoffset[4];
        off_in_reg<=off_in;
        pfres_reg<=pfres;
        pfres_reg2<=pfres_reg;
        for(k=0;k<32;k=k+1) pfres_reg2[k][63:59]<=pfoffset[k][3][`pfoff_size];
        if (off_in<off_in_reg) begin
            data_in_reg={data_in[511:0],data_in_reg[511:256]};
            if (!data_in_en) upper_invalid<=1;
            if (upper_invalid) bndl_invalid<=1;
        end
    end

    assign data_in_en_to_follow=upper_invalid;

    fastpath_ram optab_mod(
    clk,
    rst,
    optab_addr,optab_data,
    write_optab_addr,write_optab_data,write_optab_wen);

endmodule
