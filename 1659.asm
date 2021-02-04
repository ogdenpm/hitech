*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 1659.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_1659 OK++
;=========================================================
	global	_sub_1659	;	global	_sub_1659
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	wrelop		;	global	wrelop
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_1659:
	call	csv		;	call 	csv
	ld	e,(ix+6)	;	ld	e,(ix+6)
	ld	d,(ix+7)	;	ld	d,(ix+7)
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	call	wrelop		;	call	wrelop
	jp	m,loc_1677	;	jp	m,L2
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	jp	cret		;	jp	cret
loc_1677:			;L2:
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	jp	cret		;	jp	cret

; End of function sub_1659 OK++

; End of file - 1659.asm


