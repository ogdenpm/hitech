*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 46F7.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_46F7 OK++
;=========================================================
	global	_sub_46F7	;	global	_sub_46F7
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	aland		;	global	aland
	global	arelop		;	global	arelop
	global	asalrsh		;	global	asalrsh
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code	
_sub_46F7:
	call	csv		;	call	csv
	push	hl		;	push	hl
	ld	e,(ix+6)	;	ld	e,(ix+6)
	ld	d,(ix+7)	;	ld	d,(ix+7)
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	push	de		;	push	de
	ex	de,hl		;	ex	de,hl
	ld	bc,0FFFFh	;	ld	bc,-1
	add	hl,bc		;	add	hl,bc
	ex	de,hl		;	ex	de,hl
	adc	hl,bc		;	adc	hl,bc
	call	aland		;	call	aland
	ld	a,e		;	ld	a,e
	or	d		;	or	d
	or	l		;	or	l
	or	h		;	or	h
	jr	nz,loc_4734	;	jp	nz,L1
	ld	de,1		;	ld	de,1
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(ix+6)	;	ld	e,(ix+6)
	ld	d,(ix+7)	;	ld	d,(ix+7)
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	call	arelop		;	call	arelop
	jp	p,loc_4739	;	jp	p,l2
loc_4734:			;L1:
	ld	l,0		;	ld	l,0
	jp	cret		;	jp	cret
loc_4739:			;l2:
	ld	(ix+-1),0	;	ld	(ix+-1),0
	jr	loc_4742	;	jp	l3
loc_473F:			;l4:
	inc	(ix+-1)		;	inc	(ix+-1)
loc_4742:			;l3:
	ld	b,1		;	ld	b,1
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,6		;	ld	hl,6
	add	hl,de		;	add	hl,de
	call	asalrsh		;	call	asalrsh
	ld	a,e		;	ld	a,e
	or	d		;	or	d
	or	l		;	or	l
	or	h		;	or	h
	jr	nz,loc_473F	;	jp	nz,l4
	ld	a,(ix+-1)	;	ld	a,(ix+-1)
	inc	a		;	inc	a
	ld	l,a		;	ld	l,a
	jp	cret		;	jp	cret

; End of function sub_46F7 OK++

; End of file 46F7.as


