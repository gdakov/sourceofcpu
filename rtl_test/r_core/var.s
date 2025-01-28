
.global find_var
.p2align 5
find_var:
lea varlist(%rip),%rsi
loop_find:
  movq (%rsi),%rdx
  cmpq %r8,%rdx
  jeq loop_found
  testq %rdx,%rdx
  addq $16,%rsi
  jne loop_find
subq $16,%rsi
movq $0,%rax
retq
loop_found:
movq $1,%rax
retq  


.global init_var
.p2align 5
init_var:
movq $0,%rax
movq %rax,varlist(%rip)
retq


.global find_var_new
.p2align 5
find_var_new:
lea varlist(%rip),%rsi
loop_find1:
  movq (%rsi),%rdx
  cmpq %r8,%rdx
  jeq loop_found
  testq %rdx,%rdx
  addq $16,%rsi
  jne loop_find
subq $16,%rsi
movq %r8,%rsi
movq $1,%rax
retq
loop_found:
movq $1,%rax
retq  

.global find_kword
.p2align 5
find_kword:
lea kwordlist(%rip),%rsi
loop_find2:
  movq (%rsi),%rdx
  cmpq %r8,%rdx
  jeq loop_found
  testq %rdx,%rdx
  addq $16,%rsi
  jne loop_find
subq $16,%rsi
movq $0,%rax
retq
loop_found:
movq $8(%rsi),%rax
retq  

.data
.global kwordlist
.p2align 5
kwordlist:
.byte 0 0 0 0 0 0 0 0
.quad 0
.global varlist
.comm varlist,0x100000,8

