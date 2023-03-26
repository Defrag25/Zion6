//IHM JOYSTIC

//const struct TBouton BP_Memu8M4CNCReset     = {425,240,80,35};
//const struct TBouton BP_Memu8M4CNCStatus    = {425,280,80,35};
//const struct TBouton BP_M4COMMRaz   = {450,180,50,25};
//const struct TBouton BP_M4AddChar   = {385,180,50,25};


const struct TBouton LB_M8                   = { 10, 58, 50, 25};
//const struct TBouton LB_M8JoylPos            = { 10, 60, 50, 25};
const struct TBouton LB_M8Joy2Pos            = {418,220, 50, 25}; // Offsets:
const struct TBouton LB_M8JoyXOffsetPos      = {385,242, 50, 25}; // JoyX
const struct TBouton BP_M8JoyXMoins          = {430,245, 25, 25}; // -
const struct TBouton BP_M8JoyXPlus           = {460,245, 25, 25}; // +

const struct TBouton LB_M8JoyZOffsetPos      = {385,272, 50, 25}; // JoyZ
const struct TBouton BP_M8JoyZMoins          = {430,275, 25, 25}; // -
const struct TBouton BP_M8JoyZPlus           = {460,275, 25, 25}; // +

const struct TBouton LB_M8JoyFOffsetPos      = {385,302, 50, 25}; // JoyF
const struct TBouton BP_M8JoyFMoins          = {430,305, 25, 25}; // -
const struct TBouton BP_M8JoyFPlus           = {460,305, 25, 25}; // +

const struct TBouton BP_M8_JoyCalibSave      = {450,125, 50, 20}; // Save
const struct TBouton BP_M8_JoyInit           = {450,150, 50, 20}; // Init

const struct TBouton LB_M8_JoySpeedPos       = {410,175, 50, 25}; // Scann Speed
const struct TBouton BP_M8_JoySpeedMoins     = {430,200, 25, 25}; // -
const struct TBouton BP_M8_JoySpeedPlus      = {460,200, 25, 25}; // +

void IHM_Menu8_Init(){
 MenusInit(    1                       , 3             , 1                    , 1                   , 1                 , FEN_PARAMS);
//             Alive Format            , Erase         , PTouch reset         , Print page number   , draw BOT rect     , Menu Back
//              0 : rien                 0 : rien        0 : non                0 : non               0 : non             index
//              1 : petite barre         1 : tout        1 : oui                1 : oui               1 : oui
//              2 : rectangle            2 : TOP
//              3 : Icone deplacement    3 : BOT
//              4 : Efface menu 3

//  AliveFormat=1;  IHM_EraseBOTArea();    PTouch_Reset(); // Reset le Touch de la fenetre d'appel precedente  
//  IHM_PrintPageNumber();MenuBack=FEN_PARAMS;
//  my_lcd.Set_Draw_color(IHM_GREEN);
//  my_lcd.Draw_Round_Rectangle(0,52,my_lcd.Get_Display_Width()-1,  my_lcd.Get_Display_Height()-1,5);
  TerminalSizeSet(TerminalMenu8);
   tft.drawRoundRect(4,75,tft.width()-100,  tft.height()-14,3, IHM_GRAY);

  IHM_Draw_Label("Joystic Calibration",LB_M8            ,2,IHM_GRAY,IHM_BLACK,0);
  IHM_Draw_Label(      "Offsets:",LB_M8Joy2Pos          ,1,IHM_GRAY,IHM_BLACK,0);
  IHM_Draw_Label(  "Scann Speed",LB_M8_JoySpeedPos     ,1,IHM_GRAY,IHM_BLACK,0);
  IHM_Menu8_ButtonRedraw();
  Menu_FirstStart=false;
  DEBUGSerial.println(F("Menu8 (JOYSTIC) Init Done"));
}

