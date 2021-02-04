*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 1680.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_1680 OK++
;=========================================================
	global	_sub_1680	;	global	_sub_1680
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_blkclr		;	global	_blkclr
	global	_hashtab	;	global	_hashtab
	;global	_vars		;	global	_vars
	global	_sub_265	;	global	_sub_265
	global	_word_AE11	;	global	_word_AE11
	global	_word_AED7	;	global	_word_AED7
	global	_word_AF1B	;	global	_word_AF1B
	global	_word_AFE9	;	global	_word_AFE9
	global	_word_AED9	;	global	_word_AED9
	global	_word_AE53	;	global	_word_AE53
	global	_word_AF1D	;	global	_word_AF1D
	global	_lvlidx		;	global	_lvlidx
	global	csv

	psect	data
d_vars_a850:
F609:
	defw	319f
	defw	2
	defw	0
	defb	1
	defw	329f
	defw	2
	defw	0
	defb	1
	defw	339f
	defw	1
	defw	0
	defb	1
	defw	349f
	defw	4
	defw	0
	defb	1
	defw	359f
	defw	2
	defw	0
	defb	2
	defw	369f
	defw	2
	defw	0
	defb	2
	defw	379f
	defw	1
	defw	0
	defb	2
	defw	389f
	defw	4
	defw	0
	defb	2
	defw	399f
	defw	4
	defw	0
	defb	3
	defw	3109f
	defw	4
	defw	0
	defb	3
	defw	3119f
	defw	2
	defw	0
	defb	1
	defw	3129f
	defw	2
	defw	0
	defb	2
	defw	3139f
	defw	0
	defw	0
	defb	0
	defw	3149f
	defw	0
	defw	0
	defb	0

	psect	text

_sub_1680:

	call	csv		;	call csv
	push	hl		;	push hl
	push	hl		;	push hl
	ld	hl,202		;	ld	hl,202
	push	hl		;	push	hl
	ld	hl,_hashtab	;	ld	hl,_hashtab
	push	hl		;	push	hl
	call	_blkclr		;	call	_blkclr
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(ix+-4),14	;	ld	(ix+-4),14
	ld	(ix+-3),0	;	ld	(ix+-3),0
	ld	iy,F609		;	ld	iy,_vars
loc_169E:			;l14:
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,(iy+1)	;	ld	h,(iy+1)
	push	hl		;	push	hl
	call	_sub_265	;	call	_sub_265
	pop	bc		;	pop	bc
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	(hl),65		;	ld	(hl),65
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,17		;	ld	hl,17
	add	hl,de		;	add	hl,de
	ld	e,(iy+4)	;	ld	e,(iy+4)
	ld	d,(iy+5)	;	ld	d,(iy+5)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,9		;	ld	hl,9
	add	hl,de		;	add	hl,de
	ld	e,(iy+2)	;	ld	e,(iy+2)
	ld	d,(iy+3)	;	ld	d,(iy+3)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	a,(iy+6)	;	ld	a,(iy+6)
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,21		;	ld	hl,21
	add	hl,de		;	add	hl,de
	ld	(hl),a		;	ld	(hl),a
	ld	de,7		;	ld	de,7
	add	iy,de		;	add	iy,de
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	dec	hl		;	dec	hl
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	ld	a,l		;	ld	a,l
	or	h		;	or	(ix+-3)		  ; Error
	jr	nz,loc_169E	;	jp	nz,l14
	ld	hl,19f		;	ld	hl,19f
	push	hl		;	push	hl
	call	_sub_265	;	call	_sub_265
	ld	(_word_AE11),hl	;	ld	(_word_AE11),hl
	ld	hl,29f		;	ld	hl,29f
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_265	;	call	_sub_265
	ld	(_word_AED7),hl	;	ld	(_word_AED7),hl
	ld	hl,39f		;	ld	hl,39f
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_265	;	call	_sub_265
	ld	(_word_AF1B),hl	;	ld	(_word_AF1B),hl
	ld	hl,49f		;	ld	hl,49f
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_265	;	call	_sub_265
	ld	(_word_AFE9),hl	;	ld	(_word_AFE9),hl
	ld	hl,59f		;	ld	hl,59f
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_265	;	call	_sub_265
	ld	(_word_AED9),hl	;	ld	(_word_AED9),hl
	ld	hl,69f		;	ld	hl,69f
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_265	;	call	_sub_265
	ld	(_word_AE53),hl	;	ld	(_word_AE53),hl
	ld	hl,79f		;	ld	hl,79f
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_265	;	call	_sub_265
	ld	(_word_AF1D),hl	;	ld	(_word_AF1D),hl
	ld	hl,-1		;	ld	hl,-1
	ld	(_lvlidx),hl	;	ld	(_lvlidx),hl
	jp	cret		;	jp	cret

	psect	data

