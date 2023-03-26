#define FIRMWARE_VERSION  "DUE kbv 029"
#define PROJET __FILE__
#define Auteur "EMJ"



#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // reset

#include "TouchScreen_kbv.h"
#include <SPI.h>          // for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>

#include "LIB_ENCODER.h"

MCUFRIEND_kbv tft;

// JPEG decoder library
//#include <JPEGDecoder.h>
#include "DrawArc.h"

#include "variables.h"

//Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define DEBUGSerial Serial
#define CNCSerial   Serial3
//#define Serial Serial1

//void setup(void);
//void loop(void);

//uint16_t g_identifier;

// long Ttime=millis();


void setup(void) {
  DEBUGSerial.begin(115200);
  CNCSerial.begin(115200);
  Serial.begin(115200);
  for (uint8_t i=22;i<=37;i++){   pinMode(i,INPUT_PULLUP);  }

  do { uint8_t Vidage=CNCSerial.read(); } while (Serial.available()>0);

  DEBUGSerial.print(F("Projet  : ")); DEBUGSerial.println(PROJET);
  DEBUGSerial.print(F("Version : ")); DEBUGSerial.println(FIRMWARE_VERSION);
  DEBUGSerial.print(F("Date    : ")); DEBUGSerial.print(__DATE__); DEBUGSerial.print(" "); DEBUGSerial.println(__TIME__);
  
    uint32_t when = millis();
    //    while (!Serial) ;   //hangs a Leonardo until you connect aCNCSerial
    //if (!Serial) delay(50);           //allow some time for Leonardo
    DEBUGSerial.println("Serial took " + String((millis() - when)) + "ms to start");
    //    tft.reset();                 //hardware reset
    uint16_t ID = tft.readID(); //
    DEBUGSerial.print("ID = 0x");    DEBUGSerial.println(ID, HEX);
    if (ID == 0xD3D3) ID = 0x9481; // write-only shield
    tft.begin(ID);
    tft.setRotation(3);

  DEBUGSerial.print(F("ID TFT  : ")); DEBUGSerial.print(ID,HEX);      DEBUGSerial.print(" ("); DEBUGSerial.print(tft.width());
  DEBUGSerial.print(F("x"));          DEBUGSerial.print(tft.height());DEBUGSerial.print("):"); DEBUGSerial.println(3);
  DEBUGSerial.println();
  DEBUGSerial.println(F("System Setup"));
//  EEPROMFirstStart(0);   //  printStringlnColor("EEPROM First Start",WHITE,1);
  CNC_Init2();
  
  IHM_Init();

  Intro();
  
  tft.fillScreen(IHM_BLACK);
  //PrintVersion();   waitForTouchAndPrint();
  //delay(1500);
 // WindowsErase();
  arcloop() ;
  encoderInit();
 
    
  
}


void loop(void) {
    IHM_Loop();
}

void PrintVersion(){ //Doit se situer dans la racine  

   CRLF();
   printStringColor("Date    :",IHM_BLUE,1); printStringColor(__DATE__,IHM_WHITE,1);printStringColor(" | ",IHM_WHITE,1);printStringlnColor(__TIME__,IHM_WHITE,1);
   printStringColor("Projet  :",IHM_BLUE,1); printStringlnColor(PROJET,IHM_WHITE,1);
   printStringColor("Auteur  :",IHM_BLUE,1); printStringlnColor(Auteur,IHM_WHITE,1);
   printStringColor("Version :",IHM_BLUE,1); printStringlnColor(FIRMWARE_VERSION,IHM_WHITE,1);

}
