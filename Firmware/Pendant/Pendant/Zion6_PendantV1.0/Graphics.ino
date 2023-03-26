//CNC graphics

// Librairie de gestion des codes G d'une CNC



void CNCDrawCircle(uint16_t Xc,uint16_t Yc, uint16_t Radius,uint16_t Color){
  for(uint16_t i=0;i<360;i++)
   {
    float radian= i* PI/180;
    uint16_t px = Xc + (uint16_t)(Radius * cos(radian));
    uint16_t py = Yc + (uint16_t)(Radius * sin(radian));
    uint16_t ActualPixel=tft.readPixel(px,py);
    tft.drawPixel(px, py,Color^ActualPixel);

    //tft.drawPixel(px,py,Color);
   }
}

void CNCDrawDraftCircle(uint16_t Xc,uint16_t Yc, uint16_t Radius,uint8_t Step,uint16_t Color){
  for(uint16_t i=0;i<360;i=i+Step)
   {
    float radian= i* PI/180;
    uint16_t px = Xc + (uint16_t)(Radius * cos(radian));
    uint16_t py = Yc + (uint16_t)(Radius * sin(radian));
    uint16_t ActualPixel=tft.readPixel(px,py);
    tft.drawPixel(px, py,Color^ActualPixel);

    //tft.drawPixel(px,py,Color);
   }
}

