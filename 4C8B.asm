*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 4C8B.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_4C8B OK++
;=========================================================
	global	_sub_4C8B	;	global	_sub_4C8B
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_sub_36E0	;	global	_sub_36E0
	global	_dopetab	;	global	_dopetab
	global	_sub_605E	;	global	_sub_605E
	global	_sub_43EF	;	global	_sub_43EF
	global 	csv		;	global 	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_4C8B:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	a,(hl)		;	ld	a,(hl)
	cp	1		;	cp	1
	jr	nz,loc_4CD6	;	jp	nz,l12
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-2),c	;	ld	(ix+-2),c
	ld	(ix+-1),b	;	ld	(ix+-1),b
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	push	iy		;	push	iy
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
loc_4CCD:			;L4:
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	jp	cret		;	jp	cret
loc_4CD6:			;l12:
	ld	de,_dopetab	;	ld	de,_dopetab
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	a,c		;	ld	a,c
	and	2Ch		;	and	44
	ld	l,a		;	ld	l,a
	ld	a,b		;	ld	a,b
	and	1		;	and	1
	ld	h,a		;	ld	h,a
	ld	de,28h		;	ld	de,40
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_4D14	;	jp	nz,l13
	push	iy		;	push	iy
	call	_sub_36E0	;	call	_sub_36E0
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	l,(hl)		;	ld	l,(hl)
	ld	h, 0		;	ld	h,0
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_605E	;	call	_sub_605E
	pop	bc		;	pop	bc
loc_4D0A:			;L5:
	ld	a,l		;	ld	a,l
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	(hl),a		;	ld	(hl),a
	jr	loc_4CCD	;	jp	L4
loc_4D14:			;l13:
	ld	de,_dopetab	;	ld	de,_dopetab
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	bit	5,c		;	bit	5,c
	jp	z,loc_4D9D	;	jp	z,l14
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	hl,1		;	ld	hl,1
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	pop	de		;	pop	de
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,1Bh		;	ld	hl,27
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	hl,1		;	ld	hl,1
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,1Bh		;	ld	hl,27
	add	hl,de		;	add	hl,de
	pop	de		;	pop	de
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	push	iy		;	push	iy
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	a,(hl)		;	ld	a,(hl)
	cp	8		;	cp	8
	jr	z,loc_4D97	;	jp	z,L2
	ld	hl,8		;	ld	hl,8
	jp	loc_4D0A	;	jp	L5
loc_4D97:			;L2:
	ld	hl,3Dh		;	ld	hl,61
	jp	loc_4D0A	;	jp	L5
loc_4D9D:			;l14:
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	jp	cret		;	jp	cret

; End of function sub_4C8B OK++

;=========================================================
; sub_4DA3 OK++
;=========================================================
	global	_sub_4DA3	;	global	_sub_4DA3
	global	_sub_415E	;	global	_sub_415E
	global	_sub_475C	;	global	_sub_475C
	global	_sub_385B	;	global	_sub_385B
	global	_sub_3712	;	global	_sub_3712
	global 	csv		;	global 	csv

; Disassembled version		; After compiling C source code
_sub_4DA3:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	hl,15h		;	ld	hl,21
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	cp	1		;	cp	1
	jp	nz,loc_4E5C	;	jp	nz,L6
	ld	hl,11h		;	ld	hl,17
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	ld	a,d		;	ld	a,d
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	l,a		;	ld	l,a
	ld	h,a		;	ld	h,a
	push	hl		;	push	hl
	push	de		;	push	de
	call	_sub_415E	;	call	_sub_415E
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ex	de,hl		;	ex	de,hl
	ld	hl,17h		;	ld	hl,23
	add	hl,de		;	add	hl,de
	ld	e,(iy+17h)	;	ld	e,(iy+23)
	ld	d,(iy+18h)	;	ld	d,(iy+24)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,15h		;	ld	hl,21
	add	hl,de		;	add	hl,de
	ld	e,(iy+15h)	;	ld	e,(iy+21)
	ld	d,(iy+16h)	;	ld	d,(iy+22)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	push	iy		;	push	iy
	call	_sub_475C	;	call	_sub_475C
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_385B	;	call	_sub_385B
	pop	bc		;	pop	bc
	call	_sub_3712	;	call	_sub_3712
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	iy		;	push	iy
	pop	de		;	pop	de
	push	hl		;	push	hl
	ld	bc,1Dh		;	ld	bc,29
	ldir			;	ldir
	pop	hl		;	pop	hl
	ld	(iy+0),45h	;	ld	(iy+0),69
	ld	(iy+19h),8	;	ld	(iy+25),8
	ld	(iy+1Ah),0	;	ld	(iy+26),0
	ld	(iy+1Bh),0	;	ld	(iy+27),0
	ld	(iy+1Ch),0	;	ld	(iy+28),0
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	push	iy		;	push	iy
	ld	hl,0Eh		;	ld	hl,14
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	hl,0		;	ld	hl,0
	ex	(sp),hl		;	ex	(sp),hl
	push	iy		;	push	iy
	ld	hl,0Dh		;	ld	hl,13
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	jp	cret		;	jp	cret
loc_4E5C:			;L6:
	ld	hl,15h		;	ld	hl,21
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	cp	2		;	cp	2
	jr	nz,loc_4E87	;	jp	nz,l17
	ld	(iy+0),45h	;	ld	(iy+0),69
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	hl,13h		;	ld	hl,19
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	ld	a,d		;	ld	a,d
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	l,a		;	ld	l,a
	ld	h,a		;	ld	h,a
	ld	(iy+19h),e	;	ld	(iy+25),e
	ld	(iy+1Ah),d	;	ld	(iy+26),d
	ld	(iy+1Bh),l	;	ld	(iy+27),l
	ld	(iy+1Ch),h	;	ld	(iy+28),h
