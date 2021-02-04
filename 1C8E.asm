*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 1C8E.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_1C8E OK++
;=========================================================
	global	_sub_1C8E	;	global	_sub_1C8E
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	lmul		;	global	lmul
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_1C8E:
	call	csv		;	call 	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	bit	0,(iy+13)	;	bit	0,(iy+13)
	jr	z,loc_1CAA	;	jp	z,l12
	ld	l,(iy+11)	;	ld	l,(iy+11)
	ld	h,(iy+12)	;	ld	h,(iy+12)
	add	hl,hl		;	add	hl,hl
	jp	cret		;	jp	cret
loc_1CAA:			;l12:
	ld	e,(iy+15)	;	ld	e,(iy+15)
	ld	d,(iy+16)	;	ld	d,(iy+16)
	ld	hl,9		;	ld	hl,9
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	ld	e,(iy+11)	;	ld	e,(iy+11)
	ld	d,(iy+12)	;	ld	d,(iy+12)
	call	lmul		;	call	lmul
	jp	cret		;	jp	cret

; End of function sub_1C8E OK++

;=========================================================
; sub_1CC4 OK++
;=========================================================
	global	_sub_1CC4	;	global	_sub_1CC4
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_1CC4:
	call	csv		;	call 	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	a,(iy+13)	;	ld	a,(iy+13)
	or	(iy+14)		;	or	(iy+14)
	jr	z,loc_1CDE	;	jp	z,l14
	ld	hl,0		;	ld	hl,0
	jp	cret		;	jp	cret
loc_1CDE:			;l14:
	ld	e,(iy+15)	;	ld	e,(iy+15)
	ld	d,(iy+16)	;	ld	d,(iy+16)
	ld	hl,11h		;	ld	hl,17
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	jp	cret		;	jp	cret

; End of function sub_1CC4 OK++

;=========================================================
; sub_1CEF OK++
;=========================================================
	global	_sub_1CEF	;	global	_sub_1CEF
	global	_sub_1659	;	global	_sub_1659
	global	_sub_1C6D	;	global	_sub_1C6D
	global	wrelop		;	global	wrelop

	psect	text

; Disassembled version		; After compiling C source code
_sub_1CEF:
	call 	ncsv		;	call 	ncsv
	defw 	0FFF8h		;	defw 	-8
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	(ix+-2),0	;	ld	(ix+-2),0
	ld	(ix+-1),0	;	ld	(ix+-1),0
	ld	hl,0		;	ld	hl,0
	ld	(ix+-6),l	;	ld	(ix+-6),l
	ld	(ix+-5),h	;	ld	(ix+-5),h
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	jp	loc_1E89	;	jp	l16
loc_1D17:			;l17:
	ld	e,(iy+19)	;	ld	e,(iy+19)
	ld	d,(iy+20)	;	ld	d,(iy+20)
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	add	hl,hl		;	add	hl,hl	
	add	hl,de		;	add	hl,de
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-8),c	;	ld	(ix+-8),c
	ld	(ix+-7),b	;	ld	(ix+-7),b
	ld	a,(iy+2)	;	ld	a,(iy+2)
	cp	38h		;	cp	56
	jr	nz,loc_1D66	;	jp	nz,l19
	ld	e,c		;	ld	e,c
	ld	d,b		;	ld	d,b
	ld	hl,9		;	ld	hl,9
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	call	_sub_1659	;	call	_sub_1659
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	e,(ix+-8)	;	ld	e,(ix+-8)
	ld	d,(ix+-7)	;	ld	d,(ix+-7)
	ld	hl,11h		;	ld	hl,17
	add	hl,de		;	add	hl,de
	ld	de,0		;	ld	de,0
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	jp	loc_1E7C	;	jp	l20
loc_1D66:			;l19:
	ld	l,(ix+-8)	;	ld	l,(ix+-8)
	ld	h,(ix+-7)	;	ld	h,(ix+-7)
	push	hl		;	push	hl
	call	_sub_1CC4	;	call	_sub_1CC4
	ex	(sp),hl		;	ex	(sp),hl	
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	call	_sub_1C6D	;	call	_sub_1C6D
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	ld	e,(ix+-8)	;	ld	e,(ix+-8)
	ld	d,(ix+-7)	;	ld	d,(ix+-7)
	ld	hl,11h		;	ld	hl,17
	add	hl,de		;	add	hl,de
	pop	de		;	pop	de
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	(ix+-2),e	;	ld	(ix+-2),e
	ld	(ix+-1),d	;	ld	(ix+-1),d
	ld	l,(ix+-8)	;	ld	l,(ix+-8)
	ld	h,(ix+-7)	;	ld	h,(ix+-7)
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	bit	4,(hl)		;	bit	4,(hl)
	jp	z,loc_1E37	;	jp	z,l21
	ld	e,(ix+-8)	;	ld	e,(ix+-8)
	ld	d,(ix+-7)	;	ld	d,(ix+-7)
	ld	hl,5		;	ld	hl,5
	add	hl,de		;	add	hl,de
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	ld	e,(ix+-6)	;	ld	e,(ix+-6)
	ld	d,(ix+-5)	;	ld	d,(ix+-5)
	add	hl,de		;	add	hl,de
	ex	de,hl		;	ex	de,hl
	ld	hl,10h		;	ld	hl,16
	call	wrelop		;	call	wrelop
	jr	c,loc_1DCB	;	jp	c,L1
	ld	e,(ix+-8)	;	ld	e,(ix+-8)
	ld	d,(ix+-7)	;	ld	d,(ix+-7)
	ld	hl,5		;	ld	hl,5
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	or	a		;	or	a
	jr	nz,loc_1DF6	;	jp	nz,l22
