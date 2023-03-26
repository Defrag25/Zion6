
volatile uint8_t MenuState=0;
volatile uint8_t MenuBack=1;
const uint8_t    MenuStateMax=11;
uint8_t          MenuStateLast=0; // Permet de revenir à la fenetre d'appel en cas de saisie clavier NUM
uint8_t          Counter=0;

uint8_t    AliveColor=100;
uint8_t    AliveFormat=1;
//uint16_t ScannSpeedJOY         =  10; // Vitesse de scann du JOY (en ms)
uint16_t   ScannSpeedCheckStatus_Extand2  =   0; // Extension de temps qui permet de retarder la prochaine demande de status pour donner du temps de gestion des outils 
uint16_t   ScannSpeedCheckStatus = 200; // Vitesse de scann du Check Status GRBL (en ms)
uint16_t   ScannSpeedAlive       =  50; // Vitesse de scann du clignotement de status de vie
float      Val;// Variable utilisée dans l'éditeur de nombre "ClavierNum"
long       TimeStart,TimeStop; // variables generales pour les mesures de timing

TouchScreen ts(XP, YP, XM, YM, 300); //re-initialised after diagnose
TSPoint_kbv PTouch,PTouchLast,tp,PTouchLastM0,PTouchDirect,PTouchDirectLast;

//struct TWindow  {
//      uint16_t x;
//      uint16_t y;
//      }Win,Boutons;

struct TBouton      { int16_t x;int16_t y;int16_t w;int16_t h;};
const struct TBouton BP_Joy   = {450,180,50,25};
const struct TBouton BP_Back        = {23 ,75,40,40}; // Bouton de retour 
//const struct TBouton BP_BackDroite  = {450,65,50,20}; // Bouton de retour (à droite)

//struct TButton {
//  char *str;
//  uint16_t x,y,w,h,TextColor,BkColor;
//  uint8_t Size;
//  boolean  Checked;
//}BP;
//struct TButton BP2;
//uint8_t Menu0_State=0;
//uint8_t Menu1_State=0;
boolean Menu_FirstStart  = true;
boolean Menu0_Refresh    = true;
boolean Draw_Cursor      = false;
boolean Joystic_Enabled2 = true; // Activation du Joystic analogique?
boolean Joystic_Control  = false; // Activation du Joystic analogique?
boolean Joystic_Mode     = false; // Mode de fonctionnement du Joystic (false= Analog  true=pulses)
boolean POWER_Control    = false; // Activation de la puissance Moteur
boolean COMM_Control     = true;  // Activation communication vers GRBL 
boolean Option0          = false;
boolean EnableParams     = true;
boolean EnableDrawORG    = false; //EnableOption0 = false;
boolean EnableDRAWCoord  = false;
boolean EnableOption2    = false;
//boolean SAVEEEprom       = false;
boolean EnableDEBUG2      = false;
//boolean EnableSAVEEEprom  = true;
boolean DrawTool           = false;
boolean Option8           = false;
boolean Option9           = false;
boolean Option10          = false;
boolean Option11          = false;
boolean Option12          = false;
boolean Option13          = false;
boolean Accroche          = false;
boolean Persistance       = false;

unsigned long start1 = millis();
unsigned long start2 = millis();
unsigned long start3 = millis();
boolean ToolRedrawNeeded = false;
uint16_t CheckBoxVar     = 0;



uint8_t MenuIndexSelect=1;
uint8_t MenuIndexSelectCount=1;
//boolean MenuIndexSelectRefreshNeeded= true;
uint8_t MenuIndexSelectMax=8;

char *CursorLabel      ="          "; //char *CursorLabel     =_CursorLabel;
char *CursorLabelLast  ="          "; //char *CursorLabelLast =_CursorLabelLast;
char *JOY2Label        ="          "; //char *JOYLabel        =_JOYLabel;
char *JOY2LabelLast    ="          "; //char *JOYLabelLast    =_JOYLabelLast;
char *ss3              ="          "; //char *ss3             =_ss3;
char *ss3Last          ="          "; //char *ss3Last         =_ss3Last;
char *PointLabel       ="          "; //char *PointLabel        =_JOYLabel;

