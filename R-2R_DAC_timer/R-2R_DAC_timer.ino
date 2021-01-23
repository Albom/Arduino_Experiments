#include <TimerOne.h>


void setup() {

  DDRD = -1;
  PORTD = 0;

  Timer1.initialize(1);
  Timer1.attachInterrupt(dac);

}

void dac()
{
  PORTD++;
}

void loop() {

  while (1);

}
