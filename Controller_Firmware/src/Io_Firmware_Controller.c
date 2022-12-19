#include <avr/io.h>
#include "OSEPP_Motor_Shield.h"
#include <util/delay.h>
#include "USART.h"

void main(void){
    OSEPP_Motor_Shield_Init();
    USART_Init();
    while(1){
        while(USART_Receive() != 0xFF);
        uint8_t directions  = USART_Receive();
        uint8_t left_speed  = USART_Receive();
        uint8_t right_speed = USART_Receive();
        uint8_t servo_1 = USART_Receive();
        uint8_t servo_2 = USART_Receive();
        OSEPP_Motor_Shield_Set_Direction(2 - ((directions & 0x02) > 0),2 - ((directions & 0x01) > 0));
        OSEPP_Motor_Shield_Set_Speed(left_speed,right_speed);
        OSEPP_Motor_Shield_Set_Servo(servo_1, servo_2);
    }
    while(1);
}