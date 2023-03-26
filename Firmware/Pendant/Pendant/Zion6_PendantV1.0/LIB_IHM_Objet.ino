// Definition des objets de l'IHM
// VERSION Arduino DUE
//#include "LIB/TouchScreen_kbv.h"
              
const struct TBouton PICTO_MOUVEMENT   = {454, 25, 22, 22};//{455,76,20,20};

void IHM_Draw_ButtonCenter2(char *str,struct TBouton BP,uint8_t Size,uint16_t fc, uint16_t bc,uint8_t Radius,boolean Checked)
{
   uint16_t lenX,lenY;
   //const char * p = (const char *)str;
   tft.setTextColor(fc, bc); 
   tft.fillRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h , Radius, bc);
   tft.drawRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h , Radius, IHM_YELLOW);
 if (Checked) 
  
 { uint16_t col = tft.color565(0, IHM_GREEN, IHM_YELLOW);
   tft.drawRoundRect(BP.x-BP.w/2+4 , BP.y-BP.h/2+4 , BP.w-4 , BP.h-4 , Radius, col); }
   //tft.Set_Text_Mode(1);
   tft.setTextSize(Size);
   lenX = strlen((const char *)str) * 3 * Size;   
   lenY = 4 * Size;   
   tft.setCursor(BP.x-lenX+1,BP.y-lenY);
   tft.print(str);
}
void IHM_Draw_ButtonCenter(char *str,int16_t x,int16_t y,int16_t w,int16_t h,uint8_t csize,uint16_t fc, uint16_t bc,boolean mode)
{
   uint16_t lenX,lenY;
   //const char * p = (const char *)str;
      tft.fillRoundRect(x-w/2 , y-h/2 , w , h , 5 ,  bc);
      tft.drawRoundRect(x-w/2 , y-h/2 , w , h , 5 ,  IHM_YELLOW);

   tft.setTextSize(csize);
   lenX = strlen((const char *)str) * 3 * csize;   
   lenY = 4 * csize;   
   tft.setTextColor(fc, bc);  
   tft.setCursor(x-lenX,y-lenY);
   tft.print(str);
}
  //Draw_ValueBox(            "Index",0,VR_ValueBox0       ,1,IHM_WHITE, IHM_GRAY ,0,10};

//void Draw_ValueBox(char *str, struct TSPoint TP, uint8_t Index,struct TBouton BP,uint8_t Size,uint16_t fc, uint16_t bc,int Min,int Max )
//{// Box d'édition integer avec + et -
// if( (TP.x>(BP.x-BP.w/2)) &
//     (TP.x<(BP.x+BP.w/2)) &
//     (TP.y>(BP.y-BP.h/2)) &
//     (TP.y<(BP.y+BP.h/2)) )
//   { 
//
//   uint16_t lenX,lenY;
//   //const char * p = (const char *)str;
//
//      tft.fillRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h , 5 ,  bc);
//      tft.drawRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h , 5 ,  IHM_YELLOW);
// if( (TP.x>(BP.x-BP.w/2)) &
//     (TP.x<(BP.x-BP.w/2+BP.w/8)) &
//     (TP.y>(BP.y-BP.h/2)) &
//     (TP.y<(BP.y+BP.h/2)) )
//   { 
//    if(TValInteger[Index]>Min) {TValInteger[Index]=TValInteger[Index]-1;}else {TValInteger[Index]=Min;}
//   }
// if( (TP.x>(BP.x+BP.w/4)) &P.w/2 , BP.y-BP.h/2 , BP.w/4 , BP.h , 5 ,  IHM_BLACK);
//   tft.drawRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w/4 , BP.h , 5 ,  IHM_YELLOW);
//   tft.setTextColor(IHM_YELLOW);  
//   tft.setCursor(BP.x-3*BP.w/8-3 , BP.y-lenY);   tft.print("-");
//   tft.fillRoundRect(BP.x+BP.w/4 , BP.y-BP.h/2 , BP.w/4 , BP.h , 5 ,  IHM_BLACK);
//   tft.drawRoundRect(BP.x+BP.w/4 , BP.y-BP.h/2 , BP.w/4 , BP.h , 5 ,  IHM_YELLOW);
//   tft.setCursor(BP.x+3*BP.w/8-3 , BP.y-lenY);   tft.print("+");
//
//   tft.drawRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h , 5 ,  IHM_YELLOW);
//   }
//}


