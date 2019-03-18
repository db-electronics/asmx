	NOP			; 00
	LD	BC,1234H	; 01 3412
	LD	(BC),A		; 02
	INC	BC		; 03
	INC	B		; 04
	DEC	B		; 05
	LD	B,56H		; 06 56
	RLCA			; 07

	LD	(1234H),SP	; 08 3412
	ADD	HL,BC		; 09
	LD	A,(BC)		; 0A
	DEC	BC		; 0B
	INC	C		; 0C
	DEC	C		; 0D
	LD	C,56H		; 0E 56
	RRCA			; 0F

	STOP			; 10
	LD	DE,1234H	; 11 3412
	LD	(DE),A		; 12
	INC	DE		; 13
	INC	D		; 14
	DEC	D		; 15
	LD	D,56H		; 16 56
	RLA			; 17

	JR	$		; 18 FE
	ADD	HL,DE		; 19
	LD	A,(DE)		; 1A
	DEC	DE		; 1B
	INC	E		; 1C
	DEC	E		; 1D
	LD	E,56H		; 1E 56
	RRA			; 1F

	JR	NZ,$		; 20 FE
	LD	HL,1234H	; 21 3412
	LD	(HL+),A		; 22
	LD	(HLI),A		; 22
	LDI	(HL),A		; 22
	INC	HL		; 23
	INC	H		; 24
	DEC	H		; 25
	LD	H,56H		; 26 56
	DAA			; 27

	JR	Z,$		; 28 FE
	ADD	HL,HL		; 29
	LD	A,(HL+)		; 2A
	LD	A,(HLI)		; 2A
	LDI	A,(HL)		; 2A
	DEC	HL		; 2B
	INC	L		; 2C
	DEC	L		; 2D
	LD	L,56H		; 2E 56
	CPL			; 2F

	JR	NC,$		; 30 FE
	LD	SP,1234H	; 31 3412
	LD	(HL-),A		; 32
	LD	(HLD),A		; 32
	LDD	(HL),A		; 32
	INC	SP		; 33
	INC	(HL)		; 34
	DEC	(HL)		; 35
	LD	(HL),56H	; 36 56
	SCF			; 37

	JR	C,$		; 38 FE
	ADD	HL,SP		; 39
	LD	A,(HL-)		; 3A
	LD	A,(HLD)		; 3A
	LDD	A,(HL)		; 3A
	DEC	SP		; 3B
	INC	A		; 3C
	DEC	A		; 3D
	LD	A,56H		; 3E 56
	CCF			; 3F

	LD	B,B		; 40
	LD	B,C		; 41
	LD	B,D		; 42
	LD	B,E		; 43
	LD	B,H		; 44
	LD	B,L		; 45
	LD	B,(HL)		; 46
	LD	B,A		; 47

	LD	C,B		; 48
	LD	C,C		; 49
	LD	C,D		; 4A
	LD	C,E		; 4B
	LD	C,H		; 4C
	LD	C,L		; 4D
	LD	C,(HL)		; 4E
	LD	C,A		; 4F

	LD	D,B		; 50
	LD	D,C		; 51
	LD	D,D		; 52
	LD	D,E		; 53
	LD	D,H		; 54
	LD	D,L		; 55
	LD	D,(HL)		; 56
	LD	D,A		; 57

	LD	E,B		; 58
	LD	E,C		; 59
	LD	E,D		; 5A
	LD	E,E		; 5B
	LD	E,H		; 5C
	LD	E,L		; 5D
	LD	E,(HL)		; 5E
	LD	E,A		; 5F

	LD	H,B		; 60
	LD	H,C		; 61
	LD	H,D		; 62
	LD	H,E		; 63
	LD	H,H		; 64
	LD	H,L		; 65
	LD	H,(HL)		; 66
	LD	H,A		; 67

	LD	L,B		; 68
	LD	L,C		; 69
	LD	L,D		; 6A
	LD	L,E		; 6B
	LD	L,H		; 6C
	LD	L,L		; 6D
	LD	L,(HL)		; 6E
	LD	L,A		; 6F

	LD	(HL),B		; 70
	LD	(HL),C		; 71
	LD	(HL),D		; 72
	LD	(HL),E		; 73
	LD	(HL),H		; 74
	LD	(HL),L		; 75
	HALT			; 76
	LD	(HL),A		; 77

	LD	A,B		; 78
	LD	A,C		; 79
	LD	A,D		; 7A
	LD	A,E		; 7B
	LD	A,H		; 7C
	LD	A,L		; 7D
	LD	A,(HL)		; 7E
	LD	A,A		; 7F

	ADD	A,B		; 80
	ADD	A,C		; 81
	ADD	A,D		; 82
	ADD	A,E		; 83
	ADD	A,H		; 84
	ADD	A,L		; 85
	ADD	A,(HL)		; 86
	ADD	A,A		; 87

	ADC	A,B		; 88
	ADC	A,C		; 89
	ADC	A,D		; 8A
	ADC	A,E		; 8B
	ADC	A,H		; 8C
	ADC	A,L		; 8D
	ADC	A,(HL)		; 8E
	ADC	A,A		; 8F

	SUB	B		; 90
	SUB	C		; 91
	SUB	D		; 92
	SUB	E		; 93
	SUB	H		; 94
	SUB	L		; 95
	SUB	(HL)		; 96
	SUB	A		; 97

	SBC	A,B		; 98
	SBC	A,C		; 99
	SBC	A,D		; 9A
	SBC	A,E		; 9B
	SBC	A,H		; 9C
	SBC	A,L		; 9D
	SBC	A,(HL)		; 9E
	SBC	A,A		; 9F

	AND	B		; A0
	AND	C		; A1
	AND	D		; A2
	AND	E		; A3
	AND	H		; A4
	AND	L		; A5
	AND	(HL)		; A6
	AND	A		; A7

	XOR	B		; A8
	XOR	C		; A9
	XOR	D		; AA
	XOR	E		; AB
	XOR	H		; AC
	XOR	L		; AD
	XOR	(HL)		; AE
	XOR	A		; AF

	OR	B		; B0
	OR	C		; B1
	OR	D		; B2
	OR	E		; B3
	OR	H		; B4
	OR	L		; B5
	OR	(HL)		; B6
	OR	A		; B7

	CP	B		; B8
	CP	C		; B9
	CP	D		; BA
	CP	E		; BB
	CP	H		; BC
	CP	L		; BD
	CP	(HL)		; BE
	CP	A		; BF

	RET	NZ		; C0
	POP	BC		; C1
	JP	NZ,1234H	; C2 3412
	JP	1234H		; C3 3412
	CALL	NZ,1234H	; C4 3412
	PUSH	BC		; C5
	ADD	A,78H		; C6 78
	RST	00H		; C7

	RET	Z		; C8
	RET			; C9
	JP	Z,1234H		; CA 3412
	DB	0CBH		; CB - bit & rot instructions
	CALL	Z,1234H		; CC F600
	CALL	1234H		; CD 3412
	ADC	A,78H		; CE 78
	RST	08H		; CF

	RET	NC		; D0
	POP	DE		; D1
	JP	NC,1234H	; D2 3412
	DB	D3H		; D3
	CALL	NC,1234H	; D4 3412
	PUSH	DE		; D5
	SUB	78H		; D6
	RST	10H		; D7 78

	RET	C		; D8
	RETI			; D9
	JP	C,1234H		; DA 3412
	DB	DBH		; DB
	CALL	C,1234H		; DC 3412
	DB	0DDH		; DD - IX instructions
	SBC	A,78H		; DE 78
	RST	18H		; DF

	LD	(FF56H),A	; E0 56
	LDH	(56H),A		; E0 56
	LDH	(FF56H),A	; E0 56
	POP	HL		; E1
	LD	(C),A		; E2
	DB	E3H		; E3
	DB	E4H		; E4
	PUSH	HL   		; E5
	AND	78H		; E6 78
	RST	20H		; E7

	ADD	SP,56H		; E8 56
	JP	(HL)		; E9
	LD	(1234H),A	; EA 3412
	DB	EBH		; EB
	DB	ECH		; EC
