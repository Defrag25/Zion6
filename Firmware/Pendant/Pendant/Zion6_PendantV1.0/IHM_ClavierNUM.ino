//Clavier numérique de saisie de nombres
//const uint16_t ClavierNum.x = 10;
//const uint16_t ClavierNum.y = 60;
//const uint16_t ClavierNum.w = 195;
//const uint16_t ClavierNum.h = 250;


const struct TBouton ClavierNum   ={ 10, 60,195,250}; // Pour gestion des offsets !
const struct TBouton BP_1         ={ 20, 70, 30, 30};
const struct TBouton BP_2         ={ 60, 70, 30, 30};
const struct TBouton BP_3         ={100, 70, 30, 30};
const struct TBouton BP_4         ={ 20,110, 30, 30};
const struct TBouton BP_5         ={ 60,110, 30, 30};
const struct TBouton BP_6         ={100,110, 30, 30};
const struct TBouton BP_7         ={ 20,150, 30, 30};
const struct TBouton BP_8         ={ 60,150, 30, 30};
const struct TBouton BP_9         ={100,150, 30, 30};
const struct TBouton BP_SIGNE     ={ 20,190, 30, 30};
const struct TBouton BP_0         ={ 60,190, 30, 30};
const struct TBouton BP_POINT     ={100,190, 30, 30};
const struct TBouton BP_RAZ       ={160, 70, 50, 30};
const struct TBouton BP_MUL2      ={160,110, 50, 30};
const struct TBouton BP_DIV2      ={160,150, 50, 30};
const struct TBouton BP_VAL       ={160,190, 50, 30};
const struct TBouton BPcancel     ={ 48,230, 80, 30};
const struct TBouton BPenter      ={146,230, 80, 30};

///////////////////////////////////////////////////
// Clavier Scientifique
const struct TBouton BS_PLUS      ={230, 70, 50, 30}; // +
const struct TBouton BS_MOINS     ={230,110, 50, 30}; // -
const struct TBouton BS_MULT      ={230,150, 50, 30}; // *
const struct TBouton BS_DIV       ={230,190, 50, 30}; // /
const struct TBouton BS_INV       ={290, 70, 50, 30}; // 1/x


void TValInit(){
  
}

char Text[15]="              ";
 

void DrawStringInClavier(char *str){
   tft.setTextColor(IHM_WHITE,IHM_BLACK);  tft.setTextSize(2);
   tft.setCursor(ClavierNum.x+15,ClavierNum.y+10);
   tft.print(str);
   wait_released();
   //delay(200);
}

void DrawValInClavier(float V){
   tft.setTextColor(IHM_BLUE);     tft.setTextSize(2);
   tft.setCursor(ClavierNum.x+90, ClavierNum.y+25);
   tft.print(V,3);
   wait_released();
   //delay(200);
}


void DrawNUMButtonCenter2(char *str,struct TBouton BP,uint8_t csize,uint16_t fc, uint16_t bc,boolean mode)
{
   uint16_t lenX,lenY;
   const char * p = (const char *)str;
//  size_t n = 0;                  
    tft.fillCircle(ClavierNum.x+BP.x , ClavierNum.y+BP.y , BP.w/2, bc);
    tft.drawCircle(ClavierNum.x+BP.x , ClavierNum.y+BP.y , BP.w/2, IHM_YELLOW);
   lenX = strlen((const char *)str) * 3 * csize;   
   lenY = 4 * csize;   
   tft.setTextColor(fc,bc);     tft.setTextSize(csize);
   tft.setCursor(ClavierNum.x+BP.x-lenX+1,ClavierNum.y+BP.y-lenY+1);
   tft.print(*str);
}


