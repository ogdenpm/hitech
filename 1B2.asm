*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated with original code

; File - 1B2.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; sub_1B2 OK++
;=========================================================
	global	_sub_1B2	;	global	_sub_1B2
	global	ncsv,cret,indir	;	global	ncsv, cret, indir
	global	_byte_A46A	;	global	_byte_A46A
	global	_strcmp		;	global	_strcmp
	global	_tnames		;	global	_tnames
	global	brelop		;	global	brelop
	global	csv		;	global	csv

;psect	data	; Data has been temporarily moved to another location.
;
;_tnames:
;F609:
;	defw	19f
;	defw	29f
;	defw	39f
;	defw	49f
;	defw	59f
;	defw	69f
;	defw	79f
;	defw	89f
;	defw	99f
;	defw	109f
;	defw	119f
;	defw	129f
;	defw	139f
;	defw	149f
;	defw	159f
;	defw	169f
;	defw	179f
;	defw	189f
;	defw	199f
;	defw	209f
;	defw	219f
;	defw	229f
;	defw	239f
;	defw	249f
;	defw	259f
;	defw	269f
;	defw	279f
;	defw	289f
;	defw	299f
;	defw	309f
;	defw	319f
;	defw	329f
;	defw	339f
;	defw	349f
;	defw	359f
;	defw	369f
;	defw	379f
;	defw	389f
;	defw	399f
;	defw	409f
;	defw	419f
;	defw	429f
;	defw	439f
;	defw	449f
;	defw	459f
;	defw	469f
;	defw	479f
;	defw	489f
;	defw	499f
;	defw	509f
;	defw	519f
;	defw	529f
;	defw	539f
;	defw	549f
;	defw	559f
;	defw	569f
;	defw	579f
;	defw	589f
;	defw	599f
;	defw	609f
;	defw	619f
;	defw	629f
;	defw	639f
;	defw	649f
;	defw	659f
;	defw	669f
;	defw	679f
;	defw	689f
;	defw	699f
;	defw	709f
;	defw	719f
;	defw	729f
;_byte_A46A:
;F610:	defb	65

	psect	text

_sub_1B2:
; After compiling C source code	;	Disassembled version
	call 	csv		;	call	  csv
	push 	hl		;	push	  hl
	push 	hl		;	push	  hl
	ld	l,(ix+6)	;	ld	  l,(ix+6)
	ld	h,(ix+7)	;	ld	  h,(ix+7)
	push	hl		;	push	  hl
	pop	iy		;	pop	  iy
	ld	(ix+-2),0	;	ld	  (ix+-2),0
	ld	a,(_byte_A46A)	;	ld	  a,(_byte_A46A)
	ld	(ix+-1),a	;	ld	  (ix+-1),a
l14:				;loc_1CA:
	ld	e,(ix+-2)	;	ld	  e,(ix+-2)
	ld	d,0		;	ld	  d,0
	ld	l,(ix+-1)	;	ld	  l,(ix+-1)
	ld	h,d		;	ld	  h,d
	add	hl,de		;	add	  hl,de
	srl	h		;	srl	  h
	rr	l		;	rr	  l
	ld	(ix+-3),l	;	ld	  (ix+-3),l
	ld	de,_tnames	;	ld	  de,_tnames
	ld	h,0		;	ld	  h,0
	add	hl,hl		;	add	  hl,hl
	add	hl,de		;	add	  hl,de
	ld	c,(hl)		;	ld	  c,(hl)
	inc	hl		;	inc	  hl
	ld	b,(hl)		;	ld	  b,(hl)
	push	bc		;	push	  bc
	push	iy		;	push	  iy
	call	_strcmp		;	call	  _strcmp
	pop	bc		;	pop	  bc
	pop	bc		;	pop	  bc
	ld	a,l		;	ld	  a,l
	ld	(ix+-4),a	;	ld	  (ix+-4),a
	or	a		;	or	  a	 
	jr	nz,l15		;	jp	  nz,loc_1FA	<---- Code difference
	ld	l,(ix+-3)	;	ld	  l,(ix+-3)
	jp	cret		;	jp	  cret
l15:				;loc_1FA:
	ld	a,(ix+-4)	;	ld	  a,(ix+-4)
	or	a		;	or	  a
	ld	a,(ix+-3)	;	ld	  a,(ix+-3)
	jp	p,L1		;	jp	  p,loc_20B
	add	a,255		;	add	  a,0FFh	
	ld	(ix+-1),a	;	ld	  (ix+-1),a
	jr	l12		;	jp	  loc_20F	<---- Code difference
L1:				;loc_20B:
	inc	a		;	inc	  a
	ld	(ix+-2),a	;	ld	  (ix+-2),a
