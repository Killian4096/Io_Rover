#include <avr/io.h>
#include <stdint.h>
#include <config.h>
#include <USART.h>


void USART_Init(void){
    //Set Baud Rate, put something here
    UBRR0H |= (uint8_t)(BAUD_FACTOR>>8);
    UBRR0L |= (uint8_t)(BAUD_FACTOR);

    //Enable Transmitter and Receiver
    UCSR0B |= (1<<TXEN0) | (1<<RXEN0);

    //Set frame format: 8data, 2 stop bit
    UCSR0C |= (1<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00);

    //Look at UCSRnC datasheet
}

uint8_t USART_Receive(void){
    while(!(UCSR0A & (1<<RXC0)));

    return UDR0;
}

void USART_Transmit(uint8_t data){
    //Wait for transmit to finish
    while(!(UCSR0A & (1<<UDRE0)));

    //Put data into buffer
    UDR0 = data;
}