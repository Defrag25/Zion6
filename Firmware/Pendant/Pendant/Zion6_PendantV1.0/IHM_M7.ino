//EEPROM

const struct TBouton LB_M7                    = { 10, 60, 50, 25}; // Label

const struct TBouton BP_M7_EEP_BPLoad         = {440, 75, 65, 25};
const struct TBouton BP_M7_EEP_Hex            = {440,110, 65, 25};
const struct TBouton BP_M7_EEP_BPTab          = {440,140, 65, 25};
const struct TBouton BP_M7_RAZSCREEN          = {440,170, 65, 25};
const struct TBouton BP_M7_Data               = {440,200, 65, 25};
const struct TBouton BP_M7_EEP_BPInit         = {440,230, 65, 25};

const struct TBouton BP_M7_REBOOT             = {440,300, 65, 25};
const struct TBouton Chk_M7_Scroll0           = {375,190, 15,225};

void IHM_Menu7_EEP_Print(){
  TerminalClear();;
  uint8_t n;
  for(uint16_t i=0;i<20;i++){
 //   printHexColor(EEPROM.get(i,n),IHM_WHITE,1);printStringln(" ");
  }
}

void IHM_Menu7_EEP_Load(){
 
 TerminalClear();
 printStringln(" ");
 EEPROM_TAB_ToolsLoad();        printStringlnColor("EEPROM TAB Load",IHM_WHITE,1);
 EEPROM_DirectJOY_CalibLoad();  printStringlnColor("EEPROM CALIB Load",IHM_WHITE,1);
 printStringlnColor("Done",IHM_GREEN,1);
 
 waitForTouchAndPrint();
}

void IHM_Menu7_EEP_Tab()
{// Affiche une breve description des variables EEPROM
  float F; 
  TerminalSizeSet(TerminalMenu71);
  printStringlnColor("Outils",IHM_GREEN,1);
  for (uint16_t i=0; i<=7; i++)
   {
    printDecColor(i,IHM_BLUE,1);  printStringColor(":",IHM_BLUE,1);
    F=TVal[i];
    printFloatColor(F,IHM_WHITE,1,3); printStringln(" ");
   }
  printDecColor(8,IHM_BLUE,1); printStringColor(":",IHM_BLUE,1);printStringColor("Step ",IHM_GREEN,1); F=TVal[8];  printFloatColor(F,IHM_WHITE,1,3); printStringln(" ");
  printDecColor(9,IHM_BLUE,1); printStringColor(":",IHM_BLUE,1);printStringColor("Speed ",IHM_GREEN,1); F=TVal[9];  printFloatColor(F,IHM_WHITE,1,3); printStringln(" ");
  printStringColor("(",IHM_GREEN,1); F=TVal[10];  printFloatColor(F,IHM_WHITE,1,3);  printStringColor(":",IHM_BLUE,1);  F=TVal[11];  printFloatColor(F,IHM_WHITE,1,3);  printStringln(")");

  TerminalSizeSet(TerminalMenu72);
  printStringlnColor("Le reste",IHM_GREEN,1);
  for (uint16_t i=12; i<=TabNb; i++)
   {
    printDecColor(i,IHM_BLUE,1);
    printStringColor(":",IHM_BLUE,1);
    F=TVal[i];
    printFloatColor(F,IHM_WHITE,1,3); printStringln(" ");
  }
}
void IHM_Menu7_EEP_Hex()
{// Affichage Hexa
  TerminalSizeSet(TerminalMenu7);
  printStringlnColor("EEPROM",IHM_GREEN,1);
  uint16_t Add=0x0000;
  for (uint16_t j=0 ;j<25;j++)
   {
    Add=16*j;
    printStringColor("0x",IHM_BLUE,1); printHex16Color(Add,IHM_BLUE,1);  printStringColor(":",IHM_BLUE,1);
    for (uint16_t i=0; i<16; i++)
     {
      uint8_t Data8= EEUInt8Read(Add+i);
      printHexColor(Data8,IHM_WHITE,1); if (i<15){printStringColor(" ",IHM_WHITE,1);}
     }
    printStringln(" ");
   }  
}

void IHM_Menu7_EEP_Init(){
 //TerminalClear();
 //printStringln(" ");
 printStringlnColor("EEPROM TotalInit",IHM_WHITE,1);
 //EEUInt16Write(EEPROM_FlagConfOffsetStart,0);//Force une super init
 EEPROMFirstStart(true);     printStringlnColor("EEPROM First Start",IHM_WHITE,1);
 //EEPROM_TAB_ToolsInit2(); printStringlnColor("EEPROM TAB Init",IHM_WHITE,1);
 //EEPROM_JOY_CalibInit(); printStringlnColor("EEPROM CALIB Init",IHM_WHITE,1);
 
 //
 //waitForTouchAndPrint();
  
}

