#ifndef _FSM_H
#define _FSM_H

//Parametria configurable

//Fichero de log de la FSM
//#define LOG_FSM FSM_log.txt

typedef enum {INICIO,BLOQUEO,FIN,NUM_ESTADOS} estados_t;


int fsm();

#endif
