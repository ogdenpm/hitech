*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 47B2.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_47B2 OK+
;
; Could not find operators in C language generating code
; that exactly matches binary codes
;=========================================================
	global	_sub_47B2	;	global	_sub_47B2
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	arelop		;	global	arelop
	global	_nodesize	;	global	_nodesize
	global	_sub_3968	;	global	_sub_3968
	global	_sub_14F3	;	global	_sub_14F3
	global	_sub_2C5E	;	global	_sub_2C5E
	global	shll		;	global	shll
	global	lland		;	global	lland
	global	asalor		;	global	asalor
	global	_sub_46F7	;	global	_sub_46F7
	global 	csv		;	global 	csv

	psect	text

;	Disassembled version	; After compiling C source code
_sub_47B2:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	dec	hl		;	dec	hl
	xor	a		;	xor	a
	cp	h		;	cp	h
	jp	c,loc_4851 ;r0	;	jp	c,L50	;r0
	jr	nz,loc_47D4	;	jp	nz,L1
	ld	a,1Dh		;	ld	a,29
	cp	l		;	cp	l
	jp	c,loc_4851 ;r0	;	jp	c,L50	;r0
loc_47D4:			;L1:
	add	hl,hl		;	add	hl,hl
	ld	de,S158		;	ld	de,S160
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	jp	(hl)		;	jp	(hl)
loc_47DE:			;l14:			; case 12
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
loc_47E7:			;l15:			; case 28
	ld	de,1		;	ld	de,1
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	call	arelop		;	call	arelop
	jp	m,loc_4A59 ;r0	;	jp	m,L50	;r0
	ld	de,3		;	ld	de,3
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	call	arelop		;	call	arelop
	jp	p,loc_4A59 ;r0	;	jp	p,L50	;r0
loc_481B:			;L46:
	ld	hl,1		;	ld	l,1
	jp	cret		;	jp	cret
loc_4821:			;l18:			; case 10
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
loc_482A:			;l19:			; case 5
	push	iy		;	push	iy
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	de,2		;	ld	de,2
loc_4833:			;
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	nz,loc_4A59 ;r0	;	jp	nz,L50	;r0
				;l21:
	push	iy		;	push	iy
	call	_sub_3968	;	call	_sub_3968
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	or	a		;	or	a
loc_4841:			;L57:
	jp	nz,loc_4A59 ;r0	;	jp	nz,L50	;r0
	jr	loc_481B    ;r1	;	jp	L46	;r1
loc_4846:			;l23:			; case 6
	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	3		;	cp	3
	jr	nz,loc_485F	;	jp	nz,l25
loc_4851:			;L50:
	ld	l,0		;	ld	l,0
	jp	cret		;	jp	cret
loc_4856:			;l26:			; case 11
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
				;l25:
loc_485F:			;l27:			; case 4
	push	iy		;	push	iy
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	de,4		;	ld	de,4
	jr	loc_4833	;	or	a
				;	sbc	hl,de
				;	jp	nz,l21
				;	jp	L50	;r0
loc_486A:			;l29:			; case 27
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
loc_4873:			;l30:			; case 3
	push	iy		;	push	iy
	call	_sub_3968	;	call	_sub_3968
loc_4878:			;L62:
	pop	bc		;	pop	bc
	jp	cret		;	jp	cret
loc_487C:			;l31:			; case 13
	ld	a,(iy+19h)	;	ld	a,(iy+25)
	cp	8		;	cp	8
	jr	z,loc_481B  ;r1	;	jp	z,L46	;r1
	cp	9		;	cp	9
	jr	loc_4841	;	jp	L57	;if(nz) r0 else r1
