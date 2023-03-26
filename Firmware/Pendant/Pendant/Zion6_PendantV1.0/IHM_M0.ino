
// Menu de présentation


const struct TBouton B_MENUmoins            = { 25, 25, 50, 50};
const struct TBouton Chk_EnableParams       = {108,  8, 10, 10};

const struct TBouton LB_M0ChangeXPos        = {285,  6,  2,  2};
const struct TBouton LB_M0ChangeZPos        = {285, 30,  2,  2};
const struct TBouton BP_M0ChangeXPos        = {355, 11,115, 25};
const struct TBouton BP_M0ChangeZPos        = {355, 35,115, 25};

const struct TBouton BP_M0CNCStateReset     = {240, 36, 80,  18};
const struct TBouton BP_M0CNCToolPos        = {220, 13, 40,  18};
const struct TBouton BP_M0CNCORGPos         = {180, 13, 40,  18};

const struct TBouton BP_M0CNCMode           = {260, 13, 40,  16};

const struct TBouton LB_M0ChangeFPerPos     = {150,28,2, 2};  // FeedRate Percent
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IHM ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

boolean IHMCheck(struct TSPoint PT,struct TBouton BP)
 {
  int16_t _XM,_XP,_YM,_YP;
  _XM = BP.x-BP.w/2;
  _XP = BP.x+BP.w/2;
  _YM = BP.y-BP.h/2;
  _YP = BP.y+BP.h/2;
   
  if(( (PT.x>=_XM)&(PT.x<=_XP) ) & ( (PT.y>=_YM)&(PT.y<=_YP) )) 
  {
    return(1);      
  }
  return(0);
}

boolean IHMCheckIndexOLD(uint8_t Index, struct TSPoint PT,struct TBouton BP)
 {
  

  int16_t _XM,_XP,_YM,_YP;
  _XM = BP.x-BP.w/2;
  _XP = BP.x+BP.w/2;
  _YM = BP.y-BP.h/2;
  _YP = BP.y+BP.h/2;
  if(MenuIndexSelect==Index)   {
                                //AFFICHAGE
                                if(BP.h>=20) // Grand bouton
                                {
                                tft.drawRoundRect( BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h ,5, rainbow2(RainColor));//IHM_RED);
                                tft.fillTriangle ( (BP.x-BP.w/2)+2  , (BP.y+BP.h/2)-3  ,
                                                   (BP.x-BP.w/2)+2  , (BP.y+BP.h/2)-BP.h/3 ,
                                                   (BP.x-BP.w/2)+BP.h/3 , (BP.y+BP.h/2)-3  , rainbow2(RainColor));//IHM_GREEN);
                                tft.fillTriangle ( (BP.x+BP.w/2)-3  , (BP.y-BP.h/2)+2  ,
                                                   (BP.x+BP.w/2)-3  , (BP.y-BP.h/2)+BP.h/3 ,
                                                   (BP.x+BP.w/2)-BP.h/3 , (BP.y-BP.h/2)+2  , rainbow2(RainColor));//IHM_GREEN);
                                }
                                
                                else
                                { // Petit bouton
                                //tft.drawRoundRect( BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h ,5, ((millis()&0x00000FFF)>0x0800)?IHM_RED:IHM_BLUE);
                                tft.drawRoundRect( BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h ,3, rainbow(RainColor));//IHM_RED);
                                }
                                // CHECK
                                if ( IHM_BP9Pressed ) {do{IHM_BP=IHM_ButtonCheck();}while(IHM_BP9Pressed);
                                                       return(1); }
                                //if((MenuIndexSelectRefreshNeeded==true) &  (MenuIndexSelect!=MenuIndexSelectLast) ){MenuIndexSelectRefreshNeeded=true;}
                                //else {MenuIndexSelectRefreshNeeded=false;}
                               }
  else                         { 
           if(1)
            {
                                // EFFACEMENT DE L'ANCIEN BOUTON
                                uint16_t _col = tft.readPixel((BP.x-BP.w/2)+2,BP.y); // Lecture de la couleur du bouton sur le côté gauche
                                                                                    // afin d'effacer les triangles de selection
                                if(BP.h>=20) // Grand bouton
                                {
                                tft.drawRoundRect( BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h ,5, IHM_GREEN);
                                tft.fillTriangle ( (BP.x-BP.w/2)+2  , (BP.y+BP.h/2)-3  ,
                                                   (BP.x-BP.w/2)+2  , (BP.y+BP.h/2)-BP.h/3 ,
                                                   (BP.x-BP.w/2)+BP.h/3 , (BP.y+BP.h/2)-3  , _col);
                                tft.fillTriangle ( (BP.x+BP.w/2)-3  , (BP.y-BP.h/2)+2  ,
                                                   (BP.x+BP.w/2)-3  , (BP.y-BP.h/2)+BP.h/3 ,
                                                   (BP.x+BP.w/2)-BP.h/3 , (BP.y-BP.h/2)+2  , _col);
                                 }
                                 else // Petit bouton
                                 {
                                  tft.drawRoundRect( BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h ,3, IHM_GREEN);
                                 }
            }
                                }
   
  if(( (PT.x>=_XM)&(PT.x<=_XP) ) & ( (PT.y>=_YM)&(PT.y<=_YP) )) 
  {
    return(1);      
  }
  return(0);
}

