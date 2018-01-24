#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

#include "colaEventos.h"

//// VARIABLES DE ESTE MODULO
#define MAX_EVENTOS 10

static evento_t buffer[MAX_EVENTOS];
static pthread_mutex_t mutex;
static pthread_cond_t hayElemento;
static pthread_cond_t hayHueco;
static int n_elementos;
static int posC;
static int posP;

//////
void initColaEventos() {
	posC = 0;
	posP = 0;
	n_elementos=0;
	pthread_mutex_init(&mutex,NULL); 
  	pthread_cond_init(&hayElemento,NULL); 
  	pthread_cond_init(&hayHueco,NULL); 
}

// Funcion bloqueante: si hay un evento en la cola, 
// se entrega ese evento y se saca de la cola. 
//Si no hay, se queda bloqueada hasta que llegue uno
evento_t extraeEvento() {
	evento_t evento;
 	pthread_mutex_lock(&mutex);    /* acceder al buffer */
 
	//si buffer vacio esperamos	hasta que se encole un nuevo elemento
	while (n_elementos==0) {
		pthread_cond_wait(&hayElemento, &mutex); 
	}
	
	evento = buffer[posC];
	//printf("extrae EVENTO: %d \n",evento);
	posC = (posC+1)%MAX_EVENTOS;
	n_elementos--;
	pthread_cond_signal(&hayHueco);   /* buffer no lleno */ 
	//printf("DONE\n");
	pthread_mutex_unlock(&mutex);
	return evento;
}

void encolaEvento(evento_t evento) {
	
	//acceder al buffer
	pthread_mutex_lock(&mutex);       				  
	
	//si buffer lleno esperamos
	while (n_elementos==MAX_EVENTOS) { 			
           	pthread_cond_wait(&hayHueco, &mutex); 	
	}
	
	//printf("Encolando EVENTO: %d \n",evento);
    buffer[posP]=evento;
	posP=(posP+1)%MAX_EVENTOS;
	n_elementos++;
	pthread_cond_signal(&hayElemento); //enviamos señal de evento
	
	//printf("DONE \n");
	pthread_mutex_unlock(&mutex);
}
