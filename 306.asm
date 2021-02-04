*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 306.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_306 OK+
;=========================================================
	global	_sub_306	;	global	_sub_306
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_buffer		;	global	_buffer
	global	_getchar	;	global	_getchar
	global	__ctype_	;	global	__ctype_
	global	_lineno		;	global	_lineno
	global	_atoi		;	global	_atoi
	global	_strncpy	;	global	_strncpy
	global	_progname	;	global	_progname
	global	_putchar	;	global	_putchar
	global  csv		;	global  csv

	psect	text

;	Disassembled version	; After compiling C source code
_sub_306:
	call	csv		;	call	csv
	push	hl		;	push	hl
	push	hl		;	push	hl
	ld	(ix+-4),0	;	ld	(ix+-4),0
	ld	(ix+-3),0	;	ld	(ix+-3),0
loc_313:			;l12:
	ld	iy,_buffer	;	ld	iy,_buffer
loc_317:			;l17:
	call	_getchar	;	call	_getchar
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	de, -1		;	ld	de,-1
	or	a		;	or	a
	sbc	hl, de		;	sbc	hl,de
	jr	nz, loc_33B	;	jp	nz,l15
loc_328:			;			   <----+
	ld	de, -1		;				; Unnecessary
	ld	l, (ix+-2)	;				; comparison,
	ld	h, (ix+-1)	;				; it was performed
	or	a		;				; in the previous
	sbc	hl, de		;				; step
	jr	nz, loc_34B	;			   <----+
	ld	l,e		;	ld	l,e
	ld	h,d		;	ld	h,d
	jp	cret		;	jp	cret
loc_33B:			;l15:
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de
	bit	3,(hl)		;	bit	3,(hl)
	jr	nz,loc_317	;	jp	nz,l17
	jr	loc_328		;			   <----; Not required
loc_34B:			;
	ld	a,(ix+-2)	;	ld	a,e
	ld	(iy+0),a	;	ld	(iy+0),a
	inc	iy		;	inc	iy
loc_353:			;l21:
	call	_getchar	;	call	_getchar
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	(iy+0),l	;	ld	(iy+0),l
	inc	iy		;	inc	iy
	ld	de,-1		;	ld	de,-1
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	z,loc_377	;	jp	z,l20
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de
	bit	3,(hl)		;	bit	3,(hl)
	jr	z,loc_353	;	jp	z,l21
loc_377:			;l20:
	ld	de,-1		;	ld	de,-1
	add	iy,de		;	add	iy,de
	ld	(iy+0),0	;	ld	(iy+0),0
	ld	a,(_buffer)	;	ld	a,(_buffer)
	cp	34		;	cp	34
	jr	nz,loc_3AD	;	jp	nz,l23
	ld	hl,_buffer+1	;	ld	hl,_buffer+1
	push	hl		;	push	hl
	call	_atoi		;	call	_atoi
	pop	bc		;	pop	bc
	ld	(_lineno),hl	;	ld	(_lineno),hl
	ld	de,10		;	ld	de,10
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	ld	hl,1		;
	jr	nz,loc_3A4	;	jp	nz,L4
				;	ld	hl,0   <----+ Could not find operators
	dec	hl		;	jp	L3	    ; in C language generating
				;	L4:		    ; code that exactly matches
				;	ld	hl,1   <----+ binary codes
loc_3A4:			;L3:		
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	jp	loc_313		;	jp	l12
loc_3AD:			;l23:
	ld	a,(ix+-4)	;	ld	a,(ix+-4)
	or	(ix+-3)		;	or	(ix+-3)
	jr	z,loc_3D2	;	jp	z,l24
	ld	hl,39		;	ld	hl,39
	push	hl		;	push	hl
	ld	hl,_buffer	;	ld	hl,_buffer
	push	hl		;	push	hl
	ld	hl,_progname	;	ld	hl,_progname
	push	hl		;	push	hl
	call	_strncpy	;	call	_strncpy
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(ix+-4),0	;	ld	(ix+-4),0
	ld	(ix+-3),0	;	ld	(ix+-3),0
	jp	loc_313		;	jp	l12
loc_3D2:			;l24:
	ld	a,(_buffer)	;	ld	a,(_buffer)
	cp	59		;	cp	59
	jr	nz,loc_400	;	jp	nz,L1
	ld	hl,_buffer+1	;	ld	hl,_buffer+1
	ld	a,(hl)		;	ld	a,(hl)
	cp	59		;	cp	59
	jr	nz,loc_400	;	jp	z,l28
				;L1:
				;	ld	hl,_buffer
				;	jp	cret
loc_3E1:			;l28:
	call	_getchar	;	call	_getchar
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	push	hl		;	push	hl
	call	_putchar	;	call	_putchar
	pop	bc		;	pop	bc
	ld	de,10		;	ld	de,10
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_3E1	;	jp	nz,l28
	jp	loc_313		;	jp	l12
loc_400:			;
	ld	hl,_buffer	;
	jp	cret		;

; End of function sub_306 OK+

; End of file 306.asm



