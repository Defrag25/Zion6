#pragma once

#include "LIB_AS5600L.h"
#include "Zion6_Utils.h"

int expread(int add);
void expwrite(int add, int dat);
void zion6_i2c_init();
void Zion6_checkPCF();
void Zion6_checkAS();
void Zion6_refreshPCF();
void Zion6_refreshAS();
void Zion6TransmitAll();
void Zion6TransmitAllToPC();
void showScrn1(int col, int in) ;
void Zion6ProcessFDC();
void I2CSlavesAnalyse(boolean prn);
void Zion6_initPCF();
void Zion6_getOffset();

void  I2CSlavesCreateListe(boolean prn);
boolean i2cScannAdd(int address) ;
void Zion6_InitAngle();

const int nbDevMax = 20;
int liste[nbDevMax]; // 10 esclaves maxi
// si = 0 alors fin de table
// si 0x20 <= x <=0x27  - PCF8574
// si x=0x36            - AS5600
// si 0x40 <= x <=0x47  - AS5600L
// Scan I2CSlaves permet de creer cette table
const int listeStart = 0x20;
const int listeStop  = 0x47;

bool listePCF[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //[0x20-0x27]
bool listeAS[7] = {0, 0, 0, 0, 0, 0, 0}; //[0x40-0x46]

long tStart;
long tStop;

AMS_5600 AS1;
AMS_5600 AS2;
AMS_5600 AS3;
AMS_5600 AS4;
AMS_5600 AS5;
AMS_5600 AS6;
AMS_5600 AS7;

float Angle[6];           // Angle direct 0 à 360°
float lAngle[6];          // last Angle direct
float turnAngle[6];       // Nombre de tours
float realAngle[6];       // Angle -n à n
float laffAngle[6];
float offsetAngle[6];
volatile bool bShowScreen1, bScreen1;
volatile bool bShowScreen2, bScreen2;




//float Angle[6]={0.0,0.0,0.0,0.0,0.0,0.0};


#include "PCF8574.h" // Required for PCF8574
PCF8574 expander1(0x20);
PCF8574 expander2(0x21);
PCF8574 expander3(0x22);
PCF8574 expander4(0x23);
PCF8574 expander5(0x24);
PCF8574 expander6(0x25);
PCF8574 expander7(0x26);
PCF8574 expander8(0x27);


int PCF1, lPCF1;
int PCF2, lPCF2;
int PCF3, lPCF3;
int PCF4, lPCF4;
int PCF5, lPCF5;
int PCF6, lPCF6;
int PCF7, lPCF7;
int PCF8, lPCF8;

int nbPCF;
int nbAS;



int expread(int add) {
  Wire.begin();
  Wire.requestFrom(add, 1);
  int i = Wire.read();
  Wire.endTransmission();
  return (i);
}

void expwrite(int add, int dat) {
  Wire.begin();
  Wire.write(dat);
  Wire.endTransmission();
}




void zion6_i2c_init() {


  if (listePCF[0]) {
    expander1.begin();
    expander1.pinMode(0, INPUT_PULLUP);
    expander1.pinMode(1, INPUT_PULLUP);
    expander1.pinMode(2, INPUT_PULLUP);
    expander1.pinMode(3, INPUT_PULLUP);
    expander1.pinMode(4, INPUT_PULLUP);
    expander1.pinMode(5, INPUT_PULLUP);
    expander1.pinMode(6, INPUT_PULLUP);
    expander1.pinMode(7, INPUT_PULLUP);
    PCF1 = expread(0x20); lPCF1 = !PCF1;
  }


  if (listePCF[1]) {
    expander2.begin();
    expander2.pinMode(0, INPUT_PULLUP);
    expander2.pinMode(1, INPUT_PULLUP);
    expander2.pinMode(2, INPUT_PULLUP);
    expander2.pinMode(3, INPUT_PULLUP);
    expander2.pinMode(4, INPUT_PULLUP);
    expander2.pinMode(5, INPUT_PULLUP);
    expander2.pinMode(6, INPUT_PULLUP);
    expander2.pinMode(7, INPUT_PULLUP);
    PCF2 = expread(0x21); lPCF2 = !PCF2;
  }


  if (listePCF[2]) {
    expander3.begin();
    expander3.pinMode(0, INPUT_PULLUP);
    expander3.pinMode(1, INPUT_PULLUP);
    expander3.pinMode(2, INPUT_PULLUP);
    expander3.pinMode(3, INPUT_PULLUP);
    expander3.pinMode(4, INPUT_PULLUP);
    expander3.pinMode(5, INPUT_PULLUP);
    expander3.pinMode(6, INPUT_PULLUP);
    expander3.pinMode(7, INPUT_PULLUP);
    PCF3 = expread(0x22); lPCF3 = !PCF3;
  }


  if (listePCF[3]) {
    expander4.begin();
    expander4.pinMode(0, INPUT_PULLUP);
    expander4.pinMode(1, INPUT_PULLUP);
    expander4.pinMode(2, INPUT_PULLUP);
    expander4.pinMode(3, INPUT_PULLUP);
    expander4.pinMode(4, INPUT_PULLUP);
    expander4.pinMode(5, INPUT_PULLUP);
    expander4.pinMode(6, INPUT_PULLUP);
    expander4.pinMode(7, INPUT_PULLUP);
    PCF4 = expread(0x23); lPCF4 = !PCF4;
  }

  if (listePCF[4]) {
    expander5.begin();
    expander5.pinMode(0, INPUT_PULLUP);
    expander5.pinMode(1, INPUT_PULLUP);
    expander5.pinMode(2, INPUT_PULLUP);
    expander5.pinMode(3, INPUT_PULLUP);
    expander5.pinMode(4, INPUT_PULLUP);
    expander5.pinMode(5, INPUT_PULLUP);
    expander5.pinMode(6, INPUT_PULLUP);
    expander5.pinMode(7, INPUT_PULLUP);
    PCF5 = expread(0x24); lPCF5 = !PCF5;
  }

  if (listePCF[5]) {
    expander6.begin();
    expander6.pinMode(0, INPUT_PULLUP);
    expander6.pinMode(1, INPUT_PULLUP);
    expander6.pinMode(2, INPUT_PULLUP);
    expander6.pinMode(3, INPUT_PULLUP);
    expander6.pinMode(4, INPUT_PULLUP);
    expander6.pinMode(5, INPUT_PULLUP);
    expander6.pinMode(6, INPUT_PULLUP);
    expander6.pinMode(7, INPUT_PULLUP);
    PCF6 = expread(0x25); lPCF6 = !PCF6;
  }
  if (listePCF[6]) {
    expander7.begin();

    expander7.pinMode(0, INPUT_PULLUP);
    expander7.pinMode(1, INPUT_PULLUP);
    expander7.pinMode(2, INPUT_PULLUP);
    expander7.pinMode(3, INPUT_PULLUP);
    expander7.pinMode(4, INPUT_PULLUP);
    expander7.pinMode(5, INPUT_PULLUP);
    expander7.pinMode(6, INPUT_PULLUP);
    expander7.pinMode(7, INPUT_PULLUP);
    PCF7 = expread(0x26); lPCF7 = !PCF7;
  }

  if (listeAS[0]) {
    AS1.setAddTemp(0x40);
  }
  if (listeAS[1]) {
    AS2.setAddTemp(0x41);
  }
  if (listeAS[2]) {
    AS3.setAddTemp(0x42);
  }
  if (listeAS[3]) {
    AS4.setAddTemp(0x43);
  }
  if (listeAS[4]) {
    AS5.setAddTemp(0x44);
  }
  if (listeAS[5]) {
    AS6.setAddTemp(0x45);
  }
  if (listeAS[6]) {
    AS7.setAddTemp(0x46);
  }
}

void  I2CSlavesCreateListe(boolean prn) {
  if (prn)
  {
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.setCursor(0, 10);
    tft.println("listing I2C devices");

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setCursor(0, 20);
  }
  int device = 0;

  if (prn ) {
    Serial.print("Scanning I2C ");
  }
  for ( int nb = listeStart; nb <= listeStop; nb++) {
    liste[device] = 0;   // place l'addresse dans liste[]
  }
  for ( int nb = listeStart; nb <= listeStop; nb++) {
    if  ( i2cScannAdd(nb) ) {
      if (prn) {
        Serial.print(".");
      }
      liste[device] = nb;   // place l'addresse dans liste[]
      device++;
      if (device >= nbDevMax) break;
    }
  }
  if (prn)
  {
    Serial.println("");
    tft.println("}");
    if (device > 0)
    {
      int i = 0;
      Serial.print(device); Serial.println(" devices found");
      Serial.print("{");
      tft.print("{ ");
      do
      {
        Serial.print("0x"); Serial.print(liste[i], HEX); Serial.print(";");
        tft.print("0x"); tft.print(liste[i], HEX); tft.print(" ");
        i++;
      } while (liste[i] != 0);
      Serial.println("}");
      tft.print("}");
    }
    else
    {
      Serial.println("no devices found");
      tft.print("no devices found");
    }
  }
}

void I2CSlavesAnalyse(boolean prn) {
  if (prn)
  {
    tft.setTextSize(1);
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.setCursor(0, 50);
    tft.println("Analyse I2C devices");
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setCursor(0, 60);
  }
  int i = 0;
  nbPCF = 0;
  nbAS = 0;
  for (int pcf = 0; pcf < 8; pcf++) {
    listePCF[pcf] = false;
  }
  for (int _as = 0; _as < 6; _as++) {
    listeAS[_as] = false;
  }
  do
  { int v = liste[i];
    if (v >= 0x20 && v <= 0x27) {
      nbPCF++;
      listePCF[v - 0x20] = true;
    }
    if (v >= 0x40 && v <= 0x47) {
      nbAS++;
      listeAS[v - 0x40] = true;
    }

    i++;
  } while (liste[i] != 0);
  if (prn)
  {
    Serial.print(nbPCF); Serial.println(" PCF8574 found");
    Serial.print(nbAS);  Serial.println(" AS5600 found");
    tft.setTextColor(TFT_RED, TFT_BLACK); tft.print(nbPCF);   tft.setTextColor(TFT_BLUE, TFT_BLACK);  tft.println(" PCF8574 found");
    tft.setTextColor(TFT_RED, TFT_BLACK); tft.print(nbAS);    tft.setTextColor(TFT_BLUE, TFT_BLACK);  tft.println(" AS5600 found");

    tft.println(); tft.println();
    tft.print("PCF "); for (int t = 0; t <= 7; t++)   {
      listePCF[t] ? tft.print("1") : tft.print("0");
    }
    tft.println();
    tft.print("AS  "); for (int t = 0; t <= 5; t++)   {
      listeAS[t] ? tft.print("1") : tft.print("0");
    }
    tft.println();
  }
}

boolean i2cScannAdd(int address) {

  if (address > 127) return (false);
  Wire.beginTransmission(address);
  byte error = Wire.endTransmission();
  if (error == 0) {
    return (true);
  }
  return (false);
}


void showScrn1Init() {
  //if( bScreen1 == false)
  {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, 20);
    tft.println("8x PCF8574");
    tft.drawLine(0, 39, TFT_WIDTH, 39, TFT_BLUE);
    for ( int j = 0; j <= 7; j++) {
      for ( int i = 0 ; i <= 7; i++) {
        tft.drawCircle(10 + 15 * i, 15 * (j) + 50, 6, TFT_GRAY);
      }
    }
    Serial.println("Screen 1 init done");
  }

  bScreen1 = true;
  lPCF1 = PCF1 - 1;
  lPCF2 = PCF2 - 1;
  lPCF3 = PCF3 - 1;
  lPCF4 = PCF4 - 1;
  lPCF5 = PCF5 - 1;
  lPCF6 = PCF6 - 1;
  lPCF7 = PCF7 - 1;
  lPCF8 = PCF8 - 1;
}

