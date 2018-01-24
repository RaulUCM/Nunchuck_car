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

#include "colaEventos.h"

#define P_A	65  //ASCII
#define P_F	70
#define P_D	68
#define P_I	73

/*************************************************************************************************/
//Parametros GLOBALES


/*************************************************************************************************/
/**
  @brief detiene la ejecucion de la FSM
  @param evento señal que recibe
  @returns 0 si es correcto
*/
 int lee_caracter(FILE *fichero) {	
 	int buffer;
	buffer=fgetc(fichero); // Se lee un caracter	 
	//fprintf(stdout,"PARSE: leido caracter:%c\n",buffer); 
	return buffer;
 }
/*************************************************************************************************/
/**
  @brief detiene la ejecucion de la FSM
  @param evento señal que recibe
  @returns 0 si es correcto
*/
int Parse_actua(int comando){
//{AVANZA,FRENA,GIRA_IZQ,GIRA_DCH,BLOQUEA,TIMER,NUM_EVENTOS} 
			switch (comando) {
			case P_A:
				encolaEvento(AVANZA);
				fprintf(stdout,"PARSE: Accion programada %s\n","AVANZA"); 	
				break;	
			case P_F:
				encolaEvento(FRENA);		
				fprintf(stdout,"PARSE: Accion programada %s\n","FRENA"); 		
				break;	
			case P_I:
				encolaEvento(GIRA_IZQ);	
				fprintf(stdout,"PARSE: Accion programada %s\n","Gira Izquierda"); 
				break;
			case P_D:
				encolaEvento(GIRA_DCH);		
				fprintf(stdout,"PARSE: Accion programada %s\n","Gira Derecha"); 		
				break;
			default:				
				break;			
		}
	return comando;
}
/*************************************************************************************************/
/**
  @brief detiene la ejecucion de la FSM
  @param evento señal que recibe
  @returns 0 si es correcto
*/
int Parse_file(char nfichero []){
	
	int palabra; 
	FILE* fichero;
	int estado=0;
	fichero=fopen (nfichero, "r");
	
	if(fichero==NULL) {
		estado=-1;
		fprintf(stdout,"PARSE: no encontrado fichero %s\n",nfichero); 
	}else{

		fprintf(stdout,"PARSE: inicio lectura fichero %s\n",nfichero); 	
		 while (feof(fichero)==0) {
				fprintf(stdout,"PARSE: continua lectura fichero %s\n",nfichero); 
	 			palabra=lee_caracter(fichero); // lee una palabra
	 			fprintf(stdout,"PARSE: leido comando: %d\n",palabra); 
				Parse_actua(palabra);
	 	}
 		fclose(fichero);
		fprintf(stdout,"PARSE: fin lectura fichero %s\n",nfichero); 	
	}
	return estado;
}
/*************************************************************************************************/



