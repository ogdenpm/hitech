*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 4192.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_4192 OK+
;
; Code generated from restored C language program is completely
; identical to binary image of executable file. To simplify
; comparison, code fragments generated from restored C program
; with labels were moved in accordance with its location in binary
; image of the executable file.
;=========================================================
	global	_sub_4192	;	global	_sub_4192
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_sub_306	;	global	_sub_306
	global	__ctype_	;	global	__ctype_
	global	_sub_415E	;	global	_sub_415E
	global	_atol		;	global	_atol
	global	_sub_3712	;	global	_sub_3712
	global	_sub_265	;	global	_sub_265
	global	_sub_C36	;	global	_sub_C36
	global	_sub_627	;	global	_sub_627
	global	_word_AED7	;	global	_word_AED7
	global	_allocmem	;	global	_allocmem
	global	_strlen		;	global	_strlen
	global	_strcpy		;	global	_strcpy
	global	_sub_174C	;	global	_sub_174C
	global	_sub_1B2	;	global	_sub_1B2
	global	_dopetab	;	global	_dopetab
	global	_sub_1B0C	;	global	_sub_1B0C
	global	_sub_19C1	;	global	_sub_19C1
	global	_sub_17E0	;	global	_sub_17E0
	global	_faterror	;	global	_faterror
	global	_sub_43EF	;	global	_sub_43EF

	psect	text

;	Disassembled version	; After compiling C source code
_sub_4192:				
	call	ncsv		;	call 	ncsv
	defw	-8		;	defw 	-8
loc_4197:			;l12:
	call	_sub_306	;	call	_sub_306
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	ld	a,(hl)		;	ld	a,(hl)
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de
	bit	2,(hl)		;	bit	2,(hl)
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	ld	a,(hl)		;	ld	a,(hl)
	jr	nz,loc_41CF	;	jp	nz,L7
	cp	2Dh		;	cp	45
	jp	nz,loc_423C	;	jp	nz,L10
	inc	hl		;	inc	hl
	ld	a,(hl)		;	ld	a,(hl)
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de
	bit	2,(hl)		;	bit	2,(hl)
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	ld	a,(hl)		;	ld	a,(hl)
	jp	z,loc_423D	;	jp	z,L8
loc_41CF:			;L7:
	cp	2Dh		;	cp	45
	jr	nz,loc_41EA	;	jp	nz,l17
	ld	(ix+-8),1	;	ld	(ix+-8),1
	ld	(ix+-7),0	;	ld	(ix+-7),0
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	inc	hl		;	inc	hl
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	jr	loc_41F2	;	jp	l18
loc_41EA:			;l17:
	ld	(ix+-8),0	;	ld	(ix+-8),0
	ld	(ix+-7),0	;	ld	(ix+-7),0
loc_41F2:			;l18:
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	push	hl		;	push	hl
	call	_atol		;	call	_atol
	ex	(sp),	hl	;	ex	(sp),hl
	push	de		;	push	de
	call	_sub_415E	;	call	_sub_415E
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	a,(ix+-8)	;	ld	a,(ix+-8)
	or	(ix+-7)		;	or	(ix+-7)
	jr	z,loc_4236	;	jp	z,l20
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
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
	ld	(iy+19h),e	;	ld	(iy+25),e
	ld	(iy+1Ah),d	;	ld	(iy+26),d
	ld	(iy+1Bh),l	;	ld	(iy+27),l
	ld	(iy+1Ch),h	;	ld	(iy+28),h
loc_4236:			;l20:
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	jp	cret		;	jp	cret
loc_423C:			;L10:
	ld	a,(hl)		;	ld	a,(hl)
loc_423D:			;L8:
	cp	5Fh		;	cp	95
	jr	z,loc_4257	;	jp	z,L3
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	ld	a,(hl)		;	ld	a,(hl)
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	and	3		;	and	3
	or	a		;	or	a
	jp	z,loc_42A7	;	jp	z,l21
loc_4257:			;L3:
	call	_sub_3712	;	call	_sub_3712
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	(hl),	42h	;	ld	(hl),66
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	push	hl		;	push	hl
	call	_sub_265	;	call	_sub_265
	pop	bc		;	pop	bc
	ld	(iy+19h),l	;	ld	(iy+25),l
	ld	(iy+1Ah),h	;	ld	(iy+26),h
	ex	de,hl		;	ex	de,hl
	ld	hl,0Fh		;	ld	hl,15
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+17h),c	;	ld	(iy+23),c
	ld	(iy+18h),b	;	ld	(iy+24),b
	ld	hl,0Dh		;	ld	hl,13
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+15h),c	;	ld	(iy+21),c
	ld	(iy+16h),b	;	ld	(iy+22),b
	ld	hl,15h		;	ld	hl,21
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	cp	3		;	cp	3
	jr	nz,loc_4236	;	jp	nz,l20
	ld	l,e		;	ld	l,e
	ld	h,d		;	ld	h,d
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	bit	1,(hl)		;	bit	1,(hl)
	jr	nz,loc_4236	;	jp	nz,l20
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	push	hl		;	push	hl
	call	_sub_C36	;	call	_sub_C36
	pop	bc		;	pop	bc
	jr	loc_4236	;	jp	l20
loc_42A7:			;l21:
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	ld	a,(hl)		;	ld	a,(hl)
	cp	60h		;	cp	96
	jr	nz,loc_42D8	;	jp	nz,l24
	call	_sub_3712	;	call	_sub_3712
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	push	hl		;	push	hl
	pop	de		;	pop	de
	ld	hl,15h		;	ld	hl,21
	add	hl,de		;	add	hl,de
	push	hl		;	push	hl
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	push	hl		;	push	hl
	call	_sub_627	;	call	_sub_627
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(iy+17h),l	;	ld	(iy+23),l
	ld	(iy+18h),h	;	ld	(iy+24),h
	ld	(iy+0),41h	;	ld	(iy+0),65
	jp	loc_4236	;	jp	l20
