


#include "tft_due.h"
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // reset

#include "TouchScreen_kbv.h"
#include <SPI.h>          // for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;

void TFTInit(){
   uint16_t ID = tft.readID(); //
     if (ID == 0xD3D3) ID = 0x9481; // write-only shield
    tft.begin(ID);
    tft.setRotation(3);
      tft.fillScreen(IHM_BLACK);
  PrintVersion(true);
}

void printStringColor(char *str,uint16_t Color,uint8_t Size)
{
  tft.setTextSize(Size); 
 // Tsize=Size ;
 TFtColor=Color;
  tft.setTextColor(Color,IHM_BLACK); 
  while(*str) printChar(str++);
}

void printChar(char *c){
  uint16_t TempColorFont = IHM_BLUE;
  uint16_t TempColorBk   = IHM_BLACK; 
 //  if((c>=0x80)&(c>=0x89)) { MenuState=c-0x80; return;  }
 // Coloration des caracteres num
     //if ( ((c>=0x30)&(c<=0x39)) |(c=='.')|(c=='-'))  my_lcd.Set_Text_colour(BLUE); 
 if(*c==0x0d) 
  {
    CRLF(); // Efface le reste de la ligne
  }
 else
  {
   if(*c==0x0a)return;
   tft.setCursor(TXpos,TYpos);
   tft.write(*c); //    
   TXpos+=Tsize*_TXsize;
   if(TXpos>TXMax-5) { TXpos = TXposOffset+TXMin; TYpos+=Tsize*_TYsize;} //480
   }
  if(TYpos>(TYMax+Tsize*_TYsize)) {TYpos=TYMin;}         // SCROLLING TEST
  //if(TYpos>(TYMax+Tsize*_TYsize)) Terminal_Scroll(8);
  tft.setTextColor(TempColorFont); 
}
void CRLF(){
  
  for(uint8_t n=0;n<_TYsize*Tsize;n=n+1)  {      tft.drawFastHLine(TXpos, TYpos+n, TXMax-1-TXpos, IHM_BLACK);    }
  TXpos=TXposOffset+TXMin;TYpos+=Tsize*_TYsize;
  //Efface le texte de toute la ligne suivante si pas de depacement
  if(TYpos>TYMax-2)TYpos=TYMin;
  for(uint8_t n=0;n<_TYsize*Tsize;n++)  {       tft.drawFastHLine(TXpos, TYpos+n, TXMax-1-TXpos, IHM_BLACK);      }
  tft.setCursor(TXpos ,TYpos);
}

void printStringlnColor(char *str,uint16_t Color,uint8_t Size)
{
  tft.setTextSize(Size);
  Tsize=Size ; TFtColor=Color;
  tft.setTextColor(Color); 
  while(*str) printChar(str++);
  CRLF();
}

void PrintVersion(bool tp){ //Doit se situer dans la racine  

   CRLF();
   printStringColor("Date    :",IHM_BLUE,1); printStringColor(__DATE__,IHM_WHITE,1);printStringColor(" | ",IHM_WHITE,1);printStringlnColor(__TIME__,IHM_WHITE,1);
 
}

#include "SixDOF.h"
#include "DUEMatrices.h"


double thetas[] = {0, PI/2, -PI/2, 0, PI, 0};
double ds[] = {0.25, 0, 0, 0.2, 0, 0.2};
double alphas[] = {PI/2, 0, -PI/2, PI/2, PI/2, 0};
double as[] = {0, 0.25, 0, 0, 0, 0};

double jointAngles[] = {0, PI/3, PI/2, 0, -PI/4, 0};
double jointAngles2[] = {0, PI/4, 0, 0, PI/3, 0};

double pose[] = {0, 0, 0, 0, 0, 0};

double desiredPose1[] = {-0.4501, 0.15, 0.5777, 2.2923, 1.5234, -0.6599};
double desiredPose2[] = {-0.4485, 0.1225, 0.1147, 2.3934, 2.0215, 0.5019};
double desiredPose3[] = {0, -0.45, 0.05, -1.5708, 1.5708, -2.3562};

