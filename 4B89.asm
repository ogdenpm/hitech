*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 4B89.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_4B89 OK++
;
; Restored function sub_4B89 is assigned the uchar type to avoid
; casting type when it is called in other functions (sub_4C12,
; sub_54B6) and generating code corresponding to binary image.
; For this reason, return value is passed in register "l".
;=========================================================
	global	_sub_4B89	;	global	_sub_4B89
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_dopetab	;	global	_dopetab
	global 	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_4B89:
	call	csv		;	call 	csv
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
	bit	4,c		;	bit	4,c
	jr	nz,loc_4BDF	;	jp	nz,L3	   <----+ Different
	ld	a,(iy+0)	;	ld	a,(iy+0)	: jump
	cp	9		;	cp	9		: address
	jr	nz,loc_4BB8	;	jp	nz,L1		:
	ld	l,(iy+25)	;	ld	l,(iy+25)	:
	ld	h,(iy+26)	;	ld	h,(iy+26)	:
	ld	a,(hl)		;	ld	a,(hl)		:
	cp	66		;	cp	66		:
	jr	z,loc_4BDF	;	jp	z,L3	   <----+
loc_4BB8:			;L1:				:
	ld	a,(iy+0)	;	ld	a,(iy+0)	:
	cp	14		;	cp	14		:
	jr	nz,loc_4BD9	;	jp	nz,l14	   <----+
	ld	l,(iy+27)	;	ld	l,(iy+27)	:
	ld	h,(iy+28)	;	ld	h,(iy+28)	:
	ld	a,(hl)		;	ld	a,(hl)		:
	cp	67		;	cp	67		:
	jr	nz,loc_4BD9	;	jp	nz,l14	   <----+
	ld	l,(iy+25)	;	ld	l,(iy+25)
	ld	h,(iy+26)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_4B89	;	call	_sub_4B89
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l		; Different
	or	a		;	or	a		; conditions and
	jr	nz,loc_4BDF	;	jp	z,l14	   <----+ jump address
loc_4BD9:			;L3:
	ld	hl,0		;	ld	l,1	   <----+ Different
	jp	cret		;	jp	cret		: assigned
loc_4BDF:			;l14:				: values
	ld	hl,1		;	ld	l,0	   <----+
	jp	cret		;	jp	cret

; End of function sub_4B89 OK+

; End of file 4B89.as

