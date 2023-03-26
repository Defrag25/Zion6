



void RS232_BufferPrintColor0(){
  uint16_t p=0;
  char s;
  char* ps=&s;
  tft.setTextSize(1);     Tsize=1;

  printStringln(" ");  
  while (buffer[p]!=0)     // doit toujours se terminer par un 0x00
  {
    s=buffer[p];
    TFtColor=IHM_WHITE; TBkColor=IHM_BLACK;tft.setTextColor(IHM_WHITE,IHM_BLACK);
    if((s==0x0d)|(0))   { s='D'; TFtColor=IHM_GREEN; tft.setTextColor(IHM_GREEN);}  // Suppression 0x0a
    if((s==0x0a)|(0))   { s='A'; TFtColor=IHM_GREEN; tft.setTextColor(IHM_GREEN);}  // Suppression 0x0a
    //if(s==0x20)               { s='_';}
    if(p==buffer_posToProcess){ TFtColor=IHM_BLUE; tft.setTextColor(IHM_BLUE); }
    else                      {  }
    printChar(ps);
    p++;
  }
}

void RS232_Buffer2PrintColor0(){
  uint16_t p=0;
  uint16_t buffer2_posToProcess=0;
  char s;
  char* ps=&s;
  tft.setTextSize(1);    
  Tsize=1 ; TFtColor=IHM_GREEN;TBkColor=IHM_BLACK;
  tft.setTextColor(IHM_GREEN, IHM_BLACK); 

  tft.setTextSize(1);    


  //printStringln(" ");  
  buffer2[MAX_BUF2-1]=0;
  while (buffer2[p]!=0)
  {
    s=buffer2[p];
    TFtColor=IHM_WHITE; tft.setTextColor(IHM_WHITE);
    if(s==0x0d){ s='_'; TFtColor=IHM_GREEN; tft.setTextColor(IHM_GREEN);} //Suppression 0x0a
    if(s==0x0a){ s='_'; TFtColor=IHM_GREEN; tft.setTextColor(IHM_GREEN);} //Suppression 0x0a
    if(s==0x20){ s='_'; TFtColor=IHM_GRAY;  tft.setTextColor(IHM_GREEN);}
    if(p==buffer2_posToProcess){TFtColor=IHM_GREEN; tft.setTextColor(IHM_BLUE); }
    else                         {}
    printChar(ps);
    p++;    
  }
}


