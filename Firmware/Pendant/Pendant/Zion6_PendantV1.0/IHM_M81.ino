//IHM Boutons

//
//   
//
////         --------------------  
//          |                    |           S
//          |                    |           D
//          |                    | 
//          |                    |      ^        P
//          |                    |    <   >      o
//           --------------------       .        t
//
//   O   O                   O               O 
//       O              O    O    O          O 
//   O   O                   O               O 
//
//
// Definition des boutons
// Repartition des boutons sur les I/O
 

const struct TBouton LB_M81                   = { 10, 60, 50, 25};

const struct TBouton BP_M81_0                 = { 30,240, 20, 15}; // -         0 
const struct TBouton BP_M81_1                 = { 30,300, 20, 15}; // CTRL      1
const struct TBouton BP_M81_2                 = { 80,240, 20, 15}; // -         4
const struct TBouton BP_M81_3                 = { 80,270, 20, 15}; // -         3
const struct TBouton BP_M81_4                 = { 80,300, 20, 15}; // -         2
const struct TBouton BP_M81_5                 = {220,270, 20, 15}; // -         5
const struct TBouton BP_M81_6                 = {270,240, 20, 15}; // -         9
const struct TBouton BP_M81_7                 = {270,270, 20, 15}; // -         7
const struct TBouton BP_M81_8                 = {270,300, 20, 15}; // -         6
const struct TBouton BP_M81_9                 = {320,270, 20, 15}; // -         8
const struct TBouton BP_M81_10                = {440,240, 20, 15}; // SUP      12 
const struct TBouton BP_M81_11                = {440,270, 20, 15}; // -        11
const struct TBouton BP_M81_12                = {440,300, 20, 15}; // ALT      10

const struct TBouton BP_M81_Joy               = {380,180, 30, 30}; // -
const struct TBouton Chk_M81_Pot              = {460,150, 15, 100}; // -

void IHM_Menu81_Init(){
 MenusInit(    2                       , 3             , 1                    , 1                   , 1                 , FEN_PARAMS);
//             Alive Format            , Erase         , PTouch reset         , Print page number   , draw BOT rect     , Menu Back
//              0 : rien                 0 : rien        0 : non                0 : non               0 : non             index
//              1 : petite barre         1 : tout        1 : oui                1 : oui               1 : oui
//              2 : rectangle            2 : TOP
//              3 : Icone deplacement    3 : BOT
//              4 : Efface menu 3

//  AliveFormat=1;  IHM_EraseBOTArea();    PTouch_Reset(); // Reset le Touch de la fenetre d'appel precedente  
//  IHM_PrintPageNumber(); MenuBack=FEN_PARAMS;
//  my_lcd.Set_Draw_color(IHM_GREEN);
  //my_lcd.Draw_Round_Rectangle(0,52,my_lcd.Get_Display_Width()-1,  my_lcd.Get_Display_Height()-1,5);
  TerminalSizeSet(TerminalMenu81);
//  my_lcd.Set_Draw_color(IHM_GRAY);my_lcd.Draw_Round_Rectangle(4,75,my_lcd.Get_Display_Width()-100,  my_lcd.Get_Display_Height()-14,3);

  IHM_Draw_Label("Interface Boutons",LB_M81              ,2,IHM_GRAY,IHM_BLACK,0);
  IHM_Menu81_ButtonRedraw();
  Menu_FirstStart=false;
  JOYM81Last.XAna=JOY.XAna<<2; // provoque un refresh
  DEBUGSerial.println(F("Menu81 (IHM Bouton) Init Done"));
}



