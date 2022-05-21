#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include "gpio.h"

void gpio_init(){
	wiringPiSetup(); 
	pinMode(LED,OUTPUT);
	pinMode(BEEP,OUTPUT); 
	pinMode(Key1,INPUT); 
	pinMode(Key2,INPUT);
	pinMode(TRIG,OUTPUT);
	pinMode(ECHO,INPUT);
}
void* led_ctrl(int t){
	digitalWrite(BEEP,HIGH);
	delay(t);
	digitalWrite(BEEP,LOW);
}

int get_key(int num){
	if(num ==1)
		return digitalRead(Key1);
	if(num ==2)
		return digitalRead(Key2);
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
	
	d =(float)(end - start)/1000000*34000/2;
	return d;
}
