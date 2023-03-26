//Mode Gestion de l'axe Z

const struct TBouton LB_M2                  = { 10, 60, 50, 25};


const struct TBouton BP_M2Xmoins            = {110,225, 60, 30};
const struct TBouton BP_M2Xplus             = {110,295, 60, 30};
const struct TBouton BP_M2Zmoins            = { 45,260, 60, 30};
const struct TBouton BP_M2Zplus             = {175,260, 60, 30};
const struct TBouton BP_M2STOP              = {110,260, 60, 30};

const struct TBouton BP_M2FeedInc10         = {175,225, 60, 30};
const struct TBouton BP_M2FeedDec10         = {175,295, 60, 30};

const struct TBouton BP_M2BROn              = { 45,225, 60, 30};
const struct TBouton BP_M2BROff             = { 45,295, 60, 30};

//const struct TBouton BP_M2CNC_GotoORG       = {420,200,80,40};
//const struct TBouton BP_M2Zero              = {420,150,80,40};
//const struct TBouton BP_M2CNCReset          = {420,80,80,40};
//const struct TBouton BP_M2CNCInit           = {340,80,30,20};

const struct TBouton LB_M2ChangeXPos        = {  5, 85,110, 25};
const struct TBouton LB_M2ChangeZPos        = {  5,115,110, 25};
const struct TBouton LB_M2ChangeFGetPos1    = {  5,150,110, 25};  // FeedRate Get
const struct TBouton LB_M2ChangeFGetPos2    = { 40,150,110, 25};  // FeedRate Get
const struct TBouton LB_M2ChangeFPerPos     = {140,155,110, 25};  // FeedRate Percent
const struct TBouton LB_M2ChangeSGetPos1    = {  5,175,110, 25};
const struct TBouton LB_M2ChangeSGetPos2    = { 40,175,110, 25};

const struct TBouton BP_M2CNCStatus         = {450,125, 50, 20};
const struct TBouton BP_M2CNCReset          = {450,150, 50, 20};
const struct TBouton BP_M2_F                = {450,175, 50, 20};
const struct TBouton BP_M2CNC_GotoORG       = {450,200, 50, 20};
const struct TBouton BP_M2Zero              = {450,225, 50, 20};
const struct TBouton BP_M2_E                = {450,250, 50, 20};
//const struct TBouton BP_M2CNCInit           = {450,275, 50, 20};
//const struct TBouton BP_M2Reboot            = {450,300, 50, 20};


const struct TBouton BP_M2PictoDiam         = {350,200, 30, 30};
const struct TBouton BP_M2PictoDiam2        = {350,250, 30, 30};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IHM 2 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IHM_Menu2_Init(){
 MenusInit(    3                       , 3             , 1                    , 1                   , 1                 , 1);
//             Alive Format            , Erase         , PTouch reset         , Print page number   , draw BOT rect     , Menu Back
//              0 : rien                 0 : rien        0 : non                0 : non               0 : non             index
//              1 : petite barre         1 : tout        1 : oui                1 : oui               1 : oui
//              2 : rectangle            2 : TOP
//              3 : Icone deplacement    3 : BOT
//              4 : Efface menu 3

  CNCLastM2=CNC;
  IHM_Menu2_RedrawButton();
  Menu_FirstStart=false;
  DEBUGSerial.println("Menu2 Init Done");
}

