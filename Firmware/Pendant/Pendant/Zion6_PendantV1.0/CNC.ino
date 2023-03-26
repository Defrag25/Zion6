
struct CNC {
  float X=0 , Y=0 , Z=0 ;
  float BRSet      = 400 ;  // Vitesse désirée 
  float BRGet      = 0 ;    // Vitesse réelle retournée par Grbl
  float FEEDSet    = 1000 ; // Vitesse désirée pour un Jog
  float FEEDGet    = 0 ;    // Vitesse réelle retournée par Grbl
  float STEP       = 10 ;
  uint8_t ORGIndex = 0;
  struct TPointGrbl ORG = {0,0} ;    // Index du Tableau Tab  ( 0=G54
  float ORG_Z      = 0 ;    // Index du Tableau Tab  ( 0=G54
  uint8_t ToolSelect = 0;
  uint8_t Status   = 0;
  String State     = "        ";
  uint8_t NbOk     = 0; //Nb de ok recu (juste pour checker si une commande est comprise
  boolean JOGMode  = false;
  boolean ModeAbsRel = 0 ;
}CNC,CNCLast,CNCLastM2;

void CNC_Reset(){
//     buffer_pos = 0;
//     buffer_posToProcess=-1;
  if ( COMM_Control==true)
   { //Autorise la demande d'infos a Grbl
    CNCSerial.println();  
    CNCSerial.println("$X");
   }
}
void CNC_SoftReset(){
  if ( COMM_Control==true)
   {
   CNCSerial.write(0x18);  // Demande info GRBL
   }
}

void CNC_TOTAL_INIT_DEFAULT_CONFIG(){
  CNC_SoftReset();delay(500);
  //CNC_Reset();  delay(1000);
  //CNC_SET_NEW_CONFIG();
//  LoadDefaultConfig("Config.txt",1);
  delay(500);
  CNC_Reset();  delay(500);  //waitForTouchAndPrint();
}

void CNC_Set_AxeXCoef(float CoefX){
  if ( COMM_Control==true)
   {
   CNCSerial.println();
   CNCSerial.print("$100=");   CNCSerial.println(CoefX,0);  delay(50);
   }
  CNC_Reset();  delay(500);
  //waitForTouchAndPrint();
}
void CNC_Set_AxeZCoef(float CoefZ){
  if ( COMM_Control==true)
   {
   CNCSerial.println();
   CNCSerial.print("$102=");   CNCSerial.println(CoefZ,0);  delay(50);
   }
  CNC_Reset();  delay(500);
  //waitForTouchAndPrint();
}

void CNC_Init2()
{
  CNC.X          = 0 ;
  CNC.Y          = 0 ;
  CNC.Z          = 0 ;
  CNC.BRSet      = 400 ;
  CNC.BRGet      = 0 ;
  CNC.FEEDSet    = 1000 ;
  CNC.FEEDGet    = 0 ;
  CNC.STEP       = 10 ;
  CNC.ORGIndex   = 0 ;    // Index de G54
  CNC.ORG        = {0,0};
  CNC.ToolSelect = 0;
  CNC.Status     = 1 ;
  CNC.State      = "----";
  CNC.NbOk       = 0;
  CNC.JOGMode    = false;
  CNC.ModeAbsRel = 0 ; //0:ABS 1:REL
  CNCLast.X      = 0 ; // permet un premier refresh
  CNCLast.Y      = 0 ; // permet un premier refresh
  CNCLast.Z      = 0 ; // permet un premier refresh  
//  EEPROM_TAB_ToolsLoad();  
//  RS232_InitBuffer();
  CNC_Reset();delay(10);
  RS232_InitBuffer();
}


void CNC_ORG_Get(uint8_t Index){
  if (Index==0)    {    CNC.ORG.x=TVal[G54_X]; CNC.ORG.z=TVal[G54_Z];   }
  else             {    CNC.ORG.x=TVal[G55_X]; CNC.ORG.z=TVal[G55_Z];   }
}

void CNCSetPos(float x, float y , float z)
{  CNC.X=x ; CNC.Y= y; CNC.Z= z;// CNC.BR=0;  CNC.FEED = 0 ;  CNC.Status=1;
}

void CNC_SetBRInc( )
{   CNC.BRSet=CNC.BRSet+50; // CNC.FEED = 0 ;  CNC.Status=1;
 if (CNC.BRSet>1000) CNC.BRSet=1000;
 CNC_SetBR(CNC.BRSet);
}

