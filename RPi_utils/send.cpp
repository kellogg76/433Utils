/*
 Usage: ./send <systemCode> <unitCode> <command>
 Command is 0 for OFF and 1 for ON
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    /*
     output PIN is hardcoded for testing purposes
     see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     for pin mapping of the raspberry pi GPIO connector
     */
    int PIN = 0;
    unsigned long code = atoi(argv[1]);
    
    if (wiringPiSetup () == -1) return 1;
	printf("sending code[%d]\n", code);
	RCSwitch mySwitch = RCSwitch();
	mySwitch.enableTransmit(PIN);
	mySwitch.setProtocol(2);
	mySwitch.setRepeatTransmit (100);
	mySwitch.setPulseLength(800);
	mySwitch.send(code,15);
    return 0;
}
