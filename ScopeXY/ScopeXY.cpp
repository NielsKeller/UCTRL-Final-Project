#include "Arduino.h"
#include "ScopeXY.h"

//Initalize DACs with I2C adresses these are usually 0x60 and 0x61 respectivly
XYscope::XYscope(int AddressX, int AddressY)
{   
    // Get adresses
    _MCP4725_ADDR = AddressX;
    _MCP4725_ADDR2 = AddressY;
    Wire.begin();
}



// Transmit a sin wave to the DAC, call this handeler in loop.
// The phase is in terms of pi
// The index is an incrementing variable
// F is for phase ratio and is multiplied by fdiv
void XYscope::dacSin(int address, int index, float phase, float F, float fdiv){
  Wire.beginTransmission(address);
  Wire.write(64);                     // cmd to update the DAC

  
  int sinVal = (sin(index*2*PI*F*fdiv + phase*PI)+1)*4095/2;
  sinVal = constrain(sinVal,0,4095);


  Wire.write(sinVal >> 4);        // the 8 most significant bits...
  Wire.write((sinVal & 15) << 4); // the 4 least significant bits...
  Wire.endTransmission();
}



//Makes Lissajous figure with frequency ratio and phase shift 
//(phase shift is multiplied by 1/(2pi) rads) call in loop with incrementing i
void XYscope::LJFigure(float ratio, float phase, int index, float fdiv){  
  dacSin(_MCP4725_ADDR, index, phase, ratio, fdiv);
  dacSin(_MCP4725_ADDR2, index,0,1, fdiv);
}



//Makes moving Lissajous figure with passed in period in seconds with
//frequency ratio. Call in loop with incrementing i
void XYscope::LJFigureMoving(float ratio, float period, int index, float fdiv){
  LJFigure(ratio, millis()*2/(period*1000), index, fdiv);
}


//Send value to DAC constrained from 0 to 4095 (12-bits) (From Adafruit mainly)
void XYscope::dacSend(int address, int value){
  value = constrain(value, 0, 4095);

  Wire.beginTransmission(address);
  Wire.write(64);                     // cmd to update the DAC
  Wire.write(value >> 4);        // the 8 most significant bits...
  Wire.write((value & 15) << 4); // the 4 least significant bits...
  Wire.endTransmission();
}


// Line sclaed to 1000x1000
void XYscope::lineSc(int x1, int x2, int y1, int y2, long pts){

  x1 = map(x1,0,1000,0,4095);
  x2 = map(x2,0,1000,0,4095);
  y1 = map(y1,0,1000,0,4095);
  y2 = map(y2,0,1000,0,4095);

  int dy = (y2-y1)/pts;
  int dx = (x2-x1)/pts;

  int Xval = x1;
  int yval = y1;

  for(int i=0; i<pts; i++){


    dacSend(_MCP4725_ADDR, Xval);
    dacSend(_MCP4725_ADDR2, yval);

    Xval += dx;
    yval += dy;
  }
}