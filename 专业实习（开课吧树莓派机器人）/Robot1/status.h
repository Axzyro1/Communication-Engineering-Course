#ifndef _status_H_
#define _status_H_

int i2c_fd;

float AD_work(unsigned char channel);
void status_init();
int get_status(int ch);

#endif
