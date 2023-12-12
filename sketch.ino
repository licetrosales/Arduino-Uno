/* Programmcode: Echtzeituhr-Arduino-Projekt  
Autor: Licet Ullmann
Erstellt: 13.12.2023
*/
// Bibliotheken
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#define schalter 8
#define led 7
// Erstell rtc and lcd Object:
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 20, 4); // LCD-Adresse 0x27, 20 Zeichen, 4 Zeilen
char daysOfTheWeek[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};

bool zustand = 0;

void setup() {
  Serial.begin(115200);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  // LCD setup:
  lcd.init();
  lcd.backlight();


  pinMode(schalter, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  // Date Time
  DateTime now =rtc.now();
  digitalWrite(led, HIGH);
  Serial.print("Current time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();


  // LCD display:
  lcd.setCursor(0,0);
  lcd.print("Aktuelle Uhrzeit: ");
  lcd.setCursor(6,1);
  
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);

  lcd.setCursor(0,2);
   lcd.print("Datum: ");
  lcd.print(now.year(), DEC);
  lcd.print('.');
  lcd.print(now.month(), DEC);
  lcd.print('.');
  lcd.print(now.day(), DEC);

  
  

  lcd.setCursor(0,3);
  lcd.print("Wochentag: ");
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  digitalWrite(led, LOW);
  delay(1000);
  
   
}
