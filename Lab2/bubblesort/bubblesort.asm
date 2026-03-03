ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL BUBBLESORT
HERE: SJMP HERE
ORG 130H
// *****************
SWAPN:
// ADD YOUR CODE HERE
// Swap two numbers if the first is greater than the second
loop:
behind:
	MOV A, @R0
    INC R0
    CLR C
    SUBB A, @R0         
    JC NOSWAP           

    MOV A, @R0         
    MOV R5, A          
    DEC R0
    MOV A, @R0       
    INC R0
    MOV @R0, A          
    DEC R0
    MOV A, R5
    MOV @R0, A          
    INC R0
	NOSWAP:
	CJNE R0,#67H, behind
	JMP ahead

RET
BUBBLESORT:
// ADD YOUR CODE HERE
// Perform bubble sort on the array
MOV B,#08H
ahead:
MOV R0,#60H
DJNZ B, loop

RET
END