void IHM_Draw_ButtonCenter2NoOutBox(char *str,struct TBouton BP,uint8_t Size,uint16_t fc, uint16_t bc,boolean Checked)
{
   uint16_t lenX,lenY;
   tft.setTextColor(fc, bc);  
   tft.fillRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h ,  bc);
 if (Checked) 
 { tft.drawRoundRect(BP.x-BP.w/2+4 , BP.y-BP.h/2+4 , BP.w-4 , BP.h-4 , 5, IHM_YELLOW); }
   tft.setTextSize(Size);
   lenX = strlen((const char *)str) * 3 * Size;   
   lenY = 4 * Size;   
   tft.setCursor(BP.x-lenX+1,BP.y-lenY);
   tft.print(str);
}

void IHM_PrintPageNumber(uint8_t MenuState)
{
  const uint16_t x         = 70;
  const uint16_t y         = 15;
  tft.fillRoundRect(54 , 2 , 45 , 46 , 5 , IHM_BLACK);
  tft.drawRoundRect(53 , 1 , 47 , 48 , 5 , IHM_GRAY);
  tft.setTextSize(1);
  tft.setTextColor( IHM_GREEN , IHM_BLACK); 
  tft.setCursor(55,5);
  tft.print("PAGE :");
  tft.setTextSize(3);
  tft.setTextColor( IHM_RED , IHM_BLACK); 
  if (MenuState<10){ tft.setCursor(x,y+5);    tft.print(MenuState ,DEC);}
  else             { tft.setCursor(x-10,y+5); tft.print(MenuState,DEC);}
}

void IHM_Draw_ButtonCenter2Icon(uint8_t Type,struct TBouton BP,uint8_t csize,uint16_t fc, uint16_t bc)
{
  switch (Type)
   {
    case 0 :  tft.setTextColor(bc, IHM_BLACK); 
              tft.fillRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h   , 5 , bc);
              tft.drawRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h   , 5 , IHM_YELLOW);
              tft.fillRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h   , 5 , IHM_YELLOW);
              tft.fillRoundRect(BP.x-8      , BP.y-BP.h/3 , -3   , BP.h/3 , 2 , IHM_YELLOW);
              tft.fillRoundRect(BP.x+3      , BP.y-BP.h/3 , 8    , BP.h/3 , 2 , IHM_YELLOW);
              break;
    case 1 :  tft.fillRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h    , 5 , bc);
              tft.drawRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h    , 5 , IHM_YELLOW);
              tft.drawTriangle( BP.x-BP.w/4   , BP.y-BP.h/3,
                                BP.x+BP.w/4   , BP.y,
                                BP.x-BP.w/4   , BP.y+BP.h/3 , IHM_RED);
              break;
   }
}

void IHM_Draw_EditCenter(float Value,struct TBouton BP,uint8_t csize,uint16_t fc, uint16_t bc,uint8_t decimal)
{ // decimal indique le nombre de decimales 
  uint16_t lenY;
  tft.fillRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h , 5 , bc);
  tft.drawRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h , 5 , IHM_YELLOW);
  tft.setTextSize(csize);     tft.setTextColor(fc, bc); 
  lenY = 4 * csize;   
  tft.setCursor(BP.x-BP.w/2+4,BP.y-lenY+1);
  tft.print(Value,decimal);
}

