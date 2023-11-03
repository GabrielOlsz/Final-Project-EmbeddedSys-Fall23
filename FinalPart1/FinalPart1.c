//**************************************************************************************************
// Name: Gabriel Olszewski, Anthony Mauro, Alexander Castromonte
// Date: 11/6/2023
// Course: ELEC3371-01
// Description: This program maps the Joysticks buttons to enable movement when playing a game.
//              The Joystick function uses the falling edge to turn on LED's in PORTE/H using the Joystick's 5 Buttons
//              The Potentiometer is used to get ADC readings from 1 to 100 and display them on PORTD/L
//
//**************************************************************************************************

//PD2 = LEFT , PD4 = UP, PB5 = DOWN, PA6 = RIGHT, PC13 = CENTER

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

           RCC_APB2ENR |= 1 << 2;  // ENABLE GPIOA clock - necessary to use GPIOA
           RCC_APB2ENR |= 1 << 3;  // ENABLE GPIOB clock - necessary to use GPIOB
           RCC_APB2ENR |= 1 << 4;  // ENABLE GPIOC clock - necessary to use GPIOC
           RCC_APB2ENR |= 1 << 5;  // ENABLE GPIOD clock - necessary to use GPIOD
           RCC_APB2ENR |= 1 << 6;  // ENABLE GPIOE clock - necessary to use GPIOE

           GPIOE_CRH = 0x33333333; //SETS GPIOE HIGH as output

           GPIOA_CRL = 0x44444444; //SETS GPIOA LOW as input
           GPIOA_CRH = 0x44444444; //SETS GPIOA HIGH as input

           GPIOB_CRL = 0x44444444; //SETS GPIOB LOW as input
           GPIOB_CRH = 0x44444444; //SETS GPIOB HIGH as input

           GPIOC_CRL = 0x44444444; //SETS GPIOC LOW as input
           GPIOC_CRH = 0x44444444; //SETS GPIOC HIGH as input

           GPIOD_CRL = 0x44444444; //SETS GPIOD LOW as input
           GPIOD_CRH = 0x44444444; //SETS GPIOD HIGH as input
            
           adcCONFIG();


        for(;;){
 //****************************************************************************************
           //Objective 2
           GPIODConfigInput();
           Joystick();


 //****************************************************************************************
          //Objective 3
          GPIODConfigOutput();
          GPIOD_ODR = getAdcReading();
          delay_ms(100);
          
 //****************************************************************************************

        }
}

 //****************************************************************************************
//Objective 2
void Joystick() {
          if(GPIOA_IDR.B6 == 1 & pa6state == 0){        //Function for RIGHT button
                          GPIOE_ODR = 0;
                          pa6state = 1;
          }
          if(GPIOA_IDR.B6 == 0 & pa6state == 1){
                          GPIOE_ODR.B9 = 1;
                          GPIOE_ODR.B10 = 1;
                          pa6state = 0;
          }


          if(GPIOB_IDR.B5 == 1 & pb5state == 0){         //Function for DOWN button
                          GPIOE_ODR = 0;
                          pb5state = 1;
          }
          if(GPIOB_IDR.B5 == 0 & pb5state == 1){
                          GPIOE_ODR.B8 = 1;
                          GPIOE_ODR.B12 = 1;
                          pb5state = 0;
          }





          if(GPIOC_IDR.B13 == 1 & pc13state == 0){       // Function for Click button
                           GPIOE_ODR = 0;
                           pc13state = 1;
          }
          if(GPIOC_IDR.B13 == 0 & pc13state == 1){
                           GPIOE_ODR = ~GPIOE_ODR;
                           pc13state = 0;
          }





          if(GPIOD_IDR.B2 == 1 & pd2state == 0){         //Function for Left button
                          GPIOE_ODR = 0;
                          pd2state = 1;
          }
          if(GPIOD_IDR.B2 == 0 & pd2state == 1){
                          GPIOE_ODR.B13 = 1;
                          GPIOE_ODR.B14 = 1;
                          pd2state = 0;
          }






          if(GPIOD_IDR.B4 == 1 & pd4state == 0){         //Function for UP button
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

     GPIOD_CRL = 0x44444444; //SETS GPIOD LOW as input
     GPIOD_CRH = 0x44444444; //SETS GPIOD HIGH as input
     GPIOD_ODR = 0;
}
//****************************************************************************************

//****************************************************************************************
//Objective 3
void GPIODConfigOutput(){

     GPIOD_CRL = 0x33333333; //SETS GPIOD LOW as output
     GPIOD_CRH = 0x33333333; //SETS GPIOD HIGH as output
     GPIOD_ODR = 0;
}


void adcCONFIG(){
         RCC_APB2ENR |= 1 << 9 ; // Enable ADC1 Clock
         GPIOC_CRL &= ~(0xF << 0); // Configure PC0 as an Analog Input
         ADC1_SQR1 = (0b0000 << 20); // 1 conversion
         ADC1_SQR3 = 10; // Select Channel 10 as only one in
         ADC1_SMPR1 = 0b100; // Set sample time on channel 10
         ADC1_CR2 |= (0b111 << 17); // Set software start as external event for
         ADC1_CR2.ADON = 1; // Enable ADC1
         delay_ms(10);
}


unsigned int getAdcReading(){

    ADC1_CR2 |= (1 << 22) | (1 << 20);
    while(!(ADC1_SR & 0b10));
    return (((33*ADC1_DR)/1280)-5);   //Made an y=mx+b equation to convert from 256 to 4096 scale to a 1 to 100 scale for controlling game speed
}

 //****************************************************************************************