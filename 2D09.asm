*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 2D09.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_2D09 OK
;=========================================================
	global	_sub_2D09	;	global	_sub_2D09
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_putchar	;	global	_putchar
	global	__ctype_	;	global	__ctype_
	global	_atoi		;	global	_atoi
	global	wrelop		;	global	wrelop
	global	_array_80EF	;	global	_array_80EF
	global	amul		;	global	amul
	global	_sub_153A	;	global	_sub_153A
	global	_sub_387A	;	global	_sub_387A
	global	_word_AFF8	;	global	_word_AFF8
	global	lladd		;	global	lladd
	global	_printf		;	global	_printf
	global	_sub_46F7	;	global	_sub_46F7
				;	global	llsub
	global	_array_AB24	;	global	_array_AB24
	global	_off_AACA	;	global	_off_AACA
	global	_array_805F	;	global	_array_805F
	global	_sub_2CE0	;	global	_sub_2CE0
	global	aslladd		;	global	aslladd
	global	_sub_14F3	;	global	_sub_14F3
	global	_nodesize	;	global	_nodesize
	global	shal		;	global	shal		
	global	aslland		;	global	aslland
	global	alrsh		;	global	alrsh
	global	_word_AFFB	;	global	_word_AFFB
	global	_dopetab	;	global	_dopetab

	psect	text

; Disassembled version		; After compiling C source code	
_sub_2D09:
	call	ncsv		;	call 	ncsv
	defw	-25		;	defw 	-25
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	(ix+-20),l	;	ld	(ix+-20),l
	ld	(ix+-19),h	;	ld	(ix+-19),h
	ld	a,0		;	ld	a,0
	ld	(ix+-25),a	;	ld	(ix+-25),a
	ld	(ix+-18),a	;	ld	(ix+-18),a
loc_2D2B:			;l12:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h
	ld	(ix+-10),a	;	ld	(ix+-10),a
	or	a		;	or	a
	jp	z,cret		;	jp	z,cret
	cp	0Ah ;	'\n'	;	cp	10
	jp	z, loc_2DDC	;	jp	z,l17
	cp	0Dh		;	cp	13
	jp	z, loc_2DDC	;	jp	z,l17
	cp	20h ;	' '	;	cp	32
	jp	z, loc_2DC7	;	jp	z,l18
	cp	3Bh ;	';'	;	cp	59
	jp	z, cret		;	jp	z,cret
	cp	41h ;	'A'	;	cp	65
	jp	z, loc_2EA8	;	jp	z,l35
	cp	42h ;	'B'	;	cp	66
	jp	z, loc_2EA8	;	jp	z,l35
	cp	43h ;	'C'	;	cp	67
	jp	z, loc_2EA8	;	jp	z,l35
	cp	44h ;	'D'	;	cp	68
	jp	z, loc_2FBC	;	jp	z,l60
	cp	46h ;	'F'	;	cp	70
	jp	z, loc_2EA8	;	jp	z,l35
	cp	47h ;	'G'	;	cp	71
	jp	z, loc_2DEB	;	jp	z,l51
	cp	4Ch ;	'L'	;	cp	76
	jp	z, loc_2FA3	;	jp	z,l59
	cp	4Dh ;	'M'	;	cp	77
	jp	z, loc_2EA8	;	jp	z,l35
	cp	4Fh ;	'O'	;	cp	79
	jp	z, loc_2EA8	;	jp	z,l35
	cp	50h ;	'P'	;	cp	80
	jp	z, loc_2EA8	;	jp	z,l35
	cp	51h ;	'Q'	;	cp	81
	jp	z, loc_2EA8	;	jp	z,l35
	cp	52h ;	'R'	;	cp	82
	jp	z, loc_2FA3	;	jp	z,l59
	cp	53h ;	'S'	;	cp	83
	jp	z, loc_2EA8	;	jp	z,l35
	cp	54h ;	'T'	;	cp	84
	jp	z, loc_2EA8	;	jp	z,l35
	cp	55h ;	'U'	;	cp	85
	jp	z, loc_2FA3	;	jp	z,l59
	cp	56h ;	'V'	;	cp	86
	jp	z, loc_2EA8	;	jp	z,l35
	cp	57h ;	'W'	;	cp	87
	jp	z, loc_2EA8	;	jp	z,l35
	cp	58h ;	'X'	;	cp	88
	jp	z, loc_2DEB	;	jp	z,l51
	cp	5Ah ;	'Z'	;	cp	90
	jp	z, loc_2EA8	;	jp	z,l35
	cp	7Eh ;	'~'	;	cp	126
	jp	z, loc_2EA8	;	jp	z,l35
loc_2DB8:			;L19:
	ld	a,(ix+-10)	;	ld	a,(ix+-10)
	ld	l,a		;	ld	l,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	push	hl		;	push	hl
	call	_putchar	;	call	_putchar
loc_2DC3:			;L38:
	pop	bc		;	pop	bc
	jp	loc_2D2B	;	jp	l12
