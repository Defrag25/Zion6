//M18 Aide


//const struct TBouton BP_M18_Chk            = {420, 75, 40, 20};    // Status
// Ouverture de la page d'aide du menu en cours 

const struct TBouton LB_M18              = {  2, 60, 50, 25}; // Label
const struct TBouton LB_M18bis           = { 80, 60, 50, 25}; // Label
const struct TBouton Chk_M18_Scroll      = {465,190, 15,245};


void IHM_Menu18_Init(){
  // Sauvegarde de l'index du menu d'appel
  uint8_t SaveIndex = MenuStateLast;
 MenusInit(    1                       , 3             , 1                    , 1                   , 0                 , MenuBack);
//             Alive Format            , Erase         , PTouch reset         , Print page number   , draw BOT rect     , Menu Back
//              0 : rien                 0 : rien        0 : non                0 : non               0 : non             index
//              1 : petite barre         1 : tout        1 : oui                1 : oui               1 : oui
//              2 : rectangle            2 : TOP
//              3 : Icone deplacement    3 : BOT
//              4 : Efface menu 3


  //IHM_Draw_Label("Aide",LB_M18  ,2,IHM_GRAY,IHM_BLACK,0);
  TerminalSizeSet(TerminalMenu18);

  IHM_Menu18_ButtonRedraw();
  
  IHM_Menu18_SD_ReadHelp(SaveIndex);

 Menu_FirstStart=false;
 DEBUGSerial.println(F("Menu18 (Aide) Init Done"));
 if(SaveIndex!=18){MenuBack=SaveIndex;} else {MenuBack=1;}
}

void IHM_Menu18_ButtonRedraw(){
  Draw_VScrollBar(               "",Chk_M18_Scroll    ,1,IHM_WHITE,     IHM_GRAY,0,10);
} 

void IHM_Menu18_Loop(){
  if (Menu_FirstStart==true)    IHM_Menu18_Init();  
  if(PTouch.z > MINPRESSURE && PTouch.z < MAXPRESSURE)
   {   
        if (IHMCheck(PTouch,Chk_M18_Scroll)==1)      { Draw_VScrollBar( "",Chk_M18_Scroll,1, IHM_WHITE,IHM_GRAY,map(PTouch.y,Chk_M18_Scroll.y-Chk_M18_Scroll.h/2,Chk_M18_Scroll.y+Chk_M18_Scroll.h/2,0,100),10); }
   }
   if ( (IHM_BP10Pressed)  )                      { TerminalSizeSet(TerminalMenu18); }  // CTRL + ESC = AIDE
   if ( (IHM_BP11Pressed)  )                      { Terminal_ScrollH(8); }  
   if ( (IHM_BP12Pressed)  )                      { ; }  
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilitaires
void IHM_Menu18ReadFile(char *Name, uint8_t Csize)
{
  const uint8_t LineCountMax=30;
  uint8_t LineCount=LineCountMax;
  uint16_t SelectColor=IHM_WHITE;
  uint16_t LastColor=IHM_WHITE;
  Tsize=Csize;

  SD.begin(10); 
  File myFile = SD.open(Name);
  if (myFile) 
   {
    while (myFile.available()) 
     {
      char s=myFile.read();
      //delay(100);
      Line[0]=s;      Line[1]=0;
      if ( (s>='0') & (s<='9') &(SelectColor!=IHM_SILVER)) 
       {
        if(SelectColor!=IHM_GOLD)
         {
          LastColor=SelectColor;
          SelectColor=IHM_BLUE; 
         }
       }
      else
       {
        if ( (s==';') | (SelectColor==IHM_SILVER)) 
         {
          SelectColor=IHM_SILVER; 
          if(s==0x0d){ LineCount--;SelectColor=IHM_WHITE; }
         }
        else
         {       
          switch (s)
           {
            case 0x0d : LineCount--;SelectColor=IHM_WHITE; break;
            case '*'  : SelectColor=IHM_RED;break;     
            case ' '  : SelectColor=IHM_WHITE;break;     
            case '('  : SelectColor=IHM_GRAY;break;       // start GREEN
            case ')'  : SelectColor=SelectColor;break;    // stop  GREEN
            case '['  : SelectColor=IHM_GOLD;break;       // start GOLD
            case ']'  : SelectColor=SelectColor;break;    // stop  GOLD
            default   :  SelectColor=SelectColor;
           }
         }        
       }           
      tft.setTextColor(SelectColor);
      TFtColor=SelectColor;
      char t[2];t[0]=s;t[1]=0; printChar(t);
      if (LineCount==0) 
       {
        LineCount=LineCountMax; 
        waitForTouch();
        TerminalClear();
        TXpos=TXMin;
        TYpos=TYMin;
       }       // SCROLLING TEST
                                                        
     }
    myFile.close();
    printStringlnColor("<END>",IHM_GREEN,Csize);
   }
  else 
   {
    printStringColor("Erreur d'ouverture : ",IHM_RED,Csize);printStringColor(Name,IHM_WHITE,Csize);printStringln(" ");
   }  
}

void IHM_Menu18_SD_ReadHelp(uint8_t Index){
  char* Name = "/Help/Menu";
  char msg[20];
  char tmp[4];
  sprintf(tmp,"%d",Index);
  //dtostrf(Index, 0, 0, tmp);
  sprintf(msg, "%s", Name);
  strcat(msg,tmp);
  strcat(msg,".txt");
  IHM_Draw_Label(  "Lecture de : ",LB_M18      ,1,IHM_GRAY  , IHM_BLACK,0);
  IHM_Draw_Label(              msg,LB_M18bis   ,1,IHM_GREEN , IHM_BLACK,0);
  TerminalSizeSet(TerminalMenu18);//TerminalClear();
  IHM_Menu18ReadFile(msg,1);  
}
