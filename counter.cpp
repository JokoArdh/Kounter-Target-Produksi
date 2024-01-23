#include <RTClib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;

int proximityPin = D2; 
int count = 0;

void setup() {
  // put your setup code here, to run once
  pinMode(proximityPin, INPUT);
  // Wire.begin(5,4);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Status");

  rtc.begin(); 
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(proximityPin);

  if(value == 0){ // jika daya low maka tidak terdeteksi
    count++;
  }
   lcd.setCursor(0, 1);
   lcd.print(count);
   delay(1000);

  DateTime now = rtc.now();
  if(now.minute() == 2 && now.second() == 120){
    count = 0;
  }
   lcd.setCursor(0, 1);
   lcd.print(count);

  
}


