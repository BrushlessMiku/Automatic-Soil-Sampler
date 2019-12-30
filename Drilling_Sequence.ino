#include "Constant_Definitions.h"

int drillMotorEndSpeed = 255;
int drillMotorSpeed = 0;
unsigned long drillMotorRampPeriod = 500; //time for drill to throttle up in millis 
int numberOfDrillMotorThrottleSteps = 50; //number of drill motor throttle steps to take, needs to be a factor of drillMotorRampPeriod.
int drillMotorRampInterval = drillMotorRampPeriod/numberOfDrillMotorThrottleSteps;

int drillMotorThrottleStep =  (int) drillMotorEndSpeed/numberOfDrillMotorThrottleSteps;



unsigned long previousDrillRampMillis = 0; //timer for drill throttle ramping

unsigned long previousCarrierPlateMillis = 0;

int timeToBumpCarrierPlateUp = 1000; // length of time in millis to bump up carrier plate 


bool haltMotorProcedureComplete = false; 
bool carrierPlateBumpStatus = false;
bool carrierPlateParkingProcedureComplete = false;
void drillSequence(){

    //turn on drill and advance the carrier plate down until the bottom endstop is triggered.
    //when bottom endstop is triggered, turn off drill. Reverse linear actuator a short distance and wait a short moment. 
    //Reverse drill and cycle linear actuator up until top endstop is triggered.
    //set drilling_in_progress to false after triggering top endstop.       
    if (cycleStartButtonState == 1 && endstopBotSwitchState == 0){

        
        cycleLinearActuatorDown();
        rampDrillMotorUp(drillMotorEndSpeed);

    }
    
    if(cycleStartButtonState == 1 && endstopBotSwitchState == 1 && haltMotorProcedureComplete == false){
        
        stopLinearActuator();
        rampDrillMotorDown();
 
    }

    if(cycleStartButtonState == 1 && endstopBotSwitchState == 1 && haltMotorProcedureComplete == true){
        
        bumpCarrierPlateUp(timeToBumpCarrierPlateUp);
 
    }
    
    if(cycleStartButtonState == 1 && endstopBotSwitchState == 1 && carrierPlateParkingProcedureComplete == true){
        
        rampDrillMotorUp(); //spin drill motor CCW
        cycleLinearActuatorUp();
        
    }

   
}

void rampDrillMotorUp(int topDrillSpeed){
    //provide a smooth ramp up input to the drill motor 
    //should be non-blocking 

    if (currentMillis - previousDrillRampMillis >= drillMotorRampInterval){
        
        previousDrillRampMillis = currentMillis;

        if(drillMotorSpeed < topDrillSpeed){

            drillMotorSpeed += drillMotorThrottleStep;

            analogWrite(drillMotorPin, drillMotorSpeed);

        }else {

            analogWrite(drillMotorPin, topDrillSpeed);
        }
    }

}

void rampDrillMotorDown(){
    //provide a smooth ramp down input to the drill motor 
    //should be non-blocking 

    if (currentMillis - previousDrillRampMillis >= drillMotorRampInterval){
        
        previousDrillRampMillis = currentMillis;

        if(drillMotorSpeed >= 0){

            drillMotorSpeed -= drillMotorThrottleStep;

            analogWrite(drillMotorPin, drillMotorSpeed);

        }else {

            analogWrite(drillMotorPin, 0);
            haltMotorProcedureComplete = true; 
        }
    }

}

void bumpCarrierPlateUp(int bumpTime){

    //function used to "park" the carrier plate slightly above the bottom endstop switch 
    //open loop 

    if(currentMillis - previousCarrierPlateMillis >= bumpTime){

        previousCarrierPlateMillis  = currentMillis;


        if(carrierPlateBumpStatus == false){

            analogWrite(linearActuatorMotorSignal, 15);
            carrierPlateBumpStatus = true; 
        }else {

            analogWrite(linearActuatorMotorSignal, 0);
            carrierPlateParkingProcedureComplete = true; 
        }


    }

}

void cycleLinearActuatorDown(){

    analogWrite(linearActuatorMotorSignal, 15);
    drilling_In_Progress  = true; 

}

void cycleLinearActuatorUp(){
    
    analogWrite(linearActuatorMotorSignal, 15);

}

void stopLinearActuator(){

    analogWrite(linearActuatorMotorSignal, 0);
    
}

void stopDrillMotor(){

    
    analogWrite(drillMotorPin, 0);


}