void IHM_Menu2_RedrawButton(){
  IHM_Draw_Label(           "X:", LB_M2ChangeXPos      ,3,IHM_GREEN,IHM_BLACK,0);
  IHM_Draw_Label(           "Z:", LB_M2ChangeZPos      ,3,IHM_GREEN,IHM_BLACK,0);
  IHM_Draw_Label(           "F:", LB_M2ChangeFGetPos1  ,3,IHM_GRAY,IHM_BLACK,0);
  IHM_Draw_Label(           "S:", LB_M2ChangeSGetPos1  ,3,IHM_GRAY,IHM_BLACK,0);

  IHM_Draw_Label(     "Position",LB_M2                 ,2,IHM_GRAY,IHM_BLACK,0);

  IHM_Draw_ButtonCenter2(   "X-",BP_M2Xmoins           ,2,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(   "X+",BP_M2Xplus            ,2,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(   "Z-",BP_M2Zmoins           ,2,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(   "Z+",BP_M2Zplus            ,2,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2( "STOP",BP_M2STOP             ,2,IHM_BLUE , IHM_RED ,5,0);
  IHM_Draw_ButtonCenter2(   "ON",BP_M2BROn             ,2,IHM_GRAY , IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(  "OFF",BP_M2BROff            ,2,IHM_GRAY , IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2( "+10%",BP_M2FeedInc10        ,2,IHM_GRAY , IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2( "-10%",BP_M2FeedDec10        ,2,IHM_GRAY , IHM_BLUE,5,0);

  IHM_Draw_ButtonCenter2( "Status",BP_M2CNCStatus       ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2( "RESET",BP_M2CNCReset         ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2("Params",BP_M2_F               ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2( "ORG<-",BP_M2CNC_GotoORG      ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2( "->0<-",BP_M2Zero             ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2("Buff col",BP_M2_E             ,1,IHM_WHITE, IHM_BLUE,5,0);
  TerminalSizeSet(TerminalMenu2);
  IHM_Menu2_PrintPos();
  IHM_Menu2_FeedPercentPrint();

}

void IHM_Menu2_PrintPos()
{  
  if ((CNC.X!=CNCLastM2.X)||(Menu_FirstStart)==true)
   {tft.setTextSize(3);
    tft.setCursor(LB_M2ChangeXPos.x+35,LB_M2ChangeXPos.y); tft.setTextColor(IHM_BLACK); tft.print(CNCLastM2.X,3);
    tft.setCursor(LB_M2ChangeXPos.x+35,LB_M2ChangeXPos.y); tft.setTextColor(IHM_WHITE); tft.print(CNC.X,3);
    CNCLastM2.X=CNC.X;
   }   

  if ((CNC.Z!=CNCLastM2.Z)||(Menu_FirstStart)==true)
   {tft.setTextSize(3);
    tft.setCursor(LB_M2ChangeZPos.x+35,LB_M2ChangeZPos.y); tft.setTextColor(IHM_BLACK); tft.print(CNCLastM2.Z,3);
    tft.setCursor(LB_M2ChangeZPos.x+35,LB_M2ChangeZPos.y); tft.setTextColor(IHM_WHITE); tft.print(CNC.Z,3);
    CNCLastM2.Z=CNC.Z;
   }   

  if ((CNC.FEEDGet!=CNCLastM2.FEEDGet)|(Menu_FirstStart)==true)
   {tft.setTextSize(3);
    tft.setCursor(LB_M2ChangeFGetPos2.x,LB_M2ChangeFGetPos2.y); tft.setTextColor(IHM_BLACK,IHM_BLACK); tft.print(CNCLastM2.FEEDGet,0);
    tft.setCursor(LB_M2ChangeFGetPos2.x,LB_M2ChangeFGetPos2.y); tft.setTextColor(IHM_WHITE,IHM_BLACK); tft.print(CNC.FEEDGet,0);
    CNCLastM2.FEEDGet=CNC.FEEDGet;
   }   

  if ((CNC.BRGet!=CNCLastM2.BRGet)|(Menu_FirstStart)==true)
   {tft.setTextSize(3);
    tft.setCursor(LB_M2ChangeSGetPos2.x,LB_M2ChangeSGetPos2.y); tft.setTextColor(IHM_BLACK,IHM_BLACK); tft.print(CNCLastM2.BRGet,0);
    tft.setCursor(LB_M2ChangeSGetPos2.x,LB_M2ChangeSGetPos2.y); tft.setTextColor(IHM_WHITE,IHM_BLACK); tft.print(CNC.BRGet,0);
    CNCLastM2.BRGet=CNC.BRGet;
   }   
  IHM_Menu2_FeedPercentPrint();
}


void IHM_Menu2_FeedPercentPrint()
{
  if(JOYLastM2.F!=JOY.F)
   {
    sprintf(JOY2Label,"%d",JOYLastM2.F); strcat(JOY2Label,"%"); IHM_Draw_Label( JOY2Label, LB_M2ChangeFPerPos   ,2,IHM_BLACK,IHM_BLACK,0);
    sprintf(JOY2Label,"%d",JOY.F);       strcat(JOY2Label,"%"); IHM_Draw_Label( JOY2Label, LB_M2ChangeFPerPos   ,2,IHM_GRAY ,IHM_BLACK,0);
    JOYLastM2.F=JOY.F;
   }
}



void IHM_Menu2_Loop(){
  if (Menu_FirstStart==true)    IHM_Menu2_Init();  
  if(PTouch.z > MINPRESSURE && PTouch.z < MAXPRESSURE)
   {      
    boolean NeedToRefresh=false;

    if (IHMCheck(PTouch,BP_M2Xmoins)==1)     { CNC_JOG(JogXM);            NeedToRefresh=true;wait_released();}
    if (IHMCheck(PTouch,BP_M2Xplus)==1)      { CNC_JOG(JogXP);            NeedToRefresh=true;wait_released();}
    if (IHMCheck(PTouch,BP_M2Zero)==1)       { CNC_SET_Zero();            NeedToRefresh=true;wait_released();}
    if (IHMCheck(PTouch,BP_M2Zmoins)==1)     { CNC_JOG(JogZM);            NeedToRefresh=true;wait_released();}
    if (IHMCheck(PTouch,BP_M2Zplus)==1)      { CNC_JOG(JogZP);            NeedToRefresh=true;wait_released();}
    if (IHMCheck(PTouch,BP_M2STOP)==1)       { CNC_JOG_STOP();            NeedToRefresh=true;wait_released();}
    if (IHMCheck(PTouch,BP_M2BROn)==1)       { CNC_SetBR(800);            NeedToRefresh=true;wait_released();}
    if (IHMCheck(PTouch,BP_M2BROff)==1)      { CNC_SetBR(  0);            NeedToRefresh=true;wait_released();}
    if (IHMCheck(PTouch,BP_M2FeedInc10)==1)  { CNC_FeedOverRideInc10();   NeedToRefresh=true;wait_released();}
    if (IHMCheck(PTouch,BP_M2FeedDec10)==1)  { CNC_FeedOverRideDec10();   NeedToRefresh=true;wait_released();}
    
    if (IHMCheck(PTouch,BP_M2CNCStatus)==1)  { CNC_CheckGRBL();           NeedToRefresh=true;}
    if (IHMCheck(PTouch,BP_M2CNCReset )==1)  { CNC_Init2();               NeedToRefresh=true;}
    
    if (IHMCheck(PTouch,BP_M2CNC_GotoORG)==1){ CNC_MOVEZero();            NeedToRefresh=true;}
    if (IHMCheck(PTouch,BP_M2_E)==1)         { RS232_BufferPrintColor0(); NeedToRefresh=true;}
    if (IHMCheck(PTouch,BP_M2_F)==1)         { CNC_RequestParameters();   NeedToRefresh=true;}
    
    if (NeedToRefresh==true) {delay(100);};
   }
    CNC.X=(float)myEnc.read();
    CNC.Z=CNC.Z+0.001;
  IHM_Menu2_PrintPos();
}
