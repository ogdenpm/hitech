*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

	global	_sub_61AA		;global	_sub_61AA
	global	ncsv, cret, indir	;global	ncsv, cret, indir
	global	_rflag			;global	_rflag
	global	__ctype_		;global	__ctype_
	global	wrelop			;global	wrelop
	global	_sub_6589		;global	_sub_6589
	global	_word_B017		;global	_word_B017
	global	_array_AAE8		;global	_array_AAE8
	global 	csv

	psect	text

; After compiling C source code	;	Disassembled version
_sub_61AA:
	call 	csv		;	call	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy

	ld	a,(_rflag)	;	ld	a,(_rflag)
	or	a		;	or	a
	jp	nz,loc_61FA	;	jp	nz,L1

	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de
	bit	0,(hl)		;	bit	0,(hl)
	jp	z,loc_61FA	;	jp	z,L1

	ld	de,1		;	ld	de,1
	ld	l,(iy+13)	;	ld	l,(iy+0Dh)
	ld	h,(iy+14)	;	ld	h,(iy+0Eh)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	nz,loc_61FA	;	jp	nz,L1

	ld	e,(iy+11)	;	ld	e,(iy+0Bh)
	ld	d,(iy+12)	;	ld	d,(iy+0Ch)
	ld	hl,1		;	ld	hl,1
	call	wrelop		;	call	wrelop
	jr	c,loc_61FA	;	jr	c,L1

	ld	hl,9		;	ld	hl,9
	push	hl		;	push	hl
	ld	hl,(_word_B017)	;	ld	hl,(_word_B017)
	push	hl		;	push	hl
	call	_sub_6589	;	call	_sub_6589
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	or	a		;	or	a
	jr	nz,loc_61FF	;	jp	nz,l16
loc_61FA:			;L1:
	ld	l,0		;	ld	hl,0
	jp	cret		;	jp	cret
loc_61FF:			;l16:
	ld	a,(iy+21)	;	ld	a,(iy+15h)
	cp	5		;	cp	5
	jr	nz,loc_620A	;	jp	nz,l17

	set	2,(iy+3)	;	set	2,(iy+3)
loc_620A:			;l17:
	ld	(iy+21),2	;	ld	(iy+15h),2

	ld	hl,9		;	ld	hl,9
	push	hl		;	push	hl
	ld	hl,(_word_B017)	;	ld	hl,(_word_B017)
	push	hl		;	push	hl
	call	_sub_6589	;	call	_sub_6589
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc

	ld	h,0		;	ld	h,0
	ld	(iy+19),l	;	ld	(iy+13h),l
	ld	(iy+20),h	;	ld	(iy+14h),h

	ld	de,_array_AAE8	;	ld	de,_array_AAE8		; Unnecessary 
	ld	h,(iy+20)	;	ld	h,(iy+14h)	   <----+ command
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	hl,-1		;	ld	hl,0FFFFh
	or	a		;	or	a
	sbc	hl,bc		;	sbc	hl,bc
	ex	de,hl		;	ex	de,hl
	ld	hl,(_word_B017)	;	ld	hl,(_word_B017)
	ld	a,l		;	ld	a,l
	and	e		;	and	e
	ld	l,a		;	ld	l,a
	ld	a,h		;	ld	a,h
	and	d		;	and	d
	ld	h,a		;	ld	h,a
	ld	(_word_B017),hl	;	ld	(_word_B017),hl
	ld	l,1		;	ld	hl,1
	jp	cret		;	jp	cret

; End of function sub_61AA OK++

	global	_sub_6246		;global	_sub_6246
	global	_nodesize		;global	_nodesize
	global	_sub_14F3		;global	_sub_14F3
	global 	csv

; After compiling C source code	;	Disassembled version
_sub_6246:
	call 	csv		;	call	csv
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	call	_nodesize	;	call	_nodesize
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	pop	de		;	pop	de
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	nz,loc_6289	;	jp	nz,l19

	ld	l,(ix+8)	;	ld	l, (ix+8)
	ld	h,(ix+9)	;	ld	h, (ix+9)
	push	hl		;	push	hl
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	e,l		;	ld	e,l
	push	de		;	push	de
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	pop	de		;	pop	de
	cp	e		;	cp	e
	jr	nz,loc_6289	;	jp	nz,l19

	ld	hl,1		;	ld	hl,1
	jp	cret		;	jp	cret
loc_6289:			;l19:
	ld	hl,0		;	ld	hl,0
	jp	cret		;	jp	cret

; End of function sub_6246 OK++

	global	_sub_628F		;global	_sub_628F
	global 	csv

; After compiling C source code	;	Disassembled version
_sub_628F:
	call 	csv		;	call	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	1		;	cp	1
	jr	nz,loc_62B8	;	jp	nz,L3
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	1		;	cp	1
	jr	nz,loc_62B8	;	jp	nz,L3
	ld	hl,1		;	ld	hl,1
	jp	cret		;	jp	cret
