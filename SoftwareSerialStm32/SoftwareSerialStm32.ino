
#include <SoftwareSerial.h>

SoftwareSerial mySerial(A1, A2); // RX, TX

void setup() {
  mySerial.begin(4800);
  mySerial.println("Hello, world?");
}

void loop() {
  if (mySerial.available()) {
    mySerial.write(mySerial.read());
  }
}
