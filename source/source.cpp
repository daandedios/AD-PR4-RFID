
//Developer:  Daan de Dios
//Date:       2019-03-21
//function:   RFID
#include <Arduino.h>

//---------------------- includs --------------------------------
//servo lib.
#include <Servo.h>


//---------------------- includs --------------------------------




//---------------------- global vars ----------------------------
//=========================== servo =============================
Servo servoBarrier;  // create servo object to control the barrier Servo.
//=========================== servo end =========================


//---------------------- global vars end ------------------------



//----------------------- functions -----------------------------
//=========================== servo =============================
void servo() {
  servoBarrier.write(65);
  delay(1000);
  servoBarrier.write(0);
  delay(1000);
}
//=========================== servo end =========================


//----------------------- functions end -------------------------



//setup runs once, when the Arduino is first oiwerd on.
void setup() {


//=========================== servo =============================
myservo.attach(7);  // attaches the servo on pin 7 to the servo object (servoBarrier)
myservo.write(0);   // initialize servo stage 0 --> close Barrier
//=========================== servo end =========================

  
}

//loop runs continuously after the setup() has completed.
void loop() {

//=========================== servo =============================
servo();
//=========================== servo end =========================


}
