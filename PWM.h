#ifndef _SERVO_PWM_H
#define _SERVO_PWM_H


int PWM_init(int pin);
int PWM_rango(int range);
int PWM_divisor(int divisor);

int PWM_pulso(int pin, int angulo);
int PWM_velocidad(int pin, int velocidad);

int PWM_on(int pin);
int PWM_off(int pin);


#endif


