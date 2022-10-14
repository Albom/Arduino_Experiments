#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  8, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

int pinButtons[12] = {2, 6, 7, 8, 9, 10, 16, 14, 15, A0, A1, A2};

void setup() {
  for (int i = 0; i < 12; i++) {
    pinMode(pinButtons[i], INPUT_PULLUP);
  }
  

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
}

// Last state of the buttons
int lastButtonState[12] = {0,0,0,0,0,0,0,0,0,0,0,0};


void loop() {

  // Read pin values
  for (int index = 0; index < 12; index++)
  {
    int currentButtonState = !digitalRead(pinButtons[index]);
    if (currentButtonState != lastButtonState[index])
    {
      switch (index) {
        case 0: // UP
          if (currentButtonState == 1) {
            Joystick.setYAxis(-1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 1: // RIGHT
          if (currentButtonState == 1) {
            Joystick.setXAxis(1);
          } else {
            Joystick.setXAxis(0);
          }
          break;
        case 2: // DOWN
          if (currentButtonState == 1) {
            Joystick.setYAxis(1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 3: // LEFT
          if (currentButtonState == 1) {
            Joystick.setXAxis(-1);
          } else {
            Joystick.setXAxis(0);
          }
          break;
        default: // Button
          Joystick.setButton(index-4, currentButtonState);
      }
      lastButtonState[index] = currentButtonState;
    }
  }

  delay(10);
}
