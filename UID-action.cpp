
#include <SPI.h>
#include <MFRC522.h>
 
#define RST_PIN   9     // SPI Reset Pin
#define SS_PIN    10    // SPI Slave Select Pin
 
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Instanz des MFRC522 erzeugen


byte card_uid[] = {0x71, 0x99, 0x2A, 0x08};
byte batch_uid[] = {0x9A, 0xB8, 0x58, 0xD3};
 
 
int card_check = false;
int batch_check = false;
 
 
void setup() {
  // Diese Funktion wird einmalig beim Start ausgeführt
  Serial.begin(9600);  // Serielle Kommunikation mit dem PC initialisieren
  SPI.begin();         // Initialisiere SPI Kommunikation
  mfrc522.PCD_Init();  // Initialisiere MFRC522 Lesemodul

}
 
void loop() {
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
      }
    }
 
    if (card_check) {
     Serial.print("card");
    }
 
    if (batch_check) {
     Serial.print("batch");
    }
 
    // Versetzt die gelesene Karte in einen Ruhemodus, um nach anderen Karten suchen zu können.
    mfrc522.PICC_HaltA();
    delay(1000);

  }
 
}