PShape base, shoulder, upArm, loArm, end,pen;

float rotX, rotY;
float posX=1, posY=50, posZ=50;
float alpha, beta, gamma;
float F = 50;
float T = 70;
float millisOld, gTime, gSpeed = 4;

float TransX=0;
float TransY=0;
float TransZ=0;
boolean bpen;
boolean benX,benY,benZ;
//float[] Xsphere = new float[99];
//float[] Ysphere = new float[99];
//float[] Zsphere = new float[99];
PVector world = new PVector();
PGraphics p1,p3,p2;

void GUI_ROBOTSetup(){
     //  j2 = createGraphics(width/4, width/4, JAVA2D);
 // p2 = createGraphics(400, height-20, P2D);
  p1 = createGraphics(100, 100, P3D);
  p3 = createGraphics(width-510, height-30, P3D);
}


void DrawAxes(PGraphics pg,int n,int len){
 if (ShowAxes.getState()==true){ 
 if (MoveAxes.getState()==true){ 
     pg.rotateX(-PI/2);
     pg.rotateZ(PI/2);}
   pg.stroke(n,0,0);
   pg.line(0, 0, 0, len, 0, 0);
   pg.stroke(0,n,0);
   pg.line(0, 0, 0, 0, len, 0);
   pg.stroke(0,0,n);
   pg.line(0, 0, 0, 0, 0, len);
 if (MoveAxes.getState()==true){ 
     pg.rotateZ(-PI/2);
     pg.rotateX(PI/2);}
  }
}


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
float  PI= 3.1415926;

void drawRobot(PGraphics pg){
   
    pg.beginDraw();
    pg.clear();

    pg.pushMatrix();
    
         
    writePos();

 
   //smooth();
  
   pg.lights(); 
   pg.directionalLight(51, 102, 126, -1, 0, 0);
    
   pg.noStroke()   ;
 
   pg.fill(255);
   pg.textSize(12);
   pg.text("Frame rate: " + int(frameRate), 10,pg.height-2);
   
   pg.translate((width-510)/2,height/2,100+TransZ);

   pg.rotateX(rotX);
   pg.rotateY(-rotY);
   pg.scale(-2);
   
   
   //for (int i=0; i < Xsphere.length; i++) {
   //  pg.pushMatrix();
   //  pg.translate(-Ysphere[i], -Zsphere[i]-11, -Xsphere[i]);
   //  pg.fill (#D003FF, 25);
   //  pg.sphere (float(i) / 20);
   //  pg.popMatrix();
   // }
    
   pg.fill(#FFE308);  
 //  pg.translate(0,-40,0); 
   pg.shape(base);
   
 DrawAxes(pg,400,100); 
   if(AfficheAngle)pg.text("Axe1",10,10);
   
   pg.translate(0, 4, 0);
   pg.rotateY(gamma);
   pg.shape(shoulder);
   pg.translate(0,0,-10); 
   
   pg.translate(0, 25, 0);
   pg.rotateY(PI);
   pg.rotateX(alpha);
   
   pg.shape(upArm);
 DrawAxes(pg,100,50);   
   if(AfficheAngle)pg.text("Axe2",10,10);
         
   pg.translate(0, 0, 50);
   pg.rotateY(PI);
   pg.rotateX(beta);
   pg.shape(loArm);
   DrawAxes(pg,100,50);   
 
   if(AfficheAngle)pg.text("Axe3",0,0);
       
   pg.translate(0, 0, -50);
   pg.rotateY(PI);
   pg.shape(end);
   DrawAxes(pg,100,50);   
   if(AfficheAngle)      pg.text("Axe4",0,0);
  
   pg.translate(0, 0, -50+penPos);
   pg.rotateY(PI);
   pg.shape(pen);
   DrawAxes(pg,100,50);   
   if(AfficheAngle)      pg.text("pen",0,0);
 //     Axisdraw() ;
   pg.popMatrix();
   //Axisdraw(pg) ;

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
