*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 19C1.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_19C1 OK++
;=========================================================
	global	_sub_19C1	;	global	_sub_19C1
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_sub_1754	;	global	_sub_1754
	global	_sub_306	;	global	_sub_306
	global	_allocmem	;	global	_allocmem
	global	_atoi		;	global	_atoi
	global	_sub_627	;	global	_sub_627
	global	_sub_600E	;	global	_sub_600E
	global	_sub_4192	;	global	_sub_4192
	global	_faterror	;	global	_faterror
	global	_sub_475C	;	global	_sub_475C
	global	_sub_1C8E	;	global	_sub_1C8E
	global	_movmem		;	global	_movmem
	global	_sub_1CEF	;	global	_sub_1CEF

	psect	text

;	Disassembled version	; After compiling C source code
_sub_19C1:
	call	ncsv		;	call	ncsv
	defw 	0FDF2h		;	defw 	-526
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	call	_sub_306	;	call	_sub_306
	push	hl		;	push	hl
	call	_sub_1754	;	call	_sub_1754
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,0FDF2h	;	ld	hl,-526
	add	hl,de		;	add	hl,de
	ld	(ix+-6),l	;	ld	(ix+-6),l
	ld	(ix+-5),h	;	ld	(ix+-5),h
	ld	de,0		;	ld	de,0
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
loc_19EF:			;l12:
	call	_sub_306	;	call	_sub_306
	ld	(ix+-10),l	;	ld	(ix+-10),l
	ld	(ix+-9),h	;	ld	(ix+-9),h
	ld	a,(hl)		;	ld	a,(hl)
	cp	5Dh		;	cp	93
	jp	z,loc_1AAE	;	jp	z,l13
	ld	hl,16h		;	ld	hl,22
	push	hl		;	push	hl
	call	_allocmem	;	call	_allocmem
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	(iy+2),16h	;	ld	(iy+2),22
	ld	l,(ix+-10)	;	ld	l,(ix+-10)
	ld	h,(ix+-9)	;	ld	h,(ix+-9)
	ld	a,(hl)		;	ld	a,(hl)
	cp	3Ah		;	cp	58
	jr	nz,loc_1A2E	;	jp	nz,l16
	inc	hl		;	inc	hl
	push	hl		;	push	hl
	call	_atoi		;	call	_atoi
	pop	bc		;	pop	bc
	ld	(iy+5),l	;	ld	(iy+5),l
	set	4,(iy+3)	;	set	4,(iy+3)
	call	_sub_306	;	call	_sub_306
	ld	(ix+-10),l	;	ld	(ix+-10),l
	ld	(ix+-9),h	;	ld	(ix+-9),h
loc_1A2E:			;l16:
	push	iy		;	push	iy
	pop	de		;	pop	de
	ld	hl,0Dh		;	ld	hl,13
	add	hl,de		;	add	hl,de
	push	hl		;	push	hl
	ld	l,(ix+-10)	;	ld	l,(ix+-10)
	ld	h,(ix+-9)	;	ld	h,(ix+-9)
	push	hl		;	push	hl
	call	_sub_627	;	call	_sub_627
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(iy+0Fh),l	;	ld	(iy+15),l
	ld	(iy+10h),h	;	ld	(iy+16),h
	call	_sub_4192	;	call	_sub_4192
	push	hl		;	push	hl
	call	_sub_600E	;	call	_sub_600E
	pop	bc		;	pop	bc
	ld	(ix+-8),l	;	ld	(ix+-8),l
	ld	(ix+-7),h	;	ld	(ix+-7),h
	ld	a,(hl)		;	ld	a,(hl)
	cp	43h		;	cp	67
	jr	z,loc_1A63	;	jp	z,l17
	ld	hl,19f		;	ld	hl,19f
	push	hl		;	push	hl
	call	_faterror	;	call	_faterror
	pop	bc		;	pop	bc
