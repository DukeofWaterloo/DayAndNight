#include <Servo.h>

// Photoresistor Pin Setup
int topPhotoPin = 2;
int botPhotoPin = 4;

int topReading;
int botReading;

// Servo Control Setup
int currPos = 90;
int maxPos = 135;
int minPos = 45;
int turnStep = 5;
int turnTolerance = 20;

Servo solarServo;

void setup() {

  solarServo.attach(4);  // Attach physical servo to the servo object

  Serial.begin(9600);    // Start Serial Connection 
}

void loop() {

  Serial.println("--");

  // Read Analog Values from Voltage Dividers
  int topValue = analogRead(topPhotoPin);
  int botValue = analogRead(botPhotoPin);

  if (abs(topValue - botValue) > turnTolerance) { // System in Moveable Condition (above tolerance)

    if ((currPos + turnStep) < maxPos || (currPos - turnStep) > minPos) { // Motor is Moveable

      if (topValue > botValue) { // Stronger Light from Top
        currPos += turnStep;
        solarServo.write((currPos));
      }

      if (topValue < botValue) { // Stronger Light from Bottom
        currPos -= turnStep;
        solarServo.write((currPos));
      }
    }
  }

  Serial.print("Top Reading: ");
  Serial.println(topValue);

  Serial.print("Bottom Reading: ");
  Serial.println(botValue);

  Serial.println("--");

  delay(250);

}