void CNC_SetBRDec( )
{   CNC.BRSet=CNC.BRSet-50; // CNC.FEED = 0 ;  CNC.Status=1;
if (CNC.BRSet<0) {CNC.BRSet=0;}
 CNC_SetBR(CNC.BRSet);
}

void CNC_SetBR( float br)
{   CNC.BRSet=br; // CNC.FEED = 0 ;  CNC.Status=1;
  if ( COMM_Control==true){
 if (CNC.BRSet==0){CNCSerial.println("M5"); }
 else          {CNCSerial.print("M3S");CNCSerial.println(CNC.BRSet,0); }
  }
}

void CNC_Tools_Check(){
    if ( COMM_Control==true)    CNCSerial.println("$#");  // Demande info GRBL
}

void CNC_SET_Step(float Stp){
CNC.STEP=Stp;  
}

void CNC_SET_Feed(float Fd){
CNC.FEEDSet=Fd;  
}

boolean CNC_Check_Step(float f){ //juste pour l'IHM --> renvoie true si le Step correspond est selectionné
  if(CNC.STEP==f) return(true);
  return (false);
}

boolean CNC_Check_Feed(float f){ //juste pour l'IHM --> renvoie true si le Feed correspond est selectionné
  if(CNC.FEEDSet==f) return(true);
  return (false);
}

void CAN_SetFeedStopRestart(float fd){ /////////////////////////////////////////////////////////////////////////////////// TEST
  CNC.FEEDSet = fd ; 
}

void CNC_Resume()               {    if ( COMM_Control==true) {printStringlnColor("Resume",IHM_BLUE,1);CNCSerial.print("~");   }}
void CNC_FeedHold()             {    if ( COMM_Control==true) {printStringlnColor(  "Hold",IHM_BLUE,1);CNCSerial.print("!");   }}
void CNC_FeedOverRideInc10()    {    if ( COMM_Control==true) {printStringlnColor(  "+10%",IHM_BLUE,1);CNCSerial.write(0x91);  }}
void CNC_FeedOverRideDec10()    {    if ( COMM_Control==true) {printStringlnColor(  "-10%",IHM_BLUE,1);CNCSerial.write(0x92);  }}
void CNC_SetFeed(float fd)      {  CNC.FEEDSet = fd ; }
void CNC_SetStatus( uint8_t st) {  CNC.Status=st ; }
//void CNC_CheckGRBL()            {    if ( COMM_Control==true) {printStringColor(     "?",IHM_BLUE,1);Serial.print("?");   }} // Demande info GRBL
void CNC_CheckGRBL()            {    if ( COMM_Control==true) {                                        CNCSerial.print("?");   }} // Demande info GRBL
void CNC_CheckCoordGRBL()       {    if ( COMM_Control==true) {printStringlnColor(    "$#",IHM_BLUE,1);CNCSerial.println("$#");delay(250);}} // Demande info GRBL
void CNC_RequestParameters()    {    if ( COMM_Control==true) {printStringlnColor(    "$$",IHM_BLUE,1);CNCSerial.println("$$");delay(250);}} // Demande info GRBL
void CNC_GRBLSend(char* Cmd)    {    if ( COMM_Control==true) {printStringlnColor(     Cmd,IHM_BLUE,1);CNCSerial.println(Cmd); }}  // Demande info GRBL


/////////////////////////////////
// DEPLACEMENTS
/////////////////////////////////
struct TJog {float x; float y; float z; float FEEDSet ;float Step;}; // Attention (int8 pour déplacement en JOG !)
//const  TJog JogXP={1,0,0,500};
//const  TJog JogXM={-1,0,0,500};
//const  TJog JogZP={0,0,1,500};
//const  TJog JogZM={0,0,-1,500};
const  struct TJog JogXP = {1.000 ,0 ,0 ,1.000 ,1.000};
const  struct TJog JogXM = {-1.000,0 ,0 ,1.000 ,1.000};
const  struct TJog JogZP = {0 ,0 ,1.000 ,1.000 ,1.000};
const  struct TJog JogZM = {0 ,0 ,-1.000,1.000 ,1.000};

