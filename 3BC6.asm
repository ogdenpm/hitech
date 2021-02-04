*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 3BC6.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_3BC6 OK++
;
; Compiler generates identical code from restored source
; program in C, however, location of branches associated
; with case constants is different from original.
; This does not affect the function.
;=========================================================
	global	_sub_3BC6	;	global	_sub_3BC6
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	asalmod		;	global	asalmod
	global	asaland		;	global	asaland
	global	asalmul		;	global	asalmul
	global	asaladd		;	global	asaladd
	global	asalsub		;	global	asalsub
	global	asaldiv		;	global	asaldiv
	global	asallsh		;	global	asallsh
	global	asalrsh		;	global	asalrsh
	global	asalxor		;	global	asalxor
	global	asalor		;	global	asalor
	global 	csv		;	global 	csv

	psect	text

;	Disassembled version	; After compiling C source code	
_sub_3BC6:
	call	csv		;	call csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(ix+0Ch)	;	ld	l,(ix+12)
	ld	h,(ix+0Dh)	;	ld	h,(ix+13)
	ld	a,h		;	ld	a,h
	or	a		;	or	a
	jp	nz,cret		;	jp	nz,cret
	ld	a,l		;	ld	a,l
	cp	6		;	cp	6
	jp	z,loc_3C6B	;	jp	z,l4
	cp	7		;	cp	7
	jp	z,loc_3C99	;	jp	z,l5
	cp	0Ch		;	cp	12
	jr	z,loc_3C3D	;	jp	z,l6
	cp	0Eh		;	cp	14
	jr	z,loc_3C0F	;	jp	z,l7
	cp	12h		;	cp	18
	jr	z,loc_3C26	;	jp	z,l8
	cp	18h		;	cp	24
	jr	z,loc_3C54	;	jp	z,l9
	cp	1Fh		;	cp	31
	jp	z,loc_3CC7	;	jp	z,l10
	cp	2Fh		;	cp	47
	jp	z,loc_3CD3	;	jp	z,l11
	cp	3Ah		;	cp	58
	jp	z,loc_3CB0	;	jp	z,l12
	cp	3Ch		;	cp	60
	jp	z,loc_3C82	;	jp	z,l13
	jp	cret		;	jp	cret
loc_3C0F:			;l7:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	push	hl		;	push	hl
	push	de		;	push	de
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	call	asaladd		;	call	asaladd
	jp	cret		;	jp	cret
loc_3C26:			;l8:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	push	hl		;	push	hl
	push	de		;	push	de
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	call	asalsub		;	call	asalsub
	jp	cret		;	jp	cret
loc_3C3D:			;l6:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	push	hl		;	push	hl
	push	de		;	push	de
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	call	asalmul		;	call	asalmul
	jp	cret		;	jp	cret
loc_3C54:			;l9:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	push	hl		;	push	hl
	push	de		;	push	de
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	call	asaldiv		;	call	asaldiv
	jp	cret		;	jp	cret
loc_3C6B:			;l4:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	push	hl		;	push	hl
	push	de		;	push	de
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	call	asalmod		;	call	asalmod
	jp	cret		;	jp	cret
loc_3C82:			;l13:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	push	hl		;	push	hl
	push	de		;	push	de
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	call	asalor		;	call	asalor
	jp	cret		;	jp	cret
loc_3C99:			;l5:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	push	hl		;	push	hl
	push	de		;	push	de
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	call	asaland		;	call	asaland
	jp	cret		;	jp	cret
loc_3CB0:			;l12:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	push	hl		;	push	hl
	push	de		;	push	de
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	call	asalxor		;	call	asalxor
	jp	cret		;	jp	cret
loc_3CC7:			;l10:
	ld	b,(ix+8)	;	ld	b,(ix+8)
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	call	asallsh		;	call	asallsh
	jp	cret		;	jp	cret
loc_3CD3:			;l11:
	ld	b,(ix+8)	;	ld	b,(ix+8)
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	call	asalrsh		;	call	asalrsh
	jp	cret		;	jp	cret

; End of function sub_3BC6 OK+

; End of function 3BC6.as


