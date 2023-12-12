/* Programmcode: Echtzeituhr-Arduino-Projekt  
Autor: Licet Ullmann
Erstellt: 13.12.2023
*/
// Bibliotheken
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#define button 8
#define led 7
#define led_s 2

// Erstell rtc and lcd Object:
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 20, 4); // LCD-Adresse 0x27, 20 Zeichen, 4 Zeilen

char daysOfTheWeek[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};

byte customChar[] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

bool cnt = 0;

void datetime_serialT(){
  DateTime now =rtc.now();
  
  Serial.print("Aktuelle Uhrzeit: ");
  Serial.print(now.year(), DEC);
  Serial.print('.');
  Serial.print(now.month(), DEC);
  Serial.print('.');
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
}

void datetime_lcd(){
  DateTime now =rtc.now();

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
}

void setup() {
  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  // LCD setup:
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("....................");
  lcd.setCursor(4,2);
  lcd.print("Guten Tag :)");
  lcd.setCursor(0,3);
  lcd.print("....................");

  delay(3000);

  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(led_s, OUTPUT);
}


void loop() {

  if (digitalRead(button) == HIGH) {  // Wenn auf der Eingangsleitung des Tasters HIGH anliegt ...
    digitalWrite(led, HIGH);          // LED anschalten,
    digitalWrite(led_s, HIGH);
    datetime_lcd();
    datetime_serialT();
    cnt = 1;
    digitalWrite(led_s, LOW);
    delay(1000);
  } else {                                // sonst ...
    digitalWrite(led, LOW);           // LED ausschalten.
    if (cnt == 1){
      lcd.clear();
      lcd.setCursor(4,2);
      lcd.print("Wiedersehen ...");
      cnt = 0;
      delay(1500);
    }else {
      lcd.clear();
    }
    
  }
   
   
}
