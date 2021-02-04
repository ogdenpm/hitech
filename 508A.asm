*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 508A.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_508A OK++
;=========================================================
	global	_sub_508A	;	global	_sub_508A
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_sub_14F3	;	global	_sub_14F3
	global	_sub_36E0	;	global	_sub_36E0
	global	_sprintf	;	global	_sprintf
	global	_allocmem	;	global	_allocmem
	global	_strlen		;	global	_strlen
	global	_strcpy		;	global	_strcpy
	global	_sub_174C	;	global	_sub_174C
	global	_dopetab	;	global	_dopetab
	global	_nodesize	;	global	_nodesize
	global	wrelop		;	global	wrelop
	global	_sub_6246	;	global	_sub_6246
	global	_sub_475C	;	global	_sub_475C
	global	wrelop		;	global	wrelop
	global	wrelop		;	global	wrelop
	global	wrelop		;	global	wrelop
	global	_sub_43EF	;	global	_sub_43EF

	psect	text

; Disassembled version		; After compiling C source code
_sub_508A:
	call	ncsv		;	call ncsv
	defw	0FFE9h		;	defw -23

	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy

	push	hl		;	push	hl
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	3		;	cp	3
	jp	nz,loc_513A	;	jp	nz,l12

	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ld	a,(hl)		;	ld	a,(hl)
	cp	43h		;	cp	67
	jp	nz,loc_513A	;	jp	nz,l12

	ex	de,hl		;	ex	de,hl
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
	ld	(ix+-23),e	;	ld	(ix+-23),e
	ld	(ix+-22),d	;	ld	(ix+-22),d
	ld	(ix+-21),l	;	ld	(ix+-21),l
	ld	(ix+-20),h	;	ld	(ix+-20),h

	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_36E0	;	call	_sub_36E0
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_36E0	;	call	_sub_36E0

	ld	e,(ix+-23)	;	ld	e,(ix+-23)
	ld	d,(ix+-22)	;	ld	d,(ix+-22)
	ld	l,(ix+-21)	;	ld	l,(ix+-21)
	ld	h,(ix+-20)	;	ld	h,(ix+-20)
	ex	(sp),hl		;	ex	(sp),hl
	push	de		;	push	de
	ld	hl,d_508A_AA7C	;	ld	hl,19f
	push	hl		;	push	hl
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,0FFEDh	;	ld	hl,-19
	add	hl,de		;	add	hl,de
	push	hl		;	push	hl
	call	_sprintf	;	call	_sprintf
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc

	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,0FFEDh	;	ld	hl,-19
	add	hl,de		;	add	hl,de
	ex	(sp),hl		;	ex	(sp),hl
	call	_strlen		;	call	_strlen
	pop	bc		;	pop	bc
	inc	hl		;	inc	hl
	push	hl		;	push	hl
	call	_allocmem	;	call	_allocmem
	ld	(iy+19h),l	;	ld	(iy+25),l
	ld	(iy+1Ah),h	;	ld	(iy+26),h

	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,0FFEDh	;	ld	hl,-19
	add	hl,de		;	add	hl,de
	ex	(sp),hl		;	ex	(sp),hl
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
loc_5134:			;L9:
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	jp	cret		;	jp	cret
loc_513A:			;l12:
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
	jp	z,loc_51C8	;	jp	z,l14

	push	iy		;	push	iy
	call	_nodesize	;	call	_nodesize
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	pop	de		;	pop	de
	call	wrelop		;	call	wrelop
	jr	c,loc_51C8	;	jp	c,l14

	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	3		;	cp	3
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	jr	z,loc_51CF	;	jp	z,L3

	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	3		;	cp	3
	jr	z,loc_51C8	;	jp	z,l14

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

	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
loc_51B9:			;L4:
	push	iy		;	push	iy
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	jp	cret		;	jp	cret
loc_51C8:			;l14:
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
loc_51CF:			;L3:
	push	iy		;	push	iy
	call	_sub_6246	;	call	_sub_6246
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	or	a		;	or	a
	jr	z,loc_520D	;	jp	z,l18

	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	call	_sub_475C	;	call	_sub_475C
	pop	bc		;	pop	bc

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

	jr	loc_51B9	;	jp	L4
loc_520D:			;l18:
	push	iy		;	push	iy
	call	_nodesize	;	call	_nodesize
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	pop	de		;	pop	de
	call	wrelop		;	call	wrelop
	jp	c,loc_5134	;	jp	c,L9

	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	a,(hl)		;	ld	a,(hl)
	cp	14h		;	cp	20
	jp	nz,loc_52CD	;	jp	nz,l20

	push	iy		;	push	iy
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,25		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	pop	de		;	pop	de
	call	wrelop		;	call	wrelop
	jp	c,loc_52CD	;	jp	c,l20

	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	push	iy		;	push	iy
	call	_sub_6246	;	call	_sub_6246
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	or	a		;	or	h
	jr	nz,loc_52A1	;	jp	nz,l23

	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	e,l		;	ld	e,l
	push	de		;	push	de
	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	pop	de		;	pop	de
	cp	e		;	cp	e
	jr	nz,loc_52CD	;	jp	nz,l20

	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	e,l		;	ld	e,l
	push	de		;	push	de
	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	pop	de		;	pop	de
	cp	e		;	cp	e
	jr	nz,loc_52CD	;	jp	nz,l20
