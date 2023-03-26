import processing.serial.*;
Serial port;
String[] comList;
int portNum;
int posLine = 90;
//Textarea statusArea;
boolean selected = false, firstScan = false;
public void guiSetup() {
 Button ClearOutput, connectButton, disconnectButton,G17,G18,G19,cercle,Run;
  
  cp5 = new ControlP5(this);
  cp5.setAutoDraw(true);  // true permet de ne pas gérer le redessinage de cp5
  
  
  
  cp5.getTab("default")
     .activateEvent(true) // if you want to receive a controlEvent when a  tab is clicked, use activeEvent(true)
     .setSize(100,100)
     .setLabel("VIEW")
     .setId(1);


     PFont pfont = createFont("Arial", 25, true); // use true/false for smooth/no-smooth
     ControlFont font = new ControlFont(pfont, 16);
     //ControlFont font2 = new ControlFont(pfont, 25);
     cp5.setFont(font);
     
     //statusArea = cp5.addTextarea("statusArea")
     //             .setPosition(5,  height-35)
     //             .setSize( width-10, 30)
     //             .setFont(createFont("consolas", 16))
     //             .setLineHeight(14)
     //             .setColor(#FFFFFF)
     //             .setColorBackground(#114444)
     //             .setScrollBackground(#288222)
     //             .scroll(1);
                  

   
}


void GUI_refresh(){
  //GUI_VIEW_Refresh();
  //PosRefresh();
//   cp5.get(Textarea.class,"statusArea")
//                  .setPosition(5,  height-25)
//                  .setSize( width-10, 20)
//       //.updateSize()
//       ;
}


void output(int code1, String s) {
  //codes               0          1          2          3          4          5          6          7          8          9          10         11
  String[] codes = {"       ", "[ECHO] ", "[SETUP]", "[TRACE]", "[PRG] ", "[KINE] ", "[ERROR]", "[WARN] ", "[INFO] ", "     > ", "[CMD]  ", "[APP]  "};
  s=trim(s);
 if(s!=null){  
   outputArea.append(codes[code1] + " " + " " + s + "\n");
 }
}

Textfield inputField;
Button ClearOutput, connectButton, disconnectButton,G17,G18,G19,cercle,Run;
Textarea outputArea;
ScrollableList portsList;
Toggle ShowAll, ShowCMD;
Textlabel ShowAllLabel,ShowCMDLabel;

void GUI_CONNECT() {

  PFont pfont = createFont("Arial", 25, true); // use true/false for smooth/no-smooth
  ControlFont font = new ControlFont(pfont, 16);

  cp5.addTab("CONNECT")
    .setColorBackground(color(0, 160, 100))
    .setColorLabel(color(255))
    .setColorActive(color(255, 128, 0)) ;

  outputArea = cp5.addTextarea("serialOutput")
    .setPosition(2, 20)
    .setSize(495, 425)
    .setFont(createFont("consolas", 16))
    .setLineHeight(14)
    .setColor(#FFFFFF)
    .setColorBackground(#444444)
    .setScrollBackground(#222222)
    .scroll(1)
    .showScrollbar();

  cp5.getTab("CONNECT").activateEvent(true).setId(2);

  //COM port selection
  comList = Serial.list();
  portsList = cp5.addScrollableList("portsList")
    //portsList = cp5.addScrollableList(comList.toString())
    .setPosition(2, 500)
    .setSize(190, 100)
    .setBarHeight(25)
    .setItemHeight(25)
    .setItems(comList)
    .setLabel(" COM ports")
    .setBroadcast(true)
    .close();

 

  //COM port connect
  connectButton = cp5.addButton("connectButton")
    .setPosition(200, 500)
    .setSize(90, 20)
    .setLabel("connect");

  //COM port disconnect
  disconnectButton = cp5.addButton("disconnectButton")
    .setPosition(320, 500)
    .setSize(120, 20)
    .setLabel("disconnect");

  ShowAll=cp5.addToggle("ShowAll")
    .setPosition(530, 65)
    .setSize(50, 20)
    .setValue(false)
    .setLabel("")
    .setMode(ControlP5.SWITCH);
  ShowAllLabel=cp5.addTextlabel("ShowAllLabel").setText("All").setPosition(580, 65).setColorValue(#00FF00).setFont(font);

  ShowCMD=cp5.addToggle("ShowCMD")
    .setPosition(530, 90)
    .setSize(50, 20)
    .setValue(false)
    .setLabel("")
    .setMode(ControlP5.SWITCH)
    .hide();
 ShowCMDLabel=cp5.addTextlabel("ShowCMDLabel").setText("CMD").setPosition(580, 90).setColorValue(#00FF00).setFont(font).hide();

  //serial input
  inputField  = cp5.addTextfield("serialInput").setPosition(2, 450).setSize(495, 30).setAutoClear(false).setLabel("").setFocus(true);
  ClearOutput = cp5.addButton("ClearOutput").setPosition(200, 550).setSize(70, 20).setLabel("Clear").setBroadcast(true).hide();

  cp5.getController("connectButton").moveTo("CONNECT");
  cp5.getController("disconnectButton").moveTo("CONNECT");
  cp5.getController("portsList").moveTo("CONNECT");
  cp5.getController("ShowAll").moveTo("CONNECT");
  cp5.getController("ShowAllLabel").moveTo("CONNECT");
  cp5.getController("ShowCMD").moveTo("CONNECT");
  cp5.getController("ShowCMDLabel").moveTo("CONNECT");
  cp5.getController("ClearOutput").moveTo("CONNECT");
  cp5.getController("serialInput").moveTo("CONNECT");
  outputArea.moveTo("CONNECT");
}

public void serialOutput(String s) {
  //tab size fix
}

public void angleSlider(int angle) {
  posLine = angle;
}

public void portsList(int n) {
  
  selected = true;
  portNum = n;
}

void mousePressed() {
   //  println("["+ mouseX + ";" + mouseY+"]");

   

   
   
 }
 
void importTextFile(String fileName) {
 
}


void GUI_CONNECT_Refresh() {
  portsList = cp5.addScrollableList("portsList")
    .setItems(Serial.list())
    .close();
}
