#include<stdio.h>
#include<wiringPi.h>
#include<fcntl.h>
#include<wiringSerial.h>
#include<string.h>
#include<unistd.h>
#include<sys/time.h>
static int uart_fd;
static char cmd[100][119];
#define BEEP 29
#define Trig 0
#define Echo 1
#define CL1 131
#define CL2 147
#define CL3 165
#define CL4 175
#define CL5 196
#define CL6 221
#define CL7 248

#define CM1 262
#define CM2 294
#define CM3 330
#define CM4 350
#define CM5 393
#define CM6 441
#define CM7 495

#define CH1 525
#define CH2 589
#define CH3 661
#define CH4 700
#define CH5 786
#define CH6 882
#define CH7 990

int song_1[] = {CH5,CH3,CH4,CH5,CH3,CH4,CH5,CM5,CM6,CM7,0};
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
    for (i = 0;i<9;i++)
    {
	memcpy(cmd[i],locate,120);
	locate+=120;
	printf("%s",cmd[i]);

    }
    while(1)
    {
	for(int s=1;s<9;s++)
	{
	memcpy(cmd[s],locate,120);
	locate+=120;
	printf("%s",cmd[s]);


	}
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
void back()
{
serialPrintf(uart_fd,"#001P1500T1000!");
delay(1000);
serialPrintf(uart_fd,"#002P1500T1000!");
delay(1000);
serialPrintf(uart_fd,"#003P1500T1000!");
delay(1000);
serialPrintf(uart_fd,"#004P1500T1000!");
delay(1000);
serialPrintf(uart_fd,"#005P1500T1000!");
delay(1000);
serialPrintf(uart_fd,"#006P1500T1000!");
delay(1000);
}
void act()
{
    //1
    serialPrintf(uart_fd,"#001P1350T1000!");
    serialPrintf(uart_fd,"#002P1600T1000!");
    serialPrintf(uart_fd,"#003P1600T1000!");
    serialPrintf(uart_fd,"#004P1400T1000!");
    serialPrintf(uart_fd,"#005P1600T1000!");
    serialPrintf(uart_fd,"#006P1600T1000!");
    delay(1000);
    softToneWrite(BEEP, CH5);
        delay(1000);
softToneWrite(BEEP,0);
//2    
    serialPrintf(uart_fd,"#001P1500T1000!");
    serialPrintf(uart_fd,"#002P1600T1000!");
    serialPrintf(uart_fd,"#003P1600T1000!");
    serialPrintf(uart_fd,"#004P1500T1000!");
    serialPrintf(uart_fd,"#005P1600T1000!");
    serialPrintf(uart_fd,"#006P1600T1000!");
    delay(1000);
    softToneWrite(BEEP, CH7);
    delay(1000);
softToneWrite(BEEP,0);
 //3
    serialPrintf(uart_fd,"#001P1750T1000!");
    serialPrintf(uart_fd,"#002P1600T1000!");
    serialPrintf(uart_fd,"#003P1600T1000!");
    serialPrintf(uart_fd,"#004P1650T1000!");
    serialPrintf(uart_fd,"#005P1600T1000!");
    serialPrintf(uart_fd,"#006P1600T1000!");
delay(1000);
softToneWrite(BEEP, CH1);
    delay(1000);
softToneWrite(BEEP,0);
//4
    serialPrintf(uart_fd,"#001P1600T1000!");
    serialPrintf(uart_fd,"#002P1500T1000!");
    serialPrintf(uart_fd,"#003P1500T1000!");
    serialPrintf(uart_fd,"#004P1650T1000!");
    serialPrintf(uart_fd,"#005P1500T1000!");
    serialPrintf(uart_fd,"#006P1500T1000!");
    delay(1000);
    softToneWrite(BEEP, CM3);
    delay(1000);
softToneWrite(BEEP,0);
 //5
    
    serialPrintf(uart_fd,"#001P1600T1000!");
    serialPrintf(uart_fd,"#002P1400T1000!");
    serialPrintf(uart_fd,"#003P1400T1000!");
    serialPrintf(uart_fd,"#004P1650T1000!");
    serialPrintf(uart_fd,"#005P1400T1000!");
    serialPrintf(uart_fd,"#006P1400T1000!");
delay(1000);
softToneWrite(BEEP, CL1);
    delay(1000);
softToneWrite(BEEP,0);
//6 
    serialPrintf(uart_fd,"#001P1500T1000!");
    serialPrintf(uart_fd,"#002P1400T1000!");
    serialPrintf(uart_fd,"#003P1400T1000!");
    serialPrintf(uart_fd,"#004P1500T1000!");
    serialPrintf(uart_fd,"#005P1400T1000!");
    serialPrintf(uart_fd,"#006P1400T1000!");
    delay(1000);
   // 7
   softToneWrite(BEEP, CH6);
    delay(1000);
softToneWrite(BEEP,0);
    serialPrintf(uart_fd,"#001P1350T1000!");
    serialPrintf(uart_fd,"#002P1400T1000!");
    serialPrintf(uart_fd,"#003P1400T1000!");
    serialPrintf(uart_fd,"#004P1250T1000!");
    serialPrintf(uart_fd,"#005P1400T1000!");
    serialPrintf(uart_fd,"#006P1400T1000!");
   delay(1000);
   softToneWrite(BEEP, CM2);
    delay(1000);
softToneWrite(BEEP,0);
    
    
}
void action()
{
    init_action();
   // load_action();
  //  while(1){
    //    if(digitalRead(5)==0)
      //  {
        //    robot_forward(5);
       // }
//  digitalWrite(BEEP,HIGH);
     //       delay(100);
   //         digitalWrite(BEEP,LOW);
 //delay(100);
back();
pinMode(BEEP,OUTPUT);
    softToneCreate(BEEP);

while(1){
    
    
    
    
    act();
    act();
    act();
  
   
   //float disMeasure(void)
   //{
       unsigned int start,stop;
       float dis;
       digitalWrite(Trig,LOW);
       delayMicroseconds(2);
       digitalWrite(Trig,HIGH);
       delayMicroseconds(10);
       digitalWrite(Trig,LOW);
       while(!(digitalRead(Echo)==1));
       //gettimeofday(&var1,NULL);
       start=micros();
       while(!(digitalRead(Echo)==0));
       //gettimeofday(&var2,NULL);
       stop=micros();
       dis=(stop-start)*340/2;
       
       if(dis>100000000000000) break;
       
   // }   
   
   
   
   

}

}