void showScrn1(int col, int in) {
  for ( int i = 0 ; i <= 7; i++) {
    tft.drawCircle(10 + 15 * i, 15 * (col - 1) + 50, 6, TFT_BLUE);
    if (bitRead(in, i))   {
      tft.fillCircle(10 + 15 * i, 15 * (col - 1) + 50, 4, TFT_GREEN);
    }
    else                 {
      tft.fillCircle(10 + 15 * i, 15 * (col - 1) + 50, 4, TFT_BLACK);
    }
  }
}

void showScrn2Init() {
  //if( bScreen2 == false)
  {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, 20);
    tft.println("6x AS5600L");
    tft.setTextSize(1);
    tft.drawLine(0, 39, TFT_WIDTH, 39, TFT_BLUE);
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    for ( int j = 0; j < 6; j++) {
      tft.setCursor(0, (15 * j) + 50);
      tft.setTextColor(TFT_BLUE, TFT_BLACK);  tft.print("Angle"); tft.print(j);
      tft.setTextColor(TFT_RED, TFT_BLACK); tft.print("(0x4"); tft.print(j); tft.print(")");
    }
    Serial.println("Screen 2 init done");
  }

  bScreen2 = true;
  for (int n = 0; n < 6; n++) {
    laffAngle[n] = Angle[n] - 1;
  }
  //  laffAngle1=Angle1-1;
  //  laffAngle2=Angle2-1;
  //  laffAngle3=Angle3-1;
  //  laffAngle4=Angle4-1;
  //  laffAngle5=Angle5-1;
  //  laffAngle6=Angle6-1;
}
void showBIGScrn2Init() {
  //if( bScreen2 == false)
  {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, 20);
    //tft.println(" AS5600L");
    //tft.setTextSize(2);
    //tft.drawLine(0, 39, TFT_WIDTH, 39, TFT_BLUE);
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    for ( int j = 0; j < 6; j++) {
      tft.setCursor(0, (30 * j) + 20);
      tft.setTextColor(TFT_BLUE, TFT_BLACK); tft.print(j);
    }
    Serial.println("BIG Screen 2 init done");
  }

  bScreen2 = true;
  for (int n = 0; n < 6; n++) {
    laffAngle[n] = Angle[n] - 1;
  }
  //  laffAngle1=Angle1-1;
  //  laffAngle2=Angle2-1;
  //  laffAngle3=Angle3-1;
  //  laffAngle4=Angle4-1;
  //  laffAngle5=Angle5-1;
  //  laffAngle6=Angle6-1;
}