l12:				;loc_20F:	
	ld	b,(ix+-2)	;	ld	  b,(ix+-2)
	ld	a,(ix+-1)	;	ld	  a,(ix+-1)
	call	brelop		;	call	  brelop	
	jr	nc,l14		;	jp	  nc,loc_1CA	<---- Code difference
	ld	l,255		;	ld	  l,255	
	jp	cret		;	jp	  cret		

; End of function sub_1B2 OK++

;=========================================================
; gethashptr OK++
;=========================================================
	global	_gethashptr	;	global	_gethashptr
	global	_hashtab	;	global	_hashtab
	global	lmod		;	global	lmod
	global 	csv		;	global 	csv

; After compiling C source code	;	Disassembled version
_gethashptr:
	call 	csv		;	call	  csv
	push 	hl		;	push	  hl
	ld	l,(ix+6)	;	ld	  l,(ix+6)
	ld	h,(ix+7)	;	ld	  h,(ix+7)
	push	hl		;	push	  hl
	pop	iy		;	pop	  iy
	ld	(ix+-2),0	;	ld	  (ix+-2),0
	ld	(ix+-1),0	;	ld	  (ix+-1),0
	jr	l19		;	jp	  loc_24B	<---- Code difference
l20:				;loc_236:
	ld	e,(iy+0)	;	ld	  e,(iy+0)
	ld	d,0		;	ld	  d,0
	ld	l,(ix+-2)	;	ld	  l,(ix+-2)
	ld	h,(ix+-1)	;	ld	  h,(ix+-1)
	add	hl,hl		;	add	  hl,hl
	add	hl,de		;	add	  hl,de
	ld	(ix+-2),l	;	ld	  (ix+-2),l
	ld	(ix+-1),h	;	ld	  (ix+-1),h
	inc	iy		;	inc	  iy
l19:				;loc_24B:
	ld	a,(iy+0)	;	ld	  a,(iy+0)
	or	a		;	or	  a
	jr	nz,l20		;	jp	  nz,loc_236	<---- Code difference
	ld	de,101		;	ld	  de,65h
	ld	l,(ix+-2)	;	ld	  l,(ix+-2)
	ld	h,(ix+-1)	;	ld	  h,(ix+-1)
	call	lmod		;	call	  lmod
	add	hl,hl		;	add	  hl, hl
	ld	de,_hashtab	;	ld	  de,_hashtab
	add	hl,de		;	add	  hl,de
	jp	cret		;	jp	  cret

; End of function gethashptr OK++

;=========================================================
; sub_265 OK++
;=========================================================
	global	_sub_265	;	global	_sub_265
	global	_allocmem	;	global	_allocmem
	global	_strlen		;	global	_strlen
	global	_strcpy		;	global	_strcpy
	global	_nstdpth	;	global	_nstdpth
	global 	csv		;	global 	csv

; After compiling C source code	;	Disassembled version
_sub_265:
	call 	csv		;	call	  csv
	push 	hl		;	push	  hl
	ld	l,(ix+6)	;	ld	  l,(ix+6)
	ld	h,(ix+7)	;	ld	  h,(ix+7)
	push	hl		;	push	  hl
	call	_gethashptr	;	call	  _gethashptr
	pop	bc		;	pop	  bc
	ld	(ix+-2),l	;	ld	  (ix+-2),l
	ld	(ix+-1),h	;	ld	  (ix+-1),h
	ld	c,(hl)		;	ld	  c,(hl)
	inc	hl		;	inc	  hl
	ld	b,(hl)		;	ld	  b,(hl)
	push	bc		;	push	  bc
	pop	iy		;	pop	  iy	
	jr	l23		;	jp	  loc_2A8	<---- Code difference
l24:				;loc_282:
	ld	l,(ix+6)	;	ld	  l,(ix+6)
	ld	h,(ix+7)	;	ld	  h,(ix+7)
	push	hl		;	push	  hl
	ld	l,(iy+0)	;	ld	  l,(iy+0)
	ld	h,(iy+1)	;	ld	  h,(iy+1)
	push	hl		;	push	  hl
	call	_strcmp		;	call	  _strcmp
	pop	bc		;	pop	  bc		
	pop	bc		;	pop	  bc
	ld	a,l		;	ld	  a,l
	or	h		;	or	  h
	jr	nz,l26		;	jp	  nz,loc_29F	<---- Code difference
L2:				;loc_299:
	push	iy		;	push	  iy
	pop	hl		;	pop	  hl
	jp	cret		;	jp	  cret
l26:				;loc_29F:
	ld	l,(iy+7)	;	ld	  l,(iy+7)
	ld	h,(iy+8)	;	ld	  h,(iy+8)
	push	hl		;	push	  hl
	pop	iy		;	pop	  iy
