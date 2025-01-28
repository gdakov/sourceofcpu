	.file	"acds.cpp"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"BEGIN %u\n"
.LC1:
	.string	"  INP %i\n"
.LC2:
	.string	"  OUTP %i\n"
.LC3:
	.string	"  X %i\n"
.LC4:
	.string	"  Y %i\n"
.LC5:
	.string	"  X_off %i\n"
.LC6:
	.string	"  Y_off %i\n"
.LC7:
	.string	"  SROUTE ON\n"
.LC8:
	.string	"  CONN FROM %u, 12 "
.LC9:
	.string	"TO %u, %u:%u:%u "
.LC10:
	.string	"END %u\n"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC11:
	.string	"  CONN FROM %u TO %u,%u:%u:%u\n"
	.text
	.align 2
	.p2align 4
	.globl	_ZN11__acds_cell9printcellEP8_IO_FILE
	.type	_ZN11__acds_cell9printcellEP8_IO_FILE, @function
_ZN11__acds_cell9printcellEP8_IO_FILE:
.LFB895:
	.cfi_startproc
	endbr64
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	leaq	.LC0(%rip), %rdx
	xorl	%eax, %eax
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	movl	$1, %esi
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movl	16(%rdi), %ecx
	movq	%rdi, %rbx
	movq	%r13, %rdi
	call	__fprintf_chk@PLT
	movzwl	84(%rbx), %ecx
	movl	$1, %esi
	xorl	%eax, %eax
	leaq	.LC1(%rip), %rdx
	movq	%r13, %rdi
	call	__fprintf_chk@PLT
	movzwl	82(%rbx), %ecx
	movl	$1, %esi
	xorl	%eax, %eax
	leaq	.LC2(%rip), %rdx
	movq	%r13, %rdi
	call	__fprintf_chk@PLT
	movswl	8(%rbx), %ecx
	movl	$1, %esi
	xorl	%eax, %eax
	leaq	.LC3(%rip), %rdx
	movq	%r13, %rdi
	call	__fprintf_chk@PLT
	movswl	10(%rbx), %ecx
	movl	$1, %esi
	xorl	%eax, %eax
	leaq	.LC4(%rip), %rdx
	movq	%r13, %rdi
	call	__fprintf_chk@PLT
	movswl	12(%rbx), %ecx
	movl	$1, %esi
	xorl	%eax, %eax
	leaq	.LC5(%rip), %rdx
	movq	%r13, %rdi
	call	__fprintf_chk@PLT
	movswl	14(%rbx), %ecx
	xorl	%eax, %eax
	movl	$1, %esi
	leaq	.LC6(%rip), %rdx
	movq	%r13, %rdi
	call	__fprintf_chk@PLT
	testb	$1, 20(%rbx)
	jne	.L69
	movzwl	80(%rbx), %edx
	xorl	%eax, %eax
	testw	%dx, %dx
	jne	.L70
.L3:
	testb	$4, %al
	jne	.L71
.L5:
	testb	$8, %al
	jne	.L72
.L6:
	testb	$16, %al
	jne	.L73
.L7:
	testb	$32, %al
	jne	.L74
.L8:
	testb	$64, %al
	jne	.L75
.L9:
	testb	$-128, %al
	jne	.L76
.L10:
	testb	$1, %ah
	jne	.L77
.L11:
	testb	$2, %ah
	jne	.L78
.L12:
	testb	$4, %ah
	jne	.L79
.L13:
	testb	$8, %ah
	jne	.L80
.L14:
	testw	%dx, %dx
	jne	.L81
.L15:
	movq	56(%rbx), %r12
	movq	32(%rbx), %rbp
	leaq	.LC11(%rip), %r14
	cmpq	40(%rbx), %rbp
	jne	.L18
	jmp	.L67
	.p2align 4,,10
	.p2align 3