void showScrn2(int col, float in) {
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextSize(1);
  tft.setCursor(80, (15 * (col - 1)) + 50);
  tft.print(in);  tft.print("  ");
}
void showBIGScrn2(int col, float in) {
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(20, (30 * (col - 1)) + 20);
  tft.print(in);  tft.print("  ");
}

void Zion6_checkPCF() {
  if ( listePCF[0] ) {
    PCF1 = expread(0x20);
  }
  if ( listePCF[1] ) {
    PCF2 = expread(0x21);
  }
  if ( listePCF[2] ) {
    PCF3 = expread(0x22);
  }
  if ( listePCF[3] ) {
    PCF4 = expread(0x23);
  }
  if ( listePCF[4] ) {
    PCF5 = expread(0x24);
  }
  if ( listePCF[5] ) {
    PCF6 = expread(0x25);
  }
  if ( listePCF[6] ) {
    PCF7 = expread(0x26);
  }
  if ( listePCF[7] ) {
    PCF8 = expread(0x27);
  }
}
void Zion6_initPCF() {
  if ( listePCF[0] ) {
    expwrite(0x20, 0xFF);
  }
  if ( listePCF[1] ) {
    expwrite(0x21, 0xFE);  //
  }
  if ( listePCF[2] ) {
    expwrite(0x22, 0xFF);
  }
  if ( listePCF[3] ) {
    expwrite(0x23, 0xFF);
  }
  if ( listePCF[4] ) {
    expwrite(0x24, 0xFF);
  }
  if ( listePCF[5] ) {
    expwrite(0x25, 0xFF);
  }
  if ( listePCF[6] ) {
    expwrite(0x26, 0xFF);
  }
  if ( listePCF[7] ) {
    expwrite(0x27, 0xFF);
  }
}


