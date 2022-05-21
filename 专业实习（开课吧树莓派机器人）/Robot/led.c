#include<stdio.h>
#include<unistd.h>
#include<wiringPi.h>
#define BEEP_P 7
int main(){

    wiringPiSetup();
    pinMode(BEEP_P,OUTPUT);
    digitalWrite(BEEP_P,HIGH);
    return 0;

}
