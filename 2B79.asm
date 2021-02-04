*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated with original code

; File - 2B79.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_2B79 OK++
;=========================================================
	global	_sub_2B79	;	global	_sub_2B79
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_byte_AFFA	;	global	_byte_AFFA
	global	_sub_2B2A	;	global	_sub_2B2A
	global	_sub_6589	;	global	_sub_6589
	global 	csv		;	global 	csv

	psect	text

; After compiling C source code	;	Disassembled version
_sub_2B79:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	push	hl		;	push	hl
	pop	de		;	pop	de
	ld	l,(iy+1)	;	ld	l,(iy+1)
	ld	h,0		;	ld	h,0
	add	hl,de		;	add	hl,de
	ld	de,8		;	ld	de,8
	add	hl,de		;	add	hl,de
	ld	l,(hl)		;	ld	l,(hl)
	ld	(ix+-1),l	;	ld	(ix+-1),l
	xor	a		;	xor	a
	ld	(_byte_AFFA),a	;	ld	(_byte_AFFA),a
	push	iy		;	push	iy
	call	_sub_2B2A	;	call	_sub_2B2A
	pop	bc		;	pop	bc
	ld	(ix+-3),l	;	ld	(ix+-3),l
	ld	(ix+-2),h	;	ld	(ix+-2),h
	ld	a,(ix+-1)	;	ld	a,(ix+-1)
	or	a		;	or	a
	jr	z,loc_2BC9	;	jp	z,l12
	ld	l,a		;	ld	l,a
	ld	h,0		;	ld	h,0
	push	hl		;	push	hl
	ld	l,(ix+-3)	;	ld	l,(ix+-3)
	ld	h,(ix+-2)	;	ld	h,(ix+-2)
	push	hl		;	push	hl
	call	_sub_6589	;	call	_sub_6589
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	a, l		;	ld	a,l
	cp	(ix+-1)		;	cp	(ix+-1)
	jr	nz,loc_2BC9	;	jp	nz,l12
	ld	l,(ix+-1)	;	ld	l,(ix+-1)
	jp	cret		;	jp	cret
loc_2BC9:			;l12:
	ld	a,(_byte_AFFA)	;	ld	a,(_byte_AFFA)
	ld	l,a		;	ld	l,a
	jp	cret		;	jp	cret

; End of function sub_2B79 OK++

;=========================================================
; sub_2BD0 OK++
;=========================================================
	global	_sub_2BD0		;global	_sub_2BD0
	global	_sub_1F4B		;global	_sub_1F4B
	global	_word_B017		;global	_word_B017
	global	wrelop			;global	wrelop
	global	_faterror		;global	_faterror
	global	_sub_35E6		;global	_sub_35E6
	global	_sub_B96		;global	_sub_B96
	global	_array_AEDB		;global	_array_AEDB
	global	_lvlidx			;global	_lvlidx
	global	_sub_1EDF		;global	_sub_1EDF
	global	_sub_475C		;global	_sub_475C
	global csv			;

; After compiling C source code	;	Disassembled version
_sub_2BD0:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	(iy+1),0	;	ld	(iy+1),0
	push	ix		;	push	ix
	pop	hl		;	pop	hl
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	push	hl		;	push	hl
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	ld	hl,(_word_B017)	;	ld	hl,(_word_B017)
	push	hl		;	push	hl
	ld	hl,48h		;	ld	hl,72
	push	hl		;	push	hl
	push	iy		;	push	iy
	call	_sub_1F4B	;	call	_sub_1F4B
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ex	de,hl		;	ex	de,hl
	ld	hl,0		;	ld	hl,0
	call	wrelop		;	call	wrelop
	jp	m,loc_2C0F	;	jp	m,l15
	ld	hl,19f		;	ld	hl,19f
	push	hl		;	push	hl
	call	_faterror	;	call	_faterror
	pop	bc		;	pop	bc
loc_2C0F:			;l15:
	push	iy		;	push	iy
	call	_sub_35E6	;	call	_sub_35E6
	pop	bc		;	pop	bc
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	1Ah		;	cp	26
	jp	nz,loc_2C56	;	jp	nz,l16
	bit	1,(iy+15h)	;	bit	1,(iy+21)
	jr	z,loc_2C3D	;	jp	z,l17
	ld	de,_array_AEDB	;	ld	de,_array_AEDB
	ld	hl,(_lvlidx)	;	ld	hl,(_lvlidx)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	hl,11h		;	ld	hl,17
	add	hl,bc		;	add	hl,bc
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	call	_sub_B96	;	call	_sub_B96
	pop	bc		;	pop	bc
	call	_sub_1EDF	;	call	_sub_1EDF
loc_2C3D:			;l17:
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ld	a,(hl)		;	ld	a,(hl)
	cp	42h		;	cp	66
	jr	nz,loc_2C56	;	jp	nz,l16
	ex	de,hl		;	ex	de,hl
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	set	0,(hl)		;	set	0,(hl)
loc_2C56:			;l16:
	push	iy		;	push	iy
	call	_sub_475C	;	call	_sub_475C
	jp	cret		;	jp	cret

; End of function sub_2BD0 OK++

	psect	data

p_2bd0_1:
; 		"Expression too complicated"
19:	defb	69,120,112,114,101,115,115,105,111,110,32,116,111,111,32,99
	defb	111,109,112,108,105,99,97,116,101,100,0

	psect	text

; End of file 2B79.as



