*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 406.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_406 OK+
;=========================================================
	global	d_6c8_A3B6

	global	_sub_406	;	global	_sub_406
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_hashtab	;	global	_hashtab
	global	_word_B017	;	global	_word_B017
	global	_array_AAE8	;	global	_array_AAE8
	global	_sub_5CF5	;	global	_sub_5CF5
	global	_nstdpth	;	global	_nstdpth
	global	wrelop		;	global	wrelop
	global	_sub_7028	;	global	_sub_7028
	global	_lvlidx		;	global	_lvlidx
	global	_array_AE57	;	global	_array_AE57
	global	_array_AEDB	;	global	_array_AEDB
	global	_sub_BEE	;	global	_sub_BEE
	global	_sub_BCC	;	global	_sub_BCC
	global	_array_AE13	;	global	_array_AE13

	psect	text

;	Disassembled version	; After compiling C source code
_sub_406:
	call 	ncsv		;	call 	ncsv
	defw 	0FFF4h		;	defw 	-12
	ld	(ix+-4),65h	;	ld	(ix+-4),101
	ld	(ix+-3),0	;	ld	(ix+-3),0
	ld	hl,_hashtab	;	ld	hl,_hashtab
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
loc_41C:			;l14:				; m1:
	ld	(ix+-6),0	;	ld	(ix+-6),0
	ld	(ix+-5),0	;	ld	(ix+-5),0
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
loc_42E:			;L7:				; m2:
	pop	iy		;	pop	iy
	jp	loc_51C		;	jp	l15
loc_433:			;l16:				; m3:
	ld	a,(iy+2)	;	ld	a,(iy+2)
	cp	39h		;	cp	57
	jp	nz, loc_4AD	;	jp	nz,l18
	ld	a, (iy+15h)	;	ld	a,(iy+21)
	cp	2		;	cp	2
	jr	nz,loc_45C	;	jp	nz,l19
	ld	de,_array_AAE8	;	ld	de,_array_AAE8
	ld	l,(iy+13h)	;	ld	l,(iy+19)
	ld	h,(iy+14h)	;	ld	h,(iy+20)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c, (hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b, (hl)		;	ld	b,(hl)
	ld	hl,(_word_B017)	;	ld	hl,(_word_B017)
	ld	a,l		;	ld	a,l
	or	c		;	or	c
	ld	l,a		;	ld	l,a
	ld	a,h		;	ld	a,h
	or	b		;	or	b
	ld	h,a		;	ld	h,a
	ld	(_word_B017),hl	;	ld	(_word_B017),hl
loc_45C:			;l19:				; m4:
	ld	a,(iy+15h)	;	ld	a,(iy+21)
	cp	4		;	cp	4
	jr	z,loc_467	;	jp	z,L5
	cp	3		;	cp	3
	jr	nz,loc_46D	;	jp	nz,l20
loc_467:			;L5:				; m5:
		  		;	ld	hl,(_empty)	    <----+ Add
		  		;	push	hl		    <----+ parameter
	push	iy		;	push	iy			  . "empty"
	call	_sub_5CF5	;	call	_sub_5CF5		  .
	pop	bc		;	pop	bc			  .
		 		;	pop	bc		    <----+
loc_46D:			;l20:				; m6:
	ld	de,(_nstdpth)	;	ld	de,(_nstdpth)
	ld	hl,0		;	ld	hl,0
	call	wrelop		;	call	wrelop
	jr	nc,loc_4AD	;	jp	nc,l18
	ld	a,(iy+15h)	;	ld	a,(iy+21)
	cp	3		;	cp	3
	jr	nz,loc_4AD	;	jp	nz,l18
	ld	l,(iy+7)	;	ld	l,(iy+7)
	ld	h,(iy+8)	;	ld	h,(iy+8)
	ld	(ix+-8),l	;	ld	(ix+-8),l
	ld	(ix+-7),h	;	ld	(ix+-7),h
	ld	l,(ix+-6)	;	ld	l,(ix+-6)
	ld	h,(ix+-5)	;	ld	h,(ix+-5)
	ld	(iy+7),l	;	ld	(iy+7),l
	ld	(iy+8),h	;	ld	(iy+8),h
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	ld	(ix+-6),l	;	ld	(ix+-6),l
	ld	(ix+-5),h	;	ld	(ix+-5),h
	dec	(iy+4)		;	dec	(iy+4)
	ld	l,(ix+-8)	;	ld	l,(ix+-8)
	ld	h,(ix+-7)	;	ld	h,(ix+-7)
	push	hl		;	push	hl
	jr	loc_42E		;	jp	L7
loc_4AD:			;l18:				; m7:
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,(iy+1)	;	ld	h,(iy+1)
	push	hl		;	push	hl
	call	_sub_7028	;	call	_sub_7028
	pop	bc		;	pop	bc
	ld	a,(iy+2)	;	ld	a,(iy+2)
	cp	38h		;	cp	56
	jr	z,loc_4C3	;	jp	z,L3
	cp	37h		;	cp	55
	jr	nz,loc_50D	;	jp	nz,l23
loc_4C3:			;L3:				; m8:
	ld	l,(iy+13h)	;	ld	l,(iy+19)
	ld	h,(iy+14h)	;	ld	h,(iy+20)
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-12),c	;	ld	(ix+-12),c
	ld	(ix+-11),b	;	ld	(ix+-11),b	;     l6 = *(sb->b_i12);
	inc	hl		;	inc	hl
	ld	(ix+-10),l	;	ld	(ix+-10),l
	ld	(ix+-9),h	;	ld	(ix+-9),h	;     l5 = sb->b_i12 + 1;
	jr	loc_4F0		;	jp	l24		;     goto m10;
