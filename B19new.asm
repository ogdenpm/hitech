*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - B19new.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_B19 OK++
;=========================================================
	global	_sub_B19	;	global	_sub_B19
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_sub_265	;	global	_sub_265
	global	_sub_306	;	global	_sub_306
	global	_selpsect	;	global	_selpsect
	global	_sub_CAB	;	global	_sub_CAB
	global	_sub_808	;	global	_sub_808
	global	_sub_4192	;	global	_sub_4192
	global	adiv		;	global	adiv
	global	_sub_1C8E	;	global	_sub_1C8E
	global	_sub_76F	;	global	_sub_76F
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_B19:
	call	csv		;	call	csv
	push	hl		;	push	hl
	push	hl		;	push	hl
	call	_sub_306	;	call	_sub_306
	push	hl		;	push	hl
	call	_sub_265	;	call	_sub_265
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	hl,3		;	ld	hl,3
	ex	(sp),hl		;	ex	(sp),hl
	call	_selpsect	;	call	_selpsect
	pop	bc		;	pop	bc
	push	iy		;	push	iy
	call	_sub_CAB	;	call	_sub_CAB
	pop	bc		;	pop	bc
	call	_sub_4192	;	call	_sub_4192
	push	hl		;	push	hl
	push	iy		;	push	iy
	call	_sub_808	;	call	_sub_808
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	a,(iy+13)	;	ld	a,(iy+13)
	or	(iy+14)		;	or	(iy+14)
	jr	nz,loc_B5F	;	jp	nz,L2
	ld	e,(iy+15)	;	ld	e,(iy+15)
	ld	d,(iy+16)	;	ld	d,(iy+16)
	ld	hl,9		;	ld	hl,9
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	jr	loc_B62		;	jp	L1
loc_B5F:			;L2:
	ld	hl,2		;	ld	hl,2
loc_B62:			;L1:
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	ld	a,(iy+11)	;	ld	a,(iy+11)
	or	(iy+12)		;	or	(iy+12)
	jr	nz,loc_B8C	;	jp	nz,l12
	ex	de,hl		;	ex	de,hl
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	call	adiv		;	call	adiv
	ld	(iy+11),l	;	ld	(iy+11),l
	ld	(iy+12),h	;	ld	(iy+12),h
	push	iy		;	push	iy
	call	_sub_1C8E	;	call	_sub_1C8E
	pop	bc		;	pop	bc
	ld	(iy+9),l	;	ld	(iy+9),l
	ld	(iy+10),h	;	ld	(iy+10),h
loc_B8C:			;l12:
	ld	hl,93		;	ld	hl,93
	push	hl		;	push	hl
	call	_sub_76F	;	call	_sub_76F
	jp	cret		;	jp	cret

;=========================================================
; sub_B96 OK++
;=========================================================
	global	_sub_B96	;	global	_sub_B96
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	_selpsect	;	global	_selpsect
	global	_byte_AE0C	;	global	_byte_AE0C
	global	_printf		;	global	_printf
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_B96:
	call	csv		;	call	csv
	ld	hl,2		;	ld	hl,2
	push	hl		;	push	hl
	call	_selpsect	;	call	_selpsect
	pop	bc		;	pop	bc
	ld	a,(_byte_AE0C)	;	ld	a,(_byte_AE0C)
	or	a		;	or	a
	jr	nz,loc_BAF	;	jp	nz,l14
	ld	hl,b96_A61A	;	ld	hl,19f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
loc_BAF:			;l14:
	ld	hl,b96_A550	;	ld	hl,29f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	ld	a,1		;	ld	a,1
	ld	(_byte_AE0C),a	;	ld	(_byte_AE0C),a
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	ex	(sp),hl		;	ex	(sp),hl
	ld	hl,b96_A546	;	ld	hl,39f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	jp	cret		;	jp	cret

	psect	data

b96_A546:
	;"defw\tf%d\n"
defb	100,101,102,119,9,102,37,100,10,0

b96_A550:
	;"call\tncsv\n"
defb	99,97,108,108,9,110,99,115,118,10,0


bcc_A55B:
	; "jp\tcret\nf%d\tequ\t%d\n"
	defb	106,112,9,99,114,101,116,10,102,37,100,9,101,113,117,9
	defb	37,100,10,0

bee_A56F:
	; "ld\tde,k%d\nld\tbc,%d\nldir\nld\thl,k%d\n"
	defb	108,100,9,100,101,44,107,37,100,10,108,100,9,98,99,44
	defb	37,100,10,108,100,105,114,10,108,100,9,104,108,44,107,37
	defb	100,10,0

_off_A592:
F567:
	defw	19f
	defw	29f
	defw	39f
	defw	49f

e43_5_A59A:
e43_5:
	;	"ld\ta,%u\ncp\th\njp\tc,l%d\njp\tnz,1f\n" 
	;	"ld\ta,%u\ncp\tl\njp\tc,l%d\n1:add\thl,hl\n"
	;	"ld\tde,S%u\nadd\thl,de\nld\ta,(hl)\n"
	;	"inc\thl\nld\th,(hl)\nld\tl,a\njp\t(hl)\n"
	defb	108,100,9,97,44,37,117,10,99,112,9,104,10,106,112,9
	defb	99,44,108,37,100,10,106,112,9,110,122,44,49,102,10,108
	defb	100,9,97,44,37,117,10,99,112,9,108,10,106,112,9,99
	defb	44,108,37,100,10,49,58,97,100,100,9,104,108,44,104,108
	defb	10,108,100,9,100,101,44,83,37,117,10,97,100,100,9,104
	defb	108,44,100,101,10,108,100,9,97,44,40,104,108,41,10,105
	defb	110,99,9,104,108,10,108,100,9,104,44,40,104,108,41,10
	defb	108,100,9,108,44,97,10,106,112,9,40,104,108,41,10,0

b96_A61A:
	 ;	"global\tncsv, cret, indir\n"
	defb	103,108,111,98,97,108,9,110,99,115,118,44,32,99,114,101
	defb	116,44,32,105,110,100,105,114,10,0


bee_A634:
	; "k%d:defs\t%d\n"
	defb	107,37,100,58,100,101,102,115,9,37,100,10,0


c36_1:
	;	"global\t%s\n"
	defb	103,108,111,98,97,108,9,37,115,10,0


c57_1:
	;	"\tdefs\t%u\n"
	defb	9,100,101,102,115,9,37,117,10,0


cab_1:
	;	"%s:\n"
	defb	37,115,58,10,0


cdf_1:
	;	"defb\t0"
	defb	100,101,102,98,9,48,0

cdf_2:
	;	",0"
	defb	44,48,0

_off_A592_0:
19:	;	""
	defb	0

_off_A592_1:
29:	;	"bss"
	defb	98,115,115,0

_off_A592_2:
39:	;	"text"
	defb	116,101,120,116,0

_off_A592_3:
49:	;	"data"
	defb	100,97,116,97,0

selpsect_1:
	;	"psect\t%s\n"
	defb	112,115,101,99,116,9,37,115,10,0

