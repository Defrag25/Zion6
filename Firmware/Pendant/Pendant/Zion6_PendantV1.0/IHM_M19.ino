//M19 TouchScreenCalibration

const struct TBouton LB_M19              = { 10, 60, 50, 25}; // Label
const struct TBouton LB_M19bis           = { 10, 80, 50, 25}; // Label

const struct TBouton BP_M19_X0           = { 20, 25, 30, 14};   // 
const struct TBouton BP_M19_Y0           = { 50, 10, 30, 14};   // 
const struct TBouton BP_M19_X1           = { 20,290, 30, 14};   // 
const struct TBouton BP_M19_Y1           = { 50,310, 30, 14};   // 
const struct TBouton BP_M19_X2           = {460, 25, 30, 14};   // 
const struct TBouton BP_M19_Y2           = {430, 10, 30, 14};   // 
const struct TBouton BP_M19_X3           = {460,290, 30, 14};   // 
const struct TBouton BP_M19_Y3           = {430,310, 30, 14};   // 

const struct TBouton BP_M19_XMin         = { 20,160, 30, 14};   // 
const struct TBouton BP_M19_XMax         = {460,160, 30, 14};   // 
const struct TBouton BP_M19_YMin         = {240, 10, 30, 14};   // 
const struct TBouton BP_M19_YMax         = {240,310, 30, 14};   // 

const struct TBouton Chk_M19P0           = { 15, 10,  6,  6};
const struct TBouton Chk_M19P1           = { 15,310,  6,  6};
const struct TBouton Chk_M19P2           = {465, 10,  6,  6};
const struct TBouton Chk_M19P3           = {465,310,  6,  6};

struct TBouton KeyOffset           = { 0, 0, 0, 0};   // 

uint8_t BoutonIndex=0;
boolean P0Ok=false;
boolean P1Ok=false;
boolean P2Ok=false;
boolean P3Ok=false;
boolean IHMCalibFIN=false;
uint16_t X0=0,Y0=0;
uint16_t X1=0,Y1=0;
uint16_t X2=0,Y2=0;
uint16_t X3=0,Y3=0;

uint16_t UnCalibX0=0,UnCalibY0=0;
uint16_t UnCalibX1=0,UnCalibY1=0;
uint16_t UnCalibX2=0,UnCalibY2=0;
uint16_t UnCalibX3=0,UnCalibY3=0;

uint16_t XMin=0,XMax=0;
uint16_t YMin=0,YMax=0;

void IHM_Menu19_Init(){
 MenusInit(    0                       , 0             , 1                    , 0                   , 0                 , 1);
//             Alive Format            , Erase         , PTouch reset         , Print page number   , draw BOT rect     , Menu Back
//              0 : rien                 0 : rien        0 : non                0 : non               0 : non             index
//              1 : petite barre         1 : tout        1 : oui                1 : oui               1 : oui
//              2 : rectangle            2 : TOP
//              3 : Icone deplacement    3 : BOT
//              4 : Efface menu 3

  WindowsErase2();
  TerminalSizeSet(TerminalMenu19);
  
  printStringlnColor("Calibration Dalle tactile",IHM_GRAY,2);
  printStringlnColor("Cocher les 4 boxes",IHM_GREEN,2);
  Draw_Cursor=true;
  X0=0;Y0=0; X1=0;Y1=0; X2=0;Y2=0; X3=0;Y3=0;
  
  P0Ok=false;
  P1Ok=false;
  P2Ok=false;
  P3Ok=false;
  IHMCalibFIN=false;
  IHM_Menu19_ChkRedraw();
  
  IHM_M19_Chk0();
  IHM_M19_Chk1();
  IHM_M19_Chk2();
  IHM_M19_Chk3();

  Menu_FirstStart=false;
  DEBUGSerial.println(F("Menu19 (Calibration  dalle) Init Done"));
}

 
void IHM_Menu19_ChkRedraw()
{
    DrawCheckBox(                 "0",Chk_M19P0        , IHM_YELLOW , IHM_BLACK  , P0Ok   ,1);
    DrawCheckBox(                 "1",Chk_M19P1        , IHM_YELLOW , IHM_BLACK  , P1Ok   ,1);
    DrawCheckBox(                 "2",Chk_M19P2        , IHM_YELLOW , IHM_BLACK  , P2Ok   ,1);
    DrawCheckBox(                 "3",Chk_M19P3        , IHM_YELLOW , IHM_BLACK  , P3Ok   ,1);
}

