
#include "Constant_Definitions.h"
#include "PinChangeInterrupt.h"

unsigned long currentMillis = 0;


int cycleStartButtonState = 0;

int endstopBotSwitchState = 0;

bool drilling_In_Progress = false;

void setup() {
  // put your setup code here, to run once:

    setUpPins();

}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  drillSequence();
  //analogWrite(drillMotorSignal, 5);
  //analogWrite(linearActuatorMotorSignal, 90);
  

}

void cycleStartISR() {
  

  if(drilling_In_Progress == false){

    cycleStartButtonState = !cycleStartButtonState;

  }
  //If cycle start button is pressed, begin drill sequence. Do nothing if button is pressed during sequence execution. 
  //After bottom endstop is triggered, home linear actuator. 

}

void bottomEndStopTriggered(){
  //bottom endstop has been triggered, immediately tell linear actuator to stop, wait a short while, and then cycle carrier plate up. 
  endstopBotSwitchState = 1;

}
