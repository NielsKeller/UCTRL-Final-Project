

#ifndef Morse_h
#define Morse_h
    
    #include "Arduino.h"
    #include <Wire.h>
    #define fdiv1 0.03
    #define fdiv2 0.01

    class XYscope
    {
    public:
        XYscope(int AddressX, int AddressY);

        void dacSin(int address, int index, float phase, float F, float fdiv);
        void LJFigure(float ratio, float phase, int index, float fdiv);
        void LJFigureMoving(float ratio, float period, int index, float fdiv);
        void dacSend(int address, int value);
        void lineSc(int x1, int x2, int y1, int y2, long pts);
  

    private:
        // I2C addresses of ADC
        int _MCP4725_ADDR;
        int _MCP4725_ADDR2;
    };

#endif