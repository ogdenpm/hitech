*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 4FCE.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_4FCE OK+
;
; Compiler generates identical code from restored source
; program in C, however, location of branches associated
; with case constants is different from original.
; This does not affect the function.
;=========================================================
	global	_sub_4FCE	;	global	_sub_4FCE
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	asalsub		;	global	asalsub
	global	_sub_14F3	;	global	_sub_14F3
	global	_byte_B013	;	global	_byte_B013
	global	_sub_46F7	;	global	_sub_46F7
	global 	csv		;	global 	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_4FCE:
	call	csv		;	call 	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	6		;	cp	6
	jp	z,loc_5084	;	jp	z,l14
	cp	0Ch		;	cp	12
	jr	z,loc_503B	;	jp	z,l15
	cp	18h		;	cp	24
	jr	z,loc_5047	;	jp	z,l16
	cp	22h		;	cp	34
	jp	z,loc_5069	;	jp	z,l18
	cp	24h		;	cp	36
	jr	z,loc_5041	;	jp	z,l19
	cp	27h		;	cp	39
	jr	z,loc_5058	;	jp	z,l20
loc_4FF7:			;l12:
	ld	a,1		;	ld	a,1
	ld	(_byte_B013),a	;	ld	(_byte_B013),a
	ld	e,(iy+1Bh)	;	ld	e,(iy+27)
	ld	d,(iy+1Ch)	;	ld	d,(iy+28)
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
	call	_sub_46F7	;	call	_sub_46F7
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	e,l		;	ld	e,l
	ld	d,0		;	ld	d,0
	ld	hl,-1		;	ld	hl,-1
	add	hl,de		;	add	hl,de
	ex	de,hl		;	ex	de,hl
	ld	hl,0		;	ld	hl,0
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
loc_5035:			;L4:
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	jp	cret		;	jp	cret
loc_503B:			;l15:
	ld	(iy+0),1Fh	;	ld	(iy+0),31
	jr	loc_4FF7	;	jp	l12
loc_5041:			;l19:
	ld	(iy+0),28h	;	ld	(iy+0),40
	jr	loc_4FF7	;	jp	l12
loc_5047:			;l16:
	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	2		;	cp	2
	jr	nz,loc_5035	;	jp	nz,L4
	ld	(iy+0),2Fh	;	ld	(iy+0),47
	jr	loc_4FF7	;	jp	l12
loc_5058:			;l20:
	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	2		;	cp	2
	jr	nz,loc_5035	;	jp	nz,L4
	ld	(iy+0),2Ah	;	ld	(iy+0),42
	jr	loc_4FF7	;	jp	l12
loc_5069:			;l18:
	ld	(iy+0),23h	;	ld	(iy+0),35
				;	jp	L5
				;l14:
				;	ld	(iy+0),7
loc_506D:			;L5:
	ld	de,1		;	ld	de,1
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(iy+1Bh)	;	ld	e,(iy+27)
	ld	d,(iy+1Ch)	;	ld	d,(iy+28)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	call	asalsub		;	call	asalsub
	jr	loc_5035	;	jp	L4
loc_5084:			;
	ld	(iy+0),7	;
	jr	loc_506D	;

; End of function sub_4FCE OK+

; End of file 4FCE.as
