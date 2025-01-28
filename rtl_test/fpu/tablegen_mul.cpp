#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double zrand() {
  return pow(10.0,((double)rand()/RAND_MAX*100.0-50.0))*
    ((double)rand()/RAND_MAX*20.0-10.0);
}
int main() {
  union { double d;long long int a; } a,b,c;
  int i,j,sub;
  for(j=0;j<16386;j++) {
      for(i=0;i<256;i++) {
        a.d=(double) rand()/RAND_MAX*200.0-100.0;
        b.d=(double) rand()/RAND_MAX*200.0-100.0;
        sub=rand()&0x1;
        c.d=a.d*b.d;
        printf("%1x%8llx%8llx%8llx\n",sub,c.a,b.a,a.a);
      }  
      for(i=0;i<256;i++) {
        a.d=(double) rand()/RAND_MAX*2.0-1.0;
        b.d=(double) rand()/RAND_MAX*2.0-1.0;
        sub=rand()&0x1;
        c.d=a.d*b.d;
        printf("%1x%8llx%8llx%8llx\n",sub,c.a,b.a,a.a);
      }  
      for(i=0;i<512;i++) {
        a.d=zrand();
        b.d=zrand();
        sub=rand()&0x1;
        c.d=a.d*b.d;
        printf("%1x%8llx%8llx%8llx\n",sub,c.a,b.a,a.a);
      }  
  }    
}
