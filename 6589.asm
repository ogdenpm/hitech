*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

	global	_sub_6589		;global	_sub_6589
	global	ncsv,cret,indir		;global	ncsv, cret, indir
	global	wrelop			;global	wrelop
	global	_array_AAE8		;global	_array_AAE8
	global	_array_AB54		;global	_array_AB54
	global	amul			;global	amul
	global 	csv			;

	psect	text

; Disassembled version		; After compiling C source code
_sub_6589:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	push	hl		;	push 	hl
	res	6,(ix+8)	;	res	6,(ix+8)
	ld	de,18h		;	ld	de,24
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	call	wrelop		;	call	wrelop
	jp	p,loc_65D5	;	jp	p,l12
	ld	de,_array_AAE8	;	ld	de,_array_AAE8
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	push	de		;	push	de
	ld	de,_array_AAE8	;	ld	de,_array_AAE8
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	a,(ix+6)	;	ld	a,(ix+6)
	and	c		;	and	c
	ld	l,a		;	ld	l,a
	ld	a,(ix+7)	;	ld	a,(ix+7)
	and	b		;	and	b
	ld	h,a		;	ld	h,a
	pop	de		;	pop	de
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	nz,loc_6656	;	jp	nz,L1
	ld	l,(ix+8)	;	ld	l,(ix+8)
	jp	cret		;	jp	cret
loc_65D5:			;l12:
	ld	de,0FFE8h	;	ld	de,-24
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	add	hl,de		;	add	hl,de
	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h
	ld	(ix+-1),6	;	ld	(ix+-1),6
	ld	de,6		;	ld	de,6
	call	amul		;	call	amul
	ld	de,_array_AB54	;	ld	de,_array_AB54
	add	hl,de		;	add	hl,de
	ld	(ix+-3),l	;	ld	(ix+-3),l
	ld	(ix+-2),h	;	ld	(ix+-2),h
loc_65F9:			;l16:
	ld	l,(ix+-3)	;	ld	l,(ix+-3)
	ld	h,(ix+-2)	;	ld	h,(ix+-2)
	ld	a,(hl)		;	ld	a,(hl)
	or	a		;	or	a
	jr	z,loc_663A	;	jp	z,l17
	ld	de,_array_AAE8	;	ld	de,_array_AAE8
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	push	de		;	push	de
	ld	de,_array_AAE8	;	ld	de,_array_AAE8
	ld	l,(ix+-3)	;	ld	l,(ix+-3)
	ld	h,(ix+-2)	;	ld	h,(ix+-2)
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	a,(ix+6)	;	ld	a,(ix+6)
	and	c		;	and	c
	ld	l,a		;	ld	l,a
	ld	a,(ix+7)	;	ld	a,(ix+7)
	and	b		;	and	b
	ld	h,a		;	ld	h,a
	pop	de		;	pop	de
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	ld	l,(ix+-3)	;	ld	l,(ix+-3)
	ld	h,(ix+-2)	;	ld	h,(ix+-2)
	jr	nz,loc_6640	;	jp	nz,L2
	ld	l,(hl)		;	ld	l,(hl)
	jp	cret		;	jp	cret
loc_663A:			;l17:
	ld	l,(ix+-3)	;	ld	l,(ix+-3)
	ld	h,(ix+-2)	;	ld	h,(ix+-2)
loc_6640:			;L2:
	inc	hl		;	inc	hl
	ld	(ix+-3),l	;	ld	(ix+-3),l
	ld	(ix+-2),h	;	ld	(ix+-2),h
	ld	a,(hl)		;	ld	a,(hl)
	or	a		;	or	a
	jr	z,loc_6656	;	jp	z,L1
	ld	a,(ix+-1)	;	ld	a,(ix+-1)
	add	a,0FFh		;	add	a,255
	ld	(ix+-1),a	;	ld	(ix+-1),a
	or	a		;	or	a
	jr	nz,loc_65F9	;	jp	nz,l16
