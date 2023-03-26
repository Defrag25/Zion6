
import controlP5.*;
ControlP5 cp5;
boolean shiftOn=false;
float penPos=0;
int touche;

String AppSketchPath, AppDataPath;






void setup(){
  size(1200, 800, P3D);
  AppSketchPath = sketchPath();
  AppDataPath  = dataPath(""); 
  println (AppSketchPath+ "  " + AppDataPath);
  

    zguiSetup();
    initRobot();
     getGraphics();
       guiSetup();
        GUI_CONNECT();
        GUI_ROBOTSetup();
        
          GUI_PROG();
         
}

void draw(){ 
  stroke(10);
     background(100);//32);
 //drawRect(j2);
//  drawRandomColor(p2);
 // drawSphere(p3);  
 //    cp5.draw();


  //drawRobot(p1);
      // End of 3D start of 2D HUD



  //image(p1, 500, 20);
//  background(0);//32);
  //image(p2, 0, 0);
  //image(j2, 20, height-width/4-20);
  //background(1000);//32);
  fill(0);
  rect(500-2, 20-2, p3.width+4,p3.height+4);
//  fill(0);
//  rect(0, 0, 400,height-20);
   //image(p3, 500, 20);
   
   drawRobot(p3);
  image(p3, 500, 20);
  
}

void mouseDragged(){
    
    if (mousePressed && (mouseButton == RIGHT)) 
      {
        if(TransZ>0 ||TransZ<0){
        TranslateX=TranslateX+(mouseX - pmouseX) * -1*TransZ/100;  
        TranslateY=TranslateY+(mouseY - pmouseY) * -1*TransZ/100;
        }
        else{
        TranslateX=TranslateX+(mouseX - pmouseX) * 1;  
        TranslateY=TranslateY+(mouseY - pmouseY) * 1;

        }
        
      }
      
    else {
    if(mouseX>500){rotY -= (mouseX - pmouseX) * 0.01;
    rotX -= (mouseY - pmouseY) * 0.01;
    
     } 
    }
}



void mouseWheel(MouseEvent e){
  
    
 if(shiftOn==false) 
  {
    TransZ = TransZ-25*e.getCount();
    if(TransZ>500) TransZ=500;
    if(TransZ<-1000) TransZ=-1000;
 //   println(TransZ);
  }

 else posY=posY+25*e.getCount();
 if(bpen==true) penPos = penPos-5*e.getCount();
 }

void keyPressed() {
  if (keyCode == SHIFT) { shiftOn = true; }else {shiftOn = false;}
  if (keyCode == CONTROL) { bpen = true; }else {bpen = false;}
}

public void controlEvent(ControlEvent theEvent) {
  if (theEvent.isTab()) {
     //println("got an event from tab : "+theEvent.getTab().getName()+" with id "+theEvent.getTab().getId());
     return;
   }
  switch(theEvent.getController().getName()) {
    case "Prog":
    OpenDialog();
        //importTextFile();
 
      break;
  
  
    case "connectButton":
      if(selected) {
        try {
      
            port = new Serial(this, Serial.list()[portNum], 115200);
         
            //timerStatus.start();
            ClearOutput();
            output(11,  "Connected to " + Serial.list()[portNum]);            
            GUI_refresh();
            delay(250);

            cp5.getTab("default").bringToFront();
         
      
        } catch(Exception e) {
          output(11,  "Unable to connect to " + Serial.list()[portNum]);
          //output(11,  e.toString());
       
      
          //timerStatus.stop();
          GUI_refresh();
        }
      } else {
        output(11,  "Select appropriate COM port");
      }
      break;
    case "disconnectButton":
 
        output(11,  "Disconnected from " + Serial.list()[portNum]);
      
        port.stop();
      ;
        //ClearOutput();
        GUI_refresh();
    
      break;
   
  }
}

