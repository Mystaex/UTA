.global isStrSame
.global strConcatenate
.global sumU16_32
.global sumS32
.global countInRange
.global rightStringFull
.global rightStringTrunc
.global sortAscending
.global decimalStringToUint16
.global decimalStringToInt8
.global hexStringToUint8
.global uint32ToBinaryString
.global findCityAligned
.global findCityPacked

.text

//A
//bool isStrSame(const char str1[], const char str2[])
//returns 1 if the strings match, 0 otherwise
isStrSame:
	PUSH {R4}
	MOV R2, R0
	MOV R0, #1
isSame:
	LDRSB R3, [R1], #1
	LDRSB R4, [R2], #1
	CMP R3, R4
	BEQ checkNULL
	MOV R0, #0
	B strSameEnd
checkNULL:
	CMP R3, #0
	BEQ strSameEnd
	B isSame
strSameEnd:
	POP {R4}
	BX LR


//B
//void strConcatenate(char strTo[], const char strFrom[])
//adds the contents of string strFrom to strTo
//note: strTo must have enough space to hold strFrom and strTo
strConcatenate:
	LDRB R2, [R0], #1
	CMP R2, #0
	BNE strConcatenate
	SUB R0, R0, #1
strCadd:
	LDRB R3, [R1], #1
	STRB R3, [R0], #1
	CMP R3, #0
	BNE strCadd
	BX LR

//C
//uint32_t sumU16_32(const uint16_t x[], uint32_t count)
// returns sum of the values in the array (x) containing count entries.
sumU16_32:
	MOV R3, #0
sumU16Loop:
	SUB R1, R1, #1
	LDRH R2, [R0], #2
	ADD R3, R3, R2
	CMP R1, #0
	BNE sumU16Loop
	MOV R0, R3
	BX LR
	

//D
//int32_t sumS32(const int32_t x[], uint32_t count)
// returns sum of the values in the array (x) containing count entries.
sumS32:
	MOV R3, #0
sumS32Loop:
	SUB R1, R1, #1
	LDR R2, [R0], #4
	ADD R3, R3, R2
	CMP R1, #0
	BGT sumS32Loop
	MOV R0, R3
	BX LR

//E
//uint32_t countInRange(const int32_t x[], int32_t low, int32_t high, uint32_t count)
// returns number of values in the array (x) containing count entries that are >= low and <= high
countInRange:
	PUSH {R4}
	PUSH {R5}
	MOV R5, #0
countIRLoop:
	SUB R3, R3, #1
	LDR R4, [R0], #4
	CMP R4, R1
	BGE checkRange
	CMP R3, #0
	BNE countIRLoop
	B endCountInRange
checkRange:
	CMP R4, R2
	ADDLE R5, #1
	CMP R3, #0
	BNE countIRLoop
endCountInRange:
	MOV R0, R5
	POP {R5}
	POP {R4}
	BX LR

//F
//void rightStringFull(char* strOut, const char* strIn, uint32_t length)
// input: array (strIn) containing the input string, and the number of characters to extract (length)
// output: array (strOut) containing length number of strIn characters from the end of the array or an empty string if the length is larger than can be accommodated
// strIn = ‘abcdef’, length = 5 → returns strOut = ‘bcdef’
// strIn = ‘abcdef’, length = 7 → returns strOut = ‘’
rightStringFull:
	PUSH {R4}
	MOV R3, #0
getLengthRSF:
	LDRSB R4, [R1], #1
	CMP R4, #0
	BEQ RSFCont
	ADD R3, R3, #1
	B getLengthRSF
RSFCont:
	CMP R3, R2
	MOVLT R3, #0
	STRLTB R3, [R0], #1
	BLT endRSF
	ADD R2, R2, #1
	SUB R1, R1, R2
RSFCont2:
	LDRSB R4, [R1], #1
	STRB R4, [R0], #1
	CMP R4, #0
	BNE RSFCont2
endRSF:
	POP {R4}
	BX LR

//G
//void rightStringTrunc(char* strOut, const char* strIn, uint32_t length)
// input: array (strIn) containing the input string, and the number of characters to extract (length)
// output: array (strOut) containing up to, but not exceeding length number ofstrIn characters from the end of the array
// strIn = ‘abcdef’, length = 5 → returns strOut = ‘bcdef’
// strIn = ‘abcdef’, length = 7 → returns strOut = ‘abcdef’
rightStringTrunc:
	PUSH {R4}
	PUSH {R5}
	MOV R3, #0
	MOV R5, #0
getLengthRST:
	LDRB R4, [R1], #1
	CMP R4, #0
	BEQ RSTCont
	ADD R3, R3, #1
	B getLengthRST
