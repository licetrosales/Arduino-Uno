/* Programmcode: Echtzeituhr-Arduino-Projekt  
Beschreibung: Visualisierung von Datum und Uhrzeit mit einer RTC DS1307, die über I2C angeschlossen ist
Autor: Licet Ullmann
Erstellt: 13.12.2023
*/
// Bibliotheken
#include <LiquidCrystal_I2C.h>
#include <RTClib.h> // RTC-Bibliothek für die Verwendung einer Echtzeituhr
#define button 8
#define led 7
#define led_s 2


RTC_DS1307 rtc; // Erstellen eines RTC-Objektes für die DS3231 Echtzeituhr
LiquidCrystal_I2C lcd(0x27, 20, 4); // LCD-Adresse 0x27, 20 Zeichen, 4 Zeilen

char daysOfTheWeek[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};

bool cnt = 0;

// Datum und Uhrzeit an die serielle Schnittstelle senden
void datetime_serialT(){
  DateTime now =rtc.now(); // Einholen der aktuellen Zeit von der RTC
  
  Serial.print("Aktuelle Uhrzeit: ");
  Serial.print(now.year(), DEC); // Jahr ausgeben
  Serial.print('.');
  Serial.print(now.month(), DEC); // Monat ausgeben
  Serial.print('.');
  Serial.print(now.day(), DEC);  // Tag ausgeben
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC); // Stunde ausgeben
  Serial.print(':');
  Serial.print(now.minute(), DEC); // Minute ausgeben
  Serial.print(':');
  Serial.print(now.second(), DEC); // Sekunde ausgeben
  Serial.println();
}

// Datum und Uhrzeit auf dem LCD-Display anzeigen
void datetime_lcd(){
  DateTime now =rtc.now();

  // LCD display:
  lcd.setCursor(5,0);
  lcd.print(now.year(), DEC);  // Jahr ausgeben
  lcd.print('.');
  lcd.print(now.month(), DEC); // Monat ausgeben
  lcd.print('.');
  lcd.print(now.day(), DEC); // Tag ausgeben

  lcd.setCursor(6,1);
  lcd.print(now.hour(), DEC); // Stunde ausgeben
  lcd.print(':');
  lcd.print(now.minute(), DEC); // Minute ausgeben
  lcd.print(':');
  lcd.print(now.second(), DEC); // Sekunde ausgeben
 
  lcd.setCursor(0,3);
  lcd.print("Wochentag: ");
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]); // Wochentag ausgeben
}

void setup() {
  Serial.begin(9600); // Starten der seriellen Kommunikation
  // Initialisierung der RTC
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  // LCD Setup:
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
    digitalWrite(led, HIGH);          // RTC,LCD, LEDs einschalten,
    digitalWrite(led_s, HIGH);
    datetime_lcd();
    datetime_serialT();
    cnt = 1;
    digitalWrite(led_s, LOW);
    delay(1000); // Eine Sekunde warten, bevor die Schleife erneut durchlaufen wird
  } else {                                // sonst ...
    digitalWrite(led, LOW);           // RTC,LCD, LEDs ausschalten.
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
