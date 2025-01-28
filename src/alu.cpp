#include <cstdlib>
#include <cfenv>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "../rtl_test/inc/ptr.h"
#include "contx.h"
#include "../rtl_test/inc/struct.h"
#include "../rtl_test/inc/cjump.h"
#include "../rtl_test/inc/extract.h"

#define get64(a) ((((unsigned long long) a[1])<<32)|(unsigned long long) a[0])
#define set64i(a,b,c) a[0]=b;a[1]=b>>32;a[2]=c;


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
    bool exec(req *prev1,hcont *contx,char *mem,char *pmem);
    void gen_mem(req* prev1,unsigned code,char * mem,char *memp,unsigned long long addr);
    void gen_memw(req* prev1,unsigned code,char * mem,char *memp,unsigned long long addr,unsigned long long res, char res_p);
    void flgPTR(__int128 r);
    void flg64(__int128 r);
    void flg32(__int128 r);
    void flgM64(unsigned long long r, bool big=0);
    void flgM128(unsigned __int128 r, bool big=0);
    bool testj(int code);
};
    
bool req::exec(req *prev1,hcont *contx,char *mem,char *memp) {
    res_p=0;
    res=0;
    A=contx->reg_gen[rA&0x1f];
    A_p=contx->reg_genP[rA&0x1f];
    B=contx->reg_gen[rB&0x1f];
    B_p=contx->reg_genP[rB&0x1f];
    flags_in=contx->flags;
    if (has_mem==1) {
        gen_mem(NULL,op,mem,memp,addr);
        contx->reg_gen[rT&0x1f]=res;
        contx->reg_genP[rT&0x1f]=res_p;
	return false;
    } else if (has_mem==2) {
        res=contx->reg_gen[rA&0x1f];
        res_p=contx->reg_genP[rA&0x1f];
        gen_memw(NULL,op,mem,memp,addr,res,res_p);
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
            if (!(A_p && B_p)) flg64(res0^(one<<1));
	    else flgPTR(res0^(one>>19));
            B1=B;

            if (!(A_p && B_p)) flags|=((A1>=0&&B1<0&&res1<0) || (A1<0&&B1>0&&res1>0))<<4;
            if ((A_p && B_p)) flags|=((!(A1&0x80000000000)&&(B1&0x80000000000)&&(res1&0x80000000000)) || 
		((A1&0x80000000000)&&!(B1&0x80000000000)&&!(res1&0x80000000000)))<<4;
            flags|=(((A&0xf)-(B&0xf))&0x10)>>1;
            break;
            
            case 5:

            res0=((unsigned __int128) A0x)+((unsigned __int128) ~B0x)+1;
            res2=res=res0&0xffffffffull;
            flg32(res0^0x100000000ll);
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
    flags=((r>>59)&0x20)|((r>>61)&0x4)|(((unsigned long long) r==0)<<1)|
      (1^(r&0x1)^((r&0x2)>>1)^((r&0x4)>>2)^((r&0x8)>>3)^((r&0x10)>>4)^
      ((r&0x20)>>5)^((r&0x40)>>6)^((r&0x80)>>7));
}
void req::flgPTR(__int128 r) {
    flags=((r>>39)&0x20)|((r>>41)&0x4)|(((unsigned long long) r==0)<<1)|
      (1^(r&0x1)^((r&0x2)>>1)^((r&0x4)>>2)^((r&0x8)>>3)^((r&0x10)>>4)^
      ((r&0x20)>>5)^((r&0x40)>>6)^((r&0x80)>>7));
}
void req::flg32(__int128 r) {
    flags=((r>>27)&0x20)|((r>>29)&0x4)|(((unsigned) r==0)<<1)|
      (1^(r&0x1)^((r&0x2)>>1)^((r&0x4)>>2)^((r&0x8)>>3)^((r&0x10)>>4)^
      ((r&0x20)>>5)^((r&0x40)>>6)^((r&0x80)>>7));
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
        case 4: return (flags_in&0x22)==0;
        case 5: return (flags_in&0x22)!=0;
        case 6: return (flags_in&0x20)==0;
        case 7: return (flags_in&0x20)!=0;
        case 8: return !((((flags_in&0x4)!=0)^((flags_in&0x10)!=0))||
        ((flags_in&0x2)!=0));
        case 9: return ((((flags_in&0x4)!=0)^((flags_in&0x10)!=0))||
        (flags_in&0x2)!=0);
        case 10: return !(((flags_in&0x4)!=0)^((flags_in&0x10)!=0));
        case 11: return (((flags_in&0x4)!=0)^((flags_in&0x10)!=0));
        case 12: return (flags_in&0x10)!=0;
        case 13: return (flags_in&0x10)==0;
        case 14: return (flags_in&0x1)!=0;
        case 15: return (flags_in&0x1)==0;
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





req *reqs;

int main(int argc, char *argv[]) {
    Verilated::commandArgs(argc, argv);
    Vheptane_core *top=new Vheptane_core();
    Verilated::assertOn(false);
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
    snprintf(mname,256,"%s/.hsim/hsim.bin",getenv("HOME"));
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
    req_set(top,reqs,mem,memp);
    top->eval();
    top->clk=1;
    top->eval();
    top->clk=0;
    top->eval();
    top->eval();
    top->rst=0;
    while(!Verilated::gotFinish()) {
        int k,j;
        top->clk=1;
        top->eval();
	//usleep(5000);
        top->clk=0;
        top->eval();
	//usleep(5000);
        if (top->heptane_core__DOT__front_mod__DOT__cc_mod__DOT__cc_mod__DOT__wayMod_gen__BRA__7__KET____DOT__way_mod__DOT__tag_mod__DOT__init_reg2) printf("dinit7 0x%x\n",top->heptane_core__DOT__front_mod__DOT__cc_mod__DOT__cc_mod__DOT__wayMod_gen__BRA__7__KET____DOT__way_mod__DOT__tag_mod__DOT__write_NRU);
        top->rbusOut_can=1;
        if (!initcount) {
            req_set(top,reqs,mem,memp);
            cyc=cyc+1;
            if (!get_check(top,reqs,ip)) {
                printf("error @%i\n",cyc);
                sleep(1);
		return 1;
            }
            if ((cyc%100)==0) {
                printf("cycle %i\n",cyc);
            }
           
        } else {
            initcount=initcount-1;
            if (!initcount) Verilated::assertOn(true);
        }
    }
}