RSTCont:
	CMP R3, R2
	MOVLE R5, R3
	MOVGT R5, R2
	ADD R5, R5, #1
	SUB R1, R1, R5
RSTCont2:
	LDRB R4, [R1], #1
	STRB R4, [R0], #1
	CMP R4, #0
	BNE RSTCont2
endRST:
	POP {R5}
	POP {R4}
	BX LR

//H
//void sortAscending (uint32_t x[], uint32_t count)
// input: array (x) containing count entries
// output: array (x), with the values sorted in ascending order
sortAscending:
	PUSH {R4}
	PUSH {R5}
	PUSH {R6}
sortNext:
	MOV R2, #0
	MOV R6, #0
AsortLoop:
	ADD R3, R2, #1
	CMP R3, R1
	BGE sortGreater
	LDR R4,[R0,R2,LSL #2]
	LDR R5,[R0,R3,LSL #2]
	CMP R4, R5
	STRGT R5,[R0,R2,LSL #2]
	STRGT R4,[R0,R3,LSL #2]
	ADDGT R6, R6, #1
	MOV R2, R3
	B AsortLoop
sortGreater:
	CMP R6, #0
	SUBGT R1, R1, #1
	BGT sortNext
sortEnd:
	POP {R6}
	POP {R5}
	POP {R4}
	BX LR
	

//I
//uint16_t decimalStringToUint16(const char* str)
// convert the null-terminated string (str) to an unsigned 16-bit integer
// treat the string as representing a decimal number
// if a character other than 0, 1, 2, 3, 4, 5, 6, 7, 8, or 9 is present or the value is too large, return 0
decimalStringToUint16:
	PUSH {R4}
	PUSH {R5}
	PUSH {R6}
	MOV R1, #0
	MOV R2, #1
	MOV R4, #0
	MOV R5, #10
	MOV R6, #65536
endOfStringU16:
	LDRSB R3, [R0], #1
	ADD R4, R4, #1
	CMP R3, #0
	BNE endOfStringU16
	SUB R4, R4, #1
	SUB R0, R0, #2
DSU16loop:
	LDRSB R3, [R0]
	SUB R0, R0, #1
	SUB R3, R3, #48
	CMP R3, #0
	BGE checkIfInRangeDSU16
	MOV R1, #65536
	B endDSU16
checkIfInRangeDSU16:
	CMP R3, #10
	MOVGE R1, #65536
	BGE endDSU16
	MUL R3, R3, R2
	ADD R1, R1, R3
	MUL R2, R2, R5
	SUB R4, R4, #1
	CMP R4, #0
	BNE DSU16loop
endDSU16:
	CMP R1, R6
	MOVLT R0, R1
	MOVGE R0, #0
	POP {R6}
	POP {R5}
	POP {R4}
	BX LR

//J
//int8_t decimalStringToInt8(const char* str)
// convert the null-terminated string (str) to a signed 8-bit integer
// treat the string as representing a decimal number
// if a character other than 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, or – is present or the value is out of range, return 0
decimalStringToInt8:
	PUSH {R4}
	PUSH {R5}
	PUSH {R6}
	PUSH {R7}
	MOV R1, #0
	MOV R2, #1
	MOV R4, #0
	MOV R5, #10
	MOV R6, #128			
	MVN R7, #127			
endOfStringI8:
	LDRSB R3, [R0], #1
	ADD R4, R4, #1
	CMP R3, #0
	BNE endOfStringI8
	SUB R4, R4, #1
	SUB R0, R0, #2
DSI8loop:
	LDRSB R3, [R0]
	SUB R0, R0, #1
	SUB R4, R4, #1
	SUB R3, R3, #48
	CMP R3, #-3
	SUBEQ R1, R1, #1
	MVNEQ R1, R1
	BEQ endDSI8
	CMP R3, #0
	BGE checkIfInRangeDSI8
	MOV R1, #128
	B endDSI8
checkIfInRangeDSI8:
	CMP R3, #10
	MOVGE R1, #128
	BGE endDSI8
	MUL R3, R3, R2
	ADD R1, R1, R3
	MUL R2, R2, R5
	CMP R4, #0
	BNE DSI8loop
endDSI8:
	MOV R0, #0
	CMP R1, R7
	BLT endcontDSI8
	CMP R1, R6
	MOVLT R0, R1
endcontDSI8:
	POP {R7}
	POP {R6}
	POP {R5}
	POP {R4}
	BX LR

//K
//uint8_t hexStringToUint8(const char* str)
// convert the null-terminated string (str) to an unsigned 8-bit integer
// treat the string as representing a hexadecimal number
// if a character other than 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, or F is present or the value is too large, return 0
hexStringToUint8:
	PUSH {R4}
	PUSH {R5}
	PUSH {R6}
	MOV R1, #0			//Current Val
	MOV R2, #1			//Weight
	MOV R4, #0			//Count
	MOV R5, #16			//Weight factor
	MOV R6, #256		//Max Val			
endOfStringH8:
	LDRSB R3, [R0], #1
	ADD R4, R4, #1
	CMP R3, #0
	BNE endOfStringH8
	SUB R4, R4, #1
	SUB R0, R0, #2
HSU8loop:
	LDRSB R3, [R0]
	SUB R0, R0, #1
	SUB R4, R4, #1
	SUB R3, R3, #48
	CMP R3, #0
	BGE checkIfInRangeHSU8
	MOV R1, #256
	B endDSI8
checkIfInRangeHSU8:
	CMP R3, #10
	BLT RangeHSU8cont
	SUB R3, #7
	CMP R3, #10
	MOVLT R1, #256
	BLT endHSU8
	CMP R3, #16
	MOVGE R1, #256
	BGE endHSU8
RangeHSU8cont:
	MUL R3, R3, R2
	ADD R1, R1, R3
	MUL R2, R2, R5
	CMP R4, #0
	BNE HSU8loop
endHSU8:
	MOV R0, #0
	CMP R1, R6
	MOVLT R0, R1
	POP {R6}
	POP {R5}
	POP {R4}
	BX LR

//L
//void uint32ToBinaryString (char* str, uint32_t x)
// convert the unsigned integer (x) to a null-terminated string (str) representing a binary number
uint32ToBinaryString:
	MOV R2, #0x80000000
utb_loop:
    TST R1, R2 
    MOVNE R3, #49
    MOVEQ R3, #48 
    STRB R3, [R0], #1 
    MOVS R2, R2, LSR #1
    BNE utb_loop
    MOV R3, #0
    STRB R3, [R0]
    BX LR

//M
//int32_t findCityAligned (const char city[], const BUSINESS6 business[], uint32_t count)
// returns the index of the first entry in the array (business) containing count entries which matches the requested city. If the city is not found, return a value of -1. You can assume that C default alignment is used for this problem.
findCityAligned:
				//R0 City
				//R1 Business[]
				//R2 count
	PUSH {R4} 	//R4 index 
	PUSH {R5} 	//R5 char in city[] 
	PUSH {R6} 	//R6 char in business.city[] starts at 64
	PUSH {R8}	//R8 size of struct
	PUSH {R9}	//R9 keep record of city
	MVN R3, #0	//Assume city not found
	MOV R4, #0
	MOV R8, #100
	MOV R9, R0
	ADD R1, R1, #64
cityLoop:
	LDRSB R5, [R0]
	LDRSB R6, [R1]
	CMP R5, R6
	BNE cityLoop2
	ADD R0, R0, #1
	ADD R1, R1, #1
	CMP R5, #0
	BNE cityLoop
	MOVEQ R3, R4
	BEQ endCityAlign
cityLoop2:
	MOV R0, R9
	ADD R4, R4, #1
	ADD R1, R1, R8
	CMP R4, R2
	BNE cityLoop
endCityAlign:
	MOV R0, R3
	POP {R9}
	POP {R8}
	POP {R6}
	POP {R5}
	POP {R4}
	BX LR
	
//N
//int32_t findCityPacked (const char city[], const BUSINESS6 business[], uint32_t count)
// returns the index of the first entry in the array (business) containing count entries which matches the requested city. If the city is not found, return a value of -1. You can assume that C packing is used for this problem.
findCityPacked:
				//R0 City
				//R1 Business[]
				//R2 count
	PUSH {R4} 	//R4 index 
	PUSH {R5} 	//R5 char in city[] 
	PUSH {R6} 	//R6 char in business.city[] starts at 64
	PUSH {R8}	//R8 size of struct
	PUSH {R9}	//R9 keep record of city
	MVN R3, #0	//Assume city not found
	MOV R4, #0
	MOV R8, #98
	MOV R9, R0
	ADD R1, R1, #63
cityLoopP:
	LDRSB R5, [R0]
	LDRSB R6, [R1]
	CMP R5, R6
	BNE cityLoopP2
	ADD R0, R0, #1
	ADD R1, R1, #1
	CMP R5, #0
	BNE cityLoopP
	MOVEQ R3, R4
	BEQ endCityAlignP
cityLoopP2:
	MOV R0, R9
	ADD R4, R4, #1
	ADD R1, R1, R8
	CMP R4, R2
	BNE cityLoopP
endCityAlignP:
	MOV R0, R3
	POP {R9}
	POP {R8}
	POP {R6}
	POP {R5}
	POP {R4}
	BX LR
