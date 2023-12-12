//**************************************************************************************************
// Name: Alexander Castromonte, Gabriel Olszewski, Anthony Mauro
// Date: 12/18/2023
// Course: ELEC3371-01
// Description:
//
//
//
//**************************************************************************************************

//**************************************************************************************************
//VARIABLE/FUNCTION DECLARATIONS
#include "PacmanFinalPart4_objects.h"
#include "PacmanFinalPart4_resources.h" //Has all of the interrupt service routines for the Joystick buttons to work
#include "PacmanScreens.h"

unsigned long int gameTick = 0;


//INTERRUPT SERVICE ROUTINES
void TIMER1_ISR () iv IVT_INT_TIM1_UP {
     TIM1_SR.UIF = 0;               //Reset UIF flag
     counter++;

     //split counter into two numbers, ex: 25 will split to 2 and 5 to display on either left or right display
     leftSide = counter / 10;
     rightSide = counter % 10;

     if(counter >= 99){    //When counter reaches 99 seconds, reset to 0
         counter = 0;
     }
}

void TIMER3_ISR () iv IVT_INT_TIM3 {
  TIM3_SR.UIF = 0;               // Reset UIF flag so next interrupt can be recognized when UIF is set
  GPIOE_ODR.B14 = ~GPIOE_ODR.B14;  //BONUS OBJECTIVE BUZZER! ALSO TOGGLES LIGHT PE14 based on TIMER SPEED with potentiometer
  gameTick = 1;
}

void JoyStickLeft() iv IVT_INT_EXTI2 {
  EXTI_PR.B2 = 1;
  JoyStickDir = 2;
}

void JoyStickUp() iv IVT_INT_EXTI4 {
    EXTI_PR.B4 = 1;
    JoyStickDir = 4;

}

void JoyStickRightAndDown() iv IVT_INT_EXTI9_5{

if((EXTI_PR & 0x0020) == 0x0020){
    EXTI_PR.B5 = 1;

  JoyStickDir = 5;
 }
if((EXTI_PR & 0x0040) == 0x0040){
    EXTI_PR.B6 = 1;
    JoyStickDir = 6;
    }
}

//void JoyStickClick() iv IVT_INT_EXTI15_10{
//EXTI_PR.B13 = 1;
//JoyStickDir = 13;
//
//}



void PlayScreen(){

   if(JoystickDir == 0){ //default, only happens once
     player.x0 = 161;
     player.x1 = player.x0 + ENTITY_SIZE;
     player.y0 = 161;
     player.y1 = player.y0 + ENTITY_SIZE;
     player.color = CL_YELLOW;
     TFT_SET_BRUSH(1, player.color, 0,0,0,0);
     TFT_RECTANGLE(player.x0, player.y0, player.x1, player.y1);
   }
   else{
     TFT_SET_BRUSH(1, CL_BLACK, 0,0,0,0);
     TFT_RECTANGLE(player.x0, player.y0, player.x1, player.y1);
     switch(JoyStickDir){
     case 2: //LEFT
     //Check if player has collided with anything
     if(player.x0 > ENTITY_SIZE ){ //1 is the size of the border around the Screen that it is detected collision for
     //Move the player
     //loop through all wall coords
     //if not wall[x]{
     
     
     player.x0 -= ENTITY_SIZE;
     player.x1 -= ENTITY_SIZE;
     }
     }
     else{} //Collides with left edge of the screen
     
     break;

     case 4: //UP
     //Check if player has collided with anything
     if(player.y0 > 14){
     //Move the player
     player.y0 -= ENTITY_SIZE;
     player.y1 -= ENTITY_SIZE;
     }
     else{}
     break;

     case 5: //DOWN
     //Check if player has collided with anything
     if(player.y1 < 232){
     //Move the player
     player.y0 += ENTITY_SIZE;
     player.y1 += ENTITY_SIZE;
     }
     else{}
     break;

     case 6: //RIGHT
     //Check if player has collided with anything
     if(player.x1 < 318){
     //Move the player
     player.x0 += ENTITY_SIZE;
     player.x1 += ENTITY_SIZE;
     }
     else{}
     break;
     
     default:
     break;
     }

     TFT_SET_BRUSH(1, player.color, 0,0,0,0);
     TFT_RECTANGLE(player.x0, player.y0, player.x1, player.y1);
    
     //if player has collided with any of the food
     //if yes, check if food is visibile, if yes, increase score, set visibility to 0
     //loop through all the possible food positions, compare to player position
     
     
     //if player has collided with a ghost
     //if yes, end the game
     //loop through all the possible ghost positions, compare to player position
    
     while(gameTick == 0){};
     gameTick = 0;
     }
 }

