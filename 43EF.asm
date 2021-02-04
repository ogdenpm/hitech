*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 43EF.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_43EF OK+
;
; Generated code is completely identical, except for
; location of code of branches of "switch" operator.
;
; For easy visual comparison Some parts of compiled code are
; moved in accordance with order of disassembled code from
; binary image.
;=========================================================
	global	_sub_43EF	;	global	_sub_43EF
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_sub_3712	;	global	_sub_3712
	global	_word_AE11	;	global	_word_AE11
	global	_word_AF1B	;	global	_word_AF1B
	global	_word_AFE9	;	global	_word_AFE9
	global	_dopetab	;	global	_dopetab
	global	_nodesize	;	global	_nodesize
	global	_warning	;	global	_warning
	global	_sub_475C	;	global	_sub_475C
	global	wrelop		;	global	wrelop
	global	_sub_385B	;	global	_sub_385B
	global	_sub_37ED	;	global	_sub_37ED
	global	_sub_36E0	;	global	_sub_36E0
	global	_word_AF1D	;	global	_word_AF1D
	global	_word_AED9	;	global	_word_AED9

	psect	text

;	Disassembled version	; After compiling С source code	
_sub_43EF:
	call	ncsv		;	call	ncsv
	defw 	0FFFAh		;	defw	-6
	call	_sub_3712	;	call	_sub_3712
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	a,(ix+6)	;	ld	a,(ix+6)
	ld	(iy+0),a	;	ld	(iy+0),a
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	(iy+19h),l	;	ld	(iy+25),l
	ld	(iy+1Ah),h	;	ld	(iy+26),h
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	ld	(iy+1Bh),l	;	ld	(iy+27),l
	ld	(iy+1Ch),h	;	ld	(iy+28),h
	ld	de,_dopetab	;	ld	de,_dopetab
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	a,c		;	ld	a,c
	and	30h		;	and	48
	ld	l,a		;	ld	l,a
	xor	a		;	xor	a
	ld	h,a		;	ld	h,a
	or	a		;	or	a
	jr	nz,loc_443E	;	jp	nz,l17
	ld	a,l		;	ld	a,l
	cp	10h		;	cp	16
	jp	z,loc_4493	;	jp	z,l14
	cp	20h		;	cp	32
	jp	z,loc_449E	;	jp	z,l15
	cp	30h		;	cp	48
	jp	z,loc_44A3	;	jp	z,l16
loc_443E:			;l17:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	hl,17h		;	ld	hl,23
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+17h),c	;	ld	(iy+23),c
	ld	(iy+18h),b	;	ld	(iy+24),b
	ld	hl,15h		;	ld	hl,21
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+15h),c	;	ld	(iy+21),c
	ld	(iy+16h),b	;	ld	(iy+22),b
loc_445E:			;l19:
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	3		;	cp	3
	jp	z,loc_4666	;	jp	z,l20
	cp	9		;	cp	9
	jp	z,loc_4605	;	jp	z,l24
	cp	0Ah		;	cp	10
	jp	z,loc_464B	;	jp	z,l28
	cp	0Dh		;	cp	13
	jp	z,loc_464B	;	jp	z,l28
	cp	14h		;	cp	20
	jp	z,loc_45E2	;	jp	z,l35
	cp	16h		;	cp	22
	jr	z,loc_44A8	;	jp	z,l29
	cp	1Bh		;	cp	27
	jp	z,loc_4652	;	jp	z,l32
	cp	1Ch		;	cp	28
	jp	z,loc_45E2	;	jp	z,l35
	cp	30h		;	cp	48
	jp	z,loc_45E2	;	jp	z,l35
loc_448D:			;l18:
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	jp	cret		;	jp	cret
loc_4493:			;l14:
	ld	hl,(_word_AE11)	;	ld	hl,(_word_AE11)
loc_4496:			;L5:
	ld	(iy+17h),l	;	ld	(iy+23),l
	ld	(iy+18h),h	;	ld	(iy+24),h
	jr	loc_445E	;	jp	l19
loc_449E:			;l15:
	ld	hl,(_word_AF1B)	;	ld	hl,(_word_AF1B)
	jr	loc_4496	;	jp	L5
loc_44A3:			;l16:
	ld	hl,(_word_AFE9)	;	ld	hl,(_word_AFE9)
	jr	loc_4496	;	jp	L5
