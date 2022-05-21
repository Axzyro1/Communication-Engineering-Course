#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>  
#include <sys/stat.h>  
#include <fcntl.h> 

int main()
{
int cfd,i;
int fd;  
int recbytes;
int sin_size;
int b;
char buf[10]={0,1,2,3,4,5}; 
char buffer[1024]={0},a[16];   
struct sockaddr_in s_add,c_add;
unsigned short portnum=1024; 
 fd = open("/dev/my_led",O_RDWR);  
    if (fd < 0)  
    {  
        printf ("Open /dev/my_led file error\n");  
        return -1;  
    }     

printf("Hello,welcome to client !\r\n");

cfd = socket(AF_INET, SOCK_STREAM, 0);
if(-1 == cfd)
{
    printf("socket fail ! \r\n");
    return -1;
}
printf("socket ok !\r\n");

bzero(&s_add,sizeof(struct sockaddr_in));
	s_add.sin_family=AF_INET;
	printf("enter:");
	for(i=0;i<16;i++)scanf("%c",&a[i]);
	printf("%s",a);
	s_add.sin_addr.s_addr=inet_addr(a);
	s_add.sin_port=htons(portnum);
	printf("s_addr=%#x,port:%#x\r\n",s_add.sin_addr.s_addr,s_add.sin_port);
	if(-1==connect(cfd,(struct sockaddr*)(&s_add),sizeof(struct sockaddr)))
	{
		printf("connect fail !\r\n");
		return -1;
	}
	printf("connect ok !\r\n");
while(1){
recbytes = read(cfd,buffer,1024);
buffer[recbytes]='\0';
printf("%s\r\n",buffer);
if(buffer[0]=='1')
{
b=0;
printf("%d\n",b);
write(fd,&buf[0],1);  
        sleep(1);  
}
else if(buffer[0]=='2')
{
b=1;
printf("%d\n",b);
write(fd,&buf[1],1);  
        sleep(1);
}  
		else if(buffer[0]=='3')
{
b=2;
printf("%d\n",b);
write(fd,&buf[2],1);  
        sleep(1);
}  
		else if(buffer[0]=='4')
{
b=3;
printf("%d\n",b);
write(fd,&buf[3],1);  
        sleep(1);  
}
else if(buffer[0]=='5')
{
b=4;
printf("%d\n",b);
write(fd,&buf[4],1);  
        sleep(1);  
}
	else
{
b=5;
printf("%d\n",b);
write(fd,&buf[5],1);  
        sleep(1);  
}


}
close(cfd);
close(fd);
return 0;
}

