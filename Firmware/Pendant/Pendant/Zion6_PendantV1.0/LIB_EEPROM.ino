//Gestion de l'EEPROM
//EEPROM MEGA 4Kb

//#include <EEPROM.h>
//#include <AT24C1024.h>

//#include "EEPROMextent.h"

// Division en plusieurs zones

#define EEPROM_FlagConfOffsetStart 0x0000   // 0xA55A si l'EEPROM est parametree
#define EEPROM_FlagConfOffsetVal   0x0000
#define EEPROM_FlagConfOffsetStop  0x000F

#define EEPROM_TAB_AddOffsetStart  0x0010
// TAB[16] [0x0010-0x004F] (16*float)       | __ = EEFloatRead[i*4]+ EEPROM_JOY_AddOffset
//  T1_X 0x0010      0  // Offset X Tool 1
//  T1_Z 0x0014      1  // 
//  T2_X 0x0018      2  // 
//  T2_Z 0x001C      3  // 
//  T3_X 0x0020      4  // 
//  T3_Z 0x0024      5  // 
//  MoveStep  0x0028      6  // Valeur de deplacement en mode JOG
//  PositionX 0x002C      7  // Valeur de modification position axe X
//  PositionZ 0x0030      8  // Valeur de modification position axe Z
//    -  0x0030      9  //
//    -  0x0034      10 //
//    -  0x0038      11 //
//    -  0x003C      12 //
//    -  0x0040      13 //
//    -  0x0044      14 //
//    -  0x0048      15 //
//    -  0x004C      16 //
//    -  0x0050      17 //
//    -  0x0054      18 //
//    -  0x0058      19 //
//    -  0x005C      20 //
//    -  0x0060      21 //
//    -  0x0064      22 //
//    -  0x0068      23 //
//    -  0x006C      24 //
//    -  0x0070      25 //
//    -  0x0074      26 //
//    -  0x0078      27 //
//    -  0x007C      28 //
//    -  0x0080      29 //

#define EEPROM_TAB_AddOffsetEnd   0x00FF

#define EEPROM_JOY_AddOffsetStart 0x0100
// JOY[6] [0x0100-0x005F] (8*uint16)          | __ = EEFloatRead[i*2]+ EEPROM_JOY_AddOffset
//  XMin 0x0100      0  // XMin Calibration manche X
//  ZMin 0x0102      1  // ZMin         "          Z
//  FMin 0x0104      2  // FMin         "          F
//  XMax 0x0106      3  // XMax         "          X
//  ZMax 0x0108      4  // ZMax         "          Z
//  FMax 0x010A      5  // FMax         "          F
//  Offx 0x010C      6  // Offx Offset Manche X
//  Offz 0x010E      7  // Offz         "     Z 
//  Offf 0x0110      8  // Offf         "     F
//  Fscan 0x0112     9  // Fscan Frequence de scann des JOY
//   -   0x0114        //          "     - 
//   -   0x0116        //          "     - 
//   -   0x0118        //          "     - 
//   -   0x011A        //          "     - 
//   -   0x011C        //          "     - 
//   -   0x011E        //          "     - 
#define EEPROM_JOY_AddOffsetStop  0x011F

//#define EEPROM_CHECKBOX_AddOffsetStart 0x0120  // Data de 16 bits de stockage des CheckBox

#define EEPROM_CheckBoxState      0x0120

//#define EEPROM_CHECKBOX_AddOffsetStop  0x0121

void EEPROM_CheckBoxStateInit(){
// EEPROM_CheckBoxStateSave();
// DEBUGSerial.print("CheckBox Init to ");DEBUGSerial.println(CheckBoxVar);
}