void CNC_JOG(struct TJog J){ 
    if ( COMM_Control==true){
  // Mode JOG pour clavier tactile
  // Utilisé pour des deplacements d'un pas constant
  //CNC_JOG(JogZM);
  // Vitesse, JogX,JogZ,Step  
  //Astuce de merde permettant de placer le Step depuis une demande de structure constante
  J.x=CNC.STEP*J.x;
  J.y=CNC.STEP*J.y;
  J.z=CNC.STEP*J.z;
  J.FEEDSet=CNC.FEEDSet*J.FEEDSet;//*((float)(JOY.F)/100);
  if(J.FEEDSet<1)J.FEEDSet=1;
  //J.Step=CNC.STEP*J.Step;
  if((J.x!=0)|(J.y!=0)|(J.z!=0))
  {CNCSerial.print("$J=G91"); 
   if(J.x!=0) {CNCSerial.print("X");CNCSerial.print(J.x,3);}
   if(J.y!=0) {CNCSerial.print("Y");CNCSerial.print(J.y,3);}
   if(J.z!=0) {CNCSerial.print("Z");CNCSerial.print(J.z,3);}
  CNCSerial.print("F");CNCSerial.println(J.FEEDSet); 

  LastJogTime=millis();
  CNC.JOGMode=true;
  }
  }
}

void CNC_JOGPaddle(struct TJog J){
    if ( COMM_Control==true)
    {
  //CNC_JOG(JogZM);
  // Vitesse, JogX,JogZ,Step  
  //Astuce de merde permettant de placer le Step depuis une demande de structure constante
  J.x=CNC.STEP*J.x;
  J.y=CNC.STEP*J.y;
  J.z=CNC.STEP*J.z;
  J.FEEDSet=1+CNC.FEEDSet*J.FEEDSet*((float)(JOY.F)/100);
  J.Step=CNC.STEP*J.Step;
  if((J.x!=0)|(J.y!=0)|(J.z!=0))
  {Serial.print("$J=G91"); 
   if(J.x!=0) {CNCSerial.print("X");CNCSerial.print(J.x,3);}
   if(J.y!=0) {CNCSerial.print("Y");CNCSerial.print(J.y,3);}
   if(J.z!=0) {CNCSerial.print("Z");CNCSerial.print(J.z,3);}
  CNCSerial.print("F");CNCSerial.println(J.FEEDSet); 
  LastJogTime=millis();
  CNC.JOGMode=true;
  }
 }
}

boolean NOJogSinceMillis(long TimeToNoJog)
{ // renvoie true si pas de Jog depuis "TimeToNoJog"
  if ((millis()-LastJogTime)>TimeToNoJog)   { return (true);  }
  else                                      { return (false);  }
  return (true); // never reached
}

void CNC_SET_Zero(){
    if ( COMM_Control==true)  {CNCSerial.println("G92X0Y0Z0");    printStringlnColor("Zero",IHM_BLUE,1);}
}
void CNC_SET_PositionX(float NewX){
     if ( COMM_Control==true) {CNCSerial.print("G92X");CNCSerial.println(NewX,3);}
}
void CNC_SET_PositionZ(float NewZ){
     if ( COMM_Control==true) {CNCSerial.print("G92Z");CNCSerial.println(NewZ,3);}
}

void CNC_MOVEZero(){
    if ( COMM_Control==true)
    {
  CNCSerial.println("G90"); 
  CNCSerial.println("G0X0"); 
  CNCSerial.println("G0Z0"); 
   printStringlnColor("ORG<-",IHM_BLUE,1);
    }
}

void CNC_JOG_STOP(){
    if ( COMM_Control==true)
    {
      
  // Stop le mode JOG
  //Serial.print("!");
  CNC.JOGMode=false; 
 CNCSerial.write(0x85); 
  printStringlnColor("Stop",IHM_BLUE,1);
    }
}

void CNC_PrintAll(){
  printStringColor("X :",IHM_WHITE,1);printFloatColor(CNC.X      ,IHM_GREEN,1,3);printStringln(" ");
  printStringColor("Y :",IHM_WHITE,1);printFloatColor(CNC.Y      ,IHM_GREEN,1,3);printStringln(" ");
  printStringColor("Z :",IHM_WHITE,1);printFloatColor(CNC.Z      ,IHM_GREEN,1,3);printStringln(" ");
  printStringColor("Br:",IHM_WHITE,1);printFloatColor(CNC.BRGet  ,IHM_GREEN,1,3);printStringln(" ");
  printStringColor("Fd:",IHM_WHITE,1);printFloatColor(CNC.FEEDGet,IHM_GREEN,1,3);printStringln(" ");
//  uint8_t p=0;
//  String grblStat="";
//  my_lcd.Print(CNC.State,100,50);
//  ?do{grblStat+=buffer[p];p++;}while ((buffer[p]!=0)&&(p<MAX_BUF));

//  printStringColor("St:",WHITE,1);printStringColor(CNC.State,GREEN,1);printStringln(" ");


}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