d66_1:
	;	"Duplicate case label"
	defb	68,117,112,108,105,99,97,116,101,32,99,97,115,101,32,108
	defb	97,98,101,108,0

e43_3:
	;	"Non-constant case label"
	defb	78,111,110,45,99,111,110,115,116,97,110,116,32,99,97,115
	defb	101,32,108,97,98,101,108,0

e43_1:
	;	"No case\tlabels"
	defb	78,111,32,99,97,115,101,9,108,97,98,101,108,115,0

e43_2:
	;	"jp\tl%d\n"
	defb	106,112,9,108,37,100,10,0
e43_4:
	;	"us"
	defb	117,115,0

e43_6:
	;	"S%d:\n"
	defb	83,37,100,58,10,0

e43_7:
	;	"defw\tl%d\n"
	defb	100,101,102,119,9,108,37,100,10,0

e43_8:
	;	"defw\tl%d\n"
	defb	100,101,102,119,9,108,37,100,10,0

e43_9:
	;	"1:\n"
	defb	49,58,10,0

e43_10:
	;	"ld\ta,h\n"
	defb	108,100,9,97,44,104,10,0

e43_11:
	;	"jp\tnz,1f\nld\ta,l\n"
	defb	106,112,9,110,122,44,49,102,10,108,100,9,97,44,108,10
	defb	0

e43_12:
	;	"1:\n"
	defb	49,58,10,0

e43_13:
	;	"ld\ta,l\n"
	defb	108,100,9,97,44,108,10,0

e43_14:
	;	"jp\tnz,1f\nld\ta,h\n"
	defb	106,112,9,110,122,44,49,102,10,108,100,9,97,44,104,10
	defb	0

e43_15:
	;	"jp\tz,l%d\n"
	defb	106,112,9,122,44,108,37,100,10,0

e43_16:
	;	"1:\n"
	defb	49,58,10,0

e43_17:
	;	"jp\tl%d\n"
	defb	106,112,9,108,37,100,10,0

e43_18:
	;	"jp\tz,l%d\n"
	defb	106,112,9,122,44,108,37,100,10,0

e43_19:
	;	"jp\tl%d\n"
	defb	106,112,9,108,37,100,10,0

p_1420_1:
	;	"cp\t%d\n"
	defb	99,112,9,37,100,10,0

p_1420_2:
	;	"or\ta\n"
	defb	111,114,9,97,10,0

p_143f_1:
;		"push\thl\npush\tde\n"
	defb	112,117,115,104,9, 104,108,10,112,117,115,104,9,100,101,10
	defb	0

p_143f_2:
	;	"push\t%s\n"
	defb	112,117,115,104,9,37,115,10,0


p_1489_1:
	;	"pop\tde\npop\thl\n"
	defb	112,111,112,9,100,101,10,112,111,112,9,104,108,10,0

p_1489_2:
	;	"pop\t%s\n"
	defb	112,111,112,9,37,115,10,0

p_14d3_1:
	;	"ld\tl,(ix+%d)\nld\th,(ix+%d)\npush\thl\npop\tiy\n"
	defb	108,100,9,108,44,40,105,120,43,37,100,41,10,108,100,9
	defb	104,44,40,105,120,43,37,100,41,10,112,117,115,104,9,104
	defb	108,10,112,111,112,9,105,121,10,0

p_155d_1:
	;	"defb\t"
	defb	100,101,102,98,9,0

p_155d_2:
	;	"%d"
	defb	37,100,0

p_15d3_1:
	;	"j%d:\n"
	defb	106,37,100,58,10,0

p_15e7_1:
	;	"jp\tj%d\n"
	defb	106,112,9,106,37,100,10,0

	psect	text

;=========================================================
; sub_BCC OK++
;=========================================================
	global	_sub_BCC	;	global	_sub_BCC	
	global	ncsv,cret,indir	;	global	ncsv,cret,indir	
	global	_selpsect	;	global	_selpsect	
	global	_printf		;	global	_printf		
	global 	csv		;	global 	csv		

	psect	text

; Disassembled version		; After compiling C source code
_sub_BCC:
	call	csv		;	call	csv
	ld	hl,2		;	ld	hl,2
	push	hl		;	push	hl
	call	_selpsect	;	call	_selpsect
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	ld	hl,bcc_A55B	;	ld	hl,49f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	jp	cret		;	jp	cret

;=========================================================
; sub_BEE OK++
;=========================================================
	global	_sub_BEE	;	global	_sub_BEE
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	_selpsect	;	global	_selpsect
	global	_printf		;	global	_printf
	global 	csv		;	global 	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_BEE:
	call	csv		;	call	csv
	ld	hl,2		;	ld	hl,2
	push	hl		;	push	hl
	call	_selpsect	;	call	_selpsect
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	push	hl		;	push	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	ld	hl,bee_A56F	;	ld	hl,59f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	hl,1		;	ld	hl,1
	ex	(sp),hl		;	ex	(sp),hl
	call	_selpsect	;	call	_selpsect
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	ld	hl,bee_A634	;	ld	hl,69f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	jp	cret		;	jp	cret

;=========================================================
; sub_C36 OK++
;=========================================================
	global	_sub_C36	;	global	_sub_C36
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	_printf		;	global	_printf
	global 	csv		;	global 	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_C36:
	call	csv		;	call	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,(iy+1)	;	ld	h,(iy+1)
	push	hl		;	push	hl
	ld	hl,c36_1	;	ld	hl,79f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	set	1,(iy+3)	;	set	1,(iy+3)
	jp	cret		;	jp	cret

;=========================================================
; sub_C57 OK++
;=========================================================
	global	_sub_C57	;	global	_sub_C57
	global	ncsv,cret,indir	;	global	ncsv,cret,ind
	global	_selpsect	;	global	_selpsect
	global	_sub_C36	;	global	_sub_C36
	global	_sub_CAB	;	global	_sub_CAB
	global	_printf		;	global	_printf
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_C57:
	call	csv		;	call	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	bit	0,(iy+3)	;	bit	0,(iy+3)
	jp	nz,cret		;	jp	nz,cret
	ld	a,(iy+11)	;	ld	a,(iy+11)
	or	(iy+12)		;	or	(iy+12)
	jp	z,cret		;	jp	z,cret
	bit	1,(iy+13)	;	bit	1,(iy+13)
	jp	nz,cret		;	jp	nz,cret
	ld	hl,1		;	ld	hl,1
	push	hl		;	push	hl
	call	_selpsect	;	call	_selpsect
	pop	bc		;	pop	bc
	ld	a,(iy+21)	;	ld	a,(iy+21)
	cp	3		;	cp	3
	jr	nz,loc_C95	;	jp	nz,l22
	bit	1,(iy+3)	;	bit	1,(iy+3)
	push	iy		;	push	iy
	jr	nz,loc_C97	;	jp	nz,L3
	call	_sub_C36	;	call	_sub_C36
	pop	bc		;	pop	bc
