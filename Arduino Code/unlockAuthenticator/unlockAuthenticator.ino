#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_Pin 9
MFRC522 mfrc522(SS_PIN, RST_Pin);

int blockLocation = 5;
MFRC522::MIFARE_Key key;
byte bufferLen = 18;
byte passkey[18];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Put your card near the reader");
  Serial.println();
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
 

  if(!mfrc522.PICC_IsNewCardPresent()){
    //Serial.println("cock");
    return;
  }
   if(!mfrc522.PICC_ReadCardSerial()){
    //Serial.println("balls");
    return;
   }
   
  for (byte i = 0; i < 6; i++){
    key.keyByte[i] = 0xFF;
  }
   //Serial.print("UID tag: ");
   String tag = "";
   byte letter;
   for(byte i = 0; i < mfrc522.uid.size; i++){
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     tag.concat(String(mfrc522.uid.uidByte[i], HEX));
   }
   Serial.println('\n');

   byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockLocation, &key, &(mfrc522.uid));
   
   if(status != MFRC522::STATUS_OK){
    Serial.print("Authentication failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
   } else {
    Serial.println("Authentication success");
   } 

   status = mfrc522.MIFARE_Read(blockLocation, passkey, &bufferLen);

     if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Reading failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  } else {
    Serial.println("Block was read successfully");  
  }

  String passcode = "";
  for(int i = 0; i < 16; i++){
    passcode.concat(char(passkey[i]));
  }
  Serial.print("Data in Block: ");
  Serial.println(passcode);

  if(passcode == "penis"){
    digitalWrite(7, HIGH);
    Serial.println("Passcode Accepted");
  } else {
    Serial.println("brian");
    delay(2000);
    digitalWrite(7,LOW);
    Serial.println("Outputting Shock");
    delay(200);
    digitalWrite(7,HIGH);
    Serial.println("OFFF");
  }
}
  
