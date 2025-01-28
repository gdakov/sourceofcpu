

class ptr {
	public:
    unsigned long long val;
    bool get_bounds(unsigned long long &low,unsigned long long &hi,bool no_O,ptr ptr2) {
	unsigned exp=val>>59;
	bool eqn=((val>>52)&0x7f)<((val>>45)&0x7f);
        unsigned long long masque=eqn ? 0xfffffffffff : 0x1fffffffffff;	
        unsigned long long masqueL=eqn ? 0xfffffffe000 : 0xfffffffe000;	
	unsigned long long valL=(((val>>44)&1) || eqn) ? val&0xfffffffffff : ((val&0xfffffffffff)-(1ul<<(exp+13))) & masqueL;
	unsigned long long valH=(!((val>>44)&1) || eqn) ? val&0xfffffffffff : ((val&0xfffffffffff)+(1ul<<(exp+13))) & masque;
	if (valL>(val&0xfffffffffff) ) valL=0;
	low=(((val>>52)&0x7f)<<(exp+6))|((0xffffffff000<<exp)&
	masqueL&valL);
	hi=(((val>>45)&0x7f)<<(exp+6))|((0x1fffffffe000<<exp)&
	masque&valH)|((64ul<<exp)-1);
	unsigned long long lowA=(0x0ul<<(exp+6))|((0xfffffffe000<<exp)&
	masqueL&valL);
	unsigned long long hiA=(0x0ul<<(exp+6))|((0xfffffffe000<<exp)&
	masque&valH);
	if (no_O) {
	    lowA=((0xfffffffffc0<<exp)&
	    (0xfffffffffc0));
	    return (ptr2.val&lowA)==lowA;
	}
	return (ptr2.val&(0xfffffffe000<<exp))==hiA && (ptr2.val&(0xfffffffe000<<exp))==lowA;
    }
    bool get_bounds2(int no_O,ptr ptr2,unsigned long long b,bool &flip) {
	unsigned exp=val>>59;
	bool eqn=((val>>52)&0x7f)<=((val>>45)&0x7f);
	unsigned long long bnd1=(val&0xfffffffffff) & (0xfffffffe000ul<<exp);
	unsigned long long bnd2=bnd1;
	if (!eqn) {
            if ((val>>44)&1) bnd2+=1ul<<(exp+13);
	    else bnd2-=1ul<<(exp+13);
	    bnd2&=0xfffffffffff;
	}
	flip=0;
	if (no_O==1) {
	    unsigned long long bnd=((0xfffffffffc0ul<<exp)&
	    (0xfffffffffc0));
	    return (b&bnd)==0;
	}
	if (no_O==2) {
	    unsigned long long bnd=((0xfffffffffc0ul<<exp)&
	    (0xfffffffffc0));
	    return (b&bnd)==bnd;
	}
	if (eqn && !((val>>44)&1)) return false;
	if ((ptr2.val&0xfffffffffff&(0xfffffffe000ul<<exp))!=bnd1) flip=1;
	return (ptr2.val&0xfffffffffff&(0xfffffffe000ul<<exp))==bnd1 || (ptr2.val&0xfffffffffff&(0xfffffffe000ul<<exp))==bnd2;
    }
    void set_bounds(unsigned long long low,unsigned long long hi) {
        unsigned long long exp=31;
	while (1) {
	    unsigned long long mask;
       	    mask=(0xfffffffe000<<exp)&0xfffffffffff;
            if ((low&mask)==(val&mask)&&(hi&mask)==(val&mask)) {
	        val=(val&0xfffffffffff)|(((hi>>(exp+6))&0x7f)<<45)|
                (((low>>(exp+6))&0x7f)<<52)|(1ul<<44);
	    } else if ((low&mask)==(val&mask)) {
	        val=(val&0xfffffffffff)|(((((hi>>(exp+6))+1)&0x7f))<<45)|
                (((low>>(exp+6))&0x7f)<<52)|(1ul<<44);
	    } else if ((hi&mask)==(val&mask)) {
	        val=(val&0xfffffffffff)|(((hi>>(exp+6))&0x7f)<<45)|
                ((((low>>(exp+6))-1)&0x7f)<<52)|(0ul<<44);
	    } else {
	        break;
	    }
	    exp--;
	}
	val|=exp<<59;
    }
};