void CNCDrawPieCircle(uint16_t Xc,uint16_t Yc,uint16_t AngleStart,uint16_t AngleStop, uint16_t Radius,uint16_t Color,uint16_t Color2)
 {
  uint16_t NewColor;
  float radianStart= AngleStart;// * PI/180;
  float radianStop = AngleStop ;// * PI/180;
  int16_t ICosAStart = (int16_t)(Radius * cos(AngleStart * PI/180));
  int16_t ICosAStop  = (int16_t)(Radius * cos(AngleStop  * PI/180));
  int16_t ISinAStart = (int16_t)(Radius * sin(AngleStart * PI/180));
  int16_t ISinAStop  = (int16_t)(Radius * sin(AngleStop  * PI/180));

  NewColor=Color2;  
  CNCDrawDraftCircle(Xc,Yc,Radius,2+Radius/30,Color2);
  tft.drawLine ( Xc , Yc , Xc + ICosAStart , Yc + ISinAStart, NewColor);
  tft.drawLine ( Xc , Yc , Xc + ICosAStop  , Yc + ISinAStop, NewColor);
  tft.drawCircle(Xc , Yc,3, NewColor);
  tft.drawCircle(Xc + ICosAStart , Yc + ISinAStart , 3, NewColor);
  tft.drawCircle(Xc + ICosAStop  , Yc + ISinAStop  , 3 , NewColor);
  NewColor=Color;  
  for(uint16_t i=radianStart;i<radianStop;i++)
   {
    float radian = i * PI/180;
    uint16_t px  = Xc + (uint16_t)(Radius * cos(radian));
    uint16_t py  = Yc + (uint16_t)(Radius * sin(radian));
    uint16_t ActualPixel=tft.readPixel(px,py);
    
    tft.drawPixel(px,py,NewColor^ActualPixel);

    //tft.drawPixel(px,py, NewColor);
   }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dessin IHM ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const struct TBouton Dessin_ORG_OU1           = {160,300,  0,  0};
const struct TBouton Dessin_ORG_OU2           = {110,200,  0,  0};
const struct TBouton Dessin_ORG_OM            = {390,270,  0,  0};
const struct TBouton Dessin_ORG_OT            = { 10,200,  0,  0};
const struct TBouton Dessin_AXESxz            = {390,250,  0,  0};


////////////////////////////////////////////////////////////////////////////////
// Constante de definition des dessins
////////////////////////////////////////////////////////////////////////////////
const float Dessin_Factor = 5; // Facteur de multiplication entre visus ecran et taille en mm
// Definition de l'axe
const struct TBouton Dessin_LB_Axe            = { 0,  0,  9, 25}; // Origine (10,80) longeur 11 traits
//
//  (10,80)
//     X----  -  -----  -  -----
//

// Definition de la Matiere
const struct TBouton Dessin_LB_Matiere        = { 0, 0, 270, 65}; // Origine (Axe) longeur w diametre h (en mm)
// Point X = centre du mandrin = Axe.x
// Point Y = Extrémité de la matiere longeur w, diametre h)
//  (10,80)
//     X----  -  -----  -  -----
//     |          |
//     |          h
//     |          |
//      -----w----Y 

// Definition de la Trajectoire (Piece d'échec)
//const struct TBouton LB_PieceExample1    = { 0, 0, 40, 12}; // Origine (Axe) longeur w diametre h (en mm)


void IHM_Dessin_DrawOrigines(char *nom,struct TBouton Axes, boolean Rep)
{// Dessine un point d'origine avec l'option de dessin du repre ou pas
 if(EnableDrawORG==true)
  {//Dessine L'axe Z 
   //my_lcd.Set_Draw_color(IHM_BLUE);
   tft.drawCircle(Axes.x,Axes.y,5,IHM_BLUE);
   tft.setTextSize(2);
   if (Rep)
    {
     tft.drawLine(Axes.x+25,Axes.y-5,Axes.x+30,Axes.y,IHM_BLUE);  tft.drawLine(Axes.x+0 ,Axes.y  ,Axes.x+30,Axes.y,IHM_BLUE);  tft.drawLine(Axes.x+25,Axes.y+5,Axes.x+30,Axes.y,IHM_BLUE);
     tft.setTextColor(IHM_BLUE,IHM_BLACK);
     tft.setCursor(Axes.x+40,Axes.y-8);
     tft.print("Z+");  
     tft.drawLine(Axes.x   ,Axes.y   ,Axes.x,Axes.y+30,IHM_BLUE);  tft.drawLine(Axes.x+5 ,Axes.y+25,Axes.x,Axes.y+30,IHM_BLUE);  tft.drawLine(Axes.x-5 ,Axes.y+25,Axes.x,Axes.y+30,IHM_BLUE);
     tft.setCursor(Axes.x+8,Axes.y+15);
     tft.print("X+");  
     tft.setCursor(Axes.x+6,Axes.y-20);
     tft.setTextColor(IHM_WHITE);    tft.print(nom);  
    }
   else
    {
     tft.setTextColor(IHM_WHITE);    
     tft.setCursor(Axes.x+6,Axes.y+5);
     tft.print(nom);  
    }
  }  
}

void IHM_Dessin_Init(){
  //IHM_EraseBOTArea();
  IHM_Dessin_DrawOrigines( "OM", Dessin_ORG_OM  ,false);
  IHM_Dessin_DrawOrigines("OU1", Dessin_ORG_OU1 ,false);
  IHM_Dessin_DrawOrigines("OU2", Dessin_ORG_OU2 ,false);
  IHM_Dessin_DrawOrigines( "OT", Dessin_ORG_OT  ,true);
//  my_lcd.Set_Draw_color(IHM_GREEN);
  IHM_Dessin_DrawAxe(Dessin_LB_Axe);
  IHM_Dessin_DrawMatiere(Dessin_ORG_OT,Dessin_LB_Matiere);
  IHM_Dessin_DrawTraj(Dessin_ORG_OT);
}

void IHM_Dessin_DrawAxe(struct TBouton A){
  //dessine l'axe
  uint16_t OffsetX=0;
  uint16_t OffsetY=0;
  //my_lcd.Set_Draw_color(IHM_GRAY);
  for (uint8_t i=0;i<A.w;i++)
   {
    OffsetX=Dessin_ORG_OT.x+A.x+i*35;
    OffsetY=Dessin_ORG_OT.y;
    tft.drawLine(OffsetX,OffsetY+A.y,OffsetX+20,OffsetY+A.y,IHM_GRAY);tft.drawLine(OffsetX+25,OffsetY+A.y,OffsetX+30,OffsetY+A.y,IHM_GRAY);  
   }
  tft.drawCircle(A.x,A.y,3,IHM_GRAY);   
}

void IHM_Dessin_DrawMatiere(struct TBouton A,struct TBouton M){
  //dessine la matiere par rapport à un repere
  //PIECE BRUTE
  tft.drawRect( A.x+M.x,        A.y+M.y,       (M.x+M.w),   (M.y+M.h),IHM_RED);
  tft.drawCircle( A.x+(M.x+M.w),  A.y+(M.y+M.h) ,3,IHM_RED);   
}

void IHM_Dessin_DrawTraj(struct TBouton Org){
  // Dessine la trajectoire par rapport à une origine
  // Peut provenir d'un fichier de la carte SD
  CNCDrawPieCircle(     Org.x+230,        Org.y+  0,           0,     161 ,60,IHM_WHITE,IHM_GRAY); 
  tft.drawLine(   Org.x+173.4,        Org.y+ 20,   Org.x+100,    Org.y+ 20 ,IHM_WHITE);
  tft.drawLine(     Org.x+100,        Org.y+ 20,   Org.x+ 50,    Org.y+ 60 ,IHM_WHITE);
  tft.drawLine(      Org.x+50,        Org.y+ 60,   Org.x+  0,    Org.y+ 60 ,IHM_WHITE);
}

void IHM_Dessin_Trace(struct TBouton P1,struct TBouton P2 , boolean Arrow,uint16_t Color){
ActualColor=Color;
  ligne(   P1.x , P1.y , P2.x , P2.y );
  //tft.drawLine(   P1.x , P1.y , P2.x , P2.y ,Color);
  if (Arrow){
  float Angle= atan((P2.x-P1.x)/(P2.y-P1.y))*180/PI;
  float Angle2= (Angle+180-40)*PI/180;
  float Angle3= (Angle+180+40)*PI/180;
  
  tft.drawTriangle( P2.x       , P2.y,
                    P2.x-sin(Angle2)*10   , P2.y-cos(Angle2)*10,
                    P2.x-sin(Angle3)*10   , P2.y-cos(Angle3)*10,Color);
  }
}
////////////////////////////////////////////////////////////


struct TBouton  Point_GrblToTFT(float Zoom, struct TPointGrbl Grbl){

  struct TBouton PointTFT={Dessin_ORG_OT.x,Dessin_ORG_OT.y};
  // Convertion des coordonnées Grbl en coordonnées TFT
  // L'origine du dessin sur TFT est fixée à OT
  // l'axe X du TFT correspond a un deplacement en Z    Z+ -> X+    
  // l'axe Y du TFT correspond a un deplacement en X    X+ -> Y+    
  // Le facteur de Zoom est de ..
  //   -> s1 Z=10  TFT.X = OT.x + Zoom * Z
  //   ->    X=4   TFT.y=  OT.y + Zoom * X;
  //
  //Les fonctions sont:
  // Pour afficher un deplacement "G91 G0 X10 Z-4"          ->    Point_GrblToTFT(PointGrbl)  avec (PointGrbl.x=10 , PointGrbl.z=-4);
  //                                                        ->    ce qui retourne( PointTFT.x=(OT.x + Zoom * PointGrbl.z)
  //                                                        ->                   ( PointTFT.y=(OT.y + Zoom * PointGrbl.x)
  // Le zoom est fixé à 
  PointTFT.x+=(uint16_t)(Zoom*Grbl.z);
  PointTFT.y+=(uint16_t)(Zoom*Grbl.x);
  return(PointTFT);
}

struct TBouton GT (struct TPointGrbl Grbl){
  return(Point_GrblToTFT(ZoomGrblToTFT , Grbl));
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setPixelVerif(int x, int y)
{
  //if ((x >= 0 && x < 480) && (y >= 0 && y < 320))
   uint16_t ActualPixel=tft.readPixel(x,y);
   if (ActualColor==IHM_BLACK) { tft.drawPixel(x, y,IHM_BLACK); }
   else                        { tft.drawPixel(x, y,IHM_GRAY^ActualPixel); }
    //tft.drawPixel(x, y,ActualColor^ActualPixel);
//      //if ((x >= 0 && x < 480) && (y >= 0 && y < 320))
//    tft.drawPixel(x, y,ActualColor^(tft.readPixel(x,y)));
  //if ((x >= 0 && x < 480) && (y >= 0 && y < 320))
//    tft.drawPixel(x, y,ActualColor^(tft.readPixel(x,y)));


}
void xorPixel(int x, int y)
{ // Cette fonction permet de supperposer un tracé sur l'affichage actuel
  // c'est a dire que:
  // -> pour tracer un point il faut exécuter cette fonction avec la couleur d'affichage ActualColor
  // -> Pour effacer le point il faut réexécuter cette fonction avec la meme couleur 
  //if ((x >= 0 && x < 480) && (y >= 0 && y < 320))
  tft.drawPixel(x, y,ActualColor^(tft.readPixel(x,y)));
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       

void barre(int x, int y, int w, int h)
{
 tft.fillRect(x, y, w, h,IHM_WHITE);
}

void effacerEcran(void)
{
   WindowsErase();
}
void ligneHorizontale(int x, int y, int w)
{
  tft.drawFastHLine(x, y, w,IHM_WHITE);
}
 
void ligneVerticale(int x, int y, int h)
{
 tft.drawFastVLine(x, y, h,IHM_WHITE); 
}

void rectangle(int x, int y, int w, int h)
{
  ligneHorizontale(x, y, w);
  ligneHorizontale(x, y + h - 1, w);
  ligneVerticale(x, y + 1, h - 2);
  ligneVerticale(x + w - 1, y + 1, h - 2);
}

void echangerEntiers(int* x, int* y)
{
  int t = *x;
  *x = *y;
  *y = t;
}
 
void ligne(int x1, int y1, int x2, int y2)
{
  int d, dx, dy, aincr, bincr, xincr, yincr, x, y;
 
  if (abs(x2 - x1) < abs(y2 - y1)) {
    /* parcours par l'axe vertical */
 
    if (y1 > y2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }
 
    xincr = x2 > x1 ? 1 : -1;
    dy = y2 - y1;
    dx = abs(x2 - x1);
    d = 2 * dx - dy;
    aincr = 2 * (dx - dy);
    bincr = 2 * dx;
    x = x1;
    y = y1;
 
    setPixelVerif(x, y);
 
    for (y = y1+1; y <= y2; ++y) {
      if (d >= 0) {
  x += xincr;
  d += aincr;
      } else
  d += bincr;
 
      setPixelVerif(x, y);
    }
 
  } else {
    /* parcours par l'axe horizontal */
    
    if (x1 > x2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }
 
    yincr = y2 > y1 ? 1 : -1;
    dx = x2 - x1;
    dy = abs(y2 - y1);
    d = 2 * dy - dx;
    aincr = 2 * (dy - dx);
    bincr = 2 * dy;
    x = x1;
    y = y1;
 
    setPixelVerif(x, y);
 
    for (x = x1+1; x <= x2; ++x) {
      if (d >= 0) {
  y += yincr;
  d += aincr;
      } else
  d += bincr;
 
      setPixelVerif(x, y);
    }
  }    
}

void cercle(int cx, int cy, int rayon)
{
  int d, y, x;
 
  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;
 
  while (y >= x) {
    setPixelVerif(cx + x, cy + y);
    setPixelVerif(cx + y, cy + x);
    setPixelVerif(cx - x, cy + y);
    setPixelVerif(cx - y, cy + x);
    setPixelVerif(cx + x, cy - y);
    setPixelVerif(cx + y, cy - x);
    setPixelVerif(cx - x, cy - y);
    setPixelVerif(cx - y, cy - x);
 
    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }
 
    x++;
  }
}

void disque(int cx, int cy, int rayon)
{
  int d, y, x;
 
  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;
 
  while (y >= x) {
    ligneHorizontale(cx - x, cy - y, 2 * x + 1);
    ligneHorizontale(cx - x, cy + y, 2 * x + 1);
    ligneHorizontale(cx - y, cy - x, 2 * y + 1);
    ligneHorizontale(cx - y, cy + x, 2 * y + 1);
 
    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }
 
    x++;
  }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Arc de cercle /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define DEG2RAD 0.0174532925

#define LOOP_DELAY 10 // Loop delay to slow things down

byte RainInc = 0;
unsigned int RainColor = 0;

byte red = 31; // Red is the top 5 bits of a 16 bit colour value
byte green = 0;// Green is the middle 6 bits
byte blue = 0; // Blue is the bottom 5 bits
byte state = 0;
void Yopla() {
 do{
  // Continuous elliptical arc drawing
  fillArc(tft.width()/2, (tft.height()-50)/2+50, RainInc * 6, 1, tft.width()/2, (tft.height()-50)/3, 10, brightnessAdj(rainbow(RainColor)));//rainbow(col));

  //fillArc(455, 25, inc * 6, 1, 20, 20, 10, rainbow(RainColor));

  // Continuous segmented (inc*2) elliptical arc drawing
  fillArc(tft.width()/2, (tft.height()-50)/2+50, ((RainInc * 2) % 60) * 6, 1, 120, 80, 30, brightnessAdj(rainbow(RainColor)));

  fillArc(tft.width()/2, (tft.height()-50)/2+50, -1*((RainInc * 1) % 120) * 6, 1, 150, (tft.height()-50)/2, 20, brightnessAdj(rainbow(RainColor)));//rainbow(RainColor));

  // Circle drawing using arc with arc width = radius
  fillArc(tft.width()/2, (tft.height()-50)/2+50, RainInc * 6, 1, 42, 42, 42, rainbow(RainColor));

  RainInc++;
  RainColor += 1;
  if (RainColor > 191) RainColor = 0;
  if (RainInc > 59) RainInc = 0;

  delay(LOOP_DELAY);
    IHM_BP=IHM_ButtonCheck();
}while(!IHM_BP);
}

void Yopla2(uint8_t b) {
  // Continuous elliptical arc drawing
  fillArc(tft.width()/2, tft.height()/2, RainInc * 6, 1, tft.width()/2, 100, 10, brightness(rainbow(RainColor),b));//rainbow(RainColor));
  // Continuous segmented (inc*2) elliptical arc drawing
  fillArc(tft.width()/2, tft.height()/2, ((RainInc * 2) % 60) * 6, 1, 120, 80, 30, brightness(rainbow(RainColor),b));

  fillArc(tft.width()/2, tft.height()/2, -1*((RainInc * 1) % 120) * 6, 1, 150, 160, 20, brightness(rainbow(RainColor),b));//rainbow(RainColor));

  // Circle drawing using arc with arc width = radius
  fillArc(tft.width()/2, tft.height()/2, RainInc * 6, 1, 42, 42, 42, rainbow(RainColor));

  RainInc++;
  RainColor += 1;
  if (RainColor > 191) RainColor = 0;
  if (RainInc > 59) RainInc = 0;
}

void Living(){
  RainInc++;
  RainColor += 1;
  if (RainColor > 191) RainColor = 0;
  if (RainInc > 59) RainInc = 0;
  fillArc(455, 25, RainInc * 6, 1, 20, 20, 10, rainbow(RainColor));  
}
    

// #########################################################################
// Draw a circular or elliptical arc with a defined thickness
// #########################################################################

// x,y == coords of centre of arc
// start_angle = 0 - 359
// seg_count = number of 6 degree segments to draw (60 => 360 degree arc)
// rx = x axis outer radius
// ry = y axis outer radius
// w  = width (thickness) of arc in pixels
// colour = 16 bit colour value
// Note if rx and ry are the same then an arc of a circle is drawn

int fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour)
{

  byte seg = 6; // Segments are 3 degrees wide = 120 segments for 360 degrees
  byte inc = 6; // Draw segments every 3 degrees, increase to 6 for segmented ring

  // Calculate first pair of coordinates for segment start
  float sx = cos((start_angle - 90) * DEG2RAD);
  float sy = sin((start_angle - 90) * DEG2RAD);
  uint16_t x0 = sx * (rx - w) + x;
  uint16_t y0 = sy * (ry - w) + y;
  uint16_t x1 = sx * rx + x;
  uint16_t y1 = sy * ry + y;

  // Draw colour blocks every inc degrees
  for (int i = start_angle; i < start_angle + seg * seg_count; i += inc) {

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * DEG2RAD);
    float sy2 = sin((i + seg - 90) * DEG2RAD);
    int x2 = sx2 * (rx - w) + x;
    int y2 = sy2 * (ry - w) + y;
    int x3 = sx2 * rx + x;
    int y3 = sy2 * ry + y;

    tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
    tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);

    // Copy segment end to sgement start for next segment
    x0 = x2;
    y0 = y2;
    x1 = x3;
    y1 = y3;
  }
}

