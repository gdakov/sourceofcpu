
struct __PTRHDR {
  void *ptr_block;
  unsigned long block_offset;
  unsigned long alloc_size;
  unsigned long permissions_and_cookie;
};

const long __PTRHDR_CAN_FREE=0x1;
const long __PTRHDR_IS_MEMORY_MAP=0x2;
const long __PTRHDR_CAN_STORE_IN_HEAP=0x4;
const long __PTRHDR_CAN_STORE_IN_OBJECT=0x8;
const long __PTRHDR_6_CHUNKS 0x400;
const long __PTRHDR_COOKIE_OF_BOUNDS 0xfffff00000000000ul;
const long __PTRHDR_COOKIE_MASK_TO_BE_SHIFTED_BY_EXP 0xffffffff800

const static char *__UNBOUND_PTR;


inline void * check_if_can_free(void *ptr, int mark_as_unfree=0) {
  unsigned long volatile addr;
  struct __PTRHDR *p1;
  addr=(unsigned long) ptr;
  addr=addr>>1;
  addr=addr<<1;
  if (((addr>>45)&0x1f)<3)) {
      unsigned long mask2=0x70<<(addr>>45)&0x1f);
      addr=addr&~mask2;
  }
  p1=(struct __PTRHDR *) (__UNBOUND_PTR+(addr&0xffffffffffff));
  if (!(p1->permissions_and_cookie&__PTRHDR_CAN_FREE)) {
      return 0;
  }
  if ((p1->permissions_and_cookie&__PTRHDR_COOKIIE_OF_BOUNDS)!=(addr&__PTRHDR_COOKIE_OF_BOUNDS)) {
      return 0;
  }
  unsigned long mask=(__PTRHDR_COOKIE_MASK_TO_BE_SHIFTED_BY_EXP<<((addr>>45)&0x1f))&__PTRHDR_COOKIE_MASK_TO_BE_SHIFTED_BY_EXP;
  if ((p1->permissions_and_cookie&mask)!=(addr&mask)) {
      return 0;
  }
  if (mark_as_unfree) {
      if ((p1->permissions_and_cookie&__PTRHDR_6_CHUNKS) {
          unsigned long off2=(addr>>45)&0x1f)+4;
          unsigned long off3=(addr>>off2)&0x7;
          p1->permissions_and_cookie&=~(16ul<<off3);
      } else {
          p1->permissions_and_cookie&=~__PTRHDR_CAN_FREE;
      }
  }
  return p1;
}