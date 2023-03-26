// MENU DE BASE Menu1


        
#define IndexClavierNum 99
const struct TBouton BP_FEN1         = { 70, 90,120, 48};
#define FEN1 IndexClavierNum    // Calculatrice = Correspondance entre FEN et positionde la page dans la boucle control
const struct TBouton BP_FEN_JOG      = { 70, 90,120, 48};
#define FEN_JOG      3  // Z JOG   
const struct TBouton BP_FEN_POSITION = { 70,145,120, 48};
#define FEN_POSITION 2  // Position  
const struct TBouton BP_FEN_DESSIN   = { 70,200,120, 48};
#define FEN_DESSIN   20 // Dessin  
const struct TBouton BP_FEN_TOOLS    = {200, 90,120, 48};
#define FEN_TOOLS    6  // Tools   
const struct TBouton BP_FEN_SD       = {200,145,120, 48};
#define FEN_SD       90 // SD card
//const struct TBouton BP_FEN_EEPROM   = {420, 80,100, 35};
#define FEN_EEPROM   7  // EEPROM
//const struct TBouton BP_FEN_JOYSTIC  = {420,125,100, 35};
#define FEN_JOYSTIC  8  // Joystic
#define FEN_IHMBouton 81  // IHM Boutons
//const struct TBouton BP_FEN_COMM     = {420,170,100, 35};
#define FEN_COMM     4  // Comm   
const struct TBouton BP_FEN_PARAMS   = {435,275,70, 48};
#define FEN_PARAMS  10  // PARAMS
//const struct TBouton BP_FEN_TEMPLATE = {200,200,120, 48};
//#define FEN_TEMPLATE 50 // Templates
#define FEN_CALIB  19  // Calibration dalle tactile
const struct TBouton BP_ACTIVEJog    = { 70,275,120, 50};
const struct TBouton BP_ACTIVEPower  = {200,275,120, 50};
//const struct TBouton BP_ACTIVEComm   = {330,275,120, 50};
#define FEN_HELP 18  // IHM Aide

//#define TOP 0
//#define BOT 1
//#define YES 1
//#define NO  0
 


 
void IHM_Menu1_Init(){
 MenusInit(    4                       , 3             , 1                    , 1                   , 0                 , 1);
//             Alive Format            , Erase         , PTouch reset         , Print page number   , draw BOT rect     , Menu Back
//              0 : rien                 0 : rien        0 : non                0 : non               0 : non             index
//              1 : petite barre         1 : tout        1 : oui                1 : oui               1 : oui
//              2 : rectangle            2 : TOP
//              3 : Icone deplacement    3 : BOT
//              4 : Efface menu 3
//
   RainColor=0;
   MenuIndexSelect=1;MenuIndexSelectMax=8; // Nombre de bouton Indexables par le clavier
   TerminalSizeSet(TerminalMenu1);
   IHM_Menu1RedrawButton(); 

   Menu_FirstStart=false;
   DEBUGSerial.println("Menu1 Init Done");
}

void IHM_Menu1RedrawButton(){
  if(EnableParams==true)
   {
    IHM_Draw_ButtonCenter2(  "PAR.",BP_FEN_PARAMS   ,2,(EnableParams?IHM_WHITE:IHM_BLACK), (EnableParams?IHM_RED:IHM_GRAY),5,0);//EnableParams
   }
    IHM_Menu1RedrawButtonPowerAndPaddle();
    IHM_Draw_ButtonCenter2( "Z Jog",BP_FEN_JOG      ,3,IHM_WHITE, IHM_BLUE,5,0);
    IHM_Draw_ButtonCenter2(   "CNC",BP_FEN_POSITION ,3,IHM_WHITE, IHM_BLUE,5,0);
    IHM_Draw_ButtonCenter2("Dessin",BP_FEN_DESSIN   ,3,IHM_WHITE, IHM_BLUE,5,0);
    IHM_Draw_ButtonCenter2("Outils",BP_FEN_TOOLS    ,3,IHM_WHITE, IHM_BLUE,5,0);
    IHM_Draw_ButtonCenter2(  "PROG",BP_FEN_SD       ,3,IHM_WHITE, IHM_BLUE,5,0);
    //IHM_Draw_ButtonCenter2("Templ.",BP_FEN_TEMPLATE ,3,IHM_WHITE, IHM_BLUE,0);
}

