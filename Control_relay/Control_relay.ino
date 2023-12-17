#include <Wire.h> 
#define RELAY_PIN D5 // Relay nối với Pin D5


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);

}

void loop() {
  /// Bật 
  digitalWrite(RELAY_PIN, HIGH);
  Serial.println("ON");
  delay(5000);  /// Nghỉ 5s

  /// Tắt
  digitalWrite(RELAY_PIN, LOW);
  Serial.println("OFF");
  delay(5000);  /// Nghỉ 5s
}