void IHM_Draw_EditIntCenter(uint16_t Value,struct TBouton BP,uint8_t csize,uint16_t fc, uint16_t bc,boolean Checked)
{ // Le meme avec integer
  //uint16_t lenX,lenY;
  tft.fillRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h , 5 , bc);
  tft.drawRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h , 5 , IHM_YELLOW);
  tft.setTextSize(csize);     tft.setTextColor(fc, bc); 
  tft.setCursor(BP.x-BP.w/2+4,BP.y-7);
  tft.print(Value,DEC);
}



void IHM_Draw_Label(char *str,struct TBouton BP,uint8_t csize,uint16_t fc, uint16_t bc,boolean mode){
  tft.setTextSize(csize);     tft.setTextColor(fc, bc); 
  tft.setCursor(BP.x,BP.y);
  tft.print(str);
}


//boolean DrawCheckBox(char *str,struct TBouton BP,uint16_t fc, uint16_t bc,boolean Checked,boolean Enable){
//DrawCheckBox(    "Cursor",Chk_M10CURSOR    ,IHM_YELLOW , IHM_BLUE   , Draw_Cursor   ,             1);
void DrawCheckBox(char *str,struct TBouton BP,uint16_t fc, uint16_t bc,boolean Checked,boolean Enable){
   if (Enable==true) 
    {
     tft.fillRoundRect(BP.x-5 , BP.y-5 , BP.w , BP.h , 3 , Checked?fc:bc);
     tft.drawRoundRect(BP.x-5 , BP.y-5 , BP.w , BP.h , 3 , fc);
    }
    else
    {
     if(Checked){tft.fillRoundRect(BP.x-5 , BP.y-5 , BP.w , BP.h , 3 , Checked?IHM_GRAY:IHM_BLACK);}      
                 tft.drawRoundRect(BP.x-5 , BP.y-5 , BP.w , BP.h , 3 , IHM_GRAY);
    }
   tft.setTextSize(1);     tft.setTextColor(Enable?fc:IHM_GRAY, IHM_BLACK); 
   tft.setCursor(BP.x+8,BP.y-3);
   tft.print(str);
}
  
void Draw_CNCPICTODiamRayon(struct TBouton P, boolean Tp ){
if(Tp){
  tft.fillRoundRect(P.x-P.w/2 , P.y-P.w/2 , P.w , P.w , 5 , IHM_RED);
  tft.drawRoundRect(P.x-P.w/2 , P.y-P.w/2 , P.w , P.w , 5 , IHM_RED);
  tft.fillCircle(P.x, P.y, P.w-5 , IHM_YELLOW);
  tft.fillCircle(P.x, P.y, P.w-7 , IHM_RED);
  tft.setTextSize(3);     tft.setTextColor(IHM_YELLOW); 
  tft.setCursor(P.x-6,P.y-10);
  tft.print("/");
 }
 else{
  tft.fillRoundRect(P.x-P.w/2 , P.y-P.w/2 , P.w , P.h , 5 , IHM_BLUE);
  tft.drawRoundRect(P.x-P.w/2 , P.y-P.w/2 , P.w , P.h , 5 , IHM_WHITE);
  tft.setTextSize(3);     tft.setTextColor(IHM_BLUE); 
  tft.setCursor(P.x-6,P.y-10);
  tft.print("R");
 }
}

void Draw_CNCPICTOPos(struct TBouton P){
  tft.fillTriangle( P.x       , P.y-P.h,
                    P.x+P.w   , P.y+P.h,
                    P.x-P.w   , P.y+P.h, IHM_RED);
  tft.fillTriangle( P.x       , P.y-P.h-2,
                    P.x+P.w +2, P.y+P.h+2,
                    P.x-P.w -2, P.y+P.h+2,IHM_YELLOW);
  tft.setTextSize(3);     tft.setTextColor(IHM_YELLOW,tft.color565(AliveColor,0,0)); 
  tft.setCursor(P.x-7,P.y-5);
  tft.print("!");
}