;
;	case ' ':
;
loc_2DC7:			;l18:
	ld	a,(ix+-25)	;	ld	a,(ix+-25)
	or	a		;	or	a
	jr	nz,loc_2DB8	;	jp	nz,L18
	ld	hl,9		;	ld	hl,9
	push	hl		;	push	hl
	call	_putchar	;	call	_putchar
	pop	bc		;	pop	bc
	ld	(ix+-25),1	;	ld	(ix+-25),1
	jp	loc_2D2B	;	jp	l12
;
;	case '\n': 0d:
;
loc_2DDC:			;l17:
	ld	hl,0Ah		;	ld	hl,10
	push	hl		;	push	hl
	call	_putchar	;	call	_putchar
	pop	bc		;	pop	bc
	ld	(ix+-25),0	;	ld	(ix+-25),0
	jp	loc_2D2B	;	jp	l12
;
;	case 'G'
;
loc_2DEB:			;l51:				; m5:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	a,(hl)		;	ld	a,(hl)
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de
	bit	2,(hl)		;	bit	2,(hl)
	jr	z,loc_2E2E	;	jp	z,l52
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	(ix+-6),l	;	ld	(ix+-6),l
	ld	(ix+-5),h	;	ld	(ix+-5),h
	jr	loc_2E19	;	jp	l53
loc_2E0C:			;l54:				; m6:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	inc	hl		;	inc	hl
	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h
loc_2E19:	; m7:		;l53:				; m7:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	a,(hl)		;	ld	a,(hl)
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de
	bit	2,(hl)		;	bit	2,(hl)
	jr	nz,loc_2E0C	;	jp	nz,l54
	jr	loc_2E36	;	jp	l56
loc_2E2E:	; m8:		;l52:				; m8:
	ld	(ix+-6),0	;	ld	(ix+-6),0
	ld	(ix+-5),0	;	ld	(ix+-5),0
loc_2E36:	; m9:		;l56:				; m9:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h
	ld	(ix+-9),a	;	ld	(ix+-9),a
	ld	(ix+-12),47h	;	ld	(ix+-12),71
	ld	(ix+-11),0	;	ld	(ix+-11),0
				;	jp	l63
loc_2E4F:	; m10:		;l63:				; m10
	ld	a,(ix+-9)	;	ld	a,(ix+-9)
	cp	4Ch		;	cp	76
	jp	z,loc_2FC4	;	jp	z,l64
	cp	4Eh		;	cp	78
	jp	z,loc_3029	;	jp	z,l68
	cp	52h		;	cp	82
	jp	z,loc_3021	;	jp	z,l69
loc_2E61:	; m11:		;l71:			; m11
	ld	a,(ix+-10)	;	ld	a,(ix+-10)
	cp	41h		;	cp	65
	jp	z,loc_31E6	;	jp	z,l72
	cp	42h		;	cp	66
	jp	z,loc_314D	;	jp	z,l73
	cp	43h		;	cp	67
	jp	z,loc_3347	;	jp	z,l78
	cp	44h		;	cp	68
	jp	z,loc_303B	;	jp	z,l82
	cp	46h		;	cp	70
	jp	z,loc_311D	;	jp	z,l84
	cp	47h		;	cp	71
	jp	z,loc_3457	;	jp	z,l87
	cp	4Fh		;	cp	79
	jp	z,loc_31CA	;	jp	z,l93
	cp	53h		;	cp	83
	jp	z,loc_3056	;	jp	z,l94
	cp	54h		;	cp	84
	jp	z,loc_33D6	;	jp	z,l105
	cp	56h		;	cp	86
	jp	z,loc_31F3	;	jp	z,l109
	cp	58h		;	cp	88
	jp	z,loc_3457	;	jp	z,l87
	cp	5Ah		;	cp	90
	jp	z,loc_3130	;	jp	z,l121
	cp	7Eh		;	cp	126
	jp	z,loc_34F8	;	jp	z,l122
	jp	loc_2D2B	;	jp	l12
;
;	case 'A'
;
loc_2EA8:	; m12:		;l35:
	ld	de,2Dh		;	ld	de,45
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	a,(hl)		;	ld	a,(hl)
	ld	l,a		;	ld	l,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	ld	(ix+-12),l	;	ld	(ix+-12),l
	ld	(ix+-11),h	;	ld	(ix+-11),h
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	z,loc_2ED0	;	jp	z,L9
	ld	de,2Bh		;	ld	de,43
	ld	l,(ix+-12)	;	ld	l,(ix+-12)
	ld	h,(ix+-11)	;	ld	h,(ix+-11)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	nz,loc_2F52	;	jp	nz,l36
loc_2ED0:			;L9:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	inc	hl		;	inc	hl
	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h
	ld	a,(hl)		;	ld	a,(hl)
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de
	bit	2,(hl)		;	bit	2,(hl)
	jp	z,loc_2F19	;	jp	z,l37
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	call	_atoi		;	call	_atoi
	pop	bc		;	pop	bc
	ld	(ix+-8),l	;	ld	(ix+-8),l
	ld	de,2Dh		;	ld	de,45
	ld	l,(ix+-12)	;	ld	l,(ix+-12)
	ld	h,(ix+-11)	;	ld	h,(ix+-11)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_2F0F	;	jp	nz,l38
	ld	a,(ix+-8)	;	ld	a,(ix+-8)
	neg			;	neg
	ld	(ix+-8),a	;	ld	(ix+-8),a
