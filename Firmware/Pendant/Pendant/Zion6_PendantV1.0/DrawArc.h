
void arcloop() ;
int fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour);
void arcloop() {

  int w = 8;
  int rx = 160;
  int ry = 100;
  
  for (int n = 0; n < 5; n++) {
    fillArc(160, 100, 300, 40, rx-n*w, ry-n*w, w, 31-n*6);
  }

  delay(500);
}
