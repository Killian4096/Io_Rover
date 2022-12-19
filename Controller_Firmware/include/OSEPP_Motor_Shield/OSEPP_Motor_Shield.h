#ifndef OSEPP_MOTOR_SHIELD_H_
#define OSEPP_MOTOR_SHIELD_H_
#include <stdint.h>
void OSEPP_Motor_Shield_Init(void);
void OSEPP_Motor_Shield_Set_Direction(uint8_t left_direction, uint8_t right_direction);
void OSEPP_Motor_Shield_Set_Speed(uint8_t left_speed, uint8_t right_speed);
void OSEPP_Motor_Shield_Set_Servo(uint8_t servo1, uint8_t servo2);

#endif