#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#include <microDS3231.h>
MicroDS3231 rtc;
#include <GyverNTC.h>
GyverNTC therm(0, 10000, 3950);

#define MY_PERIOD 500 
uint32_t tmr1; 
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}
void loop() {
  float NTC = therm.getTempAverage();

  lcd.setCursor(1,0);
  lcd.print("time");

  String clock;
  clock += String(rtc.getHours());
  clock += ":";
  clock += String(rtc.getMinutes());
  clock += ":";
  clock += String(rtc.getSeconds());
  lcd.setCursor(0,1);
  lcd.print(clock);

  lcd.setCursor(13,0);
  lcd.print("date");

  String date;
  date += String(rtc.getDate());
  date += ".";
  date += String(rtc.getMonth());
  date += ".";
  date += String(rtc.getYear());
  lcd.setCursor(11,1);
  lcd.print(date);

  lcd.setCursor(7,2);
  lcd.print("temp");

  if (millis() - tmr1 >= MY_PERIOD) {  
    tmr1 = millis();
    lcd.setCursor(7,3);
    lcd.print(NTC);
  }
 
}