loc_4DB:			;l25:				; m9:
	ld	l,(ix+-10)	;	ld	l,(ix+-10)
	ld	h,(ix+-9)	;	ld	h,(ix+-9)
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	inc	hl		;	inc	hl
	ld	(ix+-10),l	;	ld	(ix+-10),l
	ld	(ix+-9),h	;	ld	(ix+-9),h
	push	bc		;	push	bc
	call	_sub_7028	;	call	_sub_7028	;     sub_7028((l5++)->next_ptr);
	pop	bc		;	pop	bc
loc_4F0:			;l24:				; m10:
	ld	l,(ix+-12)	;	ld	l,(ix+-12)
	ld	h,(ix+-11)	;	ld	h,(ix+-11)
	dec	hl		;	dec	hl
	ld	(ix+-12),l	;	ld	(ix+-12),l
	ld	(ix+-11),h	;	ld	(ix+-11),h
	inc	hl		;	inc	hl
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	nz,loc_4DB	;	jp	nz,l25		; if(l6-- != 0) goto m9;
	ld	l,(iy+13h)	;	ld	l,(iy+19)
	ld	h,(iy+14h)	;	ld	h,(iy+20)
	push	hl		;	push	hl
	call	_sub_7028	;	call	_sub_7028	; sub_7028((struct ptr *)sb->b_i12);
	pop	bc		;	pop	bc
loc_50D:			;l23:				; m11:
	push	iy		;	push	iy
	call	_sub_7028	;	call	_sub_7028	; sub_7028((struct ptr *)sb);
	pop	bc		;	pop	bc
	ld	l,(iy+7)	;	ld	l,(iy+7)
	ld	h,(iy+8)	;	ld	h,(iy+8)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
loc_51C:			;l15:				; m12:
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	z,loc_532	;	jp	z,l17
	ld	de,(_nstdpth)	;	ld	de,(_nstdpth)
	ld	l,(iy+4)	;	ld	l,(iy+4)
	ld	h,0		;	ld	h,0
	or	a		;	or	a
	sbc	hl, de		;	sbc	hl,de
	jp	z,loc_433	;	jp	z,l16
