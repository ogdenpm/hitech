*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 4BE5.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_4BE5 OK++
;=========================================================
	global	_sub_4BE5	;	global	_sub_4BE5
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global 	csv		;	global 	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_4BE5:
	call 	csv		;	call	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	67		;	cp	43h
	jr	nz,loc_4C0C	;	jp	nz,L13
	ld	a,(iy+25)	;	ld	a,(iy+19h)
	or	(iy+26)		;	or	(iy+1Ah)
	or	(iy+27)		;	or	(iy+1Bh)
	or	(iy+28)		;	or	(iy+1Ch)
	jr	nz,loc_4C0C	;	jr	nz,L13
	ld	hl,1		;	ld	hl,1
	jp	cret		;	jp	cret
loc_4C0C:			;L13:
	ld	hl,0		;	ld	hl,0
	jp	cret		;	jp	cret

; End of function sub_4BE5 OK++

;=========================================================
; sub_4C12 OK++
;=========================================================
	global	_sub_4C12	;	global	_sub_4C12
	global	_dopetab	;	global	_dopetab
	global	_sub_4B89	;	global	_sub_4B89
	global 	csv

; Disassembled version		; After compiling C source code
_sub_4C12:
	call	csv		;	call 	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	9		;	cp	9
	jr	nz,loc_4C36	;	jp	nz,l16
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ld	a,(hl)		;	ld	a,(hl)
	cp	42h		;	cp	66
	jr	nz,loc_4C36	;	jp	nz,l16
loc_4C30:			;L1:
	ld	hl,1		;	ld	hl,1
	jp	cret		;	jp	cret
loc_4C36:			;l16:
	ld	de,_dopetab	;	ld	de,_dopetab
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	bit	4,c		;	bit	4,c
	jr	z,loc_4C4D	;	jp	z,l18
	ld	hl,0		;	ld	hl,0
	jp	cret		;	jp	cret
loc_4C4D:			;l18:
	push	iy		;	push	iy
	call	_sub_4B89	;	call	_sub_4B89
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	or	a		;	or	h
	jr	nz,loc_4C30	;	jp	nz,L1
	ld	de,_dopetab	;	ld	de,_dopetab
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	a,c		;	ld	a,c
	and	0Fh		;	and	15
	ld	l,a		;	ld	l,a
	xor	a		;	xor	a
	ld	h,a		;	ld	h,a
	jp	cret		;	jp	cret

; End of function sub_4C12 OK++

; End of file 4BE5.as


