
.global parse_assign
.type parse_assign, @function
.p2align 5
parse_assign:
movzbl (%r9),%r8d
call is_alpha
testl %eax,%eax
je parse_error
movq $chrbuftkn,%rsi
xorl %eax,%eax
movq %eax,(%rsi)
.p2align 5
loop_tkn:
  movb %r8,(%rsi)
  addq $1, %rsi
  movzbl (%r9),%r8d
  addq $1,%r9
  call is_alpha_num
  testl %eax,%eax
  jne loop_tkn
call skip_spc
movq chrbuftkn(%rip),%r8
call find_kword
testq %rax,%rax
jne process_kword
call find_var_new
movq %rsi,assign_var(%rip)
movzbl (%r9),%edx
cmpl $'=',%edx
jne parse_error
addq $1,%r9
call skip_spc
movq $0,%r10
.p2align 5
parse_node:
xorl %eax,%eax
movl %eax,acc_minus(,%r10)
.p2align 5
loop_minus:
  movzbl (%r9),%r8d
  cmpl '-',%r8d
  jne no_minus
  movl $1,%eax
  xorl acc_minus(%rip,%r10),%eax
  movl %eax,acc_minus(,%r10)
  addq $1,%r9
  call skip_spc
  jmp loop_minus
.p2align 5
no_minus:
  cmpl '(',%r8d
  jne no_o_brack
  addl $1,%r10d
  cmpl $15,%r10d
  jg parse_error
  addq $1,%r9
  movzbl (%r9),%r8d
  jmp parse_node
.p2align 5
no_o_brack:

call is_alpha
testl %eax,%eax
je parse_number
movq $chrbuftkn,%rsi
xorl %eax,%eax
movq %eax,(%rsi)
.p2align 5
loop_tkn_node:
  movb %r8d,(%rsi)
  addq $1, %rsi
  movzbl (%r9),%r8d
  addq $1,%r9
  call is_alpha_num
  testl %eax,%eax
  jne loop_tkn
call skip_spc
movq chrbuftkn(%rip),%r8
call find_var
testl %eax,%eax
je parse_error
movq 8(%rsi),%rdx
movq %rdx,acc_val(,%r10,8)
.p2align 5
parse_operator:

.p2align 5
parse_number:


