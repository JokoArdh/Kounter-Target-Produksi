#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <RTClib.h> //define rtclib 
#include <SPI.h> //gatuane rtclib jadiwajib

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;
//define pin sensor proximiy dan buzzer
int proximityPin = D2;
int buzzerPin = D0;
float count = 0;
//membuat interval dan parameter waktu
const int interval = 1800000; // 30 menit dalam milisecond
unsigned long before = 0;
unsigned long lastRiset = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(proximityPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Status: ");

  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = rtc.now();
  int value = digitalRead(proximityPin);

  lcd.setCursor(0, 1);
  lcd.print(now.day());
  lcd.print("/");
  lcd.print(now.month());
  lcd.print("/");
  lcd.print(now.year());

if(value == 0){
  count++;
  digitalWrite(buzzerPin, HIGH);
}else{
  digitalWrite(buzzerPin, LOW);
}
//percabangan waktu untuk riset otomatis
unsigned long waktuNow = millis();
if (waktuNow - before >= interval)
{ 
 count = 0; //riset cont ke 0
 lastRiset = waktuNow; //update riset time
 before = waktuNow; //perbarui waktu terakhir u perhitungan berikutnya
}
lcd.setCursor(7, 0);
lcd.print(count);
delay(500);

}