void IHM_Menu81_ButtonRedraw(){
  DrawMenu81ButtonCenter( BP_M81_0   ,  IHM_GOLD,IHM_BP0Pressed);
  DrawMenu81ButtonCenter( BP_M81_1   ,  IHM_GOLD,IHM_BP1Pressed);
  DrawMenu81ButtonCenter( BP_M81_2   ,  IHM_GOLD,IHM_BP2Pressed);
  DrawMenu81ButtonCenter( BP_M81_3   ,  IHM_GOLD,IHM_BP3Pressed);
  DrawMenu81ButtonCenter( BP_M81_4   ,  IHM_GOLD,IHM_BP4Pressed);
  DrawMenu81ButtonCenter( BP_M81_5   ,  IHM_GOLD,IHM_BP5Pressed);
  DrawMenu81ButtonCenter( BP_M81_6   ,  IHM_GOLD,IHM_BP6Pressed);
  DrawMenu81ButtonCenter( BP_M81_7   ,  IHM_GOLD,IHM_BP7Pressed);
  DrawMenu81ButtonCenter( BP_M81_8   ,  IHM_GOLD,IHM_BP8Pressed);
  DrawMenu81ButtonCenter( BP_M81_9   ,  IHM_GOLD,IHM_BP9Pressed);
  DrawMenu81ButtonCenter( BP_M81_10  ,  IHM_GOLD,IHM_BP10Pressed);
  DrawMenu81ButtonCenter( BP_M81_11  ,  IHM_GOLD,IHM_BP11Pressed);
  DrawMenu81ButtonCenter( BP_M81_12  ,  IHM_GOLD,IHM_BP12Pressed);
  //DrawMenu81ButtonCenter( BP_M81_Joy ,  IHM_GOLD,0);
  Draw_VScrollBar(    "",Chk_M81_Pot ,1,IHM_WHITE,     IHM_GRAY,100-JOY.F,10);
}

void IHM_Menu81_Loop(){
  if (Menu_FirstStart==true)    {IHM_Menu81_Init();}
//  if(PTouch.z > MINPRESSURE && PTouch.z < MAXPRESSURE)
//   {      
//    if (IHMCheck(PTouch,BP_M81_0)==1)                { ; } //
//   }

  if(JOYLastM81.F!=JOY.F)
   {
    Draw_VScrollBar(    "",Chk_M81_Pot ,1,IHM_WHITE, IHM_GRAY,100-JOY.F,10);
    JOYLastM81.F=JOY.F;
   }
  if (( (JOYM81Last.XAna>>2)!=(JOY.XAna>>2)) | ((JOYM81Last.ZAna>>2)!=(JOY.ZAna>>2)))
   {
    DrawMenu81JoyCheck( BP_M81_Joy, IHM_BLUE);
   }
  if ( IHM_BPLast!=IHM_BP) { IHM_BPLast=IHM_BP; IHM_Menu81_ButtonRedraw();}
     
}

void DrawMenu81ButtonCenter(struct TBouton BP, uint16_t fc, boolean mode)
{
  if (mode) { tft.fillCircle(BP.x , BP.y , BP.w/2 , fc); }
  else      { tft.fillCircle(BP.x , BP.y , BP.w/2 , IHM_BLACK); }
              tft.drawCircle(BP.x , BP.y , BP.w/2 , IHM_GRAY); 
}

void DrawMenu81JoyCheck(struct TBouton BP, uint16_t fc)
{
  int16_t YTmp=map(JOYM81Last.XAna,JOY.XMin,JOY.XMax,-BP.w,+BP.w);
  int16_t XTmp=map(JOYM81Last.ZAna,JOY.ZMin,JOY.ZMax,-BP.h,BP.h);
  tft.fillCircle(BP.x-XTmp , BP.y+YTmp , 5 ,IHM_BLACK); // Efface l'ancienne position du point 
  YTmp=map(JOY.XAna,JOY.XMin,JOY.XMax,-BP.w,BP.w);
  XTmp=map(JOY.ZAna,JOY.ZMin,JOY.ZMax,-BP.h,BP.h);
  tft.fillCircle(BP.x-XTmp , BP.y+YTmp , 5 , fc);       // Affiche la position du point
  
  tft.drawRoundRect(BP.x-(BP.w+5) , BP.y-(BP.h+5) , 2*BP.w+10, 2*BP.h+10 ,5 , IHM_GRAY); 
  tft.drawCircle         (BP.x , BP.y , BP.w , IHM_GRAY); 
  JOYM81Last.XAna=JOY.XAna;
  JOYM81Last.ZAna=JOY.ZAna;  
}



















