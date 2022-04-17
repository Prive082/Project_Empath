#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_Pin 9
MFRC522 mfrc522(SS_PIN, RST_Pin);
MFRC522::MIFARE_Key key;

int blockNum = 5;

byte password[16]= {"penis"};
byte bufferLen = 18;
byte readBlockData[18];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.print("Trying to write: ");
  Serial.println();
}

void loop() {
  for (byte i = 0; i < 6; i++){
    key.keyByte[i] = 0xFF;
  }
  // put your main code here, to run repeatedly:
  if(!mfrc522.PICC_IsNewCardPresent()){
    return;
  }
   if(!mfrc522.PICC_ReadCardSerial()){
    return;
   }
   Serial.println("Card detected");
   Serial.print("UID tag: ");
   String tag = "";
   byte letter;
   for(byte i = 0; i < mfrc522.uid.size; i++){
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     tag.concat(String(mfrc522.uid.uidByte[i], HEX));
   }
   Serial.println('\n');
   Serial.println("Writing to block....");
   WriteData(blockNum,password);

   Serial.print("\n");
   Serial.println("Reading from Data Block...");
   ReadDataFromBlock(blockNum, readBlockData);

    Serial.print("\n");
   Serial.print("Data in Block:");
   Serial.print(blockNum);
   Serial.print(" --> ");
   for (int j=0 ; j<16 ; j++)
   {
     Serial.write(readBlockData[j]);
   }
   Serial.print("\n");
}

void WriteData(int block, byte blockData[]){
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block,&key, &(mfrc522.uid) );
  if(status != MFRC522::STATUS_OK){
      Serial.println("Authentication failed");
      Serial.println(mfrc522.GetStatusCodeName(status));  
      return;
  } else {
    Serial.println("Authentication Failed");  
  }
  
  status = mfrc522.MIFARE_Write(block, blockData, 16);
  if(status != MFRC522::STATUS_OK){
    Serial.print("Writing to Block failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  } else {
    Serial.println("Data was written into Block successfully");
  }
}

void ReadDataFromBlock(int blockNum, byte readBlockData[]) 
{
  /* Authenticating the desired data block for Read access using Key A */
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK)
  {
     Serial.print("Authentication failed for Read: ");
     Serial.println(mfrc522.GetStatusCodeName(status));
     return;
  }
  else
  {
    Serial.println("Authentication success");
  }

  /* Reading data from the Block */
  status = mfrc522.MIFARE_Read(blockNum, readBlockData, &bufferLen);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Reading failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("Block was read successfully");  
  }
  
}
