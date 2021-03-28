.global addU32_U64
.global addS64
.global convertS8ToS32
.global convertU16ToS32
.global maxS16
.global maxU32
.global isGreaterThanU16
.global isGreaterThanS16
.global shiftRightS32
.global shiftU16
.global isEqualU16

.text

//A
addU32_U64:
	ADD R0, R0, R1
	BX LR

//B
addS64:
	ADDS R0, R0, R2
	ADC R1, R1, R3
	BX LR

//C
convertS8ToS32:
	MOV R0, R0, ASR #0
	BX LR
	
//D
convertU16ToS32:
	MOV R0, R0, LSR #0
	BX LR
	
//E
maxS16:
	cmp R0, R1
	BMI smaller
	MOV R0, R0
	BX LR
smaller:
	MOV R0, R1
	BX LR
	
//F
maxU32:
	cmp R0, R1
	BMI smaller //smaller from above problem (E)
	MOV R0, R0
	BX LR
	
//G
isGreaterThanU16:
	cmp R0, R1
	BGT greater
	MOV R0, #0
	BX LR
greater:
	MOV R0, #1
	BX LR
	
//H
isGreaterThanS16:
	cmp R0, R1
	BGT greater //greater from above problem (H)
	MOV R0, #0
	BX LR
	
//I
shiftRightS32:
	MOV R0, R0, ASR R1
	BX LR

//J
shiftU16:
	cmp R1, #0
	BMI shiftRight
	MOV R0, R0, LSL R1
	BX LR
shiftRight:
	NEG R1, R1
	MOV R0, R0, LSR R1
	BX LR
	
//K
isEqualU16:
	cmp R0, R1
	BEQ equal
	MOV R0, #0
	BX LR
equal: 
	MOV R0, #1
	BX LR