loc_6656:			;L1:
	ld	l,0		;	ld	l,0
	jp	cret		;	jp	cret

; End of function sub_6589 OK++

	global	_sub_665B		;global	_sub_665B
	global	_array_AB24		;global	_array_AB24
	global	wrelop			;global	wrelop
	global csv			;

; Disassembled version		; After compiling C source code
_sub_665B:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	ld	a,(ix+6)	;	ld	a,(ix+6)
	or	(ix+7)		;	or	(ix+7)
	jr	nz,loc_666D	;	jp	nz,l21
loc_6667:			;L4:
	ld	hl,0		;	ld	hl,0
	jp	cret		;	jp	cret
loc_666D:			;l21:
	ld	a,(ix+8)	;	ld	a,(ix+8)
	add	a,0D0h		;	add	a,208
	ld	(ix+8),a	;	ld	(ix+8),a
	ld	(ix+-2),1	;	ld	(ix+-2),1
	ld	(ix+-1),0	;	ld	(ix+-1),0
	jr	loc_66AC	;	jp	l22
loc_667F:			;l23:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,0		;	ld	d,0
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,_array_AB24	;	ld	de,_array_AB24
	add	hl,de		;	add	hl,de
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	ld	e,(ix+6)	;	ld	e,(ix+6)
	ld	d,(ix+7)	;	ld	d,(ix+7)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	jp	z,cret		;	jp	z,cret
	inc	hl		;	inc	hl
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
loc_66AC:			;l22:
	ld	de,18h		;	ld	de,24
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	call	wrelop		;	call	wrelop
	jr	c,loc_667F	;	jp	c,l23
	jr	loc_6667	;	jp	L4

; End of function sub_665B OK++

	global	_sub_66BC		;global	_sub_66BC
	global	__ctype_		;global	__ctype_
	global	wrelop			;global	wrelop

;	Disassembled version	; After compiling C source code	;	Optimized version
_sub_66BC:
	call 	ncsv		;	call ncsv		;	call 	csv
	defw 	0FFFAh		;	defw -6			;	push 	hl
	ld	(ix+-4),0	;	ld	(ix+-4),0	;	push 	hl
	ld	(ix+-3),0	;	ld	(ix+-3),0	;
	xor	a		;	xor	a		;	xor	a
	ld	l,a		;	ld	l,a		;	ld	l,a
	ld	a,(ix+9)	;	ld	a,(ix+9)	;	ld	a,(ix+9)
	and	80h		;	and	128		;	and	128
	ld	h,a		;	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l		;	ld	a,l
	or	h		;	or	h		;	or	h
	ld	a,(ix+6)	;	ld	a,(ix+6)	;	ld	a,(ix+6)
	jp	z,loc_6757	;	jp	z,L17	;ok	;	jp	z,L13
	or	(ix+7)		;	or	(ix+7)		;	or	(ix+7)
	jr	nz,loc_66ED	;	jp	nz,l28	;ok	;	jp	nz,l13
				;				;L20:
	ld	l,(ix+8)	;	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)	;	ld	h,(ix+9)
loc_66E4:			;L23:			;m1:	;	jp	cret
	ld	(ix+-4),l	;	ld	(ix+-4),l	;
loc_66E7:			;			;m2:	;
	ld	(ix+-3),h	;	ld	(ix+-3),h	;
	jp	loc_6905	;	jp	l30	;ok	;
loc_66ED:			;l28:			;m3	;l13:
	ld	l,(ix+6)	;	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl		;	push	hl
	xor	a		;	xor	a		;	xor	a
	ld	l,a		;	ld	l,a		;	ld	l,a
	ld	a,(ix+9)	;	ld	a,(ix+9)	;	ld	a,(ix+9)
	and	80h		;	and	128		;	and	128
	ld	h,a		;	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l		;	ld	a,l
	or	h		;	or	h		;	or	h
	jr	nz,loc_6711	;	jp	nz,L16	;ok	;	jp	nz,L12
	ld	de,_array_AAE8	;	ld	de,_array_AAE8	;	ld	de,_array_AAE8
	ld	l,(ix+8)	;	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)	;	ld	h,(ix+9)
	add	hl,hl		;	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a		;	ld	l,a
	jr	loc_671D	;	jp	L15	;ok	;	jp	L11
