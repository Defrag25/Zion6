//_JOYSTIC Mode du status CNC

 const struct TBouton BP_M3Xmoins      = {150,175, 90, 50};
 const struct TBouton BP_M3Xplus       = {150,285, 90, 50};
 const struct TBouton BP_M3Zmoins      = { 50,230, 90, 50};
 const struct TBouton BP_M3Zplus       = {250,230, 90, 50};
 const struct TBouton BP_M3STOP        = {150,230, 90, 50};
 //const struct TBouton BP_M3PAUSE       = {250,285, 90, 50};
 //const struct TBouton BP_M3CANCEL      = {350,285, 90, 50};

 const struct TBouton BP_M3BRplus      = { 50,175, 90, 50};
 const struct TBouton BP_M3BRmoins     = { 50,285, 90, 50};

 const struct TBouton LB_Step          = {  5, 60,  0,  0};   // "PAS"
 const struct TBouton BP_StepP001      = { 80, 70, 50, 30};   // 0.001mm
 const struct TBouton BP_StepP01       = {140, 70, 50, 30};   // 0.01mm
 const struct TBouton BP_StepP1        = {200, 70, 50, 30};   // 0.1mm
 const struct TBouton BP_Step1P        = {260, 70, 50, 30};   // 1mm
 const struct TBouton BP_Step10P       = {320, 70, 50, 30};   // 10mm
 const struct TBouton BP_StepVar       = {400, 70, 90, 30};   // Position Edit 
 //const struct TBouton BP_StepVarSave   = {465, 70, 25, 30};   // Position Edit 
 const struct TBouton LB_StepUnit      = {  5, 80,  0,  0};   // "mm"
 

 const struct TBouton LB_Speed         = {  5, 95,  0,  0};   // "mm/min"
 const struct TBouton BP_Speed1        = { 80,105, 50, 30};   // 1mm/min
 const struct TBouton BP_Speed10       = {140,105, 50, 30};   // 10mm/min
 const struct TBouton BP_Speed100      = {200,105, 50, 30};   // 100mm/min
 const struct TBouton BP_Speed250      = {260,105, 50, 30};   // 250mm/min
 const struct TBouton BP_Speed500      = {320,105, 50, 30};   // 500mm/min
 //const struct TBouton BP_Speed1000     = {380,105, 50, 30};   // 1000mm/min
 const struct TBouton BP_SpeedVar      = {400,105, 90, 30};   // Speed Edit Pos 
// const struct TBouton BP_SpeedVarSave  = {465,105, 25, 30};   // Position Edit 
 
 const struct TBouton LB_SpeedUnit     = {  5,115,  0,  0};    // "mm/min"

 const struct TBouton BP_M3Zero0       = {430,195, 80, 26};  
 const struct TBouton BP_M3Zero1       = {430,160, 80, 26};
 const struct TBouton BP_M3Zero2       = {430,195, 80, 26};
 const struct TBouton BP_M3CNC_GotoORG = {430,230, 80, 26};
 const struct TBouton BP_M3CNCReset    = {430,265, 80, 26};
 const struct TBouton BP_M3CNC_DefTL0  = {430,150, 80, 26};
 const struct TBouton PictoPos         = {454, 25, 20, 20};