loc_C95:			;l22:
	push	iy		;	push	iy
loc_C97:			;L3:
	call	_sub_CAB	;	call	_sub_CAB
	ld	l,(iy+9)	;	ld	l,(iy+9)
	ld	h,(iy+10)	;	ld	h,(iy+10)
	ex	(sp),hl		;	ex	(sp),hl
	ld	hl,c57_1	;	ld	hl,89f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	jp	cret		;	jp	cret

;=========================================================
; sub_CAB OK++
;=========================================================
	global	_sub_CAB	;	global	_sub_CAB
	global	ncsv,cret,indir	;	global	ncsv,cret,indi
	global	_sub_C36	;	global	_sub_C36
	global	_printf		;	global	_printf
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_CAB:
	call	csv		;	call	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	bit	1,(iy+3)	;	bit	1,(iy+3)
	jr	nz,loc_CCA	;	jp	nz,l25
	ld	a,(iy+21)	;	ld	a,(iy+21)
	cp	3		;	cp	3
	jr	nz,loc_CCA	;	jp	nz,l25
	push	iy		;	push	iy
	call	_sub_C36	;	call	_sub_C36
	pop	bc		;	pop	bc
loc_CCA:			;l25:
	set	0,(iy+3)	;	set	0,(iy+3)
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,(iy+1)	;	ld	h,(iy+1)
	push	hl		;	push	hl
	ld	hl,cab_1	;	ld	hl,99f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	jp	cret		;	jp	cret

;=========================================================
; sub_CDF OK++
;=========================================================
	global	_sub_CDF	;	global	_sub_CDF
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	_printf		;	global	_printf
	global	_putchar	;	global	_putchar
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_CDF:
	call	csv		;	call	csv
	push	hl		;	push	hl
	ld	(ix+-1),0	;	ld	(ix+-1),0
	jr	loc_D14		;	jp	l28
loc_CE9:			;L4:
	or	a		;	or	a
	jr	nz,loc_CF6	;	jp	nz,l31
	ld	hl,cdf_1	;	ld	hl,109f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	jr	loc_CFE		;	jp	l32
loc_CF6:			;l31:
	ld	hl,cdf_2	;	ld	hl,119f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
loc_CFE:			;l32:
	inc	(ix+-1)		;	inc	(ix+-1)
	ld	a,(ix+-1)	;	ld	a,(ix+-1)
	cp	16		;	cp	16
	jr	nz,loc_D14	;	jp	nz,l28
	ld	(ix+-1),0	;	ld	(ix+-1),0
	ld	hl,10		;	ld	hl,10
	push	hl		;	push	hl
	call	_putchar	;	call	_putchar
	pop	bc		;	pop	bc
loc_D14:			;l28:
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	dec	hl		;	dec	hl
	ld	(ix+6),l	;	ld	(ix+6),l
	ld	(ix+7),h	;	ld	(ix+7),h
	inc	hl		;	inc	hl
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	ld	a,(ix+-1)	;	ld	a,(ix+-1)
	jr	nz,loc_CE9	;	jp	nz,L4
	or	a		;	or	a
	jp	z,cret		;	jp	z,cret
	ld	hl,10		;	ld	hl,10
	push	hl		;	push	hl
	call	_putchar	;	call	_putchar
	jp	cret		;	jp	cret


;=========================================================
; SELPSECT OK++
;=========================================================
	global	_selpsect	;	global	_selpsect
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	csv		;	global	csv
	global	_cursect	;	global	_cursect
	global	_printf		;	global	_printf

	psect	text

; Disassembled version		; After compiling C source code
_selpsect:
	call	csv		;	call	csv
	ld	de,(_cursect)	;	ld	de,(_cursect)
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jp	z,cret		;	jp	z,cret
	ld	de,F567 	;	ld	de,F587		; _off_A592
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	ld	(_cursect),hl	;	ld	(_cursect),hl
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	hl,selpsect_1	;	ld	hl,169f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	jp	cret		;	jp	cret

;=========================================================
; sub_D66 OK+
;
; Generated code from the C source is completely identical,
; except for useless code in binary image located after
; L2++ operator, which does not affect function.
;=========================================================
	global	_sub_D66	;	global	_sub_D66
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	wrelop		;	global	wrelop
	global	_uerror		;	global	_uerror

	psect	text

; Disassembled version		; After compiling C source code
_sub_D66:			;
	call	ncsv		;	call	ncsv
	defw	-9		;	defw	-9
loc_D6B:			;l40:
	ld	(ix+-1),0	;	ld	(ix+-1),0
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	ld	(ix+-3),l	;	ld	(ix+-3),l
	ld	(ix+-2),h	;	ld	(ix+-2),h
	ld	l,(ix+10)	;	ld	l,(ix+10)
	ld	h,(ix+11)	;	ld	h,(ix+11)
	ld	(ix+-5),l	;	ld	(ix+-5),l
	ld	(ix+-4),h	;	ld	(ix+-4),h
	jr	loc_E07		;	jp	l41
loc_D92:			;l42:
	ld	e,(iy+0)	;	ld	e,(iy+0)
	ld	d,(iy+1)	;	ld	d,(iy+1)
	ld	l,(iy+2)	;	ld	l,(iy+2)
	ld	h,(iy+3)	;	ld	h,(iy+3)
	call	wrelop		;	call	wrelop
	jp	p,loc_E27	;	jp	p,l45
	ld	(ix+-1),1	;	ld	(ix+-1),1
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,(iy+1)	;	ld	h,(iy+1)
	ld	(ix+-7),l	;	ld	(ix+-7),l
	ld	(ix+-6),h	;	ld	(ix+-6),h
	ld	l,(iy+2)	;	ld	l,(iy+2)
	ld	h,(iy+3)	;	ld	h,(iy+3)
	ld	(iy+0),l	;	ld	(iy+0),l
	ld	(iy+1),h	;	ld	(iy+1),h
	ld	l,(ix+-7)	;	ld	l,(ix+-7)
	ld	h,(ix+-6)	;	ld	h,(ix+-6)
	ld	(iy+2),l	;	ld	(iy+2),l
	ld	(iy+3),h	;	ld	(iy+3),h
	ld	l,(ix+-3)	;	ld	l,(ix+-3)
	ld	h,(ix+-2)	;	ld	h,(ix+-2)
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-9),c	;	ld	(ix+-9),c
	ld	(ix+-8),b	;	ld	(ix+-8),b
	inc	hl		;	inc	hl
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	dec	hl		;	dec	hl
	ld	(hl),c		;	ld	(hl),c
	inc	hl		;	inc	hl
	ld	(hl),b		;	ld	(hl),b
	ld	e,(ix+-9)	;	ld	e,(ix+-9)
	ld	d,(ix+-8)	;	ld	d,(ix+-8)
	inc	hl		;	inc	hl
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
loc_DEF:			;l46:
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(ix+-3)	;	ld	l,(ix+-3)
	ld	h,(ix+-2)	;	ld	h,(ix+-2)
	inc	hl		;	inc	hl
	inc	hl		;	inc	hl
	ld	(ix+-3),l	;	ld	(ix+-3),l
	ld	(ix+-2),h	;	ld	(ix+-2),h	Warning!
	dec	hl		;			   <----+ Useless code,
	dec	hl		;			   <----+ since