void IHM_M19_Chk0(){
 X0= PTouch.x; IHM_Draw_EditCenter(X0,BP_M19_X0 ,1, (X0==0)?IHM_WHITE:IHM_BLACK, (X0==0)?IHM_GRAY:IHM_GREEN,0); 
 Y0= PTouch.y; IHM_Draw_EditCenter(Y0,BP_M19_Y0 ,1, (Y0==0)?IHM_WHITE:IHM_BLACK, (Y0==0)?IHM_GRAY:IHM_GREEN,0);
 if( (X0!=0) & (Y0!=0) ) { printStringlnColor("Ok CheckBox0",IHM_GREEN,1); }
 UnCalibX0=PTouchDirect.x;
 UnCalibY0=PTouchDirect.y;
}
void IHM_M19_Chk1(){
 X1= PTouch.x; IHM_Draw_EditCenter(X1,BP_M19_X1 ,1, (X1==0)?IHM_WHITE:IHM_BLACK, (X1==0)?IHM_GRAY:IHM_GREEN,0);
 Y1= PTouch.y; IHM_Draw_EditCenter(Y1,BP_M19_Y1 ,1, (Y1==0)?IHM_WHITE:IHM_BLACK, (Y1==0)?IHM_GRAY:IHM_GREEN,0);
 if( (X1!=0) & (Y1!=0) ) { printStringlnColor("Ok CheckBox1",IHM_GREEN,1); }
 UnCalibX1=PTouchDirect.x;
 UnCalibY1=PTouchDirect.y;
}
void IHM_M19_Chk2(){
 X2= PTouch.x; IHM_Draw_EditCenter(X2,BP_M19_X2 ,1, (X2==0)?IHM_WHITE:IHM_BLACK, (X2==0)?IHM_GRAY:IHM_GREEN,0);
 Y2= PTouch.y; IHM_Draw_EditCenter(Y2,BP_M19_Y2 ,1, (Y2==0)?IHM_WHITE:IHM_BLACK, (Y2==0)?IHM_GRAY:IHM_GREEN,0);
 if( (X2!=0) & (Y2!=0) ) { printStringlnColor("Ok CheckBox2",IHM_GREEN,1); }
 UnCalibX2=PTouchDirect.x;
 UnCalibY2=PTouchDirect.y;

}
void IHM_M19_Chk3(){
 X3= PTouch.x; IHM_Draw_EditCenter(X3,BP_M19_X3 ,1, (X3==0)?IHM_WHITE:IHM_BLACK, (X3==0)?IHM_GRAY:IHM_GREEN,0);
 Y3= PTouch.y; IHM_Draw_EditCenter(Y3,BP_M19_Y3 ,1, (Y3==0)?IHM_WHITE:IHM_BLACK, (Y3==0)?IHM_GRAY:IHM_GREEN,0);
 if( (X3!=0) & (Y3!=0) ) { printStringlnColor("Ok CheckBox3",IHM_GREEN,1); }
 UnCalibX3=PTouchDirect.x;
 UnCalibY3=PTouchDirect.y;
}

void IHM_M19_DrawMinMax(){
  XMin=(UnCalibX0+UnCalibX1)/2; IHM_Draw_EditCenter(XMin,BP_M19_XMin ,1, IHM_GREEN, IHM_BLUE,0);
  XMax=(UnCalibX2+UnCalibX3)/2; IHM_Draw_EditCenter(XMax,BP_M19_XMax ,1, IHM_GREEN, IHM_BLUE,0);
  YMin=(UnCalibY0+UnCalibY2)/2; IHM_Draw_EditCenter(YMin,BP_M19_YMin ,1, IHM_GREEN, IHM_BLUE,0);
  YMax=(UnCalibY1+UnCalibY3)/2; IHM_Draw_EditCenter(YMax,BP_M19_YMax ,1, IHM_GREEN, IHM_BLUE,0);
}