d_vars_A8B2:
319:	defb	105,0

d_vars_A8B4:
329:	defb	115,0

d_vars_A8B6:
339:	defb	99,0

d_vars_A8B8:
349:	defb	108,0

d_vars_A8BA:
359:	defb	117,105,0

d_vars_A8BD:
369:	defb	117,115,0

d_vars_A8C0:
379:	defb	117,99,0

d_vars_A8C3:
389:	defb	117,108,0

d_vars_A8C6:
399:	defb	102,0

d_vars_A8C8:
3109:	defb	100,0

d_vars_A8CA:
3119:	defb	120,0

d_vars_A8CC:
3129:	defb	117,120,0

d_vars_A8CF:
3139:	defb	98,0

d_vars_A8D1:
3149:	defb	118,0


	psect	text

; End of function sub_1680 OK+

;=========================================================
; sub_174C OK++
;=========================================================
	global	_sub_174C	;	global	_sub_174C
	global	_word_AE0F	;	global	_word_AE0F

_sub_174C:
	ld	hl,(_word_AE0F)	;	ld	hl,(_word_AE0F)
	inc	hl		;	inc	hl
	ld	(_word_AE0F),hl	;	ld	(_word_AE0F),hl
	ret			;	ret

;=========================================================
; sub_1754 OK++
;=========================================================
	global	_sub_1754	;	global	_sub_1754
	global	_nstdpth	;	global	_nstdpth
	global	_gethashptr	;	global	_gethashptr
	global	_allocmem	;	global	_allocmem
	global	_strlen		;	global	_strlen
	global	_strcpy		;	global	_strcpy
	global csv

_sub_1754:
	call csv		;	call	csv
	push hl			;	push	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	call	_sub_265	;	call	_sub_265
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	de,(_nstdpth)	;	ld	de,(_nstdpth)
	ld	l,(iy+4)	;	ld	l,(iy+4)
	ld	h,0		;	ld	h,0
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	z,loc_17D4	;	jp	z,l17
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	call	_gethashptr	;	call	_gethashptr
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	hl,22		;	ld	hl,22
	ex	(sp),hl		;	ex	(sp),hl
	call	_allocmem	;	call	_allocmem
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+7),c	;	ld	(iy+7),c
	ld	(iy+8),b	;	ld	(iy+8),b
	push	iy		;	push	iy
	pop	de		;	pop	de
	dec	hl		;	dec	hl
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	call	_strlen		;	call	_strlen
	pop	bc		;	pop	bc
	inc	hl		;	inc	hl
	push	hl		;	push	hl
	call	_allocmem	;	call	_allocmem
	ld	(iy+0),l	;	ld	(iy+0),l
	ld	(iy+1),h	;	ld	(iy+1),h
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,(iy+1)	;	ld	h,(iy+1)
	push	hl		;	push	hl
	call	_strcpy		;	call	_strcpy
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	a,(_nstdpth)	;	ld	a,(_nstdpth)
	ld	(iy+4),a	;	ld	(iy+4),a
loc_17D4:			;l17:
	ld	a,(ix+8)	;	ld	a,(ix+8)
	ld	(iy+2),a	;	ld	(iy+2),a
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	jp	cret		;	jp	cret

	psect	data

p_1680_1:
19:	defb	108,0

p_1680_2:
29:	defb	100,0

p_1680_3:
39:	defb	98,0

p_1680_4:
49:	defb	118,0

p_1680_5:
59:	defb	99,0

p_1680_6:
69:	defb	117,99,0

p_1680_7:
79:	defb	120,0

	psect	text

; End of function sub_1754 OK++

; End of file - 1680.asm

