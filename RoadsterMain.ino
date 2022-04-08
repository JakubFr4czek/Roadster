#include <Roadster.h>
#include <Encoder.h>

#define GasPin A0
#define BrakePin A1
#define ClutchPin A2
#define SteeringWheelPin1 14
#define SteeringWheelPin2 15
#define HandbrakePin A3
#define EnginePin1 16
#define EnginePin2 10

Encoder Enc(SteeringWheelPin1, SteeringWheelPin2);
long long steeringWheelValue;

long long SteeringWheel(){
  
  steeringWheelValue =  (Enc.read()/3.64)*(-1);
  
}

bool engineLastPos=true;

void Engine(){

  if(steeringWheelValue>=-15&&steeringWheelValue<=15&&engineLastPos==true){
    analogWrite(EnginePin1,0);
    analogWrite(EnginePin2,0);
    engineLastPos=false;
  }
  else if(steeringWheelValue>15&&engineLastPos==false){
    analogWrite(EnginePin1,30);
    engineLastPos=true;
    
    }
  else if(steeringWheelValue<-15&&engineLastPos==false){
    analogWrite(EnginePin2,30);
    engineLastPos=true;

  } 
}


void setup() {
  
   Roadster.begin();
  
  //Gaz
  pinMode(GasPin, INPUT);
  Roadster.setXAxisRange(350, 700);

  //Hamulec
  pinMode(BrakePin, INPUT);
  Roadster.setYAxisRange(350, 700);

  //Sprzeglo
  pinMode(ClutchPin, INPUT);
  Roadster.setRXAxisRange(350, 700);

  //Kierownica
  pinMode(SteeringWheelPin1, INPUT);
  pinMode(SteeringWheelPin2, INPUT);
  Roadster.setRYAxisRange(350, 700);

  //Reczny
  pinMode(HandbrakePin, INPUT);
  Roadster.setZAxisRange(350, 700);

  //Silnik force feedback
  pinMode(EnginePin1, INPUT);
  pinMode(EnginePin2, INPUT);

  //poniżej będzie/ą rozpisany/e ekspnder/y wyprowadzeń
  //o tutaj właśnie, wykorzystuje dwa piny po I2C

  //zostaje dużo dodatkowych pinów: 0,1,4,5,6,7,8,9
  //tutaj można do nich rozpisać output: zegary?
  
}

void loop() {

  //Gaz
  Roadster.setRXAxis(analogRead(GasPin));

  //Hamulec
  Roadster.setYAxis(analogRead(BrakePin));

  //Sprzeglo
  Roadster.setRXAxis(analogRead(BrakePin));

  //Kierownica
  SteeringWheel();
  Roadster.setRYAxis(steeringWheelValue);

  //Silnik środkujący kierownicę
  Engine();

  //Reczny
  Roadster.setZAxis(analogRead(HandbrakePin));

  //Skrzynia biegów (będzie obsługiwana
  //z wykorzystaniem ekspandeera wyprowadzeń)
  
}
