void main() {
1 //**************************************************************************************************
2 // Name: Professor Pellicano
3 // Date: 12/31/9993
4 // Course: ELEC3371-00
5 // Description: This program initializes USART1. It waits to receive a character from USART
6 // terminal tool in the development system and then it sends the same character
7 // back. It uses baud rate of 56000. On SW12 set PA9 and PA10 to TX and RX.
8 //**************************************************************************************************
9
10 //**************************************************************************************************
11 //VARIABLE DECLARATIONS
12 unsigned int rcvrd; // Container for received data
13 unsigned int Right[10] = {"R","T"," ","P","R","E","S","S","E","D"
   unsigned int i = 0;
14 void InitializeUSART1(); // Sub function which initializes the registers to enable USART1
15
16 //**************************************************************************************************
17 //MAIN FUNCTION
18 void main() {
19 InitializeUSART1(); // Call sub function to initialize USART1
20 for(i=0; i<10; i++){
            while(USART1_SR.TC == 0){}
            USART_DR = right[i];
            }
21 //**************************************************************************************************
22 //VARIABLE DECLARATIONS
23 for(;;) {
24 // The peripheral registers can be accessed by half-words (16-bit) or words (32-bit).
25 // Per data sheet (pg. 1007) USART1_SR consists of the following:
26 // 9 8 7 6 5 4 3 2 1 0
27 //CTS LBD TXE TC RXNE IDLE ORE NE FE PE
28 while (!((USART1_SR & (1<<5))== 0x20)){} // Check RXNE in USART1 Status Register.
29 // while receiver data register is empty, wait
30 // You can also check RXNE directly
31 // while (!USART1_SR.RXNE = 1) {} //while receiver data register is empty wait
32
33 // When data becomes available, we can store it on the CPU in a variable. Data is put into
34 // the USART data register USART1_DR (pg. 1010)
35 rcvrd = USART1_DR; //read data from receiver data register
36 //while transmitter data register is not empty wait
37 while (! (USART1_SR & (1<<7)) == 0x80) {}
38 // If we want to send data out via USART, we use the same data register
39 USART1_DR = rcvrd; // transmit the received data
40 }
41 }
42 //**************************************************************************************************
43 //SUB FUNCTIONS
44 void InitializeUSART1(){ // Sub function which initializes the registers to enable USART1
45 RCC_APB2ENR |= 1; // Enable clock for Alt. Function. USART1 uses AF for PA9/PA10
46 AFIO_MAPR=0X0F000000; // Do not mask PA9 and PA10 (becaue we are using for USART)
47 RCC_APB2ENR |= 1<<2; // Enable clock for GPIOA
48 GPIOA_CRH &= ~(0xFF << 4); // Clear PA9, PA10
49 GPIOA_CRH |= (0x0B << 4); // USART1 Tx (PA9) output push-pull
50 GPIOA_CRH |= (0x04 << 8); // USART1 Rx (PA10) input floating
51 RCC_APB2ENR |= 1<<14; // enable clock for USART1
52 USART1_BRR=0X00000506; // Set baud rate to 56000
53 // Per data sheet (pg. 1010) USART1_CR1 consists of the following:
54 //13 12 11 10 9 8 7 6 5 4 3 2 1 0
55 //UE M WAKE PCE PS PEIE TXEIE TCIE RXNEIE IDLEIE TE RE RWU SBK
56 //rw rw rw rw rw rw rw rw rw rw rw rw rw rw
57 USART1_CR1 &= ~(1<<12); // Force 8 data bits. M bit is set to 0.
58 USART1_CR2 &= ~(3<<12); // Force 1 stop bit
59 USART1_CR3 &= ~(3<<8); // Force no flow control and no DMA for USART1
60 USART1_CR1 &= ~(3<<9); // Force no parity and no parity control
61 USART1_CR1 |= 3<<2; // RX, TX enable
62 //The following two instructions can also be used to enable RX and TX manually
63 //USART1_CR1.TE=1; //TX enable
64 //USART1_CR1.RE=1; //RX enable
65 USART1_CR1 |= 1<<13; // USART1 enable. This is done after configuration is complete
66 Delay_ms(100); // Wait for USART to complete configuration and enable. This is
67 // not always necessary, but good practice.
68 }


}