boolean IHM_ClavierNUM_Init(){

   AliveFormat=1;
   IHM_EraseBOTArea();
   IHM_PrintPageNumber(MenuState);
   //IHM_Draw_ButtonCenter2("<<<"  ,BP_BackDroite      ,2,BLUE, GREEN,0);
   PTouch_Reset(); // Reset le Touch de la fenetre d'appel precedente 
   //DrawStringInClavier("AZERTY");
//     tft.fillRoundRect(ClavierNum.x+2 , ClavierNum.y+2 , ClavierNum.x+ClavierNum.w-2,ClavierNum.y+50,10, IHM_BLACK);
  tft.drawRoundRect(ClavierNum.x , ClavierNum.y , ClavierNum.w , ClavierNum.h,10, IHM_GREEN);  
  IHM_ClavierNUM_EraseTextArea();
  //   my_lcd.Set_Draw_color(IHM_BLUE) ; my_lcd.Draw_Line           (ClavierNum.x+7 , ClavierNum.y+45 , ClavierNum.x+ClavierNum.w-7 , ClavierNum.y+45);
   //float n =-3.10;
   DrawValInClavier(Val);
   //TerminalSizeSet(TerminalNum);
   TerminalSizeSet(TermMinalNull);
//   my_lcd.Set_Text_Size(2);
//   //void Print_Number_Float(double num, uint8_t dec, int16_t x, int16_t y, uint8_t divider, int16_t length, uint8_t filler);
//   my_lcd.Set_Text_colour(IHM_GRAY) ; my_lcd.Print_Number_Float(n, 6, ClavierNum.x+90, ClavierNum.y+25, '.', 5, ' ');
//   my_lcd.Set_Text_colour(IHM_BLUE) ; my_lcd.Print_Number_Float(n, 3, ClavierNum.x+90, ClavierNum.y+25, '.', 5, ' ');
//Draw_Line(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
   DrawStringInClavier(Text); 
   DrawNUMButtonCenter2(        "1",BP_1,2,IHM_WHITE,IHM_BLUE,1); //   1  2  3 
   DrawNUMButtonCenter2(        "2",BP_2,2,IHM_WHITE,IHM_BLUE,1);
   DrawNUMButtonCenter2(        "3",BP_3,2,IHM_WHITE,IHM_BLUE,1);
   IHM_Draw_ButtonCenter(       "R",ClavierNum.x+BP_RAZ.x , ClavierNum.y+BP_RAZ.y,BP_RAZ.w,BP_RAZ.h,2,IHM_WHITE, IHM_GRAY,1);
   DrawNUMButtonCenter2(        "4",BP_4,2,IHM_WHITE,IHM_BLUE,1);//   4  5  6
   DrawNUMButtonCenter2(        "5",BP_5,2,IHM_WHITE,IHM_BLUE,1);
   DrawNUMButtonCenter2(        "6",BP_6,2,IHM_WHITE,IHM_BLUE,1);
   IHM_Draw_ButtonCenter(      "*2",ClavierNum.x+160 , ClavierNum.y+110,50,30,2,IHM_WHITE, IHM_GRAY,1);
   DrawNUMButtonCenter2(        "7",BP_7,2,IHM_WHITE,IHM_BLUE,1); //   7  8  9
   DrawNUMButtonCenter2(        "8",BP_8,2,IHM_WHITE,IHM_BLUE,1);
   DrawNUMButtonCenter2(        "9",BP_9,2,IHM_WHITE,IHM_BLUE,1);
   IHM_Draw_ButtonCenter(      "/2",ClavierNum.x+160 , ClavierNum.y+150,50,30,2,IHM_WHITE, IHM_GRAY,1);
   DrawNUMButtonCenter2(      "+-",BP_SIGNE,2,IHM_WHITE,IHM_BLUE,1); //   -  0  .
   DrawNUMButtonCenter2(        "0",BP_0,2,IHM_WHITE,IHM_BLUE,1);
   DrawNUMButtonCenter2(        ".",BP_POINT,2,IHM_WHITE,IHM_BLUE,1);
   IHM_Draw_ButtonCenter(     "VAL",ClavierNum.x+160 , ClavierNum.y+190,50,30,2,IHM_WHITE, IHM_GREEN,1);
 //  CANCEL VALID
   IHM_Draw_ButtonCenter(  "CANCEL",ClavierNum.x+48  , ClavierNum.y+230,80,30,2,IHM_WHITE, IHM_GRAY,1);
   IHM_Draw_ButtonCenter(  "ENTER" ,ClavierNum.x+146 , ClavierNum.y+230,80,30,2,IHM_WHITE, IHM_GRAY,1);
 //
///////////////////////////////////////////////////
// Clavier Scientifique
   IHM_Draw_ButtonCenter(       "+",ClavierNum.x+BS_PLUS.x , ClavierNum.y+BS_PLUS.y , BS_PLUS.w , BS_PLUS.h , 2, IHM_WHITE, IHM_GRAY,1);
   IHM_Draw_ButtonCenter(       "-",ClavierNum.x+BS_MOINS.x, ClavierNum.y+BS_MOINS.y, BS_MOINS.w, BS_MOINS.h, 2, IHM_WHITE, IHM_GRAY,1);
   IHM_Draw_ButtonCenter(       "*",ClavierNum.x+BS_MULT.x , ClavierNum.y+BS_MULT.y , BS_MULT.w , BS_MULT.h , 2, IHM_WHITE, IHM_GRAY,1);
   IHM_Draw_ButtonCenter(       "/",ClavierNum.x+BS_DIV.x  , ClavierNum.y+BS_DIV.y  , BS_DIV.w  , BS_DIV.h  , 2, IHM_WHITE, IHM_GRAY,1);
   IHM_Draw_ButtonCenter(     "1/x",ClavierNum.x+BS_INV.x  , ClavierNum.y+BS_INV.y  , BS_INV.w  , BS_INV.h  , 2, IHM_WHITE, IHM_GRAY,1);

   Menu_FirstStart=false;
   DEBUGSerial.println("Clavier NUM Init Done");
}

