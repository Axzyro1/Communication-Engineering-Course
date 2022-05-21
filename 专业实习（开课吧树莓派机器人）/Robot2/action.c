#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <wiringSerial.h>
#include"gpio.h"

int uart_fd;
char cmd[100][120];

int action_init(){
	uart_fd=serialOpen("/dev/ttyAMA0",115200);
	if(uart_fd<0){
		printf("open serial failure!\n");
		return 0;
	}
	return 1;
}

int action_load(){

	int fd;
	char buf[1024*10] = {};
	fd = open("robot.ini",O_RDONLY);
	if(fd < 0){
		perror("open .ini fail\n");
		return 1;
	}
	read(fd,buf,sizeof(buf));
	char *locate = strstr(buf,"G0000");
	for (int i=0;i<70;i++){	
		memcpy(cmd[i],locate+i*104,104);
	}
	return 0;
}

static void robot_act(int begin,int end,int steps,int times){
	int i;
	while(steps--){
		for(i=begin;i<=end;i++){
			serialPrintf(uart_fd,cmd[i]);
			delay(times);
		}
	}	
}

void robot_standby(){
	serialPrintf(uart_fd,cmd[0]);
}

void robot_forward(int steps){
	robot_act(0,5,steps,1000);
}

void robot_backward(int steps){
	robot_act(16,21,steps,1000);			
}

void robot_turnleft(int steps){
	robot_act(33,34,steps,1000);
}

void robot_turnright(int steps){
	robot_act(35,36,steps,1000);
}

void robot_climbup_f(){
	robot_act(38,40,1,1000);
}

void robot_climbup_b(){
	robot_act(41,43,1,1000);
}

void robot_climbup_l(){
	robot_act(44,47,1,1000);
}

void robot_climbup_r(){
	robot_act(48,53,1,1000);
}
void robot_play_1(){
	robot_act(54,56,1,1000);
}
void robot_play_2(){
	robot_act(57,65,1,2000);
}
void robot_play_3(int steps){
	robot_act(66,67,steps,1000);
}
