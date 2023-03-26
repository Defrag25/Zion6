
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
