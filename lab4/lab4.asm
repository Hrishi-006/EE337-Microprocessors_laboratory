ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL TAKE_INP
CALL CHECK_SORT

HERE: SJMP HERE
ORG 130H
// *****************
DELAY:
delay_4:
push 06h
mov r6, #4
h3: acall delay_1
djnz r6, h3
pop 06h
ret
delay_8:
push 06h
mov r6, #8
h4: acall delay_1
djnz r6, h4
pop 06h
ret
delay_1:
push 06h
mov r6, #100
h5: acall delay_10ms
djnz r6, h5
pop 06h
ret
delay_10ms:
push 06h
mov r6, #40
h2: acall delay_250us
djnz r6, h2
pop 06h
ret
delay_250us:
push 06h
mov r6, #244
h1: djnz r6, h1
pop 06h
ret



TAKE_INP:
MOV R0,#01H
MOV R1,#50H

loop:

MOV A,R0 ;light the pins
ANL A,#0FH
SWAP A
ORL A,#0FH 
MOV P1,A
ACALL delay_8

;take the higher input bits
MOV A,P1
ANL A,#0FH
SWAP A
MOV @R1,A


INC R0

MOV A,R0 ;light the pins
ANL A,#0FH
SWAP A
ORL A,#0FH 
MOV P1,A
ACALL delay_8

MOV A,P1	;lower bits
ANL A,#0FH
ADD A,@R1
MOV @R1,A
INC R1
INC R0
CJNE R0,#0DH,loop

RET


CHECK_SORT:
; Check if array of 5 elements is sorted
MOV R0,#04H
MOV R1,#50H
here2: 
MOV A,@R1      
    INC R1
    CLR C
    SUBB A,@R1     
    JC CONTINUE    
    JZ CONTINUE    

    SJMP not_sorted

CONTINUE:
    DJNZ R0, here2
	SJMP sorted



BIN_SEARCH:
sorted:
    MOV R7,#50H      ; low
    MOV R1,#54H      ; high
behind:
    ; Check if low > high
    MOV A,R7
    CLR C
    SUBB A,R1
    JC continue_search   ; low < high, continue
    JZ continue_search   ; low == high, one element left to check
    SJMP not_found       ; low > high, not found

continue_search:
    ; Calculate mid = (low + high) / 2
    MOV A,R7
    ADD A,R1
    CLR C
    RRC A
    MOV R0,A
    
    ; Compare array[mid] with key
    MOV A,@R0
    CLR C
    SUBB A,55H
    JZ found
    JC there          ; key > mid
    
    ; key < mid, search lower half
    MOV A,R0
    DEC A
    MOV R1,A          ; high = mid - 1
    SJMP behind
    
there:
    ; key > mid, search upper half
    MOV A,R0
    INC A
    MOV R7,A          ; low = mid + 1
    SJMP behind
	
LED_DISP:
; Display result or error on LEDs

not_sorted:
ACALL delay_4
MOV P1,#0F0H
ACALL delay_4
SJMP done

not_found:
ACALL delay_4
MOV P1,#80H
ACALL delay_4
SJMP done
found:
ACALL delay_4
MOV A,R0
CLR C
SUBB A,#50H
ADD A,#01H
SWAP A
MOV P1,A
ACALL delay_4
done:
RET
END