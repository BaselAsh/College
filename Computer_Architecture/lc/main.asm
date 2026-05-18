        .ORIG   x3000
        
        LD      R1, FIVE
        LD      R2, FOUR
        AND     R3, R3, #0


    
AGAIN   ADD     R3, R3, R1
        ADD     R2, R2, #-1
        BRP     AGAIN

        LD      R0, HEX30
        ADD     R0, R0, R3
        OUT
        ST      R3, RESULT
        



        HALT
        
    

    



FIVE    .FILL   #2
FOUR    .FILL   #4
HEX30   .FILL   x30
RESULT  .BLKW   1

        .END
