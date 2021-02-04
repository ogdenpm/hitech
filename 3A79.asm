*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 3A79.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_3A79 OK+
;
; From source in C, compiler generates code that performs
; expected action, but differs from original image
;=========================================================
	global	_sub_3A79	;	global	_sub_3A79
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_nodesize	;	global	_nodesize
	global	wrelop		;	global	wrelop
	global	asal		;	global	asal
	global	allsh		;	global	allsh
	global	asaland		;	global	asaland
	global	_sub_14F3	;	global	_sub_14F3
	global	shal		;	global	shal
	global	aland		;	global	aland
	global	allsh		;	global	allsh
	global	alsub		;	global	alsub
	global	asalor		;	global	asalor
	global 	csv		;	global 	csv

	psect	text

; Disassembled version		; After compiling C source code	
_sub_3A79:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	push	hl		;	push	hl
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	a,l		;	ld	a,l
	or	(ix+-1)		;	or	(ix+-1)
	jp	z,loc_3B3C	;	jp	z,l12
	ld	de,4		;	ld	de,4
	call	wrelop		;	call	wrelop
	jp	p,loc_3B3C	;	jp	p,l12
	ld	b,3		;	ld	b,3
	push	ix		;	push	ix
	pop	hl		;	pop	hl
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	call	asal		;	call	asal
	ld	b,(ix+-2)	;	ld	b,(ix+-2)
	ld	de,1		;	ld	de,1
	ld	hl,0		;	ld	hl,0
	call	allsh		;	call	allsh
	ex	de,hl		;	ex	de,hl
	ld	bc,0FFFFh	;	ld	bc,-1
	add	hl,bc		;	add	hl,bc
	ex	de,hl		;	ex	de,hl
	adc	hl,bc		;	adc	hl,bc
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	call	asaland		;	call	asaland
	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	1		;	cp	1
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9) 	;	ld	d,(ix+9)
	jr	nz,loc_3B42	;	jp	nz,L1
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	inc	hl		;	inc	hl
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	push	hl		;	push	hl
	push	de		;	push	de
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	dec	hl		;	dec	hl
	ld	b,l		;	ld	b,l
	ld	hl,1		;	ld	hl,1
	call	shal		;	call	shal
	ex	de,hl		;	ex	de,hl
	ld	a,d		;	ld	a,d
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	l,a		;	ld	l,a
	ld	h,a		;	ld	h,a
	call	aland		;	call	aland
	ld	a,e		;	ld	a,e
	or	d		;	or	d
	or	l		;	or	l
	or	h		;	or	h
	jr	z,loc_3B3C	;	jp	z,l12
	ld	b,(ix+-2)	;	ld	b,(ix+-2)
	ld	de,1		;	ld	de,1
	ld	hl,0		;	ld	hl,0
	call	allsh		;	call	allsh
	ex	de,hl		;	ex	de,hl
	ld	bc,0FFFFh	;	ld	bc,-1
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
	ld	hl,0FFFFh	;				; differs from 
	sbc	hl,bc		;			   <----+ original image
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	call	asalor		;	call	asalor
loc_3B3C:			;l12:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
loc_3B42:			;L1:
	ld	hl,17h 		;	ld	hl,23
	add	hl,de		;	add	hl,de
	ld	e,(iy+17h)	;	ld	e,(iy+23)
	ld	d,(iy+18h)	;	ld	d,(iy+24)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	hl,15h 		;	ld	hl,21
	add	hl,de		;	add	hl,de
	ld	e,(iy+15h)	;	ld	e,(iy+21)
	ld	d,(iy+16h)	;	ld	d,(iy+22)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	jp	cret		;	jp	cret

; End of function sub_3A79 OK+

; End of file 3A79.as


