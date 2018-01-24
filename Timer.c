/************************************************************************************************
*************************************************************************************************
*	 Raul Perez Arcones                                                                      
*	 Proyecto Sistemas Empotrados                                                              
*	 MNTEy                                                                                      
*************************************************************************************************
*************************************************************************************************/
#include <unistd.h>
#include <stdio.h>

#include "colaEventos.h"

#define TIMERS_MAX 100

/*************************************************************************************************/
//Parametros GLOBALES
int TIMER_timers[TIMERS_MAX];  
int TIMER_numero=0;
int TIMER_numero_max=0;
/*************************************************************************************************/
/**
  @brief  genera un nuevo evento temporal
  @param arg vacio
  @returns numero de timers
*/
int timer_init(int t){
	
	if (t<TIMERS_MAX){	
		TIMER_timers[TIMER_numero]=t;
		TIMER_numero+=1;
		if(TIMER_numero_max<t){
			TIMER_numero_max=t;
		}
		fprintf(stdout,"TIMER: evento cada %d seg configurado \n",t);
	}else {
		fprintf(stdout,"TIMER: evento cada %d seg ignorado \n",t);
	}

	return TIMER_numero;
}
/*************************************************************************************************/
/**
  @brief  Invoca la estructura del timer
  @param arg vacio
  @returns 
*/
int timer(){
	int cont=0;
	int i;	
	int flag;  //se activa si se ha generado ya evento en la iteracion
	while(1){			
		cont=(cont+1)%TIMER_numero_max;
		flag=0;
		for(i=0; i<TIMER_numero;i++){

			if(cont%TIMER_timers[i]==0 && flag==0){
				encolaEvento(TIMER);
				flag=1;
				//fprintf(stdout,"TIMER: encola evento %d\n",TIMER_timers[i]);			
			}
		}
		sleep(1);
		
	}
}