;	DEBUG			; ED (is this real?)
	DB	0EDH		; ED - misc instructions
	XOR	78H		; EE 78
	RST	28H		; EF

	LD	A,(FF56H)	; F0 56
	LDH	A,(56H)		; F0 56
	LDH	A,(FF56H)	; F0 56
	POP	AF		; F1
	LD	A,(C)		; F2
	DI			; F3
	DB	F4H		; F4
	PUSH	AF		; F5
	OR	78H		; F6 78
	RST	30H		; F7

	DB	F8H		; F8
	LD	SP,HL		; F9
	LD	A,(1234H)	; FA
	EI			; FB
	DB	FCH		; FC
	DB	0FDH		; FD - IY instructions
	CP	78H		; FE 78
	RST	38H		; FF

	RLC	B		; CB00
	RLC	C		; CB01
	RLC	D		; CB02
	RLC	E		; CB03
	RLC	H		; CB04
	RLC	L		; CB05
	RLC	(HL)		; CB06
	RLC	A		; CB07

	RRC	B		; CB08
	RRC	C		; CB09
	RRC	D		; CB0A
	RRC	E		; CB0B
	RRC	H		; CB0C
	RRC	L		; CB0D
	RRC	(HL)		; CB0E
	RRC	A		; CB0F

	RL	B		; CB10
	RL	C		; CB11
	RL	D		; CB12
	RL	E		; CB13
	RL	H		; CB14
	RL	L		; CB15
	RL	(HL)		; CB16
	RL	A		; CB17

	RR	B		; CB18
	RR	C		; CB19
	RR	D		; CB1A
	RR	E		; CB1B
	RR	H		; CB1C
	RR	L		; CB1D
	RR	(HL)		; CB1E
	RR	A		; CB1F

	SLA	B		; CB20
	SLA	C		; CB21
	SLA	D		; CB22
	SLA	E		; CB23
	SLA	H		; CB24
	SLA	L		; CB25
	SLA	(HL)		; CB26
	SLA	A		; CB27

	SRA	B		; CB28
	SRA	C		; CB29
	SRA	D		; CB2A
	SRA	E		; CB2B
	SRA	H		; CB2C
	SRA	L		; CB2D
	SRA	(HL)		; CB2E
	SRA	A		; CB2F

	SWAP	B		; CB30
	SWAP	C		; CB31
	SWAP	D		; CB32
	SWAP	E		; CB33
	SWAP	H		; CB34
	SWAP	L		; CB35
	SWAP	(HL)		; CB36
	SWAP	A		; CB37

	SRL	B		; CB38
	SRL	C		; CB39
	SRL	D		; CB3A
	SRL	E		; CB3B
	SRL	H		; CB3C
	SRL	L		; CB3D
	SRL	(HL)		; CB3E
	SRL	A		; CB3F

	BIT	0,B		; CB40
	BIT	0,C		; CB41
	BIT	0,D		; CB42
	BIT	0,E		; CB43
	BIT	0,H		; CB44
	BIT	0,L		; CB45
	BIT	0,(HL)		; CB46
	BIT	0,A		; CB47

	BIT	1,B		; CB48
	BIT	1,C		; CB49
	BIT	1,D		; CB4A
	BIT	1,E		; CB4B
	BIT	1,H		; CB4C
	BIT	1,L		; CB4D
	BIT	1,(HL)		; CB4E
	BIT	1,A		; CB4F

	BIT	2,B		; CB50
	BIT	2,C		; CB51
	BIT	2,D		; CB52
	BIT	2,E		; CB53
	BIT	2,H		; CB54
	BIT	2,L		; CB55
	BIT	2,(HL)		; CB56
	BIT	2,A		; CB57

	BIT	3,B		; CB58
	BIT	3,C		; CB59
	BIT	3,D		; CB5A
	BIT	3,E		; CB5B
	BIT	3,H		; CB5C
	BIT	3,L		; CB5D
	BIT	3,(HL)		; CB5E
	BIT	3,A		; CB5F

	BIT	4,B		; CB60
	BIT	4,C		; CB61
	BIT	4,D		; CB62
	BIT	4,E		; CB63
	BIT	4,H		; CB64
	BIT	4,L		; CB65
	BIT	4,(HL)		; CB66
	BIT	4,A		; CB67

	BIT	5,B		; CB68
	BIT	5,C		; CB69
	BIT	5,D		; CB6A
	BIT	5,E		; CB6B
	BIT	5,H		; CB6C
	BIT	5,L		; CB6D
	BIT	5,(HL)		; CB6E
	BIT	5,A		; CB6F

	BIT	6,B		; CB70
	BIT	6,C		; CB71
	BIT	6,D		; CB72
	BIT	6,E		; CB73
	BIT	6,H		; CB74
	BIT	6,L		; CB75
	BIT	6,(HL)		; CB76
	BIT	6,A		; CB77

	BIT	7,B		; CB78
	BIT	7,C		; CB79
	BIT	7,D		; CB7A
	BIT	7,E		; CB7B
	BIT	7,H		; CB7C
	BIT	7,L		; CB7D
	BIT	7,(HL)		; CB7E
	BIT	7,A		; CB7F

	RES	0,B		; CB80
	RES	0,C		; CB81
	RES	0,D		; CB82
	RES	0,E		; CB83
	RES	0,H		; CB84
	RES	0,L		; CB85
	RES	0,(HL)		; CB86
	RES	0,A		; CB87

	RES	1,B		; CB88
	RES	1,C		; CB89
	RES	1,D		; CB8A
	RES	1,E		; CB8B
	RES	1,H		; CB8C
	RES	1,L		; CB8D
	RES	1,(HL)		; CB8E
	RES	1,A		; CB8F

	RES	2,B		; CB90
	RES	2,C		; CB91
	RES	2,D		; CB92
	RES	2,E		; CB93
	RES	2,H		; CB94
	RES	2,L		; CB95
	RES	2,(HL)		; CB96
	RES	2,A		; CB97

	RES	3,B		; CB98
	RES	3,C		; CB99
	RES	3,D		; CB9A
	RES	3,E		; CB9B
	RES	3,H		; CB9C
	RES	3,L		; CB9D
	RES	3,(HL)		; CB9E
	RES	3,A		; CB9F

	RES	4,B		; CBA0
	RES	4,C		; CBA1
	RES	4,D		; CBA2
	RES	4,E		; CBA3
	RES	4,H		; CBA4
	RES	4,L		; CBA5
	RES	4,(HL)		; CBA6
	RES	4,A		; CBA7

	RES	5,B		; CBA8
	RES	5,C		; CBA9
	RES	5,D		; CBAA
	RES	5,E		; CBAB
	RES	5,H		; CBAC
	RES	5,L		; CBAD
	RES	5,(HL)		; CBAE
	RES	5,A		; CBAF

	RES	6,B		; CBB0
	RES	6,C		; CBB1
	RES	6,D		; CBB2
	RES	6,E		; CBB3
	RES	6,H		; CBB4
	RES	6,L		; CBB5
	RES	6,(HL)		; CBB6
	RES	6,A		; CBB7

	RES	7,B		; CBB8
	RES	7,C		; CBB9
	RES	7,D		; CBBA
	RES	7,E		; CBBB
	RES	7,H		; CBBC
	RES	7,L		; CBBD
	RES	7,(HL)		; CBBE
	RES	7,A		; CBBF

	SET	0,B		; CBC0
	SET	0,C		; CBC1
	SET	0,D		; CBC2
	SET	0,E		; CBC3
	SET	0,H		; CBC4
	SET	0,L		; CBC5
	SET	0,(HL)		; CBC6
	SET	0,A		; CBC7

	SET	1,B		; CBC8
	SET	1,C		; CBC9
	SET	1,D		; CBCA
	SET	1,E		; CBCB
	SET	1,H		; CBCC
	SET	1,L		; CBCD
	SET	1,(HL)		; CBCE
	SET	1,A		; CBCF

	SET	2,B		; CBD0
	SET	2,C		; CBD1
	SET	2,D		; CBD2
	SET	2,E		; CBD3
	SET	2,H		; CBD4
	SET	2,L		; CBD5
	SET	2,(HL)		; CBD6
	SET	2,A		; CBD7

	SET	3,B		; CBD8
	SET	3,C		; CBD9
	SET	3,D		; CBDA
	SET	3,E		; CBDB
	SET	3,H		; CBDC
	SET	3,L		; CBDD
	SET	3,(HL)		; CBDE
	SET	3,A		; CBDF

	SET	4,B		; CBE0
	SET	4,C		; CBE1
	SET	4,D		; CBE2
	SET	4,E		; CBE3
	SET	4,H		; CBE4
	SET	4,L		; CBE5
	SET	4,(HL)		; CBE6
	SET	4,A		; CBE7

	SET	5,B		; CBE8
	SET	5,C		; CBE9
	SET	5,D		; CBEA
	SET	5,E		; CBEB
	SET	5,H		; CBEC
	SET	5,L		; CBED
	SET	5,(HL)		; CBEE
	SET	5,A		; CBEF

	SET	6,B		; CBF0
	SET	6,C		; CBF1
	SET	6,D		; CBF2
	SET	6,E		; CBF3
	SET	6,H		; CBF4
	SET	6,L		; CBF5
	SET	6,(HL)		; CBF6
	SET	6,A		; CBF7

	SET	7,B		; CBF8
	SET	7,C		; CBF9
	SET	7,D		; CBFA
	SET	7,E		; CBFB
	SET	7,H		; CBFC
	SET	7,L		; CBFD
	SET	7,(HL)		; CBFE
	SET	7,A		; CBFF

	END