loc_E07:			;l41:				.
	ld	e,(ix+-5)	;	ld	e,(ix+-5)	.
	ld	d,(ix+-4)	;	ld	d,(ix+-4)	.
	dec	de		;	dec	de		.
	ld	(ix+-5),e	;	ld	(ix+-5),e	.
	ld	(ix+-4),d	;	ld	(ix+-4),d	. register pair HL
	ld	hl,0		;	ld	hl,0	   <----+ is assigned 0
	call	wrelop		;	call	wrelop	
	jp	m,loc_D92	;	jp	m,l42	
	ld	a,(ix+-1)	;	ld	a,(ix+-1)
	or	a		;	or	a
	jp	nz,loc_D6B	;	jp	nz,l40
	jp	cret		;	jp	cret
loc_E27:			;l45:
	ld	e,(iy+2)	;	ld	e,(iy+2)
	ld	d,(iy+3)	;	ld	d,(iy+3)
	ld	l,(iy+0)	;	ld	l,(iy+0)
	ld	h,(iy+1)	;	ld	h,(iy+1)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_DEF	;	jp	nz,l46
	ld	hl,d66_1	;	ld	hl,179f
	push	hl		;	push	hl
	call	_uerror		;	call	_uerror
	pop	bc		;	pop	bc
	jp	cret		;	jp	cret

;=========================================================
; sub_E43 OK++
;=========================================================
	global	_sub_E43	;	global	_sub_E43
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	_sub_4192	;	global	_sub_4192
	global	_sub_600E	;	global	_sub_600E
	global	_atoi		;	global	_atoi
	global	_sub_306	;	global	_sub_306
	global	_sub_36E0	;	global	_sub_36E0
	global	_sub_76F	;	global	_sub_76F
	global	_warning	;	global	_warning
	global	_sub_475C	;	global	_sub_475C
	global	_printf		;	global	_printf
	global	_uerror		;	global	_uerror
	global	_sub_D66	;	global	_sub_D66
	global	wrelop		;	global	wrelop
	global	amul		;	global	amul
	global	wrelop		;	global	wrelop
	global	_sub_3712	;	global	_sub_3712
	global	_sub_43EF	;	global	_sub_43EF
	global	_sub_415E	;	global	_sub_415E
	global	_nodesize	;	global	_nodesize
	global	_sub_265	;	global	_sub_265
	global	_selpsect	;	global	_selpsect
	global	_sub_3DC9	;	global	_sub_3DC9
	global	_sub_174C	;	global	_sub_174C
	global	_sub_1420	;	global	_sub_1420
	global	shar		;	global	shar
	global	asar		;	global	asar

	psect	text

;	Disassembled version	; After compiling C source code
_sub_E43:
	call	ncsv		;	call	ncsv
	defw	-1038		;	defw	-1038
	call	_sub_4192	;	call	_sub_4192
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	(ix+-10),0	;	ld	(ix+-8),0
	ld	(ix+-9),0	;	ld	(ix+-7),0
loc_E59:			;l49:
	call	_sub_4192	;	call	_sub_4192
	push	hl		;	push	hl
	call	_sub_600E	;	call	_sub_600E
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	call	_sub_306	;	call	_sub_306
	push	hl		;	push	hl
	call	_atoi		;	call	_atoi
	pop	bc		;	pop	bc
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	23		;	cp	23
	jr	nz,loc_EB9	;	jp	nz,l52
	ld	(ix+-12),l	;	ld	(ix+-12),l
	ld	(ix+-11),h	;	ld	(ix+-11),h
	push	iy		;	push	iy
	call	_sub_36E0	;	call	_sub_36E0
	ld	hl,93		;	ld	hl,93
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_76F	;	call	_sub_76F
	pop	bc		;	pop	bc
	ld	a,(ix+-10)	;	ld	a,(ix+-8)
	or	(ix+-9)		;	or	(ix+-7)
	jp	nz,loc_F0B	;	jp	nz,l50
	ld	hl,e43_1	;	ld	hl,189f
	push	hl		;	push	hl
	call	_warning	;	call	_warning
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_475C	;	call	_sub_475C
	ld	l,(ix+-12)	;	ld	l,(ix+-12)
	ld	h,(ix+-11)	;	ld	h,(ix+-11)
	ex	(sp),hl		;	ex	(sp),hl
	ld	hl,e43_2	;	ld	hl,199f
loc_EB0:			;L6:
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	jp	cret		;	jp	cret
loc_EB9:			;l52:
	ld	a,(iy+0)	;	ld	a,(iy+0)
	cp	67		;	cp	67
	jr	nz,loc_EFA	;	jp	nz,l54
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-10)	;	ld	l,(ix+-8)
	ld	h,(ix+-9)	;	ld	h,(ix+-7)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-528		;	ld	de,-528
	add	hl,de		;	add	hl,de
	ld	e,(iy+25)	;	ld	e,(iy+25)
	ld	d,(iy+26)	;	ld	d,(iy+26)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-10)	;	ld	l,(ix+-8)
	ld	h,(ix+-9)	;	ld	h,(ix+-7)
	inc	hl		;	inc	hl
	ld	(ix+-10),l	;	ld	(ix+-8),l
	ld	(ix+-9),h	;	ld	(ix+-7),h
	dec	hl		;	dec	hl
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-1038	;	ld	de,-1038
	add	hl,de		;	add	hl,de
	ld	e,(ix+-4)	;	ld	e,(ix+-4)
	ld	d,(ix+-3)	;	ld	d,(ix+-3)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	jr	loc_F02		;	jp	l55
loc_EFA:			;l54:
	ld	hl,e43_3	;	ld	hl,209f
	push	hl		;	push	hl
	call	_uerror		;	call	_uerror
	pop	bc		;	pop	bc
loc_F02:			;l55:
	push	iy		;	push	iy
	call	_sub_475C	;	call	_sub_475C
	pop	bc		;	pop	bc
	jp	loc_E59		;	jp	l49
