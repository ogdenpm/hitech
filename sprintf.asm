*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - sprintf.asm Created 09.03.2019 Last Modified 31.01.2021

; Unlike the standard library function, this one uses the 
; _IOWRT|_IOBINARY flags instead of _IOWRT|_IOBINARY|_IOSTRG.


	global	_sprintf	;	global	_sprintf	
	global	ncsv,cret,indir	;	global	ncsv, cret, indir	
	global	__doprnt	;	global	__doprnt	
	global	csv		;	global	csv		

	psect	text

; Disassembled version		; After compiling C source code
_sprintf:
	call 	csv		;	call	csv
	ld	hl,32767	;	ld	hl,32767
	ld	(_spf+2),h	;	ld	(_spf+2),hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	ld	(_spf),hl	;	ld	(_spf),hl
	ld	hl,_spf+6	;	ld	hl,_spf+6
	ld	(hl),82h	;	ld	(hl),-126
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,10		;	ld	hl,10
	add	hl,de		;	add	hl,de
	push	hl		;	push	hl
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	ld	hl,_spf		;	ld	hl,_spf
	push	hl		;	push	hl
	call	__doprnt	;	call	__doprnt
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	hl,(_spf)	;	ld	hl,(_spf)
	ld	(hl),0		;	ld	(hl),0
	ld	e,(ix+6)	;	ld	e,(ix+6)
	ld	d,(ix+7)	;	ld	d,(ix+7)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	cret		;	jp	cret

	psect	bss

_spf:	defs	8

	psect	text

/* End function sprintf */