loc_1A63:			;l17:
	ld	e,(ix+-8)	;	ld	e,(ix+-8)
	ld	d,(ix+-7)	;	ld	d,(ix+-7)
	ld	hl,19h		;	ld	hl,25
	add	hl, de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+0Bh),c	;	ld	(iy+11),c
	ld	(iy+0Ch),b	;	ld	(iy+12),b
	ld	l,e		;	ld	l,e
	ld	h,d		;	ld	h,d
	push	hl		;	push	hl
	call	_sub_475C	;	call	_sub_475C
	pop	bc		;	pop	bc
	push	iy		;	push	iy
	call	_sub_1C8E	;	call	_sub_1C8E
	pop	bc		;	pop	bc
	ld	(iy+9),l	;	ld	(iy+9),l
	ld	(iy+0Ah),h	;	ld	(iy+10),h
	ld	e,(ix+-6)	;	ld	e,(ix+-6)
	ld	d,(ix+-5)	;	ld	d,(ix+-5)
	ex	de,hl		;	ex	de,hl
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	ex	de,hl		;	ex	de,hl
	inc	hl		;	inc	hl
	ex	de,hl		;	ex	de,hl
	ld	(hl),d		;	ld	(hl),d
	dec	hl		;	dec	hl
	ld	(hl),e		;	ld	(hl),e
	ex	de,hl		;	ex	de,hl
	dec	hl		;	dec	hl
	add	hl,hl		;	add	hl,hl
	ld	e,(ix+-6)	;	ld	e,(ix+-6)
	ld	d,(ix+-5)	;	ld	d,(ix+-5)
	add	hl,de		;	add	hl,de
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	push	iy		;	push	iy
	pop	de		;	pop	de
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	jp	loc_19EF	;	jp	l12
loc_1AAE:			;l13:
	ld	l,(ix+-6)	;	ld	l,(ix+-6)
	ld	h,(ix+-5)	;	ld	h,(ix+-5)
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	hl,0FFFFh	;	ld	hl,-1
	add	hl,bc		;	add	hl,bc
	add	hl,hl		;	add	hl,hl
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	push	hl		;	push	hl
	call	_allocmem	;	call	_allocmem
	ld	(ix+-6),l	;	ld	(ix+-6),l
	ld	(ix+-5),h	;	ld	(ix+-5),h
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(ix+-6)	;	ld	l,(ix+-6)
	ld	h,(ix+-5)	;	ld	h,(ix+-5)
	push	hl		;	push	hl
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,0FDF2h	;	ld	hl,-526
	add	hl,de		;	add	hl,de
	push	hl		;	push	hl
	call	_movmem		;	call	_movmem
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	e,(ix+-4)	;	ld	e,(ix+-4)
	ld	d,(ix+-3)	;	ld	d,(ix+-3)
	ld	hl,13h		;	ld	hl,19
	add	hl,de		;	add	hl,de
	ld	e,(ix+-6)	;	ld	e,(ix+-6)
	ld	d,(ix+-5)	;	ld	d,(ix+-5)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	push	hl		;	push	hl
	call	_sub_1CEF	;	call	_sub_1CEF
	jp	cret		;	jp	cret
				
; End of function sub_19C1 OK++

;=========================================================
; sub_17E0 OK+
;
; Warning
;   In file CGEN.COM stack recovery failed when returning
;   from function sub_76F
;=========================================================
	global	_sub_1B0C	;	global	_sub_1B0C
	global	_sub_15FB	;	global	_sub_15FB
	global	_sub_76F	;	global	_sub_76F
	global	arelop		;	global	arelop
	global	arelop		;	global	arelop

