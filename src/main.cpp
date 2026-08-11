#include <Arduino.h>

// Gives the pin numbers for the ultrasonic sensor
#define echoPin 2
#define trigPin 3

// Variables for the ultrasonic sensor
long duration;
float distance;

const int buzzer = 8; // Buzzer connected to pin 9

void setup() {

  // Opens port 9600 for serial communication
  Serial.begin(9600);

  // Sets the trigPin as an OUTPUT and the echoPin as an INPUT
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Sets the buzzer pin as an OUTPUT
  pinMode(buzzer, OUTPUT);

}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Waits for 1 second before the next loop

  // If the distance is less than 10 cm, the buzzer will sound
  while (distance < 10) {
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(500); // Wait for 500 milliseconds
    tone(buzzer, 750); // Send 1KHz sound signal...
    delay(500); // Wait for 500 milliseconds
  }

}