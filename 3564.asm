*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 3564.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_3564 OK++
;=========================================================
	global	_sub_3564	;	global	_sub_3564
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_word_AFF8	;	global	_word_AFF8
	global	_array_80EF	;	global	_array_80EF
	global	amul		;	global	amul
	global	_sub_2D09	;	global	_sub_2D09
	global	_putchar	;	global	_putchar
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_3564:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	hl,0		;	ld	hl,0
	ld	(_word_AFF8),hl	;	ld	(_word_AFF8),hl
	ld	(ix+-1),l	;	ld	(ix+-1),l
	jp	loc_35D5	;	jp	l12
loc_357E:			;l13:
	push	iy		;	push	iy
	pop	de		;	pop	de
	ld	a,(ix+-1)	;	ld	a,(ix+-1)
	ld	l,a		;	ld	l,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	add	hl,de		;	add	hl,de
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	ld	de,0Ah		;	ld	de,10
	call	amul		;	call	amul
	ld	de,_array_80EF	;	ld	de,_array_80EF
	add	hl,de		;	add	hl,de
	ex	de,hl		;	ex	de,hl
	push	ix		;	push	ix
	pop	hl		;	pop	hl
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	hl,6		;	ld	hl,6
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	or	(hl)		;	or	(hl)
	jp	z,loc_35D2	;	jp	z,l15
	ld	a,(ix+-1)	;	ld	a,(ix+-1)
	ld	l,a		;	ld	l,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	push	hl		;	push	hl
	ld	e,(ix+-3)	;	ld	e,(ix+-3)
	ld	d,(ix+-2)	;	ld	d,(ix+-2)
	ld	hl,6		;	ld	hl,6
	add	hl, de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	push	iy		;	push	iy
	call	_sub_2D09	;	call	_sub_2D09
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	hl,0Ah		;	ld	hl,10
	ex	(sp),hl		;	ex	(sp),hl	
	call	_putchar	;	call	_putchar
	pop	bc		;	pop	bc
loc_35D2:			;l15:
	inc	(ix+-1)		;	inc	(ix+-1)
loc_35D5:			;l12:
	ld	e,(iy+1)	;	ld	e,(iy+1)
	ld	d,0		;	ld	d,0
	ld	l, (ix+-1)	;	ld	l,(ix+-1)
	ld	h,d		;	ld	h,d
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_357E	;	jp	nz,l13
	jp	cret		;	jp	cret

; End of function sub_3564 OK++

;=========================================================
; sub_35E6 OK+
;
; The absence command "ld h,0" should not affect execution
; program, since functions sub_143F and sub_1489 expect a
; parameter type uchar (1 byte), which is transmitted in
; register "l".
; Maybe this is the correct compiler response to  restored
; source.
;=========================================================
	global	_sub_35E6		;global	_sub_35E6
	global	_dopetab		;global	_dopetab
	global	_word_AFFB		;global	_word_AFFB
	global	_sub_143F		;global	_sub_143F
	global	_sub_1489		;global	_sub_1489
	global 	csv			;

; Disassembled version		; After compiling C source code
_sub_35E6:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	de,_dopetab	;	ld	de,_dopetab
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	bit	1,b		;	bit	1,b
	jr	z,loc_360B	;	jp	z,l17
	ld	hl,(_word_AFFB)	;	ld	hl,(_word_AFFB)
	inc	hl		;	inc	hl
	ld	(_word_AFFB),hl	;	ld	(_word_AFFB),hl
loc_360B:			;l17:
	ld	de,_dopetab	;	ld	de,_dopetab
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	a,c		;	ld	a,c
	and	0Ch		;	and	12
	ld	l,a		;	ld	l,a
	xor	a		;	xor	a
	ld	h,a		;	ld	h,a
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	de,8		;	ld	de,8
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	nz,loc_3685	;	jp	nz,l18
	bit	0,(iy+2)	;	bit	0,(iy+2)
	jp	z,loc_364F	;	jp	z,l19
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_35E6	;	call	_sub_35E6
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_35E6	;	call	_sub_35E6
	pop	bc		;	pop	bc
	jp	loc_3685	;	jp	l18
