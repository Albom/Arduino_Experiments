#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <BigFont01_I2C.h>
#include <microDS18B20.h>

LiquidCrystal_PCF8574 lcd(0x27); //address
BigFont01_I2C big(&lcd); // construct large font object, passing to it the name of our lcd object
MicroDS18B20<A0> sensor;

int backlightPin = 5;

void setup()
{
  pinMode(backlightPin, OUTPUT);

  lcd.begin(16, 2);
  big.begin();
  lcd.clear();
  lcd.setBacklight(255);
}

void loop()
{
  sensor.requestTemp();
  delay(1000);
  lcd.clear();
  if (sensor.readTemp()) {
    analogWrite(backlightPin, 255);
    int16_t temp = sensor.getTempInt();

    if (temp >= 0) {

      char s_temp[8];
      memset(s_temp, 0, sizeof(s_temp));
      snprintf(s_temp, sizeof(s_temp) - 1, "%d", temp);

      switch (strlen(s_temp)) {
        case 1:
          big.writechar(0, 7, s_temp[0]);
          break;
        case 2:
          big.writechar(0, 5, s_temp[0]);
          big.writechar(0, 9, s_temp[1]);
          break;
        case 3:
          big.writechar(0, 2, s_temp[0]);
          big.writechar(0, 6, s_temp[1]);
          big.writechar(0, 11, s_temp[2]);
          break;

      }
    } else {
      big.writechar(0, 7, '0');
    }
  } else {
    analogWrite(backlightPin, 10);
    big.writechar(0, 2, 'O');
    big.writechar(0, 7, 'F');
    big.writechar(0, 12, 'F');
  }
}
