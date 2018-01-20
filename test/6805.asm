; 6805.asm

dir	EQU	'D'
imm	EQU	'I'
ix1	EQU	'X'
ix2	EQU	'X2'
ext	EQU	'EX'

	BRSET	0 dir .	; 00 44 FE
	BRCLR	0 dir .	; 01 44 FE
	BRSET	1 dir .	; 02 44 FE
	BRCLR	1 dir .	; 03 44 FE
	BRSET	2 dir .	; 04 44 FE
	BRCLR	2 dir .	; 05 44 FE
	BRSET	3 dir .	; 06 44 FE
	BRCLR	3 dir .	; 07 44 FE
	BRSET	4 dir .	; 08 44 FE
	BRCLR	4 dir .	; 09 44 FE
	BRSET	5 dir .	; 0A 44 FE
	BRCLR	5 dir .	; 0B 44 FE
	BRSET	6 dir .	; 0C 44 FE
	BRCLR	6 dir .	; 0D 44 FE
	BRSET	7 dir .	; 0E 44 FE
	BRCLR	7 dir .	; 0F 44 FE

	BSET	0 dir	; 10 44
	BCLR	0 dir	; 11 44
	BSET	1 dir	; 12 44
	BCLR	1 dir	; 13 44
	BSET	2 dir	; 14 44
	BCLR	2 dir	; 15 44
	BSET	3 dir	; 16 44
	BCLR	3 dir	; 17 44
	BSET	4 dir	; 18 44
	BCLR	4 dir	; 19 44
	BSET	5 dir	; 1A 44
	BCLR	5 dir	; 1B 44
	BSET	6 dir	; 1C 44
	BCLR	6 dir	; 1D 44
	BSET	7 dir	; 1E 44
	BCLR	7 dir	; 1F 44

	BRA	.	; 20 FE
	BRN	.	; 21 FE
	BHI	.	; 22 FE
	BLS	.	; 23 FE
	BCC	.	; 24 FE
	BCS	.	; 25 FE
	BHS	.	; 24 FE
	BLO	.	; 25 FE
	BNE	.	; 26 FE
	BEQ	.	; 27 FE
	BHCC	.	; 28 FE
	BHCS	.	; 29 FE
	BPL	.	; 2A FE
	BMI	.	; 2B FE
	BMC	.	; 2C FE
	BMS	.	; 2D FE
	BIL	.	; 2E FE
	BIH	.	; 2F FE

	NEG	dir	; 30 44
	FCB	$31	; 31 44
	FCB	$32	; 32 44
	COM	dir	; 33 44
	LSR	dir	; 34 44
	FCB	$35	; 35
	ROR	dir	; 36 44
	ASR	dir	; 37 44
	ASL	dir	; 38 44
	LSL	dir	; 38 44
	ROL	dir	; 39 44
	DEC	dir	; 3A 44
	FCB	$3B	; 3B 44
	INC	dir	; 3C 44
	TST	dir	; 3D 44
	FCB	$3E	; 3E 44
	CLR	dir	; 3F 44

	NEGA		; 40
	FCB	$41	; 41
	MUL		; 42
	COMA		; 43
	LSRA		; 44
	FCB	$45	; 45
	RORA		; 46
	ASRA		; 47
	ASLA		; 48
	LSLA		; 48
	ROLA		; 49
	DECA		; 4A
	FCB	$4B	; 4B
	INCA		; 4C
	TSTA		; 4D
	FCB	$4E	; 4E
	CLRA		; 4F

	NEGX		; 50
	FCB	$51	; 51
	FCB	$52	; 52
	COMX		; 53
	LSRX		; 54
	FCB	$55	; 55
	RORX		; 56
	ASRX		; 57
	ASLX		; 58
	LSLX		; 58
	ROLX		; 59
	DECX		; 5A
	FCB	$5B	; 5B
	INCX		; 5C
	TSTX		; 5D
	FCB	$5E	; 5E
	CLRX		; 5F

	NEG	ix1,X	; 60 58
	FCB	$61	; 61
	FCB	$62	; 62
	COM	ix1,X	; 63 58
	LSR	ix1,X	; 64 58
	FCB	$65	; 65
	ROR	ix1,X	; 66 58
	ASR	ix1,X	; 67 58
	ASL	ix1,X	; 68 58
	LSL	ix1,X	; 68 58
	ROL	ix1,X	; 69 58
	DEC	ix1,X	; 6A 58
	FCB	$6B	; 6B
	INC	ix1,X	; 6C 58
	TST	ix1,X	; 6D 58
	FCB	$6E	; 6E
	CLR	ix1,X	; 6F 58

	NEG	,X	; 70
	FCB	$71	; 71
	FCB	$72	; 72
	COM	,X	; 73
	LSR	,X	; 74
	FCB	$75	; 75
	ROR	,X	; 76
	ASR	,X	; 77
	ASL	,X	; 78
	LSL	,X	; 78
	ROL	,X	; 79
	DEC	,X	; 7A
	FCB	$7B	; 7B
	INC	,X	; 7C
	TST	,X	; 7D
	FCB	$7E	; 7E
	CLR	,X	; 7F

	RTI		; 80
	RTS		; 81
	FCB	$82	; 82
	SWI		; 83
	FCB	$84	; 84
	FCB	$85	; 85
	FCB	$86	; 86
	FCB	$87	; 87
	FCB	$88	; 88
	FCB	$89	; 89
	FCB	$8A	; 8A
	FCB	$8B	; 8B
	FCB	$8C	; 8C
	FCB	$8D	; 8D
	STOP		; 8E
	WAIT		; 8F

	FCB	$90	; 90
	FCB	$91	; 91
	FCB	$92	; 92
	FCB	$93	; 93
	FCB	$94	; 94
	FCB	$95	; 95
	FCB	$96	; 96
	TAX		; 97
	CLC		; 98
	SEC		; 99
	CLI		; 9A
	SEI		; 9B
	RSP		; 9C (reset stack pointer)
	NOP		; 9D
	FCB	$9E	; 9E
	TXA		; 9F

	SUB	#imm	; A0 49
	CMP	#imm	; A1 49
	SBC	#imm	; A2 49
	CPX	#imm	; A3 49
	AND	#imm	; A4 49
	BIT	#imm	; A5 49
	LDA	#imm	; A6 49
	FCB	$A7	; A7    (STA #imm)
	EOR	#imm	; A8 49
	ADC	#imm	; A9 49
	ORA	#imm	; AA 49
	ADD	#imm	; AB 49
	FCB	$AC	; AC    (JMP #imm)
	BSR	.	; AD FE
	LDX	#imm	; AE 49
	FCB	$AF	; AF    (STX #imm)

	SUB	dir	; B0 44
	CMP	dir	; B1 44
	SBC	dir	; B2 44
	CPX	dir	; B3 44
	AND	dir	; B4 44
	BIT	dir	; B5 44
	LDA	dir	; B6 44
	STA	dir	; B7 44
	EOR	dir	; B8 44
	ADC	dir	; B9 44
	ORA	dir	; BA 44
	ADD	dir	; BB 44
	JMP	dir	; BC 44
	JSR	dir	; BD 44
	LDX	dir	; BE 44
	STX	dir	; BF 44

	SUB	ext	; C0 4558
	CMP	ext	; C1 4558
	SBC	ext	; C2 4558
	CPX	ext	; C3 4558
	AND	ext	; C4 4558
	BIT	ext	; C5 4558
	LDA	ext	; C6 4558
	STA	ext	; C7 4558
	EOR	ext	; C8 4558
	ADC	ext	; C9 4558
	ORA	ext	; CA 4558
	ADD	ext	; CB 4558
	JMP	ext	; CC 4558
	JSR	ext	; CD 4558
	LDX	ext	; CE 4558
	STX	ext	; CF 4558

	SUB	ix2,X	; D0 5832
	CMP	ix2,X	; D1 5832
	SBC	ix2,X	; D2 5832
	CPX	ix2,X	; D3 5832
	AND	ix2,X	; D4 5832
	BIT	ix2,X	; D5 5832
	LDA	ix2,X	; D6 5832
	STA	ix2,X	; D7 5832
	EOR	ix2,X	; D8 5832
	ADC	ix2,X	; D9 5832
	ORA	ix2,X	; DA 5832
	ADD	ix2,X	; DB 5832
	JMP	ix2,X	; DC 5832
	JSR	ix2,X	; DD 5832
	LDX	ix2,X	; DE 5832
	STX	ix2,X	; DF 5832

	SUB	ix1,X	; E0 58
	CMP	ix1,X	; E1 58
	SBC	ix1,X	; E2 58
	CPX	ix1,X	; E3 58
	AND	ix1,X	; E4 58
	BIT	ix1,X	; E5 58
	LDA	ix1,X	; E6 58
	STA	ix1,X	; E7 58
	EOR	ix1,X	; E8 58
	ADC	ix1,X	; E9 58
	ORA	ix1,X	; EA 58
	ADD	ix1,X	; EB 58
	JMP	ix1,X	; EC 58
	JSR	ix1,X	; ED 58
	LDX	ix1,X	; EE 58
	STX	ix1,X	; EF 58

	SUB	,X	; F0
	CMP	,X	; F1
	SBC	,X	; F2
	CPX	,X	; F3
	AND	,X	; F4
	BIT	,X	; F5
	LDA	,X	; F6
	STA	,X	; F7
	EOR	,X	; F8
	ADC	,X	; F9
	ORA	,X	; FA
	ADD	,X	; FB
	JMP	,X	; FC
	JSR	,X	; FD
	LDX	,X	; FE
	STX	,X	; FF

	END