void Draw_CNCPICTO(){
  tft.fillTriangle( PICTO_MOUVEMENT.x                     , PICTO_MOUVEMENT.y-PICTO_MOUVEMENT.h,
                    PICTO_MOUVEMENT.x+PICTO_MOUVEMENT.w   , PICTO_MOUVEMENT.y+PICTO_MOUVEMENT.h,
                    PICTO_MOUVEMENT.x-PICTO_MOUVEMENT.w   , PICTO_MOUVEMENT.y+PICTO_MOUVEMENT.h, IHM_RED);
  tft.fillTriangle( PICTO_MOUVEMENT.x                     , PICTO_MOUVEMENT.y-PICTO_MOUVEMENT.h-2,
                    PICTO_MOUVEMENT.x+PICTO_MOUVEMENT.w +2, PICTO_MOUVEMENT.y+PICTO_MOUVEMENT.h+2,
                    PICTO_MOUVEMENT.x-PICTO_MOUVEMENT.w -2, PICTO_MOUVEMENT.y+PICTO_MOUVEMENT.h+2,IHM_YELLOW);
  tft.setTextSize(3);     tft.setTextColor(IHM_YELLOW,tft.color565(AliveColor,0,0)); 
  tft.setCursor(PICTO_MOUVEMENT.x-7,PICTO_MOUVEMENT.y-5);
  tft.print("!");
}

   //Draw_VScrollBar(       "",     Chk_M81_Pot ,            1,  IHM_WHITE,    IHM_GRAY,       100-JOY.F,10);
void Draw_VScrollBar(char *str,struct TBouton BP,uint8_t csize,uint16_t fc, uint16_t bc,uint8_t Position,uint8_t Scale){
  const uint8_t CursorHeight=16;
  tft.fillRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h , 5, bc);
  tft.drawRoundRect(BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h , 5, IHM_YELLOW);
  //calcul des position pour tracage echelle
   uint16_t CursorPos=map(Position,0,100,1,BP.h-CursorHeight-1);
   tft.fillRoundRect(BP.x-BP.w/2 , BP.y+CursorPos-BP.h/2,
                          BP.w ,   CursorHeight,2, IHM_YELLOW);
   tft.drawRoundRect(BP.x-BP.w/2 , BP.y+CursorPos-BP.h/2,
                          BP.w ,   CursorHeight,2, IHM_BLACK);

   //Affiche le %
