*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 1C6D.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_1C6D OK++
;=========================================================
	global	_sub_1C6D	;	global	_sub_1C6D
	global	ncsv,cret,indir	;	global	ncsv, cret, indir	
	global csv		;	global csv		

	psect	text

;	Disassembled version	; After compiling C source code
_sub_1C6D:
	call 	csv		;	call 	csv	
	ld	e,(ix+8)	;	ld	e,(ix+8)
	ld	d,(ix+9)	;	ld	d,(ix+9)
	ld	hl,-1		;	ld	hl,-1	
	or	a		;	or	a	
	sbc	hl,de		;	sbc	hl,de	
	push	hl		;	push	hl	
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	add	hl,de		;	add	hl,de	
	pop	de		;	pop	de	
	ld	a,l		;	ld	a,l	
	and	e		;	and	e	
	ld	l,a		;	ld	l,a	
	ld	a,h		;	ld	a,h	
	and	d		;	and	d	
	ld	h,a		;	ld	h,a	
	jp	cret		;	jp	cret	

; End of function sub_1C6D++

; End of file 1C6D.as
