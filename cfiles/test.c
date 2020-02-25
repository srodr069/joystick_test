#include <avr/io.h>
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


void ADC_init(){
ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

unsigned short ReadADC(unsigned char ch){
ch = ch & 0x01;
ADMUX = (ADMUX & 0xF8) | ch;

ADCSRA |= (1<<ADSC);

while(!(ADCSRA & (1<<ADIF)));

//        ADCSRA |= (1<<ADIF);

return(ADC);
}

unsigned char _left=0;
unsigned char _right=0;
unsigned short x;
unsigned char led;
unsigned char position=1;
unsigned char counter=0;

void joy_s(){

x=ReadADC(0);
if(x>1000){
led=0x08;
_left=1;
}else if(x<400){
led=0x04;
_right=1;
}else{

led=0x00;
_right=0;
_left=0;
}
}

int main(void)
{
DDRA=0x00;PORTA=0xFF;
DDRB=0xFF;PORTB=0x00;

TimerSet(1);
TimerOn();
ADC_init();

    /* Replace with your application code */
    while (1)
    {


joy_s();
if(_left&&position==1){

}else if(_left&&position>1){
position=position -1;

}else if(_right&&position==4){
}
else if(_right&&position>=1){
position=position+1;
}else{
}

if(position==1){
led=0x01;
}else if(position==2){
led=0x02;
}else if(position==3){
led=0x04;
}else {
led=0x08;
}

PORTB=led;
while(!TimerFlag);
TimerFlag=0;

    }

}
