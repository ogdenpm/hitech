*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 283E.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_283E OK
;
; Restored source code did not allow optimizer to reduce
; number of sub_2B2A function calls to one.
;
; The switch statement, in comparison with if, more clearly
; reflects the structure of the program, however, fragments
; of the generated assembler code are arranged in an order
; different from the original.
;=========================================================
	global	_sub_283E	;	global	_sub_283E
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_array_80EF	;	global	_array_80EF
	global	amul		;	global	amul
	global	_word_B017	;	global	_word_B017
	global	__ctype_	;	global	__ctype_
	global	wrelop		;	global	wrelop
	global	_array_AB24	;	global	_array_AB24
	global	_array_AAE8	;	global	_array_AAE8
	global	_byte_AFFA	;	global	_byte_AFFA
	global	_sub_2B2A	;	global	_sub_2B2A
	global	wrelop		;	global	wrelop

	psect	text

_sub_283E:
;	Disassembled version	; After compiling C source code
	call	ncsv		;	call 	ncsv
	defw	-13		;	defw 	-13
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	push	hl		;	push	hl
	pop	de		;	pop	de
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
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
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	ld	(ix+-13),0	;	ld	(ix+-13),0
	ld	(ix+-12),0	;	ld	(ix+-12),0
	ex	de,hl		;	ex	de,hl
	ld	hl,8		;	ld	hl,8
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-2),c	;	ld	(ix+-2),c
	ld	(ix+-1),b	;	ld	(ix+-1),b
loc_2881:			;l12:				; m1:
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	a,(hl)		;	ld	a,(hl)
loc_2888:			;L5:				; m2:
	or	a		;	or	a
	jr	nz,loc_289C	;	jp	nz,l15
	ld	de,(_word_B017)	;	ld	de,(_word_B017)
	ld	a,(ix+-13)	;	ld	a,(ix+-13)
	and	e		;	and	e
	ld	l,a		;	ld	l,a
	ld	a,(ix+-12)	;	ld	a,(ix+-12)
	and	d		;	and	d
	ld	h,a		;	ld	h,a
	jp	cret		;	jp	cret
loc_289C:			;l15:				; m3:
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	(ix+-9),a	;	ld	(ix+-9),a
	cp	41h		;	cp	65 ;'A'	
	jp	z,loc_2A9C	;	jp	z,l29	
	cp	42h		;	cp	66 ;'B'	
	jp	z,loc_2A9C	;	jp	z,l29	
	cp	43h		;	cp	67 ;'C'	
	jp	z,loc_2A9C	;	jp	z,l29	
	cp	44h		;	cp	68 ;'D'	
	jr	z,loc_2881	;	jp	z,l12	
	cp	46h		;	cp	70 ;'F'	
	jp	z,loc_2A9C	;	jp	z,l29	
	cp	47h		;	cp	71 ;'G'	
	jp	z,loc_2911	;	jp	z,l39	
	cp	4Ch		;	cp	76 ;'L'	
	jp	z,loc_2AE1	;	jp	z,l60	
	cp	4Dh		;	cp	77 ;'M'	
	jp	z,loc_2A9C	;	jp	z,l29	
	cp	4Fh		;	cp	79 ;'O'	
	jp	z,loc_2A9C	;	jp	z,l29	
	cp	50h		;	cp	80 ;'P'	
	jp	z,loc_2A9C	;	jp	z,l29	
	cp	51h		;	cp	81 ;'Q'	
	jp	z,loc_2A9C	;	jp	z,l29	
	cp	52h		;	cp	82 ;'R'	
	jp	z,loc_2B22	;	jp	z,l61	
	cp	53h		;	cp	83 ;'S'	
	jp	z,loc_2A9C	;	jp	z,l29	
	cp	54h		;	cp	84 ;'T'	
	jp	z,loc_2A9C	;	jp	z,l29	
	cp	55h		;	cp	85 ;'U'	
	jr	z,loc_2881	;	jp	z,l12	
	cp	56h		;	cp	86 ;'V'	
	jp	z,loc_2A9C	;	jp	z,l29	
	cp	57h		;	cp	87 ;'W'	
	jp	z,loc_2A9C	;	jp	z,l29	
	cp	58h		;	cp	88 ;'X'	
	jr	z,loc_2911	;	jp	z,l39	
	cp	5Ah		;	cp	90 ;'Z'	
	jp	z,loc_2A9C	;	jp	z,l29	
	cp	7Eh		;	cp	126;'~'	
	jp	z,loc_2AC8	;	jp	z,l63	
	jp	loc_2881	;	jp	l12	
