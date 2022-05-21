#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <pcf8591.h>
#include <time.h>
#include "status.h"

int i2c_fd;

float AD_work(unsigned char channel){
	float AD_val; 
	unsigned char i;
	for (i = 0; i < 10; i++)
		AD_val += analogRead(channel); 
	AD_val /= 10;
	return AD_val;
}
void status_init(){
	i2c_fd = wiringPiI2CSetup(0x48);
	if(i2c_fd < 0){
		printf("i2C setup fail!\n");
	}
}
int get_status(int ch){
	int result;
	if(ch == 0)
	{
		wiringPiI2CWriteReg8(i2c_fd, 0x40, 0x00);
		return wiringPiI2CReadReg8(i2c_fd,0x40);
	}
   	else if(ch == 1)
	{
		wiringPiI2CWriteReg8(i2c_fd, 0x41, 0x01);
		return wiringPiI2CReadReg8(i2c_fd,0x41);
	}
}
