//Joystic

//const struct TBouton BP_Joy   = {450,180,50,25};
//struct TJoy { uint16_t X;    uint16_t Z;    uint16_t F; //-100% à 100%
//              uint16_t XAna; uint16_t ZAna;  uint16_t FAna;
//              uint16_t XMin; uint16_t ZMin;  uint16_t FMin;
//              uint16_t XMax; uint16_t ZMax;  uint16_t FMax;};
//struct TJoy JOY={512,512,512,512,512,512,1024,1024,1024,0,0,0};
//struct TJoy JOYLast=JOY;

void IHM_JOY_Init(){
  JOY_TabZInit();
  //pinMode(A8 ,INPUT);
  pinMode(A9 ,INPUT);
  pinMode(A10,INPUT);  

  // JOY=EEPROM_JOY_CalibLoad(); // LOAD From EEPROM
  EEPROM_DirectJOY_CalibLoad();
  JOYLast=JOY;

  // Init des variables d'affichage
  sprintf(JOY2Label,"%d",JOY.F);strcat(JOY2Label,"%");  strcpy(JOY2LabelLast,JOY2Label);
  
  DEBUGSerial.println();
  DEBUGSerial.print("JOY     :");JOY_DEBUGPrintOut(JOY);
  DEBUGSerial.println("Joystic Init Done");
}


////////////////////////////////////////////////////////////////////////////////////
// Filtrage Potentiometre
#define JOY_TABZNbPt 3
uint16_t JOY_TabZ[JOY_TABZNbPt];
uint8_t  JOY_TabZIndex = 0;

