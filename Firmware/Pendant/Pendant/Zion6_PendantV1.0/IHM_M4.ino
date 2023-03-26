//Mode du Communication


const struct TBouton BP_M4Raz               = {450,125, 50, 20};
const struct TBouton BP_M4PrintBuff         = {450,150, 50, 20};
 
const struct TBouton BP_M4_A                = {450,175, 50, 20};
const struct TBouton BP_M4_B                = {450,200, 50, 20};
const struct TBouton BP_M4_C                = {450,225, 50, 20};
const struct TBouton BP_M4_D                = {450,250, 50, 20};
const struct TBouton BP_M4_E                = {450,275, 50, 20};


//const struct TBouton BP_M4CNCStatus       = {450,250, 50, 20};

const struct TBouton BP_M4CNCReset        = {450,275, 50, 20};
const struct TBouton BP_M4REBOOT          = {450,300, 50, 20};

const struct TBouton LB_M4buffer_pos      = { 20, 65, 50, 20};
const struct TBouton LB_M4posToProcess    = { 70, 65, 50, 20};
const struct TBouton LB_M4inByte          = {130, 65, 50, 20};
const struct TBouton LB_M4buffer_Full     = {180, 65, 50, 20};
const struct TBouton LB_M4NbCmd           = {230, 65, 50, 20};

void IHM_Menu4_Init(){
 MenusInit(    1                       , 3             , 1                    , 1                   , 1                 , FEN_PARAMS);
//             Alive Format            , Erase         , PTouch reset         , Print page number   , draw BOT rect     , Menu Back
//              0 : rien                 0 : rien        0 : non                0 : non               0 : non             index
//              1 : petite barre         1 : tout        1 : oui                1 : oui               1 : oui
//              2 : rectangle            2 : TOP
//              3 : Icone deplacement    3 : BOT
//              4 : Efface menu 3

  TerminalSizeSet(TerminalMenu4);
  IHM_Menu4_RedrawButton();
  Menu_FirstStart=false;
  DEBUGSerial.println(F("Menu4 Init Done"));
  Lastbuffer_pos=buffer_pos-1;                   // Provoque un rafraichissement
  Lastbuffer_posToProcess=buffer_posToProcess-1; // Provoque un rafraichissement
  LastinByte=inByte-1;                           // Provoque un rafraichissement
  Lastbuffer_Full=buffer_Full-1;                 // Provoque un rafraichissement 
  LastNbCmd=NbCmdTest-1;                         // Provoque un rafraichissement
}

void RS232_StatusPrint()
{ // Affichage des data transmisent entre IHM & grbl
    tft.setTextSize(1);
    tft.setTextColor(IHM_WHITE,IHM_BLACK);  
    if(Lastbuffer_pos!=buffer_pos)
     {
      tft.setCursor(LB_M4buffer_pos.x+25,LB_M4buffer_pos.y);tft.setTextColor(IHM_BLACK); tft.print(Lastbuffer_pos);
      tft.setCursor(LB_M4buffer_pos.x+25,LB_M4buffer_pos.y);tft.setTextColor(IHM_WHITE); tft.print(buffer_pos);
     }
    if(Lastbuffer_posToProcess!=buffer_posToProcess)
     {
      tft.setCursor(LB_M4posToProcess.x+25,LB_M4posToProcess.y);tft.setTextColor(IHM_BLACK); tft.print(Lastbuffer_posToProcess);
      tft.setCursor(LB_M4posToProcess.x+25,LB_M4posToProcess.y);tft.setTextColor(IHM_WHITE); tft.print(buffer_posToProcess);
     }
    if(Lastbuffer2_TypeOfCmd!=buffer2_TypeOfCmd)
     {
      tft.setCursor(LB_M4inByte.x+25,TYpos=LB_M4inByte.y);tft.setTextColor(IHM_BLACK); tft.print(Lastbuffer2_TypeOfCmd);
      tft.setCursor(LB_M4inByte.x+25,TYpos=LB_M4inByte.y);tft.setTextColor(IHM_WHITE); tft.print(buffer2_TypeOfCmd);
     }
    if(Lastbuffer_Full!=buffer_Full)
     {
      tft.setCursor(LB_M4buffer_Full.x+25,LB_M4buffer_Full.y);tft.setTextColor(IHM_BLACK); tft.print(Lastbuffer_Full);
      tft.setCursor(LB_M4buffer_Full.x+25,LB_M4buffer_Full.y);tft.setTextColor(IHM_WHITE); tft.print(buffer_Full);
     }
    if(LastNbCmd!=NbCmdTest)
     {
      tft.setCursor(LB_M4NbCmd.x+25,LB_M4NbCmd.y);tft.setTextColor(IHM_BLACK); tft.print(LastNbCmd);
      tft.setCursor(LB_M4NbCmd.x+25,LB_M4NbCmd.y);tft.setTextColor(IHM_WHITE); tft.print(NbCmdTest);
     }   
  Lastbuffer_pos=buffer_pos;
  Lastbuffer_posToProcess=buffer_posToProcess;
  Lastbuffer2_TypeOfCmd=buffer2_TypeOfCmd;
  Lastbuffer_Full=buffer_Full;
  LastNbCmd=NbCmdTest;  
}