void Zion6_ProcessAngle(int m, float AngleNew) {
  if ( (AngleNew >= 0) && (AngleNew <= 360) )
  {
    if ((lAngle[m]>AngleNew)&&(abs)(lAngle[m]-AngleNew)>200){turnAngle[m]++;}
    if ((lAngle[m]<AngleNew)&&(abs)(lAngle[m]-AngleNew)>200){turnAngle[m]--;}
    
//    if ( (lAngle[m] > 190) && (AngleNew < 170)) {
//      turnAngle[m]++;
//    }
//    if ( (lAngle[m] < 170) && (AngleNew > 190)) {
//      turnAngle[m]--;
//    }
    Angle[m] = AngleNew;
    lAngle[m] = AngleNew;
    realAngle[m] = 360 * turnAngle[m] + AngleNew - offsetAngle[m];
  }
}

void Zion6_InitAngle() {
  if ( listeAS[0] ) {
    Angle[0] = (float)(AS1.getRawAngle()) * AS5600_RAW_TO_DEGREES;
    lAngle[0] = Angle[0];
    turnAngle[0] = 0;
    offsetAngle[0] = Angle[0];
  }
  if ( listeAS[1] ) {
    Angle[1] = (float)(AS2.getRawAngle()) * AS5600_RAW_TO_DEGREES;
    lAngle[1] = Angle[1];
    turnAngle[1] = 0;
    offsetAngle[1] = Angle[1];
  }
  if ( listeAS[2] ) {
    Angle[2] = (float)(AS3.getRawAngle()) * AS5600_RAW_TO_DEGREES;
    lAngle[2] = Angle[2];
    turnAngle[2] = 0;
    offsetAngle[2] = Angle[2];
  }
  if ( listeAS[3] ) {
    Angle[3] = (float)(AS4.getRawAngle()) * AS5600_RAW_TO_DEGREES;
    lAngle[3] = Angle[3];
    turnAngle[3] = 0;
    offsetAngle[3] = Angle[3];
  }
  if ( listeAS[4] ) {
    Angle[4] = (float)(AS5.getRawAngle()) * AS5600_RAW_TO_DEGREES;
    lAngle[4] = Angle[4];
    turnAngle[4] = 0;
    offsetAngle[4] = Angle[4];
  }
  if ( listeAS[5] ) {
    Angle[5] = (float)(AS6.getRawAngle()) * AS5600_RAW_TO_DEGREES;
    lAngle[5] = Angle[5];
    turnAngle[5] = 0;
    offsetAngle[5] = Angle[5];
  }
}