void IHM_Menu3_Init(){
 MenusInit(    3                       , 3             , 1                    , 1                   , 1                 , 1);
//             Alive Format            , Erase         , PTouch reset         , Print page number   , draw BOT rect     , Menu Back
//              0 : rien                 0 : rien        0 : non                0 : non               0 : non             index
//              1 : petite barre         1 : tout        1 : oui                1 : oui               1 : oui
//              2 : rectangle            2 : TOP
//              3 : Icone deplacement    3 : BOT
//              4 : Efface menu 3

  TerminalSizeSet(TerminalMenu3);
  IHM_Menu3_RedrawStepButton();
  IHM_Menu3_RedrawSpeedButton();
  IHM_Draw_ButtonCenter2(    "->0",BP_M3Zero0       ,2,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(  "ORG<-",BP_M3CNC_GotoORG ,2,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(  "Reset",BP_M3CNCReset    ,2,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(  "->TL0",BP_M3CNC_DefTL0  ,2,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(    "BR+",BP_M3BRplus      ,3,IHM_WHITE, IHM_GOLD,5,0);
  IHM_Draw_ButtonCenter2(    "BR-",BP_M3BRmoins     ,3,IHM_WHITE, IHM_GOLD,5,0);
  IHM_Draw_ButtonCenter2(     "X-",BP_M3Xmoins      ,3,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(     "X+",BP_M3Xplus       ,3,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(     "Z-",BP_M3Zmoins      ,3,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(     "Z+",BP_M3Zplus       ,3,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(   "STOP",BP_M3STOP        ,3,IHM_BLUE , IHM_RED ,5,0);
  Menu_FirstStart=false;
  DEBUGSerial.println(F("Menu3 Init Done"));
}


void IHM_Menu3_RedrawStepButton(){ // Version avec init des boutons avec la selection actuelle
   IHM_Draw_Label(             "PAS" ,LB_Step        ,2,IHM_BLUE , IHM_BLACK,0);
   IHM_Draw_ButtonCenter2(    ".001" ,BP_StepP001    ,2,IHM_WHITE, CNC_Check_Step(         0.001)?IHM_GREEN:IHM_BLUE,5,CNC_Check_Step(           0.001));
   IHM_Draw_ButtonCenter2(     ".01" ,BP_StepP01     ,2,IHM_WHITE, CNC_Check_Step(          0.01)?IHM_GREEN:IHM_BLUE,5,CNC_Check_Step(            0.01));
   IHM_Draw_ButtonCenter2(      ".1" ,BP_StepP1      ,2,IHM_WHITE, CNC_Check_Step(           0.1)?IHM_GREEN:IHM_BLUE,5,CNC_Check_Step(             0.1));
   IHM_Draw_ButtonCenter2(       "1" ,BP_Step1P      ,2,IHM_WHITE, CNC_Check_Step(             1)?IHM_GREEN:IHM_BLUE,5,CNC_Check_Step(               1));
   IHM_Draw_ButtonCenter2(      "10" ,BP_Step10P     ,2,IHM_WHITE, CNC_Check_Step(            10)?IHM_GREEN:IHM_BLUE,5,CNC_Check_Step(              10));
// IHM_Draw_ButtonCenter2(     "100" ,BP_Step100P    ,2,IHM_WHITE, CNC_Check_Step(           100)?IHM_GREEN:IHM_BLUE,5,CNC_Check_Step(             100));
   IHM_Draw_EditCenter(TVal[MoveStep],BP_StepVar     ,2,IHM_WHITE, CNC_Check_Step(TVal[MoveStep])?IHM_GREEN:IHM_BLUE,3);

   IHM_Draw_Label(           "(mm)",LB_StepUnit     ,1,IHM_GREEN ,  IHM_BLACK,0);
}

void IHM_Menu3_RedrawSpeedButton(){
   IHM_Draw_Label(           "VIT",LB_Speed       ,2,IHM_BLUE , IHM_BLACK,0);
   IHM_Draw_ButtonCenter2(    "10",BP_Speed1      ,2,IHM_WHITE, CNC_Check_Feed(            10)?IHM_GREEN:IHM_BLUE,5,CNC_Check_Feed(              10));
   IHM_Draw_ButtonCenter2(    "50",BP_Speed10     ,2,IHM_WHITE, CNC_Check_Feed(            50)?IHM_GREEN:IHM_BLUE,5,CNC_Check_Feed(              50));
   IHM_Draw_ButtonCenter2(   "100",BP_Speed100    ,2,IHM_WHITE, CNC_Check_Feed(           100)?IHM_GREEN:IHM_BLUE,5,CNC_Check_Feed(             100));
   IHM_Draw_ButtonCenter2(   "250",BP_Speed250    ,2,IHM_WHITE, CNC_Check_Feed(           250)?IHM_GREEN:IHM_BLUE,5,CNC_Check_Feed(             250));
   IHM_Draw_ButtonCenter2(  "1000",BP_Speed500    ,2,IHM_WHITE, CNC_Check_Feed(          1000)?IHM_GREEN:IHM_BLUE,5,CNC_Check_Feed(            1000));
   //IHM_Draw_EditSimpleCenter(TVal[MoveSpeed],BP_SpeedVar   ,2,IHM_WHITE, CNC_Check_Feed(TVal[MoveSpeed])?IHM_GREEN:IHM_BLUE,CNC_Check_Feed(  TVal[MoveSpeed]));
   IHM_Draw_EditCenter(TVal[MoveSpeed],BP_SpeedVar   ,2,IHM_WHITE, CNC_Check_Feed(TVal[MoveSpeed])?IHM_GREEN:IHM_BLUE,0);
   IHM_Draw_Label(       "(mm/min)",LB_SpeedUnit   ,1,IHM_GREEN,  IHM_BLACK,0);
}

void IHM_Menu3_Loop(){
  boolean NeedToRefresh=false;
  if (Menu_FirstStart==true)    IHM_Menu3_Init();  
  //uint8_t res = CheckRS232_GRBLDataAndParse();
  if(PTouch.z > MINPRESSURE && PTouch.z < MAXPRESSURE)
   {      
    //if (IHMCheck(PTouch,BP_Back)==1)         { MenuState=1;Menu_FirstStart=true ;delay(100);}
  
    if (IHMCheck(PTouch,BP_StepP001)==1)     { CNC_SET_Step(0.001);  NeedToRefresh=true;}//
    if (IHMCheck(PTouch,BP_StepP01)==1)      { CNC_SET_Step(0.01);   NeedToRefresh=true;}//
    if (IHMCheck(PTouch,BP_StepP1)==1)       { CNC_SET_Step(0.1);    NeedToRefresh=true;}//
    if (IHMCheck(PTouch,BP_Step1P)==1)       { CNC_SET_Step(1);      NeedToRefresh=true;}//
    if (IHMCheck(PTouch,BP_Step10P)==1)      { CNC_SET_Step(10);     NeedToRefresh=true;}//
    if (IHMCheck(PTouch,BP_StepVar)==1)      { 
                                              if(TVal[MoveStep]==CNC.STEP)
                                               {  //Modification de la valeur                                              
                                                 MenuStateLast=3;
                                                 MenuState=IndexClavierNum;
                                                 Val=TVal[MoveStep];
                                                 CNC_SET_Step(Val);
                                                 TValIndex=MoveStep;
                                                 strcpy(Text,"");
                                                 //sprintf(Text,"%d",TVal[MoveStep]);
                                                 Menu_FirstStart=true;
                                               }  
                                              else
                                               { // Sinon sélection
                                                CNC_SET_Step(TVal[MoveStep]);
                                                IHM_Menu3_RedrawStepButton();
                                                wait_released();
                                                //NeedToRefresh=true;//
                                               }                                               
                                             }

    if (IHMCheck(PTouch,BP_Speed1)==1)         { CNC_SetFeed(10);     NeedToRefresh=true;}//
    if (IHMCheck(PTouch,BP_Speed10)==1)        { CNC_SetFeed(50);     NeedToRefresh=true;}//
    if (IHMCheck(PTouch,BP_Speed100)==1)       { CNC_SetFeed(100);    NeedToRefresh=true;}//
    if (IHMCheck(PTouch,BP_Speed250)==1)       { CNC_SetFeed(250);    NeedToRefresh=true;}//
    if (IHMCheck(PTouch,BP_Speed500)==1)       { CNC_SetFeed(1000);   NeedToRefresh=true;}//
    if (IHMCheck(PTouch,BP_SpeedVar)==1)        { 
                                                 if(TVal[MoveSpeed]==CNC.FEEDSet)
                                                  {//Modification de la valeur                                              
                                                   MenuStateLast=3;
                                                   MenuState=IndexClavierNum;
                                                   Val=TVal[MoveSpeed];
                                                   CNC_SET_Feed(Val);
                                                   TValIndex=MoveSpeed;
                                                   strcpy(Text,"");
                                                   //sprintf(Text,"%d",TVal[MoveStep]);
                                                   Menu_FirstStart=true;
                                                  }  
                                                 else
                                                  { // Sinon sélection
                                                   CNC_SET_Feed(TVal[MoveSpeed]);
                                                   IHM_Menu3_RedrawSpeedButton();
                                                   wait_released();
                                                  }                                                
                                                }

    if (IHMCheck(PTouch,BP_M3Zero0)==1)        { CNC_SET_Zero();      IHM_Draw_ButtonCenter2("->0"     ,BP_M3Zero0      ,2,IHM_WHITE, IHM_BLUE ,5,0); wait_released();}
    //if (IHMCheck(PTouch,BP_M3Zero1)==1)      { CNC_SET_Zero();      IHM_Draw_ButtonCenter2("->1"     ,BP_M3Zero1      ,2,IHM_WHITE, IHM_BLUE ,5,0); }
    //if (IHMCheck(PTouch,BP_M3Zero2)==1)      { CNC_SET_Zero();      IHM_Draw_ButtonCenter2("->2"     ,BP_M3Zero2      ,2,IHM_WHITE, IHM_BLUE ,5,0); }
    if (IHMCheck(PTouch,BP_M3CNC_GotoORG)==1)  { CNC_MOVEZero();      IHM_Draw_ButtonCenter2("ORG<-"   ,BP_M3CNC_GotoORG,2,IHM_WHITE, IHM_BLUE ,5,0); wait_released();}
    if (IHMCheck(PTouch,BP_M3CNCReset)==1)     { CNC_Reset();         IHM_Draw_ButtonCenter2("Reset"   ,BP_M3CNCReset   ,2,IHM_BLACK, IHM_GREEN,5,0); wait_released();}
    if (IHMCheck(PTouch,BP_M3CNC_DefTL0)==1)   
     { // Edition du decalage d'outil TL0
      MenuState=FEN_TOOLS;
      Menu_FirstStart=true;
      TVal[TL0_X]=CNC.X; // Permet de placer la position actuelle dans la definition du decalage TL0
      TVal[TL0_Z]=CNC.Z;
      IHM_Draw_ButtonCenter2("->TL0"   ,BP_M3CNC_DefTL0 ,2,IHM_BLUE,  IHM_GREEN ,5,0);
      wait_released();
      }
    if (IHMCheck(PTouch,BP_M3BRplus)==1)       { CNC_SetBRInc();      wait_released();}
    if (IHMCheck(PTouch,BP_M3BRmoins)==1)      { CNC_SetBRDec();      wait_released();}
    if (IHMCheck(PTouch,BP_M3Xmoins)==1)       { CNC_JOG(JogXM);      delay(200);wait_released();}
    if (IHMCheck(PTouch,BP_M3Xplus)==1)        { CNC_JOG(JogXP);      delay(200);wait_released();}
    if (IHMCheck(PTouch,BP_M3Zmoins)==1)       { CNC_JOG(JogZM);      delay(200);wait_released();}
    if (IHMCheck(PTouch,BP_M3Zplus)==1)        { CNC_JOG(JogZP);      delay(200);wait_released();}
    if (IHMCheck(PTouch,BP_M3STOP)==1)         { CNC_JOG_STOP();      wait_released();}
//    if (IHMCheck(PTouch,BP_M3PAUSE)==1)        { CNC_FeedHold();      delay(200);wait_released();}
//    if (IHMCheck(PTouch,BP_M3CANCEL)==1)       { CNC_Resume();        delay(200);wait_released();}
  
  }
 
  if(NeedToRefresh==true) {IHM_Menu3_RedrawSpeedButton();wait_released();
                           IHM_Menu3_RedrawStepButton();}
}