loc_532:			;l17:				; m13:
	ld	a,(ix+-6)	;	ld	a,(ix+-6)
	or	(ix+-5)		;	or	(ix+-5)
	jr	z,loc_583	;	jp	z,l27
	ld	e,(ix+-6)	;	ld	e,(ix+-6)
	ld	d,(ix+-5)	;	ld	d,(ix+-5)
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	jr	loc_568		;	jp	l28
loc_555:			;l29:				; m14:
	ld	e,(ix+-6)	;	ld	e,(ix+-6)
	ld	d,(ix+-5)	;	ld	d,(ix+-5)
	ld	hl,7		;	ld	hl,7
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-6),c	;	ld	(ix+-6),c
	ld	(ix+-5),b	;	ld	(ix+-5),b
loc_568:			;l28:				; m15:
	ld	e,(ix+-6)	;	ld	e,(ix+-6)
	ld	d,(ix+-5)	;	ld	d,(ix+-5)
	ld	hl,7		;	ld	hl,7
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	or	(hl)		;	or	(hl)
	jr	nz,loc_555	;	jp	nz,l29
	ld	hl,7		;	ld	hl,7
	add	hl,de 		;	add	hl,de
	push	iy		;	push	iy
	pop	de		;	pop	de
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	jr	loc_599		;	jp	l12
loc_583:			;l27:				; m16:
	push	iy		;	push	iy
	pop	de		;	pop	de
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h;
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
loc_599:			;l12:				; m17:
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	dec	hl		;	dec	hl
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jp	nz,loc_41C	;	jp	nz,l14
	ld	hl,(_nstdpth)	;	ld	hl,(_nstdpth)
	dec	hl		;	dec	hl
	ld	(_nstdpth),hl	;	ld	(_nstdpth),hl
	ld	hl,(_lvlidx)	;	ld	hl,(_lvlidx)
	bit	7, h		;	bit	7,h
	jp	nz, cret	;	jp	nz,cret
	ld	de,_array_AE57	;	ld	de,_array_AE57
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	ld	de,(_nstdpth)	;	ld	de,(_nstdpth)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	nz,cret		;	jp	nz,cret
	ld	de,_array_AEDB	;	ld	de,_array_AEDB
	ld	hl,(_lvlidx)	;	ld	hl,(_lvlidx)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	pop	iy		;	pop	iy
	ld	l,(iy+0Fh)	;	ld	l,(iy+15)
	ld	h,(iy+10h)	;	ld	h,(iy+16)
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	a,(hl)		;	ld	a,(hl)
	cp	55		;	cp	55
	jr	nz,loc_601	;	jp	nz,l34
	bit	2,(iy+0Dh)	;	bit	2,(iy+13)
	jr	nz,loc_601	;	jp	nz,l34
	ld	l,(iy+9)	;	ld	l,(iy+9)
	ld	h,(iy+0Ah)	;	ld	h,(iy+10)
	push	hl		;	push	hl
	ld	l,(iy+11h)	;	ld	l,(iy+17)
	ld	h,(iy+12h)	;	ld	h,(iy+18)
	push	hl		;	push	hl
	call	_sub_BEE	;	call	_sub_BEE
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
loc_601:			;l34:				; m18:
	ld	de,_array_AE13	;	ld	de,_array_AE13
	ld	hl,(_lvlidx)	;	ld	hl,(_lvlidx)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	l,(iy+11h)	;	ld	l,(iy+17)
	ld	h,(iy+12h)	;	ld	h,(iy+18)
	push	hl		;	push	hl
	call	_sub_BCC	;	call	_sub_BCC
	ld	hl,(_lvlidx)	;	ld	hl,(_lvlidx)
	dec	hl		;	dec	hl
	ld	(_lvlidx),hl	;	ld	(_lvlidx),hl
	ld	hl,17Fh		;	ld	hl,383
	ld	(_word_B017),hl	;	ld	(_word_B017),hl
	jp	cret		;	jp	cret

