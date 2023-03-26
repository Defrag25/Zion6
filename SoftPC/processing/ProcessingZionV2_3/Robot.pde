PShape base, shoulder, upArm, loArm, end,pen,Axe4,pince;

float rotX, rotY;
float posX=1, posY=50, posZ=50;
float RotAxe1, RotAxe2, RotAxe3, RotAxe4, RotAxe5, RotAxe6;
float F = 50;
float T = 80;
float millisOld, gTime, gSpeed = 4;
float TranslateX=0,TranslateY=0;
float TransX=0;
float TransY=0;
float TransZ=0;
boolean bpen;
boolean benX,benY,benZ;
PVector world = new PVector();
PVector trajectory = new PVector();
float[] TrajX = new float[100];
float[] TrajY = new float[100];
float[] TrajZ = new float[100];
float LastX=0,LastY=0,LastZ=0;
int TrajPt=0;
PGraphics p1,p3,p2;
float PointX,PointY,PointZ;
void GUI_ROBOTSetup(){
     //  j2 = createGraphics(width/4, width/4, JAVA2D);
 // p2 = createGraphics(400, height-20, P2D);
  p1 = createGraphics(100, 100, P3D);
  p3 = createGraphics(width-510, height-100, P3D);}



void DrawTraj(PGraphics pg){
   pg.pushMatrix();
   pg.lights(); 
   pg.directionalLight(51, 102, 126, -1, 0, 0);
   pg.fill(255);
   pg.textSize(12);

   
   pg.translate((TranslateX+pg.width)/2,TranslateY+pg.height/2,100+TransZ);
 
   pg.rotateX(rotX);
   pg.rotateZ(-rotY);
   pg.scale(-1);;

   pg.fill(400);
   pg.stroke(100);
for (int i=0; i < TrajX.length; i++) {
   pg.pushMatrix();
     pg.translate(TrajX[i], TrajY[i], TrajZ[i]);
     pg.fill (0, 25);
     pg.stroke(100);
     pg.sphere (5);
    // print ("pop");
   pg.popMatrix();
    }
   pg.popMatrix();


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
 
   if(ShowGridX.getState()==true) {//pg.stroke(30,30,30);
   for(int x=-len/20; x<=len/20 ;x++)
    {
      int  j= x%5; if (j==0){pg.stroke(40,0,0);}else{pg.stroke(30,0,0);}
      j= x%10; if (j==0){pg.stroke(80,0,0);}
      pg.line(x*10, -len/2, 0, x*10, len/2, 0);
      pg.line(-len/2, x*10, 0, len/2, x*10, 0);
    }}
    
   if(ShowGridY.getState()==true) {//pg.stroke(30,30,30);
    for(int y=-len/20; y<=len/20 ;y++)
    {
      int  i= y%5; if (i==0){pg.stroke(0,40,0);}else{pg.stroke(0,40,0);}
      i= y%10; if (i==0){pg.stroke(0,80,0);}
      pg.line(0,y*10, -len/2, 0, y*10, len/2);
      pg.line(0,-len/2, y*10, 0, len/2, y*10);
    }
   }
   if(ShowGridZ.getState()==true) {//pg.stroke(30,30,30);

     for(int z=-len/20; z<=len/20 ;z++)
    {
      int  i= z%5; if (i==0){pg.stroke(0,0,40);}else{pg.stroke(0,0,40);}
      i= z%10; if (i==0){pg.stroke(0,0,80);}
      pg.line(z*10,0, -len/2,  z*10,0, len/2);
      pg.line(-len/2,0, z*10,  len/2,0, z*10);
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
  loArm = loadShape("Zr3_1.obj");
  Axe4 = loadShape("Zr3_2.obj");
  end = loadShape("Zr4.obj");
  pen = loadShape("Zpen.obj");
  pince = loadShape("pince.obj");
    
  shoulder.disableStyle();
  upArm.disableStyle();
  loArm.disableStyle();
  vueALL();
  //rotX=PI/3;
  //rotY=-PI/2;
  //TransZ=-400;
}
//float  PI= 3.1415926;

void drawSheet(PGraphics pg){
   pg.pushMatrix();
   pg.lights(); 
   pg.directionalLight(51, 102, 126, -1, 0, 0);
      pg.fill(255);
   pg.textSize(12);

   
   pg.translate((TranslateX+pg.width)/2,TranslateY+pg.height/2,100+TransZ);
 
   pg.rotateX(rotX);
   pg.rotateZ(-rotY);
   pg.scale(-1);;

   pg.translate(50, 40, 0);
   pg.rotateZ(45);
    DrawAxes(pg,1000,50,false);
   pg.fill(400);
   pg.stroke(100);
   pg.text("Sheet", 0,0);
   pg.rect(0,0,21,29.7);
   pg.popMatrix();


}

void drawRobot(PGraphics pg){
  int OffsetX = 500;
  int OffsetY = 35;
    rect(OffsetX-2, OffsetY-2, p3.width+4,p3.height+4);
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

   
   pg.translate((TranslateX+pg.width)/2,TranslateY+pg.height/2,100+TransZ);
 
   pg.rotateX(rotX);
   pg.rotateZ(-rotY);
   pg.scale(-1);;
    DrawAxes(pg,800,400,true);
   
    // pushMatrix();
    //  for (int i=0; i < TrajX.length; i++) {
    // translate(TrajX[i], TrajY[i], TrajZ[i]);
    // fill (#D003FF, 25);
    // sphere (10);
    //}
    // popMatrix();

   
 
    
   pg.fill(#FFE308);  
 //  pg.translate(0,-40,0);
//////////////////////////////////////////////////////////////////////////// AXE1
     if (ShowRobot.getState()==true)  {pg.shape(base);     DrawAxes(pg,400,100,false);     if(AfficheAngle)pg.text("Axe1",10,10);}
   
   pg.translate(0, 0, 25);
   pg.rotateZ(RotAxe1); //Y
//////////////////////////////////////////////////////////////////////////// AXE2
if (ShowRobot.getState()==true)  {      pg.shape(shoulder);      DrawAxes(pg,100,50,false);      if(AfficheAngle)pg.text("Axe2",10,10);}
 
   pg.translate(0,0,29); 
//   pg.translate(0, 25, 0);
//   pg.rotateZ(PI);
   pg.rotateY(RotAxe2);
//////////////////////////////////////////////////////////////////////////// AXE3   
if (ShowRobot.getState()==true)  {      pg.shape(upArm);      DrawAxes(pg,100,50,false);    if(AfficheAngle)pg.text("Axe2",10,10);}
    
   pg.translate(0, 0, 50);
   pg.rotateY(RotAxe3-PI/2);
if (ShowRobot.getState()==true)  {      pg.shape(loArm);}
   pg.rotateZ(RotAxe4-PI/2);
   
   //pg.rotateX(RotAxe2);
//////////////////////////////////////////////////////////////////////////// AXE4   
if (ShowRobot.getState()==true)  { pg.shape(Axe4);    DrawAxes(pg,100,50,false);    if(AfficheAngle)pg.text("Axe3",0,0);}
    
   pg.translate(0, 0, -50);
   pg.rotateY(PI);
   pg.rotateX(RotAxe5);
//////////////////////////////////////////////////////////////////////////// AXE5   
      if (ShowRobot.getState()==true)  {pg.shape(end);      DrawAxes(pg,100,50,false);      if(AfficheAngle)      pg.text("Axe4",0,0);}
 
   pg.translate(0, 0, 12);
   pg.rotateZ(RotAxe6);
   
   if (ShowRobot.getState()==true)  {     pg.shape(pince);        DrawAxes(pg,100,50,false);}   
   pg.translate(0, -5, 16);
   pg.rotateX(PI/2);
   pg.translate(0, 0, 0);
   pg.translate(0, 0, penPos);
   pg.rotateY(0);
//////////////////////////////////////////////////////////////////////////// AXE6
   if (ShowPen.getState()==true)
   {
     pg.shape(pen);
     DrawAxes(pg,100,50,false);   
     if(AfficheAngle)      pg.text("pen",0,0);
     
   }
//   float lastX,LastY,LastZ;
   if((PtX.getValue()!=LastX)||(PtY.getValue()!=LastY)||(PtZ.getValue()!=LastZ)){
    TrajX[TrajPt] = PtX.getValue();
    TrajY[TrajPt] = PtY.getValue();
    TrajZ[TrajPt] = PtZ.getValue();
    LastX=PtX.getValue();
    LastY=PtY.getValue();
    LastZ=PtZ.getValue();
    TrajPt=TrajPt%TrajX.length;
   }
   pg.popMatrix();
   if (ShowSheet.getState()==true)    {  drawSheet(pg); }
   if (ShowTraj.getState()==true)    {  DrawTraj(pg);  }
pg.endDraw();
   image(p3, OffsetX, OffsetY);
}



void IK(){
  float X = PtX.getValue();
  float Y = PtY.getValue();
  float Z = -PtZ.getValue()+25+29; // parceque la base du plan X commence à la hauteur de la base + hauteur axe 1
 if (ProcessIK.getState()==true){
  float L = sqrt(Y*Y+X*X);
  float dia = sqrt(Z*Z+L*L);
  float AngleX,AngleY,AngleZ;
  AngleX = PI-(atan2(L, Z)+acos((T*T-F*F-dia*dia)/(-2*F*dia)));
  AngleY = PI/2-  acos((dia*dia-T*T-F*F)/(-2*F*T));
  AngleZ = atan2(Y, X);
//  println("["+posX+";"+posY+";"+posZ+"] "+ AngleX +"  "+AngleY+ "  "+ AngleZ);
// }
// else
// {
   //if (ProcessIK.getState()==true){ 
     if(!configured){
     SliderAxe1.setValue(AngleX*180/PI);
 SliderAxe2.setValue(AngleY*180/PI);
 SliderAxe3.setValue(AngleZ*180/PI);
 RotAxe1=AngleZ;
 RotAxe2=AngleX;
 RotAxe3=AngleY;
     }
   //RotAxe1 = SliderAxe1.getValue()*PI/180;
   //RotAxe2 = SliderAxe2.getValue()*PI/180;
   //RotAxe3 = SliderAxe3.getValue()*PI/180;
   RotAxe4 = SliderAxe4.getValue()*PI/180;
   RotAxe5 = SliderAxe5.getValue()*PI/180;
   RotAxe6 = SliderAxe6.getValue()*PI/180;   
   //println("IK Axes["+RotAxe1*180/PI
   //           +";"+RotAxe2*180/PI
   //           +";"+RotAxe3*180/PI
   //           +";"+RotAxe4*180/PI
   //           +";"+RotAxe5*180/PI
   //           +";"+RotAxe6*180/PI
   //           +"] - ["+PointX
   //           +";"+PointY
   //           +";"+PointZ
   //           +"]");
              
 //}
 }
 else
 {
  SliderAxe1.setValue(RotAxe1*180/PI);
  SliderAxe2.setValue(RotAxe2*180/PI);
  SliderAxe3.setValue(RotAxe3*180/PI);
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