void ClearOutput(){
 outputArea.clear();
}
 
 void serialEvent(Serial myPort) {
 //println("received qqchose --:)  ");
  try {
   String val = myPort.readStringUntil('\n');
   if (val!=null)
    {
     val=trim(val);  
     if(val.indexOf('\n')>0) { val.substring(0,val.indexOf('\n'));      val=trim(val);}
     if(val.indexOf('\r')>0) { val.substring(0,val.indexOf('\r'));      val=trim(val);}
     if (val!=null  && val.indexOf(">")<=1 && val.length()<=2) 
      {
       if ( ShowAll.getState() == false ) { output(1,"Ok>"); print (">");}
     //  Delta.HandShake=true; Delta.Waiting=false; 
     //  Delta.Message=val;
       return;       
      }
     else
      {
       if ( ShowCMD.getState() == false ) 
        {
         if (val!=null  && val.indexOf("cartesian")>=0) 
          { output(1, decode(val)); }
         else { output(1, val); }
         //print (val);
        }
     //  Delta.HandShake=true; Delta.Waiting=false; 
     //  Delta.Message=val;
      }
     if (val!=null  && val.indexOf("cartesian")>=0) 
      {
        decode(val);
      }
      

     if (val.charAt(0)=='<'){ // '?' demande position
       //val.indexOf(">")
       String val2 = val.substring(val.indexOf("<"),val.indexOf(">")+1);
       //String val2 = val.substring(val.indexOf("<")+1,val.indexOf(">"));
       //print(val2);
     //  Delta.Message=val2;
     //  Delta.decodeStatus(val2);
     //  Delta.HandShake=true;
     //  Delta.Waiting=false;
        }

      
    }  
//     output(1,val);
/*     //statusoutput(8,Delta.Message);
     if ( (val!=null) && (ShowAll.getState() )) {
     println (val);
     statusoutput(8,Delta.Message);
     }

          
    //String val = myPort.readString();
    if (val!=null)
     {
       String[] messages = split(trim(val),' ');
       //statusoutput(8,Delta.Message);
      if(val.charAt(0)=='<'){ // '?' demande position
       //val.indexOf(">")
       String val2 = val.substring(val.indexOf("<"),val.indexOf(">")+1);
       //String val2 = val.substring(val.indexOf("<")+1,val.indexOf(">"));
       //print(val2);
       Delta.Message=val2;
       Delta.decodeStatus(val2);
       statusoutput(8,val2);
       Delta.HandShake=true;
       Delta.Waiting=false;
        }
        //println(val);
        Delta.HandShake=true;
        Delta.Waiting=false;
//      else

          if( (messages!=null&&messages.length==1)&&(val.indexOf(">")==0)) {
             Delta.HandShake=true;             
             return;
          }

     
     }    
 */
 
    }
   catch(RuntimeException e) {
   println ("***********************");
   println ("** Exception!1 (EMJ) **");    
   println ("***********************");
   e.printStackTrace();
  }
}

String decode( String s){
  // Offz=-179.41 delta x=37.10 y=37.10 z=37.10
  
 try{
  String vX = s.substring(s.indexOf("cartesian x=")+12,s.indexOf("y=")-1); 
  String vY = s.substring(s.indexOf("y=")+2,s.indexOf("z=")-1); 
  String vZ = s.substring(s.indexOf("z=")+2,s.indexOf("Offz=")-1); 
  String s2 = s.substring(s.indexOf("Offz="),s.length());
//  Delta.XPosActual = float(vX);
 // Delta.YPosActual = float(vY);
 // Delta.ZPosActual = float(vZ);
  print ("cart["+vX+";"+vY+";"+vZ+"]");
  //println();
  //println ("#"+s2+"#");  
  String oZ=""; if(s2.indexOf("Offz=")>=0)    { oZ = s2.substring(s2.indexOf("Offz=")   +5,s2.indexOf("delta x=")-1);}  //println("#"+oZ+"#");
  print (" offZ["+oZ+"]");
  String mX=""; if(s2.indexOf("delta x=")>=0) { mX = s2.substring(s2.indexOf("delta x=")+8,s2.indexOf("y=")-1);}        //println("#"+mX+"#");
  String mY=""; if(s2.indexOf("y=")>=0)       { mY = s2.substring(s2.indexOf("y=")      +2,s2.indexOf(" z="));}         //println("#"+mY+"#");
  String mZ=""; if(s2.indexOf(" z=")>=0)      { mZ = s2.substring(s2.indexOf(" z=")     +3);}                           //println("#"+mZ+"#");
  println(" mot["+mX+";"+mY+";"+mZ+"]");
 // VIEWCoord(float(vX),float(vY) , float(vZ), float(oZ) , float(mX) , float(mY) , float(mZ) );
   return("["+vX+";"+vY+";"+vZ+"]"+oZ);
     }
   catch(RuntimeException e) {
   println ("****************************");
   println ("** Exception!decode (EMJ) **");
   println ("****************************");
   e.printStackTrace();
  }
 return("decode ERROR"); 
}