void Zion6_getOffset() {
  if ( listeAS[0] ) {
    offsetAngle[0] = (float)(AS1.getRawAngle()) * AS5600_RAW_TO_DEGREES;
    turnAngle[0] = 0;
  }
  if ( listeAS[1] ) {
    offsetAngle[1] = (float)(AS2.getRawAngle()) * AS5600_RAW_TO_DEGREES;
    turnAngle[1] = 0;
  }
  if ( listeAS[2] ) {
    offsetAngle[2] = (float)(AS3.getRawAngle()) * AS5600_RAW_TO_DEGREES;
    turnAngle[2] = 0;
  }
  if ( listeAS[3] ) {
    offsetAngle[3] = (float)(AS4.getRawAngle()) * AS5600_RAW_TO_DEGREES;
    turnAngle[3] = 0;
  }
  if ( listeAS[4] ) {
    offsetAngle[4] = (float)(AS5.getRawAngle()) * AS5600_RAW_TO_DEGREES;
    turnAngle[4] = 0;
  }
  if ( listeAS[5] ) {
    offsetAngle[5] = (float)(AS6.getRawAngle()) * AS5600_RAW_TO_DEGREES;
    turnAngle[5] = 0;
  }
}

void Zion6_checkAS() {
  if ( listeAS[0] ) {
    Zion6_ProcessAngle(0, (float)(AS1.getRawAngle())*AS5600_RAW_TO_DEGREES);
  }
  if ( listeAS[1] ) {
    Zion6_ProcessAngle(1, (float)(AS2.getRawAngle())*AS5600_RAW_TO_DEGREES);
  }
  if ( listeAS[2] ) {
    Zion6_ProcessAngle(2, (float)(AS3.getRawAngle())*AS5600_RAW_TO_DEGREES);
  }
  if ( listeAS[3] ) {
    Zion6_ProcessAngle(3, (float)(AS4.getRawAngle())*AS5600_RAW_TO_DEGREES);
  }
  if ( listeAS[4] ) {
    Zion6_ProcessAngle(4, (float)(AS5.getRawAngle())*AS5600_RAW_TO_DEGREES);
  }
  if ( listeAS[5] ) {
    Zion6_ProcessAngle(5, (float)(AS6.getRawAngle())*AS5600_RAW_TO_DEGREES);
  }
  //  if ( listeAS[1] ) { float _Angle2 = (float)(AS2.getRawAngle())*AS5600_RAW_TO_DEGREES; if ((_Angle2>=0)&&(_Angle2<=360) ){Angle2=Zion6_ProcessAngle(lAngle2,_Angle2;}}
  //  if ( listeAS[2] ) { float _Angle3 = (float)(AS3.getRawAngle())*AS5600_RAW_TO_DEGREES; if ((_Angle3>=0)&&(_Angle3<=360) ){Angle3=Zion6_ProcessAngle(lAngle3,_Angle3;}}
  //  if ( listeAS[3] ) { float _Angle4 = (float)(AS4.getRawAngle())*AS5600_RAW_TO_DEGREES; if ((_Angle4>=0)&&(_Angle4<=360) ){Angle4=Zion6_ProcessAngle(lAngle4,_Angle4;}}
  //  if ( listeAS[4] ) { float _Angle5 = (float)(AS5.getRawAngle())*AS5600_RAW_TO_DEGREES; if ((_Angle5>=0)&&(_Angle5<=360) ){Angle5=Zion6_ProcessAngle(lAngle5,_Angle5;}}
  //  if ( listeAS[5] ) { float _Angle6 = (float)(AS6.getRawAngle())*AS5600_RAW_TO_DEGREES; if ((_Angle6>=0)&&(_Angle6<=360) ){Angle6=Zion6_ProcessAngle(lAngle6,_Angle6;}}
  // for (int n=0;n<6;n++){ lastlisteAS[n]=listeAS[n];}
}

