//developer:  Daan de Dios
//date:       2019-03-21
//function:   RFID Project, Mainberger-Hugelshofer-deDios

//************************ includs ******************************
//general arduino lib.
#include <Arduino.h>

//servo lib.
#include <Servo.h>

//display lib.
#include <LiquidCrystal.h>

//RFID lib.
#include <SPI.h>
#include <MFRC522.h>
//************************ includs end **************************




//************************ global Vars **************************************************

//=========================== servo =============================
// create servo object to control the barrier Servo.
Servo servoBarrier;

//Servo positions
int pos_servoBarrierOpen = 65;
int pos_servoBarrierClose = 0;
//=========================== servo end =========================

//=========================== Display  ==========================
// initialise LCD pins
const int rs = 2, // 
          en = 4, 
          d4 = 5, 
          d5 = 6, 
          d6 = 7, 
          d7 = 8;

// create LCD instanze with pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// set number of free parking spaces
int numberOfFreeParkingSpaces = 10;
//=========================== Display end =======================

//=========================== RFID ==============================
// set SPI Reset Pin
#define RST_PIN   9     

// set SPI Slave Select Pin
#define SS_PIN    10    

// define RFID tags UIDs
byte card_uid[] = {0x71, 0x99, 0x2A, 0x08};
byte batch_uid[] = {0x9A, 0xB8, 0x58, 0xD3};
byte batch2_uid[] = {0x05 0xC7 0x53 0xD3};

// initialise some check vars
int card_check = false;
int batch_check = false;
int batch2_check= false;
int checkSW = 0;

// Instanz des MFRC522 erzeugen
MFRC522 mfrc522(SS_PIN, RST_PIN);
//=========================== RFID end ==========================


//************************ global Vars end **********************************************





//************************ functions ****************************************************
//=========================== servo =============================
void servo() {
  //open barrier
  servoBarrier.write(pos_servoBarrierOpen);

  // wait 2 seconds
  delay(2000);

  //close barrier
  servoBarrier.write(pos_servoBarrierClose);

  //wait 1 second --> for looping the function servo()
  delay(1000);
}
//=========================== servo end =========================

//=========================== Display  ==========================
void setupDisplay() {
  // begin lcd display at position 16,2
  lcd.begin(16,2);
}
//=========================== Display end =======================

//=========================== RFID ==============================
void RFID {
  // RFID function

}
//=========================== RFID end ==========================

//=========================== timer =============================
void timer() {
  // timer function

}
//=========================== timer end =========================



//************************ functions end ************************************************









//setup runs once, when the Arduino is first oiwerd on.
void setup() {

  //=========================== servo =============================
  // attaches the servo on pin 7 to the servo object (servoBarrier)
  servoBarrier.attach(3);
  
  // initialize servo stage 0 --> close Barrier
  servoBarrier.write(0);
  //=========================== servo end =========================

  //=========================== Display  ==========================
  // run function setup display
  setupDisplay();

  // display output on LCD screen
  lcd.print("Anzahl Freie P.: ");
  lcd.setCursor(0, 1);
  lcd.print(numberOfFreeParkingSpaces);
  //=========================== Display end =======================

  //=========================== RFID ==============================
  // begin serial communication with pc (initialisation)
  Serial.begin(9600);

  // initialisation of SPI communication
  SPI.begin();

  // initialisation of the MFRC522 read modul
  mfrc522.PCD_Init();
  //=========================== RFID end ==========================
  
}




//loop runs continuously after the setup() has completed.
void loop() {

  //=========================== servo =============================
  // cals servo function
  //servo();
  //=========================== servo end =========================

  //=========================== Display  ==========================
  // lcd.print("Hallo Welt");
  //=========================== Display end =======================


  //=========================== RFID ============================== 
  // PICC = kontaktlose Chipkarte
  // if new tag is present print out the UID of the tag to the serial monitor
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() ) {
    Serial.print("UID:");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      // space between HEX and beginning zero by byte < 16
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    } 
    Serial.println();
 
    // UID check compare 1
    card_check = true;
    for (int j=0; j<4; j++) {
      if (mfrc522.uid.uidByte[j] != card_uid[j]) {
        card_check = false;
      }
    }
 
    // UID check compare 2
    batch_check = true;
    for (int j=0; j<4; j++) {
      if (mfrc522.uid.uidByte[j] != batch_uid[j]) {
        batch_check = false;
      }
    }

    // UID check compare 3
    batch2_check = true;
    for (int j=0; j<4; j++) {
      if (mfrc522.uid.uidByte[j] != batch2_uid[j]) {
        batch2_check = false;
      }
    }
 
    if (card_check) { 
      // call servo function 
      Serial.print("card");
      servo();

    if (checkSW == 0) {
      // print output
      lcd.clear();
      lcd.print("Anzahl Freie P.: ");
      lcd.setCursor(0, 1);
      lcd.print("9");

      // set checking var to 1
      checkSW = 1;
    }
    else{
      // print output
      lcd.clear();
      lcd.print("Bitte bezahlen:");
      lcd.setCursor(0, 1);
      lcd.print("10.-");
      delay(3000);
      lcd.clear();
      lcd.print("Anzahl Freie P.: ");
      lcd.setCursor(0, 1);
      lcd.print("10");

      // set checking var to 0
      checkSW = 0;

      }
    }
 
    if (batch_check) {
     Serial.print("batch");
     servo();
    }

    if (batch2_check) {
      Serial.print("batch");
      servo();
    }
 
    // set delay to tag and programm
    mfrc522.PICC_HaltA();
    delay(1000);

  }
  //=========================== RFID end ==========================
}