loc_2911:			;l39:				; m4:
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	a,(hl)		;	ld	a,(hl)
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de
	bit	2,(hl)		;	bit	2,(hl)
	jr	z,loc_2954	;	jp	z,l40
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	(ix+-8),l	;	ld	(ix+-8),l
	ld	(ix+-7),h	;	ld	(ix+-7),h
	jr	loc_293F	;	jp	l41
loc_2932:			;l42:				; m5:
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	inc	hl		;	inc	hl
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
loc_293F:			;l41:				; m6:
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	a,(hl)		;	ld	a,(hl)
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de
	bit	2,(hl)		;	bit	2,(hl)
	jr	nz,loc_2932	;	jp	nz,l42
	jr	loc_295C	;	jp	l46
loc_2954:			;l40:				; m7:
	ld	(ix+-8),0	;	ld	(ix+-8),0
	ld	(ix+-7),0	;	ld	(ix+-7),0
loc_295C:			;l46:				; m8:
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	cp	4Ch		;	cp	76
	jp	z,loc_29AF	;	jp	z,l47
	cp	4Eh		;	cp	78
	jr	z,loc_2998	;	jp	z,l49
	cp	52h		;	cp	126
	jp	z,loc_29E8	;	jp	z,l50
loc_2978:			;l45:				; m9:
	ld	a,(ix+-9)	;	ld	a,(ix+-9)
	cp	53h		;	cp	83
	jp	nz,loc_29F7	;	jp	nz,l51
	ld	l,(ix+-6)	;	ld	l,(ix+-6)
	ld	h,(ix+-5)	;	ld	h,(ix+-5)
	ld	a,(hl)		;	ld	a,(hl)
	cp	45h		;	cp	69
	jp	nz,loc_29F0	;	jp	nz,l52
	ex	de,hl		;	ex	de,hl
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	l,(hl)		;	ld	l,(hl)
	ld	(ix+-9),l	;	ld	(ix+-9),l
	jp	loc_2A63	;	jp	l54
loc_2998:			;l49:				; m10:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	(ix+-11),l	;	ld	(ix+-11),l
	ld	(ix+-10),h	;	ld	(ix+-10),h
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	ld	(ix+-6),l	;	ld	(ix+-6),l
	ld	(ix+-5),h	;	ld	(ix+-5),h
	jr	loc_2978	;	jp	l45
loc_29AF:			;l47:				; m11:
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	hl,0		;	ld	hl,0
	call	wrelop		;	call	wrelop
	jp	p,loc_29D6	;	jp	p,l48
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	ld	(ix+-6),l	;	ld	(ix+-6),l
	ld	(ix+-5),h	;	ld	(ix+-5),h
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
loc_29CD:			;L9:				; m12:
	dec	hl		;	dec	hl
	ld	(ix+-11),l	;	ld	(ix+-11),l
	ld	(ix+-10),h	;	ld	(ix+-10),h
	jr	loc_2978	;	jp	l45
loc_29D6:			;l48:				; m13:
	ld	l,(iy+19h)	;	ld	l,(iy+25)
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)
loc_29DC:			;L10:				; m14:
	ld	(ix+-6),l	;	ld	(ix+-6),l
	ld	(ix+-5),h	;	ld	(ix+-5),h
	inc	hl		;	inc	hl
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	jr	loc_29CD	;	jp	L9
loc_29E8:			;l50:				; m15:
	ld	l,(iy+1Bh)	;	ld	l,(iy+27)
	ld	h,(iy+1Ch)	;	ld	h,(iy+28)
	jr	loc_29DC	;	jp	L10