void JOY_TabZInit(){
  for (uint8_t i=0 ; i<JOY_TABZNbPt;i++){
    JOY_TabZ[i]=analogRead(A8); delay(1);
  }
  JOY_TabZIndex=0;
}
uint16_t JOY_ZReadFiltered(){
  JOY_TabZ[JOY_TabZIndex++]=analogRead(A8);JOY_TabZIndex%=JOY_TABZNbPt;
  uint16_t Sum=JOY_TabZ[0];
  for (uint8_t i=1 ; i<JOY_TABZNbPt;i++){
    Sum+=JOY_TabZ[i];
  }
  Sum  = Sum / JOY_TABZNbPt;
  return(Sum);  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MENU ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void JOY_Ana_Check(){
  //Lecture du potentiometre et calcul d'une simple moyenne sur 5 echantillons
  JOY.FAna =JOY_ZReadFiltered(); if (JOY.FAna<JOY.FMin) JOY.FMin=JOY.FAna; if (JOY.FAna>JOY.FMax) JOY.FMax=JOY.FAna;  JOY.F=JOY.Offf+map(JOY.FAna,JOY.FMin,JOY.FMax,0,100);
  //JOY.FAna =analogRead(A8);    if (JOY.FAna<JOY.FMin) JOY.FMin=JOY.FAna; if (JOY.FAna>JOY.FMax) JOY.FMax=JOY.FAna;  JOY.F=JOY.Offf+map(JOY.FAna,JOY.FMin,JOY.FMax,100,0);
  JOY.XAna =analogRead(A9);      if (JOY.XAna<JOY.XMin) JOY.XMin=JOY.XAna; if (JOY.XAna>JOY.XMax) JOY.XMax=JOY.XAna;  JOY.X=JOY.Offx+map(JOY.XAna,JOY.XMin,JOY.XMax,-100,+100);
  JOY.ZAna =analogRead(A10);     if (JOY.ZAna<JOY.ZMin) JOY.ZMin=JOY.ZAna; if (JOY.ZAna>JOY.ZMax) JOY.ZMax=JOY.ZAna;  JOY.Z=JOY.Offz+map(JOY.ZAna,JOY.ZMin,JOY.ZMax,-100,+100);
  if ( (JOYLast.XMin!=JOY.XMin) | (JOYLast.ZMin!=JOY.ZMin) | (JOYLast.FMin!=JOY.FMin)) { EEPROM_JOY_CalibSave2(JOY); }
}

void IHM_JOY_Loop(){
  JOY_Ana_Check();
  if (Joystic_Control)
   {
    if (Joystic_Mode==false)
     {
      // if (MenuState==0)  JOY_DrawGraph(); 
      // JOY_Draw(PosJoyDraw);
      // JOY_TFTPrintPos();
      if ((JOY.Z>20) & (JOYLast.Z<20))    {CNC_JOG(JogZP);}
      if ((JOY.Z<-20)& (JOYLast.Z>-20))   {CNC_JOG(JogZM);}
      if ((JOY.X>20) & (JOYLast.X<20))    {CNC_JOG(JogXP);}
      if ((JOY.X<-20)& (JOYLast.X>-20))   {CNC_JOG(JogXM);}
      JOYLast=JOY;
     }
    else //Joystic_Mode==true
     {
      //  //struct TJog {float x; float y; float z; float FEEDSet ;float Step;}; // Attention (int8 pour déplacement en JOG !)
      //  //const  struct TJog JogXP = {1.000 ,0 ,0 ,1.000 ,1.000};

      struct TJog JogTempo = {0 ,0 ,0 ,1.000 ,1.000};
      boolean JoggingOrNot=false;
      if ( abs(JOY.Z)>20 )    { JoggingOrNot=true; JogTempo.z = ((float)(JOY.Z)/50); }  // JOY.Z de (-100:100)  ->   (-2:2) 
      if ( abs(JOY.X)>20 )    { JoggingOrNot=true; JogTempo.x = ((float)(JOY.X)/50); }  // JOY.Z de (-100:100)  ->   (-2:2) 
      if(JoggingOrNot==true)
       {
        JogTempo.FEEDSet= 1+(float)(JOY.F)/50;                           // (1 à 200%)
        CNC.STEP=1;
        CNC_JOG(JogTempo);
        //     delay(10);
       }
      if( CNC.JOGMode==true)
       {
        if (NOJogSinceMillis(100)==true) {CNC_JOG_STOP();} //Serial.println("Stop Jogging");}
       }
     }
   }
}

void JOY_Draw(struct TBouton Pos){
  if((JOYLast.X!=JOY.X)|(JOYLast.Z!=JOY.Z)|(JOYLast.F!=JOY.F)  ) 
   {
   tft.drawCircle(240+JOYLast.X,160+JOYLast.Z,JOYLast.F,IHM_BLACK);
   tft.drawLine(240,160,240+JOYLast.X,160+JOYLast.Z,IHM_BLACK);
   tft.drawLine(240,160,240+JOY.X,160+JOY.Z,IHM_YELLOW);
   tft.drawCircle(240+JOY.X,160+JOY.Z,JOY.F,IHM_BLUE);
   }
}

uint16_t JOY_Graphpos=5; // Variable de position courbes
void JOY_DrawGraph(){
  JOY_Graphpos++;if(JOY_Graphpos>=tft.width()-100)JOY_Graphpos=5;
  tft.drawFastVLine(JOY_Graphpos,76,tft.height()-76-14, IHM_BLACK);
  tft.drawPixel(JOY_Graphpos,200+JOY.X,IHM_BLUE);
  tft.drawPixel(JOY_Graphpos,200+JOY.Z,IHM_GREEN);
  tft.drawPixel(JOY_Graphpos,200-JOY.F,IHM_RED);
  tft.drawPixel(JOY_Graphpos  ,200,IHM_WHITE);
  if ((JOY_Graphpos&0x0008)!=0){tft.drawPixel(JOY_Graphpos  ,200-20,IHM_MAROON);} // Point de trace ligne -20%
  if ((JOY_Graphpos&0x0008)!=0){tft.drawPixel(JOY_Graphpos  ,200+20,IHM_MAROON);} // Point de trace ligne +20%
  if ((JOY_Graphpos&0x0004)!=0){tft.drawPixel(JOY_Graphpos-1,200,   IHM_BLACK);}    // Création pointillé
}

//void JOY_TFTPrintPos()
//{
//  if(JOYLast.F!=JOY.F)
//   {
//
//    tft.setTextSize(2);
//    tft.setCursor(BP_M0ChangeZPos.x-50,BP_M0ChangeZPos.y-5); tft.setTextColor(IHM_BLACK,IHM_BLACK);   tft.print(CNCLast.Z,3);
//    tft.setTextColor(IHM_BLACK,IHM_BLACK);                                                      tft.print(JOY2LabelLast,255,35);  
//    tft.setTextColor(IHM_WHITE,IHM_BLACK); sprintf(JOY2Label,"%d",JOY.F);strcat(JOY2Label,"%"); tft.print(JOY2Label,255,35);  
//    //JOY2LabelLast=strcpy(JOY2LabelLast,JOY2Label);
//    strcpy(JOY2LabelLast,JOY2Label);
//   }
//}

void JOY_DEBUGPrintOut(struct TJoy J){
  DEBUGSerial.print("Calib. [");DEBUGSerial.print(J.XMin);DEBUGSerial.print(" X ");DEBUGSerial.print(J.XMax);DEBUGSerial.print("] [");
                                DEBUGSerial.print(J.ZMin);DEBUGSerial.print(" Z ");DEBUGSerial.print(J.ZMax);DEBUGSerial.print("] [");
                                DEBUGSerial.print(J.FMin);DEBUGSerial.print(" F ");DEBUGSerial.print(J.FMax);DEBUGSerial.println("]");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gestion IHM avec boutons en face avant //
////////////////////////////////////////////