boolean IHMCheckIndex(uint8_t Index, struct TSPoint PT,struct TBouton BP)
 {
  

  int16_t _XM,_XP,_YM,_YP;
  _XM = BP.x-BP.w/2;
  _XP = BP.x+BP.w/2;
  _YM = BP.y-BP.h/2;
  _YP = BP.y+BP.h/2;
  if(MenuIndexSelect==Index)   {
                                if(BP.h>=20) // Grand bouton
                                {
                                tft.drawRoundRect( BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h ,5, rainbow(RainColor));//IHM_RED);
                                tft.fillTriangle ( (BP.x-BP.w/2)+2  , (BP.y+BP.h/2)-3  ,
                                                   (BP.x-BP.w/2)+2  , (BP.y+BP.h/2)-BP.h/3 ,
                                                   (BP.x-BP.w/2)+BP.h/3 , (BP.y+BP.h/2)-3  , rainbow(RainColor));//IHM_GREEN);
                                tft.fillTriangle ( (BP.x+BP.w/2)-3  , (BP.y-BP.h/2)+2  ,
                                                   (BP.x+BP.w/2)-3  , (BP.y-BP.h/2)+BP.h/3 ,
                                                   (BP.x+BP.w/2)-BP.h/3 , (BP.y-BP.h/2)+2  , rainbow(RainColor));//IHM_GREEN);
                                }
                                
                                else
                                { // Petit bouton
                                //tft.drawRoundRect( BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h ,5, ((millis()&0x00000FFF)>0x0800)?IHM_RED:IHM_BLUE);
                                tft.drawRoundRect( BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h ,5, rainbow(RainColor));//IHM_RED);
                                }
                                if ( IHM_BP9Pressed ) {do{IHM_BP=IHM_ButtonCheck();}while(IHM_BP9Pressed);
                                                       return(1); }
                               }
  else                         {
                 if(MenuIndexSelectCount!=0)
                  {MenuIndexSelectCount--;
                 // printFloatColor(MenuIndexSelectCount,IHM_WHITE,1,0);CRLF(); //Pour DEBUG du nombre d'effacement d'objet 
                 //printFloatColor(RainColor,IHM_WHITE,1,0);CRLF(); //Pour DEBUG du nombre d'effacement d'objet 
                  
                   uint16_t _col = tft.readPixel((BP.x-BP.w/2)+2,BP.y); // Lecture de la couleur du bouton sur le côté gauche
                 
                                                                                    // afin d'effacer les triangles de selection
                                if(BP.h>=20) // Grand bouton
                                {
                                tft.drawRoundRect( BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h ,5, IHM_GREEN);
                                tft.fillTriangle ( (BP.x-BP.w/2)+2  , (BP.y+BP.h/2)-3  ,
                                                   (BP.x-BP.w/2)+2  , (BP.y+BP.h/2)-BP.h/3 ,
                                                   (BP.x-BP.w/2)+BP.h/3 , (BP.y+BP.h/2)-3  , _col);
                                tft.fillTriangle ( (BP.x+BP.w/2)-3  , (BP.y-BP.h/2)+2  ,
                                                   (BP.x+BP.w/2)-3  , (BP.y-BP.h/2)+BP.h/3 ,
                                                   (BP.x+BP.w/2)-BP.h/3 , (BP.y-BP.h/2)+2  , _col);
                                 }
                                 else // Petit bouton
                                 {
                                  tft.drawRoundRect( BP.x-BP.w/2 , BP.y-BP.h/2 , BP.w , BP.h ,5, IHM_GREEN);
                                 }
                  }
                               }
  if(( (PT.x>=_XM)&(PT.x<=_XP) ) & ( (PT.y>=_YM)&(PT.y<=_YP) )) 
  {
    return(1);      
  }
  return(0);
}





