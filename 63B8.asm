*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

	global	_sub_63B8		;global	_sub_63B8
	global	ncsv, cret, indir	;global	ncsv, cret, indir
	global	_sub_6589		;global	_sub_6589
	global	_array_AAE8		;global	_array_AAE8
	global	wrelop			;global	wrelop
	global	_array_AB54		;global	_array_AB54
	global	amul			;global	amul
	global 	csv

	psect	text

;	Disassembled version	; After compiling C source code
_sub_63B8:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	push	hl		;	push 	hl
	res	6,(ix+0Ah)	;	res	6,(ix+10)
	ld	(ix+-1),0	;	ld	(ix+-1),0
	ld	a,(ix+8)	;	ld	a,(ix+8)
	or	(ix+9)		;	or	(ix+9)
	jr	nz,loc_63E7	;	jp	nz,l12
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	push	hl		;	push	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
loc_63DA:			;L7:
	push	hl		;	push	hl
	call	_sub_6589	;	call	_sub_6589
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	e,l		;	ld	e,l
	ld	(ix+-1),e	;	ld	(ix+-1),e
	jp	loc_6583	;	jp	l13
loc_63E7:			;l12:
	xor	a		;	xor	a
	ld	l,a		;	ld	l,a
	ld	a,(ix+9)	;	ld	a,(ix+9)
	and	80h		;	and	128
	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	z,loc_642F	;	jp	z,l14
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	push	hl		;	push	hl
	xor	a		;	xor	a
	ld	l,a		;	ld	l,a
	ld	a,(ix+9)	;	ld	a,(ix+9)
	and	80h		;	and	128
	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	nz,loc_6417	;	jp	nz,L6
	ld	de,_array_AAE8	;	ld	de,_array_AAE8
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	jr	loc_6423	;	jp	L5
loc_6417:			;L6:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	hl,-1		;	ld	hl,-1
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
loc_6423:			;L5:
	ld	a,l		;	ld	a,l
	and	(ix+6)		;	and	(ix+6)
	ld	l,a		;	ld	l,a
	ld	a,h		;	ld	a,h
	and	(ix+7)		;	and	(ix+7)
	ld	h,a		;	ld	h,a
	jr	loc_63DA	;	jp	L7
loc_642F:			;l14:
	ld	de,18h		;	ld	de,24
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	call	wrelop		;	call	wrelop
	jp	p,loc_64EB	;	jp	p,l16
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	push	hl		;	push	hl
	xor	a		;	xor	a
	ld	l,a		;	ld	l,a
	ld	a,(ix+9)	;	ld	a,(ix+9)
	and	80h		;	and	128
	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	nz,loc_6462	;	jp	nz,L4
	ld	de,_array_AAE8	;	ld	de,_array_AAE8
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	jr	loc_646E	;	jp	L3
loc_6462:			;L4:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	hl,-1		;	ld	hl,-1
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
loc_646E:			;L3:
	ld	a,l		;	ld	a,l
	and	(ix+6)		;	and	(ix+6)
	ld	l,a		;	ld	l,a
	ld	a,h		;	ld	a,h
	and	(ix+7)		;	and	(ix+7)
	ld	h,a		;	ld	h,a
	push	hl		;	push	hl
	call	_sub_6589	;	call	_sub_6589
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	ld	(ix+-1),a	;	ld	(ix+-1),a
	or	a		;	or	a
	jp	nz,loc_6583	;	jp	nz,l13
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	push	hl		;	push	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	call	_sub_6589	;	call	_sub_6589
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	e,l		;	ld	e,l
	ld	h,0		;	ld	h,0
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jp	z,loc_6583	;	jp	z,l13
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	xor	a		;	xor	a
	ld	l,a		;	ld	l,a
	ld	a,(ix+-3)	;	ld	a,(ix+-3)
	and	80h		;	and	128
	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	nz,loc_64CB	;	jp	nz,L2
	ld	de,_array_AAE8	;	ld	de,_array_AAE8
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	jr	loc_64D7	;	jp	L1
loc_64CB:			;L2:
	ld	e,(ix+-4)	;	ld	e,(ix+-4)
	ld	d,(ix+-3)	;	ld	d,(ix+-3)
	ld	hl,-1		;	ld	hl,-1
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
loc_64D7:	; m9:		;L1:
	push	hl		;	push	hl
	call	_sub_6589	;	call	_sub_6589
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	or	a		;	or	a
	jp	z,loc_6583	;	jp	z,l13
	ld	a,(ix+-4)	;	ld	a,(ix+-4)
loc_64E5:			;
	ld	(ix+-1),a	;	ld	(ix+-1),a
	jp	loc_6583	;	jp	l13
loc_64EB:			;l16:
	ld	(ix+-4),6	;	ld	(ix+-4),6
	ld	(ix+-3),0	;	ld	(ix+-3),0
	ld	e,(ix+0Ah)	;	ld	e,(ix+10)
	ld	d,(ix+0Bh)	;	ld	d,(ix+11)
	ld	hl,0FFE8h	;	ld	hl,-24
	add	hl,de		;	add	hl,de
	ld	de,6		;	ld	de,6
	call	amul		;	call	amul
	ld	de,_array_AB54	;	ld	de,_array_AB54
	add	hl,de 		;	add	hl,de
	push	hl		;	push	hl
	pop	iy		;	pop	iy
loc_650A:	; m12		;l21:
	ld	a,(iy+0)	;	ld	a,(iy+0)
	or	a		;	or	a
	jr	nz,loc_6571	;	jp	z,l13
	jr	loc_6583	;	ld	l,(ix+-4)
				;	ld	h,(ix+-3)
				;	dec	hl
				;	ld	(ix+-4),l
				;	ld	(ix+-3),h
				;	inc	hl
				;	ld	a,l
				;	or	h
loc_6512:			;	jp	z,l13
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	inc	hl		;	inc	hl
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	dec	hl		;	dec	hl
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	push	hl		;	push	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	call	_sub_6589	;	call	_sub_6589
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	ld	(ix+-2),a	;	ld	(ix+-2),a
	or	a		;	or	a
	jr	z,loc_650A	;	jp	z,l21
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	ld	de,_array_AAE8	;	ld	de,_array_AAE8
	ld	l,a		;	ld	l,a
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	call	_sub_6589	;	call	_sub_6589
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	or	a		;	or	a
	jr	nz,loc_656B	;	jp	nz,l24
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,0		;	ld	h,0
	push	hl		;	push	hl
	ld	de,_array_AAE8	;	ld	de,_array_AAE8
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	call	_sub_6589	;	call	_sub_6589
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	or	a		;	or	a
	jr	z,loc_650A	;	jp	z,l21
loc_656B:			;l24:
	ld	a,(ix+-2)	;	ld	a,(ix+-2)
	jp	loc_64E5	;	ld	(ix+-1),a
loc_6571:			;
	ld	l,(ix+-4)	;
	ld	h,(ix+-3)	;
	dec	hl		;
	ld	(ix+-4),l	;
	ld	(ix+-3),h	;
	inc	hl		;
	ld	a,l		;
	or	h		;
	jr	nz,loc_6512	;
loc_6583:			;l13:
	ld	l,(ix+-1)	;	ld	l,(ix+-1)
	jp	cret		;	jp	cret

; Location code snippets differs, but the program is logically correct

; End of function sub_63B8 OK+

; End of file sub_63B8.as


