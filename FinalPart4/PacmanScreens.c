

void GameOverScreen(){

 }

void HighScoreScreen(){

 }

void TitleScreen(){

 }
 
void HowtoScreen(){

}
 
 void ClearScreen(){
    TFT_Set_Pen(CL_BlUE,1);
    TFT_Set_Brush(1,CL_BLUE,0,0,0,0);
    TFT_RECTANGLE(0,0,320,240);
    TFT_SET_PEN(CL_BLACK,1);
    TFT_SET_BRUSH(1,CL_BLACK,0,0,0,0);
    TFT_RECTANGLE(1,1,319,239);
    TFT_SET_FONT(TFT_defaultFont, CL_RED, FO_HORIZONTAL);
    TFT_WRITE_TEXT("PACMAN GAME MADE BY GABE,ALEX,ANTHONY 2023", 5, 220);
 }