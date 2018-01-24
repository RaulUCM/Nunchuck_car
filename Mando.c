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

#include "Nunchuck.h"
#include "colaEventos.h"

#define MAN_JX 0x7d
#define MAN_JY 0x71
#define MAN_M  0x50
#define MAN_BC 0
/*************************************************************************************************/
//Parametros GLOBALES


/*************************************************************************************************/
/**
  @brief detiene la ejecucion de la FSM
  @param evento señal que recibe
  @returns 0 si es correcto
*/
void* mando_event(void* arg){
	
	int x,y,c;
	Nunchuck_init();
	
	while(1){

		Nunchuck_lectura();

		x=Nunchuck_JoyStick_X();
		y=Nunchuck_JoyStick_Y();
		c=Nunchuck_Botton_c();	
		
		//fprintf(stdout,"MANDO: X leido %x\n",x); 
		//fprintf(stdout,"MANDO: Y leido %x\n",y); 
		//fprintf(stdout,"MANDO: C leido %d\n",c); 		

		
		if(c == MAN_BC){
			encolaEvento(BLOQUEA);		
			fprintf(stdout,"MANDO: Accion detectada %s\n","BLOQUEA"); 
		};

		if(x < MAN_JX - MAN_M){
			encolaEvento(GIRA_IZQ);		
			fprintf(stdout,"MANDO: Accion detectada %s\n","Gira Izquierda"); 
		}else if(x > MAN_JX + MAN_M){
			encolaEvento(GIRA_DCH);		
			fprintf(stdout,"MANDO: Accion detectada %s\n","Gira Derecha"); 
		}

		if(y > MAN_JY + MAN_M){
			encolaEvento(AVANZA);		
			fprintf(stdout,"MANDO: Accion detectada %s\n","AVANZA"); 
		}else if(y < MAN_JY - MAN_M){
			encolaEvento(FRENA);		
			fprintf(stdout,"MANDO: Accion detectada %s\n","FRENA"); 
		}

		sleep(1);
	}

	return 0;
}
