; 8048.ASM

        NOP             ; 00
        HALT            ; 01    HALT on Oki MSM80Cxx and Toshiba 8048
        OUTL    BUS,A   ; 02
        ADD     A,#-1   ; 03 FF
        JMP     $0000   ; 04 00
        EN      I       ; 05
        DB      06H     ; 06
        DEC     A       ; 07

        INS     A,BUS   ; 08
        IN      A,P1    ; 09
        IN      A,P2    ; 0A
        DB      0BH     ; 0B
        MOVD    A,P4    ; 0C
        MOVD    A,P5    ; 0D
        MOVD    A,P6    ; 0E
        MOVD    A,P7    ; 0F

        INC     @R0     ; 10
        INC     @R1     ; 11
        JB0     .+2     ; 12 xx
        ADDC    A,#-1   ; 13 FF
        CALL    $0000   ; 14 00
        DIS     I       ; 15
        JTF     .+2     ; 16 xx
        INC     A       ; 17

        INC     R0      ; 18
        INC     R1      ; 19
        INC     R2      ; 1A
        INC     R3      ; 1B
        INC     R4      ; 1C
        INC     R5      ; 1D
        INC     R6      ; 1E
        INC     R7      ; 1F

        XCH     A,@R0   ; 20
        XCH     A,@R1   ; 21
        DB      22H     ; 22
        MOV     A,#-1   ; 23 FF
        JMP     $0100   ; 24 00
        EN      TCNTI   ; 25
        JNT0    .+2     ; 26 xx
        CLR     A       ; 27

        XCH     A,R0    ; 28
        XCH     A,R1    ; 29
        XCH     A,R2    ; 2A
        XCH     A,R3    ; 2B
        XCH     A,R4    ; 2C
        XCH     A,R5    ; 2D
        XCH     A,R6    ; 2E
        XCH     A,R7    ; 2F

        XCHD    A,@R0   ; 30
        XCHD    A,@R1   ; 31
        JB1     .+2     ; 32 xx
        DB      33H     ; 33
        CALL    $0100   ; 34 00
        DIS     TCNTI   ; 35
        JT0     .+2     ; 36 xx
        CPL     A       ; 37

        DB      38H     ; 38
        OUTL    P1,A    ; 39
        OUTL    P2,A    ; 3A
        DB      3BH     ; 3B
        MOVD    P4,A    ; 3C
        MOVD    P5,A    ; 3D
        MOVD    P6,A    ; 3E
        MOVD    P7,A    ; 3F

        ORL     A,@R0   ; 40
        ORL     A,@R1   ; 41
        MOV     A,T     ; 42
        ORL     A,#-1   ; 43 FF
        JMP     $0200   ; 44 00
        STRT    CNT     ; 45
        JNT1    .+2     ; 46 xx
        SWAP    A       ; 47

        ORL     A,R0    ; 48
        ORL     A,R1    ; 49
        ORL     A,R2    ; 4A
        ORL     A,R3    ; 4B
        ORL     A,R4    ; 4C
        ORL     A,R5    ; 4D
        ORL     A,R6    ; 4E
        ORL     A,R7    ; 4F

        ANL     A,@R0   ; 50
        ANL     A,@R1   ; 51
        JB2     .+2     ; 52 xx
        ANL     A,#-1   ; 53 FF
        CALL    $0200   ; 54 00
        STRT    T       ; 55
        JT1     .+2     ; 56 xx
        DA      A       ; 57

        ANL     A,R0    ; 58
        ANL     A,R1    ; 59
        ANL     A,R2    ; 5A
        ANL     A,R3    ; 5B
        ANL     A,R4    ; 5C
        ANL     A,R5    ; 5D
        ANL     A,R6    ; 5E
        ANL     A,R7    ; 5F

        ADD     A,@R0   ; 60
        ADD     A,@R1   ; 61
        MOV     T,A     ; 62
        DB      63H     ; 63
        JMP     $0300   ; 64 00
        STOP    TCNT    ; 65
        DB      66H     ; 66
        RRC     A       ; 67

        ADD     A,R0    ; 68
        ADD     A,R1    ; 69
        ADD     A,R2    ; 6A
        ADD     A,R3    ; 6B
        ADD     A,R4    ; 6C
        ADD     A,R5    ; 6D
        ADD     A,R6    ; 6E
        ADD     A,R7    ; 6F

        ADDC    A,@R0   ; 70
        ADDC    A,@R1   ; 71
        JB3     .+2     ; 72 xx
        DB      73H     ; 73
        CALL    $0300   ; 74 00
        ENT0    CLK     ; 75
        JF1     .+2     ; 76 xx
        RR      A       ; 77

        ADDC    A,R0    ; 78
        ADDC    A,R1    ; 79
        ADDC    A,R2    ; 7A
        ADDC    A,R3    ; 7B
        ADDC    A,R4    ; 7C
        ADDC    A,R5    ; 7D
        ADDC    A,R6    ; 7E
        ADDC    A,R7    ; 7F

        MOVX    A,@R0   ; 80
        MOVX    A,@R1   ; 81
        HLTS            ; 82     HLTS on Oki MSM80Cxx
        RET             ; 83
        JMP     $0400   ; 84 00
        CLR     F0      ; 85
        JNI     .+2     ; 86 xx
        DB      87H     ; 87

        ORL     BUS,#-1 ; 88 FF
        ORL     P1,#-1  ; 89 FF
        ORL     P2,#-1  ; 8A FF
        DB      8BH     ; 8B
        ORLD    P4,A    ; 8C
        ORLD    P5,A    ; 8D
        ORLD    P6,A    ; 8E
        ORLD    P7,A    ; 8F

        MOVX    @R0,A   ; 90
        MOVX    @R1,A   ; 91
        JB4     .+2     ; 92 xx
        RETR            ; 93
        CALL    $0400   ; 94 00
        CPL     F0      ; 95
        JNZ     .+2     ; 96 xx
        CLR     C       ; 97

        ANL     BUS,#-1 ; 98 FF
        ANL     P1,#-1  ; 99 FF
        ANL     P2,#-1  ; 9A FF
        DB      9BH     ; 9B
        ANLD    P4,A    ; 9C
        ANLD    P5,A    ; 9D
        ANLD    P6,A    ; 9E
        ANLD    P7,A    ; 9F

        MOV     @R0,A   ; A0
        MOV     @R1,A   ; A1
        FLT             ; A2     FLT on Oki MSM80Cxx
        MOVP    A,@A    ; A3
        JMP     $0500   ; A4 00
        CLR     F1      ; A5
        DB      A6H     ; A6
        CPL     C       ; A7

        MOV     R0,A    ; A8
        MOV     R1,A    ; A9
        MOV     R2,A    ; AA
        MOV     R3,A    ; AB
        MOV     R4,A    ; AC
        MOV     R5,A    ; AD
        MOV     R6,A    ; AE
        MOV     R7,A    ; AF

        MOV     @R0,#-1 ; B0 FF
        MOV     @R1,#-1 ; B1 FF
        JB5     .+2     ; B2 xx
        JMPP    @A      ; B3
        CALL    $0500   ; B4 00
        CPL     F1      ; B5
        JF0     .+2     ; B6 xx
        DB      B7H     ; B7

        MOV     R0,#-1  ; B8 FF
        MOV     R1,#-1  ; B9 FF
        MOV     R2,#-1  ; BA FF
        MOV     R3,#-1  ; BB FF
        MOV     R4,#-1  ; BC FF
        MOV     R5,#-1  ; BD FF
        MOV     R6,#-1  ; BE FF
        MOV     R7,#-1  ; BF FF

        DB      C0H     ; C0
        DB      C1H     ; C1
        FLTT            ; C2     FLTT on Oki MSM80Cxx
        DB      C3H     ; C3
        JMP     $0600   ; C4 00
        SEL     RB0     ; C5
        JZ      .+2     ; C6 xx
        MOV     A,PSW   ; C7

        DEC     R0      ; C8
        DEC     R1      ; C9
        DEC     R2      ; CA
        DEC     R3      ; CB
        DEC     R4      ; CC
        DEC     R5      ; CD
        DEC     R6      ; CE
        DEC     R7      ; CF

        XRL     A,@R0   ; D0
        XRL     A,@R1   ; D1
        JB6     .+2     ; D2 xx
        XRL     A,#-1   ; D3 FF
        CALL    $0600   ; D4 00
        SEL     RB1     ; D5
        DB      D6H     ; D6
        MOV     PSW,A   ; D7

        XRL     A,R0    ; D8
        XRL     A,R1    ; D9
        XRL     A,R2    ; DA
        XRL     A,R3    ; DB
        XRL     A,R4    ; DC
        XRL     A,R5    ; DD
        XRL     A,R6    ; DE
        XRL     A,R7    ; DF

        DB      E0H     ; E0
        DB      E1H     ; E1
        DB      E2H     ; E2
        MOVP3   A,@A    ; E3
        JMP     $0700   ; E4 00
        SEL     MB0     ; E5
        JNC     .+2     ; E6 xx
        RL      A       ; E7

        DJNZ    R0,.+2  ; E8 xx
        DJNZ    R1,.+2  ; E9 xx
        DJNZ    R2,.+2  ; EA xx
        DJNZ    R3,.+2  ; EB xx
        DJNZ    R4,.+2  ; EC xx
        DJNZ    R5,.+2  ; ED xx
        DJNZ    R6,.+2  ; EE xx
        DJNZ    R7,.+2  ; EF xx

        MOV     A,@R0   ; F0
        MOV     A,@R1   ; F1
        JB7     .+2     ; F2 xx
        DB      F3H     ; F3
        CALL    $0700   ; F4 00
        SEL     MB1     ; F5
        JC      .+2     ; F6 xx
        RLC     A       ; F7

        MOV     A,R0    ; F8
        MOV     A,R1    ; F9
        MOV     A,R2    ; FA
        MOV     A,R3    ; FB
        MOV     A,R4    ; FC
        MOV     A,R5    ; FD
        MOV     A,R6    ; FE
        MOV     A,R7    ; FF
