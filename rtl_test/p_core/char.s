
.global is_alpha
is_alpha:
cmpl $'A',%r8
csetge %eax
cmpl $'Z',%r8
csetle %ebx
andl %ebx,%eax
cmpl $'a',%r8
csetge %edx
cmpl $'z',%r8
csetle %ebx
andl %ebx,%edx
orl %edx,%eax
cmpl $'_',%r8
cseteq %edx
orl %edx,%eax
retq

.global is_alpha_num
is_alpha_num:
cmpl $'A',%r8
csetge %eax
cmpl $'Z',%r8
csetle %ebx
andl %ebx,%eax
cmpl $'a',%r8
csetge %edx
cmpl $'Z',%r8
csetle %ebx
andl %ebx,%edx
orl %edx,%eax
cmpl $'_',%r8
cseteq %edx
orl %edx,%eax
cmpl $'0',%r8
csetge %edx
cmpl $'9',%r8
csetle %ebx
andl %ebx,%edx
orl %edx,%eax
retq


