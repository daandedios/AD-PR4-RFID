
//developer:  Daan de Dios
//date:       2019-03-21
//function:   RFID

#include <Arduino.h>




//---------------------- includs --------------------------------
//servo lib.
#include <Servo.h>

//display lib.
#include <LiquidCrystal.h>

//RFID lib.
#include <LiquidCrystal.h>

//---------------------- includs --------------------------------






//---------------------- global vars ----------------------------
//=========================== servo =============================
Servo servoBarrier;  // create servo object to control the barrier Servo.

//Servo positions
int pos_servoBarrierOpen = 65;
int pos_servoBarrierClose = 0;
//=========================== servo end =========================


//=========================== Display  ==========================
const int rs = 2, // 
          en = 4, 
          d4 = 5, 
          d5 = 6, 
          d6 = 7, 
          d7 = 8;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int numberOfFreeParkingSpaces = 10;
//=========================== Display end =======================


//=========================== RFID  =============================
const int rs = 2, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//=========================== RFID end ==========================




//---------------------- global vars end ------------------------








//----------------------- functions -----------------------------
//=========================== servo =============================
void servo() {
  //open barrier
  servoBarrier.write(pos_servoBarrierOpen);

  delay(1000);

  //close barrier
  servoBarrier.write(pos_servoBarrierClose);
  delay(1000);
}
//=========================== servo end =========================


//=========================== Display  ==========================
void setupDisplay() {
  lcd.begin(16,2);
}
//=========================== Display end =======================






//----------------------- functions end -------------------------








//setup runs once, when the Arduino is first oiwerd on.
void setup() {

  //=========================== servo =============================
  servoBarrier.attach(3);  // attaches the servo on pin 7 to the servo object (servoBarrier)
  servoBarrier.write(0);   // initialize servo stage 0 --> close Barrier
  //=========================== servo end =========================


  //=========================== Display  ==========================
  setupDisplay();
  lcd.print("Anzahl Freie: ");
  lcd.setCursor(0, 1);
  lcd.print(numberOfFreeParkingSpaces);
  //=========================== Display end =======================

  
  //=========================== RFID  =============================
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  //=========================== RFID end ==========================



}








//loop runs continuously after the setup() has completed.
void loop() {

  //=========================== servo =============================
  //servo(); // opens barrier and clos barrier after 1000 miliseconds.
  //=========================== servo end =========================


  //=========================== Display  ==========================
  
  lcd.setCursor(0, 1);
  lcd.print(numberOfFreeParkingSpaces);
  //=========================== Display end =======================




}
