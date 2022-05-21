#include <stdio.h>
#include <wiringPiI2C.h>

int i2c_fd=0;

int status_init(){
	i2c_fd = wiringPiI2CSetup(0x48);
	if(i2c_fd<0){
		printf("i2c setup fail");
		return -1;
	}
	return 0;
}


int get_status(int ch){
	if(ch==1){
		wiringPiI2CWriteReg8(i2c_fd,0x41,0x00);
		return wiringPiI2CReadReg8(i2c_fd,0x41);
	}else if(ch==0){
		wiringPiI2CWriteReg8(i2c_fd,0x40,0x00);
		return wiringPiI2CReadReg8(i2c_fd,0x40);	
	}else{
		printf("ch value invalid");	
	}

}



