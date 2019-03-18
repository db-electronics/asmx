        PROCESSOR 65C816

abs     EQU     'AB'
absl    EQU     'ABL'
dir     EQU     'D'     ; zero/direct page
imm     EQU     'I'
idx     EQU     'X'

        BRK                     ; 00
        ORA     (idx,X)         ; 01 58
        COP     $FF             ; 02 FF
        ORA     idx,S           ; 03 58
        TSB     dir             ; 04 44
        ORA     dir             ; 05 44
        ASL     dir             ; 06 44
        ORA     [dir]           ; 07 44

        PHP                     ; 08
        ORA     #imm            ; 09 49
        ASL     A               ; 0A
        PHD                     ; 0B
        TSB     abs             ; 0C 4241
        ORA     abs             ; 0D 4241
        ASL     abs             ; 0E 4241
        ORA     absl            ; 0F 4C4241

        BPL     *               ; 10 FE
        ORA     (idx),Y         ; 11 58
        ORA     (idx)           ; 12 58
        ORA     (idx,S),Y       ; 13 58
        TRB     dir             ; 14 44
        ORA     dir,X           ; 15 44
        ASL     dir,X           ; 16 44
        ORA     [dir],Y         ; 17 44

        CLC                     ; 18
        ORA     abs,Y           ; 19 4241
        INA                     ; 1A
        TCS                     ; 1B
        TRB     abs             ; 1C 4241
        ORA     abs,X           ; 1D 4241
        ASL     abs,X           ; 1E 4241
        ORA     absl,X          ; 1F 4C4241

        JSR     abs             ; 20 4241
        AND     (idx,X)         ; 21 58
        JSL     absl            ; 22 4C4241
        AND     idx,S           ; 23 58
        BIT     dir             ; 24 44
        AND     dir             ; 25 44
        ROL     dir             ; 26 44
        AND     [dir]           ; 27 44

        PLP                     ; 28
        AND     #imm            ; 29 49
        ROL     A               ; 2A
        PLD                     ; 2B
        BIT     abs             ; 2C 4241
        AND     abs             ; 2D 4241
        ROL     abs             ; 2E 4241
        AND     absl            ; 2F 4C4241

        BMI     *               ; 30 FE
        AND     (idx),Y         ; 31 58
        AND     (idx)           ; 32 58
        AND     (idx,S),Y       ; 33 58
        BIT     dir,X           ; 34 44
        AND     dir,X           ; 35 44
        ROL     dir,X           ; 36 44
        AND     [dir],Y         ; 37 44

        SEC                     ; 38
        AND     abs,Y           ; 39 4241
        DEA                     ; 3A
        TSC                     ; 3B
        BIT     abs,X           ; 3C 4241
        AND     abs,X           ; 3D 4241
        ROL     abs,X           ; 3E 4241
        AND     absl,X          ; 3F 4C4241

        RTI                     ; 40
        EOR     (idx,X)         ; 41 58
        WDM                     ; 42
        EOR     idx,S           ; 43 58
        MVP     'S','D'         ; 44 44 53
        EOR     dir             ; 45 44
        LSR     dir             ; 46 44
        EOR     [dir]           ; 47 44

        PHA                     ; 48
        EOR     #imm            ; 49 49
        LSR     A               ; 4A
        PHK                     ; 4B
        JMP     abs             ; 4C 4241
        EOR     abs             ; 4D 4241
        LSR     abs             ; 4E 4241
        EOR     absl            ; 4F 4C4241

        BVC     *               ; 50 FE
        EOR     (idx),Y         ; 51 58
        EOR     (idx)           ; 52 58
        EOR     (idx,S),Y       ; 43 58
        MVN     'S','D'         ; 54 44 53
        EOR     dir,X           ; 55 44
        LSR     dir,X           ; 56 44
        EOR     [dir],Y         ; 57 44

        CLI                     ; 58
        EOR     abs,Y           ; 59 4241
        PHY                     ; 5A
        TCD                     ; 5B
        JMP     absl            ; 5C 4C4241
        EOR     abs,X           ; 5D 4241
        LSR     abs,X           ; 5E 4241
        EOR     absl,X          ; 5F 4C4241

        RTS                     ; 60
        ADC     (idx,X)         ; 61 58
        PER     *               ; 62 FDFF
        ADC     idx,S           ; 63 58
        STZ     dir             ; 64 44
        ADC     dir             ; 65 44
        ROR     dir             ; 66 44
        ADC     [dir]           ; 67 44

        PLA                     ; 68
        ADC     #imm            ; 69 49
        ROR     A               ; 6A
        RTL                     ; 6B
        JMP     (abs)           ; 6C
        ADC     abs             ; 6D 4241
        ROR     abs             ; 6E 4241
        ADC     absl            ; 6F 4C4241

        BVS     *               ; 70 FE
        ADC     (idx),Y         ; 71 58
        ADC     (idx)           ; 72 58
        ADC     (idx,S),Y       ; 73 58
        STZ     dir,X           ; 74 44
        ADC     dir,X           ; 75 44
        ROR     dir,X           ; 76 44
        ADC     [dir],Y         ; 77 44

        SEI                     ; 78
        ADC     abs,Y           ; 79 4241
        PLY                     ; 7A
        TDC                     ; 7B
        JMP     (abs,X)         ; 7C 4241
        ADC     abs,X           ; 7D 4241
        ROR     abs,X           ; 7E 4241
        ADC     absl,X          ; 7F 4C4241

        BRA     *               ; 80 FE
        STA     (idx,X)         ; 81 58
        BRL     *               ; 82 FDFF
        STA     idx,S           ; 83 58
        STY     dir             ; 84 44
        STA     dir             ; 85 44
        STX     dir             ; 86 44
        STA     [dir]           ; 87 44

        DEY                     ; 88
        BIT     #imm            ; 89 49
        TXA                     ; 8A
        PHB                     ; 8B
        STY     abs             ; 8C 4241
        STA     abs             ; 8D 4241
        STX     abs             ; 8E 4241
        STA     absl            ; 8F 4C4241

        BCC     *               ; 90 FE
        STA     (idx),Y         ; 91 58
        STA     (idx)           ; 92 58
        STA     (idx,S),Y       ; 93 58
        STY     dir,X           ; 94 44
        STA     dir,X           ; 95 44
        STX     dir,Y           ; 96 44
        STA     [dir],Y         ; 97 44

        TYA                     ; 98
        STA     abs,Y           ; 99 4241
        TXS                     ; 9A
        TXY                     ; 9B
        STZ     abs             ; 9C 4241
        STA     abs,X           ; 9D 4241
        STZ     abs,X           ; 9E 4241
        STA     absl,X          ; 9F 4C4241

        LDY     #imm            ; A0 49
        LDA     (idx,X)         ; A1 58
        LDX     #imm            ; A2 49
        LDA     idx,S           ; A3 58
        LDY     dir             ; A4 44
        LDA     dir             ; A5 44
        LDX     dir             ; A6 44
        LDA     [dir]           ; A7 44

        TAY                     ; A8
        LDA     #imm            ; A9 49
        TAX                     ; AA
        PLB                     ; AB
        LDY     abs             ; AC 4241
        LDA     abs             ; AD 4241
        LDX     abs             ; AE 4241
        LDA     absl            ; AF 4C4241

        BCS     *               ; B0 FE
        LDA     (idx),Y         ; B1 58
        LDA     (idx)           ; B2 58
        LDA     (idx,S),Y       ; A3 58
        LDY     dir,X           ; B4 44
        LDA     dir,X           ; B5 44
        LDX     dir,Y           ; B6 44
        LDA     [dir],Y         ; B7 44

        CLV                     ; B8
        LDA     abs,Y           ; B9 4241
        TSX                     ; BA
        TYX                     ; BB
        LDY     abs,X           ; BC 4241
        LDA     abs,X           ; BD 4241
        LDX     abs,Y           ; BE 4241
        LDA     absl,X          ; BF 4C4241

        CPY     #imm            ; C0 49
        CMP     (idx,X)         ; C1 58
        REP     #imm            ; C2 49
        CMP     idx,S           ; C3 58
        CPY     dir             ; C4 44
        CMP     dir             ; C5 44
        DEC     dir             ; C6 44
        CMP     [dir]           ; C7 44

        INY                     ; C8
        CMP     #imm            ; C9 49
        DEX                     ; CA
        WAI                     ; CB
        CPY     abs             ; CC 4241
        CMP     abs             ; CD 4241
        DEC     abs             ; CE 4241
        CMP     absl            ; CF 4C4241

        BNE     *               ; D0 FE
        CMP     (idx),Y         ; D1 58
        CMP     (idx)           ; D2 58
        CMP     (idx,S),Y       ; C3 58
        PEI     dir             ; D4 44 - might be "PEI [dir]"
        CMP     dir,X           ; D5 44
        DEC     dir,X           ; D6 44
        CMP     [dir],Y         ; D7 44

        CLD                     ; D8
        CMP     abs,Y           ; D9 4241
        PHX                     ; DA
        STP                     ; DB
        JML     (abs)           ; DC 4241
        CMP     abs,X           ; DD 4241
        DEC     abs,X           ; DE 4241
        CMP     absl,X          ; DF 4C4241

        CPX     #imm            ; E0 49
        SBC     (idx,X)         ; E1 58
        SEP     #imm            ; E2 49
        SBC     idx,S           ; E3 58
        CPX     dir             ; E4 44
        SBC     dir             ; E5 44
        INC     dir             ; E6 44
        SBC     [dir]           ; E7 44

        INX                     ; E8
        SBC     #imm            ; E9 49
        NOP                     ; EA
        XBA                     ; EB
        CPX     abs             ; EC 4241
        SBC     abs             ; ED 4241
        INC     abs             ; EE 4241
        SBC     absl            ; EF 4C4241

        BEQ     *               ; F0 FE
        SBC     (idx),Y         ; F1 58
        SBC     (idx)           ; F2 58
        SBC     (idx,S),Y       ; E3 58
        PEA     abs             ; F4 4241
        SBC     dir,X           ; F5 44
        INC     dir,X           ; F6 44
        SBC     [dir],Y         ; F7 44

        SED                     ; F8
        SBC     abs,Y           ; F9 4241
        PLX                     ; FA
        XCE                     ; FB
        JSR     (abs,X)         ; FC 4241
        SBC     abs,X           ; FD 4241
        INC     abs,X           ; FE 4241
        SBC     absl,X          ; FF 4C4241

        END
