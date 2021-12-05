//Written by Jakub Frączek 
//contact: kuba.fr.20@gmail.com
//phone: 667 717 381

/*  !README FIRST! 
 *   
 *  KONFIGURACJA PROGRAMU
 *  1. Pobrać następujące biblioteki:
 *  - https://github.com/MHeironimus/ArduinoJoystickLibrary
 *  - https://github.com/PaulStoffregen/Encoder
 *  - https://github.com/dmadison/ArduinoXInput
 *  2. Przenieść i rozpakować pobrane biblioteki do dokumenty/arduino/libraries
 *  3. Pobrać najnowsze wydanie: https://github.com/dmadison/ArduinoXInput_AVR
 *  4. Odnaleźć miejsce na dysku w którym zainstalowane jest Arduino IDE,
 *  przykładowo: D:\Arduino\
 *  5. Do folderu D:\Arduino\hardware przenieść i rozpakować pobrany plik
 *   
 *  JOYSTICK
 *  W celu użycia arduino jako zwykłego kontrolera, należy odkomentować #define JOY
 *  oraz zakomentować #define XBOX oraz wybrać Arduino z AVR Boards, nie trzeba wybierać portu.
 *  Gdy pokaże się "Uploading..." dwa razy szybko kliknąć guzik reset na arduino, dioda
 *  z podpisem L powinna zacząć migać. 
 *  
 *  XBOX 360 GAMEPAD
 *  W celu użycia arduino jako pada od xboxa 360 należy odkomentować #define XBOX
 *  oraz zakomentować #define JOY oraz wybrać Arduino Leonardo z XInput AVR Boards, 
 *  nie trzeba wybierać portu. Gdy pokaże się "Uploading..." dwa razy szybko kliknąć 
 *  guzik reset na arduino, dioda z podpisem L powinna zacząć migać. 
 * 
*/


#define XBOX // pokazuje sie jako pad od xbox 360
//#define JOY // pokazuje sie jako zwykly joystick

#ifdef JOY
  #include <Joystick.h> //https://github.com/MHeironimus/ArduinoJoystickLibrary
#endif

#ifdef XBOX
  #include <XInput.h> //https://github.com/dmadison/ArduinoXInput
#endif

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

#define CLUTCH_PIN A2
#define BRAKE_PIN A3
#define GAS_PIN A1
#define STEERING_PIN_A 0 
#define STEERING_PIN_B 1
#define GEARBOX_PIN_A 10
#define GEARBOX_PIN_B 16
#define GEARBOX_PIN_C 14
#define GEARBOX_BUTTON_PIN_A 8
#define GEARBOX_BUTTON_PIN_B 9
#define INDICATOR_PIN_A 2
#define INDICATOR_PIN_B 4
#define LIGHTS_PIN 7
#define ENGINE_PIN_A 5
#define ENGINE_PIN_B 6
#define WIPER_PIN 3

#define CLUTCH_RANGE_A 600
#define CLUTCH_RANGE_B 930
#define BRAKE_RANGE_A 906
#define BRAKE_RANGE_B 1023
#define GAS_RANGE_A 0
#define GAS_RANGE_B 60
#define STEERING_RANGE_A -800
#define STEERING_RANGE_B 800


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



short *clutchPin = new short[1]{CLUTCH_PIN};
Element_Ranged clutch(CLUTCH_ENABLED,clutchPin,1,CLUTCH_RANGE_A,CLUTCH_RANGE_B); //600

short *brakePin = new short[1]{BRAKE_PIN};
Element_Ranged brake(BRAKE_ENABLED,brakePin,1,BRAKE_RANGE_A,BRAKE_RANGE_B);

short *gasPin = new short[1]{GAS_PIN};
Element_Ranged gas(GAS_ENABLED,gasPin,1,GAS_RANGE_A,GAS_RANGE_B);

short *steeringPin = new short[2]{STEERING_PIN_A,STEERING_PIN_B};
Element_Ranged steering(STEERING_ENABLED ,steeringPin,2,STEERING_RANGE_A,STEERING_RANGE_B);

