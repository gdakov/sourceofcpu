#define PARAM_H 0
#define PARAM_I 2

#define EX_INVD 1
#define EX_UNDER 0x2
#define EX_UNDER_STD 0x4
#define EX_OVER 0x8
#define EX_OVER_STD 0x10
#define EX_INEX 0x20
#define EX_INEX_STD 0x40
#define EX_DENOR 0x80
#define EX_DENOR_STD 0x100
#define EX_LOGC_CONS 0x200
#define EX_LOGC_PROD 0x400


unsigned short OPS_ADD[]={
  fop_addDH,
  fop_addDL,
  fop_addDP,
  fop_subDH,
  fop_subDL,
  fop_subDP,
//  fop_addS,
//  fop_addSP,
//  fop_subS,
//  fop_subSP,
  fop_permDS,
  fop_cmpDH,
  fop_cmpDL,
//  fop_cmpS,
  fop_pcmplt,
  fop_pcmpge,
  fop_pcmpeq,
  fop_pcmpne,
//  fop_pcmplt|1024,//single
//  fop_pcmpge|1024,
//  fop_pcmpeq|1024,
//  fop_pcmpne|1024,
  fop_logic,
  fop_logic+1,
  fop_logic+2,
  fop_logic+3
  };

unsigned short OPS_MUL[]={
  fop_mulDH,
  fop_mulDL,
  fop_mulDP,
  fop_divDH,
  fop_divDL,
  fop_sqrtDH,
  fop_sqrtDL,
//  fop_mulS,
//  fop_mulSP,
//  fop_divS,
//  fop_sqrtS,
  fop_permDS,
  fop_rndED,
  fop_rndDS,
  fop_rndDSP,
  fop_cvtD,
  fop_cvtS,
  fop_cvt32D,
  fop_cvt32S

  };


unsigned short OPS_MUL_no2[]={
  fop_mulDH,
  fop_mulDL,
  fop_mulDP,
//  fop_mulS,
//  fop_mulSP,
  fop_permDS,
  fop_rndED,
  fop_rndDS,
  fop_rndDSP
  };


struct req {
  unsigned long A[2];
  unsigned long B[2];
  unsigned short Ah;
  unsigned short Bh;
  char Ax[2];
  char Bx[2];
  int op;
  int en;
  unsigned long res[2];
  unsigned short resh;
  char resx[2];
  unsigned short exceptions;
  void opADDd (int iA,int iB, int iRes, int rmode);
  void opSUBd (int iA,int iB, int iRes, int rmode);
  void oprSUBd(int iA,int iB, int iRes, int rmode);
  void opMULd (int iA,int iB, int iRes, int rmode);
  void opADDs(int cnt, int rmode);
  void opSUBs(int cnt, int rmode);
  void opMULs(int cnt, int rmode);
  void opADDx(int rmode);
  void opSUBx(int rmode);
  void opMULx(int rmode);
  void opPERMd (int iAB,int iB, int iRes, int swp, int cpy);
};
/*
 * double: extra exponent bit Ax[iA]>>1 (comes before last)
 * single: lower half extra exponent Ax[iA]&1,upper half Ax[iA]>>1
 * extended: extra exponent same as double, Ah=sign and exponent
 * "native" denormals are treated as zero
 * */

int rndfunc(bool last,bool rbit,bool tail,bool sgn, int rmod) {
  switch (rmod) {
      case 0:
      return 0;
      case 1:
      return rbit;
      case 2:
      return rbit && (tail || last);
      case 3:
      return sgn ? 0 : rbit||tail;
      case 4:
      return (!sgn) ? 0 : rbit||tail;
      case 5:
      return sgn ? 0 : rbit;
      case 6:
      return (!sgn) ? 0 : rbit;
      default:
      printf("rndfunc error\n");
      exit(10);
  }
}

req reqs[32][10]={};

