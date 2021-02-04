*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 385B.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_385B OK++
;=========================================================
	global	_sub_385B	;	global	_sub_385B
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global 	csv		;	global 	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_385B:
	call 	csv		;	call	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(iy+21)	;	ld	l,(iy+15h)
	ld	h,(iy+22)	;	ld	h,(iy+16h)
	add	hl,hl		;	add	hl,hl
	add	hl,hl		;	add	hl,hl
	set	0,l		;	set	0,l
	ld	(iy+21),l	;	ld	(iy+15h),l
	ld	(iy+22),h	;	ld	(iy+16h),h
	jp	cret		;	jp	cret

; End of function sub_385B OK++

;=========================================================
; sub_387A OK++
;=========================================================
	global	_sub_387A	;	global	_sub_387A
	global	_sub_37ED	;	global	_sub_37ED
	global	_nodesize	;	global	_nodesize
	global 	csv		;	global 	csv

; Disassembled version		; After compiling C source code
_sub_387A:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	a,(iy+15h)	;	ld	a,(iy+21)
	or	(iy+16h)	;	or	(iy+22)
	jr	nz,loc_38AD	;	jp	nz,l14
	ld	e,(iy+17h)	;	ld	e,(iy+23)
	ld	d,(iy+18h)	;	ld	d,(iy+24)
	ld	hl,0Fh		;	ld	hl,15
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	or	(hl)		;	or	(hl)
	jr	nz,loc_38AD	;	jp	nz,l14
	ld	hl,0Dh		;	ld	hl,13
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	or	(hl)		;	or	(hl)
	jr	nz,loc_38AD	;	jp	nz,l14
	ld	hl,1		;	ld	hl,1
	jp	cret		;	jp	cret
loc_38AD:			;l14:
	push	iy		;	push	iy
	call	_sub_37ED	;	call	_sub_37ED
	pop	bc		;	pop	bc
	push	iy		;	push	iy
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	(ix+-1),l	;	ld	(ix+-1),l
	push	iy		;	push	iy
	call	_sub_385B	;	call	_sub_385B
	pop	bc		;	pop	bc
	ld	l,(ix+-1)	;	ld	l,(ix+-1)
	ld	h, 0		;	ld	h,0
	jp	cret		;	jp	cret

; End of function sub_387A OK++

;=========================================================
; sub_38CA OK++
;=========================================================
	global	_sub_38CA	;	global	_sub_38CA
	global csv		;	global 	csv

; Disassembled version		; After compiling C source code
_sub_38CA:
	call	csv		;	call 	csv
	ld	e,(ix+6)	;	ld	e,(ix+6)
	ld	d,(ix+7)	;	ld	d,(ix+7)
	ld	hl,15h		;	ld	hl,21
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	a,c		;	ld	a,c
	and	(ix+8)		;	and	(ix+8)
	ld	l,a		;	ld	l,a
	ld	a,b		;	ld	a,b
	and	(ix+9)		;	and	(ix+9)
	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	z,loc_38EE	;	jp	z,l18
loc_38E8:			;L1:
	ld	hl,1		;	ld	hl,1
	jp	cret		;	jp	cret