//   my_lcd.Set_Text_Mode(1);   my_lcd.Set_Text_Size(csize);
//   sprintf(ss3,"%d",Position);
//   lenX = strlen((const char *)ss3) * 3 * csize;   
//   lenY = 4 * csize;   
//   my_lcd.Set_Text_colour(BLACK);    my_lcd.Set_Text_Back_colour(bc);
//   my_lcd.Print(ss3, BP.x-5, BP.y-8-BP.h/2+CursorPos);
//   my_lcd.Print("%", BP.x-2, BP.y+2-BP.h/2+CursorPos);
}
void Alive()
{
  if((millis() - start1)>ScannSpeedAlive)        
   {
    start1 = millis(); 
    switch (AliveFormat)
     {
      case 0 : return;
      case 1 :
               tft.fillRect(tft.width()-60 , 5 , 5 , 41 , tft.color565(0,AliveColor,0));
               AliveColor+=10;
               break;
      case 2 :
               tft.drawRoundRect(52        , 0         , tft.width()-52 , 50  , 5 , tft.color565(0,0,AliveColor));
               AliveColor+=10;
               break;
      case 3 : // Triangle d'info RUN
               tft.fillTriangle( PICTO_MOUVEMENT.x                     , PICTO_MOUVEMENT.y-PICTO_MOUVEMENT.h,
                                 PICTO_MOUVEMENT.x+PICTO_MOUVEMENT.w   , PICTO_MOUVEMENT.y+PICTO_MOUVEMENT.h,
                                 PICTO_MOUVEMENT.x-PICTO_MOUVEMENT.w   , PICTO_MOUVEMENT.y+PICTO_MOUVEMENT.h, tft.color565(AliveColor,0,0));
               tft.drawTriangle( PICTO_MOUVEMENT.x                     , PICTO_MOUVEMENT.y-PICTO_MOUVEMENT.h-2,
                                 PICTO_MOUVEMENT.x+PICTO_MOUVEMENT.w +2, PICTO_MOUVEMENT.y+PICTO_MOUVEMENT.h+2,
                                 PICTO_MOUVEMENT.x-PICTO_MOUVEMENT.w -2, PICTO_MOUVEMENT.y+PICTO_MOUVEMENT.h+2, IHM_YELLOW);
               tft.setTextSize(3);     tft.setTextColor(IHM_YELLOW,tft.color565(AliveColor,0,0)); 
               tft.setCursor(PICTO_MOUVEMENT.x-7,PICTO_MOUVEMENT.y-3);
               tft.print("!");
               AliveColor+=10;
               break;
    case 4 : // Efface le Triangle d'info RUN
               tft.fillTriangle( PICTO_MOUVEMENT.x                     , PICTO_MOUVEMENT.y-PICTO_MOUVEMENT.h-2,
                                 PICTO_MOUVEMENT.x+PICTO_MOUVEMENT.w +2, PICTO_MOUVEMENT.y+PICTO_MOUVEMENT.h+2,
                                 PICTO_MOUVEMENT.x-PICTO_MOUVEMENT.w -2, PICTO_MOUVEMENT.y+PICTO_MOUVEMENT.h+2, IHM_BLACK);

              AliveFormat=1;
              break;
      default  : ;
     }
   }
}
 
  
void printFloatColor(float F,uint16_t Color,uint8_t Size, uint8_t Decimal){ 
//  Tsize=Size ; TFtColor=Color;
//  char *Temp;
//  sprintf(Temp,"%f",F);
//  tft.print(F,Decimal);
//  tft.setTextSize(Size);     tft.setTextColor(Color,IHM_BLACK); 
//  tft.setCursor(TXpos ,TYpos);
//  tft.print(F,Decimal);
  Tsize=Size ; TFtColor=Color;
  tft.setTextSize(Size);     tft.setTextColor(Color); 
  char Temp [15]; 
  switch (Decimal){
   case 0:   sprintf(Temp,"%.0f",F);
              break;
   case 1:   sprintf(Temp,"%.1f",F);
              break;
   case 2:   sprintf(Temp,"%.2f",F);
              break;
   case 3:   sprintf(Temp,"%.3f",F);
              break;
   default :  sprintf(Temp,"%f",F);
              break;
  }
  printString(Temp);

}


void printHexColor(uint8_t IH8,uint16_t Color,uint8_t Size){
  Tsize=Size ; TFtColor=Color;
  tft.setTextSize(Size);     tft.setTextColor(Color); 
  char Temp [15]; 
  sprintf(Temp,"%d",IH8);
  printString(Temp);
}


void printHexColor(uint16_t UI16,uint16_t Color,uint8_t Size){
  Tsize=Size ; TFtColor=Color;
  tft.setTextSize(Size);     tft.setTextColor(Color); 
  char Temp [15]; 
  sprintf(Temp,"%d",UI16);
  printString(Temp);
}

void printDecColor(int16_t I16,uint16_t Color,uint8_t Size){
  Tsize=Size ; TFtColor=Color;
  tft.setTextSize(Size);     tft.setTextColor(Color); 
  char Temp [15]; 
  sprintf(Temp,"%d",I16);
  printString(Temp);
}

void printHex16Color(uint16_t I16,uint16_t Color,uint8_t Size){
  Tsize=Size ; TFtColor=Color;
  tft.setTextSize(Size);     tft.setTextColor(Color); 
  char Temp [15]; 
  sprintf(Temp,"%x",I16);
  printString(Temp);
}



