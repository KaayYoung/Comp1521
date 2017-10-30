	.file	"where_are_the_bits.c"
	.section	.rodata
.LC0:
	.string	"%ul\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$20, %esp
	subl	$8, %esp
	pushl	$4
	pushl	$.LC0
	call	printf
	addl	$16, %esp
.L2:
	movzbl	-12(%ebp), %eax
	andl	$-16, %eax
	movb	%al, -12(%ebp)
	movzbl	-12(%ebp), %eax
	andl	$-16, %eax
	orl	$1, %eax
	movb	%al, -12(%ebp)
	jmp	.L2
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Debian 4.9.2-10) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
