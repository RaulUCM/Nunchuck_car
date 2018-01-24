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
#include <gertboard.h>
#include <wiringPiSPI.h>

#define SPI_BASE 100
#define SPI_CH_0 0
#define SPI_CH_1 1

/*************************************************************************************************/
//Parametros GLOBALES



/*************************************************************************************************/
/**
  @brief Inicialización del lector NFC
  @param sin entrada
  @returns estado inicial
*/
int  NFC_init(){
	//gertboardAnalogSetup(SPI_BASE);	
	fprintf(stdout,"NFC:  Configurado \n");
	return 0;
}
/*************************************************************************************************/
/**
  @brief Realiza una lectura del NFC
  @param sin entrada
  @returns dato leido
*/
int  NFC_lectura(){
	int dato;	
	dato=analogRead(SPI_BASE+SPI_CH_0);
	fprintf(stdout,"NFC: lectura %d \n",dato);
	return dato;
}
/*************************************************************************************************/
/**
  @brief Prueba de lectura del NFC
  @param sin entrada
  @returns dato leido
*/
int NFC_test(){
	int i,dato;
	
	fprintf(stdout,"NFC: test \n");

	for(i=0;i<100;i++){
		dato=analogRead(SPI_BASE+SPI_CH_0);
		fprintf(stdout,"NFC: lectura %d dato=%d \n",i,dato);
		delay(1000);
	}
	return dato;
}
/*************************************************************************************************/

		

		