loc_F0B:			;l50:
	ld	l,(ix+-10)	;	ld	l,(ix+-8)
	ld	h,(ix+-9)	;	ld	h,(ix+-7)
	push	hl		;	push	hl
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,-1038	;	ld	hl,-1038
	add	hl,de		;	add	hl,de
	push	hl		;	push	hl
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,-528		;	ld	hl,-528
	add	hl,de		;	add	hl,de
	push	hl		;	push	hl
	call	_sub_D66	;	call	_sub_D66
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,-528		;	ld	hl,-528
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-10)	;	ld	l,(ix+-8)
	ld	h,(ix+-9)	;	ld	h,(ix+-7)
	dec	hl		;	dec	hl
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-528		;	ld	de,-528
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	or	a		;	or	a
	sbc	hl,bc		;	sbc	hl,bc
	ld	(ix+-8),l	;	ld	(ix+-6),l
	ld	(ix+-7),h	;	ld	(ix+-5),h
	bit	7,(ix+-7)	;	bit	7,(ix+-5)
	jp	nz,loc_111F	;	jp	nz,l56
	ld	de,16000	;	ld	de,16000
	call	wrelop		;	call	wrelop
	jp	p,loc_111F	;	jp	p,l56
	ld	de,5		;	ld	de,5
	ld	l,(ix+-10)	;	ld	l,(ix+-8)
	ld	h,(ix+-9)	;	ld	h,(ix+-7)
	call	amul		;	call	amul
	push	hl		;	push	hl
	ld	de,20		;	ld	de,20
	ld	l,(ix+-8)	;	ld	l,(ix+-10)
	ld	h,(ix+-7)	;	ld	h,(ix+-9)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	pop	de		;	pop	de
	call	wrelop		;	call	wrelop
	jp	p,loc_111F	;	jp	p,l56
	call	_sub_3712	;	call	_sub_3712
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	(iy+0),65	;	ld	(iy+0),65
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,23		;	ld	hl,23
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+23),c	;	ld	(iy+23),c
	ld	(iy+24),b	;	ld	(iy+24),b
	ld	hl,21		;	ld	hl,21
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+21),c	;	ld	(iy+21),c
	ld	(iy+22),b	;	ld	(iy+22),b
	push	iy		;	push	iy
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,-528		;	ld	hl,-528
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	ld	a,d		;	ld	a,d
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	l,a		;	ld	l,a
	ld	h,a		;	ld	h,a
	push	hl		;	push	hl
	push	de		;	push	de
	call	_sub_415E	;	call	_sub_415E
	pop	bc		;	pop	bc
	ex	(sp),hl		;	ex	(sp),hl
	ld	hl,20		;	ld	hl,20
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	ld	hl,18		;	ld	hl,18
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ex	(sp),hl		;	ex	(sp),hl
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	de,2		;	ld	de,2
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	z,loc_1025	;	jp	z,l59
	call	_sub_3712	;	call	_sub_3712
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	(hl),65		;	ld	(hl),65
	ld	hl,e43_4	;	ld	hl,219f
	push	hl		;	push	hl
	call	_sub_265	;	call	_sub_265
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,23		;	ld	hl,23
	add	hl,de		;	add	hl,de
	pop	de		;	pop	de
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	push	iy		;	push	iy
	ld	hl,20		;	ld	hl,20
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
loc_1025:			;l59:
	ld	hl,2		;	ld	hl,2
	push	hl		;	push	hl
	call	_selpsect	;	call	_selpsect
	ld	hl,0		;	ld	hl,0
	ex	(sp),hl		;	ex	(sp),hl
	push	iy		;	push	iy
	ld	hl,11		;	ld	hl,11
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_3DC9	;	call	_sub_3DC9
	pop	bc		;	pop	bc
	call	_sub_174C	;	call	_sub_174C
	ld	(ix+-6),l	;	ld	(ix+-6),l
	ld	(ix+-5),h	;	ld	(ix+-5),h
	push	hl		;	push	hl
	ld	l,(ix+-12)	;	ld	l,(ix+-12)
	ld	h,(ix+-11)	;	ld	h,(ix+-11)
	push	hl		;	push	hl
	ld	l,(ix+-8)	;	ld	l,(ix+-10)
	xor	a		;	xor	a
	ld	h,a		;	ld	h,a
	push	hl		;	push	hl
	ld	l,(ix+-12)	;	ld	l,(ix+-12)
	ld	h,(ix+-11)	;	ld	h,(ix+-11)
	push	hl		;	push	hl
	ld	b,8		;	ld	b,8
	ld	l,(ix+-8)	;	ld	l,(ix+-10)
	ld	h,(ix+-7)	;	ld	h,(ix+-9)
	call	shar		;	call	shar
	push	hl		;	push	hl
	ld	hl,e43_5	;	ld	hl,229f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	ld	hl,12		;	ld	hl,12
	add	hl,sp		;	add	hl,sp
	ld	sp,hl		;	ld	sp,hl
	ld	hl,3		;	ld	hl,3
	push	hl		;	push	hl
	call	_selpsect	;	call	_selpsect
	ld	l,(ix+-6)	;	ld	l,(ix+-6)
	ld	h,(ix+-5)	;	ld	h,(ix+-5)
	ex	(sp),hl		;	ex	(sp),hl
	ld	hl,e43_6	;	ld	hl,239f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(ix+-4),0	;	ld	(ix+-4),0
	ld	(ix+-3),0	;	ld	(ix+-3),0
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	hl,-528		;	ld	hl,-528
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-8),c	;	ld	(ix+-10),c
	ld	(ix+-7),b	;	ld	(ix+-9),b
loc_10A5:			;l62:
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-528		;	ld	de,-528
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	ld	l,(ix+-8)	;	ld	l,(ix+-10)
	ld	h,(ix+-7)	;	ld	h,(ix+-9)
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_10ED	;	jp	nz,l63
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-1038	;	ld	de,-1038
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	hl,e43_7	;	ld	hl,249f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	inc	hl		;	inc	hl
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	jr	loc_10FD	;	jp	l64
loc_10ED:			;l63:
	ld	l,(ix+-12)	;	ld	l,(ix+-12)
	ld	h,(ix+-11)	;	ld	h,(ix+-11)
	push	hl		;	push	hl
	ld	hl,e43_8	;	ld	hl,259f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
loc_10FD:			;l64:
	ld	l,(ix+-8)	;	ld	l,(ix+-10)
	ld	h,(ix+-7)	;	ld	h,(ix+-9)
	inc	hl		;	inc	hl
	ld	(ix+-8),l	;	ld	(ix+-10),l
	ld	(ix+-7),h	;	ld	(ix+-9),h
	ld	e,(ix+-10)	;	ld	e,(ix+-8)
	ld	d,(ix+-9)	;	ld	d,(ix+-7)
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	call	wrelop		;	call	wrelop
	jp	m,loc_10A5	;	jp	m,l62
	jp	cret		;	jp	cret
