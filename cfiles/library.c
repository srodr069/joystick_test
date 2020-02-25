void ADC_init(){

    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);

}


unsigned short ReadADC(unsigned char ch){

    ch = ch & 0x07;

    ADMUX = (ADMUX & 0xF8) | ch;

    

    ADCSRA |= (1<<ADSC);


    while(!(ADCSRA & (1<<ADIF)));

    

    //        ADCSRA |= (1<<ADIF);

    

    return(ADC);

}




























unsigned char _left = 0;

unsigned char _right = 0;

unsigned char _up = 0;

unsigned char _down = 0;

unsigned char led = 0x00;


//#define x ReadADC(0)

//#define y ReadADC(1)

unsigned short x;

unsigned short y;


void js(){

    x = ReadADC(0);

    y = ReadADC(1);

    if(x > 900){

        led = 0x08;

        _left = 1; //left

    }

    else if(x < 300){

        led = 0x04; //right

        _right = 1;

    }

    else if(y < 300){

        led = 0x02; //up

        _up = 1;

    }

    else if(y > 900 ){

        led = 0x01; //down

        _down = 1;

    }

    else{

        led = 0x00;

        _left = 0;

        _right = 0;

        _down = 0;

        _up = 0;

    }

}






volatile unsigned char TimerFlag = 0;


unsigned long _avr_timer_M = 1;

unsigned long _avr_timer_cntcurr = 0;



void TimerOn(){

    TCCR1B = 0x0B;



    OCR1A = 125;

    TIMSK1 = 0x02;

    TCNT1 = 0;

    _avr_timer_cntcurr = _avr_timer_M;


    SREG = 0x80;

}


void TimerOff(){

    TCCR1B = 0x00;

}


void TimerISR(){

    TimerFlag = 1;

}


ISR(TIMER1_COMPA_vect){

    _avr_timer_cntcurr--;

    if(_avr_timer_cntcurr == 0){

        TimerISR();

        _avr_timer_cntcurr = _avr_timer_M;

    }

}


void TimerSet(unsigned long M){

    _avr_timer_M = M;

    _avr_timer_cntcurr = _avr_timer_M;

}