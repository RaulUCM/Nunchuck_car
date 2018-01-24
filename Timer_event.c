/************************************************************************************************
*************************************************************************************************
*	 Raul Perez Arcones                                                                      
*	 Proyecto Sistemas Empotrados                                                              
*	 MNTEy                                                                                      
*************************************************************************************************
*************************************************************************************************/
#include <unistd.h>
#include <stdio.h>

#include "Timer.h"

/*************************************************************************************************/
/**
  @brief  Invoca la estructura del timer
  @param arg vacio
  @returns 
*/
void* timer_event(void* arg){
	timer_init(2);  //genera un evento cada segundo 
	timer_init(5);  //genera un evento cada 5 segundos
	timer_init(7);  //genera un evento cada 7 segundos
	
	timer();

	return 0;
}
/*************************************************************************************************/