loc_111F:			;l56:
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	call	_nodesize	;	call	_nodesize
	pop	bc		;	pop	bc
	ld	de,2		;	ld	de,2
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	ld	l,e		;	ld	l,e
	ld	h,d		;	ld	h,d
	push	hl		;	push	hl
	jp	nz,loc_135E	;	jp	nz,L5
	call	_selpsect	;	call	_selpsect
	ld	hl,0		;	ld	hl,0
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	ld	hl,11		;	ld	hl,11
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_3DC9	;	call	_sub_3DC9
	pop	bc		;	pop	bc
	ld	(ix+-14),255	;	ld	(ix+-14),255
	ld	(ix+-13),255	;	ld	(ix+-13),255
	ld	a,0		;	ld	a,0
	ld	(ix+-18),a	;	ld	(ix+-17),a
	ld	(ix+-17),a	;	ld	(ix+-18),a
	ld	l,a		;	ld	l,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	ld	(ix+-16),l	;	ld	(ix+-16),l
	ld	(ix+-15),h	;	ld	(ix+-15),h
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	jp	loc_131F	;	jp	l66
loc_1175:			;l67:
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-528		;	ld	de,-528
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	l,(ix+-14)	;	ld	l,(ix+-14)
	ld	h,(ix+-13)	;	ld	h,(ix+-13)
	ld	a,l		;	ld	a,l
	and	c		;	and	c
	ld	l,a		;	ld	l,a
	ld	a,h		;	ld	a,h
	and	b		;	and	b
	ld	h,a		;	ld	h,a
	ld	(ix+-14),l	;	ld	(ix+-14),l
	ld	(ix+-13),h	;	ld	(ix+-13),h
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-528		;	ld	de,-528
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	l,(ix+-16)	;	ld	l,(ix+-16)
	ld	h,(ix+-15)	;	ld	h,(ix+-15)
	ld	a,l		;	ld	a,l
	or	c		;	or	c
	ld	l,a		;	ld	l,a
	ld	a,h		;	ld	a,h
	or	b		;	or	b
	ld	h,a		;	ld	h,a
	ld	(ix+-16),l	;	ld	(ix+-16),l
	ld	(ix+-15),h	;	ld	(ix+-15),h
	ld	b,8		;	ld	b,8
	call	shar		;	call	shar
	ex	de,hl		;	ex	de,hl
	ld	b,8		;	ld	b,8
	ld	l,(ix+-14)	;	ld	l,(ix+-14)
	ld	h,(ix+-13)	;	ld	h,(ix+-13)
	call	shar		;	call	shar
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	z,loc_1226	;	jp	z,l69
	ld	e,(ix+-16)	;	ld	e,(ix+-16)
	xor	a		;	xor	a
	ld	d,a		;	ld	d,a
	ld	l,(ix+-14)	;	ld	l,(ix+-14)
	ld	h,a		;	ld	h,a
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	z,loc_1226	;	jp	z,l69
	ld	a,(ix+-17)	;	ld	a,(ix+-18)
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	a,(ix+-18)	;	ld	a,(ix+-17)
	ld	l,a		;	ld	l,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l
	or	e		;	or	e
	ld	l,a		;	ld	l,a
	ld	a,h		;	ld	a,h
	or	d		;	or	d
	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	z,loc_1201	;	jp	z,l71
	ld	hl,e43_9	;	ld	hl,269f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
loc_1201:			;l71:
	xor	a		;	xor	a
	ld	(ix+-18),a	;		ld	(ix+-17),a
	ld	(ix+-17),a	;ld	(ix+-18),a
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-528		;	ld	de,-528
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(ix+-16),c	;	ld	(ix+-16),c
	ld	(ix+-15),b	;	ld	(ix+-15),b
	ld	(ix+-14),c	;	ld	(ix+-14),c
	ld	(ix+-13),b	;	ld	(ix+-13),b
loc_1226:			;l69:
	ld	b,8		;	ld	b,8
	ld	l,(ix+-16)	;	ld	l,(ix+-16)
	ld	h,(ix+-15)	;	ld	h,(ix+-15)
	call	shar		;	call	shar
	ex	de,hl		;	ex	de,hl
	ld	b,8		;	ld	b,8
	ld	l,(ix+-14)	;	ld	l,(ix+-14)
	ld	h,(ix+-13)	;	ld	h,(ix+-13)
	call	shar		;	call	shar
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_1284	;	jp	nz,l72
	ld	a,(ix+-18)	;	ld	a,(ix+-17)
	or	a		;	or	a
	jr	nz,loc_126B	;	jp	nz,l73
	ld	hl,e43_10	;	ld	hl,279f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	ld	b,8		;	ld	b,8
	ld	l,(ix+-14)	;	ld	l,(ix+-14)
	ld	h,(ix+-13)	;	ld	h,(ix+-13)
	call	shar		;	call	shar
	push	hl		;	push	hl
	call	_sub_1420	;	call	_sub_1420
	ld	hl,e43_11	;	ld	hl,289f
	ex	(sp),hl		;	ex	(sp),hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	ld	(ix+-18),1	;	ld	(ix+-17),1
loc_126B:			;l73:
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-528		;	ld	de,-528
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	xor	a		;	xor	a
	ld	b,a		;	ld	b,a
	ld	(hl),b		;	ld	(hl),b
	dec	hl		;	dec	hl
	ld	(hl),c		;	ld	(hl),c
	jr	loc_12DF	;	jp	l74
loc_1284:			;l72:
	ld	a,(ix+-17)	;	ld	a,(ix+-18)
	or	a		;	or	a
	jr	nz,loc_12B4	;	jp	nz,l75
	ld	a,(ix+-18)	;	ld	a,(ix+-17)
	or	a		;	or	a
	jr	z,loc_1298	;	jp	z,l76
	ld	hl,e43_12	;	ld	hl,299f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
loc_1298:			;l76:
	ld	hl,e43_13	;	ld	hl,309f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	ld	l,(ix+-14)	;	ld	l,(ix+-14)
	xor	a		;	xor	a
	ld	h,a		;	ld	h,a
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_1420	;	call	_sub_1420
	ld	hl,e43_14	;	ld	hl,319f
	ex	(sp),hl		;	ex	(sp),hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	ld	(ix+-17),1	;	ld	(ix+-18),1
loc_12B4:			;l75:
	ld	b,8		;	ld	b,8
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-528		;	ld	de,-528
	add	hl,de		;	add	hl,de
	call	asar		;	call	asar
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-528		;	ld	de,-528
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	xor	a		;	xor	a
	ld	b,a		;	ld	b,a
	ld	(hl),b		;	ld	(hl),b
	dec	hl		;	dec	hl
	ld	(hl),c		;	ld	(hl),c
loc_12DF:			;l74:
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-528		;	ld	de,-528
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	call	_sub_1420	;	call	_sub_1420
	pop	bc		;	pop	bc
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-1038	;	ld	de,-1038
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	hl,e43_15	;	ld	hl,329f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	inc	hl		;	inc	hl
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
loc_131F:			;l66:
	ld	e,(ix+-10)	;	ld	e,(ix+-8)
	ld	d,(ix+-9)	;	ld	d,(ix+-7)
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	call	wrelop		;	call	wrelop
	jp	m,loc_1175	;	jp	m,l67
	ld	a,(ix+-17)	;	ld	a,(ix+-18)
	ld	e,a		;	ld	e,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	d,a		;	ld	d,a
	ld	a,(ix+-18)	;	ld	a,(ix+-17)
	ld	l,a		;	ld	l,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l
	or	e		;	or	e
	ld	l,a		;	ld	l,a
	ld	a,h		;	ld	a,h
	or	d		;	or	d
	ld	h,a		;	ld	h,a
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	jr	z,loc_1351	;	jp	z,l77
	ld	hl,e43_16	;	ld	hl,339f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
