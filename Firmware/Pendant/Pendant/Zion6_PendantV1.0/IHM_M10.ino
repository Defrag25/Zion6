
//PARAMS Machine
#define FEN_PARAMS    10
//const struct TBouton BP_M4CNCReset        = {425,240, 80, 35};
const struct TBouton LB_M10                 = { 10, 54, 50, 25};    // Grbl
const struct TBouton LB_M10_C1              = {270, 55, 60, 20};    // Status
const struct TBouton BP_M10_C1L0            = {300, 75, 60, 20};    // Status
const struct TBouton BP_M10_C1L1            = {300,100, 60, 20};    // $$
const struct TBouton BP_M10_C1L2            = {300,125, 60, 20};    // $#
const struct TBouton BP_M10_C1L3            = {300,150, 60, 20};    // $G
const struct TBouton BP_M10_C1L4            = {300,175, 60, 20};    //$10=0
const struct TBouton BP_M10_C1L5            = {300,200, 60, 20};    //$10=1
const struct TBouton BP_M10_C1L6            = {300,225, 60, 20};
const struct TBouton BP_M10_C1L7            = {300,250, 60, 20};
const struct TBouton BP_M10_C1L8            = {300,275, 60, 20};
const struct TBouton BP_M10_C1L9            = {300,300, 60, 20};

const struct TBouton LB_M10_C2              = {340, 55, 60, 20};
const struct TBouton BP_M10_C2L0            = {370, 75, 60, 20};
const struct TBouton BP_M10_C2L1            = {370,100, 60, 20};
const struct TBouton BP_M10_C2L2            = {370,125, 60, 20};
const struct TBouton BP_M10_C2L3            = {370,150, 60, 20};
const struct TBouton BP_M10_C2L4            = {370,175, 60, 20};
const struct TBouton BP_M10_C2L5            = {370,200, 60, 20};
const struct TBouton BP_M10_C2L6            = {370,225, 60, 20};
const struct TBouton BP_M10_C2L7            = {370,250, 60, 20};
const struct TBouton BP_M10_C2L8            = {370,275, 60, 20};
const struct TBouton BP_M10_C2L9            = {370,300, 60, 20};

const struct TBouton LB_M10_C3              = {410, 55, 50, 20};
const struct TBouton BP_M10_C3L0            = {440, 75, 60, 20};
const struct TBouton BP_M10_C3L1            = {440,100, 60, 20};
const struct TBouton BP_M10_C3L2            = {440,125, 60, 20};
const struct TBouton BP_M10_C3L3            = {440,150, 60, 20};
const struct TBouton BP_M10_C3L4            = {440,175, 60, 20};
const struct TBouton BP_M10_C3L5            = {440,200, 60, 20};
const struct TBouton BP_M10_C3L6            = {440,225, 60, 20};
const struct TBouton BP_M10_C3L7            = {440,250, 60, 20};
const struct TBouton BP_M10_C3L8            = {440,275, 60, 20};
const struct TBouton BP_M10_C3L9            = {440,300, 60, 20};



const struct TBouton Chk_M10DEBUG           = {210,100, 10, 10};  //
const struct TBouton Chk_M10CURSOR          = {210,115, 10, 10};  //
const struct TBouton Chk_M10DRAW_COORD      = {210,130, 10, 10};
const struct TBouton Chk_M10DRAW_ORG        = {210,145, 10, 10};
const struct TBouton Chk_M10JoyAna          = {210,160, 10, 10};
const struct TBouton Chk_M10JoyMode         = {210,175, 10, 10};
const struct TBouton Chk_M10_6              = {210,190, 10, 10};
const struct TBouton Chk_M10_7              = {210,205, 10, 10};
const struct TBouton Chk_M10_8              = {210,220, 10, 10};
const struct TBouton Chk_M10_9              = {210,235, 10, 10};
const struct TBouton Chk_M10_10             = {210,250, 10, 10};
const struct TBouton Chk_M10_11             = {210,265, 10, 10};
const struct TBouton Chk_M10_12             = {210,280, 10, 10};
 

const struct TPoint P1={12,-11.2,45};
struct TMachine M1 = Machine0;

