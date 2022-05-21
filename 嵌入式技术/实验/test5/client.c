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
int main(int argc, char **argv)
{
    pid_t fd;
    const char buff[] = "Hello! Welcome here gggggggggggg!\r\n"; //定义要发送的数据缓冲区；
    int sockfd, connsock;          //定义一个socket套接字，用于通讯
    struct sockaddr_in serveraddr; //定义网络套接字地址结构
    if (argc != 2)
    {
        printf("Usage: echo ip地址");
        exit(0);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //创建一个套接字
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;   //指定使用的通讯协议族
    serveraddr.sin_port = htons(5000); //指定要连接的服务器的端口
    inet_pton(AF_INET, argv[1], &serveraddr.sin_addr);
    connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)); //连接服务器
    send(sockfd, buff, sizeof(buff), 0);                                 //向客户端发送数据
    close(sockfd);                                                       //关闭套接字
    return (0);
}