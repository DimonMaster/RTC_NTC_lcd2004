#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#include <microDS3231.h>
MicroDS3231 rtc;
#include <microDS18B20.h>
MicroDS18B20<2> sensor;     // указываем пин

#define MY_PERIOD 500  // период в мс
uint32_t tmr1; 
void setup() {
  sensor.setResolution(9);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}
void loop() {
  sensor.requestTemp();   // запросить температуру
  if (millis() - tmr1 >= 300) {  // ищем разницу
    tmr1 = millis();
  }

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

  
  lcd.setCursor(6,3);
  lcd.print(sensor.getTemp());  // выводим температуру
  lcd.write(223);         // символ градуса
  lcd.print("C  ");
  
 
}