loc_1DCB:			;L1:
	ld	a,(ix+-6)	;	ld	a,(ix+-6)
	or	(ix+-5)		;	or	(ix+-5)
	jr	z,loc_1DEE	;	jp	z,l23
	ld	e,(ix+-8)	;	ld	e,(ix+-8)
	ld	d,(ix+-7)	;	ld	d,(ix+-7)
	ld	hl,11h		;	ld	hl,17
	add	hl,de 		;	add	hl,de
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	inc	de		;	inc	de
	inc	de		;	inc	de
	ld	(ix+-2),e	;	ld	(ix+-2),e
	ld	(ix+-1),d	;	ld	(ix+-1),d
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
loc_1DEE:			;l23:
	ld	(ix+-6),0	;	ld	(ix+-6),0
	ld	(ix+-5),0	;	ld	(ix+-5),0
loc_1DF6:			;l22:
	ld	a,(ix+-6)	;	ld	a,(ix+-6)
	ld	e,(ix+-8)	;	ld	e,(ix+-8)
	ld	d,(ix+-7)	;	ld	d,(ix+-7)
	ld	hl,6		;	ld	hl,6
	add	hl,de		;	add	hl,de
	ld	(hl),a		;	ld	(hl),a
	ld	hl,5		;	ld	hl,5
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	ld	d,0		;	ld	d,0
	ld	l,a		;	ld	l,a
	ld	h,(ix+-5)	;	ld	h,(ix+-5)
	add	hl,de		;	add	hl,de
	ld	(ix+-6),l	;	ld	(ix+-6),l
	ld	(ix+-5),h	;	ld	(ix+-5),h
	ld	de,20h		;	ld	de,32
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	nz,loc_1E7C	;	jp	nz,l20
	ld	(ix+-6),0	;	ld	(ix+-6),0
	ld	(ix+-5),0	;	ld	(ix+-5),0
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	jr	loc_1E7C	;	jp	l20
loc_1E37:			;l21:
	ld	a,(ix+-6)	;	ld	a,(ix+-6)
	or	(ix+-5)		;	or	(ix+-5)
	jr	z,loc_1E62	;	jp	z,l25
	ld	(ix+-6),0	;	ld	(ix+-6),0
	ld	(ix+-5),0	;	ld	(ix+-5),0
	ld	e,(ix+-8)	;	ld	e,(ix+-8)
	ld	d,(ix+-7)	;	ld	d,(ix+-7)
	ld	hl,11h		;	ld	hl,17
	add	hl,de		;	add	hl,de
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	inc	de		;	inc	de
	inc	de		;	inc	de
	ld	(ix+-2),e	;	ld	(ix+-2),e
	ld	(ix+-1),d	;	ld	(ix+-1),d
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
loc_1E62:			;l25:
	ld	e,(ix+-8)	;	ld	e,(ix+-8)
	ld	d,(ix+-7)	;	ld	d,(ix+-7)
	ld	hl,9		;	ld	hl,9
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl) 		;	ld	b,(hl)
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	add	hl,bc		;	add	hl,bc
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
loc_1E7C:			;l20:
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	inc	hl		;	inc	hl
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
loc_1E89:			;l16:
	ld	l,(iy+19)	;	ld	l,(iy+19)
	ld	h,(iy+20)	;	ld	h,(iy+20)
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl) 		;	ld	d,(hl)
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	nz,loc_1D17	;	jp	nz,l17
	ld	a,(ix+-6)	;	ld	a,(ix+-6)
	or	(ix+-5)		;	or	(ix+-5)
	jr	z,loc_1EBC	;	jp	z,l26
	ld	(ix+-6),0	;	ld	(ix+-6),0
	ld	(ix+-5),0	;	ld	(ix+-5),0
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
loc_1EBC:			;l26:
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	call	_sub_1C6D	;	call	_sub_1C6D
	ld	(iy+9),l	;	ld	(iy+9),l
	ld	(iy+10),h	;	ld	(iy+10),h
	ld	(iy+17),0	;	ld	(iy+17),0
	ld	(iy+18),0	;	ld	(iy+18),0
	ld	(iy+2),37h 	;	ld	(iy+2),55
	jp	cret		;	jp	cret

