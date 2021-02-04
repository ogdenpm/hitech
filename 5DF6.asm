*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 5DF6.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_5DF6 OK++
;=========================================================
	global	_sub_5DF6	;	global	_sub_5DF6
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_dopetab	;	global	_dopetab
	global	_sub_43EF	;	global	_sub_43EF
	global	_sub_36E0	;	global	_sub_36E0
	global	_allocmem	;	global	_allocmem
	global	_strlen		;	global	_strlen
	global	_strcat		;	global	_strcat
	global	_strcpy		;	global	_strcpy
	global	_sub_7028	;	global	_sub_7028
	global 	csv		;	global 	csv

	psect	text

;	Disassembled version	; After compiling C source code
_sub_5DF6:
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
	jr	nz,loc_5E29	;	jp	nz,l12	
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	call	_sub_5DF6	;	call	_sub_5DF6
	pop	bc		;	pop	bc
	ld	(iy+1Bh),l	;	ld	(iy+27),l
	ld	(iy+1Ch),h	;	ld	(iy+28),h	
loc_5E29:			;l12:
	ld	a,(ix+-1)	;	ld	a,(ix+-1)
	or	a		;	or	a
	jr	z,loc_5E40	;	jp	z,l15
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_5DF6	;	call	_sub_5DF6
	pop	bc		;	pop	bc
	ld	(iy+19h),l	;	ld	(iy+25),l
	ld	(iy+1Ah),h	;	ld	(iy+26),h	
loc_5E40:			;l15:
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	12h		;	cp	18
	jr	z,loc_5E51	;	jp	z,l17	
	cp	15h		;	cp	21
	jp	z,loc_5EC6	;	jp	z,l20
	cp	26h		;	cp	38
	jp	nz,loc_5EC0	;	jp	nz,l14
loc_5E51:			;l17:
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	ld	a,(hl)		;	ld	a,(hl)
	cp	43h		;	cp	67
	jp	nz,loc_5E93	;	jp	nz,l18
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
	ld	hl,0		;	ld	hl,0
	pop	bc		;	pop	bc
	or	a		;	or	a
	sbc	hl,bc		;	sbc	hl,bc
	pop	bc		;	pop	bc
	ex	de,hl		;	ex	de,hl
	ld	hl,0		;	ld	hl,0
	sbc	hl,bc		;	sbc	hl,bc
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(iy+1Bh)	;	ld	e,(iy+27)
	ld	d,(iy+1Ch)	;	ld	d,(iy+28)
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
	ld	l,c		;	ld	l,c
	ld	h,b		;	ld	h,b
	jr	loc_5EAE	;	jp	l19
loc_5E93:			;l18:
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	ld	hl,15h		;	ld	hl,21
	push	hl			;push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(iy+1Bh),l	;	ld	(iy+27),l
	ld	(iy+1Ch),h	;	ld	(iy+28),h
loc_5EAE:			;l19:
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	12h		;	cp	18
	jr	z,loc_5EBA	;	jp	z,L2
	ld	hl,25h		;	ld	hl,37
	jr	loc_5EBD	;	jp	L1
loc_5EBA:			;L2:
	ld	hl,0Eh		;	ld	hl,14
loc_5EBD:			;L1:
	ld	(iy+0),l	;	ld	(iy+0),l
loc_5EC0:			;l14:
	push	iy		;	push	iy
loc_5EC2:			;L3:
	pop	hl		;	pop	hl
	jp	cret		;	jp	cret
loc_5EC6:			;l20:
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ld	a,(hl)		;	ld	a,(hl)
	cp	15h		;	cp	21
	jr	nz,loc_5EED	;	jp	nz,l21
	push	iy		;	push	iy
	call	_sub_36E0	;	call	_sub_36E0
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
loc_5EED:			;l21:
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ld	a,(hl)		;	ld	a,(hl)
	cp	44h		;	cp	68
	push	iy		;	push	iy
	jr	nz,loc_5EC2	;	jp	nz,L3
	call	_sub_36E0	;	call	_sub_36E0
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ex	(sp),hl		;	ex	(sp),hl
	call	_strlen		;	call	_strlen
	pop	bc		;	pop	bc
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	push	hl		;	push	hl
	call	_allocmem	;	call	_allocmem
	ld	(ix+-3),l	;	ld	(ix+-3),l
	ld	(ix+-2),h	;	ld	(ix+-2),h
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ex	(sp),	hl	;	ex	(sp),hl
	ld	hl,19f		;	ld	hl,19f
	push	hl		;	push	hl
	ld	l,(ix+-3)	;	ld	l,(ix+-3)
	ld	h,(ix+-2)	;	ld	h,(ix+-2)
	push	hl		;	push	hl
	call	_strcpy		;	call	_strcpy
	pop	bc		;	pop	bc
	ex	(sp),hl		;	ex	(sp),hl
	call	_strcat		;	call	_strcat
	pop	bc		;	pop	bc
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_7028	;	call	_sub_7028
	pop	bc		;	pop	bc
	ld	l,(ix+-3)	;	ld	l,(ix+-3)
	ld	h,(ix+-2)	;	ld	h,(ix+-2)
	ld	(iy+19h),l	;	ld	(iy+25),l
	ld	(iy+1Ah),h	;	ld	(iy+26),h
	jp	loc_5EC0	;	jp	l14

; End of function sub_5DF6 OK++

	psect	data

p_5df6_1:
19:	; "-"
	defb	45,0

	psect	text

; End of file 5DF6.as


