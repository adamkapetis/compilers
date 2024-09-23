	.text
	.file	"count.ll"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	movl	$0, .Lvars+92(%rip)
	movl	$42, %ebx
	testl	%ebx, %ebx
	jle	.LBB0_3
	.p2align	4, 0x90
.LBB0_2:                                # %body
                                        # =>This Inner Loop Header: Depth=1
	decl	%ebx
	movl	.Lvars+92(%rip), %eax
	incl	%eax
	movl	%eax, .Lvars+92(%rip)
	movslq	%eax, %rdi
	callq	writeInteger@PLT
	movl	$.Lnl, %edi
	callq	writeString@PLT
	testl	%ebx, %ebx
	jg	.LBB0_2
.LBB0_3:                                # %endfor
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.Lvars,@object                  # @vars
	.local	.Lvars
	.comm	.Lvars,104,16
	.type	.Lnl,@object                    # @nl
	.section	.rodata,"a",@progbits
.Lnl:
	.asciz	"\n"
	.size	.Lnl, 2

	.section	".note.GNU-stack","",@progbits
