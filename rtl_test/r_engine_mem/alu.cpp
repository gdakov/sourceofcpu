#include <cstdlib>
#include <cfenv>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "../inc/ptr.h"
#include "contx.h"
#include "../inc/struct.h"
#include "../inc/cjump.h"
#include "../inc/extract.h"

#define get64(a) ((((unsigned long long) a[1])<<32)|(unsigned long long) a[0])
#define set64i(a,b,c) a[0]=b;a[1]=b>>32;a[2]=c;

unsigned short OPS_REGL[]={0,1,4,5,8,9,12,13,16,17,32|4096,33|4096,34|4096,
35|4096,36|4096,37|4096,39|4096,40|4096,41|4096,42|4096,43|4096,48|4096,49|4096,
50|4096,51|4096,52,53,54|4096,55|4096,56|4096,57,4|16384,5|16384,4|32768,5|32768,8|16384,9|16384};
unsigned short OPS_S_REGL[]={0,1,4,5,8,9,12,13,16,17,20,21,24,25,28,29,32|4096,
33|4096,34|4096,35|4096,36|4096,37|4096,39|4096,40|4096,41|4096,42|4096,43|4096,48|4096,49|4096,50|4096,51|4096,52,53,54|4096,55|4096,56|4096,57,
4|16384,5|16384,4|32768,5|32768,8|16384,9|16384};
unsigned short OPS_M_REGL[]={1,2,3,5,7,9,10,11,12|4096,13|4096,14|4096,
12|4096|1024,13|4096|1024,14|4096|1024};

void fp_get_ext(long double a, unsigned num[3]);
void fp_get_double(double a, unsigned num[3]);
void fp_get_single(float a, unsigned num[3]);
bool ckran_alu(unsigned long long ptr,unsigned long long addr);

struct lsent {
    unsigned short op;
    unsigned short sh;
    unsigned short sz;
};

lsent load_op[]={
    0xa0,0,1, //inv tlb
    
    0x20,0,1,
    0x22,0,2,
    0x24,0,4,
    0x26,0,8,
/*    0x00,0,16,
    0x02,0,16,
    0x04,0,16,
    0x06,0,10,
    0x08,0,4,
    0x0a,0,4,
    0x0c,0,4,
    0x0e,0,8,
    0x10,0,8,
    0x12,0,8,
    0x14,0,8,
    0x16,0,8,
    0x18,0,16,
    0x1a,0,16,
    0x1c,0,16,
    0x1e,0,17,*/
    
    0x60,0,1,
    0x62,0,2,
    0x64,0,4,
    0x66,0,8,
 /*   0x40,0,16,
    0x42,0,16,
    0x44,0,16,
    0x46,0,10,
    0x48,0,4,
    0x4a,0,4,
    0x4c,0,4,
    0x4e,0,8,
    0x50,0,8,
    0x52,0,8,
    0x54,0,8,
    0x56,0,8,
    0x58,0,16,
    0x5a,0,16,
    0x5c,0,16,
    0x5e,0,17,*/
    
    0x160,1,1,
    0x162,1,2,
    0x164,1,4,
    0x166,1,8,
 /*   0x140,1,16,
    0x142,1,16,
    0x144,1,16,
    0x146,1,10,
    0x148,1,4,
    0x14a,1,4,
    0x14c,1,4,
    0x14e,1,8,
    0x150,1,8,
    0x152,1,8,
    0x154,1,8,
    0x156,1,8,
    0x158,1,16,
    0x15a,1,16,
    0x15c,1,16,
    0x15e,1,17,*/
    
    0x260,2,1,
    0x262,2,2,
    0x264,2,4,
    0x266,2,8,
   /* 0x240,2,16,
    0x242,2,16,
    0x244,2,16,
    0x246,2,10,
    0x248,2,4,
    0x24a,2,4,
    0x24c,2,4,
    0x24e,2,8,
    0x250,2,8,
    0x252,2,8,
    0x254,2,8,
    0x256,2,8,
    0x258,2,16,
    0x25a,2,16,
    0x25c,2,16,
    0x25e,2,17,*/
    
    0x360,3,1,
    0x362,3,2,
    0x364,3,4,
    0x366,3,8//,
   /* 0x340,3,16,
    0x342,3,16,
    0x344,3,16,
    0x346,3,10,
    0x348,3,4,
    0x34a,3,4,
    0x34c,3,4,
    0x34e,3,8,
    0x350,3,8,
    0x352,3,8,
    0x354,3,8,
    0x356,3,8,
    0x358,3,16,
    0x35a,3,16,
    0x35c,3,16,
    0x35e,3,17*/
};

lsent store_op[]={
    0x21,0,1,
    0x23,0,2,
    0x25,0,4,
    0x27,0,8,
 /*   0x01,0,16,
    0x03,0,16,
    0x05,0,16,
    0x07,0,10,
    0x09,0,8,
    0x0b,0,8,
    0x0d,0,4,
    0x0f,0,4,
    0x11,0,4,
    0x13,0,8,
    0x15,0,16,
    0x17,0,16,
    0x19,0,16,
    0x1b,0,8,
    0x1f,0,17,*/
    
    0x61,0,1,
    0x63,0,2,
    0x65,0,4,
    0x67,0,8,
   /* 0x41,0,16,
    0x43,0,16,
    0x45,0,16,
    0x47,0,10,
    0x49,0,8,
    0x4b,0,8,
    0x4d,0,4,
    0x4f,0,4,
    0x51,0,4,
    0x53,0,8,
    0x55,0,16,
    0x57,0,16,
    0x59,0,16,
    0x5b,0,8,
    0x5f,0,17,*/
    
    0x161,1,1,
    0x163,1,2,
    0x165,1,4,
    0x167,1,8,
   /* 0x141,1,16,
    0x143,1,16,
    0x145,1,16,
    0x147,1,10,
    0x149,1,8,
    0x14b,1,8,
    0x14d,1,4,
    0x14f,1,4,
    0x151,1,4,
    0x153,1,8,
    0x155,1,16,
    0x157,1,16,
    0x159,1,16,
    0x15b,1,8,
    0x15f,1,17,*/
    
    0x261,2,1,
    0x263,2,2,
    0x265,2,4,
    0x267,2,8,
    /*0x241,2,16,
    0x243,2,16,
    0x245,2,16,
    0x247,2,10,
    0x249,2,8,
    0x24b,2,8,
    0x24d,2,4,
    0x24f,2,4,
    0x251,2,4,
    0x253,2,8,
    0x255,2,16,
    0x257,2,16,
    0x259,2,16,
    0x25b,2,8,
    0x25f,2,17,*/
    
    0x361,3,1,
    0x363,3,2,
    0x365,3,4,
    0x367,3,8//,
   /* 0x341,3,16,
    0x343,3,16,
    0x345,3,16,
    0x347,3,10,
    0x349,3,8,
    0x34b,3,8,
    0x34d,3,4,
    0x34f,3,4,
    0x351,3,4,
    0x353,3,8,
    0x355,3,16,
    0x357,3,16,
    0x359,3,16,
    0x35b,3,8,
    0x35f,3,17*/
};
char reg8[][8]={
"al",
"bl",
"cl",
"dl",
"spl",
"bpl",
"sil",
"dil",
"r8b",
"r9b",
"r10b",
"r11b",
"r12b",
"r13b",
"r14b",
"r15b",
"r16b",
"r17b",
"r18b",
"r19b",
"r20b",
"r21b",
"r22b",
"r23b",
"r24b",
"r25b",
"r26b",
"r27b",
"r28b",
"r29b",
"r30b",
"r31b",
"ah",
"bh",
"ch",
"dh",
"sph",
"bph",
"sih",
"dih",
"r8h",
"r9h",
"r10h",
"r11h",
"r12h",
"r13h",
"r14h",
"r15h",
"r16h",
"r17h",
"r18h",
"r19h",
"r20h",
"r21h",
"r22h",
"r23h",
"r24h",
"r25h",
"r26h",
"r27h",
"r28h",
"r29h",
"r30h",
"r31h"
};


char reg16[][8]={
"ax",
"bx",
"cx",
"dx",
"sp",
"bp",
"si",
"di",
"r8w",
"r9w",
"r10w",
"r11w",
"r12w",
"r13w",
"r14w",
"r15w",
"r16w",
"r17w",
"r18w",
"r19w",
"r20w",
"r21w",
"r22w",
"r23w",
"r24w",
"r25w",
"r26w",
"r27w",
"r28w",
"r29w",
"r30w",
"r31w"
};


char reg32[][8]={
"eax",
"ebx",
"ecx",
"edx",
"esp",
"ebp",
"esi",
"edi",
"r8d",
"r9d",
"r10d",
"r11d",
"r12d",
"r13d",
"r14d",
"r15d",
"r16d",
"r17d",
"r18d",
"r19d",
"r20d",
"r21d",
"r22d",
"r23d",
"r24d",
"r25d",
"r26d",
"r27d",
"r28d",
"r29d",
"r30d",
"r31d"
};

char reg65[][8]={
"rax",
"rbx",
"rcx",
"rdx",
"rsp",
"rbp",
"rsi",
"rdi",
"r8",
"r9",
"r10",
"r11",
"r12",
"r13",
"r14",
"r15",
"r16",
"r17",
"r18",
"r19",
"r20",
"r21",
"r22",
"r23",
"r24",
"r25",
"r26",
"r27",
"r28",
"r29",
"r30",
"r31"
};

#define MEMRGN_DATA 512*1024*1024
#define MEMRGN_DATA_SZ 65536

class req {
    public:
    unsigned int op;
    unsigned long long A,B,res;
    unsigned long long addr;
    unsigned A_p,B_p,res_p,excpt;
    unsigned flags,flags_in;
    unsigned fset;
    unsigned alt,mul;
    unsigned en;
    unsigned num[3];
    int rA,rB,rT;
    unsigned base,index,scale;
    unsigned offset;
    unsigned has_mem;
    unsigned has_alu;
    char asmtext[64];
    bool gen(bool alt_, bool mul_, bool can_shift, req *prev1,hcont *contx,int has_mem_,char *mem,char *pmem);
    bool exec(req *prev1,hcont *contx,char *mem,char *pmem, int itcnt);
    void gen_init(int rT,int dom,unsigned long long int val,int val_p);
    void gen_mem(req* prev1,unsigned code,char * mem,char *memp,unsigned long long addr);
    void gen_memw(req* prev1,unsigned code,char * mem,char *memp,unsigned long long addr,unsigned long long res, char res_p);
    void flgPTR(__int128 r);
    void flg64(__int128 r);
    void flg32(__int128 r);
    void flgM64(unsigned long long r, bool big=0);
    void flgM128(unsigned __int128 r, bool big=0);
    bool testj(int code);
};
    
void req::gen_init(int rT_,int dom,unsigned long long int val,int val_p) {
    has_alu=true;
    res=val;
    res_p=val_p;
    B=val;
    B_p=val_p;
    A=0;
    A_p=0;
    op=32;
    rB=-1;
    rA=-1;
    this->rT=rT_;
    op=32;
    if (!val_p) snprintf(asmtext,sizeof asmtext,"movabs $%li,%%%s\n",B,reg65[rT]);
    else snprintf(asmtext,sizeof asmtext,"movabsp $%li,%%%s\n",B,reg65[rT]);//WARNING: movabsp non impl and not in cpu spec
}

