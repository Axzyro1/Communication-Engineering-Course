#ifndef _action_H_
#define _action_H_

int uart_fd;
char cmd[100][200];

int action_init();
int action_load();
void robot_standby();
void robot_forward(int steps);
void robot_backward(int steps);
void robot_turnright(int steps);
void robot_turnleft(int steps);
void robot_climbup_f();
void robot_climbup_b();
void robot_climbup_r();
void robot_climbup_l();
void robot_play_1();
void robot_play_2();
void robot_play_3(int steps);

#endif
