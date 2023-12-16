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




//INTERRUPT SERVICE ROUTINES
void TIMER1_ISR () iv IVT_INT_TIM1_UP {
     TIM1_SR.UIF = 0;               //Reset UIF flag
     
     /* //Uncomment this section if a game timer is wanted on the MET1155
     counter++;
     //split counter into two numbers, ex: 25 will split to 2 and 5 to display on either left or right display
     leftSide = counter / 10;
     rightSide = counter % 10;

     if(counter >= 99){    //When counter reaches 99 seconds, reset to 0
         counter = 0;
     } */
}

void TIMER3_ISR () iv IVT_INT_TIM3 {
  TIM3_SR.UIF = 0;               // Reset UIF flag so next interrupt can be recognized when UIF is set
  GPIOE_ODR.B13 = GPIOE_ODR.B13;
  //GPIOE_ODR.B14 = ~GPIOE_ODR.B14;  //BONUS OBJECTIVE BUZZER! ALSO TOGGLES LIGHT PE14 based on TIMER SPEED with potentiometer
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
     player.x0 = 151;
     player.x1 = player.x0 + SIZE;
     player.y0 = 163;
     player.y1 = player.y0 + SIZE;
     player.color = CL_YELLOW;
     TFT_SET_BRUSH(1, player.color, 0,0,0,0);
     TFT_RECTANGLE(player.x0, player.y0, player.x1, player.y1);
     TFT_Set_Pen(CL_BLACK, 1);
     q = player.x0;
     w = player.y0;
     e = player.x1;
     r = player.y1;
   }

   else{
     TFT_SET_BRUSH(1, CL_BLACK, 0,0,0,0);
     TFT_RECTANGLE(player.x0, player.y0, player.x1, player.y1);
     switch(JoyStickDir){
     case 2: //LEFT
     //Check if player has collided with anything
     //Loop through all wall coords with CheckWallCollision
       if(CheckWallCollision() == 1){}
       if(CheckWallCollision() == 0){

       w = player.y0;
       r = player.y1;

       q = player.x0 - ENTITY_SIZE;
       e = player.x1 - ENTITY_SIZE;
       if(CheckNextWallCollision() == 1){}
       if(CheckNextWallCollision() == 0){
         //Move the player
         player.x0 -= ENTITY_SIZE;
         player.x1 -= ENTITY_SIZE;
         GPIOE_ODR.B14 = ~GPIOE_ODR.B14;  //BONUS OBJECTIVE BUZZER!
         }
       }
     else{} //Collides with left edge of the screen

     break;

     case 4: //UP
     //Check if player has collided with anything
       if(CheckWallCollision() == 1){}
       if(CheckWallCollision() == 0){

       q = player.x0;
       e = player.x1;

       w = player.y0 - ENTITY_SIZE;
       r = player.y1 - ENTITY_SIZE;
       if(CheckNextWallCollision() == 1){}
       if(CheckNextWallCollision() == 0){
         //Move the player
         player.y0 -= ENTITY_SIZE;
         player.y1 -= ENTITY_SIZE;
         GPIOE_ODR.B14 = ~GPIOE_ODR.B14;  //BONUS OBJECTIVE BUZZER!
         }
       }
     else{}
     break;

     case 5: //DOWN
     //Check if player has collided with anything
       if(CheckWallCollision() == 1){}
       if(CheckWallCollision() == 0){

       q = player.x0;
       e = player.x1;

       w = player.y0 + ENTITY_SIZE;
       r = player.y1 + ENTITY_SIZE;
       if(CheckNextWallCollision() == 1){}
       if(CheckNextWallCollision() == 0){
         //Move the player
         player.y0 += ENTITY_SIZE;
         player.y1 += ENTITY_SIZE;
         GPIOE_ODR.B14 = ~GPIOE_ODR.B14;  //BONUS OBJECTIVE BUZZER!
         }
       }
     else{}
     break;

     case 6: //RIGHT
     //Check if player has collided with anything
       if(CheckWallCollision() == 1){}
       if(CheckWallCollision() == 0){

       w = player.y0;
       r = player.y1;

       q = player.x0 + ENTITY_SIZE;
       e = player.x1 + ENTITY_SIZE;
       if(CheckNextWallCollision() == 1){}
       if(CheckNextWallCollision() == 0){
         //Move the player
         player.x0 += ENTITY_SIZE;
         player.x1 += ENTITY_SIZE;
         GPIOE_ODR.B14 = ~GPIOE_ODR.B14;  //BONUS OBJECTIVE BUZZER!
         }
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
     if(CheckFoodCollision() == 0){}
     if(CheckFoodCollision() == 1){
       playerScore++;
       food[i].x0 = 0;
       food[i].y0 = 0;
       food[i].x1 = 0;
       food[i].y1 = 0;
       GPIOE_ODR.B14 = ~GPIOE_ODR.B14;  //BONUS OBJECTIVE BUZZER!
     }
     

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
         drawMap();

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
                 leftSide = playerScore / 10;
                 rightSide = playerScore % 10;
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
    for(i = 0; i < numWalls; i++){
        if((player.x0 < walls[i].x1) && (player.x1 > walls[i].x0) && (player.y0 < walls[i].y1) && (player.y1 > walls[i].y0)){
            return 1; // Collision
        }
    }
    return 0; // No collision
}

int CheckNextWallCollision(){
    for(i = 0; i < numWalls; i++){
        if((q < walls[i].x1) && (e > walls[i].x0) && (w < walls[i].y1) && (r > walls[i].y0)){
            return 1; // Collision
        }
    }
    return 0; // No collision
}

int CheckFoodCollision(){
    for(i = 0; i < numFood; i++){
        if((player.x0 < food[i].x1) && (player.x1 > food[i].x0) && (player.y0 < food[i].y1) && (player.y1 > food[i].y0)){
            return 1; // Collision
        }
    }
    return 0; // No collision
}


void drawMap(){   //Draws the map (rectangles) and bits (food)
 TFT_Set_Pen(CL_BLUE, 1);

  TFT_Set_Brush(1, CL_BLACK, 0, 0, 0, 0);
  TFT_Rectangle(0,0, 320, 240);

  TFT_Set_Brush(0, CL_BLUE, 0, 0, 0, 0);

  TFT_Rectangle(0,0, 319, 239); //blue outline rectangle

  TFT_Rectangle_Round_Edges(30, 30, 100, 50, 8);

  TFT_Rectangle_Round_Edges(30, 30, 50, 80, 8);

  TFT_Rectangle_Round_Edges(220, 30, 290, 50, 8);

  TFT_Rectangle_Round_Edges(270, 30, 290, 80, 8);

  TFT_Rectangle_Round_Edges(130, 30, 190, 50, 8); //top middle box

  TFT_Rectangle_Round_Edges(30, 190, 100, 210, 8);

  TFT_Rectangle_Round_Edges(30, 160, 50, 210, 8);

  TFT_Rectangle_Round_Edges(220, 190, 290, 210, 8);

  TFT_Rectangle_Round_Edges(270, 160, 290, 210, 8);

  TFT_Rectangle_Round_Edges(130, 190, 190, 210, 8); //bottom middle box

  TFT_Rectangle_Round_Edges(0, 110, 20, 130, 4);

  TFT_Rectangle_Round_Edges(50, 110, 100, 130, 8);

  //Center box split in 2
  TFT_Rectangle_Round_Edges(130, 80, 190, 108, 8); //upper center box
                                          //110
  TFT_Rectangle_Round_Edges(130, 132, 190, 160, 8); //lower center box
                                //130
  //TFT_Rectangle_Round_Edges(130, 80, 190, 160, 8); //original big center box
                           // {150, 110, 170, 130}

  TFT_Rectangle_Round_Edges(80, 80, 100, 160, 8); //vertical box of left T shape

  TFT_Rectangle_Round_Edges(300, 110, 320, 130, 4);

  TFT_Rectangle_Round_Edges(220, 110, 270, 130, 8);

  TFT_Rectangle_Round_Edges(220, 80, 240, 160, 8); //verticalbox of right T shape


//Draw Pellets:

TFT_Set_Pen(CL_YELLOW, 1);

TFT_Set_Brush(1, CL_YELLOW, 0, 0, 0, 0);

// TOP ROW
 TFT_Rectangle(8, 12, 12, 16);

 TFT_Rectangle(38, 12, 42, 16);

 TFT_Rectangle(68, 12, 72, 16);

 TFT_Rectangle(98, 12, 102, 16);

 TFT_Rectangle(128, 12, 132, 16);

 TFT_Rectangle(158, 12, 162, 16);

 TFT_Rectangle(188, 12, 192, 16);

 TFT_Rectangle(218, 12, 222, 16);

 TFT_Rectangle(248, 12, 252, 16);

 TFT_Rectangle(278, 12, 282, 16);

 TFT_Rectangle(308, 12, 312, 16);



//BOTTOM ROW
TFT_Rectangle(8, 224, 12, 228);

 TFT_Rectangle(38, 224, 42, 228);

 TFT_Rectangle(68, 224, 72, 228);

 TFT_Rectangle(98, 224, 102, 228);

 TFT_Rectangle(128, 224, 132, 228);

 TFT_Rectangle(158, 224, 162, 228);

 TFT_Rectangle(188, 224, 192, 228);

 TFT_Rectangle(218, 224, 222, 228);

 TFT_Rectangle(248, 224, 252, 228);

 TFT_Rectangle(278, 224, 282, 228);

 TFT_Rectangle(308, 224, 312, 228);


 //LEFT BORDER

TFT_Rectangle(8, 42, 12, 46);

TFT_Rectangle(8, 72, 12, 76);

//TFT_Rectangle(8, 98, 12, 102);

//TFT_Rectangle(8, 128, 12, 132);

TFT_Rectangle(8, 162, 12, 166);

TFT_Rectangle(8, 192, 12, 196);


//RIGHT BORDER

TFT_Rectangle(308, 42, 312, 46);

TFT_Rectangle(308, 72, 312, 76);

//TFT_Rectangle(308, 98, 312, 102);

//TFT_Rectangle(308, 128, 312, 132);

TFT_Rectangle(308, 162, 312, 166);

TFT_Rectangle(308, 192, 312, 196);

//SECOND COLUMN

TFT_Rectangle(38, 98, 42, 102);

//TFT_Rectangle(38, 118, 42, 122);

TFT_Rectangle(38, 144, 42, 148);

//THIRD COLUMN

TFT_Rectangle(68, 68, 72, 72);

TFT_Rectangle(68, 98, 72,102);

TFT_Rectangle(68, 144, 72, 148);

TFT_Rectangle(68, 174, 72, 178);

TFT_Rectangle(88, 68, 92, 72);

TFT_Rectangle(88, 174, 92, 178);

//FOURTH COLUMN

TFT_Rectangle(116, 38, 120, 42);

TFT_Rectangle(116, 68, 120, 72);

TFT_Rectangle(116, 98, 120, 102);

TFT_Rectangle(116, 128, 120, 132);

TFT_Rectangle(116, 158, 120, 162);

TFT_Rectangle(116, 188, 120, 192);

TFT_Rectangle(142, 68, 146, 72);

TFT_Rectangle(172, 68, 176, 72);



//FIFTH COLUMN

TFT_Rectangle(200, 38, 204, 42);

TFT_Rectangle(200, 68, 204, 72);

TFT_Rectangle(200, 98, 204, 102);

TFT_Rectangle(200, 128, 204, 132);

TFT_Rectangle(200, 158, 204, 162);

TFT_Rectangle(200, 188, 204, 192);


//SIXTH COLUMN

TFT_Rectangle(252, 68, 256, 72);

TFT_Rectangle(252, 98, 256, 102);

TFT_Rectangle(252, 144, 256, 148);

TFT_Rectangle(252, 174, 256, 178);

TFT_Rectangle(228, 68, 232, 72);

TFT_Rectangle(228, 174, 232, 178);

//SEVENTH COLUMN

TFT_Rectangle(278, 98, 282, 102);

//TFT_Rectangle(278, 118, 282, 122);

TFT_Rectangle(278, 144, 282, 148);
//ghost test ******
TFT_Set_Pen(CL_FUCHSIA, 1);
TFT_Set_Brush(1, CL_FUCHSIA, 0, 0, 0, 0);
TFT_Rectangle_Round_Edges(ghosts[0].x0,ghosts[0].y0,ghosts[0].x1,ghosts[0].y1, 5);
TFT_Set_Pen(CL_WHITE, 1);
TFT_Set_Brush(1, CL_WHITE, 0, 0, 0, 0);
TFT_Rectangle(ghostEyes[0].x0,ghostEyes[0].y0,ghostEyes[0].x1,ghostEyes[0].y1);
TFT_Rectangle(ghostEyes[1].x0,ghostEyes[1].y0,ghostEyes[1].x1,ghostEyes[1].y1);
TFT_Set_Pen(CL_BLACK, 1);
TFT_Set_Brush(1, CL_BLACK, 0, 0, 0, 0);
TFT_Rectangle(ghostEyes[2].x0,ghostEyes[2].y0,ghostEyes[2].x1,ghostEyes[2].y1);
TFT_Rectangle(ghostEyes[3].x0,ghostEyes[3].y0,ghostEyes[3].x1,ghostEyes[3].y1);

//*****************

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
           GPIOD_CRH = 0x33333333; //SETS GPIOD HIGH as output


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