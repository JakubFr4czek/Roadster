//Written by Jakub Frączek 
//contact: kuba.fr.20@gmail.com

#include <Joystick.h> //https://github.com/MHeironimus/ArduinoJoystickLibrary
#include <Encoder.h> //https://github.com/PaulStoffregen/Encoder

/**
 * Poniższe instrukcje pozwalają na włączenie lub wyłączenie
 * poszczególnych komponentów w całym kodzie
 * 0 - wyłączony
 * 1 - włączony
 */

#define GAS_ENABLED 1
#define CLUTCH_ENABLED 1
#define BRAKE_ENABLED 1
#define STEERING_ENABLED 1
#define GEARBOX_ENABLED 1
#define GEARBOX_CHANGE_ENABLED 1
#define WIPERS_ENABLED 1
#define LIGHTS_ENABLED 1
#define INDICATORS_ENABLED 1
#define ENGINE_ENABLED 1

void setInputPin(short pin[], int aSize);

class Element{
  public:
    bool enabled;
    short *pin;
    int aSize;

    void setPin(short a[], int b ){
      aSize=b;
      pin = new short[aSize];
      for(int i=0; i<aSize; i++)
        pin[i]=a[i];
    }
};

class Ranged{
  public: 
    int value_from;
    int value_to;
};

class Element_Ranged: public Element, public Ranged{
    public:
      Element_Ranged(bool a, short b[], int c, int d, int e){
        enabled=a;
        setPin(b,c);
        value_from=d;
        value_to=e;

        if(enabled)
          setInputPin(b,c);
      }
};

class Element_NRanged: public Element{
    public:
      Element_NRanged(bool a, short b[], int c){
        enabled=a;
        setPin(b,c); 

        if(enabled)
          setInputPin(b,c);
      }
};

short *clutchPin = new short[1]{A2};
Element_Ranged clutch(CLUTCH_ENABLED,clutchPin,1,600,930); //600

short *brakePin = new short[1]{A3};
Element_Ranged brake(BRAKE_ENABLED,brakePin,1,906,1023);

short *gasPin = new short[1]{A1};
Element_Ranged gas(GAS_ENABLED,gasPin,1,0,60);

short *steeringPin = new short[2]{0,1};
Element_Ranged steering(STEERING_ENABLED ,steeringPin,2,-800,800);

short *gearboxPin = new short[3]{10,16,14};
Element_NRanged gearbox(GEARBOX_ENABLED,gearboxPin,3);

short *gearboxChangePin = new short[2]{8,9};
Element_NRanged gearboxChange(GEARBOX_CHANGE_ENABLED,gearboxChangePin,2);

short *indicatorsPin = new short[2]{2,4};
Element_NRanged indicators(INDICATORS_ENABLED,indicatorsPin,2);

short *lightsPin = new short[1]{7};
Element_NRanged lights(LIGHTS_ENABLED,lightsPin,1);

short *enginePiny = new short[2]{5,6};
Element_NRanged engine(ENGINE_ENABLED,enginePiny,2);

short *wiperPin = new short[1]{3};
Element_NRanged wiper(WIPERS_ENABLED,wiperPin,1); 

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,28, 0,            
  false, //x
  false, //y
  true, //z
  true, //rx
  true, //ry
  true, //rz. 
  false, //rudder
  false, //throttle
  false, // accelerator
  false, // brake
  false // steering
  );

void setInputPin(short pin[], int aSize){

  if(aSize>1){
    for(int i=0; i<aSize; i++)
      pinMode(pin[i],INPUT);
  }
  else
    pinMode(pin[0], INPUT);
  
}

short gear[] = {0,1,2,3,4,5,6}; //numery przyciskĂłw do biegĂłw
short lastGear=100; 

void Gearbox(){
  bool bA=digitalRead(gearbox.pin[0]);
  bool bB=digitalRead(gearbox.pin[1]);
  bool bC=digitalRead(gearbox.pin[2]);


  
  if(!bA&&!bB&&!bC){ //PrzyjÄĹem losowa wartosc - 100 za luz
    if(lastGear!=100)
      Joystick.setButton(lastGear,LOW);
    lastGear=100;
  }
  else if(bA&&!bB&&!bC){ //4 - czwarty bieg
  if(lastGear!=gear[4])
      Joystick.setButton(lastGear,LOW);
    lastGear=gear[4];
    Joystick.setButton(gear[4],HIGH);
  }
  else if(!bA&&bB&&!bC){ //3 - trzeci bieg
  if(lastGear!=gear[3])
      Joystick.setButton(lastGear,LOW);
    lastGear=gear[3];
    Joystick.setButton(gear[3],HIGH);
  }
  else if(bA&&bB&&!bC){ //0 - wsteczny
  if(lastGear!=gear[0])
      Joystick.setButton(lastGear,LOW);
    lastGear=gear[0];
    Joystick.setButton(gear[0],HIGH);
  }
  else if(!bA&&!bB&&bC){ //1 - pierwszy bieg
  if(lastGear!=gear[1])
      Joystick.setButton(lastGear,LOW);
    lastGear=gear[1];
    Joystick.setButton(gear[1],HIGH);
  }
  else if(bA&&!bB&&bC){ //2 - drugi bieg
  if(lastGear!=gear[2])
      Joystick.setButton(lastGear,LOW);
    lastGear=gear[2];
    Joystick.setButton(gear[2],HIGH);
  }
  else if(!bA&&bB&&bC){ //5-piÄty bieg
  if(lastGear!=gear[5])
      Joystick.setButton(lastGear,LOW);
    lastGear=gear[5];
    Joystick.setButton(gear[5],HIGH);
  }
  else if(bA&&bB&&bC){ //6-wsteczny bieg
  if(lastGear!=gear[6])
      Joystick.setButton(lastGear,LOW);
    lastGear=gear[6];
    Joystick.setButton(gear[6],HIGH);
  }    
  
}