;	Disassembled version	; After compiling C source code
_sub_1B0C:
	call	ncsv		;	call 	ncsv
	defw	0FDF2h		;	defw 	-526
	ld	(ix+-6),0	;	ld	(ix+-6),0
	ld	(ix+-5),80h	;	ld	(ix+-5),128
	ld	(ix+-8),0FFh	;	ld	(ix+-8),255
	ld	(ix+-7),7Fh	;	ld	(ix+-7),127
	ld	hl, 34h		;	ld	hl,52
	push	hl		;	push	hl
	call	_sub_306	;	call	_sub_306
	push	hl		;	push	hl
	call	_sub_1754	;	call	_sub_1754
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,0FDF2h	;	ld	hl,-526
	add	hl,de		;	add	hl,de
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	ld	de,0		;	ld	de,0
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
loc_1B44:			;l19:
	call	_sub_4192	;	call	_sub_4192
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	a,(hl)		;	ld	a,(hl)
	cp	17h		;	cp	23
	push	hl		;	push	hl
	jp	nz,loc_1BBE	;	jp	nz,L1
	call	_sub_475C	;	call	_sub_475C
	pop	bc		;	pop	bc
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	dec	hl		;	dec	hl
	add	hl,hl		;	add	hl,hl
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	(ix+-10),l	;	ld	(ix+-10),l
	ld	(ix+-9),h	;	ld	(ix+-9),h
	push	hl		;	push	hl
	call	_allocmem	;	call	_allocmem
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	ld	l,(ix+-10)	;	ld	l,(ix+-10)
	ld	h,(ix+-9)	;	ld	h,(ix+-9)
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	push	hl		;	push	hl
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,0FDF2h	;	ld	hl,-526
	add	hl,de		;	add	hl,de
	push	hl		;	push	hl
	call	_movmem		;	call	_movmem
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	ld	(iy+13h),l	;	ld	(iy+19),l
	ld	(iy+14h),h	;	ld	(iy+20),h
	ld	l,(ix+-6)	;	ld	l,(ix+-6)
	ld	h,(ix+-5)	;	ld	h,(ix+-5)
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(ix+-8)	;	ld	l,(ix+-8)
	ld	h,(ix+-7)	;	ld	h,(ix+-7)
	push	hl		;	push	hl
	push	iy		;	push	iy
	call	_sub_15FB	;	call	_sub_15FB	;  1BAF  CALL 15FB	;  1B91  CALL 15CA
	pop	bc		;	pop	bc		;  1BB2  POP  BC	;  1B94  POP  BC
	pop	bc		;	pop	bc		;  1BB3  POP  BC	;  1B95  POP  BC
	ld	hl,5Dh		;	ld	hl,93		;  1BB4  LD   HL,005D	;  1B96  LD   HL,005D
	ex	(sp),hl		;	ex	(sp),hl		;  1BB7  EX   SP,HL	;  1B99  EX   SP,HL
	call	_sub_76F	;	call	_sub_76F	;  1BB8  CALL 076F	;  1B9A  CALL 0745
; 	missing pop bc		;	pop	bc		;			;  1B9D  POP  BC
	jp	cret		;	jp	cret		;  1BBB  JP   8024	;  1B9E  JP   8DE0
loc_1BBE:			;L1:				;			;
	call	_sub_600E	;	call	_sub_600E	;  1BBE  CALL 600E	;  1BA1  CALL 5F7D
	pop	bc		;	pop	bc		;  1BC1  POP  BC	;  1BA4  POP  BC
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ex	de,hl		;	ex	de,hl
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	e,(ix+-4)	;	ld	e,(ix+-4)
	ld	d,(ix+-3)	;	ld	d,(ix+-3)
	ex	de,hl		;	ex	de,hl
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	ex	de,hl		;	ex	de,hl
	inc	hl		;	inc	hl
	ex	de,hl		;	ex	de,hl
	ld	(hl),d		;	ld	(hl),d
	dec	hl		;	dec	hl
	ld	(hl),e		;	ld	(hl),e
	ex	de,hl		;	ex	de,hl
	dec	hl		;	dec	hl
	add	hl,hl		;	add	hl,hl
	ld	e,(ix+-4)	;	ld	e,(ix+-4)
	ld	d,(ix+-3)	;	ld	d,(ix+-3)
	add	hl,de		;	add	hl,de
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	(hl),c		;	ld	(hl),c
	inc	hl		;	inc	hl
	ld	(hl),b		;	ld	(hl),b
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
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
	ld	e,(ix+-6)	;	ld	e,(ix+-6)
	ld	d,(ix+-5)	;	ld	d,(ix+-5)
	ld	a,d		;	ld	a,d
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	l,a		;	ld	l,a
	ld	h,a		;	ld	h,a
	call	arelop		;	call	arelop
	jp	p,loc_1C27	;	jp	p,l23
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-6),c	;	ld	(ix+-6),c
	ld	(ix+-5),b	;	ld	(ix+-5),b
loc_1C27:			;l23:
	ld	e,(ix+-8)	;	ld	e,(ix+-8)
	ld	d,(ix+-7)	;	ld	d,(ix+-7)
	ld	a,d		;	ld	a,d
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	l,a		;	ld	l,a
	ld	h,a		;	ld	h,a
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
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
	call	arelop		;	call	arelop
	jp	p,loc_1C5F	;	jp	p,l24
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-8),c	;	ld	(ix+-8),c
	ld	(ix+-7),b	;	ld	(ix+-7),b
loc_1C5F:			;l24:
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	call	_sub_475C	;	call	_sub_475C
	pop	bc		;	pop	bc
	jp	loc_1B44	;	jp	l19


; End of function sub_1B0C OK+

	psect	data

p_19c1_A934:
19:	defb	83,116,114,117,99,100,101,99,108,32,45,32,98,97,100,9
	defb	110,101,108,101,109,0

	psect	text

; End of file - 19C1.asm


