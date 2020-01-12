
void setUpPins(){
    //declare output pins and attach all interrupts

    pinMode(endStopTopIndicatorPin, OUTPUT);
    pinMode(endStopBotIndicatorPin, OUTPUT);
    pinMode(endStopBot, INPUT);
    pinMode(endStopTop, INPUT);
    pinMode(drillMotorPin, OUTPUT);
    pinMode(linearActuatorMotorSignal, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(cycleStartButtonPin), cycleStart_ISR, CHANGE);
    attachPCINT(digitalPinToPCINT(endStopBot), bottomEndStopTriggered_ISR, CHANGE);
    attachPCINT(digitalPinToPCINT(endStopTop), topEndStopTriggered_ISR, CHANGE);
}