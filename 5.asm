*Title Disassembling CGEN.COM Hi-Tech C v3.09
*Heading Checking recreated code with original

; File - 5.asm Created 09.03.2019 Last Modified 31.01.2021

;=========================================================
; Data from file 5.asm
;=========================================================
	global	_off_AACA

	psect	data

_off_AACA:
	defw	19f
	defw	29f
	defw	39f
	defw	49f
	defw	59f
	defw	69f
	defw	79f
	defw	89f
	defw	99f
	defw	109f
	defw	119f
	defw	129f
	defw	139f
	defw	149f
	defw	159f

	global	_array_AAE8

_array_AAE8:
	defw	   0,  1,   2,   4,   8,  16,  32,  64, 128, 256
	defw	 512,  1,   6,  24,  96, 120, 102, 126, 127,   0
	defw	 121, 97,  25,   7, 126,  30,  63,  62, 127,  30

global	_array_AB24

_array_AB24:
	defb	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	defb	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	defb	 0,  0,  1,  0,  2,  3,  4,  5,  6,  7
	defb	13, 14, 12, 14, 12, 15,  1, 17,  0,  0
	defb	15,  1, 14,  1, 13,  1, 12,  1

global	_array_AB54

_array_AB54:
	defb	14
	defb	13
	defb	12
	defb	0
	defb	0
	defb	0

	defb	13
	defb	12
	defb	0
	defb	0
	defb	0
	defb	0

	defb	1
	defb	4
	defb	5
	defb	2
	defb	3
	defb	6

	defb	4
	defb	5
	defb	2
	defb	3
	defb	6
	defb	0

	defb	21
	defb	22
	defb	23
	defb	0
	defb	0
	defb	0

	defb	12
	defb	13
	defb	0
	defb	0
	defb	0
	defb	0

19:	defb	0
29:	defb	97,0
39:	defb	99,0
49:	defb	98,0
59:	defb	101,0
69:	defb	100,0
79:	defb	108,0
89:	defb	104,0
99:	defb	105,120,0
109:	defb	105,121,0
119:	defb	115,112,0
129:	defb	97,102,0
139:	defb	98,99,0
149:	defb	100,101,0
159:	defb	104,108,0

	psect	text

; End of file 5.asm