loc_6711:			;L16:			;m4:	;L12:
	ld	e,(ix+8)	;	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	hl,0FFFFh	;	ld	hl,-1		;	ld	hl,-1
	or	a		;	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de		;	sbc	hl,de
loc_671D:			;L15:			;m5:	;L11:
	ld	a,l		;	ld	a,l		;	ld	a,l
	and	(ix+0Ah)	;	and	(ix+10)		;	and	(ix+10)
	ld	l,a		;	ld	l,a		;	ld	l,a
	ld	a,h		;	ld	a,h		;	ld	a,h
	and	(ix+0Bh)	;	and	(ix+11)		;	and	(ix+11)
	ld	h,a		;	ld	h,a		;	ld	h,a
	push	hl		;	push	hl		;	push	hl
	call	_sub_6589	;	call	_sub_6589	;	call	_sub_6589
	pop	bc		;	pop	bc		;	pop	bc
	pop	bc		;	pop	bc		;	pop	bc
	ld	e,l		;	ld	e,l		;	ld	e,l
	ld	h,0		;	ld	h,0		;	ld	h,0
	ld	(ix+-2),l	;	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	a,l		;	ld	a,l		;	ld	a,l
	or	h		;	or	(ix+-1)	;???	;	or	(ix+-1)
	jr	z,loc_673F	;	jp	z,l31	;ok	;	jp	z,l14
	ld	h,(ix+-1)	;	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	jr	loc_66E4	;	jp	L23	;ok	;	jp	cret
loc_673F:			;l31:			;m6:	;l14:
	ld	l,(ix+6)	;	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl		;	push	hl
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)	;	ld	h,(ix+11)
				;				;L16:
	push	hl		;	push	hl		;	push	hl
	call	_sub_6589	;	call	_sub_6589	;	call	_sub_6589
	pop	bc		;	pop	bc		;	pop	bc
	pop	bc		;	pop	bc		;	pop	bc
	ld	e,l		;	ld	e,l		;	ld	e,l
	ld	h,0		;	ld	h,0		;	ld	h,0
	jr	loc_66E4	;	jp	L23	;ok	;	jp	cret
loc_6757:	;m7:		;L17:			;m7:	;L13:
	or	(ix+7)		;	or	(ix+7)		;	or	(ix+7)
	ld	a,(ix+8)	;	ld	a,(ix+8)	;	ld	a,(ix+8)
	jp	nz,loc_6814	;	jp	nz,L18	;ok	;	jp	nz,L14
	or	(ix+9)		;	or	(ix+9)		;	or	(ix+9)
	jr	z,loc_676D	;	jp	z,L24	;ok	;	jp	z,L20
	ld	a,(ix+0Ch)	;	ld	a,(ix+12)	;	ld	a,(ix+12)
	or	(ix+0Dh)	;	or	(ix+13)		;	or	(ix+13)
	jr	nz,loc_6776	;	jp	nz,l33		;	jp	z,L20
				;				;	ld	l,(ix+12)
				;				;	ld	h,(ix+13)
				;				;	ld	(ix+-6),l
				;				;	ld	(ix+-5),h
				;				;	jp	l20
loc_676D:	;m9:		;L24:			;m9:	;
	ld	l,(ix+8)	;	ld	l,(ix+8)	;
	ld	h,(ix+9)	;	ld	h,(ix+9)	;
	jp	loc_66E4	;	jp	L23	;ok	;
