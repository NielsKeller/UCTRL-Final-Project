#include <Wire.h>


// Comment from sparkfun -----------------
//This is the I2C Address of the MCP4725, by default (A0 pulled to GND).
//For devices with A0 pulled HIGH, use 0x61
// Comment from sparkfun -----------------

#define MCP4725_ADDR 0x60  
#define MCP4725_ADDR2 0x61   

static const int xAd = 0x60;
static const int yAd = 0x61;

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG    

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__SOFTSERIAL

#include <SoftwareSerial.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600


#include <RemoteXY.h>

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 93 bytes
  { 255,3,0,0,0,86,0,19,0,0,0,0,31,1,106,200,1,1,6,0,
  1,28,14,50,50,0,136,31,0,1,28,74,50,50,0,136,31,0,1,28,
  139,50,50,0,135,31,0,129,32,34,41,12,64,24,83,116,97,116,105,99,
  32,49,0,129,32,93,41,12,64,24,83,116,97,116,105,99,32,50,0,129,
  33,158,40,12,64,24,77,111,118,105,110,103,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t Static_1; // =1 if button pressed, else =0
  uint8_t Static_2; // =1 if button pressed, else =0
  uint8_t Moving; // =1 if button pressed, else =0

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

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

//Makes Lissajous figure with frequency ratio and phase shift (phase shift is multiplied by 1/(2pi) rads) call in loop with incrementing i
void LJFigure(float ratio, float phase, int index, float fdiv){
  
  dacSin(MCP4725_ADDR, index, phase, ratio, fdiv);
  dacSin(MCP4725_ADDR2, index,0,1, fdiv);
}

void LJFigureMoving(float ratio, float period, int index, float fdiv){
  LJFigure(ratio, millis()*2/(period*1000), index, fdiv);
}

void setup()
{
  Serial.begin(9600);
  RemoteXY_Init ();
  Wire.begin();
}

#define fdiv1 0.03

void loop() {
  static float ratio = 0;
  static float phase = 0;
  
  RemoteXY_Handler ();

  static int i = 0;

  if (RemoteXY.Static_1 == 1){
    LJFigure(3.0/2, 7.0/8, i, 0.0051);
    i++;
  }

  if (RemoteXY.Static_2 == 1){
    const int pt = 50;
    const int ptLong = 200;

    lineSc( 50,   800,    640,   500, ptLong);
    lineSc(790,   900,    535,   950, ptLong); //vals off on scope here, manual adjust
    lineSc(900,   900,    950,   300, ptLong);
  
    //Legs
    lineSc(900,   800,    300,   100, pt);
    lineSc(800,   800,    100,   300, pt);
    lineSc(800,   700,    300,   100, pt);
    lineSc(700,   700,    100,   300, pt);
  
    lineSc(700,   600,    300,   300, pt);
  
    lineSc(600,   500,    300,   100, pt);
    lineSc(500,   500,    100,   300, pt);
    lineSc(500,   400,    300,   100, pt);

    //head
    lineSc(400,   400,    100,   900, ptLong);
    lineSc(400,   300,    900,   700, pt);
    lineSc(300,   300,    700,   900, pt);
    lineSc(300,   200,    900,   700, pt);
    lineSc(200,   50,    700,   650, pt);

    //eyes
    lineSc(250,   250,    645,   695, pt);
    lineSc(350,   350,    645,   695, pt);
    
  }

  if (RemoteXY.Moving == 1){
    LJFigureMoving(2/1, 3, i, fdiv1);
    i++;
  }
}