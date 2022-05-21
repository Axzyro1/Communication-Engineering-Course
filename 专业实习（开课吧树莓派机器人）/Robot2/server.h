#ifndef _SERVER_H_
#define _SERVER_H_

#define SER_IP "192.168.12.1"
#define SER_POET 4578

extern int server_init();
extern int server_accept();
extern int server_recv(char *buf,int len);
extern void server_close(int );

#endif