void IHM_Menu8_ButtonRedraw(){
  IHM_Draw_Label(          "JoyX",LB_M8JoyXOffsetPos    ,1,IHM_BLUE   , IHM_BLACK,0);
  IHM_Draw_Label(          "JoyZ",LB_M8JoyZOffsetPos    ,1,IHM_GREEN  , IHM_BLACK,0);
  IHM_Draw_Label(          "JoyF",LB_M8JoyFOffsetPos    ,1,IHM_RED    , IHM_BLACK,0);
  IHM_Draw_ButtonCenter2(     "-",BP_M8JoyXMoins        ,2,IHM_WHITE  , IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(     "+",BP_M8JoyXPlus         ,2,IHM_WHITE  , IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(     "-",BP_M8JoyZMoins        ,2,IHM_WHITE  , IHM_GREEN,5,0);
  IHM_Draw_ButtonCenter2(     "+",BP_M8JoyZPlus         ,2,IHM_WHITE  , IHM_GREEN,5,0);
  IHM_Draw_ButtonCenter2(     "-",BP_M8JoyFMoins        ,2,IHM_WHITE  , IHM_RED,5,0);
  IHM_Draw_ButtonCenter2(     "+",BP_M8JoyFPlus         ,2,IHM_WHITE  , IHM_RED,5,0);  
  IHM_Draw_ButtonCenter2( "Saved",BP_M8_JoyCalibSave    ,1,IHM_GREEN  , IHM_BLUE,5,0);  
  IHM_Draw_ButtonCenter2(  "Init",BP_M8_JoyInit         ,1,IHM_WHITE  , IHM_BLUE,5,0);  
  IHM_Draw_ButtonCenter2(     "+",BP_M8_JoySpeedPlus    ,2,IHM_WHITE  , IHM_BLUE,5,0);  
  IHM_Draw_ButtonCenter2(     "-",BP_M8_JoySpeedMoins   ,2,IHM_WHITE  , IHM_BLUE,5,0);  
 
}

void IHM_Menu8_SetOffset(uint16_t OffX,uint16_t OffZ,uint16_t OffF,uint16_t OffS){
  JOY.Offx  += OffX;
  JOY.Offz  += OffZ;
  JOY.Offf  += OffF;
  JOY.Fscan += OffS;
  IHM_Draw_ButtonCenter2( "Save" ,BP_M8_JoyCalibSave    ,2,IHM_WHITE      , IHM_RED,5,0);  
  delay(10);
}
void IHM_Menu8_EEP_JOYRaz(){
 TerminalClear();
 printStringln(" ");
 printStringlnColor("Calibration Joystic init",IHM_WHITE,1);
  EEPROM_JOY_CalibInit2(); 
  printStringlnColor("Necessite une recalibration du joystic",IHM_RED,1);
  EEPROM_JOY_CalibLoad();
 //printStringln(" ");   printStringlnColor("Touchez la dalle ! ",IHM_BLUE,1);  
 //waitForTouchAndPrint();
}


void IHM_Menu8_Loop(){
  boolean RefreshNeeded=false;
  if (Menu_FirstStart==true)    {IHM_Menu8_Init();}
  if(PTouch.z > MINPRESSURE && PTouch.z < MAXPRESSURE)
   {      

    if (IHMCheck(PTouch,BP_M8JoyXMoins)==1)        { IHM_Menu8_SetOffset(-1, 0, 0, 0); RefreshNeeded=true;}//IHM_Menu8_ButtonRedraw();delay(100);}
    if (IHMCheck(PTouch,BP_M8JoyXPlus)==1)         { IHM_Menu8_SetOffset( 1, 0, 0, 0); RefreshNeeded=true;}//IHM_Menu8_ButtonRedraw();delay(100);}
    if (IHMCheck(PTouch,BP_M8JoyZMoins)==1)        { IHM_Menu8_SetOffset( 0,-1, 0, 0); RefreshNeeded=true;}//IHM_Menu8_ButtonRedraw();delay(100);}
    if (IHMCheck(PTouch,BP_M8JoyZPlus)==1)         { IHM_Menu8_SetOffset( 0, 1, 0, 0); RefreshNeeded=true;}//IHM_Menu8_ButtonRedraw();delay(100);}
    if (IHMCheck(PTouch,BP_M8JoyFMoins)==1)        { IHM_Menu8_SetOffset( 0, 0,-1, 0); RefreshNeeded=true;}//IHM_Menu8_ButtonRedraw();delay(100);}
    if (IHMCheck(PTouch,BP_M8JoyFPlus)==1)         { IHM_Menu8_SetOffset( 0, 0, 1, 0); RefreshNeeded=true;}//IHM_Menu8_ButtonRedraw();delay(100);}

    
    if (IHMCheck(PTouch,BP_M8_JoySpeedPlus)==1)    { if(JOY.Fscan>100) JOY.Fscan=99;  IHM_Menu8_SetOffset( 0, 0, 0, 1); }
    if (IHMCheck(PTouch,BP_M8_JoySpeedMoins)==1)   { if(JOY.Fscan>  0)                IHM_Menu8_SetOffset( 0, 0, 0, -1); }

    if (IHMCheck(PTouch,BP_M8_JoyInit)==1)         { IHM_Menu8_EEP_JOYRaz();     IHM_Menu8_ButtonRedraw();}
    if (IHMCheck(PTouch,BP_M8_JoyCalibSave)==1)    { IHM_Draw_ButtonCenter2( "Saving" ,BP_M8_JoyCalibSave   ,1,IHM_BLACK    , IHM_GREEN,5,0); 
                                                     EEPROM_JOY_CalibSave2(JOY);
                                                     IHM_Menu8_ButtonRedraw();
                                                     RefreshNeeded=true;
                                                   }
    if (RefreshNeeded==true){ wait_released();}
   }
   JOY_DrawGraph(); // Trace Les courbes du Joystic
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gestion IHM avec boutons en face avant //
////////////////////////////////////////////
