#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void GPIO_init() {
  DDRB |= (1 << DDB5);
}

void GPIO_toggle() {
  PORTB ^= (1 << PORTB5);
}

void setup() {
  GPIO_init();
}

void loop() {
  GPIO_toggle();
 _delay_ms(1000);
}