void IHM_Menu4_RedrawButton(){
  IHM_Draw_Label(             "Pos:",LB_M4buffer_pos     ,1,IHM_GRAY,IHM_BLACK,0);
  IHM_Draw_Label(             "Tr.:",LB_M4posToProcess   ,1,IHM_GRAY,IHM_BLACK,0);
  IHM_Draw_Label(             "Typ:",LB_M4inByte         ,1,IHM_GRAY,IHM_BLACK,0);
  IHM_Draw_Label(            "Full:",LB_M4buffer_Full    ,1,IHM_GRAY,IHM_BLACK,0);
  IHM_Draw_Label(              "Nb:",LB_M4NbCmd          ,1,IHM_GRAY,IHM_BLACK,0);

  IHM_Draw_ButtonCenter2(      "RAZ",BP_M4Raz            ,1,IHM_WHITE,IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(     "Buff",BP_M4PrintBuff      ,1,IHM_WHITE,IHM_BLUE,5,0);

  IHM_Draw_ButtonCenter2( "Buff col",BP_M4_A             ,1,IHM_WHITE,IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2( "Buf2 col",BP_M4_B             ,1,IHM_WHITE,IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(        "?",BP_M4_C             ,1,IHM_WHITE,IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(   "Traite",BP_M4_D             ,1,IHM_WHITE,IHM_BLUE,5,0);
  IHM_Draw_ButtonCenter2(   "Resume",BP_M4_E             ,1,IHM_WHITE,IHM_BLUE,5,0);
     
  IHM_Draw_ButtonCenter2(   "REBOOT",BP_M4REBOOT         ,1,IHM_WHITE, IHM_RED,5,0);
}

void IHM_Menu4_Loop(){
  boolean Refresh=false;

  if (Menu_FirstStart==true)    IHM_Menu4_Init();  
  if (PTouch.z > MINPRESSURE && PTouch.z < MAXPRESSURE)
   {      
    if (IHMCheck(PTouch,BP_M4Raz)==1)            { TerminalSizeSet(Terminal2);IHM_Menu4_RedrawButton();}    //{ TerminalSizeSet(Terminal2);}    
    if (IHMCheck(PTouch,BP_M4PrintBuff)==1)      { printStringlnColor(buffer,IHM_GRAY,1);
                                                   //printDecColor(MAX_BUF,IHM_GRAY,1);
                                                 }

    if (IHMCheck(PTouch,BP_M4_A)==1)             { RS232_BufferPrintColor0();  IHM_Menu4_RedrawButton(); Refresh=true;}
    if (IHMCheck(PTouch,BP_M4_B)==1)             { RS232_Buffer2PrintColor0(); IHM_Menu4_RedrawButton(); Refresh=true;}
    if (IHMCheck(PTouch,BP_M4_C)==1)             { CNC_CheckGRBL() ;IHM_Menu4_RedrawButton();  Refresh=true;}
    if (IHMCheck(PTouch,BP_M4_D)==1)             { Traite(); IHM_Menu4_RedrawButton();  Refresh=true;}
    if (IHMCheck(PTouch,BP_M4_E)==1)             { CNC_Resume() ;IHM_Menu4_RedrawButton();  Refresh=true;}
    if (IHMCheck(PTouch,BP_M4REBOOT)==1)         { resetFunc(); }//void(*resetFunc)(void) =0;  

  
   }
  if (Refresh==true){wait_released();}
  RS232_StatusPrint();
}