short *gearboxPin = new short[3]{GEARBOX_PIN_A,GEARBOX_PIN_B,GEARBOX_PIN_C};
Element_NRanged gearbox(GEARBOX_ENABLED,gearboxPin,3);

short *gearboxChangePin = new short[2]{GEARBOX_BUTTON_PIN_A,GEARBOX_BUTTON_PIN_B};
Element_NRanged gearboxChange(GEARBOX_CHANGE_ENABLED,gearboxChangePin,2);

short *indicatorsPin = new short[2]{INDICATOR_PIN_A,INDICATOR_PIN_B};
Element_NRanged indicators(INDICATORS_ENABLED,indicatorsPin,2);

short *lightsPin = new short[1]{LIGHTS_PIN};
Element_NRanged lights(LIGHTS_ENABLED,lightsPin,1);

short *enginePiny = new short[2]{ENGINE_PIN_A,ENGINE_PIN_B};
Element_NRanged engine(ENGINE_ENABLED,enginePiny,2);

short *wiperPin = new short[1]{WIPER_PIN};
Element_NRanged wiper(WIPERS_ENABLED,wiperPin,1); 

#ifdef JOY
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
#endif

void setInputPin(short pin[], int aSize){

  if(aSize>1){
    for(int i=0; i<aSize; i++)
      pinMode(pin[i],INPUT);
  }
  else
    pinMode(pin[0], INPUT);
  
}

short gear[] = {0,1,2,3,4,5,6}; //numery przyciskĂłw do biegĂłw
#ifdef XBOX
  XInputControl XboxGear[] = { BUTTON_LB, BUTTON_RB, BUTTON_A, BUTTON_B, BUTTON_X, BUTTON_Y, BUTTON_START};
#endif
short lastGear=100; 

void Gearbox(){
  bool bA=digitalRead(gearbox.pin[0]);
  bool bB=digitalRead(gearbox.pin[1]);
  bool bC=digitalRead(gearbox.pin[2]);


  
  if(!bA&&!bB&&!bC){ //PrzyjÄĹem losowa wartosc - 100 za luz
    if(lastGear!=100){

      #ifdef XBOX
        XInput.setButton(XboxGear[lastGear], 0);
      #endif
      
      #ifdef JOY
        Joystick.setButton(lastGear,LOW);
      #endif
      
    }
    lastGear=100;
  }
  else if(bA&&!bB&&!bC){ //4 - czwarty bieg
    if(lastGear!=gear[4]){
      
      #ifdef XBOX
        XInput.setButton(XboxGear[lastGear], 0);
      #endif

      #ifdef JOY
        Joystick.setButton(lastGear,LOW);
      #endif
      
   }        
   
    lastGear=gear[4];

    #ifdef XBOX
      XInput.setButton(XboxGear[4], HIGH);
    #endif
    #ifdef JOY
      Joystick.setButton(gear[4],HIGH);
    #endif
  }
  else if(!bA&&bB&&!bC){ //3 - trzeci bieg
    if(lastGear!=gear[3]){
      
      #ifdef XBOX
        XInput.setButton(XboxGear[lastGear], 0);
      #endif
      #ifdef JOY
        Joystick.setButton(lastGear,LOW);
      #endif
        
    }
    
    lastGear=gear[3];
    
    #ifdef XBOX
      XInput.setButton(XboxGear[3], HIGH);
    #endif
    #ifdef JOY
      Joystick.setButton(gear[3],HIGH);
    #endif
  }
  else if(bA&&bB&&!bC){ //0 - wsteczny
    if(lastGear!=gear[0]){
      
      #ifdef XBOX
        XInput.setButton(XboxGear[lastGear], 0);
      #endif
      #ifdef JOY
        Joystick.setButton(lastGear,LOW);
      #endif
  }
  
    lastGear=gear[0];
    
    #ifdef XBOX
      XInput.setButton(XboxGear[0], HIGH);
    #endif
    #ifdef JOY
      Joystick.setButton(gear[0],HIGH);
    #endif
  }
  else if(!bA&&!bB&&bC){ //1 - pierwszy bieg
  if(lastGear!=gear[1]){
    
      #ifdef XBOX
        XInput.setButton(XboxGear[lastGear], 0);
      #endif
      #ifdef JOY
        Joystick.setButton(lastGear,LOW);
      #endif
  }
  
    lastGear=gear[1];

    #ifdef XBOX
      XInput.setButton(XboxGear[1], HIGH);
    #endif
    #ifdef JOY
      Joystick.setButton(gear[1],HIGH);
    #endif
  }
  else if(bA&&!bB&&bC){ //2 - drugi bieg
    if(lastGear!=gear[2]){
      #ifdef XBOX
        XInput.setButton(XboxGear[lastGear], 0);
      #endif
      #ifdef JOY
        Joystick.setButton(lastGear,LOW);
      #endif
  }
  
    lastGear=gear[2];
    #ifdef XBOX
      XInput.setButton(XboxGear[2], HIGH);
    #endif
    #ifdef JOY
      Joystick.setButton(gear[2],HIGH);
    #endif
  }
  else if(!bA&&bB&&bC){ //5-piÄty bieg
    if(lastGear!=gear[5]){
      #ifdef XBOX
        XInput.setButton(XboxGear[lastGear], 0);
      #endif
      #ifdef JOY
        Joystick.setButton(lastGear,LOW);
      #endif
  }
  
    lastGear=gear[5];
    #ifdef XBOX
      XInput.setButton(XboxGear[5], HIGH);
    #endif
    #ifdef JOY
      Joystick.setButton(gear[5],HIGH);
    #endif
  }
  else if(bA&&bB&&bC){ //6-wsteczny bieg
  if(lastGear!=gear[6]){
      #ifdef XBOX
        XInput.setButton(XboxGear[lastGear], 0);
      #endif
      #ifdef JOY
        Joystick.setButton(lastGear,LOW);
      #endif
  }
  
    lastGear=gear[6];
    #ifdef XBOX
      XInput.setButton(XboxGear[6], HIGH);
    #endif
    #ifdef JOY
      Joystick.setButton(gear[6],HIGH);
    #endif
  }    
  
}

