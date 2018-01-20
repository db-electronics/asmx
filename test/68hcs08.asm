; 6805.asm

dir	EQU	'D'
imm	EQU	'I'
imm16	EQU	'IM'
ix1	EQU	'X'
ix2	EQU	'X2'
ext	EQU	'EX'
sp1	EQU	'S'
sp2	EQU	'S2'

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
	CBEQ	dir,.	; 31 44 FD
	LDHX	ext	; 32 4558
	COM	dir	; 33 44
	LSR	dir	; 34 44
	STHX	dir	; 35 44
	ROR	dir	; 36 44
	ASR	dir	; 37 44
	ASL	dir	; 38 44
	LSL	dir	; 38 44
	ROL	dir	; 39 44
	DEC	dir	; 3A 44
	DBNZ	dir,.	; 3B 44 FD
	INC	dir	; 3C 44
	TST	dir	; 3D 44
	CPHX	ext	; 3E 4558
	CLR	dir	; 3F 44

	NEGA		; 40
	CBEQA	#imm,.	; 41 49 FD
	MUL		; 42
	COMA		; 43
	LSRA		; 44
	LDHX	#imm16	; 45 494D
	RORA		; 46
	ASRA		; 47
	ASLA		; 48
	LSLA		; 48
	ROLA		; 49
	DECA		; 4A
	DBNZA	.	; 4B FE
	INCA		; 4C
	TSTA		; 4D
	MOV	dir,dir+1 ; 4E 44 45
	CLRA		; 4F

	NEGX		; 50
	CBEQX	#imm,.	; 51 49 FD
	DIV		; 52
	COMX		; 53
	LSRX		; 54
	LDHX	dir	; 55 44
	RORX		; 56
	ASRX		; 57
	ASLX		; 58
	LSLX		; 58
	ROLX		; 59
	DECX		; 5A
	DBNZX	.	; 5B FE
	INCX		; 5C
	TSTX		; 5D
	MOV	dir,X+	; 5E 44
	CLRX		; 5F

	NEG	ix1,X	; 60 58
	CBEQ	ix1,X+,. ; 61 58 FD
	NSA		; 62
	COM	ix1,X	; 63 58
	LSR	ix1,X	; 64 58
	CPHX	#imm16	; 65 494D
	ROR	ix1,X	; 66 58
	ASR	ix1,X	; 67 58
	ASL	ix1,X	; 68 58
	LSL	ix1,X	; 68 58
	ROL	ix1,X	; 69 58
	DEC	ix1,X	; 6A 58
	DBNZ	ix1,X,.	; 6B 58 FD
	INC	ix1,X	; 6C 58
	TST	ix1,X	; 6D 58
	MOV	#imm,dir ; 6E 49 44
	CLR	ix1,X	; 6F 58

	NEG	,X	; 70
	CBEQ	,X+,.	; 71 FE
	DAA		; 72
	COM	,X	; 73
	LSR	,X	; 74
	CPHX	dir	; 75 44
	ROR	,X	; 76
	ASR	,X	; 77
	ASL	,X	; 78
	LSL	,X	; 78
	ROL	,X	; 79
	DEC	,X	; 7A
	DBNZ	,X,.	; 7B FE
	INC	,X	; 7C
	TST	,X	; 7D
	MOV	,X+,dir	; 7E 44
	CLR	,X	; 7F

	RTI		; 80
	RTS		; 81
	BGND		; 82
	SWI		; 83
	TAP		; 84
	TPA		; 85
	PULA		; 86
	PSHA		; 87
	PULX		; 88
	PSHX		; 89
	PULH		; 8A
	PSHH		; 8B
	CLRH		; 8C
	FCB	$8D	; 8D
	STOP		; 8E
	WAIT		; 8F

	BGE	.	; 90 FE
	BLT	.	; 91 FE
	BGT	.	; 92 FE
	BLE	.	; 93 FE
	TXS		; 94
	TSX		; 95
	STHX	ext	; 96 4558
	TAX		; 97
	CLC		; 98
	SEC		; 99
	CLI		; 9A
	SEI		; 9B
	RSP		; 9C (reset stack pointer)
	NOP		; 9D
	FCB	$9E	; 9E (PAGE 2)
	TXA		; 9F

	SUB	#imm	; A0 49
	CMP	#imm	; A1 49
	SBC	#imm	; A2 49
	CPX	#imm	; A3 49
	AND	#imm	; A4 49
	BIT	#imm	; A5 49
	LDA	#imm	; A6 49
	AIS	#imm	; A7 49
	EOR	#imm	; A8 49
	ADC	#imm	; A9 49
	ORA	#imm	; AA 49
	ADD	#imm	; AB 49
	FCB	$AC	; AC    (JMP #imm)
	BSR	.	; AD FE
	LDX	#imm	; AE 49
	AIX	#imm	; AF 49

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

	NEG	sp1,SP	; 9E60 53
	CBEQ	sp1,SP,. ; 9E61 53 FC
			; 9E62
	COM	sp1,SP	; 9E63 53
	LSR	sp1,SP	; 9E64 53
			; 9E65
	ROR	sp1,SP	; 9E66 53
	ASR	sp1,SP	; 9E67 53
	ASL	sp1,SP	; 9E68 53
	LSL	sp1,SP	; 9E68 53
	ROL	sp1,SP	; 9E69 53
	DEC	sp1,SP	; 9E6A 53
	DBNZ	sp1,SP,. ; 9E6B 53 FC
	INC	sp1,SP	; 9E6C 53
	TST	sp1,SP	; 9E6D 53
			; 9E6E
	CLR	sp1,SP	; 9E6F 53

	LDHX	,X	; 9EAE
	LDHX	ix2,X	; 9EBE 5832
	LDHX	ix1,X	; 9ECE 58

	SUB	sp2,SP	; 9ED0 5332
	CMP	sp2,SP	; 9ED1 5332
	SBC	sp2,SP	; 9ED2 5332
	CPX	sp2,SP	; 9ED3 5332
	AND	sp2,SP	; 9ED4 5332
	BIT	sp2,SP	; 9ED5 5332
	LDA	sp2,SP	; 9ED6 5332
	STA	sp2,SP	; 9ED7 5332
	EOR	sp2,SP	; 9ED8 5332
	ADC	sp2,SP	; 9ED9 5332
	ORA	sp2,SP	; 9EDA 5332
	ADD	sp2,SP	; 9EDB 5332
			; 9EDC
			; 9EDD
	LDX	sp2,SP	; 9EDE 5332
	STX	sp2,SP	; 9EDF 5332

	SUB	sp1,SP	; 9EE0 53
	CMP	sp1,SP	; 9EE1 53
	SBC	sp1,SP	; 9EE2 53
	CPX	sp1,SP	; 9EE3 53
	AND	sp1,SP	; 9EE4 53
	BIT	sp1,SP	; 9EE5 53
	LDA	sp1,SP	; 9EE6 53
	STA	sp1,SP	; 9EE7 53
	EOR	sp1,SP	; 9EE8 53
	ADC	sp1,SP	; 9EE9 53
	ORA	sp1,SP	; 9EEA 53
	ADD	sp1,SP	; 9EEB 53
			; 9EEC
			; 9EED
	LDX	sp1,SP	; 9EEE 53
	STX	sp1,SP	; 9EEF 53

	CPHX	sp1,SP	; 9EF3 53
	LDHX	sp1,SP	; 9EFE 53
	STHX	sp1,SP	; 9EFF 53

; invalid combinations:

	STHX	,X
	STHX	ix1,X
	CPHX	,X
	CPHX	ix1,X
	JMP	sp1,SP
	JSR	sp1,SP

	END
