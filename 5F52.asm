*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 5F52.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_5F52 OK++
;=========================================================
	global	_sub_5F52	;	global	_sub_5F52
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_dopetab	;	global	_dopetab
	global	_sub_36E0	;	global	_sub_36E0
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_5F52:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	de,_dopetab	;	ld	de,_dopetab
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	and	0Ch		;	and	12
	ld	(ix+-1),a	;	ld	(ix+-1),a
	cp	8		;	cp	8
	jr	nz,loc_5F85	;	jp	nz,l12
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	call	_sub_5F52	;	call	_sub_5F52
	pop	bc		;	pop	bc
	ld	(iy+1Bh),l	;	ld	(iy+27),l
	ld	(iy+1Ch),h	;	ld	(iy+28),h
loc_5F85:			;l12:
	ld	a,(ix+-1)	;	ld	a,(ix+-1)
	or	a		;	or	a
	jr	z,loc_5F9C	;	jp	z,l15
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_5F52	;	call	_sub_5F52
	pop	bc		;	pop	bc
	ld	(iy+19h),l	;	ld	(iy+25),l
	ld	(iy+1Ah),h	;	ld	(iy+26),h
loc_5F9C:			;l15:
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	0Eh		;	cp	14
	jr	z,loc_5FAE	;	jp	z,l16
	cp	25h		;	cp	37
	jp	z,loc_5FD7	;	jp	z,l18
loc_5FA8:			;l14:
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	jp	cret		;	jp	cret
loc_5FAE:			;l16:
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ld	a,(hl)		;	ld	a,(hl)
	cp	15h		;	cp	21
	jr	nz,loc_5FD7	;	jp	nz,l18
	ld	(ix+-3),l	;	ld	(ix+-3),l
	ld	(ix+-2),h	;	ld	(ix+-2),h
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	ld	(iy+19h),l	;	ld	(iy+25),l
	ld	(iy+1Ah),h	;	ld	(iy+26),h
	ld	l,(ix+-3)	;	ld	l,(ix+-3)
	ld	h,(ix+-2)	;	ld	h,(ix+-2)
	ld	(iy+1Bh),l	;	ld	(iy+27),l
	ld	(iy+1Ch),h	;	ld	(iy+28),h
loc_5FD7:			;l18:
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	ld	a,(hl)		;	ld	a,(hl)
	cp	15h		;	cp	21
	jr	nz,loc_5FA8	;	jp	nz,l14
	push	hl		;	push	hl
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	ld	e,(iy+1Bh)	;	ld	e,(iy+27)
	ld	d,(iy+1Ch)	;	ld	d,(iy+28)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+1Bh),c	;	ld	(iy+27),c
	ld	(iy+1Ch),b	;	ld	(iy+28),b
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	25h		;	cp	37
	jr	z,loc_6006	;	jp	z,L2
	ld	hl,12h		;	ld	hl,18
	jr	loc_6009	;	jp	L1
loc_6006:			;L2:
	ld	hl,26h		;	ld	hl,38
loc_6009:			;L1:
	ld	(iy+0),l	;	ld	(iy+0),l
	jr	loc_5FA8	;	jp	l14

; End of function sub_5F52 OK++

; End of file 5F52.as