int rZValue=0;
int currentRzValue=0;

void Clutch(){
  rZValue=analogRead(clutch.pin[0]);
  if(rZValue!=currentRzValue){

    #ifdef XBOX
      XInput.setJoystickX(JOY_LEFT, rZValue);
    #endif
    #ifdef JOY
      Joystick.setRzAxis(rZValue);
    #endif

    currentRzValue=rZValue;
  }
}

int rXValue=0; 
int currentRxValue=0; 

void Brake(){
  rXValue=analogRead(brake.pin[0]);
  if(rXValue!=currentRxValue){

    #ifdef XBOX
      XInput.setTrigger(TRIGGER_LEFT, rXValue);
    #endif
    #ifdef JOY
      Joystick.setRxAxis(rXValue);
    #endif

    currentRxValue=rXValue;
  }
}

int rYValue=0; 
int currentRyValue=0;

void Gas(){
  rYValue=analogRead(gas.pin[0]);
  if(rYValue!=currentRyValue){

    #ifdef XBOX
      XInput.setTrigger(TRIGGER_RIGHT, rYValue);
    #endif
    #ifdef JOY
      Joystick.setRyAxis(rYValue);
    #endif

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
    #ifdef XBOX
       XInput.setJoystickX(JOY_RIGHT, steeringValue);
    #endif
    #ifdef JOY
      Joystick.setZAxis(steeringValue); 
    #endif 
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
    analogWrite(engine.pin[0],30);
    engineLastPos=true;
    
    }
  else if(steeringValue<-15&&engineLastPos==false){
    analogWrite(engine.pin[1],30);
    engineLastPos=true;

  } 
}

bool lastgearboxChange=0; 
bool currentgearboxChange=0;