boolean IHM_ButtonsWaitReleased(){
  do{IHM_BP=IHM_ButtonCheck();} while ( IHM_BP!=0 ); 
}
void IHM_All_MenuIndexCheck(){
  if ( IHM_BP8Pressed )  
   { 
    MenuIndexSelectCount=MenuIndexSelectMax; // Permet de faire un seul rafraichissement de tous les boutons
    if(MenuIndexSelect<MenuIndexSelectMax)   { MenuIndexSelect++; } 
    else                                     { MenuIndexSelect=1; }
    do{IHM_BP=IHM_ButtonCheck();} while ( IHM_BP8Pressed ); 
   } //DEBUGSerial.println(MenuIndexSelect,DEC);} 
  if ( IHM_BP6Pressed )  
   { 
    MenuIndexSelectCount=MenuIndexSelect; 
    if(MenuIndexSelect>1)                    { MenuIndexSelect--; }
    else                                       { MenuIndexSelect=MenuIndexSelectMax; }
    do{IHM_BP=IHM_ButtonCheck();}while ( IHM_BP6Pressed); 
   } //DEBUGSerial.println(MenuIndexSelect,DEC);} 
}

void IHM_Menu0_PrintPos()
{
      //tft.setTextSize(2);

  ///////////////////////////
  // Position X
  if ( (CNC.X!=CNCLast.X) || (Menu_FirstStart==true) )
   { tft.setTextSize(2);
     tft.setCursor(BP_M0ChangeXPos.x-50,BP_M0ChangeXPos.y-5); tft.setTextColor(IHM_BLACK);   tft.print(CNCLast.X,3);
     tft.setCursor(BP_M0ChangeXPos.x-50,BP_M0ChangeXPos.y-5); tft.setTextColor(IHM_WHITE);   tft.print(CNC.X,3);
     CNCLast.X=CNC.X;    
   } 
  ///////////////////////////
  // Position Z
  if ( (CNC.Z!=CNCLast.Z) || (Menu_FirstStart==true) )
   { tft.setTextSize(2);
     tft.setCursor(BP_M0ChangeZPos.x-50,BP_M0ChangeZPos.y-5); tft.setTextColor(IHM_BLACK);   tft.print(CNCLast.Z,3);
     tft.setCursor(BP_M0ChangeZPos.x-50,BP_M0ChangeZPos.y-5); tft.setTextColor(IHM_WHITE);   tft.print(CNC.Z,3);
     CNCLast.Z=CNC.Z;    
   }   
  ///////////////////////////
  // Mode
  if ( (CNC.State!=CNCLast.State) || (Menu_FirstStart==true) )
   {
    // Efface le texte precedent
   if (COMM_Control==true)
    {
     if(CNC.State=="IDLE")  { IHM_Draw_ButtonCenter2(    "IDLE",BP_M0CNCStateReset   ,2,IHM_WHITE, IHM_BLUE,5,0);}
     if(CNC.State=="ALARM") { IHM_Draw_ButtonCenter2(   "ALARM",BP_M0CNCStateReset   ,2,IHM_WHITE, IHM_RED,5,0);}
     if(CNC.State=="JOG")   { IHM_Draw_ButtonCenter2(     "JOG",BP_M0CNCStateReset   ,2,IHM_WHITE, IHM_GREEN,5,0);}
     if(CNC.State=="RUN")   { IHM_Draw_ButtonCenter2(     "RUN",BP_M0CNCStateReset   ,2,IHM_WHITE, IHM_GREEN,5,0);}
     if(CNC.State=="----")  { IHM_Draw_ButtonCenter2(    "----",BP_M0CNCStateReset   ,2,IHM_BLACK, IHM_GRAY,5,0);}
     if(CNC.State=="HOLD:0"){ IHM_Draw_ButtonCenter2(    "HOLD",BP_M0CNCStateReset   ,2,IHM_BLACK, IHM_GRAY,5,0);}
    }
    CNCLast.State=CNC.State;
   }   
  ///////////////////////////
  // Outil selectionne
  if ( (CNC.ToolSelect!=CNCLast.ToolSelect) || (Menu_FirstStart==true) )
   {
    if(CNC.ToolSelect==0){ IHM_Draw_ButtonCenter2NoOutBox(    "T1",BP_M0CNCToolPos   ,2,IHM_GREEN, IHM_BLACK,0);}    
    if(CNC.ToolSelect==1){ IHM_Draw_ButtonCenter2NoOutBox(    "T2",BP_M0CNCToolPos   ,2,IHM_GREEN, IHM_BLACK,0);}    
    if(CNC.ToolSelect==2){ IHM_Draw_ButtonCenter2NoOutBox(   "TL0",BP_M0CNCToolPos   ,2,IHM_GREEN, IHM_BLACK,0);}    
    CNCLast.ToolSelect=CNC.ToolSelect;
   }
  if ( (CNC.ORGIndex!=CNCLast.ORGIndex) || (Menu_FirstStart==true) )
   {
    if(CNC.ORGIndex==0){ IHM_Draw_ButtonCenter2NoOutBox(       "G54",BP_M0CNCORGPos   ,2,IHM_RED , IHM_BLACK,0);}    
    if(CNC.ORGIndex==1){ IHM_Draw_ButtonCenter2NoOutBox(       "G55",BP_M0CNCORGPos   ,2,IHM_RED , IHM_BLACK,0);}    
    CNCLast.ORGIndex=CNC.ORGIndex;
   }
  if ( (CNC.ModeAbsRel!=CNCLast.ModeAbsRel) || (Menu_FirstStart==true) )
   {
    CNCLast.ModeAbsRel=CNC.ModeAbsRel;
   }
  if(JOYLastM2.F!=JOY.F)
   {
    tft.setTextSize(2);
    tft.setCursor(LB_M0ChangeFPerPos.x,LB_M0ChangeFPerPos.y); tft.setTextColor(IHM_BLACK);   tft.print(JOYLastM2.F,DEC); tft.print("%");
    tft.setCursor(LB_M0ChangeFPerPos.x,LB_M0ChangeFPerPos.y); tft.setTextColor(IHM_WHITE);   tft.print(JOY.F,DEC);       tft.print("%");
    JOYLastM2.F=JOY.F;
   }
}


