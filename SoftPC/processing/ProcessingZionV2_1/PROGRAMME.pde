///////////////////
// GUI PROGRAMME //
///////////////////
import java.awt.Font;
Textarea ProgArea;
Button ClearProg,Prog,Swit,ProgStep;
 //PImage[] PowerBtnImg = {loadImage("Power1.png"), loadImage("Power1.png"), loadImage("Power1.png")};
 
int PrgLine =1;
 
 
 
 
void GUI_PROG(){
  
  cp5.addTab("PROGRAMME")
     .setColorBackground(color(0, 160, 100))
     .setColorLabel(color(255))
     .setColorActive(color(255,128,0))
     ;
 
 cp5.getTab("PROGRAMME").activateEvent(true).setId(3);
    
 ProgArea = cp5.addTextarea("ProgOutput")
                  .setPosition(2, 20)
                  .setSize(495, 425)
                  .setFont(createFont("consolas", 16))
                  .setLineHeight(14)
                  .setColor(#FFFFFF)
                  .setColorBackground(#909090)
                  .setScrollBackground(#222222)
                  .scroll(10)                 
             
                  .showScrollbar();
  
  Prog = cp5.addButton("Prog")
       .setPosition(525, 400)
//       .setImages(loadImage("Power1.png"), loadImage("Power1.png"), loadImage("Power1.png"))
       .setSize(70, 20)
//       .updateSize()
       .setLabel("LOAD")
       .setBroadcast(true)       ;
  ProgStep = cp5.addButton("ProgStep")
       .setPosition(525, 370)
       .setSize(70, 20)
       .setLabel("Step")
       .setBroadcast(true)       ;

 Swit = cp5.addButton("GO")
       .setPosition(625, 400)
       .setSize(70, 20)
       .setLabel("GO")
       .setBroadcast(true)       ;

  ClearProg = cp5.addButton("ClearProgOutput")
          .setPosition(525, 425)
          .setSize(70, 20)
          .setLabel("Clear")
           .setBroadcast(true);

    cp5.getController("Prog").moveTo("PROGRAMME");
    cp5.getController("ProgStep").moveTo("PROGRAMME");
    cp5.getController("GO").moveTo("PROGRAMME");
    ProgArea.moveTo("PROGRAMME");
    ClearProg.moveTo("PROGRAMME");
   

}
public void GO(){
  println ("change");
  //cp5.setTab("default");
  cp5.getTab("default").bringToFront();
}

public void ProgOutput(String s) {
  //tab size fix
}

void ClearProgOutput(){
 ProgArea.clear();
}

void outputProg(int code1, String s) {
//void ProgPrint(int code1, String s) {
  //codes               0          1          2          3          4          5          6          7          8          9          10         11
  String[] codes = {"       ", "[ECHO] ", "[SETUP]", "[TRACE]", "[PRG] ", "[PWM]  ", "[ERROR]", "[WARN] ", "[INFO] ", "     > ", "[CMD]  ", "[APP]  "};
  ProgArea.append(codes[code1] + " " + " " + s + "\n");
}

void OpenDialog() {
  selectInput("Select a file to process:", "fileOpenSelected",dataFile(AppDataPath));//dataFile(AppDataPath));
}

void fileOpenSelected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    importTextFile(selection.getAbsolutePath());
  }
}

void SaveDialog() {
  
  selectOutput("Select a file to write to:", "fileSaveSelected",dataFile(AppDataPath));//dataFile(AppDataPath));
}
void fileSaveSelected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    importTextFile(selection.getAbsolutePath());
  }
}
public void serialInput(String s){
    if(true){ //Delta.Connected) {
      int len = s.length();
      output(10,s.substring(0,len));
    //  Delta.send(s.substring(0,len));
    }

}
