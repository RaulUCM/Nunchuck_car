/************************************************************************************************
*************************************************************************************************
*	 Raul Perez Arcones                                                                      
*	 Proyecto Sistemas Empotrados                                                              
*	 MNTEy                                                                                      
*************************************************************************************************
*************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wiringPi.h>
#include <pthread.h>

#include "fsm.h"
#include "Nunchuck.h"
#include "direccion.h"
#include "NFC_lector.h"
#include "Timer_event.h"
#include "Mando.h"
#include "Parse.h"

#define PATH_FILE_IN     "Files_IN/"		//Carpeta con los ficheros de entrada y configuracion
#define PATH_FILE_OUT "Files_OUT/"	//Carpeta con los ficheros de salida  y logs
/*************************************************************************************************/
//Parametros GLOBALES
char MAIN_ruta_in []="Files_IN/";
/*************************************************************************************************/
/**
  @brief Main de ejecucion de la FSM

  @param argc puede recibir como argumento el fichero con un recorrido programado
  @returns genera una ejecución continua
*/
int main(int argc, char *argv[]) {
	
	char f_ruta [30] ;
	
	if ( argc > 2 ){ 
		fprintf(stdout,"MAIN: Parametros ignorados \n" );
	}
	if ( argc > 1 ){ 
		strcpy(f_ruta, PATH_FILE_IN);			
		strcat(f_ruta, argv[1]);	
	
		fprintf(stdout,"MAIN: Fichero con ruta programda %s \n",f_ruta);	
		Parse_file(f_ruta);
	}
	
	//inicializar wiringPi
	wiringPiSetup(); 
	
/*************************************************************************************************/
//Pruebas
	fprintf(stdout,"MAIN: Testing.....\n");
//	NFC_test();
	dir_test();
	Nunchuck_test();
	fprintf(stdout,"MAIN: Testing..... OK \n");
/*************************************************************************************************/	
	delay(1000);	
	pthread_t th1, th2;		
	
	//generamos hilo de eventos temporales
	pthread_create(&th1,NULL, timer_event,(void*)NULL);
	fprintf(stdout,"MAIN: Invoco Hilo evento temporal\n");

	pthread_create(&th2,NULL, mando_event,(void*)NULL);
	fprintf(stdout,"MAIN: Invoco Hilo control remoto\n");

	//hilo principal de la FSM
	fprintf(stdout,"MAIN: Invoco FSM\n");
	fsm();
	fprintf(stdout,"MAIN: Fin de la FSM!. Salimos\n");	
	
	return 0;
}
