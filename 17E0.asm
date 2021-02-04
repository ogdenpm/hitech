*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 17E0.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_17E0
;
; Compiler generates identical code from restored source
; program in C, however, location of branches associated
; with case constants is different from original.
; This does not affect the function.
;=========================================================
	global	_sub_17E0	;	global	_sub_17E0
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_sub_1754	;	global	_sub_1754
	global	_sub_306	;	global	_sub_306
	global	_sub_627	;	global	_sub_627
	global	_sub_600E	;	global	_sub_600E
	global	_sub_4192	;	global	_sub_4192
	global	_faterror	;	global	_faterror
	global	_sub_475C	;	global	_sub_475C
	global	_sub_76F	;	global	_sub_76F
	global	_sub_1C8E	;	global	_sub_1C8E
	global	_uerror		;	global	_uerror
	global	_sub_5CF5	;	global	_sub_5CF5
	global	_sub_174C	;	global	_sub_174C
	global	_lvlidx		;	global	_lvlidx
	global	_array_AE57	;	global	_array_AE57
	global	_nstdpth	;	global	_nstdpth
	global	_array_AE97	;	global	_array_AE97
	global	_array_AE13	;	global	_array_AE13
	global	_array_AEDB	;	global	_array_AEDB
	global csv

	psect	text

;	Disassembled version	; After compiling C source code
_sub_17E0:
	call	csv		;	call 	csv
	push	hl		;	push 	hl
	push	hl		;	push 	hl
	ld	hl,39h		;	ld	hl,57
	push	hl		;	push	hl
	call	_sub_306	;	call	_sub_306
	push	hl		;	push	hl
	call	_sub_1754	;	call	_sub_1754
	pop	bc		;	pop	bc
	push	hl		;	push	hl
	pop	iy		;	pop	iy
	push	hl		;	push	hl
	pop	de		;	pop	de
	ld	hl,0Dh		;	ld	hl,13
	add	hl,de		;	add	hl,de
	ex	(sp),hl		;	ex	(sp),hl
	call	_sub_306	;	call	_sub_306
	push	hl		;	push	hl
	call	_sub_627	;	call	_sub_627
	pop	bc		;	pop	bc
	pop	bc		;	pop	bc
	ld	(iy+0Fh),l	;	ld	(iy+15),l
	ld	(iy+10h),h	;	ld	(iy+16),h
	call	_sub_4192	;	call	_sub_4192
	push	hl		;	push	hl
	call	_sub_600E	;	call	_sub_600E
	pop	bc		;	pop	bc
	ld	(ix+-2),l	;	ld	(ix+-2),l
	ld	(ix+-1),h	;	ld	(ix+-1),h
	ld	a,(hl)		;	ld	a,(hl)
	cp	43h		;	cp	67
	jr	z,loc_1825	;	jp	z,l12
	ld	hl,19f		;	ld	hl,19f
	push	hl		;	push	hl
	call	_faterror	;	call	_faterror
	pop	bc		;	pop	bc
loc_1825:			;l12:
	ld	e,(ix+-2)	;	ld	e,(ix+-2)
	ld	d,(ix+-1)	;	ld	d,(ix+-1)
	ld	hl,19h		;	ld	hl,25
	add	hl,de		;	add	hl,de
	ld	c,(hl)		;	ld	c,(hl)
	inc	hl		;	inc	hl
	ld	b,(hl)		;	ld	b,(hl)
	ld	(iy+0Bh),c	;	ld	(iy+11),c
	ld	(iy+0Ch),b	;	ld	(iy+12),b
	ld	l,e		;	ld	l,e
	ld	h,d		;	ld	h,d
	push	hl		;	push	hl
	call	_sub_475C	;	call	_sub_475C
	pop	bc		;	pop	bc
	call	_sub_306	;	call	_sub_306
	ld	a,(hl)		;	ld	a,(hl)
	ld	l,a		;	ld	l,a
	rla			;	rla
	sbc	a,a		;	sbc	a,a
	ld	h,a		;	ld	h,a
	ld	(ix+-4),l	;	ld	(ix+-4),l
	ld	(ix+-3),h	;	ld	(ix+-3),h
	ld	hl,5Dh		;	ld	hl,93
	push	hl		;	push	hl
	call	_sub_76F	;	call	_sub_76F
	pop	bc		;	pop	bc
	ld	l,(ix+-4)	;	ld	l,(ix+-4)
	ld	h,(ix+-3)	;	ld	h,(ix+-3)
	ld	a,h		;	ld	a,h
	or	a		;	or	a
	jr	nz,loc_1890	;	jp	nz,l30
	ld	a,l		;	ld	a,l
	cp	41h		;	cp	65
	jr	z,loc_18AE	;	jp	z,l16		
	cp	45h		;	cp	69
	jr	z,loc_18C4	;	jp	z,l18
	cp	50h		;	cp	80
	jr	z,loc_18B8	;	jp	z,l22
	cp	52h		;	cp	82
	jr	z,loc_18B4	;	jp	z,l20
	cp	53h		;	cp	83
	jr	z,loc_18BE	;	jp	z,l24
	cp	54h		;	cp	84
	jr	z,loc_18CA	;	jp	z,l26
	cp	61h		;	cp	97
	jr	z,loc_18AE	;	jp	z,l16
	cp	65h		;	cp	101
	jr	z,loc_18C4	;	jp	z,l18
	cp	70h		;	cp	112
	jr	z,loc_18B8	;	jp	z,l22
	cp	72h		;	cp	114
	jr	z,loc_18B4	;	jp	z,l20
	cp	73h		;	cp	115
	jr	z,loc_18BE	;	jp	z,l24
	cp	74h		;	cp	116
	jr	z,loc_18CA	;	jp	z,l26
