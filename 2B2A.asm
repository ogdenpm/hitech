*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 2B2A.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_2B2A OK+
;
; Generated code has insignificant differences. Source code
; was probably compiled by a previous version of compiler.
;=========================================================
	global	_sub_2B2A	;	global	_sub_2B2A
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_dopetab	;	global	_dopetab
	global	_sub_283E	;	global	_sub_283E
	global 	csv		;	global 	csv

	psect	text

; Disassembled version		; After compiling C source code	
_sub_2B2A:
	call	csv		;	call 	csv		
	ld	l,(ix+6)	;	ld	l,(ix+6)	
	ld	h,(ix+7)	;	ld	h,(ix+7)	
	push	hl		;	push	hl		
	pop	iy		;	pop	iy		
	ld	a,(iy+1)	;	ld	a,(iy+1)	
	or	a		;	or	a		
	jr	nz,loc_2B67	;	jp	nz,l12		
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
	jr	nz,loc_2B59	;	jp	nz,l13		
	ld	hl,0		;	ld	hl,0		
	jp	cret		;	jp	cret		
loc_2B59:			;l13:				
	ld	l,(iy+19h)	;	ld	l,(iy+25)	
	ld	h,(iy+1Ah)	;	ld	h,(iy+26)	
	push	hl		;	push	hl		
	call	_sub_2B2A	;	call	_sub_2B2A	
loc_2B63:			;L1:				
	pop	bc		;	pop	bc		
	jp	cret		;	jp	cret		
loc_2B67:			;l12:				
	ld	e,(iy+1) 	;			   <----+ Compiler generates    
	ld	d,0		;	ld	l,(iy+1)	; correct code, but 
	ld	hl,-1		;	ld	h,0		; different from
	add	hl,de		;	dec	hl	   <----+ original
	push	hl		;	push	hl		
	push	iy		;	push	iy		
	call	_sub_283E	;	call	_sub_283E	
	pop	bc		;	pop	bc		
	jr	loc_2B63	;	jp	L1		


; End of function sub_2B2A OK+

; End of file 2B2A.as




