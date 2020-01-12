
#include "Constant_Definitions.h"
#include "PinChangeInterrupt.h"

unsigned long currentMillis = 0;


byte cycleStartButtonState = 0;

byte endstopBotSwitchState = 0;

byte endstopTopSwitchState = 0;

bool drilling_In_Progress = false;

void setup() {
  // put your setup code here, to run once:

    setUpPins();
    pwmSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  drillSequence();
  //analogWrite(drillMotorSignal, 5);
  //analogWrite(linearActuatorMotorSignal, 90);
  
  //Serial.print("butt");
}

void cycleStart_ISR() {
  

  if(drilling_In_Progress == false){

    cycleStartButtonState = !cycleStartButtonState;

  }
  //If cycle start button is pressed, begin drill sequence. Do nothing if button is pressed during sequence execution. 
  //After bottom endstop is triggered, home linear actuator. 

}

void bottomEndStopTriggered_ISR(){
  //bottom endstop has been triggered, immediately tell linear actuator to stop, wait a short while, and then cycle carrier plate up. 
  endstopBotSwitchState = 1;
}

void topEndStopTriggered_ISR(){

  endstopTopSwitchState = 1;

}