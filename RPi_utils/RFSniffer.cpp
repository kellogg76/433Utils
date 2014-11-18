/*
  RF_Sniffer
  
  Hacked from http://code.google.com/p/rc-switch/
  
  by @justy to provide a handy RF code sniffer
*/

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
using namespace std;



void filewriter()
{
  char str[10];
  //opens file
  ofstream a_file ( "temperature_log.txt" );
  // Outputs to file
  a_file<<TVRoomTemp();
  // Close the file
  a_file.close();
}
   
RCSwitch mySwitch;
 
int main(int argc, char *argv[]) {
int TVRoomTemp()  
     // This pin is not the first pin on the RPi GPIO header!
     // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     // for more information.
     int PIN = 2;
     
     if(wiringPiSetup() == -1)
       return 0;

     mySwitch = RCSwitch();
     mySwitch.enableReceive(PIN);  // Receiver on inerrupt 0 => that is pin #2
     
    
     while(1) {
  
      if (mySwitch.available()) {
    
        int value = mySwitch.getReceivedValue();
    
        if (value == 0) {
          printf("Unknown encoding");
        } else {    
   
          printf("Received %i\n", mySwitch.getReceivedValue() );
          TVRoomTemp = mySwitch.getReceivedValue();
          filewriter();
        }
        
        mySwitch.resetAvailable();
    
      }
      
  
  }

  exit(0);


}