loc_6776:	;m10		;l33:			;m10:	;
	ld	l,(ix+0Ch)	;	ld	l,(ix+12)	;
	ld	h,(ix+0Dh)	;	ld	h,(ix+13)	;
	ld	(ix+-6),l	;	ld	(ix+-6),l	;
	ld	(ix+-5),h	;	ld	(ix+-5),h	;
	jr	loc_6791	;	jp	l38	;ok	;
loc_6784:	;m11:		;l37:			;m11:	;l19:
	ld	l,(ix+-6)	;	ld	l,(ix+-6)	;	ld	l,(ix+-6)
	ld	h,(ix+-5)	;	ld	h,(ix+-5)	;	ld	h,(ix+-5)
	inc	hl		;	inc	hl		;	inc	hl
	ld	(ix+-6),l	;	ld	(ix+-6),l	;	ld	(ix+-6),l
	ld	(ix+-5),h	;	ld	(ix+-5),h	;	ld	(ix+-5),h
loc_6791:	;m12:		;l38:			;m12:	;l20:
	ld	l,(ix+-6)	;	ld	l,(ix+-6)	;	ld	l,(ix+-6)
	ld	h,(ix+-5)	;	ld	h,(ix+-5)	;	ld	h,(ix+-5)
	inc	hl		;	inc	hl		;	inc	hl
	ld	a,(hl)		;	ld	a,(hl)		;	ld	a,(hl)
	ld	e,a		;	ld	e,a		;	ld	e,a
	rla			;	rla			;	rla
	sbc	a,a		;	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a		;	ld	d,a
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de		;	add	hl,de
	bit	2,(hl)		;	bit	2,(hl)		;	bit	2,(hl)
	jr	nz,loc_6784	;	jp	z,l37	;ok	;	jp	z,l19
	ld	de,18h		;	ld	de,24		;	ld	de,24
	ld	l,(ix+8)	;	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)	;	ld	h,(ix+9)
	call	wrelop		;	call	wrelop		;	call	wrelop
	jp	m,loc_67DA	;	jp	m,loc_699D	;ok	;	jp	m,l25
	ld	l,(ix+8)	;	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl		;	push	hl
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)	;	ld	h,(ix+11)
	push	hl		;	push	hl		;	push	hl
	call	_sub_6589	;	call	_sub_6589	;	call	_sub_6589
	pop	bc		;	pop	bc		;	pop	bc
	pop	bc		;	pop	bc		;	pop	bc
	ld	e,l		;	ld	e,l		;	ld	e,l
	ld	h,0		;	ld	h,0		;	ld	h,0
	ld	(ix+8),l	;	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h	;	ld	(ix+9),h
	ld	a,l		;	ld	a,l		;	ld	a,l
	or	h		;	or	(ix+9)		;	or	(ix+9)
	jr	nz,loc_67DA ;-+	;	jp	z,L24	;ok	;	jp	z,L20
	ld	(ix+-4),h   ;	;				;
	jp	loc_66E7      ;	;				;
loc_67DA:	; m13:	<-----+	;loc_699D:			;m13:	;l25:
	ld	l,(ix+-6)	;	ld	l,(ix+-6)	;	ld	l,(ix+-6)
	ld	h,(ix+-5)	;	ld	h,(ix+-5)	;	ld	h,(ix+-5)
	ld	a,(hl)		;	ld	l,(hl)		;	ld	l,(hl)
	ld	l,a		;				;
	rla			;				;
	sbc	a,a		;				;
	ld	h,a		;				;
	push	hl		;	push	hl		;	push	hl
	ld	l,(ix+8)	;	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl		;	push	hl
	call	_sub_665B	;	call	_sub_665B	;	call	_sub_665B
	pop	bc		;	pop	bc		;	pop	bc
	pop	bc		;	pop	bc		;	pop	bc
	ld	(ix+8),l	;	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h	;	ld	(ix+9),h
	ld	e,(ix+0Ch)	;	ld	e,(ix+12)	;	ld	e,(ix+12)
	ld	d,(ix+0Dh)	;	ld	d,(ix+13)	;	ld	d,(ix+13)
	ld	l,(ix+-6)	;	ld	l,(ix+-6)	;	ld	l,(ix+-6)
	ld	h,(ix+-5)	;	ld	h,(ix+-5)	;	ld	h,(ix+-5)
	dec	hl		;	dec	hl		;	dec	hl
	ld	(ix+-6),l	;	ld	(ix+-6),l	;	ld	(ix+-6),l
	ld	(ix+-5),h	;	ld	(ix+-5),h	;	ld	(ix+-5),h
	inc	hl		;	inc	hl		;	inc	hl
	or	a		;	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_67DA	;	jp	nz,loc_699D	;ok	;	jp	nz,l25
	jp	loc_676D	;	jp	L24		;	jp	L20
