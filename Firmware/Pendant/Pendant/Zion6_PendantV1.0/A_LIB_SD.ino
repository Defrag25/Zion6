#include <SPI.h>
#include <SD.h>

uint16_t SDRoyalIndex=0;
uint16_t IndexSelected=0;

void printDirectory(File dir, int numTabs,boolean AffIndex) ;
void printDirectorySimple(File dir); 

File root;

const int chipSelect = 10;    

void SDWRTemp(char *Name,uint8_t Csize)
{
  SD.begin(chipSelect); 
  printStringColor("Lecture de : ",IHM_BLUE,Csize);printStringColor(Name,IHM_WHITE,Csize);printStringln(" ");
  Line[0]=0;
  File myFile = SD.open(Name);
  if (myFile) 
   {
    printStringlnColor(Name,IHM_GREEN,Csize);//printStringln(" ");
    Line[0]=0;
    LinePos=0;
    while (myFile.available()) {
      char s=myFile.read();
      Line[LinePos++]=s;      Line[LinePos]=0;
      if(LinePos>(MAX_CARAC - 1)){LinePos=0;}  
      if (s==0x0d) 
       {
        printStringColor(Line,IHM_WHITE,Csize); LinePos=0; 
       }
    }
    myFile.close();
    printStringlnColor("<END>",IHM_GREEN,Csize);
   } else {
    printStringColor("Erreur d'ouverture : ",IHM_RED,Csize);printStringColor(Name,IHM_WHITE,Csize);printStringln(" ");
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SD Directory //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SD_DIR(uint8_t Csize,boolean PrintOrNot){

  root = SD.open("/");
  SDRoyalIndex=0;    
  printDirectory(root, 0 , true);
}

void printDirectory(File dir, int numTabs,boolean AffIndex) 
{
 boolean PrintOrNot=true;  
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }

      SDRoyalIndex++;    
      printDecColor(SDRoyalIndex, IHM_GREEN,Csize);printStringColor(":", IHM_GREEN,Csize);
    
    for (uint8_t i = 0; i < numTabs; i++) { printStringColor("|",IHM_GRAY,Csize); }
    
    if (entry.isDirectory()) {
      if(IndexSelected==SDRoyalIndex){     printStringlnColor(entry.name(),IHM_GREEN,Csize);    }
      else                           {     printStringlnColor(entry.name(),IHM_GRAY ,Csize);    }
      printDirectory(entry, numTabs + 1, true);
    } else {
      if(IndexSelected==SDRoyalIndex){  printStringColor(entry.name(),  IHM_GREEN,          Csize); 
                                        if(dir.name()!="/"){ strcpy(FileSelected,dir.name());
                                                             strcat(FileSelected,"/");                                                                    
                                                             strcat(FileSelected,entry.name());
                                                           }
                                     else                  {
                                                             strcpy(FileSelected,entry.name());
                                                           }
                                     }
      else                           {  printStringColor(entry.name(),  IHM_WHITE,          Csize);    }

      PosTab(20);      printFloatColor(entry.size(),IHM_BLUE,Csize,0);CRLF();
    }
    entry.close();
  }
// Faire Stop affichage 
}


long SD_DIRSimple(){
  root = SD.open("/");
  SDRoyalIndex=0;    
  printDirectorySimple(root);
}

void printDirectorySimple(File dir) 
// FileSelected prend le nom du fichier d'index SDRoyalIndex
{
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
      SDRoyalIndex++;    
    if (entry.isDirectory()) { printDirectorySimple(entry);  } 
    else 
     { if(IndexSelected==SDRoyalIndex)
            {
              if(dir.name()!="/")
               {
                strcpy(FileSelected,dir.name());
                strcat(FileSelected,"/");                                                                    
                strcat(FileSelected,entry.name());
               }
              else { strcpy(FileSelected,entry.name()); }
            }
     }
    entry.close();
  }
}
