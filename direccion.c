/************************************************************************************************
*************************************************************************************************
*	 Raul Perez Arcones                                                              
*	 Proyecto Sistemas Empotrados                                                              
*	 MNTEy                                                                                   
*************************************************************************************************
*************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

#include "PWM.h"


#define SERVO_IZQ 	23		//gpio wiringpi
#define SERVO_DCH 	1		//gpio wiringpi

#define PWM_RANG  2490
#define PWM_DIVI  160
#define PWM_DIVI_X  2

#define DIREC_VMAX		39			//Velocidad maxima
#define DIREC_VMED		20			//Velocidad de parada segun regulado el servo
#define DIREC_VMIN 		1			//velocidad minima (marcha atras)
#define DIREC_VDIF		 2			//aceleracion

/*************************************************************************************************/
//Parametros GLOBALES

int DIREC_velocidad=DIREC_VMED;

/*************************************************************************************************/
/**
  @brief invierte la direccion del segundo servo
  @param velocidad
  @returns velocidad simetrica
*/
int inverso(int velocidad){
	int veloc,diff;
	diff=DIREC_VMED-velocidad;
	veloc=DIREC_VMED+diff;
	return veloc;
}
/*************************************************************************************************/
/**
  @brief Configura los servos
  @param sin parametro
  @returns devuelve 0 si es correcto
*/
int dir_init(){
	
 	PWM_init(SERVO_IZQ);
 	PWM_init(SERVO_DCH);
	
	DIREC_velocidad=DIREC_VMED;

	PWM_velocidad(SERVO_DCH,DIREC_velocidad);
	PWM_velocidad(SERVO_IZQ,DIREC_velocidad);
	
	fprintf(stdout,"DIREC: Dirección configurada \n");

	return DIREC_velocidad-DIREC_VMED;
}
/*************************************************************************************************/
/**
  @brief Aumenta la velocidad de los servos
  @param sin parametro
  @returns velocidad actual
*/
int dir_avanza(){

	DIREC_velocidad+=DIREC_VDIF;

	if(DIREC_velocidad>DIREC_VMAX){
		DIREC_velocidad=DIREC_VMAX;
	}
	PWM_velocidad(SERVO_IZQ,DIREC_velocidad);
	PWM_velocidad(SERVO_DCH,inverso(DIREC_velocidad));

	return DIREC_velocidad-DIREC_VMED;
}
/*************************************************************************************************/
/**
  @brief Disminuye la velocidad de los servos
  @param sin parametro
  @returns velocidad actual
*/
int dir_frena(){
	DIREC_velocidad-=DIREC_VDIF;

	if(DIREC_velocidad<DIREC_VMIN){
		DIREC_velocidad=DIREC_VMIN;
	}
	PWM_velocidad(SERVO_IZQ,DIREC_velocidad);
	PWM_velocidad(SERVO_DCH,inverso(DIREC_velocidad));

	return DIREC_velocidad-DIREC_VMED;
}
/*************************************************************************************************/
/**
  @brief Detiene momentaneamente el servo contrario
  @param sin parametro
  @returns velocidad actual
*/
int dir_giraIzq(){

	PWM_velocidad(SERVO_IZQ,DIREC_VMED);
	PWM_velocidad(SERVO_DCH,inverso(DIREC_VMED+5));
	delay(500);
	PWM_velocidad(SERVO_IZQ,DIREC_velocidad);
	PWM_velocidad(SERVO_DCH,inverso(DIREC_velocidad));
	return DIREC_velocidad-DIREC_VMED;
}
/*************************************************************************************************/
/**
  @brief Detiene momentaneamente el servo contrario
  @param sin parametro
  @returns velocidad actual
*/
int dir_giraDch(){	
	PWM_velocidad(SERVO_IZQ,DIREC_VMED+5);
	PWM_velocidad(SERVO_DCH,inverso(DIREC_VMED));
	delay(500);
	PWM_velocidad(SERVO_IZQ,DIREC_velocidad);
	PWM_velocidad(SERVO_DCH,inverso(DIREC_velocidad));
	return DIREC_velocidad-DIREC_VMED;
}
/*************************************************************************************************/
/**
  @brief Detiene los los servos
  @param sin parametro
  @returns velocidad actual
*/
int dir_para(){	
	pwmWrite(SERVO_DCH,0);	
	pwmWrite(SERVO_IZQ,0);
	
	fprintf(stdout,"DIREC: Avanzando 0\n");	

	return 0;
}
/*************************************************************************************************/
/**
  @brief Comprueba el funcionamiento de la direccion
  @param sin parametro
  @returns velocidad actual
*/
int dir_test(){

	PWM_init(SERVO_IZQ);
 	PWM_init(SERVO_DCH);

	fprintf(stdout,"DIREC: Test Sevos parados velocidad = 0\n");	
	pwmWrite(SERVO_DCH,0);
	pwmWrite(SERVO_IZQ,0);
	delay(1000);

	fprintf(stdout,"DIREC: Test Servo DCH  ..............................\n");	

	fprintf(stdout,"DIREC: Servo D v =  1 \n");	
	pwmWrite(SERVO_DCH,1);
	delay(600);

	fprintf(stdout,"DIREC: Servo D v =  5 \n");	
	pwmWrite(SERVO_DCH,5);
	delay(600);

	fprintf(stdout,"DIREC: Servo D v = 10 \n");	
	pwmWrite(SERVO_DCH,10);
	delay(600);

	fprintf(stdout,"DIREC: Servo D v = 15 \n");	
	pwmWrite(SERVO_DCH,15);
	delay(600);

	fprintf(stdout,"DIREC: Servo D v = 20 \n");	
	pwmWrite(SERVO_DCH,20);
	delay(600);

	fprintf(stdout,"DIREC: Servo D v = 30 \n");	
	pwmWrite(SERVO_DCH,30);
	delay(600);

	fprintf(stdout,"DIREC: Servo D v = 0 \n");	
	pwmWrite(SERVO_DCH,0);
	delay(600);

	fprintf(stdout,"DIREC: Test Servo IZQ  ..............................\n");	

	fprintf(stdout,"DIREC: Servo I v =  1 \n");	
	pwmWrite(SERVO_IZQ,1);
	delay(600);

	fprintf(stdout,"DIREC: Servo I v =  5 \n");	
	pwmWrite(SERVO_IZQ,5);
	delay(600);

	fprintf(stdout,"DIREC: Servo I v = 10 \n");	
	pwmWrite(SERVO_IZQ,10);
	delay(600);

	fprintf(stdout,"DIREC: Servo I v = 15 \n");	
	pwmWrite(SERVO_IZQ,15);
	delay(600);

	fprintf(stdout,"DIREC: Servo I v = 20 \n");	
	pwmWrite(SERVO_IZQ,20);
	delay(600);

	fprintf(stdout,"DIREC: Servo I v = 30 \n");	
	pwmWrite(SERVO_IZQ,30);
	delay(600);

	fprintf(stdout,"DIREC: Servo I v = 0 \n");	
	pwmWrite(SERVO_IZQ,0);
	delay(600);

	return 0;
}				
				
