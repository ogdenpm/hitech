*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 3CDF.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_3CDF OK++
;=========================================================
	global	_sub_3CDF	;	global	_sub_3CDF
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_sub_2BD0	;	global	_sub_2BD0
	global	_sub_36E0	;	global	_sub_36E0
	global	_byte_B014	;	global	_byte_B014
	global	_dopetab	;	global	_dopetab
	global	_sub_4C6D	;	global	_sub_4C6D
	global	_array_AFFD	;	global	_array_AFFD
	global	_sub_377A	;	global	_sub_377A
	global 	csv		;	global 	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_3CDF:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	1Ch		;	cp	28
	jr	nz,loc_3D0D	;	jp	nz,l12
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_2BD0	;	call	_sub_2BD0
	pop	bc		;	pop	bc
	push	iy		;	push	iy
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
loc_3D0D:			;l12:
	ld	a,(_byte_B014)	;	ld	a,(_byte_B014)
	cp	0Ah		;	cp	10
	jr	z,loc_3D25	;	jp	z,L3
	ld	de,_dopetab	;	ld	de,_dopetab
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	bit	6,b		;	bit	6,b
	jr	z,loc_3D2B	;	jp	z,l16
loc_3D25:			;L3:
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	jp	cret		;	jp	cret
loc_3D2B:			;l16:
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	0Fh		;	cp	15
	jr	z,loc_3D36	;	jp	z,l18
	cp	13h		;	cp	19
	jr	nz,loc_3D76	;	jp	nz,l15
loc_3D36:			;l18:
	push	iy		;	push	iy
	call	_sub_4C6D	;	call	_sub_4C6D
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	or	a		;	or	a
	jr	z,loc_3D76	;	jp	z,l15
	ld	a,(_byte_B014)	;	ld	a,(_byte_B014)
	ld	e,a		;	ld	e,a
	inc	a		;	inc	a
	ld	(_byte_B014),a	;	ld	(_byte_B014),a
	ld	l,e		;	ld	l,e
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	ld	de,_array_AFFD	;	ld	de,_array_AFFD
	add	hl,de		;	add	hl,de
	push	iy		;	push	iy
	pop	de		;	pop	de
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	0Fh		;	cp	15
	jr	z,loc_3D62	;	jp	z,L2
	ld	hl,26h 		;	ld	hl,38
	jr	loc_3D65	;	jp	L1
loc_3D62:			;L2:
	ld	hl,25h		;	ld	hl,37
loc_3D65:			;L1:
	ld	(iy+0),l	;	ld	(iy+0),l
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_377A	;	call	_sub_377A
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
loc_3D76:			;l15:
	ld	de,_dopetab	;	ld	de,_dopetab
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-2),c	;	ld	(ix+-2),c
	ld	(ix+-1),b	;	ld	(ix+-1),b
	ld	a,c		;	ld	a,c
	and	0Ch		;	and	12
	ld	l,a		;	ld	l,a
	xor	a		;	xor	a
	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	z,loc_3DA4	;	jp	z,l20
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_3CDF	;	call	_sub_3CDF
	pop	bc		;	pop	bc
	ld	(iy+19h),l	;	ld	(iy+25),l
	ld	(iy+1Ah),h	;	ld	(iy+26),h
loc_3DA4:			;l20:
	ld	de,8		;	ld	de,8
	ld	a,(ix+-2)	;	ld	a,(ix+-2)
	and	0Ch		;	and	12
	ld	l,a		;	ld	l,a
	xor	a		;	xor	a
	ld	h,a		;	ld	h,a
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	nz,loc_3D25	;	jp	nz,L3
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	call	_sub_3CDF	;	call	_sub_3CDF
	pop	bc		;	pop	bc
	ld	(iy+1Bh),l	;	ld	(iy+27),l
	ld	(iy+1Ch),h	;	ld	(iy+28),h
	jp	loc_3D25	;	jp	L3

; End of function sub_3CDF OK++

;=========================================================
; sub_3DC9 OK++
;=========================================================
	global	_sub_3DC9	;	global	_sub_3DC9
	global	_sub_600E	;	global	_sub_600E
	global	_warning	;	global	_warning
	global	_sub_475C	;	global	_sub_475C
	global	wrelop		;	global	wrelop
	global 	csv		;

; Disassembled version		; After compiling C source code
_sub_3DC9:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	push	hl		;	push	hl
	call	_sub_600E	;	call	_sub_600E
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	4		;	cp	4
	jr	nz,loc_3E2B	;	jp	nz,l23
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ld	a,(hl)		;	ld	a,(hl)
	cp	43h		;	cp	67
	jr	nz,loc_3E2B	;	jp	nz,l23
	ld	hl,19f		;	ld	hl,19f
	push	hl		;	push	hl
	call	_warning	;	call	_warning
	pop	bc		;	pop	bc
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
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
	ld	a,e		;	ld	a,e
	or	d		;	or	d
	or	l		;	or	l
	or	h		;	or	h
	jr	z,loc_3E3C	;	jp	z,l25
	ld	(iy+0),5	;	ld	(iy+0),5
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	ld	(iy+19h),l	;	ld	(iy+25),l
	ld	(iy+1Ah),h	;	ld	(iy+26),h
loc_3E2B:			;l23:
	xor	a		;	xor	a
	ld	(_byte_B014),a	;	ld	(_byte_B014),a
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	0Fh		;	cp	15
	jr	nz,loc_3E45	;	jp	nz,l27
	ld	(iy+0),25h	;	ld	(iy+0),37
	jr	loc_3E50	;	jp	l28
loc_3E3C:			;l25:
	push	iy		;	push	iy
	call	_sub_475C	;	call	_sub_475C
	pop	bc		;	pop	bc
	jp	cret		;	jp	cret
loc_3E45:			;l27:
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	13h		;	cp	19
	jr	nz,loc_3E50	;	jp	nz,l28
	ld	(iy+0),26h 	;	ld	(iy+0),38
loc_3E50:			;l28:
	push	iy		;	push	iy
	call	_sub_3CDF	;	call	_sub_3CDF
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	a,(_byte_B014)	;	ld	a,(_byte_B014)
	or	a		;	or	a
	push	iy		;	push	iy
	jr	z,loc_3E68	;	jp	z,L4
	call	_sub_600E	;	call	_sub_600E
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ex	(sp),hl		;	ex	(sp),hl
loc_3E68:			;L4:
	call	_sub_2BD0	;	call	_sub_2BD0
	pop	bc		;	pop	bc
	ld	(ix+-2),0	;	ld	(ix+-2),0
	ld	(ix+-1),0	;	ld	(ix+-1),0
	jr	loc_3E96	;	jp	l31
loc_3E76:			;l32:
	ld	de,_array_AFFD	;	ld	de,_array_AFFD
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	call	_sub_2BD0	;	call	_sub_2BD0
	pop	bc		;	pop	bc
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	inc	hl		;	inc	hl
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
loc_3E96:			;l31:
	ld	a,(_byte_B014)	;	ld	a,(_byte_B014)
	ld	e,a		;	ld	e,a
	ld	d,0		;	ld	d,0
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	call	wrelop		;	call	wrelop
	jr	c,loc_3E76	;	jp	c,l32
	jp	cret		;	jp	cret

; End of function sub_3DC9 OK++

	psect	data

d_3dc9_A9B4:
19:	;	"constant conditional branch"
defb	99,111,110,115,116,97,110,116,32,99,111,110,100,105,116,105
defb	111,110,97,108,32,98,114,97,110,99,104,0


	psect	text

; End of file 3CDF.as