struct TPoint  { float X;float Y;float Z;};
const struct TPoint Point0={0,0,0};


void MachinePointPrint(char *Name,struct TPoint P){  // MachinePointPrint("G54",P54)
  //TerminalSizeSet(Terminal2);
  printStringColor("[",IHM_WHITE,1);printStringColor(Name,IHM_BLUE,1);printStringColor(":",IHM_WHITE,1);
  
  printFloatColor(P.X,IHM_GREEN,1,3);printStringColor(",",IHM_WHITE,1);
  printFloatColor(P.Y,IHM_GREEN,1,3);printStringColor(",",IHM_WHITE,1);
  printFloatColor(P.Z,IHM_GREEN,1,3);printStringColor("]",IHM_WHITE,1);
  printStringln(" ");
}



struct TMachine {
        struct TPoint G54; // X,Y,Z
        struct TPoint G55; // 
        struct TPoint G56; // 
        struct TPoint G57; // 
        struct TPoint G58; // 
        struct TPoint G59; // 
        struct TPoint G28; // 
        struct TPoint G30; // 
        struct TPoint G92; // 
        struct TPoint TL0; // 
        struct TPoint PRB; // 
};


struct TMachine Machine0 = { Point0,Point0,Point0,Point0,Point0,
                             Point0,Point0,Point0,Point0,Point0,Point0};


void MachineCoordPrint(struct TMachine M){//MachineCoordPrint(Machine0);
  //TerminalSizeSet(TermMachine);
  MachinePointPrint("G54",M.G54);
  MachinePointPrint("G55",M.G55);
  MachinePointPrint("G56",M.G56);
  MachinePointPrint("G57",M.G57);
  MachinePointPrint("G58",M.G58);
  MachinePointPrint("G59",M.G59);
  MachinePointPrint("G28",M.G28);
  MachinePointPrint("G30",M.G30);
  MachinePointPrint("G92",M.G92);
  MachinePointPrint("TL0",M.TL0);
  MachinePointPrint("PRB",M.PRB);

}

void CNC_SET_NEW_CONFIG1(){ //pour une vis au pas de 4mm
  if ( COMM_Control==true)
  {
// Mini tour CNC
CNCSerial.println("$0=10");     delay(50);
CNCSerial.println("$1=25");     delay(50);
CNCSerial.println("$2=3");      delay(50);
CNCSerial.println("$3=6");      delay(50);
CNCSerial.println("$4=0");      delay(50);
CNCSerial.println("$5=1");      delay(50);
CNCSerial.println("$6=0");      delay(50);
CNCSerial.println("$10=0");     delay(50);
CNCSerial.println("$11=0.010"); delay(50);
CNCSerial.println("$12=0.020"); delay(50);
CNCSerial.println("$13=0");     delay(50);
CNCSerial.println("$20=0");     delay(50);
CNCSerial.println("$21=1");     delay(50);
CNCSerial.println("$22=0");     delay(50);
CNCSerial.println("$23=0");     delay(50);
CNCSerial.println("$24=25");    delay(50);
CNCSerial.println("$25=500");   delay(50);
CNCSerial.println("$26=250");   delay(50);
CNCSerial.println("$27=1.000"); delay(50);
CNCSerial.println("$30=5000");  delay(50);
CNCSerial.println("$31=0");     delay(50);
CNCSerial.println("$32=0");     delay(50);
CNCSerial.println("$40=6");     delay(50);
CNCSerial.println("$100=600");  delay(50);
CNCSerial.println("$101=1000");  delay(50);
CNCSerial.println("$102=800"); delay(50);
CNCSerial.println("$110=1000");  delay(50);
CNCSerial.println("$111=1000");  delay(50);
CNCSerial.println("$112=800"); delay(50);
CNCSerial.println("$120=20");   delay(50);
CNCSerial.println("$121=20");   delay(50);
CNCSerial.println("$122=20");   delay(50);
CNCSerial.println("$130=200");  delay(50);
CNCSerial.println("$131=200");  delay(50);
CNCSerial.println("$132=200");  delay(50);
  }
}