loc_364F:			;l19:
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	call	_sub_35E6	;	call	_sub_35E6
	pop	bc		;	pop	bc
	bit	1,(iy+2)	;	bit	1,(iy+2)
	jp	z,loc_367A	;	jp	z,l21
	ld	e,(iy+1Bh)	;	ld	e,(iy+27)
	ld	d,(iy+1Ch)	;	ld	d,(iy+28)
	ld	l,e		;	ld	l,e
	ld	h,d		;	ld	h,d
	inc	hl		;	inc	hl
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	add	hl,de		;	add	hl,de
	ld	de,0Eh		;	ld	de,14
	add	hl,de		;	add	hl,de
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;			<-- difference in code
	push	hl		;	push	hl
	call	_sub_143F	;	call	_sub_143F
	pop	bc		;	pop	bc
loc_367A:			;l21:
	ld	l,(iy+19h)	;	ld	l,(iy+27)
	ld	h,(iy+1Ah)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	call	_sub_35E6	;	call	_sub_35E6
	pop	bc		;	pop	bc
loc_3685:			;l18:
	ld	de,4		;	ld	de,4
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_369E	;	jp	nz,l22
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_35E6	;	call	_sub_35E6
	pop	bc		;	pop	bc
loc_369E:			;l22:
	bit	1,(iy+2)	;	bit	1,(iy+2)
	jp	z,loc_36BE	;	jp	z,l23
	ld	e,(iy+1Bh)	;	ld	e,(iy+27)
	ld	d,(iy+1Ch)	;	ld	d,(iy+28)
	ld	l,e		;	ld	l,e
	ld	h,d		;	ld	h,d
	inc	hl		;	inc	hl
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	add	hl,de		;	add	hl,de
	ld	de,0Eh		;	ld	de,14
	add	hl,de		;	add	hl,de
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;			<-- difference in code
	push	hl		;	push	hl
	call	_sub_1489	;	call	_sub_1489
	pop	bc		;	pop	bc
loc_36BE:			;l23:
	push	iy		;	push	iy
	call	_sub_3564	;	call	_sub_3564
	pop	bc		;	pop	bc
	ld	de,_dopetab	;	ld	de,_dopetab
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	bit	1,b		;	bit	1,b
	jp	z,cret		;	jp	z,cret
	ld	hl,(_word_AFFB)	;	ld	hl,(_word_AFFB)
	dec	hl		;	dec	hl
	ld	(_word_AFFB),hl	;	ld	(_word_AFFB),hl
	jp	cret		;	jp	cret
				
			
; End of function sub_35E6 OK+ 	

;=========================================================
; sub_36E0 OK++
;=========================================================
	global	_sub_36E0	;	global	_sub_36E0
	global	_byte_B013	;	global	_byte_B013
	global	_sub_7028	;	global	_sub_7028
	global	_word_B011	;	global	_word_B011
	global 	csv		;	global 	csv

; Disassembled version		; After compiling C source code
_sub_36E0:
	call	csv		;	call 	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	a,1		;	ld	a,1
	ld	(_byte_B013),a	;	ld	(_byte_B013),a
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	44h		;	cp	68
	jr	nz,loc_3702	;	jp	nz,l26
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_7028	;	call	_sub_7028
loc_3702:			;l26:
	ld	hl,(_word_B011)	;	ld	hl,(_word_B011)
	ld	(iy+17h),l	;	ld	(iy+23),l
	ld	(iy+18h),h	;	ld	(iy+24),h
	ld	(_word_B011),iy	;	ld	(_word_B011),iy
	jp	cret		;	jp	cret

; Endof function sub_36E0 OK++

;=========================================================
; sub_3712 OK++
;=========================================================
	global	_sub_3712	;	global	_sub_3712
	global	_blkclr		;	global	_blkclr
	global	_allocmem	;	global	_allocmem
	global	csv		;	global	csv

