/*
*  Created by Parthe Singha Roy
*  Date: 18-08-2022
*  
*/




#include <HardwareSerial.h>
//Global Object
HardwareSerial userSerial(2);

//Macros
#define RXD2 16
#define TXD2 17
#define pin_one 5
#define pin_two 4

//Global variable
int dataOne;
int dataTwo;

//Initial setup
void setup() {
  //set the recieve pins
  pinMode(pin_one,INPUT);
  pinMode(pin_two,INPUT);
  
  userSerial.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.begin(115200);

  //debug
  //  Serial.println("Serial Monitor Start");
}

// loop code
void loop() { //Choose Serial1 or Serial2 as required
    dataOne = digitalRead(pin_one);
    dataTwo = digitalRead(pin_two);// read the input pin

    if(dataOne==1){
        userSerial.write("L");
        //Serial.println("button-1 clicked."); //debug
        delay(1000);
    }
     if(dataTwo==1){
        userSerial.write("R");
        //Serial.println("button-2 clicked."); //debug
        delay(1000);
    }
    delay(200);
}
