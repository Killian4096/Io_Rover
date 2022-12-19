#ifndef USART_H_
#define USART_H_
#include <stdint.h>


void USART_Init(void);
uint8_t USART_Receive(void);
void USART_Transmit(uint8_t data);

#endif