//int fillArcExp(  240,   160,               0,            60,    100,    120,    10, colour);
int fillArcExp(int x, int y, int start_angle, int stop_angle, int rx, int ry, int w, unsigned int colour)
{

  byte seg = 1; // Segments are 3 degrees wide = 120 segments for 360 degrees
  byte inc = 1; // Draw segments every 3 degrees, increase to 6 for segmented ring

  // Calculate first pair of coordinates for segment start
  float sx = cos((start_angle ) * DEG2RAD);
  float sy = sin((start_angle ) * DEG2RAD);
 // uint16_t x0 = sx * (rx - w) + x;
 // uint16_t y0 = sy * (ry - w) + y;
  uint16_t x1 = sx * rx + x;
  uint16_t y1 = sy * ry + y;

  // Draw colour blocks every inc degrees
  for (int i = start_angle; i <  stop_angle; i += inc) {

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg ) * DEG2RAD);
    float sy2 = sin((i + seg ) * DEG2RAD);
 //   int x2 = sx2 * (rx - w) + x;
 //   int y2 = sy2 * (ry - w) + y;
    int x3 = sx2 * rx + x;
    int y3 = sy2 * ry + y;

    tft.drawLine(x1,y1,x3,y3,colour);
   // tft.drawLine(x1,y1,x2,y2,colour);
