#pragma once

#include "HID-Project.h" // https://github.com/NicoHood/HID/wiki/Gamepad-API

class Roadster_ {

  private:
  
    int AxisValueMin16Bit = -32768;
    int AxisValueMax16Bit = 32767;
    
    int AxisValueMin8Bit = -128;
    int AxisValueMax8Bit = 128;

    //16 bit Axes below
    int XAxisInputValueMin;
    int XAxisInputValueMax;

    int YAxisInputValueMin;
    int YAxisInputValueMax;

    int RXAxisInputValueMin;
    int RXAxisInputValueMax;

    int RYAxisInputValueMin;
    int RYAxisInputValueMax;

    //8 bit Axes below
    int ZAxisInputValueMin;
    int ZAxisInputValueMax;

    int RZAxisInputValueMin;
    int RZAxisInputValueMax;

  public:

    inline Roadster_(void);
    inline void begin(void); //releases all buttons
   
    inline void setXAxisRange(int inputValueMin_, int inputValueMax_);
    inline void setYAxisRange(int inputValueMin_, int inputValueMax_);
    inline void setRXAxisRange(int inputValueMin_, int inputValueMax_);
    inline void setRYAxisRange(int inputValueMin_, int inputValueMax_);
    inline void setZAxisRange(int inputValueMin_, int inputValueMax_);
    inline void setRZAxisRange(int inputValueMin_, int inputValueMax_);

    inline void setXAxis(int value_);
    inline void setYAxis(int value_);
    inline void setRXAxis(int value_);
      inline void setRYAxis(int value_);
      inline void setZAxis(int value_);
    inline void setRZAxis(int value_);
    inline void pressButton(int buttonId_);
    inline void releaseButton(int buttonId_);
    inline void releaseAllButtons();

    inline void setDPad1(int configuration_);
    inline void setDPad2(int configuration_);

    inline void updateValues(void);
    
};

extern Roadster_ Roadster;

#include "Roadster.hpp"