void CNC_SET_NEW_CONFIG2(){ // pour une vis au pas de 2mm
  CNC_SET_NEW_CONFIG1();
 CNCSerial.println("$100=1200");  delay(50);
}

void CNC_SET_NEW_CONFIGAccel1(){ // Acceleration rapide
 CNCSerial.println("$120=20");  delay(50);
 CNCSerial.println("$121=20");  delay(50);
 CNCSerial.println("$122=20");  delay(50);
}
void CNC_SET_NEW_CONFIGAccel2(){ // Acceleration lente
 CNCSerial.println("$120=80");  delay(50);
 CNCSerial.println("$121=80");  delay(50);
 CNCSerial.println("$122=80");  delay(50);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// $10=0 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//<Idle|WPos:-13.412,0.000,-28.753|FS:0,0|Se:0.00>
//<Idle|WPos:-13.412,0.000,-28.753|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//<Idle|WPos:-13.412,0.000,-28.753|FS:0,0|Ov:100,100,100|Se:0.00>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// $10=1 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//<Idle|MPos:0.000,0.000,0.000|FS:0,0|Se:0.00>
//<Idle|MPos:0.000,0.000,0.000|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//<Idle|MPos:0.000,0.000,0.000|FS:0,0|Ov:100,100,100|Se:0.00>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// $10=2 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//<Idle|WPos:-13.412,0.000,-28.753|Bf:13,128|FS:0,0|Se:0.00>
//<Idle|WPos:-13.412,0.000,-28.753|Bf:13,128|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//<Idle|WPos:-13.412,0.000,-28.753|Bf:13,128|FS:0,0|Ov:100,100,100|Se:0.00>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// $10=3 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//<Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|Se:0.00>
//<Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//<Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|Ov:100,100,100|Se:0.00>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// $10=4 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//<Idle|WPos:-13.412,0.000,-28.753|FS:0,0|Se:0.00>
//<Idle|WPos:-13.412,0.000,-28.753|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//<Idle|WPos:-13.412,0.000,-28.753|FS:0,0|Ov:100,100,100|Se:0.00>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// $10=5 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//<Idle|MPos:0.000,0.000,0.000|FS:0,0|Se:0.00>
//<Idle|MPos:0.000,0.000,0.000|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//<Idle|MPos:0.000,0.000,0.000|FS:0,0|Ov:100,100,100|Se:0.00>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// $10=6 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//6// <Idle|WPos:-13.412,0.000,-28.753|Bf:13,128|FS:0,0|Se:0.00>
//6// <Idle|WPos:-13.412,0.000,-28.753|Bf:13,128|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//6// <Idle|WPos:-13.412,0.000,-28.753|Bf:13,128|FS:0,0|Ov:100,100,100|Se:0.00>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// $10=7 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//7// <Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|Se:0.00>
//7// <Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//7// <Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|Ov:100,100,100|Se:0.00>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// $10=8 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//8// <Idle|WPos:-13.412,0.000,-28.753|FS:0,0|Se:0.00>
//8// <Idle|WPos:-13.412,0.000,-28.753|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//8// <Idle|WPos:-13.412,0.000,-28.753|FS:0,0|Ov:100,100,100|Se:0.00>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// $10=8+4+2 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//15// <Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|Se:0.00>
//15// <Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//15// <Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|Ov:100,100,100|Se:0.00>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// $10= valeur de 0 à 8 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//0// <Idle|WPos:-13.412,0.000,-28.753|FS:0,0|Se:0.00>
//0// <Idle|WPos:-13.412,0.000,-28.753|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//0// <Idle|WPos:-13.412,0.000,-28.753|FS:0,0|Ov:100,100,100|Se:0.00>
//1// <Idle|MPos:0.000,0.000,0.000|FS:0,0|Se:0.00>
//1// <Idle|MPos:0.000,0.000,0.000|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//1// <Idle|MPos:0.000,0.000,0.000|FS:0,0|Ov:100,100,100|Se:0.00>
//2// <Idle|WPos:-13.412,0.000,-28.753|Bf:13,128|FS:0,0|Se:0.00>
//2// <Idle|WPos:-13.412,0.000,-28.753|Bf:13,128|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//2// <Idle|WPos:-13.412,0.000,-28.753|Bf:13,128|FS:0,0|Ov:100,100,100|Se:0.00>
//3// <Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|Se:0.00>
//3// <Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//3// <Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|Ov:100,100,100|Se:0.00>
//4// <Idle|WPos:-13.412,0.000,-28.753|FS:0,0|Se:0.00>
//4// <Idle|WPos:-13.412,0.000,-28.753|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//4// <Idle|WPos:-13.412,0.000,-28.753|FS:0,0|Ov:100,100,100|Se:0.00>
//5// <Idle|MPos:0.000,0.000,0.000|FS:0,0|Se:0.00>
//5// <Idle|MPos:0.000,0.000,0.000|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//5// <Idle|MPos:0.000,0.000,0.000|FS:0,0|Ov:100,100,100|Se:0.00>
//6// <Idle|WPos:-13.412,0.000,-28.753|Bf:13,128|FS:0,0|Se:0.00>
//6// <Idle|WPos:-13.412,0.000,-28.753|Bf:13,128|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//6// <Idle|WPos:-13.412,0.000,-28.753|Bf:13,128|FS:0,0|Ov:100,100,100|Se:0.00>
//7// <Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|Se:0.00>
//7// <Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//7// <Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|Ov:100,100,100|Se:0.00>
//8// <Idle|WPos:-13.412,0.000,-28.753|FS:0,0|Se:0.00>
//8// <Idle|WPos:-13.412,0.000,-28.753|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//8// <Idle|WPos:-13.412,0.000,-28.753|FS:0,0|Ov:100,100,100|Se:0.00>
//15//<Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|Se:0.00>
//15//<Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|WCO:13.412,0.000,28.753|Se:0.00>
//15//<Idle|MPos:0.000,0.000,0.000|Bf:13,128|FS:0,0|Ov:100,100,100|Se:0.00>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Principe du Split /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//enum grblStatusValuesIndex 
//     Stat ,    X    ,  Y    ,    Z    , F  , S   , grbl6   , grbl7 ,  grblValLasted}; Avant
//     Stat ,    X    ,  Y    ,    Z    , F  , S   , grbl6   , grbl7 ,  xxxx  , xxx  ,  xx     , xxx  ,  grblValLasted}; Apres
//0// <Idle , -13.412 , 0.000 , -28.753 , 0  , 0   ,  0.00   >
//0// <Idle , -13.412 , 0.000 , -28.753 , 0  , 0   , 13.412  , 0.000 , 28.753 , 0.00 >
//0// <Idle , -13.412 , 0.000 , -28.753 , 0  , 0   ,  100    , 100   , 100    , 0.00 >
//1// <Idle ,   0.000 , 0.000 ,   0.000 , 0  , 0   ,  0.00   >
//1// <Idle ,   0.000 , 0.000 ,   0.000 , 0  , 0   , 13.412  , 0.000 , 28.753 , 0.00 >
//1// <Idle ,   0.000 , 0.000 ,   0.000 , 0  , 0   ,  100    , 100   , 100    , 0.00 >
//2// <Idle , -13.412 , 0.000 , -28.753 , 13 , 128 ,  0      , 0     , 0.00   >
//2// <Idle , -13.412 , 0.000 , -28.753 , 13 , 128 ,  0      , 0     , 13.412 , 0.000 , 28.753 , 0.00 >
//2// <Idle , -13.412 , 0.000 , -28.753 , 13 , 128 ,  0      , 0     , 100    , 100   , 100    , 0.00 >
//3// <Idle ,   0.000 , 0.000 ,   0.000 , 13 , 128 ,  0      , 0     , 0.00   >
//3// <Idle ,   0.000 , 0.000 ,   0.000 , 13 , 128 ,  0      , 0     , 13.412 , 0.000 , 28.753 , 0.00 >
//3// <Idle ,   0.000 , 0.000 ,   0.000 , 13 , 128 ,  0      , 0     , 100    , 100   , 100    , 0.00 >
//4// <Idle , -13.412 , 0.000 , -28.753 , 0  , 0   ,  0.00   >
//4// <Idle , -13.412 , 0.000 , -28.753 , 0  , 0   , 13.412  , 0.000 , 28.753 , 0.00  >
//4// <Idle , -13.412 , 0.000 , -28.753 , 0  , 0   ,  100    , 100   , 100    , 0.00  >
//5// <Idle ,   0.000 , 0.000 ,   0.000 , 0  , 0   ,  0.00   >
//5// <Idle ,   0.000 , 0.000 ,   0.000 , 0  , 0   , 13.412  , 0.000 , 28.753 , 0.00  >
//5// <Idle ,   0.000 , 0.000 ,   0.000 , 0  , 0   ,  100    , 100   , 100    , 0.00  >
//6// <Idle , -13.412 , 0.000 , -28.753 , 13 , 128 ,  0      , 0     , 0.00   >
//6// <Idle , -13.412 , 0.000 , -28.753 , 13 , 128 ,  0      , 0     , 13.412 , 0.000 , 28.753 , 0.00 >
//6// <Idle , -13.412 , 0.000 , -28.753 , 13 , 128 ,  0      , 0     , 100    , 100   ,     100, 0.00 >
//7// <Idle ,   0.000 , 0.000 ,   0.000 , 13 , 128 ,  0      , 0     , 0.00   >
//7// <Idle ,   0.000 , 0.000 ,   0.000 , 13 , 128 ,  0      , 0     , 13.412 , 0.000 ,28.753  , 0.00 >
//7// <Idle ,   0.000 , 0.000 ,   0.000 , 13 , 128 ,  0      , 0     , 100    , 100   ,100     , 0.00 >
//8// <Idle , -13.412 , 0.000 , -28.753 , 0  , 0   ,  0.00   >
//8// <Idle , -13.412 , 0.000 , -28.753 , 0  , 0   , 13.412  , 0.000 , 28.753 , 0.00  >
//8// <Idle , -13.412 , 0.000 , -28.753 , 0  , 0   ,  100    , 100   , 100    , 0.00  >
//15//<Idle ,   0.000 , 0.000 ,   0.000 , 13 , 128 ,  0      , 0     , 0.00   > 
//15//<Idle ,   0.000 , 0.000 ,   0.000 , 13 , 128 ,  0      , 0     , 13.412 , 0.000 , 28.753 , 0.00 >
//15//<Idle ,   0.000 , 0.000 ,   0.000 , 13 , 128 ,  0      , 0     , 100    , 100   , 100    , 0.00 >  













/*
    0x18 (ctrl-x) : Soft-Reset
        Immediately halts and safely resets Grbl without a power-cycle.
        Accepts and executes this command at any time.
        If reset while in motion, Grbl will throw an alarm to indicate position may be lost from the motion halt.
        If reset while not in motion, position is retained and re-homing is not required.
        An input pin is available to connect a button or switch.

    ? : Status Report Query
        Immediately generates and sends back runtime data with a status report.
        Accepts and executes this command at any time, except during a homing cycle and when critical alarm (hard/soft limit error) is thrown.

    ~ : Cycle Start / Resume
        Resumes a feed hold, a safety door/parking state when the door is closed, and the M0 program pause states.
        Command is otherwise ignored.
        If the parking compile-time option is enabled and the safety door state is ready to resume, Grbl will re-enable the spindle and coolant, move back into position, and then resume.
        An input pin is available to connect a button or switch.

    ! : Feed Hold
        Places Grbl into a suspend or HOLD state. If in motion, the machine will decelerate to a stop and then be suspended.
        Command executes when Grbl is in an IDLE, RUN, or JOG state. It is otherwise ignored.
        If jogging, a feed hold will cancel the jog motion and flush all remaining jog motions in the planner buffer. The state will return from JOG to IDLE or DOOR, if was detected as ajar during the active hold.
        By machine control definition, a feed hold does not disable the spindle or coolant. Only motion.
        An input pin is available to connect a button or switch.


Extended-ASCII Realtime Command Descriptions

Grbl v1.1 installed more than a dozen new realtime commands to control feed, rapid, and spindle overrides. To help prevent users from inadvertently altering overrides with a keystroke and allow for more commands later on, all of the new control characters have been moved to the extended ASCII character set. These are not easily type-able on a keyboard, but, depending on the OS, they may be entered using specific keystroke and code. GUI developers will need to be able to send extended ASCII characters, values 128 (0x80) to 255 (0xFF), to Grbl to take advantage of these new features.

    0x84 : Safety Door
        Although typically connected to an input pin to detect the opening of a safety door, this command allows a GUI to enact the safety door behavior with this command.
        Immediately suspends into a DOOR state and disables the spindle and coolant. If in motion, the machine will decelerate to a stop and then be suspended.
        If executed during homing, Grbl will instead halt motion and throw a homing alarm.
        If already in a suspend state or HOLD, the DOOR state supersedes it.
        If the parking compile-time option is enabled, Grbl will park the spindle to a specified location.
        Command executes when Grbl is in an IDLE, HOLD, RUN, HOMING, or JOG state. It is otherwise ignored.
        If jogging, a safety door will cancel the jog and all queued motions in the planner buffer. When the safety door is closed and resumed, Grbl will return to an IDLE state.
        An input pin is available to connect a button or switch, if enabled with a compile-time option.
        Some builds of Grbl v0.9 used the @ character for this command, but it was undocumented. Moved to extended-ASCII to prevent accidental commanding.

    0x85 : Jog Cancel
        Immediately cancels the current jog state by a feed hold and automatically flushing any remaining jog commands in the buffer.
        Command is ignored, if not in a JOG state or if jog cancel is already invoked and in-process.
        Grbl will return to the IDLE state or the DOOR state, if the safety door was detected as ajar during the cancel.

    Feed Overrides
        Immediately alters the feed override value. An active feed motion is altered within tens of milliseconds.
        Does not alter rapid rates, which include G0, G28, and G30, or jog motions.
        Feed override value can not be 10% or greater than 200%.
        If feed override value does not change, the command is ignored.
        Feed override range and increments may be changed in config.h.
        The commands are:
            0x90 : Set 100% of programmed rate.
            0x91 : Increase 10%
            0x92 : Decrease 10%
            0x93 : Increase 1%
            0x94 : Decrease 1%

    Rapid Overrides
        Immediately alters the rapid override value. An active rapid motion is altered within tens of milliseconds.
        Only effects rapid motions, which include G0, G28, and G30.
        If rapid override value does not change, the command is ignored.
        Rapid override set values may be changed in config.h.
        The commands are:
            0x95 : Set to 100% full rapid rate.
            0x96 : Set to 50% of rapid rate.
            0x97 : Set to 25% of rapid rate.

    Spindle Speed Overrides
        Immediately alters the spindle speed override value. An active spindle speed is altered within tens of milliseconds.
        Override values may be changed at any time, regardless of if the spindle is enabled or disabled.
        Spindle override value can not be 10% or greater than 200%
        If spindle override value does not change, the command is ignored.
        Spindle override range and increments may be altered in config.h.
        The commands are:
            0x99 : Set 100% of programmed spindle speed
            0x9A : Increase 10%
            0x9B : Decrease 10%
            0x9C : Increase 1%
            0x9D : Decrease 1%

    0x9E : Toggle Spindle Stop
        Toggles spindle enable or disable state immediately, but only while in the HOLD state.
        The command is otherwise ignored, especially while in motion. This prevents accidental disabling during a job that can either destroy the part/machine or cause personal injury. Industrial machines handle the spindle stop override similarly.
        When motion restarts via cycle start, the last spindle state will be restored and wait 4.0 seconds (configurable) before resuming the tool path. This ensures the user doesn't forget to turn it back on.
        While disabled, spindle speed override values may still be altered and will be in effect once the spindle is re-enabled.
        If a safety door is opened, the DOOR state will supersede the spindle stop override, where it will manage the spindle re-energizing itself upon closing the door and resuming. The prior spindle stop override state is cleared and reset.

    0xA0 : Toggle Flood Coolant
        Toggles flood coolant state and output pin until the next toggle or g-code command alters it.
        May be commanded at any time while in IDLE, RUN, or HOLD states. It is otherwise ignored.
        This override directly changes the coolant modal state in the g-code parser. Grbl will continue to operate normally like it received and executed an M8 or M9 g-code command.
        When $G g-code parser state is queried, the toggle override change will be reflected by an M8 enabled or disabled with an M9 or not appearing when M7 is present.

    0xA1 : Toggle Mist Coolant
        Enabled by ENABLE_M7 compile-time option. Default is disabled.
        Toggles mist coolant state and output pin until the next toggle or g-code command alters it.
        May be commanded at any time while in IDLE, RUN, or HOLD states. It is otherwise ignored.
        This override directly changes the coolant modal state in the g-code parser. Grbl will continue to operate normally like it received and executed an M7 or M9 g-code command.
        When $G g-code parser state is queried, the toggle override change will be reflected by an M7 enabled or disabled with an M9 or not appearing when M8 is present.

.


 */