//    tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
//    tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);

    // Copy segment end to sgement start for next segment
//    x0 = x2;
//    y0 = y2;
    x1 = x3;
    y1 = y3;
  }
}


unsigned int brightnessAdj(unsigned int colour)
{
  JOY_Ana_Check();
  return(brightness(colour, (int)JOY.F));  
}
// #########################################################################
// Return the 16 bit colour with brightness 0-100%
// #########################################################################
unsigned int brightness(unsigned int colour, int brightness)
{
  byte red   = colour >> 11;
  byte green = (colour & 0x7E0) >> 5;
  byte blue  = colour & 0x1F;

  blue =  (blue * brightness) / 100;
  green = (green * brightness) / 100;
  red =   (red * brightness) / 100;

  return (red << 11) + (green << 5) + blue;
}

// #########################################################################
// Return a 16 bit rainbow colour
// #########################################################################
unsigned int rainbow(byte value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to 127 = red
  //if (RainColor++>25){RainColor=0; return (red << 11 | green << 5 | blue);}
  switch (state) {
    case 0:
      green ++;
      if (green == 64) {
        green = 63;
        state = 1;
      }
      break;
    case 1:
      red--;
      if (red == 255) {
        red = 0;
        state = 2;
      }
      break;
    case 2:
      blue ++;
      if (blue == 32) {
        blue = 31;
        state = 3;
      }
      break;
    case 3:
      green --;
      if (green == 255) {
        green = 0;
        state = 4;
      }
      break;
    case 4:
      red ++;
      if (red == 32) {
        red = 31;
        state = 5;
      }
      break;
    case 5:
      blue --;
      if (blue == 255) {
        blue = 0;
        state = 0;
     }
      break;
  }
  return red << 11 | green << 5 | blue;
}
unsigned int rainbow2(byte value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to 127 = red
  if (RainInc++>200){RainInc=0; return (red << 11 | green << 5 | blue);}
  switch (state) {
    case 0:
      green ++;
      if (green == 64) {
        green = 63;
        state = 1;
      }
      break;
    case 1:
      red--;
      if (red == 255) {
        red = 0;
        state = 2;
      }
      break;
    case 2:
      blue ++;
      if (blue == 32) {
        blue = 31;
        state = 3;
      }
      break;
    case 3:
      green --;
      if (green == 255) {
        green = 0;
        state = 4;
      }
      break;
    case 4:
      red ++;
      if (red == 32) {
        red = 31;
        state = 5;
      }
      break;
    case 5:
      blue --;
      if (blue == 255) {
        blue = 0;
        state = 0;
     }
      break;
    default : state=0;  
  }
  return red << 11 | green << 5 | blue;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Vumetre ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include <Fonts/FreeMonoBold24pt7b.h>
//sprintf(tempC, "%4.3f", degreesC)
#define IHM_GREY    IHM_GRAY
// Define meter size as 1 for tft.rotation(0) or 1.3333 for tft.rotation(1)
#define M_SIZE 1.3333

float ltx = 0;    // Saved x coord of bottom of needle
uint16_t osx = M_SIZE*120, osy = M_SIZE*120; // Saved x & y coords
uint32_t updateTime = 0;       // time for next update

int old_analog =  -999; // Value last displayed

int value[6] = {0, 0, 0, 0, 0, 0};
int old_value[6] = { -1, -1, -1, -1, -1, -1};
int d = 0;

void YoplaBoom() {
  analogMeter(); // Draw analogue meter
  do{
  if (updateTime <= millis()) {
    updateTime = millis() + 35; // Update emter every 35 milliseconds
 
    // Create a Sine wave for testing
    d += 4; if (d >= 360) d = 0;
    value[0] = 50 + 50 * sin((d + 0) * 0.0174532925);
 
    plotNeedle(value[0], 0); // It takes between 2 and 12ms to replot the needle with zero delay
  }
    IHM_BP=IHM_ButtonCheck();
  }while(!IHM_BP);
}


// #########################################################################
//  Draw the analogue meter on the screen
// #########################################################################
void analogMeter()
{

  // Meter outline
  tft.fillRect(0, 0, M_SIZE*239, M_SIZE*126, IHM_GRAY);
  tft.fillRect(5, 3, M_SIZE*230, M_SIZE*119, IHM_WHITE);

  tft.setTextColor(IHM_BLACK);  // Text colour

  // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
  for (int i = -50; i < 51; i += 5) {
    // Long scale tick length
    int tl = 15;

    // Coodinates of tick to draw
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (M_SIZE*100 + tl) + M_SIZE*120;
    uint16_t y0 = sy * (M_SIZE*100 + tl) + M_SIZE*140;
    uint16_t x1 = sx * M_SIZE*100 + M_SIZE*120;
    uint16_t y1 = sy * M_SIZE*100 + M_SIZE*140;

    // Coordinates of next tick for zone fill
    float sx2 = cos((i + 5 - 90) * 0.0174532925);
    float sy2 = sin((i + 5 - 90) * 0.0174532925);
    int x2 = sx2 * (M_SIZE*100 + tl) + M_SIZE*120;
    int y2 = sy2 * (M_SIZE*100 + tl) + M_SIZE*140;
    int x3 = sx2 * M_SIZE*100 + M_SIZE*120;
    int y3 = sy2 * M_SIZE*100 + M_SIZE*140;

    // Yellow zone limits
    //if (i >= -50 && i < 0) {
    //  tft.fillTriangle(x0, y0, x1, y1, x2, y2, IHM_YELLOW);
    //  tft.fillTriangle(x1, y1, x2, y2, x3, y3, IHM_YELLOW);
    //}

    // Green zone limits
    if (i >= 0 && i < 25) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, IHM_GREEN);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, IHM_GREEN);
    }

    // Orange zone limits
    if (i >= 25 && i < 50) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, IHM_ORANGE);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, IHM_ORANGE);
    }

    // Short scale tick length
    if (i % 25 != 0) tl = 8;

    // Recalculate coords incase tick lenght changed
    x0 = sx * (M_SIZE*100 + tl) + M_SIZE*120;
    y0 = sy * (M_SIZE*100 + tl) + M_SIZE*140;
    x1 = sx * M_SIZE*100 + M_SIZE*120;
    y1 = sy * M_SIZE*100 + M_SIZE*140;

    // Draw tick
    tft.drawLine(x0, y0, x1, y1, IHM_BLACK);

    // Check if labels should be drawn, with position tweaks
    if (i % 25 == 0) {
      // Calculate label positions
      x0 = sx * (M_SIZE*100 + tl + 10) + M_SIZE*120;
      y0 = sy * (M_SIZE*100 + tl + 10) + M_SIZE*140;
      switch (i / 25) {
#if 0
        case -2: tft.drawCentreString("0", x0, y0 - 12, 2); break;
        case -1: tft.drawCentreString("25", x0, y0 - 9, 2); break;
        case 0: tft.drawCentreString("50", x0, y0 - 7, 2); break;
        case 1: tft.drawCentreString("75", x0, y0 - 9, 2); break;
        case 2: tft.drawCentreString("100", x0, y0 - 12, 2); break;
#endif
        case -2: _drawString("0", x0-10, y0 - 12, 2); break;
        case -1: _drawString("25", x0-10, y0 - 9, 2); break;
        case 0: _drawString("50", x0-10, y0 - 7, 2); break;
        case 1: _drawString("75", x0-10, y0 - 9, 2); break;
        case 2: _drawString("100", x0-10, y0 - 12, 2); break;
      }
    }

    // Now draw the arc of the scale
    sx = cos((i + 5 - 90) * 0.0174532925);
    sy = sin((i + 5 - 90) * 0.0174532925);
    x0 = sx * M_SIZE*100 + M_SIZE*120;
    y0 = sy * M_SIZE*100 + M_SIZE*140;
    // Draw scale arc, don't draw the last part
    if (i < 50) tft.drawLine(x0, y0, x1, y1, IHM_BLACK);
  }

  _drawString("%RH", M_SIZE*(5 + 230 - 40), M_SIZE*(119 - 20), 2); // Units at bottom right
  //tft.drawString("%RH", M_SIZE*(5 + 230 - 40), M_SIZE*(119 - 20), 2); // Units at bottom right

  //tft.drawCentreString("%RH", M_SIZE*120, M_SIZE*70, 4); // Comment out to avoid font 4

  tft.drawRect(5, 3, M_SIZE*230, M_SIZE*119, IHM_BLACK); // Draw bezel line
  plotNeedle(0, 0); // Put meter needle at 0
}

