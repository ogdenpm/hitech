*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 13D.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_13D OK+
;
; The C source is the ver.3 that is closest to  binary code.
; It does not create unnecessary unconditional jumps.
;=========================================================
	global	_array_987D	;	global	_array_987D
	global	_array_990D	;	global	_array_990D
	global	_array_9BD4	;	global	_array_9BD4
	global	_sub_13D	;	global	_sub_13D
	global	ncsv,cret,indir	;	global	csv

	psect	text

;	Disassembled version	; After compiling C source code
_sub_13D:
	call	ncsv		;	call 	csv
	defw	f159		;	push 	hl
	ld	de,_array_987D	;	ld	de,_array_987D
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-2),c	;	ld	(ix+-2),c
	ld	(ix+-1),b	;	ld	(ix+-1),b
	jp	loc_166		;	jp	l15
loc_159:			;l14:
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	inc	hl		;	inc	hl
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
loc_166:			;l15:
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,_array_990D	;	ld	hl,_array_990D
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	or	a		;	or	a
	jp	nz,loc_178	;	jp	z,l14
	jp	loc_194		;
loc_178:			;
	ld	e,(ix+-2)	;
	ld	d,(ix+-1)	;
	ld	hl,_array_990D	;	ld	hl,_array_990D
	add	hl,de		;	add	hl,de
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	ld	e,(ix+6)	;	ld	e,(ix+6)
	ld	d,(ix+7)	;	ld	d,(ix+7)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	nz,loc_197	;	jp	z,l14
	jp	loc_194		;
loc_194:			;
	jp	loc_19D		;
loc_197:			;
	jp	loc_19A		;
loc_19A:			;
	jp	loc_159		;
loc_19D:			;
	ld	de,_array_9BD4	;	ld	de,_array_9BD4
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l, a		;	ld	l,a
	jp	loc_1AF		;
loc_1AF:			;
	jp	cret		;	jp	cret
				;
f159	equ	-2		;

; End of function sub_13D

; End of file 13D.asm