.L82:
	movq	(%r12), %rax
	movq	0(%rbp), %rdx
	movl	$1, %esi
	movq	%r13, %rdi
	addq	$8, %r12
	addq	$8, %rbp
	movl	16(%rdx), %r8d
	movzbl	%ah, %edx
	movzbl	%al, %r9d
	pushq	%rdx
	.cfi_def_cfa_offset 56
	movl	%eax, %edx
	xorl	%eax, %eax
	shrl	$16, %edx
	pushq	%rdx
	.cfi_def_cfa_offset 64
	movq	%r14, %rdx
	call	__fprintf_chk@PLT
	popq	%rax
	.cfi_def_cfa_offset 56
	popq	%rdx
	.cfi_def_cfa_offset 48
	cmpq	%rbp, 40(%rbx)
	je	.L67
.L18:
	movl	16(%rbx), %ecx
	cmpq	%r12, 64(%rbx)
	jne	.L82
.L17:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movq	%r13, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 32
	movl	$1, %esi
	popq	%r12
	.cfi_def_cfa_offset 24
	leaq	.LC10(%rip), %rdx
	popq	%r13
	.cfi_def_cfa_offset 16
	xorl	%eax, %eax
	popq	%r14
	.cfi_def_cfa_offset 8
	jmp	__fprintf_chk@PLT
	.p2align 4,,10
	.p2align 3
.L67:
	.cfi_restore_state
	movl	16(%rbx), %ecx
	jmp	.L17
	.p2align 4,,10
	.p2align 3
.L69:
	movl	$12, %edx
	movq	%r13, %rcx
	movl	$1, %esi
	leaq	.LC7(%rip), %rdi
	call	fwrite@PLT
	movzwl	80(%rbx), %edx
	xorl	%eax, %eax
	testw	%dx, %dx
	je	.L3
.L70:
	movl	16(%rbx), %ecx
	leaq	.LC8(%rip), %rdx
	movl	$1, %esi
	movq	%r13, %rdi
	call	__fprintf_chk@PLT
	movzwl	80(%rbx), %edx
	testb	$1, %dl
	je	.L4
	movl	4(%rbx), %eax
	subq	$8, %rsp
	.cfi_def_cfa_offset 56
	movl	16(%rbx), %ecx
	xorl	%r8d, %r8d
	leaq	.LC9(%rip), %rdx
	movq	%r13, %rdi
	xorl	%r9d, %r9d
	movl	$1, %esi
	pushq	%rax
	.cfi_def_cfa_offset 64
	xorl	%eax, %eax
	call	__fprintf_chk@PLT
	movzwl	80(%rbx), %edx
	popq	%rdi
	.cfi_def_cfa_offset 56
	popq	%r8
	.cfi_def_cfa_offset 48
.L4:
	movzwl	%dx, %eax
	testb	$2, %dl
	je	.L3
	movl	4(%rbx), %eax
	subq	$8, %rsp
	.cfi_def_cfa_offset 56
	movl	16(%rbx), %ecx
	movl	$1, %esi
	leaq	.LC9(%rip), %rdx
	xorl	%r9d, %r9d
	movl	$1, %r8d
	movq	%r13, %rdi
	pushq	%rax
	.cfi_def_cfa_offset 64
	xorl	%eax, %eax
	call	__fprintf_chk@PLT
	movzwl	80(%rbx), %eax
	popq	%rcx
	.cfi_def_cfa_offset 56
	popq	%rsi
	.cfi_def_cfa_offset 48
	movl	%eax, %edx
	testb	$4, %al
	je	.L5
.L71:
	movl	4(%rbx), %eax
	subq	$8, %rsp
	.cfi_def_cfa_offset 56
	movl	16(%rbx), %ecx
	xorl	%r9d, %r9d
	leaq	.LC9(%rip), %rdx
	movl	$2, %r8d
	movl	$1, %esi
	movq	%r13, %rdi
	pushq	%rax
	.cfi_def_cfa_offset 64
	xorl	%eax, %eax
	call	__fprintf_chk@PLT
	movzwl	80(%rbx), %eax
	popq	%r12
	.cfi_def_cfa_offset 56
	popq	%r14
	.cfi_def_cfa_offset 48
	movl	%eax, %edx
	testb	$8, %al
	je	.L6