// #########################################################################
// Update needle position
// This function is blocking while needle moves, time depends on ms_delay
// 10ms minimises needle flicker if text is drawn within needle sweep area
// Smaller values OK if text not in sweep area, zero for instant movement but
// does not look realistic... (note: 100 increments for full scale deflection)
// #########################################################################
void plotNeedle(int value, byte ms_delay)
{
  tft.setTextColor(IHM_BLACK, IHM_WHITE);
  char buf[8]; 
  sprintf(buf, "%4.3f", value);
  //dtostrf(value, 4, 0, buf);
  _drawString("%RH", M_SIZE*(5 + 230 - 40), M_SIZE*(119 - 20), 2); // Units at bottom right
  //tft.drawString("%RH", M_SIZE*(5 + 230 - 40), M_SIZE*(119 - 20), 2); // Units at bottom right
  _drawString(buf, M_SIZE*40-40, M_SIZE*(119 - 20), 2);
  //tft.drawRightString(buf, M_SIZE*40, M_SIZE*(119 - 20), 2);

  if (value < -10) value = -10; // Limit value to emulate needle end stops
  if (value > 110) value = 110;

  // Move the needle until new value reached
  while (!(value == old_analog)) {
    if (old_analog < value) old_analog++;
    else old_analog--;

    if (ms_delay == 0) old_analog = value; // Update immediately if delay is 0

    float sdeg = map(old_analog, -10, 110, -150, -30); // Map value to angle
    // Calcualte tip of needle coords
    float sx = cos(sdeg * 0.0174532925);
    float sy = sin(sdeg * 0.0174532925);

    // Calculate x delta of needle start (does not start at pivot point)
    float tx = tan((sdeg + 90) * 0.0174532925);

    // Erase old needle image
    tft.drawLine(M_SIZE*(120 + 20 * ltx - 1), M_SIZE*(140 - 20), osx - 1, osy, IHM_WHITE);
    tft.drawLine(M_SIZE*(120 + 20 * ltx), M_SIZE*(140 - 20), osx, osy, IHM_WHITE);
    tft.drawLine(M_SIZE*(120 + 20 * ltx + 1), M_SIZE*(140 - 20), osx + 1, osy, IHM_WHITE);

    // Re-plot text under needle
    tft.setTextColor(IHM_BLACK);
  //  tft.setFont(&FreeMonoBold24pt7b);
 //   _drawString("%RH", M_SIZE*80, M_SIZE*100, 1); // // Comment out to avoid font 4
//    tft.setFont();
//    tft.drawCentreString("%RH", M_SIZE*120, M_SIZE*70, 4); // // Comment out to avoid font 4

    // Store new needle end coords for next erase
    ltx = tx;
    osx = M_SIZE*(sx * 98 + 120);
    osy = M_SIZE*(sy * 98 + 140);

    // Draw the needle in the new postion, magenta makes needle a bit bolder
    // draws 3 lines to thicken needle
    tft.drawLine(M_SIZE*(120 + 20 * ltx - 1), M_SIZE*(140 - 20), osx - 1, osy, IHM_RED);
    tft.drawLine(M_SIZE*(120 + 20 * ltx), M_SIZE*(140 - 20), osx, osy, IHM_MAGENTA);
    tft.drawLine(M_SIZE*(120 + 20 * ltx + 1), M_SIZE*(140 - 20), osx + 1, osy, IHM_RED);

    // Slow needle down slightly as it approaches new postion
    if (abs(old_analog - value) < 10) ms_delay += ms_delay / 5;

    // Wait before next update
    delay(ms_delay);
  }
}