void EEPROM_CheckBoxStateLoad(){
  
  struct TSD_Search Tm=SD_Search("/System/Check.txt","CheckBoxVar",false); if(Tm.Result) { CheckBoxVar=Tm.Value; } else { CheckBoxVar=0; }
  DEBUGSerial.print("CheckBox Load = ");DEBUGSerial.print(highByte(CheckBoxVar),HEX);DEBUGSerial.println(lowByte(CheckBoxVar),HEX);
  
  if((CheckBoxVar & 0b0000000000000001)!=0) {EnableParams=true;}     else {EnableParams=false; }
  if((CheckBoxVar & 0b0000000000000010)!=0) {EnableDEBUG2=true;}     else {EnableDEBUG2=false; }
  if((CheckBoxVar & 0b0000000000000100)!=0) {Draw_Cursor=true;}      else {Draw_Cursor=false; }
  if((CheckBoxVar & 0b0000000000001000)!=0) {EnableDRAWCoord=true;}  else {EnableDRAWCoord=false; }
  if((CheckBoxVar & 0b0000000000010000)!=0) {EnableDrawORG=true;}    else {EnableDrawORG=false; }
  if((CheckBoxVar & 0b0000000000100000)!=0) {Joystic_Enabled2=true;} else {Joystic_Enabled2=false; }
  if((CheckBoxVar & 0b0000000001000000)!=0) {Joystic_Mode=true;}     else {Joystic_Mode=false; }
  if((CheckBoxVar & 0b0000000010000000)!=0) {DrawTool=true;}         else {DrawTool=false; }
  if((CheckBoxVar & 0b0000000100000000)!=0) {Option8=true;}          else {Option8=false; }
  if((CheckBoxVar & 0b0000001000000000)!=0) {Option9=true;}          else {Option9=false; }
  if((CheckBoxVar & 0b0000010000000000)!=0) {Option10=true;}         else {Option10=false; }
  if((CheckBoxVar & 0b0000100000000000)!=0) {Option11=true;}         else {Option11=false; }
  if((CheckBoxVar & 0b0001000000000000)!=0) {Option12=true;}         else {Option12=false; }
}

void EEPROM_CheckBoxStateSave(){
  CheckBoxVar=0;
  if(EnableParams==true)     CheckBoxVar|= 0b0000000000000001;
  if(EnableDEBUG2==true)     CheckBoxVar|= 0b0000000000000010;
  if(Draw_Cursor==true)      CheckBoxVar|= 0b0000000000000100;
  if(EnableDRAWCoord==true)  CheckBoxVar|= 0b0000000000001000;
  if(EnableDrawORG==true)    CheckBoxVar|= 0b0000000000010000;
  if(Joystic_Enabled2==true) CheckBoxVar|= 0b0000000000100000;
  if(Joystic_Mode==true)     CheckBoxVar|= 0b0000000001000000;
  if(DrawTool==true)         CheckBoxVar|= 0b0000000010000000;
  if(Option8==true)          CheckBoxVar|= 0b0000000100000000;
  if(Option9==true)          CheckBoxVar|= 0b0000001000000000;
  if(Option10==true)         CheckBoxVar|= 0b0000010000000000;
  if(Option11==true)         CheckBoxVar|= 0b0000100000000000;
  if(Option12==true)         CheckBoxVar|= 0b0001000000000000;
  IHM_SD_SetCheckBoxConfig();
}


void EEPROMFirstStart(boolean Force){
  // Check le Flag pour voir si les data sont "valides"
  uint16_t i;
  if ((EEUInt16Read(EEPROM_FlagConfOffsetStart)==0xA55A)&(Force == false))
   {
     EEPROM_TAB_ToolsLoad();
     EEPROM_DirectJOY_CalibLoad();    
     EEPROM_CheckBoxStateLoad();
     struct TJoy JOY={512, 512, 512,
                      512, 512, 512,
                        0,   0,   0,
                     1024,1024,1024,
                        0,   0,   0,
                       10};




     DEBUGSerial.println("EEPROM Config Loaded");
   }
  else
   {
     EEPROM_TAB_ToolsInit2();
     EEPROM_JOY_CalibInit2();
     EEPROM_CheckBoxStateInit();
     EEUInt16Write(EEPROM_FlagConfOffsetStart,0xA55A);
     DEBUGSerial.println("First Start Total EEPROM Default Config");
     DEBUGSerial.println("Restart");
     resetFunc();
   }
}