loc_29F0:			;l52:				; m16:
	ld	(ix+-9),0	;	ld	(ix+-9),0
	jp	loc_2A63	;	jp	l54
loc_29F7:			;l51:				; m17:
	ld	a,(ix+-9)	;	ld	a,(ix+-9)
	cp	47h		;	cp	71
	ld	e,(ix+-11)	;	ld	e,(ix+-11)
	ld	d,(ix+-10)	;	ld	d,(ix+-10)
	ld	l,(ix+-6)	;	ld	l,(ix+-6)
	ld	h,(ix+-5)	;	ld	h,(ix+-5)
	jr	z,loc_2A14	;	jp	z,L7
	add	hl,de		;	add	hl,de
	ld	de,9		;	ld	de,9
	add	hl,de		;	add	hl,de
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	jr	loc_2A1C	;	jp	L3
loc_2A14:			;L7:				; m18:
	add	hl,de		;	add	hl,de
	ld	de,0Fh		;	ld	de,15
	add	hl,de		;	add	hl,de
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
loc_2A1C:			;L3:				; m19:
	ld	(ix+-9),l	;	ld	(ix+-9),l
	ld	a,(ix+-8)	;	ld	a,(ix+-8)
	or	(ix+-7)		;	or	(ix+-7)
	jp	z,loc_2A63	;	jp	z,l54
	jr	loc_2A50	;	jp	l56
loc_2A2A:			;l57:				; m20:
	ld	l,(ix+-8)	;	ld	l,(ix+-8)
	ld	h,(ix+-7)	;	ld	h,(ix+-7)
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	(ix+-8),l	;	ld	(ix+-8),l
	ld	(ix+-7),h	;	ld	(ix+-7),h
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,0FFD0h	;	ld	hl,-48
	add	hl,de		;	add	hl,de
	ex	de,hl		;	ex	de,hl
	ld	l,(ix+-9)	;	ld	l,(ix+-9)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,_array_AB24	;	ld	de,_array_AB24
	add	hl,de		;	add	hl,de
	ld	l,(hl)		;	ld	l,(hl)
	ld	(ix+-9),l	;	ld	(ix+-9),l
loc_2A50:			;l56:				; m21:
	ld	l,(ix+-8)	;	ld	l,(ix+8)
	ld	h,(ix+-7)	;	ld	h,(ix+9)
	ld	a,(hl)		;	ld	a,(hl)
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	hl,__ctype_+1	;	ld	hl,__ctype_+1
	add	hl,de		;	add	hl,de
	bit	2,(hl)		;	bit	2,(hl)
	jr	nz,loc_2A2A	;	jp	nz,l57
loc_2A63:			;l54:				; m22:
	ld	de,_array_AAE8	;	ld	de,_array_AAE8
	ld	l,(ix+-9)	;	ld	l,(ix+-9)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	l,(ix+-13)	;	ld	l,(ix+-13)
	ld	h,(ix+-12)	;	ld	h,(ix+-12)
	ld	a,l		;	ld	a,l
	or	c		;	or	c
	ld	l,a		;	ld	l,a
	ld	a,h		;	ld	a,h
	or	b		;	or	b
	ld	h,a		;	ld	h,a
	ld	(ix+-13),l	;	ld	(ix+-13),l
	ld	(ix+-12),h	;	ld	(ix+-12),h
	ld	a,(ix+-9)	;	ld	a,(ix+-9)
	or	a		;	or	a
	jp	z,loc_2881	;	jp	z,l12
	ld	(_byte_AFFA),a	;	ld	(_byte_AFFA),a
	jp	loc_2881	;	jp	l12
loc_2A8F:			;l31:				; m23:
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	inc	hl		;	inc	hl
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
loc_2A9C:			;l29:				; m24:
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	a,(hl)		;	ld	a,(hl)
	or	a		;	or	a
	ld	a,(hl)		;	ld	a,(hl)
	jp	z,loc_2888	;	jp	z,L5
	cp	4Eh		;	cp	78 		; 'N'
	ld	a,(hl)		;	ld	a,(hl)
	jp	z,loc_2888	;	jp	z,L5
	cp	4Ch		;	cp	76 		; 'L'
	ld	a,(hl)		;	ld	a,(hl)
	jp	z,loc_2888	;	jp	z,L5
	cp	52h		;	cp	82 		; 'R'
	jr	nz,loc_2A8F	;	jp	nz,l31
	jp	loc_2881	;	jp	l12
