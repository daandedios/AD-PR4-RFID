#include <Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(7);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);
}

void loop() {

myservo.write(65);
delay(1000);
myservo.write(0);

delay(1000);

                   
}
