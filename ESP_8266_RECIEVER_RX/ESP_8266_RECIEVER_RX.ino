#include <Servo.h>

//Create Servo Object
Servo myservo;

#define servo_pin D4 // servo pin
#define servo_delay 1000
#define R D1
#define G D2
#define B D3

// Function prototype
void rgb(int red, int green, int blue);

// Global Varible
char incomingByte; // for incoming serial data
int pos = 0; 



void setup() { 
  Serial.begin(115200); // opens serial port, sets data rate to 115200 bps
    myservo.attach(2); //D4
    myservo.write(0);
    delay(1000);
}

void loop() {
  // reply only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);
  }

if(incomingByte == 'L'){
  for (pos = 0; pos <= 180; pos += 36) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(servo_delay);                       // waits 1 s for the servo to reach the position

    if(pos == 180){
      incomingByte = 'A';
    }
    
  }
}
  if(incomingByte == 'R'){
  for (pos = 180; pos >= 0; pos -= 36) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    rgb();
    delay(servo_delay);                       // waits 1s for the servo to reach the position
    if(pos == 0){
      incomingByte = 'A';
    }
  }
 }
delay(500);
}





//void rgb(int red, int green, int blue)
//{
//    analogWrite(R, red);
//    analogWrite(G, green);
//    analogWrite(B, blue);
//}