void Zion6_refreshPCF() {
  if ( bScreen1 == false) {
    showScrn1Init();
    bScreen1 = true;
  }
  if ( listePCF[0] ) {
    if (PCF1 != lPCF1) {
      showScrn1(1, PCF1);
      lPCF1 = PCF1;
    }
  }
  if ( listePCF[1] ) {
    if (PCF2 != lPCF2) {
      showScrn1(2, PCF2);
      lPCF2 = PCF2;
    }
  }
  if ( listePCF[2] ) {
    if (PCF3 != lPCF3) {
      showScrn1(3, PCF3);
      lPCF3 = PCF3;
    }
  }
  if ( listePCF[3] ) {
    if (PCF4 != lPCF4) {
      showScrn1(4, PCF4);
      lPCF4 = PCF4;
    }
  }
  if ( listePCF[4] ) {
    if (PCF5 != lPCF5) {
      showScrn1(5, PCF5);
      lPCF5 = PCF5;
    }
  }
  if ( listePCF[5] ) {
    if (PCF6 != lPCF6) {
      showScrn1(6, PCF6);
      lPCF6 = PCF6;
    }
  }
  if ( listePCF[6] ) {
    if (PCF7 != lPCF7) {
      showScrn1(7, PCF7);
      lPCF7 = PCF7;
    }
  }
  if ( listePCF[7] ) {
    if (PCF8 != lPCF8) {
      showScrn1(8, PCF8);
      lPCF8 = PCF8;
    }
  }
}

void Zion6_refreshAS() {
  if ( bScreen2 == false) {
    showBIGScrn2Init();
    bScreen2 = true;
  }
  for (int n = 0; n < 6; n++) {
    if (listeAS[n]) {
      if (realAngle[n] != laffAngle[n]) {
        showBIGScrn2(n + 1, realAngle[n]);
        laffAngle[n] = realAngle[n];
      }
    }
  }
  //  if ( listeAS[0] ) {   if(Angle1!=laffAngle1){    showBIGScrn2(1,Angle1);     laffAngle1=Angle1; }}
  //  if ( listeAS[1] ) {   if(Angle2!=laffAngle2){    showBIGScrn2(2,Angle2);     laffAngle2=Angle2; }}
  //  if ( listeAS[2] ) {   if(Angle3!=laffAngle3){    showBIGScrn2(3,Angle3);     laffAngle3=Angle3; }}
  //  if ( listeAS[3] ) {   if(Angle4!=laffAngle4){    showBIGScrn2(4,Angle4);     laffAngle4=Angle4; }}
  //  if ( listeAS[4] ) {   if(Angle5!=laffAngle5){    showBIGScrn2(5,Angle5);     laffAngle5=Angle5; }}
  //  if ( listeAS[5] ) {   if(Angle6!=laffAngle6){    showBIGScrn2(6,Angle6);     laffAngle6=Angle6; }}
}