loc_2F0F:			;l38:
	ld	(ix+-12),0	;	ld	(ix+-12),0
	ld	(ix+-11),0	;	ld	(ix+-11),0
	jr	loc_2F2C	;	jp	l40
loc_2F19:			;l37:
	ld	(ix+-8),0	;	ld	(ix+-8),0
	jr	loc_2F2C	;	jp	l40
loc_2F1F:			;l41:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
loc_2F25:			;L11:
	inc	hl		;	inc	hl
	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h
loc_2F2C:			;l40:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	a,(hl)		;	ld	a,(hl)
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de
	bit	2,(hl)		;	bit	2,(hl)
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	jr	nz,loc_2F25	;	jp	nz,L11
	ld	a,(hl)		;	ld	a,(hl)
	cp	2Bh		;	cp	43
	jr	z,loc_2F25	;	jp	z,L11
	ld	a,(hl)		;	ld	a,(hl)
	cp	2Dh		;	cp	45
	jr	z,loc_2F1F	;	jp	z,l41
	jp	loc_2F8F	;	jp	l43
loc_2F52:			;l36:
	ld	de,3Eh		;	ld	de,62
	ld	l,(ix+-12)	;	ld	l,(ix+-12)
	ld	h,(ix+-11)	;	ld	h,(ix+-11)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_2F83	;	jp	nz,l44
	ld	(ix+-8),0	;	ld	(ix+-8),0
	jr	loc_2F76	;	jp	l48
loc_2F66:			;l47:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	inc	hl		;	inc	hl
	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h
	inc	(ix+-8)		;	inc	(ix+-8)
loc_2F76:			;l48:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	a,(hl)		;	ld	a,(hl)
	cp	3Eh		;	cp	62
	jr	z,loc_2F66	;	jp	z,l47
	jr	loc_2F8F	;	jp	l43
loc_2F83:			;l44:
	ld	(ix+-12),0	;	ld	(ix+-12),0
	ld	(ix+-11),0	;	ld	(ix+-11),0
	ld	(ix+-8),0	;	ld	(ix+-8),0
loc_2F8F:			;l43:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h
	ld	(ix+-9),a	;	ld	(ix+-9),a
	jp	loc_2E4F	;	(jp 	l63)
;
;	case 'L'
;
loc_2FA3:			;l59:
	ld	a,(ix+-10)	;	ld	a,(ix+-10)
	ld	(ix+-9),a	;	ld	(ix+-9),a
	ld	(ix+-10),7Eh	;	ld	(ix+-10),126
loc_2FAD:			;L20:
	ld	(ix+-12),0	;	ld	(ix+-12),0
	ld	(ix+-11),0	;	ld	(ix+-11),0
	ld	(ix+-8),0	;	ld	(ix+-8),0
	jp	loc_2E4F	;	jp	l63
;
;	case 'D':
;
loc_2FBC:			;l60:
	ld	a,(ix+-10)	;	ld	a,(ix+-10)
	ld	(ix+-9),a	;	ld	(ix+-9),a
	jr	loc_2FAD	;	jp	L20

loc_2FC4:	; m27		;l64:			; m27
	ld	a,(ix+10)	;	ld	a,(ix+10)
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,0		;	ld	hl,0
	call	wrelop		;	call	wrelop
	jp	p,loc_3006	;	jp	p,l65
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	push	iy		;
	pop	de		;
	ld	a,(ix+10)	;	ld	a,(ix+10)
	add	a,-1		;	add	a,255
	ld	(ix+-17),a	;	ld	(ix+-17),a
				;l66:
				;	ld	e,(ix+-4)
				;	ld	d,(ix+-3)
				;	ld	a,(ix+-17)
loc_2FE8:	;m28		;
	ld	l,a		;	ld	l,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	add	hl,de		;	add	hl,de
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	ld	de,0Ah		;	ld	de,10
	call	amul		;	call	amul
	ld	de,_array_80EF	;	ld	de,_array_80EF
	add	hl,de		;	add	hl,de
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	jp	loc_2E61	;	jp	l71
loc_3006:			;l65:
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
loc_300C:			;
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
				;l67:
				;	ld	l,(ix+-4)
				;	ld	h,(ix+-3)
	inc	hl		;	inc	hl
	ld	a,(hl)		;	ld	a,(hl)
	add	a,-1		;	add	a,255
	ld	(ix+-17),a	;	ld	(ix+-17),a
				;	jp	l66
				;
	ld	e,(ix+-4)	;
	ld	d,(ix+-3)	;
	jr	loc_2FE8	;
loc_3021:			;l69:
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	jr	loc_300C	;	ld	(ix+-4),l
				;	ld	(ix+-3),h
				;	jp	l67
loc_3029:			;l68:
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	ld	a,(ix+10)	;	ld	a,(ix+10)
	ld	(ix+-17),a	;	ld	(ix+-17),a
	jp	loc_2E61	;	jp	l71
