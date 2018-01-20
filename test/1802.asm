;	all 1802 opcodes

	IDL		; 00	wait for interrupt or DMA
	LDN	R1	; 01	D = M(R1)
	LDN	R2	; 02	D = M(R2)
	LDN	R3	; 03	D = M(R3)
	LDN	R4	; 04	D = M(R4)
	LDN	R5	; 05	D = M(R5)
	LDN	R6	; 06	D = M(R6)
	LDN	R7	; 07	D = M(R7)
	LDN	R8	; 08	D = M(R8)
	LDN	R9	; 09	D = M(R9)
	LDN	RA	; 0A	D = M(RA)
	LDN	RB	; 0B	D = M(RB)
	LDN	RC	; 0C	D = M(RC)
	LDN	RD	; 0D	D = M(RD)
	LDN	RE	; 0E	D = M(RE)
	LDN	RF	; 0F	D = M(RF)

	INC	R0	; 10	R0 = R0 + 1
	INC	R1	; 11	R1 = R1 + 1
	INC	R2	; 12	R2 = R2 + 1
	INC	R3	; 13	R3 = R3 + 1
	INC	R4	; 14	R4 = R4 + 1
	INC	R5	; 15	R5 = R5 + 1
	INC	R6	; 16	R6 = R6 + 1
	INC	R7	; 17	R7 = R7 + 1
	INC	R8	; 18	R8 = R8 + 1
	INC	R9	; 19	R9 = R9 + 1
	INC	RA	; 1A	RA = RA + 1
	INC	RB	; 1B	RB = RB + 1
	INC	RC	; 1C	RC = RC + 1
	INC	RD	; 1D	RD = RD + 1
	INC	RE	; 1E	RE = RE + 1
	INC	RF	; 1F	RF = RF + 1

	DEC	R0	; 20	R0 = R0 - 1
	DEC	R1	; 21	R1 = R1 - 1
	DEC	R2	; 22	R2 = R2 - 1
	DEC	R3	; 23	R3 = R3 - 1
	DEC	R4	; 24	R4 = R4 - 1
	DEC	R5	; 25	R5 = R5 - 1
	DEC	R6	; 26	R6 = R6 - 1
	DEC	R7	; 27	R7 = R7 - 1
	DEC	R8	; 28	R8 = R8 - 1
	DEC	R9	; 29	R9 = R9 - 1
	DEC	RA	; 2A	RA = RA - 1
	DEC	RB	; 2B	RB = RB - 1
	DEC	RC	; 2C	RC = RC - 1
	DEC	RD	; 2D	RD = RD - 1
	DEC	RE	; 2E	RE = RE - 1
	DEC	RF	; 2F	RF = RF - 1

	BR	.+1	; 30 nn	- branch always
	BQ	.+1	; 31 nn - branch if Q=1
	BZ	.+1	; 32 nn - branch if D=0
	BDF	.+1	; 33 nn - branch if DF=1 (aka BPZ BGE)
	B1	.+1	; 34 nn - branch if EF1=1
	B2	.+1	; 35 nn - branch if EF2=1
	B3	.+1	; 36 nn - branch if EF3=1
	B4	.+1	; 37 nn - branch if EF4=1
	SKP		; 38	RP = RP + 1 (skip next byte) (aka NBR nn)
	BNQ	.+1	; 39 nn - branch if Q=0
	BNZ	.+1	; 3A nn - branch if D!=0
	BNF	.+1	; 3B nn - branch if DF=0 (aka BM BL)
	BN1	.+1	; 3C nn - branch if EF1=0
	BN2	.+1	; 3D nn - branch if EF2=0
	BN3	.+1	; 3E nn - branch if EF3=0
	BN4	.+1	; 3F nn - branch if EF4=0

	LDA	R0	; 40	D = M(R0); R0 = R0 + 1
	LDA	R1	; 41	D = M(R1); R1 = R1 + 1
	LDA	R2	; 42	D = M(R2); R2 = R2 + 1
	LDA	R3	; 43	D = M(R3); R3 = R3 + 1
	LDA	R4	; 44	D = M(R4); R4 = R4 + 1
	LDA	R5	; 45	D = M(R5); R5 = R5 + 1
	LDA	R6	; 46	D = M(R6); R6 = R6 + 1
	LDA	R7	; 47	D = M(R7); R7 = R7 + 1
	LDA	R8	; 48	D = M(R8); R8 = R8 + 1
	LDA	R9	; 49	D = M(R9); R9 = R9 + 1
	LDA	RA	; 4A	D = M(RA); RA = RA + 1
	LDA	RB	; 4B	D = M(RB); RB = RB + 1
	LDA	RC	; 4C	D = M(RC); RC = RC + 1
	LDA	RD	; 4D	D = M(RD); RD = RD + 1
	LDA	RE	; 4E	D = M(RE); RE = RE + 1
	LDA	RF	; 4F	D = M(RF); RF = RF + 1

	STR	R0	; 50	M(R0) = D
	STR	R1	; 51	M(R1) = D
	STR	R2	; 52	M(R2) = D
	STR	R3	; 53	M(R3) = D
	STR	R4	; 54	M(R4) = D
	STR	R5	; 55	M(R5) = D
	STR	R6	; 56	M(R6) = D
	STR	R7	; 57	M(R7) = D
	STR	R8	; 58	M(R8) = D
	STR	R9	; 59	M(R9) = D
	STR	RA	; 5A	M(RA) = D
	STR	RB	; 5B	M(RB) = D
	STR	RC	; 5C	M(RC) = D
	STR	RD	; 5D	M(RD) = D
	STR	RE	; 5E	M(RE) = D
	STR	RF	; 5F	M(RF) = D

	IRX		; 60	X = X + 1
	OUT	1	; 61	bus = M(RX); RX = RX + 1
	OUT	2	; 62	bus = M(RX); RX = RX + 1
	OUT	3	; 63	bus = M(RX); RX = RX + 1
	OUT	4	; 64	bus = M(RX); RX = RX + 1
	OUT	5	; 65	bus = M(RX); RX = RX + 1
	OUT	6	; 66	bus = M(RX); RX = RX + 1
	OUT	7	; 67	bus = M(RX); RX = RX + 1
	DB	68H	; 68	undefined opcode?
	INP	1	; 69	M(RX) = bus; D = bus
	INP	2	; 6A	M(RX) = bus; D = bus
	INP	3	; 6B	M(RX) = bus; D = bus
	INP	4	; 6C	M(RX) = bus; D = bus
	INP	5	; 6D	M(RX) = bus; D = bus
	INP	6	; 6E	M(RX) = bus; D = bus
	INP	7	; 6F	M(RX) = bus; D = bus

	RET		; 70	X,P = M(RX); RX = RX + 1; IE = 1
	DIS		; 71	X,P = M(RX); RX = RX + 1; IE = 0
	LDXA		; 72	D = M(RX); RX = RX + 1
	STXD		; 73	M(RX) = D; RX = RX - 1
	ADC		; 74	DF,D = M(RX) + D + DF
	SDB		; 75	DF,D = M(RX) - D - !DF
	SHRC		; 76	D = D >> 1; DF = LSB(D); MSB(D) = DF (aka RSHR)
	SMB		; 77	DF,D = D - M(RX) - !DF
	SAV		; 78	M(RX) = T
	MARK		; 79	T = X,P; M(R2) = X,P; X = P; R2 = R2 - 1
	REQ		; 7A	Q = 0
	SEQ		; 7B	Q = 1
	ADCI	00H	; 7C nn	D,DF = M(RP) + D + DF; RP = RP + 1
	SDBI	00H	; 7D nn	D,DF = M(RP) - D - !DF; RP = RP + 1
	SHLC		; 7E	D = D << 1; DF = MSB(D); LSB(D) = DF (aka RSHL)
	SMBI	00H	; 7F nn	DF,D = D - M(RP) - !DF; RP = RP + 1

	GLO	R0	; 80	D = R0.lo
	GLO	R1	; 81	D = R.lo
	GLO	R2	; 82	D = R.lo
	GLO	R3	; 83	D = R.lo
	GLO	R4	; 84	D = R.lo
	GLO	R5	; 85	D = R.lo
	GLO	R6	; 86	D = R.lo
	GLO	R7	; 87	D = R.lo
	GLO	R8	; 88	D = R.lo
	GLO	R9	; 89	D = R.lo
	GLO	RA	; 8A	D = R.lo
	GLO	RB	; 8B	D = R.lo
	GLO	RC	; 8C	D = R.lo
	GLO	RD	; 8D	D = R.lo
	GLO	RE	; 8E	D = R.lo
	GLO	RF	; 8F	D = R.lo

	GHI	R0	; 90	D = R0.hi
	GHI	R1	; 91	D = R.hi
	GHI	R2	; 92	D = R.hi
	GHI	R3	; 93	D = R.hi
	GHI	R4	; 94	D = R.hi
	GHI	R5	; 95	D = R.hi
	GHI	R6	; 96	D = R.hi
	GHI	R7	; 97	D = R.hi
	GHI	R8	; 98	D = R.hi
	GHI	R9	; 99	D = R.hi
	GHI	RA	; 9A	D = R.hi
	GHI	RB	; 9B	D = R.hi
	GHI	RC	; 9C	D = R.hi
	GHI	RD	; 9D	D = R.hi
	GHI	RE	; 9E	D = R.hi
	GHI	RF	; 9F	D = R.hi

	PLO	R0	; A0	R0.lo = D
	PLO	R1	; A1	R.lo = D
	PLO	R2	; A2	R.lo = D
	PLO	R3	; A3	R.lo = D
	PLO	R4	; A4	R.lo = D
	PLO	R5	; A5	R.lo = D
	PLO	R6	; A6	R.lo = D
	PLO	R7	; A7	R.lo = D
	PLO	R8	; A8	R.lo = D
	PLO	R9	; A9	R.lo = D
	PLO	RA	; AA	R.lo = D
	PLO	RB	; AB	R.lo = D
	PLO	RC	; AC	R.lo = D
	PLO	RD	; AD	R.lo = D
	PLO	RE	; AE	R.lo = D
	PLO	RF	; AF	R.lo = D

	PHI	R0	; B0	R0.hi = D
	PHI	R1	; B1	R.hi = D
	PHI	R2	; B2	R.hi = D
	PHI	R3	; B3	R.hi = D
	PHI	R4	; B4	R.hi = D
	PHI	R5	; B5	R.hi = D
	PHI	R6	; B6	R.hi = D
	PHI	R7	; B7	R.hi = D
	PHI	R8	; B8	R.hi = D
	PHI	R9	; B9	R.hi = D
	PHI	RA	; BA	R.hi = D
	PHI	RB	; BB	R.hi = D
	PHI	RC	; BC	R.hi = D
	PHI	RD	; BD	R.hi = D
	PHI	RE	; BE	R.hi = D
	PHI	RF	; BF	R.hi = D

	LBR	.	; C0 nnnn - long branch always
	LBQ	.	; C1 nnnn - long branch if Q=1
	LBZ	.	; C2 nnnn - long branch if D=0
	LBDF	.	; C3 nnnn - long branch if DF=1
	NOP		; C4	no-operation
	LSNQ		; C5	skip 2 bytes if Q=0
	LSNZ		; C6	skip 2 bytes if D!=0
	LSNF		; C7	skip 2 bytes if DF=0
	LSKP		; C8	RP = RP + 2 (skip 2 bytes) (aka NLBR nnnn)
	LBNQ	.	; C9 nnnn - long branch if Q=0
	LBNZ	.	; CA nnnn - long branch if D!=0
	LBNF	.	; CB nnnn - long branch if DF=0
	LSIE		; CC	skip 2 bytes if IE=1
	LSQ		; CD	skip 2 bytes if Q=1
	LSZ		; CE	skip 2 bytes if D=0
	LSDF		; CF	skip 2 bytes if DF=1

	SEP	R0	; D0	P = 0
	SEP	R1	; D1	P = 1
	SEP	R2	; D2	P = 2
	SEP	R3	; D3	P = 3
	SEP	R4	; D4	P = 4
	SEP	R5	; D5	P = 5
	SEP	R6	; D6	P = 6
	SEP	R7	; D7	P = 7
	SEP	R8	; D8	P = 8
	SEP	R9	; D9	P = 9
	SEP	RA	; DA	P = A
	SEP	RB	; DB	P = B
	SEP	RC	; DC	P = C
	SEP	RD	; DD	P = D
	SEP	RE	; DE	P = E
	SEP	RF	; DF	P = F

	SEX	R0	; E0	X = 0
	SEX	R1	; E1	X = 1
	SEX	R2	; E2	X = 2
	SEX	R3	; E3	X = 3
	SEX	R4	; E4	X = 4
	SEX	R5	; E5	X = 5
	SEX	R6	; E6	X = 6
	SEX	R7	; E7	X = 7
	SEX	R8	; E8	X = 8
	SEX	R9	; E9	X = 9
	SEX	RA	; EA	X = A
	SEX	RB	; EB	X = B
	SEX	RC	; EC	X = C
	SEX	RD	; ED	X = D
	SEX	RE	; EE	X = E
	SEX	RF	; EF	X = F

	LDX		; F0	D = M(RX)
	OR		; F1	D = D | M(RX)
	AND		; F2	D = D & M(RX)
	XOR		; F3	D = D ^ M(RX)
	ADD		; F4	DF,D = M(RX) + D
	SD		; F5	DF,D = M(RX) - D
	SHR		; F6	D = D >> 1; DF = LSB(D); MSB(D) = 0
	SM		; F7	DF,D = D - M(RX)
	LDI	00H	; F8 nn	D = M(RP); RP = RP + 1
	ORI	00H	; F9 nn	D = D | M(RP); RP = RP + 1	
	ANI	00H	; FA nn	D = D & M(RP); RP = RP + 1
	XRI	00H	; FB nn	D = D ^ M(RP); RP = RP + 1
	ADI	00H	; FC nn	DF,D = M(RP) + D; RP = RP + 1
	SDI	00H	; FD nn	DF,D = M(RP) - D; RP = RP + 1
	SHL		; FE	D = D >> 1; DF = MSB(D); LSB(D) = 0
	SMI	00H	; FF nn	DF,D = D - M(RP) - !DF; RP = RP + 1

;	duplicate opcodes

	NBR	.+1	; 38 nn - never branch
	BPZ	.+1	; 33 nn - branch if positive or zero
	BGE	.+1	; 33 nn - branch if greater-than or equal
	BM	.+1	; 3B nn - branch if minus
	BL	.+1	; 3B nn - branch if less-than
	NLBR	.	; C8 nnnn - never long branch
	RSHR		; 76	ring shift right
	RSHL		; 7E	ring shift left

	IF	0

; addressing modes
	NOP		; C4	no operands
	INC	0	; 10	register without "R"
	INC	R0	; 10	register
	INC	RF	; 1F	register 15
	INC	R15	; 1F	register 15
	LDI	00H	; F8 00	immediate
	BR	.+1	; 30 nn	short branch
	LBR	.	; C0 nnnn - long branch
	OUT	7	; 67	IN/OUT instruction

	INC	16	; bad
	INC	-1	; bad
	LDN	R0	; bad
	OUT	0	; bad
	OUT	8	; bad

; branch test

	ORG	10FCH
	BR	.+2	; good
	BR	.+2	; bad

	ORG	11FFH
	BR	.+2	; good

	ORG	12FEH
	BR	.+1	; good

	ORG	13FFH
	BR	.	; bad

	ENDIF
