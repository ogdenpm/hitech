	global	_main
	global	ncsv, cret, indir
	global	_beg_sbrk
	global	_sbrk
	global	_bflag
	global	_eflag
	global	_hflag
	global	_pflag
	global	_rflag
	global	_wflag
	global	_faterror
	global	wrelop
	global	_freopen
	global	__iob
	global	_sub_1680
	global	_sub_6D1
	global	_fclose
	global	_uerror
	global	_exit
	global	_errcnt
	global	csv

	psect	text

_main:
	call	csv
	ld	hl,0
	push	hl
	call	_sbrk
	pop	bc
	ld	(_beg_sbrk),hl
	ld	l,(ix+6)
	ld	h,(ix+7)
	dec	hl
	ld	(ix+6),l
	ld	(ix+7),h
	ld	l,(ix+8)
	ld	h,(ix+9)
	inc	hl
	inc	hl
	ld	(ix+8),l
	ld	(ix+9),h
	jr	l3
l4:
	ld	l,(ix+8)
	ld	h,(ix+9)
	ld	a,(hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	inc	hl
	ld	a,(hl)		; switch(argv[0][1])
	cp	66		; case 'B'
	jp	z,l8	
	cp	69		; case 'E'
	jp	z,l9	
	cp	72		; case 'H'
	jp	z,l10	
	cp	80		; case 'P'
	jr	z,l12	
	cp	82		; case 'R'
	jr	z,l13	
	cp	87		; case 'W'
	jr	z,l15	
	cp	112		; case 'p'
	jr	z,l12	
	cp	119		; case 'w'
	jr	z,l15	

	ld	l,(ix+8)	; default:
	ld	h,(ix+9)
	ld	a,(hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	inc	hl
	ld	a,(hl)
	ld	l,a

	rla
	sbc	a,a
	ld	h,a

	push	hl
	ld	hl,19f
	push	hl
	call	_faterror
	pop	bc
	pop	bc
l6:
	ld	l,(ix+8)
	ld	h,(ix+9)
	inc	hl
	inc	hl
	ld	(ix+8),l
	ld	(ix+9),h		; argv++;
	ld	l,(ix+6)
	ld	h,(ix+7)
	dec	hl
	ld	(ix+6),l
	ld	(ix+7),h		; argc—;
l3:
	ld	e,(ix+6)
	ld	d,(ix+7)
	ld	hl,0
	call	wrelop
	jp	m,L4
	jr	l5
l12:
	ld	a,1
	ld	(_pflag),a
	jr	l6
l15:
	ld	a,1
	ld	(_wflag),a
	jr	l6
l13:
	ld	a,1
	ld	(_rflag),a
	jr	l6
l8:
	ld	a,1
	ld	(_bflag),a
	jr	l6
l9:
	ld	a,1
	ld	(_eflag),a
	jr	l6
l10:
	ld	a,1
	ld	(_hflag),a
	jr	l6
L4:
	ld	l,(ix+8)
	ld	h,(ix+9)
	ld	a,(hl)
	inc	hl
	ld	h,(hl)
	ld	l,a
	ld	a,(hl)
	cp	'-'
	jp	z,l4	; **argv == '-' == 0
l5:
	ld	e,(ix+6)
	ld	d,(ix+7)
	dec	de
	ld	(ix+6),e
	ld	(ix+7),d
	inc	de
	ld	hl,0
	call	wrelop
	jp	p,l17

	ld	hl,__iob
	push	hl
	ld	hl,29f
	push	hl
	ld	l,(ix+8)
	ld	h,(ix+9)
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	call	_freopen
	pop	bc
	pop	bc
	pop	bc
	ld	a,l
	or	h
	jr	nz,l18

	ld	l,(ix+8)
	ld	h,(ix+9)
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	ld	hl,39f
	push	hl
	call	_faterror
	pop	bc
	pop	bc
	jr	l17
l18:
	ld	e,(ix+6)
	ld	d,(ix+7)
	ld	hl,0
	call	wrelop
	jp	p,l17

	ld	hl,__iob+8
	push	hl
	ld	hl,49f
	push	hl
	ld	l,(ix+8)
	ld	h,(ix+9)
	inc	hl
	inc	hl
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	call	_freopen
	pop	bc
	pop	bc
	pop	bc
	ld	a,l
	or	h
	jr	nz,l17

	ld	l,(ix+8)
	ld	h,(ix+9)
	inc	hl
	inc	hl
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	ld	hl,59f
	push	hl
	call	_faterror
	pop	bc
	pop	bc
l17:
	call	_sub_1680
	call	_sub_6D1
	ld	hl,__iob+8
	push	hl
	call	_fclose
	pop	bc
	ld	de,-1
	or	a
	sbc	hl,de
	jr	nz,l22

	ld	hl,69f
	push	hl
	call	_uerror
	pop	bc
l22:
	ld	hl,(_errcnt)
	ld	a,l
	or	h
	ld	hl,1
	jr	nz,L1
	dec	hl
L1:
	push	hl
	call	_exit
	jp	cret

	psect	data

d_main_AB9C:
19:	defb	73,108,108,101,103,97,108,9,115,119,105,116,99,104,32,37
	defb	99,0
d_main_ABAE:
29:	defb	114,0
d_main_ABB0:
39:	defb	67,97,110,39,116,32,111,112,101,110,32,37,115,0
d_main_ABBE:
49:	defb	119,0
d_main_ABC0:
59:	defb	67,97,110,39,116,32,99,114,101,97,116,101,32,37,115,0
d_main_ABD0:
69:	defb	69,114,114,111,114,32,99,108,111,115,105,110,103,32,111,117
	defb	116,112,117,116,32,102,105,108,101,0

	psect	text

