
//developer:  Daan de Dios
//date:       2019-03-21
//function:   RFID

#include <Arduino.h>




//---------------------- includs --------------------------------
//servo lib.
#include <Servo.h>


//---------------------- includs --------------------------------






//---------------------- global vars ----------------------------
//=========================== servo =============================
Servo servoBarrier;  // create servo object to control the barrier Servo.

//Servo positions
int pos_servoBarrierOpen = 65;
int pos_servoBarrierClose = 0;

//=========================== servo end =========================


//---------------------- global vars end ------------------------








//----------------------- functions -----------------------------
//=========================== servo =============================
void servo() {
  //open barrier
  servoBarrier.write(pos_servoBarrierOpen);

  delay(1000);

  //close barrier
  servoBarrier.write(pos_servoBarrierClose);
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


servo(); // opens barrier and clos barrier after 1000 miliseconds.



//=========================== servo end =========================


}
