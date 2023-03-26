float angle = 0;
import controlP5.*;
ControlP5 cp5;
Button RemoteON;

void setup() {
  size(600, 400, P3D);
    cp5 = new ControlP5(this);
  cp5.setAutoDraw(true);  // true permet de ne pas gérer le redessinage de cp5
  
  
     PFont pfont = createFont("Arial", 25, true); // use true/false for smooth/no-smooth
     ControlFont font = new ControlFont(pfont, 16);
     //ControlFont font2 = new ControlFont(pfont, 25);
     cp5.setFont(font);
     
     RemoteON    = cp5.addButton("RemoteON").setPosition(10, 10).setSize(50, 20).setLabel("Remote ON");

  getGraphics();
}
void RemoteON(){
  print("bp5");
}
void draw() {
  background(64);
  // Start of 3D drawing
  pushMatrix();
  translate(100+width/2, height/2);
  rotateX(angle);
  rotateY(angle * 1.123);
  angle += 0.01;
  fill(200, 200, 0);
  stroke(0, 64, 0);
  strokeWeight(1);
  sphereDetail(32);
  sphere(150);
  popMatrix();
  // End of 3D start of 2D HUD
  getGraphics().hint(PConstants.DISABLE_DEPTH_TEST);
  fill(255, 160);
  stroke(0);
  strokeWeight(6);
  rect(3, height-20, width-6, 18);
  getGraphics().hint(PConstants.ENABLE_DEPTH_TEST);
}