void PosCursorXY(uint16_t X,uint16_t Y){
  tft.setCursor(TXMin + X*6,TYMin + Y*8);
  TXpos = TXMin + X*Tsize*_TXsize;
  TYpos = TYMin + Y*Tsize*_TYsize;
}

void PosTab(uint8_t TAB){
    TXpos = TXMin + TAB*6;
}



void printString(char *str)
{
  while(*str) printChar(str++);
}

void printStringln(char *str)
{
  while(*str) printChar(str++);
  CRLF();
}

void printStringlnColor(char *str,uint16_t Color,uint8_t Size)
{
  tft.setTextSize(Size);
  Tsize=Size ; TFtColor=Color;
  tft.setTextColor(Color); 
  while(*str) printChar(str++);
  CRLF();
}
void printStringlnColorBk(char *str,uint16_t Color,uint16_t BkColor,uint8_t Size)
{
//    Tsize=Size ; TFtColor=Color;
//  while(*str) printChar(str++);
//  CRLF();//printChar(0x0d);
  tft.setTextSize(Size); 
  Tsize=Size ; TFtColor=Color;TBkColor=BkColor;
  tft.setTextColor(Color,BkColor); 
  while(*str) printChar(str++);

}

void printStringColor(char *str,uint16_t Color,uint8_t Size)
{
  tft.setTextSize(Size); 
  Tsize=Size ; TFtColor=Color;
  tft.setTextColor(Color,IHM_BLACK); 
  while(*str) printChar(str++);
}

void printStringColorBk(char *str,uint16_t Color,uint16_t BkColor,uint8_t Size)
{
  Tsize=Size ; TFtColor=Color;
  //tft.setTextSize(Size); tft.setTextColor(Color,BkColor); 
  while(*str) printChar(str++);
}

void CRLF(){
  
  for(uint8_t n=0;n<_TYsize*Tsize;n=n+1)  {      tft.drawFastHLine(TXpos, TYpos+n, TXMax-1-TXpos, IHM_BLACK);    }
  TXpos=TXposOffset+TXMin;TYpos+=Tsize*_TYsize;
  //Efface le texte de toute la ligne suivante si pas de depacement
  if(TYpos>TYMax-2)TYpos=TYMin;
  for(uint8_t n=0;n<_TYsize*Tsize;n++)  {       tft.drawFastHLine(TXpos, TYpos+n, TXMax-1-TXpos, IHM_BLACK);      }
  tft.setCursor(TXpos ,TYpos);
}

void printChar(char *c){
  uint16_t TempColorFont = TFtColor;
  uint16_t TempColorBk   = TBkColor; 
 //  if((c>=0x80)&(c>=0x89)) { MenuState=c-0x80; return;  }
 // Coloration des caracteres num
     //if ( ((c>=0x30)&(c<=0x39)) |(c=='.')|(c=='-'))  my_lcd.Set_Text_colour(BLUE); 
 if(*c==0x0d) 
  {
    CRLF(); // Efface le reste de la ligne
  }
 else
  {
   if(*c==0x0a)return;
   tft.setCursor(TXpos,TYpos);
   tft.write(*c); //    
   TXpos+=Tsize*_TXsize;
   if(TXpos>TXMax-5) { TXpos = TXposOffset+TXMin; TYpos+=Tsize*_TYsize;} //480
   }
  if(TYpos>(TYMax+Tsize*_TYsize)) {TYpos=TYMin;}         // SCROLLING TEST
  //if(TYpos>(TYMax+Tsize*_TYsize)) Terminal_Scroll(8);
  tft.setTextColor(TempColorFont); 
  TFtColor = TempColorFont;
  TBkColor = TempColorBk; 
}
     
