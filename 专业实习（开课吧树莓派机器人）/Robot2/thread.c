#include <wiringPi.h>
#include "thread.h"
#include "status.h"
#include "action.h"
#include "gpio.h"
#include "server.h"

static char c;
void dis_det(){
	float d=30;	
	printf("xx\n");
	d = get_dis();
	printf("%f\n",d);
	if(d > 2 && d < 25){
		beep_ctrl(1000);
		robot_standby();
		delay(1000);
		robot_turnright(4);
	}	
}
void *server_thread(void *arg)
{
	server_accept();
	while(1){
		server_recv(&c,1);
		printf("recv cmd:%c\n",c);
	}
}
void *judge_thread(void *arg)
{
	int err;
	pthread_t server_id;
	err = pthread_create(&server_id,NULL,server_thread,NULL);
	if(err != 0){
		perror("server_thread create fail\n");
		return -1;
	}
	while(1){
		switch(c){
			case 'E':
			{
					int i=3;
					while(i--){				
						if(c == 'H'){
							robot_standby();
							break;
						}
						dis_det();	
						robot_forward(1);		
					}
					robot_standby();
					break;
				}
			case 'K':
			{
					int i=3;
					while(i--){
						if(c == 'H'){
							robot_standby();
							break;
						}
						robot_backward(1);
					}
					robot_standby();
					break;
				}
			case 'G':
			{
					int i=5;
					while(i--){
						if(c == 'H'){
							robot_standby();
							break;
						}
						robot_turnleft(1);
					}
					break;
				}
			case 'I':
			{
					int i=5;
					while(i--){
						if(c == 'H'){
							robot_standby();
							break;
						}
						robot_turnright(1);
					}
					break;
				}
			case 'A':
			{
					robot_play_1();
					c = 'H';
					break;
				}
			case 'B':
			{		
					robot_play_2();
					c = 'H';
					break;
				}
			case 'C':
			{
					robot_play_3(3);
					c = 'H';
					break;
				}
			}
		}
}
void *status_det(void *arg){
	int x=85,y=85;
	status_init();
	while(1){
		delay(1000);
		y = get_status(1);
		x = get_status(0);
		printf("x = %d, y = %d\n",x,y);
		if(y > 62 && y < 70){
			delay(1000);
			robot_climbup_l();
			y = get_status(1);
			x = get_status(0);
		}
		if(y>100){
			delay(1000);
			robot_climbup_r();
			y = get_status(1);
			x = get_status(0);
		}
		if(x >63 && x<69 ){
			delay(1000);
			robot_climbup_f();
			y = get_status(1);
			x = get_status(0);
		}
		if(x >100 ){
			delay(1000);
			robot_climbup_b();
			y = get_status(1);
			x = get_status(0);
		}
	}
}	


int init_thread(){
	int err;
	pthread_t dis_id,stat_id,judge_id;
//	err = pthread_create(&dis_id,NULL,dis_det,NULL);
//	if(err != 0){
//		perror("dis_det create fail\n");
//		return -1;
//	}
	err = pthread_create(&stat_id,NULL,status_det,NULL);
	if(err != 0){
		perror("status_det create fail\n");
		return -1;
	}
	err = pthread_create(&judge_id,NULL,judge_thread,NULL);
	if(err != 0){
		perror("judge_thread create fail\n");
		return -1;
	}
	return 0;
}