loc_62B8:			;L3:
	ld	hl,0		;	ld	hl,0
	jp	cret		;	jp	cret

; End of function sub_628F OK++

	global	_sub_62BE		;global	_sub_62BE
	global	brelop			;global	brelop
	global	allsh			;global	allsh
	global	asaldiv			;global	asaldiv
	global	arelop			;global	arelop
	global	arelop			;global	arelop

; After compiling C source code	;	Disassembled version
_sub_62BE:
	call 	ncsv		;	call	ncsv
	defw 	-9		;	dw	0FFF7h

	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy

	ld	l,(iy+25)	;	ld	l,(iy+19h)
	ld	h,(iy+26)	;	ld	h,(iy+1Ah)
	push	hl		;	push	hl
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	add	hl,hl		;	add	hl,hl
	add	hl,hl		;	add	hl,hl
	add	hl,hl		;	add	hl,hl
	ld	(ix+-9),l	;	ld	(ix+0F7h),l
	ld	b,32		;	ld	b,20h
	ld	a,l		;	ld	a,l
	call	brelop		;	call	brelop
	jp	m,loc_62EB	;	jp	m,l23
	ld	l,1		;	ld	l,1
	jp	cret		;	jp	cret	
loc_62EB:			;l23:
	ld	b,(ix+-9)	;	ld	b,(ix+0F7h)
	ld	de,1		;	ld	de,1
	ld	hl,0		;	ld	hl,0
	call	allsh		;	call	allsh	
	ld	(ix+-4),e	;	ld	(ix+0FCh),e
	ld	(ix+-3),d	;	ld	(ix+0FDh),d
	ld	(ix+-2),l	;	ld	(ix+0FEh),l
	ld	(ix+-1),h	;	ld	(ix+0FFh),h
	ld	(ix+-8),0	;	ld	(ix+0F8h),0
	ld	(ix+-7),0	;	ld	(ix+0F9h),0
	ld	(ix+-6),0	;	ld	(ix+0FAh),0
	ld	(ix+-5),0	;	ld	(ix+0FBh),0
	ld	l,(iy+25)	;	ld	l,(iy+19h)
	ld	h,(iy+26)	;	ld	h,(iy+1Ah)
	push	hl		;	push	hl
	push	iy		;	push	iy
	call	_sub_628F	;	call	_sub_628F
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	or	a		;	or	a
	jp	z,loc_6360	;	jp	z,l24

	ld	de,2		;	ld	de,2
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	push	de		;	push	de
	push	ix		;	push	ix
	pop	hl		;	pop	hl
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	call	asaldiv		;	call	asaldiv 
	ld	e,(ix+-4)	;	ld	e,(ix+0FCh)
	ld	d,(ix+-3)	;	ld	d,(ix+0FDh)
	ld	l,(ix+-2)	;	ld	l,(ix+0FEh)
	ld	h,(ix+-1)	;	ld	h,(ix+0FFh)
	push	hl		;	push	hl
	push	de		;	push	de
	ld	hl,0		;	ld	hl,0
	pop	bc		;	pop	bc
	or	a		;	or	a
	sbc	hl,bc		;	sbc	hl,bc
	pop	bc		;	pop	bc
	ex	de,hl		;	ex	de,hl
	ld	hl,0		;	ld	hl,0
	sbc	hl,bc		;	sbc	hl, bc
	ld	(ix+-8),e	;	ld	(ix+0F8h),e
	ld	(ix+-7),d	;	ld	(ix+0F9h),d
	ld	(ix+-6),l	;	ld	(ix+0FAh),l
	ld	(ix+-5),h	;	ld	(ix+0FBh),h
loc_6360:			;l24:
	ld	e,(ix+-8)	;	ld	e,(ix+0F8h)
	ld	d,(ix+-7)	;	ld	d,(ix+0F9h)
	ld	l,(ix+-6)	;	ld	l,(ix+0FAh)
	ld	h,(ix+-5)	;	ld	h,(ix+0FBh)
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	hl,25		;	ld	hl,19h
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
	jp	m,loc_63B2	;	jp	m,L5
	ld	e,(ix+-4)	;	ld	e,(ix+0FCh)
	ld	d,(ix+-3)	;	ld	d,(ix+0FDh)
	ld	l,(ix+-2)	;	ld	l,(ix+0FEh)
	ld	h,(ix+-1)	;	ld	h,(ix+0FFh)
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	hl,25		;	ld	hl,19h
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
	jp	p,loc_63B2	;	jp	p,L5
	ld	hl,1		;	ld	hl,1
	jp	cret		;	jp	cret
loc_63B2:			;L5:
	ld	hl,0		;	ld	hl,0
	jp	cret		;	jp	cret
	
; End of function sub_62BE OK++

; Endof function sub_61AA.as


