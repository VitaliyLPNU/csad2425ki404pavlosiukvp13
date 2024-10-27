#include <Arduino.h>

void setup() {
  Serial.begin(9600);  // Ініціалізація UART з baud rate 9600
  while (!Serial) {
    ;  // Чекаємо на підключення
  }
  Serial.println("Server ready...");
}

void loop() {
  if (Serial.available() > 0) {
    // Отримуємо повідомлення від клієнта
    String message = Serial.readStringUntil('\n');
    // Модифікуємо повідомлення
    String modifiedMessage = message + " [Modified by Server]";
    
    // Відправляємо модифіковане повідомлення назад клієнту
    Serial.println(modifiedMessage);
  }
  delay(100);  // Невелика затримка для стабільної передачі
}