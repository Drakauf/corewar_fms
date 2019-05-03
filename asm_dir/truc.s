	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.intel_syntax noprefix
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	push	rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi2:
	.cfi_def_cfa_register rbp
	sub	rsp, 192
	mov	eax, 4294967295
	mov	ecx, eax
	mov	dword ptr [rbp - 4], 0
	mov	dword ptr [rbp - 8], edi
	mov	qword ptr [rbp - 16], rsi
	mov	rdi, rcx
	call	_malloc
	mov	esi, 13
	mov	qword ptr [rbp - 184], rax
	cmp	rax, 0
	sete	dl
	and	dl, 1
	movzx	edi, dl
	call	_ft_assert
	mov	rdi, qword ptr [rbp - 184]
	call	_free
	mov	qword ptr [rbp - 176], 0
	cmp	dword ptr [rbp - 8], 1
	jne	LBB0_2
## BB#1:
	mov	rax, qword ptr [rbp - 16]
	mov	rdi, qword ptr [rax]
	call	_print_help
	mov	dword ptr [rbp - 4], eax
	jmp	LBB0_7
LBB0_2:
	mov	esi, 4
	cmp	dword ptr [rbp - 8], 5
	setg	al
	and	al, 1
	movzx	edi, al
	call	_ft_assert
	lea	rsi, [rbp - 168]
	mov	rcx, qword ptr [rbp - 16]
	add	rcx, 8
	mov	rdi, rcx
	call	_get_arguments
	lea	rcx, [rbp - 168]
	mov	rdi, qword ptr [rbp - 64]
	add	rcx, 12
	mov	rdx, qword ptr [rbp - 72]
	mov	rsi, rcx
	call	_get_contents
	mov	esi, 10
	mov	qword ptr [rbp - 112], rax
	cmp	rax, 0
	setne	r8b
	xor	r8b, -1
	and	r8b, 1
	movzx	edi, r8b
	call	_ft_assert
	cmp	qword ptr [rbp - 72], 0
	jne	LBB0_4
## BB#3:
	mov	rdi, qword ptr [rbp - 112]
	mov	esi, dword ptr [rbp - 156]
	call	_disassemble
	mov	dword ptr [rbp - 4], eax
	jmp	LBB0_7
LBB0_4:
	lea	rdi, [rbp - 168]
	lea	rsi, [rbp - 176]
	call	_general_parser
	lea	rdi, [rbp - 168]
	mov	rsi, qword ptr [rbp - 176]
	call	_print_total_errors
	cmp	eax, 0
	je	LBB0_6
## BB#5:
	mov	dword ptr [rbp - 4], 1
	jmp	LBB0_7
LBB0_6:
	lea	rdi, [rbp - 168]
	mov	rsi, qword ptr [rbp - 176]
	mov	rdx, qword ptr [rbp - 72]
	call	_write_binary
	lea	rdi, [rbp - 168]
	mov	rsi, qword ptr [rbp - 176]
	call	_free_all
	mov	dword ptr [rbp - 4], 0
LBB0_7:
	mov	eax, dword ptr [rbp - 4]
	add	rsp, 192
	pop	rbp
	ret
	.cfi_endproc

	.p2align	4, 0x90
_print_total_errors:                    ## @print_total_errors
	.cfi_startproc
## BB#0:
	push	rbp
Lcfi3:
	.cfi_def_cfa_offset 16
Lcfi4:
	.cfi_offset rbp, -16
	mov	rbp, rsp
Lcfi5:
	.cfi_def_cfa_register rbp
	sub	rsp, 80
	mov	qword ptr [rbp - 16], rdi
	mov	qword ptr [rbp - 24], rsi
	mov	rsi, qword ptr [rbp - 16]
	mov	edi, dword ptr [rsi]
	call	_ft_itoa
	mov	qword ptr [rbp - 32], rax
	mov	dword ptr [rbp - 36], 0
	mov	rax, qword ptr [rbp - 16]
	cmp	dword ptr [rax], 0
	je	LBB1_5