loc_44A8:			;l29:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	a,(hl)		;	ld	a,(hl)
	cp	41h		;	cp	65
	jp	nz,loc_4519	;	jp	nz,l30
	ex	de,hl		;	ex	de,hl
	ld	hl,17h		;	ld	hl,23
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-2),c	;	ld	(ix+-2),c
	ld	(ix+-1),b	;	ld	(ix+-1),b
	push	iy		;	push	iy
	call	_sub_36E0	;	call	_sub_36E0
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	(iy+17h),l	;	ld	(iy+23),l
	ld	(iy+18h),h	;	ld	(iy+24),h
	ex	de,hl		;	ex	de,hl
	ld	hl,13h		;	ld	hl,19
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	add	hl,hl		;	add	hl,hl
	add	hl,bc		;	add	hl,bc
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	ld	a,d		;	ld	a,d
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	l,a		;	ld	l,a
	ld	h,a		;	ld	h,a
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(ix+0Ah)	;	ld	e,(ix+10)
	ld	d,(ix+0Bh)	;	ld	d,(ix+11)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	pop	de		;	pop	de
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	inc	hl		;	inc	hl
	pop	bc		;	pop	bc
	ld	(hl),c		;	ld	(hl),c
	inc	hl		;	inc	hl
	ld	(hl),b		;	ld	(hl),b
	jp	loc_448D	;	jp	l18
loc_4519:			;l30:
	ld	e,(iy+17h)	;	ld	e,(iy+23)
	ld	d,(iy+18h)	;	ld	d,(iy+24)
	ld	hl,13h		;	ld	hl,19
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	e,(ix+0Ah)	;	ld	e,(ix+10)
	ld	d,(ix+0Bh)	;	ld	d,(ix+11)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	add	hl,hl		;	add	hl,hl
	add	hl,bc		;	add	hl,bc
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-2),c	;	ld	(ix+-2),c
	ld	(ix+-1),b	;	ld	(ix+-1),b
	ld	e,c		;	ld	e,c
	ld	d,b		;	ld	d,b
	ld	hl,0Fh		;	ld	hl,15
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+17h),c	;	ld	(iy+23),c
	ld	(iy+18h),b	;	ld	(iy+24),b
	ld	hl,0Dh		;	ld	hl,13
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+15h),c	;	ld	(iy+21),c
	ld	(iy+16h),b	;	ld	(iy+22),b
	ld	hl,11h		;	ld	hl,17
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	ld	a,d		;	ld	a,d
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	l,a		;	ld	l,a
	ld	h,a		;	ld	h,a
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(ix+0Ah)	;	ld	e,(ix+10)
	ld	d,(ix+0Bh)	;	ld	d,(ix+11)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	pop	de		;	pop	de
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	inc	hl		;	inc	hl
	pop	bc		;	pop	bc
	ld	(hl),c		;	ld	(hl),c
	inc	hl		;	inc	hl
	ld	(hl),b		;	ld	(hl),b
	ld	e,(ix+0Ah)	;	ld	e,(ix+10)
	ld	d,(ix+0Bh)	;	ld	d,(ix+11)
	ld	hl,17h		;	ld	hl,23
	add	hl,de		;	add	hl,de
	ld	de,(_word_AF1D)	;	ld	de,(_word_AF1D)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	bit	4,(hl)		;	bit	4,(hl)
	jp	z,loc_448D	;	jp	z,l18
	call	_sub_3712	;	call	_sub_3712
	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	push	hl		;	push	hl
	ld	bc,1Dh		;	ld	bc,29
	ldir			;	ldir
	pop	hl		;	pop	hl
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	push	iy		;	push	iy
	pop	de		;	pop	de
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	(iy+0),47h	;	ld	(iy+0),71
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
				;	jp	L2
loc_45D9:			;L2:
	ld	(iy+1Bh),l	;	ld	(iy+27),l
	ld	(iy+1Ch),h	;	ld	(iy+28),h
	jp	loc_448D	;	jp	l18
loc_45E2:			;l35:
	ld	e,(iy+1Bh)	;	ld	e,(iy+27)
	ld	d,(iy+1Ch)	;	ld	d,(iy+28)
	ld	hl,17h		;	ld	hl,23
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+17h),c	;	ld	(iy+23),c
	ld	(iy+18h),b	;	ld	(iy+24),b
	ld	hl,15h		;	ld	hl,21
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+15h),c	;	ld	(iy+21),c
	ld	(iy+16h),b	;	ld	(iy+22),b
	jp	loc_448D	;	jp	l18
