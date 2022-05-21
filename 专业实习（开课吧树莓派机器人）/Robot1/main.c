#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include "gpio.h"
#include "status.h"
#include "action.h"

void* forwardctrl(void *arg) 
{ 
	while(1)
	{
		if(get_key(1) == 0)
		{  
			robot_forward(5);
		}
	} 
}
void* backctrl(void *arg) 
{ 
	while(1)
	{
		if(get_key(2) == 0) 
			robot_backward(5); 
	} 
}
void* turnctrl(void *arg) 
{ 
	while(1)
	{
		float d;	
		printf("xx\n");
		d = get_dis();
		printf("%f\n",d);
		if(d  < 20){
			//led_ctrl(1000);
			robot_standby();
			delay(1000);
			robot_turnright(3);
		}
	}
}
void *climbctrl(void *arg){
	int x=0,y=0;
	status_init();
	while(1){
		delay(1000);
		y = get_status(1);
		x = get_status(0);
		//printf("x = %d, y = %d\n",x,y);
		if(y > 62 && y < 70){
			delay(3000);
			robot_climbup_f();
			y = get_status(1);
			x = get_status(0);
		}
		if(y>95 && y<105){
			delay(3000);
			robot_climbup_b();
			y = get_status(1);
			x = get_status(0);
		}
		if(x >63 && x<69 ){
			delay(3000);
			robot_climbup_l();
			y = get_status(1);
			x = get_status(0);
		}
		if(x >97 && x<105){
			delay(3000);
			robot_climbup_r();
			y = get_status(1);
			x = get_status(0);
		}	
	}
}	
int main()
{
	pthread_t forward_id,backward_id,turn_id,climb_id;
	int err;
	gpio_init();
	action_init();
	err = pthread_create(&forward_id,NULL,backctrl,NULL);
	if(err != 0)
	{
		perror("create forward_thread fail!\n");
		return 1;
	}
	err = pthread_create(&backward_id,NULL,forwardctrl,NULL); 
	if(err != 0)
	{ 
		perror("create backward_thread fail\n"); 
		return 1; 
	}
	err = pthread_create(&turn_id,NULL,turnctrl,NULL);
	if(err != 0)
	{
		perror("create turn_thread fail!\n");
		return 1;
	}
	err = pthread_create(&climb_id,NULL,climbctrl,NULL);
	if(err != 0)
	{
		perror("create climb_thread fail!\n");
		return 1;
	}
	while(1)
	{
		delay(1);
	} 
	return 0;
}
