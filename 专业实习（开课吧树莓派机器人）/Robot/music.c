#include<stdlib.h>
#include<wiringPi.h>
#include<stdio.h>
#include<softTone.h>
#include"status.h"
#define BUTTON_1 5
#define BUTTON_2 6
#define BEEP 29
#define LED_PIN_W 7
#include<unistd.h>
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
int main()
{
    printf("hello world\n");
    wiringPiSetup();
    pinMode(LED_PIN_W,OUTPUT);
    pinMode(BUTTON_1,INPUT);
    pinMode(BUTTON_2,INPUT);
    pinMode(BEEP,OUTPUT);
    softToneCreate(BEEP);
    init_angle();
    int i=0;
    int x,y;
    int s=0;
    while(1){
        x = get_angle(0);
        y = get_angle(1);
        printf("x = %d , y = %d\n",x,y);
        sleep(1);
       // if(s==0){
       //     sleep(2);
       // softToneWrite(BEEP, CH5);
       // delay(1000);
       // softToneWrite(BEEP,0);
       // sleep(2);
   // softToneWrite(BEEP, CH7);
   // delay(1000);
    //    softToneWrite(BEEP,0);
      //  sleep(2);
     //   softToneWrite(BEEP, CH1);
   //     delay(1000);
    //    softToneWrite(BEEP,0);
     //   sleep(2);
      //  softToneWrite(BEEP, CM3);
     //   delay(1000);
     //   softToneWrite(BEEP,0);
//s=1;
// }
        if(digitalRead(BUTTON_1)==0)
        {
		digitalWrite(LED_PIN_W,LOW);
        }
        else
        {
            digitalWrite(LED_PIN_W,HIGH);
        }
        
        
        
        if(digitalRead(BUTTON_2)==1)//1 is not press
        {
			digitalWrite(BEEP,LOW); //LOW is not BEEP

            i=0;
        }
        else
        {
            while(i<11)
            if(i<11){
            softToneWrite(BEEP, song_1[i]);
            delay(350);
            i++;}
            
          
        }



        
        
    }
    return 0;

}