loc_6814:			;L18:			;m14:	;L14:
	or	(ix+9)		;	or	(ix+9)		;	or	(ix+9)
	jr	nz,loc_6822	;	jp	nz,loc_6939	;ok	;	jp	nz,l26
loc_6819:			;loc_69E8:			;m15:	;L18:
	ld	l,(ix+6)	;	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)	;	ld	h,(ix+7)
	jp	loc_66E4	;	jp	L23	;ok	;	jp	cret
loc_6822:			;loc_6939:			;m16:	;l26:
	xor	a		;	xor	a		;	xor	a
	ld	l,a		;	ld	l,a		;	ld	l,a
	ld	a,(ix+9)	;	ld	a,(ix+9)	;	ld	a,(ix+9)
	and	80h		;	and	128		;	and	128
	ld	h,a		;	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l		;	ld	a,l
	or	h		;	or	h		;	or	h
	jr	nz,loc_683F	;	jp	nz,L12	;ok	;	jp	nz,L8
	ld	de,_array_AAE8	;	ld	de,_array_AAE8	;	ld	de,_array_AAE8
	ld	l,(ix+8)	;	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)	;	ld	h,(ix+9)
	add	hl,hl		;	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a		;	ld	l,a
	jr	loc_684B	;	jp	L11	;ok	;	jp	L7
loc_683F:			;L12:			;m17:	;L8:
	ld	e,(ix+8)	;	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	hl,0FFFFh	;	ld	hl,-1		;	ld	hl,-1
	or	a		;	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de		;	sbc	hl,de
loc_684B:			;L11:			;m18:	;L7:
	ex	de,hl		;	ex	de,hl		;	ex	de,hl
	push	de		;	push	de		;	push	de
	xor	a		;	xor	a		;	xor	a
	ld	l,a		;	ld	l,a		;	ld	l,a
	ld	a,(ix+7)	;	ld	a,(ix+7)	;	ld	a,(ix+7)
	and	80h		;	and	128		;	and	128
	ld	h,a		;	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l		;	ld	a,l
	or	h		;	or	h		;	or	h
	jr	nz,loc_686A	;	jp	nz,L10	;ok	;	jp	nz,L6
	ld	de,_array_AAE8	;	ld	de,_array_AAE8	;	ld	de,_array_AAE8
	ld	l,(ix+6)	;	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)	;	ld	h,(ix+7)
	add	hl,hl		;	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a		;	ld	l,a
	jr	loc_6876	;	jp	L9	;ok	;	jp	L5
loc_686A:			;L10:			;m19:	;L6:
	ld	e,(ix+6)	;	ld	e,(ix+6)	;	ld	e,(ix+6)
	ld	d,(ix+7)	;	ld	d,(ix+7)	;	ld	d,(ix+7)
	ld	hl,0FFFFh	;	ld	hl,-1		;	ld	hl,-1
	or	a		;	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de		;	sbc	hl,de
