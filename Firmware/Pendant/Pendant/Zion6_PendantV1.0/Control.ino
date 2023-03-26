// Gestion de l'état du Joystic

//#include "LIB/TouchScreen_kbv.h"

#define IHM_BP0Pressed  ((IHM_BP & 0b0000000000000001)!=0?1:0)  
#define IHM_BP1Pressed  ((IHM_BP & 0b0000000000000010)!=0?1:0) 
#define IHM_BP2Pressed  ((IHM_BP & 0b0000000000000100)!=0?1:0) 
#define IHM_BP3Pressed  ((IHM_BP & 0b0000000000001000)!=0?1:0) 
#define IHM_BP4Pressed  ((IHM_BP & 0b0000000000010000)!=0?1:0) 
#define IHM_BP5Pressed  ((IHM_BP & 0b0000000000100000)!=0?1:0) 
#define IHM_BP6Pressed  ((IHM_BP & 0b0000000001000000)!=0?1:0) 
#define IHM_BP7Pressed  ((IHM_BP & 0b0000000010000000)!=0?1:0) 
#define IHM_BP8Pressed  ((IHM_BP & 0b0000000100000000)!=0?1:0) 
#define IHM_BP9Pressed  ((IHM_BP & 0b0000001000000000)!=0?1:0) 
#define IHM_BP10Pressed ((IHM_BP & 0b0000010000000000)!=0?1:0) 
#define IHM_BP11Pressed ((IHM_BP & 0b0000100000000000)!=0?1:0) 
#define IHM_BP12Pressed ((IHM_BP & 0b0001000000000000)!=0?1:0)

void(*resetFunc)(void) =*setup; 
//void(*resetFunc)(void) =*loop; 
//void softwareReset( unsigned long delayMillis) {
//  uint32_t resetTime = millis() + delayMillis;
//  while ( resetTime > millis()) { 
//    // wait and do nothing until the required delay expires... 
//  }
//  // jump to the start of the program
//  asm volatile ( "jmp 0");  
//}

void IHM_Init(){
//Affiche présentation  + version
  AliveFormat=1;
//  IHM_JOY_Init(); 
  Menu_FirstStart  = true;
  Menu0_Refresh    = true;

//  POWER_Control    = false; // Activation de la puissance Moteur
//  COMM_Control     = true;  // Activation communication vers GRBL 
//  EnableOption2    = false;
  EEPROM_CheckBoxStateLoad();
  MenuState=0;
//  SAVEEEprom       = false;
//  EnableSAVEEEprom = true;
  PTouch_Reset();
}


void IHM_Loop()
{
//  MenuState=1;MenuBack=1;
  IHM_Menu0_Init();  // Cette ligne n'est pas un doublon d'Init0 car le flag "Menu0_Refresh" est mis à 0 pour le premier passage dans la boucle do..
//  Menu_FirstStart=true;
//  MenuState=1;  // Affichage direct du menu 1 au 1er demarrage
//  ScannSpeedCheckStatus_Extand2=0;
  do   {
    TimingStart();
    
    IHM_Menu0_Loop();
    TimingCheckPoint(1);
    switch (MenuState)
     {
       case 0:  MenuState=1;      Menu_FirstStart=true;         break;                  
       case 1:  IHM_Menu1_Loop();        break;  // Menu principal 
       case 10: IHM_Menu10_Loop();       break;  // Parametres
       case 18: IHM_Menu18_Loop();       break;  // Aide
       case 19: IHM_Menu19_Loop();       break;  // Calibration
       case 2:  IHM_Menu2_Loop();        break;  // CNC                
       //case 20: IHM_Menu20_Loop();       break;  // Dessin                  
       case 3:  IHM_Menu3_Loop();        break;  // CNC                
       case 4:  IHM_Menu4_Loop();        break;  // Communication
//       case 5:  MenuState++;             break;                  
//       //case 50: IHM_Menu50_Loop();       break; // Template
//       //case 51: IHM_Menu51_Loop();       break; // Chariotage
//       //case 52: IHM_Menu52_Loop();       break; // "Test Objets"
//       case 6:  IHM_Menu6_Loop();        break;                  
       case 7:  IHM_Menu7_Loop();        break;
       case 8:  IHM_Menu8_Loop();        break;
       case 81: IHM_Menu81_Loop();       break;
//       case 9:  MenuState=0;             break;
//       case 90: IHM_Menu90_Loop();       break;
//       case 91: IHM_Menu91_Loop();       break;
//       case 92: IHM_Menu92_Loop();       break;

       case 99: IHM_ClavierNUM_Loop();   break;
       default : MenuState=0;            break;
     }
TimingCheckPoint(2);

   // Tout ce qui suit fait vivre l'IHM
   // Le temps passé dans les fonctions de boucle doit etre petit  
    Alive();   // Témoin de vie
    
    //VirtualTraiteAll();
//    if (COMM_Control==true)
//     { //stop la demande d'infos a Grbl
      if((millis() - start2)>(ScannSpeedCheckStatus + ScannSpeedCheckStatus_Extand2))  
       {
        start2 = millis();
        CNC_CheckGRBL();  
        ScannSpeedCheckStatus_Extand2=0; // juste une foi "à chaques fois"
       }   // Demande info GRBL
//     }//COMM_Control
//    else  CNC.State="----";
   TimingCheckPoint(3);
    CheckRS232();         // regarde si reception d'une data de Grbl
    VirtualTraiteAll();   // Traite la data de Grbl
    if(Joystic_Enabled2==true)
     {
      if((millis() - start3)>JOY.Fscan) 
       {
        start3 = millis();
        IHM_JOY_Loop(); 
       }
     } // Scann Joystic
     TimingCheckPoint(4); 
    IHM_BP=IHM_ButtonCheck();
    TimingCheckPoint(5);
    //if (IHM_BP!=0) DEBUGSerial.println(IHM_BP,BIN);
    if ( (IHM_BP1Pressed) & (IHM_BP10Pressed) & (IHM_BP12Pressed) ) { resetFunc(); }                                // CTRL + ALT + SUP = RESET
    if ( (IHM_BP1Pressed) & (IHM_BP2Pressed) )                      { MenuState=18;        Menu_FirstStart=true; }  // CTRL + ESC = AIDE
    if ( (IHM_BP0Pressed) & (!IHM_BP1Pressed) )                     { MenuState=MenuBack;  Menu_FirstStart=true;IHM_ButtonsWaitReleased(); }  // ESC = refresh fenetre
    if ( (!IHM_BP1Pressed) & (IHM_BP10Pressed) & (IHM_BP12Pressed)) { ; }                       // ALT + SUP = Imprime ecran
    
   //}while(1);
       //if(millis()>Ttime+1000){      IHM_PrintPageNumber(Counter);Ttime=millis();Counter=(Counter+1)%20;}
//    digitalWrite(13, HIGH);
//    PTouch=ts.getPoint();

//    digitalWrite(13, LOW);
//    pinMode(XM, OUTPUT);  pinMode(YP, OUTPUT);
//    if(PTouch.z > MINPRESSURE && PTouch.z < MAXPRESSURE)
//     {      
//      PTouch.x = map(PTouch.x, TS_MINX, TS_MAXX , 0            , tft.width());
//      PTouch.y = map(PTouch.y, TS_MINY, TS_MAXY , tft.height() , 0);
//
//
////      tft.fillCircle(PTouchLast.x, PTouchLast.y, 2, BLACK);
////      tft.fillCircle(PTouch.x, PTouch.y, 2, WHITE);
//      tft.drawFastHLine(PTouchLast.x-2, PTouchLast.y, 5, IHM_BLACK);
//      tft.drawFastVLine(PTouchLast.x, PTouchLast.y-2, 5, IHM_BLACK);
//      tft.drawFastHLine(PTouch.x-2, PTouch.y, 5, WHITE);
//      tft.drawFastVLine(PTouch.x, PTouch.y-2, 5, WHITE);
//      PTouchLast.x=PTouch.x;
//      PTouchLast.y=PTouch.y;
//      //Serial.println(PTouch.x);
//      //Serial.print("Touch After > "); Serial.print("(");Serial.print(PTouch.x);Serial.print(";");
//      //Serial.print(PTouch.y);Serial.print(") "); Serial.println(PTouch.z);    //Affiche curseur
//      //delay(1);
//     }
TimingCheckPoint(0);
}while(true);
} // 


