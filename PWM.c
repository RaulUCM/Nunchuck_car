/************************************************************************************************
*************************************************************************************************
*	 Raul Perez Arcones                                                              
*	 Proyecto Sistemas Empotrados                                                              
*	 MNTEy                                                                                   
*************************************************************************************************
*************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
//#include <softPwm.h>

#define FREQ_HZ     19200000  //f Rasberry 19.2MHz

#define PWM_DIVI 160
#define PWM_RANG   2490
#define ANGULO_REF  90


/*************************************************************************************************/
//Parametros GLOBALES

//gpio mode 1 pwm
//gpio pwm-ms
//gpio pwmc 160
//gpio pwmr 2490
//gpio pwm 1 90


/*************************************************************************************************/
/**
  @brief Modifica el rango del PWM de los servos
  @param rango a establecer
  @returns devuelve el rango
*/
int PWM_rango(int range){
	pwmSetRange(range);
	return 0;
}
/*************************************************************************************************/
/**
  @brief Modifica el divisor del PWM de los servos
  @param divisor a establecer
  @returns devuelve el divisor
*/
int PWM_divisor(int divisor){
	pwmSetClock(divisor);
	return divisor;
}
/*************************************************************************************************/
/**
  @brief Configura los servos
  @param sin parametro
  @returns devuelve 0 si es correcto
*/
int PWM_init(int pin){
	//printf("Configurando servo PWM:\n"

	pinMode(pin,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(PWM_DIVI);
	pwmSetRange(PWM_RANG); 

	fprintf(stdout,"SERVO: rango (%d) y divisor (%d) inicializado\n",PWM_RANG,PWM_DIVI);
	return 0;
}
/*************************************************************************************************/
/**
  @brief Configura los servos
  @param sin parametro
  @returns devuelve 0 si es correcto
*/
int PWM_pulso(int pin, int angulo){
	int val = angulo + ANGULO_REF;
	int range = PWM_RANG + val;
	//printf("Moviendo el motor en GP %d a %dº con Range %d y val %d\n", pin, angulo, range, val);
	pwmSetRange(range); 
	pwmWrite(pin,val+ANGULO_REF);
	return 0;
}
/*************************************************************************************************/
/**
  @brief Configura el duty de los servos 
  @param pin sobre el que actua
  @param aumenta el dutty del PWM
  @returns devuelve la velocidad
*/
int PWM_velocidad(int pin, int velocidad){
	pwmWrite(pin,velocidad);
	return velocidad;
}
/*************************************************************************************************/
/**
  @brief Activa la salida pwm para el pin
  @param pin sobre el que actua
  @returns devuelve 0 si es correcto
*/
int  PWM_on(int pin){	
	pinMode(pin,PWM_OUTPUT);
	return 0;
}
/*************************************************************************************************/
/**
  @brief desactiva la salida pwm para el pin
  @param pin sobre el que actua
  @returns devuelve 0 si es correcto
*/
int PWM_off(int pin){	
	pinMode(pin,OUTPUT);
	return 0;
}
/*************************************************************************************************/


