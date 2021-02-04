*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 605E.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_605E OK++
;=========================================================
	global	_sub_605E	;	global	_sub_605E
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_605E:
	call	csv		;	call 	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	ld	a,h		;	ld	a,h
	or	a		;	or	a
	jr	nz,loc_6084	;	jp	nz,l12
	ld	a,l		;	ld	a,l
	cp	2		;	cp	2
	jr	z,loc_6084	;	jp	z,l12
	cp	1Eh		;	cp	30
	jr	z,loc_6090	;	jp	z,l15
	cp	20h		;	cp	32
	jr	z,loc_6096	;	jp	z,l16
	cp	29h		;	cp	41
	jr	z,loc_608A	;	jp	z,l17
	cp	2Dh		;	cp	45
	jr	z,loc_60A2	;	jp	z,l18
	cp	2Eh		;	cp	46
	jr	z,loc_609C	;	jp	z,l19
loc_6084:			;l12:
	ld	hl,29h		;	ld	hl,41
	jp	cret		;	jp	cret
loc_608A:			;l17:
	ld	hl,2		;	ld	hl,2
	jp	cret		;	jp	cret
loc_6090:			;l15:
	ld	hl,2Eh		;	ld	hl,46
	jp	cret		;	jp	cret
loc_6096:			;l16:
	ld	hl,2Dh		;	ld	hl,45
	jp	cret		;	jp	cret
loc_609C:			;l19:
	ld	hl,1Eh		;	ld	hl,30
	jp	cret		;	jp	cret
loc_60A2:			;l18:
	ld	hl,20h		;	ld	hl,32
	jp	cret		;	jp	cret

; Compiler generates identical code from restored source
; program in C, however, location of branches associated
; with case constants is different from original.
; This does not affect the function.

; End of function sub_605E

; End of file 605E.asm


