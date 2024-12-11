# CMPE3815 Final Project: X-Y Oscilloscope Drawer

CMPE 3815, Microcontroller Systems\
Niels Keller\
Samuel Starzec

## Overview

The goal of this project was to have a microcontroller use an oscilloscope's X-Y mode to display Lissajous figures. The first stretch goal was to have the oscilloscope display more geometric shapes. The second stretch goal was design and fabricate a functioning PCB. Both stretch goals were met.

## Important Files

* Circuit schematic &rarr; Images/Circuit.png
* PCB files (KiCad) &rarr; PCB
* Arduino Library &rarr; ScopeXY.zip
* Final Reports &rarr; Reports

## Hardware Components

* Arduino UNO
* MCP4725 DAC (x2)
* PCB
* Bluetooth JDY-16 BLE Module

## Basic Documentation

    XYscope(int AddressX, int AddressY);

Constructor of the XYscope class.<br>
Parameters:

* int AddressX &rarr; I2C address of X DAC
* int AddressY &rarr; I2C address of Y DAC

##

    void dacSend(int address, int value);

Send output value to the DAC.<br>
Parameters:

* int address &rarr; I2C address of DAC
* int value &rarr; 0 - 4096 value to set output to

##

    void LJFigure(float ratio, float phase, int index, float fdiv);

Display Lissajous curve.<br>
Parameters:

* float ratio &rarr; Ratio between frequencies
* float phase &rarr; Phase offset ($\pi$ * radians)
* int index &rarr; Index on the sinusoid. Controls the input value
* float fdiv &rarr; Speed modifier $\approx$ 0.01 . Should be roughly the same for most figures for each scope.

##

    void LJFigureMoving(float ratio, float period, int index, float fdiv);

Display moving Lissajous curve.<br>
Parameters:

* float ratio &rarr; Ratio between frequencies
* float period &rarr; Period in seconds
* int index &rarr; Index on the sinusoid. Controls the input value
* float fdiv &rarr; Speed modifier: Should be roughly the same for most figures for each scope.

##

    void lineSc(int x1, int x2, int y1, int y2, long pts);

Maps lines from a 1000x1000 plane to the osiloscope and displays them.<br>
Parameters:

* int x1 &rarr; First x point
* int x2 &rarr; Second x point
* int y1 &rarr; First y point
* int y2 &rarr; Second y point
* long pts &rarr; Total number of points to plot

## Example Images

Unfortunately only display properly on GitHub.<br>
https://github.com/NielsKeller/ScopeXY 


![LJ figure](https://github.com/NielsKeller/ScopeXY/blob/main/Images/CoverDemo.jpeg)

![Geo Dog](https://github.com/NielsKeller/ScopeXY/blob/main/Images/Geodog.jpeg)

![Circuit Design](https://github.com/NielsKeller/ScopeXY/blob/main/Images/Circuit.png)

