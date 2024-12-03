#include <Wire.h>
#define fdiv1 0.03
#define fdiv2 0.01

// Comment from sparkfun -----------------
//This is the I2C Address of the MCP4725, by default (A0 pulled to GND).
//For devices with A0 pulled HIGH, use 0x61
// Comment from sparkfun -----------------

#define MCP4725_ADDR 0x60  
#define MCP4725_ADDR2 0x61   

static const int xAd = 0x60;  
static const int yAd = 0x61; 


//Send value to DAC constrained from 0 to 4095 (12-bits)
void dacSend(int address, int value){
  value = constrain(value, 0, 4095);

  Wire.beginTransmission(address);
  Wire.write(64);                     // cmd to update the DAC
  Wire.write(value >> 4);        // the 8 most significant bits...
  Wire.write((value & 15) << 4); // the 4 least significant bits...
  Wire.endTransmission();
}



void line(int x1, int x2, int y1, int y2, long pts){
  

  for(int i=0; i<pts; i++){
    int Xval = x1+map(i,0,pts,x1,x2);
    int Yval = y1+map(i,0,pts,y1,y2);


    dacSend(xAd, Xval);
    dacSend(yAd, Yval);
  }
}

// Line sclaed to 1000x1000
void lineSc(int x1, int x2, int y1, int y2, long pts){

  x1 = map(x1,0,1000,0,4095);
  x2 = map(x2,0,1000,0,4095);
  y1 = map(y1,0,1000,0,4095);
  y2 = map(y2,0,1000,0,4095);

  int dy = (y2-y1)/pts;
  int dx = (x2-x1)/pts;

  int Xval = x1;
  int yval = y1;

  for(int i=0; i<pts; i++){
    // int Xval = x1+map(i,0,pts,x1,x2);
    // int Yval = y1+map(i,0,pts,y1,y2);


    dacSend(xAd, Xval);
    dacSend(yAd, yval);

    Xval += dx;
    yval += dy;
  }
}



void setup()
{
  Wire.begin();
}


void loop() {

  const int pt = 75;

  lineSc(0,   0,    0,   1000, pt);
  lineSc(0,   1000, 1000,0,    pt);
  lineSc(1000,1000, 0,   1000, pt);
  
}
