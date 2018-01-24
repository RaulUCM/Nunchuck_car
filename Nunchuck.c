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
#include <wiringPi.h>
#include <wiringPiI2C.h>


#define NUNCHUCK_DIR 	0x52	//dir I2C dispositivo

#define NCK_R_CFG 	0x40	
#define NCK_D_CFG 	0x00

#define NCK_JS_X	0x00
#define NCK_JS_Y	0x01
#define NCK_AC_X	0x02	//8bits <<2
#define NCK_AC_Y	0x03	//8bits <<2
#define NCK_AC_Z	0x04	//8bits <<2
#define NCK_BOTN	0x05	//accZ accY accX c-button z-button

#define NCK_B_C		0x02
#define NCK_B_z		0x01
#define NCK_CODE	0x17

/*************************************************************************************************/
//Parametros GLOBALES
int NCK_fd=0;		//Identificador del canal I2C

int NCK_joyX = 0;
int NCK_joyY = 0;
int NCK_accX = 0;
int NCK_accY = 0;
int NCK_accZ = 0;
int NCK_c = 0;
int NCK_z = 0;

/*************************************************************************************************/
/**
  @brief inicia la conexion I2C del dispositivo
  @param ninguno
  @returns identificador del dispositivo
*/
int Nunchuck_init(){
	

	NCK_fd = wiringPiI2CSetup(NUNCHUCK_DIR);
	if (NCK_fd < 0) {
		fprintf(stdout,"NUNCHUCK: No Configurado %d\n",NCK_fd);
	}
    	wiringPiI2CWriteReg8(NCK_fd, NCK_R_CFG, NCK_D_CFG);
    	delayMicroseconds(500);
	
	NCK_joyX = 0;
	NCK_joyY = 0;
	NCK_accX = 0;
	NCK_accY = 0;
	NCK_accZ = 0;
	NCK_c = 0;
	NCK_z = 0;

	fprintf(stdout,"NUNCHUCK: Configurado %d\n",NCK_fd);

	return NCK_fd;
}

/*************************************************************************************************/
/**
  @brief devuelve el valor del JoyStick eje X
  @returns valor del registro
*/
int Nunchuck_JoyStick_X(){ return NCK_joyX;}
/*************************************************************************************************/
/**
  @brief devuelve el valor del JoyStick eje Y
  @returns valor del registro
*/
int Nunchuck_JoyStick_Y(){ return NCK_joyY;}
/*************************************************************************************************/
/**
  @brief devuelve el valor del Boton C
  @returns valor del registro
*/
int Nunchuck_Botton_c(){ return NCK_c;}
/*************************************************************************************************/
/**
  @brief devuelve el valor del Boton Z
  @returns valor del registro
*/
int Nunchuck_Botton_z(){ return NCK_z;}
/*************************************************************************************************/
/**
  @brief devuelve el valor del Acelerometro eje X
  @returns valor del registro
*/
int Nunchuck_Acelerometro_X(){ return NCK_accX;}
/*************************************************************************************************/
/**
  @brief devuelve el valor del Acelerometro eje Y
  @returns valor del registro
*/
int Nunchuck_Acelerometro_Y(){ return NCK_accY;}
/*************************************************************************************************/
/**
  @brief devuelve el valor del Acelerometro eje Z
  @returns valor del registro
*/
int Nunchuck_Acelerometro_Z(){ return NCK_accZ;}
/*************************************************************************************************/
/**
  @brief lee el registro de botones
  @param ninguno
  @returns valor del registro
*/
int Nunchuck_lectura(){	
		
	int bytes[6];
    	int i;
    
        wiringPiI2CWrite(NCK_fd, 0x00);
        delayMicroseconds(500);
        for (i=0; i<6; i++) {
            bytes[i] = wiringPiI2CRead(NCK_fd);
        }

        NCK_joyX = bytes[0];
        NCK_joyY = bytes[1];
        NCK_accX = (bytes[2] << 2) | ((bytes[5] & 0xc0) >> 6);
        NCK_accY = (bytes[3] << 2) | ((bytes[5] & 0x30) >> 4);
        NCK_accZ = (bytes[4] << 2) | ((bytes[5] & 0x0c) >> 2);
        NCK_c = (bytes[5] & 0x02) >> 1;
        NCK_z = bytes[5] & 0x01;


    	//fprintf(stdout,"NUNCHUCK: JS_X: %x  JS_Y: %x \n", NCK_joyX,NCK_joyY);
	//fprintf(stdout,"NUNCHUCK: Boton_C: %x  Boton_Z: %x \n", NCK_c,NCK_z);
	//fprintf(stdout,"NUNCHUCK: Acc_X: %x  Acc_Y: %x Acc_Z: %x \n",NCK_accX,NCK_accY,NCK_accZ);
    return 0;
}
	

/*************************************************************************************************/
int Nunchuck_test(){

	fprintf(stdout,"NUNCHUCK: Testing.....\n");
	Nunchuck_init();

	int bytes[6];
    	int i,cont=0; 
	while(cont<15) {
		wiringPiI2CWrite(NCK_fd, 0x00);
		delayMicroseconds(500);
		for (i=0; i<6; i++) {
			bytes[i] = wiringPiI2CRead(NCK_fd);
		}

		int joyX = bytes[0];
		int joyY = bytes[1];
		int accelX = (bytes[2] << 2) | ((bytes[5] & 0xc0) >> 6);
		int accelY = (bytes[3] << 2) | ((bytes[5] & 0x30) >> 4);
		int accelZ = (bytes[4] << 2) | ((bytes[5] & 0x0c) >> 2);
		int c = (bytes[5] & 0x02) >> 1;
		int z = bytes[5] & 0x01;

		printf("data: joyX=%x joyY=%x accelX=%x accelY=%x accelZ=%x c=%x z=%x\n", joyX, joyY, accelX, accelY, accelZ, c, z);
		delay(500);
		cont+=1;
    }
	
	return 0;
}