loc_1351:			;l77:
	ld	l,(ix+-12)	;	ld	l,(ix+-12)
	ld	h,(ix+-11)	;	ld	h,(ix+-11)
	push	hl		;	push	hl
	ld	hl,e43_17	;	ld	hl,349f
	jp	loc_EB0		;	jp	L6
loc_135E:			;L5:
	call	_selpsect	;	call	_selpsect
	ld	hl,0		;	ld	hl,0
	ex	(sp),hl		;	ex	(sp),hl
	ld	l,(ix+-2)	;	ld	l,(ix+-2)
	ld	h,(ix+-1)	;	ld	h,(ix+-1)
	push	hl		;	push	hl
	ld	hl,70		;	ld	hl,70
	push	hl		;	push	hl
	call	_sub_43EF	;	call	_sub_43EF
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_3DC9	;	call	_sub_3DC9
	pop	bc		;	pop	bc
	ld	(ix+-4),0	;	ld	(ix+-4),0
	ld	(ix+-3),0	;	ld	(ix+-3),0
	jp	loc_13FD	;	jp	l78
loc_1385:			;l79:
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-528		;	ld	de,-528
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	ld	de,256		;	ld	de,256
	call	wrelop		;	call	wrelop
	jp	p,loc_13F0	;	jp	p,l81
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-528		;	ld	de,-528
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	ld	h,(hl)		;	ld	h,(hl)
	ld	l,a		;	ld	l,a
	ld	de,-128		;	ld	de,-128
	call	wrelop		;	call	wrelop
	jp	m,loc_13F0	;	jp	m,l81
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-528		;	ld	de,-528
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	call	_sub_1420	;	call	_sub_1420
	pop	bc		;	pop	bc
	push	ix		;	push	ix
	pop	de		;	pop	de
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,-1038	;	ld	de,-1038
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	hl,e43_18	;	ld	hl,359f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
loc_13F0:			;l81:
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	inc	hl		;	inc	hl
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
loc_13FD:			;l78:
	ld	e,(ix+-10)	;	ld	e,(ix+-8)
	ld	d,(ix+-9)	;	ld	d,(ix+-7)
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	call	wrelop		;	call	wrelop
	jp	m,loc_1385	;	jp	m,l79
	ld	l,(ix+-12)	;	ld	l,(ix+-12)
	ld	h,(ix+-11)	;	ld	h,(ix+-11)
	push	hl		;	push	hl
	ld	hl,e43_19	;	ld	hl,369f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	jp	cret		;	jp	cret

;=========================================================
; sub_1420 OK++
;=========================================================
	global	_sub_1420	;	global	_sub_1420
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	_printf		;	global	_printf
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code_
_sub_1420:
	call	csv		;	call	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	ld	a,l		;	ld	a,l
	or	(ix+7)		;	or	(ix+7)
	jr	nz,loc_1435	;	jp	nz,L8
	ld	hl,p_1420_2	;	ld	hl,389f
	jr	loc_1438	;	jp	L7
loc_1435:			;L8:
	ld	hl,p_1420_1	;	ld	hl,379f
loc_1438:			;L7:
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	jp	cret		;	jp	cret

;=========================================================
; sub_143F OK++
;=========================================================
	global	_sub_143F	;	global	_sub_143F
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	_printf		;	global	_printf
	global	wrelop		;	global	wrelop
	global	_off_AACA	;	global	_off_AACA
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_143F:
	call	csv		;	call	csv
	ld	a,(ix+6)	;	ld	a,(ix+6)
	cp	15		;	cp	15
	jr	nz,loc_1454	;	jp	nz,l85
	ld	hl,p_143f_1	;	ld	hl,399f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	jp	cret		;	jp	cret
loc_1454:			;l85:
	ld	e,(ix+6)	;	ld	e,(ix+6)
	ld	d,0		;	ld	d,0
	ld	hl,7		;	ld	hl,7
	call	wrelop		;	call	wrelop
	jr	c,loc_1471	;	jp	c,l86
	ld	e,(ix+6)	;	ld	e,(ix+6)
	ld	d,0		;	ld	d,0
	srl	d		;	srl	d
	rr	e		;	rr	e
	ld	hl,11		;	ld	hl,11
	add	hl,de		;	add	hl,de
	ld	(ix+6),l	;	ld	(ix+6),l
loc_1471:			;l86:
	ld	de,_off_AACA	;	ld	de,_off_AACA
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	hl,p_143f_2	;	ld	hl,409f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	jp	cret		;	jp	cret

;=========================================================
; sub_1489 OK++
;=========================================================
	global	_sub_1489	;	global	_sub_1489
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	_printf		;	global	_printf
	global	wrelop		;	global	wrelop
	global	_off_AACA	;	global	_off_AACA
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_1489:
	call	csv		;	call	csv
	ld	a,(ix+6)	;	ld	a,(ix+6)
	cp	15		;	cp	15
	jr	nz,loc_149E	;	jp	nz,l88
	ld	hl,p_1489_1	;	ld	hl,419f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	jp	cret		;	jp	cret
loc_149E:			;l88:
	ld	e,(ix+6)	;	ld	e,(ix+6)
	ld	d,0		;	ld	d,0
	ld	hl,7		;	ld	hl,7
	call	wrelop		;	call	wrelop
	jr	c,loc_14BB	;	jp	c,l89
	ld	e,(ix+6)	;	ld	e,(ix+6)
	ld	d,0		;	ld	d,0
	srl	d		;	srl	d
	rr	e		;	rr	e
	ld	hl,11		;	ld	hl,11
	add	hl,de		;	add	hl,de
	ld	(ix+6),l	;	ld	(ix+6),l
loc_14BB:			;l89:
	ld	de,_off_AACA	;	ld	de,_off_AACA
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,0		;	ld	h,0
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	push	bc		;	push	bc
	ld	hl,p_1489_2	;	ld	hl,429f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	jp	cret		;	jp	cret

;=========================================================
; sub_14D3 OK++
;=========================================================
	global	_sub_14D3	;	global	_sub_14D3
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	_printf		;	global	_printf
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_14D3:
	call	csv		;	call	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	l,(iy+17)	;	ld	l,(iy+17)
	ld	h,(iy+18)	;	ld	h,(iy+18)
	inc	hl		;	inc	hl
	push	hl		;	push	hl
	dec	hl		;	dec	hl
	push	hl		;	push	hl
	ld	hl,p_14d3_1	;	ld	hl,439f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	jp	cret		;	jp	cret

;=========================================================
; sub_14F3 OK++
;=========================================================
	global	_sub_14F3	;	global	_sub_14F3
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	wrelop		;	global	wrelop
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_14F3:
	call	csv		;	call	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	bit	1,(iy+21)	;	bit	1,(iy+21)
	jr	z,loc_150A	;	jp	z,l92
loc_1505:			;L9:
	ld	l,0		;	ld	l,0
	jp	cret		;	jp	cret
