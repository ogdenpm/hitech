*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 808.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_808 OK+
;
; Generated code is completely identical, except for
; incomprehensible code inside function that does not
; affect program logic
;
; Warting!
;   The original executable file contains additional code
;   that does not affect the logic of the function.
;=========================================================
	global	_sub_808	;	global	_sub_808
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_sub_475C	;	global	_sub_475C
	global	_sub_1CC4	;	global	_sub_1CC4
	global	amod		;	global	amod
	global	amod		;	global	amod
	global	_sub_CDF	;	global	_sub_CDF
	global	_sub_43EF	;	global	_sub_43EF
	global	_sub_415E	;	global	_sub_415E
	global	allsh		;	global	allsh
	global	_sub_4192	;	global	_sub_4192
	global	_nodesize	;	global	_nodesize
	global	_sub_2BD0	;	global	_sub_2BD0
	global	_sub_600E	;	global	_sub_600E
	global	wrelop		;	global	wrelop
	global	wrelop		;	global	wrelop
	global	_uerror		;	global	_uerror

	psect	text

;	Disassembled version	; After compiling C source code
_sub_808:
	call 	ncsv		;	call 	ncsv
	defw 	0FFF4h		;	defw 	-12
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	(ix+-2),0	;	ld	(ix+-2),0
	ld	(ix+-1),0	;	ld	(ix+-1),0
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	a,(hl)		;	ld	a,(hl)
	cp	1Ah		;	cp	26
	jp	nz,loc_A95	;	jp	nz,l13
	push	hl		;	push	hl
	call	_sub_475C	;	call	_sub_475C
	pop	bc		;	pop	bc
	ld	(ix+-10),0	;	ld	(ix+-10),0
	ld	(ix+-9),0	;	ld	(ix+-9),0
	ld	a,(iy+2)	;	ld	a,(iy+2)
	cp	37h		;	cp	55
	jp	nz,loc_A22	;	jp	nz,l14
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	ld	(ix+-6),l	;	ld	(ix+-6),l
	ld	(ix+-5),h	;	ld	(ix+-5),h
	jp	loc_A0B		;	jp	l15
loc_84B:			;l16:
	ld	e,(ix+-6)	;	ld	e,(ix+-6)
	ld	d,(ix+-5)	;	ld	d,(ix+-5)
	ld	hl,13h		;	ld	hl,19
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	l,(ix+-10)	;	ld	l,(ix+-10)
	ld	h,(ix+-9)	;	ld	h,(ix+-9)
	inc	hl		;	inc	hl
	ld	(ix+-10),l	;	ld	(ix+-10),l
	ld	(ix+-9),h	;	ld	(ix+-9),h
	dec	hl		;	dec	hl
	add	hl,hl		;	add	hl,hl
	add	hl,bc		;	add	hl,bc
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-8),c	;	ld	(ix+-8),c
	ld	(ix+-7),b	;	ld	(ix+-7),b
	push	bc		;	push	bc
	call	_sub_1CC4	;	call	_sub_1CC4
	pop	bc		;	pop	bc
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	z,loc_8CC	;	jp	z,l18
	ld	e, l		;	ld	e,l
	ld	d, h		;	ld	d,h
	inc	de		;	inc	de
	ld	(ix+-4),e	;	ld	(ix+-4),e
	ld	(ix+-3),d	;	ld	(ix+-3),d
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	call	amod		;	call	amod
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	z,loc_8CC	;	jp	z,l18
	ld	e,(ix+-4)	;	ld	e,(ix+-4)
	ld	d,(ix+-3)	;	ld	d,(ix+-3)
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	call	amod		;	call	amod
	ex	de,hl		;	ex	de,hl
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	ex	de,hl		;	ex	de,hl
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	add	hl,de		;	add	hl,de
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	l,e		;	ld	l,e
	ld	h,d		;	ld	h,d
	push	hl		;	push	hl
	call	_sub_CDF	;	call	_sub_CDF
	pop	bc		;	pop	bc
