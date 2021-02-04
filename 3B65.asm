*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 3B65.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_3B65 OK++
;=========================================================
	global	_sub_3B65	;	global	_sub_3B65
	global  ncsv,cret,indir	;	global	ncsv, cret, indir
	global	asllmod		;	global	aslldiv
	global	aslldiv		;	global	asllmod
	global	asllrsh		;	global	asllrsh
	global 	csv		;	global 	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_3B65:
	call	csv		;	call 	csv
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
	jr	z,loc_3BA3	;	jp	z,l4	<---- Code difference
	cp	18h		;	cp	24
	jr	z,loc_3B8C	;	jp	z,l5	<---- Code difference
	cp	2Fh		;	cp	47
	jr	z,loc_3BBA	;	jp	z,l6	<---- Code difference
	jp	cret		;	jp	cret
loc_3B8C:			;l4:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	push	hl		;	push	hl
	push	de		;	push	de
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	call	aslldiv		;	call	aslldiv
	jp	cret		;	jp	cret
loc_3BA3:			;l5:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	l,(ix+0Ah)	;	ld	l,(ix+10)
	ld	h,(ix+0Bh)	;	ld	h,(ix+11)
	push	hl		;	push	hl
	push	de		;	push	de
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	call	asllmod		;	call	asllmod
	jp	cret		;	jp	cret
loc_3BBA:			;l6:
	ld	b,(ix+8)	;	ld	b,(ix+8)
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	call	asllrsh		;	call	asllrsh
	jp	cret		;	jp	cret

; End of function sub_3B65 OK++

; End of file 3B65.as


