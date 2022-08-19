#include <Servo.h>

//Create Servo Object
Servo myservo;

#define servo_pin D4 // servo pin
#define servo_delay 1000
#define R D1
#define G D2
#define B D3
#define USE_SERIAL Serial

// Function prototype
void rgb(int red, int green, int blue);
int hexToDec(String hexVal);
void set_color(String hex);


// Global Varible
char incomingByte; // for incoming serial data
int pos = 0; 
int i=0;
int j=5;
//RGB Color
char * RGB[8]={
  "#deb75b",
  "#ecf00a",
  "#3bfc2d",
  "#2dfce4",
  "#a32dfc",
  "#fc26e7",
  "#ff1499"};

//void setup
void setup() { 
    USE_SERIAL.begin(115200); // opens serial port, sets data rate to 115200 bps
    pinMode(R, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(B, OUTPUT);
    myservo.attach(2); //D4
    myservo.write(0);
    delay(1000);
}

void loop() {
  
  // reply only when you receive data:
  if (USE_SERIAL.available() > 0) {
    // read the incoming byte:
    incomingByte = USE_SERIAL.read();
    // say what you got:
    USE_SERIAL.print("I received: ");
    USE_SERIAL.println(incomingByte);
  }

if(incomingByte == 'L'){
  for (pos = 0; pos <= 180; pos += 36) { // goes from 0 degrees to 180 degrees

    
    
    // in steps of 36 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    set_color(RGB[i]);
    i++;
    delay(servo_delay);                       // waits 1 s for the servo to reach the position
    //pos check
    if(pos >= 180){
      incomingByte = 'A';
      i=0;
      return;
    }
  }
}

if(incomingByte == 'R'){
  for (pos = 180; pos >= 0; pos -= 36) { // goes from 180 degrees to 0 degrees
    
    
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    set_color(RGB[j]);
    j--;
    delay(servo_delay);                       // waits 1s for the servo to reach the position
    if(pos <= 0){
       incomingByte = 'A';
       j=5;
       return;
    }
  }
 }
delay(500);
}



void set_color(String hex){
    int r, g, b;
    if (hex.length() != 7){
        USE_SERIAL.println("Invalid color code");
        return;
    }
    r = hexToDec(hex.substring(1, 3));
    g = hexToDec(hex.substring(3, 5));
    b = hexToDec(hex.substring(5));
//    USE_SERIAL.println("set_color");
    rgb(r, g, b);
}

void rgb(int red, int green, int blue)
{
    analogWrite(R, red);
    analogWrite(G, green);
    analogWrite(B, blue);
}

//hex to decimal converter function
int hexToDec(String hexVal)
{
    int len = hexVal.length();
    int base = 1, i = 0;
    int dec_val = 0;

    for (i = 0; hexVal[i] != '\0'; i++){
        if (hexVal[i] >= 'a' && hexVal[i] <= 'z')
            hexVal[i] = hexVal[i] - 32;
    }
    for (int i = len - 1; i >= 0; i--){
        if (hexVal[i] >= '0' && hexVal[i] <= '9')
        {
            dec_val += (int(hexVal[i]) - 48) * base;
            // incrementing base by power
            base = base * 16;
        }
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F'){
            dec_val += (int(hexVal[i]) - 55) * base;
            base = base * 16;
        }
    }
    return dec_val;
}
