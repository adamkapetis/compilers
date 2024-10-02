	.text
	.file	"grace program"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$72, %rsp
	.cfi_def_cfa_offset 80
	movq	$5, 24(%rsp)
	movq	$6, 16(%rsp)
	movb	$97, 15(%rsp)
	movl	$5, %edi
	movl	$2, %esi
	movl	$97, %edx
	callq	hello@PLT
	addq	$72, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.globl	hello                           # -- Begin function hello
	.p2align	4, 0x90
	.type	hello,@function
hello:                                  # @hello
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdi, -16(%rsp)
	movb	%dl, -17(%rsp)
	movq	$2, -8(%rsp)
	movl	$5, %eax
	retq
.Lfunc_end1:
	.size	hello, .Lfunc_end1-hello
	.cfi_endproc
                                        # -- End function
	.globl	main.1                          # -- Begin function main.1
	.p2align	4, 0x90
	.type	main.1,@function
main.1:                                 # @main.1
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	main@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end2:
	.size	main.1, .Lfunc_end2-main.1
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
