*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 600E.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_600E OK++
;=========================================================
	global	_sub_600E	;	global	_sub_600E
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_word_B015	;	global	_word_B015
	global	_sub_5DF6	;	global	_sub_5DF6
	global	_byte_B013	;	global	_byte_B013
	global	_sub_3EAA	;	global	_sub_3EAA
	global	_sub_54B6	;	global	_sub_54B6
	global	_warning	;	global	_warning
	global	_sub_5F52	;	global	_sub_5F52
	global 	csv		;	global 	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_600E:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	hl,0		;	ld	hl,0
	ld	(_word_B015),hl	;	ld	(_word_B015),hl
	push	iy		;	push	iy
	call	_sub_5DF6	;	call	_sub_5DF6
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	(ix+-2),0	;	ld	(ix+-2),0
	ld	(ix+-1),0	;	ld	(ix+-1),0
loc_6032:			;l14:
	xor	a		;	xor	a
	ld	(_byte_B013),a	;	ld	(_byte_B013),a
	push	iy		;	push	iy
	call	_sub_54B6	;	call	_sub_54B6
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_3EAA	;	call	_sub_3EAA
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	a,(_byte_B013)	;	ld	a,(_byte_B013)
	or	a		;	or	a
	jr	nz,loc_6032	;	jp	nz,l14
	ld	hl,(_word_B015)	;	ld	hl,(_word_B015)
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	z,loc_6055	;	jp	z,l15
	push	hl		;	push	hl
	call	_warning	;	call	_warning
	pop	bc		;	pop	bc
loc_6055:			;l15:
	push	iy		;	push	iy
	call	_sub_5F52	;	call	_sub_5F52
	pop	bc		;	pop	bc
	jp	cret		;	jp	cret

; End of function sub_600E OK++

; End of file 600E.asm


