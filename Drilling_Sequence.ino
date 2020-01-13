#include "Constant_Definitions.h"

unsigned int drillMotorTargetSpeed = 65535;
unsigned int drillMotorSpeed = 0;
unsigned long drillMotorRampPeriod = 1000; //time for drill to throttle up in millis 
int numberOfDrillMotorThrottleSteps = 100; //number of drill motor throttle steps to take, needs to be a factor of drillMotorRampPeriod.
int drillMotorRampInterval = drillMotorRampPeriod/numberOfDrillMotorThrottleSteps;

unsigned int drillMotorThrottleStep = (unsigned int) drillMotorTargetSpeed/numberOfDrillMotorThrottleSteps;

unsigned long previousDrillRampMillis = 0; //timer for drill throttle ramping

unsigned long previousCarrierPlateMillis = 0;

int timeToBumpCarrierPlateUp = 1000; // length of time in millis to bump up carrier plate 

int timeToBumpCarrierPlateDown = 1000;

bool downStrokeHaltMotorProcedureComplete = false; 
bool upStrokeHaltMotorProcedureComplete = false;
bool carrierPlateBumpProcedureComplete = false;
bool carrierPlateParkingProcedureComplete = false;


void drillSequence(){

    //turn on drill and advance the carrier plate down until the bottom endstop is triggered.
    //when bottom endstop is triggered, turn off drill. Reverse linear actuator a short distance and wait a short moment. 
    //Reverse drill and cycle linear actuator up until top endstop is triggered.
    //set drilling_in_progress to false after triggering top endstop.       
    if (cycleStartButtonState == 1 && endstopBotSwitchState == 0){

        cycleLinearActuatorDown();
        rampDrillMotorUp(drillMotorTargetSpeed);

    }
    
    if(cycleStartButtonState == 1 && endstopBotSwitchState == 1 && downStrokeHaltMotorProcedureComplete == false){
        
        stopLinearActuator();
        rampDrillMotorDown_DownStroke();
 
    }

    if(cycleStartButtonState == 1 && endstopBotSwitchState == 1 && carrierPlateParkingProcedureComplete == false &&
         downStrokeHaltMotorProcedureComplete == true){
        
            bumpCarrierPlateUp(timeToBumpCarrierPlateUp);
    }
    
    if(cycleStartButtonState == 1 && endstopBotSwitchState == 1 && endstopTopSwitchState == 0 && 
        carrierPlateParkingProcedureComplete == true){
        
            rampDrillMotorUp(drillMotorTargetSpeed); //spin drill motor CCW
            cycleLinearActuatorUp();
        
    }

    if(cycleStartButtonState == 1 && endstopTopSwitchState == 1 && upStrokeHaltMotorProcedureComplete == false){

        //carrierPlateParkingProcedureComplete = false;
        stopLinearActuator();
        rampDrillMotorDown_UpStroke();

    }

    if(cycleStartButtonState == 1 && endstopTopSwitchState == 1 && upStrokeHaltMotorProcedureComplete == true){

        bumpCarrierPlateDown(timeToBumpCarrierPlateDown);

    }

   
}

void rampDrillMotorUp(unsigned int topDrillSpeed){
    //provide a smooth ramp up input to the drill motor 
    //should be non-blocking 

    if (currentMillis - previousDrillRampMillis >= drillMotorRampInterval){
        
        previousDrillRampMillis = currentMillis;

        if(drillMotorSpeed < topDrillSpeed- drillMotorThrottleStep){

            drillMotorSpeed += drillMotorThrottleStep;
            writePWM16Bit(drillMotorPin, drillMotorSpeed);

        }else {
            
            writePWM16Bit(drillMotorPin, topDrillSpeed);
        }
    }

}

void rampDrillMotorDown_DownStroke(){
    //provide a smooth ramp down input to the drill motor 
    //should be non-blocking 

    if (currentMillis - previousDrillRampMillis >= drillMotorRampInterval){
        
        previousDrillRampMillis = currentMillis;

        if(drillMotorSpeed > drillMotorThrottleStep){

            downStrokeHaltMotorProcedureComplete = false;

            drillMotorSpeed -= drillMotorThrottleStep;

            writePWM16Bit(drillMotorPin, drillMotorSpeed);

        }else {

            writePWM16Bit(drillMotorPin, 0);
            downStrokeHaltMotorProcedureComplete = true; 

            //delay(1000);
        }
    }

}

void rampDrillMotorDown_UpStroke(){
    //provide a smooth ramp down input to the drill motor 
    //should be non-blocking 

    if (currentMillis - previousDrillRampMillis >= drillMotorRampInterval){
        
        previousDrillRampMillis = currentMillis;

        if(drillMotorSpeed > 0){

            upStrokeHaltMotorProcedureComplete = false;

            drillMotorSpeed -= drillMotorThrottleStep;

            writePWM16Bit(drillMotorPin, drillMotorSpeed);

        }else {

            writePWM16Bit(drillMotorPin, 0);
            upStrokeHaltMotorProcedureComplete = true;
            carrierPlateBumpProcedureComplete = false;
 
        }
    }

}

void bumpCarrierPlateUp(int timeToBumpCarrierPlateUp){

    //function used to "park" the carrier plate slightly above the bottom endstop switch 
    //open loop 

    if(currentMillis - previousCarrierPlateMillis >= timeToBumpCarrierPlateUp){

        previousCarrierPlateMillis  = currentMillis;


        if(carrierPlateBumpProcedureComplete == false){

            writePWM16Bit(linearActuatorMotorSignal, 1500);
            carrierPlateBumpProcedureComplete = true; 

        }else {

            writePWM16Bit(linearActuatorMotorSignal, 0);
           
            carrierPlateParkingProcedureComplete = true; 

            delay(1000);
        }


    }

}

void bumpCarrierPlateDown(int timeToBumpCarrierPlateDown){

    //function used to "park" the carrier plate slightly below the top endstop switch 
    //open loop 

    if(currentMillis - previousCarrierPlateMillis >= timeToBumpCarrierPlateDown){

        previousCarrierPlateMillis  = currentMillis;


        if(carrierPlateBumpProcedureComplete == false){

            writePWM16Bit(linearActuatorMotorSignal, 1500);
            carrierPlateBumpProcedureComplete = true; 
        }else {

            writePWM16Bit(linearActuatorMotorSignal, 0);

            carrierPlateParkingProcedureComplete = true; 

            delay(1000);
        }


    }

}

void cycleLinearActuatorDown(){

    writePWM16Bit(linearActuatorMotorSignal, 1500);
    drilling_In_Progress  = true; 

}

void cycleLinearActuatorUp(){
    
    writePWM16Bit(linearActuatorMotorSignal, 1500);
    carrierPlateBumpProcedureComplete = false; 

}

void stopLinearActuator(){

    writePWM16Bit(linearActuatorMotorSignal, 0);
    
}

void stopDrillMotor(){

    
    writePWM16Bit(drillMotorPin, 0);


}
