; 8051.ASM

dir     equ     'D'
imm     equ     'I'
bit     equ     0x28
b       equ     0x02
ad16    equ     $1234

        NOP             ; 00
        AJMP    $0001   ; 01 xx
        LJMP    ad16    ; 02 xxxx
        RR      A       ; 03
        INC     A       ; 04
        INC     dir     ; 05 dir
        INC     @R0     ; 06
        INC     @R1     ; 07
        INC     R0      ; 08
        INC     R1      ; 09
        INC     R2      ; 0A
        INC     R3      ; 0B
        INC     R4      ; 0C
        INC     R5      ; 0D
        INC     R6      ; 0E
        INC     R7      ; 0F

        JBC     bit.b,. ; 10 bit rel
        ACALL   $0011   ; 11 xx
        LCALL   ad16    ; 12 xxxx
        RRC     A       ; 13
        DEC     A       ; 14
        DEC     dir     ; 15 dir
        DEC     @R0     ; 16
        DEC     @R1     ; 17
        DEC     R0      ; 18
        DEC     R1      ; 19
        DEC     R2      ; 1A
        DEC     R3      ; 1B
        DEC     R4      ; 1C
        DEC     R5      ; 1D
        DEC     R6      ; 1E
        DEC     R7      ; 1F

        JB      bit.b,. ; 20 bit rel
        AJMP    $0121   ; 21 xx
        RET             ; 22
        RL      A       ; 23
        ADD     A,#imm  ; 24 imm
        ADD     A,dir   ; 25 dir
        ADD     A,@R0   ; 26
        ADD     A,@R1   ; 27
        ADD     A,R0    ; 28
        ADD     A,R1    ; 29
        ADD     A,R2    ; 2A
        ADD     A,R3    ; 2B
        ADD     A,R4    ; 2C
        ADD     A,R5    ; 2D
        ADD     A,R6    ; 2E
        ADD     A,R7    ; 2F

        JNB     bit.b,. ; 30 bit rel
        ACALL   $0131   ; 31 xx
        RETI            ; 32
        RLC     A       ; 33
        ADDC    A,#imm  ; 34 imm
        ADDC    A,dir   ; 35 dir
        ADDC    A,@R0   ; 36
        ADDC    A,@R1   ; 37
        ADDC    A,R0    ; 38
        ADDC    A,R1    ; 39
        ADDC    A,R2    ; 3A
        ADDC    A,R3    ; 3B
        ADDC    A,R4    ; 3C
        ADDC    A,R5    ; 3D
        ADDC    A,R6    ; 3E
        ADDC    A,R7    ; 3F

        JC      .       ; 40 rel
        AJMP    $0241   ; 41 xx
        ORL     dir,A   ; 42 dir
        ORL     dir,#imm; 43 dir imm
        ORL     A,#imm  ; 44 imm
        ORL     A,dir   ; 45 dir
        ORL     A,@R0   ; 46
        ORL     A,@R1   ; 47
        ORL     A,R0    ; 48
        ORL     A,R1    ; 49
        ORL     A,R2    ; 4A
        ORL     A,R3    ; 4B
        ORL     A,R4    ; 4C
        ORL     A,R5    ; 4D
        ORL     A,R6    ; 4E
        ORL     A,R7    ; 4F

        JNC     .       ; 50 rel
        ACALL   $0251   ; 51 xx
        ANL     dir,A   ; 52 dir
        ANL     dir,#imm; 53 dir imm
        ANL     A,#imm  ; 54 imm
        ANL     A,dir   ; 55 dir
        ANL     A,@R0   ; 56
        ANL     A,@R1   ; 57
        ANL     A,R0    ; 58
        ANL     A,R1    ; 59
        ANL     A,R2    ; 5A
        ANL     A,R3    ; 5B
        ANL     A,R4    ; 5C
        ANL     A,R5    ; 5D
        ANL     A,R6    ; 5E
        ANL     A,R7    ; 5F

        JZ      .       ; 60 rel
        AJMP    $0361   ; 61 xx
        XRL     dir,A   ; 62 dir
        XRL     dir,#imm; 63 dir imm
        XRL     A,#imm  ; 64 imm
        XRL     A,dir   ; 65 dir
        XRL     A,@R0   ; 66
        XRL     A,@R1   ; 67
        XRL     A,R0    ; 68
        XRL     A,R1    ; 69
        XRL     A,R2    ; 6A
        XRL     A,R3    ; 6B
        XRL     A,R4    ; 6C
        XRL     A,R5    ; 6D
        XRL     A,R6    ; 6E
        XRL     A,R7    ; 6F

        JNZ     .       ; 70 rel
        ACALL   $0371   ; 71 xx
        ORL     C,bit.b ; 72 bit
        JMP     @A+DPTR ; 73
        MOV     A,#imm  ; 74 imm
        MOV     dir,#imm; 75 dir imm
        MOV     @R0,#imm; 76 imm
        MOV     @R1,#imm; 77 imm
        MOV     R0,#imm ; 78 imm
        MOV     R1,#imm ; 79 imm
        MOV     R2,#imm ; 7A imm
        MOV     R3,#imm ; 7B imm
        MOV     R4,#imm ; 7C imm
        MOV     R5,#imm ; 7D imm
        MOV     R6,#imm ; 7E imm
        MOV     R7,#imm ; 7F imm

        SJMP    .       ; 80 rel
        AJMP    $0481   ; 81 xx
        ANL     C,bit.b ; 82 bit
        MOVC    A,@A+PC ; 83
        DIV     AB      ; 84
        MOV     dir,dir+1 ; 85 src dst
        MOV     dir,@R0 ; 86 dir
        MOV     dir,@R1 ; 87 dir
        MOV     dir,R0  ; 88 dir
        MOV     dir,R1  ; 89 dir
        MOV     dir,R2  ; 8A dir
        MOV     dir,R3  ; 8B dir
        MOV     dir,R4  ; 8C dir
        MOV     dir,R5  ; 8D dir
        MOV     dir,R6  ; 8E dir
        MOV     dir,R7  ; 8F dir

        MOV     DPTR,#ad16 ; 90 xxxx
        ACALL   $0491   ; 91 xx
        MOV     bit.b,C ; 92 bit
        MOVC    A,@A+DPTR ; 93
        SUBB    A,#imm  ; 94 imm
        SUBB    A,dir   ; 95 dir
        SUBB    A,@R0   ; 96
        SUBB    A,@R1   ; 97
        SUBB    A,R0    ; 98
        SUBB    A,R1    ; 99
        SUBB    A,R2    ; 9A
        SUBB    A,R3    ; 9B
        SUBB    A,R4    ; 9C
        SUBB    A,R5    ; 9D
        SUBB    A,R6    ; 9E
        SUBB    A,R7    ; 9F

        ORL     C,/bit.b ; A0 bit
        AJMP    $05A1   ; A1 xx
        MOV     C,bit.b ; A2 bit
        INC     DPTR    ; A3
        MUL     AB      ; A4
        DB      A5H
        MOV     @R0,dir ; A6 dir
        MOV     @R1,dir ; A7 dir
        MOV     R0,dir  ; A8 dir
        MOV     R1,dir  ; A9 dir
        MOV     R2,dir  ; AA dir
        MOV     R3,dir  ; AB dir
        MOV     R4,dir  ; AC dir
        MOV     R5,dir  ; AD dir
        MOV     R6,dir  ; AE dir
        MOV     R7,dir  ; AF dir

        ANL     C,/bit.b ; B0 bit
        ACALL   $05B1   ; B1 xx
        CPL     bit.b   ; B2 bit
        CPL     C       ; B3
        CJNE    A,#imm,.; B4 imm rel
        CJNE    dir,.   ; B5 dir rel
        CJNE    @R0,#imm,.; B6 imm rel
        CJNE    @R1,#imm,.; B7 imm rel
        CJNE    R0,#imm,.; B8 imm rel
        CJNE    R1,#imm,.; B9 imm rel
        CJNE    R2,#imm,.; BA imm rel
        CJNE    R3,#imm,.; BB imm rel
        CJNE    R4,#imm,.; BC imm rel
        CJNE    R5,#imm,.; BD imm rel
        CJNE    R6,#imm,.; BE imm rel
        CJNE    R7,#imm,.; BF imm rel

        PUSH    dir     ; C0 dir
        AJMP    $06C1   ; C1 xx
        CLR     bit.b   ; C2 bit
        CLR     C       ; C3
        SWAP    A       ; C4
        XCH     A,dir   ; C5 dir
        XCH     A,@R0   ; C6
        XCH     A,@R1   ; C7
        XCH     A,R0    ; C8
        XCH     A,R1    ; C9
        XCH     A,R2    ; CA
        XCH     A,R3    ; CB
        XCH     A,R4    ; CC
        XCH     A,R5    ; CD
        XCH     A,R6    ; CE
        XCH     A,R7    ; CF

        POP     dir     ; D0 dir
        ACALL   $06D1   ; D1 xx
        SETB    bit.b   ; D2 bit
        SETB    C       ; D3
        DA      A       ; D4
        DJNZ    dir,.   ; D5 dir rel
        XCHD    A,@R0   ; D6
        XCHD    A,@R1   ; D7
        DJNZ    R0,.    ; D8 rel
        DJNZ    R1,.    ; D9 rel
        DJNZ    R2,.    ; DA rel
        DJNZ    R3,.    ; DB rel
        DJNZ    R4,.    ; DC rel
        DJNZ    R5,.    ; DD rel
        DJNZ    R6,.    ; DE rel
        DJNZ    R7,.    ; DF rel

        MOVX    A,@DPTR ; E0
        AJMP    $07E1   ; E1 xx
        MOVX    A,@R0   ; E2
        MOVX    A,@R1   ; E3
        CLR     A       ; E4
        MOV     A,dir   ; E5 dir
        MOV     A,@R0   ; E6
        MOV     A,@R1   ; E7
        MOV     A,R0    ; E8
        MOV     A,R1    ; E9
        MOV     A,R2    ; EA
        MOV     A,R3    ; EB
        MOV     A,R4    ; EC
        MOV     A,R5    ; ED
        MOV     A,R6    ; EE
        MOV     A,R7    ; EF

        MOVX    @DPTR,A ; F0
        ACALL   $07F1   ; F1 xx
        MOVX    @R0,A   ; F2
        MOVX    @R1,A   ; F3
        CPL     A       ; F4
        MOV     dir,A   ; F5 dir
        MOV     @R0,A   ; F6
        MOV     @R1,A   ; F7
        MOV     R0,A    ; F8
        MOV     R1,A    ; F9
        MOV     R2,A    ; FA
        MOV     R3,A    ; FB
        MOV     R4,A    ; FC
        MOV     R5,A    ; FD
        MOV     R6,A    ; FE
        MOV     R7,A    ; FF
