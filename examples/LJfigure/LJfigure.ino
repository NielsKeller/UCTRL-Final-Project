#include <Wire.h>


// Comment from sparkfun -----------------
//This is the I2C Address of the MCP4725, by default (A0 pulled to GND).
//For devices with A0 pulled HIGH, use 0x61
// Comment from sparkfun -----------------

#define MCP4725_ADDR 0x60  
#define MCP4725_ADDR2 0x61   


//Send value to DAC constrained from 0 to 4095 (12-bits)
void dacSend(int address, int value){
  value = constrain(value, 0, 4095);

  Wire.beginTransmission(address);
  Wire.write(64);                     // cmd to update the DAC
  Wire.write(value >> 4);        // the 8 most significant bits...
  Wire.write((value & 15) << 4); // the 4 least significant bits...
  Wire.endTransmission();
}

// Transmit a sin wave to the DAC, call this handeler in loop.
// The phase is in terms of pi
// The index is an incrementing variable
// F is for phase ratio and is multiplied by fdiv
void dacSin(int address, int index, float phase, float F, float fdiv){
  Wire.beginTransmission(address);
  Wire.write(64);                     // cmd to update the DAC

  int sinVal = (sin(index*2*PI*F*fdiv + phase*PI)+1)*4095/2;
  sinVal = constrain(sinVal,0,4095);


  Wire.write(sinVal >> 4);        // the 8 most significant bits...
  Wire.write((sinVal & 15) << 4); // the 4 least significant bits...
  Wire.endTransmission();
}


//Makes Lissajous figure with frequency ratio and phase shift (phase shift is multiplied by 1/(2pi) rads) call in loop with incrementing i
void LJFigure(float ratio, float phase, int index, float fdiv){  
  dacSin(MCP4725_ADDR, index, phase, ratio, fdiv);
  dacSin(MCP4725_ADDR2, index,0,1, fdiv);
}

//Makes moving Lissajous figure with passed in period in seconds with
//frequency ratio. Call in loop with incrementing i
void LJFigureMoving(float ratio, float period, int index, float fdiv){
  LJFigure(ratio, millis()*2/(period*1000), index, fdiv);
}


void setup()
{
  Wire.begin();
}

#define fdiv1 0.03
#define fdiv2 0.01

void loop() {

  static int i = 0;
  LJFigure(6.0/5, 1.0/4, i, 0.01);
  // LJFigure(3.0/2, 7.0/8, i, 0.0051);
  // LJFigureMoving(2/1, 3, i, fdiv1);
  i++;
  
}