loc_8CC:			;l18:
	ld	l,(ix+-8)	;	ld	l,(ix+-8)
	ld	h,(ix+-7)	;	ld	h,(ix+-7)
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	bit	4,(hl)		;	bit	4,(hl)
	jp	z,loc_9EA	;	jp	z,l20
	ld	e,(ix+-8)	;	ld	e,(ix+-8)
	ld	d,(ix+-7)	;	ld	d,(ix+-7)
	ld	hl,5		;	ld	hl,5
	add	hl,de		;	add	hl,de
	ld	b,(hl)		;	ld	b,(hl)
	ld	de,1		;	ld	de,1
	ld	hl,0		;	ld	hl,0
	call	allsh		;	call	allsh
	ex	de,hl		;	ex	de,hl
	ld	bc,0FFFFh	;	ld	bc,-1
	add	hl,bc		;	add	hl,bc
	ex	de,hl		;	ex	de,hl
	adc	hl,bc		;	adc	hl,bc
	push	hl		;	push	hl
	push	de		;	push	de
	call	_sub_415E	;	call	_sub_415E
	pop	bc		;	pop	bc
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	ld	hl,7		;	ld	hl,7
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h
	ld	e,(ix+-8)	;	ld	e,(ix+-8)
	ld	d,(ix+-7)	;	ld	d,(ix+-7)
	ld	hl,6		;	ld	hl,6
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	or	a		;	or	a
	jr	z,loc_95D	;	jp	z,l21		  Warting!
	ld	hl,6		;			  <-----+ Extra code does not
	add	hl,de		;				; affect the execution
	ld	l,(hl)		;			  <-----+ of the function !
				;
	ld	hl,0		;	ld	de,0	  <-----+ Zeroing
	ld	d,l		;	ld	l,e		; registers
	ld	e,l		;	ld	h,d	  <-----+ is different
	push	hl		;	push	hl
	push	de		;	push	de
	call	_sub_415E	;	call	_sub_415E
	pop	bc		;	pop	bc
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	ld	hl,1Fh		;	ld	hl,31
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(ix+-12)	;	ld	l,(ix+-12)
	ld	h,(ix+-11)	;	ld	h,(ix+-11)
	push	hl		;	push	hl
	ld	hl,3Ch		;	ld	hl,60
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(ix+-12),l	;	ld	(ix+-12),l
	ld	(ix+-11),h	;	ld	(ix+-11),h
	jr	loc_969		;	jp	l22
loc_95D:			;l21:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	(ix+-12),l	;	ld	(ix+-12),l
	ld	(ix+-11),h	;	ld	(ix+-11),h
loc_969:			;l22:
	ld	e,(ix+-6)	;	ld	e,(ix+-6)
	ld	d,(ix+-5)	;	ld	d,(ix+-5)
	ld	hl,13h		;	ld	hl,19
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	ld	l,(ix+-10)	;	ld	l,(ix+-10)
	ld	h,(ix+-9)	;	ld	h,(ix+-9)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	z,loc_9DE	;	jp	z,l23
	ld	e,(ix+-6)	;	ld	e,(ix+-6)
	ld	d,(ix+-5)	;	ld	d,(ix+-5)
	ld	hl,13h		;	ld	hl,19
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	l,(ix+-10)	;	ld	l,(ix+-10)
	ld	h,(ix+-9)	;	ld	h,(ix+-9)
	add	hl,hl		;	add	hl,hl
	add	hl,bc		;	add	hl,bc
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	bit	4,(hl)		;	bit	4,(hl)
	jr	z,loc_9DE	;	jp	z,l23
	ld	e,(ix+-8)	;	ld	e,(ix+-8)
	ld	d,(ix+-7)	;	ld	d,(ix+-7)
	ld	hl,11h		;	ld	hl,17
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	push	de		;	push	de
	ld	e,(ix+-6)	;	ld	e,(ix+-6)
	ld	d,(ix+-5)	;	ld	d,(ix+-5)
	ld	hl,13h		;	ld	hl,19
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	l,(ix+-10)	;	ld	l,(ix+-10)
	ld	h,(ix+-9)	;	ld	h,(ix+-9)
	add	hl,hl		;	add	hl,hl
	add	hl,bc		;	add	hl,bc
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	hl,11h		;	ld	hl,17
	add	hl,bc		;	add	hl,bc
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	pop	de		;	pop	de
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	z, loc_A0B	;	jp	z,l15
loc_9DE:			;l23:
	ld	l,(ix+-12)	;	ld	l,(ix+-12)
	ld	h,(ix+-11)	;	ld	h,(ix+-11)
	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h
