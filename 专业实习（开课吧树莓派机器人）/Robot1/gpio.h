#ifndef _gpio_H_
#define _gpio_H_

#define Key1 5
#define Key2 6
#define LED 7
#define BEEP 29
#define TRIG 0
#define ECHO 1

void gpio_init();
void* led_ctrl(int t);
int get_key(int num);
float get_dis(void);

#endif

