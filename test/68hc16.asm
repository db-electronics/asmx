	COM	$38,X		; 00 38
	DEC	$38,X		; 01 38
	NEG	$38,X		; 02 38
	INC	$38,X		; 03 38
	ASL	$38,X		; 04 38
	CLR	$38,X		; 05 38
	TST	$38,X		; 06 38
	FCB	$07		; 07
	BCLR	$3136,X,#$4D	; 08 4D 3136
	BSET	$3136,X,#$4D	; 09 4D 3136
	BRCLR	$3136,X,#$4D,.	; 0A 4D 3136 FB
	BRSET	$3136,X,#$4D,.	; 0B 4D 3136 FB
	ROL	$38,X		; 0C 38
	ASR	$38,X		; 0D 38
	ROR	$38,X		; 0E 38
	LSR	$38,X		; 0F 38

	COM	$38,Y		; 10 38
	DEC	$38,Y		; 11 38
	NEG	$38,Y		; 12 38
	INC	$38,Y		; 13 38
	ASL	$38,Y		; 14 38
	CLR	$38,Y		; 15 38
	TST	$38,Y		; 16 38
	FCB	$17		; 17 - prebyte
	BCLR	$3136,Y,#$4D	; 18 4D 3136
	BSET	$3136,Y,#$4D	; 19 4D 3136
	BRCLR	$3136,Y,#$4D,.	; 1A 4D 3136 FB
	BRSET	$3136,Y,#$4D,.	; 1B 4D 3136 FB
	ROL	$38,Y		; 1C 38
	ASR	$38,Y		; 1D 38
	ROR	$38,Y		; 1E 38
	LSR	$38,Y		; 1F 38

	COM	$38,Z		; 20 38
	DEC	$38,Z		; 21 38
	NEG	$38,Z		; 22 38
	INC	$38,Z		; 23 38
	ASL	$38,Z		; 24 38
	CLR	$38,Z		; 25 38
	TST	$38,Z		; 26 38
	FCB	$27		; 27 - prebyte
	BCLR	$3136,Z,#$4D	; 28 4D 3136
	BSET	$3136,Z,#$4D	; 29 4D 3136
	BRCLR	$3136,Z,#$4D,.	; 2A 4D 3136 FB
	BRSET	$3136,Z,#$4D,.	; 2B 4D 3136 FB
	ROL	$38,Z		; 2C 38
	ASR	$38,Z		; 2D 38
	ROR	$38,Z		; 2E 38
	LSR	$38,Z		; 2F 38

	MOVB	$38,X,$3136	; 30 38 3136
	MOVW	$38,X,$3136	; 31 38 3136
	MOVB	$3136,$38,X	; 32 38 3136
	MOVW	$3136,$38,X	; 33 38 3136
	PSHM	D,E,X,Y,Z,K,CCR	; 34 7F
	PULM	CCR,K,Z,Y,X,E,D	; 35 7F
	BSR	.		; 36 FE
	FCB	$37		; 37 - prebyte
	BCLR	$3136,#$4D	; 38 4D 3136
	BSET	$3136,#$4D	; 39 4D 3136
	BRCLR	$3136,#$4D,.	; 3A 4D 3136 FB
	BRSET	$3136,#$4D,.	; 3B 4D 3136 FB
	AIX	#$49		; 3C 49
	AIY	#$49		; 3D 49
	AIZ	#$49		; 3E 49
	AIS	#$49		; 3F 49

	SUBA	$38,X		; 40 38
	ADDA	$38,X		; 41 38
	SBCA	$38,X		; 42 38
	ADCA	$38,X		; 43 38
	EORA	$38,X		; 44 38
	LDAA	$38,X		; 45 38
	ANDA	$38,X		; 46 38
	ORAA	$38,X		; 47 38
	CMPA	$38,X		; 48 38
	BITA	$38,X		; 49 38
	STAA	$38,X		; 4A 38
	JMP	$13230,X	; 4B 013230
	CPX	$38,X		; 4C 38
	CPY	$38,X		; 4D 38
	CPZ	$38,X		; 4E 38
	CPS	$38,X		; 4F 38

	SUBA	$38,Y		; 50 38
	ADDA	$38,Y		; 51 38
	SBCA	$38,Y		; 52 38
	ADCA	$38,Y		; 53 38
	EORA	$38,Y		; 54 38
	LDAA	$38,Y		; 55 38
	ANDA	$38,Y		; 56 38
	ORAA	$38,Y		; 57 38
	CMPA	$38,Y		; 58 38
	BITA	$38,Y		; 59 38
	STAA	$38,Y		; 5A 38
	JMP	$13230,Y	; 5B 013230
	CPX	$38,Y		; 5C 38
	CPY	$38,Y		; 5D 38
	CPZ	$38,Y		; 5E 38
	CPS	$38,Y		; 5F 38

	SUBA	$38,Z		; 60 38
	ADDA	$38,Z		; 61 38
	SBCA	$38,Z		; 62 38
	ADCA	$38,Z		; 63 38
	EORA	$38,Z		; 64 38
	LDAA	$38,Z		; 65 38
	ANDA	$38,Z		; 66 38
	ORAA	$38,Z		; 67 38
	CMPA	$38,Z		; 68 38
	BITA	$38,Z		; 69 38
	STAA	$38,Z		; 6A 38
	JMP	$13230,Z	; 6B 013230
	CPX	$38,Z		; 6C 38
	CPY	$38,Z		; 6D 38
	CPZ	$38,Z		; 6E 38
	CPS	$38,Z		; 6F 38

	SUBA	#$38		; 70 38
	ADDA	#$38		; 71 38
	SBCA	#$38		; 72 38
	ADCA	#$38		; 73 38
	EORA	#$38		; 74 38
	LDAA	#$38		; 75 38
	ANDA	#$38		; 76 38
	ORAA	#$38		; 77 38
	CMPA	#$38		; 78 38
	BITA	#$38		; 79 38
	JMP	$3136		; 7A 3136
	MAC	#$38		; 7B 38
	ADDE	#$38		; 7C 38
	FCB	$7D		; 7D
	FCB	$7E		; 7E
	FCB	$7F		; 7F

	SUBD	$38,X		; 80 38
	ADDD	$38,X		; 81 38
	SBCD	$38,X		; 82 38
	ADCD	$38,X		; 83 38
	EORD	$38,X		; 84 38
	LDD	$38,X		; 85 38
	ANDD	$38,X		; 86 38
	ORD	$38,X		; 87 38
	CPD	$38,X		; 88 38
	JSR	$13230,X	; 89 013230
	STD	$38,X		; 8A 38
	BRSET	$38,X,#$4D,.	; 8B 4D 38 FC
	STX	$38,X		; 8C 38
	STY	$38,X		; 8D 38
	STZ	$38,X		; 8E 38
	STS	$38,X		; 8F 38

	SUBD	$38,Y		; 90 38
	ADDD	$38,Y		; 91 38
	SBCD	$38,Y		; 92 38
	ADCD	$38,Y		; 93 38
	EORD	$38,Y		; 94 38
	LDD	$38,Y		; 95 38
	ANDD	$38,Y		; 96 38
	ORD	$38,Y		; 97 38
	CPD	$38,Y		; 98 38
	JSR	$13230,Y	; 99 013230
	STD	$38,Y		; 9A 38
	BRSET	$38,Y,#$4D,.	; 9B 4D 38 FC
	STX	$38,Y		; 9C 38
	STY	$38,Y		; 9D 38
	STZ	$38,Y		; 9E 38
	STS	$38,Y		; 9F 38

	SUBD	$38,Z		; A0 38
	ADDD	$38,Z		; A1 38
	SBCD	$38,Z		; A2 38
	ADCD	$38,Z		; A3 38
	EORD	$38,Z		; A4 38
	LDD	$38,Z		; A5 38
	ANDD	$38,Z		; A6 38
	ORD	$38,Z		; A7 38
	CPD	$38,Z		; A8 38
	JSR	$13230,Z	; A9 013230
	STD	$38,Z		; AA 38
	BRSET	$38,Z,#$4D,.	; AB 4D 38 FC
	STX	$38,Z		; AC 38
	STY	$38,Z		; AD 38
	STZ	$38,Z		; AE 38
	STS	$38,Z		; AF 38

	BRA	.		; B0 FE
	BRN	.		; B1 FE
	BHI	.		; B2 FE
	BLS	.		; B3 FE
	BCC	.		; B4 FE - aka BHS
	BCS	.		; B5 FE - aka BLO
	BNE	.		; B6 FE
	BEQ	.		; B7 FE
	BVC	.		; B8 FE
	BVS	.		; B9 FE
	BPL	.		; BA FE
	BMI	.		; BB FE
	BGE	.		; BC FE
	BLT	.		; BD FE
	BGT	.		; BE FE
	BLE	.		; BF FE

	SUBB	$38,X		; C0 38
	ADDB	$38,X		; C1 38
	SBCB	$38,X		; C2 38
	ADCB	$38,X		; C3 38
	EORB	$38,X		; C4 38
	LDAB	$38,X		; C5 38
	ANDB	$38,X		; C6 38
	ORAB	$38,X		; C7 38
	CMPB	$38,X		; C8 38
	BITB	$38,X		; C9 38
	STAB	$38,X		; CA 38
	BRCLR	$38,X,#$4D,.	; CB 4D 38 FC
	LDX	$38,X		; CC 38
	LDY	$38,X		; CD 38
	LDZ	$38,X		; CE 38
	LDS	$38,X		; CF 38

	SUBB	$38,Y		; D0 38
	ADDB	$38,Y		; D1 38
	SBCB	$38,Y		; D2 38
	ADCB	$38,Y		; D3 38
	EORB	$38,Y		; D4 38
	LDAB	$38,Y		; D5 38
	ANDB	$38,Y		; D6 38
	ORAB	$38,Y		; D7 38
	CMPB	$38,Y		; D8 38
	BITB	$38,Y		; D9 38
	STAB	$38,Y		; DA 38
	BRCLR	$38,Y,#$4D,.	; DB 4D 38 FC
	LDX	$38,Y		; DC 38
	LDY	$38,Y		; DD 38
	LDZ	$38,Y		; DE 38
	LDS	$38,Y		; DF 38

	SUBB	$38,Z		; E0 38
	ADDB	$38,Z		; E1 38
	SBCB	$38,Z		; E2 38
	ADCB	$38,Z		; E3 38
	EORB	$38,Z		; E4 38
	LDAB	$38,Z		; E5 38
	ANDB	$38,Z		; E6 38
	ORAB	$38,Z		; E7 38
	CMPB	$38,Z		; E8 38
	BITB	$38,Z		; E9 38
	STAB	$38,Z		; EA 38
	BRCLR	$38,Z,#$4D,.	; EB 4D 38 FC
	LDX	$38,Z		; EC 38
	LDY	$38,Z		; ED 38
	LDZ	$38,Z		; EE 38
	LDS	$38,Z		; EF 38

	SUBB	#$38		; F0 38
	ADDB	#$38		; F1 38
	SBCB	#$38		; F2 38
	ADCB	#$38		; F3 38
	EORB	#$38		; F4 38
	LDAB	#$38		; F5 38
	ANDB	#$38		; F6 38
	ORAB	#$38		; F7 38
	CMPB	#$38		; F8 38
	BITB	#$38		; F9 38
	JSR	$3136		; FA 3136
	RMAC	#$38		; FB 38
	ADDD	#$38		; FC 38
	FCB	$FD		; FD
	FCB	$FE		; FE
	FCB	$FF		; FF

