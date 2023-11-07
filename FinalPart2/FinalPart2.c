//**************************************************************************************************
// Name: Professor Pellicano
// Date: 12/31/9993
// Course: ELEC3371-00
// Description: This program initializes USART1. It waits to receive a character from USART
//				terminal tool in the development system and then it sends the same character
//				back. It uses baud rate of 56000. On SW12 set PA9 and PA10 to TX and RX.
//**************************************************************************************************

//**************************************************************************************************
//VARIABLE DECLARATIONS
unsigned int rcvrd;			// Container for received data

void InitializeUSART1();	// Sub function which initializes the registers to enable USART1

//**************************************************************************************************
//MAIN FUNCTION
void main() {
	InitializeUSART1();		// Call sub function to initialize USART1

//**************************************************************************************************
//VARIABLE DECLARATIONS
	for(;;) {
		// The peripheral registers can be accessed by half-words (16-bit) or words (32-bit).
		// Per data sheet (pg. 1007) USART1_SR consists of the following:
		// 9   8   7   6   5   4    3   2  1  0
		//CTS LBD TXE TC RXNE IDLE ORE NE FE PE
		while (!((USART1_SR & (1<<5))== 0x20)){} // Check RXNE in USART1 Status Register.
												 // while receiver data register is empty, wait
		// You can also check RXNE directly
		// while (!USART1_SR.RXNE = 1) {}    //while receiver data register is empty wait

		// When data becomes available, we can store it on the CPU in a variable. Data is put into
		// the USART data register USART1_DR (pg. 1010)
		rcvrd = USART1_DR;    //read data from receiver data register
		//while transmitter data register is not empty wait
		 while (! (USART1_SR & (1<<7)) == 0x80) {}
		 // If we want to send data out via USART, we use the same data register
		 USART1_DR = rcvrd-1;                // transmit the received data
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