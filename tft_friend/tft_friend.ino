#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


void setup() {
  tft.begin(0x9340);
  tft.setRotation(0);
  tft.fillScreen(BLUE);
  tft.setTextSize(2);
  tft.setTextColor(WHITE, BLUE);
//  tft.println("Hello, Mark!");
   Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char x = Serial.read();
    tft.print(x);
  }
}
