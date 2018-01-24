#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <errno.h>

int main(void) {
    int NUNCHUCK_DEVICE = 0x52;

    printf("Testing the nunchuck through I2C\n");
    wiringPiSetup();
    int fd = wiringPiI2CSetup(NUNCHUCK_DEVICE);
    if (fd < 0) {
        printf("Error setting up I2C: %d\n", errno);
        exit(0);
    }
    wiringPiI2CWriteReg8(fd, 0x40, 0x00);
    delayMicroseconds(500);

    int bytes[6];
    int i;
    while(1) {
        wiringPiI2CWrite(fd, 0x00);
        delayMicroseconds(500);
        for (i=0; i<6; i++) {
            bytes[i] = wiringPiI2CRead(fd);
        }

        int joyX = bytes[0];
        int joyY = bytes[1];
        int accelX = (bytes[2] << 2) | ((bytes[5] & 0xc0) >> 6);
        int accelY = (bytes[3] << 2) | ((bytes[5] & 0x30) >> 4);
        int accelZ = (bytes[4] << 2) | ((bytes[5] & 0x0c) >> 2);
        int c = (bytes[5] & 0x02) >> 1;
        int z = bytes[5] & 0x01;

        printf("data: joyX=%x joyY=%x accelX=%x accelY=%x accelZ=%x c=%x z=%x\n", joyX, joyY, accelX, accelY, accelZ, c, z);
	delay(1000);
    }
    return 0;
}
