CC = gcc
CFLAGS = -Wall -g
LIBS= -lm -lwiringPi -lwiringPiDev -lpthread
FILES= main.o colaEventos.o fsm.o direccion.o PWM.o Nunchuck.o NFC_lector.o Timer_event.o Timer.o Mando.o Parse.o
PR=z_Proy

$(PR) : $(FILES)
	$(CC) $(CFLAGS) -o $(PR) $(FILES) $(LIBS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm *.o $(PR)