; End of function sub_1CEF OK++

;=========================================================
; sub_1EDF OK++
;=========================================================
	global	_sub_1EDF	;	global	_sub_1EDF
	global	_hashtab	;	global	_hashtab
	global	_sub_14D3	;	global	_sub_14D3
	global	_nstdpth	;	global	_nstdpth
	global	_word_AFE9	;	global	_word_AFE9
	global 	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_1EDF:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	ld	hl,_hashtab	;	ld	hl,_hashtab
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
loc_1EEC:			;l30:
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	pop	iy		;	pop	iy
	jr	loc_1F1D	;	jp	l31
loc_1EFA:			;l32:
	ld	a,(iy+2)	;	ld	a,(iy+2)
	cp	39h 		;	cp	57
	jr	nz,loc_1F14	;	jp	nz,l34
	ld	a,(iy+15h)	;	ld	a,(iy+21)
	cp	2		;	cp	2
	jr	nz,loc_1F14	;	jp	nz,l34
	bit	2,(iy+3)	;	bit	2,(iy+3)
	jr	z,loc_1F14	;	jp	z,l34
	push	iy		;	push	iy
	call	_sub_14D3	;	call	_sub_14D3
	pop	bc		;	pop	bc
loc_1F14:			;l34:
	ld	l,(iy+7)	;	ld	l,(iy+7)
	ld	h,(iy+8)	;	ld	h,(iy+8)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
loc_1F1D:			;l31:
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	z,loc_1F32	;	jp	z,l28
	ld	de,(_nstdpth)	;	ld	de,(_nstdpth)
	ld	l,(iy+4)	;	ld	l,(iy+4)
	ld	h,0		;	ld	h,0
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	z,loc_1EFA	;	jp	z,l32
loc_1F32:			;l28:
	ld	de,_word_AFE9	;	ld	de,_word_AFE9
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_1EEC	;	jp	nz,l30
	jp	cret		;	jp	cret

; End of function sub_1EDF OK++

; End of file 1C8E.as