## BB#1:
	mov	edi, 2
	lea	rsi, [rip + L_.str]
	mov	eax, 7
	mov	edx, eax
	call	_write
	mov	rsi, qword ptr [rbp - 32]
	mov	rdi, qword ptr [rbp - 32]
	mov	qword ptr [rbp - 48], rax ## 8-byte Spill
	mov	qword ptr [rbp - 56], rsi ## 8-byte Spill
	call	_ft_strlen
	mov	edi, 2
	mov	rsi, qword ptr [rbp - 56] ## 8-byte Reload
	mov	rdx, rax
	call	_write
	mov	rdx, qword ptr [rbp - 16]
	cmp	dword ptr [rdx], 1
	mov	qword ptr [rbp - 64], rax ## 8-byte Spill
	jne	LBB1_3
## BB#2:
	mov	edi, 2
	lea	rsi, [rip + L_.str.1]
	mov	eax, 11
	mov	edx, eax
	call	_write
	mov	qword ptr [rbp - 72], rax ## 8-byte Spill
	jmp	LBB1_4
LBB1_3:
	mov	edi, 2
	lea	rsi, [rip + L_.str.2]
	mov	eax, 12
	mov	edx, eax
	call	_write
	mov	qword ptr [rbp - 80], rax ## 8-byte Spill
LBB1_4:
	jmp	LBB1_12
LBB1_5:
	mov	rax, qword ptr [rbp - 16]
	cmp	qword ptr [rax + 72], 0
	jne	LBB1_7
## BB#6:
	mov	edi, 2
	lea	rsi, [rip + L_.str.3]
	mov	eax, 40
	mov	edx, eax
	call	_write
	mov	edi, eax
	mov	dword ptr [rbp - 36], edi
LBB1_7:
	mov	rax, qword ptr [rbp - 16]
	cmp	qword ptr [rax + 64], 0
	jne	LBB1_9
## BB#8:
	mov	edi, 2
	lea	rsi, [rip + L_.str.4]
	mov	eax, 43
	mov	edx, eax
	call	_write
	mov	edi, eax
	mov	dword ptr [rbp - 36], edi
LBB1_9:
	mov	rax, qword ptr [rbp - 16]
	cmp	dword ptr [rax + 92], 0
	jne	LBB1_11
## BB#10:
	mov	edi, 2
	lea	rsi, [rip + L_.str.5]
	mov	eax, 34
	mov	edx, eax
	call	_write
	mov	edi, eax
	mov	dword ptr [rbp - 36], edi
LBB1_11:
	jmp	LBB1_12
LBB1_12:
	cmp	dword ptr [rbp - 36], 0
	jne	LBB1_15
## BB#13:
	mov	rax, qword ptr [rbp - 16]
	cmp	dword ptr [rax], 0
	jne	LBB1_15
## BB#14:
	mov	dword ptr [rbp - 4], 0
	jmp	LBB1_16
LBB1_15:
	mov	rdi, qword ptr [rbp - 16]
	mov	rsi, qword ptr [rbp - 24]
	call	_free_all
	mov	dword ptr [rbp - 4], 1
LBB1_16:
	mov	eax, dword ptr [rbp - 4]
	add	rsp, 80
	pop	rbp
	ret
	.cfi_endproc

	.comm	_g_inst_info,272,4      ## @g_inst_info
	.comm	_g_dflt_inst_set,136,4  ## @g_dflt_inst_set
	.comm	_g_altr_inst_set,136,4  ## @g_altr_inst_set
	.comm	_g_binsize,680,4        ## @g_binsize
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"\033[1;31m"

L_.str.1:                               ## @.str.1
	.asciz	" error\n\033[0m"

L_.str.2:                               ## @.str.2
	.asciz	" errors\n\033[0m"

L_.str.3:                               ## @.str.3
	.asciz	"\033[0;31mError: \033[0mmissing .name section\n"

L_.str.4:                               ## @.str.4
	.asciz	"\033[0;31mError: \033[0mmissing .comment section\n"

L_.str.5:                               ## @.str.5
	.asciz	"\033[0;31mError: \033[0mno instructions\n"


.subsections_via_symbols