void creat_reqs(int row,unsigned fpcsr) {
  int n;
  int op;
  for(n=0;n<3;n++) {
      op=OPS_ADD[lrand48()%(sizeof OPS_ADD/sizeof OPS_ADD[0])];
      if (reqs[row][4+n].en) goto do_mul;
      reqs[row][4+n].en=1;
      reqs[row][4+n].res[0]=reqs[row][4+n].A[0];
      reqs[row][4+n].res[1]=reqs[row][4+n].A[1];
      reqs[row][4+n].resx[0]=reqs[row][4+n].Ax[0];
      reqs[row][4+n].resx[1]=reqs[row][4+n].Ax[1];
      reqs[row][4+n].resh=reqs[row][4+n].Ah;
      switch (op) {
	  case fop_addDL:
	  op|=0x100&lrand48();
	  reqs[row][4+n].opADDd(0,(op&0x100)!=0,0,(fpcsr>>22)&7);
	  break;
	  case fop_subDL:
	  op|=0x100&lrand48();
	  reqs[row][4+n].opSUBd(0,(op&0x100)!=0,0,(fpcsr>>22)&7);
	  break;
	  case fop_addDH:
	  op|=0x200&lrand48();
	  reqs[row][4+n].opADDd(1,(op&0x200)==0,1,(fpcsr>>22)&7);
	  break;
	  case fop_subDH:
	  op|=0x200&lrand48();
	  reqs[row][4+n].opSUBd(1,(op&0x200)==0,1,(fpcsr>>22)&7);
	  break;
	  case fop_permDS:
	  op|=0x1700&lrand48();
	  reqs[row][4+n].opPERMd(0,(op&0x100)!=0,0,(op&0x400)!=0,(op&0x1000)!=0);
	  reqs[row][4+n].opPERMd(1,(op&0x200)==0,1,(op&0x400)!=0,(op&0x1000)!=0);
	  break;
	  case fop_addDP:
	  op|=0x1300&lrand48();
	  if (op&0x1000) opSWP();
	  reqs[row][4+n].opADDd(0,(op&0x100)!=0,0,(fpcsr>>22)&7);
	  reqs[row][4+n].opADDd(1,(op&0x200)==0,1,(fpcsr>>22)&7);
	  if (op&0x1000) opUnSWP();
	  break;
	  case fop_subDP:
	  op|=0x1300&lrand48();
	  if (op&0x1000) opSWP();
	  reqs[row][4+n].opSUBd(0,(op&0x100)!=0,0,(fpcsr>>22)&7);
	  reqs[row][4+n].opSUBd(1,(op&0x200)==0,1,(fpcsr>>22)&7);
	  if (op&0x1000) opUnSWP();
	  break;
	  case fop_addsubDP:
	  op|=0x1300&lrand48();
	  if (op&0x1000) opSWP();
	  reqs[row][4+n].opSUBd(0,(op&0x100)!=0,0,(fpcsr>>22)&7);
	  reqs[row][4+n].opADDd(1,(op&0x200)==0,1,(fpcsr>>22)&7);
	  if (op&0x1000) opUnSWP();
	  break;
	  case fop_and:
	  reqs[row][4+n].res[0]=reqs[row][4+n].A[0]  &reqs[row][4+n].B[0];
	  reqs[row][4+n].res[1]=reqs[row][4+n].A[1]  &reqs[row][4+n].B[1];
	  reqs[row][4+n].resx[0]=reqs[row][4+n].Ax[0]&reqs[row][4+n].Bx[0];
	  reqs[row][4+n].resx[1]=reqs[row][4+n].Ax[1]&reqs[row][4+n].Bx[1];
	  reqs[row][4+n].resh=reqs[row][4+n].Ah      &reqs[row][4+n].Bh;
	  break;
	  case fop_or:
	  reqs[row][4+n].res[0]=reqs[row][4+n].A[0]  |reqs[row][4+n].B[0];
	  reqs[row][4+n].res[1]=reqs[row][4+n].A[1]  |reqs[row][4+n].B[1];
	  reqs[row][4+n].resx[0]=reqs[row][4+n].Ax[0]|reqs[row][4+n].Bx[0];
	  reqs[row][4+n].resx[1]=reqs[row][4+n].Ax[1]|reqs[row][4+n].Bx[1];
	  reqs[row][4+n].resh=reqs[row][4+n].Ah      |reqs[row][4+n].Bh;
	  break;
	  case fop_xor:
	  reqs[row][4+n].res[0]=reqs[row][4+n].A[0]  ^reqs[row][4+n].B[0];
	  reqs[row][4+n].res[1]=reqs[row][4+n].A[1]  ^reqs[row][4+n].B[1];
	  reqs[row][4+n].resx[0]=reqs[row][4+n].Ax[0]^reqs[row][4+n].Bx[0];
	  reqs[row][4+n].resx[1]=reqs[row][4+n].Ax[1]^reqs[row][4+n].Bx[1];
	  reqs[row][4+n].resh=reqs[row][4+n].Ah      ^reqs[row][4+n].Bh;
	  break;
	  case fop_andn:
	  reqs[row][4+n].res[0]=reqs[row][4+n].A[0]  &~reqs[row][4+n].B[0];
	  reqs[row][4+n].res[1]=reqs[row][4+n].A[1]  &~reqs[row][4+n].B[1];
	  reqs[row][4+n].resx[0]=reqs[row][4+n].Ax[0]&~reqs[row][4+n].Bx[0];
	  reqs[row][4+n].resx[1]=reqs[row][4+n].Ax[1]&~reqs[row][4+n].Bx[1];
	  reqs[row][4+n].resh=reqs[row][4+n].Ah      &~reqs[row][4+n].Bh;
	  break;
      }
      reqs[row][4+n].op=op;
do_mul:
      if (n!=2) op=OPS_MUL_no2[lrand48()%(sizeof OPS_MUL_no2/sizeof OPS_MUL_no2[0])];
      else op=OPS_MUL[lrand48()%(sizeof OPS_MUL/sizeof OPS_MUL[0])];
      if (reqs[row][7+n].en) goto after_mul;
      switch (op) {
	  case fop_mulDL:
	  op|=0x100&lrand48();
	  reqs[row][4+n].opMULd(0,(op&0x100)!=0,0,(fpcsr>>22)&7);
	  break;
	  case fop_mulDH:
	  op|=0x200&lrand48();
	  reqs[row][4+n].opMULd(1,(op&0x200)==0,1,(fpcsr>>22)&7);
	  break;
	  case fop_permDS:
	  op|=0x1700&lrand48();
	  reqs[row][4+n].opPERMd(0,(op&0x100)!=0,0,(op&0x400)!=0,(op&0x1000)!=0);
	  reqs[row][4+n].opPERMd(1,(op&0x200)==0,1,(op&0x400)!=0,(op&0x1000)!=0);
	  break;
	  case fop_mulDP:
	  op|=0x1300&lrand48();
	  if (op&0x1000) opSWP();
	  reqs[row][4+n].opMULd(0,(op&0x100)!=0,0,(fpcsr>>22)&7);
	  reqs[row][4+n].opMULd(1,(op&0x200)==0,1,(fpcsr>>22)&7);
	  if (op&0x1000) opUnSWP();
	  break;
      }
after_mul:
  }
}

bool fpcu_poke(Vblock_compute * top,int row) {
}

bool fpcu_peek(Vblock_compute * top,int row) {
}