loc_303B:			;l82:
	ld	hl,(_word_AFF8)	;	ld	hl,(_word_AFF8)
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jp	z,loc_2D2B	;	jp	z,l12
	push	hl		;	push	hl
	ld	hl,19f	;"%d"	;	ld	hl,39f	;"%d"
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	hl,0		;	ld	hl,0
				;	jp	L24
loc_3050:			;L24:
	ld	(_word_AFF8),hl	;	ld	(_word_AFF8),hl
	jp	loc_2D2B	;	jp	l12
loc_3056:			;l94:
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	ld	a,(hl)		;	ld	a,(hl)
	cp	45h		;	cp	69
	jr	nz,loc_307F	;	jp	nz,l95
	ex	de,hl		;	ex	de,hl
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	add	hl,hl		;	add	hl,hl
	ld	de,_off_AACA	;	ld	de,_off_AACA
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	hl,29f	;"%s"	;	ld	hl,79f
				;	jp	L25
				;L25:
	push	hl		;	push	hl
	call	_printf		;	call	_printf
loc_307A:			;L32:
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	jp	loc_30D5	;	jp	l85
loc_307F:			;l95:
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	ld	a,(hl)		;	ld	a,(hl)
	cp	43h		;	cp	67
	jr	nz,loc_30A6	;	jp	nz,l97
	ex	de,hl		;	ex	de,hl
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
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	push	hl		;	push	hl
	call	_sub_2CE0	;	call	_sub_2CE0
	pop	bc		;	pop	bc
	jr	loc_307A	;	jp	L32
loc_30A6:			;l97:
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	ld	a,(hl)		;	ld	a,(hl)
	cp	44h		;	cp	68
	ex	de,hl		;	ex	de,hl
	ld	hl,19h		;	ld	hl,25
	jr	nz,loc_30C3	;	jp	nz,L15
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	hl,39f		;	ld	hl,89f
loc_30BD:			;
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	jr	loc_307A	;	jp	L32
loc_30C3:			;L15:
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	hl,49f		;	ld	hl,99f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
loc_30D5:	m39:		;l85:
	ld	a,(ix+-12)	;	ld	a,(ix+-12)
	or	(ix+-11)	;	or	(ix+-11)
	jp	nz,loc_2D2B	;	jp	nz,l12
	ld	a,(_word_AFF8)	;	ld	a,(_word_AFF8)
	ld	e,a		;	ld	e,a
	ld	a,(ix+-8)	;	ld	a,(ix+-8)
	add	a,e		;	add	a,e
	ld	(ix+-8),a	;	ld	(ix+-8),a
	ld	hl,0		;	ld	hl,0
	ld	(_word_AFF8),hl	;	ld	(_word_AFF8),hl
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
				;	ld	hl,(_word_AFF8)
	call	wrelop		;	call	wrelop
	ld	a,(ix+-8)	;	ld	a,(ix+-8)
	jp	p,loc_310C	;	jp	p,L16
	ld	l,a		;	ld	l,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	push	hl		;	push	hl
	ld	hl,59f		;	ld	hl,109f
				;	jp	L46
loc_3104:			;L46:
	push	hl		;	push	hl
	call	_printf		;	call	_printf
				;	jp	L42
loc_3108:			;L42:
	pop	bc		;	pop	bc
	jp	loc_2DC3	;	jp	L38
loc_310C:			;L16:
	or	a		;	or	a
	jp	p,loc_2D2B	;	jp	p,l12
	ld	a,(ix+-8)	;	ld	a,(ix+-8)
	ld	l,a		;	ld	l,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	push	hl		;	push	hl
	ld	hl,69f		;	ld	hl,119f
	jr	loc_3104	;	jp	L46
loc_311D:			;l84:
	ld	e,(ix+-4)	;	ld	e,(ix+-4)
	ld	d,(ix+-3)	;	ld	d,(ix+-3)
	ld	hl,1Bh	;27	;	ld	hl,27
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	hl,79f		;	ld	hl,49f
	jr	loc_30BD	;
				;
loc_3130:			;l121:
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	push	hl		;	push	hl
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ex	de,hl		;	ex	de,hl
	ld	hl,0		;	ld	hl,0
	ld	(ix+-16),e	;	ld	(ix+-16),e
	ld	(ix+-15),d	;	ld	(ix+-15),d
	ld	(ix+-14),l	;	ld	(ix+-14),l
	ld	(ix+-13),h	;	ld	(ix+-13),h
	jr	loc_3168	;	jp	l74
loc_314D:			;l73:
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	push	hl		;	push	hl
	call	_sub_387A	;	call	_sub_387A
	pop	bc		;	pop	bc
	ex	de,hl		;	ex	de,hl
	ld	hl,0		;	ld	hl,0
	ld	(ix+-16),e	;	ld	(ix+-16),e
	ld	(ix+-15),d	;	ld	(ix+-15),d
	ld	(ix+-14),l	;	ld	(ix+-14),l
	ld	(ix+-13),h	;	ld	(ix+-13),h
