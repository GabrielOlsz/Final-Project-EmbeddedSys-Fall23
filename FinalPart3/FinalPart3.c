//**************************************************************************************************
// Name: Alexander Castromonte, Gabriel Olszewski, Anthony Mauro
// Date: 11/20/2023
// Course: ELEC3371-00
// Description: This program initializes USART1. It waits to receive a character from USART
//                                terminal tool in the development system and then it sends the same character
//                                back. It uses baud rate of 56000. On SW12 set PA9 and PA10 to TX and RX.
//**************************************************************************************************

//**************************************************************************************************
//INTERRUPT SERVICE ROUTINE
void TIMER3_ISR () iv IVT_INT_TIM3 {
  TIM3_SR.UIF = 0;  			// Reset UIF flag so next interrupt can be recognized when UIF is set
  GPIOD_ODR = ~ GPIOD_ODR;	// Toggle PORTD LEDs
  GPIOE_ODR = ~ GPIOE_ODR;	// Toggle PORTE LEDs
}

void TIMER1_ISR () {

}


//**************************************************************************************************
//VARIABLE DECLARATIONS
unsigned int rcvrd;                        // Container for received data
unsigned int right[11] = {'R','T',' ','P','R','E','S','S','E','D', ' '};
unsigned int left[11] = {'L','T',' ','P','R','E','S','S','E','D', ' '};
unsigned int up[11] = {'U','P',' ','P','R','E','S','S','E','D', ' '};
unsigned int down[11] = {'D','N',' ','P','R','E','S','S','E','D', ' '};
unsigned int click[11] = {'C','K',' ','P','R','E','S','S','E','D', ' '};
unsigned int pause[6] = {'P','A','U','S','E',' '};
unsigned int unpause[9] = {'U','N','P','A','U','S','E','D',' '};
unsigned int pauseToggle = 0;
unsigned int i = 0;
void InitializeUSART1();        // Sub function which initializes the registers to enable USART1
void Timer1Configuration();
void Timer3IntConfiguration();

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


//**************************************************************************************************
//MAIN FUNCTION
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


           adcCONFIG();



        InitializeUSART1();                // Call sub function to initialize USART1


//**************************************************************************************************
//VARIABLE DECLARATIONS
        for(;;) {

                 GPIODConfigInput();            //Function to call GPIOD config input
                 Joystick();                    //Function for joystick
               	 Timer1Configuration();
               	 Timer3IntConfiguration();

                GPIODConfigOutput();           //Function to call GPIOD config output
                GPIOD_ODR = getAdcReading();   //Display ADC signal to GPIOD LEDS
                delay_ms(100);


                if(((USART1_SR & (1<<5))== 0x20)){
                  if (pauseToggle == 0 && (USART1_DR == 'p' || USART1_DR == 'P')){
                    i = 0;
                    pauseToggle = 1;
                  }

                  else if(pauseToggle == 1 && (USART1_DR == 'p' || USART1_DR == 'P')){
                    i = 2;
                    pauseToggle = 0;

                 }
                for (i = i; i<9; i++){
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = unpause[i];              //Prints out unpause
                }

                }

        }

}
//**************************************************************************************************
//SUB FUNCTIONS
void InitializeUSART1(){ // Sub function which initializes the registers to enable USART1
        RCC_APB2ENR |= 1;                 // Enable clock for Alt. Function. USART1 uses AF for PA9/PA10
        AFIO_MAPR=0X0F000000;             // Do not mask PA9 and PA10 (becaue we are using for USART)
        RCC_APB2ENR |= 1<<2;              // Enable clock for GPIOA
        GPIOA_CRH &= ~(0xFF << 4);        // Clear PA9, PA10
        GPIOA_CRH |= (0x0B << 4);         // USART1 Tx (PA9) output push-pull
        GPIOA_CRH |= (0x04 << 8);         // USART1 Rx (PA10) input floating
        RCC_APB2ENR |= 1<<14;             // enable clock for USART1
        USART1_BRR=0X00000506;            // Set baud rate to 56000
        // Per data sheet (pg. 1010) USART1_CR1 consists of the following:
        //13 12   11  10  9    8     7    6      5      4  3  2   1   0
        //UE  M WAKE PCE PS PEIE TXEIE TCIE RXNEIE IDLEIE TE RE RWU SBK
        //rw rw  rw   rw rw   rw    rw   rw     rw     rw rw rw  rw  rw
        USART1_CR1 &= ~(1<<12);          // Force 8 data bits. M bit is set to 0.
        USART1_CR2 &= ~(3<<12);          // Force 1 stop bit
        USART1_CR3 &= ~(3<<8);           // Force no flow control and no DMA for USART1
        USART1_CR1 &= ~(3<<9);           // Force no parity and no parity control
        USART1_CR1 |= 3<<2;              // RX, TX enable
        //The following two instructions can also be used to enable RX and TX manually
        //USART1_CR1.TE=1; //TX enable
        //USART1_CR1.RE=1; //RX enable
        USART1_CR1 |= 1<<13;            // USART1 enable. This is done after configuration is complete
        Delay_ms(100);                  // Wait for USART to complete configuration and enable. This is
                                                                        // not always necessary, but good practice.
}



