#line 1 "C:/Users/olszg/Documents/F23_Embedded_Systems_Class/FinalPart1/FinalPart1.c"
#line 13 "C:/Users/olszg/Documents/F23_Embedded_Systems_Class/FinalPart1/FinalPart1.c"
unsigned long int pa6state = 0;
unsigned long int pd2state = 0;
unsigned long int pd4state = 0;
unsigned long int pb5state = 0;
unsigned long int pc13state = 0;

void GPIODConfigOutput();
void adcCONFIG();
void Joystick();
void GPIODConfigInput();
unsigned int getAdcReading();



void main() {

 RCC_APB2ENR |= 1 << 2;
 RCC_APB2ENR |= 1 << 3;
 RCC_APB2ENR |= 1 << 4;
 RCC_APB2ENR |= 1 << 5;
 RCC_APB2ENR |= 1 << 6;

 GPIOE_CRH = 0x33333333;

 GPIOA_CRL = 0x44444444;
 GPIOA_CRH = 0x44444444;

 GPIOB_CRL = 0x44444444;
 GPIOB_CRH = 0x44444444;

 GPIOC_CRL = 0x44444444;
 GPIOC_CRH = 0x44444444;

 GPIOD_CRL = 0x44444444;
 GPIOD_CRH = 0x44444444;

 adcCONFIG();


 for(;;){


 GPIODConfigInput();
 Joystick();




 GPIODConfigOutput();
 GPIOD_ODR = getAdcReading();
 delay_ms(100);



 }
}



void Joystick() {
 if(GPIOA_IDR.B6 == 1 & pa6state == 0){
 GPIOE_ODR = 0;
 pa6state = 1;
 }
 if(GPIOA_IDR.B6 == 0 & pa6state == 1){
 GPIOE_ODR.B9 = 1;
 GPIOE_ODR.B10 = 1;
 pa6state = 0;
 }


 if(GPIOB_IDR.B5 == 1 & pb5state == 0){
 GPIOE_ODR = 0;
 pb5state = 1;
 }
 if(GPIOB_IDR.B5 == 0 & pb5state == 1){
 GPIOE_ODR.B8 = 1;
 GPIOE_ODR.B12 = 1;
 pb5state = 0;
 }





 if(GPIOC_IDR.B13 == 1 & pc13state == 0){
 GPIOE_ODR = 0;
 pc13state = 1;
 }
 if(GPIOC_IDR.B13 == 0 & pc13state == 1){
 GPIOE_ODR = ~GPIOE_ODR;
 pc13state = 0;
 }





 if(GPIOD_IDR.B2 == 1 & pd2state == 0){
 GPIOE_ODR = 0;
 pd2state = 1;
 }
 if(GPIOD_IDR.B2 == 0 & pd2state == 1){
 GPIOE_ODR.B13 = 1;
 GPIOE_ODR.B14 = 1;
 pd2state = 0;
 }






 if(GPIOD_IDR.B4 == 1 & pd4state == 0){
 GPIOE_ODR = 0;
 pd4state = 1;
 }
 if(GPIOD_IDR.B4 == 0 & pd4state == 1){
 GPIOE_ODR.B11 = 1;
 GPIOE_ODR.B15 = 1;
 pd4state = 0;
 }

}


void GPIODConfigInput(){

 GPIOD_CRL = 0x44444444;
 GPIOD_CRH = 0x44444444;
 GPIOD_ODR = 0;
}




void GPIODConfigOutput(){

 GPIOD_CRL = 0x33333333;
 GPIOD_CRH = 0x33333333;
 GPIOD_ODR = 0;
}


void adcCONFIG(){
 RCC_APB2ENR |= 1 << 9 ;
 GPIOC_CRL &= ~(0xF << 0);
 ADC1_SQR1 = (0b0000 << 20);
 ADC1_SQR3 = 10;
 ADC1_SMPR1 = 0b100;
 ADC1_CR2 |= (0b111 << 17);
 ADC1_CR2.ADON = 1;
 delay_ms(10);
}


unsigned int getAdcReading(){

 ADC1_CR2 |= (1 << 22) | (1 << 20);
 while(!(ADC1_SR & 0b10));
 return (((33*ADC1_DR)/1280)-5);
}
