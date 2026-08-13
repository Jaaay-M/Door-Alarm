#include <Arduino.h>

// ESP32 GPIO pins for the HC-SR04 ultrasonic sensor
#define echoPin 26
#define trigPin 27

// ESP32 GPIO pin for the buzzer
const int buzzer = 25;

// Variables for the ultrasonic sensor
long duration;
float distance;

void setup() {
  // Opens port 9600 for serial communication
  Serial.begin(9600);

  // Sets the HC-SR04 pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Sets the buzzer pin as an OUTPUT
  pinMode(buzzer, OUTPUT);

  // Make sure the buzzer starts off
  noTone(buzzer);
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sends a 10 microsecond trigger pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, with a 30 ms timeout
  duration = pulseIn(echoPin, HIGH, 30000);

  // If no echo was received, don't calculate a false distance
  if (duration == 0) {
    Serial.println("No echo received");
    noTone(buzzer);
    delay(100);
    return;
  }

  // Calculate the distance in centimetres
  distance = duration * 0.034 / 2;

  // Print the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If the distance is less than 10 cm, sound the buzzer
  if (distance < 10) {
    tone(buzzer, 1000);
    delay(500);
    tone(buzzer, 750);
    delay(500);
  } else {
    noTone(buzzer);
    delay(100);
  }
}