.L72:
	movl	4(%rbx), %eax
	subq	$8, %rsp
	.cfi_def_cfa_offset 56
	movl	16(%rbx), %ecx
	xorl	%r9d, %r9d
	leaq	.LC9(%rip), %rdx
	movl	$3, %r8d
	movl	$1, %esi
	movq	%r13, %rdi
	pushq	%rax
	.cfi_def_cfa_offset 64
	xorl	%eax, %eax
	call	__fprintf_chk@PLT
	movzwl	80(%rbx), %eax
	popq	%r11
	.cfi_def_cfa_offset 56
	popq	%rbp
	.cfi_def_cfa_offset 48
	movl	%eax, %edx
	testb	$16, %al
	je	.L7
.L73:
	movl	4(%rbx), %eax
	subq	$8, %rsp
	.cfi_def_cfa_offset 56
	movl	16(%rbx), %ecx
	xorl	%r9d, %r9d
	leaq	.LC9(%rip), %rdx
	movl	$4, %r8d
	movl	$1, %esi
	movq	%r13, %rdi
	pushq	%rax
	.cfi_def_cfa_offset 64
	xorl	%eax, %eax
	call	__fprintf_chk@PLT
	movzwl	80(%rbx), %eax
	popq	%r9
	.cfi_def_cfa_offset 56
	popq	%r10
	.cfi_def_cfa_offset 48
	movl	%eax, %edx
	testb	$32, %al
	je	.L8
.L74:
	movl	4(%rbx), %eax
	subq	$8, %rsp
	.cfi_def_cfa_offset 56
	movl	16(%rbx), %ecx
	movl	$5, %r8d
	leaq	.LC9(%rip), %rdx
	movq	%r13, %rdi
	xorl	%r9d, %r9d
	movl	$1, %esi
	pushq	%rax
	.cfi_def_cfa_offset 64
	xorl	%eax, %eax
	call	__fprintf_chk@PLT
	movzwl	80(%rbx), %eax
	popq	%rdi
	.cfi_def_cfa_offset 56
	popq	%r8
	.cfi_def_cfa_offset 48
	movl	%eax, %edx
	testb	$64, %al
	je	.L9
.L75:
	movl	4(%rbx), %eax
	subq	$8, %rsp
	.cfi_def_cfa_offset 56
	movl	16(%rbx), %ecx
	movl	$1, %esi
	leaq	.LC9(%rip), %rdx
	xorl	%r9d, %r9d
	movl	$6, %r8d
	movq	%r13, %rdi
	pushq	%rax
	.cfi_def_cfa_offset 64
	xorl	%eax, %eax
	call	__fprintf_chk@PLT
	movzwl	80(%rbx), %eax
	popq	%rcx
	.cfi_def_cfa_offset 56
	popq	%rsi
	.cfi_def_cfa_offset 48
	movl	%eax, %edx
	testb	$-128, %al
	je	.L10
.L76:
	movl	4(%rbx), %eax
	subq	$8, %rsp
	.cfi_def_cfa_offset 56
	movl	16(%rbx), %ecx
	xorl	%r9d, %r9d
	leaq	.LC9(%rip), %rdx
	movl	$7, %r8d
	movl	$1, %esi
	movq	%r13, %rdi
	pushq	%rax
	.cfi_def_cfa_offset 64
	xorl	%eax, %eax
	call	__fprintf_chk@PLT
	movzwl	80(%rbx), %eax
	popq	%r12
	.cfi_def_cfa_offset 56
	popq	%r14
	.cfi_def_cfa_offset 48
	movl	%eax, %edx
	testb	$1, %ah
	je	.L11
.L77:
	movl	4(%rbx), %eax
	subq	$8, %rsp
	.cfi_def_cfa_offset 56
	movl	16(%rbx), %ecx
	xorl	%r9d, %r9d
	leaq	.LC9(%rip), %rdx
	movl	$8, %r8d
	movl	$1, %esi
	movq	%r13, %rdi
	pushq	%rax
	.cfi_def_cfa_offset 64
	xorl	%eax, %eax
	call	__fprintf_chk@PLT
	movzwl	80(%rbx), %eax
	popq	%r11
	.cfi_def_cfa_offset 56
	popq	%rbp
	.cfi_def_cfa_offset 48
	movl	%eax, %edx
	testb	$2, %ah
	je	.L12
