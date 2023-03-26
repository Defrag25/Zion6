import peasy.*;

PeasyCam cam;

void Axissetup() {
  //size(500,500,P3D);
  cam = new PeasyCam(this, 500);
  cam.setMinimumDistance(100);
  cam.setMaximumDistance(1000);


}
void Axisdraw(PGraphics pg) { 

//  color blue = color (0,0,255);
//  color yellow = color (255,255,0);

//  rotateX(-.001);
//  rotateY(-.001);
//  background(255);
//  translate(0,0,0);


  pushMatrix();
    fill(200);
  pg.rect(0,0,125,125);

  // asse x
  pg.stroke(0,100,0); 
  pg.line(0, 0, 0, 150, 0, 0);
  pg.fill(0,100,0);
  pg.text("X Axis",140,-5,0);

  pg.stroke(200);
  pg.line(0, 0, 10, 100, 0, 10);
  pg.line(0, 0, 20, 100, 0, 20);
  pg.line(0, 0, 30, 100, 0, 30);
  pg.line(0, 0, 40, 100, 0, 40);
  pg.line(0, 0, 50, 100, 0, 50);


  pg.stroke(255,0,0);
  pg.line(0, 0, 0, 0, 150, 0);

  pg.pushMatrix();
  pg.rotate(-HALF_PI);
  pg.fill(255,0,0);
  pg.text("Y Axis",-160,-5,0);
  pg.popMatrix();



  pg.stroke(200);
  pg.line(0, 0, 10, 0, 100, 10);
  pg.line(0, 0, 20, 0, 100, 20);
  pg.line(0, 0, 30, 0, 100, 30);
  pg.line(0, 0, 40, 0, 100, 40);
  pg.line(0, 0, 50, 0, 100, 50);





pg.stroke(0,0,255);
pg.line(0, 0, 0, 0, 0, 150);
pg.pushMatrix();
  pg.rotateY(-HALF_PI);
  pg.fill(0,0,255);
  pg.text("Z Axis",140,-5,0);
  pg.popMatrix();



pg.stroke(200);
pg.line(10, 0, 0, 10, 0, 100);
pg.line(20, 0, 0, 20, 0, 100);
pg.line(30, 0, 0, 30, 0, 100);
pg.line(40, 0, 0, 40, 0, 100);
pg.line(50, 0, 0, 50, 0, 100);
pg.line(0, 10, 0, 0, 10, 100);
pg.line(0, 20, 0, 0, 20, 100);
pg.line(0, 30, 0, 0, 30, 100);
pg.line(0, 40, 0, 0, 40, 100);
pg.line(0, 50, 0, 0, 50, 100);


//translate(10, 10, 10);
//noStroke();
//lights();
//fill(0,255,0);
//sphere(5);


//translate(25, 10, 50);
//noStroke();
//lights();
//fill(blue);
//sphere(5);

//translate(25, 30, 10);
//noStroke();
//lights();
//fill(255,0,0);
//sphere(5);

//translate(75, 10, 50);
//noStroke();
//lights();
//fill(yellow);
////sphere(5);

//translate(0,0,50);
popMatrix();


}
