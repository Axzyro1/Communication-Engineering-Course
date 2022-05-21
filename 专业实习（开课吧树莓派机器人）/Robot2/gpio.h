#ifndef _GPIO_H__
#define _GPIO_H__

#define LED 7
#define BEEP 29
#define KEY1 5
#define KEY2 6
#define TRIG 0
#define ECHO 1

void gpio_init();
int get_key(int key);
void beep_ctrl(int dely);
float get_dis(void);

#endif