.L78:
	movl	4(%rbx), %eax
	subq	$8, %rsp
	.cfi_def_cfa_offset 56
	movl	16(%rbx), %ecx
	xorl	%r9d, %r9d
	leaq	.LC9(%rip), %rdx
	movl	$9, %r8d
	movl	$1, %esi
	movq	%r13, %rdi
	pushq	%rax
	.cfi_def_cfa_offset 64
	xorl	%eax, %eax
	call	__fprintf_chk@PLT
	movzwl	80(%rbx), %eax
	popq	%r9
	.cfi_def_cfa_offset 56
	popq	%r10
	.cfi_def_cfa_offset 48
	movl	%eax, %edx
	testb	$4, %ah
	je	.L13
.L79:
	movl	4(%rbx), %eax
	subq	$8, %rsp
	.cfi_def_cfa_offset 56
	movl	16(%rbx), %ecx
	movl	$10, %r8d
	leaq	.LC9(%rip), %rdx
	movq	%r13, %rdi
	xorl	%r9d, %r9d
	movl	$1, %esi
	pushq	%rax
	.cfi_def_cfa_offset 64
	xorl	%eax, %eax
	call	__fprintf_chk@PLT
	movzwl	80(%rbx), %eax
	popq	%rdi
	.cfi_def_cfa_offset 56
	popq	%r8
	.cfi_def_cfa_offset 48
	movl	%eax, %edx
	testb	$8, %ah
	je	.L14
.L80:
	movl	4(%rbx), %eax
	subq	$8, %rsp
	.cfi_def_cfa_offset 56
	movl	16(%rbx), %ecx
	movl	$1, %esi
	leaq	.LC9(%rip), %rdx
	xorl	%r9d, %r9d
	movl	$11, %r8d
	movq	%r13, %rdi
	pushq	%rax
	.cfi_def_cfa_offset 64
	xorl	%eax, %eax
	call	__fprintf_chk@PLT
	movzwl	80(%rbx), %edx
	popq	%rcx
	.cfi_def_cfa_offset 56
	popq	%rsi
	.cfi_def_cfa_offset 48
	testw	%dx, %dx
	je	.L15
.L81:
	movq	%r13, %rsi
	movl	$10, %edi
	call	fputc@PLT
	jmp	.L15
	.cfi_endproc
.LFE895:
	.size	_ZN11__acds_cell9printcellEP8_IO_FILE, .-_ZN11__acds_cell9printcellEP8_IO_FILE
	.align 2
	.p2align 4
	.globl	_ZN11__acds_cell4evalEv
	.type	_ZN11__acds_cell4evalEv, @function
_ZN11__acds_cell4evalEv:
.LFB902:
	.cfi_startproc
	endbr64
	movq	%rdi, %rcx
	movslq	4(%rcx), %rsi
	movl	%esi, %eax
	sall	$4, %eax
	cmpl	$1, %eax
	jle	.L85
.L115:
	movl	$8, %r8d
	.p2align 4,,10
	.p2align 3
.L90:
	xorl	%edx, %edx
	movl	$1, %eax
	jmp	.L88
	.p2align 4,,10
	.p2align 3
.L114:
	testq	%rsi, %rsi
	je	.L87
	movq	96(%rcx), %rsi
	movq	88(%rcx), %rdi
	movzbl	(%rdi,%rdx), %edi
	andb	(%rsi,%rdx), %dil
	orb	%dil, (%rsi,%rax)
	movq	96(%rcx), %rsi
	movq	88(%rcx), %rdi
	movzbl	(%rdi,%rax), %edi
	andb	(%rsi,%rax), %dil
	orb	%dil, (%rsi,%rdx)
.L87:
	addq	$1, %rax
	addq	$1, %rdx
	cmpq	$17, %rax
	je	.L113
