*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 415E.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_415E OK++
;=========================================================
	global	_sub_415E	;	global	_sub_415E
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_sub_3712	;	global	_sub_3712
	global	_word_AE11	;	global	_word_AE11
	global 	csv		;	global 	csv

	psect	text

_sub_415E:
; Disassembled version		; After compiling C source code
	call 	csv		;	call	csv
	call	_sub_3712	;	call	_sub_3712
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	(iy+0),43h	;	ld	(iy+0),67
	ld	hl,(_word_AE11)	;	ld	hl,(_word_AE11)
	ld	(iy+23),l	;	ld	(iy+17h),l
	ld	(iy+24),h	;	ld	(iy+18h),h
	ld	e,(ix+6)	;	ld	e,(ix+6)
	ld	d,(ix+7)	;	ld	d,(ix+7)
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	(iy+25),e	;	ld	(iy+19h),e
	ld	(iy+26),d	;	ld	(iy+1Ah),d
	ld	(iy+27),l	;	ld	(iy+1Bh),l
	ld	(iy+28),h	;	ld	(iy+1Ch),h
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	jp	cret		;	jp	cret

; End of function sub_415E OK++

; End of file 415E.asm


