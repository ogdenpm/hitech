global	_nonTextRecPtr
psect	data
_nonTextRecPtr:
global	_nonTextRecBuf
defw	_nonTextRecBuf+3
global	_order32
_order32:
defb	0
defb	1
defb	2
defb	3
global	_order16
_order16:
defb	0
defb	1
global	_libHandlers
_libHandlers:
global	_libPass1
defw	_libPass1
global	_libPass2
defw	_libPass2
global	_usageMsg
_usageMsg:
defb	85
defb	115
defb	97
defb	103
defb	101
defb	58
defb	32
defb	108
defb	105
defb	110
defb	107
defb	32
defb	91
defb	45
defb	99
defb	98
defb	97
defb	115
defb	101
defb	93
defb	91
defb	45
defb	100
defb	115
defb	121
defb	109
defb	102
defb	105
defb	108
defb	101
defb	93
defb	91
defb	45
defb	114
defb	93
defb	91
defb	45
defb	110
defb	93
defb	91
defb	45
defb	115
defb	93
defb	91
defb	45
defb	120
defb	93
defb	91
defb	45
defb	122
defb	93
defb	91
defb	45
defb	111
defb	111
defb	102
defb	105
defb	108
defb	101
defb	93
defb	91
defb	45
defb	112
defb	115
defb	112
defb	101
defb	99
defb	93
defb	91
defb	45
defb	109
defb	109
defb	97
defb	112
defb	93
defb	123
defb	45
defb	117
defb	115
defb	121
defb	109
defb	125
defb	91
defb	45
defb	119
defb	119
defb	105
defb	100
defb	116
defb	104
defb	93
defb	32
defb	105
defb	110
defb	112
defb	117
defb	116
defb	32
defb	46
defb	46
defb	46
defb	0
global	_moduleFp
_moduleFp:
global	__iob
defw	__iob
global	_width
_width:
defw	80
global	_rec_types
_rec_types:
defw	19f
defw	29f
defw	39f
defw	49f
defw	59f
defw	69f
defw	79f
defw	89f
defw	99f
global	_recHandler
_recHandler:
defw	0
defw	0
global	_textRecPass1
defw	_textRecPass1
global	_textRecPass2
defw	_textRecPass2
global	_psectRecPass1
defw	_psectRecPass1
global	_skipRecData
defw	_skipRecData
global	_relocRecPass1
defw	_relocRecPass1
global	_relocRecPass2
defw	_relocRecPass2
global	_symRecPass1
defw	_symRecPass1
global	_symRecPass2
defw	_symRecPass2
defw	_skipRecData
global	_startRecPass2
defw	_startRecPass2
global	_endRecPass1
defw	_endRecPass1
global	_endRecPass2
defw	_endRecPass2
global	_identRecPass1
defw	_identRecPass1
defw	_skipRecData
global	_xpsectRecPass1
defw	_xpsectRecPass1
defw	_skipRecData
global	_finPassHandler
_finPassHandler:
global	_finPass1
defw	_finPass1
global	_finPass2
defw	_finPass2
global	_nextPsect
_nextPsect:
global	_psectInfo
defw	_psectInfo
global	_err_write
global	ncsv, cret, indir
global	_fatal_err
global	_fname_outp
psect	text
_err_write:
ld	hl,(_fname_outp)
push	hl
ld	hl,109f
push	hl
call	_fatal_err
pop	bc
pop	bc
ret	
global	_readRecData
global	_recbuf
global	_haveIdent
global	_badFormat
global	brelop
global	brelop
global	brelop
global	brelop
global	_key_M
global	_printf
global	_key_C
global	_writeRec
global	_length
_identRecPass1:
global csv
call csv
push hl
ld	hl,_recbuf
push	hl
call	_readRecData
pop	bc
ld	a,(_haveIdent)
or	a
ld	(ix+-1),0
jp	z,l21
jp	l11
l8:
ld	e,(ix+-1)
ld	d,0
ld	hl,_recbuf
add	hl,de
ld	a,(hl)
ld	hl,_order32
add	hl,de
cp	(hl)
jp	z,l10
ld	hl,119f
push	hl
call	_badFormat
pop	bc
l10:
inc	(ix+-1)
l11:
ld	b,4
ld	a,(ix+-1)
call	brelop
jp	c,l8
ld	(ix+-1),0
jp	l16
l13:
ld	e,(ix+-1)
ld	d,0
ld	hl,_recbuf+4
add	hl,de
ld	a,(hl)
ld	hl,_order16
add	hl,de
cp	(hl)
jp	z,l15
ld	hl,129f
push	hl
call	_badFormat
pop	bc
l15:
inc	(ix+-1)
l16:
ld	b,2
ld	a,(ix+-1)
call	brelop
jp	c,l13
jp	cret
l18:
ld	e,(ix+-1)
ld	d,0
ld	hl,_recbuf
add	hl,de
ld	a,(hl)
ld	hl,_order32
add	hl,de
ld	(hl),a
inc	(ix+-1)
l21:
ld	b,4
ld	a,(ix+-1)
call	brelop
jp	c,l18
ld	(ix+-1),0
jp	l25
l22:
ld	e,(ix+-1)
ld	d,0
ld	hl,_recbuf+4
add	hl,de
ld	a,(hl)
ld	hl,_order16
add	hl,de
ld	(hl),a
inc	(ix+-1)
l25:
ld	b,2
ld	a,(ix+-1)
call	brelop
jp	c,l22
ld	a,1
ld	(_haveIdent),a
ld	a,(_key_M)
or	a
jp	z,l26
ld	hl,_recbuf+6
push	hl
ld	hl,139f
push	hl
call	_printf
pop	bc
pop	bc
l26:
ld	a,(_key_C)
or	a
jp	nz,cret
ld	hl,_recbuf
push	hl
ld	hl,(_length)
push	hl
ld	hl,7
push	hl
call	_writeRec
jp	cret
global	_readRecHdr
global	_fread
global	_numRecord
global	shll
global	_rectyp
global	wrelop
global	brelop
global	wrelop
_readRecHdr:
ld	hl,(_moduleFp)
push	hl
ld	hl,1
push	hl
ld	hl,3
push	hl
ld	hl,_recbuf
push	hl
call	_fread
pop	bc
pop	bc
pop	bc
pop	bc
ld	de,1
or	a
sbc	hl,de
jp	z,l29
ld	hl,149f
push	hl
call	_badFormat
pop	bc
l29:
ld	hl,(_numRecord)
inc	hl
ld	(_numRecord),hl
ld	a,(_recbuf)
ld	e,a
ld	d,0
ld	b,8
ld	hl,_recbuf+1
ld	l,(hl)
ld	h,d
call	shll
add	hl,de
ld	(_length),hl
ld	hl,_recbuf+2
ld	a,(hl)
ld	(_rectyp),a
ld	e,a
ld	d,0
ld	hl,0
call	wrelop
jp	nc,L2
ld	b,9
ld	a,(_rectyp)
call	brelop
jp	c,l30
L2:
ld	a,(_rectyp)
ld	l,a
ld	h,0
push	hl
ld	hl,159f
push	hl
call	_badFormat
pop	bc
pop	bc
l30:
ld	de,(_length)
ld	hl,509
call	wrelop
ret	nc
ld	hl,(_length)
push	hl
ld	hl,3
push	hl
ld	hl,169f
push	hl
call	_badFormat
pop	bc
pop	bc
pop	bc
ret	
_readRecData:
global csv
call csv
ld	hl,(_moduleFp)
push	hl
ld	hl,(_length)
push	hl
ld	hl,1
push	hl
ld	l,(ix+6)
ld	h,(ix+7)
push	hl
call	_fread
pop	bc
pop	bc
pop	bc
pop	bc
ld	de,(_length)
or	a
sbc	hl,de
jp	z,cret
ld	l,e
ld	h,d
push	hl
ld	de,_rec_types
ld	hl,_recbuf+2
ld	l,(hl)
ld	h,0
add	hl,hl
add	hl,de
ld	c,(hl)
inc	hl
ld	b,(hl)
push	bc
ld	hl,179f
push	hl
call	_badFormat
jp	cret
global	_conv_i16tole
global	_fwrite
global	_outFp
_writeRec:
global csv
call csv
push hl
push hl
ld	a,(ix+6)
ld	(ix+-1),a
push	ix
pop	hl
dec	hl
dec	hl
dec	hl
push	hl
ld	l,(ix+8)
ld	h,(ix+9)
push	hl
call	_conv_i16tole
pop	bc
pop	bc
ld	hl,(_outFp)
push	hl
ld	hl,1
push	hl
ld	hl,3
push	hl
push	ix
pop	hl
dec	hl
dec	hl
dec	hl
push	hl
call	_fwrite
pop	bc
pop	bc
pop	bc
pop	bc
ld	de,1
or	a
sbc	hl,de
jp	nz,l35
ld	hl,(_outFp)
push	hl
ld	l,(ix+8)
ld	h,(ix+9)
push	hl
ld	l,e
ld	h,d
push	hl
ld	l,(ix+10)
ld	h,(ix+11)
push	hl
call	_fwrite
pop	bc
pop	bc
pop	bc
pop	bc
ld	e,(ix+8)
ld	d,(ix+9)
or	a
sbc	hl,de
jp	z,cret
l35:
call	_err_write
jp	cret
global	_writeText
global	_curAddr
global	_textRecPtr
global	_endAddr
global	wrelop
global	wrelop
global	_strlen
global	_textRecBuf
global	_targetAddress
global	_conv_btou32
global	_offset_address
global	lrelop
global	_fseek
global	llsub
global	_conv_u32tob
global	lladd
global	_alreadyWritten
_writeText:
call ncsv
defw -7
ld	de,(_textRecPtr)
ld	hl,(_curAddr)
call	wrelop
jp	c,cret
ld	de,(_endAddr)
ld	hl,(_curAddr)
call	wrelop
jp	nc,cret
ld	hl,_textRecBuf+4
push	hl
call	_strlen
pop	bc
ex	de,hl
ld	hl,5
add	hl,de
ld	(ix+-5),l
ld	(ix+-4),h
ld	de,(_curAddr)
ld	hl,(_endAddr)
or	a
sbc	hl,de
ld	(ix+-7),l
ld	(ix+-6),h
push	ix
pop	hl
dec	hl
dec	hl
dec	hl
push	hl
ld	e,(ix+-7)
ld	d,(ix+-6)
ld	l,(ix+-5)
ld	h,(ix+-4)
add	hl,de
push	hl
call	_conv_i16tole
pop	bc
pop	bc
ld	(ix+-1),1
ld	a,(_key_C)
or	a
jp	z,l38
ld	hl,_textRecBuf
push	hl
call	_conv_btou32
pop	bc
ld	(_targetAddress),de
ld	(_targetAddress+2),hl
ld	de,(_offset_address)
ld	hl,(_offset_address+2)
push	hl
push	de
ld	de,(_targetAddress)
ld	hl,(_targetAddress+2)
call	lrelop
jp	nc,l39
ld	de,(_offset_address)
ld	hl,(_offset_address+2)
push	hl
push	de
ld	hl,189f
push	hl
call	_fatal_err
pop	bc
pop	bc
pop	bc
l39:
ld	hl,0
push	hl
ld	de,(_offset_address)
ld	hl,(_offset_address+2)
push	hl
push	de
ld	de,(_targetAddress)
ld	hl,(_targetAddress+2)
call	llsub
push	hl
push	de
ld	hl,(_outFp)
push	hl
call	_fseek
pop	bc
pop	bc
pop	bc
pop	bc
ld	de,-1
or	a
sbc	hl,de
jp	nz,l40
ld	hl,(_fname_outp)
push	hl
ld	hl,199f
push	hl
call	_fatal_err
pop	bc
pop	bc
l40:
ld	hl,(_outFp)
push	hl
ld	l,(ix+-7)
ld	h,(ix+-6)
push	hl
ld	hl,1
push	hl
ld	hl,(_curAddr)
push	hl
call	_fwrite
pop	bc
pop	bc
pop	bc
pop	bc
ld	e,(ix+-7)
ld	d,(ix+-6)
or	a
sbc	hl,de
jp	z,l42
call	_err_write
jp	l42
l38:
ld	hl,(_outFp)
push	hl
ld	hl,1
push	hl
ld	hl,3
push	hl
push	ix
pop	hl
dec	hl
dec	hl
dec	hl
push	hl
call	_fwrite
pop	bc
pop	bc
pop	bc
pop	bc
ld	de,1
or	a
sbc	hl,de
jp	nz,L4
ld	hl,(_outFp)
push	hl
ld	l,(ix+-5)
ld	h,(ix+-4)
push	hl
ld	l,e
ld	h,d
push	hl
ld	hl,_textRecBuf
push	hl
call	_fwrite
pop	bc
pop	bc
pop	bc
pop	bc
ld	e,(ix+-5)
ld	d,(ix+-4)
or	a
sbc	hl,de
jp	nz,L4
ld	hl,(_outFp)
push	hl
ld	l,(ix+-7)
ld	h,(ix+-6)
push	hl
ld	hl,1
push	hl
ld	hl,(_curAddr)
push	hl
call	_fwrite
pop	bc
pop	bc
pop	bc
pop	bc
ld	e,(ix+-7)
ld	d,(ix+-6)
or	a
sbc	hl,de
jp	z,l42
L4:
call	_err_write
l42:
ld	hl,_textRecBuf
push	hl
ld	e,(ix+-7)
ld	d,(ix+-6)
ld	hl,0
push	hl
push	de
ld	hl,_textRecBuf
push	hl
call	_conv_btou32
pop	bc
call	lladd
push	hl
push	de
call	_conv_u32tob
ld	hl,(_endAddr)
ld	(_curAddr),hl
ld	e,(ix+-7)
ld	d,(ix+-6)
ld	hl,(_alreadyWritten)
add	hl,de
ld	(_alreadyWritten),hl
jp	cret
global	_flushText
global	_textLen
_flushText:
ld	de,(_textRecPtr)
ld	hl,(_textLen)
add	hl,de
ld	(_endAddr),hl
jp	_writeText
global	_wrRecord
_wrRecord:
global csv
call csv
push hl
ld	de,_nonTextRecBuf
ld	hl,(_nonTextRecPtr)
or	a
sbc	hl,de
ld	(ix+-2),l
ld	(ix+-1),h
ld	hl,_nonTextRecBuf+2
ld	a,(hl)
or	a
jp	z,cret
ld	de,3
ld	l,(ix+-2)
ld	h,(ix+-1)
or	a
sbc	hl,de
jp	z,cret
ld	hl,_nonTextRecBuf+2
ld	a,(hl)
cp	3
call	z,_writeText
ld	hl,_nonTextRecBuf
push	hl
ld	l,(ix+-2)
ld	h,(ix+-1)
dec	hl
dec	hl
dec	hl
push	hl
call	_conv_i16tole
pop	bc
ld	hl,(_outFp)
ex	(sp),hl
ld	l,(ix+-2)
ld	h,(ix+-1)
push	hl
ld	hl,1
push	hl
ld	hl,_nonTextRecBuf
push	hl
call	_fwrite
pop	bc
pop	bc
pop	bc
pop	bc
ld	e,(ix+-2)
ld	d,(ix+-1)
or	a
sbc	hl,de
call	nz,_err_write
ld	hl,_nonTextRecBuf+2
ld	(hl),0
ld	hl,_nonTextRecBuf+3
ld	(_nonTextRecPtr),hl
jp	cret
global	_chkAddRecordItem
global	wrelop
_chkAddRecordItem:
global csv
call csv
ld	hl,_nonTextRecBuf+2
ld	a,(hl)
cp	(ix+6)
jp	nz,l50
ld	de,(_nonTextRecPtr)
ld	l,(ix+8)
ld	h,(ix+9)
add	hl,de
ex	de,hl
ld	hl,_nonTextRecBuf+512
call	wrelop
jp	nc,cret
l50:
call	_wrRecord
ld	a,(ix+6)
ld	hl,_nonTextRecBuf+2
ld	(hl),a
jp	cret
global	shar
_conv_i16tole:
global csv
call csv
ld	a,(ix+6)
ld	l,(ix+8)
ld	h,(ix+9)
ld	(hl),a
ld	b,8
ld	l,a
ld	h,(ix+7)
call	shar
ld	a,l
ld	l,(ix+8)
ld	h,(ix+9)
inc	hl
ld	(hl),a
jp	cret
global	_conv_letoi16
global	shll
_conv_letoi16:
global csv
call csv
ld	l,(ix+6)
ld	h,(ix+7)
push	hl
pop	iy
push	hl
pop	de
ld	a,(_order16)
ld	l,a
ld	h,0
add	hl,de
ld	e,(hl)
ld	d,0
push	de
ld	b,8
push	iy
pop	de
ld	hl,_order16+1
ld	l,(hl)
ld	h,0
add	hl,de
ld	l,(hl)
ld	h,0
call	shll
pop	de
add	hl,de
jp	cret
global	_conv_u16tob
global	shlr
_conv_u16tob:
global csv
call csv
ld	l,(ix+8)
ld	h,(ix+9)
push	hl
pop	iy
push	hl
pop	de
ld	a,(_order16)
ld	l,a
ld	h,0
add	hl,de
ld	a,(ix+6)
ld	(hl),a
ld	b,8
ld	l,a
ld	h,(ix+7)
call	shlr
ld	a,l
push	iy
pop	de
ld	hl,_order16+1
ld	l,(hl)
ld	h,0
add	hl,de
ld	(hl),a
jp	cret
global	lllsh
global	aslladd
global	wrelop
_conv_btou32:
call ncsv
defw -5
ld	l,(ix+6)
ld	h,(ix+7)
push	hl
pop	iy
ld	(ix+-5),4
ld	(ix+-4),0
ld	(ix+-3),0
ld	(ix+-2),0
ld	(ix+-1),0
jp	l55
l56:
ld	a,(ix+-5)
ld	l,a
rla
sbc	a,a
ld	h,a
add	hl,hl
add	hl,hl
add	hl,hl
ex	de,hl
ld	b,e
ld	a,(ix+-5)
ld	e,a
rla
sbc	a,a
ld	d,a
ld	hl,_order32
add	hl,de
ld	l,(hl)
ld	h,0
push	iy
pop	de
add	hl,de
ld	e,(hl)
ld	d,0
ld	hl,0
call	lllsh
push	hl
push	de
push	ix
pop	hl
dec	hl
dec	hl
dec	hl
dec	hl
call	aslladd
l55:
ld	a,(ix+-5)
dec	(ix+-5)
ld	e,a
rla
sbc	a,a
ld	d,a
ld	hl,0
call	wrelop
jp	m,l56
ld	e,(ix+-4)
ld	d,(ix+-3)
ld	l,(ix+-2)
ld	h,(ix+-1)
jp	cret
global	asllrsh
global	brelop
_conv_u32tob:
global csv
call csv
push hl
ld	l,(ix+10)
ld	h,(ix+11)
push	hl
pop	iy
ld	(ix+-1),0
jp	l62
l59:
ld	a,(ix+6)
ld	e,(ix+-1)
ld	d,0
ld	hl,_order32
add	hl,de
ld	l,(hl)
ld	h,d
push	iy
pop	de
add	hl,de
ld	(hl),a
ld	b,8
push	ix
pop	de
ld	hl,6
add	hl,de
call	asllrsh
inc	(ix+-1)
l62:
ld	b,4
ld	a,(ix+-1)
call	brelop
jp	c,l59
jp	cret
global	_conv_btou24
global	lllsh
global	aslladd
global	wrelop
_conv_btou24:
call ncsv
defw -5
ld	l,(ix+6)
ld	h,(ix+7)
push	hl
pop	iy
ld	(ix+-5),3
ld	(ix+-4),0
ld	(ix+-3),0
ld	(ix+-2),0
ld	(ix+-1),0
jp	l64
l65:
ld	a,(ix+-5)
ld	l,a
rla
sbc	a,a
ld	h,a
add	hl,hl
add	hl,hl
add	hl,hl
ex	de,hl
ld	b,e
ld	a,(ix+-5)
ld	e,a
rla
sbc	a,a
ld	d,a
ld	hl,_order32
add	hl,de
ld	l,(hl)
ld	h,0
push	iy
pop	de
add	hl,de
ld	e,(hl)
ld	d,0
ld	hl,0
call	lllsh
push	hl
push	de
push	ix
pop	hl
dec	hl
dec	hl
dec	hl
dec	hl
call	aslladd
l64:
ld	a,(ix+-5)
dec	(ix+-5)
ld	e,a
rla
sbc	a,a
ld	d,a
ld	hl,0
call	wrelop
jp	m,l65
ld	e,(ix+-4)
ld	d,(ix+-3)
ld	l,(ix+-2)
ld	h,(ix+-1)
jp	cret
global	_conv_u24tob
global	asllrsh
global	brelop
_conv_u24tob:
global csv
call csv
push hl
ld	l,(ix+10)
ld	h,(ix+11)
push	hl
pop	iy
ld	(ix+-1),0
jp	l71
l68:
ld	a,(ix+6)
ld	e,(ix+-1)
ld	d,0
ld	hl,_order32
add	hl,de
ld	l,(hl)
ld	h,d
push	iy
pop	de
add	hl,de
ld	(hl),a
ld	b,8
push	ix
pop	de
ld	hl,6
add	hl,de
call	asllrsh
inc	(ix+-1)
l71:
ld	b,3
ld	a,(ix+-1)
call	brelop
jp	c,l68
jp	cret
psect	data
19:
defb	0
29:
defb	84,69,88,84,0
39:
defb	80,83,69,67,84,0
49:
defb	82,69,76,79,67,0
59:
defb	83,89,77,0
69:
defb	83,84,65,82,84,0
79:
defb	69,78,68,0
89:
defb	73,68,69,78,84,0
99:
defb	88,80,83,69,67,84,0
109:
defb	37,115,58,32,87,114,105,116,101,32,101,114,114,111,114,32
defb	40,111,117,116,32,111,102,32,100,105,115,107,32,115,112,97
defb	99,101,63,41,0
119:
defb	105,100,101,110,116,32,114,101,99,111,114,100,115,32,100,111
defb	32,110,111,116,32,109,97,116,99,104,0
129:
defb	105,100,101,110,116,32,114,101,99,111,114,100,115,32,100,111
defb	32,110,111,116,32,109,97,116,99,104,0
139:
defb	77,97,99,104,105,110,101,32,116,121,112,101,32,105,115,32
defb	37,115,10,10,0
149:
defb	110,111,32,101,110,100,32,114,101,99,111,114,100,32,102,111
defb	117,110,100,0
159:
defb	117,110,107,110,111,119,110,32,114,101,99,111,114,100,32,116
defb	121,112,101,58,32,37,100,0
169:
defb	114,101,99,111,114,100,32,116,111,111,32,117,105,110,116,51
defb	50,95,116,58,32,37,100,43,37,100,0
179:
defb	105,110,99,111,109,112,108,101,116,101,32,37,115,32,114,101
defb	99,111,114,100,32,98,111,100,121,58,32,108,101,110,103,116
defb	104,32,61,32,37,100,0
189:
defb	109,111,100,117,108,101,32,104,97,115,32,99,111,100,101,32
defb	98,101,108,111,119,32,102,105,108,101,32,98,97,115,101,32
defb	111,102,32,48,37,108,120,104,0
199:
defb	37,115,58,32,83,101,101,107,32,101,114,114,111,114,0
global	_newSymCnt
psect	bss
_newSymCnt:
defs	2
global	_symSize
_symSize:
defs	2
_outFp:
defs	2
global	_linker_pass
_linker_pass:
defs	1
global	_libraryName
_libraryName:
defs	2
_textLen:
defs	2
global	_fname_sym
_fname_sym:
defs	2
global	_symbol_table
_symbol_table:
defs	2
global	_libTable
_libTable:
defs	2
_rectyp:
defs	1
global	_maxLinkAddress
_maxLinkAddress:
defs	4
_endAddr:
defs	2
_fname_outp:
defs	2
global	_cntUnresolved
_cntUnresolved:
defs	2
global	_absSym
_absSym:
defs	2
_numRecord:
defs	2
_alreadyWritten:
defs	2
_psectInfo:
defs	540
global	_fixupName
_fixupName:
defs	2
global	_psect_location
_psect_location:
defs	2
_recbuf:
defs	512
_key_C:
defs	1
global	_saveLoadAddress
_saveLoadAddress:
defs	4
global	_symCnt
_symCnt:
defs	2
global	_size_symbols
_size_symbols:
defs	2
global	_libraryFp
_libraryFp:
defs	2
global	_key_H
_key_H:
defs	1
global	_key_I
_key_I:
defs	1
global	_key_L
_key_L:
defs	1
global	_moduleLoaded
_moduleLoaded:
defs	1
_curAddr:
defs	2
_key_M:
defs	1
global	_key_N
_key_N:
defs	1
global	_loadAddress
_loadAddress:
defs	4
global	_fname_map
_fname_map:
defs	2
_length:
defs	2
global	_key_R
_key_R:
defs	1
global	_key_S
_key_S:
defs	1
global	_fname_obj
_fname_obj:
defs	2
global	_num_lib_files
_num_lib_files:
defs	2
global	_key_X
_key_X:
defs	1
_textRecPtr:
defs	2
global	_key_Z
_key_Z:
defs	1
global	_moduleSize
_moduleSize:
defs	4
global	_symFp
_symFp:
defs	2
global	_key_LM
_key_LM:
defs	1
_nonTextRecBuf:
defs	512
global	_libBuf
_libBuf:
defs	100
_haveIdent:
defs	1
_offset_address:
defs	4
global	_haveEntryPt
_haveEntryPt:
defs	1
global	_moduleNeeded
_moduleNeeded:
defs	1
global	_err_num
_err_num:
defs	2
global	_num_files
_num_files:
defs	2
_targetAddress:
defs	4
global	_num_modules
_num_modules:
defs	2
global	_linkAddress
_linkAddress:
defs	4
_textRecBuf:
defs	512
global	_curFileId
_curFileId:
defs	2
global	_textBaseAddress
_textBaseAddress:
defs	4
psect	text