//**************************************************************************************************
void Joystick() {
          if(GPIOA_IDR.B6 == 1 & pa6state == 0){        //Function for RIGHT button
                          GPIOE_ODR = 0;
                          pa6state = 1;
          }
          if(GPIOA_IDR.B6 == 0 & pa6state == 1){
                          GPIOE_ODR.B9 = 1;
                          GPIOE_ODR.B10 = 1;

                 for (i = 0; i<11; i++){
                 while(USART1_SR.TC == 0) {}
                 USART1_DR = right[i];
                 }
                          pa6state = 0;
          }


          if(GPIOB_IDR.B5 == 1 & pb5state == 0){         //Function for DOWN button
                          GPIOE_ODR = 0;
                          pb5state = 1;
          }
          if(GPIOB_IDR.B5 == 0 & pb5state == 1){
                          GPIOE_ODR.B8 = 1;
                          GPIOE_ODR.B12 = 1;

                 for (i = 0; i<11; i++){
                 while(USART1_SR.TC == 0) {}
                 USART1_DR = down[i];
                 }
                          pb5state = 0;
          }


          if(GPIOC_IDR.B13 == 1 & pc13state == 0){       // Function for Click button
                           GPIOE_ODR = 0;
                           pc13state = 1;
          }
          if(GPIOC_IDR.B13 == 0 & pc13state == 1){
                           GPIOE_ODR = ~GPIOE_ODR;

                   for (i = 0; i<11; i++){
                   while(USART1_SR.TC == 0) {}
                   USART1_DR = click[i];
                   }
                           pc13state = 0;
          }





          if(GPIOD_IDR.B2 == 1 & pd2state == 0){         //Function for Left button
                          GPIOE_ODR = 0;
                          pd2state = 1;
          }
          if(GPIOD_IDR.B2 == 0 & pd2state == 1){
                          GPIOE_ODR.B13 = 1;
                          GPIOE_ODR.B14 = 1;
                   for (i = 0; i<11; i++){
                   while(USART1_SR.TC == 0) {}
                   USART1_DR = left[i];
                   }
                          pd2state = 0;
          }






          if(GPIOD_IDR.B4 == 1 & pd4state == 0){         //Function for UP button
                          GPIOE_ODR = 0;
                          pd4state = 1;
          }
          if(GPIOD_IDR.B4 == 0 & pd4state == 1){
                          GPIOE_ODR.B11 = 1;
                          GPIOE_ODR.B15 = 1;
                     for (i = 0; i<11; i++){
                     while(USART1_SR.TC == 0) {}
                     USART1_DR = up[i];
                     }
                          pd4state = 0;
          }

}

//**************************************************************************************************
void GPIODConfigInput(){

     GPIOD_CRL = 0x44444444; //SETS GPIOD LOW as input
     GPIOD_CRH = 0x44444444; //SETS GPIOD HIGH as input
     GPIOD_ODR = 0;
}

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


void Timer1Configuration(){
	RCC_APB2ENR |= (1 << 11);   // Enable TIMER1 clock. RCC: Clock Configuration Register
								// Different clocks may use different registers.
								// Ex. TIMER4 uses RCC_APB1ENR
	TIM1_CR1 = 0x0000;  // Disable timer until configuration is complete
						// If reset value of RCC_CFGR is used, then the 8MHz clock will
						// be the clock source for timer
	TIM1_PSC = 7999;    // Clock to TIMx_CNT = 72000000 (clock applied to prescaler register) /
					    //                     7999 (Value in TIMx_PSC) + 1) = 9000
	TIM1_ARR = 9000;	// Reload timer count register with this value when count register resets
						// to 0 after counting from zero to this value
	TIM1_CR1 = 0x0001; 	// Enable TIMER1

// Notice: Bit 4 of TIM1_CR1 specifies whether the counter count up (BIT4=0) or counts down (BIT4=1)
// In this configuration this counting up is used.
}

void Timer3IntConfiguration(){
	RCC_APB1ENR |= (1 << 1);// Enable TIMER3 clock. RCC: Clock Configuration Register
	TIM1_CR1 = 0x0000;  	// Disable timer until configuration is complete
							// If reset value of RCC_CFGR is used, then the 8MHz clock will
							// be the clock source for timer
	TIM1_PSC = 7999;    	// Clock to TIMx_CNT = 72000000 (clock applied to prescaler register) /
							//                     7999 (Value in TIMx_PSC) + 1) = 9000
	TIM1_ARR = 9000;		// Reload timer count register with this value when count register resets
							// to 0 after counting from zero to this value
	NVIC_ISER0 |= 1<<29;	// Enable global interrupt for TIMER3 in NVIC
							// Interrupt set enable register 0. Position of this interrupt in vector
							// table is 29, so set the corresponding bit in interrupt service enable
							// register 0. This is a 32 bit register. ISER1 is used for interrupt
							// numbers greater than 31.
	TIM3_DIER.UIE = 1;  	// Update interrupt enable
	TIM3_CR1 = 0x0001; 		// Enable TIMER3
}

 //****************************************************************************************