void Zion6TransmitAll() {
  Serial2.print(tStop - tStart); Serial2.print(">"); Serial2.print(count); Serial2.print("|");
  listePCF[0] ? Serial2.print(PCF1) : Serial2.print("*"); Serial2.print(";");
  listePCF[1] ? Serial2.print(PCF2) : Serial2.print("*"); Serial2.print(";");
  listePCF[2] ? Serial2.print(PCF3) : Serial2.print("*"); Serial2.print(";");
  listePCF[3] ? Serial2.print(PCF4) : Serial2.print("*"); Serial2.print(";");
  listePCF[4] ? Serial2.print(PCF5) : Serial2.print("*"); Serial2.print(";");
  listePCF[5] ? Serial2.print(PCF6) : Serial2.print("*"); Serial2.print(";");
  listePCF[6] ? Serial2.print(PCF7) : Serial2.print("*"); Serial2.print(";");
  listePCF[7] ? Serial2.print(PCF8) : Serial2.print("*"); Serial2.print("|");

  listeAS[0] ? Serial2.print(realAngle[0]) : Serial2.print("*"); Serial2.print(";");
  listeAS[1] ? Serial2.print(realAngle[1]) : Serial2.print("*"); Serial2.print(";");
  listeAS[2] ? Serial2.print(realAngle[2]) : Serial2.print("*"); Serial2.print(";");
  listeAS[3] ? Serial2.print(realAngle[3]) : Serial2.print("*"); Serial2.print(";");
  listeAS[4] ? Serial2.print(realAngle[4]) : Serial2.print("*"); Serial2.print(";");
  listeAS[5] ? Serial2.print(realAngle[5]) : Serial2.print("*"); Serial2.print(";");
  Serial2.println();
}
//void Zion6TransmitAllToPCold(){
//  Serial.print(tStop-tStart);Serial.print(">");Serial.print(count);Serial.print("|");
//  listePCF[0]?Serial.print(PCF1):Serial.print("*");Serial.print(";");
//  listePCF[1]?Serial.print(PCF2):Serial.print("*");Serial.print(";");
//  listePCF[2]?Serial.print(PCF3):Serial.print("*");Serial.print(";");
//  listePCF[3]?Serial.print(PCF4):Serial.print("*");Serial.print(";");
//  listePCF[4]?Serial.print(PCF5):Serial.print("*");Serial.print(";");
//  listePCF[5]?Serial.print(PCF6):Serial.print("*");Serial.print(";");
//  listePCF[6]?Serial.print(PCF7):Serial.print("*");Serial.print(";");
//  listePCF[7]?Serial.print(PCF8):Serial.print("*");Serial.print("|");
//
//  listeAS[0]?Serial.print(Angle1):Serial.print("*");Serial.print(";");
//  listeAS[1]?Serial.print(Angle2):Serial.print("*");Serial.print(";");
//  listeAS[2]?Serial.print(Angle3):Serial.print("*");Serial.print(";");
//  listeAS[3]?Serial.print(Angle4):Serial.print("*");Serial.print(";");
//  listeAS[4]?Serial.print(Angle5):Serial.print("*");Serial.print(";");
//  listeAS[5]?Serial.print(Angle6):Serial.print("*");Serial.print(";");
//  Serial.println();
//}

void Zion6ProcessFDC() {
  // Mapping des pin FDC <> PCF8574_IO
  //      01234567
  // 0x20 FFFF....  FDC1
  // 0x21 .FFF....  FDC2
  // 0x22 12345.FF  boutons  et FDC3
  // 0x23 F.......  FDC4
  // 0x24 F.......  FDC5
  // 0x25 FP......  FDC6, Palpeur

  if (listePCF[0]) {
    bitRead(PCF1, 0) ? digitalWrite(FDC_REF1, 1) : digitalWrite(FDC_REF1, 0);  // OK
  }
  if (listePCF[1]) {
    bitRead(PCF2, 1) ? digitalWrite(FDC_REF2, 1) : digitalWrite(FDC_REF2, 0);  // OK
  }
  if (listePCF[2]) {
    bitRead(PCF3, 6) ? digitalWrite(FDC_REF3, 0) : digitalWrite(FDC_REF3, 1);  // OK mais inversé
  }
  if (listePCF[3]) {
    bitRead(PCF4, 0) ? digitalWrite(FDC_REF4, 1) : digitalWrite(FDC_REF4, 0);
  }
  if (listePCF[4]) {
    bitRead(PCF5, 0) ? digitalWrite(FDC_REF5, 1) : digitalWrite(FDC_REF5, 0);
  }
  if (listePCF[5]) {
    bitRead(PCF6, 0) ? digitalWrite(FDC_REF6, 1) : digitalWrite(FDC_REF6, 0);
  }
  if (listePCF[5]) {
    bitRead(PCF6, 1) ? digitalWrite( PALPEUR, 1) : digitalWrite( PALPEUR, 0);
  }

}