.L88:
	movq	%rax, %rsi
	andl	$15, %esi
	cmpq	$11, %rsi
	jle	.L114
	testq	%rsi, %rsi
	je	.L87
	movq	96(%rcx), %rsi
	movq	88(%rcx), %rdi
	movzbl	(%rdi,%rdx), %edi
	orb	(%rsi,%rdx), %dil
	andb	%dil, (%rsi,%rax)
	movq	96(%rcx), %rsi
	movq	88(%rcx), %rdi
	movzbl	(%rdi,%rax), %edi
	orb	(%rsi,%rax), %dil
	addq	$1, %rax
	andb	%dil, (%rsi,%rdx)
	addq	$1, %rdx
	cmpq	$17, %rax
	jne	.L88
.L113:
	subq	$1, %r8
	jne	.L90
	movslq	4(%rcx), %rsi
	movl	%esi, %eax
	sall	$4, %eax
	cmpl	$1, %eax
	jg	.L115
.L85:
	xorl	%edi, %edi
	testq	%rsi, %rsi
	jle	.L111
.L91:
	movq	%rdi, %rax
	cqto
	idivq	%rsi
	andl	$15, %eax
	cmpq	$11, %rax
	jg	.L92
	movzwl	80(%rcx), %edx
	btl	%eax, %edx
	jnc	.L92
	movq	%rdi, %rax
	movq	96(%rcx), %rdx
	andl	$4294967280, %eax
	movq	%rax, %rsi
	movzbl	(%rdx,%rdi), %r8d
	orq	$13, %rax
	orq	$12, %rsi
	orb	%r8b, (%rdx,%rsi)
	movq	96(%rcx), %rdx
	movzbl	(%rdx,%rdi), %esi
	orb	%sil, (%rdx,%rax)
	movslq	4(%rcx), %rsi
.L92:
	addq	$1, %rdi
	cmpq	%rdi, %rsi
	jg	.L91
.L111:
	ret
	.cfi_endproc
.LFE902:
	.size	_ZN11__acds_cell4evalEv, .-_ZN11__acds_cell4evalEv
	.align 2
	.p2align 4
	.globl	_ZN11__acds_cell9antiphaseEv
	.type	_ZN11__acds_cell9antiphaseEv, @function
_ZN11__acds_cell9antiphaseEv:
.LFB903:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %rcx
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movslq	4(%rdi), %r9
	movl	%r9d, %eax
	movq	%r9, %rbx
	sall	$4, %eax
	cmpl	%eax, %r9d
	jge	.L126
	leaq	1(%r9), %r11
	addq	$16, %r9
.L122:
	movl	$8, %r10d
	.p2align 4,,10
	.p2align 3
.L121:
	movq	%r11, %rax
	jmp	.L120
	.p2align 4,,10
	.p2align 3
.L139:
	andl	%r12d, %edx
	orl	%ebp, %edx
	movb	%dl, (%rsi)
	movq	96(%rcx), %rdx
	movq	88(%rcx), %rsi
	movzbl	(%rsi,%rax), %esi
	andb	(%rdx,%rax), %sil
	addq	$1, %rax
	orb	%sil, (%rdx,%rdi)
	cmpq	%r9, %rax
	je	.L138
.L120:
	movq	88(%rcx), %r8
	movq	96(%rcx), %rdx
	leaq	-1(%rax), %rdi
	movzbl	-1(%r8,%rax), %r12d
	movq	%rax, %r8
	leaq	(%rdx,%rax), %rsi
	movzbl	-1(%rdx,%rax), %edx
	andl	$15, %r8d
	movzbl	(%rsi), %ebp
	cmpq	$11, %r8
	jle	.L139
	orl	%r12d, %edx
	andl	%ebp, %edx
	movb	%dl, (%rsi)
	movq	96(%rcx), %rdx
	movq	88(%rcx), %rsi
	movzbl	(%rsi,%rax), %esi
	orb	(%rdx,%rax), %sil
	addq	$1, %rax
	andb	%sil, (%rdx,%rdi)
	cmpq	%r9, %rax
	jne	.L120