#define T1_X 0      // Index X Tool 1
#define T1_Z 1      // Index Z Tool 1
#define T2_X 2      // Index X Tool 2
#define T2_Z 3      // Index Z Tool 2
#define T3_X 4      // Index X Tool 3
#define T3_Z 5      // Index Z Tool 3
#define TL0_X 6     // Index X Tool TL0
#define TL0_Z 7     // Index Z Tool TL0
#define MoveStep  8  // Index Step
#define MoveSpeed 9  // Index Speed
#define PositionX 10 // Position de l'axe X (uniquement pour permettre la modification avec le clavier)
#define PositionZ 11 // Position de l'axe Z (uniquement pour permettre la modification avec le clavier)
#define Pt_FromX  12 // Point de depart d'un travail
#define Pt_FromZ  13 // Point de depart d'un travail
#define Pt_ToX    14 // Point de depart d'un travail
#define Pt_ToZ    15 // Point de depart d'un travail
#define Pt_CentreX 16 // Point de depart d'un travail
#define Pt_CentreZ 17 // Point de depart d'un travail
#define Pt_Feed    18 // Point de depart d'un travail
#define Pt_Repeat  19 // Point de depart d'un travail
#define Pt_Increment 20 // Point de depart d'un travail
#define MoveStep2 21  // Index Step2
#define G54_X     22  // G54
#define G54_Z     23  // G54
#define G55_X     24  // G54
#define G55_Z     25  // G54
#define PointX    26 // PointX
#define PointZ    27 // PointZ
#define ActivPX   28 // PointX
#define ActivPZ   29 // PointZ
// 

#define TabNb 29 
float TVal[TabNb+1] ;
volatile uint8_t TValIndex=0; // Index du pointeur sur la variable à valider suite à la validation clavier Num
//float n[2]; //unsigned char switch_off_1[450] PROGMEM = 
//int TValInteger[10];

struct TJoy { int16_t X;     int16_t Z;      uint16_t F; // (-100% à 100%) (-100% à 100%) (0% à 100%)
              uint16_t XAna; uint16_t ZAna;  uint16_t FAna;
              uint16_t XMin; uint16_t ZMin;  uint16_t FMin;
              uint16_t XMax; uint16_t ZMax;  uint16_t FMax;
              int16_t Offx;  int16_t Offz;   int16_t Offf;
              uint16_t Fscan;};
              
struct TJoy JOY={  512, 512, 512,        // modifié en attente d'eeprom
                   512, 512, 512,
                   0,0,0,
                  1024,1024,1024,
                     0,   0,   0,
                    10};
struct TJoy JOYLast=JOY;
struct TJoy JOYM81Last=JOY;
struct TJoy JOYLastM2=JOY;  // Pour Menu2
struct TJoy JOYLastM20=JOY;  // Pour Menu2
struct TJoy JOYLastM81=JOY;  // Pour Menu2
volatile long   LastJogTime ;
uint16_t IHM_BP=0;
uint16_t IHM_BPLast=0;

