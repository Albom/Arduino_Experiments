#include <OneWire.h>
#include <LiquidCrystal_PCF8574.h>
#include <BigFont01_I2C.h> // modified
#include <DallasTemperature.h>

LiquidCrystal_PCF8574 lcd(0x27); //address
BigFont01_I2C big(&lcd); // construct large font object, passing to it the name of our lcd object
int backlightPin = 5; // PWM pin for the LCD backlight

#define ONE_WIRE_BUS A0
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);


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

  float tempC = 0;

  bool success = false;
  int nAttempts = 10;
  for (int attempt = 0; attempt < nAttempts; attempt++) {
    sensor.requestTemperatures();
    tempC = sensor.getTempCByIndex(0);
    if (tempC != DEVICE_DISCONNECTED_C) {
      success = true;
      break;
    }
  }

  if (success) {

    lcd.clear();
    analogWrite(backlightPin, 255);

    int16_t temp = (int16_t)tempC;

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
    lcd.clear();
    big.writechar(0, 2, 'O');
    big.writechar(0, 7, 'F');
    big.writechar(0, 12, 'F');
  }

  delay(1000);

}
