*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated with original code

; File - 3EAA.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_3EAA OK+
;
; From source in C, compiler generates code that performs
; expected action, but differs from original image
;=========================================================
	global	_sub_3EAA	;	global	_sub_3EAA
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_dopetab	;	global	_dopetab
	global	_sub_14F3	;	global	_sub_14F3
	global	_sub_36E0	;	global	_sub_36E0
	global	_sub_39CA	;	global	_sub_39CA
	global	_word_B015	;	global	_word_B015
	global	_sub_3B65	;	global	_sub_3B65
	global	_sub_475C	;	global	_sub_475C
	global	_sub_3A79	;	global	_sub_3A79
	global	_sub_3BC6	;	global	_sub_3BC6
	global	alsub		;	global	alsub
	global 	csv		;	global 	csv

	psect	text

;	Disassembled version	; After compiling C source code	
_sub_3EAA:
	call	csv		;	call csv
	push	hl		;	push hl
	push	hl		;	push hl
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
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	z,loc_3EE6	;	jp	z,l12
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_3EAA	;	call	_sub_3EAA
	pop	bc		;	pop	bc
	ld	(iy+19h),l	;	ld	(iy+25),l
	ld	(iy+1Ah),h	;	ld	(iy+26),h
loc_3EE6:			;l12:				;m1:
	ld	de,8		;	ld	de,8
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_3F05	;	jp	nz,l13
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	call	_sub_3EAA	;	call	_sub_3EAA
	pop	bc		;	pop	bc
	ld	(iy+1Bh),l	;	ld	(iy+27),l
	ld	(iy+1Ch),h	;	ld	(iy+28),h
loc_3F05:			;l13:				; m2:
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	14h		;	cp	20
	jr	nz,loc_3F5B	;	jp	nz,l14
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ld	a,(hl)		;	ld	a,(hl)
	cp	44h		;	cp	68
	jr	nz,loc_3F5B	;	jp	nz,l14
	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	3		;	cp	3
	jr	nz,loc_3F5B	;	jp	nz,l14
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,17h		;	ld	hl,23
	add	hl,de		;	add	hl,de
	ld	e,(iy+17h)	;	ld	e,(iy+23)
	ld	d,(iy+18h)	;	ld	d,(iy+24)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	push	iy		;	push	iy
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	jp	cret		;	jp	cret
loc_3F5B:			;l14:				; m3:
	ld	a,(ix+-4)	;	ld	a,(ix+-4)
	or	(ix+-3)		;	or	(ix+-3)
	jr	z,loc_3F6E	;	jp	z,L11
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ld	a,(hl)		;	ld	a,(hl)
	cp	43h		;	cp	67
	jr	z,loc_3F74	;	jp	z,l18
loc_3F6E:			;L11:
	push	iy		;	push	iy		; Label 
loc_3F70:			;			   <----+ deleted
	pop	hl		;	pop	hl		; by optimizer
	jp	cret		;	jp	cret
loc_3F74:			;l18:
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	14h		;	cp	20
	jr	nz,loc_3F84	;	jp	nz,l19
	push	iy		;	push	iy
	call	_sub_39CA	;	call	_sub_39CA
	pop	bc		;	pop	bc
	jp	cret		;	jp	cret
loc_3F84:			;l19:
	ld	de,8		;	ld	de,8
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_3FA1	;	jp	nz,l21
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	ld	a,(hl)		;	ld	a,(hl)
	cp	43h		;	cp	67
	push	iy		;			   <----+
	jr	z,loc_3FA3	;	jp	nz,L11		: Result of 
	jr	loc_3F70	;				: optimizer 
loc_3FA1:			;l21:				: pass
	push	iy		;	push	iy		:
loc_3FA3:			;			   <----+
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	2		;	cp	2
	ld	a,(iy+0)	;	ld	a,(iy+0)
	jr	nz,loc_3FD2	;	jp	nz,L5
	cp	6		;	cp	6
	jp	z,loc_4048	;	jp	z,l26
	cp	18h		;	cp	24
	jp	z,loc_4048	;	jp	z,l26
	cp	1Eh		;	cp	30
	jp	z,loc_4040	;	jp	z,l29
	cp	20h		;	cp	32
	jp	z,loc_4040	;	jp	z,l29
	cp	2Dh		;	cp	45
	jp	z,loc_4040	;	jp	z,l29
	cp	2Eh		;	cp	46
	jp	z,loc_4040	;	jp	z,l29
	cp	2Fh		;	cp	47
	jp	z,loc_4048	;	jp	z,l26
