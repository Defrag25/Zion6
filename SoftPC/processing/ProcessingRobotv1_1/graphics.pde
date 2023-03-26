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