int req::gen_loop(bool close, hcont *contx, int loopno) {
  //close is true if it is a loop close insn, otherwise it is a loop begin insn
  int cnt=lrand48()&0xff;
  int addr0=(lrand48()%(MEMRGN_SIZE/2));
  int addr1=(lrand48()%(MEMRGN_SIZE/2));
  if (!close) {
      snprintf((*(this)).asmtext,sizeof (asmtext), "LoOp%i:\nmovq $%i, %%r15\n",loopno,cnt);
      this->res=cnt;
      (this)->rT=15;
      this->flags=flags_in;
      contx->gen[15]=cnt;
      snprintf((*(this+1)).asmtext,sizeof (asmtext), "movq $%i, %%r14\n",addr0);
      (this+1)->res=addr0;
      (this+1)->rT=14;
      (this+1)->flags=flags_in;
      contx->gen[14]=addr0;
      snprintf((*(this+2)).asmtext,sizeof (asmtext), "movq $%i, %%r13\n",addr1);
      (this+2)->res=addr1;
      (this+2)->rT=13;
      (this+2)->flags=flags_in;
      contx->gen[13]=addr1;
      return 3;
  } else {
      snprintf((*(this)).asmtext,sizeof (asmtext), "sub $1, %%r15\n");
      this->res=contx->gen[15]-1;
      this->rT=15;
      this->flg64(this->res);
      contx->gen[15]=gen[15]-1;
      snprintf((*(this+1)).asmtext,sizeof (asmtext), "jne LoOp%i\n",loopno);
      (this+1)->rT=-1;
      (this+1)->flg64(this->res);
      return 2;
  }
}

char *prna(long long int &addr, bool inloop) {
  static char buf[32] __attribute__(thread);
  buf[0]=0;
  int reg=addr&1;
  if (inloop) addr>>=1;
  if (inloop) {
    snprintf(buf,32," $%i(%%r%i,%%r15,8)", addr, 13+reg);
  } else {
    snprintf(buf,32," mem+%i(%%rip)", addr);
  }
  return buf;
}

