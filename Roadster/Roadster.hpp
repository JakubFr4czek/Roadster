#pragma once

Roadster_::Roadster_(void){

    AxisValueMin16Bit = -32768;
    AxisValueMax16Bit = 32767;

    AxisValueMin8Bit = -128;
    AxisValueMax8Bit = 128; 

}

void Roadster_::begin(void){

    Gamepad.begin();

}

void Roadster_::setXAxisRange(int inputValueMin_, int inputValueMax_){

    XAxisInputValueMin = inputValueMin_; 
    XAxisInputValueMax = inputValueMax_;

}

void Roadster_::setYAxisRange(int inputValueMin_, int inputValueMax_){

    YAxisInputValueMin = inputValueMin_; 
    YAxisInputValueMax = inputValueMax_; 

}

void Roadster_::setRXAxisRange(int inputValueMin_, int inputValueMax_){ 

    RXAxisInputValueMin = inputValueMin_; 
    RXAxisInputValueMax = inputValueMax_; 

}

void Roadster_::setRYAxisRange(int inputValueMin_, int inputValueMax_){ 

    RYAxisInputValueMin = inputValueMin_;
    RYAxisInputValueMax = inputValueMax_; 

}

void Roadster_::setZAxisRange(int inputValueMin_, int inputValueMax_){ 

    ZAxisInputValueMin = inputValueMin_; 
    ZAxisInputValueMax = inputValueMax_; 

}

void Roadster_::setRZAxisRange(int inputValueMin_, int inputValueMax_){ 

    RZAxisInputValueMin = inputValueMin_; 
    RZAxisInputValueMax = inputValueMax_; 

}

void Roadster_::setXAxis(int value_){ 

    if(value_ < XAxisInputValueMin) value_ = XAxisInputValueMin; 
    if(value_ > XAxisInputValueMax) value_ = XAxisInputValueMax; 
    Gamepad.xAxis(map(value_, XAxisInputValueMin, XAxisInputValueMax, AxisValueMin16Bit, AxisValueMax16Bit)); this->updateValues(); 

}

void Roadster_::setYAxis(int value_){ 

    if(value_ < YAxisInputValueMin) value_ = YAxisInputValueMin; 
    if(value_ > YAxisInputValueMax) value_ = YAxisInputValueMax; 
    Gamepad.yAxis(map(value_, YAxisInputValueMin, YAxisInputValueMax, AxisValueMin16Bit, AxisValueMax16Bit)); this->updateValues(); 

}

void Roadster_::setRXAxis(int value_){

    if(value_ < RXAxisInputValueMin) value_ = RXAxisInputValueMin; 
    if(value_ > RXAxisInputValueMax) value_ = RXAxisInputValueMax; 
    Gamepad.rxAxis(map(value_, RXAxisInputValueMin, RXAxisInputValueMax, AxisValueMin16Bit, AxisValueMax16Bit)); this->updateValues(); 
    
}

void Roadster_::setRYAxis(int value_){ 

    if(value_ < RYAxisInputValueMin) value_ = RYAxisInputValueMin; 
    if(value_ > RYAxisInputValueMax) value_ = RYAxisInputValueMax; 
    Gamepad.ryAxis(map(value_, RYAxisInputValueMin, RYAxisInputValueMax, AxisValueMin16Bit, AxisValueMax16Bit)); this->updateValues(); 
    
}

void Roadster_::setZAxis(int value_){

    if(value_ < ZAxisInputValueMin) value_ = ZAxisInputValueMin; 
    if(value_ > ZAxisInputValueMax) value_ = ZAxisInputValueMax; 
    Gamepad.zAxis(map(value_, ZAxisInputValueMin, ZAxisInputValueMax, AxisValueMin8Bit, AxisValueMax8Bit)); this->updateValues(); 
    
}

void Roadster_::setRZAxis(int value_){ 

    if(value_ < RZAxisInputValueMin) value_ = RZAxisInputValueMin; 
    if(value_ > RZAxisInputValueMax) value_ = RZAxisInputValueMax; 
    Gamepad.rzAxis(map(value_, RZAxisInputValueMin, RZAxisInputValueMax, AxisValueMin8Bit, AxisValueMax8Bit)); this->updateValues();

}

void Roadster_::pressButton(int buttonId_){ 

    Gamepad.press(buttonId_); 
    this->updateValues(); 

}

void Roadster_::releaseButton(int buttonId_){ 

    Gamepad.release(buttonId_); 
    this->updateValues(); 

}

void Roadster_::releaseAllButtons(){ 
    
    Gamepad.releaseAll(); 

}

void Roadster_::setDPad1(int configuration_){ 

    Gamepad.dPad1(configuration_); 
    
}

void Roadster_::setDPad2(int configuration_){ 
    
    Gamepad.dPad2(configuration_); 
    
}

void Roadster_::updateValues(){ 
    
    Gamepad.write(); 
    
}

Roadster_ Roadster;