void _drawString(char *buf, int16_t x, int16_t y, int16_t size)
{
  tft.setTextSize(size);
  tft.setCursor(x, y);
  tft.print(buf);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Oscilloscope //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int sbuf[318];
int cbuf[318];
#define myGLCD tft
void Oups()
{
  uint32_t width = myGLCD.width();
  Serial.print("Width: "); Serial.println(width);
  uint32_t height = myGLCD.height();
  Serial.print("Height: "); Serial.println(height);

  int buf[318];

// Clear the screen and draw the frame
  myGLCD.setTextSize(1);

  myGLCD.fillScreen(IHM_BLACK);
  myGLCD.fillRect(0, 0, 319, 14,IHM_RED);
  myGLCD.fillRect(0, 226, 319, 14,IHM_GREY);

  myGLCD.setTextColor(IHM_BLACK,IHM_RED);
  myGLCD.setCursor(100, 4);
  myGLCD.print("* STM32_IHM_8bit *");
  myGLCD.setTextColor(IHM_YELLOW,IHM_GREY);
  myGLCD.setCursor(100, 230);
  myGLCD.print("Adapted by nopnop2002");

  myGLCD.drawRect(0, 14, 319, 211, IHM_BLUE);

// Draw crosshairs
  myGLCD.drawLine(159, 15, 159, 224,IHM_BLUE);
  myGLCD.drawLine(1, 119, 318, 119,IHM_BLUE);
  for (int i=9; i<310; i+=10)
    myGLCD.drawLine(i, 117, i, 121,IHM_BLUE);
  for (int i=19; i<220; i+=10)
    myGLCD.drawLine(157, i, 161, i,IHM_BLUE);

// Draw sin-lines, cos-lines  
  myGLCD.setTextColor(IHM_CYAN);
  _drawString("Sin", 5, 15,2);
  for (int i=1; i<318; i=i+2)
  {
    sbuf[i-1] = 119+(sin(((i*1.13)*3.14)/180)*95);
    myGLCD.drawPixel(i,sbuf[i-1],IHM_CYAN);
  }
  myGLCD.setTextColor(IHM_RED);
  _drawString("Cos", 5, 30,2);
  for (int i=1; i<318; i=i+2)
  {
    cbuf[i-1] = 119+(cos(((i*1.13)*3.14)/180)*95);
    myGLCD.drawPixel(i,cbuf[i-1],IHM_YELLOW);
  }

  static int delta = 0;

// Erase sin-lines, cos-lines
  for (int i=1; i<318; i=i+2)
  {
    myGLCD.drawPixel(i,sbuf[i-1],IHM_BLACK);
  }
  for (int i=1; i<318; i=i+2)
  {
    myGLCD.drawPixel(i,cbuf[i-1],IHM_BLACK);
  }

// Draw sin-lines, cos-lines  
  delta++;
  if (delta == 318) delta = 0;
  for (int i=1; i<318; i=i+2)
  {
    sbuf[i-1] = 119+(sin((((i+delta)*1.13)*3.14)/180)*95);
    myGLCD.drawPixel(i,sbuf[i-1],IHM_CYAN);
  }
  for (int i=1; i<318; i=i+2)
  {
    cbuf[i-1] = 119+(cos((((i+delta)*1.13)*3.14)/180)*95);
    myGLCD.drawPixel(i,cbuf[i-1],IHM_YELLOW);
  }

  myGLCD.setTextColor(IHM_CYAN);
//  myGLCD.drawString("Sin", 5, 15,2);
  _drawString("Sin", 5, 15,2);
  myGLCD.setTextColor(IHM_YELLOW);
//  myGLCD.drawString("Cos", 5, 30,2);
  _drawString("Cos", 5, 30,2);
  myGLCD.drawLine(159, 15, 159, 224,IHM_BLUE);
  myGLCD.drawLine(1, 119, 318, 119,IHM_BLUE);
}