void RS232_InitBuffer(){
  //TT    ={0,0,0,0,0};
  //TTLast={1,1,1,1,1};
  
 buffer_pos=0;
 buffer_posToProcess=0;
 inByte=0;
 buffer_Full=0;
 NbCmdTest=0;
 Lastbuffer_pos=1;
 Lastbuffer_posToProcess=1;
 LastinByte=1;
 Lastbuffer_Full=1;
 LastNbCmd=1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t CheckRS232(void) 
{
// retourne 0 si pas de caractere
//          inByte si caractere avec remplissage des caracetres dans buffeur tournant
//          Incremente NbCmd à chaque reception de fin de ligne
  uint16_t WhereToPutNext;
  inByte = 0;
  if(buffer_Full==0)
  {
   while (Serial.available()>0)
    {//remplie le buffer 

    //buffer[MAX_BUF]=0;
    
    WhereToPutNext=buffer_pos+1;
    //Serial.print("A");Serial.print(WhereToPutNext);Serial.print(" ");
    if (WhereToPutNext>=MAX_BUF)               { WhereToPutNext=0;}
    //Serial.print("B");Serial.print(WhereToPutNext);Serial.print(" ");
    if (WhereToPutNext==buffer_posToProcess){ buffer_Full=1;return(0);} 
    //Serial.print("C");Serial.print(WhereToPutNext);Serial.print(" ");
    inByte =CNCSerial.read();
    buffer[buffer_pos]=inByte;
    
    //Serial.print("D");Serial.print(buffer_pos);Serial.print(" ");
    buffer_pos=WhereToPutNext;
    //Serial.print("E ");Serial.print(buffer_pos);Serial.println("/");
   
    if((inByte==0x0a)||(inByte==0x0d)) //Suppression 0x0a
     {
      if(buffer_Full==0)
       {
        if(NbCmdTest>254){buffer_Full=2;}
        else {NbCmdTest++;}
       }
     }
    // blinkLED()  ;
   }
  }     ///if(TT.buffer_Full==0
  else
  {//buffer_Full
   buffer_pos=0;
   buffer_posToProcess=0;
   CNC.NbOk=0;   
  }
 return(inByte);
}
void TOTAL(int n){
  //DEBUGSerial.print("TRAITE=");DEBUGSerial.print(n,DEC);DEBUGSerial.print(" NbCmdTest=");DEBUGSerial.println(NbCmdTest,DEC);
  //DEBUGSerial.print("buffer2=");DEBUGSerial.println(buffer2);
  //DEBUGSerial.print("buffer=");DEBUGSerial.println(buffer);
  
//if(n==0){do{}while(1);}
}
boolean CNCWaitOk(uint16_t MaxTimeToWaitMillis)
{// Attends "MaxTimeToWaitMillis" ms un Ok
  long TimeStart = millis();
  uint8_t NbOkBefore = CNC.NbOk;
  do
   {
    if(NbOkBefore!=CNC.NbOk){  return (true);  }                                        // Sortie de boucle si GRBL a repondu ok
    if((millis() - start2)>(ScannSpeedCheckStatus + ScannSpeedCheckStatus_Extand2))     // Demande status Grbl
     { // Demande info GRBL
      start2 = millis();   CNC_CheckGRBL();  
      ScannSpeedCheckStatus_Extand2=0; // juste une foi " à chaques fois"
     }  

    //Affichage en temps reel des positions
    CheckRS232();             // Ces 4 lignes permettent de controler et d'afficher 
    VirtualTraiteAll();       // le status machine lors d'un programme
    Alive();                  //
    IHM_Menu0_Loop();         //

    // Check le "clavier Tactile" de gestion du programme (RUN,PAUSE,STOP...)
    // avec sortie de boucle si un evenement clavier est demandé, c'est le prog d'appel qui traite la demande
//    boolean Event = IHM_Menu91_PROGCheck();
//    if (Event) return(true);

  }while((millis()-TimeStart)<MaxTimeToWaitMillis);
  return (false);
}

void VirtualTraiteAll(){
  while(NbCmdTest>0)
  { 
     VirtualTraite();
     TOTAL(0);
     //DEBUGSerial.println(NbCmdTest,DEC);
  }
  // Remet le pointeur buffer à 0 s'il toutes les data sont traitées
  // ce qui evite les commandes coupées dans le cas du debordement du buffeur
  // Probleme à gérer dans la prochaine version
  if(buffer_posToProcess==buffer_pos)
    {
      buffer_pos=0;
      buffer_posToProcess=0;
    }
}


void VirtualTraite(){
//  if (NbCmd>0)
//   {
DEBUGSerial.println("Virtual Traite");
    char s;
    //uint8_t s;
    uint16_t n =buffer_posToProcess;
    uint16_t MaxCount = MAX_BUF-1; // Nb de boucle maxi au cas où le buffeur soit remplie de caracteres à la con
    s= buffer[n];    
    
    buffer2[0]=0x0d;buffer2_pos=0;
    do
     {//Cherche la ligne en ommettant les "0x0a,0x0d"
      s= buffer[n];    
      if ( (s!=0x20) &
           (s!=0x0a) &    //Suppression 0x0a
           (s!=0x0d) )
       {
        buffer2[buffer2_pos++]=s;
        buffer2[buffer2_pos]=0x0d;
        buffer2[buffer2_pos+1]=0x00;
       }
      if(n++>=MAX_BUF){n=0;}
      if((0) | (s==0x0d)) {NbCmdTest--;}   //Suppression 0x0a
      if((s==0x0a) | (0)) {NbCmdTest--;}   //Suppression 0x0a
     }while( (s!=0x00) & (s!=0x0a) & (s!=0x0d) & (MaxCount--!=0) ); //Suppression 0x0a
    buffer_posToProcess=n;
    //TOTAL(1);
    buffer_Full=0;
    /////////printStringlnColor(buffer2,IHM_GOLD,1);
    buffer2_TypeOfCmd=Traite();
    TOTAL(2);
//   }
DEBUGSerial.println("Virtual Traite FIN");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fonctionne avec $10=0
//                          1              2             3             4              5         6            7      8      9       10      11      12      13
enum grblStatusValuesIndex {grblValStatus, grblValMachX, grblValMachY, grblValMachZ,  grblFeed, grblSpindle, grbl6, grbl7, grbl8 , grbl9 , grb20 , grb21 , grblValLasted};
float grblStatusFloatValues[grblValLasted+1];

void toSplitCommand(String SplitText, String SplitChar) ;
#define  SplittingArraySize 13
String   SplittingArray[SplittingArraySize+1];
String grblStatusValues[grblValLasted];

void Incompris(char *str){
  RS232_Buffer2PrintColor0();    
}

uint8_t  Traite(){
  // traite la chaine dans buffer2
  //retourne
  // 0 si chaine NON conforme à GRBL
  // 1 si = 0x0D ou 0x0A
  // 2 si = '<.........
  // 3 si = '[......... 
  // 4 si = 'er........ 
  // 5 si = 'ok........ 
  // 6 si  incompris 
  //DEBUGSerial.println("Traite");
  //DEBUGSerial.print(buffer2);
 switch(buffer2[0])
 {
  case 0x00 :  //Traite1();
              if(EnableDEBUG2==true){Incompris(buffer2);          printStringlnColor(" >> Commande inconnue (0)",IHM_RED,1);}
              return(0);
              break;
  case 0x0A : //Suppression 0x0a
              return(1);
              break;
  case 0X0D : if(EnableDEBUG2==true)
               { 
               // printStringlnColor("ok",IHM_GREEN,1);
               }
              return(1);
              break;

  case '<' :  (Traite1());
              return(2);
              break;
              
  case '[' :  //(Traite2());
              return(3);
              break;

  case 'e' :
  case 'E' :  if ( ((buffer2[1]=='r') | (buffer2[1]=='R')) &
                   ((buffer2[2]=='r') | (buffer2[2]=='R')))
               { //erreur
                Incompris(buffer2); printStringlnColor(" >> Erreur",IHM_RED,1);
                CNC.NbOk++;        
               }
//            (Traite2());
              return(4);              
              break;
  case 'o' :
  case 'O' :  if ((buffer2[1]=='k')|(buffer2[1]=='K'))
               { //Cool au moins une commande comprise
                CNC.NbOk++;        
                if(EnableDEBUG2==true){Incompris(buffer2);          printStringlnColor(" >> OK",IHM_GREEN,1);}
               }
              return(5);
              break;

  case 'G' :  if (buffer2[1]=='r')  //Presentation de grbl = Allumage a chaud
               { //
                CNC.NbOk++;        
                if(EnableDEBUG2==true){Incompris(buffer2);          printStringlnColor(" >> OK",IHM_GREEN,1);}
               }
              return(6);
              break;

  case '$' :    CNC.NbOk++; // Rece^tion des parametres grbl
              if(EnableDEBUG2==true){Incompris(buffer2);}
              return(7);
              break;

  default  :  //Traite1();
              Incompris(buffer2);          printStringlnColor(" >> Commande inconnue",IHM_RED,1);
              return(8);
              break;
 }  
 return(254);
} 

uint8_t  Traite1(){
  uint8_t p=0;
  String grblStat="";
  // Conversion du buffer2 en string
  do{grblStat+=buffer2[p];p++;}while ((buffer2[p]!=0)&&(p<MAX_BUF));
  grblStat.toUpperCase();
  DEBUGSerial.println("Traite1");
// Cherche si la chaine est bien dans le format "<....>"                         // 
//                                                                               //    <Idle|MPos:0.000,0.000,0.000|FS:0,0|WCO:0.000,0.000,0.000>
  uint16_t startStatPos = grblStat.indexOf("<");  if (startStatPos==-1)return(1);//    ^
  uint16_t endStatPos   = grblStat.indexOf(">");  if (endStatPos==-1)  return(1);//                                                             ^
  uint16_t endStatusPos = grblStat.indexOf("|");  if (endStatusPos==-1)return(1);//         ^
  //Extract Status from <....>                                                   //
//a verifier  CNC.State = grblStat.substring(startStatPos+1, endStatusPos-0);                //     Idle
  // Clean received data                                                         //    <Idle|MPos:0.000,0.000,0.000|FS:0,0|WCO:0.000,0.000,0.000>
  grblStat = grblStat.substring(startStatPos+1, endStatPos-0);                   //     Idle|MPos:0.000,0.000,0.000|FS:0,0|WCO:0.000,0.000,0.000   //  Idle|MPos:0.000,0.000,0.000|FS:0,0|Ov:100,100,100
  grblStat.replace("|MPOS:",",");                                                //     Idle,     0.000,0.000,0.000|FS:0,0|WCO:0.000,0.000,0.000   //  Idle,     0.000,0.000,0.000|FS:0,0|Ov:100,100,100
  grblStat.replace("|WPOS:",",");                                                //     Idle,     0.000,0.000,0.000|FS:0,0|WCO:0.000,0.000,0.000   //  Idle,     0.000,0.000,0.000|FS:0,0|Ov:100,100,100
  grblStat.replace(  "|BF:",",");                                                //     Idle,     0.000,0.000,0.000|FS:0,0|WCO:0.000,0.000,0.000   //  Idle,     0.000,0.000,0.000|FS:0,0|Ov:100,100,100
  grblStat.replace(  "|FS:",",");                                                //     Idle,     0.000,0.000,0.000,   0,0|WCO:0.000,0.000,0.000   //  Idle,     0.000,0.000,0.000,     0,0|Ov:100,100,100  
  grblStat.replace( "|WCO:",",");                                                //     Idle,     0.000,0.000,0.000,   0,0,0.000,0.000,0.000       //  Idle,     0.000,0.000,0.000,0,0|Ov:100,100,100  
  grblStat.replace(  "|OV:",",");                                                //     Idle,     0.000,0.000,0.000,   0,0,0.000,0.000,0.000       //  Idle,     0.000,0.000,0.000,0,0,   100,100,100  
  grblStat.replace(  "|SE:",",");                                                //     Idle,     0.000,0.000,0.000,   0,0,0.000,0.000,0.000       //  Idle,     0.000,0.000,0.000,0,0,100,100,100  
  grblStat.replace(  "|PN:",",");                                                //     Idle,     0.000,0.000,0.000,   0,0,0.000,0.000,0.000       //  Idle,     0.000,0.000,0.000,0,0,100,100,100  
//                                                                               //     IDLE,0.000,0.000,0.000,0,0,0.000,0.000,0.000
TOTAL(3);
  toSplitCommand(grblStat, ",");
  //DEBUGSerial.println("Traite1 Chacked");
  TOTAL(4);
  for(int i = 0; i < grblValLasted; i++)                 // Copy data from tool array to user array                    
   {
     grblStatusValues[i] = SplittingArray[i];
   }
   TOTAL(5);
   if(grblStatusValues[grblValStatus]!="")
   {
    String ff="";
    ff=grblStatusValues[grblValMachX];  CNC.X       = ff.toFloat();
    ff=grblStatusValues[grblValMachY];  CNC.Y       = ff.toFloat();
    ff=grblStatusValues[grblValMachZ];  CNC.Z       = ff.toFloat();
    ff=grblStatusValues[grblSpindle];   CNC.BRGet   = ff.toFloat();
    ff=grblStatusValues[grblFeed];      CNC.FEEDGet = ff.toFloat();

    CNC.State=grblStatusValues[grblValStatus];
   }
   TOTAL(6);
  //DEBUGSerial.print("X:");  DEBUGSerial.println(CNC.X);
  return(2);
}

uint8_t  Traite2(){
  uint8_t p=0;
  String grblStat="";
  String grblValue="";
  // Convertion du buffer2 en string
  do{grblStat+=buffer2[p];p++;}while ((buffer2[p]!=0)&&(p<MAX_BUF));
  grblStat.toUpperCase();

// Cherche si la chaine est bien dans le format "[....]" 
//                                                                                        [G55:12.000,900.999,222.110]
  uint16_t startStatPos = grblStat.indexOf("[");  if (startStatPos==-1)return(1);//       ^
  uint16_t endStatPos   = grblStat.indexOf("]");  if (endStatPos==-1)  return(1);//                                  ^
  uint16_t endStatusPos = grblStat.indexOf(":");  if (endStatusPos==-1)return(1);//           ^
  //Extract data from [....]                                                     //
  //CNC.State = grblStat.substring(startStatPos+1, endStatusPos-0);              //
  // Clean received data                                                         // 
  grblValue= grblStat.substring(startStatPos+1, endStatusPos-0);                 //        G55
  grblStat = grblStat.substring(startStatPos+1, endStatPos-0);                   //        G55:12.000,900.999,222.110

  for(int i = 0; i <= 4; i++)
   {
     grblStatusValues[i] = SplittingArray[i];
   }

 if (grblStat.startsWith("G54:",0)){printStringlnColor("Got G54",IHM_PINK,1);return(0);}
 if (grblStat.startsWith("G55:",0)){printStringlnColor("Got G55",IHM_PINK,1);return(0);}
 if (grblStat.startsWith("G56:",0)){printStringlnColor("Got G56",IHM_PINK,1);return(0);}
 if (grblStat.startsWith("G57:",0)){printStringlnColor("Got G57",IHM_PINK,1);return(0);}
 if (grblStat.startsWith("G58:",0)){printStringlnColor("Got G58",IHM_PINK,1);return(0);}
 if (grblStat.startsWith("G59:",0)){printStringlnColor("Got G59",IHM_PINK,1);return(0);}
 if (grblStat.startsWith("G28:",0)){printStringlnColor("Got G28",IHM_PINK,1);return(0);}
 if (grblStat.startsWith("G30:",0)){printStringlnColor("Got G30",IHM_PINK,1);return(0);}
 if (grblStat.startsWith("G92:",0)){printStringlnColor("Got G92",IHM_PINK,1);return(0);}
 if (grblStat.startsWith("TL0:",0)){printStringlnColor("Got TL0",IHM_PINK,1);return(0);}
 if (grblStat.startsWith("PRB:",0)){printStringlnColor("Got PRB",IHM_PINK,1);return(0);}
 return(3);
}

//-----------------------------------------------------------------------------------------------------------------------------
// toSplitCommand for to split received string delimited with expected char separator par1, par2, par3, .....
// and put them in an array (SplittingArray)
//enum grblStatusValuesIndex {grblValStatus, grblValMachX, grblValMachY, grblValMachZ, grblFeed, grblSpindle, grbl6, grbl7, grbl8};
//-----------------------------------------------------------------------------------------------------------------------------
void toSplitCommand(String SplitText, String SplitChar) {
  SplitText = SplitChar + SplitText ;
  int SplitCount = SplittingArraySize;
  int SplitIndex = -1;
  int SplitIndex2;
  for(int i = 0; i < SplitCount - 1; i++) {
    SplitIndex  = SplitText.indexOf(SplitChar, SplitIndex + 1);
    SplitIndex2 = SplitText.indexOf(SplitChar, SplitIndex + 1);
    if(SplitIndex2 < 0) SplitIndex2 = SplitText.length() ;
    SplittingArray[i] = SplitText.substring(SplitIndex+1, SplitIndex2);
    SplittingArray[i+1] = "#";
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonctions de debug  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//int decoupe()
//{
//    char* sub;
//    char chaine[] = "Bonjour, comment allez vous ? Moi impec !";
//    sub = strtok(chaine,",?! ");
//    while(sub)
//    {
//        printf("%s\n",sub);
//        sub = strtok(NULL,",?! ");
//    }
//    return 0;
//}