l23:				;loc_2A8:
	push	iy		;	push	  iy
	pop	hl		;	pop	  hl
	ld	a,l		;	ld	  a,l
	or	h		;	or	  h
	jr	nz,l24		;	jp	  nz,loc_282	<---- Code difference
	ld	hl,22		;	ld	  hl,16h
	push	hl		;	push	  hl
	call	_allocmem	;	call	  _allocmem
	pop	bc		;	pop	  bc
	push	hl		;	push	  hl
	pop	iy		;	pop	  iy
	ld	l,(ix+-2)	;	ld	  l,(ix+-2)
	ld	h,(ix+-1)	;	ld	  h,(ix+-1)
	ld	c,(hl)		;	ld	  c,(hl)
	inc	hl		;	inc	  hl
	ld	b,(hl)		;	ld	  b,(hl)
	ld	(iy+7),c	;	ld	  (iy+7),c
	ld	(iy+8),b	;	ld	  (iy+8),b	
	ld	l,(ix+6)	;	ld	  l,(ix+6)
	ld	h,(ix+7)	;	ld	  h,(ix+7)
	push	hl		;	push	  hl
	call	_strlen		;	call	  _strlen
	pop	bc		;	pop	  bc
	inc	hl		;	inc	  hl
	push	hl		;	push	  hl
	call	_allocmem	;	call	  _allocmem
	ld	(iy+0),l	;	ld	  (iy+0),l
	ld	(iy+1),h	;	ld	  (iy+1),h
	ld	l,(ix+6)	;	ld	  l,(ix+6)
	ld	h,(ix+7)	;	ld	  h,(ix+7)
	ex	(sp),hl		;	ex	  (sp),hl
	ld	l,(iy+0)	;	ld	  l,(iy+0)
	ld	h,(iy+1)	;	ld	  h,(iy+1)
	push	hl		;	push	  hl
	call	_strcpy		;	call	  _strcpy
	pop	bc		;	pop	  bc
	pop	bc		;	pop	  bc
	ld	a,(_nstdpth)	;	ld	  a,(_nstdpth)
	ld	(iy+4),a	;	ld	  (iy+4),a
	push	iy		;	push	  iy
	pop	de		;	pop	  de
	ld	l,(ix+-2)	;	ld	  l,(ix+-2)
	ld	h,(ix+-1)	;	ld	  h,(ix+-1)
	ld	(hl),e		;	ld	  (hl),e
	inc	hl		;	inc	  hl
	ld	(hl),d		;	ld	  (hl),d		
	jr	L2		;	jp	  loc_299	<---- Code difference

;psect	data	; Data has been temporarily moved to another location.

;19:	defb	0
;29:	defb	33,0
;39:	defb	33,61,0
;49:	defb	35,0
;59:	defb	36,0
;69:	defb	36,85,0
;79:	defb	37,0
;89:	defb	38,0
;99:	defb	38,38,0
;109:	defb	38,85,0
;119:	defb	40,0
;129:	defb	41,0
;139:	defb	42,0
;149:	defb	42,85,0
;159:	defb	43,0
;169:	defb	43,43,0
;179:	defb	43,85,0
;189:	defb	44,0
;199:	defb	45,0
;209:	defb	45,45,0
;219:	defb	45,62,0
;229:	defb	45,85,0
;239:	defb	46,0
;249:	defb	46,46,0
;259:	defb	47,0
;269:	defb	58,0
;279:	defb	58,85,0
;289:	defb	58,115,0
;299:	defb	59,0
;309:	defb	59,59,0
;319:	defb	60,0
;329:	defb	60,60,0
;339:	defb	60,61,0
;349:	defb	61,0
;359:	defb	61,37,0
;369:	defb	61,38,0
;379:	defb	61,42,0
;389:	defb	61,43,0
;399:	defb	61,45,0
;409:	defb	61,47,0
;419:	defb	61,60,60,0
;429:	defb	61,61,0
;439:	defb	61,62,62,0
;449:	defb	61,94,0
;459:	defb	61,124,0
;469:	defb	62,0
;479:	defb	62,61,0
;489:	defb	62,62,0
;499:	defb	63,0
;509:	defb	64,0
;519:	defb	91,92,0
;529:	defb	91,97,0
;539:	defb	91,99,0
;549:	defb	91,101,0
;559:	defb	91,105,0
;569:	defb	91,115,0
;579:	defb	91,117,0
;589:	defb	91,118,0
;599:	defb	94,0
;609:	defb	123,0
;619:	defb	124,0
;629:	defb	124,124,0
;639:	defb	125,0
;649:	defb	126,0
;659:	defb	82,69,67,73,80,0
;669:	defb	84,89,80,69,0
;679:	defb	73,68,0
;689:	defb	67,79,78,83,84,0
;699:	defb	70,67,79,78,83,84,0
;709:	defb	82,69,71,0
;719:	defb	73,78,65,82,69,71,0
;729:	defb	66,73,84,70,73,69,76,68,0

	psect	text

; End of function sub_265 OK++

; End of file - 1B2.as */