SixDOF manipulator(thetas, ds, alphas, as, 6);

void setup() {
  TFTInit();
  Serial.begin(115200);

  Serial.print("x");
  Serial.print("\t");
  Serial.print("y");
  Serial.print("\t");
  Serial.print("z");
  Serial.print("\t");
  Serial.print("theta");
  Serial.print("\t");
  Serial.print("phi");
  Serial.print("\t");
  Serial.print("psi");
  Serial.println();

  delay(50);
  
  manipulator.forwardKinematics(jointAngles);
  
  Serial.println("FStep 1");
//  Serial.println(freeMemory());
//  Serial.println();
}

void printTAB(double* T){
  Serial.print(T[0]);  Serial.print("\t");
  Serial.print(T[1]);  Serial.print("\t");
  Serial.print(T[2]);  Serial.print("\t");
  Serial.print(T[3]);  Serial.print("\t");
  Serial.print(T[4]);  Serial.print("\t");
  Serial.print(T[5]);  Serial.println();
  
}

void loop() {

  manipulator.getPose(pose);

  
  // Angles are printed in degrees.
  // The function calls below shows how easy it is to get the results from the inverse kinematics solution.
//  Serial.print(pose[0]);
//  Serial.print("\t");
//  Serial.print(pose[1]);
//  Serial.print("\t");
//  Serial.print(pose[2]);
//  Serial.print("\t");
//  Serial.print(pose[3]);
//  Serial.print("\t");
//  Serial.print(pose[4]);
//  Serial.print("\t");
//  Serial.print(pose[5]);
//  Serial.println(); Serial.println();
printTAB( pose);
printTAB( pose);
printTAB( pose);

  do {
Serial.println("Step 4");   
    manipulator.inverseKinematics(desiredPose1[0], 
                                  desiredPose1[1], 
                                  desiredPose1[2], 
                                  desiredPose1[3], 
                                  desiredPose1[4], 
                                  desiredPose1[5], 0, 5);

Serial.println("Step 5");   
delay(500);
manipulator.getPose(pose);
  Serial.println("Step 6");   
    // Angles are printed in degrees.
    // The function calls below shows how easy it is to get the results from the inverse kinematics solution.
    Serial.print(pose[0]);
    Serial.print(" --> ");
    Serial.print(desiredPose1[0]);
    Serial.print("\t");
    Serial.print(pose[1]);
    Serial.print(" --> ");
    Serial.print(desiredPose1[1]);
    Serial.print("\t");
    Serial.print(pose[2]);
    Serial.print(" --> ");
    Serial.print(desiredPose1[2]);
    Serial.print("\t");
    Serial.print(pose[3]);
    Serial.print(" --> ");
    Serial.print(desiredPose1[3]);
    Serial.print("\t");
    Serial.print(pose[4]);
    Serial.print(" --> ");
    Serial.print(desiredPose1[4]);
    Serial.print("\t");
    Serial.print(pose[5]);
    Serial.print(" --> ");
    Serial.print(desiredPose1[5]);
    Serial.println();
  
    manipulator.getJointAngles(jointAngles);
    Serial.print(jointAngles[0]);
    Serial.print("\t");
    Serial.print(jointAngles[1]);
    Serial.print("\t");
    Serial.print(jointAngles[2]);
    Serial.print("\t");
    Serial.print(jointAngles[3]);
    Serial.print("\t");
    Serial.print(jointAngles[4]);
    Serial.print("\t");
    Serial.print(jointAngles[5]);
    Serial.println();

  } while (manipulator.getIKStatus() == SixDOF::FAILED);

//  Serial.print("Free memory: ");
//  Serial.println(freeMemory());
//  Serial.println();

  Serial.println("============================================");
  
  delay(100);
  
  do {

    manipulator.inverseKinematics(desiredPose2[0], 
                                  desiredPose2[1], 
                                  desiredPose2[2], 
                                  desiredPose2[3], 
                                  desiredPose2[4], 
                                  desiredPose2[5], 0.05, 1.8);


    manipulator.getPose(pose);
  
    // Angles are printed in degrees.
    // The function calls below shows how easy it is to get the results from the inverse kinematics solution.
    Serial.print(pose[0]);
    Serial.print(" --> ");
    Serial.print(desiredPose2[0]);
    Serial.print("\t");
    Serial.print(pose[1]);
    Serial.print(" --> ");
    Serial.print(desiredPose2[1]);
    Serial.print("\t");
    Serial.print(pose[2]);
    Serial.print(" --> ");
    Serial.print(desiredPose2[2]);
    Serial.print("\t");
    Serial.print(pose[3]);
    Serial.print(" --> ");
    Serial.print(desiredPose2[3]);
    Serial.print("\t");
    Serial.print(pose[4]);
    Serial.print(" --> ");
    Serial.print(desiredPose2[4]);
    Serial.print("\t");
    Serial.print(pose[5]);
    Serial.print(" --> ");
    Serial.print(desiredPose2[5]);
    Serial.println();
  
    manipulator.getJointAngles(jointAngles);
    Serial.print(jointAngles[0]);
    Serial.print("\t");
    Serial.print(jointAngles[1]);
    Serial.print("\t");
    Serial.print(jointAngles[2]);
    Serial.print("\t");
    Serial.print(jointAngles[3]);
    Serial.print("\t");
    Serial.print(jointAngles[4]);
    Serial.print("\t");
    Serial.print(jointAngles[5]);
    Serial.println();

  } while (manipulator.getIKStatus() == SixDOF::FAILED);

//  Serial.print("Free memory: ");
//  Serial.println(freeMemory());
//  Serial.println();

  Serial.println("============================================");

  delay(100);
  
  do {

    manipulator.inverseKinematics(desiredPose3[0], 
                                  desiredPose3[1], 
                                  desiredPose3[2], 
                                  desiredPose3[3], 
                                  desiredPose3[4], 
                                  desiredPose3[5], 0.05, 1.8);


    manipulator.getPose(pose);
  
    // Angles are printed in degrees.
    // The function calls below shows how easy it is to get the results from the inverse kinematics solution.
    Serial.print(pose[0]);
    Serial.print(" --> ");
    Serial.print(desiredPose3[0]);
    Serial.print("\t");
    Serial.print(pose[1]);
    Serial.print(" --> ");
    Serial.print(desiredPose3[1]);
    Serial.print("\t");
    Serial.print(pose[2]);
    Serial.print(" --> ");
    Serial.print(desiredPose3[2]);
    Serial.print("\t");
    Serial.print(pose[3]);
    Serial.print(" --> ");
    Serial.print(desiredPose3[3]);
    Serial.print("\t");
    Serial.print(pose[4]);
    Serial.print(" --> ");
    Serial.print(desiredPose3[4]);
    Serial.print("\t");
    Serial.print(pose[5]);
    Serial.print(" --> ");
    Serial.print(desiredPose3[5]);
    Serial.println();
  
    manipulator.getJointAngles(jointAngles);
    Serial.print(jointAngles[0]);
    Serial.print("\t");
    Serial.print(jointAngles[1]);
    Serial.print("\t");
    Serial.print(jointAngles[2]);
    Serial.print("\t");
    Serial.print(jointAngles[3]);
    Serial.print("\t");
    Serial.print(jointAngles[4]);
    Serial.print("\t");
    Serial.print(jointAngles[5]);
    Serial.println();

  } while (manipulator.getIKStatus() == SixDOF::FAILED);

//  Serial.print("Free memory: ");
//  Serial.println(freeMemory());
//  Serial.println();

  Serial.println("============================================");
  Serial.println("END");
  Serial.println("============================================");
  Serial.print("END");
  while(1){};
}