void     EEFloatWrite(uint16_t Add,float f)     {}// EEPROM.put(Add, f);  }
float    EEFloatRead(uint16_t Add)              {}// float f;   return(EEPROM.get(Add,f));  }
void     EEUInt8Write(uint16_t Add,uint8_t i)   {}// EEPROM.write(Add, i);  }
uint8_t  EEUInt8Read(uint16_t Add)              {}// return(EEPROM.read(Add));  }
void     EEUInt16Write(uint16_t Add,uint16_t i) {}// EEPROM.put(Add, i);  }
uint16_t EEUInt16Read(uint16_t Add)             {}// uint16_t i;  return(EEPROM.get(Add,i));  }

  

void EEPROM_Taille(){
  printStringColor("Taille EEPROM : ",IHM_BLUE,1);printDecColor(131072,IHM_GREEN,1);
//  printStringColor("Taille EEPROM : ",IHM_BLUE,1);printDecColor(EEPROM.length(),IHM_GREEN,1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TOOLS
void EEPROM_TAB_ToolsInit2()
{ //Efface la zone data EEPROM 
  for(uint16_t i=0 ; i<=TabNb ; i++)   
   {
    EEFloatWrite(EEPROM_TAB_AddOffsetStart+i*4,0);     
   }  
  DEBUGSerial.println("TAB Tools Init done");
}
      
void  EEPROM_TAB_ToolsLoad()
{ //Lecture des données de l'EEPROM et placement dans le tableau TVal[]
//  for(uint16_t i=0 ; i<=TabNb ; i++)  {   TVal[i]=0;     }
  struct TSD_Search Tm;
 
////////////////////////////
// "/System/Var.txt" //  
  Tm = SD_Search("/System/Var.txt","T1_X" , false);   if(Tm.Result) { TVal[0]=Tm.Value; } //
  Tm = SD_Search("/System/Var.txt","T1_Z" , false);   if(Tm.Result) { TVal[1]=Tm.Value; } //
  Tm = SD_Search("/System/Var.txt","T2_X" , false);   if(Tm.Result) { TVal[2]=Tm.Value; } //
  Tm = SD_Search("/System/Var.txt","T2_Z" , false);   if(Tm.Result) { TVal[3]=Tm.Value; } //
  Tm = SD_Search("/System/Var.txt","T3_X" , false);   if(Tm.Result) { TVal[4]=Tm.Value; } //
  Tm = SD_Search("/System/Var.txt","T3_Z" , false);   if(Tm.Result) { TVal[5]=Tm.Value; } //
  Tm = SD_Search("/System/Var.txt","TL0_X" , false);  if(Tm.Result) { TVal[6]=Tm.Value; } //
  Tm = SD_Search("/System/Var.txt","TL0_Z" , false);  if(Tm.Result) { TVal[7]=Tm.Value; } //
  Tm = SD_Search("/System/Var.txt","G54_X" , false);  if(Tm.Result) { TVal[22]=Tm.Value; } //
  Tm = SD_Search("/System/Var.txt","G54_Z" , false);  if(Tm.Result) { TVal[23]=Tm.Value; } //
  Tm = SD_Search("/System/Var.txt","G55_X" , false);  if(Tm.Result) { TVal[24]=Tm.Value; } //
  Tm = SD_Search("/System/Var.txt","G55_Z" , false);  if(Tm.Result) { TVal[25]=Tm.Value; } //
  DEBUGSerial.println("TAB Tools Loaded");
}

void  EEPROM_TAB_ToolsSave()
{ //Sauve le TVal[] en SD
 const char* FileName="/System/Var.txt";
  SD.remove(FileName);  
  File dataFile = SD.open(FileName, FILE_WRITE);
  if (dataFile)    {  

    dataFile.println("/////////////////////// Version 2");
    dataFile.println("// Variables systeme //");
    dataFile.println("///////////////////////");

    dataFile.print("[T1_X] ");         dataFile.println(TVal[0],3);
    dataFile.print("[T1_Z] ");         dataFile.println(TVal[1],3);
    dataFile.print("[T2_X] ");         dataFile.println(TVal[2],3);
    dataFile.print("[T2_Z] ");         dataFile.println(TVal[3],3);
    dataFile.print("[T3_X] ");         dataFile.println(TVal[4],3);
    dataFile.print("[T3_Z] ");         dataFile.println(TVal[5],3);
    dataFile.print("[TL0_X] ");        dataFile.println(TVal[6],3);
    dataFile.print("[TL0_Z] ");        dataFile.println(TVal[7],3);
    dataFile.print("[MoveStep] ");     dataFile.println(TVal[8],3);
    dataFile.print("[MoveSpeed] ");    dataFile.println(TVal[9],3);
    dataFile.print("[PositionX] ");    dataFile.println(TVal[10],3);
    dataFile.print("[PositionZ] ");    dataFile.println(TVal[11],3);

    dataFile.print("[Pt_FromX] ");     dataFile.println(TVal[12],3);
    dataFile.print("[Pt_FromZ] ");     dataFile.println(TVal[13],3);
    dataFile.print("[Pt_ToX] ");       dataFile.println(TVal[14],3);
    dataFile.print("[Pt_ToZ] ");       dataFile.println(TVal[15],3);
    dataFile.print("[Pt_CentreX] ");   dataFile.println(TVal[16],3);
    dataFile.print("[Pt_CentreZ] ");   dataFile.println(TVal[17],3);

    dataFile.print("[Pt_Feed] ");      dataFile.println(TVal[18],3);
    dataFile.print("[Pt_Repeat] ");    dataFile.println(TVal[19],3);
    dataFile.print("[Pt_Increment] "); dataFile.println(TVal[20],3);
    dataFile.print("[MoveStep2] ");    dataFile.println(TVal[21],3);
    dataFile.print("[G54_X] ");        dataFile.println(TVal[22],3);
    dataFile.print("[G54_Z] ");        dataFile.println(TVal[23],3);
    dataFile.print("[G55_X] ");        dataFile.println(TVal[24],3);
    dataFile.print("[G55_Z] ");        dataFile.println(TVal[25],3);
  
    dataFile.print("[PointX] ");       dataFile.println(TVal[26],3);
    dataFile.print("[PointZ] ");       dataFile.println(TVal[27],3);
    dataFile.print("[ActivPX] ");      dataFile.println(TVal[28],3);
    dataFile.print("[ActivPZ] ");      dataFile.println(TVal[29],3);

    dataFile.close();   
    }
  else             {    DEBUGSerial.print("error opening ");DEBUGSerial.println(FileName);    }

  DEBUGSerial.println("TAB Tools Saved");
}

void  EEPROM_TAB_ToolsPrint()
{ //envoie en DEBUG TVal[] 
  for(uint16_t i=0 ; i<=TabNb ; i++)
   {    EEFloatWrite(EEPROM_TAB_AddOffsetStart+i*4,TVal[i]);     }
  DEBUGSerial.println("TAB Tools Saved");
}

void EEPROM_TAB_MoveStepSave(){
  EEFloatWrite(EEPROM_TAB_AddOffsetStart+MoveStep*4,TVal[MoveStep]);   
}

void EEPROM_TAB_MoveStepLoad(){
  TVal[MoveStep]=EEFloatRead(EEPROM_TAB_AddOffsetStart+MoveStep*4);   
}

void EEPROM_TAB_MoveSpeedSave(){
  EEFloatWrite(EEPROM_TAB_AddOffsetStart+MoveSpeed*4,TVal[MoveSpeed]);   
}

void EEPROM_TAB_MoveSpeedLoad(){
  TVal[MoveSpeed]=EEFloatRead(EEPROM_TAB_AddOffsetStart+MoveSpeed*4);   
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JOY
void  EEPROM_JOY_CalibInit2(){
  struct TJoy J={512, 512, 512,
                   512, 512, 512,
                  1024,1024,1024,
                     0,   0,   0,
                     0,   0,   0,
                    10};
  EEPROM_JOY_CalibSave2(J);
  DEBUGSerial.println("Joystic Calibration Initialisation done");
}

struct TJoy EEPROM_JOY_CalibLoad()
{ //Charge la struct JOY[] de l'EEPROM
  struct TJoy J={512, 512, 512,
                   512, 512, 512,
                  1024,1024,1024,
                     0,   0,   0,
                     0,   0,   0,
                    10};
  J.XMin=EEUInt16Read(EEPROM_JOY_AddOffsetStart+0*2);     
  J.ZMin=EEUInt16Read(EEPROM_JOY_AddOffsetStart+1*2);     
  J.FMin=EEUInt16Read(EEPROM_JOY_AddOffsetStart+2*2);     
  J.XMax=EEUInt16Read(EEPROM_JOY_AddOffsetStart+3*2);     
  J.ZMax=EEUInt16Read(EEPROM_JOY_AddOffsetStart+4*2);     
  J.FMax=EEUInt16Read(EEPROM_JOY_AddOffsetStart+5*2);     
  J.Offx=EEUInt16Read(EEPROM_JOY_AddOffsetStart+6*2);     
  J.Offz=EEUInt16Read(EEPROM_JOY_AddOffsetStart+7*2);     
  J.Offf=EEUInt16Read(EEPROM_JOY_AddOffsetStart+8*2);     
  J.Fscan=EEUInt16Read(EEPROM_JOY_AddOffsetStart+9*2);     

  DEBUGSerial.println("Joystic Calibration Loaded");
  return(J);
}


void EEPROM_DirectJOY_CalibLoad()
{ //Charge la struct JOY[] de la SD
  IHM_SD_Getconfig();
}

void  EEPROM_JOY_CalibSave2(struct TJoy J)
{ //Sauve la sruct JOY[] en SD
  IHM_SD_SetJoysticConfig(J);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gestion dans la SD ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TSD_Search  SD_Search(char *FileName,char *KeyWord, boolean PrintOrNot){
// Recherche et affiche la sous chaine "Keyword" dans le fichier "FileName"
// renvoie : struct TSD_Search { boolean Result; uint16_t Value;};
//struct TSD_Search { boolean Result; float Value; uint16_t Index};
//                    Result : true,false (Keyword trouvé ou pas)
//                    Value  : conversion de la valeur en int
//                    Index  : N° de la ligne où se trouve le Keyword dans le fichier
  struct TSD_Search Temp={false,0,0};
  String SDLine="";
  String StringRes="";
  uint16_t Index=1;
  if(PrintOrNot)  {TerminalSizeSet(TerminalMenu10);  Csize=1;  }
  SD.begin(10); 
  if(PrintOrNot)  { tft.setTextSize(Csize); printStringColor("Lecture de : ",IHM_BLUE,Csize);    printStringlnColor(FileName,IHM_WHITE,Csize); }
  Line[0]=0;
  File myFile = SD.open(FileName);
  if (myFile) 
   {       
    Line[0]=0;     LinePos=0;     Temp.Result=false;
    while (myFile.available() && (Temp.Result==false)) // Permet de sortir quand Keyword trouvé
     {
      char s=myFile.read();
      Line[LinePos++]=s;      
      Line[LinePos]=0;
      if(LinePos>(MAX_CARAC - 1)) { LinePos=0; }
      if (s==0x0d)       
      {
        uint8_t p=0;
        SDLine="";
        //  // Conversion du buffer2 en string
       do{ SDLine+=Line[p];p++; }while ( (Line[p]!=0) && (p<MAX_BUF) );
       //SDLine.toUpperCase();
       if(SDLine.indexOf(KeyWord)>0) { tft.setTextColor(IHM_WHITE); Temp.Index=Index; Temp.Result=true;}
       else                          { tft.setTextColor(IHM_GRAY); }
       Index++;
       if(PrintOrNot) { tft.print(SDLine); }
       LinePos=0;
      }
    }
   
   myFile.close();
   if(Temp.Result)
    {
     
     tft.setTextColor(IHM_WHITE);     
     uint16_t endStatusPos = SDLine.indexOf("]");
     if (endStatusPos!=-1)   
      {
       StringRes=SDLine.substring(endStatusPos+1, SDLine.indexOf(0x0d));
       Temp.Value= StringRes.toFloat();
      }
    }
  } else {
    if(PrintOrNot){ printStringColor("Erreur d'ouverture : ",IHM_RED,Csize); printStringlnColor(FileName,IHM_WHITE,Csize); }
  }
  return(Temp);
}

void IHM_SD_Getconfig(){
  struct TSD_Search Tm;
///////////////////////
// /System/Check.txt //  
  Tm = SD_Search("/System/Check.txt","CheckBoxVar",false); if(Tm.Result) { CheckBoxVar=Tm.Value; } else { CheckBoxVar=0; }//  printStringColor("CheckBoxVar =",IHM_WHITE,Csize);printDecColor(CheckBoxVar,IHM_BLUE,Csize);CRLF();
  printDecColor(millis(),IHM_WHITE,Csize); printStringlnColor(" CheckBox configuration loaded",IHM_GREEN,Csize);
  
////////////////////////////
// "/System/Joystic.txt" //  
  Tm = SD_Search("/System/Joystic.txt","JXMin" , false);  if(Tm.Result) { JOY.XMin=Tm.Value; } else { JOY.XMin=1024; }//
  Tm = SD_Search("/System/Joystic.txt","JZMin" , false);  if(Tm.Result) { JOY.ZMin=Tm.Value; } else { JOY.ZMin=1024; }//
  Tm = SD_Search("/System/Joystic.txt","JFMin" , false);  if(Tm.Result) { JOY.FMin=Tm.Value; } else { JOY.FMin=1024; }//
  Tm = SD_Search("/System/Joystic.txt","JXMax" , false);  if(Tm.Result) { JOY.XMax=Tm.Value; } else { JOY.XMax=0; }//
  Tm = SD_Search("/System/Joystic.txt","JZMax" , false);  if(Tm.Result) { JOY.ZMax=Tm.Value; } else { JOY.ZMax=0; }//
  Tm = SD_Search("/System/Joystic.txt","JFMax" , false);  if(Tm.Result) { JOY.FMax=Tm.Value; } else { JOY.FMax=0; }//
  Tm = SD_Search("/System/Joystic.txt","JOffx" , false);  if(Tm.Result) { JOY.Offx=Tm.Value; } else { JOY.Offx=0; }//
  Tm = SD_Search("/System/Joystic.txt","JOffz" , false);  if(Tm.Result) { JOY.Offz=Tm.Value; } else { JOY.Offz=0; }//
  Tm = SD_Search("/System/Joystic.txt","JOfff" , false);  if(Tm.Result) { JOY.Offf=Tm.Value; } else { JOY.Offf=0; }//
  Tm = SD_Search("/System/Joystic.txt","JFscan", false);  if(Tm.Result) { JOY.Fscan=Tm.Value; } else { JOY.Fscan=10; }//

//  TS2_MINX =TS_MINX;
//  TS2_MAXX =TS_MAXX;
//  TS2_MINY =TS_MINY;
//  TS2_MAXY =TS_MAXX;

//  Tm = SD_Search("/System/Joystic.txt","TXMin", false);  if(Tm.Result)  { TS2_MINX=Tm.Value; } //
//  Tm = SD_Search("/System/Joystic.txt","TXMax", false);  if(Tm.Result)  { TS2_MAXX=Tm.Value; } //
//  Tm = SD_Search("/System/Joystic.txt","TYMin", false);  if(Tm.Result)  { TS2_MINY=Tm.Value; } //
//  Tm = SD_Search("/System/Joystic.txt","TYMax", false);  if(Tm.Result)  { TS2_MAXY=Tm.Value; } //

  printDecColor(millis(),IHM_WHITE,Csize); printStringlnColor(" Joystic calibration loaded",IHM_GREEN,Csize);
}

long SD_Write(boolean CreateOrAdd, char *FileName, char *KeyWord, int16_t Value, boolean PrintOrNot){
// Sauvegarde ou ajout des parametres dans FileName
// CreateOrAdd : true  = creation du fichier
//               false = ajout dans le fichier
// *FileName   : Nom fichier avec chemin
// *KeyWord    : Clef
// Value       : integer
// PrintOrNot  : true  = Affichage
//               false = pas d'affichage
// retourne simplement le temps passé 
  long TimeStart = millis();
  String dataString = "[";
         dataString += KeyWord;
         dataString += "] ";
         dataString += String(Value);
 
  if(CreateOrAdd){SD.remove(FileName);}  
  File dataFile = SD.open(FileName, FILE_WRITE);
  if (dataFile)    {    dataFile.println(dataString);    dataFile.close();   }
  else             {    DEBUGSerial.println("error opening datalog.txt");    }
  return (millis()-TimeStart);
}

long SD_WriteComments(boolean CreateOrAdd, char *FileName, char *Comment, boolean PrintOrNot){
// Sauvegarde ou ajout de commentaires dans FileName
// CreateOrAdd : true  = creation du fichier
//               false = ajout dans le fichier
// *FileName   : Nom fichier avec chemin
// *KeyWord    : Clef
// PrintOrNot  : true  = Affichage
//               false = pas d'affichage
// retourne simplement le temps passé 
  long TimeStart = millis();
  String dataString = ";";
         dataString += Comment;
 
  if(CreateOrAdd){SD.remove(FileName);}  
  File dataFile = SD.open(FileName, FILE_WRITE);
  if (dataFile)    {    dataFile.println(dataString);    dataFile.close();   }
  else             {    DEBUGSerial.print("error opening ");DEBUGSerial.println(FileName);    }
  return (millis()-TimeStart);
}

     
void IHM_SD_Setconfig2(){
  IHM_SD_SetCheckBoxConfig();
  //printFloatColor(millis(),IHM_WHITE,Csize,0); printStringlnColor(" CheckBox configuration saved",IHM_GREEN,Csize);
  IHM_SD_SetJoysticConfig(JOY);
  //printFloatColor(millis(),IHM_WHITE,Csize,0); printStringlnColor(" Joystic calibration saved",IHM_GREEN,Csize);
}

void IHM_SD_SetCheckBoxConfig(){
  const char* FileName="/System/Check.txt";
  SD.remove(FileName);  
  File dataFile = SD.open(FileName, FILE_WRITE);
  if (dataFile)    
   {  
    dataFile.println("////////////// Version 2");
    dataFile.println("// CheckBox //");
    dataFile.println("//////////////");
    dataFile.print("[CheckBoxVar] ");   dataFile.println(CheckBoxVar);
    dataFile.close();   
   }
  else             {    DEBUGSerial.print("error opening ");DEBUGSerial.println(FileName);    }
}

void IHM_SD_SetJoysticConfig(struct TJoy J){
 const char* FileName="/System/Joystic.txt";
//struct TJoy J={ 0,0,0,
//                0,0,0,
//                1024,1024,1024,
//                0,0,0,
//                0,0,0,
//                10  };
  SD.remove(FileName);  
  File dataFile = SD.open(FileName, FILE_WRITE);
  if (dataFile)    {  

    dataFile.println("//////////////////// Version 2");
    dataFile.println("// Joystic Config //");
    dataFile.println("////////////////////");

    dataFile.print("[JXMin] ");   dataFile.println(J.XMin);
    dataFile.print("[JZMin] ");   dataFile.println(J.ZMin);
    dataFile.print("[JFMin] ");   dataFile.println(J.FMin);
    dataFile.print("[JXMax] ");   dataFile.println(J.XMax);
    dataFile.print("[JZMax] ");   dataFile.println(J.ZMax);
    dataFile.print("[JFMax] ");   dataFile.println(J.FMax);
    dataFile.print("[JOffx] ");   dataFile.println(J.Offx);
    dataFile.print("[JOffz] ");   dataFile.println(J.Offz);
    dataFile.print("[JOfff] ");   dataFile.println(J.Offf);
    dataFile.print("[JFscan] ");  dataFile.println(J.Fscan);

    dataFile.println("/////////////////////////////");
    dataFile.println("// Touchscreen calibration //");
    dataFile.println("/////////////////////////////");
    dataFile.print("[TXMin] ");   dataFile.println(TS_MINX);
    dataFile.print("[TXMax] ");   dataFile.println(TS_MAXX);
    dataFile.print("[TYMin] ");   dataFile.println(TS_MINY);
    dataFile.print("[TYMax] ");   dataFile.println(TS_MAXY);
    dataFile.println("/////////////////////////////");
    dataFile.println("//                         //");
    dataFile.println("/////////////////////////////");
    dataFile.close();   
    }
  else             {    DEBUGSerial.print("error opening ");DEBUGSerial.println(FileName);    }
}
