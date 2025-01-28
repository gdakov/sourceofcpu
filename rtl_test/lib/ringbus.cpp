#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>   

class ringbus {
    char *mem;
    char *str;
    ringbus();
    void adjust();
    void print();
};

ringbus::ringbus() {
    int fd=open("./rbus",O_RDWR);
    lseek(fd,2*getpagesize()-1,SEEK_SET);
    write(fd,"",1);
    mem=mmap(0,2*getpagesize(),PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
    if (mmap(0,getpagesize(),PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_FIXED,fd,
	getpagesize())) !=(mem+getpagesize()) { perror("ringbus: mmap\n");
        exit(1); }
    bzero(mem,getpagesize());
    str=mem;
}

void ringbus::adjust() {
    int n=strlen(str);
    str+=n;
    if ((str-mem)>=getpagesize()) str-=getpagesize();
}