loc_1890:			;l30:
	ld	hl,29f		;	ld	hl,29f
	push	hl		;	push	hl
	call	_faterror	;	call	_faterror
	pop	bc		;	pop	bc
loc_1898:			;l13:
	push	iy		;	push	iy
	call	_sub_1C8E	;	call	_sub_1C8E
	pop	bc		;	pop	bc
	ld	(iy+9),l	;	ld	(iy+9),l
	ld	(iy+0Ah),h	;	ld	(iy+10),h
	ld	a,(iy+2)	;	ld	a,(iy+2)
	cp	41h		;	cp	65
	jr	nz,loc_1913	;	jp	z,cret
	jp	cret		;			   ;----+
loc_18AE:			;l16:				;
	ld	(iy+15h),1	;	ld	(iy+21),1	;
	jr	loc_1898	;	jp	l13		;
loc_18B4:			;l20:				;
	set	3,(iy+3)	;	set	3,(iy+3)	;
loc_18B8:			;l22:				;
	ld	(iy+15h),5	;	ld	(iy+21),5	;
	jr	loc_1898	;	jp	l13		;
loc_18BE:			;l24:				;
	ld	(iy+15h),4	;	ld	(iy+21),4	;
	jr	loc_1898	;	jp	l13		;
loc_18C4:			;l18:				;
	ld	(iy+15h),3	;	ld	(iy+21),3	;
	jr	loc_1898	;	jp	l13		;
loc_18CA:			;l26:				;
	ld	(iy+2),41h	;	ld	(iy+2),65	;
	ld	a,(iy+0Dh)	;	ld	a,(iy+13)	;
	or	(iy+0Eh)	;	or	(iy+14)		;
	jr	z,loc_18E4	;	jp	z,l27		;
	ld	(iy+11h),0	;	ld	(iy+17),0	;
	ld	(iy+12h),0	;	ld	(iy+18),0	;
	ld	(iy+15h),2	;	ld	(iy+21),2	;
	jr	loc_18FF	;	jp	l28		;
loc_18E4:			;l27:				;
	ld	e,(iy+0Fh)	;	ld	e,(iy+15)	;
	ld	d,(iy+10h)	;	ld	d,(iy+16)	;
	ld	hl,11h		;	ld	hl,17		;
	add	hl,de		;	add	hl,de		;
	ld	c,(hl)		;	ld	c,(hl)		;
	inc	hl		;	inc	hl		;
	ld	b,(hl)		;	ld	b,(hl)		;
	ld	(iy+11h),c	;	ld	(iy+17),c	;
	ld	(iy+12h),b	;	ld	(iy+18),b	;
	ld	hl,15h		;	ld	hl,21		;
	add	hl,de		;	add	hl,de		;
	ld	l,(hl)		;	ld	l,(hl)		;
	ld	(iy+15h),l	;	ld	(iy+21),l	;
loc_18FF:			;l28:				;
	ld	de,1		;	ld	de,1		;
	ld	l,(iy+0Bh)	;	ld	l,(iy+11)	;
	ld	h,(iy+0Ch) 	;	ld	h,(iy+12)	;
	or	a		;	or	a		;
	sbc	hl,de		;	sbc	hl,de		;
	jr	z,loc_1898	;	jp	z,l13		;
	ld	(iy+15h),0	;	ld	(iy+21),0	;
	jr	loc_1898	;	jp	l13		;
