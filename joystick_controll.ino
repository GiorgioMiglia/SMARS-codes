#include <AFMotor.h>

AF_DCMotor Rmotor(1);
AF_DCMotor Lmotor(2);

#define turnPin A2
#define velPin A1
int vel = 0;
int velocity = 0;
boolean front = true;

void setup() {
  pinMode(turnPin, INPUT);
  pinMode(velPin, INPUT);
  Serial.begin(9600);
  Lmotor.setSpeed(velocity);
  Rmotor.setSpeed(velocity);
  Rmotor.run(RELEASE);
  Lmotor.run(RELEASE);
}

void loop() {
  if (analogRead(velPin)<470 or analogRead(velPin)>570) {
    int acc = map(analogRead(velPin), 0, 1023, -10, 10);
    vel += acc;
    vel = max(vel, -20);
    vel = min(vel, 20);
    if (vel < 0) {
      front = false;
    } else {
      front = true;
    }
    if (abs(vel) <= 8) {
      Lmotor.run(RELEASE);
      Rmotor.run(RELEASE);
    } else {
      Lmotor.setSpeed(200);        // sets L motor speed
      Rmotor.setSpeed(200);        // sets R motor speed
      goStraight();
      delay(200);
    }
  }
  if (analogRead(turnPin) < 470) { //turn left
    while (analogRead(turnPin) < 470) {
      Rmotor.run(FORWARD);
      Lmotor.run(BACKWARD);
      Serial.println(analogRead(turnPin));
    }
    goStraight();
  }
  if (analogRead(turnPin) > 570) { // turn right
    while (analogRead(turnPin) > 570) {
      Rmotor.run(BACKWARD);
      Lmotor.run(FORWARD);
      Serial.println(analogRead(turnPin));
    }
    goStraight();
  }
  delay(100);
}

void goStraight() {
  if (front) {
    Rmotor.run(FORWARD);
    Lmotor.run(FORWARD);
  } else {
    Rmotor.run(BACKWARD);
    Lmotor.run(BACKWARD);
  }
}