loc_4887:			;l34:			; case 14
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	push	de		;	push	de
	push	iy		;	push	iy
	call	_sub_2C5E	;	call	_sub_2C5E
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(ix+-4),e	;	ld	(ix+-4),e
	ld	(ix+-3),d	;	ld	(ix+-3),d
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	de,0FF80h	;	ld	de,-128
	ld	hl,0FFFFh	;	ld	hl,-1
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(ix+-4)	;	ld	e,(ix+-4)
	ld	d,(ix+-3)	;	ld	d,(ix+-3)
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	call	arelop		;	call	arelop
	jp	m,loc_4A59 ;r0	;	jp	m,L50	;r0
	ld	de,7Dh		;	ld	de,125
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(ix+-4)	;	ld	e,(ix+-4)
	ld	d,(ix+-3)	;	ld	d,(ix+-3)
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
loc_48D7:			;L53:
	call	arelop		;	call	arelop
	jp	p,loc_4A59 ;r0	;	jp	p,L50	;r0
	jp	loc_481B   ;r1	;	jp	L46	;r1
loc_48E0:	; case 25	;l37:		; case 25
	ld	de,1		;	ld	de,1
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	call	arelop		;	call	arelop
	jp	m,loc_4A59 ;r0	;	jp	m,L50	;r0
	ld	de,5		;	ld	de,5
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	jr	loc_48D7	;	jp	L53
loc_4910:			;l40:			; case 26
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	ld	(ix+-4),e	;	ld	(ix+-4),e
	ld	(ix+-3),d	;	ld	(ix+-3),d
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	2		;	cp	2
	jr	nz,loc_4986	;	jp	nz,l42
	ld	e,(ix+-4)	;	ld	e,(ix+-4)
	ld	d,(ix+-3)	;	ld	d,(ix+-3)
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	push	de		;	push	de
	push	iy		;	push	iy
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	add	hl,hl		;	add	hl,hl
	add	hl,hl		;	add	hl,hl
	add	hl,hl		;	add	hl,hl
	ld	b,l		;	ld	b,l
	ld	hl,1		;	ld	hl,1
	call	shll		;	call	shll
	ex	de,hl		;	ex	de,hl
	ld	hl,0		;	ld	hl,0
	call	lland		;	call	lland
	ld	a,e		;	ld	a,e
	or	d		;	or	d
	or	l		;	or	l
	or	h		;	or	h
	jr	z,loc_4986	;	jp	z,l42
	push	iy		;	push	iy
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	add	hl,hl		;	add	hl,hl
	add	hl,hl		;	add	hl,hl
	add	hl,hl		;	add	hl,hl
	ld	b,l		;	ld	b,l
	ld	hl,1		;	ld	hl,1
	call	shll		;	call	shll
	dec	hl		;	dec	hl
	ex	de,hl		;	ex	de,hl
	ld	hl, -1		;	ld	hl,-1
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	ex	de,hl		;	ex	de,hl
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	push	de		;	push	de
	push	ix		;	push	ix
	pop	hl		;	pop	hl
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	call	asalor		;	call	asalor
loc_4986:			;l42:
	bit	7,(ix+-1)	;	bit	7,(ix+-4)
	jp	z,loc_4A59 ;r0	;	jp	z,L50	;r0
	ld	de, -4		;	ld	de,-4
	ld	hl, -1		;	ld	hl,-1
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(ix+-4)	;	ld	e,(ix+-4)
	ld	d,(ix+-3)	;	ld	d,(ix+-3)
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	call	arelop		;	call	arelop
	jp	m,loc_4A59 ;r0	;	jp	m,L50	;r0
	jp	loc_481B   ;r1	;	jp	L46	;r1
loc_49AA:			;l46:			; case 9
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
loc_49B3:			;l47:			; case 2
	push	iy		;	push	iy
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	de,1		;	ld	de,1
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	nz,loc_4A59 ;r0	;	jp	nz,L50	;r0
	push	iy		;	push	iy
	call	_sub_3968	;	call	_sub_3968
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	or	a		;	or	a
	jp	loc_4841	;L61:			; if(nz) r0 else r1
				;	jp	z,L46	; r1
				;	jp	L50	; r0
