#include <Wire.h>
#include <ScopeXY.h>


XYscope XYscope(0x60, 0x61);

void setup() {
  // put your setup code here, to run once:

}

void loop() {

  static int i = 0;
  // XYscope.LJFigure(6.0/5, 1.0/4, i, 0.01);
  // XYscope.LJFigure(3.0/2, 7.0/8, i, 0.0051);
  XYscope.LJFigureMoving(2/1, 3, i, fdiv1);
  i++;
}
