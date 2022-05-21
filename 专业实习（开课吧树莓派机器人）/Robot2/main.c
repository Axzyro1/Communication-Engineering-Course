#include <stdio.h>
#include <wiringPi.h>
#include "thread.h"
#include "gpio.h"
#include "action.h"
#include "status.h"
#include "thread.h"
#include "server.h"


int main(){
	gpio_init();
	if(action_init() == 0){
		printf("init action fail!\n");
		return 1;
	}
	action_load();
	server_init();
	status_init();
	init_thread();
	robot_standby();
	while(1){
		delay(1000);
	}

	return 0;
}
