*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 2C5E.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_2C5E OK+
;
; From source in C, compiler generates code that performs
; expected action, but differs from original image
;=========================================================
	global	_sub_2C5E	;	global	_sub_2C5E
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_nodesize	;	global	_nodesize
	global	brelop		;	global	brelop
	global	allsh		;	global	allsh
	global	aland		;	global	aland
	global	allsh		;	global	allsh
	global	alsub		;	global	alsub
	global	asalor		;	global	asalor
	global 	csv		;	global 	csv

	psect	text

;	Disassembled version	; After compiling C source code	
_sub_2C5E:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	add	hl,hl		;	add	hl,hl
	add	hl,hl		;	add	hl,hl
	add	hl,hl		;	add	hl,hl
	ld	a,l		;	ld	a,l
	ld	(ix+-1),a	;	ld	(ix+-1),a
	ld	b,32		;	ld	b,32
	call	brelop		;	call	brelop
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	l,(ix+10)	;	ld	l,(ix+10)
	ld	h,(ix+11)	;	ld	h,(ix+11)
	jp	p,cret		;	jp	p,cret
	push	hl		;	push	hl
	push	de		;	push	de
	ld	a,(ix+-1)	;	ld	a,(ix+-1)
	add	a,255		;	add	a,255
	ld	b,a		;	ld	b,a
	ld	de,1		;	ld	de,1
	ld	hl,0		;	ld	hl,0
	call	allsh		;	call	allsh
	call	aland		;	call	aland
	ld	a,e		;	ld	a,e
	or	d		;	or	d
	or	l		;	or	l
	or	h		;	or	h
	jr	z,loc_2CD1	;	jp	z,l13
	ld	b,(ix+-1)	;	ld	b,(ix+-1)
	ld	de,1		;	ld	de,1
	ld	hl,0		;	ld	hl,0
	call	allsh		;	call	allsh
	ex	de,hl		;	ex	de,hl
	ld	bc,-1		;	ld	bc,-1
	add	hl,bc		;	add	hl,bc
	ex	de,hl		;	ex	de,hl
	adc	hl,bc		;	adc	hl,bc
	push	hl		;	push	hl
	push	de		;	push	de
	ld	l,c		;	ld	e,c	   <----+ At this point,
	ld	h,b		;	ld	d,b		; from source
	pop	bc		;	ld	l,c		; in C, compiler
	or	a		;	ld	h,b		; generates code
	sbc	hl,bc		;	call	alsub		; that performs
	pop	bc		;				; expected
	ex	de,hl		;				; action, but
	ld	hl,-1		;				; differs from 
	sbc	hl,bc		;			   <----+ original image
	push	hl		;	push	hl
	push	de		;	push	de
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,8		;	ld	hl,8
	add	hl,de		;	add	hl,de
	call	asalor		;	call	asalor
loc_2CD1:			;l13:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	l,(ix+10)	;	ld	l,(ix+10)
	ld	h,(ix+11)	;	ld	h,(ix+11)
	jp	cret		;	jp	cret

; End of function sub_2C5E OK+

; End of file 2C5E.as


