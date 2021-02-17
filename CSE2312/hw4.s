.global prodF64
.global int32ToFloat
.global dotpF32
.global minF64

.text

// Ethan Chase | 1001457646
// CSE 2312-002

//a. void prodF64(double z[], const double x[], const double y[], uint32_t count)
// compute the product of each element in the arrays x and y containing count entries; z[i] = x[i] * y[i], 
//for i = 0, 1, … count-1. If x = {10, 20, 30}, y = {5, 10, 5}, and count = 3, then z = {50, 200, 150}
prodF64:
	cmp R3, #0					//Is the count = 0?
	BEQ prodF64_end				//yes, end
	VLDR D0, [R1]				//no, load the current value of R1
	VLDR D1, [R2]				//load the current value of R2
	ADD R1, R1, #8				//Increment to next value of R1 array
	ADD R2, R2, #8				//Increment to next value of R2 array
	VMUL.F64 D2, D0, D1			//Multiply current values of R1 and R2 arrays
	VSTR D2, [R0]				//Store product of R1 and R2 into R0 at current spot
	ADD R0, R0, #8				//Increment to next value of R0 array
	SUB R3, #1					//Decrement the count
	B prodF64					//Continue the loop
prodF64_end:
	BX LR

//b. float int32ToFloat(int32_t x)
// converts the signed integer to a single-precision floating point number
int32ToFloat:
	VMOV S1, R0					//Set S1 to R0(value passed in)
	VCVT.F32.S32 S0, S1			//Convert int32_t into float
	BX LR


//c. float dotpF32(const float x[], const float y[], uint32_t count)
// returns the dot product of two arrays (x and y) containing count entries
dotpF32:
	MOV R3, #0					//Set R3 to 0
	VMOV S0, R3					//Set S0 to 0 through R3
dotpF32_loop:
	CMP R2, #0					//Is the count = 0?
	BEQ dotpF32_end				//yes, end
	VLDR S1, [R0]				//no, load current value of R0 array
	VLDR S2, [R1]				//load current value of R1 array
	ADD R0, R0, #4				//Increment to next value in R0 array
	ADD R1, R1, #4				//Increment to next value in R1 array
	VMUL.F32 S3, S1, S2			//Multiply current values of R0 and R1 arrays into S3
	VADD.F32 S0, S0, S3			//Add S3 to current sum of multiplications
	SUB R2, R2, #1				//Decrement the count
	B dotpF32_loop				//Continue the loop
dotpF32_end:
	BX LR

//d. double minF64(const double x[], uint32_t count)
// returns the minimum value in the array (x) containing count entries. if x = {-1.1, 20, -3} and count = 3, 
//then the function returns -3.
minF64:
	MOV R2, #0					//Set R2 to 0
	CMP R1, #0					//Is count = 0?
	VMOV.F64 D0, R2, R2 		//Initially set D0 to 0
	BEQ minF64_end				//If count = 0, end 
	VLDR D0, [R0]				//Load x[0] into D0 as default value
	ADD R0, R0, #8				//Increment to next value in R0 array
	SUB R1, R1, #1				//Decrement size
minF64_loop:
	CMP R1, #0					//Is the count = 0?
	BEQ minF64_end				//yes, end
	VLDR D1, [R0]				//no,load current value of R0 array
	ADD R0, R0, #8				//Increment to next value in R0 array
	SUB R1, R1, #1				//Decrement count
	VCMP.F64 D0, D1				//Compare current min to x[i]
	VMRS APSR_nzcv, FPSCR		//Load flags from VCMP
	VMOVGT.F64 D0, D1			//If D0 > D1, D0 = D1
	B minF64_loop				//Continue loop
minF64_end:
	BX LR
	


