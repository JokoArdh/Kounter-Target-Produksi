#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <ESP8266WiFi.h> // library untuk memanggil wifi di esp8266
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

#define BOTtoken "6735451040:AAGJarLPTmso-OzDEvkldUxLOrpIDse_TnY"
#define idChat "6636819964"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

LiquidCrystal_I2C lcd(0x27, 16, 2);
//define pin sensor proximiy dan buzzer
int proximityPin = D2;
int buzzerPin = D0;
float count = 0;
//membuat interval dan parameter waktu
const int interval = 180000; // 30 menit dalam milisecond
unsigned long before = 0;
unsigned long lastRiset = 0;
unsigned long lastMessageTime = 0;

//membuat koneksi wifi
const char* ssid = "Joko";
const char* password = "ipxr1234";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  Serial.println();
  Serial.println();
  Serial.print("connecting to :");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setTrustAnchors(&cert);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
  }
  Serial.println();
  Serial.println("Wifi Connected");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
  

  pinMode(proximityPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Status: ");


  //config NTP untuk telegram
   Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(proximityPin);

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

  lastMessageTime = interval;
 String pesan = "jumlah hasil sensor " + String(count);
  bot.sendMessage(idChat, pesan, "");
  Serial.println("pesan terkirim ke telegram");

 count = 0; //riset cont ke 0
 lastRiset = waktuNow; //update riset time
 before = waktuNow; //perbarui waktu terakhir u perhitungan berikutnya
}
lcd.setCursor(7, 0);
lcd.print(count);
delay(500);

}