int rZValue=0;
int currentRzValue=0;

void Clutch(){
  rZValue=analogRead(clutch.pin[0]);
  if(rZValue!=currentRzValue){
    Joystick.setRzAxis(rZValue);
    currentRzValue=rZValue;
  }
}

int rXValue=0; 
int currentRxValue=0; 

void Brake(){
  rXValue=analogRead(brake.pin[0]);
  if(rXValue!=currentRxValue){
    Joystick.setRxAxis(rXValue);
    currentRxValue=rXValue;
  }
}

int rYValue=0; 
int currentRyValue=0;

void Gas(){
  rYValue=analogRead(gas.pin[0]);
  if(rYValue!=currentRyValue){
    Joystick.setRyAxis(rYValue);
    currentRyValue=rYValue;
  }
}

Encoder Enc(steering.pin[0],steering.pin[1]);
long posEnc;
int steeringValue=0;

void Steering(){
  long long enc; 
  enc = Enc.read()/3.64;
  if (enc != posEnc) 
  {
    
    steeringValue=enc*(-1);
    //Serial.println(steeringValue);
    Joystick.setZAxis(steeringValue);  
    posEnc = enc;
  }
}

bool engineLastPos=true;

void EngineFfb(){

  if(steeringValue>=-15&&steeringValue<=15&&engineLastPos==true){
    analogWrite(engine.pin[0],0);
    analogWrite(engine.pin[1],0);
    engineLastPos=false;
  }
  else if(steeringValue>15&&engineLastPos==false){
    analogWrite(engine.pin[1],30);
    engineLastPos=true;
    
    }
  else if(steeringValue<-15&&engineLastPos==false){
    analogWrite(engine.pin[0],30);
    engineLastPos=true;

  } 
}

bool lastgearboxChange=0; 
bool currentgearboxChange=0;

void GearboxChange(){

  currentgearboxChange=digitalRead(8);
  if(currentgearboxChange==1&&lastgearboxChange==0){
      Joystick.setButton(8,0);
      Joystick.setButton(9,1);
      lastgearboxChange=currentgearboxChange;
  }
  else if(currentgearboxChange==0&&lastgearboxChange==1){
      Joystick.setButton(8,1);
      Joystick.setButton(9,0);
      lastgearboxChange=currentgearboxChange;
  }
}

int currentIndicatorLeft;
int lastIndicatorLeft=0;


void LeftIndicator(){

  currentIndicatorLeft=digitalRead(indicators.pin[0]);

  if(currentIndicatorLeft==true&&lastIndicatorLeft==false){

    Joystick.setButton(10,1);
    lastIndicatorLeft=true;

  }
  if(currentIndicatorLeft==false&&lastIndicatorLeft==true){

    Joystick.setButton(10,0);
    Joystick.setButton(10,1);
    Joystick.setButton(10,0);

    lastIndicatorLeft=false;

  }
}

int currentIndicatorRight;
int lastIndicatorRight=0;

void RightIndicator(){

  currentIndicatorRight=digitalRead(indicators.pin[1]);

 if(currentIndicatorRight==true&&lastIndicatorRight==false){

    Joystick.setButton(11,1);
    lastIndicatorRight=true;

  }
  if(currentIndicatorRight==false&&lastIndicatorRight==true){

    Joystick.setButton(11,0);
    Joystick.setButton(11,1);
    Joystick.setButton(11,0);

    lastIndicatorRight=false;

  }  

}

int currentLights;
int lastLights=0;
void Lights(){

  currentLights=digitalRead(lights.pin[0]);
  if(currentLights!=lastLights){
    Joystick.setButton(12,currentLights);
    lastLights=currentLights;
  }
}

int currentWiper;
int lastWiper=0;
void Wiper(){

  currentWiper=digitalRead(wiper.pin[0]);
  if(currentWiper!=lastWiper){
    Joystick.setButton(13,currentWiper);
    lastWiper=currentWiper;
  }
}

void setup() {
    
  Joystick.begin();
  //Serial.begin(9600);

  if(brake.enabled){
    Joystick.setRxAxisRange(brake.value_from, brake.value_to); 
    Joystick.setRxAxis(rXValue);
  }

  if(gas.enabled){
    Joystick.setRyAxisRange(gas.value_from,gas.value_to); 
    Joystick.setRyAxis(rYValue);
  }

  if(clutch.enabled){
    Joystick.setRzAxisRange(clutch.value_from,clutch.value_to); 
    Joystick.setRzAxis(rZValue);
  }

  if(steering.enabled){
  Joystick.setZAxisRange(steering.value_from,steering.value_to); 
  Joystick.setZAxis(steeringValue);
  }

  delete[] steeringPin;
  delete[] gearboxPin;
  delete[] enginePiny;
  delete[] indicatorsPin;
  delete[] lightsPin;
  delete[] clutchPin;
  delete[] brakePin;
  delete[] gasPin;
  delete[] gearboxChangePin;
  delete[] wiperPin;

}


void loop() {

  if(gearboxChange.enabled){
    GearboxChange();
  }
  
  if(gearbox.enabled){
      Gearbox();
  }

  if(clutch.enabled)
    Clutch();
    
  if(brake.enabled) 
    Brake();
    
  if(gas.enabled)
    Gas();
    
  if(steering.enabled)
    Steering();

  if(indicators.enabled){
    LeftIndicator();
    RightIndicator();
  }

  if(wiper.enabled)
    Wiper();

  if(lights.enabled){
    Lights();
  }

  if(engine.enabled)
    EngineFfb();

}
