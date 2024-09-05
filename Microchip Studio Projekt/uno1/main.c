/*
* Florian Schäffer
* https://www.blafusel.de
*
* Make 3/2024
* Uno Debugger Demo
*/

#define F_CPU 16000000UL		//16 MHz Quarz

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t cnt = 0;		// volatile

ISR (INT0_vect)			// Interrupt Service Routine wird beiTastendruck aufgerufen
{
	cnt++;
}

int main(void)
{
	DDRB |= (1 << PINB4);			// Pin PB4 (12) im Richtungsregister auf 1 = Output
	DDRD &= ~(1 << PIND2);			// Pin PD2 (INT0) im Richtungsregister auf 0 = Input
	PORTD |= (1 << PIND2);			// Pull-Up fuer PD2 aktivieren
	EICRA |= (1 << ISC01);			// fallende Flanke loest IRQ aus, 1. Teil: ISC01=1
	EICRA &= ~(1 << ISC00);			// fallende Flanke loest IRQ aus, 2. Teil: ISC00=0
	EIMSK |= (1 << INT0);			// INT0 zulassen
	
	sei();	// Global Interrupt Enable
	
	while (1)
	{
		if (cnt >= 5)
			PORTB |= (1 << PINB4);		// PA1 LED HIGH (ein)
	}
	while(1);
	return(0);
}