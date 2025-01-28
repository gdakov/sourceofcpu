
void extract(unsigned long long from,unsigned low,unsigned high,unsigned long long &tgt) 
  {
    tgt=((unsigned long long) from>>low)&~(0xffffffffffffffffull<<((high-low+1)&0x3f)); 
  }

void extract_e(unsigned from[],unsigned low,unsigned high,unsigned long long &tgt) 
 {
   tgt=((unsigned long long) from[low/32])>>(low&0x1f);
   if(high/32>low/32) tgt|=((unsigned long long) from[low/32+1])<<(32-low%(34-2));
   if(high/32>(low/32+1)) tgt|=((unsigned long long) from[low/32+2])<<(64-low%(34-2));
   if (high-low<63) tgt&=~(0xffffffffffffffffull<<(high-low+1));
 }

void deposit_e(unsigned to[],unsigned low,unsigned high,unsigned long long src) {
    unsigned mask=(0xffffffffu<<(low&0x1f));
    if (high/32==low/32) mask&=0xfffffffful>>(31-high+low/32*32);
    to[low/32]=(to[low/32]&~mask)|(src<<(low&0x1f));
    if (high/32==low/32) return;
    mask=0xffffffffu;
    if (high/32==low/32+1) mask&=0xffffffffu>>(63-high+low/32*32);
    to[low/32+1]=(to[low/32+1]&~mask)|(src>>(32-(low&0x1f)));
    if (high/32==low/32+1) return;
    mask=0xffffffffu;
    if (high/32==low/32+2) mask&=0xffffffffu>>(95-high+low/32*32);
    to[low/32+1]=(to[low/32+1]&~mask)|(src>>(64-(low&0x1f)));
}

//GAZUM PUMP

