#include <stdio.h>
#include <wiringSerial.h>
#include <wiringPi.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "gpio.h"

int uart_fd;
static char cmd[100][200];

int action_init()
{
	uart_fd=serialOpen("/dev/ttyAMA0",115200);
	if(uart_fd<0){
		perror("open ttyAMA0 fail\n");
		return uart_fd;
	}
	return 1;
}
int action_load()
{
	int fd;
	char buf[1024*10]={0};
	char *locate=NULL;
	fd = open("robot.ini",O_RDONLY);
	if(fd<0){
		perror("open robot.ini fail\n");
		return 1;
	}
	read(fd,buf,sizeof(buf));
	locate = strstr(buf,"G0000");
	for(int i=0;i<50;i++){
		memcpy(cmd[i],locate,104);
		locate += 104;
	}
	return 0;
	
}		
static void robot_act(int begin,int end,int dly)
{
	int i;
	for(i=begin;i<=end;i++){
		serialPrintf(uart_fd,cmd[i]);
		delay(dly);
	}
}
void robot_standby()
{
	serialPrintf(uart_fd,cmd[1]);
}
void robot_forward(int steps)
{
	while(steps--){
		robot_act(1,16,1000);
	}	
}
void robot_backward(int steps)
{
	while(steps--){
		robot_act(17,29,1000);
	}
}
void robot_turnright(int steps)
{
	while(steps--){
		robot_act(30,33,1000);
	}
}
void robot_turnleft(int steps)
{
	while(steps--){
		robot_act(34,37,1000);
	}
}
void robot_climbup_f()
{
	robot_act(38,40,1000);
}
void robot_climbup_b()
{
	robot_act(41,43,1000);
}
void robot_climbup_l()
{
	robot_act(44,47,1000);
}
void robot_climbup_r()
{
	robot_act(48,53,1000);
}
void robot_play_1()
{
	robot_act(54,56,1000);
}
void robot_play_2()
{
	robot_act(57,64,1000);
}
void robot_play_3(int steps)
{
	while(steps--){
		robot_act(65,66,1000);
	}
}
