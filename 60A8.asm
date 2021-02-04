*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 60A8.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_60A8
;
; Added the r_bc variable to preserve the logical
; behavior of the function. This function was optimized
; manually in assembly language. In places with forced 
; type casting in the original binary program image, the 
; value is returned in the HL register pair.
;
; Generated code is different, but does not affect the
; program logic. This function is boolean and only returns
; 0 or 1.
;=========================================================
	global	_sub_60A8	;	global	_sub_60A8
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_nodesize	;	global	_nodesize
	global	wrelop		;	global	wrelop
	global	_sub_14F3	;	global	_sub_14F3
	global	shll		;	global	shll
	global	arelop		;	global	arelop
	global	asaldiv		;	global	asaldiv
	global 	csv		;	global 	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_60A8:
	call	csv		;	call ncsv
	push	hl		;	defw -5
	push	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	67		;	cp	67
	jr	z,loc_60C2	;	jp	z,l12
loc_60BD:			;L3:			<--+
	ld	l,0		;	ld	l,0	   ;
	jp	cret		;	jp	cret	   ;
loc_60C2:			;l12:	   		   ;
	ld	l,(ix+8)	;	ld	l,(ix+8)   ;
	ld	h,(ix+9)	;	ld	h,(ix+9)   ;
	push	hl		;	push	hl   	   ;
	call	_nodesize	;	call	_nodesize  ;
	pop	bc		;	pop	bc   	   ;
	ld	de,4		;	ld	de,4   	   ; Return 0
	call	wrelop		;	call	wrelop     ; in a different
	jp	c,loc_60F8	;	jp	c,l18	   ; location
	bit	7,(iy+28)	;	bit	7,(iy+28)  ;
	jr	z,loc_60EC	;	jp	z,l17      ;
	ld	l,(ix+8)	;	ld	l,(ix+8)   ;
	ld	h,(ix+9)	;	ld	h,(ix+9)   ;
	push	hl		;	push	hl	   ;
	call	_sub_14F3	;	call	_sub_14F3  ;
	pop	bc		;	pop	bc	   ;
	ld	a,l		;	ld	a,l	   ;
	cp	1		;	cp	1	   ;
	jr	nz,loc_60F2 ;-+	;	jp	nz,L3	---+
loc_60EC:		      ;	;l17:
	ld	hl,1	      ;	;	ld	l,1  <--+	
	jp	cret	      ;	;	jp	cret	; Returns a 				
loc_60F2:		;<----+	;			; value	1 or 0
	ld	hl,0		;		        ; in L register
	jp	cret		;		     <--+		
loc_60F8:			;l18:				
	ld	l,(ix+8)	;	ld	l,(ix+8)	
	ld	h,(ix+9)	;	ld	h,(ix+9)	
	push	hl		;	push	hl		
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
	ld	(ix+-4),e	;	ld	(ix+-4),e	
	ld	(ix+-3),d	;	ld	(ix+-3),d	
	ld	(ix+-2),l	;	ld	(ix+-2),l	
	ld	(ix+-1),h	;	ld	(ix+-1),h	
	ld	l,(ix+8)	;	ld	l,(ix+8)	
	ld	h,(ix+9)	;	ld	h,(ix+9)	
	push	hl		;	push	hl		
	call	_sub_14F3	;	call	_sub_14F3	
	pop	bc		;	pop	bc		
	ld	a,l		;	ld	a,l		
	cp	2		;	cp	2		
	jp	nz,loc_615C	;	jp	nz,l20		
	bit	7,(iy+28)	;	bit	7,(iy+28)	
	jr	nz,loc_60BD	;	jp	nz,L3		
				;	ld	(ix+-5),1 <-+
	ld	e,(ix+-4)	;	ld	e,(ix+-4)   ;
	ld	d,(ix+-3)	;	ld	d,(ix+-3)   ;
	ld	l,(ix+-2)	;	ld	l,(ix+-2)   ;
	ld	h,(ix+-1)	;	ld	h,(ix+-1)   ;
	push	hl		;	push	hl	    ; Variable is
	push	de		;	push	de	    ; initialized
loc_6142:			;L1:			    ; above
	ld	e,(iy+25)	;	ld	e,(iy+25)   ;
	ld	d,(iy+26)	;	ld	d,(iy+26)   ;
	ld	l,(iy+27)	;	ld	l,(iy+27)   ;
	ld	h,(iy+28)	;	ld	h,(iy+28)   ;
	call	arelop		;	call	arelop	    ;
	ld	bc,1		;			----+		
	jp	m,loc_6158	;	jp	m,l24
	dec	bc		;	dec	(ix+-5)
loc_6158:			;l24:
	ld	l,c		;	ld	l,(ix+-5)
	jp	cret		;	jp	cret		
loc_615C:			;l20:				
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
	bit	7,(iy+28)	;	bit	7,(iy+28)	
				;	ld	(ix+-5),1 <-+
	ld	e,(ix+-4)	;	ld	e,(ix+-4)   ;
	ld	d,(ix+-3)	;	ld	d,(ix+-3)   ;
	ld	l,(ix+-2)	;	ld	l,(ix+-2)   ;
	ld	h,(ix+-1)	;	ld	h,(ix+-1)   ;
	push	hl		;	push	hl	    ;
	push	de		;	push	de	    ;
	jr	z,loc_6142	;	jp	z,L1	    ;
	ld	hl,0		;	ld	hl,0	    ;
	pop	bc		;	pop	bc	    ;
	or	a		;	or	a	    ; Variable is
	sbc	hl,bc		;	sbc	hl,bc	    ; initialized
	pop	bc		;	pop	bc	    ; above
	ex	de,hl		;	ex	de,hl	    ;
	ld	hl,0		;	ld	hl,0	    ;
	sbc	hl,bc		;	sbc	hl,bc	    ;
	push	hl		;	push	hl	    ;
	push	de		;	push	de	    ;
	ld	e,(iy+25)	;	ld	e,(iy+25)   ;
	ld	d,(iy+26)	;	ld	d,(iy+26)   ;
	ld	l,(iy+27)	;	ld	l,(iy+27)   ;
	ld	h,(iy+28)	;	ld	h,(iy+28)   ;
	call	arelop		;	call	arelop	    ;
	ld	bc,1		;			----+	
	jp	p,loc_6158	;	jp	p,l24		
	dec	bc		;	dec	(ix+-5)		
	jr	loc_6158	;	jp	l24		

; End of function sub_60A8

; End of file 60A8.as


