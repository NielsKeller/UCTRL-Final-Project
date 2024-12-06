#include <Wire.h>
#include <ScopeXY.h>

void setup()
{
  Wire.begin();
}

// Initalize Scope
XYscope XYscope(0x60, 0x61);

void loop() {
  const int timeInImg = 20*1000; //ms
  const int pt = 50;
  const int ptLong = 200;
  int demo = millis()/timeInImg%3;
  static int i = 0;
  
  switch (demo) {
  case 0:
    XYscope.lineSc( 50,   800,    640,   500, ptLong);
    XYscope.lineSc(790,   900,    535,   950, ptLong); //vals off on scope here, manual adjust
    XYscope.lineSc(900,   900,    950,   300, ptLong);
    
    //Legs
    XYscope.lineSc(900,   800,    300,   100, pt);
    XYscope.lineSc(800,   800,    100,   300, pt);
    XYscope.lineSc(800,   700,    300,   100, pt);
    XYscope.lineSc(700,   700,    100,   300, pt);
    
    XYscope.lineSc(700,   600,    300,   300, pt);
    
    XYscope.lineSc(600,   500,    300,   100, pt);
    XYscope.lineSc(500,   500,    100,   300, pt);
    XYscope.lineSc(500,   400,    300,   100, pt);

    //head
    XYscope.lineSc(400,   400,    100,   900, ptLong);
    XYscope.lineSc(400,   300,    900,   700, pt);
    XYscope.lineSc(300,   300,    700,   900, pt);
    XYscope.lineSc(300,   200,    900,   700, pt);
    XYscope.lineSc(200,   50,    700,   650, pt);

    //eyes
    XYscope.lineSc(250,   250,    645,   695, pt);
    XYscope.lineSc(350,   350,    645,   695, pt);
    break;

  case 1:
    XYscope.LJFigure(3.0/2, 7.0/8, i, 0.0051);
    i++;
    break;

  case 2:
    XYscope.LJFigure(6.0/5, 1.0/4, i, 0.0075);
    i++;
    break;

  }




    






  
}
