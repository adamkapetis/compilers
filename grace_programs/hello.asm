	.text
	.file	"grace program"
	.globl	hello                           # -- Begin function hello
	.p2align	4, 0x90
	.type	hello,@function
hello:                                  # @hello
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$.Lstrconst, %edi
	callq	writeString@PLT
	movl	$.Lstrconst.1, %edi
	callq	strlen@PLT
	movq	(%rsp), %rdi
	callq	writeInteger@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	hello, .Lfunc_end0-hello
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	hello@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	.Lstrconst,@object              # @strconst
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lstrconst:
	.asciz	"Hello world! hey\\\\n "
	.size	.Lstrconst, 21

	.type	.Lstrconst.1,@object            # @strconst.1
.Lstrconst.1:
	.asciz	"Hello world"
	.size	.Lstrconst.1, 12

	.section	".note.GNU-stack","",@progbits