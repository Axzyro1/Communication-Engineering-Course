#ifndef _THREAD_H__
#define _THREAD_H__

#include <pthread.h>

int init_thread(void);
void * status_det(void *arg);
void dis_det();
void *server_thread(void *arg);
void *judge_thread(void *arg);

#endif


