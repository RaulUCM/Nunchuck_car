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
#include <math.h>
#include <wiringPi.h>

#include "fsm.h"
#include "colaEventos.h"
#include "direccion.h"

/*************************************************************************************************/
//Parametros GLOBALES

int FSM_fin=0;  

/*************************************************************************************************/
/**
  @brief Inicialización de la FSM
  @param sin entrada
  @returns estado inicial
*/
estados_t init_FSM() {
	
	estados_t estado;


	fprintf(stdout,"FSM: INICIALIAZANDO Maquina de estados\n");
	dir_init();	
	fprintf(stdout,"FSM: Maquina de estados INICIALIZADA\n");
		
	//Incializamos Parametros

	estado=INICIO;	
	FSM_fin=0;
	
	return estado;	
}
/*************************************************************************************************/
/**
  @brief detiene la ejecucion de la FSM
  @param evento señal que recibe
  @returns 0 si es correcto
*/
int estado_timer(){
	fprintf(stdout,"FSM: evento temporal \n");
	return 0;
}
/*************************************************************************************************/
/**
  @brief detiene la ejecucion de la FSM
  @param evento señal que recibe
  @returns evento siguiente
*/
estados_t estado_inicio(evento_t evento){
	
	estados_t estado;
	
		switch (evento) {
			case AVANZA:
					dir_avanza();
					fprintf(stdout,"FSM: Avanza\n");
					estado=INICIO;			
				break;	
			case FRENA:
					dir_frena();
					fprintf(stdout,"FSM: Frena\n");
					estado=INICIO;			
				break;	
			case GIRA_IZQ:
					dir_giraIzq();
					fprintf(stdout,"FSM: Gira IZQ\n");
					estado=INICIO;
				break;
			case GIRA_DCH:
					dir_giraDch();
					fprintf(stdout,"FSM: Gira DCH\n");
					estado=INICIO;			
				break;
			case BLOQUEA:
					dir_para();
					fprintf(stdout,"FSM: BLOQUEADO\n");
					estado=BLOQUEO;			
				break;	
			case TIMER:
					estado_timer();
					estado=INICIO;
				break;
			case FINALIZA:
					estado_timer();
					estado=INICIO;
				break;
			default:
					estado=INICIO;
				break;			
		}
				
	return estado;
}

/*************************************************************************************************/
/**
  @brief ignora la llegada de eventos a la FSM salvo el BLOQUEA
  @param evento señal que recibe
  @returns estado siguiente
*/
estados_t estado_bloqueo(evento_t evento){
	
	estados_t estado;
		
	//solo atendera el evento de desbloqueo
	if(evento==BLOQUEA){
		estado=INICIO;
	}else{
		estado=BLOQUEO;
	}		
	
	return estado;
}
/*************************************************************************************************/
/**
  @brief detiene la ejecucion de la FSM
  @param evento señal que recibe
  @returns 0 si es correcto
*/
estados_t estado_fin(evento_t evento){
	estados_t estado;
	FSM_fin=1;
	estado=FIN;
	dir_para();
	fprintf(stdout,"FSM: finaliza bucle\n");
	return estado;
}

/*************************************************************************************************/
/**
  @brief bucle de la FSM
  @param sin entrada
  @returns 0 si es correcto
*/
int fsm() {
	
	evento_t evento;
	estados_t estadoActual;
	estadoActual=init_FSM();	
	
	fprintf(stdout,"FSM: comienza bucle\n");		
	
	while (FSM_fin==0) {
	//while (1) {
		evento = extraeEvento(); // Si no hay evento se queda a la espera
			
		switch (estadoActual) {			
			case INICIO:
				estadoActual=estado_inicio(evento);
				break;
			case BLOQUEO:
				estadoActual=estado_bloqueo(evento);
				break;
			case FIN:
				estadoActual=estado_fin(evento);
				break;
			default:
				fprintf(stdout,"FSM: Estado Desconocido\n");
				break;
		}//switch
	}//while
	return 0;
}//fsm
/*************************************************************************************************/