loc_150A:			;l92:
	ld	a,(iy+21)	;	ld	a,(iy+21)
	or	(iy+22)		;	or	(iy+22)
	jr	z,loc_1517	;	jp	z,l93
	ld	l,2		;	ld	l,2
	jp	cret		;	jp	cret
loc_1517:			;l93:
	ld	e,(iy+23)	;	ld	e,(iy+23)
	ld	d,(iy+24)	;	ld	d,(iy+24)
	ld	hl,11		;	ld	hl,11
	add	hl,de		;	add	hl,de
	ld	e,(hl)		;	ld	e,(hl)
	inc	hl		;	inc	hl
	ld	d,(hl)		;	ld	d,(hl)
	ld	hl,1		;	ld	hl,1
	call	wrelop		;call	wrelop
	jr	c,loc_1505	;	jp	c,L9
	ld	e,(iy+23)	;	ld	e,(iy+23)
	ld	d,(iy+24)	;	ld	d,(iy+24)
	ld	hl,21		;	ld	hl,21
	add	hl,de		;	add	hl,de
	ld	l,(hl)		;	ld	l,(hl)
	jp	cret		;	jp	cret

;=========================================================
; sub_153A OK++
;=========================================================
	global	_sub_153A	;	global	_sub_153A
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	_array_A542	;	global	_array_A542
	global	csv		;	global	csv
	global	_putchar	;	global	_putchar
	global	_sub_14F3	;	global	_sub_14F3

	psect	text

; Disassembled version		; After compiling C source code
_sub_153A:
	call	csv		;	call	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	push	hl		;	push	hl
	call	_sub_14F3	;	call	_sub_14F3
	ld	e,l		;	ld	e,l
	ld	d,0		;	ld	d,0
	ld	hl,_array_A542	;	ld	hl,F628
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	ld	l,a		;	ld	l,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	ex	(sp),hl		;	ex	(sp),hl
	call	_putchar	;	call	_putchar
	jp	cret		;	jp	cret

;=========================================================
; sub_155D OK++
;=========================================================
	global	_sub_155D	;	global	_sub_155D
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	_printf		;	global	_printf
	global	_putchar	;	global	_putchar
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_155D:
	call	csv		;	call	csv
	push	hl		;	push	hl
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	ld	(ix+-1),0	;	ld	(ix+-1),0
	jr	loc_15B0	;	jp	l97
loc_1570:			;L10:
	or	a		;	or	a
	jr	nz,loc_157D	;	jp	nz,l100
	ld	hl,p_155d_1	;	ld	hl,449f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	jr	loc_1585	;	jp	l101
loc_157D:			;l100:
	ld	hl,44		;	ld	hl,44
	push	hl		;	push	hl
	call	_putchar	;	call	_putchar
	pop	bc		;	pop	bc
loc_1585:			;l101:
	push	iy		;	push	iy
	pop	hl		;	pop	hl
	inc	hl		;	inc	hl
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	dec	hl		;	dec	hl
	ld	l,(hl)		;	ld	l,(hl)
	ld	h,0		;	ld	h,0
	push	hl		;	push	hl
	ld	hl,p_155d_2	;	ld	hl,459f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	inc	(ix+-1)		;	inc	(ix+-1)
	ld	a,(ix+-1)	;	ld	a,(ix+-1)
	cp	16		;	cp	16
	jr	nz,loc_15B0	;	jp	nz,l97
	ld	hl,10		;	ld	hl,10
	push	hl		;	push	hl
	call	_putchar	;	call	_putchar
	pop	bc		;	pop	bc
	ld	(ix+-1),0	;	ld	(ix+-1),0
loc_15B0:			;l97:
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	dec	hl		;	dec	hl
	ld	(ix+8),l	;	ld	(ix+8),l
	ld	(ix+9),h	;	ld	(ix+9),h
	inc	hl		;	inc	hl
	ld	a,l		;	ld	a,l
	or	h		;	or	h
	ld	a,(ix+-1)	;	ld	a,(ix+-1)
	jr	nz,loc_1570	;	jp	nz,L10
	or	a		;	or	a
	jp	z,cret		;	jp	z,cret
	ld	hl,10		;	ld	hl,10
	push	hl		;	push	hl
	call	_putchar	;	call	_putchar
	jp	cret		;	jp	cret

;=========================================================
; sub_15D3 OK++
;=========================================================
	global	_sub_15D3	;	global	_sub_15D3
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	_printf		;	global	_printf
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_15D3:
	call	csv		;	call	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	ld	hl,p_15d3_1	;	ld	hl,469f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	jp	cret		;	jp	cret

;=========================================================
; sub_15E7 OK++
;=========================================================
	global	_sub_15E7	;	global	_sub_15E7
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	_printf		;	global	_printf
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_15E7:
	call	csv		;	call	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	ld	hl,p_15e7_1	;	ld	hl,479f
	push	hl		;	push	hl
	call	_printf		;	call	_printf
	jp	cret		;	jp	cret

;=========================================================
; sub_15FB OK++
;=========================================================
	global	_sub_15FB	;	global	_sub_15FB
	global	ncsv,cret,indir	;	global	ncsv,cret,indir
	global	wrelop		;	global	wrelop
	global	csv		;	global	csv

	psect	text

; Disassembled version		; After compiling C source code
_sub_15FB:
	call	csv		;	call	csv
	ld	l,(ix+6)	;	ld	l,(ix+6)
	ld	h,(ix+7)	;	ld	h,(ix+7)
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	bit	7,(ix+9)	;	bit	7,(ix+9)
	jr	nz,loc_1631	;	jp	nz,l108
	ld	(iy+21),2	;	ld	(iy+21),2
	ld	e,(ix+10)	;	ld	e,(ix+10)
	ld	d,(ix+11)	;	ld	d,(ix+11)
	ld	hl,255		;	ld	hl,255
	call	wrelop		;	call	wrelop
	jp	m,loc_162B	;	jp	m,l110
	ld	(iy+9),1	;	ld	(iy+9),1
loc_1624:			;l111:
	ld	(iy+10),0	;	ld	(iy+10),0
	jp	cret		;	jp	cret
loc_162B:			;l110:
	ld	(iy+9),2	;	ld	(iy+9),2
	jr	loc_1624	;	jp	l111
loc_1631:			;l108:
	ld	(iy+21),1	;	ld	(iy+21),1
	ld	e,(ix+10)	;	ld	e,(ix+10)
	ld	d,(ix+11)	;	ld	d,(ix+11)
	ld	hl,127		;	ld	hl,127
	call	wrelop		;	call	wrelop
	jp	m,loc_162B	;	jp	m,l110
	ld	de,-128		;	ld	de,-128
	ld	l,(ix+8)	;	ld	l,(ix+8)
	ld	h,(ix+9)	;	ld	h,(ix+9)
	call	wrelop		;	call	wrelop
	jp	m,loc_162B	;	jp	m,l110
	ld	(iy+9),1	;	ld	(iy+9),1
	jr	loc_1624	;	jp	l111

; End of file - b19new.asm



