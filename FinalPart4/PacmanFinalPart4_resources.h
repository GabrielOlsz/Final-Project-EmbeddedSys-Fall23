
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
void drawMap();
int CheckNextWallCollision();

 #define SIZE 15        //actually acting as pacman size currently
 #define ENTITY_SIZE 5 //acting as how many pixels pacman moves currently - change names eventually
 #define BORDER_X 320
 #define BORDER_Y 240
 #define FOOD_SIZE 4
 #define FOOD_BIG_SIZE 7
 #define numWalls 18

 struct EntityProperties{
        int x0;
        int x1;
        int y0;
        int y1;
        int color;
        int isVisible;
 };
 
 struct Wall{
        int x0;
        int y0;
        int x1;
        int y1;
 };
 

struct EntityProperties player;
struct EntityProperties ghosts[4];
struct EntityProperties food[200];
struct Wall walls[numWalls] = {{0,239, 320, 340}, {30, 30, 100, 50}, {30, 30, 50, 80}, {220, 30, 290, 50}, {270, 30, 290, 80}, {130, 30, 190, 60}, {30, 190, 100, 210}, {30, 160, 50, 210}, {220, 190, 290, 210}, {270, 160, 290, 210}, {130, 180, 190, 210}, {0, 110, 20, 130}, {50, 110, 100, 130}, {130, 90, 190, 150}, {80, 90, 100, 150}, {300, 110, 320, 130}, {220, 110, 270, 130}, {220, 90, 240, 150}};

 


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
unsigned long int gameTick = 0;

unsigned long int q = 0;
unsigned long int w = 0;
unsigned long int e = 0;
unsigned long int r = 0;