loc_2ABB:			;l65:				; m25: 'R'
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	inc	hl		;	inc	hl
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
loc_2AC8:			;l63:				; m26: '~'
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ld	a,(hl)		;	ld	a,(hl)
	or	a		;	or	a
	ld	a,(hl)		;	ld	a,(hl)
	jp	z,loc_2888	;	jp	z,L5
	cp	4Ch		;	cp	76
	ld	a,(hl)		;	ld	a,(hl)
	jp	z,loc_2888	;	jp	z,L5
	cp	52h		;	cp	82
	jr	nz,loc_2ABB	;	jp	nz,l65
	jp	loc_2881	;	jp	l12		; goto m1;
loc_2AE1:			;l60:				; m27: 'L'
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	hl,0		;	ld	hl,0
	call	wrelop		;	call	wrelop
	jp	p,loc_2B15 ;--+	;	jp	p,L2	;-------+
	ld	l,(ix+8)      ;	;	ld	l,(ix+8)	;
	ld	h,(ix+9)      ;	;	ld	h,(ix+9)	;
	dec	hl	      ;	;	dec	hl		;
	push	hl	      ;	;	push	hl		;
	push	iy	      ;	;	push	iy		;
	call	_sub_283E     ;	;	call	_sub_283E	;
	pop	bc	      ;	;	pop	bc		;
	pop	bc	      ;	;	pop	bc		;
			      ;	;	jp	L1     ;----+	;
			      ;	;L2:		;<----------;---+
			      ;	;	ld	l,(iy+25)   ;
			      ;	;	ld	h,(iy+26)   ;
			      ;	;	push	hl	    ;
			      ;	;	call	_sub_2B2A   ;
			      ; ;	pop	bc	    ;
loc_2AFF:	;<---------+  ;	;L1:		       ;<---+	; m28:
	ex	de,hl	   ;  ;	;	ex	de,hl
			   ;  ; ;L8:		       ;<---+
	ld	l,(ix+-13) ;  ;	;	ld	l,(ix+-13)  ;
	ld	h,(ix+-12) ;  ;	;	ld	h,(ix+-12)  ;
	ld	a,l	   ;  ;	;	ld	a,l	    ;
	or	e	   ;  ;	;	or	e	    ;
	ld	l,a	   ;  ;	;	ld	l,a	    ;
	ld	a,h	   ;  ;	;	ld	a,h	    ;
	or	d	   ;  ;	;	or	d	    ;
	ld	h,a	   ;  ;	;	ld	h,a	    ;
	ld	(ix+-13),l ;  ;	;	ld	(ix+-13),l  ;
	ld	(ix+-12),h ;  ;	;	ld	(ix+-12),h  ;
	jp	loc_2881   ;  ;	;	jp	l12	    ;	; goto m1;
			   ;  ; ;			    ;
loc_2B15:		;<-)--+	;			    ;
	ld	l,(iy+19h) ;	;			    ;
	ld	h,(iy+1Ah) ;	;			    ;
loc_2B1B:		;<-)--+	;			    ;
	push	hl	   ;  ;	;			    ;
	call	_sub_2B2A  ;  ;	;			    ;
	pop	bc	   ;  ;	;			    ;
	jr	loc_2AFF ;-+  ;	;			    ;
			      ;	;			    ;			    ;
loc_2B22:		      ;	;l61:			    ;	; m31 'R;
	ld	l,(iy+1Bh)    ;	;	ld	l,(iy+27)   ;
	ld	h,(iy+1Ch)    ;	;	ld	h,(iy+28)   ;
	jr	loc_2B1B  ;---+	;	push	hl	    ;
				;	call	_sub_2B2A   ;
				;	pop	bc	    ;
				;	ex	de,hl	    ;
				;	jp	L8	;---+


; End of function sub_283E

; End of file 283E.as


