#include <wiringPi.h>
#include "thread.h"
#include "status.h"
#include "action.h"
#include "gpio.h"

void dis_det(){
	float d;	
	printf("xx\n");
	d = get_dis();
	if(d  < 20){
		printf("%f\n",d);
		led_ctrl(1000);
		robot_standby();
		delay(1000);
		robot_turnright(3);
	}	
}

void *status_det(void *arg){
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

int init_thread(){
	int err;
	pthread_t dis_id,stat_id;
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

	return 0;
}

