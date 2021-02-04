*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 76F.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_76F
;=========================================================
	global	_sub_76F	;	global	_sub_76F
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_getchar	;	global	_getchar
	global	__ctype_	;	global	__ctype_
	global	_sub_6C8	;	global	_sub_6C8
	global 	csv

	psect	text

;	Disassembled version	; After compiling C source code	
_sub_76F:
	call	csv		;	call csv
	push	hl		;	push hl
loc_773:			;l14:
	call	_getchar	;	call	_getchar
	ld	(ix+-1),l	;	ld	(ix+-1),l
	ld	a,l		;	ld	a,l
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de
	bit	3,(hl)		;	bit	3,(hl)
 	jr	nz,loc_773	;	jp	nz,l14
	ld	a,e		;	ld	a,e
	cp	(ix+6)		;	cp	(ix+6)
	jp	z, cret		;	jp	z,cret
	call	_sub_6C8	;	call	_sub_6C8
	jp	cret		;	jp	cret

; End of function sub_76F OK++

;=========================================================
; sub_793
;=========================================================
	global	_sub_793	;	global	_sub_793
	global	_selpsect	;	global	_selpsect
	global	_sub_2BD0	;	global	_sub_2BD0
	global	_sub_600E	;	global	_sub_600E
	global	_sub_43EF	;	global	_sub_43EF
	global	_sub_4192	;	global	_sub_4192
	global	_sub_306	;	global	_sub_306
	global	_atoi		;	global	_atoi
	global	_sub_155D	;	global	_sub_155D

;	Disassembled version	; After compiling C source code
_sub_793:
	call 	ncsv		;	call 	ncsv
	defw	0FBFEh		;	defw 	-1026
	ld	hl,3		;	ld	hl,3
	push	hl		;	push	hl
	call	_selpsect	;	call	_selpsect
	ld	hl,0		;	ld	hl,0
	ex	(sp),hl		;	ex	(sp),hl
	ld	hl,0		;	ld	hl,0
	push	hl		;	push	hl
	call	_sub_4192	;	call	_sub_4192
	push	hl		;	push	hl
	ld	hl,1Bh		;	ld	hl,27
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ex	(sp),hl		;	ex	(sp),hl
	ld	hl,1Ah		;	ld	hl,26
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_600E	;	call	_sub_600E
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_2BD0	;	call	_sub_2BD0
	pop	bc		;	pop	bc
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,0FBFEh	;	ld	hl,-1026
	add	hl,de		;	add	hl,de
	push	hl		;	push	hl
	pop	iy		;	pop	iy
loc_7D1:			;l17:
	call	_sub_306	;	call	_sub_306
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	a, (hl)		;	ld	a,(hl)
	cp	5Dh		;	cp	93
	jr	z,loc_7EB	;	jp	z,l18
	push	hl		;	push	hl
	call	_atoi		;	call	_atoi
	pop	bc		;	pop	bc
	ld	(iy+0),l	;	ld	(iy+0),l
	inc	iy		;	inc	iy
	jr	loc_7D1		;	jp	l17
loc_7EB:			;l18:
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,0FBFEh	;	ld	hl,-1026
	add	hl,de		;	add	hl,de
	ex	de,hl		;	ex	de,hl
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	push	hl		;	push	hl
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,0FBFEh	;	ld	hl,-1026
	add	hl,de		;	add	hl,de
	push	hl		;	push	hl
	call	_sub_155D	;	call	_sub_155D
	jp	cret		;	jp	cret

; End of function sub_793 OK++

; End of file 76F.as


