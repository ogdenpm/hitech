global	_finPass1
global	ncsv, cret, indir
global	_loadAddress
global	_linkAddress
global	_maxLinkAddress
global	_key_R
global	_psect_location
global	_simpl_err
global	_getSymbol
global	_fatal_err
global	aslladd
global	aslland
global	aslladd
global	aslland
global	_saveLoadAddress
global	_parseLongVal
global	lland
global	aslladd
global	lrelop
global	lland
global	aslladd
global	_psectInfo
global	aslladd
global	aslland
global	lland
global	lladd
global	lrelop
global	lladd
global	aslladd
global	aslladd
global	aslland
global	lland
global	aslladd
global	_nextPsect
global	lrelop
global	_conv_u32tob
global	_textRecBuf
global	_strcpy
global	_writeRec
global	_strlen
global	_setPsectOrigin
global	_absSym
global	_sprintf
global	_defineIfNeeded
global	lrelop
global	llsub
global	_cntUnresolved
global	_key_I
global	_symbol_table
global	aslladd
global	_key_S
global	_key_C
global	_wrRecord
global	_nonTextRecBuf
global	_conv_u16tob
global	_nonTextRecPtr
global	_key_X
global	_key_Z
global	_isLocalName
global	_wrSymbol
global	_key_H
global	_fprintf
global	_symFp
psect	text
_finPass1:
call ncsv
defw -33
ld	iy,0
ld	de,0
ld	l,e
ld	h,d
ld	(_loadAddress),de
ld	(_loadAddress+2),hl
ld	(_linkAddress),de
ld	(_linkAddress+2),hl
ld	(_maxLinkAddress),de
ld	(_maxLinkAddress+2),hl
ld	a,(_key_R)
or	a
jp	nz,l6
ld	hl,(_psect_location)
ld	a,l
or	h
jp	z,l6
ld	(ix+-30),l
ld	(ix+-29),h
l7:
ld	l,(ix+-30)
ld	h,(ix+-29)
ld	a,(hl)
or	a
jp	nz,l10
ld	hl,19f
push	hl
call	_simpl_err
pop	bc
l6:
ld	hl,_psectInfo
ld	(ix+-24),l
ld	(ix+-23),h
jp	l48
l10:
ld	l,(ix+-30)
ld	h,(ix+-29)
ld	(ix+-32),l
ld	(ix+-31),h
jp	l14
L26:
inc	hl
ld	(ix+-32),l
ld	(ix+-31),h
l14:
ld	l,(ix+-32)
ld	h,(ix+-31)
ld	a,(hl)
or	a
jp	z,L24
ld	a,(hl)
cp	61
jp	z,L24
ld	a,(hl)
cp	44
jp	z,L24
ld	a,(hl)
cp	47
jp	nz,L26
L24:
ld	l,(hl)
ld	(ix+-33),l
ld	l,(ix+-32)
ld	h,(ix+-31)
ld	(hl),0
ld	hl,32768
push	hl
ld	l,(ix+-30)
ld	h,(ix+-29)
push	hl
call	_getSymbol
pop	bc
pop	bc
push	hl
pop	iy
ld	a,l
or	h
jp	nz,l15
ld	hl,16384
push	hl
ld	l,(ix+-30)
ld	h,(ix+-29)
push	hl
call	_getSymbol
pop	bc
pop	bc
push	hl
pop	iy
ld	a,l
or	h
jp	nz,l15
ld	l,(ix+-30)
ld	h,(ix+-29)
push	hl
ld	hl,29f
push	hl
call	_fatal_err
pop	bc
pop	bc
l15:
bit	7,(iy+8)
jp	z,l16
ld	l,(ix+-30)
ld	h,(ix+-29)
push	hl
ld	hl,39f
push	hl
call	_simpl_err
pop	bc
pop	bc
l16:
ld	l,(iy+0)
ld	h,(iy+1)
ld	(ix+-24),l
ld	(ix+-23),h
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,26
add	hl,de
ld	a,(hl)
or	a
jp	z,l17
ld	l,(ix+-30)
ld	h,(ix+-29)
push	hl
ld	hl,49f
push	hl
call	_fatal_err
pop	bc
pop	bc
l17:
ld	a,(ix+-33)
ld	l,(ix+-32)
ld	h,(ix+-31)
ld	(ix+-30),l
ld	(ix+-29),h
ld	(hl),a
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,12
add	hl,de
ld	a,(hl)
inc	hl
or	(hl)
jp	z,l18
ld	hl,12
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
ld	hl,-1
add	hl,bc
ex	de,hl
ld	hl,0
push	hl
push	de
ld	hl,_linkAddress
call	aslladd
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,12
add	hl,de
ld	e,(hl)
inc	hl
ld	d,(hl)
ld	hl,0
ex	de,hl
ld	bc,-1
add	hl,bc
ex	de,hl
adc	hl,bc
push	hl
push	de
ld	l,c
ld	h,b
pop	bc
or	a
sbc	hl,bc
pop	bc
ex	de,hl
ld	hl,-1
sbc	hl,bc
push	hl
push	de
ld	hl,_linkAddress
call	aslland
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,12
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
ld	hl,-1
add	hl,bc
ex	de,hl
ld	hl,0
push	hl
push	de
ld	hl,_loadAddress
call	aslladd
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,12
add	hl,de
ld	e,(hl)
inc	hl
ld	d,(hl)
ld	hl,0
ex	de,hl
ld	bc,-1
add	hl,bc
ex	de,hl
adc	hl,bc
push	hl
push	de
ld	l,c
ld	h,b
pop	bc
or	a
sbc	hl,bc
pop	bc
ex	de,hl
ld	hl,-1
sbc	hl,bc
push	hl
push	de
ld	hl,_loadAddress
call	aslland
l18:
ld	a,1
ld	(ix+-28),a
ld	(ix+-27),a
ld	de,(_loadAddress)
ld	hl,(_loadAddress+2)
ld	(_saveLoadAddress),de
ld	(_saveLoadAddress+2),hl
ld	a,(ix+-33)
cp	61
ld	l,(ix+-30)
ld	h,(ix+-29)
jp	nz,L15
inc	hl
ld	(ix+-30),l
ld	(ix+-29),h
ld	hl,_linkAddress
push	hl
push	ix
pop	de
ld	hl,-30
add	hl,de
push	hl
call	_parseLongVal
pop	bc
pop	bc
ld	a,l
or	a
jp	z,l20
ld	hl,59f
L25:
push	hl
call	_fatal_err
pop	bc
jp	l6
l20:
ld	de,(_linkAddress)
ld	hl,(_linkAddress+2)
ld	(_loadAddress),de
ld	(_loadAddress+2),hl
ld	(ix+-27),2
ld	l,(ix+-30)
ld	h,(ix+-29)
ld	a,(hl)
cp	47
jp	z,l21
ld	(ix+-28),2
l21:
ld	l,(ix+-30)
ld	h,(ix+-29)
L15:
ld	a,(hl)
cp	47
jp	nz,l22
ld	(ix+-28),1
ld	l,(ix+-30)
ld	h,(ix+-29)
inc	hl
ld	(ix+-30),l
ld	(ix+-29),h
ld	hl,_loadAddress
push	hl
push	ix
pop	de
ld	hl,-30
add	hl,de
push	hl
call	_parseLongVal
pop	bc
pop	bc
ld	a,l
or	a
jp	z,l23
ld	de,(_saveLoadAddress)
ld	hl,(_saveLoadAddress+2)
ld	(_loadAddress),de
ld	(_loadAddress+2),hl
jp	l22
l23:
ld	(ix+-28),2
l22:
bit	7,(iy+9)
jp	z,l25
ld	de,(_linkAddress)
ld	hl,(_linkAddress+2)
push	hl
push	de
ld	l,(ix+-24)
ld	h,(ix+-23)
pop	de
ld	(hl),e
inc	hl
ld	(hl),d
inc	hl
pop	bc
ld	(hl),c
inc	hl
ld	(hl),b
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,12
add	hl,de
ld	a,(hl)
inc	hl
or	(hl)
jp	z,l26
ld	de,(_linkAddress)
ld	hl,(_linkAddress+2)
push	hl
push	de
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,12
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
ld	hl,-1
add	hl,bc
ex	de,hl
ld	hl,0
call	lland
ld	a,e
or	d
or	l
or	h
ld	e,(ix+-24)
ld	d,(ix+-23)
jp	z,L16
ld	hl,12
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
push	bc
ld	hl,22
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
ld	hl,6
add	hl,bc
ld	c,(hl)
inc	hl
ld	b,(hl)
push	bc
ld	hl,69f
push	hl
call	_fatal_err
pop	bc
pop	bc
pop	bc
l26:
ld	e,(ix+-24)
ld	d,(ix+-23)
L16:
ld	hl,14
add	hl,de
ld	e,(hl)
inc	hl
ld	d,(hl)
inc	hl
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
push	hl
push	de
ld	hl,_linkAddress
call	aslladd
push	hl
push	de
ld	de,(_maxLinkAddress)
ld	hl,(_maxLinkAddress+2)
call	lrelop
jp	nc,l27
ld	de,(_linkAddress)
ld	hl,(_linkAddress+2)
ld	(_maxLinkAddress),de
ld	(_maxLinkAddress+2),hl
l27:
ld	de,(_loadAddress)
ld	hl,(_loadAddress+2)
push	hl
push	de
ld	l,(ix+-24)
ld	h,(ix+-23)
inc	hl
inc	hl
inc	hl
inc	hl
pop	de
ld	(hl),e
inc	hl
ld	(hl),d
inc	hl
pop	bc
ld	(hl),c
inc	hl
ld	(hl),b
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,12
add	hl,de
ld	a,(hl)
inc	hl
or	(hl)
jp	z,l28
ld	de,(_loadAddress)
ld	hl,(_loadAddress+2)
push	hl
push	de
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,12
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
ld	hl,-1
add	hl,bc
ex	de,hl
ld	hl,0
call	lland
ld	a,e
or	d
or	l
or	h
ld	e,(ix+-24)
ld	d,(ix+-23)
jp	z,L17
ld	hl,12
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
push	bc
ld	hl,22
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
ld	hl,6
add	hl,bc
ld	c,(hl)
inc	hl
ld	b,(hl)
push	bc
ld	hl,79f
push	hl
call	_fatal_err
pop	bc
pop	bc
pop	bc
l28:
ld	e,(ix+-24)
ld	d,(ix+-23)
L17:
ld	hl,14
add	hl,de
ld	e,(hl)
inc	hl
ld	d,(hl)
inc	hl
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
push	hl
push	de
ld	hl,_loadAddress
call	aslladd
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,26
add	hl,de
ld	(hl),1
jp	l29
l25:
ld	hl,_psectInfo
ld	(ix+-26),l
ld	(ix+-25),h
jp	l33
l30:
ld	e,(ix+-26)
ld	d,(ix+-25)
ld	hl,24
add	hl,de
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
push	iy
pop	de
or	a
sbc	hl,de
jp	nz,l32
ld	e,(ix+-26)
ld	d,(ix+-25)
ld	hl,26
add	hl,de
ld	a,(hl)
or	a
jp	nz,l32
ld	a,(ix+-27)
cp	1
jp	nz,l35
ld	hl,12
add	hl,de
ld	a,(hl)
inc	hl
or	(hl)
jp	z,l35
ld	hl,12
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
ld	hl,-1
add	hl,bc
ex	de,hl
ld	hl,0
push	hl
push	de
ld	hl,_linkAddress
call	aslladd
ld	e,(ix+-26)
ld	d,(ix+-25)
ld	hl,12
add	hl,de
ld	e,(hl)
inc	hl
ld	d,(hl)
ld	hl,0
ex	de,hl
ld	bc,-1
add	hl,bc
ex	de,hl
adc	hl,bc
push	hl
push	de
ld	l,c
ld	h,b
pop	bc
or	a
sbc	hl,bc
pop	bc
ex	de,hl
ld	hl,-1
sbc	hl,bc
push	hl
push	de
ld	hl,_linkAddress
call	aslland
l35:
ld	de,(_linkAddress)
ld	hl,(_linkAddress+2)
push	hl
push	de
ld	l,(ix+-26)
ld	h,(ix+-25)
pop	de
ld	(hl),e
inc	hl
ld	(hl),d
inc	hl
pop	bc
ld	(hl),c
inc	hl
ld	(hl),b
ld	e,(ix+-26)
ld	d,(ix+-25)
ld	hl,12
add	hl,de
ld	a,(hl)
inc	hl
or	(hl)
ld	de,(_linkAddress)
ld	hl,(_linkAddress+2)
push	hl
push	de
ld	e,(ix+-26)
ld	d,(ix+-25)
jp	z,L18
ld	hl,12
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
ld	hl,-1
add	hl,bc
ex	de,hl
ld	hl,0
call	lland
ld	a,e
or	d
or	l
or	h
jp	z,l36
ld	e,(ix+-26)
ld	d,(ix+-25)
ld	hl,12
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
push	bc
ld	hl,22
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
ld	hl,6
add	hl,bc
ld	c,(hl)
inc	hl
ld	b,(hl)
push	bc
ld	hl,89f
push	hl
call	_fatal_err
pop	bc
pop	bc
pop	bc
l36:
ld	de,(_linkAddress)
ld	hl,(_linkAddress+2)
push	hl
push	de
ld	e,(ix+-26)
ld	d,(ix+-25)
L18:
ld	hl,14
add	hl,de
ld	e,(hl)
inc	hl
ld	d,(hl)
inc	hl
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
call	lladd
push	hl
push	de
ld	de,(_maxLinkAddress)
ld	hl,(_maxLinkAddress+2)
call	lrelop
jp	nc,l37
ld	de,(_linkAddress)
ld	hl,(_linkAddress+2)
push	hl
push	de
ld	e,(ix+-26)
ld	d,(ix+-25)
ld	hl,14
add	hl,de
ld	e,(hl)
inc	hl
ld	d,(hl)
inc	hl
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
call	lladd
ld	(_maxLinkAddress),de
ld	(_maxLinkAddress+2),hl
l37:
ld	a,(ix+-27)
cp	1
jp	nz,l38
ld	e,(ix+-26)
ld	d,(ix+-25)
ld	hl,14
add	hl,de
ld	e,(hl)
inc	hl
ld	d,(hl)
inc	hl
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
push	hl
push	de
ld	hl,_linkAddress
call	aslladd
l38:
ld	a,(ix+-28)
cp	1
jp	nz,l39
ld	e,(ix+-26)
ld	d,(ix+-25)
ld	hl,12
add	hl,de
ld	a,(hl)
inc	hl
or	(hl)
jp	z,l39
ld	hl,12
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
ld	hl,-1
add	hl,bc
ex	de,hl
ld	hl,0
push	hl
push	de
ld	hl,_loadAddress
call	aslladd
ld	e,(ix+-26)
ld	d,(ix+-25)
ld	hl,12
add	hl,de
ld	e,(hl)
inc	hl
ld	d,(hl)
ld	hl,0
ex	de,hl
ld	bc,-1
add	hl,bc
ex	de,hl
adc	hl,bc
push	hl
push	de
ld	l,c
ld	h,b
pop	bc
or	a
sbc	hl,bc
pop	bc
ex	de,hl
ld	hl,-1
sbc	hl,bc
push	hl
push	de
ld	hl,_loadAddress
call	aslland
l39:
ld	de,(_loadAddress)
ld	hl,(_loadAddress+2)
push	hl
push	de
ld	l,(ix+-26)
ld	h,(ix+-25)
inc	hl
inc	hl
inc	hl
inc	hl
pop	de
ld	(hl),e
inc	hl
ld	(hl),d
inc	hl
pop	bc
ld	(hl),c
inc	hl
ld	(hl),b
ld	e,(ix+-26)
ld	d,(ix+-25)
ld	hl,12
add	hl,de
ld	a,(hl)
inc	hl
or	(hl)
jp	z,l40
ld	de,(_loadAddress)
ld	hl,(_loadAddress+2)
push	hl
push	de
ld	e,(ix+-26)
ld	d,(ix+-25)
ld	hl,12
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
ld	hl,-1
add	hl,bc
ex	de,hl
ld	hl,0
call	lland
ld	a,e
or	d
or	l
or	h
jp	z,l40
ld	e,(ix+-26)
ld	d,(ix+-25)
ld	hl,12
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
push	bc
ld	hl,22
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
ld	hl,6
add	hl,bc
ld	c,(hl)
inc	hl
ld	b,(hl)
push	bc
ld	hl,99f
push	hl
call	_fatal_err
pop	bc
pop	bc
pop	bc
l40:
ld	a,(ix+-28)
cp	1
ld	e,(ix+-26)
ld	d,(ix+-25)
jp	nz,L19
ld	hl,14
add	hl,de
ld	e,(hl)
inc	hl
ld	d,(hl)
inc	hl
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
push	hl
push	de
ld	hl,_loadAddress
call	aslladd
ld	e,(ix+-26)
ld	d,(ix+-25)
L19:
ld	hl,26
add	hl,de
ld	(hl),1
l32:
ld	de,27
ld	l,(ix+-26)
ld	h,(ix+-25)
add	hl,de
ld	(ix+-26),l
ld	(ix+-25),h
l33:
ld	de,(_nextPsect)
ld	l,(ix+-26)
ld	h,(ix+-25)
or	a
sbc	hl,de
jp	nz,l30
l29:
ld	l,(ix+-30)
ld	h,(ix+-29)
ld	a,(hl)
cp	44
jp	nz,L20
inc	hl
ld	(ix+-30),l
ld	(ix+-29),h
jp	l7
L20:
ld	a,(hl)
or	a
jp	z,l6
ld	hl,109f
jp	L25
l45:
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,8
add	hl,de
ld	e,(hl)
inc	hl
ld	d,(hl)
inc	hl
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
ld	a,e
or	d
or	l
or	h
jp	z,l49
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,14
add	hl,de
ld	e,(hl)
inc	hl
ld	d,(hl)
inc	hl
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
push	hl
push	de
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,8
add	hl,de
ld	e,(hl)
inc	hl
ld	d,(hl)
inc	hl
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
call	lrelop
jp	nc,l49
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,22
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
ld	hl,6
add	hl,bc
ld	c,(hl)
inc	hl
ld	b,(hl)
push	bc
ld	hl,119f
push	hl
call	_simpl_err
pop	bc
pop	bc
l49:
ld	a,(_key_R)
or	a
ld	e,(ix+-24)
ld	d,(ix+-23)
jp	z,L21
ld	hl,22
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
ld	hl,8
add	hl,bc
ld	c,(hl)
inc	hl
ld	b,(hl)
bit	6,b
jp	nz,l52
ld	hl,_textRecBuf
push	hl
ld	hl,14
add	hl,de
ld	e,(hl)
inc	hl
ld	d,(hl)
inc	hl
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
push	hl
push	de
call	_conv_u32tob
pop	bc
pop	bc
pop	bc
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,22
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
ld	hl,6
add	hl,bc
ld	c,(hl)
inc	hl
ld	b,(hl)
push	bc
ld	hl,_textRecBuf+4
push	hl
call	_strcpy
pop	bc
ld	hl,_textRecBuf
ex	(sp),hl
ld	hl,_textRecBuf+4
push	hl
call	_strlen
ex	de,hl
ld	hl,5
add	hl,de
ex	(sp),hl
ld	hl,1
push	hl
call	_writeRec
pop	bc
pop	bc
pop	bc
jp	l52
L21:
ld	hl,26
add	hl,de
ld	a,(hl)
or	a
ld	e,(ix+-24)
ld	d,(ix+-23)
jp	nz,L22
ld	hl,24
add	hl,de
ld	a,(hl)
inc	hl
or	(hl)
ld	hl,22
jp	nz,L23
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
ld	hl,8
add	hl,bc
ld	c,(hl)
inc	hl
ld	b,(hl)
bit	6,b
jp	z,l54
ld	hl,_psectInfo
ld	(ix+-26),l
ld	(ix+-25),h
jp	l58
l55:
ld	e,(ix+-26)
ld	d,(ix+-25)
ld	hl,26
add	hl,de
ld	a,(hl)
or	a
jp	nz,l57
ld	hl,24
add	hl,de
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
push	iy
pop	de
or	a
sbc	hl,de
jp	nz,l57
ld	l,(ix+-26)
ld	h,(ix+-25)
push	hl
call	_setPsectOrigin
pop	bc
l57:
ld	de,27
ld	l,(ix+-26)
ld	h,(ix+-25)
add	hl,de
ld	(ix+-26),l
ld	(ix+-25),h
l58:
ld	de,(_nextPsect)
ld	l,(ix+-26)
ld	h,(ix+-25)
or	a
sbc	hl,de
jp	nz,l55
jp	l60
l54:
ld	l,(ix+-24)
ld	h,(ix+-23)
push	hl
call	_setPsectOrigin
pop	bc
l60:
ld	e,(ix+-24)
ld	d,(ix+-23)
L22:
ld	hl,22
L23:
add	hl,de
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
push	hl
pop	iy
ld	de,(_absSym)
or	a
sbc	hl,de
jp	z,l52
ld	de,16
ld	a,(iy+8)
and	16
ld	l,a
ld	a,(iy+9)
and	64
ld	h,a
or	a
sbc	hl,de
jp	nz,l52
ld	l,(iy+6)
ld	h,(iy+7)
push	hl
ld	hl,129f
push	hl
push	ix
pop	de
ld	hl,-20
add	hl,de
push	hl
call	_sprintf
pop	bc
pop	bc
ld	hl,16
ex	(sp),hl
ld	de,0
ld	l,e
ld	h,d
push	hl
push	de
push	iy
push	ix
pop	de
ld	hl,-20
add	hl,de
push	hl
call	_defineIfNeeded
ld	hl,10
add	hl,sp
ld	sp,hl
ld	(ix+-18),72
ld	hl,16
push	hl
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,14
add	hl,de
ld	e,(hl)
inc	hl
ld	d,(hl)
inc	hl
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
push	hl
push	de
push	iy
push	ix
pop	de
ld	hl,-20
add	hl,de
push	hl
call	_defineIfNeeded
ld	hl,10
add	hl,sp
ld	sp,hl
ld	l,(ix+-24)
ld	h,(ix+-23)
ld	e,(hl)
inc	hl
ld	d,(hl)
inc	hl
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
push	hl
push	de
ld	l,(ix+-24)
ld	h,(ix+-23)
inc	hl
inc	hl
inc	hl
inc	hl
ld	e,(hl)
inc	hl
ld	d,(hl)
inc	hl
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
call	lrelop
jp	z,l52
ld	(ix+-18),66
ld	hl,16
push	hl
ld	l,(ix+-24)
ld	h,(ix+-23)
ld	e,(hl)
inc	hl
ld	d,(hl)
inc	hl
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
push	hl
push	de
ld	l,(ix+-24)
ld	h,(ix+-23)
inc	hl
inc	hl
inc	hl
inc	hl
ld	e,(hl)
inc	hl
ld	d,(hl)
inc	hl
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
call	llsub
push	hl
push	de
push	iy
push	ix
pop	de
ld	hl,-20
add	hl,de
push	hl
call	_defineIfNeeded
ld	hl,10
add	hl,sp
ld	sp,hl
l52:
ld	de,0
ld	l,e
ld	h,d
push	hl
push	de
ld	e,(ix+-24)
ld	d,(ix+-23)
ld	hl,14
add	hl,de
pop	de
ld	(hl),e
inc	hl
ld	(hl),d
inc	hl
pop	bc
ld	(hl),c
inc	hl
ld	(hl),b
ld	de,27
ld	l,(ix+-24)
ld	h,(ix+-23)
add	hl,de
ld	(ix+-24),l
ld	(ix+-23),h
l48:
ld	de,(_nextPsect)
ld	l,(ix+-24)
ld	h,(ix+-23)
or	a
sbc	hl,de
jp	nz,l45
ld	a,(_key_R)
or	a
jp	nz,l64
ld	hl,(_cntUnresolved)
ld	a,l
or	h
jp	z,l65
ld	a,(_key_I)
or	a
jp	nz,l65
ld	de,1
or	a
sbc	hl,de
jp	z,L8
ld	hl,115
jp	L7
L8:
ld	hl,0
L7:
push	hl
ld	hl,139f
push	hl
call	_simpl_err
pop	bc
pop	bc
l65:
ld	hl,(_symbol_table)
ld	(ix+-22),l
ld	(ix+-21),h
jp	l69
l66:
ld	l,(ix+-22)
ld	h,(ix+-21)
ld	c,(hl)
inc	hl
ld	b,(hl)
push	bc
pop	iy
ld	a,c
or	b
jp	z,l68
xor	a
ld	l,a
ld	a,(iy+9)
and	192
ld	h,a
ld	a,l
or	h
jp	nz,l68
ld	de,6
ld	a,(iy+8)
and	15
ld	l,a
xor	a
ld	h,a
or	a
sbc	hl,de
jp	nz,l71
ld	a,(_key_I)
or	a
jp	nz,l68
ld	l,(iy+6)
ld	h,(iy+7)
push	hl
ld	hl,149f
push	hl
call	_simpl_err
pop	bc
pop	bc
jp	l68
l71:
ld	e,(iy+4)
ld	d,(iy+5)
ld	hl,8
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
bit	7,c
jp	nz,l68
ld	de,2
ld	a,(iy+8)
and	15
ld	l,a
xor	a
ld	h,a
or	a
sbc	hl,de
jp	z,l68
ld	l,(iy+4)
ld	h,(iy+5)
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
ld	e,(hl)
inc	hl
ld	d,(hl)
inc	hl
ld	a,(hl)
inc	hl
ld	h,(hl)
ld	l,a
push	hl
push	de
push	iy
pop	hl
call	aslladd
l68:
ld	l,(ix+-22)
ld	h,(ix+-21)
inc	hl
inc	hl
ld	(ix+-22),l
ld	(ix+-21),h
l69:
ld	de,(_symbol_table)
ld	hl,1994
add	hl,de
ld	e,(ix+-22)
ld	d,(ix+-21)
or	a
sbc	hl,de
jp	nz,l66
l64:
ld	a,(_key_S)
or	a
jp	nz,cret
ld	hl,(_symbol_table)
ld	(ix+-22),l
ld	(ix+-21),h
jp	l79
l76:
ld	l,(ix+-22)
ld	h,(ix+-21)
ld	c,(hl)
inc	hl
ld	b,(hl)
push	bc
pop	iy
ld	a,c
or	b
jp	z,l78
bit	7,(iy+9)
jp	z,l81
ld	a,(_key_C)
or	a
jp	nz,l78
call	_wrRecord
ld	hl,_nonTextRecBuf+2
ld	(hl),2
ld	hl,(_nonTextRecPtr)
push	hl
ld	a,(_key_R)
or	a
jp	nz,L6
ld	hl,128
jp	L5
L6:
ld	hl,0
L5:
ex	de,hl
ld	l,(iy+8)
ld	a,(iy+9)
and	127
ld	h,a
ld	a,l
or	e
ld	l,a
ld	a,h
or	d
ld	h,a
push	hl
call	_conv_u16tob
pop	bc
pop	bc
ld	l,(iy+6)
ld	h,(iy+7)
push	hl
ld	hl,(_nonTextRecPtr)
inc	hl
inc	hl
push	hl
call	_strcpy
pop	bc
ld	l,(iy+6)
ld	h,(iy+7)
ex	(sp),hl
call	_strlen
pop	bc
ld	e,l
ld	d,h
inc	de
inc	de
inc	de
ld	hl,(_nonTextRecPtr)
add	hl,de
ld	(_nonTextRecPtr),hl
jp	l78
l81:
bit	6,(iy+9)
jp	nz,l78
ld	a,(_key_X)
or	a
jp	z,L3
bit	4,(iy+8)
jp	z,l78
L3:
ld	a,(_key_Z)
or	a
jp	z,L1
ld	l,(iy+6)
ld	h,(iy+7)
push	hl
call	_isLocalName
pop	bc
ld	a,l
or	a
jp	nz,l78
L1:
push	iy
call	_wrSymbol
pop	bc
l78:
ld	l,(ix+-22)
ld	h,(ix+-21)
inc	hl
inc	hl
ld	(ix+-22),l
ld	(ix+-21),h
l79:
ld	de,(_symbol_table)
ld	hl,1994
add	hl,de
ld	e,(ix+-22)
ld	d,(ix+-21)
or	a
sbc	hl,de
jp	nz,l76
ld	a,(_key_H)
or	a
jp	z,cret
ld	hl,159f
push	hl
ld	hl,(_symFp)
push	hl
call	_fprintf
jp	cret
psect	data
19:
defb	98,97,100,32,39,45,112,39,32,102,111,114,109,97,116,0
29:
defb	117,110,107,110,111,119,110,32,112,115,101,99,116,58,32,37
defb	115,0
39:
defb	112,115,101,99,116,32,105,115,32,97,98,115,111,108,117,116
defb	101,58,32,37,115,0
49:
defb	112,115,101,99,116,32,111,114,105,103,105,110,32,109,117,108
defb	116,105,112,108,121,32,100,101,102,105,110,101,100,58,32,37
defb	115,0
59:
defb	98,97,100,32,111,114,105,103,105,110,32,102,111,114,109,97
defb	116,32,105,110,32,115,112,101,99,0
69:
defb	80,115,101,99,116,32,37,115,32,110,111,116,32,114,101,108
defb	111,99,97,116,101,100,32,111,110,32,48,120,37,120,32,98
defb	111,117,110,100,97,114,121,0
79:
defb	80,115,101,99,116,32,37,115,32,110,111,116,32,108,111,97
defb	100,101,100,32,111,110,32,48,120,37,120,32,98,111,117,110
defb	100,97,114,121,32,0
89:
defb	80,115,101,99,116,32,37,115,32,110,111,116,32,114,101,108
defb	111,99,97,116,101,100,32,111,110,32,48,120,37,120,32,98
defb	111,117,110,100,97,114,121,0
99:
defb	80,115,101,99,116,32,37,115,32,110,111,116,32,108,111,97
defb	100,101,100,32,111,110,32,48,120,37,120,32,98,111,117,110
defb	100,97,114,121,32,0
109:
defb	98,97,100,32,39,45,112,39,32,102,111,114,109,97,116,0
119:
defb	112,115,101,99,116,32,101,120,99,101,101,100,115,32,109,97
defb	120,32,115,105,122,101,58,32,37,115,0
129:
defb	95,95,76,37,115,0
139:
defb	117,110,100,101,102,105,110,101,100,32,115,121,109,98,111,108
defb	37,99,58,0
149:
defb	37,115,0
159:
defb	37,37,108,111,99,97,108,115,10,0
psect	text