loc_1913:			;				;
	ld	a,(iy+0Dh)	;	ld	a,(iy+13)  <----+
	or	(iy+0Eh)	;	or	(iy+14)
	jr	nz,loc_193A	;	jp	nz,l34
	ld	a,(iy+9)	;	ld	a,l
	or	(iy+0Ah)	;	or	(iy+10)
	jr	nz,loc_193A	;	jp	nz,l34
	ld	e,(iy+0Fh)	;	ld	e,(iy+15)
	ld	d,(iy+10h)	;	ld	d,(iy+16)
	ld	hl,9		;	ld	hl,9
	add	hl,de		;	add	hl,de
	ld	a,(hl)		;	ld	a,(hl)
	inc	hl		;	inc	hl
	or	(hl)		;	or	(hl)
	jr	nz,loc_193A	;	jp	nz,l34
	ld	hl,39f		;	ld	hl,39f
	push	hl		;	push	hl
	call	_uerror	;	call	_uerror
	pop	bc		;	pop	bc
loc_193A:			;l34:
	ld	a,(iy+15h)	;	ld	a,(iy+21)
	cp	5		;	cp	1
	jr	z,loc_1945	;	jp	z,l36
	cp	1		;	cp	5
	jr	nz,loc_1955	;	jp	z,l36
				;			   ;----+
loc_1945:			;l36:				;
	ld	l,(ix+-4)	;	ld	l,(ix+-4)	;
	ld	h,(ix+-3)	;	ld	h,(ix+-3)	;
	push	hl		;	push	hl		;
	push	iy		;	push	iy		;
	call	_sub_5CF5	;	call	_sub_5CF5	;
	pop	bc		;	pop	bc		;
	pop	bc		;	pop	bc		;
	jr	loc_195E	;	jp	l33		;
loc_1955:			;				;
	call	_sub_174C	;	call	_sub_174C  <----+
	ld	(iy+11h),l	;	ld	(iy+17),l
	ld	(iy+12h),h	;	ld	(iy+18),h
loc_195E:			;l33:
	bit	1,(iy+0Dh)	;	bit	1,(iy+13)
	jp	z,cret		;	jp	z,cret
	ld	a,(iy+0Bh)	;	ld	a,(iy+11)
	or	(iy+0Ch)	;	or	(iy+12)
	jp	z,cret		;	jp	z,cret
	ld	de,20h		;	ld	de,32
	ld	hl,(_lvlidx)	;	ld	hl,(_lvlidx)
	inc	hl		;	inc	hl
	ld	(_lvlidx),hl	;	ld	(_lvlidx),hl
	or	a		;	or	a
	sbc	hl,de		;	sbc	hl,de
	jr	nz,loc_1985	;	jp	nz,l40
	ld	hl,49f		;	ld	hl,49f
	push	hl		;	push	hl
	call	_faterror	;	call	_faterror
	pop	bc		;	pop	bc
loc_1985:			;l40:
	ld	de,_array_AE57	;	ld	de,_array_AE57
	ld	hl,(_lvlidx)	;	ld	hl,(_lvlidx)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,(_nstdpth)	;	ld	de,(_nstdpth)
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	de,_array_AE97	;	ld	de,_array_AE97
	ld	hl,(_lvlidx)	;	ld	hl,(_lvlidx)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,6		;	ld	de,6
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	de,_array_AE13	;	ld	de,_array_AE13
	ld	hl,(_lvlidx)	;	ld	hl,(_lvlidx)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	ld	de,0		;	ld	de,0
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	ld	de,_array_AEDB	;	ld	de,_array_AEDB
	ld	hl,(_lvlidx)	;	ld	hl,(_lvlidx)
	add	hl,hl		;	add	hl,hl
	add	hl,de		;	add	hl,de
	push	iy		;	push	iy
	pop	de		;	pop	de
	ld	(hl),e		;	ld	(hl),e
	inc	hl		;	inc	hl
	ld	(hl),d		;	ld	(hl),d
	jp	cret		;	jp	cret

; End of function sub_17E0 OK+

	psect	data

d_17e0_A8E2:
19:
	defb	66,97,100,32,101,108,101,109,101,110,116,32,99,111,117,110
	defb	116,32,101,120,112,114,0
d_17e0_A8F9:
29:
	defb	66,97,100,32,115,116,111,114,97,103,101,32,99,108,97,115
	defb	115,0
d_17e0_A90B:
39:
	defb	66,97,100,32,100,105,109,101,110,115,105,111,110,115,0
d_17e0_A91A:
49:
	defb	70,117,110,99,116,105,111,110,115,32,110,101,115,116,101,100
	defb	32,116,111,111,32,100,101,101,112,0

	psect	text

; End of file 17E0.asm


