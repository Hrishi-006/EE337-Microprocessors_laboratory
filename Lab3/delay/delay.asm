ORG 0H
LJMP MAIN
ORG 100H
MAIN:
MOV P1, #01H
CALL DELAY_1s
MOV P1, #00H
HERE: SJMP HERE
ORG 130H

DELAY_1s:
push 00h
mov r0, #100 
h3: acall delay_10ms		;0.998555 s
djnz r0, h3
pop 00h
RET

delay_10ms:
push 00h
mov r0, #40
h2: acall delay_250us
djnz r0, h2
pop 00h
ret

delay_250us:
push 00h
mov r0, #244
h1: djnz r0, h1
pop 00h
ret

END