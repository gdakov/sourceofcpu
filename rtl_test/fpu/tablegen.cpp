#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double zrand() {
  return pow(10.0,((double)rand()/RAND_MAX*40.0-20.0))*
    ((double)rand()/RAND_MAX*20.0-10.0);
}
long double zlrand() {
  return pow(10.0,((long double)rand()/RAND_MAX*40.0-20.0))*
    ((long double)rand()/RAND_MAX*20.0-10.0);
}

void prn_double() {
  union { double d;long long int a; } a,b,c;
  int i,j,sub;
  for(j=0;j<16386;j++) {
      for(i=0;i<256;i++) {
        a.d=(double) rand()/RAND_MAX*200.0-100.0;
        b.d=(double) rand()/RAND_MAX*200.0-100.0;
        sub=rand()&0x1;
        c.d=sub ? a.d-b.d : a.d+b.d;
        printf("%1x%16llx%16llx%16llx\n",sub,c.a,b.a,a.a);
      }  
      for(i=0;i<256;i++) {
        a.d=(double) rand()/RAND_MAX*2.0-1.0;
        b.d=(double) rand()/RAND_MAX*2.0-1.0;
        sub=rand()&0x1;
        c.d=sub ? a.d-b.d : a.d+b.d;
        printf("%1x%16llx%16llx%16llx\n",sub,c.a,b.a,a.a);
      }  
      for(i=0;i<256;i++) {
        a.d=zrand();
        b.d=zrand();
        sub=rand()&0x1;
        c.d=sub ? a.d-b.d : a.d+b.d;
        printf("%1x%16llx%16llx%16llx\n",sub,c.a,b.a,a.a);
      }  
      for(i=0;i<256;i++) {
        a.d=zrand();
        b.d=zrand();
        b.a|=0x000fffffffffffffll;
        sub=rand()&0x1;
        c.d=sub ? a.d-b.d : a.d+b.d;
        printf("%1x%16llx%16llx%16llx\n",sub,c.a,b.a,a.a);
      }  
  }    
}

void prn_ext() {
  union { long double d; struct {long long a;unsigned short b;} ex; } a,b,c;
  int i,j,sub;
  for(j=0;j<16386;j++) {
      for(i=0;i<256;i++) {
        a.d=(long double) rand()/RAND_MAX*200.0-100.0;
        b.d=(long double) rand()/RAND_MAX*200.0-100.0;
        sub=rand()&0x1;
        c.d=sub ? a.d-b.d : a.d+b.d;
        printf("%1x%4x%16llx%4x%16llx%4x%16llx\n",sub,
          c.ex.b,c.ex.a,b.ex.b,b.ex.a,a.ex.b,a.ex.a);
      }  
      for(i=0;i<256;i++) {
        a.d=(long double) rand()/RAND_MAX*2.0-1.0;
        b.d=(long double) rand()/RAND_MAX*2.0-1.0;
        sub=rand()&0x1;
        c.d=sub ? a.d-b.d : a.d+b.d;
        printf("%1x%4x%16llx%4x%16llx%4x%16llx\n",sub,
          c.ex.b,c.ex.a,b.ex.b,b.ex.a,a.ex.b,a.ex.a);
      }  
      for(i=0;i<256;i++) {
        a.d=zlrand();
        b.d=zlrand();
        sub=rand()&0x1;
        c.d=sub ? a.d-b.d : a.d+b.d;
        printf("%1x%4x%16llx%4x%16llx%4x%16llx\n",sub,
          c.ex.b,c.ex.a,b.ex.b,b.ex.a,a.ex.b,a.ex.a);
      }  
      for(i=0;i<256;i++) {
        a.d=zlrand();
        b.d=zlrand();
        b.ex.a=0xffffffffffffffffll;
        sub=rand()&0x1;
        c.d=sub ? a.d-b.d : a.d+b.d;
        printf("%1x%4x%16llx%4x%16llx%4x%16llx\n",sub,
          c.ex.b,c.ex.a,b.ex.b,b.ex.a,a.ex.b,a.ex.a);
      }  
  }    
}

int main(int argc,char *argv[]) {
  union { double d;long long int a; struct {long long a;long b;} ex; } a,b,c;
  if (argc==1) prn_double();
  else {
    if (argv[1][0]=='e') prn_ext();
    else fprintf(stderr,"Invalid argment.\n");
  }
}