void MenusInit(uint8_t Format          ,uint8_t Erase  , uint8_t TouchReset   , uint8_t PageNumber  , uint8_t DrawRect  , uint8_t MBack){
//             Alive Format            , Erase         , PTouch reset         , Print page number   , draw BOT rect     , Menu Back
//              0 : rien                 0 : rien        0 : non                0 : non               0 : non             index
//              1 : petite barre         1 : tout        1 : oui                1 : oui               1 : oui
//              2 : rectangle            2 : TOP
//              3 : Icone deplacement    3 : BOT
//              4 : Efface menu 3
//
  AliveFormat=Format;
  switch (Erase){
    case 0 : break;
    case 1 : WindowsErase(); break;
    case 2 : IHM_EraseTOPArea(); break;
    case 3 : IHM_EraseBOTArea(); break;
  }
 if (TouchReset) { PTouch_Reset(); } 
 if (PageNumber) { IHM_PrintPageNumber(MenuState); }
 if (DrawRect) { 
    tft.drawRoundRect(0,52,tft.width()-1,tft.height()-1-52 ,5, IHM_GREEN);
    }
 MenuBack=MBack;
 MenuStateLast=MenuState; // Permet de connaitre l'index de la fenetre d'appel
// Menu_FirstStart=false;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MENU ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
void IHM_Menu0_Init(){
  DEBUGSerial.println();
  AliveFormat=(Joystic_Control?3:1); // Affiche le logo MOUVEMENT SI JOG ACTIF
  AliveFormat=1;
  PTouch_Reset();// Reset le Touch de la fenetre d'appel precedente 
  IHM_EraseTOPArea();//my_lcd.Fill_Screen(IHM_BLACK); 

  tft.drawRoundRect(52,0,tft.width()-52-52, 50 ,5, IHM_GRAY);

  IHM_Draw_ButtonCenter2("<",B_MENUmoins,2,IHM_BLUE ,IHM_GREEN,5,0);

  IHM_PrintPageNumber(MenuState);

  DrawCheckBox(                 "Params",Chk_EnableParams            , IHM_YELLOW , IHM_BLUE    , EnableParams  ,1);
  IHM_Draw_Label(                    "X",LB_M0ChangeXPos      ,2     , IHM_GRAY   , IHM_BLACK                   ,0);
  IHM_Draw_Label(                    "Z",LB_M0ChangeZPos      ,2     , IHM_GRAY   , IHM_BLACK                   ,0);
  IHM_Draw_ButtonCenter2(         "----",BP_M0CNCStateReset   ,2     , IHM_WHITE  , IHM_GRAY                    ,5,0);
  IHM_Draw_ButtonCenter2NoOutBox(   "T0",BP_M0CNCToolPos      ,2     , IHM_GREEN  , IHM_BLACK                   ,0);
  IHM_Draw_ButtonCenter2NoOutBox(  "G54",BP_M0CNCORGPos       ,2     , IHM_RED    , IHM_BLACK                   ,0);
  
  DEBUGSerial.println("IHM Start");
  Menu0_Refresh        = false;  
  IHM_Menu0_PrintPos();
  Menu_FirstStart      = false;
  DEBUGSerial.println("Menu0 Init Done");  
}


void IHM_Menu0_Loop(){
  boolean RefreshNeededWhenCheckedChanged =false; // Var to refresh Current Windows on checked Change
  boolean NewAxePositionXToSave=false; // Permet la sauvegarde de la nouvelle position d'axe X
  if (Menu0_Refresh==true)    IHM_Menu0_Init();  
    //CHECK TouchScreen
  digitalWrite(13, HIGH);
  //TSPoint 
  PTouch = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);  pinMode(YP, OUTPUT);

  if(PTouch.z > MINPRESSURE && PTouch.z < MAXPRESSURE)
   {      
    //Recale Ecran <> TouchScreen
    TXpos=TXMin;TYpos=TYMin;
//      DEBUGSerial.print("Before > "); DEBUGSerial.print("(");DEBUGSerial.print(PTouch.x);DEBUGSerial.print(";");
//       DEBUGSerial.print(PTouch.y);DEBUGSerial.print(") "); DEBUGSerial.println(PTouch.z);    //Affiche curseur
    PTouch.x = map(PTouch.x, TS_MINX, TS_MAXX , 0            , tft.width());
    PTouch.y = map(PTouch.y, TS_MINY, TS_MAXY , tft.height() , 0);
//      DEBUGSerial.print("After    "); DEBUGSerial.print("(");DEBUGSerial.print(PTouch.x);DEBUGSerial.print(";");
//       DEBUGSerial.print(PTouch.y);DEBUGSerial.print(") "); DEBUGSerial.println(PTouch.z);    //Affiche curseur
    //if(EnableParams)
    // {
    //  DEBUGSerial.print("Touch > "); DEBUGSerial.print("(");DEBUGSerial.print(PTouch.x);DEBUGSerial.print(";");
    //   DEBUGSerial.print(PTouch.y);DEBUGSerial.print(") "); DEBUGSerial.println(PTouch.z);    //Affiche curseur
    // }
    if(Draw_Cursor)
     {
#if (1) 
    ActualColor=IHM_WHITE; 
    xorPixel(PTouchLast.x-2, PTouchLast.y);
    xorPixel(PTouchLast.x-1, PTouchLast.y);
    xorPixel(PTouchLast.x-0, PTouchLast.y);
    xorPixel(PTouchLast.x+1, PTouchLast.y);
    xorPixel(PTouchLast.x+2, PTouchLast.y);
    xorPixel(PTouchLast.x  , PTouchLast.y-2);
    xorPixel(PTouchLast.x  , PTouchLast.y-1);
    xorPixel(PTouchLast.x  , PTouchLast.y-0);
    xorPixel(PTouchLast.x  , PTouchLast.y+1);
    xorPixel(PTouchLast.x  , PTouchLast.y+2);
    ActualColor=IHM_WHITE; 
    xorPixel(PTouch.x-2, PTouch.y);
    xorPixel(PTouch.x-1, PTouch.y);
    xorPixel(PTouch.x-0, PTouch.y);
    xorPixel(PTouch.x+1, PTouch.y);
    xorPixel(PTouch.x+2, PTouch.y);
    xorPixel(PTouch.x  , PTouch.y-2);
    xorPixel(PTouch.x  , PTouch.y-1);
    xorPixel(PTouch.x  , PTouch.y-0);
    xorPixel(PTouch.x  , PTouch.y+1);
    xorPixel(PTouch.x  , PTouch.y+2);
    PTouchLast.x=PTouch.x;
    PTouchLast.y=PTouch.y;
#endif
#if (0)
    tft.drawFastHLine(PTouchLast.x-2, PTouchLast.y   , 5, IHM_BLACK);
    tft.drawFastVLine(PTouchLast.x  , PTouchLast.y-2 , 5, IHM_BLACK);
    tft.drawFastHLine(PTouch.x-2    , PTouch.y       , 5, IHM_WHITE);
    tft.drawFastVLine(PTouch.x      , PTouch.y-2     , 5, IHM_WHITE);
#endif
    PTouchLast.x=PTouch.x;    PTouchLast.y=PTouch.y;
    }
    if(EnableDRAWCoord)
     { // Affichage des coordonnées du pointeur en bas de l'écran
      tft.setTextSize(1);
      tft.setCursor(10,310); tft.setTextColor(IHM_BLACK); tft.print("(");tft.print(PTouchLastM0.x);tft.print(",");tft.print(PTouchLastM0.y);tft.print(")");
      tft.setCursor(10,310); tft.setTextColor(IHM_GREEN); tft.print("(");tft.print(PTouch.x);      tft.print(",");tft.print(PTouch.y);      tft.print(")");
      PTouchLastM0=PTouch;
     }
    PTouchLast=PTouch;
    
    /////////////////////////////////
    // Check Boutons de navigation //
    /////////////////////////////////

    if (IHMCheck(PTouch,B_MENUmoins)==1) // BP MOINS
     {
       DEBUGSerial.println("Bouton MOINS");
       IHM_PrintPageNumber(MenuState);
       if(MenuState>0)
        {Menu0_Refresh=true;
          //MenuState--;
          Menu_FirstStart=true;delay(100);
          MenuState=MenuBack;
          IHM_PrintPageNumber(MenuState);
        }
       if (MenuState==0)
        {
         Menu0_Refresh=true;
        }
        wait_released();
     }

    if (IHMCheck(PTouch,Chk_EnableParams)==1) { RefreshNeededWhenCheckedChanged=true; if(EnableParams==true)EnableParams=false;     else EnableParams=true;   Menu_FirstStart  = true;DrawCheckBox(     "Params",Chk_EnableParams,IHM_YELLOW, IHM_BLUE,EnableParams,1);wait_released(); }
    if (IHMCheck(PTouch,BP_M0CNCToolPos)==1)  { if(CNC.ToolSelect++>=2)CNC.ToolSelect=0;  wait_released();                             delay(250);ToolRedrawNeeded=true; }
    if (IHMCheck(PTouch,BP_M0CNCORGPos)==1)   { if(CNC.ORGIndex++>=1) CNC.ORGIndex=0;     wait_released();  CNC_ORG_Get(CNC.ORGIndex); delay(250); ToolRedrawNeeded=true; } 
   }
  if (IHMCheck(PTouch,BP_M0CNCStateReset)==1) {CNC_Reset();  wait_released();}
//  if (IHMCheck(PTouch,BP_M0CNCMode)==1)       {CNC.ModeAbsRel=!CNC.ModeAbsRel;  wait_released();delay(250);}
  
  IHM_Menu0_PrintPos();
  if (RefreshNeededWhenCheckedChanged==true) Menu0_Refresh=true;
   
  
  //if (Joystic_Enabled) {AliveFormat=3;}else {AliveFormat==1;} 
//  if ((Joystic_Control==true)&(POWER_Control==true)){AliveFormat=3;}else{AliveFormat=1;}
  //AliveFormat=(Joystic_Control?3:1); // Affiche le logo MOUVEMENT SI JOG ACTIF
  //Living();
}


