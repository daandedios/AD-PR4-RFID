
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
#include <SPI.h>
#include <MFRC522.h>

//---------------------- includs --------------------------------


int check_card1;

int checkSW = 0;


//---------------------- global vars ----------------------------
//=========================== servo =============================
Servo servoBarrier;  // create servo object to control the barrier Servo.

//Servo positions
int pos_servoBarrierOpen = 65;
int pos_servoBarrierClose = 0;
//=========================== servo end =========================

int setTrue = 0;

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

//=========================== RFID ==============================
#define RST_PIN   9     // SPI Reset Pin
#define SS_PIN    10    // SPI Slave Select Pin

byte card_uid[] = {0x71, 0x99, 0x2A, 0x08};
byte batch_uid[] = {0x9A, 0xB8, 0x58, 0xD3};

int card_check = false;
int batch_check = false;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Instanz des MFRC522 erzeugen
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


//=========================== RFID ==============================
//=========================== RFID end ==========================

//=========================== timer =============================
void timer() {

}
//=========================== timer end =========================





//----------------------- functions end -------------------------








//setup runs once, when the Arduino is first oiwerd on.
void setup() {

  //=========================== servo =============================
  servoBarrier.attach(3);  // attaches the servo on pin 7 to the servo object (servoBarrier)
  servoBarrier.write(0);   // initialize servo stage 0 --> close Barrier
  //=========================== servo end =========================


  //=========================== Display  ==========================
  setupDisplay();
  lcd.print("Anzahl Freie P.: ");
  lcd.setCursor(0, 1);
  lcd.print(numberOfFreeParkingSpaces);
  //=========================== Display end =======================


  //=========================== RFID ==============================
   // Diese Funktion wird einmalig beim Start ausgeführt
  Serial.begin(9600);  // Serielle Kommunikation mit dem PC initialisieren
  SPI.begin();         // Initialisiere SPI Kommunikation
  mfrc522.PCD_Init();  // Initialisiere MFRC522 Lesemodul
  //=========================== RFID end ==========================
  
}








//loop runs continuously after the setup() has completed.
void loop() {

  //=========================== servo =============================
  //servo(); // opens barrier and clos barrier after 1000 miliseconds.
  //=========================== servo end =========================


  //=========================== Display  ==========================
  
  //=========================== Display end =======================

  //=========================== RFID ==============================
   // Diese Funktion wird in Endlosschleife ausgeführt
 
  // Nur wenn eine Karte gefunden wird und gelesen werden konnte, wird der Inhalt von IF ausgeführt
  // PICC = proximity integrated circuit card = kontaktlose Chipkarte
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() ) {
    Serial.print("Gelesene UID:");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      // Abstand zwischen HEX-Zahlen und führende Null bei Byte < 16
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    } 
    Serial.println();
 
    // UID Vergleichen mit card_uid
    card_check = true;
    for (int j=0; j<4; j++) {
      if (mfrc522.uid.uidByte[j] != card_uid[j]) {
        card_check = false;
      }
    }
 
    // UID Vergleichen mit batch_uid
    batch_check = true;
    for (int j=0; j<4; j++) {
      if (mfrc522.uid.uidByte[j] != batch_uid[j]) {
        batch_check = false;
            check_card1 = 1;
      }
    }


 
    if (card_check) {
  
      Serial.print("card");
      servo();

    if (checkSW == 0) {
      lcd.clear();
      lcd.print("Anzahl Freie P.: ");
      lcd.setCursor(0, 1);
      lcd.print("9");
      checkSW = 1;
    }
    else{
      lcd.clear();
      lcd.print("Bitte bezahlen:");
      lcd.setCursor(0, 1);
      lcd.print("10.-");
      delay(4000);
      lcd.clear();
      lcd.print("Anzahl Freie P.: ");
      lcd.setCursor(0, 1);
      lcd.print("10");
      checkSW = 0;
      
      }
      
    }
 
    if (batch_check) {
     Serial.print("batch");
     servo();
    }
 
    // Versetzt die gelesene Karte in einen Ruhemodus, um nach anderen Karten suchen zu können.
    mfrc522.PICC_HaltA();
    delay(1000);

  }
  //=========================== RFID end ==========================


}
