
class alu_req {
    public:
    unsigned int op;
    unsigned long long A,B,res;
    unsigned A_p,B_p,res_p,excpt;
    unsigned flags,flags_in;
    unsigned fset;
    unsigned alt,mul;
    unsigned en;
    unsigned num[3];
    void gen(bool alt_, bool mul_, bool can_shift);
    void exc();
    void flg64(__int128 r);
    void flg32(__int128 r);
    void flgM64(unsigned long long r, bool big=0);
    void flgM128(unsigned __int128 r, bool big=0);
    bool testj(int code);
};


voud alu_req::exc() {
    if (!alt && !mul) {
        __int128 res0;
        int A0=A,B0=B,res2;
        unsigned A0x=A,B0x=B;
        long long int A1=A,B1=B,res1;
        unsigned __int128 one=0x8000000000000000ull;
        unsigned long long ptr=A_p ? A : B;
	res_p=0;
	bool no_O=false;
        switch(op&0xff) {
            case 0:
            res0=((unsigned __int128)  A)+(unsigned __int128) B;
            if (A_p && B_p) excpt=11;
addie:
	    if (A_p || B_p) {
		res1=res=res0&0xfffffffffff;
		unsigned long low,hi;
		ptr p;
		p.val=ptr;
		if (!p.get_bounds(low,hi)) {
		    exc=11;
		    break;
		}
		if (res1>hi || res1<low) {
		    unsigned exp=p>>59;
		    if (((p.val>>52)&0x7f)<((p.val>>45)&0x7f)) {
			unsigned long masq=(0xfffffffe000<<exp)&0xfffffffffff;
			if ((res1&masq)!=(ptr&masq)) {
			    excpt=11;
			} else {
			    res&=~(1<<44);
			}
		    } else if ((p.val>>44)&1) {
			unsigned long masq=(0xfffffffe000<<exp)&0xfffffffffff;
			unsigned long delta=0x2000<<exp;
			if ((res1&masq)!=(ptr&masq) && (res1&masq)!=((ptr+delta)&masq) ) {
			    excpt=11;
			} else if ((res1&masq)!=(ptr&masq)) {
		            res^=1<<44;
			}
		    } else {
			unsigned long masq=(0xfffffffe000<<exp)&0xfffffffffff;
			unsigned long delta=0x2000<<exp;
			if ((res1&masq)!=(ptr&masq) && (res1&masq)!=((ptr-delta)&masq) ) {
			    excpt=11;
			} else if ((res1&masq)!=(ptr&masq)) {
		            res^=1<<44;
			}
		    }
		}
		res_p=1;
	    } else {
                res1=res=res0;
		res_p=0;
	    }
            flg64(res0);
            if (!no_O) {
		flags|=((A1>0&&B1>0&&res1<0) || (A1<0&&B1<0&&res1>0))<<4;
                flags|=(((A&0xf)+(B&0xf))&0x10)>>1;
	    }
            break;
            
            case 1:
            res0=((unsigned __int128) A0x)+(unsigned __int128) B0x;
            res2=res=res0&0xffffffffull;
            flg32(res0);
            flags|=((A0>0&&B0>0&&res2<0) || (A0<0&&B0<0&&res2>0))<<4;
            flags|=(((A&0xf)+(B&0xf))&0x10)>>1;
            break;

            case 4:
            res0=((unsigned __int128) A)+((unsigned __int128)~B)+(one>>63);
	    if (A_p && !B_p) goto addie; 
            res1=res=res0;
	    if (A_p && B_p) res&=0xfffffffffff;
	    if (~A_p && B_p) excpt=11;
	    res_p=0;
            flg64(res0^(one<<1));
            
            flags|=((A1>=0&&B1<0&&res1<0) || (A1<0&&B1>0&&res1>0))<<4;
            flags|=(((A&0xf)-(B&0xf))&0x10)>>1;
            break;
            
            case 5:
            res0=((unsigned __int128) A0x)+((unsigned __int128) ~B0x)+1;
            res2=res=res0&0xffffffffull;
            flg32(res0^0x100000000ll);
            flags|=((A0>=0&&B0<0&&res2<0) || (A0<0&&B0>0&&res2>0))<<4;
            flags|=(((A&0xf)-(B&0xf))&0x10)>>1;
            break;

            case 8:
            res0=A&B;
	    if (A_p && !B_p) { no_O=true; goto addie; }
            res1=res=res0;
            flg64(res0);
            break;

            case 9:
            res0=A0x&B0x;
            res2=res=res0&0xffffffffull;
            flg32(res);
            break;

            case 12:
            res0=A|B;
	    if (A_p && !B_p) { no_O=true; goto addie; }
            res1=res=res0;
            flg64(res0);
            break;

            case 13:
            res0=A0x|B0x;
            res2=res=res0&0xffffffffull;
            flg32(res);
            break;

            case 16:
            res0=A^B;
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
	    res_p=B_p;
            flags=flags_in;
            break;

            case 33:
            res=B&0xffffffffull;
            flags=flags_in;
            break;

            case 34:
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
            //op|=rand()&0x700;
            res=testj(((op&0x700)>>7)|(op&0x1)) ? B : A;
            res_p=testj(((op&0x700)>>7)|(op&0x1)) ? B_p : A_p;
            flags=flags_in;
            break;
            
            case 50:
            case 51:
            //op|=rand()&0x700;
            res=testj(((op&0x700)>>7)|(op&0x1)) ? B0x : A0x;
            flags=flags_in;
            break;
            
            
            case 52:
            case 53:
            //op|=rand()&0x700;
            res=0;
            flags=testj(((op&0x700)>>7)|(op&0x1)) ? A&0x3f : flags_in;
            break;

            case 54:
            case 55:
            //op|=rand()&0x700;
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
        resSx= (signed long) As * (signed long) Bs;
        res0x=(unsigned long) Au * (unsigned long) Bu;
        res0=A0*B0;
        resS=AS*BS;
	res_p=false;
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
            fp_get_ext((op&0x400) ? (long double) (signed long) B : 
              (long double) B,num);
            flags=flags_in;
            break;
            
            case 13:
            fp_get_double((op&0x400) ? (double) (signed long) B : 
              (double) B,num);
            flags=flags_in;
            break;

            case 14:
            fp_get_single((op&0x400) ? (float) (signed long) B : (float) B,num);
            flags=flags_in;
            break;
        }
    }
}
