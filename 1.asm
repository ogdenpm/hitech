*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 1.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; Data from file 1.asm
;=========================================================
	global	_buffer,     _lineno,     _progname,   _byte_AE0C, _cursect
	global	_word_AE0F,  _word_AE11,  _array_AE13, _word_AE53, _nstdpth
	global	_array_AE57, _array_AE97, _word_AED7,  _word_AED9, _array_AEDB
	global	_word_AF1B,  _word_AF1D,  _hashtab,    _word_AFE9, _lvlidx
	global	_word_AFEF,  _word_AFF1,  _byte_AFF3,  _word_AFF4, _word_AFF6
	global	_word_AFED,  _word_AFF8,  _byte_AFFA,  _word_AFFB, _array_AFFD
	global	_word_B011,  _byte_B013,  _byte_B014,  _word_B015, _word_B017
	global	_wflag,      _pflag,      _hflag,      _errcnt,    _bflag
	global	_beg_sbrk,   _eflag,      _rflag,      _word_B023

	psect	bss

;Source				;Change	name	;Base			;Current
;--------------------------	;-----------	;-----------------      ;----------------
_buffer:	defs	60			;ADA6 buffer	  	;ADA6 _buffer
_lineno:	defs	2			;ADE2 _lineno	  	;ADE2 _lineno
_progname:	defs	40			;ADE4 _progname		;ADE4 _progname
_byte_AE0C:	defs	1			;AE0C _byte_AE0C	;AE0C _byte_AE0C
_cursect:	defs	2	; AE0D		;AE0D _word_AE0D	;AE0D _cursect
_word_AE0F:	defs	2			;AE0F _word_AE0F	;AE0F _word_AE0F
_word_AE11:	defs	2			;AE11 _word_AE11	;AE11 _word_AE11
_array_AE13:	defs	64			;AE13 _array_AE13	;AE13 _array_AE13
_word_AE53:	defs	2			;AE53 _word_AE53	;AE53 _word_AE53
_nstdpth:	defs	2	; AE55		;AE55 _word_AE55	;AE55 _nstdpth
_array_AE57:	defs	64			;AE57 _array_AE57	;AE57 _array_AE57
_array_AE97:	defs	64			;AE97 _array_AE97	;AE97 _array_AE97
_word_AED7:	defs	2			;AED7 _word_AED7	;AED7 _word_AED7
_word_AED9:	defs	2			;AED9 _word_AED9	;AED9 _word_AED9
_array_AEDB:	defs	64			;AEDB _array_AEDB	;AEDB _array_AEDB
_word_AF1B:	defs	2			;AF1B _word_AF1B	;AF1B _word_AF1B
_word_AF1D:	defs	2			;AF1D _word_AF1D	;AF1D _word_AF1D
_hashtab:	defs	202	; AF1F		;AF1F _array_AF1F	;AF1F _hashtab
_word_AFE9:	defs	2			;AFE9 _word_AFE9	;AFE9 _word_AFE9
_lvlidx:	defs	2	; AFEB		;AFEB _word_AFEB	;AFEB _lvlidx
_word_AFED:	defs	2			;AFED _word_AFED	;AFED _word_AFEF
_word_AFEF:	defs	2			;AFEF _word_AFEF	;AFEF _word_AFF1
_word_AFF1:	defs	2			;AFF1 _word_AFF1	;AFF1 _byte_AFF3
_byte_AFF3:	defs	1			;AFF3 _byte_AFF3	;AFF2 _word_AFF4
_word_AFF4:	defs	2			;AFF4 _word_AFF4	;AFF4 _word_AFF6
_word_AFF6:	defs	2			;AFF6 _word_AFF6	;AFF6 _word_AFED
_word_AFF8:	defs	2			;AFF8 _word_AFF8	;AFF8 _word_AFF8
_byte_AFFA:	defs	1			;AFFA _byte_AFFA	;AFFA _byte_AFFA
_word_AFFB:	defs	2			;AFFB _word_AFFB	;AFFB _word_AFFB
_array_AFFD:	defs	014h			;AFFD _array_AFFD	;AFFD _array_AFFD
_word_B011:	defs	2			;B011 _word_B011	;B025 _word_B011
_byte_B013:	defs	1			;B013 _byte_B013	;B027 _byte_B013
_byte_B014:	defs	1			;B014 _byte_B014	;B028 _byte_B014
_word_B015:	defs	2			;B015 _word_B015	;B029 _word_B015
_word_B017:	defs	2			;B017 _word_B017	;B02B _word_B017
_wflag:		defs	1			;B019 _wflag	  	;B019 _wflag
_pflag:		defs	1			;B01A _pflag	  	;B01A _pflag
_hflag:		defs	1			;B01B _hflag	  	;B01B _hflag
_errcnt:	defs	2	; BO1C		;B01C _word_B01C	;B01C _errcnt
_bflag:		defs	1			;B01E _bflag	  	;B01E _bflag
_beg_sbrk:	defs	2			;B01F _beg_sbrk		;B01F _beg_sbrk
_eflag:		defs	1			;B021 _eflag	  	;B021 _eflag
_rflag:		defs	1			;B022 _rflag	  	;B022 _rflag
_word_B023:	defs	3			;B023		  	;B023 _word_B023
;
;Source				;Change	name	;Base			;Current
;--------------------------	;-----------	;-----------------      ;----------------
;					     /	;B026 spf		;B026 _spf
;					    ;	;B02E _byte_B02E	;B02E _left
;					    ;	;B02F _word_B02F	;B02F _ffile
;					    ;	;B031 _byte_B031	;B031 _base
; Variables are defined in other functions <	;B032 _buf_B032		;B032 __sibuf
;					    ;	;B232 __argc_		;B232 __argc_
;					    ;	;B234 memtop		;B234 memtop
;					     \	;B236 __Hbss		;B236 __Hbss

	psect	text

; End of data from file 1.asm

; End of file -  1.asm */

