*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 2CE0.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_2CE0 OK++
;=========================================================
	global	_sub_2CE0	;	global	_sub_2CE0
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_printf		;	global	_printf
	global	_sub_2C5E	;	global	_sub_2C5E
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code	
_sub_2CE0:
	call 	csv		;	call 	csv		
	ld	e,(ix+8)	;	ld	e,(ix+8)	
	ld	d,(ix+9)	;	ld	d,(ix+9)	
	ld	l,(ix+10)	;	ld	l,(ix+0Ah)	
	ld	h,(ix+11)	;	ld	h,(ix+0Bh)	
	push	hl		;	push	hl		
	push	de		;	push	de		
	ld	l,(ix+6)	;	ld	l,(ix+6)	
	ld	h,(ix+7)	;	ld	h,(ix+7)	
	push	hl		;	push	hl		
	call	_sub_2C5E	;	call	_sub_2C5E	
	pop	bc		;	pop	bc		
	pop	bc		;	pop	bc		
	ex	(sp),hl		;	ex	(sp),hl		
	push	de		;	push	de		
	ld	hl,19f		;	ld	hl,19f		
	push	hl		;	push	hl		
	call	_printf		;	call	_printf		
	jp	cret		;	jp	cret		

; End of function sub_2CE0 OK++

	psect	data

p_2ce0_1:
19:
	defb	37,108,100,0

	psect	text

; End of file 2CE0.as