loc_4E87:			;l17:
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	jp	cret		;	jp	cret

; End of function sub_4DA3 OK++

;=========================================================
; sub_4E8D OK++
;=========================================================
	global	_sub_4E8D	;	global	_sub_4E8D
	global 	csv		;	global 	csv

; Disassembled version		; After compiling C source code
_sub_4E8D:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	de,_dopetab	;	ld	de,_dopetab
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	bit	4,b		;	bit	4,b
	jr	z,loc_4EFE	;	jp	z,l19
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,17h		;	ld	hl,23
	add	hl,de		;	add	hl,de
	ld	e,(iy+17h)	;	ld	e,(iy+23)
	ld	d,(iy+18h)	;	ld	d,(iy+24)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,15h		;	ld	hl,21
	add	hl,de		;	add	hl,de
	ld	e,(iy+15h)	;	ld	e,(iy+21)
	ld	d,(iy+16h)	;	ld	d,(iy+22)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	ld	hl,9		;	ld	hl,9
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	(iy+19h),l	;	ld	(iy+25),l
	ld	(iy+1Ah),h	;	ld	(iy+26),h
	jr	loc_4F4F	;	jp	l20
loc_4EFE:			;l19:
	call	_sub_3712	;	call	_sub_3712
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	push	hl		;	push	hl
	ld	bc,1Dh		;	ld	bc,29
	ldir			;	ldir
	pop	hl		;	pop	hl
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	(hl),41h	;	ld	(hl),65
	push	hl		;	push	hl
	call	_sub_385B	;	call	_sub_385B
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ex	(sp),hl		;	ex	(sp),hl
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	ld	hl,9		;	ld	hl,9
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ex	(sp),hl		;	ex	(sp),hl
	ld	hl,14h		;	ld	hl,20
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(iy+19h),l	;	ld	(iy+25),l
	ld	(iy+1Ah),h	;	ld	(iy+26),h
loc_4F4F:			;l20:
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,17h		;	ld	hl,23
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+17h),c	;	ld	(iy+23),c
	ld	(iy+18h),b	;	ld	(iy+24),b
	ld	hl,15h		;	ld	hl,21
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+15h),c	;	ld	(iy+21),c
	ld	(iy+16h),b	;	ld	(iy+22),b
	ld	e,(iy+1Bh)	;	ld	e,(iy+27)
	ld	d,(iy+1Ch)	;	ld	d,(iy+28)
	ld	hl,15h		;	ld	hl,21
	add	hl,de		;	add	hl,de
	ld	e,c		;	ld	e,c
	ld	d,b		;	ld	d,b
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	e,(iy+1Bh)	;	ld	e,(iy+27)
	ld	d,(iy+1Ch)	;	ld	d,(iy+28)
	ld	hl,17h		;	ld	hl,23
	add	hl,de		;	add	hl,de
	ld	e,(iy+17h)	;	ld	e,(iy+23)
	ld	d,(iy+18h)	;	ld	d,(iy+24)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	(iy+0),0Eh	;	ld	(iy+0),14
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	push	iy		;	push	iy
	ld	hl,0Dh		;	ld	hl,13
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	jp	cret		;	jp	cret

; End of function sub_4E8D OK++

;=========================================================
; sub_4FA8 OK++
;=========================================================
	global	_sub_4FA8	;	global	_sub_4FA8
	global 	csv		;	global 	csv

; Disassembled version		; After compiling C source code
_sub_4FA8:
	call 	csv		;	call	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(iy+27)	;	ld	l,(iy+1Bh)
	ld	h,(iy+28)	;	ld	h,(iy+1Ch)
	push	hl		;	push	hl
	call	_sub_475C	;	call	_sub_475C
	pop	bc		;	pop	bc
	push	iy		;	push	iy
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	ld	l,(iy+25)	;	ld	l,(iy+19h)
	ld	h,(iy+26)	;	ld	h,(iy+1Ah)
	jp	cret		;	jp	cret

; End of function sub_4FA8 OK++

; End of file 4C8B.as