loc_52A1:			;l23:
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b, (hl)		;	ld	b,(hl)
	ld	(iy+19h),c	;	ld	(iy+25),c
	ld	(iy+1Ah),b	;	ld	(iy+26),b

	ld	hl,1Bh		;	ld	hl,27
	add	hl, de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	call	_sub_36E0	;	call	_sub_36E0
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	jp	loc_5134	;	jp	L9
loc_52CD:			;l20:
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
	xor	a		;	xor	a
	ld	l,a		;	ld	l,a
	ld	a,b		;	ld	a,b
	and	0Ch		;	and	12
	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jp	z,loc_5134	;	jp	z,L9

	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	3		;	cp	3
	jp	z,loc_5134	;	jp	z,L9

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
	bit	2,b		;	bit	2,b
	jr	z,loc_534B	;	jp	z,l28

	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	ld	a,(hl)		;	ld	a,(hl)
	cp	14h		;	cp	20
	jp	nz,loc_5134	;	jp	nz,L9

	ld	l,e		;	ld	l,e
	ld	h,d		;	ld	h,d
	push	hl		;	push	hl
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	hl,19h		;	ld	hl,25
	add	hl,bc		;	add	hl,bc
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	pop	de		;	pop	de
	call	wrelop		;	call	wrelop
	jp	nc,loc_5134	;	jp	nc,L9
loc_534B:			;l28:
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	hl,14h		;	ld	hl,20
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h

	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	iy		;	push	iy
	pop	de		;	pop	de
	push	hl		;	push	hl
	ld	bc,1Dh		;	ld	bc,29
	ldir			;	ldir
	pop	hl		;	pop	hl

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
	bit	3,c		;	bit	3,c
	push	iy		;	push	iy
	jr	z,loc_53B4	;	jp	z,L1

	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,1Bh		;	ld	hl,27
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	hl,14h		;	ld	hl,20
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	jr	loc_53BC	;	jp	l32
loc_53B4:			;L1:
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	ld	iy,0		;	ld	iy,0
loc_53BC:			;l32:
	push	iy		;	push	iy
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	push	hl		;	push	hl
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h

	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	jp	cret		;	jp	cret

; End of function sub_508A OK++

;=========================================================
; sub_53EE OK++
;=========================================================
	global	_sub_53EE	;	global	_sub_53EE
	global	_byte_B013	;	global	_byte_B013
	global 	csv		;	global 	csv

; Disassembled version		; After compiling C source code
_sub_53EE:
	call	csv		;	call	csv
	push	hl		;	push	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy

	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	(ix+-2),e	;	ld	(ix+-2),e
	ld	(ix+-1),d	;	ld	(ix+-1),d

	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a

	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	ld	de,_dopetab	;	ld	de,_dopetab
	add	hl, de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	bit	4,b		;	bit	4,b
	jr	z,loc_5469	;	jp	z,l34

	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-2),c	;	ld	(ix+-2),c
	ld	(ix+-1),b	;	ld	(ix+-1),b
	ld	e,c		;	ld	e,c
	ld	d,b		;	ld	d,b
	ld	hl,17h		;	ld	hl,23
	add	hl,de		;	add	hl,de
	ld	e,(iy+17h)	;	ld	e,(iy+23)
	ld	d,(iy+18h)	;	ld	d,(iy+24)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	e,c		;	ld	e,c
	ld	d,b		;	ld	d,b
	ld	hl,15h		;	ld	hl,21
	add	hl,de		;	add	hl,de
	ld	e,(iy+15h)	;	ld	e,(iy+21)
	ld	d,(iy+16h)	;	ld	d,(iy+22)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	push	iy		;	push	iy
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	jp	cret		;	jp	cret
loc_5469:			;l34:
	ld	(iy+0),14h	;	ld	(iy+0),20
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	(iy+1Bh),l	;	ld	(iy+27),l
	ld	(iy+1Ch),h	;	ld	(iy+28),h
	ex	de,hl		;	ex	de,hl
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+19h),c	;	ld	(iy+25),c
	ld	(iy+1Ah),b	;	ld	(iy+26),b
	ld	l,e		;	ld	l,e
	ld	h,d		;	ld	h,d
	ld	(hl),41h	;	ld	(hl),65
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
	ld	a,1		;	ld	a,1
	ld	(_byte_B013),a	;	ld	(_byte_B013),a
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	jp	cret		;	jp	cret

	psect	data