loc_49CD:			;l50:			; case 20
	push	iy		;	push	iy
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	de,4		;	ld	de,4
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	nz,loc_4851 ;r0	;	jp	nz,L50	; r0
loc_49DC:			;l52:
	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	3		;	cp	3
	jr	nz,loc_49FB	;	jp	nz,l54
	jp	loc_4851 ;r0	;	jp	L50	; r0
loc_49EA:			;l55:			; case 16
	push	iy		;	push	iy
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	de,2		;	ld	de,2
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	z,loc_49DC	;	jp	z,l52
	jp	loc_4851 ;r0	;	jp	L50	; r0
loc_49FB:			;l54:
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	3		;	cp	3
	jp	z,loc_4851 ;r0	;	jp	z,L50	; r0
	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	2		;	cp	2
loc_4A15:			;
	jp	z,loc_481B  ;r1	;	jp	z,L46	; r1
				;l59:
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	2		;	cp	2
	jp	loc_4841	;	jp	L58	;if(nz) r0 else r1
loc_4A29:	; case 29	;l61:		; case 29
	ld	a,(iy+19h)	;	ld	a,(iy+25)
	or	(iy+1Ah)	;	or	(iy+26)
	or	(iy+1Bh)	;	or	(iy+27)
	or	(iy+1Ch)	;	or	(iy+28)
loc_4A35:			;	jp	L57	;if(nz) r0 else r1
	ld	hl,1		;		   <----+ Could not find operators
	jp	z,cret		;			; in C language generating
	dec	hl		;			; code that exactly matches
	jp	cret		;		   <----+ binary codes
loc_4A3F:			;l63:			; case 19
	push	iy		;	push	iy
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	de,4		;	ld	de,4
loc_4A48:			;
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	nz,loc_4851 ;r0	;	jp	nz,L50	; r0
				;l65:
	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	1		;	cp	1
	jr	z,loc_4A6A	;	jp	nz,L50	; r0
				;	ld	l,(iy+25)
				;	ld	h,(iy+26)
				;	push	hl
				;	call	_sub_14F3
				;	pop	bc
				;	ld	a,l
				;	cp	1
				;	jp	L57
loc_4A59:			;
	ld	hl,0		;
	jp	cret		;
loc_4A5F:			;l68:			; case 17
	push	iy		;	push	iy
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	de,2		;	ld	de,2
	jr	loc_4A48	;	or	a
				;	sbc	hl,de
				;	jp	z,l65
				;	jp	L50	; r0
loc_4A6A:			;
	ld	l,(iy+19h)	;
	ld	h,(iy+1Ah)	;
	push	hl		;
	call	_sub_14F3	;
	pop	bc		;
	ld	a,l		;
	cp	1		;
	jp	loc_4841	;
				;
loc_4A7B:			;l70:			; case15
	ld	de,1		;	ld	de,1
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	push	de		;	push	de
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	call	arelop		;	call	arelop
				;	jp	L57	if(nz) r0 else r1
	ld	bc,1		;			   <----+ Could not find
	jr	z,loc_4A98	;				; operators in C
	dec	bc		;				; language generating
loc_4A98:			;				; code that exactly
	ld	l,c		;				; matches binary
	jp	cret		;			   <----+ codes
loc_4A9C:	; case 0	;l72:			; case 0
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
loc_4AAE:			;L45:
	push	hl		;	push	hl
	push	de		;	push	de
	call	_sub_46F7	;	call	_sub_46F7
	pop	bc		;	pop	bc
	jp	loc_4878	;	jp	L59
loc_4AB7:			;l73:			; case 1
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
	ld	hl, -1		;	ld	de,-1	   <----+ At this point,
	pop	bc		;	ld	l,e		; from source
	or	a		;	ld	h,d		; in C, compiler
	sbc	hl,bc		;	call	alsub		; generates code
	pop	bc		;				; that performs
	ex	de,hl		;				; expected action,
	ld	hl, -1		;				; but differs from 
	sbc	hl,bc		;			   <----+ original image
	jr	loc_4AAE	;	jp	L45