loc_3168:			;l74:
	ld	de,2Dh		;	ld	de,45
	ld	l,(ix+-12)	;	ld	l,(ix+-12)
	ld	h,(ix+-11)	;	ld	h,(ix+-11)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	nz,loc_31B1	;	jp	nz,l75
	ld	a,(ix+-18)	;	ld	a,(ix+-18)
	or	a		;	or	a
	jp	nz,loc_324D	;
	ld	e,(ix+-16)	;	ld	e,(ix+-16)
	ld	d,(ix+-15)	;	ld	d,(ix+-15)
	ld	l,(ix+-14)	;	ld	l,(ix+-14)
	ld	h,(ix+-13)	;	ld	h,(ix+-13)
	push	hl		;	push	hl
	push	de		;	push	de
				;	jp	nz,L22
	ld	de,(_word_AFF8)	;	ld	de,(_word_AFF8)
	ld	a,d		;	ld	a,d
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	l,a		;	ld	l,a
	ld	h,a		;	ld	h,a
	call	lladd		;	call	lladd
	ld 	(ix+-24),e	;	ld	(ix+-24),e
	ld	(ix+-23),d	;	ld	(ix+-23),d
	ld	(ix+-22),l	;	ld	(ix+-22),l
	ld	(ix+-21),h	;	ld	(ix+-21),h
	ld	hl,0		;	ld	hl,0
	ld	(_word_AFF8),hl	;	ld	(_word_AFF8),hl
	ld	(ix+-18),1	;	ld	(ix+-18),1
	jp	loc_324D	;	jp	l77
loc_31B1:			;l75:
	ld	e,(ix+-16)	;	ld	e,(ix+-16)
	ld	d,(ix+-15)	;	ld	d,(ix+-15)
	ld	l,(ix+-14)	;	ld	l,(ix+-14)
	ld	h,(ix+-13)	;	ld	h,(ix+-13)
	push	hl		;	push	hl
	push	de		;	push	de
				;L22:
	ld	hl,89f	;"%lu"	;	ld	hl,19f	;"%lu"
	push	hl		;	push	hl
	call	_printf		;	call	_printf
				;	pop	bc
loc_31C6:			;L42:
	pop	bc		;	pop	bc
	jp	loc_3108	;	jp	L38
loc_31CA:			;l93:
	ld	de,_array_805F	;	ld	de,_array_805F
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	hl,99f		;	ld	hl,69f
				;	jp	L46
loc_31DF:			;L46:
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	jp	loc_3108	;	jp	L42
loc_31E6:			;l72:
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	push	hl		;	push	hl
	call	_sub_153A	;	call	_sub_153A
	jp	loc_2DC3	;	jp	L38
loc_31F3:			;l109:
	ld	de,2Dh		;	ld	de,45
	ld	l,(ix+-12)	;	ld	l,(ix+-12)
	ld	h,(ix+-11)	;	ld	h,(ix+-11)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	z,loc_3210	;	jp	z,L5
	ld	de,2Bh		;	ld	de,43
	ld	l,(ix+-12)	;	ld	l,(ix+-12)
	ld	h,(ix+-11)	;	ld	h,(ix+-11)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	nz,loc_330B	;	jp	nz,l110
loc_3210:			;L5:
	ld	a,(ix+-18)	;	ld	a,(ix+-18)
	or	a		;	or	a
	jp	nz,loc_324D	;	jp	nz,l77
	ld	e,(ix+-4)	;	ld	e,(ix+-4)
	ld	d,(ix+-3)	;	ld	d,(ix+-3)
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
	ld	de,(_word_AFF8)	;	ld	de,(_word_AFF8)
	ld	a,d		;	ld	a,d
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	l,a		;	ld	l,a
	ld	h,a		;	ld	h,a
	call	lladd		;	call	lladd
	ld	(ix+-24),e	;	ld	(ix+-24),e
	ld	(ix+-23),d	;	ld	(ix+-23),d
	ld	(ix+-22),l	;	ld	(ix+-22),l
	ld	(ix+-21),h	;	ld	(ix+-21),h
	ld	hl,0		;	ld	hl,0
	ld	(_word_AFF8),hl	;	ld	(_word_AFF8),hl
	ld	(ix+-18),1	;	ld	(ix+-18),1
loc_324D:			;l77:
	ld	de,2Dh		;	ld	de,45
	ld	l,(ix+-12)	;	ld	l,(ix+-12)
	ld	h,(ix+-11)	;	ld	h,(ix+-11)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	z,loc_3263	;	jp	z,L4
	ld	de,1		;	ld	de,1
	ld	hl,0		;	ld	hl,0
	jr	loc_3268	;	jp	L3
loc_3263:			;L4:
	ld	de,-1		;	ld	de,-1
	ld	l,e		;	ld	l,e
	ld	h,d		;	ld	h,d
