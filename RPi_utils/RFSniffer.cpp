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
#include <time.h>
using namespace std;

//File Writing Function called on line 61
void filewriter(int a)
{
  //Get a timestamp
  time_t rawtime;
  struct tm * timeinfo;

  time (&rawtime);
  timeinfo = localtime (&rawtime);

//Open, Write and close the temperature_log.txt file
  char str[10];
  //opens file
  ofstream a_file ( "temperature_log.txt", ios::app );
  // Outputs to file
  a_file << asctime(timeinfo) << "," << a << endl;
  // Close the file
  a_file.close();
}
   
RCSwitch mySwitch;
 
int main(int argc, char *argv[]) {
     // This pin is not the first pin on the RPi GPIO header!
     // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     int PIN = 2;
     
     if(wiringPiSetup() == -1)
       return 0;

     mySwitch = RCSwitch();
     mySwitch.enableReceive(PIN);  // Receiver on interrupt 0 => that is pin #2
     
    
     while(1) {
  
      if (mySwitch.available()) {
    
        int value = mySwitch.getReceivedValue();
    
        if (value == 0) {
          printf("Unknown encoding");
        } else {    
   
          printf("Received %i\n", mySwitch.getReceivedValue() );
          int a = mySwitch.getReceivedValue();
          filewriter(a);
        }
        
        mySwitch.resetAvailable();
    
      }
      
  
  }

  exit(0);


}