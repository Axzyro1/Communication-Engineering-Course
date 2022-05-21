#include<stdio.h>
#include<wiringPi.h>
#include<fcntl.h>
#include<wiringSerial.h>
#include<string.h>
#include <unistd.h>
static int uart_fd;
static char cmd[100][119];
#define BEEP 29
int init_action()
{
	
    uart_fd = serialOpen("/dev/ttyAMA0",115200);
    if(uart_fd<0)
    {
        printf("open serial failure\n");
        return 0;
    }
    return 1;
}
int load_action()
{
    int fd;
    char *locate = NULL;
    int i ;
    char buf[1024*10] = {0};
    fd = open("./robot.ini",O_RDONLY);
    if(fd<0)
    {
        perror("open file error");
        return 0;
    }
    read(fd,buf,sizeof(buf));
    locate = strstr(buf,"G0000");
    printf("%s\n",locate);
    for (i = 0;i<88;i++)
    {
	memcpy(cmd[i],locate,120);
	locate+=120;
	printf("%s",cmd[i]);

    }
}
void robot_action(int begin,int end,int dt,int times)
{
    
    while(times--){
        for(int i =begin;i<end;i++)
        {
        serialPrintf(uart_fd,cmd[i]);
        delay(dt);
        }
    }
}
void robot_forward(int steps)
{
    robot_action(3,11,1000,steps);

}
void robot_backward(int steps)
{
    robot_action(12,19,1000,steps);
}
int main()
{
    init_action();
  //  load_action();
  //  while(1){
//        if(digitalRead(5)==0)
 //       {
 //           robot_forward(5);
 //       }
 // digitalWrite(BEEP,HIGH);
 //           delay(100);
 //           digitalWrite(BEEP,LOW);
// delay(100);



//serialPrintf(uart_fd,"#001P1500T1000!");
    serialPrintf(uart_fd,"#004P1500T1000!");

    serialPrintf(uart_fd,"#002P2000T1000!");
    serialPrintf(uart_fd,"#003P1100T1000!");
    
    serialPrintf(uart_fd,"#005P1000T1000!");
    serialPrintf(uart_fd,"#006P1900T1000!");
//}



    return 0;

}

