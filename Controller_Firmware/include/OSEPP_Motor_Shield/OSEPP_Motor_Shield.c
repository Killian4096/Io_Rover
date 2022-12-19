#include <avr/io.h>
#include <stdint.h>
#include <config.h>
#include "OSEPP_Motor_Shield.h"

/*
TODO:
Testing
Servos

*/


void OSEPP_Motor_Shield_Init(){
    //SHIFTER

    //Set shift register pins to output
    DDRD |= (1<<DDD7) | (1<<DDD4);
    DDRB |= (1<<DDB4) | (1<<DDB0);

    OSEPP_Motor_Shield_Set_Direction(0,0);

    //SPEED

    //Enable pwm2 pins for left
    DDRB |= (1<<DDB3);
    DDRD |= (1<<DDD3);

    //Enable pwm0 pins for right
    DDRD |= (1<<DDD6) | (1<<DDD5);

    //Set pwm mode to clear on compare and fast pwm mode 3, no prescale
    TCCR2A |= (1<<COM2A1) | (1<<COM2B1) | (1<<WGM21) | (1<<WGM20);
    TCCR2B |= (1<<CS20);


    TCCR0A |= (1<<COM0A1) | (1<<COM0B1) | (1<<WGM01) | (1<<WGM00);
    TCCR0B |= (1<<CS00);

    //Set speed to 0
    OSEPP_Motor_Shield_Set_Speed(127,127);

    //SERVOS

    //Set pins to output
    DDRB |= (1<<DDB2) | (1<<DDB1);


    //Set pwm mode to clear on compare and fast pwm mode 7, 256 prescale
    TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11);
    TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
    ICR1 = 4999;

    //Set Init direction
    OSEPP_Motor_Shield_Set_Servo(127, 127);

    return;
}

static void OSEPP_Motor_Shield_Load_Shifter(uint8_t value){
    value = value > 0;

    //Load Value
    PORTB |= (value << PORTB0);

    //Tick Loader
    PORTD |= (1<<PORTD4);

    //Clear
    PORTD &= ~(1<<PORTD4);
    PORTB &= ~(1<<PORTB0);
}

void OSEPP_Motor_Shield_Set_Direction(uint8_t left_direction, uint8_t right_direction){
    //0 = brake, 1 = forward, 2=reverse
    
    //11 DIR_CLK -> SHCP shifts on clock tick
    //12 DIR_LATCH -> STCP moves from shift to output
    //13 DIR_EN -> OE resets when pulled high, pull low to do stuff????
    //14 DIR_SER -> INPUT, when DIR_CLK tick read value

    //Arduino
    // 12 -> DIR_LATCH -> PB4
    // 8  -> DIR_SER -> PB0
    // 7  -> DIR_EN -> PD7
    // 4  -> DIR_CLK -> PD4

    //1 and 2 forward, 3 and 4 reversed

    //Load Shift Register
    OSEPP_Motor_Shield_Load_Shifter(right_direction==2); //M4B
    OSEPP_Motor_Shield_Load_Shifter(right_direction==1); //M3B
    OSEPP_Motor_Shield_Load_Shifter(right_direction==1); //M4A
    OSEPP_Motor_Shield_Load_Shifter( left_direction==1); //M2B
    OSEPP_Motor_Shield_Load_Shifter( left_direction==2); //M1B
    OSEPP_Motor_Shield_Load_Shifter( left_direction==1); //M1A
    OSEPP_Motor_Shield_Load_Shifter( left_direction==2); //M2A
    OSEPP_Motor_Shield_Load_Shifter(right_direction==2); //M3A

    //Tick output
    PORTB |= (1<<PORTB4);
    PORTB &= ~(1<<PORTB4);





    return;
}

void OSEPP_Motor_Shield_Set_Speed(uint8_t left_speed, uint8_t right_speed){
    //Set left speed
    OCR2A = left_speed;
    OCR2B = left_speed;

    //Set right speed
    OCR0A = right_speed;
    OCR0B = right_speed;
}

void OSEPP_Motor_Shield_Set_Servo(uint8_t servo1, uint8_t servo2){
    uint16_t servo1_c = SERVO_1_MIN_PWM + ((SERVO_1_MAX_PWM - SERVO_1_MIN_PWM) * (servo1/256.0));
    uint16_t servo2_c = SERVO_2_MIN_PWM + ((SERVO_2_MAX_PWM - SERVO_2_MIN_PWM) * (servo2/256.0));
    OCR1B = servo1_c;
    OCR1A = servo2_c;
}