PShape base, shoulder, upArm, loArm, end,pen;

float rotX, rotY;
float posX=1, posY=50, posZ=50;
float RotAxe3, RotAxe2, RotAxe1;
float F = 50;
float T = 70;
float millisOld, gTime, gSpeed = 4;
float TranslateX=0,TranslateY=0;
float TransX=0;
float TransY=0;
float TransZ=0;
boolean bpen;
boolean benX,benY,benZ;
PVector world = new PVector();
PGraphics p1,p3,p2;

void GUI_ROBOTSetup(){
     //  j2 = createGraphics(width/4, width/4, JAVA2D);
 // p2 = createGraphics(400, height-20, P2D);
  p1 = createGraphics(100, 100, P3D);
  p3 = createGraphics(width-510, height-30, P3D);
}


void DrawAxes(PGraphics pg,int n,int len,boolean grid){
 if (ShowAxes.getState()==true){ 
 //if (ProcessIK.getState()==true){ 
 //    pg.rotateX(-PI/2);
 //    pg.rotateZ(PI/2);}
   pg.stroke(n,0,0);
   pg.line(0, 0, 0, len, 0, 0);   
   pg.stroke(0,n,0);
   pg.line(0, 0, 0, 0, len, 0);
   pg.stroke(0,0,n);
   pg.line(0, 0, 0, 0, 0, len);
 }   if (grid){
 
   if(ShowGrid.getState()==true) {pg.stroke(30,30,30);
   for(int x=-len/20; x<=len/20 ;x++){
    pg.line(x*10, -len/2, 0, x*10, len/2, 0);
    pg.line(-len/2, x*10, 0, len/2, x*10, 0);
   }
  }
   
 //if (ProcessIK.getState()==true){ 
 //    pg.rotateZ(-PI/2);
 //    pg.rotateX(PI/2);}
}
}


void initRobot(){
  base = loadShape("Zr5.obj");
  shoulder = loadShape("Zr1.obj");
  upArm = loadShape("Zr2.obj");
  loArm = loadShape("Zr3.obj");
  end = loadShape("Zr4.obj");
  pen = loadShape("Zpen.obj");
    
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

   
   pg.translate((TranslateX+width-510)/2,TranslateY+height/2,100+TransZ);
 
   pg.rotateX(rotX);
   pg.rotateZ(-rotY);
   pg.scale(-2);
    DrawAxes(pg,800,400,true);
   
   
 
    
   pg.fill(#FFE308);  
 //  pg.translate(0,-40,0);
//////////////////////////////////////////////////////////////////////////// AXE1
     pg.shape(base);
     DrawAxes(pg,400,100,false); 
     if(AfficheAngle)pg.text("Axe1",10,10);
   
   pg.translate(0, 0, 25);
   pg.rotateZ(RotAxe1); //Y
//////////////////////////////////////////////////////////////////////////// AXE2
      pg.shape(shoulder);
      DrawAxes(pg,100,50,false);   
      if(AfficheAngle)pg.text("Axe2",10,10);
 
   pg.translate(0,0,29); 
//   pg.translate(0, 25, 0);
//   pg.rotateZ(PI);
   pg.rotateY(RotAxe2);
//////////////////////////////////////////////////////////////////////////// AXE3   
      pg.shape(upArm);
      DrawAxes(pg,100,50,false);   
      if(AfficheAngle)pg.text("Axe2",10,10);
    
   pg.translate(0, 0, 50);
   pg.rotateY(RotAxe3);
   //pg.rotateX(RotAxe2);
//////////////////////////////////////////////////////////////////////////// AXE4   
      pg.shape(loArm);
      DrawAxes(pg,100,50,false);   
      if(AfficheAngle)pg.text("Axe3",0,0);
    
   pg.translate(0, 0, -50);
   pg.rotateY(PI);
//////////////////////////////////////////////////////////////////////////// AXE5   
      pg.shape(end);
      DrawAxes(pg,100,50,false);   
      if(AfficheAngle)      pg.text("Axe4",0,0);
 
   pg.translate(0, 0, -50+penPos);
   pg.rotateY(0);
//////////////////////////////////////////////////////////////////////////// AXE6
   if (ShowPen.getState()==true)
   {
     pg.shape(pen);
     DrawAxes(pg,100,50,false);   
     if(AfficheAngle)      pg.text("pen",0,0);
     
   }
   
   pg.popMatrix();

   pg.endDraw();
}



void IK(){
  float X = posX;
  float Y = posY;
  float Z = posZ;
 if (ProcessIK.getState()==true){
  float L = sqrt(Y*Y+X*X);
  float dia = sqrt(Z*Z+L*L);

  RotAxe3 = PI/2-(atan2(L, Z)+acos((T*T-F*F-dia*dia)/(-2*F*dia)));
  RotAxe2 = -PI+acos((dia*dia-T*T-F*F)/(-2*F*T));
  RotAxe1 = atan2(Y, X);
 }
 else
 {
   RotAxe1 = SliderAxe1.getValue()*PI/180;
   RotAxe2 = 1*(SliderAxe2.getValue()*PI/180);
   RotAxe3 = -PI/2+SliderAxe3.getValue()*PI/180;
 }
  
}

//void setTime(){
//  gTime += ((float)millis()/1000 - millisOld)*(gSpeed/4);
//  if(gTime >= 4)  gTime = 0;  
//  millisOld = (float)millis()/1000;
//}

void writePos(){
  IK();
  //setTime();
  //posX = sin(gTime*PI/2)*70;
  //posZ = sin(gTime*PI)*10;
  //posX=SliderAxe1.getValue();
}
