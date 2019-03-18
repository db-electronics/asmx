; 68000/68010 instruction set tests

M68010  EQU     0

; proc

ea      EQU     $1234
ofs     EQU     $4321

; --- EA tests ---

        MOVE    D0,D0           ; 3000
        MOVE    A0,D0           ; 3008
        MOVE    (A0),D0         ; 3010
        MOVE    (A0)+,D0        ; 3018
        MOVE    -(A0),D0        ; 3020
        MOVE    ofs(A0),D0      ; 3028 4321
        MOVE    (ofs,A0),D0     ; 3028 4321
        MOVE    $12(A0,D0),D0   ; 3030 0012
        MOVE    ($12,A0,D0),D0  ; 3030 0012
        MOVE    (A0,D0),D0      ; 3030 0000
        MOVE    $12(A0,A0),D0   ; 3030 8012
        MOVE    ($12,A0,A0),D0  ; 3030 8012
        MOVE    (A0,A0),D0      ; 3030 8000
        MOVE    $1234,D0        ; 3038 1234
        MOVE    $12345678,D0    ; 3039 1234 5678
        MOVE.B  #$12,D0         ; 103C 0012
        MOVE    #$1234,D0       ; 303C 1234
        MOVE.W  #$1234,D0       ; 303C 1234
        MOVE.L  #$12345,D0      ; 203C 0001 2345
        MOVE    *(PC),D0        ; 303A FFFE
        MOVE    (*,PC),D0       ; 303A FFFE
        MOVE    *(PC,D0),D0     ; 303B 00FE
        MOVE    (*,PC,D0),D0    ; 303B 00FE
	MOVE	(PC,D0),D0	; 303B 0000
        MOVE    *(PC,A0),D0     ; 303B 80FE
        MOVE    (*,PC,A0),D0    ; 303B 80FE
	MOVE	(PC,A0),D0	; 303B 8000
        MOVE    $12345678,$12345678     ; 33F9 1234 5678 1234 5678
        MOVE.L  #$12345678,$12345678    ; 23FC 1234 5678 1234 5678
        MOVE    ofs(A2),ofs(A1)         ; 336A 4321 4321
        MOVE    $12(A2,D1),$12(A2,D1)   ; 31B0 0012 0012
        MOVE    $12(A2,D1.W),$12(A2,D1.W) ; 31B0 0012 0012
        MOVE    $12(A2,D1.L),$12(A2,D1.L) ; 35B2 1812 1812
        MOVE    (A2,D1),(A2,D1)         ; 35B2 1000 1000
        MOVE    (A2,D1.L),(A2,D1.L)     ; 35B2 1800 1800
        MOVE.L  #$12345678,$12(A2,D1)   ; 25BC 1234 5678 1012
        MOVE    *(PC,D1),$12(A2,D1)     ; 35BB 10FE 1012
        MOVE    *(PC,D1.L),$12(A2,D1)   ; 35BB 18FE 1012
        MOVE    *(PC,D1),$12345678      ; 33FB 10FE 1234 5678
        MOVE    *(PC,D1.W),$12345678    ; 33FB 10FE 1234 5678
        MOVE    *(PC,D1.L),$12345678    ; 33FB 18FE 1234 5678
        MOVE    (PC,D1.L),$12345678     ; 33FB 1800 1234 5678