void GearboxChange(){

  currentgearboxChange=digitalRead(8);
  if(currentgearboxChange==1&&lastgearboxChange==0){

      #ifdef XBOX
        XInput.setButton(BUTTON_L3, 0);
        XInput.setButton(BUTTON_R3, 1);
      #endif
      #ifdef JOY
        Joystick.setButton(8,0);
        Joystick.setButton(9,1);
      #endif

      lastgearboxChange=currentgearboxChange;
  }
  else if(currentgearboxChange==0&&lastgearboxChange==1){

     #ifdef XBOX
        XInput.setButton(BUTTON_L3, 1);
        XInput.setButton(BUTTON_R3, 0);
      #endif
      #ifdef JOY
        Joystick.setButton(8,1);
        Joystick.setButton(9,0);
      #endif

      lastgearboxChange=currentgearboxChange;
  }
}

int currentIndicatorLeft;
int lastIndicatorLeft=0;


void LeftIndicator(){

  currentIndicatorLeft=digitalRead(indicators.pin[0]);

  if(currentIndicatorLeft==true&&lastIndicatorLeft==false){

    #ifdef XBOX
      XInput.setDpad(DPAD_LEFT, 1);
    #endif
    #ifdef JOY
      Joystick.setButton(10,1);
    #endif

    lastIndicatorLeft=true;

  }
  if(currentIndicatorLeft==false&&lastIndicatorLeft==true){

    #ifdef XBOX
      XInput.setDpad(DPAD_LEFT, 0);
      XInput.setDpad(DPAD_LEFT, 1);
      XInput.setDpad(DPAD_LEFT, 0);
    #endif
    #ifdef JOY
      Joystick.setButton(10,0);
      Joystick.setButton(10,1);
      Joystick.setButton(10,0);
    #endif
    lastIndicatorLeft=false;

  }
}

int currentIndicatorRight;
int lastIndicatorRight=0;

void RightIndicator(){

  currentIndicatorRight=digitalRead(indicators.pin[1]);

 if(currentIndicatorRight==true&&lastIndicatorRight==false){

    #ifdef XBOX
      XInput.setDpad(DPAD_RIGHT, 1);
    #endif
    #ifdef JOY
      Joystick.setButton(11,1);
    #endif
    lastIndicatorRight=true;

  }
  if(currentIndicatorRight==false&&lastIndicatorRight==true){

    #ifdef XBOX
      XInput.setDpad(DPAD_RIGHT, 0);
      XInput.setDpad(DPAD_RIGHT, 1);
      XInput.setDpad(DPAD_RIGHT, 0);
    #endif
    #ifdef JOY
      Joystick.setButton(11,0);
      Joystick.setButton(11,1);
      Joystick.setButton(11,0);
    #endif

    lastIndicatorRight=false;

  }  

}

int currentLights;
int lastLights=0;
void Lights(){

  currentLights=digitalRead(lights.pin[0]);
  if(currentLights!=lastLights){

    #ifdef XBOX
      XInput.setDpad(DPAD_UP, currentLights);
    #endif
    #ifdef JOY
      Joystick.setButton(12,currentLights);
    #endif
    lastLights=currentLights;
  }
}

int currentWiper;
int lastWiper=0;
void Wiper(){

  currentWiper=digitalRead(wiper.pin[0]);
  if(currentWiper!=lastWiper){

    #ifdef XBOX
      XInput.setDpad(DPAD_DOWN, currentWiper);
    #endif
    #ifdef JOY
      Joystick.setButton(13,currentWiper);
    #endif

    lastWiper=currentWiper;
  }
}

void setup() {
  
  #ifdef JOY
    Joystick.begin();

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

  #endif
  #ifdef XBOX
    XInput.setAutoSend(true);
    XInput.begin();
    
    if(brake.enabled)
      XInput.setRange(TRIGGER_LEFT, brake.value_from, brake.value_to);
    if(gas.enabled)
      XInput.setRange(TRIGGER_RIGHT, gas.value_from, gas.value_to);
    if(clutch.enabled)
      XInput.setRange(JOY_LEFT, clutch.value_from, clutch.value_to);
    if(steering.enabled)
      XInput.setRange(JOY_RIGHT, steering.value_from, steering.value_to);
  


  #endif
   
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