boolean ClavierCheck(TSPoint PT,struct TBouton BP)
 {
  uint16_t _XM,_XP,_YM,_YP;
  _XM = ClavierNum.x+BP.x-BP.w/2;
  _XP = ClavierNum.x+BP.x+BP.w/2;
  _YM = ClavierNum.y+BP.y-BP.h/2;
  _YP = ClavierNum.y+BP.y+BP.h/2;  
  if(( (PT.x>=_XM)&&(PT.x<=_XP) ) && ( (PT.y>=_YM)&&(PT.y<=_YP) )) return(1);      
  return(0);
}

void PutInText(char *c){
  if (strlen(Text)<8) {strcat(Text,c);}
}

boolean IHM_ClavierNUM_Loop(){
  boolean res=false;
  if (Menu_FirstStart==true)                { IHM_ClavierNUM_Init();  }
  if(PTouch.z > MINPRESSURE && PTouch.z < MAXPRESSURE)
   {      
    if (ClavierCheck(PTouch,BP_0)==1)  {   DEBUGSerial.print("0"); PutInText("0");  DrawStringInClavier(Text); }
    if (ClavierCheck(PTouch,BP_1)==1)  {   DEBUGSerial.print("1"); PutInText("1");  DrawStringInClavier(Text); }
    if (ClavierCheck(PTouch,BP_2)==1)  {   DEBUGSerial.print("2"); PutInText("2");  DrawStringInClavier(Text); }
    if (ClavierCheck(PTouch,BP_3)==1)  {   DEBUGSerial.print("3"); PutInText("3");  DrawStringInClavier(Text); }
    if (ClavierCheck(PTouch,BP_4)==1)  {   DEBUGSerial.print("4"); PutInText("4");  DrawStringInClavier(Text); }
    if (ClavierCheck(PTouch,BP_5)==1)  {   DEBUGSerial.print("5"); PutInText("5");  DrawStringInClavier(Text); }
    if (ClavierCheck(PTouch,BP_6)==1)  {   DEBUGSerial.print("6"); PutInText("6");  DrawStringInClavier(Text); }
    if (ClavierCheck(PTouch,BP_7)==1)  {   DEBUGSerial.print("7"); PutInText("7");  DrawStringInClavier(Text); }
    if (ClavierCheck(PTouch,BP_8)==1)  {   DEBUGSerial.print("8"); PutInText("8");  DrawStringInClavier(Text); }
    if (ClavierCheck(PTouch,BP_9)==1)  {   DEBUGSerial.print("9"); PutInText("9");  DrawStringInClavier(Text); }
    if (ClavierCheck(PTouch,BP_POINT)==1){ DEBUGSerial.print("."); PutInText(".");  DrawStringInClavier(Text); }
    if (ClavierCheck(PTouch,BP_DIV2)==1)   
     {Val=Val / 2;
      IHM_ClavierNUM_EraseTextArea();
      DrawValInClavier(Val); 
     }
    if (ClavierCheck(PTouch,BP_MUL2)==1)   
     {Val=Val * 2;
      IHM_ClavierNUM_EraseTextArea();
      DrawValInClavier(Val); 
     }
    if (ClavierCheck(PTouch,BP_SIGNE)==1)   
     {Val=Val * (-1); 
      IHM_ClavierNUM_EraseTextArea();
      DrawValInClavier(Val); 
     }

    if (ClavierCheck(PTouch,BP_RAZ)==1)  
     {Val=0;
      IHM_ClavierNUM_EraseTextArea();
      DrawValInClavier(Val); 
     }

    if ((ClavierCheck(PTouch,BP_VAL)==1) & (Text!="")) 
     {Val=atof(Text);strcpy(Text,"");
     IHM_ClavierNUM_EraseTextArea();
     DrawValInClavier(Val); 
     }

    if (ClavierCheck(PTouch,BPenter)==1) 
     {//if(Text!=""){Val=atof(Text);}
      IHM_ClavierNUM_EraseTextArea();
      DrawValInClavier(Val); 
      MenuState=MenuStateLast;  Menu_FirstStart=true; // retour à la fenetre d'appel (La valeur est dans val)
      res=true; // Permet à la fenetre d'appel de valider la data
      TVal[TValIndex]=Val;
      EEPROM_TAB_ToolsSave();
      EEPROM_TAB_ToolsLoad();
     }

    if (ClavierCheck(PTouch,BPcancel)==1) 
     {
      //my_lcd.Set_Draw_color(IHM_BLACK) ; my_lcd.Fill_Round_Rectangle(ClavierNum.x+2 , ClavierNum.y+2 , ClavierNum.x+ClavierNum.w-2,ClavierNum.y+50,10);
      //my_lcd.Set_Draw_color(IHM_GRAY)  ; my_lcd.Draw_Round_Rectangle(ClavierNum.x+2 , ClavierNum.y+2 , ClavierNum.x+ClavierNum.w-2,ClavierNum.y+50,10);
      //DrawValInClavier(Val); 
      MenuState=MenuStateLast;  Menu_FirstStart=true; // retour à la fenetre d'appel
                                                      // La valeur est dans val
      res=false; // 
     }
///////////////////////////////////////////////////
// Clavier Scientifique
    if (ClavierCheck(PTouch,BS_PLUS)==1)  
     {
      if (Text!="")
       {
         float Val1=atof(Text);Val+=Val1;//strcpy(Text,"");DrawValInClavier(Val);       
         IHM_ClavierNUM_EraseTextArea();
         DrawValInClavier(Val); 
       }
     }
    if (ClavierCheck(PTouch,BS_MOINS)==1)  
     {
      if (Text!="")
       {
         float Val1=atof(Text);Val-=Val1;//strcpy(Text,"");DrawValInClavier(Val);       
         IHM_ClavierNUM_EraseTextArea();
         DrawValInClavier(Val); 
       }
     }
    if (ClavierCheck(PTouch,BS_MULT)==1)  
     {
      if (Text!="")
       {
         float Val1=atof(Text);Val*=Val1;//strcpy(Text,"");DrawValInClavier(Val);       
         IHM_ClavierNUM_EraseTextArea();
         DrawValInClavier(Val); 
       }
     }
    if (ClavierCheck(PTouch,BS_DIV)==1)  
     {
      if (Text!="")
       {
         float Val1=atof(Text);Val/=Val1;//strcpy(Text,"");DrawValInClavier(Val);       
         IHM_ClavierNUM_EraseTextArea();
         DrawValInClavier(Val); 
       }
     }
    if (ClavierCheck(PTouch,BS_INV)==1)  
     {
      if (Text!="")
       {
         //float Val1=atof(Text);
         Val=1/Val;//strcpy(Text,"");DrawValInClavier(Val);       
         IHM_ClavierNUM_EraseTextArea();
         DrawValInClavier(Val); 
       }
     }
  }
}

void IHM_ClavierNUM_EraseTextArea(){
  strcpy(Text,"");
  tft.fillRoundRect(ClavierNum.x+2 , ClavierNum.y+2 , ClavierNum.w-4,50,10, IHM_BLACK);
  tft.drawRoundRect(ClavierNum.x+2 , ClavierNum.y+2 , ClavierNum.w-4,50,10, IHM_GRAY);  
}