void IHM_EraseTOPArea(){
  tft.fillRect( 0 , 0 , tft.width() , 52,IHM_BLACK);
}
void IHM_EraseBOTArea(){
  tft.fillRect( 0 , 52 , tft.width() , tft.height() , IHM_BLACK);
}

void IHM_EraseTotalArea(){
  tft.fillScreen(IHM_BLACK);
}



extern const uint8_t hanzi[];


void showhanzi(unsigned int x, unsigned int y, unsigned char index)
{
    uint8_t i, j, c, first = 1;
    uint8_t *temp = (uint8_t*)hanzi;
    uint16_t color;
    tft.setAddrWindow(x, y, x + 31, y + 31); //
    temp += index * 128;
    for (j = 0; j < 128; j++)
    {
        c = pgm_read_byte(temp);
        for (i = 0; i < 8; i++)
        {
            if ((c & (1 << i)) != 0)
            {
                color = IHM_RED;
            }
            else
            {
                color = IHM_BLACK;
            }
            tft.pushColors(&color, 1, first);
            first = 0;
        }
        temp++;
    }
}





void windowScroll(int16_t x, int16_t y, int16_t wid, int16_t ht, int16_t dx, int16_t dy, uint16_t *buf)
{
    if (dx) for (int16_t row = 0; row < ht; row++) {
            READGRAM(x, y + row, buf, wid, 1);
            tft.setAddrWindow(x, y + row, x + wid - 1, y + row);
            tft.pushColors(buf + dx, wid - dx, 1);
            tft.pushColors(buf + 0, dx, 0);
        }
    if (dy) for (int16_t col = 0; col < wid; col++) {
            READGRAM(x + col, y, buf, 1, ht);
            tft.setAddrWindow(x + col, y, x + col, y + ht - 1);
            tft.pushColors(buf + dy, ht - dy, 1);
            tft.pushColors(buf + 0, dy, 0);
        }
}




void Intro(){
 tft.fillScreen(IHM_BLACK);
 for (uint8_t n=0;n<100;n++)
  { 
   Yopla2(100);
   delay(10);    
  }
  delay(100);    
  WindowsErase();
}
// x,y == coords of centre of arc
// start_angle = 0 - 359
// seg_count = number of 6 degree segments to draw (60 => 360 degree arc)
// rx = x axis outer radius
// ry = y axis outer radius
// w  = width (thickness) of arc in pixels
// colour = 16 bit colour value
// Note if rx and ry are the same then an arc of a circle is drawn
//int fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour)

void Intro2(){
  WindowsErase();
 for (int n=0;n<359;n++)
  { 
 
  fillArcExp( 240, 160, random(360), random(360), random(100), random(100), 0,rainbow(IHM_GREEN));
  }  //delay(2);    
  fillArcExp( 240, 160, 20, 100, 80, 50, 0, IHM_BLUE);
    
}










void WindowsErase(){
  uint16_t maxscroll;
  if (tft.getRotation() & 1) maxscroll = tft.width();
  else maxscroll = tft.height();
  for (uint16_t i = 0; i <= maxscroll; i++) 
   {
    tft.vertScroll(0, maxscroll, i);
    tft.drawFastVLine(i, 0, tft.height(), IHM_BLACK);
   }
  tft.vertScroll(0, maxscroll, 0);
}



void tests(){
    tft.fillScreen( IHM_BLACK);
    tft.fillRoundRect(100, 200, 110, 220, 30, tft.color565(0, IHM_GREEN, 0));
    tft.drawRoundRect(150, 35,45, 23,  8, tft.color565(IHM_RED, 0, 0));
    tft.drawTriangle(20, 25, 56,99, 45, 102 , IHM_RED);
    tft.drawCircle(250, 250, 150, IHM_GREEN);
}
void printmsg(int row, const char *msg)
{
    tft.setTextColor( IHM_YELLOW , IHM_BLACK);
    tft.setCursor(0, row);
    tft.println(msg);
}
