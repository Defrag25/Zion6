//////////////////////////////////////////////////////////////////
// TTGO I2C
//////////////////////////////////////////////////////////////////

// Provides a graphical output on the built in display of the TTGO for both
// Temperature and humidity or switch between those and heat index with a
// push of a button.  The second button switches everything between Celsius

 
// Core : TTGO LoRa32-OLED V1
// 
// ATTENTION 
//
// >> Penser à modifier le fichier de définition de l'afficheur "User_Setup_Select.h"
// C:\Users\.......\Documents\Arduino\libraries\TFT_eSPI\User_Setup_Select.h
// >>>   #include <User_Setups/Setup25_TTGO_T_Display.h>
// C:\Users\.......\Documents\Arduino\libraries\TFT_eSPI\User_Setups\Setup25_TTGO_T_Display.h
// >>>   #define TFT_WIDTH  135
// >>>   #define TFT_HEIGHT 240

// 1.8 Modification des angles, comptage du nombre de tours
// 
#define __VERSION__ "1.8"
#define __AUTEUR__ "EMJ"



//void AngRefresh();

const long refreshTime = 10; // 10ms
const long researchTime = 1000; // recherche ajout ou perte periph

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MACRO a placer dans le fichier racine du projet                                                                                                      //
#define MName char s[] = __FILE__; byte b = sizeof(s); while ( (b > 0) && (s[b] != '\\')) b--;  char *filename = &s[++b]; //Serial.println(filename);     //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





boolean CheckOffset=false;
int count;

#include "esp32-hal-gpio.h"
#include "Zion6_Utils.h"
#include "Zion6_Pinout.h"
#include <Wire.h>
#include <TFT_eSPI.h>
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();
#include "Zion6_I2c.h"


    
#define BUTTON1PIN 35
#define BUTTON2PIN 0



hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR onTime() {
   portENTER_CRITICAL_ISR(&timerMux);
   count++;
    //Zion6_checkPCF(); 
    //Zion6_checkAS(); 

   portEXIT_CRITICAL_ISR(&timerMux);
}
long lastDebounceButton1 = 0;    // Holds Button1 last debounce
long lastDebounceButton2 = 0;    // Holds Button2 last debounce
long debounceDelay       = 50;  // 200ms between re-polling

// INTRPT Function to execute when Button 1 is Pushed
void IRAM_ATTR toggleButton1() {
  bShowScreen1=true;bShowScreen2=false;bScreen1=false;
 
}

// INTRPT Function to execute when Button 2 is Pushed
void IRAM_ATTR toggleButton2() {
    bShowScreen2=true;bShowScreen1=false;bScreen2=false;
  CheckOffset=true;
}



//void AngRefresh(){
//  tft.setTextColor(TFT_GREEN, TFT_BLACK);
//  tft.setCursor(0, 150);
//  tft.setTextSize(1);
//  tft.print("AS1:"); tft.print(0.000);tft.println("   ");//Angle1);
//  tft.print("AS2:"); tft.print(Angle2);tft.println("   ");
//}

long lastm;
long lastr;

void setup() {
  lastm=millis();
  lastr=millis();
   
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,13,15);
  pinMode(FDC_REF1,OUTPUT);
  pinMode(FDC_REF2,OUTPUT);
  pinMode(FDC_REF3,OUTPUT);
  pinMode(FDC_REF4,OUTPUT);
  pinMode(FDC_REF5,OUTPUT);
  pinMode(FDC_REF6,OUTPUT);
  Wire.begin();
   MName;                  //
  Serial.print("Welcome ");Serial.println(filename); // Réutilisation du nom
  Serial.println("avec visu axe via listener");
  
  pinMode(BUTTON1PIN, INPUT_PULLUP);
  pinMode(BUTTON2PIN, INPUT_PULLUP);
  attachInterrupt(BUTTON1PIN, toggleButton1, FALLING);
  attachInterrupt(BUTTON2PIN, toggleButton2, FALLING);

  tft.begin();
  tft.setRotation(2); //Landscape
  presentation();
  I2CSlavesCreateListe(true);
  I2CSlavesAnalyse(true);
 // Zion6_initPCF();
  zion6_i2c_init();
 
  tft.println();
  tft.print(filename);tft.print(" ");tft.println(__VERSION__);
  tft.println(__DATE__);
  tft.println(__AUTEUR__); 
  tft.println("Zion6");
  delay(250); 
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
 
 
 

  tStart=millis();
  tStop=millis();
 // Configure le Prescaler a 80 le quart de l ESP32 est cadence a 80Mhz
 // 80000000 / 80 = 1000000 tics / seconde
  timer = timerBegin(0, 80, true);                
  timerAttachInterrupt(timer, &onTime, true);    
    
   // Regle le declenchement d une alarme chaque seconde
  timerAlarmWrite(timer, 10000, true);           
  timerAlarmEnable(timer);
  bScreen1=false;
  bScreen2=false;
  bShowScreen1 = true;
  bShowScreen1 = false;

  pinMode(FDC_REF1,OUTPUT);
  pinMode(FDC_REF2,OUTPUT);
  pinMode(FDC_REF3,OUTPUT);
  pinMode(FDC_REF4,OUTPUT);
  pinMode(FDC_REF5,OUTPUT);
  pinMode(FDC_REF6,OUTPUT);
  digitalWrite(FDC_REF1,1);
  digitalWrite(FDC_REF2,1);
  digitalWrite(FDC_REF3,1);
  digitalWrite(FDC_REF4,1);
  digitalWrite(FDC_REF5,1);
  digitalWrite(FDC_REF6,1);
  Zion6_InitAngle();
  //Zion6_getOffset(); 
}

void loop() {
 // delay(1000);  //Required by this device to function properly
 tStart=micros();
 //
 if (CheckOffset==true)
  {
    Zion6_getOffset(); 
    CheckOffset=false;
  }
  //if((millis()-lastm)>refreshTime)
  //{ // rafraichissement périodique 10ms
  //  lastm=millis();
  //}
 if(0){ 
  if((millis()-lastr)>researchTime)
   { // recherche périodique 1s
    int  lnbPCF=nbPCF;
    int  lnbAS=nbAS;
    I2CSlavesCreateListe(false);
    I2CSlavesAnalyse(false);
    lastr=millis();
    if ( (lnbPCF!=nbPCF)|| (lnbAS!=nbAS) )
     {
        I2CSlavesCreateListe(true);
    I2CSlavesAnalyse(true);
      bScreen1=false;
      bScreen2=false;
      
     }
    // Serial.println("Searching");
   }
 }
  Zion6_checkPCF(); 
  Zion6_checkAS(); 
  Zion6ProcessFDC();
  

  if (  bShowScreen1)  { Zion6_refreshPCF();}
  if ( !bShowScreen1) { Zion6_refreshAS();}
 
  //if (flgButton1!=lflgButton1)
  tStop=micros();
  Zion6TransmitAll();
  Zion6TransmitAllToPC();
 

 delay(10);
}
