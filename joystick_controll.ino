#include <AFMotor.h> 

AF_DCMotor Rmotor(1);
AF_DCMotor Lmotor(2);

#define button A0
#define turnPin A2
#define velPin A1
int vel = 0;
int velocity = 0;
boolean front = true;

void setup() {
  pinMode(button, INPUT);
  pinMode(turnPin, INPUT);
  pinMode(velPin, INPUT);
  Serial.begin(9600);
  Lmotor.setSpeed(velocity);    
  Rmotor.setSpeed(velocity);
  Rmotor.run(RELEASE);         
  Lmotor.run(RELEASE);
}

void loop() {
 /* if(digitalRead(button)) {
    toggleMotors();
  }*/
 // Serial.println(analogRead(velPin));
  if(analogRead(velPin)<470 or analogRead(velPin)>570) {  
    int acc = map(analogRead(velPin), 0, 1023, -10, 10);
    vel += acc;
    vel = max(vel, 250);
    vel = min(vel, 250);
    if (vel<0) { 
      vel = min(vel,-120);
      velocity = -vel;
      front = false; 
    } else {
      vel = max(vel, 120);
      velocity = vel;
      front= true;
    }   
    Lmotor.setSpeed(velocity);        // sets L motor speed
    Rmotor.setSpeed(velocity);        // sets R motor speed
    goStraight();
    Serial.print(velocity);
    Serial.print("        ");
    Serial.println(vel);
  }
  if(analogRead(turnPin)<470) {  //turn left
    while(analogRead(turnPin)<470){
      Rmotor.run(FORWARD);         
      Lmotor.run(BACKWARD);
      Serial.println("L");
    }
    goStraight();  
  }
  if(analogRead(turnPin)>570) { // turn right
    while(analogRead(turnPin)>570){
      Rmotor.run(BACKWARD);         
      Lmotor.run(FORWARD);
      Serial.println("R");
    }
    goStraight();  
  }
  
  delay(100);
}

void goStraight() {
  if(front) {
    Rmotor.run(FORWARD);         
    Lmotor.run(FORWARD);    
  } else {
    Rmotor.run(BACKWARD);         
    Lmotor.run(BACKWARD);
  }
}

/*void toggleMotors(){
  Rmotor.run(RELEASE);         
  Lmotor.run(RELEASE); 
  Serial.println("svbh");
  delay(100); 
}*/