d_5cf5_AA6B:
	;	"%s: large offset"
	defb	37,115,58,32,108,97,114,103,101,32,111,102,102,115,101,116
	defb	0

d_508A_AA7C:
	;	"%ld:
	defb	37,108,100,0

d_54b6_AA80:
	;	"mismatched comparision"
	defb	109,105,115,109,97,116,99,104,101,100,32,99,111,109,112,97
	defb	114,105,115,105,111,110,0

d_54b6_AA97:
	;	"degenerate unsigned comparision"
	defb	100,101,103,101,110,101,114,97,116,101,32,117,110,115,105,103
	defb	110,101,100,32,99,111,109,112,97,114,105,115,105,111,110,0

d_54b6_AAB7:
	;	"'Division by zero'"
	defb	68,105,118,105,115,105,111,110,32,98,121,32,122,101,114,111
	defb	0


	psect	text

; End of function sub_53EE OK++
; End of file s508A.as

*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

;=========================================================
; sub_sub_54B6 OK
;=========================================================
	global	_sub_54B6
	global	ncsv,cret,indir
	global	_dopetab
	global	_sub_4C12
	global	wrelop
	global	_byte_B013
	global	_sub_4B89
	global	_nodesize
	global	_sub_60A8
	global	_sub_14F3
	global	_sub_62BE
	global	_sub_36E0
	global	_word_B015
	global	_sub_6246
	global	_sub_4DA3
	global	_sub_4E8D
	global	_sub_4C8B
	global	_sub_4BE5
	global	_sub_475C
	global	_sub_415E
	global	asaladd
	global	arelop
	global	_sub_4FA8
	global	_sub_3712
	global	_word_AE53
	global	_word_AED9
	global	_sub_43EF
	global	arelop
	global	_sub_46F7
	global	_sub_4FCE
	global	_warning
	global	allsh
	global	lland
	global	lrelop
	global	_sub_508A
	global	_sub_53EE

	psect	text

_sub_54B6:
	call	ncsv
	defw	0FFF6h
	ld	l,(ix+6)
	ld	h,(ix+7)
	push	hl
	pop	iy
	ld	de,_dopetab
	ld	l,(iy+0)
	ld	h,0
	add	hl,hl
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ld	a,c
	and	0Ch
	ld	l,a
	xor	a
	ld	h,a
	ld	(ix+-6),l
	ld	(ix+-5),h
	ld	a,l
	or	(ix+-5)
	jr	z,loc_54F4
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	push	hl
	call	_sub_54B6
	pop	bc
	ld	(iy+19h),l
	ld	(iy+1Ah),h
 loc_54F4:
	ld	de,8
	ld	l,(ix+-6)
	ld	h,(ix+-5)
	or	a
	sbc	hl,de
	jr	nz,loc_5513
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	push	hl
	call	_sub_54B6
	pop	bc
	ld	(iy+1Bh),l
	ld	(iy+1Ch),h
loc_5513:
	ld	de,_dopetab
	ld	l,(iy+0)
	ld	h,0
	add	hl,hl
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	bit	6,c
	jp	z,loc_5638
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	push	hl
	call	_sub_4C12
	ex	(sp),hl
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	push	hl
	call	_sub_4C12
	pop	bc
	pop	de
	call	wrelop
	jp	p,loc_556B
	ld	a,1
	ld	(_byte_B013),a
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	ld	(ix+-2),l
	ld	(ix+-1),h
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	ld	(iy+19h),l
	ld	(iy+1Ah),h
	ld	l,(ix+-2)
	ld	h,(ix+-1)
	ld	(iy+1Bh),l
	ld	(iy+1Ch),h
loc_556B:
	ld	de,_dopetab
	ld	l,(iy+0)
	ld	h,0
	add	hl,hl
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	bit	5,b
	jp	z,loc_5638
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	ld	a,(iy+0)
	cp	(hl)
	jp	nz,loc_5638
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	push  	hl
	call	_sub_4B89
	pop	bc
	ld	a,l
	or	a
	jr	z,loc_55E2
	ld	e,(iy+19h)
	ld	d,(iy+1Ah)
	ld	(ix+-2),e
	ld	(ix+-1),d
	ld	hl,1Bh
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	call	_sub_4B89
	pop	bc
	ld	a,l
	or	a
	jr	z,loc_55E2
	ld	a,1
	ld	(_byte_B013),a
	ld	e,(ix+-2)
	ld	d,(ix+-1)
	ld	hl,1Bh
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ld	(iy+19h),c
	ld	(iy+1Ah),b
	ld	hl,1Bh
	add	hl,de
	push	iy
	pop	de
	ld	(hl),e
	inc	hl
	ld	(hl),d
	ld	l,(ix+-2)
	ld	h,(ix+-1)
	push	hl
	pop	iy
	jr	loc_5638
