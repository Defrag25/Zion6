

boolean shiftOn=false;
float penPos=0;



PGraphics j2, p2, p3;

void setup(){
    size(1200, 800, P3D);
     j2 = createGraphics(width/4, width/4, JAVA2D);
  p2 = createGraphics(width, height/4-20, P2D);
  p3 = createGraphics(width-145, height-30, P3D);
    guiSetup();
    initRobot();
     getGraphics();
}

void draw(){ 
     background(32);
 //drawRect(j2);
  drawRandomColor(p2);
 // drawSphere(p3);  
 //    cp5.draw();

drawRobot(p3);
      // End of 3D start of 2D HUD


  image(p3, 140, 20);
//  image(p2, 0, height-20/4+20);
  //image(j2, 20, height-width/4-20);
}

void mouseDragged(){
    rotY -= (mouseX - pmouseX) * 0.01;
    rotX -= (mouseY - pmouseY) * 0.01;
}



void mouseWheel(MouseEvent e){
 if(shiftOn==false) TransZ = TransZ-25*e.getCount();
 else posY=posY+25*e.getCount();
 if(bpen==true) penPos = penPos-25*e.getCount();
 }

void keyPressed() {
  if (keyCode == SHIFT) { shiftOn = true; }else {shiftOn = false;}
  if (keyCode == CONTROL) { bpen = true; }else {bpen = false;}
}
 
