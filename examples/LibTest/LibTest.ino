#include <Wire.h>
#include <ScopeXY.h>

// Initalize Scope
XYscope XYscope(0x60, 0x61);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  if (false){
    static int i = 0;
    // XYscope.LJFigure(6.0/5, 1.0/4, i, 0.01);
    // XYscope.LJFigure(3.0/2, 7.0/8, i, 0.0051);
    XYscope.LJFigureMoving(2/1, 3, i, fdiv1);
    i++;
  }
  else{
    int pt = 100;
    XYscope.lineSc(0,   0,    0,   1000, pt);
    XYscope.lineSc(0,   1000, 1000,0,    pt);
    XYscope.lineSc(1000,1000, 0,   1000, pt);
  }

}