loc_55E2:
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	push	hl
	call	_sub_4C12
	pop	bc
	push	hl
	ld	e,(iy+19h)
	ld	d,(iy+1Ah)
	ld	hl,1Bh
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	call	_sub_4C12
	pop	bc
	pop	de
	call	wrelop
	jp	p,loc_5638
	ld	a,1
	ld	(_byte_B013),a
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	ld	(ix+-2),l
	ld	(ix+-1),h
	ld	e,(iy+19h)
	ld	d,(iy+1Ah)
	ld	hl,1Bh
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ld	(iy+1Bh),c
	ld	(iy+1Ch),b
	ld	hl,1Bh
	add	hl,de
	ld	e,(ix+-2)
	ld	d,(ix+-1)
	ld	(hl),e
	inc	hl
	ld	(hl),d
loc_5638:
	ld	de,_dopetab
	ld	l,(iy+0)
	ld	h,0
	add	hl,hl
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	xor	a
	ld	l,a
	ld	a,b
	and	0Ch
	ld	h,a
	ld	de,800h
	or	a
	sbc	hl,de
	jp	nz,loc_5715
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	ld	a,(hl)
	cp	14h
	jp	nz,loc_5715
	push	iy
	call	_nodesize
	pop	bc
	push	hl
	ld	e,(iy+19h)
	ld	d,(iy+1Ah)
	ld	hl,19h
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	call	_nodesize
	pop	bc
	pop	de
	call	wrelop
	jp	nc,loc_5715
	ld	e,(iy+19h)
	ld	d,(iy+1Ah)
	ld	hl,19h
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	push	hl
	call	_sub_60A8
	pop	bc
	pop	bc
	ld	a,l
	or	a
	jp	z,loc_5715
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	ld	(ix+-4),l
	ld	(ix+-3),h
	ld	e,(ix+-4)
	ld	d,(ix+-3)
	ld	hl,19h
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ld	(iy+19h),c
	ld	(iy+1Ah),b
	ld	e,c
	ld	d,b
	ld	hl,17h
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ld	(iy+17h),c
	ld	(iy+18h),b
	ld	hl,15h
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ld	(iy+15h),c
	ld	(iy+16h),b
	ld	e,(iy+1Bh)
	ld	d,(iy+1Ch)
	ld	hl,17h
	add	hl,de
	ld	e,(iy+17h)
	ld	d,(iy+18h)
	ld	(hl),e
	inc	hl
	ld	(hl),d
	ld	e,(iy+1Bh)
	ld	d,(iy+1Ch)
	ld	hl,15h
	add	hl,de
	ld	e,c
	ld	d,b
	ld	(hl),e
	inc	hl
	ld	(hl),d
	ld	e,(ix+-4)
	ld	d,(ix+-3)
	ld	hl,19h
	add	hl,de
	push	iy
	pop	de
	ld	(hl),e
	inc	hl
	ld	(hl),d
	ld	l,(ix+-4)
	ld	h,(ix+-3)
	push	hl
	pop	iy
 loc_5715:
	ld	de,_dopetab
	ld	l,(iy+0)
	ld	h,0
	add	hl,hl
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ld	a,c
	and	20h
	ld	l,a
	ld	a,b
	and	4
	ld	h,a
	ld	de,420h
	or	a
	sbc	hl,de
	jp	nz,loc_58D0
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	ld	(ix+-2),l
	ld	(ix+-1),h
	ld	a,(hl)
	cp	14h
	jp	nz,loc_58D0
	ld	e,(ix+-2)
	ld	d,(ix+-1)
	ld	hl,19h
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	call	_nodesize
	pop	bc
	ld	a,l
	or	h
	jp	z,loc_58D0
	ld	l,(ix+-2)
	ld	h,(ix+-1)
	push	hl
	call	_nodesize
	pop	bc
	push	hl
	ld	e,(ix+-2)
	ld	d,(ix+-1)
	ld	hl,19h
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	call	_nodesize
	pop	bc
	pop	de
	call	wrelop
	jp	nc,loc_58D0
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	ld	a,(hl)
	cp	43h
	jp	nz,loc_5839
	ld	l,(ix+-2)
	ld	h,(ix+-1)
	push	hl
	call	_sub_14F3
	pop	bc
	ld	a,l
	cp	1
	jr	z,loc_57B5
	ld	e,(ix+-2)
	ld	d,(ix+-1)
	ld	hl,19h
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	call	_sub_14F3
	pop	bc
	ld	a,l
	cp	2
	jp	nz,loc_5839
 loc_57B5:
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	push	hl
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	push	hl
	call	_sub_62BE
	pop	bc
	pop	bc
	ld	a,l
	or	a
	jp	z,loc_5830
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	push	hl
	call	_sub_36E0
	pop	bc
	ld	e,(iy+19h)
	ld	d,(iy+1Ah)
	ld	hl,1Bh
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	call	_sub_36E0
	pop	bc
	ld	e,(iy+19h)
	ld	d,(iy+1Ah)
	ld	hl,19h
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ld	(iy+19h),c
	ld	(iy+1Ah),b
	ld	e,c
	ld	d,b
	ld	hl,17h
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ld	e,(iy+1Bh)
	ld	d,(iy+1Ch)
	ld	hl,17h
	add	hl,de
	ld	(hl),c
	inc	hl
	ld	(hl),b
	ld	e,(iy+19h)
	ld	d,(iy+1Ah)
	ld	hl,15h
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ld	e,(iy+1Bh)
	ld	d,(iy+1Ch)
	ld	hl,15h
	add	hl,de
	ld	(hl),c
	inc	hl
	ld	(hl),b
	jp	loc_58D0
 loc_5830:
	ld	hl,d_54b6_AA80
	ld	(_word_B015),hl
	jp	loc_58D0
 loc_5839:
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	ld	a,(hl)
	cp	14h
	jp	nz,loc_58D0
	ex	de,hl
	ld	hl,19h
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	ld	e,(iy+19h)
	ld	d,(iy+1Ah)
	ld	hl,19h
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	call	_sub_6246
	pop	bc
	pop	bc
	ld	a,l
	or	a
	jp	z,loc_58D0
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	ld	(ix+-2),l
	ld	(ix+-1),h
	ld	e,(ix+-2)
	ld	d,(ix+-1)
	ld	hl,19h
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ld	(iy+19h),c
	ld	(iy+1Ah),b
	ld	hl,1Bh
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	call	_sub_36E0
	ld	l,(ix+-2)
	ld	h,(ix+-1)
	ex	(sp),hl
	call	_sub_36E0
	pop	bc
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	ld	(ix+-2),l
	ld	(ix+-1),h
	ld	e,(ix+-2)
	ld	d,(ix+-1)
	ld	hl,19h
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ld	(iy+1Bh),c
	ld	(iy+1Ch),b
	ld	hl,1Bh
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	call	_sub_36E0
	ld	l,(ix+-2)
	ld	h,(ix+-1)
	ex	(sp),hl
	call	_sub_36E0
	pop	bc
 loc_58D0:
	ld	a,(iy+0)
	cp	1
	jp	z,loc_5973
	cp	6
	jp	z,loc_5B65
	cp	7
	jp	z,loc_5B90
	cp	9
	jp	z,loc_5CB0
	cp	0Ch
	jp	z,loc_5B3A
	cp	0Dh
	jp	z,loc_5CC4
	cp	0Eh
	jp	z,loc_5A9B
	cp	10h
	jp	z,loc_5C9E
	cp	12h
	jp	z,loc_5A9B
	cp	14h
	jp	z,loc_5C96
	cp	16h
	jp	z,loc_596C
	cp	18h
	jp	z,loc_5B3A
	cp	1Eh
	jp	z,loc_597A
	cp	1Fh
	jp	z,loc_5A9B
	cp	20h
	jp	z,loc_59C9
	cp	22h
	jp	z,loc_5B65
	cp	23h
	jp	z,loc_5B90
	cp	24h
	jp	z,loc_5B3A
	cp	25h
	jp	z,loc_5A9B
	cp	26h
	jp	z,loc_5A9B
	cp	27h
	jp	z,loc_5B3A
	cp	28h
	jp	z,loc_5A9B
	cp	2Ah
	jp	z,loc_5A9B
	cp	2Ch
	jp	z,loc_5A58
	cp	2Dh
	jp	z,loc_59C9
	cp	2Eh
	jr	z,loc_597A
	cp	2Fh
	jp	z,loc_5A9B
	cp	3Ch
	jp	z,loc_5A58
	cp	42h
	push	iy
	jp	nz,loc_59C5
	call	_sub_4DA3
 loc_5968:
	pop	bc
	jp	cret
 loc_596C:
	push	iy
	call	_sub_4E8D
	jr	loc_5968
 loc_5973:
	push	iy
	call	_sub_4C8B
	jr	loc_5968
 loc_597A:
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	push	hl
	call	_sub_14F3
	pop	bc
	ld	a,l
	cp	2
	jr	nz,loc_59C3
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	push	hl
	call	_sub_4BE5
	pop	bc
	ld	a,l
	or	a
	jr	z,loc_59C3
	ld	hl,d_54b6_AA97
	ld	(_word_B015),hl
	push	iy
	call	_sub_475C
	pop	bc
	ld	a,(iy+0)
	cp	2Eh
	jr	z,loc_59B3
	ld	de,0
	ld	l,e
	ld	h,d
	jr	loc_59B9
 loc_59B3:
	ld	de,1
	ld	hl,0
 loc_59B9:
	push	hl
	push	de
	call	_sub_415E
	pop	bc
	pop	bc
	push	hl
	pop	iy
 loc_59C3:
	push	iy
 loc_59C5:
	pop	hl
	jp	cret
 loc_59C9:
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	push	hl
	call	_sub_14F3
	pop	bc
	ld	a,l
	cp	2
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	jr	nz,loc_5A02
	push	hl
	call	_sub_4BE5
	pop	bc
	ld	a,l
	or	a
	jr	z,loc_59FC
	ld	a,(iy+0)
	cp	2Dh
	jr	z,loc_59F4
	ld	hl,29h
	jr	loc_59F7
 loc_59F4:
	ld	hl,2
 loc_59F7:
	ld	(iy+0),l
	jr	loc_59C3
 loc_59FC:
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
 loc_5A02:
	ld	a,(hl)
	cp	43h
	jr	nz,loc_5A28
	ld	de,1
	ld	hl,0
	push	hl
	push	de
	ld	e,(iy+1Bh)
	ld	d,(iy+1Ch)
	ld	hl,19h
	add	hl,de
	call	asaladd
	ld	a,(iy+0)
	cp	2Dh
	jr	z,loc_5A53
 loc_5A23:
	ld	hl,1Eh
	jr	loc_59F7
 loc_5A28:
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	ld	(ix+-2),l
	ld	(ix+-1),h
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	ld	(iy+19h),l
	ld	(iy+1Ah),h
	ld	l,(ix+-2)
	ld	h,(ix+-1)
	ld	(iy+1Bh),l
	ld	(iy+1Ch),h
	ld	a,(iy+0)
	cp	2Dh
	jr	z,loc_5A23
 loc_5A53:
	ld	hl,2Eh
	jr	loc_59F7
 loc_5A58:
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	ld	a,(hl)
	cp	43h
	jr	nz,loc_5A9B
	ld	de,0FFFFh
	ld	l,e
	ld	h,d
	push	hl
	push	de
	ld	e,(iy+1Bh)
	ld	d,(iy+1Ch)
	ld	hl,19h
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	inc	hl
	ld	a,(hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	call	lrelop
	jr	nz,loc_5A9B
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	push	hl
	call	_sub_475C
	pop	bc
	push	iy
	call	_sub_36E0
	pop	bc
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	jp	cret
 loc_5A9B:
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	ld	a,(hl)
	cp	43h
	jr	nz,loc_5AC1
	ex	de,hl
	ld	hl,19h
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	inc	hl
	ld	a,(hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	ld	a,e
	or	d
	or	l
	or	h
	jr	nz,loc_5AC1
 loc_5AB9:
	push	iy
 loc_5ABB:
	call	_sub_4FA8
	jp	loc_5968
 loc_5AC1:
	ld	de,_dopetab
	ld	l,(iy+0)
	ld	h,0
	add	hl,hl
	add	hl,de
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	bit	7,c
	jp	z,loc_59C3
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	push	hl
	call	_nodesize
	pop	bc
	ld	de,1
	or	a
	sbc	hl,de
	jp	z,loc_59C3
	call	_sub_3712
	ld	(ix+-2),l
	ld	(ix+-1),h
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	push	hl
	call	_sub_14F3
	pop	bc
	ld	a,l
	cp	2
	jr	z,loc_5B05
	ld	hl,(_word_AED9)
	jr	loc_5B08
 loc_5B05:
	ld	hl,(_word_AE53)
 loc_5B08:
	push	hl
	ld	e,(ix+-2)
	ld	d,(ix+-1)
	ld	hl,17h
	add	hl,de
	pop	de
	ld	(hl),e
	inc	hl
	ld	(hl),d
	ld	l,(ix+-2)
	ld	h,(ix+-1)
	ld	(hl),41h
	push	hl
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	push	hl
	ld	hl,14h
	push	hl
	call	_sub_43EF
	pop	bc
	pop	bc
	pop	bc
	ld	(iy+1Bh),l
	ld	(iy+1Ch),h
	jp	loc_59C3
 loc_5B3A:
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	ld	a,(hl)
	cp	43h
	jr	nz,loc_5B65
	ld	de,1
	ld	hl,0
	push	hl
	push	de
	ld	e,(iy+1Bh)
	ld	d,(iy+1Ch)
	ld	hl,19h
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	inc	hl
	ld	a,(hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	call	lrelop
	jp	z,loc_5AB9
 loc_5B65:
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	ld	a,(hl)
	cp	43h
	jr	nz,loc_5B90
	ex	de,hl
	ld	hl,19h
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	inc	hl
	ld	a,(hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	push	hl
	push	de
	call	_sub_46F7
	pop	bc
	pop	bc
	ld	a,l
	or	a
	jr	z,loc_5B90
	push	iy
	call	_sub_4FCE
	jp	loc_5968
 loc_5B90:
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	ld	a,(hl)
	cp	43h
	jp	nz,loc_5C12
	ex	de,hl
	ld	hl,19h
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	inc	hl
	ld	a,(hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	ld	a,e
	or	d
	or	l
	or	h
	jp	nz,loc_5C12
	ld	a,(iy+0)
	cp	6
	jr	z,loc_5BD4
	cp	7
	jr	z,loc_5BE1
	cp	0Ch
	jr	z,loc_5BE1
	cp	18h
	jr	z,loc_5BD4
	cp	22h
	jr	z,loc_5BD4
	cp	23h
	jp	z,loc_5C0C
	cp	24h
	jr	z,loc_5C0C
	cp	27h
	jr	nz,loc_5C12
 loc_5BD4:
	ld	hl,d_54b6_AAB7
	push	hl
	call	_warning
	pop	bc
 loc_5BDC:
	push	iy
	jp	loc_59C5
 loc_5BE1:
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	push	hl
	call	_sub_475C
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	ex	(sp),	hl
	call	_sub_475C
	pop	bc
	ld	(iy+0),43h
	ld	(iy+19h),0
	ld	(iy+1Ah),0
	ld	(iy+1Bh),0
	ld	(iy+1Ch),0
	jr	loc_5BDC
 loc_5C0C:
	ld	(iy+0),21h
	jr	loc_5BDC
 loc_5C12:
	push	iy
	call	_nodesize
	pop	bc
	ld	de,4
	call	wrelop
	jr	nc,loc_5C3D
	push	iy
	call	_nodesize
	pop	bc
	add	hl,hl
	add	hl,hl
	add	hl,hl
	ld	b,l
	ld	de,1
	ld	hl,0
	call	allsh
	ex	de,hl
	ld	bc,0FFFFh
	add	hl,bc
	ex	de,hl
	adc	hl,bc
	jr	loc_5C42
 loc_5C3D:
	ld	de,0FFFFh
	ld	l,e
	ld	h,d
 loc_5C42:
	ld	(ix+-10),e
	ld	(ix+-9),d
	ld	(ix+-8),l
	ld	(ix+-7),h
	ld	a,(iy+0)
	cp	7
	jr	z,loc_5C5A
	cp	23h
	jp	nz,loc_59C3
 loc_5C5A:
	ld	l,(iy+1Bh)
	ld	h,(iy+1Ch)
	ld	a,(hl)
	cp	43h
	jp	nz,loc_59C3
	ld	e,(ix+-10)
	ld	d,(ix+-9)
	ld	l,(ix+-8)
	ld	h,(ix+-7)
	push	hl
	push	de
	push	hl
	push	de
	ld	e,(iy+1Bh)
	ld	d,(iy+1Ch)
	ld	hl,19h
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	inc	hl
	ld	a,(hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	call	lland
	call	lrelop
	push	iy
	jp	nz,loc_59C5
	jp	loc_5ABB
 loc_5C96:
	push	iy
	call	_sub_508A
	jp	loc_5968
 loc_5C9E:
	push	iy
	call	_sub_36E0
	pop	bc
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	push	hl
	pop	iy
	jp	loc_59C3
 loc_5CB0:
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	ld	a,(hl)
	cp	0Dh
	push	iy
	jp	nz,loc_59C5
 loc_5CBE:
	call	_sub_53EE
	jp	loc_5968
 loc_5CC4:
	ld	l,(iy+19h)
	ld	h,(iy+1Ah)
	ld	a,(hl)
	cp	9
	jp	nz,loc_59C3
	ex	de,hl
	ld	hl,19h
	add	hl,de
	ld	a,(hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	ld	(ix+-2),l
	ld	(ix+-1),h
	ld	a,(hl)
	cp	0Ah
	jp	z,loc_59C3
	ld	a,(hl)
	cp	21h
	jp	z,loc_59C3
	ld	a,(hl)
	cp	30h
	push	iy
	jp	z,loc_59C5
	jr	loc_5CBE

; End	of function sub_54B6

*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

;=========================================================
; sub_sub_5CF5 OK+
;
; Compiler generates identical code from restored source
; program in C, however, location of branches associated
; with case constants is different from original.
; This does not affect the function.
;=========================================================
	global	_sub_5CF5	;	global	_sub_5CF5
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_sub_61AA	;	global	_sub_61AA
	global	_array_AE13	;	global	_array_AE13
	global	_lvlidx		;	global	_lvlidx
	global	wrelop		;	global	wrelop
	global	wrelop		;	global	wrelop
	global	_warning	;	global	_warning
	global	_sub_C57	;	global	_sub_C57
	global	_array_AE97	;	global	_array_AE97
	global	csv		;	global	csv

	psect	text

;	Disassembled version	; After compiling C source code
_sub_5CF5:
	call	csv		;	call 	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	a,(iy+15h)	;	ld	a,(iy+21)	
	cp	1		;	cp	1
	jr	z,loc_5D1A	;	jp	z,l14	
	cp	3		;	cp	3
	jp	z,loc_5DEF	;	jp	z,l19	
	cp	4		;	cp	4
	jp	z,loc_5DEF	;	jp	z,l19	
	cp	5		;	cp	5
	jp	z,loc_5D84	;	jp	z,l20	
	jp	cret		;	jp	cret
loc_5D1A:			;l14:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	push	iy		;	push	iy
	call	_sub_61AA	;	call	_sub_61AA
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	or	a		;	or	h
	jp	nz,cret		;	jp	nz,cret
	ld	c,(iy+9)	;	ld	c,(iy+9)
	ld	b,(iy+0Ah)	;	ld	b,(iy+10)
	ld	de,_array_AE13	;	ld	de,_array_AE13
	ld	hl,(_lvlidx)	;	ld	hl,(_lvlidx)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	ex	de,hl		;	ex	de,hl
	or	a		;	or	a
	sbc	hl,bc		;	sbc	hl,bc
	ex	de,hl		;	ex	de,hl
	ld	(hl),d		;	ld	(hl),d
	dec	hl		;	dec	hl
	ld	(hl),e		;	ld	(hl),e
	ex	de,hl		;	ex	de,hl
	ld	de,_array_AE13	;	ld	de,_array_AE13
	ld	hl,(_lvlidx)	;	ld	hl,(_lvlidx)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	ld	(iy+11h),l	;	ld	(iy+17),l
	ld	(iy+12h),h	;	ld	(iy+18),h
	ld	de,0FF80h	;	ld	de,-128
	call	wrelop		;	call	wrelop
	jp	p,cret		;	jp	p,cret
	ld	e,(iy+9)	;	ld	de,4
	ld	d,(iy+0Ah)	;	ld	l,(iy+9)
	ld	hl,4		;	ld	h,(iy+10)
	call	wrelop		;	call	wrelop
	jp	c,cret		;	jp	c,cret
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,(iy+1)	;	ld	h,(iy+1)
	push	hl		;	push	hl
	ld	hl,d_5cf5_AA6B	;	ld	hl,19f
	push	hl		;	push	hl
	call	_warning	;	call	_warning
	pop	bc		;	pop	bc
loc_5D80:			;L1:
	pop	bc		;	pop	bc
	jp	cret		;	jp	cret
loc_5D84:			;l20:
	ld	de,_array_AE97	;	ld	de,_array_AE97
	ld	hl,(_lvlidx)	;	ld	hl,(_lvlidx)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+11h),c	;	ld	(iy+17),c
	ld	(iy+12h),b	;	ld	(iy+18),b
	ld	c,(iy+9)	;	ld	c,(iy+9)
	ld	b,(iy+0Ah)	;	ld	b,(iy+10)
	ld	hl,(_lvlidx)	;	ld	hl,(_lvlidx)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	ex	de,hl		;	ex	de,hl
	add	hl,bc		;	add	hl,bc
	ex	de,hl		;	ex	de,hl
	ld	(hl),d		;	ld	(hl),d
	dec	hl		;	dec	hl
	ld	(hl),e		;	ld	(hl),e
	ex	de,hl		;	ex	de,hl
	ld	de,1		;	ld	de,1
	ld	l,c		;	ld	l,c
	ld	h,b		;	ld	h,b
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_5DD5	;	jp	nz,l21
	ld	l,(iy+0Fh)	;	ld	l,(iy+15)
	ld	h,(iy+10h)	;	ld	h,(iy+16)
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	a,(hl)		;	ld	a,(hl)
	cp	37h		;	cp	55
	jr	z,loc_5DD5	;	jp	z,l21		; Restored function  
	ld	a,(hl)		;			   <----+ does not generate an
	cp	38h		;	cp	56		; unnecessary command
	jr	z,loc_5DD5	;	jp	z,l21
	ld	de,_array_AE97	;	ld	de,_array_AE97
	ld	hl,(_lvlidx)	;	ld	hl,(_lvlidx)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	inc	bc		;	inc	bc
	ld	(hl),b		;	ld	(hl),b
	dec	hl		;	dec	hl
	ld	(hl),c		;	ld	(hl),c
loc_5DD5:			;l21:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	push	iy		;	push	iy
	call	_sub_61AA	;	call	_sub_61AA
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	or	a		;	or	a
	jp	nz,cret		;	jp	nz,cret
	ld	(iy+15h),1	;	ld	(iy+21),1
	jp	cret		;	jp	cret
loc_5DEF:			;l19:
	push	iy		;	push	iy
	call	_sub_C57	;	call	_sub_C57
	jr	loc_5D80	;	jp	L1

; End of function sub_5CF5 OK+


; End of file 5CF5.asm


