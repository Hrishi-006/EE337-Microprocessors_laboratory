ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL MAC_THRESH
HERE: SJMP HERE
ORG 130H

MAC_THRESH:
; Perform MAC operation
; Store 18-bit result at 50H,51H,52H
; Compare result with T1 and T2 (use XRL if required)
; Set/clear P3.0 and P3.1 accordingly
CLR P3.0
CLR P3.1
MOV 77H,#00H
MOV 78H,#00H
MOV 79H,#00H
MOV 7BH,#00H


MOV A,70H
MOV B,73H
MUL AB
MOV 54H,A
MOV 53H,B

MOV A,71H
MOV B,74H
MUL AB
MOV 56H,A
MOV 55H,B

MOV A,72H
MOV B,75H
MUL AB
MOV 58H,A
MOV 57H,B

SJMP ADD16
behind:

MOV 76H,#01H
MOV 7AH,#80H



MOV R7,#03H
MOV R1,#50H
MOV R0,#76H
there:
MOV A,@R1
CLR C
SUBB A,@R0
JC ss  ;  when T1>x
JZ la ; when they are equal
SETB P3.0	;when x>T1
SETB P3.1
SJMP done
la:
INC R1
INC R0

DJNZ R7,there

ss:
MOV R0,#79H
MOV R1,#50H
MOV R7,#03H

there2:
MOV A,@R1
CLR C
SUBB A,@R0
JC s2  ;  when T2>x
JZ l2 ; when they are equal
CLR P3.0	;when x>T2
SETB P3.1
SJMP done
l2:
INC R1
INC R0

DJNZ R7,there2
s2:

SETB P3.0
CLR P3.1

done:
RET
ADD16:
CLR A
CLR C
MOV A,54H
ADD A,56H
MOV 52H,A 
MOV A,53H
ADDC A,55H
MOV 51H,A
CLR A
ADDC A,#00H
MOV 50H,A

CLR A
CLR C
MOV A,58H
ADD A,52H
MOV 52H,A 
MOV A,57H
ADDC A,51H
MOV 51H,A
CLR A
ADDC A,#00H
MOV 50H,A
SJMP behind
RET

END