        PROCESSOR 65C02

abs     EQU     'AB'
dir     EQU     'D'     ; zero/direct page
imm     EQU     'I'
idx     EQU     'X'

        BRK                     ; 00
        ORA     (idx,X)         ; 01 58
        DB      $02             ; 02
        DB      $03             ; 03
        TSB     dir             ; 04 48
        ORA     dir             ; 05 48
        ASL     dir             ; 06 48
        RMB0    dir             ; 07 48

        PHP                     ; 08
        ORA     #imm            ; 09 49
        ASL     A               ; 0A
        DB      $0B             ; 0B
        TSB     abs             ; 0C 4241
        ORA     abs             ; 0D 4241
        ASL     abs             ; 0E 4241
        BBR0    dir,*           ; 0F 48 FD

        BPL     *               ; 10 FE
        ORA     (idx),Y         ; 11 58
        ORA     (idx)           ; 12 58
        DB      $13             ; 13
        TRB     dir             ; 14 48
        ORA     dir,X           ; 15 48
        ASL     dir,X           ; 16 48
        RMB1    dir             ; 17 48

        CLC                     ; 18
        ORA     abs,Y           ; 19 4241
        INA                     ; 1A
        DB      $1B             ; 1B
        TRB     abs             ; 1C 4241
        ORA     abs,X           ; 1D 4241
        ASL     abs,X           ; 1E 4241
        BBR1    dir,*           ; 1F 48 FD

        JSR     abs             ; 20 4241
        AND     (idx,X)         ; 21 58
        DB      $22             ; 22
        DB      $23             ; 23
        BIT     dir             ; 24 48
        AND     dir             ; 25 48
        ROL     dir             ; 26 48
        RMB2    dir             ; 27 48

        PLP                     ; 28
        AND     #imm            ; 29 49
        ROL     A               ; 2A
        DB      $2B             ; 2B
        BIT     abs             ; 2C 4241
        AND     abs             ; 2D 4241
        ROL     abs             ; 2E 4241
        BBR2    dir,*           ; 2F 48 FD

        BMI     *               ; 30 FE
        AND     (idx),Y         ; 31 58
        AND     (idx)           ; 32 58
        DB      $33             ; 33
        BIT     dir,X           ; 34 48
        AND     dir,X           ; 35 48
        ROL     dir,X           ; 36 48
        RMB3    dir             ; 37 48

        SEC                     ; 38
        AND     abs,Y           ; 39 4241
        DEA                     ; 3A
        DB      $3B             ; 3B
        BIT     abs,X           ; 3C 4241
        AND     abs,X           ; 3D 4241
        ROL     abs,X           ; 3E 4241
        BBR3    dir,*           ; 3F 48 FD

        RTI                     ; 40
        EOR     (idx,X)         ; 41 58
        DB      $42             ; 42
        DB      $43             ; 43
        DB      $44             ; 44
        EOR     dir             ; 45 48
        LSR     dir             ; 46 48
        RMB4    dir             ; 47 48

        PHA                     ; 48
        EOR     #imm            ; 49 49
        LSR     A               ; 4A
        DB      $4B             ; 4B
        JMP     abs             ; 4C 4241
        EOR     abs             ; 4D 4241
        LSR     abs             ; 4E 4241
        BBR4    dir,*           ; 4F 48 FD

        BVC     *               ; 50 FE
        EOR     (idx),Y         ; 51 58
        EOR     (idx)           ; 52 58
        DB      $53             ; 53
        DB      $54             ; 54
        EOR     dir,X           ; 55 48
        LSR     dir,X           ; 56 48
        RMB5    dir             ; 57 48

        CLI                     ; 58
        EOR     abs,Y           ; 59 4241
        PHY                     ; 5A
        DB      $5B             ; 5B
        DB      $5C             ; 5C
        EOR     abs,X           ; 5D 4241
        LSR     abs,X           ; 5E 4241
        BBR5    dir,*           ; 5F 48 FD

        RTS                     ; 60
        ADC     (idx,X)         ; 61 58
        DB      $62             ; 62
        DB      $63             ; 63
        STZ     dir             ; 64 48
        ADC     dir             ; 65 48
        ROR     dir             ; 66 48
        RMB6    dir             ; 67 48

        PLA                     ; 68
        ADC     #imm            ; 69 49
        ROR     A               ; 6A
        DB      $6B             ; 6B
        JMP     (abs)           ; 6C
        ADC     abs             ; 6D 4241
        ROR     abs             ; 6E 4241
        BBR6    dir,*           ; 6F 48 FD

        BVS     *               ; 70 FE
        ADC     (idx),Y         ; 71 58
        ADC     (idx)           ; 72 58
        DB      $73             ; 73
        STZ     dir,X           ; 74 48
        ADC     dir,X           ; 75 48
        ROR     dir,X           ; 76 48
        RMB7    dir             ; 77 48

        SEI                     ; 78
        ADC     abs,Y           ; 79 4241
        PLY                     ; 7A
        DB      $7B             ; 7B
        JMP     (abs,X)         ; 7C 4241
        ADC     abs,X           ; 7D 4241
        ROR     abs,X           ; 7E 4241
        BBR7    dir,*           ; 7F 48 FD

        BRA     *               ; 80 FE
        STA     (idx,X)         ; 81 58
        DB      $82             ; 82
        DB      $83             ; 83
        STY     dir             ; 84 48
        STA     dir             ; 85 48
        STX     dir             ; 86 48
        SMB0    dir             ; 87 48

        DEY                     ; 88
        BIT     #imm            ; 89 49
        TXA                     ; 8A
        DB      $8B             ; 8B
        STY     abs             ; 8C 4241
        STA     abs             ; 8D 4241
        STX     abs             ; 8E 4241
        BBS0    dir,*           ; 8F 48 FD

        BCC     *               ; 90 FE
        STA     (idx),Y         ; 91 58
        STA     (idx)           ; 92 58
        DB      $93             ; 93
        STY     dir,X           ; 94 48
        STA     dir,X           ; 95 48
        STX     dir,Y           ; 96 48
        SMB1    dir             ; 97 48

        TYA                     ; 98
        STA     abs,Y           ; 99 4241
        TXS                     ; 9A
        DB      $9B             ; 9B
        STZ     abs             ; 9C 4241
        STA     abs,X           ; 9D 4241
        STZ     abs,X           ; 9E 4241
        BBS1    dir,*           ; 9F 48 FD

        LDY     #imm            ; A0 49
        LDA     (idx,X)         ; A1 58
        LDX     #imm            ; A2 49
        DB      $A3             ; A3
        LDY     dir             ; A4 48
        LDA     dir             ; A5 48
        LDX     dir             ; A6 48
        SMB2    dir             ; A7 48

        TAY                     ; A8
        LDA     #imm            ; A9 49
        TAX                     ; AA
        DB      $AB             ; AB
        LDY     abs             ; AC 4241
        LDA     abs             ; AD 4241
        LDX     abs             ; AE 4241
        BBS2    dir,*           ; AF 48 FD

        BCS     *               ; B0 FE
        LDA     (idx),Y         ; B1 58
        LDA     (idx)           ; B2 58
        DB      $B3             ; B3
        LDY     dir,X           ; B4 48
        LDA     dir,X           ; B5 48
        LDX     dir,Y           ; B6 48
        SMB3    dir             ; B7 48

        CLV                     ; B8
        LDA     abs,Y           ; B9 4241
        TSX                     ; BA
        DB      $BB             ; BB
        LDY     abs,X           ; BC 4241
        LDA     abs,X           ; BD 4241
        LDX     abs,Y           ; BE 4241
        BBS3    dir,*           ; BF 48 FD

        CPY     #imm            ; C0 49
        CMP     (idx,X)         ; C1 58
        DB      $C2             ; C2
        DB      $C3             ; C3
        CPY     dir             ; C4 48
        CMP     dir             ; C5 48
        DEC     dir             ; C6 48
        SMB4    dir             ; C7 48

        INY                     ; C8
        CMP     #imm            ; C9 49
        DEX                     ; CA
        DB      $CB             ; CB
        CPY     abs             ; CC 4241
        CMP     abs             ; CD 4241
        DEC     abs             ; CE 4241
        BBS4    dir,*           ; CF 48 FD

        BNE     *               ; D0 FE
        CMP     (idx),Y         ; D1 58
        CMP     (idx)           ; D2 58
        DB      $D3             ; D3
        DB      $D4             ; D4
        CMP     dir,X           ; D5 48
        DEC     dir,X           ; D6 48
        SMB5    dir             ; D7 48

        CLD                     ; D8
        CMP     abs,Y           ; D9 4241
        PHX                     ; DA
        DB      $DB             ; DB
        DB      $DC             ; DC
        CMP     abs,X           ; DD 4241
        DEC     abs,X           ; DE 4241
        BBS5    dir,*           ; DF 48 FD

        CPX     #imm            ; E0 49
        SBC     (idx,X)         ; E1 58
        DB      $E2             ; E2
        DB      $E3             ; E3
        CPX     dir             ; E4 48
        SBC     dir             ; E5 48
        INC     dir             ; E6 48
        SMB6    dir             ; E7 48

        INX                     ; E8
        SBC     #imm            ; E9 49
        NOP                     ; EA
        DB      $EB             ; EB
        CPX     abs             ; EC 4241
        SBC     abs             ; ED 4241
        INC     abs             ; EE 4241
        BBS6    dir,*           ; EF 48 FD

        BEQ     *               ; F0 FE
        SBC     (idx),Y         ; F1 58
        SBC     (idx)           ; F2 58
        DB      $F3             ; F3
        DB      $F4             ; F4
        SBC     dir,X           ; F5 48
        INC     dir,X           ; F6 48
        SMB7    dir             ; F7 48

        SED                     ; F8
        SBC     abs,Y           ; F9 4241
        PLX                     ; FA
        DB      $FB             ; FB
        DB      $FC             ; FC
        SBC     abs,X           ; FD 4241
        INC     abs,X           ; FE 4241
        BBS7    dir,*           ; FF 48 FD

        END