uint16_t IHM_ButtonCheck(){
  uint16_t Temp=0;
  uint16_t Mask=0b0000000000000001;
  for (uint8_t i=22;i<=37;i++){
    if (digitalRead(i)==0) Temp|=Mask; Mask=Mask << 1;
  }
  return(Temp);
}

//////////////
//attachInterrupt()
//[External Interrupts]
//Description
//Digital Pins With Interrupts
//
// The first parameter to attachInterrupt() is an interrupt number. 
// Normally you should use digitalPinToInterrupt(pin) to translate the actual digital pin to the specific interrupt number. For example, 
// if you connect to pin 3, use digitalPinToInterrupt(3) as the first parameter to attachInterrupt().
//
// Board                                Digital Pins Usable For Interrupts
//
// Uno, Nano, Mini, other 328-based     2, 3
//Uno WiFi Rev.2, Nano Every            all digital pins
//Mega, Mega2560, MegaADK               2, 3, 18, 19, 20, 21
//Micro, Leonardo, other 32u4-based     0, 1, 2, 3, 7
//Zero                                  all digital pins, except 4
//MKR Family boards                     0, 1, 4, 5, 6, 7, 8, 9, A1, A2
//Nano 33 IoT                           2, 3, 9, 10, 11, 13, 15, A5, A7
//Nano 33 BLE, Nano 33 BLE Sense        all pins
//Due                                   all digital pins
//101                                   all digital pins (Only pins 2, 5, 7, 8, 10, 11, 12, 13 work with CHANGE)


//Syntax

//attachInterrupt(digitalPinToInterrupt(pin), ISR, mode) (recommended)
//attachInterrupt(interrupt, ISR, mode) (not recommended)
//attachInterrupt(pin, ISR, mode) (Not recommended. Additionally, this syntax only works on Arduino SAMD Boards, Uno WiFi Rev2, Due, and 101.)
//Parameters
//
//interrupt: the number of the interrupt. Allowed data types: int.
//pin: the Arduino pin number.
//ISR: the ISR to call when the interrupt occurs; this function must take no parameters and return nothing. This function is sometimes referred to as an interrupt service routine.
//mode: defines when the interrupt should be triggered. Four constants are predefined as valid values:
//
//    LOW to trigger the interrupt whenever the pin is low,
//
//    CHANGE to trigger the interrupt whenever the pin changes value
//
//    RISING to trigger when the pin goes from low to high,
//
//    FALLING for when the pin goes from high to low.
//
//The Due, Zero and MKR1000 boards allow also:
//
//    HIGH to trigger the interrupt whenever the pin is high.



//Example Code
//
//const byte ledPin = 13;
//const byte interruptPin = 2;
//volatile byte state = LOW;
//
//void setup() {
//  pinMode(ledPin, OUTPUT);
//  pinMode(interruptPin, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
//}
//
//void loop() {
//  digitalWrite(ledPin, state);
//}
//
//void blink() {
//  state = !state;
//}