void IHM_Menu0_LoopMinimal()
{ // CHECK TouchScreen
  // Affiche curseur
  // Affiche Coordonnées
  digitalWrite(13, HIGH);
  //TSPoint 
  PTouch = ts.getPoint();
  PTouchDirect=PTouch;
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);  pinMode(YP, OUTPUT);
  
  if(PTouch.z > MINPRESSURE && PTouch.z < MAXPRESSURE)
   {      
    //Recale Ecran <> TouchScreen
    
    PTouch.x = map(PTouch.x, TS_MINX, TS_MAXX , 0            , tft.width());
    PTouch.y = map(PTouch.y, TS_MINY, TS_MAXY , tft.height() , 0);

    
#if (1)
    ActualColor=IHM_WHITE; 
    xorPixel(PTouchLast.x-2, PTouchLast.y);
    xorPixel(PTouchLast.x-1, PTouchLast.y);
    xorPixel(PTouchLast.x-0, PTouchLast.y);
    xorPixel(PTouchLast.x+1, PTouchLast.y);
    xorPixel(PTouchLast.x+2, PTouchLast.y);
    xorPixel(PTouchLast.x  , PTouchLast.y-2);
    xorPixel(PTouchLast.x  , PTouchLast.y-1);
    xorPixel(PTouchLast.x  , PTouchLast.y-0);
    xorPixel(PTouchLast.x  , PTouchLast.y+1);
    xorPixel(PTouchLast.x  , PTouchLast.y+2);
    ActualColor=IHM_WHITE; 
    xorPixel(PTouch.x-2, PTouch.y);
    xorPixel(PTouch.x-1, PTouch.y);
    xorPixel(PTouch.x-0, PTouch.y);
    xorPixel(PTouch.x+1, PTouch.y);
    xorPixel(PTouch.x+2, PTouch.y);
    xorPixel(PTouch.x  , PTouch.y-2);
    xorPixel(PTouch.x  , PTouch.y-1);
    xorPixel(PTouch.x  , PTouch.y-0);
    xorPixel(PTouch.x  , PTouch.y+1);
    xorPixel(PTouch.x  , PTouch.y+2);
    PTouchLast.x=PTouch.x;
    PTouchLast.y=PTouch.y;
#endif

//    PTouchLast=PTouch;
   }  
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TERMINAL TFT ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                   w
// (TxposMin,TyposMin)-----------               // Les dimensions w,h du terminal sont optimales si elles sont en rapport
//          |                    |              // avec la taille de la polices
//          |                    |              // Elles sont toutes en pixel et en mode portrait !
//          |                    | h
//          |     (Txpos,Typos)  |
//          |           A        |
//           --------------------
//
//
//
//uint16_t TXpos=0;    // Position gauche du terminal
//uint16_t TYpos=0;    // Position basse 
//const uint8_t TXposOffset = 0 ; //Offset de ddeplacement du texte par rapport au bord gauche du terminal (permet de placer des N° de lignes
//uint8_t  _TXsize=6;   // Taille caractere police
//uint8_t  _TYsize=8;   // Taille caractere police
//uint8_t  Tsize=1;    // 2 (pas testé autre taille) 
//uint16_t TXMin=8;    // Position Left Terminal
//uint16_t TYMin=78;  
//// Attension les données 'Width' et 'Height' sont inversées car elles sont placées dans les Max pendant la compilation , donc avant la rotate dans l'init
//// Je les déclarent donc en DUR pour la compil en mode portrait
//uint16_t TXMax=480;//-TXMin;//my_lcd.Get_Display_Width()-1-TXMin; // Taille de terminal en pixel
//uint16_t TYMax=320;//-TYMin;//my_lcd.Get_Display_Height()-10-TYMin;