loc_3268:			;L3:
	push	hl		;	push	hl
	push	de		;	push	de
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,-24		;	ld	hl,-24
	add	hl,de		;	add	hl,de
	call	aslladd		;	call	aslladd
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	push	hl		;	push	hl
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	2		;	cp	2
	jp	nz,loc_32BF	;	jp	nz,l112
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	push	hl		;	push	hl
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	de,4		;	ld	de,4
	call	wrelop		;	call	wrelop
	jp	nc,loc_32BF	;	jp	nc,l112
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	push	hl		;	push	hl
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	add	hl,hl		;	add	hl,hl
	add	hl,hl		;	add	hl,hl
	add	hl,hl		;	add	hl,hl
	ld	b,l		;	ld	b,l
	ld	hl,1		;	ld	hl,1
	call	shal		;	call	shll
	dec	hl		;	dec	hl
	ex	de,hl		;	ex	de,hl
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	push	de		;	push	de
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,0FFE8h	;	ld	hl,-24
	add	hl,de		;	add	hl,de
	call	aslland		;	call	aslland
loc_32BF:			;l112:
	ld	a,(ix+-24)	;	ld	a,(ix+-24)
	or	(ix+-23)	;	or	(ix+-23)
	or	(ix+-22)	;	or	(ix+-22)
	or	(ix+-21)	;	or	(ix+-21)
	jp	z,loc_3304	;	jp	z,l114
	jr	loc_32DD	;	jp	l118
loc_32D0:	; m58:		;l117:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	dec	hl		;	dec	hl
	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h
loc_32DD:	; m59:		;l118:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	l,(ix+-20)	;	ld	l,(ix+-20)
	ld	h,(ix+-19)	;	ld	h,(ix+-19)
	call	wrelop		;	call	wrelop
	jr	nc,loc_32FA	;	jp	nc,l116
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	dec	hl		;	dec	hl
	ld	a,(hl)		;	ld	a,(hl)
	cp	0Ah		;	cp	10
	jr	nz,loc_32D0	;	jp	nz,l117
loc_32FA:	; m60:		;l116:
	ld	hl,0Ah		;	ld	hl,10
	push	hl		;	push	hl
	call	_putchar	;	call	_putchar
	jp	loc_2DC3	;	jp	L38
loc_3304:			;l114:
	ld	(ix+-18),0	;	ld	(ix+-18),0
	jp	loc_2D2B	;	jp	l12
loc_330B:			;l110:
	ld	a,(_word_AFF8)	;	ld	a,(_word_AFF8)
	ld	e,a		;	ld	e,a
	ld	a,(ix+-8)	;	ld	a,(ix+-8)
	add	a,e		;	add	a,e
	ld	(ix+-8),a	;	ld	(ix+-8),a
	ld	hl,0		;	ld	hl,0
	ld	(_word_AFF8),hl	;	ld	(_word_AFF8),hl
	ld	b,a		;	ld	b,a
	sla	b		;	sla	b
	sla	b		;	sla	b
	sla	b		;	sla	b
	ld	e,(ix+-4)	;	ld	e,(ix+-4)
	ld	d,(ix+-3)	;	ld	d,(ix+-3)
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
	call	alrsh		;	call	alrsh
	push	hl		;	push	hl
	push	de		;	push	de
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	push	hl		;	push	hl
	call	_sub_2CE0	;	call	_sub_2CE0
	jp	loc_31C6	;	(jp 	L45)
loc_3347:			;l78:
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	ld	a,(hl)		;	ld	a,(hl)
	cp	47h		;	cp	71
	ld	e,l		;	ld	e,l
	ld	d,h		;	ld	d,h
	jr	nz,loc_3369	;	jp	nz,L12
	ld	hl,1Bh		;	ld	hl,27
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	hl,6		;	ld	hl,6
	add	hl,bc		;	add	hl,bc
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	push	hl		;	push	hl
	ld	hl,109f	; "%d"	;	ld	hl,29f ; "%d"
	jp	loc_31DF	;	(goto L46)
loc_3369:	; m64:		;L12:
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
	ld	(ix+-16),e	;	ld	(ix+-16),e
	ld	(ix+-15),d	;	d	(ix+-15),d
	ld	(ix+-14),l	;	ld	(ix+-14),l
	ld	(ix+-13),h	;	ld	(ix+-13),h
	push	hl		;	push	hl
	push	de			;push	de
	call	_sub_46F7	;	call	_sub_46F7
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	or	a			;or	a
	ld	e,(ix+-16)	;	ld	e,(ix+-16)
	ld	d,(ix+-15)	;	ld	d,(ix+-15)
	ld	l,(ix+-14)	;	ld	l,(ix+-14)
	ld	h,(ix+-13)	;	ld	h,(ix+-13)
	push	hl		;	push	hl
	push	de		;	push	de
	jr	nz,loc_33B6	;	jp	nz,L13
	ld	hl,-1		;	ld	de,-1	   <----+ At this point,
	pop	bc		;	ld	l,e		; from source
	or	a		;	ld	h,d		; in C, compiler
	sbc	hl,bc		;	call	llsub		; generates code
	pop	bc		;				; that performs
	ex	de,hl		;				; expected action,
	ld	hl,-1		;				; but differs from 
	sbc	hl,bc		;			   <----+ original image
	ld	(ix+-16),e	;	ld	(ix+-16),e
	ld	(ix+-15),d	;	ld	(ix+-15),d
	ld	(ix+-14),l	;	ld	(ix+-14),l
	ld	(ix+-13),h	;	ld	(ix+-13),h
	push	hl		;	push	hl
	push	de		;	push	de
