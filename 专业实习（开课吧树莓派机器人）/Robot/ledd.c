#include<stdlib.h>
#include<wiringPi.h>
#include<stdio.h>
#define BUTTON_1 5
#define BUTTON_2 6
#define BEEP 29
#define LED_PIN_W 7
int main()
{
    printf("hello world\n");
    wiringPiSetup();
    pinMode(LED_PIN_W,OUTPUT);
    pinMode(BUTTON_1,INPUT);
    pinMode(BUTTON_2,INPUT);
    pinMode(BEEP,OUTPUT);
    //pullUpDnControl(BUTTON_1,PUD_UP);
    while(1){
        if(digitalRead(BUTTON_1)==0)
        {
		digitalWrite(LED_PIN_W,LOW);
        }
        else
        {
            digitalWrite(LED_PIN_W,HIGH);
        }
        if(digitalRead(BUTTON_2)==1)
        {
			digitalWrite(BEEP,LOW);
        }
        else
        {
            digitalWrite(BEEP,HIGH);
        }
        delay(50);
    }
    return 0;

}