; Disassembled version		; After compiling C source code
_sub_3712:
	call	csv		;	call 	csv
	ld	a,1		;	ld	a,1
	ld	(_byte_B013),a	;	ld	(_byte_B013),a
	ld	hl,(_word_B011)	;	ld	hl,(_word_B011)
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	z,loc_373B	;	jp	z,l28
	ld	iy,(_word_B011)	;	ld	iy,(_word_B011)
	ld	l,(iy+17h)	;	ld	l,(iy+23)
	ld	h,(iy+18h)	;	ld	h,(iy+24)
	ld	(_word_B011),hl	;	ld	(_word_B011),hl
	ld	hl,1Dh		;	ld	hl,29
	push	hl		;	push	hl
	push	iy		;	push	iy
	call	_blkclr		;	call	_blkclr
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	jr	loc_3746	;	jp	l29
loc_373B:			;l28:
	ld	hl,1Dh		;	ld	hl,29
	push	hl		;	push	hl
	call	_allocmem	;	call	_allocmem
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
loc_3746:			;l29:
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	jp	cret		;	jp	cret

; End of function sub_3712 OK++

;=========================================================
; sub_3712 OK++
;=========================================================
	global	_sub_374C	;	global	_sub_374C
	global	csv		;	global	csv

; Disassembled version		; After compiling C source code	
_sub_374C:
	call	csv		;	call 	csv
	ld	hl,(_word_B011)	;	ld	hl,(_word_B011)
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	nz,loc_376A	;	jp	nz,l32
	ld	l,0		;	ld	l,0
	jp	cret		;	jp	cret
loc_375B:			;l33:
	ld	l,(iy+17h)	;	ld	l,(iy+23)
	ld	h,(iy+18h)	;	ld	h,(iy+24)
	ld	(_word_B011),hl	;	ld	(_word_B011),hl
	push	iy		;	push	iy
	call	_sub_7028	;	call	_sub_7028
	pop	bc		;	pop	bc
loc_376A:			;l32:
	ld	iy,(_word_B011)	;	ld	iy,(_word_B011)
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	nz,loc_375B	;	jp	nz,l33
	ld	l,1		;	ld	l,1
	jp	cret		;	jp	cret

; End of function sub_374C OK++

;=========================================================
; sub_377A OK++
;=========================================================
	global	_sub_377A	;	global	_sub_377A
	global	csv		;	global	csv

; Disassembled version		; After compiling C source code	
_sub_377A:
	call	csv		;	call 	csv
	call	_sub_3712	;	call	_sub_3712
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	iy		;	push	iy
	pop	de		;	pop	de
	push	hl		;	push	hl
	ld	bc,1Dh		;	ld	bc,29
	ldir			;	ldir
	pop	hl		;	pop	hl
	ld	de,_dopetab	;	ld	de,_dopetab
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	a,c		;	ld	a,c
	and	0Ch		;	and	12
	ld	l,a		;	ld	l,a
	xor	a		;	xor	a
	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	z,loc_37BB	;	jp	z,l36
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
	push	hl		;	push	hl
	call	_sub_377A	;	call	_sub_377A
	pop	bc		;	pop	bc
	ld	(iy+19h),l	;	ld	(iy+25),l
	ld	(iy+1Ah),h	;	ld	(iy+26),h
loc_37BB:			;l36:
	ld	de,_dopetab	;	ld	de,_dopetab
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	a,c		;	ld	a,c
	and	0Ch		;	and	12
	ld	l,a		;	ld	l,a
	xor	a		;	xor	a
	ld	h,a		;	ld	h,a
	ld	de,8		;	ld	de,8
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_37E7	;	jp	nz,l37
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	push	hl		;	push	hl
	call	_sub_377A	;	call	_sub_377A
	pop	bc		;	pop	bc
	ld	(iy+1Bh),l	;	ld	(iy+27),l
	ld	(iy+1Ch),h	;	ld	(iy+28),h
loc_37E7:			;l37:
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	jp	cret		;	jp	cret

; End of function sub_377A OK++

; End of file 3564.asm