void IHM_Menu19_Loop(){
 //do  {
   do    {
     boolean Refresh=false;
     IHM_Menu0_LoopMinimal();// Avec affichage du point corrigé

     #if (1) // Affichage du point non corrigé
     if (PTouchDirect.x<(TerminalMenu19.x                 )){PTouchDirect.x=TerminalMenu19.x+2;                 }
     if (PTouchDirect.x>(TerminalMenu19.x+TerminalMenu19.w)){PTouchDirect.x=TerminalMenu19.x+TerminalMenu19.w-2;}
     if (PTouchDirect.y<(TerminalMenu19.y                 )){PTouchDirect.y=TerminalMenu19.y+2;                 }
     if (PTouchDirect.y>(TerminalMenu19.y+TerminalMenu19.h)){PTouchDirect.y=TerminalMenu19.y+TerminalMenu19.h-2;}
     CorrectionKey();
     PTouchDirect.x+=KeyOffset.x;
     PTouchDirect.y+=KeyOffset.y;
    ActualColor=IHM_GREEN; 
    xorPixel(PTouchDirectLast.x-2, PTouchDirectLast.y);
    xorPixel(PTouchDirectLast.x-1, PTouchDirectLast.y);
    xorPixel(PTouchDirectLast.x-0, PTouchDirectLast.y);
    xorPixel(PTouchDirectLast.x+1, PTouchDirectLast.y);
    xorPixel(PTouchDirectLast.x+2, PTouchDirectLast.y);
    xorPixel(PTouchDirectLast.x  , PTouchDirectLast.y-2);
    xorPixel(PTouchDirectLast.x  , PTouchDirectLast.y-1);
    xorPixel(PTouchDirectLast.x  , PTouchDirectLast.y-0);
    xorPixel(PTouchDirectLast.x  , PTouchDirectLast.y+1);
    xorPixel(PTouchDirectLast.x  , PTouchDirectLast.y+2);
    ActualColor=IHM_GREEN; 
    xorPixel(PTouchDirect.x-2, PTouchDirect.y);
    xorPixel(PTouchDirect.x-1, PTouchDirect.y);
    xorPixel(PTouchDirect.x-0, PTouchDirect.y);
    xorPixel(PTouchDirect.x+1, PTouchDirect.y);
    xorPixel(PTouchDirect.x+2, PTouchDirect.y);
    xorPixel(PTouchDirect.x  , PTouchDirect.y-2);
    xorPixel(PTouchDirect.x  , PTouchDirect.y-1);
    xorPixel(PTouchDirect.x  , PTouchDirect.y-0);
    xorPixel(PTouchDirect.x  , PTouchDirect.y+1);
    xorPixel(PTouchDirect.x  , PTouchDirect.y+2);
    PTouchDirectLast.x=PTouchDirect.x;
    PTouchDirectLast.y=PTouchDirect.y;
#endif

     
     if (Menu_FirstStart==true)    IHM_Menu19_Init();  
     if(PTouch.z > MINPRESSURE && PTouch.z < MAXPRESSURE)
      {
       if (IHMCheck(PTouch,Chk_M19P0       )==1)  { if(P0Ok==true)P0Ok=false; else P0Ok=true; Refresh=true; IHM_M19_Chk0();}
       if (IHMCheck(PTouch,Chk_M19P1       )==1)  { if(P1Ok==true)P1Ok=false; else P1Ok=true; Refresh=true; IHM_M19_Chk1();}
       if (IHMCheck(PTouch,Chk_M19P2       )==1)  { if(P2Ok==true)P2Ok=false; else P2Ok=true; Refresh=true; IHM_M19_Chk2();}
       if (IHMCheck(PTouch,Chk_M19P3       )==1)  { if(P3Ok==true)P3Ok=false; else P3Ok=true; Refresh=true; IHM_M19_Chk3();}
      }
     if (Refresh==true){IHM_Menu19_ChkRedraw();delay(200);}
     if ( (P0Ok==true) & (P1Ok==true) & (P2Ok==true) & (P3Ok==true)){IHMCalibFIN=true;}
    }while (IHMCalibFIN==false);
   //IHM_Draw_Label("Reboot ",LB_M19                 ,3,IHM_GRAY,IHM_BLACK,0);
   IHM_M19_DrawMinMax();
   delay(100);
   printStringlnColor("Touchez l'ecran",IHM_GREEN,2);
     waitForTouch();    

   Menu_FirstStart=true;
  //}while(1);
   MenuState=0; // Necessaire car le boot ne fonctionne pas bien 
   resetFunc(); 
}

void WindowsErase2(){
  uint16_t maxscroll;
  if (tft.getRotation() & 1) maxscroll = tft.width();
  else maxscroll = tft.height();
  for (uint16_t i = 0; i <= maxscroll; i++) 
   {
    tft.vertScroll(0, maxscroll, i);
    tft.drawFastVLine(i, 0, tft.height(), brightness(rainbow(IHM_BLUE),40));
   }
  tft.vertScroll(0, maxscroll, 0);
}


void CorrectionKey(){
      IHM_BP=IHM_ButtonCheck();
  if (IHM_BP5Pressed)                           { KeyOffset.x-=10; delay(100); }                                // 
  if (IHM_BP6Pressed)                           { KeyOffset.y-=10; delay(100); }                                // 
  if (IHM_BP8Pressed)                           { KeyOffset.y+=10; delay(100); }                                // 
  if (IHM_BP9Pressed)                           { KeyOffset.x+=10; delay(100); }                                // 
  if (IHM_BP7Pressed)                           { KeyOffset.x=0;KeyOffset.y=0; delay(100); }                    // 
  if ( (IHM_BP0Pressed) & (!IHM_BP1Pressed) )   { resetFunc(); }  
}
