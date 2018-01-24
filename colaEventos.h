#ifndef _COLAEVENTOS_H
#define _COLAEVENTOS_H

typedef enum {AVANZA,FRENA,GIRA_IZQ,GIRA_DCH,BLOQUEA,TIMER,FINALIZA,NUM_EVENTOS} evento_t;

void initColaEventos();

evento_t extraeEvento();
void encolaEvento(evento_t ev);

#endif
