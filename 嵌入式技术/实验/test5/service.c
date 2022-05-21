#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
void main()
{
    pid_t fd;
    int listensock, connsock;
    char recvbuff[100];                                                           //定义要接收的数据缓冲区
    struct sockaddr_in serveraddr;                                                //定义网络套接字地址结构
    listensock = socket(AF_INET, SOCK_STREAM, 0);                                 //创建一个套接字，用于监听
    bzero(&serveraddr, sizeof(struct sockaddr));                                  //地址结构清零
    serveraddr.sin_family = AF_INET;                                              //指定使用的通讯协议族
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);                               //指定接受任何连接
    serveraddr.sin_port = htons(5000);                                            //指定监听的端口
    bind(listensock, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in)); //给套接 口邦定地址
    listen(listensock, 1024); //开始监听
    connsock = accept(listensock, (struct sockaddr *)NULL, NULL);    //建立通讯的套接字，accept函数，等待客户端程序使用connect函数的连接
    recv(connsock, recvbuff, sizeof(recvbuff), 0); //接收服务器的数据
    printf("%s\n", recvbuff);                      //打印接收到的数据
    sleep(2);
    close(connsock);   //关闭通讯套接字
    close(listensock); //关闭监听套接字
}
