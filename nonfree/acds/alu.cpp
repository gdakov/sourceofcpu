#include "acds.cpp"


void gen_alu_adder() {
  int k;
  acds_cell<64,0x8,8,0x1b> buf_drv_0_5[2];
  acds_cell<64,0x8,8,0x77> and_drv_0_8_stage1[6];
  acds_cell<64,0x8,8,0x1b> buf_drv_0_5_inv[2];
  acds_cell<64,0x8,8,0x77> and_drv_0_8_stage1_inv[6];
  for(k=0;k<2;k=k1+)
      buf_drv_0_5_stage1[k]=new acds_cell(15*(k%4),k/4,0);//two driven by select wire
  for(k=2;k<8;k=k+1)
      and_drv_0_8_stage1[k]=new acds_cell(15*k(%4),k/4+1,0); //at most one and driven by select wire
  for(k=0;k<2;k=k1+)
      acds_cell<64,0x104,4,0x6cb> buf_drv_0_5_stage1_inv[k]=new acds_cell(15*(k%4),k/4+2,0);//two driven by select wire
  for(k=2;k<8;k=k+1)
      acds_cell<64,0x8,8,0x77> and_drv_0_8_stage1_inv[k]=new acds_cell(15*k(%4),k/4+2,0); //at most one and driven by select wire
  curmodule.port["valA"].add_input(buf_drv_0_5_stage1[0],2,0,64);
  curmodule.port["valA"].add_input(buf_drv_0_5_stage1[0],8,1,64);
  curmodule.port["valA$inv"].add_input(buf_drv_0_5_stage1[0],0x80,0,64);
  curmodule.port["valB"].add_input(buf_drv_0_5_stage1[1],2,0,64);
  curmodule.port["valB"].add_input(buf_drv_0_5_stage1[1],8,2,64);
  curmodule.port["valB"].add_input(buf_drv_0_5_stage1[1],0x80,3,64);

  curmodule.port["valA$inv"].add_input(buf_drv_0_5_stage1_inv[0],2,0,64);
  curmodule.port["valA$inv"].add_input(buf_drv_0_5_stage1_inv[0],8,1,64);
  curmodule.port["valA"].add_input(buf_drv_0_5_stage1_inv[0],0x80,0,64);
  curmodule.port["valB$inv"].add_input(buf_drv_0_5_stage1_inv[1],2,0,64);
  curmodule.port["valB$inv"].add_input(buf_drv_0_5_stage1_inv[1],8,2,64);
  curmodule.port["valB$inv"].add_input(buf_drv_0_5_stage1_inv[1],0x80,3,64);

  curmodule.port["valA"].add_input(and_drv_0_8_stage1[0],2,0,64);
  curmodule.port["valA"].add_input(and_drv_0_8_stage1[2],2,1,64);
  curmodule.port["valA$inv"].add_input(and_drv_0_8_stage1[4],2,0,64);
  curmodule.port["valA"].add_input(and_drv_0_8_stage1[0],0x20,0,64);
  curmodule.port["valA"].add_input(and_drv_0_8_stage1[2],0x20,1,64);
  curmodule.port["valA$inv"].add_input(and_drv_0_8_stage1[4],0x20,0,64);
  curmodule.port["valA"].add_input(and_drv_0_8_stage1[1],2,0,64);
  curmodule.port["valA"].add_input(and_drv_0_8_stage1[3],2,1,64);
  curmodule.port["valA$inv"].add_input(and_drv_0_8_stage1[5],2,0,64);
  curmodule.port["valB"].add_input(and_drv_0_5_stage1[0],4,0,64);
  curmodule.port["valB"].add_input(and_drv_0_5_stage1[0],0x10,2,64);
  curmodule.port["valB"].add_input(and_drv_0_5_stage1[1],4,3,64);
  curmodule.port["valB"].add_input(and_drv_0_5_stage1[2],4,0,64);
  curmodule.port["valB"].add_input(and_drv_0_5_stage1[2],0x10,2,64);
  curmodule.port["valB"].add_input(and_drv_0_5_stage1[3],4,3,64);
  curmodule.port["valB"].add_input(and_drv_0_5_stage1[4],4,0,64);
  curmodule.port["valB"].add_input(and_drv_0_5_stage1[4],0x10,2,64);
  curmodule.port["valB"].add_input(and_drv_0_5_stage1[5],4,3,64);
}