; --- opcodes ---

        ABCD    D2,D1           ; C302
        ABCD.B  D2,D1           ; C302
        ABCD    -(A2),-(A1)     ; C30A
        ABCD.B  -(A2),-(A1)     ; C30A

        ADD     ea,D1           ; D278
        ADD.B   #$12,D1         ; 0601 0012
        ADD     #$1234,D1       ; 0641 1234
        ADD.W   #$1234,D1       ; 0641 1234
        ADD.L   #$12345678,D1   ; 0681 1234 5678
        ADD     D2,D1           ; C242

        ADDA    ea,A1           ; D2F8
        ADDA    #$1234,A1       ; D2FC 1234 / 43E9 1234
        ADDA.W  #$1234,A1       ; D2FC 1234 / 43E9 1234
        ADDA.L  #$12345678,A1   ; D3FC 1234 5678
        ADDA    D2,A1           ; D2C2

        ADDI.B  #$12,D1         ; 0601 0012
        ADDI    #$1234,D1       ; 0641 1234
        ADDI.W  #$1234,D1       ; 0641 1234
        ADDI.L  #$12345678,D1   ; 0681 1234 5678

        ADDQ    #1,D1           ; 5241
        ADDQ    #8,D1           ; 5041

        ADDX.B  D2,D1           ; D302
        ADDX    D2,D1           ; D342
        ADDX.W  D2,D1           ; D342
        ADDX.L  D2,D1           ; D382
        ADDX.B  -(A2),-(A1)     ; D30A
        ADDX    -(A2),-(A1)     ; D34A
        ADDX.W  -(A2),-(A1)     ; D34A
        ADDX.L  -(A2),-(A1)     ; D38A

        AND     ea,D1           ; C278 1234
        AND.B   #$12,D1         ; 0201 0012
        AND     #$1234,D1       ; 0241 1234
        AND.W   #$1234,D1       ; 0241 1234
        AND.L   #$12345678,D1   ; 0281 1234 5678
        AND     D2,D1           ; C242

        ANDI.B  #$12,D1         ; 0201 0012
        ANDI    #$1234,D1       ; 0241 1234
        ANDI.W  #$1234,D1       ; 0241 1234
        ANDI.L  #$12345678,D1   ; 0281 1234 5678

        ANDI    #$12,CCR        ; 023C 0012
        ANDI.B  #$12,CCR        ; 023C 0012

        ANDI    #$1234,SR       ; 027C 1234 (priv)
        ANDI.W  #$1234,SR       ; 027C 1234 (priv)

        ASL.B   D2,D1           ; E521
        ASL     D2,D1           ; E561
        ASL.W   D2,D1           ; E561
        ASL.L   D2,D1           ; E5A1
        ASL.B   #1,D1           ; E301
        ASL     #1,D1           ; E341
        ASL.W   #1,D1           ; E341
        ASL.L   #1,D1           ; E381
        ASL     #8,D1           ; E141
        ASL     ea              ; E1F8 1234
        ASL.W   ea              ; E1F8 1234

        ASR.B   D2,D1           ; E421
        ASR     D2,D1           ; E461
        ASR.W   D2,D1           ; E461
        ASR.L   D2,D1           ; E4A1
        ASR.B   #1,D1           ; E201
        ASR     #1,D1           ; E241
        ASR.W   #1,D1           ; E241
        ASR.L   #1,D1           ; E281
        ASR     #8,D1           ; E041
        ASR     ea              ; E0F8 1234
        ASR.W   ea              ; E0F8 1234

        BHI     *+$1236         ; 6200 1234
        BLS     *+$1236         ; 6300 1234
        BCC     *+$1236         ; 6400 1234
        BHS     *+$1236         ; 6400 1234
        BCS     *+$1236         ; 6500 1234
        BLO     *+$1236         ; 6500 1234
        BNE     *+$1236         ; 6600 1234
        BEQ     *+$1236         ; 6700 1234
        BVC     *+$1236         ; 6800 1234
        BVS     *+$1236         ; 6900 1234
        BPL     *+$1236         ; 6A00 1234
        BMI     *+$1236         ; 6B00 1234
        BGE     *+$1236         ; 6C00 1234
        BLT     *+$1236         ; 6D00 1234
        BGT     *+$1236         ; 6E00 1234
        BLE     *+$1236         ; 6F00 1234

        BCC.W   *+$1236         ; 6400 1234
        BCC.B   *               ; 64FE
        BCC.S   *               ; 64FE

        BCHG    D2,ea           ; 0578 1234
        BCHG.B  D2,ea           ; 0578 1234
        BCHG    D2,D1           ; 0541
        BCHG.L  D2,D1           ; 0541
        BCHG    #0,ea           ; 0878 0000 1234
        BCHG.B  #0,ea           ; 0878 0000 1234
        BCHG    #7,ea           ; 0878 0007 1234
        BCHG    #0,D1           ; 0841 0000
        BCHG.L  #0,D1           ; 0841 0000
        BCHG    #31,D1          ; 0841 001F
        BCHG    D2,D1           ; 0541
        BCHG.L  D2,D1           ; 0541

        BCLR    D2,ea           ; 05B8 1234
        BCLR.B  D2,ea           ; 05B8 1234
        BCLR    D2,D1           ; 0581
        BCLR.L  D2,D1           ; 0581
        BCLR    #0,ea           ; 08B8 0000 1234
        BCLR.B  #0,ea           ; 08B8 0000 1234
        BCLR    #7,ea           ; 08B8 0007 1234
        BCLR    #0,D1           ; 0881 0000
        BCLR.L  #0,D1           ; 0881 0000
        BCLR    #31,D1          ; 0881 001F
        BCLR    D2,D1           ; 0581
        BCLR.L  D2,D1           ; 0581

        BKPT    #5              ; 484D (68010)

        BRA.B   *               ; 60FE
        BRA.S   *               ; 60FE
        BRA.W   *+$1236         ; 6000 1234
        BRA     *+$1236         ; 6000 1234
        BRA     *+12            ; 6000 000A / 600A

        BSET    D2,ea           ; 05F8 1234
        BSET.B  D2,ea           ; 05F8 1234
        BSET    D2,D1           ; 05C1
        BSET.L  D2,D1           ; 05C1
        BSET    #0,ea           ; 08F8 0000 1234
        BSET.B  #0,ea           ; 08F8 0000 1234
        BSET    #7,ea           ; 08F8 0007 1234
        BSET    #0,D1           ; 08C1 0000
        BSET.L  #0,D1           ; 08C1 0000
        BSET    #31,D1          ; 08C1 001F
        BSET    D2,D1           ; 05C1
        BSET.L  D2,D1           ; 05C1

        BSR.B   *               ; 61FE
        BSR.S   *               ; 61FE
        BSR.W   *+$1236         ; 6100 1234
        BSR     *+$1236         ; 6100 1234
        BSR     *+12            ; 6100 000A / 610A

        BTST    D2,ea           ; 0538 1234
        BTST.B  D2,ea           ; 0538 1234
        BTST    D2,D1           ; 0501
        BTST.L  D2,D1           ; 0501
        BTST    #0,ea           ; 0838 0000 1234
        BTST.B  #0,ea           ; 0838 0000 1234
        BTST    #7,ea           ; 0838 0007 1234
        BTST    #0,D1           ; 0801 0000
        BTST.L  #0,D1           ; 0801 0000
        BTST    #31,D1          ; 0801 001F
        BTST    D2,D1           ; 0501
        BTST.L  D2,D1           ; 0501

        CHK     ea,D1           ; 43B8 1234
        CHK     #$1234,D1       ; 43BC 1234
        CHK.W   #$1234,D1       ; 43BC 1234

        CLR.B   ea              ; 4238 1234
        CLR     ea              ; 4278 1234
        CLR.W   ea              ; 4278 1234
        CLR.L   ea              ; 42B8 1234

        CMP     ea,D1           ; B278 1234
        CMP.B   #$12,D1         ; 0C01 0012
        CMP     #$1234,D1       ; 0C41 1234
        CMP.W   #$1234,D1       ; 0C41 1234
        CMP.L   #$12345678,D1   ; 0C81 1234 5678
        CMP.L   A2,D1           ; B28A
        CMP.L   D1,D2           ; B342

        CMPA    ea,A1           ; B2F8 1234
        CMPA    #$1234,A1       ; B2FC 1234
        CMPA.W  #$1234,A1       ; B2FC 1234
        CMPA.L  #$12345678,A1   ; B3FC 1234 5678
        CMPA.L  D2,A1           ; B3C2

        CMPI.B  #$12,D1         ; 0C01 0012
        CMPI    #$1234,D1       ; 0C41 1234
        CMPI.W  #$1234,D1       ; 0C41 1234
        CMPI.L  #$12345678,D1   ; 0C81 1234 5678

        CMPM    (A2)+,(A1)+     ; B34A

        DBT     D1,*            ; 50C9 FFFE
        DBRA    D1,*            ; 51C9 FFFE
        DBF     D1,*            ; 51C9 FFFE
        DBHI    D1,*            ; 52C9 FFFE
        DBLS    D1,*            ; 53C9 FFFE
        DBCC    D1,*            ; 54C9 FFFE
        DBHS    D1,*            ; 54C9 FFFE
        DBCS    D1,*            ; 55C9 FFFE
        DBLO    D1,*            ; 55C9 FFFE
        DBNE    D1,*            ; 56C9 FFFE
        DBEQ    D1,*            ; 57C9 FFFE
        DBVC    D1,*            ; 58C9 FFFE
        DBVS    D1,*            ; 59C9 FFFE
        DBPL    D1,*            ; 5AC9 FFFE
        DBMI    D1,*            ; 5BC9 FFFE
        DBGE    D1,*            ; 5CC9 FFFE
        DBLT    D1,*            ; 5DC9 FFFE
        DBGT    D1,*            ; 5EC9 FFFE
        DBLE    D1,*            ; 5FC9 FFFE

        DIVS    ea,D1           ; 83F8 1234
        DIVS.W  ea,D1           ; 83F8 1234

        DIVU    ea,D1           ; 82F8 1234
        DIVU.W  ea,D1           ; 82F8 1234

        EOR.B   D1,ea           ; B338 1234
        EOR     D1,ea           ; B378 1234
        EOR.W   D1,ea           ; B378 1234
        EOR.L   D1,ea           ; B3B8 1234

        EORI.B  #$12,ea         ; 0A38 0012 1234
        EORI    #$1234,ea       ; 0A78 1234 1234
        EORI.W  #$1234,ea       ; 0A78 1234 1234
        EORI.L  #$12345678,ea   ; 0AB8 1234 5678 1234
        EORI    #$1234,D1       ; 0A41 1234

        EORI    #$12,CCR        ; 0A3C 0012
        EORI.B  #$12,CCR        ; 0A3C 0012

        EORI    #$1234,SR       ; 0A7C 1234 (priv)
        EORI.W  #$1234,SR       ; 0A7C 1234 (priv)

        EXG     D2,D1           ; C541
        EXG     D1,D2           ; C342
        EXG     A2,A1           ; C549
        EXG     A1,A2           ; C34A
        EXG     D2,A1           ; C589
        EXG     A1,D2           ; C589

        EXT     D1              ; 4881
        EXT.W   D1              ; 4881
        EXT.L   D1              ; 48C1

        ILLEGAL                 ; 4AFC

        JMP     ea              ; 4EF8 1234
        JMP     (A0)            ; 4ED0

        JSR     ea              ; 4EB8 1234
        JSR     (A0)            ; 4E90

        LEA     ea,A1           ; 43F8 1234
        LEA     (A0),A1         ; 43D0

        LINK    A6,#-$1234      ; 4E56 EDCC
        LINK.W  A6,#-$1234      ; 4E56 EDCC

        LSL.B   D2,D1           ; E529
        LSL     D2,D1           ; E569
        LSL.W   D2,D1           ; E569
        LSL.L   D2,D1           ; E5A9
        LSL.B   #1,D1           ; E309
        LSL     #1,D1           ; E349
        LSL.W   #1,D1           ; E349
        LSL.L   #1,D1           ; E389
        LSL     #8,D1           ; E149
        LSL     ea              ; E3F8 1234
        LSL.W   ea              ; E3F8 1234

        LSR.B   D2,D1           ; E429
        LSR     D2,D1           ; E469
        LSR.W   D2,D1           ; E469
        LSR.L   D2,D1           ; E4A9
        LSR.B   #1,D1           ; E209
        LSR     #1,D1           ; E249
        LSR.W   #1,D1           ; E249
        LSR.L   #1,D1           ; E289
        LSR     #8,D1           ; E049
        LSR     ea              ; E2F8 1234
        LSR.W   ea              ; E2F8 1234

        MOVE.B  ea,D1           ; 1238 1234
        MOVE    ea,D1           ; 3238 1234
        MOVE.W  ea,D1           ; 3238 1234
        MOVE.L  ea,D1           ; 2238 1234
        MOVE.B  #$12,ea         ; 11FC 0012 1234
        MOVE    #$1234,ea       ; 31FC 1234 1234
        MOVE.W  #$1234,ea       ; 31FC 1234 1234
        MOVE.L  #$12345678,ea   ; 21FC 1234 5678 1234

        MOVEA   ea,A1           ; 3278 1234
        MOVEA   #$1234,A1       ; 327C 1234
        MOVEA.W #$1234,A1       ; 327C 1234
        MOVEA.L #$12345678,A1   ; 227C 1234 5678

        MOVEA   D2,A1           ; 3242
 if M68010
        MOVE    CCR,ea          ; 42F8 1234 (68010)
        MOVE.W  CCR,ea          ; 42F8 1234 (68010)
 endif
        MOVE    ea,CCR          ; 44F8 1234
        MOVE.W  ea,CCR          ; 44F8 1234
        MOVE    SR,ea           ; 40F8 1234 (priv on 68010+)
        MOVE.W  SR,ea           ; 40F8 1234 (priv on 68010+)
        MOVE    ea,SR           ; 46F8 1234 (priv)
        MOVE.W  ea,SR           ; 46F8 1234 (priv)
        MOVE    USP,A6          ; 4E6E
        MOVE    A6,USP          ; 4E66

	MOVEM.L	(A5),D0-D7/A0-A7  ; 4CD5 FFFF
	MOVEM.L	(A5),D5-D7/A0-A4  ; 4CD5 1FE0
	MOVEM.L	(A5)+,D5-D7/A0-A4 ; 4CDD 1FE0
	MOVEM.L	D0-D7/A0-A7,(A5)  ; 48D5 FFFF
	MOVEM.L	D5-D7/A0-A4,-(A5) ; 48E5 07F8

 if M68010
        MOVEC   SFC,D0          ; 4E7A 0000 (priv 68010+)
        MOVEC   SFC,A0          ; 4E7A 8000 (priv 68010+)
        MOVEC   D0,SFC          ; 4E7B 0000 (priv 68010+)
        MOVEC   A0,SFC          ; 4E7B 8000 (priv 68010+)
        MOVEC   A0,DFC          ; 4E7B 8001 (priv 68010+)
        MOVEC   A0,USP          ; 4E7B 8800 (priv 68010+)
        MOVEC   A0,VBR          ; 4E7B 8801 (priv 68010+)

        MOVES   ea,D0           ; 0E78 0000 1234 (priv 68010+)
        MOVES   ea,A0           ; 0E78 8000 1234 (priv 68010+)
        MOVES.B ea,A0           ; 0E38 8000 1234 (priv 68010+)
        MOVES.W ea,A0           ; 0E78 8000 1234 (priv 68010+)
        MOVES.L ea,A0           ; 0EB8 8000 1234 (priv 68010+)
        MOVES   D0,ea           ; 0E78 0800 1234 (priv 68010+)
        MOVES   A0,ea           ; 0E78 8800 1234 (priv 68010+)
        MOVES.B A0,ea           ; 0E38 8800 1234 (priv 68010+)
        MOVES.W A0,ea           ; 0E78 8800 1234 (priv 68010+)
        MOVES.L A0,ea           ; 0EB8 8800 1234 (priv 68010+)
 endif

        MOVEP   D2,($1234,A1)   ; 0589
        MOVEP.W D2,($1234,A1)   ; 0589
        MOVEP.L D2,($1234,A1)   ; 05C9
        MOVEP   ($1234,A1),D2   ; 0509
        MOVEP.W ($1234,A1),D2   ; 0509
        MOVEP.L ($1234,A1),D2   ; 0549
        MOVEP   D2,$1234(A1)    ; 0589
        MOVEP   $1234(A1),D2    ; 0509

        MOVEQ   #-$80,D1        ; 7280
        MOVEQ   #0,D1           ; 7200
        MOVEQ.L #0,D1           ; 7200
        MOVEQ   #$7F,D1         ; 727F

        MULS    ea,D1           ; C3F8 1234
        MULS.W  ea,D1           ; C3F8 1234

        MULU    ea,D1           ; C2F8 1234
        MULU.W  ea,D1           ; C2F8 1234

        NBCD    ea              ; 4838 1234
        NBCD.B  ea              ; 4838 1234

        NEG.B   ea              ; 4438 1234
        NEG     ea              ; 4478 1234
        NEG.W   ea              ; 4478 1234
        NEG.L   ea              ; 44B8 1234

        NEGX.B  ea              ; 4038 1234
        NEGX    ea              ; 4078 1234
        NEGX.W  ea              ; 4078 1234
        NEGX.L  ea              ; 40B8 1234

        NOP                     ; 4E71

        NOT.B   ea              ; 4638 1234
        NOT     ea              ; 4678 1234
        NOT.W   ea              ; 4678 1234
        NOT.L   ea              ; 46B8 1234

        OR      ea,D1           ; 8278 1234
        OR.B    #$12,D1         ; 0001 0012
        OR      #$1234,D1       ; 0041 1234
        OR.W    #$1234,D1       ; 0041 1234
        OR.L    #$12345678,D1   ; 0081 1234 5678

        ORI.B   #$12,ea         ; 0038 0012 1234
        ORI     #$1234,ea       ; 0078 1234 1234
        ORI.W   #$1234,ea       ; 0078 1234 1234
        ORI.L   #$12345678,ea   ; 00B8 1234 5678 1234

        ORI     #$12,CCR        ; 003C 0012
        ORI.B   #$12,CCR        ; 003C 0012

        ORI     #$1234,SR       ; 007C 1234 (priv)
        ORI.W   #$1234,SR       ; 007C 1234 (priv)

        PEA     ea              ; 4878 1234
        PEA     (A0)            ; 4850

        RESET                   ; 4E70 (priv)

        ROL.B   D2,D1           ; E539
        ROL     D2,D1           ; E579
        ROL.W   D2,D1           ; E579
        ROL.L   D2,D1           ; E5B9
        ROL.B   #1,D1           ; E319
        ROL     #1,D1           ; E359
        ROL.W   #1,D1           ; E359
        ROL.L   #1,D1           ; E399
        ROL     #8,D1           ; E159
        ROL     ea              ; E7F8 1234
        ROL.W   ea              ; E7F8 1234

        ROR.B   D2,D1           ; E439
        ROR     D2,D1           ; E479
        ROR.W   D2,D1           ; E479
        ROR.L   D2,D1           ; E4B9
        ROR.B   #1,D1           ; E219
        ROR     #1,D1           ; E259
        ROR.W   #1,D1           ; E259
        ROR.L   #1,D1           ; E299
        ROR     #8,D1           ; E059
        ROR     ea              ; E6F8 1234
        ROR.W   ea              ; E6F8 1234

        ROXL.B  D2,D1           ; E531
        ROXL    D2,D1           ; E571
        ROXL.W  D2,D1           ; E571
        ROXL.L  D2,D1           ; E5B1
        ROXL.B  #1,D1           ; E311
        ROXL    #1,D1           ; E351
        ROXL.W  #1,D1           ; E351
        ROXL.L  #1,D1           ; E391
        ROXL    #8,D1           ; E151
        ROXL    ea              ; E5F8 1234
        ROXL.W  ea              ; E5F8 1234

        ROXR.B  D2,D1           ; E431
        ROXR    D2,D1           ; E471
        ROXR.W  D2,D1           ; E471
        ROXR.L  D2,D1           ; E4B1
        ROXR.B  #1,D1           ; E211
        ROXR    #1,D1           ; E251
        ROXR.W  #1,D1           ; E251
        ROXR.L  #1,D1           ; E291
        ROXR    #8,D1           ; E051
        ROXR    ea              ; E4F8 1234
        ROXR.W  ea              ; E4F8 1234

 if M68010
        RTD     #$1234          ; 4E74 1234 (68010)
 endif

        RTE                     ; 4E73 (priv)

        RTR                     ; 4E77

        RTS                     ; 4E75

        SBCD    D2,D1           ; 8302
        SBCD.B  D2,D1           ; 8302
        SBCD    -(A2),-(A1)     ; 830A
        SBCD.B  -(A2),-(A1)     ; 830A

        ST      ea              ; 50F8 1234
        SF      ea              ; 51F8 1234
        SHI     ea              ; 52F8 1234
        SLS     ea              ; 53F8 1234
        SCC     ea              ; 54F8 1234
        SHS     ea              ; 54F8 1234
        SCS     ea              ; 55F8 1234
        SLO     ea              ; 55F8 1234
        SNE     ea              ; 56F8 1234
        SEQ     ea              ; 57F8 1234
        SVC     ea              ; 58F8 1234
        SVS     ea              ; 59F8 1234
        SPL     ea              ; 5AF8 1234
        SMI     ea              ; 5BF8 1234
        SGE     ea              ; 5CF8 1234
        SLT     ea              ; 5DF8 1234
        SGT     ea              ; 5EF8 1234
        SLE     ea              ; 5FF8 1234

        STOP    #$1234          ; 4E72 1234 (priv)

        SUB     ea,D1           ; 9278 1234
        SUB.B   #$12,D1         ; 0401 0012
        SUB     #$1234,D1       ; 0441 1234
        SUB.W   #$1234,D1       ; 0441 1234
        SUB.L   #$12345678,D1   ; 0481 1234 5678
        SUB     D2,D1           ; 9242

        SUBA    ea,A1           ; 92F8 1234
        SUBA    #$1234,A1       ; 92FC 1234
        SUBA.W  #$1234,A1       ; 92FC 1234
        SUBA.L  #$12345678,A1   ; 93FC 1234 5678
        SUBA    D2,A1           ; 92C2

        SUBI.B  #$12,D1         ; 0401 0012
        SUBI    #$1234,D1       ; 0441 1234
        SUBI.W  #$1234,D1       ; 0441 1234
        SUBI.L  #$12345678,D1   ; 0481 1234 5678

        SUBQ    #1,D1           ; 5341
        SUBQ    #8,D1           ; 5141

        SUBX.B  D2,D1           ; 9302
        SUBX    D2,D1           ; 9342
        SUBX.W  D2,D1           ; 9342
        SUBX.L  D2,D1           ; 9382
        SUBX.B  -(A2),-(A1)     ; 930A
        SUBX    -(A2),-(A1)     ; 934A
        SUBX.W  -(A2),-(A1)     ; 934A
        SUBX.L  -(A2),-(A1)     ; 938A

        SWAP    D1              ; 4841
        SWAP.W  D1              ; 4841

        TAS     ea              ; 4AF8 1234
        TAS.B   ea              ; 4AF8 1234

        TRAP    #10             ; 4EFA

        TRAPV                   ; 4E76

        TST.B   ea              ; 4A38 1234
        TST     ea              ; 4A78 1234
        TST.W   ea              ; 4A78 1234
        TST.L   ea              ; 4AB8 1234

        UNLK    A6              ; 4E5E

        END
