#include <stdio.h>
#include <wiringPi.h>
#include "gpio.h"

void gpio_init(){
	wiringPiSetup();
	pinMode(LED,OUTPUT);
	pinMode(BEEP,OUTPUT);
	pinMode(KEY1,INPUT);
	pinMode(KEY2,INPUT);
	pinMode(TRIG,OUTPUT);
	pinMode(ECHO,INPUT);
}

int get_key(int key){
	if(key == KEY1){
		return digitalRead(KEY1);
	}
	if(key == KEY2){
		return digitalRead(KEY2);
	}
}

void beep_ctrl(int dely){
	digitalWrite(BEEP,HIGH);
	delay(dely);
	digitalWrite(BEEP,LOW);

}

float get_dis(void){
	float d;
	unsigned int start,end;

	digitalWrite(TRIG,LOW);
	delayMicroseconds(2);
	digitalWrite(TRIG,HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG,LOW);
	while(!(digitalRead(ECHO) == 1));
	
	start = micros();
	
	while(!(digitalRead(ECHO) == 0));
	end = micros();
	
	d =(float) (end - start)/1000000*34000/2;
	return d;
}