.L138:
	subq	$1, %r10
	jne	.L121
	movl	4(%rcx), %edi
	movl	%edi, %eax
	sall	$4, %eax
	cmpl	%eax, %ebx
	jl	.L122
	movslq	%edi, %r9
.L117:
	xorl	%esi, %esi
	testq	%r9, %r9
	jle	.L136
.L123:
	movq	%rsi, %rax
	cqto
	idivq	%r9
	andl	$15, %eax
	cmpq	$11, %rax
	jg	.L124
	movzwl	80(%rcx), %edx
	btl	%eax, %edx
	jnc	.L124
	movq	%rsi, %rdx
	movq	96(%rcx), %rax
	andl	$4294967280, %edx
	orq	$12, %rdx
	movzbl	(%rax,%rdx), %edx
	andb	%dl, (%rax,%rsi)
	movl	4(%rcx), %edi
.L124:
	addq	$1, %rsi
	movslq	%edi, %r9
	cmpq	%rsi, %r9
	jg	.L123
.L136:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L126:
	.cfi_restore_state
	movl	%r9d, %edi
	jmp	.L117
	.cfi_endproc
.LFE903:
	.size	_ZN11__acds_cell9antiphaseEv, .-_ZN11__acds_cell9antiphaseEv
	.align 2
	.p2align 4
	.globl	_ZN11__acds_cell5driveEv
	.type	_ZN11__acds_cell5driveEv, @function
_ZN11__acds_cell5driveEv:
.LFB904:
	.cfi_startproc
	endbr64
	movq	32(%rdi), %r8
	movq	56(%rdi), %r9
	cmpq	40(%rdi), %r8
	je	.L147
	movl	$12, %r10d
	cmpq	%r9, 64(%rdi)
	je	.L147
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	jmp	.L149
	.p2align 4,,10
	.p2align 3
.L143:
	cmpq	%r9, 64(%rdi)
	je	.L145
.L149:
	movq	(%r9), %rcx
	movzwl	82(%rdi), %edx
	addq	$8, %r8
	addq	$8, %r9
	addq	96(%rdi), %rdx
	movq	-8(%r8), %r11
	movq	%rcx, %rax
	movzbl	%cl, %ecx
	sarq	$16, %rax
	addq	88(%r11), %rcx
	movzwl	%ax, %eax
	movzbl	(%rdx,%rax), %edx
	movl	%edx, %ebx
	leal	0(,%rdx,8), %eax
	movl	%edx, %esi
	sall	$4, %ebx
	orl	%ebx, %eax
	orl	%edx, %eax
	addl	%edx, %edx
	andl	$8, %edx
	orl	%edx, %eax
	movl	%esi, %edx
	shrb	$4, %sil
	shrb	$3, %dl
	orl	%esi, %edx
	orl	%edx, %eax
	movq	96(%r11), %rdx
	andb	(%rdx,%r10), %al
	movb	%al, (%rcx)
	cmpq	%r8, 40(%rdi)
	jne	.L143
.L145:
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L147:
	.cfi_restore 3
	ret
	.cfi_endproc
.LFE904:
	.size	_ZN11__acds_cell5driveEv, .-_ZN11__acds_cell5driveEv
	.globl	acds_global_ID_counter
	.bss
	.align 4
	.type	acds_global_ID_counter, @object
	.size	acds_global_ID_counter, 4
acds_global_ID_counter:
	.zero	4
	.globl	global_bus_Y_off
	.align 4
	.type	global_bus_Y_off, @object
	.size	global_bus_Y_off, 4
global_bus_Y_off:
	.zero	4
	.globl	global_bus_X_off
	.align 4
	.type	global_bus_X_off, @object
	.size	global_bus_X_off, 4
global_bus_X_off:
	.zero	4
	.globl	global_anchor_y
	.align 4
	.type	global_anchor_y, @object
	.size	global_anchor_y, 4
global_anchor_y:
	.zero	4
	.globl	global_anchor_x
	.align 4
	.type	global_anchor_x, @object
	.size	global_anchor_x, 4
global_anchor_x:
	.zero	4
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
