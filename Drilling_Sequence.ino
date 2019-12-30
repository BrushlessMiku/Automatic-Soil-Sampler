#include "Constant_Definitions.h"

int drillMotorEndSpeed = 255;
int drillMotorSpeed = 0;
int drillMotorRampPeriod = 500; //time for drill to throttle up in millis 
int numberOfDrillMotorThrottleSteps = 50; //number of drill motor throttle steps to take, needs to be a factor of drillMotorRampPeriod.
int drillMotorRampInterval = drillMotorRampPeriod/numberOfDrillMotorThrottleSteps;

int drillMotorThrottleStep =  (int) drillMotorEndSpeed/numberOfDrillMotorThrottleSteps;



unsigned long previousDrillRampMillis = 0; //timer for drill throttle ramping

void drillSequence(){

    //turn on drill and advance the carrier plate down until the bottom endstop is triggered.
    //when bottom endstop is triggered, turn off drill. Reverse linear actuator a short distance and wait a short moment. 
    //Reverse drill and cycle linear actuator up until top endstop is triggered.
    //set drilling_in_progress to false after triggering top endstop.       
    if (cycleStartButtonState == 1 && endstopBotSwitchState == 0)

        {
            cycleLinearAcuatorDown();
            rampDrillMotorUp(drillMotorEndSpeed);

    }
    
    else{

        stopLinearActuator();
        stopDrillMotor();
    }
   
}

void rampDrillMotorUp(int endSpeed){
    //provide a smooth ramp input to the drill motor 
    //should be non-blocking 

    if (currentMillis - previousDrillRampMillis >= drillMotorRampInterval){
        
        previousDrillRampMillis += drillMotorRampInterval;

        if(drillMotorSpeed < endSpeed){

            drillMotorSpeed += drillMotorThrottleStep;

            analogWrite(drillMotorPin, drillMotorSpeed);

        }else {

            analogWrite(drillMotorPin, endSpeed);
        }
    }

}
void cycleLinearAcuatorDown(){

    analogWrite(linearActuatorMotorSignal, 15);
    drilling_In_Progress  = true; 

}

void stopLinearActuator(){

    analogWrite(linearActuatorMotorSignal, 0);
    
}

void stopDrillMotor(){

    
    analogWrite(drillMotorPin, 0);


}