*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 4C6D.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_4C6D OK+
;
; Could not find operators in C language generating code
; that exactly matches binary codes
;=========================================================
	global	_sub_4C6D	;	global	_sub_4C6D
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_4C6D:
	call	csv		;	call	csv
	ld	e, (ix+6)	;	ld	e,(ix+6)
	ld	d, (ix+7)	;	ld	d,(ix+7)
	ld	hl, 19h		;	ld	hl,25
	add	hl, de		;	add	hl,de
	ld	a, (hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h, (hl)		;	ld	h,(hl)
	ld	l, a		;	ld	l,a
	ld	a, (hl)		;	ld	a,(hl)
	cp	45h 		;	cp	69
	ld	hl, 1		;	jp	nz,l12	   <----+ Could not find
	jp	z, cret		;	ld	l,1		; operators in C
	dec	hl		;	jp	cret		; language generating
	jp	cret		;l12:				; code that exactly
				;	ld	l,0		; matches binary
				;	jp	cret	   <----+ codes

; End of function sub_4C6D OK+

; End of file 4C6D.as


	