;	17xx instructions

	COM	$3136,X		; 1700 3136
	DEC	$3136,X		; 1701 3136
	NEG	$3136,X		; 1702 3136
	INC	$3136,X		; 1703 3136
	ASL	$3136,X		; 1704 3136
	CLR	$3136,X		; 1705 3136
	TST	$3136,X		; 1706 3136
	FCB	$17,$07		; 1707
	BCLR	$38,X,#$4D	; 1708 4D 38
	BSET	$38,X,#$4D	; 1709 4D 38
	FCB	$17,$0A		; 170A
	FCB	$17,$0B		; 170B
	ROL	$3136,X		; 170C 3136
	ASR	$3136,X		; 170D 3136
	ROR	$3136,X		; 170E 3136
	LSR	$3136,X		; 170F 3136

	COM	$3136,Y		; 1710 3136
	DEC	$3136,Y		; 1711 3136
	NEG	$3136,Y		; 1712 3136
	INC	$3136,Y		; 1713 3136
	ASL	$3136,Y		; 1714 3136
	CLR	$3136,Y		; 1715 3136
	TST	$3136,Y		; 1716 3136
	FCB	$17,$17		; 1717
	BCLR	$38,Y,#$4D	; 1718 4D 38
	BSET	$38,Y,#$4D	; 1719 4D 38
	FCB	$17,$1A		; 171A
	FCB	$17,$1B		; 171B
	ROL	$3136,Y		; 171C 3136
	ASR	$3136,Y		; 171D 3136
	ROR	$3136,Y		; 171E 3136
	LSR	$3136,Y		; 171F 3136

	COM	$3136,Z		; 1720 3136
	DEC	$3136,Z		; 1721 3136
	NEG	$3136,Z		; 1722 3136
	INC	$3136,Z		; 1723 3136
	ASL	$3136,Z		; 1724 3136
	CLR	$3136,Z		; 1725 3136
	TST	$3136,Z		; 1726 3136
	FCB	$17,$27		; 1727
	BCLR	$38,Z,#$4D	; 1728 4D 38
	BSET	$38,Z,#$4D	; 1729 4D 38
	FCB	$17,$2A		; 172A
	FCB	$17,$2B		; 172B
	ROL	$3136,Z		; 172C 3136
	ASR	$3136,Z		; 172D 3136
	ROR	$3136,Z		; 172E 3136
	LSR	$3136,Z		; 172F 3136

	COM	$3136		; 1730 3136
	DEC	$3136		; 1731 3136
	NEG	$3136		; 1732 3136
	INC	$3136		; 1733 3136
	ASL	$3136		; 1734 3136
	CLR	$3136		; 1735 3136
	TST	$3136		; 1736 3136
	FCB	$17,$37		; 1737
	FCB	$17,$38		; 1738
	FCB	$17,$39		; 1739
	FCB	$17,$3A		; 173A
	FCB	$17,$3B		; 173B
	ROL	$3136		; 173C 3136
	ASR	$3136		; 173D 3136
	ROR	$3136		; 173E 3136
	LSR	$3136		; 173F 3136

	SUBA	$3136,X		; 1740 3136
	ADDA	$3136,X		; 1741 3136
	SBCA	$3136,X		; 1742 3136
	ADCA	$3136,X		; 1743 3136
	EORA	$3136,X		; 1744 3136
	LDAA	$3136,X		; 1745 3136
	ANDA	$3136,X		; 1746 3136
	ORAA	$3136,X		; 1747 3136
	CMPA	$3136,X		; 1748 3136
	BITA	$3136,X		; 1749 3136
	STAA	$3136,X		; 174A 3136
	FCB	$17,$4B		; 174B
	CPX	$3136,X		; 174C 3136
	CPY	$3136,X		; 174D 3136
	CPZ	$3136,X		; 174E 3136
	CPS	$3136,X		; 174F 3136

	SUBA	$3136,Y		; 1750 3136
	ADDA	$3136,Y		; 1751 3136
	SBCA	$3136,Y		; 1752 3136
	ADCA	$3136,Y		; 1753 3136
	EORA	$3136,Y		; 1754 3136
	LDAA	$3136,Y		; 1755 3136
	ANDA	$3136,Y		; 1756 3136
	ORAA	$3136,Y		; 1757 3136
	CMPA	$3136,Y		; 1758 3136
	BITA	$3136,Y		; 1759 3136
	STAA	$3136,Y		; 175A 3136
	FCB	$17,$5B		; 175B
	CPX	$3136,Y		; 175C 3136
	CPY	$3136,Y		; 175D 3136
	CPZ	$3136,Y		; 175E 3136
	CPS	$3136,Y		; 175F 3136

	SUBA	$3136,Z		; 1760 3136
	ADDA	$3136,Z		; 1761 3136
	SBCA	$3136,Z		; 1762 3136
	ADCA	$3136,Z		; 1763 3136
	EORA	$3136,Z		; 1764 3136
	LDAA	$3136,Z		; 1765 3136
	ANDA	$3136,Z		; 1766 3136
	ORAA	$3136,Z		; 1767 3136
	CMPA	$3136,Z		; 1768 3136
	BITA	$3136,Z		; 1769 3136
	STAA	$3136,Z		; 176A 3136
	FCB	$17,$6B		; 176B
	CPX	$3136,Z		; 176C 3136
	CPY	$3136,Z		; 176D 3136
	CPZ	$3136,Z		; 176E 3136
	CPS	$3136,Z		; 176F 3136

	SUBA	$3136		; 1770 3136
	ADDA	$3136		; 1771 3136
	SBCA	$3136		; 1772 3136
	ADCA	$3136		; 1773 3136
	EORA	$3136		; 1774 3136
	LDAA	$3136		; 1775 3136
	ANDA	$3136		; 1776 3136
	ORAA	$3136		; 1777 3136
	CMPA	$3136		; 1778 3136
	BITA	$3136		; 1779 3136
	STAA	$3136		; 177A 3136
	FCB	$17,$7B		; 177B
	CPX	$3136		; 177C 3136
	CPY	$3136		; 177D 3136
	CPZ	$3136		; 177E 3136
	CPS	$3136		; 177F 3136

	FCB	$17,$80		; 1780
	FCB	$17,$81		; 1781
	FCB	$17,$82		; 1782
	FCB	$17,$83		; 1783
	FCB	$17,$84		; 1784
	FCB	$17,$85		; 1785
	FCB	$17,$86		; 1786
	FCB	$17,$87		; 1787
	FCB	$17,$88		; 1788
	FCB	$17,$89		; 1789
	FCB	$17,$8A		; 178A
	FCB	$17,$8B		; 178B
	STX	$3136,X		; 178C 3136
	STY	$3136,X		; 178D 3136
	STZ	$3136,X		; 178E 3136
	STS	$3136,X		; 178F 3136

	FCB	$17,$90		; 1790
	FCB	$17,$91		; 1791
	FCB	$17,$92		; 1792
	FCB	$17,$93		; 1793
	FCB	$17,$94		; 1794
	FCB	$17,$95		; 1795
	FCB	$17,$96		; 1796
	FCB	$17,$97		; 1797
	FCB	$17,$98		; 1798
	FCB	$17,$99		; 1799
	FCB	$17,$9A		; 179A
	FCB	$17,$9B		; 179B
	STX	$3136,Y		; 179C 3136
	STY	$3136,Y		; 179D 3136
	STZ	$3136,Y		; 179E 3136
	STS	$3136,Y		; 179F 3136

	FCB	$17,$A0		; 17A0
	FCB	$17,$A1		; 17A1
	FCB	$17,$A2		; 17A2
	FCB	$17,$A3		; 17A3
	FCB	$17,$A4		; 17A4
	FCB	$17,$A5		; 17A5
	FCB	$17,$A6		; 17A6
	FCB	$17,$A7		; 17A7
	FCB	$17,$A8		; 17A8
	FCB	$17,$A9		; 17A9
	FCB	$17,$AA		; 17AA
	FCB	$17,$AB		; 17AB
	STX	$3136,Z		; 17AC 3136
	STY	$3136,Z		; 17AD 3136
	STZ	$3136,Z		; 17AE 3136
	STS	$3136,Z		; 17AF 3136

	FCB	$17,$B0		; 17B0
	FCB	$17,$B1		; 17B1
	FCB	$17,$B2		; 17B2
	FCB	$17,$B3		; 17B3
	FCB	$17,$B4		; 17B4
	FCB	$17,$B5		; 17B5
	FCB	$17,$B6		; 17B6
	FCB	$17,$B7		; 17B7
	FCB	$17,$B8		; 17B8
	FCB	$17,$B9		; 17B9
	FCB	$17,$BA		; 17BA
	FCB	$17,$BB		; 17BB
	STX	$3136		; 17BC 3136
	STY	$3136		; 17BD 3136
	STZ	$3136		; 17BE 3136
	STS	$3136		; 17BF 3136

	SUBB	$3136,X		; 17C0 3136
	ADDB	$3136,X		; 17C1 3136
	SBCB	$3136,X		; 17C2 3136
	ADCB	$3136,X		; 17C3 3136
	EORB	$3136,X		; 17C4 3136
	LDAB	$3136,X		; 17C5 3136
	ANDB	$3136,X		; 17C6 3136
	ORAB	$3136,X		; 17C7 3136
	CMPB	$3136,X		; 17C8 3136
	BITB	$3136,X		; 17C9 3136
	STAB	$3136,X		; 17CA 3136
	FCB	$17,$CB		; 17CB
	LDX	$3136,X		; 17CC 3136
	LDY	$3136,X		; 17CD 3136
	LDZ	$3136,X		; 17CE 3136
	LDS	$3136,X		; 17CF 3136

	SUBB	$3136,Y		; 17D0 3136
	ADDB	$3136,Y		; 17D1 3136
	SBCB	$3136,Y		; 17D2 3136
	ADCB	$3136,Y		; 17D3 3136
	EORB	$3136,Y		; 17D4 3136
	LDAB	$3136,Y		; 17D5 3136
	ANDB	$3136,Y		; 17D6 3136
	ORAB	$3136,Y		; 17D7 3136
	CMPB	$3136,Y		; 17D8 3136
	BITB	$3136,Y		; 17D9 3136
	STAB	$3136,Y		; 17DA 3136
	FCB	$17,$DB		; 17DB
	LDX	$3136,Y		; 17DC 3136
	LDY	$3136,Y		; 17DD 3136
	LDZ	$3136,Y		; 17DE 3136
	LDS	$3136,Y		; 17DF 3136

	SUBB	$3136,Z		; 17E0 3136
	ADDB	$3136,Z		; 17E1 3136
	SBCB	$3136,Z		; 17E2 3136
	ADCB	$3136,Z		; 17E3 3136
	EORB	$3136,Z		; 17E4 3136
	LDAB	$3136,Z		; 17E5 3136
	ANDB	$3136,Z		; 17E6 3136
	ORAB	$3136,Z		; 17E7 3136
	CMPB	$3136,Z		; 17E8 3136
	BITB	$3136,Z		; 17E9 3136
	STAB	$3136,Z		; 17EA 3136
	FCB	$17,$EB		; 17EB
	LDX	$3136,Z		; 17EC 3136
	LDY	$3136,Z		; 17ED 3136
	LDZ	$3136,Z		; 17EE 3136
	LDS	$3136,Z		; 17EF 3136

	SUBB	$3136		; 17F0 3136
	ADDB	$3136		; 17F1 3136
	SBCB	$3136		; 17F2 3136
	ADCB	$3136		; 17F3 3136
	EORB	$3136		; 17F4 3136
	LDAB	$3136		; 17F5 3136
	ANDB	$3136		; 17F6 3136
	ORAB	$3136		; 17F7 3136
	CMPB	$3136		; 17F8 3136
	BITB	$3136		; 17F9 3136
	STAB	$3136		; 17FA 3136
	FCB	$17,$FB		; 17FB
	LDX	$3136		; 17FC 3136
	LDY	$3136		; 17FD 3136
	LDZ	$3136		; 17FE 3136
	LDS	$3136		; 17FF 3136