loc_9EA:			;l20:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	ld	l,(ix+-8)	;	ld	l,(ix+-8)
	ld	h,(ix+-7)	;	ld	h,(ix+-7)
	push	hl		;	push	hl
	call	_sub_808	;	call	_sub_808
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ex	de,hl		;	ex	de,hl
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	add	hl,de		;	add	hl,de
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
loc_A0B:			;l15:
	call	_sub_4192	;	call	_sub_4192
	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h
	ld	a,(hl)		;	ld	a,(hl)
	cp	17h		;	cp	23
	jp	nz,loc_84B	;	jp	nz,l16
	push	hl		;	push	hl
loc_A1B:			;L2:
	call	_sub_475C	;	call	_sub_475C
	pop	bc		;	pop	bc
	jp	loc_AC8		;	jp	l27
loc_A22:			;l14:
	ld	l,(iy+15)	;	ld	l,(iy+15)
	ld	h,(iy+16)	;	ld	h,(iy+16)
	ld	(ix+-6),l	;	ld	(ix+-6),l
	ld	(ix+-5),h	;	ld	(ix+-5),h
loc_A2E:			;l31:
	call	_sub_4192	;	call	_sub_4192
	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h
	ld	a,(hl)		;	ld	a,(hl)
	cp	1Ah		;	cp	26
	jr	nz,loc_A59	;	jp	nz,L1
	push	hl		;	push	hl
	ld	l,(ix+-6)	;	ld	l,(ix+-6)
	ld	h,(ix+-5)	;	ld	h,(ix+-5)
	push	hl		;	push	hl
	call	_sub_808	;	call	_sub_808
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ex	de,hl		;	ex	de,hl
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	add	hl,de		;	add	hl,de
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	jr	loc_A2E		;	jp	l31
loc_A59:			;L1:
	ld	a,(hl)		;	ld	a,(hl)
	cp	17h		;	cp	23
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	jr	z,loc_A1B	;	jp	z,L2
	call	_nodesize	;	call	_nodesize
	ex	de,hl		;	ex	de,hl
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	add	hl,de		;	add	hl,de
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	hl,0		;	ld	hl,0
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	ld	hl,31h		;	ld	hl,49
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_600E	;	call	_sub_600E
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_2BD0	;	call	_sub_2BD0
	pop	bc		;	pop	bc
	jr	loc_A2E		;	jp	l31
loc_A95:			;l13:
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	ld	hl,31h		;	ld	hl,49
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_600E	;	call	_sub_600E
	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h
	ex	(sp),hl		;	ex	(sp),hl
	call	_nodesize	;	call	_nodesize
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_2BD0	;	call	_sub_2BD0
	pop	bc		;	pop	bc
loc_AC8:			;l27:
	ld	e,(iy+9)	;	ld	e,(iy+9)
	ld	d,(iy+10)	;	ld	d,(iy+10)
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	call	wrelop		;	call	wrelop
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	l,(iy+9)	;	ld	l,(iy+9)
	ld	h,(iy+10)	;	ld	h,(iy+10)
	jr	nc,loc_AFB	;	jp	nc,L3
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	push	hl		;	push	hl
	call	_sub_CDF	;	call	_sub_CDF
	pop	bc		;	pop	bc
	ld	l,(iy+9)	;	ld	l,(iy+9)
	ld	h,(iy+10)	;	ld	h,(iy+10)
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	jr	loc_B10		;	jp	l37
loc_AFB:			;L3:
	call	wrelop		;	call	wrelop
	jr	nc,loc_B10	;	jp	nc,l37
	ld	a,(iy+9)	;	ld	a,(iy+9)
	or	(iy+10)		;	or	(iy+10)
	jr	z,loc_B10	;	jp	z,l37
	ld	hl,19f		;	ld	hl,19f
	push	hl		;	push	hl
	call	_uerror		;	call	_uerror
	pop	bc		;	pop	bc
loc_B10:			;l37:
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	jp	cret		;	jp	cret

; End of function sub_808 OK+

	psect	data

d_808_A3C4:
19:	defb	84,111,111,32,109,97,110,121,32,105,110,105,116,105,97,108
	defb	105,122,101,114,115,0

	psect	text

; End of file - 808.asm


