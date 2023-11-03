_main:
;FinalPart1.c,27 :: 		void main() {
;FinalPart1.c,29 :: 		RCC_APB2ENR |= 1 << 2;  // ENABLE GPIOA clock - necessary to use GPIOA
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #4
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
STR	R1, [R0, #0]
;FinalPart1.c,30 :: 		RCC_APB2ENR |= 1 << 3;  // ENABLE GPIOB clock - necessary to use GPIOB
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #8
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
STR	R1, [R0, #0]
;FinalPart1.c,31 :: 		RCC_APB2ENR |= 1 << 4;  // ENABLE GPIOC clock - necessary to use GPIOC
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #16
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
STR	R1, [R0, #0]
;FinalPart1.c,32 :: 		RCC_APB2ENR |= 1 << 5;  // ENABLE GPIOD clock - necessary to use GPIOD
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #32
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
STR	R1, [R0, #0]
;FinalPart1.c,33 :: 		RCC_APB2ENR |= 1 << 6;  // ENABLE GPIOE clock - necessary to use GPIOE
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #64
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
STR	R1, [R0, #0]
;FinalPart1.c,35 :: 		GPIOE_CRH = 0x33333333; //SETS GPIOE HIGH as output
MOV	R1, #858993459
MOVW	R0, #lo_addr(GPIOE_CRH+0)
MOVT	R0, #hi_addr(GPIOE_CRH+0)
STR	R1, [R0, #0]
;FinalPart1.c,37 :: 		GPIOA_CRL = 0x44444444; //SETS GPIOA LOW as input
MOV	R1, #1145324612
MOVW	R0, #lo_addr(GPIOA_CRL+0)
MOVT	R0, #hi_addr(GPIOA_CRL+0)
STR	R1, [R0, #0]
;FinalPart1.c,38 :: 		GPIOA_CRH = 0x44444444; //SETS GPIOA HIGH as input
MOV	R1, #1145324612
MOVW	R0, #lo_addr(GPIOA_CRH+0)
MOVT	R0, #hi_addr(GPIOA_CRH+0)
STR	R1, [R0, #0]
;FinalPart1.c,40 :: 		GPIOB_CRL = 0x44444444; //SETS GPIOB LOW as input
MOV	R1, #1145324612
MOVW	R0, #lo_addr(GPIOB_CRL+0)
MOVT	R0, #hi_addr(GPIOB_CRL+0)
STR	R1, [R0, #0]
;FinalPart1.c,41 :: 		GPIOB_CRH = 0x44444444; //SETS GPIOB HIGH as input
MOV	R1, #1145324612
MOVW	R0, #lo_addr(GPIOB_CRH+0)
MOVT	R0, #hi_addr(GPIOB_CRH+0)
STR	R1, [R0, #0]
;FinalPart1.c,43 :: 		GPIOC_CRL = 0x44444444; //SETS GPIOC LOW as input
MOV	R1, #1145324612
MOVW	R0, #lo_addr(GPIOC_CRL+0)
MOVT	R0, #hi_addr(GPIOC_CRL+0)
STR	R1, [R0, #0]
;FinalPart1.c,44 :: 		GPIOC_CRH = 0x44444444; //SETS GPIOC HIGH as input
MOV	R1, #1145324612
MOVW	R0, #lo_addr(GPIOC_CRH+0)
MOVT	R0, #hi_addr(GPIOC_CRH+0)
STR	R1, [R0, #0]
;FinalPart1.c,46 :: 		GPIOD_CRL = 0x44444444; //SETS GPIOD LOW as input
MOV	R1, #1145324612
MOVW	R0, #lo_addr(GPIOD_CRL+0)
MOVT	R0, #hi_addr(GPIOD_CRL+0)
STR	R1, [R0, #0]
;FinalPart1.c,47 :: 		GPIOD_CRH = 0x44444444; //SETS GPIOD HIGH as input
MOV	R1, #1145324612
MOVW	R0, #lo_addr(GPIOD_CRH+0)
MOVT	R0, #hi_addr(GPIOD_CRH+0)
STR	R1, [R0, #0]
;FinalPart1.c,49 :: 		adcCONFIG();
BL	_adcCONFIG+0
;FinalPart1.c,52 :: 		for(;;){
L_main0:
;FinalPart1.c,55 :: 		GPIODConfigInput();
BL	_GPIODConfigInput+0
;FinalPart1.c,56 :: 		Joystick();
BL	_Joystick+0
;FinalPart1.c,61 :: 		GPIODConfigOutput();
BL	_GPIODConfigOutput+0
;FinalPart1.c,62 :: 		GPIOD_ODR = getAdcReading();
BL	_getAdcReading+0
MOVW	R1, #lo_addr(GPIOD_ODR+0)
MOVT	R1, #hi_addr(GPIOD_ODR+0)
STR	R0, [R1, #0]
;FinalPart1.c,63 :: 		delay_ms(100);
MOVW	R7, #5651
MOVT	R7, #5
NOP
NOP
L_main3:
SUBS	R7, R7, #1
BNE	L_main3
NOP
NOP
NOP
NOP
;FinalPart1.c,67 :: 		}
IT	AL
BAL	L_main0
;FinalPart1.c,68 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
_Joystick:
;FinalPart1.c,72 :: 		void Joystick() {
;FinalPart1.c,73 :: 		if(GPIOA_IDR.B6 == 1 & pa6state == 0){        //Function for RIGHT button
MOVW	R0, #lo_addr(GPIOA_IDR+0)
MOVT	R0, #hi_addr(GPIOA_IDR+0)
_LX	[R0, ByteOffset(GPIOA_IDR+0)]
CMP	R0, #1
MOVW	R1, #0
BNE	L__Joystick22
MOVS	R1, #1
L__Joystick22:
UXTB	R1, R1
MOVW	R0, #lo_addr(_pa6state+0)
MOVT	R0, #hi_addr(_pa6state+0)
LDR	R0, [R0, #0]
CMP	R0, #0
MOVW	R0, #0
BNE	L__Joystick23
MOVS	R0, #1
L__Joystick23:
AND	R0, R1, R0, LSL #0
CMP	R0, #0
IT	EQ
BEQ	L_Joystick5
;FinalPart1.c,74 :: 		GPIOE_ODR = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
STR	R1, [R0, #0]
;FinalPart1.c,75 :: 		pa6state = 1;
MOVS	R1, #1
MOVW	R0, #lo_addr(_pa6state+0)
MOVT	R0, #hi_addr(_pa6state+0)
STR	R1, [R0, #0]
;FinalPart1.c,76 :: 		}
L_Joystick5:
;FinalPart1.c,77 :: 		if(GPIOA_IDR.B6 == 0 & pa6state == 1){
MOVW	R0, #lo_addr(GPIOA_IDR+0)
MOVT	R0, #hi_addr(GPIOA_IDR+0)
_LX	[R0, ByteOffset(GPIOA_IDR+0)]
CMP	R0, #0
MOVW	R1, #0
BNE	L__Joystick24
MOVS	R1, #1
L__Joystick24:
UXTB	R1, R1
MOVW	R0, #lo_addr(_pa6state+0)
MOVT	R0, #hi_addr(_pa6state+0)
LDR	R0, [R0, #0]
CMP	R0, #1
MOVW	R0, #0
BNE	L__Joystick25
MOVS	R0, #1
L__Joystick25:
AND	R0, R1, R0, LSL #0
CMP	R0, #0
IT	EQ
BEQ	L_Joystick6
;FinalPart1.c,78 :: 		GPIOE_ODR.B9 = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
_SX	[R0, ByteOffset(GPIOE_ODR+0)]
;FinalPart1.c,79 :: 		GPIOE_ODR.B10 = 1;
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
_SX	[R0, ByteOffset(GPIOE_ODR+0)]
;FinalPart1.c,80 :: 		pa6state = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_pa6state+0)
MOVT	R0, #hi_addr(_pa6state+0)
STR	R1, [R0, #0]
;FinalPart1.c,81 :: 		}
L_Joystick6:
;FinalPart1.c,84 :: 		if(GPIOB_IDR.B5 == 1 & pb5state == 0){         //Function for DOWN button
MOVW	R0, #lo_addr(GPIOB_IDR+0)
MOVT	R0, #hi_addr(GPIOB_IDR+0)
_LX	[R0, ByteOffset(GPIOB_IDR+0)]
CMP	R0, #1
MOVW	R1, #0
BNE	L__Joystick26
MOVS	R1, #1
L__Joystick26:
UXTB	R1, R1
MOVW	R0, #lo_addr(_pb5state+0)
MOVT	R0, #hi_addr(_pb5state+0)
LDR	R0, [R0, #0]
CMP	R0, #0
MOVW	R0, #0
BNE	L__Joystick27
MOVS	R0, #1
L__Joystick27:
AND	R0, R1, R0, LSL #0
CMP	R0, #0
IT	EQ
BEQ	L_Joystick7
;FinalPart1.c,85 :: 		GPIOE_ODR = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
STR	R1, [R0, #0]
;FinalPart1.c,86 :: 		pb5state = 1;
MOVS	R1, #1
MOVW	R0, #lo_addr(_pb5state+0)
MOVT	R0, #hi_addr(_pb5state+0)
STR	R1, [R0, #0]
;FinalPart1.c,87 :: 		}
L_Joystick7:
;FinalPart1.c,88 :: 		if(GPIOB_IDR.B5 == 0 & pb5state == 1){
MOVW	R0, #lo_addr(GPIOB_IDR+0)
MOVT	R0, #hi_addr(GPIOB_IDR+0)
_LX	[R0, ByteOffset(GPIOB_IDR+0)]
CMP	R0, #0
MOVW	R1, #0
BNE	L__Joystick28
MOVS	R1, #1
L__Joystick28:
UXTB	R1, R1
MOVW	R0, #lo_addr(_pb5state+0)
MOVT	R0, #hi_addr(_pb5state+0)
LDR	R0, [R0, #0]
CMP	R0, #1
MOVW	R0, #0
BNE	L__Joystick29
MOVS	R0, #1
L__Joystick29:
AND	R0, R1, R0, LSL #0
CMP	R0, #0
IT	EQ
BEQ	L_Joystick8
;FinalPart1.c,89 :: 		GPIOE_ODR.B8 = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
_SX	[R0, ByteOffset(GPIOE_ODR+0)]
;FinalPart1.c,90 :: 		GPIOE_ODR.B12 = 1;
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
_SX	[R0, ByteOffset(GPIOE_ODR+0)]
;FinalPart1.c,91 :: 		pb5state = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_pb5state+0)
MOVT	R0, #hi_addr(_pb5state+0)
STR	R1, [R0, #0]
;FinalPart1.c,92 :: 		}
L_Joystick8:
;FinalPart1.c,98 :: 		if(GPIOC_IDR.B13 == 1 & pc13state == 0){       // Function for Click button
MOVW	R0, #lo_addr(GPIOC_IDR+0)
MOVT	R0, #hi_addr(GPIOC_IDR+0)
_LX	[R0, ByteOffset(GPIOC_IDR+0)]
CMP	R0, #1
MOVW	R1, #0
BNE	L__Joystick30
MOVS	R1, #1
L__Joystick30:
UXTB	R1, R1
MOVW	R0, #lo_addr(_pc13state+0)
MOVT	R0, #hi_addr(_pc13state+0)
LDR	R0, [R0, #0]
CMP	R0, #0
MOVW	R0, #0
BNE	L__Joystick31
MOVS	R0, #1
L__Joystick31:
AND	R0, R1, R0, LSL #0
CMP	R0, #0
IT	EQ
BEQ	L_Joystick9
;FinalPart1.c,99 :: 		GPIOE_ODR = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
STR	R1, [R0, #0]
;FinalPart1.c,100 :: 		pc13state = 1;
MOVS	R1, #1
MOVW	R0, #lo_addr(_pc13state+0)
MOVT	R0, #hi_addr(_pc13state+0)
STR	R1, [R0, #0]
;FinalPart1.c,101 :: 		}
L_Joystick9:
;FinalPart1.c,102 :: 		if(GPIOC_IDR.B13 == 0 & pc13state == 1){
MOVW	R0, #lo_addr(GPIOC_IDR+0)
MOVT	R0, #hi_addr(GPIOC_IDR+0)
_LX	[R0, ByteOffset(GPIOC_IDR+0)]
CMP	R0, #0
MOVW	R1, #0
BNE	L__Joystick32
MOVS	R1, #1
L__Joystick32:
UXTB	R1, R1
MOVW	R0, #lo_addr(_pc13state+0)
MOVT	R0, #hi_addr(_pc13state+0)
LDR	R0, [R0, #0]
CMP	R0, #1
MOVW	R0, #0
BNE	L__Joystick33
MOVS	R0, #1
L__Joystick33:
AND	R0, R1, R0, LSL #0
CMP	R0, #0
IT	EQ
BEQ	L_Joystick10
;FinalPart1.c,103 :: 		GPIOE_ODR = ~GPIOE_ODR;
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
LDR	R0, [R0, #0]
MVN	R1, R0
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
STR	R1, [R0, #0]
;FinalPart1.c,104 :: 		pc13state = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_pc13state+0)
MOVT	R0, #hi_addr(_pc13state+0)
STR	R1, [R0, #0]
;FinalPart1.c,105 :: 		}
L_Joystick10:
;FinalPart1.c,111 :: 		if(GPIOD_IDR.B2 == 1 & pd2state == 0){         //Function for Left button
MOVW	R0, #lo_addr(GPIOD_IDR+0)
MOVT	R0, #hi_addr(GPIOD_IDR+0)
_LX	[R0, ByteOffset(GPIOD_IDR+0)]
CMP	R0, #1
MOVW	R1, #0
BNE	L__Joystick34
MOVS	R1, #1
L__Joystick34:
UXTB	R1, R1
MOVW	R0, #lo_addr(_pd2state+0)
MOVT	R0, #hi_addr(_pd2state+0)
LDR	R0, [R0, #0]
CMP	R0, #0
MOVW	R0, #0
BNE	L__Joystick35
MOVS	R0, #1
L__Joystick35:
AND	R0, R1, R0, LSL #0
CMP	R0, #0
IT	EQ
BEQ	L_Joystick11
;FinalPart1.c,112 :: 		GPIOE_ODR = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
STR	R1, [R0, #0]
;FinalPart1.c,113 :: 		pd2state = 1;
MOVS	R1, #1
MOVW	R0, #lo_addr(_pd2state+0)
MOVT	R0, #hi_addr(_pd2state+0)
STR	R1, [R0, #0]
;FinalPart1.c,114 :: 		}
L_Joystick11:
;FinalPart1.c,115 :: 		if(GPIOD_IDR.B2 == 0 & pd2state == 1){
MOVW	R0, #lo_addr(GPIOD_IDR+0)
MOVT	R0, #hi_addr(GPIOD_IDR+0)
_LX	[R0, ByteOffset(GPIOD_IDR+0)]
CMP	R0, #0
MOVW	R1, #0
BNE	L__Joystick36
MOVS	R1, #1
L__Joystick36:
UXTB	R1, R1
MOVW	R0, #lo_addr(_pd2state+0)
MOVT	R0, #hi_addr(_pd2state+0)
LDR	R0, [R0, #0]
CMP	R0, #1
MOVW	R0, #0
BNE	L__Joystick37
MOVS	R0, #1
L__Joystick37:
AND	R0, R1, R0, LSL #0
CMP	R0, #0
IT	EQ
BEQ	L_Joystick12
;FinalPart1.c,116 :: 		GPIOE_ODR.B13 = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
_SX	[R0, ByteOffset(GPIOE_ODR+0)]
;FinalPart1.c,117 :: 		GPIOE_ODR.B14 = 1;
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
_SX	[R0, ByteOffset(GPIOE_ODR+0)]
;FinalPart1.c,118 :: 		pd2state = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_pd2state+0)
MOVT	R0, #hi_addr(_pd2state+0)
STR	R1, [R0, #0]
;FinalPart1.c,119 :: 		}
L_Joystick12:
;FinalPart1.c,126 :: 		if(GPIOD_IDR.B4 == 1 & pd4state == 0){         //Function for UP button
MOVW	R0, #lo_addr(GPIOD_IDR+0)
MOVT	R0, #hi_addr(GPIOD_IDR+0)
_LX	[R0, ByteOffset(GPIOD_IDR+0)]
CMP	R0, #1
MOVW	R1, #0
BNE	L__Joystick38
MOVS	R1, #1
L__Joystick38:
UXTB	R1, R1
MOVW	R0, #lo_addr(_pd4state+0)
MOVT	R0, #hi_addr(_pd4state+0)
LDR	R0, [R0, #0]
CMP	R0, #0
MOVW	R0, #0
BNE	L__Joystick39
MOVS	R0, #1
L__Joystick39:
AND	R0, R1, R0, LSL #0
CMP	R0, #0
IT	EQ
BEQ	L_Joystick13
;FinalPart1.c,127 :: 		GPIOE_ODR = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
STR	R1, [R0, #0]
;FinalPart1.c,128 :: 		pd4state = 1;
MOVS	R1, #1
MOVW	R0, #lo_addr(_pd4state+0)
MOVT	R0, #hi_addr(_pd4state+0)
STR	R1, [R0, #0]
;FinalPart1.c,129 :: 		}
L_Joystick13:
;FinalPart1.c,130 :: 		if(GPIOD_IDR.B4 == 0 & pd4state == 1){
MOVW	R0, #lo_addr(GPIOD_IDR+0)
MOVT	R0, #hi_addr(GPIOD_IDR+0)
_LX	[R0, ByteOffset(GPIOD_IDR+0)]
CMP	R0, #0
MOVW	R1, #0
BNE	L__Joystick40
MOVS	R1, #1
L__Joystick40:
UXTB	R1, R1
MOVW	R0, #lo_addr(_pd4state+0)
MOVT	R0, #hi_addr(_pd4state+0)
LDR	R0, [R0, #0]
CMP	R0, #1
MOVW	R0, #0
BNE	L__Joystick41
MOVS	R0, #1
L__Joystick41:
AND	R0, R1, R0, LSL #0
CMP	R0, #0
IT	EQ
BEQ	L_Joystick14
;FinalPart1.c,131 :: 		GPIOE_ODR.B11 = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
_SX	[R0, ByteOffset(GPIOE_ODR+0)]
;FinalPart1.c,132 :: 		GPIOE_ODR.B15 = 1;
MOVW	R0, #lo_addr(GPIOE_ODR+0)
MOVT	R0, #hi_addr(GPIOE_ODR+0)
_SX	[R0, ByteOffset(GPIOE_ODR+0)]
;FinalPart1.c,133 :: 		pd4state = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_pd4state+0)
MOVT	R0, #hi_addr(_pd4state+0)
STR	R1, [R0, #0]
;FinalPart1.c,134 :: 		}
L_Joystick14:
;FinalPart1.c,136 :: 		}
L_end_Joystick:
BX	LR
; end of _Joystick
_GPIODConfigInput:
;FinalPart1.c,139 :: 		void GPIODConfigInput(){
;FinalPart1.c,141 :: 		GPIOD_CRL = 0x44444444; //SETS GPIOD LOW as input
MOV	R1, #1145324612
MOVW	R0, #lo_addr(GPIOD_CRL+0)
MOVT	R0, #hi_addr(GPIOD_CRL+0)
STR	R1, [R0, #0]
;FinalPart1.c,142 :: 		GPIOD_CRH = 0x44444444; //SETS GPIOD HIGH as input
MOV	R1, #1145324612
MOVW	R0, #lo_addr(GPIOD_CRH+0)
MOVT	R0, #hi_addr(GPIOD_CRH+0)
STR	R1, [R0, #0]
;FinalPart1.c,143 :: 		GPIOD_ODR = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(GPIOD_ODR+0)
MOVT	R0, #hi_addr(GPIOD_ODR+0)
STR	R1, [R0, #0]
;FinalPart1.c,144 :: 		}
L_end_GPIODConfigInput:
BX	LR
; end of _GPIODConfigInput
_GPIODConfigOutput:
;FinalPart1.c,149 :: 		void GPIODConfigOutput(){
;FinalPart1.c,151 :: 		GPIOD_CRL = 0x33333333; //SETS GPIOD LOW as output
MOV	R1, #858993459
MOVW	R0, #lo_addr(GPIOD_CRL+0)
MOVT	R0, #hi_addr(GPIOD_CRL+0)
STR	R1, [R0, #0]
;FinalPart1.c,152 :: 		GPIOD_CRH = 0x33333333; //SETS GPIOD HIGH as output
MOV	R1, #858993459
MOVW	R0, #lo_addr(GPIOD_CRH+0)
MOVT	R0, #hi_addr(GPIOD_CRH+0)
STR	R1, [R0, #0]
;FinalPart1.c,153 :: 		GPIOD_ODR = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(GPIOD_ODR+0)
MOVT	R0, #hi_addr(GPIOD_ODR+0)
STR	R1, [R0, #0]
;FinalPart1.c,154 :: 		}
L_end_GPIODConfigOutput:
BX	LR
; end of _GPIODConfigOutput
_adcCONFIG:
;FinalPart1.c,157 :: 		void adcCONFIG(){
;FinalPart1.c,158 :: 		RCC_APB2ENR |= 1 << 9 ; // Enable ADC1 Clock
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #512
MOVW	R0, #lo_addr(RCC_APB2ENR+0)
MOVT	R0, #hi_addr(RCC_APB2ENR+0)
STR	R1, [R0, #0]
;FinalPart1.c,159 :: 		GPIOC_CRL &= ~(0xF << 0); // Configure PC0 as an Analog Input
MOVW	R0, #lo_addr(GPIOC_CRL+0)
MOVT	R0, #hi_addr(GPIOC_CRL+0)
LDR	R1, [R0, #0]
MVN	R0, #15
ANDS	R1, R0
MOVW	R0, #lo_addr(GPIOC_CRL+0)
MOVT	R0, #hi_addr(GPIOC_CRL+0)
STR	R1, [R0, #0]
;FinalPart1.c,160 :: 		ADC1_SQR1 = (0b0000 << 20); // 1 conversion
MOVW	R1, #0
MOVW	R0, #lo_addr(ADC1_SQR1+0)
MOVT	R0, #hi_addr(ADC1_SQR1+0)
STR	R1, [R0, #0]
;FinalPart1.c,161 :: 		ADC1_SQR3 = 10; // Select Channel 10 as only one in
MOVS	R1, #10
MOVW	R0, #lo_addr(ADC1_SQR3+0)
MOVT	R0, #hi_addr(ADC1_SQR3+0)
STR	R1, [R0, #0]
;FinalPart1.c,162 :: 		ADC1_SMPR1 = 0b100; // Set sample time on channel 10
MOVS	R1, #4
MOVW	R0, #lo_addr(ADC1_SMPR1+0)
MOVT	R0, #hi_addr(ADC1_SMPR1+0)
STR	R1, [R0, #0]
;FinalPart1.c,163 :: 		ADC1_CR2 |= (0b111 << 17); // Set software start as external event for
MOVW	R0, #lo_addr(ADC1_CR2+0)
MOVT	R0, #hi_addr(ADC1_CR2+0)
LDR	R1, [R0, #0]
MOVW	R0, #lo_addr(ADC1_CR2+0)
MOVT	R0, #hi_addr(ADC1_CR2+0)
STR	R1, [R0, #0]
;FinalPart1.c,164 :: 		ADC1_CR2.ADON = 1; // Enable ADC1
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(ADC1_CR2+0)
MOVT	R0, #hi_addr(ADC1_CR2+0)
_SX	[R0, ByteOffset(ADC1_CR2+0)]
;FinalPart1.c,165 :: 		delay_ms(10);
MOVW	R7, #33331
MOVT	R7, #0
NOP
NOP
L_adcCONFIG15:
SUBS	R7, R7, #1
BNE	L_adcCONFIG15
NOP
NOP
NOP
NOP
;FinalPart1.c,166 :: 		}
L_end_adcCONFIG:
BX	LR
; end of _adcCONFIG
_getAdcReading:
;FinalPart1.c,169 :: 		unsigned int getAdcReading(){
;FinalPart1.c,171 :: 		ADC1_CR2 |= (1 << 22) | (1 << 20);
MOVW	R0, #lo_addr(ADC1_CR2+0)
MOVT	R0, #hi_addr(ADC1_CR2+0)
LDR	R1, [R0, #0]
MOVW	R0, #lo_addr(ADC1_CR2+0)
MOVT	R0, #hi_addr(ADC1_CR2+0)
STR	R1, [R0, #0]
;FinalPart1.c,172 :: 		while(!(ADC1_SR & 0b10));
L_getAdcReading17:
MOVW	R0, #lo_addr(ADC1_SR+0)
MOVT	R0, #hi_addr(ADC1_SR+0)
LDR	R0, [R0, #0]
AND	R0, R0, #2
CMP	R0, #0
IT	NE
BNE	L_getAdcReading18
IT	AL
BAL	L_getAdcReading17
L_getAdcReading18:
;FinalPart1.c,173 :: 		return (((33*ADC1_DR)/1280)-5);   //Made an y=mx+b equation to convert from 256 to 4096 scale to a 1 to 100 scale for controlling game speed
MOVW	R0, #lo_addr(ADC1_DR+0)
MOVT	R0, #hi_addr(ADC1_DR+0)
LDR	R1, [R0, #0]
MOVS	R0, #33
MULS	R1, R0, R1
MOVW	R0, #1280
UDIV	R0, R1, R0
SUBS	R0, R0, #5
UXTH	R0, R0
;FinalPart1.c,174 :: 		}
L_end_getAdcReading:
BX	LR
; end of _getAdcReading
