#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Server ready...");
}

void loop() {
  if (Serial.available() > 0) {

    String message = Serial.readStringUntil('\n');

    String modifiedMessage = message + " [Modified by Server]";
    

    Serial.println(modifiedMessage);
  }
  delay(100);
}
