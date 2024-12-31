#include <vector>

#define driven_phase_mask 0xff
#define driven_off_mask 0xffff0000
#define driven_off_shift 16
#define driven_count_mask 0xff00
#define driven_count_shift 8
#define pclk_1 0x1
#define pclk_2 0x2
#define pclk_3 0x4
#define pclk_12 0x8
#define pclk_13 0x10
#define pclk_23 0x20
#define pclk_ppower 0xff
/* Please note that the library suggest N-only dynamic, but a P-only dynamic 
  would have identical circuit which is more optimal. */
int global_anchor_x;
int global_anchor_y;
int global_bus_X_off;
int global_bus_Y_off;
int acds_global_ID_counter=0;

class __acds_cell {
  int phase;
  int size;
  short anchor_x;
  short anchor_y;
  short x_off;
  short y_off;
  short x_mod;
  short y_mod;
  unsigned int ID;
  void *Owner;
  std::vector<void *> driven_obj;
  std::vector<long> driven_off_pos;
  unsigned short precharge_mask;
  unsigned short outp;
  unsigned short INP;
  unsigned char io[2][16];
  public:
  void eval();
  void antiphase();
  void drive();
  void printcell(file * f);
};

  void __acds_cell::printcell(file *f) {
      fprintf(f,"BEGIN %u\n",ID);
      fprintf(f,"  INP %i\n",INP);
      fprintf(f,"  OUTP %i\n",outp);
      fprintf(f,"  X %i\n",anchor_x);
      fprintf(f,"END %u\n",ID);
  }
  void __acds_cell::eval() {
      long n,n2;
      for(n=size;n<(size*16);n++) {
          if ((n&15)<12) {
            io[1][n]=io[1][n] | io[1][n-size] & io[0][n-size];
            io[1][n-size]=io[1][n-size] | io[1][n] & io[0][n];
          } else {
            io[1][n]=io[1][n] & (io[1][n-size]|io[0][n-size]);
            io[1][n-size]=io[1][n-size] & (io[1][n]|io[0][n]);
          }
      }
      for(n=0;n<size;n++) if (((n/size)&15)<12 && (precharge_mask>>((n/size)&15))&1) {
        io[1][n&0xfffffff0|12]|=io[1][n];
        io[1][n&0xfffffff0|13]|=io[1][n];
      }
  }
  void __acds_cell::antiphase() {
      long n,n2;
     for(n=size;n<(size*16);n++) {
          if ((n&15)<12) {
            io[1][n]=io[1][n] | io[1][n-size] & io[0][n-size];
            io[1][n-size]=io[1][n-size] | io[1][n] & io[0][n];
          } else {
            io[1][n]=io[1][n] & (io[1][n-size]|io[0][n-size]);
            io[1][n-size]=io[1][n-size] & (io[1][n]|io[0][n]);
          }
      }
      for(n=0;n<size;n++) if (((n/size)&15)<12 && (precharge_mask>>((n/size)&15))&1) {
        io[1][n]&=io[1][n&0xfffffff0|12];
      } 
  }
  void __acds_cell::drive() {
    std::vector<void *>::iterator obj;
    std::vector<long>::iterator field;
    for(obj=driven_obj.begin(),field=driven_off_pos.begin(); 
      obj!=driven_obj.end() && field!=driven_off_pos.end();obj++,field++) {
      long n,pos,cnt,off,othersz;
      pos=(*field&driven_phase_mask);      
      off=(*field&driven_off_mask)>>driven_off_shift;
      cnt=(*field&driven_count_mask)>>driven_count_shift;
      othersz=((__acds_cell *)*obj)->size;
      if (pos<12) for(n=0;n<cnt;n=n+1) {
        ((__acds_cell *) *obj)->io[0][n*16+pos]|=(
          (io[1][n*16+outp+off]|(io[1][n*16+outp+off]<<3)|(io[1][n*16+outp+off]<<4)|
            ((io[1][n*16+outp+off]&0x4)<<1))|(io[1][n*16+outp+off]>>3)|(io[1][n*16+outp+off]>>4))&((__acds_cell *) *obj)->io[1][n*16+12];
      }
      if (pos>=12) for(n=0;n<cnt;n=n+1) {
        ((__acds_cell *) *obj)->io[0][n*16+pos]&=
          (io[1][n*16+outp+off]|(io[1][n*16+outp+off]<<3)|(io[1][n*16+outp+off]<<4)|
            (((io[1][n*16+outp+off]&0x4)<<1))|(io[1][n*16+outp+off]>>3)|(io[1][n*16+outp+off]>>4));
      }
    }
  }
template <long _size,long _precharge_mask,long _outp,long _INP> class acds_cell {
  int phase;
  int size;
  short anchor_x;
  short anchor_y;
  short x_off;
  short y_off;
  short x_mod;
  short y_mod;
  unsigned int ID;
  void *Owner;
  std::vector<void *> driven_obj;
  std::vector<long> driven_off_pos;
  unsigned short precharge_mask;
  unsigned short outp;
  unsigned short INP;
  unsigned char io[2][16][_size];
  public:
  acds_cell<_size,_precharge_mask,_outp,_INP> () {
      anchor_x=global_anchor_x;
      anchor_y=global_anchor_y;
      x_off=global_bus_X_off;
      y_off=global_bus_Y_off;
      x_mod=16000;
      y_mod=16000;
      long n;
      size=_size;
      precharge_mask=_precharge_mask;
      outp=_outp;
      INP=_INP;
      for(n=0;n<(size*16);n=n+1) {
          if ((1<<((n/size)&15))&INP) io[1][n%16][n/16]=0xff;
      }
      ID=acds_global_ID_counter++;
  }
  acds_cell<_size,_precharge_mask,_outp,_INP> (int x,int y) {
      anchor_x=global_anchor_x+x;
      anchor_y=global_anchor_y+y;
      x_off=global_bus_X_off;
      y_off=global_bus_Y_off;
      x_mod=16000;
      y_mod=16000;
      size=_size;
      precharge_mask=_precharge_mask;
      outp=_outp;
      INP=_INP;
      long n;
      for(n=0;n<(size*16);n=n+1) {
          if ((1<<((n/size)&15))&INP) io[1][n%16][n/16]=0xff;
      }
      ID=acds_global_ID_counter++;
  }
  int acds_cell::add_input(void * from, int off, int pos, int count) {
    __acds_cell *f=(__acds_cell *) from;
    if (off>f->size && off>0 || off<size && off<0) return 0;//error
    f->driven_obj[f->driven_obj.size()]=((void *)this);
    f->driven_off_pos[f->driven_off_pos.size()]=(pos)|
       ((off<<driven_off_shift)&driven_off_mask)|
       ((count<<driven_count_shift)&driven_count_mask);
    int cntmax= off>0 ? f->size-off : size+off;
    if (cntmax<count) return 0;
    return count;
  }
  void eval() {
      __acds_cell *f=(__acds_cell *) this;
      f->eval();
      f->drive();
  }
};
