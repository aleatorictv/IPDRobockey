#include "helpers.h"
#include "CONFIG.h"
#include "puckfinding.h"

int puckState;
int lastPuck;
int hasPuck =0;
int front = 1;
int nearFront = 2;
int left = 3;
int right = 4;
int behind = 5;

int sensors[8]={0,0,0,0,0,0,0,0};

char buff[100];

int findPuck(){
	puckState = 0;
	updateADC();
	return puckState;
}
void initADC(){
	//Enable input on F0-4
	m_disableJTAG();
	
	// VOLTAGE REFERENCE
	clear(ADMUX,REFS1);	// set 0,1 for Vcc
	set(ADMUX,REFS0);

	// ADC PRESCALER
	set(ADCSRA,ADPS2);	// most accurate between 50 and 200 kHz, set to 1,1,1 /128
	set(ADCSRA,ADPS1);	// 16MHz/128 = 125kHz
	set(ADCSRA,ADPS0);

	// INTERRUPTS
	set(ADCSRA,ADIE); // enable ADC interrupt
	sei(); // enable global interrupts
	
	//SET INPUT PINS
	clear(DDRF,0);
	clear(DDRF,1);
	clear(DDRF,4);
	clear(DDRF,5);
	clear(DDRF,6);
	clear(DDRD,6);
	clear(DDRD,4);
	clear(DDRD,7);
	
	//SET INPUT PINS
	clear(PORTF,0);
	clear(PORTF,1);
	clear(PORTF,4);
	clear(PORTF,5);
	clear(PORTF,6);
	clear(PORTD,6);
	clear(PORTD,4);
	clear(PORTD,7);
	
	// DISABLING DIGITAL INPUTS
	set(DIDR0,ADC0D);  // disable pin F0
	set(DIDR0,ADC1D); //F1
	set(DIDR0,ADC4D); //F4
	set(DIDR0,ADC5D); //F5
	set(DIDR0,ADC6D); //F6
	set(DIDR0,ADC7D); //F7
	set(DIDR2,ADC8D); //D4
	set(DIDR2,ADC9D); //D6
	set(DIDR2,ADC10D); //D7
	// TRIGGERING
	set(ADCSRA, ADATE); // in free-running state
}
void updateADC(){
	
	//run through 9 sensors in sequence and wait till all conversions are done 
	sensors[0] = checkF0();
	sensors[1] = checkF1();
	sensors[2] = checkF4();
	sensors[3] = checkF5();
	sensors[4] = checkF6();
	sensors[5] = checkF7();
	sensors[6] = checkD6();
	sensors[7] = checkD4();
	sensors[8] = checkD7();
	sprintf(buff,"LTRs: %d %d %d %d %d %d %d %d %d\n", sensors[0], sensors[1], sensors[2],sensors[3],sensors[4],sensors[5], sensors[6], sensors[7], sensors[8]);
	sendBuffer(buff);
	
}
int checkF0(){
	//PAUSE ADC to avoid interrupting interrupts
	clear(ADCSRA,ADEN);
	
	//check F0
	clear(ADCSRB,MUX5);
	clear(ADMUX,MUX2);
	clear(ADMUX,MUX1);
	clear(ADMUX, MUX0);

	//enable ADC subsystem
	set(ADCSRA,ADEN);//begin conversion
	set(ADCSRA,ADSC);

	//check if flag is set
	while(!check(ADCSRA,ADIF));
	return ADC;
}
int checkF1(){
	//PAUSE ADC to avoid interrupting interrupts
	clear(ADCSRA,ADEN);
	
	//check F1
    clear(ADCSRB,MUX5);
    clear(ADMUX,MUX2);
    clear(ADMUX,MUX1);
    set(ADMUX, MUX0);

	//enable ADC subsystem
	set(ADCSRA,ADEN);//begin conversion
	set(ADCSRA,ADSC);

	//check if flag is set
	while(!check(ADCSRA,ADIF));
	return ADC;
}
int checkF4(){
	//PAUSE ADC to avoid interrupting interrupts
	clear(ADCSRA,ADEN);
	
	//check F4
	clear(ADCSRB,MUX5);
	set(ADMUX,MUX2);
	clear(ADMUX,MUX1);
	clear(ADMUX, MUX0);

	//enable ADC subsystem
	set(ADCSRA,ADEN);//begin conversion
	set(ADCSRA,ADSC);

	//check if flag is set
	while(!check(ADCSRA,ADIF));
	return ADC;
}
int checkF5(){
	//PAUSE ADC to avoid interrupting interrupts
	clear(ADCSRA,ADEN);
	
	//check F5
	clear(ADCSRB,MUX5);
	set(ADMUX,MUX2);
	clear(ADMUX,MUX1);
	set(ADMUX, MUX0);

	//enable ADC subsystem
	set(ADCSRA,ADEN);//begin conversion
	set(ADCSRA,ADSC);

	//check if flag is set
	while(!check(ADCSRA,ADIF));
	return ADC;
}
int checkF6(){
	//PAUSE ADC to avoid interrupting interrupts
	clear(ADCSRA,ADEN);
	
	//check F6
	clear(ADCSRB,MUX5);
	set(ADMUX,MUX2);
	set(ADMUX,MUX1);
	clear(ADMUX, MUX0);

	//enable ADC subsystem
	set(ADCSRA,ADEN);//begin conversion
	set(ADCSRA,ADSC);

	//check if flag is set
	while(!check(ADCSRA,ADIF));
	return ADC;
}
int checkF7(){
	//PAUSE ADC to avoid interrupting interrupts
	clear(ADCSRA,ADEN);
	
	//check F7
	clear(ADCSRB,MUX5);
	set(ADMUX,MUX2);
	set(ADMUX,MUX1);
	set(ADMUX, MUX0);

	//enable ADC subsystem
	set(ADCSRA,ADEN);//begin conversion
	set(ADCSRA,ADSC);

	//check if flag is set
	while(!check(ADCSRA,ADIF));
	return ADC;
}
int checkD4(){
	//PAUSE ADC to avoid interrupting interrupts
	clear(ADCSRA,ADEN);
	
	//check D4
	set(ADCSRB,MUX5);
	clear(ADMUX,MUX2);
	clear(ADMUX,MUX1);
	clear(ADMUX, MUX0);

	//enable ADC subsystem
	set(ADCSRA,ADEN);//begin conversion
	set(ADCSRA,ADSC);

	//check if flag is set
	while(!check(ADCSRA,ADIF));
	return ADC;
}
int checkD6(){
	//PAUSE ADC to avoid interrupting interrupts
	clear(ADCSRA,ADEN);
	
	//check D6
	set(ADCSRB,MUX5);
	clear(ADMUX,MUX2);
	clear(ADMUX,MUX1);
	set(ADMUX, MUX0);

	//enable ADC subsystem
	set(ADCSRA,ADEN);//begin conversion
	set(ADCSRA,ADSC);

	//check if flag is set
	while(!check(ADCSRA,ADIF));
	return ADC;
}
int checkD7(){
	//PAUSE ADC to avoid interrupting interrupts
	clear(ADCSRA,ADEN);
	
	//check F0
	set(ADCSRB,MUX5);
	clear(ADMUX,MUX2);
	set(ADMUX,MUX1);
	clear(ADMUX, MUX0);

	//enable ADC subsystem
	set(ADCSRA,ADEN);//begin conversion
	set(ADCSRA,ADSC);

	//check if flag is set
	while(!check(ADCSRA,ADIF));
	return ADC;
}