loc_33B6:			;L13:
	call	_sub_46F7	;	call	_sub_46F7
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	e,l		;	ld	e,l
	ld	d,0		;	ld	d,0
	ld	hl,-1		;	ld	hl,-1
	add	hl,de		;	add	hl,de
	srl	h		;	srl	h
	rr	l		;	rr	l
	srl	h		;	srl	h
	rr	l		;	rr	l
	srl	h		;	srl	h
	rr	l		;	rr	l
	ex	de,hl		;	ex	de,hl
	ld	hl,(_word_AFF8)	;	ld	hl,(_word_AFF8)
	add	hl,de		;	add	hl,de
	jp	loc_3050	;
loc_33D6:			;l105:
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	ld	a,(hl)		;	ld	a,(hl)
	cp	47h		;	cp	71
	ld	e,l		;	ld	e,l
	ld	d,h		;	ld	d,h
	jr	nz,loc_33F8	;	jp	nz,L17
	ld	hl,1Bh		;	ld	hl,27
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	hl,5		;	ld	hl,5
	add	hl,bc		;	add	hl,bc
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	push	hl		;	push	hl
	ld	hl,119f		;	ld	hl,129f
	jp	loc_31DF	;	jp	L46
loc_33F8:	;m67		;L17:
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
	ld	(ix+-16),e	;	ld	(ix+-16),e
	ld	(ix+-15),d	;	ld	(ix+-15),d
	ld	(ix+-14),l	;	ld	(ix+-14),l
	ld	(ix+-13),h	;	ld	(ix+-13),h
	push	hl		;	push	hl
	push	de		;	push	de
	call	_sub_46F7	;	call	_sub_46F7
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	or	a		;	or	a
	ld	e,(ix+-16)	;	ld	e,(ix+-16)
	ld	d,(ix+-15)	;	ld	d,(ix+-15)
	ld	l,(ix+-14)	;	ld	l,(ix+-14)
	ld	h,(ix+-13)	;	ld	h,(ix+-13)
	push	hl		;	push	hl
	push	de		;	push	de
	jr	nz,loc_3445	;	jp	nz,L18
	ld	hl,-1		;	ld	de,-1	   <----+ At this point,
	pop	bc		;	ld	l,e		; from source
	or	a		;	ld	h,d		; in C, compiler
	sbc	hl,bc		;	call	llsub		; generates code
	pop	bc		;				; that performs
	ex	de,hl		;				; expected action,
	ld	hl,-1		;				; but differs from 
	sbc	hl,bc		;			   <----+ original image
	ld	(ix+-16),e	;ld	(ix+-16),e
	ld	(ix+-15),d	;ld	(ix+-15),d
	ld	(ix+-14),l	;ld	(ix+-14),l
	ld	(ix+-13),h	;ld	(ix+-13),h
	push	hl		;	push	hl
	push	de		;	push	de
loc_3445:			;L18:
	call	_sub_46F7	;	call	_sub_46F7
	pop	bc		;	pop	bc
	ld	e,l		;	ld	e,l
	ld	d,0		;	ld	d,0
	ld	hl,-1		;	ld	hl,-1
	add	hl,de		;	add	hl,de
	ex	(sp),hl		;	ex	(sp),hl
	ld	hl,129f		;	ld	hl,139f
	jp	loc_31DF	;	jp	L46
loc_3457:			;l87:
	ld	a,(ix+-10)	;	ld	a,(ix+-10)
	cp	47h		;	cp	71
	ld	e,(ix+-4)	;	ld	e,(ix+-4)
	ld	d,(ix+-3)	;	ld	d,(ix+-3)
	ld	a,(ix+-17)	;	ld	a,(ix+-17)
	ld	l,a		;	ld	l,a
	jr	z,loc_3475	;	jp	z,L15
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	add	hl,de		;	add	hl,de
	ld	de,9		;	ld	de,9
	add	hl,de		;	add	hl,de
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	jr	loc_3480	;	jp	L7
loc_3475:			;L15:
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	add	hl,de		;	add	hl,de
	ld	de,0Fh		;	ld	de,15
	add	hl,de		;	add	hl,de
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
loc_3480:			;L7:
	ld	(ix+-7),l	;	ld	(ix+-7),l
	ld	a,(ix+-6)	;	ld	a,(ix+-6)
	or	(ix+-5)		;	or	(ix+-5)
	jp	z,loc_34C8	;	jp	z,l88
	jp	loc_34B5	;	jp	l89
loc_348F:			;l90:
	ld	l,(ix+-6)	;	ld	l,(ix+-6)
	ld	h,(ix+-5)	;	ld	h,(ix+-5)
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	(ix+-6),l	;	ld	(ix+-6),l
	ld	(ix+-5),h	;	ld	(ix+-5),h
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,-48		;	ld	hl,-48
	add	hl,de		;	add	hl,de
	ex	de,hl		;	ex	de,hl
	ld	l,(ix+-7)	;	ld	l,(ix+-7)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,_array_AB24	;	ld	de,_array_AB24
	add	hl,de		;	add	hl,de
	ld	l,(hl)		;	ld	l,(hl)
	ld	(ix+-7),l	;	ld	(ix+-7),l