loc_38EE:			;l18:
	ld	e,(ix+6)	;	ld	e,(ix+6)
	ld	d,(ix+7)	;	ld	d,(ix+7)
	ld	hl,15h		;	ld	hl,21
	add	hl,de		;	add	hl,de
	ld	a, (hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	or	(hl)		;	or	(hl)
	jr	z,loc_3903	;	jp	z,l19
loc_38FD:			;L3:
	ld	hl,0		;	ld	hl,0
	jp	cret		;	jp	cret
loc_3903:			;l19:
	ld	e,(ix+6)	;	ld	e,(ix+6)
	ld	d,(ix+7)	;	ld	d,(ix+7)
	ld	hl,17h		;	ld	hl,23
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	pop	iy		;	pop	iy
loc_3913:			;l22:
	ld	a,(iy+0Dh)	;	ld	a,(iy+13)
	and	(ix+8)		;	and	(ix+8)
	ld	l,a		;	ld	l,a
	ld	a,(iy+0Eh)	;	ld	a,(iy+14)
	and	(ix+9)		;	and	(ix+9)
	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	nz,loc_38E8	;	jp	nz,L1
	ld	a,(iy+0Dh)	;	ld	a,(iy+13)
	or	(iy+0Eh)	;	or	(iy+14)
	jr	nz,loc_38FD	;	jp	nz,L3
	ld	l,(iy+0Fh)	;	ld	l,(iy+15)
	ld	h,(iy+10h)	;	ld	h,(iy+16)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	nz,loc_3913	;	jp	nz,l22
	jr	loc_38FD	;	jp	L3

; End of function sub_38CA OK++

;=========================================================
; sub_393C OK++
;=========================================================
	global	csv		;	global 	csv
	global	_sub_393C	;	global	_sub_393C

; Disassembled version		; After compiling C source code
_sub_393C:
	call 	csv		;	call	csv
	ld	hl,1		;	ld	hl,1
	push	hl		;	push	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	call	_sub_38CA	;	call	_sub_38CA
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	jp	cret		;	jp	cret

; End of function sub_393C OK++

;=========================================================
; sub_33952 OK++
;=========================================================
	global	csv		;	global 	csv
	global	_sub_3952	;	global	_sub_3952

; Disassembled version		; After compiling C source code
_sub_3952:
	call 	csv		;	call	csv
	ld	hl,2		;	ld	hl,2
	push	hl		;	push	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	call	_sub_38CA	;	call	_sub_38CA
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	jp	cret		;	jp	cret

; End of function sub_3952 OK++

;=========================================================
; sub_3968 OK++
;=========================================================
	global	_sub_3968	;	global	_sub_3968
	global	csv		;	global 	csv

; Disassembled version		; After compiling C source code
_sub_3968:
	call	csv		;	call 	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(iy+17h)	;	ld	l,(iy+23)
	ld	h,(iy+18h)	;	ld	h,(iy+24)
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	a,(hl)		;	ld	a,(hl)
	cp	37h		;	cp	55
	jr	nz,loc_398D	;	jp	nz,l28
	bit	0,(iy+15h)	;	bit	0,(iy+21)
	jr	nz,loc_398D	;	jp	nz,l28
	ld	hl,1		;	ld	hl,1
	jp	cret		;	jp	cret
loc_398D:			;l28:
	ld	hl,0		;	ld	hl,0
	jp	cret		;	jp	cret

; End of function sub_3968 OK++

;=========================================================
; nodesize OK++
;=========================================================
	global	csv		;	global 	csv
	global	_uerror		;	global	_uerror

; Disassembled version		; After compiling C source code
_nodesize:
	call	csv		;	call 	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	bit	1,(iy+15h)	;	bit	1,(iy+21)
	jr	z,loc_39AD	;	jp	z,l31
	ld	hl,19f		;	ld	hl,19f
	push	hl		;	push	hl
	call	_uerror		;	call	_uerror
	pop	bc		;	pop	bc
loc_39AD:			;l31:
	bit	0,(iy+15h)	;	bit	0,(iy+21)
	jr	z,loc_39B9	;	jp	z,l32
	ld	hl,2		;	ld	hl,2
	jp	cret		;	jp	cret
loc_39B9:			;l32:
	ld	e,(iy+17h)	;	ld	e,(iy+23)
	ld	d,(iy+18h)	;	ld	d,(iy+24)
	ld	hl,9		;	ld	hl,9
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	jp	cret		;	jp	cret

; End of function nodesize OK++

;=========================================================
; sub_39CA OK++
;=========================================================
	global	_sub_39CA	;	global	_sub_39CA
	global	_sub_36E0	;	global	_sub_36E0
	global	_sub_14F3	;	global	_sub_14F3
	global	_sprintf	;	global	_sprintf
	global	_allocmem	;	global	_allocmem
	global	_strlen		;	global	_strlen
	global	_strcpy		;	global	_strcpy
	global	_sub_174C	;	global	_sub_174C
	global	_sub_3A79	;	global	_sub_3A79

; Disassembled version		; After compiling C source code
_sub_39CA:
	call 	ncsv		;	call 	ncsv
	defw	0FFCEh		;	defw 	-34
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	push	iy		;	push	iy
	call	_sub_14F3	;	call	_sub_14F3
	pop	bc		;	pop	bc
	ld	a,l		;	ld	a,l
	cp	3		;	cp	3
	jr	nz,loc_3A5C	;	jp	nz,l34
	ld	e,(iy+19h)	;	ld	e,(iy+25)
	ld	d,(iy+1Ah)	;	ld	d,(iy+26)
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
	ld	hl,29f		;	ld	hl,29f
	push	hl		;	push	hl
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,0FFCEh	;	ld	hl,-34
	add	hl,de		;	add	hl,de
	push	hl		;	push	hl
	call	_sprintf	;	call	_sprintf
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_36E0	;	call	_sub_36E0
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,0FFCEh	;	ld	hl,-34
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
	ld	hl,0FFCEh	;	ld	hl,-34
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
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	jp	cret		;	jp	cret
loc_3A5C:			;l34:
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	push	iy		;	push	iy
	call	_sub_3A79	;	call	_sub_3A79
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	push	iy		;	push	iy
	call	_sub_36E0	;	call	_sub_36E0
	pop	bc		;	pop	bc
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	jp	cret		;	jp	cret

; End of function sub_39CA OK++

	psect	data

p_nodesize_1:
19:
	defb	99,97,110,39,116,32,116,97,107,101,32,115,105,122,101,111
	defb	102,32,102,117,110,99,0

p_39ca_1:
29:
	defb	37,108,100,46,0

	psect	text

; End of file 385B.asm