loc_4ADB:			;l74:			; case 24
	push	iy		;	push	iy
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	de,4		;	ld	de,4
loc_4AE4:			;L22:
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	z,loc_4B02	;	jp	z,l76
	jp	loc_4851 ;r0	;	jp	L50	;r0
loc_4AEC:			;l77:			; case 18
	push	iy		;	push	iy
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	de,2		;	ld	de,2
	jr	loc_4AE4	;	jp	L22
loc_4AF7:			;l79:			; case 8
	push	iy		;	push	iy
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	de,1		;	ld	de,1
	jr	loc_4AE4	;	or	a	   <----+ Code
				;	sbc	hl,de		; is
				;	jp	nz,L50 ;r0 <----+ different
loc_4B02:			;l76:
	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	1		;	cp	1
	jr	z,loc_4B19	;	jp	z,l81
	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	2		;	cp	2
	jp	nz,loc_4A59 ;r0	;	jp	nz,L50	; r0
loc_4B19:			;l81:
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	3		;	cp	3
	jp	loc_4841	;	jp	L58	;if(nz) r0 else r1
loc_4B2A:			;l84:			; case 23
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	de,1		;	ld	de,1
loc_4B38:			;L59:
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	z,loc_4B60	;	jp	z,l86
	jp	loc_4851    ;r0	;	jp	L50	; r0
loc_4B40:			;l87:			; case 22
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	de,2		;	ld	de,2
	jr	loc_4B38	;	jp	L56
loc_4B50:			;l89:			; case 21
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	de,4		;	ld	de,4
	jr	loc_4B38	;	jp	L56
loc_4B60:			;l86:
	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	3		;	cp	3
	jp	nz,loc_4A59 ;r0	;	jp	nz,L50	; r0
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	1		;	cp	1
	jp	loc_4A15	;	jp	nz,l59	   <----+ Code is
				;	jp	L46   ; r1 <----+ different
loc_4B7D:			;l93:		      ; case 7
	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	3		;	cp	3
	jp	loc_4A35	;	jp	L57	;if(nz) r0 else r1

	psect	data

p_47b2_AA2F_sw:
S158:
	defw	loc_4A9C ;0	;	defw	l72
	defw	loc_4AB7 ;1	;	defw	l73
	defw	loc_49B3 ;2	;	defw	l47
	defw	loc_4873 ;3	;	defw	l30
	defw	loc_485F ;4	;	defw	l27
	defw	loc_482A ;5	;	defw	l19
	defw	loc_4846 ;6	;	defw	l23
	defw	loc_4B7D ;7	;	defw	l93
	defw	loc_4AF7 ;8	;	defw	l79
	defw	loc_49AA ;9	;	defw	l46
	defw	loc_4821 ;10	;	defw	l18
	defw	loc_4856 ;11	;	defw	l26
	defw	loc_47DE ;12	;	defw	l14
	defw	loc_487C ;13	;	defw	l31
	defw	loc_4887 ;14	;	defw	l34
	defw	loc_4A7B ;15	;	defw	l70
	defw	loc_49EA ;16	;	defw	l55
	defw	loc_4A5F ;17	;	defw	l68
	defw	loc_4AEC ;18	;	defw	l77
	defw	loc_4A3F ;19	;	defw	l63
	defw	loc_49CD ;20	;	defw	l50
	defw	loc_4B50 ;21	;	defw	l89
	defw	loc_4B40 ;22	;	defw	l87
	defw	loc_4B2A ;23	;	defw	l84
	defw	loc_4ADB ;24	;	defw	l74
	defw	loc_48E0 ;25	;	defw	l37
	defw	loc_4910 ;26	;	defw	l40
	defw	loc_486A ;27	;	defw	l29
	defw	loc_47E7 ;28	;	defw	l15
	defw	loc_4A29 ;29	;	defw	l61

	psect	text

; End of function sub_47B2 OK+

; End of file 47B2.as


