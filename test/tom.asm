        ADD     R1,R2	        ;  0   0022
        ADDC    R1,R2	        ;  1   0422
        ADDQ    1,R2	        ;  2   0822
        ADDQT   1,R2            ;  3   0C22
        SUB     R1,R2           ;  4   1022
        SUBC    R1,R2           ;  5   1422
        SUBQ    1,R2            ;  6   1822
        SUBQT   1,R2            ;  7   1C22
        NEG     R2              ;  8   2002
        AND     R1,R2           ;  9   2422
        OR      R1,R2           ; 10   2822
        XOR     R1,R2           ; 11   2C22
        NOT     R2              ; 12   3002
        BTST    1,R2            ; 13   3422
        BSET    1,R2            ; 14   3822
        BCLR    1,R2            ; 15   3C22

        MULT    R1,R2           ; 16   4022
        IMULT   R1,R2           ; 17   4422
        IMULTN  R1,R2           ; 18   4822
        RESMAC  R2              ; 19   4C02
        IMACN   R1,R2           ; 20   5022
        DIV     R1,R2           ; 21   5422
        ABS     R2              ; 22   5802
        SH      R1,R2           ; 23   5C22
        SHLQ    31,R2           ; 24   6022
        SHRQ    31,R2           ; 25   6422
        SHA     R1,R2           ; 26   6822
        SHARQ   31,R2           ; 27   6C22
        ROR     R1,R2           ; 28   7022
        RORQ    1,R2            ; 29   7422
        ROLQ    31,R2           ; 29   7422
        CMP     R1,R2           ; 30   7822
        CMPQ    1,R2            ; 31   7C22

        SAT8    R2              ; 32 T 8002
        SUBQMOD 1,R2            ; 32 J 8022
        SAT16   R2              ; 33 T 8402
        SAT16S  R2              ; 33 J 8402
        MOVE    R1,R2           ; 34   8822
        MOVEQ   1,R2            ; 35   8C22
        MOVETA  R1,R2           ; 36   9022
        MOVEFA  R1,R2           ; 37   9422
        MOVEI   $12345678,R2    ; 38   9802 56781234
        LOADB   (R1),R2         ; 39   9C22
        LOADW   (R1),R2         ; 40   A022
        LOAD    (R1),R2         ; 41   A422
        LOADP   (R1),R2         ; 42 T A822
        SAT32S  R2              ; 42 J A802
        LOAD    (R14+1),R2      ; 43   AC22
        LOAD    (R15+1),R2      ; 44   B022
        STOREB  R1,(R2)         ; 45   B422
        STOREW  R1,(R2)         ; 46   B822
        STORE   R1,(R2)         ; 47   BC22

        STOREP  R1,(R2)         ; 48 T C022
        MIRROR  R2              ; 48 J C002
        STORE   R1,(R14+2)      ; 49   C422
        STORE   R1,(R15+2)      ; 50   C822
        MOVE    PC,R2           ; 51   CC02
        JUMP    $02,(R1)        ; 52   D022
        JR      $02,*+2         ; 53   D422
        MMULT   R1,R2           ; 54   D822
        MTOI    R1,R2           ; 55   DC22
        NORMI   R1,R2           ; 56   E022
        NOP                     ; 57   E400
        LOAD    (R14+R1),R2     ; 58   E822
        LOAD    (R15+R1),R2     ; 59   EC22
        STORE   R1,(R14+R2)     ; 60   F022
        STORE   R1,(R15+R2)     ; 61   F422
        SAT24   R2              ; 62 J F802
        UNPACK  R2              ; 63 T FC02
        PACK    R2              ; 63 T FC22
        ADDQMOD 1,R2            ; 63 J FC22
