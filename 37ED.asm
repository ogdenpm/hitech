*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 37ED.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_37ED OK++
;=========================================================
	global	_sub_37ED	;	global	_sub_37ED
	global ncsv,cret,indir	;	global	ncsv, cret, indir
	global	aslr		;	global	aslr
	global	csv		;	global	csv

	psect	text

_sub_37ED:
; Disassembled version		; After compiling C source code
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(iy+17h)	;	ld	l,(iy+23)
	ld	h,(iy+18h)	;	ld	h,(iy+24)
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	a,(iy+15h)	;	ld	a,(iy+21)
	or	(iy+16h)	;	or	(iy+22)
	jr	z,loc_3827	;	jp	z,l13
	ld	b,2		;	ld	b,2
	push	iy		;	push	iy
	pop	de		;	pop	de
	ld	hl,15h		;	ld	hl,21
	add	hl,de		;	add	hl,de
	call	aslr		;	call	aslr
	jp	cret		;	jp	cret
loc_381D:			;L1:
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-2),c	;	ld	(ix+-2),c
	ld	(ix+-1),b	;	ld	(ix+-1),b
loc_3827:			;l13:
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,0Dh		;	ld	hl,13
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	or	(hl)		;	or	(hl)
	ld	hl,0Fh		;	ld	hl,15
	jr	z,loc_381D	;	jp	z,L1
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+17h),c	;	ld	(iy+23),c
	ld	(iy+18h),b	;	ld	(iy+24),b
	ld	hl, 0Dh		;	ld	hl,13
	add	hl, de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	srl	b		;	srl	b
	rr	c		;	rr	c
	srl	b		;	srl	b
	rr	c		;	rr	c
	ld	(iy+15h),c	;	ld	(iy+21),c
	ld	(iy+16h),b	;	ld	(iy+22),b
	jp	cret		;	jp	cret

; End of function sub_37ED OK++

; End of file 37ED.as
