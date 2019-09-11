#include <AFMotor.h>  
#include <NewPing.h>

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 250 
#define MAX_SPEED 140 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

boolean goesForward = false;
int distance = 0;
int speedSet = 0;
int x = 2;
int distanceR = 0;
int distanceL =  0;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
  
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
void setup() {
   delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}
 

void loop() {
 distance = readPing();
 if(distance<=25)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  turnLeft();
  distanceL = readPing();
  delay(200);
  turnRightAll();
  distanceR = readPing();
  delay(200);
  


  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
 }
 distance = readPing();
}



  void moveStop() {
   distance = readPing();
  
    motor1.run(RELEASE); 
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    delay (100);
    } 

                  int readPing() { 
                  delay(70);
                  int cm = sonar.ping_cm();
                  if(cm==0)
                  {
                    cm = 250;
                  }
                  return cm;
                }
  
void moveForward() {
   distance = readPing();

// goesForward=true;
 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD); 
    motor4.run(FORWARD);     
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(2);
   }
  }
}


void moveBackward() {

    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(2);
  }
}  

void turnLeft() {
 


  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);     
   distanceL = readPing();
  delay(1320);
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);      

} 
 
void turnRight() {
  
  motor1.run(BACKWARD);     
  motor2.run(FORWARD);  
  motor3.run(BACKWARD);
  motor4.run(FORWARD);   
  distanceR = readPing();
  delay(1320);
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}  

void turnRightAll(){

  motor1.run(BACKWARD);     
  motor2.run(FORWARD);  
  motor3.run(BACKWARD);
  motor4.run(FORWARD);    
  distanceR = readPing();
  delay (2500);
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