loc_42D8:			;l24:
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	ld	a,(hl)		;	ld	a,(hl)
	cp	2Eh		;	cp	46
	jp	nz,loc_4340	;	jp	nz,L9				
	inc	hl		;	inc	hl
	ld	a,(hl)		;	ld	a,(hl)
	or	a		;	or	a
	dec	hl		;	dec	hl
	jp	z,loc_4340	;	jp	z,L9
	inc	hl		;	inc	hl
	ld	a,(hl)		;	ld	a,(hl)
	cp	2Eh		;	cp	46
	jp	z,loc_433A	;	jp	z,l27
	call	_sub_3712	;	call	_sub_3712
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	hl,(_word_AED7)	;	ld	hl,(_word_AED7)
	ld	(iy+17h),l	;	ld	(iy+23),l
	ld	(iy+18h),h	;	ld	(iy+24),h
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	push	hl		;	push	hl
	call	_strlen		;	call	_strlen
	ex	(sp),hl		;	ex	(sp),hl
	call	_allocmem	;	call	_allocmem
	pop	bc		;	pop	bc
	ld	(iy+19h),l	;	ld	(iy+25),l
	ld	(iy+1Ah),h	;	ld	(iy+26),h
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	inc	hl		;	inc	hl
	push	hl		;	push	hl
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_strcpy		;	call	_strcpy
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	call	_sub_174C	;	call	_sub_174C
	ld	(iy+1Bh),l	;	ld	(iy+27),l
	ld	(iy+1Ch),h	;	ld	(iy+28),h	
	ld	(iy+0),44h	;	ld	(iy+0),68
	jp	loc_4236	;	jp	l20
loc_433A:			;l27:
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
loc_4340:			;L9:
	push	hl		;	push	hl
	call	_sub_1B2	;	call	_sub_1B2
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	ld	(ix+-8),l	;	ld	(ix+-8),l
	ld	(ix+-7),h	;	ld	(ix+-7),h
	ld	de,_dopetab	;	ld	de,_dopetab
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
	ld	(ix+-6),l	;	ld	(ix+-6),l
	ld	(ix+-5),h	;	ld	(ix+-5),h
	ld	h,(ix+-5)	;	ld	h,(ix+-5)
	ld	a,h		;	ld	a,h
	or	a		;	or	a
	jp	nz,loc_4197	;	jp	nz,l12
	ld	a,l		;	ld	a,l
	or	a		;	or	a
	jp	z,loc_43BC	;	jp	z,l37
	cp	4		;	cp	4
	jp	z,loc_43D1	;	jp	z,l38
	cp	8		;	cp	8
	jp	z,loc_43DA	;	jp	z,l39
	cp	0Ch		;	cp	12
	jp	nz,loc_4197	;	jp	nz,l12
	ld	l,(ix+-8)	;	ld	l,(ix+-8)
	ld	h,(ix+-7)	;	ld	h,(ix+-7)
	ld	a,h		;	ld	a,h
	or	a		;	or	a		^
	jr	nz,loc_43B4	;	jp	nz,l31		;
	ld	a,l		;	ld	a,l		; Code generated from     
	cp	34h		;	cp	52		; restored C language
	jr	z,loc_43AE	;	jp	z,l33		; program is completely
	cp	37h		;	cp	55		; identical to binary
	jr	z,loc_43A0	;	jp	z,l35		; image of executable
	cp	38h		;	cp	56		; file
	jr	z,loc_43A0	;	jp	z,l35		;
	cp	39h		;	cp	57	   <----+
	jr	nz,loc_43B4	;	jp	z,l36		; To simplify comparison,
				;	l36:			; code fragments generated
	call	_sub_17E0	;	call	_sub_17E0	; from restored C program
	jp	loc_4197	;	jp	l12		; with labels were moved
loc_43A0:			;l35:				; in accordance with its
	ld	l,(ix+-8)	;	ld	l,(ix+-8)	; location in binary image
	ld	h,(ix+-7)	;	ld	h,(ix+-7)	; of the executable file
	push	hl		;	push	hl		;
	call	_sub_19C1	;	call	_sub_19C1	v
	pop	bc		;	pop	bc
	jp	loc_4197	;	jp	l12
loc_43AE:			;l33:
	call	_sub_1B0C	;	call	_sub_1B0C
	jp	loc_4197	;	jp	l12
loc_43B4:			;l31:
	ld	hl,19f		;	ld	hl,19f
	push	hl		;	push	hl
	call	_faterror	;	call	_faterror
	pop	bc		;	pop	bc
loc_43BC:			;l37:
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
loc_43C0:			;L12:
	push	hl		;	push	hl
	ld	l,(ix+-8)	;	ld	l,(ix+-8)
	ld	h,(ix+-7)	;	ld	h,(ix+-7)
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	jp	cret		;	jp	cret
loc_43D1:			;l38:
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	call	_sub_4192	;	call	_sub_4192
	jr	loc_43C0	;	jp	L12
loc_43DA:			;l39:
	call	_sub_4192	;	call	_sub_4192
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	call	_sub_4192	;	call	_sub_4192
	push	hl		;	push	hl
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	jr	loc_43C0	;	jp	L12

	psect	data

p_4192_1:
19:
	defb	69,120,112,114,101,115,115,105,111,110,32,101,114,114,111,114
	defb	0

	psect	text

; End of function sub_4192 OK+

; End of file 4192.asm