boolean TerminalSizeSet(struct TTerm T) //TerminalSizeSet(TermDefault);
{ // Provoque un "reset" du terminal , renvoie false si les dimensions sortent de l'écran
  if(T.x<tft.width() )       TXMin=T.x; else return(false);
  if(T.y<tft.height())       TYMin=T.y; else return(false);
  if((T.x+T.w)<tft.width() ) TXMax=T.x+T.w; else {TXMax=tft.width(); return(false);}
  if((T.y+T.h)<tft.height()) TYMax=T.y+T.h; else {TYMax=tft.height();return(false);}
  TerminalClear();
  
  //Tsize=Size ; TFtColor=Color;
  tft.setTextColor(IHM_GRAY,IHM_BLACK); 

  tft.drawRect(TXMin-1,TYMin-1,(TXMax-TXMin)+2, (TYMax-TYMin)+2 , IHM_BLUE);
  return(true);
}

void TerminalClear(){
  tft.setTextColor(IHM_BLACK,IHM_BLACK); 
  tft.fillRect(TXMin,TYMin,TXMax-TXMin, TYMax-TYMin , IHM_BLACK);
  TXpos=TXMin;TYpos=TYMin;
}

uint16_t TerminalGetIndex(struct TSPoint PT,struct TTerm Term,uint8_t Csize){
  //Retourne l'index de ligne du clic 
  // Si le clic est hors du terminal (-1)
  // 
  //Check en premier si le clic est dans le terminal comme avec la fonction de gestion des boutons
  if( ( (PT.x>=Term.x) & (PT.x<=(Term.x+Term.w)) ) &
      ( (PT.y>=Term.y) & (PT.y<=(Term.y+Term.h)) )) 
  {
    //Calcul l'index
    uint16_t In = (PT.y-Term.y)/(_TYsize*Csize);
    return(In+1);      
  }
  return(-1);  
}