struct TTerm {uint16_t x;uint16_t y;uint16_t w;uint16_t h;};
const struct TTerm TermMinalNull = {    0,   0,        0,        0}; // faut faire un multiple de 6 +1
const struct TTerm TermDefault   = {    0,   0,      479,      319}; // faut faire un multiple de 6 +1
const struct TTerm Terminal1     = {    8,  78,      479,(317- 78)};
const struct TTerm Terminal2     = {    5,  78,      375,      223};
const struct TTerm TerminalMenu0 = {  170,  60,      105,      250};
const struct TTerm TerminalMenu1 = {  300,  60,      150,      182};
const struct TTerm TerminalMenu10= {    1,  70,      197,(318- 70)};//(315- 78)};
const struct TTerm TerminalMenu18= {    1,  70,(479- 47),(318- 70)};
const struct TTerm TerminalMenu19= {    45,  25,  479-2*45,   319-2*25};
const struct TTerm TerminalMenu2 = {  210, 130,(412-210),(315-130)}; //317-130=
const struct TTerm TerminaMenu20_Micro= {  385,  285,(475-385),(315- 285)};
const struct TTerm TerminalMenu20= {  385,  71,(477-385),(316- 71)};
const struct TTerm TerminalMenu3 = {  205, 130,(375-205),(195-130)};
const struct TTerm TerminalMenu4 = {    5,  78,      375,      223};
const struct TTerm TerminalMenu50= {  350,  55,(475-350),(100- 55)};
const struct TTerm TerminalMenu51= {  330, 150,(475-330),(292-150)};
const struct TTerm TerminalMenu52= {  330, 150,(475-330),(292-150)};
const struct TTerm TerminalMenu59= {  350, 110,(475-350),(315-110)};
const struct TTerm TerminalMenu6 = {  350, 250,(475-350),(315-250)};
const struct TTerm TerminalMenu7 = {    5,  78,(380- 29),(300- 78)};
const struct TTerm TerminalMenu71= {    5,  78,(100-  5),(300- 78)};
const struct TTerm TerminalMenu72= {  102,  78,(200-102),(300- 78)};
const struct TTerm TerminalMenu8 = {  390,  55,(475-390),(113- 55)};
const struct TTerm TerminalMenu81= {   35,  80,(280- 35),(210- 80)};
const struct TTerm TerminalMenu90= {  140,  60,(385-140),(315- 60)};
const struct TTerm TerminalMenu91= {    3,  70,(385-  5),(318- 70)};//(270- 78)};
const struct TTerm TerminalMenu92= {    3,  70,(385-  5),(318- 70)};//(270- 78)};
const struct TTerm TerminalNum   = {  350,  60,(475-350),(315- 60)};
const struct TTerm TermMachine   = {    5,  78,      375,      223};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Variables Gestion Transmission //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_BUF     300    
char    FileSelected[40];

#define  MAX_BUF2   200    
char     buffer2[MAX_BUF2];
uint16_t buffer2_pos=0;
uint8_t  buffer2_TypeOfCmd=0;     uint8_t  Lastbuffer2_TypeOfCmd=0;

char     buffer[MAX_BUF+1];
uint16_t buffer_pos=0;            uint16_t Lastbuffer_pos=1;
uint16_t buffer_posToProcess=0;   uint16_t Lastbuffer_posToProcess=1;
uint8_t  inByte=0;                uint8_t  LastinByte=1;
uint8_t  buffer_Full=0;           uint8_t  Lastbuffer_Full=1;
volatile int8_t  NbCmdTest=0;             uint8_t  LastNbCmd=1;
uint8_t  Csize=1;   // taille police de caractere en cours
//struct TSerial {
//                char     buffer[MAX_BUF];
//                volatile uint16_t buffer_pos=0;
//                volatile uint16_t buffer_posToProcess=0;
//                volatile uint8_t  inByte=0;
//                volatile uint8_t  buffer_Full=0;
//                volatile uint8_t  NbCmd=0;
//};
//struct TSerial TT    ={0,0,0,0,0};
//struct TSerial TTLast={1,1,1,1,1};

//struct TSerial TT;
//struct TSerial TTLast;


