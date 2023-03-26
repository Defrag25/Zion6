PGraphics j2, p2, p3;

void setup() {
  size(400, 400, P2D);
  j2 = createGraphics(width/4, width/4, JAVA2D);
  p2 = createGraphics(width, height/4-20, P2D);
  p3 = createGraphics(width-20, 3*height/4, P3D);
}
void draw() {
  background(0);
//  drawRect(j2);
  drawRandomColor(p2);
  drawSphere(p3);  
  image(p3, 10, 10);
  image(p2, 0, 3*height/4+20);
 // image(j2, 20, height-width/4-20);
}

void drawRandomColor(PGraphics pg) {
  if (random(100) < 2) {
    pg.beginDraw();
    pg.background(color(random(255), random(255), random(255)));
    pg.endDraw();
  }
}

void drawSphere(PGraphics pg) {
  pg.beginDraw();
  pg.background(128,128);
  pg.translate(pg.width/2,pg.height/2);
  pg.sphere(pg.width*1/4 + pg.width*1/6 * cos( TWO_PI * float(millis() % 4000)/4000 ) );
  pg.endDraw();
}

void drawRect(PGraphics pg) {
  pg.beginDraw();
  pg.clear();
  pg.stroke(128);
  pg.strokeWeight(10);
  pg.fill(128, 0, 0, 128);
  pg.rect(0, 0, pg.width, pg.height);
  int m = int(millis()/10) % pg.width;
  pg.rect(m/2, m/2, pg.width-m, pg.height-m);
  pg.endDraw();
}