void Terminal_ScrollH(uint8_t nb){
 windowScroll2(TXMin, TYMin, TXMax-TXMin, TYMax-TYMin, 0, nb, scrollbuf);
}
void Terminal_ScrollV(uint8_t nb){
 windowScroll2(TXMin, TYMin, TXMax-TXMin, TYMax-TYMin, nb, 0, scrollbuf);
}

void windowScroll2(int16_t x, int16_t y, int16_t wid, int16_t ht, int16_t dx, int16_t dy, uint16_t *buf)
{
//    if (dx) for (int16_t row = 0; row < htht; row++) {
//        //delay(100);
//            READGRAM(x, y + row, buf, wid, 1);
//            tft.setAddrWindow(x, y + row, x + wid - 1, y + row);
//            tft.pushColors(buf + dx, wid - dx, 1);
//            tft.pushColors(buf + 0, dx, 0);
//        }
    if (dx) for (int16_t col = 0; col < ht; col++) {
        //delay(100);
        READGRAM(x , y+col , buf, 1, wid);
            tft.setAddrWindow(x , y+col , x + col, y + ht - 1);
            tft.pushColors(buf + dy, ht - dy, 1);
            tft.pushColors(buf + 0, dy, 0);
        }
    if (dy) for (int16_t col = 0; col < wid; col++) {
        //delay(100);
        READGRAM(x + col, y, buf, 1, ht);
            tft.setAddrWindow(x + col, y, x + col, y + ht - 1);
            tft.pushColors(buf + dy, ht - dy, 1);
            tft.pushColors(buf + 0, dy, 0);
        }
}