//{"t":116166,"g":[{"d":[-2.93181056,4.00000000,9.94301319,0.74624395,4.97150659,2.98999767]}]}#
//{"t":116174,"g":[{"d":[-2.94400739,4.00000000,9.95322990,0.67621970,4.97661495,2.99999761]}]}#
//{"t":116182,"ng":1,"lu":0,"g":[{"t":"Zion6","xvy":0,"pd":1000,"sz":6,"l":["Axe1","Axe2","Axe3","Axe4","Axe5","Axe6"],"c":["green","orange","cyan","yellow","pink","blue"],"d":[-2.95629930,4.00000000,9.96351623,0.59740095,4.98175811,3.00999760]}]}#
//{"t":116203,"g":[{"d":[-2.97819852,4.00000000,9.98181438,0.41310443,4.99128532,3.01999759]}]}#
//{"t":116211,"g":[{"d":[-2.98485612,4.00000000,9.98737239,0.34281859,4.99400043,3.02999758]}]}#

long n = 0;
void Zion6TransmitAllToPC() {
  //  Serial.print(tStop-tStart);Serial.print(">");Serial.print(count);Serial.print("|");
  //  listePCF[0]?Serial.print(PCF1):Serial.print("*");Serial.print(";");
  //  listePCF[1]?Serial.print(PCF2):Serial.print("*");Serial.print(";");
  //  listePCF[2]?Serial.print(PCF3):Serial.print("*");Serial.print(";");
  //  listePCF[3]?Serial.print(PCF4):Serial.print("*");Serial.print(";");
  //  listePCF[4]?Serial.print(PCF5):Serial.print("*");Serial.print(";");
  //  listePCF[5]?Serial.print(PCF6):Serial.print("*");Serial.print(";");
  //  listePCF[6]?Serial.print(PCF7):Serial.print("*");Serial.print(";");
  //  listePCF[7]?Serial.print(PCF8):Serial.print("*");Serial.print("|");

  double v0 = realAngle[0] ; if (!listeAS[0]) v0 = 0;
  double v1 = realAngle[1] ; if (!listeAS[1]) v1 = 0;
  double v2 = realAngle[2] ; if (!listeAS[2]) v2 = 0;
  double v3 = realAngle[3] ; if (!listeAS[3]) v3 = 0;
  double v4 = realAngle[4] ; if (!listeAS[4]) v4 = 0;
  double v5 = realAngle[5] ; if (!listeAS[5]) v5 = 0;
  //renvoie l'entete tt les 1000ms
  if ( (millis() - n) > 1000) {
    n = millis();
    Serial.print("{\"t\":"); Serial.print(millis()); Serial.print(",\"ng\":1,\"lu\":0,\"g\":[{\"t\":\"Zion6\",\"xvy\":0,\"pd\":1000,\"sz\":6,\"l\":[\"Axe1\",\"Axe2\",\"Axe3\",\"Axe4\",\"Axe5\",\"Axe6\"],\"c\":");
    Serial.print("[\"green\",\"orange\",\"cyan\",\"yellow\",\"pink\",\"blue\"],\"d\":[");
  }
  else
  {
    Serial.print("{\"t\":"); Serial.print(millis()); Serial.print(",\"g\":[{\"d\":[");

  }

  Serial.print(v0); Serial.print(",");
  Serial.print(v1); Serial.print(",");
  Serial.print(v2); Serial.print(",");
  Serial.print(v3); Serial.print(",");
  Serial.print(v4); Serial.print(",");
  Serial.print(v5); Serial.print(",");
  Serial.println("]}]}#");


}
