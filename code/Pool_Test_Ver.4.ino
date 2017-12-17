//Servo setup
#include <Servo.h> 
Servo servoLeft;
Servo servoRight;
int servoPos = 0;

//Relay and Fan
#define RELAY 2 //Connect to Digital Pin 2

//LED Strip
#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
#define FADESPEED 5

//Using the random function
long randomNumber;

void setup() {
  servoLeft.attach(8); //Digital Pin 8
  servoLeft.write(90); //Initial Angle
  servoRight.attach(9);
  servoRight.write(90);
  
  pinMode(RELAY, OUTPUT);     

  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  
  randomSeed(analogRead(0)); //A0 is unconnected, just initialising the random number generator with a fairly random input
}

void loop() {
  randomNumber = random(1,6); //random function returns a random number between min and max-1
  triggerAction();
}

void triggerAction(){
  if (randomNumber == 1) {
    forwardMove();
  }
  if (randomNumber == 2) {
    backwardMove();
  }
  if (randomNumber == 3) { 
    cwSpin();
  }
  if (randomNumber == 4) {
    ccwSpin();
  }
  if (randomNumber == 5) {
    colorCycle();
  }
}

void forwardMove() {
  servoLeft.write(0); //0 Degrees = Front Position
  servoRight.write(0);
  fanCycle();
}

void backwardMove() {
  servoLeft.write(180); //180 Degrees = Rear Position
  servoRight.write(180);  
  fanCycle();
}

void cwSpin() { //clock-wise spin
  servoLeft.write(0);
  servoRight.write(180);
  fanCycle();
}

void ccwSpin() { //counter clock-wise spin
  servoLeft.write(180);
  servoRight.write(0);
  fanCycle();
}

void fanCycle() {
  delay(1000); //Wait 1 Second, making sure servos complete rotations 
  digitalWrite(RELAY,HIGH);  // Turns Relay and Fan ON
  delay(8000);
  digitalWrite(RELAY,LOW);   // Turns Relay and Fan Off
  delay(2000);
  servoLeft.write(90);
  servoRight.write(90);  
  delay(1000);
}

void colorCycle() {
  int r, g, b;
 
  // fade from blue to violet
  for (r = 0; r < 256; r++) { 
    analogWrite(REDPIN, r);
    delay(FADESPEED);
  } 
  // fade from violet to red
  for (b = 255; b > 0; b--) { 
    analogWrite(BLUEPIN, b);
    delay(FADESPEED);
  } 
  // fade from red to yellow
  for (g = 0; g < 256; g++) { 
    analogWrite(GREENPIN, g);
    delay(FADESPEED);
  } 
  // fade from yellow to green
  for (r = 255; r > 0; r--) { 
    analogWrite(REDPIN, r);
    delay(FADESPEED);
  } 
  // fade from green to teal
  for (b = 0; b < 256; b++) { 
    analogWrite(BLUEPIN, b);
    delay(FADESPEED);
  } 
  // fade from teal to blue
  for (g = 255; g > 0; g--) { 
    analogWrite(GREENPIN, g);
    delay(FADESPEED);
  }
}

