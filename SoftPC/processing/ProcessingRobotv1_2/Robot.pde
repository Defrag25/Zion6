PShape base, shoulder, upArm, loArm, end,pen;

float rotX, rotY;
float posX=1, posY=50, posZ=50;
float alpha, beta, gamma;
float F = 50;
float T = 70;
float millisOld, gTime, gSpeed = 4;
float TransZ=0;
boolean bpen;
float[] Xsphere = new float[99];
float[] Ysphere = new float[99];
float[] Zsphere = new float[99];
PVector world = new PVector();

void initRobot(){
      base = loadShape("r5.obj");
    shoulder = loadShape("r1.obj");
    upArm = loadShape("r2.obj");
    loArm = loadShape("r3.obj");
    end = loadShape("r4.obj");
    pen = loadShape("pen.obj");
    
    shoulder.disableStyle();
    upArm.disableStyle();
    loArm.disableStyle();

}


void drawRobot(PGraphics pg){
    pg.beginDraw();
    pg.clear();
    pg.pushMatrix();
    writePos();

   //smooth();

   pg.lights(); 
   pg.directionalLight(51, 102, 126, -1, 0, 0);
    
    for (int i=0; i< Xsphere.length - 1; i++) {
    Xsphere[i] = Xsphere[i + 1];
    Ysphere[i] = Ysphere[i + 1];
    Zsphere[i] = Zsphere[i + 1];
    }
    
    Xsphere[Xsphere.length - 1] = posX;
    Ysphere[Ysphere.length - 1] = posY;
    Zsphere[Zsphere.length - 1] = posZ;
   
   pg.line(0,0,0,1000,1000,1000);
   pg.noStroke()   ;
   
    pg.fill(255);
  pg.textSize(16);
  pg.text("Frame rate: " + int(frameRate), 10,pg.height-2);
  //cp5.draw();
   
   pg.translate(width/2,height/2,100+TransZ);

   pg.rotateX(rotX);
   pg.rotateY(-rotY);
   pg.scale(-4);
   
   
   for (int i=0; i < Xsphere.length; i++) {
     pg.pushMatrix();
     pg.translate(-Ysphere[i], -Zsphere[i]-11, -Xsphere[i]);
     pg.fill (#D003FF, 25);
     pg.sphere (float(i) / 20);
     pg.popMatrix();
    }
    
   pg.fill(#FFE308);  
   pg.translate(0,-40,0); 
   pg.shape(base);
   if(AfficheAngle)pg.text("Axe1",10,10);
   
   pg.translate(0, 4, 0);
   pg.rotateY(gamma);
   pg.shape(shoulder);
   pg.translate(0,0,-10); 
   
   pg.translate(0, 25, 0);
   pg.rotateY(PI);
   pg.rotateX(alpha);
   pg.shape(upArm);
   if(AfficheAngle)pg.text("Axe2",10,10);
         
   pg.translate(0, 0, 50);
   pg.rotateY(PI);
   pg.rotateX(beta);
   pg.shape(loArm);
   if(AfficheAngle)pg.text("Axe3",0,0);
       
   pg.translate(0, 0, -50);
   pg.rotateY(PI);
   pg.shape(end);
   if(AfficheAngle)      pg.text("Axe4",0,0);
  
   pg.translate(0, 0, -50+penPos);
   pg.rotateY(PI);
   pg.shape(pen);
   if(AfficheAngle)      pg.text("pen",0,0);
   pg.popMatrix();
   pg.endDraw();
}

void IK(){
  float X = posX;
  float Y = posY;
  float Z = posZ;

  float L = sqrt(Y*Y+X*X);
  float dia = sqrt(Z*Z+L*L);

  alpha = PI/2-(atan2(L, Z)+acos((T*T-F*F-dia*dia)/(-2*F*dia)));
  beta = -PI+acos((dia*dia-T*T-F*F)/(-2*F*T));
  gamma = atan2(Y, X);
  
}

void setTime(){
  gTime += ((float)millis()/1000 - millisOld)*(gSpeed/4);
  if(gTime >= 4)  gTime = 0;  
  millisOld = (float)millis()/1000;
}

void writePos(){
  IK();
  setTime();
  posX = sin(gTime*PI/2)*70;
  posZ = sin(gTime*PI)*10;
}

void drawRobotolg(){
       pushMatrix();
     writePos();

   //smooth();

   lights(); 
   directionalLight(51, 102, 126, -1, 0, 0);
    
    for (int i=0; i< Xsphere.length - 1; i++) {
    Xsphere[i] = Xsphere[i + 1];
    Ysphere[i] = Ysphere[i + 1];
    Zsphere[i] = Zsphere[i + 1];
    }
    
    Xsphere[Xsphere.length - 1] = posX;
    Ysphere[Ysphere.length - 1] = posY;
    Zsphere[Zsphere.length - 1] = posZ;
   
   line(0,0,0,1000,1000,1000);
   noStroke()   ;
   
    fill(255);
  textSize(16);
  text("Frame rate: " + int(frameRate), 10, 30);
  //cp5.draw();
   
   translate(width/2,height/2,100+TransZ);

   rotateX(rotX);
   rotateY(-rotY);
   scale(-4);
   
   
   for (int i=0; i < Xsphere.length; i++) {
     pushMatrix();
     translate(-Ysphere[i], -Zsphere[i]-11, -Xsphere[i]);
     fill (#D003FF, 25);
     sphere (float(i) / 20);
     popMatrix();
    }
    
   fill(#FFE308);  
   translate(0,-40,0); 
       if(AfficheAngle)text("Axe1",10,10);
     shape(base);
   
   translate(0, 4, 0);

   rotateY(gamma);
     shape(shoulder);
     translate(0,0,-10); 
   translate(0, 25, 0);
   rotateY(PI);
   rotateX(alpha);
     shape(upArm);
      if(AfficheAngle)text("Axe2",10,10);
     //if(AfficheAngle)text("Axe3",10,10);
      
   translate(0, 0, 50);
   rotateY(PI);
   rotateX(beta);
     shape(loArm);
         if(AfficheAngle)text("Axe3",0,0);
   
      
   translate(0, 0, -50);
   rotateY(PI);
     shape(end);
      if(AfficheAngle)      text("Axe4",0,0);
   translate(0, 0, -50+penPos);
   rotateY(PI);
     shape(pen);
      if(AfficheAngle)      text("pen",0,0);
     //cp5.draw();
  //noLights();
    popMatrix();
}