;	27xx instructions

	COMW	$3136,X		; 2700 3136
	DECW	$3136,X		; 2701 3136
	NEGW	$3136,X		; 2702 3136
	INCW	$3136,X		; 2703 3136
	ASLW	$3136,X		; 2704 3136
	CLRW	$3136,X		; 2705 3136
	TSTW	$3136,X		; 2706 3136
	FCB	$27,$07		; 2707
	BCLRW	$3136,X,#$4D	; 2708 4D 3136
	BSETW	$3136,X,#$4D	; 2709 4D 3136
	FCB	$27,$0A		; 270A
	FCB	$27,$0B		; 270B
	ROLW	$3136,X		; 270C 3136
	ASRW	$3136,X		; 270D 3136
	RORW	$3136,X		; 270E 3136
	LSRW	$3136,X		; 270F 3136

	COMW	$3136,Y		; 2710 3136
	DECW	$3136,Y		; 2711 3136
	NEGW	$3136,Y		; 2712 3136
	INCW	$3136,Y		; 2713 3136
	ASLW	$3136,Y		; 2714 3136
	CLRW	$3136,Y		; 2715 3136
	TSTW	$3136,Y		; 2716 3136
	FCB	$27,$17		; 2717
	BCLRW	$3136,Y,#$4D	; 2718 4D 3136
	BSETW	$3136,Y,#$4D	; 2719 4D 3136
	FCB	$27,$1A		; 271A
	FCB	$27,$1B		; 271B
	ROLW	$3136,Y		; 271C 3136
	ASRW	$3136,Y		; 271D 3136
	RORW	$3136,Y		; 271E 3136
	LSRW	$3136,Y		; 271F 3136

	COMW	$3136,Z		; 2720 3136
	DECW	$3136,Z		; 2721 3136
	NEGW	$3136,Z		; 2722 3136
	INCW	$3136,Z		; 2723 3136
	ASLW	$3136,Z		; 2724 3136
	CLRW	$3136,Z		; 2725 3136
	TSTW	$3136,Z		; 2726 3136
	FCB	$27,$27		; 2727
	BCLRW	$3136,Z,#$4D	; 2728 4D 3136
	BSETW	$3136,Z,#$4D	; 2729 4D 3136
	FCB	$27,$2A		; 272A
	FCB	$27,$2B		; 272B
	ROLW	$3136,Z		; 272C 3136
	ASRW	$3136,Z		; 272D 3136
	RORW	$3136,Z		; 272E 3136
	LSRW	$3136,Z		; 272F 3136

	COMW	$3136		; 2730 3136
	DECW	$3136		; 2731 3136
	NEGW	$3136		; 2732 3136
	INCW	$3136		; 2733 3136
	ASLW	$3136		; 2734 3136
	CLRW	$3136		; 2735 3136
	TSTW	$3136		; 2736 3136
	FCB	$27,$37		; 2737
	BCLRW	$3136,#$4D	; 2738 4D 3136
	BSETW	$3136,#$4D	; 2739 4D 3136
	FCB	$27,$3A		; 273A
	FCB	$27,$3B		; 273B
	ROLW	$3136		; 273C 3136
	ASRW	$3136		; 273D 3136
	RORW	$3136		; 273E 3136
	LSRW	$3136		; 273F 3136

	SUBA	E,X		; 2740
	ADDA	E,X		; 2741
	SBCA	E,X		; 2742
	ADCA	E,X		; 2743
	EORA	E,X		; 2744
	LDAA	E,X		; 2745
	ANDA	E,X		; 2746
	ORAA	E,X		; 2747
	CMPA	E,X		; 2748
	BITA	E,X		; 2749
	STAA	E,X		; 274A
	FCB	$27,$4B		; 274B
	NOP			; 274C - TXX?
	TYX			; 274D
	TZX			; 274E
	TSX			; 274F

	SUBA	E,Y		; 2750
	ADDA	E,Y		; 2751
	SBCA	E,Y		; 2752
	ADCA	E,Y		; 2753
	EORA	E,Y		; 2754
	LDAA	E,Y		; 2755
	ANDA	E,Y		; 2756
	ORAA	E,Y		; 2757
	CMPA	E,Y		; 2758
	BITA	E,Y		; 2759
	STAA	E,Y		; 275A
	FCB	$27,$5B		; 275B
	TXY			; 275C
	FCB	$27,$5D		; 275D
	TZY			; 275E
	TSY			; 275F

	SUBA	E,Z		; 2760
	ADDA	E,Z		; 2761
	SBCA	E,Z		; 2762
	ADCA	E,Z		; 2763
	EORA	E,Z		; 2764
	LDAA	E,Z		; 2765
	ANDA	E,Z		; 2766
	ORAA	E,Z		; 2767
	CMPA	E,Z		; 2768
	BITA	E,Z		; 2769
	STAA	E,Z		; 276A
	FCB	$27,$6B		; 276B
	TXZ			; 276C
	TYZ			; 276D
	FCB	$27,$6E		; 276E
	TSZ			; 276F

	COME			; 2770
	DECE			; 2771
	NEGE			; 2772
	INCE			; 2773
	ASLE			; 2774
	CLRE			; 2775
	TSTE			; 2776
	RTI			; 2777
	ADE			; 2778
	SDE			; 2779
	XGDE			; 277A
	TDE			; 277B
	ROLE			; 277C
	ASRE			; 277D
	RORE			; 277E
	LSRE			; 277F

	SUBD	E,X		; 2780
	ADDD	E,X		; 2781
	SBCD	E,X		; 2782
	ADCD	E,X		; 2783
	EORD	E,X		; 2784
	LDD	E,X		; 2785
	ANDD	E,X		; 2786
	ORD	E,X		; 2787
	CPD	E,X		; 2788
	FCB	$27,$89		; 2789
	STD	E,X		; 278A
	FCB	$27,$8B		; 278B
	FCB	$27,$8C		; 278C
	FCB	$27,$8D		; 278D
	FCB	$27,$8E		; 278E
	FCB	$27,$8F		; 278F

	SUBD	E,Y		; 2790
	ADDD	E,Y		; 2791
	SBCD	E,Y		; 2792
	ADCD	E,Y		; 2793
	EORD	E,Y		; 2794
	LDD	E,Y		; 2795
	ANDD	E,Y		; 2796
	ORD	E,Y		; 2797
	CPD	E,Y		; 2798
	FCB	$27,$99		; 2799
	STD	E,Y		; 279A
	FCB	$27,$9B		; 279B
	FCB	$27,$9C		; 279C
	FCB	$27,$9D		; 279D
	FCB	$27,$9E		; 279E
	FCB	$27,$9F		; 279F

	SUBD	E,Z		; 27A0
	ADDD	E,Z		; 27A1
	SBCD	E,Z		; 27A2
	ADCD	E,Z		; 27A3
	EORD	E,Z		; 27A4
	LDD	E,Z		; 27A5
	ANDD	E,Z		; 27A6
	ORD	E,Z		; 27A7
	CPD	E,Z		; 27A8
	FCB	$27,$A9		; 27A9
	STD	E,Z		; 27AA
	FCB	$27,$AB		; 27AB
	FCB	$27,$AC		; 27AC
	FCB	$27,$AD		; 27AD
	FCB	$27,$AE		; 27AE
	FCB	$27,$AF		; 27AF

	LDHI			; 27B0
	TEDM			; 27B1
	TEM			; 27B2
	TMXED			; 27B3
	TMER			; 27B4
	TMET			; 27B5
	ASLM			; 27B6
	CLRM			; 27B7
	PSHMAC			; 27B8
	PULMAC			; 27B9
	ASRM			; 27BA
	TEKB			; 27BB
	FCB	$27,$BC		; 27BC
	FCB	$27,$BD		; 27BD
	FCB	$27,$BE		; 27BE
	FCB	$27,$BF		; 27BF

	SUBB	E,X		; 27C0
	ADDB	E,X		; 27C1
	SBCB	E,X		; 27C2
	ADCB	E,X		; 27C3
	EORB	E,X		; 27C4
	LDAB	E,X		; 27C5
	ANDB	E,X		; 27C6
	ORAB	E,X		; 27C7
	CMPB	E,X		; 27C8
	BITB	E,X		; 27C9
	STAB	E,X		; 27CA
	FCB	$27,$CB		; 27CB
	FCB	$27,$CC		; 27CC
	FCB	$27,$CD		; 27CD
	FCB	$27,$CE		; 27CE
	FCB	$27,$CF		; 27CF

	SUBB	E,Y		; 27D0
	ADDB	E,Y		; 27D1
	SBCB	E,Y		; 27D2
	ADCB	E,Y		; 27D3
	EORB	E,Y		; 27D4
	LDAB	E,Y		; 27D5
	ANDB	E,Y		; 27D6
	ORAB	E,Y		; 27D7
	CMPB	E,Y		; 27D8
	BITB	E,Y		; 27D9
	STAB	E,Y		; 27DA
	FCB	$27,$DB		; 27DB
	FCB	$27,$DC		; 27DC
	FCB	$27,$DD		; 27DD
	FCB	$27,$DE		; 27DE
	FCB	$27,$DF		; 27DF

	SUBB	E,Z		; 27E0
	ADDB	E,Z		; 27E1
	SBCB	E,Z		; 27E2
	ADCB	E,Z		; 27E3
	EORB	E,Z		; 27E4
	LDAB	E,Z		; 27E5
	ANDB	E,Z		; 27E6
	ORAB	E,Z		; 27E7
	CMPB	E,Z		; 27E8
	BITB	E,Z		; 27E9
	STAB	E,Z		; 27EA
	FCB	$27,$EB		; 27EB
	FCB	$27,$EC		; 27EC
	FCB	$27,$ED		; 27ED
	FCB	$27,$EE		; 27EE
	FCB	$27,$EF		; 27EF

	COMD			; 27F0
	LPSTOP			; 27F1
	NEGD			; 27F2
	WAI			; 27F3
	ASLD			; 27F4
	CLRD			; 27F5
	TSTD			; 27F6
	RTS			; 27F7
	SXT			; 27F8
	LBSR	.		; 27F9 FFFC
	TBEK			; 27FA
	TED			; 27FB
	ROLD			; 27FC
	ASRD			; 27FD
	RORD			; 27FE
	LSRD			; 27FF

