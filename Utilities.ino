

void pwmSetup_16bit(){

    //sets up Timer1 to generate symmetric PWM signals with fastest clock prescale of 1
    TCCR1A = 0;
    TCCR1B = 0;

    TCCR1A |= (1 << WGM11) | (1 << COM1A1) | ( 1 << COM1B1);

    TCCR1B |= ( 1 << WGM13) | ( 1 << CS10);

    ICR1 = 0xFFFF;
}



void writePWM16Bit(int pin, unsigned int pwmValue){

    // uses Timer1 to write PWM signals on Atmega328p pins 9 and 10. 
    if(pin == 9){

        OCR1A = pwmValue;

    }
    
    
    if(pin == 10){

        OCR1B = pwmValue;

    } 


}

