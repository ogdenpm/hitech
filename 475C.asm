*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 475C.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_475C OK++
;=========================================================
	global	_sub_475C	;	global	_sub_475C
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_dopetab	;	global	_dopetab
	global	_sub_36E0	;	global	_sub_36E0
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_475C:
	call	csv		;	call 	csv
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
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	a,c		;	ld	a,c
	and	0Ch		;	and	12
	ld	l,a		;	ld	l,a
	xor	a		;	xor	a
	ld	h,a		;	ld	h,a
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	z,loc_47AA	;	jp	z,l12
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_475C	;	call	_sub_475C
	pop	bc		;	pop	bc
	ld	de,8		;	ld	de,8
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_47AA	;	jp	nz,l12
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	call	_sub_475C	;	call	_sub_475C
	pop	bc		;	pop	bc
loc_47AA:			;l12:
	push	iy		;	push	iy
	call	_sub_36E0	;	call	_sub_36E0
	jp	cret		;	jp	cret

; End of function sub_475C OK++

; End of file 475C.asm