loc_3FD2:			;L3:
	cp	1		;	cp	1			
	jp	z,loc_4117	;	jp	z,l35		; Possibly
				;	ld	a,(iy+0)    <---+ deleted 
	cp	2		;	cp	2		; manually
	jp	z,loc_40AA	;	jp	z,l37
	cp	6		;	cp	6
	jp	z,loc_40AF	;	jp	z,l39
	cp	7		;	cp	7
	jp	z,loc_40AF	;	jp	z,l39
	cp	8		;	cp	8
	jp	z,loc_40AF	;	jp	z,l39
	cp	0Ch		;	cp	12
	jp	z,loc_40AF	;	jp	z,l39
	cp	0Eh		;	cp	14
	jp	z,loc_40AF	;	jp	z,l39
	cp	12h		;	cp	18
	jp	z,loc_40AF	;	jp	z,l39
	cp	15h		;	cp	21
	jp	z,loc_40DD	;	jp	z,l46
	cp	18h		;	cp	24
	jp	z,loc_40AF	;	jp	z,l39
	cp	1Eh		;	cp	30
	jp	z,loc_40AA	;	jp	z,l37
	cp	1Fh		;	cp	31
	jp	z,loc_40AF	;	jp	z,l39
	cp	20h		;	cp	32
	jp	z,loc_40AA	;	jp	z,l37
	cp	29h		;	cp	41
	jp	z,loc_40AA	;	jp	z,l37
	cp	2Dh		;	cp	45
	jp	z,loc_40AA	;	jp	z,l37
	cp	2Eh		;	cp	46
	jp	z,loc_40AA	;	jp	z,l37
	cp	2Fh		;	cp	47
	jp	z,loc_40AF	;	jp	z,l39
	cp	3Ah		;	cp	58
	jp	z,loc_40AF	;	jp	z,l39
	cp	3Ch		;	cp	60
	jp	z,loc_40AF	;	jp	z,l39
	cp	3Dh		;	cp	61
	jp	z,loc_40AF	;	jp	z,l39
	cp	3Fh		;	cp	63
	jp	z,loc_413A	;	jp	z,l59
loc_403B:			;			    <---+ Optimization 
	push	iy		;			    	; pass built a 
	jp	loc_3F70	;	jp	L11	    <---+ more optimal 
loc_4040:			;l32:				: code
	ld	hl,19f		;	ld	hl,19f		:
loc_4043:			;L12:				:
	ld	(_word_B015),hl	;	ld	(_word_B015),hl	:
	jr	loc_403B	;	jp	L11	    <---+
loc_4048:			;l29:
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,0		;	ld	h,0
	push	hl		;	push	hl
	ld	e,(iy+1Bh)	;	ld	e,(iy+27)
	ld	d,(iy+1Ch)	;	ld	d,(iy+28)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	inc	hl		;	inc	hl
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	push	hl		;	push	hl
	call	_sub_3B65	;	call	_sub_3B65
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
loc_4074:			;l63:
	ld	de,8		;	ld	de,8
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_408D	;	jp	nz,l64
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	call	_sub_475C	;	call	_sub_475C
	pop	bc		;	pop	bc
loc_408D:			;l64:
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	push	iy		;	push	iy
	call	_sub_3A79	;	call	_sub_3A79
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	push	iy		;	push	iy
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	jp	cret		;	jp	cret
loc_40AA:			;l40:
	ld	hl,29f		;	ld	hl,29f
	jr	loc_4043	;	jp	L12
loc_40AF:			;l42:
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,0		;	ld	h,0
	push	hl		;	push	hl
	ld	e,(iy+1Bh)	;	ld	e,(iy+27)
	ld	d,(iy+1Ch)	;	ld	d,(iy+28)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	inc	hl		;	inc	hl
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	push	hl		;	push	hl
	call	_sub_3BC6	;	call	_sub_3BC6
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	jr	loc_4074	;	jp	l63
loc_40DD:			;l49:
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	inc	hl		;	inc	hl
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	push	hl		;	push	hl
	push	de		;	push	de
	ld	hl,0		;	ld	hl,0
	pop	bc		;	pop	bc
	or	a		;	or	a
	sbc	hl,bc		;	sbc	hl,bc
	pop	bc		;	pop	bc
	ex	de,hl		;	ex	de,hl
	ld	hl,0		;	ld	hl,0
	sbc	hl,bc		;	sbc	hl,bc
loc_40FF:			;L8:
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	pop	de		;	pop	de
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	inc	hl		;	inc	hl
	pop	bc		;	pop	bc
	ld	(hl),c		;	ld	(hl),c
	inc	hl		;	inc	hl
	ld	(hl),b		;	ld	(hl),b
	jp	loc_4074	;	jp	l63
loc_4117:			;l38:
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	inc	hl		;	inc	hl
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	ld	a,e		;	ld	a,e
	or	d		;	or	d
	or	l		;	or	l
	or	h		;	or	h
	ld	de,1		;			   <----+
	jr	z,loc_4133	;	jp	z,L2		; Could not find
	dec	de		;	ld	de,0		; operators in
loc_4133:			;L10:				; C language
	ld	a,d		;	ld	hl,0		; generating 
	rla			;	jp	L8		; code that
	sbc	a,a		;L2:				; exactly matches
	ld	l,a		;	ld	de,1		; binary codes
	ld	h,a		;	jp	L10		;
	jr	loc_40FF	;			   <----+
loc_413A:			;l62:
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	inc	hl		;	inc	hl
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	push	hl		;	push	hl
	push	de		;	push	de
	ld	hl,0FFFFh	;	ld	de,-1	   <----+ At this point,
	pop	bc		;	ld	l,e		; from source
	or	a		;	ld	h,d		; in C, compiler
	sbc	hl,bc		;	call	alsub		; generates code
	pop	bc		;				; that performs
	ex	de,hl		;				; expected action,
	ld	hl,0FFFFh	;				; but differs from 
	sbc	hl,bc		;			   <----+ original image
	jr	loc_40FF	;	jp	L8

; End of function sub_3EAA OK+

	psect	data

p_3eaa_A9D0:
19:
	defb	99,111,110,115,116,97,110,116,32,114,101,108,97,116,105,111
	defb	110,97,108,32,101,120,112,114,101,115,115,105,111,110,0

p_3eaa_A9EF:
29:
	defb	99,111,110,115,116,97,110,116,32,114,101,108,97,116,105,111
	defb	110,97,108,32,101,120,112,114,101,115,115,105,111,110,0

	psect	text

; End of file 3EAA.as