loc_6876:			;L9:			;m20:	;L5:
	pop	de		;	pop	de		;	pop	de
	ld	a,l		;	ld	a,l		;	ld	a,l
	and	e		;	and	e		;	and	e
	ld	l,a		;	ld	l,a		;	ld	l,a
	ld	a,h		;	ld	a,h		;	ld	a,h
	and	d		;	and	d		;	and	d
	ld	h,a		;	ld	h,a		;	ld	h,a
	ld	(ix+-2),l	;	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h	;	ld	(ix+-1),h
	xor	a		;	xor	a		;	xor	a
	ld	l,a		;	ld	l,a		;	ld	l,a
	ld	a,(ix+7)	;	ld	a,(ix+7)	;	ld	a,(ix+7)
	and	80h		;	and	128		;	and	128
	ld	h,a		;	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l		;	ld	a,l
	or	h		;	or	h		;	or	h
	jr	nz,loc_68A0	;	jp	nz,L8	;ok	;	jp	nz,L4
	ld	de,_array_AAE8	;	ld	de,_array_AAE8	;	ld	de,_array_AAE8
	ld	l,(ix+6)	;	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)	;	ld	h,(ix+7)
	add	hl,hl		;	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a		;	ld	l,a
	jr	loc_68AC	;	jp	L7	;ok	;	jp	L3
loc_68A0:			;L8:			;m21:	;L4:
	ld	e,(ix+6)	;	ld	e,(ix+6)	;	ld	e,(ix+6)
	ld	d,(ix+7)	;	ld	d,(ix+7)	;	ld	d,(ix+7)
	ld	hl,0FFFFh	;	ld	hl,-1		;	ld	hl,-1
	or	a		;	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de		;	sbc	hl,de
loc_68AC:			;L7:			;m22:	;L3:
	ld	e,(ix+-2)	;	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	or	a		;	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de		;	sbc	hl,de
	jp	z,loc_6819	;	jp	z,loc_69E8	;ok	;	jp	z,L18
	xor	a		;	xor	a		;	xor	a
	ld	l,a		;	ld	l,a		;	ld	l,a
	ld	a,(ix+9)	;	ld	a,(ix+9)	;	ld	a,(ix+9)
	and	80h		;	and	128		;	and	128
	ld	h,a		;	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l		;	ld	a,l
	or	h		;	or	h		;	or	h
	jr	nz,loc_68D5	;	jp	nz,L6	;ok	;	jp	nz,L2
	ld	de,_array_AAE8	;	ld	de,_array_AAE8	;	ld	de,_array_AAE8
	ld	l,(ix+8)	;	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)	;	ld	h,(ix+9)
	add	hl,hl		;	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a		;	ld	l,a
	jr	loc_68E1	;	jp	L5	;ok	;	jp	L1
loc_68D5:			;L6:			;m23:	;L2:
	ld	e,(ix+8)	;	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	hl,0FFFFh	;	ld	hl,-1		;	ld	hl,-1
	or	a		;	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de		;	sbc	hl,de
loc_68E1:			;L5:			;m24:	;L1:
	ld	e,(ix+-2)	;	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	or	a		;	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de		;	sbc	hl,de
	jp	z,loc_676D	;	jp	z,L24	;ok	;	jp	z,L20
	ld	l,(ix+6)	;	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl		;	push	hl
	ld	l,e		;	ld	l,e		;	ld	l,e
	ld	h,d		;	ld	h,d		;	ld	h,d
	push	hl		;	push	hl		;	jp	L16
	call	_sub_6589	;	call	_sub_6589	;
	pop	bc		;	pop	bc		;
	pop	bc		;	pop	bc		;
	ld	e,l		;	ld	e,l		;
	ld	h,0		;	ld	h,0		;
	ld	(ix+-4),l	;	ld	(ix+-4),l	;
	ld	(ix+-3),h	;	ld	(ix+-3),h	;
loc_6905:			;l30:			;m25:	;
	ld	l,(ix+-4)	;	ld	l,(ix+-4)	;
	ld	h,(ix+-3)	;	ld	h,(ix+-3)	;
	jp	cret		;	jp	cret		;

; End of function sub_66BC OK+


; End of file sub_6589.as