void IHM_Menu7_EEP_Raz(){
 IHM_EraseBOTArea();  
}


void IHM_Menu7_Init(){
   MenusInit(    1                       , 3             , 1                    , 1                   , 1                 , FEN_PARAMS);
//             Alive Format            , Erase         , PTouch reset         , Print page number   , draw BOT rect     , Menu Back
//              0 : rien                 0 : rien        0 : non                0 : non               0 : non             index
//              1 : petite barre         1 : tout        1 : oui                1 : oui               1 : oui
//              2 : rectangle            2 : TOP
//              3 : Icone deplacement    3 : BOT
//              4 : Efface menu 3

  IHM_Draw_Label("EEPROM",LB_M7                 ,2,IHM_GRAY,IHM_BLACK,0);
  IHM_Menu7_RedrawButton();
  Draw_VScrollBar(        "",Chk_M7_Scroll0,1,IHM_WHITE, IHM_GRAY,75,10);
  EEPROM_Taille();
  Menu_FirstStart=false;
  DEBUGSerial.println(F("Menu7 (EEPROM) Init Done"));
}

void IHM_Menu7_RedrawButton()    {
  TerminalSizeSet(TerminalMenu7);
  IHM_Draw_ButtonCenter2("Load"   ,BP_M7_EEP_BPLoad    ,1,IHM_GREEN, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2("Hex"    ,BP_M7_EEP_Hex           ,1,IHM_GREEN, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2("Tab"    ,BP_M7_EEP_BPTab     ,1,IHM_GREEN, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2("Raz"    ,BP_M7_RAZSCREEN     ,1,IHM_GREEN, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2("Data"   ,BP_M7_Data              ,1,IHM_GREEN, IHM_BLUE,5,0);
  
  IHM_Draw_ButtonCenter2("Init"   ,BP_M7_EEP_BPInit    ,1,(EnableParams?IHM_WHITE:IHM_BLACK), (EnableParams?IHM_RED:IHM_GRAY),5,0);//EnableParams
  IHM_Draw_ButtonCenter2("REBOOT" ,BP_M7_REBOOT        ,1,IHM_WHITE, IHM_RED,5,0);
}


void IHM_Menu7EEPROM_WRITE(){

//SaveDep();
//loadDep();
}

void IHM_Menu7_Loop(){
  if (Menu_FirstStart==true)    IHM_Menu7_Init();  
  if(PTouch.z > MINPRESSURE && PTouch.z < MAXPRESSURE)
   {    
    if (IHMCheck(PTouch,BP_Back)==1)   {    MenuState=1;Menu_FirstStart=true;delay(100);}

    if (IHMCheck(PTouch,BP_M7_EEP_BPLoad)==1)  { IHM_Menu7_EEP_Load();IHM_Menu7_Init();  IHM_Menu7_RedrawButton();}
    if (IHMCheck(PTouch,BP_M7_EEP_Hex)==1)         { IHM_Menu7_EEP_Hex(); }
    if (IHMCheck(PTouch,BP_M7_EEP_BPTab)==1)   { IHM_Menu7_EEP_Tab(); }
    if (IHMCheck(PTouch,BP_M7_Data)==1)            { IHM_Menu7EEPROM_WRITE(); }
    if (IHMCheck(PTouch,BP_M7_RAZSCREEN)==1)   { IHM_Menu7_Init();                       IHM_Menu7_RedrawButton();}
    if (IHMCheck(PTouch,BP_M7_REBOOT)==1)      { resetFunc();  }

       //////////////////////////////
       // Activation bouton si Enable Option coché
    if (EnableParams==true)
     {
      if (IHMCheck(PTouch,BP_M7_EEP_BPInit)==1)  { IHM_Menu7_EEP_Init();       IHM_Menu7_RedrawButton();}//IHM_Draw_ButtonCenter2("Init"  ,EEP_BPInit   ,2,GREEN,BLUE ,5,0);       }
     }
    if (IHMCheck(PTouch,Chk_M7_Scroll0)==1)         { Draw_VScrollBar( "",Chk_M7_Scroll0,1, IHM_WHITE,IHM_GRAY,map(PTouch.y,Chk_M7_Scroll0.y-Chk_M7_Scroll0.h/2,Chk_M7_Scroll0.y+Chk_M7_Scroll0.h/2,0,100),10);    }
   
   }
}