loc_34B5:			;l89:
	ld	l,(ix+-6)	;	ld	l,(ix+-6)
	ld	h,(ix+-5)	;	ld	h,(ix+-5)
	ld	a,(hl)		;	ld	a,(hl)
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de
	bit	2,(hl)		;	bit	2,(hl)
	jr	nz,loc_348F	;	jp	nz,l90
loc_34C8:	; m74		;l88:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	a,(hl)		;	ld	a,(hl)
	cp	2Bh		;	cp	43
	jr	z,loc_34E4	;	jp	z,l92
	ld	a,(_word_AFF8)	;	ld	a,(_word_AFF8)
	ld	e,a		;	ld	e,a
	ld	a,(ix+-7)	;	ld	a,(ix+-7)
	add	a,e		;	add	a,e
	ld	(ix+-7),a	;	ld	(ix+-7),a
	ld	hl,0		;	ld	hl,0
	ld	(_word_AFF8),hl	;	ld	(_word_AFF8),hl
loc_34E4:	; m75		;l92:
	ld	de,_off_AACA	;	ld	de,_off_AACA
	ld	l,(ix+-7)	;	ld	l,(ix+-7)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	hl,139f		;	ld	hl,59f
	jp	loc_31DF	;	jp	L46
loc_34F8:	; m76		;l122:
	ld	a,(ix+-9)	;	ld	a,(ix+-9)
	cp	55h		;	cp	85
	jp	nz,loc_3533	;	jp	nz,l123
	ld	a,(_word_AFFB)	;	ld	a,(_word_AFFB)
	ld	e,a		;	ld	e,a
	ld	a,(ix+-8)	;	ld	a,(ix+-8)
	add	a,e		;	add	a,e
	ld	(ix+-8),a	;	ld	(ix+-8),a
	ld	de,_dopetab	;	ld	de,_dopetab
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	bit	1,b		;	bit	1,b
	jr	z,loc_3525	;	jp	z,l124
	ld	a,(ix+10)	;	ld	a,(ix+10)
	or	a		;	or	a
	jr	z,loc_3525	;	jp	z,l124
	dec	(ix+-8)		;	dec	(ix+-8)
loc_3525:	; m77		;l124:
	ld	a,(ix+-8)	;	ld	a,(ix+-8)
	ld	l,a		;	ld	l,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	push	hl		;	push	hl
	ld	hl,149f		;	ld	hl,149f
	jp	loc_31DF	;	jp	L46
loc_3533:	; m78		;l123:
	ld	a,(ix+-8)	;	ld	a,(ix+-8)
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,(_word_AFF8)	;	ld	hl,(_word_AFF8)
	add	hl,de		;	add	hl,de
	ld	(_word_AFF8),hl	;	ld	(_word_AFF8),hl
	ld	a,(ix+-17)	;	ld	a,(ix+-17)
	ld	l,a		;	ld	l,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	push	hl		;	push	hl
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,8		;	ld	hl,8
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	push	hl		;	push	hl
	call	_sub_2D09	;	call	_sub_2D09
	jp	loc_31C6	;	jp	L45

	psect	data

p_2d09_1:
19:	defb 37,100,0    ; "%d"	;	defb	37,108,117,0	;"%lu"

p_2d09_2:
29:	defb 37,115,0    ; "%s"	;	defb	37,100,0	;"%d"

p_2d09_3:
39:	defb 37,115,0    ; "%s"	;	defb	37,100,0	;"%d"

p_2d09_4:
49:	defb 37,115,0    ; "%s"	;	defb	37,100,0	;"%d"

p_2d09_5:
59:	defb 43,37,100,0 ;"+%d" ;	defb	37,115,0	;"%s"

p_2d09_6:
69:	defb 37,100,0    ; "%d"	;	defb	37,115,0	;"%s"

p_2d09_7:
79:	defb 37,100,0    ; "%d"	;	defb	37,115,0	;"%s"

p_2d09_8:
89:	defb 37,108,117,0; "%lu";	defb	37,115,0	;"%s"

p_2d09_9:
99:	defb 37,115,0    ; "%s"	;	defb	37,115,0	;"%s"

p_2d09_10:
109:	defb 37,100,0    ; "%d"	;	defb	43,37,100,0	;"+%d"

p_2d09_11:
119:	defb 37,100,0    ; "%d"	;	defb	37,100,0	;"%d"

p_2d09_12:
129:	defb 37,100,0    ; "%d"	;	defb	37,100,0	;"%d"

p_2d09_13:
139:	defb 37,115,0    ; "%s"	;	defb	37,100,0	;"%d"

p_2d09_14:
149:	defb 37,100,0    ; "%d"	;	defb	37,100,0	;"%d"

	psect	text

; End of function sub_2D09

; End of file 2D09.as


