const int IR_sensor1 = 7; // IR sensor 1 connected to digital pin 7
//const int IR_sensor2 = 8; // IR sensor 2 connected to digital pin 8

void setup() {
  pinMode(IR_sensor1, INPUT); // Set IR sensor 1 pin as input
//  pinMode(IR_sensor2, INPUT); // Set IR sensor 2 pin as input
  Serial.begin(9600); // Start serial communication
}

void loop() {
  int sensorValue1 = digitalRead(IR_sensor1); // Read IR sensor 1 value
//  int sensorValue2 = digitalRead(IR_sensor2); // Read IR sensor 2 value
  Serial.print("Sensor 1: ");
  Serial.println(sensorValue1);
//  Serial.print("  Sensor 2: ");
//  Serial.println(sensorValue2); // Print IR sensor values to serial monitor
  delay(3000); // Delay 100ms
}
