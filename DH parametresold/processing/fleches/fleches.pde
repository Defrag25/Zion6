PVector origin = new PVector();
PVector local = new PVector();
PVector world = new PVector();

PVector i = new PVector();
PVector j = new PVector();
PVector k = new PVector();

float theta = 0.0;
float scalar = 50.0;
float rotvel = 0.01;
String titleformat = "i [ %.2f , %.2f ] , "
  + "k [ %.2f , %.2f ]";

void setup() {
  size(384, 256);
  origin.set(width * 0.5, height * 0.5);
  float offset = min(width, height) * 0.325;
  local.set(offset, 0.0);
  scalar = offset * 0.325;
}

void draw() {
  background(0xffffffff);

  local.rotate(rotvel);

  // Translate the mover from local to
  // world space by adding the origin.
  PVector.add(local, origin, world);

  // Assume camera is looking down at
  // the origin and mover.
  j.set(0.0, 0.0, 1.0);

  // Since the mover is traveling clockwise, its
  // right side is always pointing to the origin.
  PVector.sub(origin, world, i);
  i.normalize();

  // Derive forward (a line tangent to the
  // imaginary circle formed by the rotation)
  // by crossing right with up.
  PVector.cross(i, j, k);
  k.normalize();

  surface.setTitle(String.format(
    titleformat, i.x, i.y, k.x, k.y));

  // Scale and translate directions for display.
  i.mult(scalar);
  k.mult(scalar);
  i.add(world);
  k.add(world);

  // Draw i, j, k.
  strokeWeight(1.5);
  stroke(0xffff0000);
  line(origin.x, origin.y, origin.x + scalar, origin.y);
  line(world.x, world.y, i.x, i.y);
  stroke(0xff00ff00);
  line(origin.x, origin.y, origin.x, origin.y + scalar);
  // Up is not visible in local space.
  stroke(0xff0000ff);
  line(world.x, world.y, k.x, k.y);
  // Forward is not visible in world space.

  // Draw origin and mover.
  strokeWeight(15);
  stroke(0x7f000000);
  point(origin.x, origin.y);
  point(world.x, world.y);

  // Draw endpoints of i, j, k.
  strokeWeight(7.5);
  stroke(0xffff0000);
  point(origin.x + scalar, origin.y);
  point(i.x, i.y);
  stroke(0xff00ff00);
  point(origin.x, origin.y + scalar);
  point(world.x, world.y);
  stroke(0xff0000ff);
  point(k.x, k.y);
  point(origin.x, origin.y);
}