#define IHM_BLACK     0x0000
#define IHM_WHITE     0xFFFF
#define IHM_GRAY      0x7BEF   //0b 0111 1011 1110 1111
#define IHM_LIGHT_GRAY 0xC618  //0b 1100 0110 0001 1000
#define IHM_DARK_GRAY 0x39E7   //0b 0011 1001 1110 0111
#define IHM_GREEN     0x07E0
#define IHM_LIME      0x87E0
#define IHM_BLUE      0x001F
#define IHM_RED       0xF800
#define IHM_AQUA      0x5D1C
#define IHM_YELLOW    0xFFE0
#define IHM_MAGENTA   0xF81F
#define IHM_CYAN      0x07FF
#define IHM_DARK_CYAN 0x03EF
#define IHM_ORANGE    0xFCA0
#define IHM_PINK      0xF97F
#define IHM_BROWN     0x8200
#define IHM_VIOLET    0x9199
#define IHM_SILVER    0xA510
#define IHM_GOLD      0xA508
#define IHM_NAVY      0x000F
#define IHM_MAROON    0x7800
#define IHM_PURPLE    0x780F
#define IHM_OLIVE     0x7BE0



// Assign human-readable names to some common 16-bit color values:
//#include "LIB/TouchScreen_kbv.h"
//#define  BLACK   0x0000
//#define BLUE    0x001F
//#define RED     0xF800
//#define GREEN   0x07E0
//#define CYAN    0x07FF
//#define MAGENTA 0xF81F
//#define YELLOW  0xFFE0
//#define WHITE   0xFFFF



#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif
//extern const uint8_t hanzi[];
//void tests();
//unsigned long testText() ;



uint16_t scrollbuf[480];    // my biggest screen is 320x480
#define READGRAM(x, y, buf, w, h)  tft.readGRAM(x, y, buf, w, h)


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Variables Gestion Terminal //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                   w
// (TxposMin,TyposMin)-----------               // Les dimensions w,h du terminal sont optimales si elles sont en rapport
//          |                    |              // avec la taille de la polices
//          |                    |              // Elles sont toutes en pixel et en mode portrait !
//          |                    | h
//          |     (Txpos,Typos)  |
//          |           A        |
//           --------------------
//
//

uint16_t TXpos=0;    // Position gauche du terminal
uint16_t TYpos=0;    // Position basse 
const uint8_t TXposOffset = 0 ; //Offset de ddeplacement du texte par rapport au bord gauche du terminal (permet de placer des N° de lignes
const uint8_t  _TXsize=6;   // Taille caractere police
const uint8_t  _TYsize=8;   // Taille caractere police
uint8_t  Tsize=1;    // 2 (pas testé autre taille) 
uint16_t TFtColor=IHM_WHITE ;
uint16_t TBkColor=IHM_BLACK ;
uint16_t TXMin=8;    // Position Left Terminal
uint16_t TYMin=78;  
// Attension les données 'Width' et 'Height' sont inversées car elles sont placées dans les Max pendant la compilation , donc avant la rotate dans l'init
// Je les déclarent donc en DUR pour la compil en mode portrait
uint16_t TXMax=480;//-TXMin;//my_lcd.Get_Display_Width()-1-TXMin; // Taille de terminal en pixel
uint16_t TYMax=320;//-TYMin;//my_lcd.Get_Display_Height()-10-TYMin;




#define PROG_NO_PROG   0
#define PROG_UNDEFINED 1
#define PROG_READY     2
#define PROG_STOP      3
#define PROG_PAUSE     4
#define PROG_RESUME    5
#define PROG_RUNNING   6

struct TProg { uint8_t Status; char* Name;uint16_t LignesNb; uint16_t LigneIndex;};
struct TProg PROG ={PROG_NO_PROG,"cone.txt",50,1};

uint16_t ActualColor; // couleur Pixel en cours
struct TPointGrbl {float x;     float z;};
struct TPointTFT  {uint16_t  x; uint16_t y;};
 float ZoomGrblToTFT = 10;
 float ZoomGrblToTFTLast = 10;
 const float DiamCorrection =2;
//struct TPointGrbl ORG_G54        = {  0,  0};

//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SD           //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
#define   MAX_CARAC       80         
char      Line[MAX_CARAC];     // where we store the message until we get a new line
uint8_t   LinePos=0;

struct TSD_Search { boolean Result; float Value; uint16_t Index;};