loc_4605:			;l24:
	ld	a,(iy+15h)	;	ld	a,(iy+21)
	or	(iy+16h)	;	or	(iy+22)
	jr	nz,loc_4642	;	jp	nz,l25
	ld	e,(iy+17h)	;	ld	e,(iy+23)
	ld	d,(iy+18h)	;	ld	d,(iy+24)
	ld	hl,0Bh		;	ld	hl,11
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	ld	hl,1		;	ld	hl,1
	call	wrelop		;	call	wrelop
	jr	nc,loc_4642	;	jp	nc,l25
	ld	e,(iy+17h)	;	ld	e,(iy+23)
	ld	d,(iy+18h)	;	ld	d,(iy+24)
	ld	hl,0Dh		;	ld	hl,13
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+15h),c	;	ld	(iy+21),c
	ld	(iy+16h),b	;	ld	(iy+22),b
	ld	hl,0Fh		;	ld	hl,15
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+17h),c	;	ld	(iy+23),c
	ld	(iy+18h),b	;	ld	(iy+24),b
loc_4642:			;l25:
	push	iy		;	push	iy
	call	_sub_385B	;	call	_sub_385B
loc_4647:			;L4:
	pop	bc		;	pop	bc
	jp	loc_448D	;	jp	l18
loc_464B:			;l28:
	push	iy		;	push	iy
	call	_sub_37ED	;	call	_sub_37ED
	jr	loc_4647	;	jp	L4
loc_4652:			;l32:
	ld	hl,(_word_AED9)	;	ld	hl,(_word_AED9)
	ld	(iy+17h),l	;	ld	(iy+23),l
	ld	(iy+18h),h	;	ld	(iy+24),h
	ld	(iy+15h),1	;	ld	(iy+21),1
	ld	(iy+16h),0	;	ld	(iy+22),0
	jp	loc_448D	;	jp	l18
loc_4666:			;l20:
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ld	a,(hl)		;	ld	a,(hl)
	cp	42h		;	cp	66
	jr	nz,loc_4691	;	jp	nz,l21
	ex	de,hl		;	ex	de,hl
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	hl,9		;	ld	hl,9
	add	hl,bc			;add	hl,bc
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	ld	hl,0		;	ld	hl,0
	ld	(ix+-6),e	;	ld	(ix+-6),e
	ld	(ix+-5),d	;	ld	(ix+-5),d
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	jr	loc_46AC	;	jp	l22
loc_4691:			;l21:
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ex	de,hl		;	ex	de,hl
	ld	hl,0		;	ld	hl,0
	ld	(ix+-6),e	;	ld	(ix+-6),e
	ld	(ix+-5),d	;	ld	(ix+-5),d
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
loc_46AC:			;l22:
	ld	a,(ix+-6)	;	ld	a,(ix+-6)
	or	(ix+-5)		;	or	(ix+-5)
	or	(ix+-4)		;	or	(ix+-4)
	or	(ix+-3)		;	or	(ix+-3)
	jr	nz,loc_46C2	;	jp	nz,l23
	ld	hl,19f		;	ld	hl,19f
	push	hl		;	push	hl
	call	_warning	;	call	_warning
	pop	bc		;	pop	bc
loc_46C2:			;l23:
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_475C	;	call	_sub_475C
	pop	bc		;	pop	bc
	ld	(iy+0),43h	;	ld	(iy+0),67
	ld	hl,(_word_AE11)	;	ld	hl,(_word_AE11)
	ld	(iy+17h),l	;	ld	(iy+23),l
	ld	(iy+18h),h	;	ld	(iy+24),h
	ld	(iy+15h),0	;	ld	(iy+21),0
	ld	(iy+16h),0	;	ld	(iy+22),0
	ld	e,(ix+-6)	;	ld	e,(ix+-6)
	ld	d,(ix+-5)	;	ld	d,(ix+-5)
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	ld	(iy+19h),e	;	ld	(iy+25),e
	ld	(iy+1Ah),d	;	ld	(iy+26),d
	jp	loc_45D9	;	(jp	L2)

	psect	data

p_43ef_AA1F:
	;	'Sizeof yields 0'
19:	defb	83,105,122,101,111,102,32,121,105,101,108,100,115,32,48,0


	psect	text

; End of function sub_43EF

; Endof file 43EF.as