//MAIN FUNCTION
void main() {
         initializeGPIO();            //Enable port clocks
         adcCONFIG();                 //Configure ADC read
         InitializeUSART1();          //Configure USART1
         Timer1Configuration();
         JoystickConfiguration();
         Start_TP();
         ClearScreen();
         RCC_APB2ENR.IOPEEN = 1;

        for(;;) {

                 PlayScreen();
                /*
                 switch(ScreenStateMachine){
                  case 1:
                  PlayScreen();
                  GameOverScreen();
                  break;
                  case 2:
                  HighScoreScreen();
                  case 3:
                  HowtoScreen();
                  break;
                  
                  default:
                  TitleScreen();
                  break;
                 }  */



                 Timer3IntConfiguration();
                 //MET1155********************************************************
                 GPIOD_ODR = left7segdisplay[leftSide];  //Use values from TIMER1 Function above to display onto 7 segment with an array
                 delay_ms(1);                         //Small delay so eyes cannot tell the display is refreshing, if there is no delay then the display gets dim
                 GPIOD_ODR = right7segdisplay[rightSide];
                 delay_ms(1);
                 //****************************************************************


                switch(JoyStickDir){
                     case 2:
                          for (i = 0; i<11; i++){
                         while(USART1_SR.TC == 0) {}
                         USART1_DR = left[i];

                         }
                           //JoyStickDir = 0;
                     break;

                     case 4:
                     for (i = 0; i<11; i++){
                     while(USART1_SR.TC == 0) {}
                     USART1_DR = up[i];
                     }
                         // JoyStickDir = 0;
                     break;

                     case 5:
                          for (i = 0; i<11; i++){
                         while(USART1_SR.TC == 0) {}
                         USART1_DR = down[i];
                         }
                          //JoyStickDir = 0;
                     break;

                     case 6:
                          for (i = 0; i<11; i++){
                           while(USART1_SR.TC == 0) {}
                           USART1_DR = right[i];
                           }
                         //  JoyStickDir = 0;
                     break;

//                     case 13:
//                          for (i = 0; i<11; i++){
//                       while(USART1_SR.TC == 0) {}
//                       USART1_DR = click[i];
//                       }
//                       JoyStickDir = 0;
//                     break;

                     default:
                     //JoyStickDir = 0;
                     break;

                }
                //****************************************************************

                if(((USART1_SR & (1<<5))== 0x20)){           //Wait for USART to receive
                  if (pauseToggle == 0 && (USART1_DR == 'p' || USART1_DR == 'P')){      //If user sends p or P to USART then receive "UNPAUSED"
                    i = 0;                                                              //USART Terminal must be set ASCII data format
                    pauseToggle = 1;
                  }

                  else if(pauseToggle == 1 && (USART1_DR == 'p' || USART1_DR == 'P')){  //If user sends p or P to USART then receive "PAUSED"
                    i = 2;
                    pauseToggle = 0;

                 } else if(USART1_DR == 'q' || USART1_DR == 'Q'){      //Objective 2
                         USART1_DR = counter;
                 }
                  for (i = i; i<9; i++){
                      while(USART1_SR.TC == 0) {}
                      USART1_DR = unpause[i];              //Prints out unpause/pause in USART
                  }

                }




        }

}





 //**************************************************************************************************
 //**************************************************************************************************
 //**************************************************************************************************
 //**************************************************************************************************
 //**************************************************************************************************
 //**************************************************************************************************
 //**************************************************************************************************
 //**************************************************************************************************
 //**************************************************************************************************
 //**************************************************************************************************
 //**************************************************************************************************
 //**************************************************************************************************
 //**************************************************************************************************
 //**************************************************************************************************
 //**************************************************************************************************


 int CheckWallCollision(){
   for(int i = 0, i >= numWalls, i++){
      if(walls[i].y1 >= player.y0 || walls[i].x0 >= player.x1 || walls[i].y0 <= player.y1 || walls[i].x1 <= player.x0){
       return 1; //Collision has occured
      }
      return 0;

   }


}


 void JoyStickConfiguration(){
 GPIOA_CRL = 0x4000000;
 GPIOB_CRL =  0x400000;
// GPIOC_CRH =  0x40000;
 GPIOD_CRL =  0x40400;

  RCC_APB2ENR.IOPBEN = 1;
  RCC_APB2ENR.IOPAEN = 1;
  RCC_APB2ENR.IOPDEN = 1;
 // RCC_APB2ENR.IOPCEN = 1;
  RCC_APB2ENR.AFIOEN = 1; // Enable clock for alternate pin function
  AFIO_EXTICR1 = 0x0300; // PD2 as External interrupt
  AFIO_EXTICR2 = 0x0013; // PB6 as External interrupt
  AFIO_EXTICR4 = 0x2000; // PC13 as External interrupt
  //EXTI_RTSR = 0x0074;    // rising edge
  EXTI_FTSR =0x0074; // Set interrupt on falling edge for PA0 and PB6
  EXTI_IMR |= 0x0074; // Interrupt on PA0 and PB6 are non-maskable
//  NVIC_ISER0 |= 1<< 8; //Enable NVIC interrupt for EXTI2  PD2
//  NVIC_ISER0 |= 1<< 10; //Enable NVIC interrupt for EXTI4 PD4
//  NVIC_ISER0 |= 1<<23; // Enable NVIC interrupt for EXTI9_% (PB6 & PA5)
//  NVIC_ISER0 |= 1<< 40; //Enable NVIC interrupt for EXTI5_10 (PC13)
  NVIC_ISER0.B8 = 1;
  NVIC_ISER0.B10 = 1;
  NVIC_ISER0.B23 = 1;

}

