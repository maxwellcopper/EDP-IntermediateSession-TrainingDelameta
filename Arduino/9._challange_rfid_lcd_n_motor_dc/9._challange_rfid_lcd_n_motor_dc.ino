#include <LiquidCrystal_I2C.h>
#include<SPI.h>
#include<MFRC522.h>

#define A1 5  // Motor A pins
#define A2 6

//inisialisi variable
#define SS_PIN 10
#define RST_PIN 9

String uidString;
int buzz = 7;
int ir = 2;
MFRC522 mfrc522(SS_PIN, RST_PIN); //create mfrc522 instance

//lcd an
LiquidCrystal_I2C lcd(0x27, 16, 2);

int x = 100;
void bener(){
  digitalWrite(buzz, HIGH);
  delay(150);
  digitalWrite(buzz, LOW);
  delay(50);
  digitalWrite(buzz, HIGH);
  delay(150);
  digitalWrite(buzz, LOW);
  delay(50);
}

void salah(){
  digitalWrite(buzz, HIGH);
  delay(300);
  digitalWrite(buzz,LOW);
  delay(50);
}

void setup()
{
  Serial.begin(115200);
  lcd.begin();

  
  SPI.begin(); //initiate SPI BUS
  mfrc522.PCD_Init();
  pinMode(buzz, OUTPUT);
  Serial.println("Tempelkan Kartu");
  lcd.clear(); //Menghapus Karakter di LCD
  lcd.setCursor(0,0);
  lcd.print("Tempelkan Kartu");
  lcd.setCursor(0,1);
  lcd.print("Gerbang tertutup");
  pinMode(ir, INPUT);
  Serial.println("gerbang ketutup");

  //motor setup
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
}

 
void loop()
{
  if(mfrc522.PICC_IsNewCardPresent()){
      readRFID();
      Serial.print("ID : ");
      Serial.println(uidString);
      if(uidString== "5-8D-4-AE" || uidString == "5-8F-8E-BF"){ //ktp aing
         bener();
         buka();
         Serial.println("berhasil1");
         lcd.clear(); //Menghapus Karakter di LCD
         lcd.setCursor(0,0);
         lcd.print("Berhasil");
         delay(500);
         lcd.clear(); //Menghapus Karakter di LCD
         lcd.setCursor(0,0);
         lcd.print("Gerbang Terbuka");
         lcd.setCursor(0,1);
         lcd.print("Silahkan Masuk!");         
         Serial.println("Masuuuk oii");
         Serial.println("Gerbang Kebuka");
         while(1){
          int state = digitalRead(ir);
          if (state == 1){
            state =1;
          }else {
            tutup();
            lcd.clear(); //Menghapus Karakter di LCD
            lcd.setCursor(0,0);
            lcd.print("Gerbang Tertutup");
            delay(3000);
            lcd.clear(); //Menghapus Karakter di LCD
            lcd.setCursor(0,0);
            lcd.print("Tempelkan Kartu!");
            lcd.setCursor(0,1);
            lcd.print("Gerbang Tertutup");
            Serial.println("Gerbang ketutup");
            break;
          }
         }
      }
      else{
        salah();
        diem();
        lcd.clear(); //Menghapus Karakter di LCD
        lcd.setCursor(0,0);
        lcd.print("tidak terdaftar");
        lcd.setCursor(0,1);
        delay(3000);
        lcd.clear(); //Menghapus Karakter di LCD
        lcd.setCursor(0,0);
        lcd.print("Tempelkan Kartu!");
        lcd.setCursor(0,1);
        lcd.print("Gerbang Tertutup");
        
        Serial.println("ga terdaftar");
        Serial.println("Gerbang ketutup");
      }
    }
  
}


void buka(){
  analogWrite(A1, 255);
  analogWrite(A2, 0);
  delay(x);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
}

void tutup(){
  analogWrite(A1, 0);
  analogWrite(A2, 210);
  delay(x);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
}

void diem(){
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
}


void readRFID(){  
  mfrc522.PICC_ReadCardSerial();
  uidString = String(mfrc522.uid.uidByte[0],HEX) + "-" +
              String(mfrc522.uid.uidByte[1],HEX) + "-" +
              String(mfrc522.uid.uidByte[2],HEX) + "-" +
              String(mfrc522.uid.uidByte[3],HEX);
              uidString.toUpperCase();
  }