bool req::gen(bool alt_, bool mul_, bool can_shift,bool inloop, int loopiter, req *prev1,hcont *contx,int has_mem_,char *mem,char *memp) {
    alt=alt_;
    mul=mul_;
    excpt=-1;
    bool rtn=has_mem_;
    if (!alt && !mul && !can_shift) op=OPS_REGL[rand()%(sizeof OPS_REGL/2)];
    if (!alt && !mul && can_shift)  op=OPS_S_REGL[rand()%(sizeof OPS_S_REGL/2)];
    if (!alt && mul) op=OPS_M_REGL[rand()%(sizeof OPS_M_REGL/2)]|0x800;
    if (alt) op=rand()&0x1ffff;
    if (inloop && !mem && !(lrand48()%0xa)) op=0xf000+lrand48()%14;
    res_p=0;
    rA=rand()&0xf;
    rB=rand()&0xf;
    rT=rand()%(16-3*inloop);
    if (has_mem_ && rT==16) rT=17;
    if (has_mem_ && rA==16) rA=17;
    if (has_mem_) addr=lrand48()%(MEMRGN_DATA_SZ-8);
    if (rand()&1) {
        B=lrand48()&0xffffffff;
	B_p=0;
	rA&=0xf;
	rT&=0xf;
	rB=-1;
    } else if (rand()&1) {
	B=(lrand48()&0x1fff)-0x1000;
	B_p=0;
	rB=-1;
    } else {
	B=contx->reg_gen[rB];
	B_p=contx->reg_genP[rB];
    }
    A=contx->reg_gen[rA];
    A_p=contx->reg_genP[rA];
    asmtext[0]=0;
    flags_in=contx->flags;

    has_alu=1;
    //has_mem=0;
    if (!alt && !mul) {
        __int128 res0;
        int A0=A,B0=B,res2;
        unsigned A0x=A,B0x=B;
        long long int A1=A,B1=B,res1;
        unsigned __int128 one=0x8000000000000000ull;
        unsigned long long pttr=A_p ? A : B;
	bool no_O=false;
	int mmem=0;
	char cmpstr[32];
	if (has_mem_) mmem=lrand48()%3;
        if ((op&0xf000)!=0xf000) switch(op&0xff) {
            case 0:
	    if (has_mem_==2) {
		(this-1)->gen_mem(NULL,8,mem,memp,addr);
		rA=16;
		A=(this-1)->res;
		A_p=(this-1)->res_p;
		if (rB>=0)
		    snprintf(asmtext,sizeof (asmtext), "plusq %%%s, %s\n",reg65[rB],prna(addr,inloop));
		else
		    snprintf(asmtext,sizeof (asmtext), "plusq $%i, %s\n",B,prna(addr,inloop));
	    } else if (has_mem_) {
		(this-1)->gen_mem(NULL,8,mem,memp,addr);
		rB=16;
		B=(this-1)->res;
		B_p=(this-1)->res_p;
		snprintf(asmtext,sizeof (asmtext), "plusq %s, %%%s, %%%s\n",prna(addr,inloop),reg65[rA],reg65[rT]);
	    } else if (rB>=0) snprintf(asmtext,sizeof asmtext,"plusq %%%s, %%%s, %%%s\n",reg65[rB],reg65[rA],reg65[rT]);
	    else snprintf(asmtext,sizeof asmtext,"plusq $%i, %%%s, %%%s\n",(int) B,reg65[rA],reg65[rT]);

            res0=((unsigned __int128)  A)+(unsigned __int128) B;
            if (A_p && B_p) excpt=11;
	    if (A_p && !B_p) res0= (res0&0xfffffffffff)|(A&0xfffff00000000000);
	    if (!A_p && B_p) res0= (res0&0xfffffffffff)|(B&0xfffff00000000000);
addie:
            ptr p,p2;
	    if (A_p || B_p) {
		res1=(res=res0)&0xfffffffffff;
		unsigned long long low,hi;
		p.val=pttr;
		unsigned long long b=p2.val;
		if (!no_O) p2.val=res;
		unsigned exp=p.val>>59;
		bool flip;

		if (!p.get_bounds2(no_O,p2,b,flip) && (exp!=31 || no_O)) {
		    excpt=11;
		    break;
		}
		if ((((res>>44)^(pttr>>44))&1)!=flip) {
		    excpt=11;
		    break;
		};
		res_p=1;
                flg64(res0);
	        res1=res0;
	    } else {
                res1=res=res0;
		res_p=0;
                flg64(res0);
	        res1=res0;
		B1=B;
                if (!no_O) {
		    flags|=((A1>0&&B1>0&&res1<0) || (A1<0&&B1<0&&res1>0))<<4;
                    flags|=(((A&0xf)+(B&0xf))&0x10)>>1;
	        }
	    }
            break;
            
            case 1:
	    if (has_mem_==2) {
		(this-1)->gen_mem(NULL,4,mem,memp,addr);
		rA=16;
		A0x=A=(this-1)->res;
		A_p=(this-1)->res_p;
		if (rB>=0)
		    snprintf(asmtext,sizeof (asmtext), "plusl %%%s, %s\n",reg32[rB],prna(addr,inloop));
		else
		    snprintf(asmtext,sizeof (asmtext), "plusl $%i, %s\n",B,prna(addr,inloop));
	    } else if (has_mem_) {
		(this-1)->gen_mem(NULL,4,mem,memp,addr);
		rB=16;
		B0x=B=(this-1)->res;
		B_p=(this-1)->res_p;
		snprintf(asmtext,sizeof (asmtext), "plusl %s, %%%s, %%%s\n",prna(addr,inloop),reg32[rA],reg32[rT]);
	    } else if (rB>=0) snprintf(asmtext,sizeof asmtext,"plusl %%%s, %%%s, %%%s\n",reg32[rB],reg32[rA],reg32[rT]);
	    else snprintf(asmtext,sizeof asmtext,"plusl $%i, %%%s, %%%s\n",(int) B,reg32[rA],reg32[rT]);

            res0=((unsigned __int128) A0x)+(unsigned __int128) B0x;
            res2=res=res0&0xffffffffull;
            flg32(res0);
	    B0=B;
            flags|=((A0>0&&B0>0&&res2<0) || (A0<0&&B0<0&&res2>0))<<4;
            flags|=(((A&0xf)+(B&0xf))&0x10)>>1;
            break;

            case 4:
	    if ((op&16384) && has_mem!=2) {
		rT=-1;
		strcpy(cmpstr,"cmpq");
	    } else if ((op&32768) && has_mem!=2) {
		rT=-1;
		strcpy(cmpstr,"cmpb");
	    } else {
		strcpy(cmpstr,"subq");
	    }
	    if (has_mem_==2) {
		(this-1)->gen_mem(NULL,8,mem,memp,addr);
		rA=16;
		A=(this-1)->res;
		A_p=(this-1)->res_p;
		if (rB>=0)
		    snprintf(asmtext,sizeof (asmtext), "subq %%%s, %s\n",reg65[rB],prna(addr,inloop));
		else
		    snprintf(asmtext,sizeof (asmtext), "subq $%i, %s\n",B,prna(addr,inloop));
	    } else  if (has_mem_) {
		(this-1)->gen_mem(NULL,(op&32768) ? 1 : 8,mem,memp,addr);
		if (cmpstr[0]=='c' && lrand48()&1) {
		    rA=16;
		    A=(this-1)->res;
		    A_p=(this-1)->res_p;
		    if (op&32768) {
			signed char sc;
			A=sc=A;
			B=sc=B;
			A_p=0;
			B_p=0;
		    }
		    if (rB>=0) snprintf(asmtext,sizeof (asmtext), "%s %%%s, %s\n",cmpstr,(op&32768) ? reg8[rB] : reg65[rB],prna(addr,inloop));
		    else snprintf(asmtext,sizeof (asmtext), "%s $%li, %s\n",cmpstr,B,prna(addr,inloop));
	            goto subie;
		}
		rB=16;
		B=(this-1)->res;
		B_p=(this-1)->res_p;
		if (cmpstr[0]=='c') {
		    if (op&32768) {
			signed char x1;
			A=x1= A;
			B=x1= B;
			A_p=0;
			B_p=0;
		    }
		    snprintf(asmtext,sizeof (asmtext), "%s %s, %%%s\n",cmpstr,prna(addr,inloop),(op&32768) ? reg8[rA] : reg65[rA]);
		} else {
		    snprintf(asmtext,sizeof (asmtext), "subq %s, %%%s, %%%s\n",prna(addr,inloop),reg65[rA],reg65[rT]);
		}
	    } else if (cmpstr[0]=='c') {
		if (op&32768) {
		    signed char x1;
		    A=x1= A;
		    B=x1= B;
		    A_p=0;
		    B_p=0;
		}
		if (rB>=0) snprintf(asmtext,sizeof asmtext,"%s %%%s, %%%s\n",cmpstr,(op&32768) ? reg8[rB] : reg65[rB],
				(op&32768) ? reg8[rA] : reg65[rA]);
	        else snprintf(asmtext,sizeof asmtext,"%s $%i, %%%s\n",cmpstr,(int) B,(op&32768) ? reg8[rA] : reg65[rA]);
	    } else {
		if (rB>=0) snprintf(asmtext,sizeof asmtext,"subq %%%s, %%%s, %%%s\n",reg65[rB],reg65[rA],reg65[rT]);
	        else snprintf(asmtext,sizeof asmtext,"subq $%i, %%%s, %%%s\n",(int) B,reg65[rA],reg65[rT]);
	    }
            subie:
            res0=((unsigned __int128) A)+((unsigned __int128)~B)+(one>>63);
	    if (A_p && !B_p) {
                res0=(((unsigned __int128) A)+(((unsigned __int128)~B)+(one>>63))&0xffffffffffful)|
		((unsigned __int128) A&0xfffff00000000000ul);
		goto addie; 
	    }
            res1=res=res0;
	    if (A_p && B_p) {
		res1=res=
	        res0=(((unsigned __int128) A&0xfffffffffff)+(((unsigned __int128)~B)&0xffffffffffful))+(one>>63);
		res1=res=res0&0xfffffffffff;
	    }
	    if (!A_p && B_p) excpt=11;
	    res_p=0;
            if (!(A_p && B_p)) flg64(res0);
	    else flgPTR(res0);
            B1=B;

            if (!(A_p && B_p)) flags|=((A1>=0&&B1<0&&res1<0) || (A1<0&&B1>0&&res1>0))<<4;
            if ((A_p && B_p)) flags|=((!(A1&0x80000000000)&&(B1&0x80000000000)&&(res1&0x80000000000)) || 
		((A1&0x80000000000)&&!(B1&0x80000000000)&&!(res1&0x80000000000)))<<4;
            flags|=(((A&0xf)-(B&0xf))&0x10)>>1;
            break;
            
            case 5:
	    if ((op&16384) && has_mem!=2) {
		rT=-1;
		strcpy(cmpstr,"cmpl");
	    } else if ((op&32768) && has_mem!=2) {
		rT=-1;
		strcpy(cmpstr,"cmpw");
	    } else {
		strcpy(cmpstr,"subl");
	    }
	    if (has_mem_==2) {
		(this-1)->gen_mem(NULL,4,mem,memp,addr);
		rA=16;
		A0x=A=(this-1)->res;
		A_p=(this-1)->res_p;
		if (rB>=0)
		    snprintf(asmtext,sizeof (asmtext), "subl %%%s, %s\n",reg32[rB],prna(addr,inloop));
		else
		    snprintf(asmtext,sizeof (asmtext), "subl $%i, %s\n",B,prna(addr,inloop));
	    } else if (has_mem_) {
		(this-1)->gen_mem(NULL,(op&32768) ? 2 : 4,mem,memp,addr);
		if (cmpstr[0]=='c' && lrand48()&1) {
		    rA=16;
		    A=(this-1)->res;
		    A_p=(this-1)->res_p;
		    A0x=A;
		    if (op&32768) {
			signed short s2;
			A0x=s2= A0x;
			B0x=s2= B0x;
			A_p=0;
			B_p=0;
		    }
		    if (rB>=0) snprintf(asmtext,sizeof (asmtext), "%s %%%s, %s\n",cmpstr,(op&32768) ? reg16[rB] : reg32[rB],prna(addr,inloop));
		    else snprintf(asmtext,sizeof (asmtext), "%s $%i, mem+%i(%rip)\n",cmpstr,B0x,prna(addr,inloop));
	            goto subie32;
		}
		rB=16;
		B0x=B=(this-1)->res;
		B_p=(this-1)->res_p;
		if (cmpstr[0]=='c') {
		    if (op&32768) {
			signed short p1;
			A0x=p1= A0x;
			B0x=p1= B0x;
			A_p=0;
			B_p=0;
		    }
		    snprintf(asmtext,sizeof (asmtext), "%s %s, %%%s\n",cmpstr,prna(addr,inloop),(op&16384) ? reg32[rA] : reg16[rA]);
		} else {
		    snprintf(asmtext,sizeof (asmtext), "subl %s, %%%s, %%%s\n",prna(addr,inloop),reg32[rA],reg32[rT]);
		}
	    } else if (cmpstr[0]=='c') {
		if (op&32768) {
		    signed short s2;
		    A0x=s2= A0x;
		    B0x=s2= B0x;
		    A_p=0;
		    B_p=0;
		}
	        if (rB>=0) snprintf(asmtext,sizeof asmtext,"%s %%%s, %%%s\n",cmpstr,(op&32768) ? reg16[rB] : reg32[rB],
				(op&32768) ? reg16[rA] : reg32[rA]);
		else snprintf(asmtext,sizeof asmtext,"%s $%i, %%%s\n",cmpstr,(int) B,(op&32768) ? reg16[rA] : reg32[rA]);
	    } else {
	        if (rB>=0) snprintf(asmtext,sizeof asmtext,"subl %%%s, %%%s, %%%s\n",reg32[rB],reg32[rA],reg32[rT]);
		else snprintf(asmtext,sizeof asmtext,"subl $%i, %%%s, %%%s\n",(int) B,reg32[rA],reg32[rT]);
	    }

subie32:
            res0=((unsigned __int128) A0x)+((unsigned __int128) ~B0x)+1;
            res2=res=res0&0xffffffffull;
            flg32(res0);
	    B0=B;
            flags|=((A0>=0&&B0<0&&res2<0) || (A0<0&&B0>0&&res2>0))<<4;
            flags|=(((A&0xf)-(B&0xf))&0x10)>>1;
            break;

            case 8:
	    if ((op&16384) && has_mem!=2) {
		rT=-1;
		strcpy(cmpstr,"testq");
	    } else {
		strcpy(cmpstr,"andq");
	    }
	    if (has_mem_==2) {
		(this-1)->gen_mem(NULL,8,mem,memp,addr);
		rA=16;
		A=(this-1)->res;
		A_p=(this-1)->res_p;
		if (rB>=0)
		    snprintf(asmtext,sizeof (asmtext), "andq %%%s, %s\n",reg65[rB],prna(addr,inloop));
		else
		    snprintf(asmtext,sizeof (asmtext), "andq $%i, %s\n",B,prna(addr,inloop));
	    } else if (has_mem_) {
		(this-1)->gen_mem(NULL,8,mem,memp,addr);
		if (cmpstr[0]=='t' && lrand48()&1) {
		    rA=16;
		    A=(this-1)->res;
		    A_p=(this-1)->res_p;
		    if (rB>=0) snprintf(asmtext,sizeof (asmtext), "%s %%%s, %s\n",cmpstr,reg65[rB],prna(addr,inloop));
		    else snprintf(asmtext,sizeof (asmtext), "%s $%li, %s\n",cmpstr,B,prna(addr,inloop));
	            goto andff;
		}
		rB=16;
		B=(this-1)->res;
		B_p=(this-1)->res_p;
		if (cmpstr[0]=='t') {
		    snprintf(asmtext,sizeof (asmtext), "%s %s, %%%s\n",cmpstr,prna(addr,inloop),reg65[rA]);
		} else {
		    rB=16;
		    B=(this-1)->res;
		    B_p=(this-1)->res_p;
		    snprintf(asmtext,sizeof (asmtext), "andq %s, %%%s, %%%s\n",prna(addr,inloop),reg65[rA],reg65[rT]);
		}
	    } else if (rB>=0) {
	        if (cmpstr[0]!='t') snprintf(asmtext,sizeof asmtext,"andq %%%s, %%%s, %%%s\n",reg65[rB],reg65[rA],reg65[rT]);
	        else snprintf(asmtext,sizeof asmtext,"testq %%%s, %%%s\n",reg65[rB],reg65[rA]);
	    } else {
	        if (cmpstr[0]!='t') snprintf(asmtext,sizeof asmtext,"andq $%i, %%%s, %%%s\n",(int) B,reg65[rA],reg65[rT]);
	        else snprintf(asmtext,sizeof asmtext,"testq $%i, %%%s\n",(int) B,reg65[rA]);
	    }
andff:
            res1=res=res0=A&B;
	    if (A_p && B_p) excpt=11;
	    if (A_p && !B_p) { 
		no_O=2; 
                res1=res=res0=A&(B|0xfffff00000000000);
		p2.val=B&0xfffffffffff;
		goto addie; 
	    }
	    if (!A_p && B_p) { 
		no_O=2; 
                res1=res=res0=B&(A|0xfffff00000000000);
		p2.val=A&0xfffffffffff;
		goto addie; 
	    }
            res1=res=res0;
            flg64(res0);
            break;

            case 9:
	    if ((op&16384) && has_mem!=2) {
		rT=-1;
		strcpy(cmpstr,"testl");
	    } else {
		strcpy(cmpstr,"andl");
	    }
	    if (has_mem_==2) {
		(this-1)->gen_mem(NULL,4,mem,memp,addr);
		rA=16;
		A0x=A=(this-1)->res;
		A_p=(this-1)->res_p;
		if (rB>=0)
		    snprintf(asmtext,sizeof (asmtext), "andl %%%s, %s\n",reg32[rB],prna(addr,inloop));
		else
		    snprintf(asmtext,sizeof (asmtext), "andl $%i, %s\n",B,prna(addr,inloop));
	    } else if (has_mem_) {
		(this-1)->gen_mem(NULL,4,mem,memp,addr);
		if (cmpstr[0]=='t' && lrand48()&1) {
		    rA=16;
		    A=(this-1)->res;
		    A_p=(this-1)->res_p;
		    A0x=A;
		    if (rB>=0) snprintf(asmtext,sizeof (asmtext), "%s %%%s, %s\n",cmpstr,reg32[rB],prna(addr,inloop));
		    else snprintf(asmtext,sizeof (asmtext), "%s $%li, %s\n",cmpstr,B,prna(addr,inloop));
	            goto andffl;
		}
		rB=16;
		B=(this-1)->res;
		B_p=(this-1)->res_p;
		B0x=B;
		if (cmpstr[0]=='t') {
		    snprintf(asmtext,sizeof (asmtext), "%s %s, %%%s\n",cmpstr,prna(addr,inloop),reg32[rA]);
		} else {
		    rB=16;
		    B0x=B=(this-1)->res;
		    B_p=(this-1)->res_p;
		    snprintf(asmtext,sizeof (asmtext), "andl %s, %%%s, %%%s\n",prna(addr,inloop),reg32[rA],reg32[rT]);
		}
	    } else if (rB>=0) {
	        if (cmpstr[0]!='t') snprintf(asmtext,sizeof asmtext,"andl %%%s, %%%s, %%%s\n",reg32[rB],reg32[rA],reg32[rT]);
	        else snprintf(asmtext,sizeof asmtext,"testl %%%s, %%%s\n",reg32[rB],reg32[rA]);
	    } else {
	        if (cmpstr[0]!='t') snprintf(asmtext,sizeof asmtext,"andl $%i, %%%s, %%%s\n",(int) B,reg32[rA],reg32[rT]);
	        else snprintf(asmtext,sizeof asmtext,"andl $%i, %%%s\n",(int) B,reg32[rA]);
	    }
andffl:
            res0=A0x&B0x;
            res2=res=res0&0xffffffffull;
            flg32(res);
            break;

            case 12:
	    if (has_mem_==2) {
		(this-1)->gen_mem(NULL,8,mem,memp,addr);
		rA=16;
		A=(this-1)->res;
		A_p=(this-1)->res_p;
		if (rB>=0)
		    snprintf(asmtext,sizeof (asmtext), "orq %%%s, %s\n",reg65[rB],prna(addr,inloop));
		else
		    snprintf(asmtext,sizeof (asmtext), "orq $%i, %s\n",B,prna(addr,inloop));
	    } else if (has_mem_) {
		(this-1)->gen_mem(NULL,8,mem,memp,addr);
		rB=16;
		B=(this-1)->res;
		B_p=(this-1)->res_p;
		snprintf(asmtext,sizeof (asmtext), "orq %s, %%%s, %%%s\n",prna(addr,inloop),reg65[rA],reg65[rT]);
	    } else if (rB>=0) snprintf(asmtext,sizeof asmtext,"orq %%%s, %%%s, %%%s\n",reg65[rB],reg65[rA],reg65[rT]);
	    else snprintf(asmtext,sizeof asmtext,"orq $%i, %%%s, %%%s\n",(int) B,reg65[rA],reg65[rT]);

            res1=res=res0=A|B;
	    if (A_p && B_p) excpt=11;
	    if (A_p && !B_p) { 
		no_O=1; 
                res1=res=res0=A|(B&0xfffffffffff);
		p2.val=B&0xfffffffffff;
		goto addie; 
	    }
	    if (!A_p && B_p) { 
		no_O=1; 
                res1=res=res0=B|(A&0xfffffffffff);
		p2.val=A&0xfffffffffff;
		goto addie; 
	    }
            res1=res=res0;
            flg64(res0);
            break;

            case 13:
	    if (has_mem_==2) {
		(this-1)->gen_mem(NULL,4,mem,memp,addr);
		rA=16;
		A0x=A=(this-1)->res;
		A_p=(this-1)->res_p;
		if (rB>=0)
		    snprintf(asmtext,sizeof (asmtext), "orl %%%s, %s\n",reg32[rB],prna(addr,inloop));
		else
		    snprintf(asmtext,sizeof (asmtext), "orl $%i, %s\n",B,prna(addr,inloop));
	    } else if (has_mem_) {
		(this-1)->gen_mem(NULL,4,mem,memp,addr);
		rB=16;
		B0x=B=(this-1)->res;
		B_p=(this-1)->res_p;
		snprintf(asmtext,sizeof (asmtext), "orl %s, %%%s, %%%s\n",prna(addr,inloop),reg32[rA],reg32[rT]);
	    } else if (rB>=0) snprintf(asmtext,sizeof asmtext,"orl %%%s, %%%s, %%%s\n",reg32[rB],reg32[rA],reg32[rT]);
	    else snprintf(asmtext,sizeof asmtext,"orl $%i, %%%s, %%%s\n",(int) B,reg32[rA],reg32[rT]);

            res0=A0x|B0x;
            res2=res=res0&0xffffffffull;
            flg32(res);
            break;

            case 16:
	    if (has_mem_==2) {
		(this-1)->gen_mem(NULL,8,mem,memp,addr);
		rA=16;
		A=(this-1)->res;
		A_p=(this-1)->res_p;
		if (rB>=0)
		    snprintf(asmtext,sizeof (asmtext), "xorq %%%s, %s\n",reg65[rB],prna(addr,inloop));
		else
		    snprintf(asmtext,sizeof (asmtext), "xorq $%i, %s\n",B,prna(addr,inloop));
	    } else if (has_mem_) {
		(this-1)->gen_mem(NULL,8,mem,memp,addr);
		rB=16;
		B=(this-1)->res;
		B_p=(this-1)->res_p;
		snprintf(asmtext,sizeof (asmtext), "xorq %s, %%%s, %%%s\n",prna(addr,inloop),reg65[rA],reg65[rT]);
	    } else if (rB>=0) snprintf(asmtext,sizeof asmtext,"xorq %%%s, %%%s, %%%s\n",reg65[rB],reg65[rA],reg65[rT]);
	    else snprintf(asmtext,sizeof asmtext,"xorq $%i, %%%s, %%%s\n",(int) B,reg65[rA],reg65[rT]);

            res1=res=res0=A^B;
	    if (A_p && B_p) excpt=11;
	    if (A_p && !B_p) { 
		no_O=1; 
                res1=res=res0=A^(B&0xfffffffffff);
		p2.val=B&0xfffffffffff;
		goto addie; 
	    }
	    if (!A_p && B_p) { 
		no_O=1; 
                res1=res=res0=B^(A&0xfffffffffff);
		p2.val=A&0xfffffffffff;
		goto addie; 
	    }
            res1=res=res0;
            flg64(res0);
            break;

            case 17:
	    if (has_mem_==2) {
		(this-1)->gen_mem(NULL,4,mem,memp,addr);
		rA=16;
		A0x=A=(this-1)->res;
		A_p=(this-1)->res_p;
		if (rB>=0)
		    snprintf(asmtext,sizeof (asmtext), "xorl %%%s, %s\n",reg32[rB],prna(addr,inloop));
		else
		    snprintf(asmtext,sizeof (asmtext), "xorl $%i, %s\n",B,prna(addr,inloop));
	    } else if (has_mem_) {
		(this-1)->gen_mem(NULL,4,mem,memp,addr);
		rB=16;
		B0x=B=(this-1)->res;
		B_p=(this-1)->res_p;
		snprintf(asmtext,sizeof (asmtext), "xorl %s, %%%s, %%%s\n",prna(addr,inloop),reg32[rA],reg32[rT]);
	    } else if (rB>=0) snprintf(asmtext,sizeof asmtext,"xorl %%%s, %%%s, %%%s\n",reg32[rB],reg32[rA],reg32[rT]);
	    else snprintf(asmtext,sizeof asmtext,"xorl $%i, %%%s, %%%s\n",(int) B,reg32[rA],reg32[rT]);

            res0=A0x^B0x;
            res2=res=res0&0xffffffffull;
            flg32(res);
            break;

            case 20:
	    if (rB>=0) snprintf(asmtext,sizeof asmtext,"salq %%%s, %%%s, %%%s\n",reg65[rB],reg65[rA],reg65[rT]);
	    else snprintf(asmtext,sizeof asmtext,"shlq $%i, %%%s, %%%s\n",(int) B,reg65[rA],reg65[rT]);

            res0=((__int128) A)<<(B&0x3f);
	    
            res1=res=res0;
	    if ((B&0xe00)==0x200 || (B&0xe00)==0x400 || (B&0xe00)==0x800) {
	            unsigned long long msk=0;
		    res=0;
		    if (B&0x80) res=A;
		    if (B&0x100) res=(A&0x80000000) ? 0xffffffff00000000ull : 0ull;
		    if (B&0x200) msk|=(A&0xffff0000)>>16;
		    if (B&0x400) msk|=((A&0xff000000)>>16)|((A&0xff0000));
		    if (B&0x800) msk|=(A&0xffff0000);
		    res=(res&~msk)|(res0&msk);
		    res1=res;
		    res0&=0xffffffffffffffffull<<63<<1;
		    res0|=res;//res1?
	    }
            flg64(res0);
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;

            case 21:
	    if (rB>=0) snprintf(asmtext,sizeof asmtext,"sall %%%s, %%%s, %%%s\n",reg32[rB],reg32[rA],reg32[rT]);
	    else snprintf(asmtext,sizeof asmtext,"shll $%i, %%%s, %%%s\n",(int) B,reg32[rA],reg32[rT]);

            res0=((__int128) A0x)<<(B0x&0x3f);
            res2=res=res0&0xffffffffull;
            if ((B&0xe00)==0x200 || (B&0xe00)==0x400 || (B&0xe00)==0x800) {
	            unsigned long long msk=0;
		    res=0;
		    if (B&0x80) res=A;
		    if (B&0x100) res=(A&0x80000000) ? 0xffffffff00000000ull : 0ull;
		    if (B&0x200) msk|=(A&0xffff0000)>>16;
		    if (B&0x400) msk|=((A&0xff000000)>>16)|((A&0xff0000));
		    if (B&0x800) msk|=(A&0xffff0000);
		    res=(res&~msk)|(res0&msk);
		    res1=res;
		    res0&=0xffffffffffffffffull<<63<<1;
		    res0|=res;//res1?
	    } 
            if ((B&0x100) && (A&0x80000000) { res|=0xffffffff00000000ull; res1=res; }
            flg32(res0);
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;

            case 24:
	    if (rB>=0) snprintf(asmtext,sizeof asmtext,"shrq %%%s, %%%s, %%%s\n",reg65[rB],reg65[rA],reg65[rT]);
	    else snprintf(asmtext,sizeof asmtext,"shrq $%i, %%%s, %%%s\n",(int) B,reg65[rA],reg65[rT]);

            res0=(B&0x3f) ?((__int128)  A) >>((B&0x3f)-1) :((__int128)  A)<<1;
            res1=res=(res0>>1);
            if ((B&0xe00)==0x200 || (B&0xe00)==0x400 || (B&0xe00)==0x800) {
	            unsigned long long msk=0;
		    res=0;
		    if (B&0x80) res=A;
		    if (B&0x100) res=(A&0x80000000) ? 0xffffffff00000000ull : 0ull;
		    if (B&0x200) msk|=(A&0xffff0000)>>16;
		    if (B&0x400) msk|=((A&0xff000000)>>16)|((A&0xff0000));
		    if (B&0x800) msk|=(A&0xffff0000);
		    res=(res&~msk)|((res0>>1)&msk);
		    res1=res;
		    res0&=(0xffffffffffffffffull<<63<<2)|1;
		    res0|=(__int128 ) res<<1;
	    } 
	    flg64(((res0>>1)&0xffffffffffffffffull)|((res0&0x1) ? one<<1:0));
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;

            case 25:
	    if (rB>=0) snprintf(asmtext,sizeof asmtext,"shrl %%%s, %%%s, %%%s\n",reg32[rB],reg32[rA],reg32[rT]);
	    else snprintf(asmtext,sizeof asmtext,"shrl $%i, %%%s, %%%s\n",(int) B,reg32[rA],reg32[rT]);

            res0=(B0x&0x3f) ?((__int128)A0x) >>((B0x&0x3f)-1) :((__int128)  A0x)<<1;
            res=(res0>>1)&0xffffffffull;
            if ((B&0xe00)==0x200 || (B&0xe00)==0x400 || (B&0xe00)==0x800) {
	            unsigned long long msk=0;
		    res=0;
		    if (B&0x80) res=A;
		    if (B&0x100) res=(A&0x80000000) ? 0xffffffff00000000ull : 0ull;
		    if (B&0x200) msk|=(A&0xffff0000)>>16;
		    if (B&0x400) msk|=((A&0xff000000)>>16)|((A&0xff0000));
		    if (B&0x800) msk|=(A&0xffff0000);
		    res=(res&~msk)|((res0>>1)&msk);
		    res1=res;
		    res0&=(0xffffffffffffffffull<<63<<2)|1;
		    res0|=res<<1;//res1?
	    }  
	    if ((B&0x100) && (A&0x80000000) { res|=0xffffffff00000000ull; res1=res; }
  
	    flg32(((res0>>1)&0xffffffffu)|((res0&0x1)<<32));
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;

            case 28:
	    if (rB>=0) snprintf(asmtext,sizeof asmtext,"sarq %%%s, %%%s, %%%s\n",reg65[rB],reg65[rA],reg65[rT]);
	    else snprintf(asmtext,sizeof asmtext,"sarq $%i, %%%s, %%%s\n",(int) B,reg65[rA],reg65[rT]);

            res0=(B&0x3f) ?((__int128) A1) >>((B&0x3f)-1) :((__int128)  A1)<<1;
            res1=res=(res0>>1);
       	    if ((B&0xe00)==0x200 || (B&0xe00)==0x400 || (B&0xe00)==0x800) {
	            unsigned long long msk=0;
		    res=0;
		    if (B&0x80) res=A;
		    if (B&0x100) res=(A&0x80000000) ? 0xffffffff00000000ull : 0ull;
		    if (B&0x200) msk|=(A&0xffff0000)>>16;
		    if (B&0x400) msk|=((A&0xff000000)>>16)|((A&0xff0000));
		    if (B&0x800) msk|=(A&0xffff0000);
		    res=(res&~msk)|((res0>>1)&msk);
		    res1=res;
		    res0&=(0xffffffffffffffffull<<63<<2)|1;
		    res0|=(__int128) res<<1;
	    }     
	    flg64(((res0>>1)&0xffffffffffffffffull)|((res0&0x1) ? one<<1 : 0));
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;

            case 29:
	    if (rB>=0) snprintf(asmtext,sizeof asmtext,"sarl %%%s, %%%s, %%%s\n",reg32[rB],reg32[rA],reg32[rT]);
	    else snprintf(asmtext,sizeof asmtext,"sarl $%i, %%%s, %%%s\n",(int) B,reg32[rA],reg32[rT]);

            res0=(B0x&0x3f) ? ((__int128) A0) >>((B0x&0x3f)-1) :((__int128) A0)<<1;
            res2=res=(res0>>1)&0xffffffffull;
            if ((B&0xe00)==0x200 || (B&0xe00)==0x400 || (B&0xe00)==0x800) {
	            unsigned long long msk=0;
		    res=0;
		    if (B&0x80) res=A;
		    if (B&0x100) res=(A&0x80000000) ? 0xffffffff00000000ull : 0ull;
		    if (B&0x200) msk|=(A&0xffff0000)>>16;
		    if (B&0x400) msk|=((A&0xff000000)>>16)|((A&0xff0000));
		    if (B&0x800) msk|=(A&0xffff0000);
		    res=(res&~msk)|((res0>>1)&msk);
		    res1=res;
		    res0&=(0xffffffffffffffffull<<63<<2)|1;
		    res0|=res<<1;
	    }  
	    if ((B&0x100) && (A&0x80000000) { res|=0xffffffff00000000ull; res1=res; }
	    flg32(((res0>>1)&0xffffffffu)|((res0&0x1)<<32));
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;
 
            case 32:
	    if (has_mem_==2) {
		(this-1)->gen_memw(NULL,8,mem,memp,addr,A,A_p);
		snprintf((*(this-1)).asmtext,sizeof (asmtext), "movq %%%s, %s\n",reg65[rA],prna(addr,inloop));
		(this-1)->rT=-1;
		(this-1)->flags=flags_in;
		rtn=false;
		break;
	    } else if (has_mem_) {
		(this-1)->gen_mem(NULL,8,mem,memp,addr);
		snprintf((*(this-1)).asmtext,sizeof (asmtext), "movq %s, %%%s\n",prna(addr,inloop),reg65[rT]);
                (*(this-1)).rT=rT;
		rtn=false;
                (this-1)->flags=flags_in;
		break;
	    } else if (rB>=0) snprintf(asmtext,sizeof asmtext,"movq %%%s,  %%%s\n",reg65[rB],reg65[rT]);
	    else snprintf(asmtext,sizeof asmtext,"movq $%i, %%%s\n",(int) B,reg65[rT]);
            res=B;
            flags=flags_in;
            break;

            case 33:
	    if (has_mem_==2) {
		(this-1)->gen_memw(NULL,4,mem,memp,addr,A,A_p);
		snprintf((*(this-1)).asmtext,sizeof (asmtext), "movl %%%s, %s\n",reg32[rA],prna(addr,inloop));
		(this-1)->rT=-1;
		(this-1)->flags=flags_in;
		rtn=false;
		break;
	    } else if (has_mem_) {
		(this-1)->gen_mem(NULL,4,mem,memp,addr);
		snprintf((*(this-1)).asmtext,sizeof (asmtext), "movl %s, %%%s\n",prna(addr,inloop),reg32[rT]);
                (*(this-1)).rT=rT;
		rtn=false;
                (this-1)->flags=flags_in;
		break;
	    } else if (rB>=0) snprintf(asmtext,sizeof asmtext,"movl %%%s,  %%%s\n",reg32[rB],reg32[rT]);
	    else snprintf(asmtext,sizeof asmtext,"movl $%i, %%%s\n",(int) B,reg32[rT]);
            res=B&0xffffffffull;
            flags=flags_in;
            break;

            case 34:
	    if (has_mem_==2) {
		(this-1)->gen_memw(NULL,2,mem,memp,addr,A,A_p);
		snprintf((*(this-1)).asmtext,sizeof (asmtext), "movw %%%s, %s\n",reg16[rA],prna(addr,inloop));
		(this-1)->rT=-1;
		(this-1)->flags=flags_in;
		rtn=false;
		break;
	    } else if (rB>=0) snprintf(asmtext,sizeof asmtext,"movw %%%s,  %%%s\n",reg16[rB],reg16[rT]);
	    else snprintf(asmtext,sizeof asmtext,"movw $%i, %%%s\n",(int) B,reg16[rT]);
	    rA=rT;
	    A=contx->reg_gen[rA];
            res=(B&0xffffull)|(A&0xffffffffffff0000ull);
            flags=flags_in;
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;

            case 35:
	    if (rB<0) {
		rB=rand()&0x1f;
		B=contx->reg_gen[rB];
		B_p=contx->reg_genP[rB];
	    }
	    if (has_mem_==2) {
		(this-1)->gen_memw(NULL,1,mem,memp,addr,A,A_p);
		snprintf((*(this-1)).asmtext,sizeof (asmtext), "movb %%%s, %s\n",reg8[rA],prna(addr,inloop));
		(this-1)->rT=-1;
		(this-1)->flags=flags_in;
		rtn=false;
		break;
	    } else if (rB>=0) snprintf(asmtext,sizeof asmtext,"movb %%%s,  %%%s\n",reg8[rB+((op&1024)>>5)],reg8[rT+((op&256)>>3)]);
	    else snprintf(asmtext,sizeof asmtext,"movb $%i, %%%s\n",(int) B,reg8[rT]);
	    rA=rT;
	    A=contx->reg_gen[rA];
            if (op&256) res=(A&0xffffffffffff00ffull)| ((op&1024) ? B&0xff00ull :
                (B&0xffull)<<8);
            else res=(A&0xffffffffffffff00ull)| ((op&1024) ? (B&0xff00ull)>>8 :
                B&0xffull);
            flags=flags_in;
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;

            case 36:
	    if (has_mem_) {
		(this-1)->gen_mem(NULL,1,mem,memp,addr);
		snprintf((*(this-1)).asmtext,sizeof (asmtext), "movzbl %s, %%%s\n",prna(addr,inloop),reg32[rT]);
                (*(this-1)).rT=rT;
		rtn=false;
		(*(this-1)).flags=flags_in;
		break;
	    } else if (rB<0) {
		rB=rand()&0x1f;
		B=contx->reg_gen[rB];
		B_p=contx->reg_genP[rB];
	    }
	    if (rB>=0) snprintf(asmtext,sizeof asmtext,"movzbl %%%s,  %%%s\n",reg8[rB],reg32[rT]);
	    else snprintf(asmtext,sizeof asmtext,"movzbl $%i, %%%s\n",(int) B,reg32[rT]);
            res=B&0xffull;
            flags=flags_in;
            break;

            case 37:
	    if (has_mem_) {
		(this-1)->gen_mem(NULL,2,mem,memp,addr);
		snprintf((*(this-1)).asmtext,sizeof (asmtext), "movzwl %s, %%%s\n",prna(addr,inloop),reg32[rT]);
                (*(this-1)).rT=rT;
		rtn=false;
		(*(this-1)).flags=flags_in;
		break;
	    } else if (rB<0) {
		rB=rand()&0x1f;
		B=contx->reg_gen[rB];
		B_p=contx->reg_genP[rB];
	    }
	    if (rB>=0) snprintf(asmtext,sizeof asmtext,"movzwl %%%s,  %%%s\n",reg16[rB],reg32[rT]);
	    else snprintf(asmtext,sizeof asmtext,"movzwl $%i, %%%s\n",(int) B,reg32[rT]);
            res=B&0xffffull;
            flags=flags_in;
            break;

            case 39:
	    if (rB<0) {
		rB=rand()&0x1f;
		B=contx->reg_gen[rB];
		B_p=contx->reg_genP[rB];
	    }
	    if (rB>=0) snprintf(asmtext,sizeof asmtext,"movsbq %%%s,  %%%s\n",reg8[rB],reg65[rT]);
	    else snprintf(asmtext,sizeof asmtext,"movsbq $%i, %%%s\n",(int) B,reg65[rT]);
            res=(B&0x80) ? B|0xffffffffffffff00ull : B&0xffull;
            flags=flags_in;
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;

            case 40:
	    if (rB<0) {
		rB=rand()&0x1f;
		B=contx->reg_gen[rB];
		B_p=contx->reg_genP[rB];
	    }
	    if (rB>=0) snprintf(asmtext,sizeof asmtext,"movswq %%%s,  %%%s\n",reg16[rB],reg65[rT]);
	    else snprintf(asmtext,sizeof asmtext,"movswq $%i, %%%s\n",(int) B,reg65[rT]);
            res=(B&0x8000) ? B|0xffffffffffff0000ull : B&0xffffull;
            flags=flags_in;
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;

            case 41:
	    if (rB<0) {
		rB=rand()&0x1f;
		B=contx->reg_gen[rB];
		B_p=contx->reg_genP[rB];
	    }
	    if (rB>=0) snprintf(asmtext,sizeof asmtext,"movslq %%%s,  %%%s\n",reg32[rB],reg65[rT]);
	    else snprintf(asmtext,sizeof asmtext,"movslq $%i, %%%s\n",(int) B,reg65[rT]);
            res=(B&0x80000000) ? B|0xffffffff00000000ull : B&0xffffffffull;
            flags=flags_in;
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;

            case 42:
	    if (rB<0) {
		rB=rand()&0x1f;
		B=contx->reg_gen[rB];
		B_p=contx->reg_genP[rB];
		B0=B;
		B0x=B;
	    }
	    if (rB>=0) snprintf(asmtext,sizeof asmtext,"movsbl %%%s,  %%%s\n",reg8[rB],reg32[rT]);
	    else snprintf(asmtext,sizeof asmtext,"movsbl $%i, %%%s\n",(int) B,reg32[rT]);
            res=(B0&0x80) ? B0x|0xffffff00ull : B0x&0xffull;
            flags=flags_in;
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;

            case 43:
	    if (rB<0) {
		rB=rand()&0x1f;
		B=contx->reg_gen[rB];
		B_p=contx->reg_genP[rB];
		B0=B;
		B0x=B;
	    }
	    if (rB>=0) snprintf(asmtext,sizeof asmtext,"movswl %%%s,  %%%s\n",reg16[rB],reg32[rT]);
	    else snprintf(asmtext,sizeof asmtext,"movswl $%i, %%%s\n",(int) B,reg32[rT]);
            res=(B0&0x8000) ? B0x|0xffff0000ull : B0x&0xffffull;
            flags=flags_in;
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;

            case 48:
            case 49:
            op|=rand()&0x700;
	    if (rB<0) {
		rB=rand()&0x1f;
		B=contx->reg_gen[rB];
		B_p=contx->reg_genP[rB];
	    }
	    snprintf(asmtext,sizeof asmtext,"cmov%sq %%%s, %%%s, %%%s\n",COND(op),reg65[rB],reg65[rA],reg65[rT]);

            res=testj(((op&0x700)>>7)|(op&0x1)) ? B : A;
            res_p=testj(((op&0x700)>>7)|(op&0x1)) ? B_p : A_p;
            flags=flags_in;
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;
            
            case 50:
            case 51:
            op|=rand()&0x700;
            op|=rand()&0x700;
	    if (rB<0) {
		rB=rand()&0x1f;
		B=contx->reg_gen[rB];
		B_p=contx->reg_genP[rB];
		B0=B;
		B0x=B;
	    }
	    snprintf(asmtext,sizeof asmtext,"cmov%sl %%%s, %%%s, %%%s\n",COND(op),reg32[rB],reg32[rA],reg32[rT]);
            res=testj(((op&0x700)>>7)|(op&0x1)) ? B0x : A0x;
            flags=flags_in;
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;
            
            
            case 52:
            case 53:
            op|=rand()&0x700;
	    if (rB<0) {
		rB=rand()&0x1f;
		B=contx->reg_gen[rB];
		B_p=contx->reg_genP[rB];
	    }
	    snprintf(asmtext,sizeof asmtext,"clahf%sl %%%s\n",COND(op),reg32[rA]);
            res=0;
            flags=testj(((op&0x700)>>7)|(op&0x1)) ? A&0x3f : flags_in;
	    rT=-1;
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;

            case 54:
            case 55:
            op|=rand()&0x700;
	    if (rB<0) {
		rB=rand()&0x1f;
		B=contx->reg_gen[rB];
		B_p=contx->reg_genP[rB];
	    }
	    snprintf(asmtext,sizeof asmtext,"cset%sl %%%s\n",COND(op),reg32[rT]);
            res=testj(((op&0x700)>>7)|(op&0x1));
            flags=flags_in;
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;

            case 56:
	    if (rB<0) {
		rB=rand()&0x1f;
		B=contx->reg_gen[rB];
		B_p=contx->reg_genP[rB];
	    }
	    snprintf(asmtext,sizeof asmtext,"sahfl %%%s\n",reg32[rT]);
            res=flags_in&0x3f;
            flags=flags_in;
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;

            case 57:
	    if (rB<0) {
		rB=rand()&0x1f;
		B=contx->reg_gen[rB];
		B_p=contx->reg_genP[rB];
	    }
	    snprintf(asmtext,sizeof asmtext,"lahfl %%%s\n",reg32[rA]);
            res=0;
            flags=A&0x3f;
	    rT=-1;
	    if (has_mem_) {
		rtn=false;
		(*(this-1))=*this;
	    }
            break;
        } else {
           snprintf(asmtext, sizeof amstext, "j%s LaBl%i\nLaBl%i:\n",COND(op&0xf),lbl,lbl);
           lbl++;
           res=0;
           rT=-1;
           flags=flags_in; 
           rtn=false;
      }
    } else if (!alt) {
        __int128 AS=(long long) A;
        unsigned __int128 A0=A;
        __int128 BS=(long long) B;
        unsigned __int128 B0=B;
        __int128 resS;
        unsigned __int128 res0;
        int As=(int) A;
        unsigned Au=(unsigned) A;
        int Bs=(int) B;
        unsigned Bu=(unsigned) B;
        long long resSx;
        unsigned long long res0x;
        unsigned __int128 resU;
        resSx= (signed long long) As * (signed long long) Bs;
        res0x=(unsigned long long) Au * (unsigned long long) Bu;
        res0=A0*B0;
        resS=AS*BS;
        switch(op&0xff) {
            case 1:
            res=res0x;
            flgM64(res0x,true);
            break;

            case 2:
            res=res0x & 0xffffffffull;
            flgM64(res0x);
            break;

            case 3:
            res=res0;
            flgM128(res0);
            break;
            
            case 9:
            res=resSx;
            flgM64(resSx,1);
            break;

            case 10:
            res=resSx & 0xffffffffull;
            flgM64(resSx);
            break;

            case 11:
            res=resS;
            flgM128(resS);
            break;

            case 5:
            resU=resS>>63;
            res=resU>>1;
            flgM128(resS,1);
            break;
            
            case 7:
            resU=res0>>63;
            res=resU>>1;
            flgM128(res0,1);
            break;

            case 12:
            fp_get_ext((op&0x400) ? (long double) (signed long long) B : 
              (long double) B,num);
            flags=flags_in;
            break;
            
            case 13:
            fp_get_double((op&0x400) ? (double) (signed long long) B : 
              (double) B,num);
            flags=flags_in;
            break;

            case 14:
            fp_get_single((op&0x400) ? (float) (signed long long) B : (float) B,num);
            flags=flags_in;
            break;
        }
    }
    en=rand()&0xff!=0;
    if (!(op&0x1000)) contx->flags=flags;
    if (has_mem_ && ((*(this-1)).rT>=0)) {
	contx->reg_gen[(*(this-1)).rT]=(*(this-1)).res;
	contx->reg_genP[(*(this-1)).rT]=(*(this-1)).res_p;
    }
    if ((rtn||!has_mem_) && (rT>=0) && has_mem_!=2) {
	contx->reg_gen[rT]=res;
	contx->reg_genP[rT]=res_p;
    }
    if (has_mem_==2 && rtn) {
	rT=16;
	contx->reg_gen[rT]=res;
	contx->reg_genP[rT]=res_p;
        (this+1)->gen_memw(NULL,(this-1)->op,mem,memp,addr,res,res_p);
    }
    return rtn;
}
    
bool req::exec(req *prev1,hcont *contx,char *mem,char *memp,int itcnt) {
    res_p=0;
    res=0;
    A=contx->reg_gen[rA&0x1f];
    A_p=contx->reg_genP[rA&0x1f];
    B=contx->reg_gen[rB&0x1f];
    B_p=contx->reg_genP[rB&0x1f];
    flags_in=contx->flags;
    if (has_mem==1) {
        gen_mem(NULL,op,mem,memp,addr+itcnt*8);
        contx->reg_gen[rT&0x1f]=res;
        contx->reg_genP[rT&0x1f]=res_p;
	return false;
    } else if (has_mem==2) {
        res=contx->reg_gen[rA&0x1f];
        res_p=contx->reg_genP[rA&0x1f];
        gen_memw(NULL,op,mem,memp,addr+itcnt*8,res,res_p);
	return false;
    } else if (!alt && !mul) {
        __int128 res0;
        int A0=A,B0=B,res2;
        unsigned A0x=A,B0x=B;
        long long int A1=A,B1=B,res1;
        unsigned __int128 one=0x8000000000000000ull;
        unsigned long long pttr=A_p ? A : B;
	bool no_O=false;
	int mmem=0;
        switch(op&0xff) {
            case 0:

            res0=((unsigned __int128)  A)+(unsigned __int128) B;
            if (A_p && B_p) excpt=11;
	    if (A_p && !B_p) res0= (res0&0xfffffffffff)|(A&0xfffff00000000000);
	    if (!A_p && B_p) res0= (res0&0xfffffffffff)|(B&0xfffff00000000000);
addie:
            ptr p,p2;
	    if (A_p || B_p) {
		res1=(res=res0)&0xfffffffffff;
		unsigned long long low,hi;
		p.val=pttr;
		unsigned long long b=p2.val;
		if (!no_O) p2.val=res;
		unsigned exp=p.val>>59;
		bool flip;

		if (!p.get_bounds2(no_O,p2,b,flip) && (exp!=31 || no_O)) {
		    excpt=11;
		    break;
		}
		if ((((res>>44)^(pttr>>44))&1)!=flip) {
		    excpt=11;
		    break;
		};
		res_p=1;
                flg64(res0);
	        res1=res0;
	    } else {
                res1=res=res0;
		res_p=0;
                flg64(res0);
	        res1=res0;
		B1=B;
                if (!no_O) {
		    flags|=((A1>0&&B1>0&&res1<0) || (A1<0&&B1<0&&res1>0))<<4;
                    flags|=(((A&0xf)+(B&0xf))&0x10)>>1;
	        }
	    }
            break;
            
            case 1:

            res0=((unsigned __int128) A0x)+(unsigned __int128) B0x;
            res2=res=res0&0xffffffffull;
            flg32(res0);
	    B0=B;
            flags|=((A0>0&&B0>0&&res2<0) || (A0<0&&B0<0&&res2>0))<<4;
            flags|=(((A&0xf)+(B&0xf))&0x10)>>1;
            break;

            case 4:

            res0=((unsigned __int128) A)+((unsigned __int128)~B)+(one>>63);
	    if (A_p && !B_p) {
                res0=(((unsigned __int128) A)+(((unsigned __int128)~B)+(one>>63))&0xffffffffffful)|
		((unsigned __int128) A&0xfffff00000000000ul);
		goto addie; 
	    }
            res1=res=res0;
	    if (A_p && B_p) {
		res1=res=
	        res0=(((unsigned __int128) A&0xfffffffffff)+(((unsigned __int128)~B)&0xffffffffffful))+(one>>63);
		res1=res=res0&0xfffffffffff;
	    }
	    if (!A_p && B_p) excpt=11;
	    res_p=0;
            if (!(A_p && B_p)) flg64(res0);
	    else flgPTR(res0);
            B1=B;

            if (!(A_p && B_p)) flags|=((A1>=0&&B1<0&&res1<0) || (A1<0&&B1>0&&res1>0))<<4;
            if ((A_p && B_p)) flags|=((!(A1&0x80000000000)&&(B1&0x80000000000)&&(res1&0x80000000000)) || 
		((A1&0x80000000000)&&!(B1&0x80000000000)&&!(res1&0x80000000000)))<<4;
            flags|=(((A&0xf)-(B&0xf))&0x10)>>1;
            break;
            
            case 5:

            res0=((unsigned __int128) A0x)+((unsigned __int128) ~B0x)+1;
            res2=res=res0&0xffffffffull;
            flg32(res0);
	    B0=B;
            flags|=((A0>=0&&B0<0&&res2<0) || (A0<0&&B0>0&&res2>0))<<4;
            flags|=(((A&0xf)-(B&0xf))&0x10)>>1;
            break;

            case 8:

            res1=res=res0=A&B;
	    if (A_p && B_p) excpt=11;
	    if (A_p && !B_p) { 
		no_O=2; 
                res1=res=res0=A&(B|0xfffff00000000000);
		p2.val=B&0xfffffffffff;
		goto addie; 
	    }
	    if (!A_p && B_p) { 
		no_O=2; 
                res1=res=res0=B&(A|0xfffff00000000000);
		p2.val=A&0xfffffffffff;
		goto addie; 
	    }
            res1=res=res0;
            flg64(res0);
            break;

            case 9:

            res0=A0x&B0x;
            res2=res=res0&0xffffffffull;
            flg32(res);
            break;

            case 12:

            res1=res=res0=A|B;
	    if (A_p && B_p) excpt=11;
	    if (A_p && !B_p) { 
		no_O=1; 
                res1=res=res0=A|(B&0xfffffffffff);
		p2.val=B&0xfffffffffff;
		goto addie; 
	    }
	    if (!A_p && B_p) { 
		no_O=1; 
                res1=res=res0=B|(A&0xfffffffffff);
		p2.val=A&0xfffffffffff;
		goto addie; 
	    }
            res1=res=res0;
            flg64(res0);
            break;

            case 13:

            res0=A0x|B0x;
            res2=res=res0&0xffffffffull;
            flg32(res);
            break;

            case 16:

            res1=res=res0=A^B;
	    if (A_p && B_p) excpt=11;
	    if (A_p && !B_p) { 
		no_O=1; 
                res1=res=res0=A^(B&0xfffffffffff);
		p2.val=B&0xfffffffffff;
		goto addie; 
	    }
	    if (!A_p && B_p) { 
		no_O=1; 
                res1=res=res0=B^(A&0xfffffffffff);
		p2.val=A&0xfffffffffff;
		goto addie; 
	    }
            res1=res=res0;
            flg64(res0);
            break;

            case 17:

            res0=A0x^B0x;
            res2=res=res0&0xffffffffull;
            flg32(res);
            break;

            case 20:

            res0=((__int128) A)<<(B&0x3f);
            res1=res=res0;
            flg64(res0);
            break;

            case 21:

            res0=((__int128) A0x)<<(B0x&0x3f);
            res2=res=res0&0xffffffffull;
            flg32(res0);
            break;

            case 24:

            res0=(B&0x3f) ?((__int128)  A) >>((B&0x3f)-1) :((__int128)  A)<<1;
            res1=res=(res0>>1);
            flg64(((res0>>1)&0xffffffffffffffffull)|((res0&0x1) ? one<<1:0));
            break;

            case 25:

            res0=(B0x&0x3f) ?((__int128)A0x) >>((B0x&0x3f)-1) :((__int128)  A0x)<<1;
            res=(res0>>1)&0xffffffffull;
            flg32(((res0>>1)&0xffffffffu)|((res0&0x1)<<32));
            break;

            case 28:

            res0=(B&0x3f) ?((__int128) A1) >>((B&0x3f)-1) :((__int128)  A1)<<1;
            res1=res=(res0>>1);
            flg64(((res0>>1)&0xffffffffffffffffull)|((res0&0x1) ? one<<1 : 0));
            break;

            case 29:

            res0=(B0x&0x3f) ? ((__int128) A0) >>((B0x&0x3f)-1) :((__int128) A0)<<1;
            res2=res=(res0>>1)&0xffffffffull;
            flg32(((res0>>1)&0xffffffffu)|((res0&0x1)<<32));
            break;
 
            case 32:
            res=B;
            flags=flags_in;
            break;

            case 33:
            res=B&0xffffffffull;
            flags=flags_in;
            break;

            case 34:
	    rA=rT;
	    A=contx->reg_gen[rA];
            res=(B&0xffffull)|(A&0xffffffffffff0000ull);
            flags=flags_in;
            break;

            case 35:
            if (op&256) res=(A&0xffffffffffff00ffull)| ((op&1024) ? B&0xff00ull :
                (B&0xffull)<<8);
            else res=(A&0xffffffffffffff00ull)| ((op&1024) ? (B&0xff00ull)>>8 :
                B&0xffull);
            flags=flags_in;
            break;

            case 36:
            res=B&0xffull;
            flags=flags_in;
            break;

            case 37:
            res=B&0xffffull;
            flags=flags_in;
            break;

            case 39:
            res=(B&0x80) ? B|0xffffffffffffff00ull : B&0xffull;
            flags=flags_in;
            break;

            case 40:
            res=(B&0x8000) ? B|0xffffffffffff0000ull : B&0xffffull;
            flags=flags_in;
            break;

            case 41:
            res=(B&0x80000000) ? B|0xffffffff00000000ull : B&0xffffffffull;
            flags=flags_in;
            break;

            case 42:
            res=(B0&0x80) ? B0x|0xffffff00ull : B0x&0xffull;
            flags=flags_in;
            break;

            case 43:
            res=(B0&0x8000) ? B0x|0xffff0000ull : B0x&0xffffull;
            flags=flags_in;
            break;

            case 48:
            case 49:

            res=testj(((op&0x700)>>7)|(op&0x1)) ? B : A;
            res_p=testj(((op&0x700)>>7)|(op&0x1)) ? B_p : A_p;
            flags=flags_in;
            break;
            
            case 50:
            case 51:
            res=testj(((op&0x700)>>7)|(op&0x1)) ? B0x : A0x;
            flags=flags_in;
            break;
            
            
            case 52:
            case 53:
            res=0;
            flags=testj(((op&0x700)>>7)|(op&0x1)) ? A&0x3f : flags_in;
            break;

            case 54:
            case 55:
            res=testj(((op&0x700)>>7)|(op&0x1));
            flags=flags_in;
            break;

            case 56:
            res=flags_in&0x3f;
            flags=flags_in;
            break;

            case 57:
            res=0;
            flags=A&0x3f;
            break;
        }
    } else if (!alt) {
        __int128 AS=(long long) A;
        unsigned __int128 A0=A;
        __int128 BS=(long long) B;
        unsigned __int128 B0=B;
        __int128 resS;
        unsigned __int128 res0;
        int As=(int) A;
        unsigned Au=(unsigned) A;
        int Bs=(int) B;
        unsigned Bu=(unsigned) B;
        long long resSx;
        unsigned long long res0x;
        unsigned __int128 resU;
        resSx= (signed long long) As * (signed long long) Bs;
        res0x=(unsigned long long) Au * (unsigned long long) Bu;
        res0=A0*B0;
        resS=AS*BS;
        switch(op&0xff) {
            case 1:
            res=res0x;
            flgM64(res0x,true);
            break;

            case 2:
            res=res0x & 0xffffffffull;
            flgM64(res0x);
            break;

            case 3:
            res=res0;
            flgM128(res0);
            break;
            
            case 9:
            res=resSx;
            flgM64(resSx,1);
            break;

            case 10:
            res=resSx & 0xffffffffull;
            flgM64(resSx);
            break;

            case 11:
            res=resS;
            flgM128(resS);
            break;

            case 5:
            resU=resS>>63;
            res=resU>>1;
            flgM128(resS,1);
            break;
            
            case 7:
            resU=res0>>63;
            res=resU>>1;
            flgM128(res0,1);
            break;

            case 12:
            fp_get_ext((op&0x400) ? (long double) (signed long long) B : 
              (long double) B,num);
            flags=flags_in;
            break;
            
            case 13:
            fp_get_double((op&0x400) ? (double) (signed long long) B : 
              (double) B,num);
            flags=flags_in;
            break;

            case 14:
            fp_get_single((op&0x400) ? (float) (signed long long) B : (float) B,num);
            flags=flags_in;
            break;
        }
    }
    if (!(op&0x1000)) contx->flags=flags;
    if ((rT>=0)) {
	contx->reg_gen[rT]=res;
	contx->reg_genP[rT]=res_p;
    }
    return false;
}
    
void req::gen_mem(req* prev1,unsigned code,char *mem,char *memp,unsigned long long addr) {
    res=0;
    res_p=0;
    rT=16;
    op=code;
    asmtext[0]='\x00';
#define UC (unsigned long long)
    switch(code) {
        case 8: res_p=(memp[MEMRGN_DATA+addr/64]>>((addr&0x38)>>3))&0x1;
		res|=UC (unsigned char) mem[MEMRGN_DATA+addr+4]<<32;
	        res|=UC (unsigned char) mem[MEMRGN_DATA+addr+5]<<40;        
	        res|=UC (unsigned char) mem[MEMRGN_DATA+addr+6]<<48;        
	        res|=UC (unsigned char) mem[MEMRGN_DATA+addr+7]<<56;        
        case 4: res|=UC (unsigned char) mem[MEMRGN_DATA+addr+2]<<16;
	        res|=UC (unsigned char) mem[MEMRGN_DATA+addr+3]<<24;        
        case 2: res|=UC (unsigned char) mem[MEMRGN_DATA+addr+1]<<8; 
        case 1: res|=UC (unsigned char) mem[MEMRGN_DATA+addr]; break;
    }
#undef UC
}

void req::gen_memw(req* prev1,unsigned code,char *mem,char *memp,unsigned long long addr,unsigned long long Dt,char Dt_p) {
    res=0;
    res_p=0;
    rT=-1;
    asmtext[0]='w';
    asmtext[1]='\x00';
    op=code;
    mem[MEMRGN_DATA+addr+0]=(Dt>>0)&0xffull;
    if (code) mem[MEMRGN_DATA+addr+1]=(Dt>>8)&0xffull;
    if (code>2) mem[MEMRGN_DATA+addr+2]=(Dt>>16)&0xffull;
    if (code>2) mem[MEMRGN_DATA+addr+3]=(Dt>>24)&0xffull;
    if (code>4) {
        mem[MEMRGN_DATA+addr+4]=(Dt>>32)&0xffull;
        mem[MEMRGN_DATA+addr+5]=(Dt>>40)&0xffull;
        mem[MEMRGN_DATA+addr+6]=(Dt>>48)&0xffull;
        mem[MEMRGN_DATA+addr+7]=(Dt>>56)&0xffull;
    }
    memp[(MEMRGN_DATA+addr)/64]=(memp[(MEMRGN_DATA+addr)/64])&(0xff7f>>(7-((MEMRGN_DATA+addr)/8)%8))|
	(Dt_p<<(((MEMRGN_DATA+addr)/8)%8));
}


void req::flg64(__int128 r) {
    flags=((r>>59)&0x20)|((r>>61)&0x4)|(((unsigned long long) r==0)<<1);
}
void req::flgPTR(__int128 r) {
    flags=((r>>39)&0x20)|((r>>41)&0x4)|(((unsigned long long) r==0)<<1);
}
void req::flg32(__int128 r) {
    flags=((r>>27)&0x20)|((r>>29)&0x4)|(((unsigned) r==0)<<1);
}
void req::flgM64(unsigned long long r,bool big) {
    flags=(((r&0xffffffff00000000ull)!=0)<<5) | (((r&0xffffffff80000000ull)!=
    0xffffffff80000000ull && (r&0xffffffff80000000ull)!=0)<<4) | ((((long long )
    r<0 && big)  ||((r&0x80000000ull) && !big))<<2) | (((r==0 && big)||
    ((r&0xffffffffull)==0 && !big))<<1) | (1^(r&0x1)^((r&0x2)>>1)^((r&0x4)>>2)^
    ((r&0x8)>>3)^((r&0x10)>>4)^((r&0x20)>>5)^((r&0x40)>>6)^((r&0x80)>>7));
}
void req::flgM128(unsigned __int128 r, bool big) {
    unsigned __int128 r0=r>>63;
    long long r1=r;
    r0=r0>>1;
    flags=((r0!=0)<<5) | (!((r0==0xffffffffffffffffull && r1<0) | (r0==0 &&
    r1>=0))<<4) | (((r0&0x8000000000000000 && big) || (r1<0 && !big))<<2) |
    (((r==0 && big) || (r1==0 && !big))<<1) | (1^(r&0x1)^((r&0x2)>>1)^
    ((r&0x4)>>2)^((r&0x8)>>3)^((r&0x10)>>4)^((r&0x20)>>5)^((r&0x40)>>6)^
    ((r&0x80)>>7));
}

bool req::testj(int code) {
    switch(code) {
        case 0: return (flags_in&0x2)!=0;
        case 1: return (flags_in&0x2)==0;
        case 2: return (flags_in&0x4)!=0;
        case 3: return (flags_in&0x4)==0;
        case 4: return (flags_in&0x22)==0x20;
        case 5: return (flags_in&0x22)!=20;
        case 6: return (flags_in&0x20)==0x20;
        case 7: return (flags_in&0x20)!=0x20;
        case 8: return !((((flags_in&0x4)!=0)^((flags_in&0x10)!=0))||
        ((flags_in&0x2)!=0));
        case 9: return ((((flags_in&0x4)!=0)^((flags_in&0x10)!=0))||
        (flags_in&0x2)!=0);
        case 10: return !(((flags_in&0x4)!=0)^((flags_in&0x10)!=0));
        case 11: return (((flags_in&0x4)!=0)^((flags_in&0x10)!=0));
        case 12: return (flags_in&0x10)!=0;
        case 13: return (flags_in&0x10)==0;
        case 14: return (flags_in&0x1)!=0;
        case 15: return true;
    }
}



void prog_locate(req *reqs,unsigned char *mem) {
    unsigned long long addr=0;
    unsigned long long ins=0;
    unsigned bits=mem[30]|(mem[31]<<8);
    while (1) {
	int n,sz;
	reqs[ins++].offset=addr;
	for(n=0;n<15;n++) if (bits&(1<<n)) {sz=n; break;}
	addr+=sz*2+2;
	bits>>=sz+1;
	if (!bits) {
	    addr=(addr+31)&0xfffffffe0;
            bits=mem[addr+30]|(mem[addr+31]<<8);
	}
	if (ins>=(10000000-1)) return;
    }
}
void fp_get_ext(long double a, unsigned num[3]) {
    if (a!=0.0) {
        unsigned *p1=(unsigned*) &a;
        unsigned short *p2=(unsigned short *) &a;

        num[0]=p1[0];
        num[1]=p1[1]<<1;
        num[2]=((p1[1]>>31)&0x1)|((p2[4]&0x4000)>>13)|0x4|(((~p2[4])&0x4000)<<4)|
          ((p2[4]&0xbfff)<<4);
    } else {
        num[0]=0;
        num[1]=0;
        num[2]=0x4;
    }
}

void fp_get_double(double a, unsigned num[3]) {
    if (a!=0.0) {
        unsigned long long *p1= (unsigned long long *)&a;
        num[0]=*p1&0xffffffffu;
        num[1]=((*p1&0x7fffffff00000000ull)>>31)^0x80000000ull;
        num[2]=(*p1>>63)|((*p1>>61)&0x2)|0x8;
    } else {
        num[0]=0;
        num[1]=0;
        num[2]=0x8;
    }
}

void fp_get_single(float a1, unsigned num[3]) {
    float a=a1;
    unsigned *p1=(unsigned *) &a;
    if (a!=0.0) {
        num[0]=*p1^0x40000000;
        num[1]=(*p1>>30)&0x1;
        num[2]=0xC;
    } else {
        num[0]=0;
        num[1]=0;
        num[2]=0xC;
    }
}

bool ckran_alu(unsigned long long ptr,unsigned long long &addr) {
    unsigned off=ptr>>58;
    if (ptr&0xfffffe0000000000ull!=addr&0xfffffe0000000000ull)
        return false;
    unsigned long long ptru=(ptr&0x1ffffffffffull)>>(off+9);
    unsigned long long addru=(addr&0x1ffffffffffull)>>(off+9);
    if (ptru==addru) return true;
    if (addru==(ptru+1) && (ptr&0x40000000000) && (ptr&0x20000000000))
    {
        addr^=0x40000000000;
        return true;
    }
    if (addru==(ptru-1) && !(ptr&0x40000000000) && (ptr&0x20000000000))
    {
        addr^=0x40000000000;
        return true;
    }
    return false;
}


void gen_memrgn(char *mem,char *pmem) {
    int n;
    for(n=0;n<(MEMRGN_DATA_SZ/8);n++) {
	unsigned long long *xmem=(unsigned long long *) (mem+8*n+MEMRGN_DATA);
     //   if ((lrand48()%3)==1) {
//	    pmem[n/8+MEMRGN_DATA/64]|=1<<(n&0x7);
//	    *xmem=lrand48()&0xfffffffffff;
//	    *xmem|=0xf80ff00000000000ul;	    
//	} else {
	    pmem[n/8+MEMRGN_DATA/64]&=~(1<<(n&0x7));
	    *xmem=lrand48()&0xfffffffffff;
	    *xmem|=lrand48()<<44;	    
//	}
    }
}


void gen_prog(req *reqs,int count, FILE *f,hcont *contx,char *mem,char *pmem) {
   int n;
   fprintf(f,".text\n");
   fprintf(f,".global _start\n");
   fprintf(f,".comm mem,65536\n");
   fprintf(f,"_start:\n");
   for(n=0;n<31;n++) {
       if (n!=6) reqs[n].gen_init(n,0,lrand48()|(lrand48()<<48),0);
       else reqs[n].gen_init(n,0,0xf80fe00008000000,1);
       fprintf(f,"%s",reqs[n].asmtext);
       contx->reg_gen[n]=reqs[n].res;
       contx->reg_genP[n]=reqs[n].res_p;
   }
   reqs[31].gen_init(31,0,0x8000,0);
   fprintf(f,"%s",reqs[31].asmtext);
   contx->reg_gen[n]=reqs[n].res;
   contx->reg_genP[n]=reqs[n].res_p;
  // reqs[32].gen_movcsr(csr_page,31);
   
   for(n=32;n<(count-2);n++) {
	   int p;
	   if ((p=(lrand48()&1))==1) {
               if (reqs[n+1].gen(false, false, false, NULL,contx,1,mem,pmem)) n++;
	       fprintf(f,"%s",reqs[n].asmtext);
	   } else {
               if (reqs[n+1].gen(false, false, true , NULL,contx,2,mem,pmem)) {
		   n+=2;
	           fprintf(f,"%s",reqs[n-1].asmtext);
	       } else {
	           fprintf(f,"%s",reqs[n].asmtext);
	       }
	   }
   }
   fprintf(f,".p2align 5\n");
   
   
}

req *reqs;

void prog_print(char *name) {
  FILE *f;
  int insn;
  f=fopen(name,"w");
  for(insn=0;insn<1000000; insn++) {
    int n;
    fputc('0'+reqs[insn].res_p+2*(reqs[insn].rT>=0),f);
    for(n=0;n<16;n++) {
      char c=(reqs[insn].res>>(64-4*n))&0xf;
      if (c<10) c=c+'0';
      else c=c+'a';
      fputc(c,f);
    }
    char c=reqs[insn].rT&0xf;
    if (c<10) c=c+'0';
    else c=c+'a';
    fputc(c,f);
    fputc('0'+((reqs[insn].rT&0x10)>>4),f);
    c=reqs[insn].rA&0xf;
    if (c<10) c=c+'0';
    else c=c+'a';
    fputc(c,f);
    fputc('0'+((reqs[insn].rA&0x10)>>4),f);
    c=reqs[insn].rB&0xf;
    if (c<10) c=c+'0';
    else c=c+'a';
    fputc(c,f);
    fputc('0'+((reqs[insn].rT&0x10)>>4),f);
    c=(reqs[insn].flags&0x1f)>>1;
    if (c<10) c=c+'0';
    else c=c+'a';
    fputc(c,f);
    fputc('0'+((reqs[insn].flags&0x20)>>5)+2*(reqs[insn].op>>12,f);
    fputc('\n',f);
    for(n=0;n<8;n++) {
      char c=(reqs[insn].offset>>(32-4*n))&0xf;
      if (c<10) c=c+'0';
      else c=c+'a';
      fputc(c,f);
    }
  }
  fclose(f);
}


int main(int argc, char *argv[]) {
    int initcount=10;
    int cyc=0;
    unsigned long long ip=0;
    FILE *FOUT=fopen("/tmp/asm2.s","w");
    if (!FOUT) exit(1);
    hcont contx;
    memset((void *) &contx,0,sizeof (contx));
    char *mem=(char *) mmap(0,2l*1024*1024*1024,PROT_READ|PROT_WRITE,MAP_ANON|MAP_PRIVATE,-1,0);
    char *memp=(char *) mmap(0,2l*1024*1024*1024/64,PROT_READ|PROT_WRITE,MAP_ANON|MAP_PRIVATE,-1,0);
    char *memw=(char *) mmap(0,2l*1024*1024*1024,PROT_READ|PROT_WRITE,MAP_ANON|MAP_PRIVATE,-1,0);
    char *mempw=(char *) mmap(0,2l*1024*1024*1024/64,PROT_READ|PROT_WRITE,MAP_ANON|MAP_PRIVATE,-1,0);
    if (!mem) {
	perror("mem");
	exit(1);
    }
    //bzero(mem,2l*1024*1024*1024);
    reqs=new req[10000000];
    fesetround(FE_TOWARDZERO);
    top->clk=0;
    top->rst=1;
    gen_memrgn(mem,memp);
    memcpy(memw,mem,2l*1024*1024*1024);
    memcpy(mempw,memp,2l*1024*1024*1024/64);
    gen_prog(reqs,10000000,FOUT,&contx,memw,mempw);
    fclose(FOUT);
    if (argc==2 && !strcmp(argv[1],"-asm")) exit(0);
    char mname[256];
    mname[0]=0;
    snprintf(mname,256,"./hsim.bin");
    int fd=open(mname,O_RDONLY);
    if (fd>=0) {
	struct stat s;
	long long sz;
	fstat(fd,&s);
	sz=s.st_size;
	sz=(sz+4095l)&0xfffffffff000;
	if (sz>(1024l*1024*1024)) {
            printf("map too big!\n");
	    exit(1);
	}
        if (!mmap(mem,sz,PROT_READ|PROT_WRITE,MAP_FIXED|MAP_PRIVATE,fd,0)) {
	    perror("mmap");
	    exit(1);
	}
    } else {
	perror("open() ");
    }
    prog_locate(reqs,(unsigned char *)mem);
    mname[0]=0;
    snprintf(mname,256,"./prog.memh");
    prog_print(mname);
    FILE *f=fopen("./bin.memh","w");
    FILE *f1=fopen("./hsim.bin","r");
    int ende;
    do {
        ende=fread(mname,128,1,f1);
        if (ende) {
            int n;
            char c;
            for(n=0;n<128;n=n+1) {
                c='0'+mname[n]&0xf;
                if (c>'9') c+='a'-'9';
                fputc(c,f);
                c='0'+(mname[n]&0xf0)>>4;
                if (c>'9') c+='a'-'9';
                fputc(c,f);
            }
            fputc('\n',f);
        }
    } while (ende!=0);
    fclose(f1);
    fprintf(f,"@400000\n");
    for(ende=0;ende<(DATARGN_SZ/128);ende=ende+1) {
        int n;
        char c;
        for(n=0;n<128;n=n+1) {
            c='0'+mem[128*ende+n]&0xf;
            if (c>'9') c+='a'-'9';
            fputc(c,f);
            c='0'+(mname[128*ende+n]&0xf0)>>4;
            if (c>'9') c+='a'-'9';
            fputc(c,f);
        }
        fputc('\n',f);
    }
    ende=fclose(f);
    if (ende) printf("flcose error (data)\n");
    f=fopen("./bin_p.memh","w");
    fputc('\n',f);
    ende=fclose(f);
    if (ende) printf("flcose error (ptr)\n");
    return 0;
}