#define READGRAM(x, y, buf, w, h)  tft.readGRAM(x, y, buf, w, h)




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DALLE ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Read_Resistive(void)
{
  tp = ts.getPoint();
  pinMode(YP, OUTPUT);      //restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);   //because TFT control pins
  digitalWrite(XM, LOW);
}

bool is_pressed(void)
{
  bool state;
  Read_Resistive();
  state = (tp.z > MINPRESSURE && tp.z < MAXPRESSURE);
  return state;
}

bool is_released(void)
{
  bool state;
  Read_Resistive();
  state = (tp.z > MINPRESSURE && tp.z < MAXPRESSURE);
  return !state;
}
void wait_released(){
  do{}while(is_pressed());
}

void waitForTouch()
{
  while (is_pressed() == true) {}
  while (is_pressed() == false) {}
  while (is_pressed() == true) {}
  wait_released();
}

void waitForTouchAndPrint(){
  PosCursorXY(20,10);
  printStringColor("Touchez la dalle !",IHM_GREEN,2);  
  waitForTouch();    
}

void PTouch_Reset()
{// Reset les variables Touch entre changement de fenetres
  PTouch.x=0;       PTouch.y=0;       PTouchLast.z=0;
  PTouchLast.x=0;   PTouchLast.y=0;   PTouchLast.z=0;
  PTouchLastM0.x=0; PTouchLastM0.y=0; PTouchLastM0.z=0;  
}
