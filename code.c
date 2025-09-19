#include <Servo.h>

Servo binServo;

// Sensor pins
#define IR_SENSOR 2
#define METAL_SENSOR 3
#define MOISTURE_SENSOR A0

int irValue, metalValue, moistureValue;

void setup() {
  Serial.begin(9600);
  binServo.attach(9);   // Servo motor pin
  pinMode(IR_SENSOR, INPUT);
  pinMode(METAL_SENSOR, INPUT);
}

void loop() {
  irValue = digitalRead(IR_SENSOR);
  metalValue = digitalRead(METAL_SENSOR);
  moistureValue = analogRead(MOISTURE_SENSOR);

  if(irValue == HIGH) {  // Object detected
    Serial.println("Object Detected");

    if(metalValue == HIGH) {
      Serial.println("Metal Waste");
      binServo.write(0);   // Move to metal section
    }
    else if(moistureValue > 500) {
      Serial.println("Wet Waste");
      binServo.write(90);  // Move to wet section
    }
    else {
      Serial.println("Dry/Plastic Waste");
      binServo.write(180); // Move to dry section
    }
    delay(2000); // wait before next detection
  }
}
