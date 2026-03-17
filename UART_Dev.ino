#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define BAUD 9600
#define UBRR_VALUE 103

void UART_init()
{
  UBRR0H = (unsigned char)(UBRR_VALUE >> 8);
  UBRR0L = (unsigned char)UBRR_VALUE;
  UCSR0B = (1 << TXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART_transmit(char data) {
  
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}

void UART_sendString(const char *str) {
    while (*str) {
      UART_transmit(*str++);
    }
}

void setup() {
  UART_init();
}

void loop() {
  UART_sendString("Hello from UART\r\n");
   _delay_ms(1000);
}