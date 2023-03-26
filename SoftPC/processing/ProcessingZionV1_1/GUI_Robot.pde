
Button RemoteON,RemoteOFF;
Toggle ShowAxes,MoveAxes;
float angle = 0;
boolean AfficheAngle=true;
public void zguiSetup() {

  
  cp5 = new ControlP5(this);
  cp5.setAutoDraw(true);  // true permet de ne pas gérer le redessinage de cp5
  
   cp5.addTab("POWER")
    .setColorBackground(color(0, 160, 100))
    .setColorLabel(color(255))
    .setColorActive(color(255, 128, 0)) ;
  
  cp5.getTab("default")
     .activateEvent(true) // if you want to receive a controlEvent when a  tab is clicked, use activeEvent(true)
     .setSize(100,100)
     .setLabel("VIEW")
     .setId(1);


     PFont pfont = createFont("Arial", 25, true); // use true/false for smooth/no-smooth
     ControlFont font = new ControlFont(pfont, 16);
     //ControlFont font2 = new ControlFont(pfont, 25);
     cp5.setFont(font);
     
     RemoteON    = cp5.addButton("RemoteON").setPosition(10, 50).setSize(100, 20).setLabel("ON");
     RemoteOFF   = cp5.addButton("RemoteOFF").setPosition(10, 80).setSize(100, 20).setLabel("OFF");
     ShowAxes    = cp5.addToggle("Axes")
                      .setPosition(100,150)
                      .setSize(50,20)
                      .setValue(true)
                      .setMode(ControlP5.SWITCH)  ;
     MoveAxes    = cp5.addToggle("MoveAxes")
                      .setPosition(100,220)
                      .setSize(50,20)
                      .setValue(false)
                      .setMode(ControlP5.SWITCH)  ;
  //cp5.getController("ShowAxes").moveTo("default");
   
}
void RemoteON(){
  println("bouton ON");
  AfficheAngle=true;
  
}

void RemoteOFF(){
  println("bouton OFF");
  AfficheAngle=false;
  
}
