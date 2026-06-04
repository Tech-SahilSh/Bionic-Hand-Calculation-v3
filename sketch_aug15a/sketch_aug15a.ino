#include <Servo.h>

#define NUM_SERVOS 5

Servo thumbServo, indexServo, middleServo, ringServo, pinkyServo;

const int THUMB_PIN = 3;
const int INDEX_PIN = 5;
const int MIDDLE_PIN = 6;
const int RING_PIN = 9;
const int PINKY_PIN = 10;

const int THUMB_CLOSE_POS = 0;
const int INDEX_CLOSE_POS = 160;
const int MIDDLE_CLOSE_POS = 160;
const int RING_CLOSE_POS = 0;
const int PINKY_CLOSE_POS = 0;

const int THUMB_OPEN_POS = 90;
const int INDEX_OPEN_POS = 0;
const int MIDDLE_OPEN_POS = 0;
const int RING_OPEN_POS = 170;
const int PINKY_OPEN_POS = 170;

void setup() {
  Serial.begin(9600);
  thumbServo.attach(THUMB_PIN);
  indexServo.attach(INDEX_PIN);
  middleServo.attach(MIDDLE_PIN);
  ringServo.attach(RING_PIN);
  pinkyServo.attach(PINKY_PIN);

  // Keep all fingers folded at start
  setIndividualFingerPositions(0b00000);
}

void loop() {
  if (Serial.available() > 0) {
    byte fingerStates = Serial.read();
    setIndividualFingerPositions(fingerStates);
  }
}

void setIndividualFingerPositions(byte states) {
  thumbServo.write((states & (1 << 0)) ? THUMB_OPEN_POS : THUMB_CLOSE_POS);
  indexServo.write((states & (1 << 1)) ? INDEX_OPEN_POS : INDEX_CLOSE_POS);
  middleServo.write((states & (1 << 2)) ? MIDDLE_OPEN_POS : MIDDLE_CLOSE_POS);
  ringServo.write((states & (1 << 3)) ? RING_OPEN_POS : RING_CLOSE_POS);
  pinkyServo.write((states & (1 << 4)) ? PINKY_OPEN_POS : PINKY_CLOSE_POS);
  delay(15);
}