//**************************************************************************************************
//SUB FUNCTIONS

void initializeGPIO(){

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
           GPIOD_CRH = 0x33333333; //SETS GPIOD HIGH as input
           GPIOD_ODR = 0;

           adcCONFIG();
           InitializeUSART1();                // Call sub function to initialize USART1
 }

//**************************************************************************************************


void InitializeUSART1(){ // Sub function which initializes the registers to enable USART1
        RCC_APB2ENR |= 1;                 // Enable clock for Alt. Function. USART1 uses AF for PA9/PA10
        AFIO_MAPR=0X0F000000;             // Do not mask PA9 and PA10 (becaue we are using for USART)
        RCC_APB2ENR |= 1<<2;              // Enable clock for GPIOA
        GPIOA_CRH &= ~(0xFF << 4);        // Clear PA9, PA10
        GPIOA_CRH |= (0x0B << 4);         // USART1 Tx (PA9) output push-pull
        GPIOA_CRH |= (0x04 << 8);         // USART1 Rx (PA10) input floating
        RCC_APB2ENR |= 1<<14;             // enable clock for USART1
        USART1_BRR=0X00000506;            // Set baud rate to 56000
        USART1_CR1 &= ~(1<<12);          // Force 8 data bits. M bit is set to 0.
        USART1_CR2 &= ~(3<<12);          // Force 1 stop bit
        USART1_CR3 &= ~(3<<8);           // Force no flow control and no DMA for USART1
        USART1_CR1 &= ~(3<<9);           // Force no parity and no parity control
        USART1_CR1 |= 3<<2;              // RX, TX enable
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
        TIM1_PSC = 14399;    // Clock to TIMx_CNT = 72000000/(14399+1) = 5000
        TIM1_ARR = 5000;        // Reload timer count register with this value when count register resets
                                                // to 0 after counting from zero to this value
        NVIC_ISER0.B25 = 1;     // Enable global interrupt for TIMER1 in NVIC
        TIM1_DIER.UIE = 1;     // Update interrupt enable
        TIM1_CR1 = 0x0001;         // Enable TIMER1

}

void Timer3IntConfiguration(){
        RCC_APB1ENR |= (1 << 1);// Enable TIMER3 clock. RCC: Clock Configuration Register
        TIM3_CR1 = 0x0000;          // Disable timer until configuration is complete
                                                        // If reset value of RCC_CFGR is used, then the 8MHz clock will
                                                        // be the clock source for timer
        TIM3_PSC = getAdcReading() * 5;            // Clock to TIMx_CNT = 72000000 (clock applied to prescaler register) /



                                                        //                     7999 (Value in TIMx_PSC) + 1) = 9000
        TIM3_ARR = (72000000)/((getAdcReading()*5)+1);                // Reload timer count register with this value when count register resets
                                                        // to 0 after counting from zero to this value
        NVIC_ISER0.B29 = 1;        // Enable global interrupt for TIMER3 in NVIC
                                                        // Interrupt set enable register 0. Position of this interrupt in vector
                                                        // table is 29, so set the corresponding bit in interrupt service enable
                                                        // register 0. This is a 32 bit register. ISER1 is used for interrupt
                                                        // numbers greater than 31.
        TIM3_DIER.UIE = 1;          // Update interrupt enable
        TIM3_CR1 = 0x0001;          // Enable TIMER3
}

