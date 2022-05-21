#include<stdlib.h>
#include<wiringPi.h>
#include<stdio.h>
#include<softTone.h>
#include"status.h"
#include"action.h"
#define BUTTON_1 5
#define BUTTON_2 6
#define BEEP 29
#define LED_PIN_W 7
#include<unistd.h>

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
        //sleep(1);
if(x<75){
     softToneWrite(BEEP, CH5);
        delay(1000);
softToneWrite(BEEP,0);
}
if(y<75)
{
softToneWrite(BEEP, CH7);
    delay(1000);
softToneWrite(BEEP,0);
}
if(x>100)
{
softToneWrite(BEEP, CH1);
    delay(1000);
softToneWrite(BEEP,0);
}
 if(y>98)
{
softToneWrite(BEEP, CM3);
    delay(1000);
softToneWrite(BEEP,0);
}
    
        if(digitalRead(BUTTON_1)==0)
        {
		digitalWrite(LED_PIN_W,LOW);
        action();
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

