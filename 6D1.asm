*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 6D1.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_6D1
;
; Compiler generates identical code from restored source
; program in C, however, location of branches associated
; with case constants is different from original.
; This does not affect the function.
;=========================================================

	global	d_6c8_A3B6

	global	_sub_6D1	;	global	_sub_6D1
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_word_B017	;	global	_word_B017
	global	_sub_E43	;	global	_sub_E43
	global	_sub_793	;	global	_sub_793
	global	_sub_1B0C	;	global	_sub_1B0C
	global	_selpsect	;	global	_selpsect
	global	_sub_3DC9	;	global	_sub_3DC9
	global	_sub_4192	;	global	_sub_4192
	global	_sub_76F	;	global	_sub_76F
	global	_sub_B19	;	global	_sub_B19
	global	_sub_19C1	;	global	_sub_19C1
	global	_sub_17E0	;	global	_sub_17E0
	global	_nstdpth	;	global	_nstdpth
	global	_sub_406	;	global	_sub_406
	global	_sub_6C8	;	global	_sub_6C8
	global	_sub_1B2	;	global	_sub_1B2
	global	_sub_306	;	global	_sub_306
	global	csv

	psect	text

;	Disassembled version	; After compiling C source code
_sub_6D1:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	ld	hl,17Fh		;	ld	hl,383
	ld	(_word_B017),hl	;	ld	(_word_B017),hl
loc_6DB:			;l15:
	call	_sub_306	;	call	_sub_306
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	de, -1		;	ld	de, -1
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_6EF	;	jp	nz,l16
	call	_sub_406	;	call	_sub_406
	jp	cret		;	jp	cret
loc_6EF:			;l16:
	push	iy		;	push	iy
	call	_sub_1B2	;	call	_sub_1B2
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	(ix+-2),e	;	ld	(ix+-2),e
	ld	(ix+-1),d	;	ld	(ix+-1),d
	ld	hl,0FFCEh	;	ld	hl,-50
	add	hl,de		;	add	hl,de
	xor	a		;	xor	a
	cp	h		;	cp	h
	jp	c,loc_769	;	jp	c,l30
	jr	nz,loc_710	;	jp	nz,L1
	ld	a,0Ch		;	ld	a,12
	cp	l		;	cp	l
	jr	c,loc_769	;	jp	c,l30
loc_710:			;L1:
	add	hl,hl		;	add	hl,hl
	ld	de,off_A39C	;	ld	de,S162
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	jp	(hl)		;	jp	(hl)
loc_71A:			;l25:
	ld	hl,(_nstdpth)	;	ld	hl,(_nstdpth)
	inc	hl		;	inc	hl
	ld	(_nstdpth),hl	;	ld	(_nstdpth),hl
	jr	loc_6DB		;	jp	l15
loc_723:			;l26:
	call	_sub_406	;	call	_sub_406
	jr	loc_6DB		;	jp	l15
loc_728:			;l20:
	ld	hl,2		;	ld	hl,2
	push	hl		;	push	hl
	call	_selpsect	;	call	_selpsect
	pop	bc		;	pop	bc
	call	_sub_4192	;	call	_sub_4192
	push	hl		;	push	hl
	call	_sub_3DC9	;	call	_sub_3DC9
	ld	hl,5Dh		;	ld	hl,93
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_76F	;	call	_sub_76F
loc_73E:			;L2:
	pop	bc		;	pop	bc
	jr	loc_6DB		;	jp	l15
loc_741:			;l24:
	call	_sub_17E0	;	call	_sub_17E0
	jr	loc_6DB		;	jp	l15
				;l22:
loc_746:			;l23:
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;push	hl
	call	_sub_19C1	;	call	_sub_19C1
	jr	loc_73E		;	jp	L2
loc_752:			;l17:
	call	_sub_E43	;	call	_sub_E43
	jr	loc_6DB		;	jp	l15
loc_757:			;l19:
	call	_sub_1B0C	;	call	_sub_1B0C
	jp	loc_6DB		;	jp	l15
loc_75D:			;l21:
	call	_sub_B19	;	call	_sub_B19
	jp	loc_6DB		;	jp	l15
loc_763:			;l18:
	call	_sub_793	;	call	_sub_793
	jp	loc_6DB		;	jp	l15
				;l27:
				;l28:
				;l29:
loc_769:			;l30:
	call	_sub_6C8	;	call	_sub_6C8
	jp	loc_6DB		;	jp	l15

; End of function _sub_6D1 OK+

	psect	data

off_A39C:				
	defw	loc_752		;	defw	l17
	defw	loc_763		;	defw	l18
	defw	loc_757		;	defw	l19
	defw	loc_728		;	defw	l20
	defw	loc_75D		;	defw	l21
	defw	loc_746		;	defw	l22
	defw	loc_746		;	defw	l23
	defw	loc_741		;	defw	l24
	defw	loc_769		;	defw	l27
	defw	loc_71A		;	defw	l25
	defw	loc_769		;	defw	l28
	defw	loc_769		;	defw	l29
	defw	loc_723		;	defw	l26

d_6c8_A3B6:
19:	;	"Bad int. code"
	defb	66,97,100,32,105,110,116,46,32,99,111,100,101,0

	psect	text

; End of file 6D1.asm


