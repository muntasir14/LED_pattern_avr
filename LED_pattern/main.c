/*
 * LED_pattern.c
 *
 * Created: 8/18/2024 10:03:26 AM
 * Author : muntasir
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

uint8_t keypad[4][4] = {{1, 2, 3, 10},
						{4, 5, 6, 11},
						{7, 8, 9, 12},
						{14, 0, 15, 13}};
							
uint8_t getKeyPressed() {
	DDRB = 0x0F;
	PORTB = 0xF0;
	DDRC = 0x0F;
	
	for(uint8_t row = 0; row < 4; row++) {
		PORTB = ~(1 << row);
		_delay_ms(20);
		for(uint8_t col = 0; col < 4; col++) {
			if(!(PINB & (1 << (col + 4)))) {
				return keypad[row][col];
			}
		}
	}
	return 0;
}

int main(void)
{
	DDRC = 0xFF;
	PORTC = 0x00;
	
	uint8_t key;
	
	
	while(1) {
		key = getKeyPressed();
		if(key != 0) {
			PORTC = key;
		}
		_delay_ms(100);
	}
	
}

