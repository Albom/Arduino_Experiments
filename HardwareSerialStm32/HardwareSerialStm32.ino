
void setup() {
  Serial1.begin(9600);
  Serial1.println("Hello, world?");
}

void loop() {
  if (Serial1.available()) {
    Serial1.write(Serial1.read());
  }
}
