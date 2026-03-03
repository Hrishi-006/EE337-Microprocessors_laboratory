/* Calculator using Port 3
   Operand1  -> P3
   Operand2  -> P3
   Opcode    -> P3
   Result    -> 52H (low / quotient)
   Extra     -> 53H (high / carry / remainder)
*/

ORG 0H
LJMP MAIN

ORG 100H
MAIN:
CALL Cal
HERE: SJMP HERE

ORG 130H
Cal:
        ; -------- Read inputs --------
		
        MOV A, P3        ; Operand 1
        MOV 50H, A

        MOV A, P3        ; Operand 2
        MOV 51H, A

        MOV A, P3        ; Opcode
        MOV 54H, A

        ; -------- Load operands --------
        MOV A, 50H
        MOV B, 51H
        MOV R0, 54H

        ; -------- ADD --------
        CJNE R0, #01H, CHECK_SUB
        ADD A, B
        MOV 52H, A
        MOV 53H, #00H
        JNC ENDING
        MOV 53H, #01H
        SJMP ENDING

CHECK_SUB:
        ; -------- SUB --------
        CJNE R0, #02H, CHECK_MUL
        CLR C
        SUBB A, B
        MOV 52H, A
        MOV 53H, #00H
        JNC ENDING
        MOV 53H, #01H
        SJMP ENDING

CHECK_MUL:
        ; -------- MUL --------
        CJNE R0, #03H, CHECK_DIV
        MUL AB
        MOV 52H, A       ; Low byte
        MOV 53H, B       ; High byte
        SJMP ENDING

CHECK_DIV:
        ; -------- DIV --------
        CJNE R0, #04H, INVALID
        DIV AB
        MOV 52H, A       ; Quotient
        MOV 53H, B       ; Remainder
        SJMP ENDING

INVALID:
        MOV 52H, #00H
        MOV 53H, #00H
		SJMP ENDING
ENDING:
        ; -------- Display loop (unchanged) --------
Y:      MOV A , #0F0H
X:      MOV P1, A
        DEC A
        CJNE A , #00H , X
        JMP Y

RET

END