void IHM_Menu10_Init(){
 MenusInit(    1                       , 3             , 1                    , 1                   , 0                 , 1);
//             Alive Format            , Erase         , PTouch reset         , Print page number   , draw BOT rect     , Menu Back
//              0 : rien                 0 : rien        0 : non                0 : non               0 : non             index
//              1 : petite barre         1 : tout        1 : oui                1 : oui               1 : oui
//              2 : rectangle            2 : TOP
//              3 : Icone deplacement    3 : BOT
//              4 : Efface menu 3
  MenuIndexSelect=1;MenuIndexSelectMax=33; // Nombre de bouton Indexables par le clavier
  RainColor=0;
  TerminalSizeSet(TerminalMenu10);
  IHM_Menu10_ButtonRedraw();
  IHM_Menu10_RedrawCheckBox();
  Menu_FirstStart=false;
  PrintVersion();
  DEBUGSerial.println(F("Menu10 Init Done"));
}



void IHM_Menu10_ButtonRedraw(){
    
  IHM_Draw_Label(      "Parametres",LB_M10            ,1,IHM_GRAY,IHM_BLACK,0);

  IHM_Draw_Label(            "Grbl",LB_M10_C1         ,1,IHM_GRAY , IHM_BLACK,0);
  IHM_Draw_ButtonCenter2(       "-",BP_M10_C1L0       ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(  "Status",BP_M10_C1L1       ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(      "$$",BP_M10_C1L2       ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(      "$G",BP_M10_C1L3       ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(       "-",BP_M10_C1L4       ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(       "BIG",BP_M10_C1L5       ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(       "-",BP_M10_C1L6       ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(       "-",BP_M10_C1L7       ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(       "-",BP_M10_C1L8       ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(       "-",BP_M10_C1L9       ,1,IHM_WHITE, IHM_BLUE,5,0);

  IHM_Draw_Label(          "System",LB_M10_C2         ,1,IHM_GRAY , IHM_BLACK,0);
  IHM_Draw_ButtonCenter2(     "IHM",BP_M10_C2L0       ,1,IHM_BLACK, IHM_GREEN,5,0);
  IHM_Draw_ButtonCenter2(    "Comm",BP_M10_C2L1       ,1,IHM_BLACK, IHM_GREEN,5,0);
  IHM_Draw_ButtonCenter2( "JOYstic",BP_M10_C2L2       ,1,IHM_BLACK, IHM_GREEN,5,0);
  IHM_Draw_ButtonCenter2(   "Calib",BP_M10_C2L3       ,1,IHM_BLACK, IHM_GREEN,5,0);
  IHM_Draw_ButtonCenter2(  "EEPROM",BP_M10_C2L4       ,1,IHM_BLACK, IHM_GREEN,5,0);
  IHM_Draw_ButtonCenter2("CheckBox",BP_M10_C2L5       ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2( "Yopla()",BP_M10_C2L6       ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(    "Boom",BP_M10_C2L7       ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(   "Ouups",BP_M10_C2L8       ,1,IHM_WHITE, IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(    "Aide",BP_M10_C2L9       ,1,IHM_WHITE, IHM_BLUE,5,0);

  IHM_Draw_Label(          "config",LB_M10_C3         ,1,IHM_GRAY , IHM_BLACK,0);
  IHM_Draw_ButtonCenter2(       "-",BP_M10_C3L0       ,1,IHM_GRAY , IHM_BLACK,5,0);
  IHM_Draw_ButtonCenter2(   "$10=0",BP_M10_C3L1       ,1,(EnableParams?IHM_WHITE:IHM_BLACK), (EnableParams?IHM_RED:IHM_GRAY),5,0);//EnableParams
  IHM_Draw_ButtonCenter2(   "$10=1",BP_M10_C3L2       ,1,(EnableParams?IHM_WHITE:IHM_BLACK), (EnableParams?IHM_RED:IHM_GRAY),5,0);//EnableParams
  IHM_Draw_ButtonCenter2(   "$10=2",BP_M10_C3L3       ,1,(EnableParams?IHM_WHITE:IHM_BLACK), (EnableParams?IHM_RED:IHM_GRAY),5,0);//EnableParams
  IHM_Draw_ButtonCenter2("A Rapide",BP_M10_C3L4       ,1,(EnableParams?IHM_WHITE:IHM_BLACK), (EnableParams?IHM_RED:IHM_GRAY),5,0);//EnableParams
  IHM_Draw_ButtonCenter2("A Lente ",BP_M10_C3L5       ,1,(EnableParams?IHM_WHITE:IHM_BLACK), (EnableParams?IHM_RED:IHM_GRAY),5,0);//EnableParams
  IHM_Draw_ButtonCenter2(       "-",BP_M10_C3L6       ,1,(EnableParams?IHM_WHITE:IHM_BLACK), (EnableParams?IHM_RED:IHM_GRAY),5,0);//EnableParams
  IHM_Draw_ButtonCenter2("vis P4mm",BP_M10_C3L7       ,1,(EnableParams?IHM_WHITE:IHM_BLACK), (EnableParams?IHM_RED:IHM_GRAY),5,0);//EnableParams
  IHM_Draw_ButtonCenter2("vis P2mm",BP_M10_C3L8       ,1,(EnableParams?IHM_WHITE:IHM_BLACK), (EnableParams?IHM_RED:IHM_GRAY),5,0);//EnableParams
  IHM_Draw_ButtonCenter2(  "REBOOT",BP_M10_C3L9       ,1,(EnableParams?IHM_WHITE:IHM_BLACK), (EnableParams?IHM_RED:IHM_GRAY),5,0);//EnableParams
}

void IHM_Menu10_RedrawCheckBox(){
  EEPROM_CheckBoxStateLoad();
  DrawCheckBox(             "Debug",Chk_M10DEBUG      , IHM_YELLOW , IHM_BLUE   , EnableDEBUG2     ,1);
  DrawCheckBox(            "Cursor",Chk_M10CURSOR     , IHM_YELLOW , IHM_BLUE   , Draw_Cursor      ,1);
  DrawCheckBox(             "Coord",Chk_M10DRAW_COORD , IHM_YELLOW , IHM_BLUE   , EnableDRAWCoord  ,1);
  DrawCheckBox(          "Origines",Chk_M10DRAW_ORG   , IHM_YELLOW , IHM_BLUE   , EnableDrawORG    ,1);
  DrawCheckBox(           "JOY Ana",Chk_M10JoyAna     , IHM_YELLOW , IHM_BLUE   , Joystic_Enabled2 ,1);
  DrawCheckBox(          "JOY Mode",Chk_M10JoyMode    , IHM_YELLOW , IHM_BLUE   , Joystic_Mode     ,1);
  DrawCheckBox(         "Draw Tool",Chk_M10_6         , IHM_YELLOW , IHM_BLUE   , DrawTool         ,1);
  DrawCheckBox(                 "-",Chk_M10_7         , IHM_YELLOW , IHM_BLUE   , Option8          ,1);
  DrawCheckBox(                 "-",Chk_M10_8         , IHM_YELLOW , IHM_BLUE   , Option9          ,1);
  DrawCheckBox(                 "-",Chk_M10_9         , IHM_YELLOW , IHM_BLUE   , Option10         ,1);
  DrawCheckBox(                 "-",Chk_M10_10        , IHM_YELLOW , IHM_BLUE   , Option11         ,1);
  DrawCheckBox(           "Timings",Chk_M10_11        , IHM_YELLOW , IHM_BLUE   , Option12         ,1);
  DrawCheckBox(            "PARAMS",Chk_M10_12        , IHM_YELLOW , IHM_BLUE   , EnableParams     ,1);
}

void IHM_Menu10_CheckAllCheckBox(){
  boolean Refresh=false;
  if (IHMCheckIndex(21,PTouch,Chk_M10DEBUG)==1)      { Refresh=true; if(EnableDEBUG2==true)     EnableDEBUG2=false;      else EnableDEBUG2=true; }
  if (IHMCheckIndex(22,PTouch,Chk_M10CURSOR)==1)     { Refresh=true; if(Draw_Cursor==true)      Draw_Cursor=false;       else Draw_Cursor=true; }
  if (IHMCheckIndex(23,PTouch,Chk_M10DRAW_COORD)==1) { Refresh=true; if(EnableDRAWCoord==true)  EnableDRAWCoord=false;   else EnableDRAWCoord=true; }
  if (IHMCheckIndex(24,PTouch,Chk_M10DRAW_ORG )==1)  { Refresh=true; if(EnableDrawORG==true)    EnableDrawORG=false;     else EnableDrawORG=true; }
  if (IHMCheckIndex(25,PTouch,Chk_M10JoyAna   )==1)  { Refresh=true; if(Joystic_Enabled2==true) Joystic_Enabled2=false;  else Joystic_Enabled2=true; }
  if (IHMCheckIndex(26,PTouch,Chk_M10JoyMode  )==1)  { Refresh=true; if(Joystic_Mode==true)     Joystic_Mode=false;      else Joystic_Mode=true; }
  if (IHMCheckIndex(27,PTouch,Chk_M10_6       )==1)  { Refresh=true; if(DrawTool==true)         DrawTool=false;          else DrawTool=true; }
  if (IHMCheckIndex(28,PTouch,Chk_M10_7       )==1)  { Refresh=true; if(Option8==true)          Option8=false;           else Option8=true; }
  if (IHMCheckIndex(29,PTouch,Chk_M10_8       )==1)  { Refresh=true; if(Option9==true)          Option9=false;           else Option9=true; }
  if (IHMCheckIndex(30,PTouch,Chk_M10_9       )==1)  { Refresh=true; if(Option10==true)         Option10=false;          else Option10=true; }
  if (IHMCheckIndex(31,PTouch,Chk_M10_10      )==1)  { Refresh=true; if(Option11==true)         Option11=false;          else Option11=true; }
  if (IHMCheckIndex(32,PTouch,Chk_M10_11      )==1)  { Refresh=true; if(Option12==true)         Option12=false;          else Option12=true; }
  if (IHMCheckIndex(33,PTouch,Chk_M10_12      )==1)  { Refresh=true; if(EnableParams==true)     EnableParams=false ;     else EnableParams=true; }
  if (Refresh==true) 
   {
    EEPROM_CheckBoxStateSave();    
    IHM_Menu10_RedrawCheckBox();
    wait_released();delay(250);
   }  
}

void IHM_Menu10_LoadConf(uint8_t V){
  if(V==1) {  CNC_SET_NEW_CONFIG1();}
  else     {  CNC_SET_NEW_CONFIG2();}
//  LoadDefaultConfig("Config.txt",1);
}


void TimingStart(){
  if(Option12)
  { Option13=true;
    TXpos=TXMin;TYpos=TYMin;
    TimeStart=micros();
    //TimeStart=millis();
    float Time= (float)(micros()-TimeStart);
    //float Time= (float)(millis()-TimeStart);
    printStringColor("Start :",IHM_WHITE,Csize);printFloatColor(Time,IHM_BLUE,Csize,0);printStringlnColor("us",IHM_WHITE,Csize);
    
  }  
}
void TimingCheckPoint(uint8_t n){
  
  if(Option13)
  {
    float Time= (float)(micros()-TimeStart);
    //float Time= (float)(millis()-TimeStart);
    //printStringColor("Check ",IHM_WHITE,Csize);
    if (n!=0){  printDecColor(n,IHM_GREEN,Csize);
                printStringColor(":",IHM_GREEN,Csize);
             }
    else     {  printStringColor("Stop at ",IHM_WHITE,Csize);
             }
    
    printFloatColor(Time,IHM_BLUE,Csize,0);
    printStringlnColor("us",IHM_WHITE,Csize);
    //TimeStart=millis();
  }  
  if(n==0){Option13=false;} //Stop les checkpoints
}

void IHM_Menu10_TimingsCheck(){
  if(Option12)
  {
    //float Time= (float)(millis()-TimeStart);
    //printStringColor("Temps de boucle :",IHM_WHITE,Csize);printFloatColor(Time,IHM_BLUE,Csize,3);printStringlnColor("ms",IHM_WHITE,Csize);
    //TimeStart=millis();
  }
}


void IHM_Menu10_Loop(){
   boolean NeedToRefresh=false;
  if (Menu_FirstStart==true)    IHM_Menu10_Init();  
  //if(PTouch.z > MINPRESSURE && PTouch.z < MAXPRESSURE)
  // {

     if (IHMCheckIndex(1,PTouch,BP_M10_C1L0)==1)             {                     NeedToRefresh=true; }//
     if (IHMCheckIndex(2,PTouch,BP_M10_C1L1)==1)             { CNC_GRBLSend("?");  NeedToRefresh=true; }//
     if (IHMCheckIndex(3,PTouch,BP_M10_C1L2)==1)             { CNC_GRBLSend("$$"); NeedToRefresh=true; }//
     if (IHMCheckIndex(4,PTouch,BP_M10_C1L3)==1)             { CNC_GRBLSend("$G"); NeedToRefresh=true; }//
     if (IHMCheckIndex(5,PTouch,BP_M10_C1L4)==1)             { SD_Search("/System/Check.txt","JFscan", true);            NeedToRefresh=true; }//
     if (IHMCheckIndex(6,PTouch,BP_M10_C1L5)==1)             { SD_Search("/System/Joystic.txt","JZMax" , true);          NeedToRefresh=true; }//
     if (IHMCheckIndex(7,PTouch,BP_M10_C1L6)==1)             {   //ListeItems();
                                                              NeedToRefresh=true; }//
     if (IHMCheckIndex(8,PTouch,BP_M10_C1L7)==1)             { ; }
     if (IHMCheckIndex(9,PTouch,BP_M10_C1L8)==1)             { ; }
     if (IHMCheckIndex(10,PTouch,BP_M10_C1L9)==1)            { ; }//

     if (IHMCheckIndex(11,PTouch,BP_M10_C2L0)==1)            { MenuState=FEN_IHMBouton;  Menu_FirstStart=true;}
     if (IHMCheckIndex(12,PTouch,BP_M10_C2L1)==1)            { MenuState=FEN_COMM;       Menu_FirstStart=true;}
     if (IHMCheckIndex(13,PTouch,BP_M10_C2L2)==1)            { MenuState=FEN_JOYSTIC;    Menu_FirstStart=true;}
     if (IHMCheckIndex(14,PTouch,BP_M10_C2L3)==1)            { MenuState=FEN_CALIB;      Menu_FirstStart=true;}
     if (IHMCheckIndex(15,PTouch,BP_M10_C2L4)==1)            { MenuState=FEN_EEPROM;     Menu_FirstStart=true;}
     if (IHMCheckIndex(16,PTouch,BP_M10_C2L5)==1)            { DEBUGSerial.print("Free :");SD_Search("/System/Check.txt","CheckBoxVar",true);NeedToRefresh=true; }
     if (IHMCheckIndex(17,PTouch,BP_M10_C2L6)==1)            { Yopla();                  NeedToRefresh=true; }
     if (IHMCheckIndex(18,PTouch,BP_M10_C2L7)==1)            { YoplaBoom();              NeedToRefresh=true; }
     if (IHMCheckIndex(19,PTouch,BP_M10_C2L8)==1)            { Intro();
                                                              Intro2();
                                                              WindowsErase();
                                                             }
     if (IHMCheckIndex(20,PTouch,BP_M10_C2L9)==1)            { MenuState=FEN_HELP;       Menu_FirstStart=true;}


     //////////////////////////////
     // Activation bouton si Enable Option coché
     if (EnableParams==true)
      {
       if (IHMCheck(PTouch,BP_M10_C3L0)==1)            { NeedToRefresh=true; }//
       if (IHMCheck(PTouch,BP_M10_C3L1)==1)            { CNC_GRBLSend("$10=0"); NeedToRefresh=true; }//
       if (IHMCheck(PTouch,BP_M10_C3L2)==1)            { CNC_GRBLSend("$10=1"); NeedToRefresh=true; }//
       if (IHMCheck(PTouch,BP_M10_C3L3)==1)            { CNC_GRBLSend("$10=2"); NeedToRefresh=true; }//
       if (IHMCheck(PTouch,BP_M10_C3L4)==1)            { CNC_SET_NEW_CONFIGAccel1(); NeedToRefresh=true; }// Acceleration rapide
       if (IHMCheck(PTouch,BP_M10_C3L5)==1)            { CNC_SET_NEW_CONFIGAccel2(); NeedToRefresh=true; }// Acceleration lente
       if (IHMCheck(PTouch,BP_M10_C3L6)==1)            { NeedToRefresh=true; }//Coef 
       if (IHMCheck(PTouch,BP_M10_C3L7)==1)            { IHM_Menu10_LoadConf(1); NeedToRefresh=true; }//
       if (IHMCheck(PTouch,BP_M10_C3L8)==1)            { IHM_Menu10_LoadConf(2); NeedToRefresh=true; }//
       if (IHMCheck(PTouch,BP_M10_C3L9)==1)            { resetFunc(); }
      } // if EnableParams
      
     IHM_Menu10_CheckAllCheckBox();
     if (NeedToRefresh==true){delay(250);}
  //} //if PTouch.z > ....     
  IHM_All_MenuIndexCheck();//
  IHM_Menu10_TimingsCheck(); // Check le timing boucle
}

 
// Utilitaire pour calculer la mémoire RAM disponible 
//int freeRam () {
//    extern int __heap_start, *__brkval;
//    int v;
//    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
//}
//#include <malloc.h>
//#include <stdlib.h>
//#include <stdio.h>
//
//extern char _end;
//extern "C" char *sbrk(int i);
//char *ramstart=(char *)0x20070000;
//char *ramend=(char *)0x20088000;
//
//void freeRam2() {
//  char *heapend=sbrk(0);
//  register char * stack_ptr asm ("sp");
//  struct mallinfo mi=mallinfo();
//  DEBUGSerial.print("Dynamic ram used        :"); DEBUGSerial.println(mi.uordblks);
//  DEBUGSerial.print("Program static ram used :"); DEBUGSerial.println(&_end - ramstart);
//  DEBUGSerial.print("Stack ram used          :"); DEBUGSerial.println(ramend - stack_ptr);
//  DEBUGSerial.print("My guess at free mem    :"); DEBUGSerial.println(stack_ptr - heapend + mi.fordblks);
////  char n=malloc(50);
//}