void IHM_Menu1RedrawButtonPowerAndPaddle(){
    IHM_Draw_ButtonCenter2(  "Paddle",BP_ACTIVEJog   ,2,(Joystic_Control?IHM_BLUE:IHM_GREEN), (Joystic_Control?IHM_RED:IHM_BLUE),5,0);//Joystic_Control
    IHM_Draw_ButtonCenter2(   "POWER",BP_ACTIVEPower ,2,(POWER_Control?  IHM_BLUE:IHM_GREEN), (POWER_Control?  IHM_RED:IHM_BLUE),5,0);//POWER Control  
}

void IHM_Menu1_Loop(){
  if (Menu_FirstStart==true)    IHM_Menu1_Init();  
//  if(PTouch.z > MINPRESSURE && PTouch.z < MAXPRESSURE)
 //  {      
    if (IHMCheckIndex(1,PTouch,BP_FEN_JOG)==1)      {  MenuState=FEN_JOG      ; Menu_FirstStart=true;}
    if (IHMCheckIndex(2,PTouch,BP_FEN_POSITION)==1) {  MenuState=FEN_POSITION ; Menu_FirstStart=true;}
    if (IHMCheckIndex(3,PTouch,BP_FEN_DESSIN)==1)   {  MenuState=FEN_DESSIN   ; Menu_FirstStart=true;}
    if (IHMCheckIndex(4,PTouch,BP_FEN_TOOLS)==1)    {  MenuState=FEN_TOOLS    ; Menu_FirstStart=true;}
    if (IHMCheckIndex(5,PTouch,BP_FEN_SD)==1)       {  MenuState=FEN_SD       ; Menu_FirstStart=true;}
TimingCheckPoint(101);
//    if(COMM_Control==true)
//     {
      if (IHMCheckIndex(6,PTouch,BP_ACTIVEJog)==1)    {  AliveFormat=(Joystic_Control?4:3);
                                                  Joystic_Control=!Joystic_Control;
                                                  if (Joystic_Control==true){POWER_Control=true;}
                                                  IHM_Menu1RedrawButtonPowerAndPaddle();
                                                  delay(250);
                                               }
      if (IHMCheckIndex(7,PTouch,BP_ACTIVEPower)==1)  {  AliveFormat=(Joystic_Control?4:3);
                                                  POWER_Control=!POWER_Control;
                                                  if (POWER_Control==false){Joystic_Control=false;}
                                                  IHM_Menu1RedrawButtonPowerAndPaddle();  ///////////////////////////////////////////////////////////////////////////////////////////////
                                                  delay(250);
                                               }
//     }
//    if (IHMCheck(PTouch,BP_ACTIVEComm)==1)   {  //AliveFormat=(Joystic_Control?4:3);
//                                                COMM_Control=!COMM_Control;
//                                                if (COMM_Control==false){Joystic_Control=false;POWER_Control=false;}
//                                                IHM_Menu1RedrawButtonPowerAndPaddle();
//                                                delay(250);
//                                             }
    //////////////////////////////
    // Activation bouton si Enable Option cochee
    if (EnableParams==true)
     {
      if (IHMCheckIndex(8,PTouch,BP_FEN_PARAMS)==1)  {  MenuState=FEN_PARAMS  ; Menu_FirstStart=true;}//delay(100);}
     }// if EnableParams
 // }//if PTouch.z > ....     
 TimingCheckPoint(102);
 IHM_All_MenuIndexCheck();//
}
 








 
