
//VARIABLE/FUNCTION DECLARATIONS

void JoyStickConfiguration();
void GPIODConfigOutput();
void adcCONFIG();
void Joystick();
void GPIODConfigInput();
unsigned int getAdcReading();
void InitializeUSART1();        // Sub function which initializes the registers to enable USART1
void Timer1Configuration();
void Timer3IntConfiguration();
void initializeGPIO();
int CheckWallCollision();
int CheckFoodCollision();



 struct EntityProperties{
        int x0;
        int x1;
        int y0;
        int y1;
        int color;
        int isVisible;
 };

 struct EntityProperties player;
 struct EntityProperties ghosts[4];
 struct EntityProperties food[200];
 unsigned long int numWalls = 17;
 struct EntityProperties walls[numWalls];
 

 #define ENTITY_SIZE 20
 #define BORDER_X 320
 #define BORDER_Y 240
 #define FOOD_SIZE 4
 #define FOOD_BIG_SIZE 7




unsigned int right[11] = {'R','T',' ','P','R','E','S','S','E','D', ' '};
unsigned int left[11] = {'L','T',' ','P','R','E','S','S','E','D', ' '};
unsigned int up[11] = {'U','P',' ','P','R','E','S','S','E','D', ' '};
unsigned int down[11] = {'D','N',' ','P','R','E','S','S','E','D', ' '};
unsigned int click[11] = {'C','K',' ','P','R','E','S','S','E','D', ' '};
unsigned int unpause[9] = {'U','N','P','A','U','S','E','D',' '};
unsigned int left7segdisplay[10] = {0XA000, 0XA100, 0XA400, 0XA500, 0XB000, 0XB100, 0XB400, 0XB500, 0XE000, 0XE100};
unsigned int right7segdisplay[10] = {0XA800, 0XA900, 0XAC00, 0XAD00, 0XB800, 0XB900, 0XBC00, 0XBD00, 0XE800, 0XE900};
unsigned int pauseToggle = 0;
unsigned int i = 0;
int counter = 0;
int leftSide;
int rightSide;
unsigned long int pa6state = 0;
unsigned long int pd2state = 0;
unsigned long int pd4state = 0;
unsigned long int pb5state = 0;
unsigned long int pc13state = 0;
unsigned long int JoyStickDir = 0;
unsigned long int ScreenStateMachine = 0;