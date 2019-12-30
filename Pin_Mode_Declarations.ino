
void setUpPins(){
    //declare output pins and attach all interrupts

    pinMode(endStopTopIndicatorPin, OUTPUT);
    pinMode(endStopBotIndicatorPin, OUTPUT);
    pinMode(drillMotorPin, OUTPUT);
    pinMode(linearActuatorMotorSignal, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(cycleStartButtonPin), cycleStartISR, CHANGE);
    attachPCINT(digitalPinToPCINT(endStopBot), bottomEndStopTriggered, CHANGE);

}