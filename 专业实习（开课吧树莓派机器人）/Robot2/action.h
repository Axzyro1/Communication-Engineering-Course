#ifndef _ACTION_H__
#define _ACTION_H__

int action_init();
int action_load();
void action_test();
void robot_standby();
void robot_forward(int steps);
void robot_backward(int steps);
void robot_turnleft(int steps);
void robot_turnright(int steps);
void robot_climbup_f();
void robot_climbup_b();
void robot_climbup_l();
void robot_climbup_r();
void robot_play_1();
void robot_play_2();
void robot_play_3(int steps);

#endif