; End of function sub_406 OK+

;=========================================================
; sub_627 OK++
;=========================================================
	global	_sub_627	;	global	_sub_627
	global	asll		;	global	asll
	global	__ctype_	;	global	__ctype_
	global	asll		;	global	asll
	global	aslr		;	global	aslr
	global	_sub_265	;	global	_sub_265
	global 	csv		;

	psect	text

;	Disassembled version	; After compiling C source code	
_sub_627:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	(ix+-2),0	;	ld	(ix+-2),0
	ld	(ix+-1),0	;	ld	(ix+-1),0
	inc	iy		;	inc	iy
loc_63E:			;l39:
	ld	b,2		;	ld	b,2
	push	ix		;	push	ix
	pop	hl		;	pop	hl
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	call	asll		;	call	asll
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	28h		;	cp	40
	jr	nz,loc_657	;	jp	nz,l40
	set	1,(ix+-2)	;	set	1,(ix+-2)
	inc	iy		;	inc	iy
	jr	loc_664		;	jp	l37
loc_657:			;l40:
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	2Ah		;	cp	42
	jr	nz,loc_664	;	jp	nz,l37
	set	0,(ix+-2)	;	set	0,(ix+-2)
	inc	iy		;	inc	iy
loc_664:			;l37:
	ld	a,(iy+0)	;	ld	a,(iy+0)
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	and	7		;	and	7
	or	a		;	or	a
	jr	nz,loc_67A	;	jp	nz,l38
	ld	a,e		;	ld	a,e
	cp	5Fh		;	cp	95
	jr	nz,loc_63E	;	jp	nz,l39
loc_67A:			;l38:
	ld	de,0		;	ld	de,0
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	jr	loc_6B7		;	jp	l43
loc_688:			;l44:
	ld	b,2		;	ld	b,2
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	call	asll		;	call	asll
	ld	a,(ix+-2)	;	ld	a,(ix+-2)
	and	3		;	and	3
	ld	e,a		;	ld	e,a
	xor	a		;	xor	a
	ld	d,a		;	ld	d,a
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	a,c		;	ld	a,c
	or	e		;	or	e
	ld	c,a		;	ld	c,a
	ld	a,b		;	ld	a,b
	or	d		;	or	d
	ld	b, a		;	ld	b,a
	ld	(hl),b		;	ld	(hl),b
	dec	hl		;	dec	hl
	ld	(hl),c		;	ld	(hl),c
	ld	b,2		;	ld	b,2
	push	ix		;	push	ix
	pop	hl		;	pop	hl
	dec	hl		;	dec	hl
	dec	hl 		;	dec	hl
	call	aslr		;	call	aslr
loc_6B7:			;l43:
	ld	a,(ix+-2)	;	ld	a,(ix+-2)
	or	(ix+-1)		;	or	(ix+-1)
	jr	nz,loc_688	;	jp	nz,l44
	push	iy		;	push	iy
	call	_sub_265	;	call	_sub_265
	pop	bc		;	pop	bc
	jp	cret		;	jp	cret

; End of function sub_627 OK++

;=========================================================
; sub_6C8 OK++
;=========================================================
	global	_sub_6C8	;	_sub_6C8
	global	_faterror	;	_faterror

;	Disassembled version	; After compiling C source code
_sub_6C8:
	ld	hl,d_6c8_A3B6	;	ld	hl,19f
	push	hl		;	push	hl
	call	_faterror	;	call	_faterror		
	pop	bc		;	pop	bc
	ret			;	ret				

	psect	data

;d_6c8_A3B6:
;19:	;	"Bad int. code"
;	defb	66,97,100,32,105,110,116,46,32,99,111,100,101,0

;	psect	text

; End of function sub_6C8 OK++


; End of file 406.asm