;	37xx instructions

	COMA			; 3700
	DECA			; 3701
	NEGA			; 3702
	INCA			; 3703
	ASLA			; 3704
	CLRA			; 3705
	TSTA			; 3706
	TBA			; 3707
	PSHA			; 3708
	PULA			; 3709
	SBA			; 370A
	ABA			; 370B
	ROLA			; 370C
	ASRA			; 370D
	RORA			; 370E
	LSRA			; 370F

	COMB			; 3710
	DECB			; 3711
	NEGB			; 3712
	INCB			; 3713
	ASLB			; 3714
	CLRB			; 3715
	TSTB			; 3716
	TAB			; 3717
	PSHB			; 3718
	PULB			; 3719
	XGAB			; 371A
	CBA			; 371B
	ROLB			; 371C
	ASRB			; 371D
	RORB			; 371E
	LSRB			; 371F

	SWI			; 3720
	DAA			; 3721
	ACE			; 3722
	ACED			; 3723
	MUL			; 3724
	EMUL			; 3725
	EMULS			; 3726
	FMULS			; 3727
	EDIV			; 3728
	EDIVS			; 3729
	IDIV			; 372A
	FDIV			; 372B
	TPD			; 372C
	TDP			; 372D
	FCB	$37,$2E		; 372E
	TDMSK			; 372F

	SUBE	#$3136		; 3730 3136
	ADDE	#$3136		; 3731 3136
	SBCE	#$3136		; 3732 3136
	ADCE	#$3136		; 3733 3136
	EORE	#$3136		; 3734 3136
	LDE	#$3136		; 3735 3136
	ANDE	#$3136		; 3736 3136
	ORE	#$3136		; 3737 3136
	CPE	#$3136		; 3738 3136
	FCB	$37,$39		; 3739
	ANDP	#$3136		; 373A 3136
	ORP	#$3136		; 373B 3136
	AIX	#$3136		; 373C 3136
	AIY	#$3136		; 373D 3136
	AIZ	#$3136		; 373E 3136
	AIS	#$3136		; 373F 3136

	SUBE	$3136,X		; 3740 3136
	ADDE	$3136,X		; 3741 3136
	SBCE	$3136,X		; 3742 3136
	ADCE	$3136,X		; 3743 3136
	EORE	$3136,X		; 3744 3136
	LDE	$3136,X		; 3745 3136
	ANDE	$3136,X		; 3746 3136
	ORE	$3136,X		; 3747 3136
	CPE	$3136,X		; 3748 3136
	FCB	$37,$49		; 3749
	STE	$3136,X		; 374A 3136
	FCB	$37,$4B		; 374B
	XGEX			; 374C
	AEX			; 374D
	TXS			; 374E
	ABX			; 374F

	SUBE	$3136,Y		; 3750 3136
	ADDE	$3136,Y		; 3751 3136
	SBCE	$3136,Y		; 3752 3136
	ADCE	$3136,Y		; 3753 3136
	EORE	$3136,Y		; 3754 3136
	LDE	$3136,Y		; 3755 3136
	ANDE	$3136,Y		; 3756 3136
	ORE	$3136,Y		; 3757 3136
	CPE	$3136,Y		; 3758 3136
	FCB	$37,$59		; 3759
	STE	$3136,Y		; 375A 3136
	FCB	$37,$5B		; 375B
	XGEY			; 375C
	AEY			; 375D
	TYS			; 375E
	ABY			; 375F

	SUBE	$3136,Z		; 3760 3136
	ADDE	$3136,Z		; 3761 3136
	SBCE	$3136,Z		; 3762 3136
	ADCE	$3136,Z		; 3763 3136
	EORE	$3136,Z		; 3764 3136
	LDE	$3136,Z		; 3765 3136
	ANDE	$3136,Z		; 3766 3136
	ORE	$3136,Z		; 3767 3136
	CPE	$3136,Z		; 3768 3136
	FCB	$37,$69		; 3769
	STE	$3136,Z		; 376A 3136
	FCB	$37,$6B		; 376B
	XGEZ			; 376C
	AEZ			; 376D
	TZS			; 376E
	ABZ			; 376F

	SUBE	$3136		; 3770 3136
	ADDE	$3136		; 3771 3136
	SBCE	$3136		; 3772 3136
	ADCE	$3136		; 3773 3136
	EORE	$3136		; 3774 3136
	LDE	$3136		; 3775 3136
	ANDE	$3136		; 3776 3136
	ORE	$3136		; 3777 3136
	CPE	$3136		; 3778 3136
	FCB	$37,$79		; 3779
	STE	$3136		; 377A 3136
	FCB	$37,$7B		; 377B
	CPX	#$3136		; 377C 3136
	CPY	#$3136		; 377D 3136
	CPZ	#$3136		; 377E 3136
	CPS	#$3136		; 377F 3136

	LBRA	.		; 3780 FFFC
	LBRN	.		; 3781 FFFC
	LBHI	.		; 3782 FFFC
	LBLS	.		; 3783 FFFC
	LBCC	.		; 3784 FFFC - aka LBHS
	LBCS	.		; 3785 FFFC - aka LBLO
	LBNE	.		; 3786 FFFC
	LBEQ	.		; 3787 FFFC
	LBVC	.		; 3788 FFFC
	LBVS	.		; 3789 FFFC
	LBPL	.		; 378A FFFC
	LBMI	.		; 378B FFFC
	LBGE	.		; 378C FFFC
	LBLT	.		; 378D FFFC
	LBGT	.		; 378E FFFC
	LBLE	.		; 378F FFFC

	LBMV	.		; 3790 FFFC
	LBEV	.		; 3791 FFFC
	FCB	$37,$92		; 3792
	FCB	$37,$93		; 3793
	FCB	$37,$94		; 3794
	FCB	$37,$95		; 3795
	FCB	$37,$96		; 3796
	FCB	$37,$97		; 3797
	FCB	$37,$98		; 3798
	FCB	$37,$99		; 3799
	FCB	$37,$9A		; 379A
	FCB	$37,$9B		; 379B
	TBXK			; 379C
	TBYK			; 379D
	TBZK			; 379E
	TBSK			; 379F

	FCB	$37,$A0		; 37A0
	FCB	$37,$A1		; 37A1
	FCB	$37,$A2		; 37A2
	FCB	$37,$A3		; 37A3
	FCB	$37,$A4		; 37A4
	FCB	$37,$A5		; 37A5
	BGND			; 37A6
	FCB	$37,$A7		; 37A7
	FCB	$37,$A8		; 37A8
	FCB	$37,$A9		; 37A9
	FCB	$37,$AA		; 37AA
	FCB	$37,$AB		; 37AB
	TXKB			; 37AC
	TYKB			; 37AD
	TZKB			; 37AE
	TSKB			; 37AF

	SUBD	#$3136		; 37B0 3136
	ADDD	#$3136		; 37B1 3136
	SBCD	#$3136		; 37B2 3136
	ADCD	#$3136		; 37B3 3136
	EORD	#$3136		; 37B4 3136
	LDD	#$3136		; 37B5 3136
	ANDD	#$3136		; 37B6 3136
	ORD	#$3136		; 37B7 3136
	CPD	#$3136		; 37B8 3136
	FCB	$37,$B9		; 37B9
	FCB	$37,$BA		; 37BA
	FCB	$37,$BB		; 37BB
	LDX	#$3136		; 37BC 3136
	LDY	#$3136		; 37BD 3136
	LDZ	#$3136		; 37BE 3136
	LDS	#$3136		; 37BF 3136

	SUBD	$3136,X		; 37C0 3136
	ADDD	$3136,X		; 37C1 3136
	SBCD	$3136,X		; 37C2 3136
	ADCD	$3136,X		; 37C3 3136
	EORD	$3136,X		; 37C4 3136
	LDD	$3136,X		; 37C5 3136
	ANDD	$3136,X		; 37C6 3136
	ORD	$3136,X		; 37C7 3136
	CPD	$3136,X		; 37C8 3136
	FCB	$37,$C9		; 37C9
	STD	$3136,X		; 37CA 3136
	FCB	$37,$CB		; 37CB
	XGDX			; 37CC
	ADX			; 37CD
	FCB	$37,$CE		; 37CE
	FCB	$37,$CF		; 37CF

	SUBD	$3136,Y		; 37D0 3136
	ADDD	$3136,Y		; 37D1 3136
	SBCD	$3136,Y		; 37D2 3136
	ADCD	$3136,Y		; 37D3 3136
	EORD	$3136,Y		; 37D4 3136
	LDD	$3136,Y		; 37D5 3136
	ANDD	$3136,Y		; 37D6 3136
	ORD	$3136,Y		; 37D7 3136
	CPD	$3136,Y		; 37D8 3136
	FCB	$37,$D9		; 37D9
	STD	$3136,Y		; 37DA 3136
	FCB	$37,$DB		; 37DB
	XGDY			; 37DC
	ADY			; 37DD
	FCB	$37,$DE		; 37DE
	FCB	$37,$DF		; 37DF

	SUBD	$3136,Z		; 37E0 3136
	ADDD	$3136,Z		; 37E1 3136
	SBCD	$3136,Z		; 37E2 3136
	ADCD	$3136,Z		; 37E3 3136
	EORD	$3136,Z		; 37E4 3136
	LDD	$3136,Z		; 37E5 3136
	ANDD	$3136,Z		; 37E6 3136
	ORD	$3136,Z		; 37E7 3136
	CPD	$3136,Z		; 37E8 3136
	FCB	$37,$E9		; 37E9
	STD	$3136,Z		; 37EA 3136
	FCB	$37,$EB		; 37EB
	XGDZ			; 37EC
	ADZ			; 37ED
	FCB	$37,$EE		; 37EE
	FCB	$37,$EF		; 37EF

	SUBD	$3136		; 37F0 3136
	ADDD	$3136		; 37F1 3136
	SBCD	$3136		; 37F2 3136
	ADCD	$3136		; 37F3 3136
	EORD	$3136		; 37F4 3136
	LDD	$3136		; 37F5 3136
	ANDD	$3136		; 37F6 3136
	ORD	$3136		; 37F7 3136
	CPD	$3136		; 37F8 3136
	FCB	$37,$F9		; 37F9
	STD	$3136		; 37FA 3136
	FCB	$37,$FB		; 37FB
	TPA			; 37FC
	TAP			; 37FD
	MOVB	$3136,$1234	; 37FE 3136 1234
	MOVW	$3136,$1234	; 37FF 3136 1234

;	other stuff

	MAC	3,8		; 7B 38
	RMAC	3,8		; FB 38
