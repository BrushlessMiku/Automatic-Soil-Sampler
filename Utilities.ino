

void pwmSetup(){

    TCCR1A = 0;
    TCCR1B = 0;

    TCCR1A |= (1<< WGM11) | (1 << COM1A1) | ( 1 << COM1B1);

    TCCR1B |= ( 1 << WGM13) | ( 1 << CS10);

    ICR1 = 0xFFFF;
}

void writePWM(int pin, int pwmValue){

    if(pin == 9){

        OCR1A = pwmValue;

    }
    
    
    if(pin == 10){

        OCR1B = pwmValue;

    } 


}