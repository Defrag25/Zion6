
Button RemoteON,RemoteOFF;
Toggle ShowAxes,ProcessIK,ShowGridX,ShowGridY,ShowGridZ;

Toggle ShowPen;
Slider SliderAxe1,SliderAxe2,SliderAxe3,SliderAxe4,SliderAxe5,SliderAxe6;;
Slider PtX,PtY,PtZ;
float angle = 0;
boolean AfficheAngle=false;
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
     ShowAxes    = cp5.addToggle("Axes")     .setPosition(100,150).setSize(50,20).setValue(true).setMode(ControlP5.SWITCH)  ;
     ProcessIK   = cp5.addToggle("ProcessIK").setPosition(100,200).setSize(50,20).setValue(false).setMode(ControlP5.SWITCH)  ;
     ShowPen     = cp5.addToggle("Pen")  .setPosition(100,250).setSize(50,20).setValue(true).setMode(ControlP5.SWITCH)  ;
     ShowGridX   = cp5.addToggle("GridX")  .setPosition(170,150).setSize(50,20).setValue(true).setMode(ControlP5.SWITCH)  ;
     ShowGridY   = cp5.addToggle("GridY")  .setPosition(240,150).setSize(50,20).setValue(true).setMode(ControlP5.SWITCH)  ;
     ShowGridZ   = cp5.addToggle("GridZ")  .setPosition(310,150).setSize(50,20).setValue(true).setMode(ControlP5.SWITCH)  ;

     SliderAxe1 = cp5.addSlider("Axe1").setPosition(10, 550).setSize(390, 20).setRange(-90, 90).setLabel("Axe1").setSliderMode(Slider.FLEXIBLE).setNumberOfTickMarks(18);
     SliderAxe1.showTickMarks(true).snapToTickMarks(false).setValue(0);
     SliderAxe1.getValueLabel().align(ControlP5.CENTER, ControlP5.LEFT_OUTSIDE).setPaddingX(-20);
     SliderAxe2 = cp5.addSlider("Axe2").setPosition(10, 590).setSize(390, 20).setRange(-10, 90).setLabel("Axe2").setSliderMode(Slider.FLEXIBLE).setNumberOfTickMarks(18);
     SliderAxe2.showTickMarks(true).snapToTickMarks(false).setValue(0);
     SliderAxe2.getValueLabel().align(ControlP5.CENTER, ControlP5.LEFT_OUTSIDE).setPaddingX(-20);
     SliderAxe3 = cp5.addSlider("Axe3").setPosition(10, 630).setSize(390, 20).setRange(-90, 45).setLabel("Axe3").setSliderMode(Slider.FLEXIBLE).setNumberOfTickMarks(18);
     SliderAxe3.showTickMarks(true).snapToTickMarks(false).setValue(0);
     SliderAxe3.getValueLabel().align(ControlP5.CENTER, ControlP5.LEFT_OUTSIDE).setPaddingX(-20);

     SliderAxe4 = cp5.addSlider("Axe4").setPosition(10, 670).setSize(390, 20).setRange(-120, 120).setLabel("Axe4").setSliderMode(Slider.FLEXIBLE).setNumberOfTickMarks(18);
     SliderAxe4.showTickMarks(true).snapToTickMarks(false).setValue(0);
     SliderAxe4.getValueLabel().align(ControlP5.CENTER, ControlP5.LEFT_OUTSIDE).setPaddingX(-20);
     SliderAxe5 = cp5.addSlider("Axe5").setPosition(10, 710).setSize(390, 20).setRange(-120, 120).setLabel("Axe5").setSliderMode(Slider.FLEXIBLE).setNumberOfTickMarks(18);
     SliderAxe5.showTickMarks(true).snapToTickMarks(false).setValue(0);
     SliderAxe5.getValueLabel().align(ControlP5.CENTER, ControlP5.LEFT_OUTSIDE).setPaddingX(-20);
     SliderAxe6 = cp5.addSlider("Axe6").setPosition(10, 750).setSize(390, 20).setRange(-180, 180).setLabel("Axe6").setSliderMode(Slider.FLEXIBLE).setNumberOfTickMarks(18);
     SliderAxe6.showTickMarks(true).snapToTickMarks(false).setValue(0);
     SliderAxe6.getValueLabel().align(ControlP5.CENTER, ControlP5.LEFT_OUTSIDE).setPaddingX(-20);

     PtX = cp5.addSlider("PtX").setPosition(10, 300).setSize(390, 20).setRange(-100, 100).setLabel("Z").setSliderMode(Slider.FLEXIBLE).setNumberOfTickMarks(18);
     PtX.showTickMarks(true).snapToTickMarks(false).setValue(0);
     PtX.getValueLabel().align(ControlP5.CENTER, ControlP5.LEFT_OUTSIDE).setPaddingX(-20);
     PtY = cp5.addSlider("PtY").setPosition(10, 350).setSize(390, 20).setRange(-100, 100).setLabel("Y").setSliderMode(Slider.FLEXIBLE).setNumberOfTickMarks(18);
     PtY.showTickMarks(true).snapToTickMarks(false).setValue(0);
     PtY.getValueLabel().align(ControlP5.CENTER, ControlP5.LEFT_OUTSIDE).setPaddingX(-20);
     PtZ = cp5.addSlider("PtZ").setPosition(10, 400).setSize(390, 20).setRange(-100, 100).setLabel("Z6").setSliderMode(Slider.FLEXIBLE).setNumberOfTickMarks(18);
     PtZ.showTickMarks(true).snapToTickMarks(false).setValue(0);
     PtZ.getValueLabel().align(ControlP5.CENTER, ControlP5.LEFT_OUTSIDE).setPaddingX(-20);

}
void RemoteON(){
  println("bouton ON");
  AfficheAngle=true;
  
}

void RemoteOFF(){
  println("bouton OFF");
  AfficheAngle=false;
  
}
