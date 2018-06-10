/**********************Line Following Robot CPT*********************************
  This code is using and Aurdino, aurdomoto and the Pololu QTR Sensor Library.
  It will follow a line on a track made of black tape on a white bristol board.

  Created by: Yash Dhume, Kelley Wong, Filip Jedrusiak
  Teacher: Mr. Kolch
  Course Code: TEJ 4M1
  Date Started: April 25th 2017
  Date Completed: May 11th 2017
********************************************************************************/

//*******************DECLARATION******************************
int forward = 0; //direction of motor spin foward
int reverse = 1; //direction of motor spin reverse
int motorA = 0; //Left motor
int motorB = 1; //Right motor
int leftMotorDirection = 12; // direction control for motor A
int rightMotorDirection = 13; // direction\control for motor B
int speedPwnLeft = 3; // PWM control (speed) for motor A
int speedPwnRight = 11; // PWM control (speed) for motor B
int leftSensor = A0; //Left analog sensor
int rightSensor = A1; //Right analog sensor
int fowardSpeed = 75; //speed for the foward
int turnSpeed = 128;//speed when it turns
int reverseSpeed = 64; //speed when reverses
int stopSpeed = 0; //speed of that motor will be stoped
int sensorMiddleNumber = 300; // this is the middle number of white and black that the anolgue sensor senses
int killSwitch = 0; //stop robot counter
//*************************************************************


void setup() {//setsup the sensors and motors so aurdino understands if it is an input or output
  pinMode(speedPwnLeft, OUTPUT); //output for the motors
  pinMode(speedPwnRight, OUTPUT); //output for the motors
  pinMode(leftMotorDirection, OUTPUT); //output for the motors
  pinMode(rightMotorDirection, OUTPUT); //output for the motors
  pinMode(leftSensor, INPUT); //input for sensor
  pinMode(rightSensor, INPUT); //input for sensor
  Serial.begin(9600);//Begin output to console


}

void loop() {//main code which will give you drive the robot
  Serial.print("Left");//prints the word left in serual monitor
  Serial.println(analogRead(leftSensor));//prints left sensor in serial monitor
  Serial.print("Right");//prints right wird in serual monitor
  Serial.println(analogRead(rightSensor));//print right word in the serial Monitor

  if ((analogRead(leftSensor) < sensorMiddleNumber) && (analogRead(rightSensor) < sensorMiddleNumber)) {
    //Robot will move forward when on it sensoes white
    driveArdumoto(motorA, forward, fowardSpeed);//MotorA foward at 75 speeed
    driveArdumoto(motorB, forward, fowardSpeed);//MotorB foward at 75 speeed
  }
  else if ((analogRead(leftSensor) < sensorMiddleNumber) && (analogRead(rightSensor) > sensorMiddleNumber)) {
    //Robot will turn right once its sensos black
    driveArdumoto(motorA, forward, stopSpeed);//MotorA stops
    driveArdumoto(motorB, forward, turnSpeed); //MotorB foward at 128 speeed
  }
  else if ((analogRead(leftSensor) > sensorMiddleNumber) && (analogRead(rightSensor) < sensorMiddleNumber)) {
    //Robot will turn left once its sensos black
    driveArdumoto(motorA, forward, turnSpeed); //motorA spins  foroward 128 speed
    driveArdumoto(motorB, forward, stopSpeed);//motorB stops
  }

  else if ((analogRead(leftSensor) > sensorMiddleNumber ) && (analogRead(rightSensor) > sensorMiddleNumber) ) {
    while (killSwitch == 1 ) {//when kill switch is one robot will stop
      driveArdumoto(motorA, forward, stopSpeed);//motorA stops
      driveArdumoto(motorB, forward, stopSpeed);//motorB stops
    }
    driveArdumoto(motorA, reverse, turnSpeed); //motorA spins back at 128speed
    driveArdumoto(motorB, reverse, turnSpeed); //motorb spins back at 128 speed
    delay(250);//stops code from going to the next  line for 250 millisecounds
    driveArdumoto(motorA, forward, stopSpeed);//motorA stops
    driveArdumoto(motorB, forward, stopSpeed);//motorB stops
    

  
    killSwitch=1;//makes the counter go up so it stops the next time
reverseDrive(motorA, motorB, forward, reverse);//calls reverse methid
  }

}
void reverseDrive(int motorA, int motorB, int forward, int reverse) {//robot goes right until left sensor hits black

  driveArdumoto(motorA, reverse, 76);//motora reverser right with 76 speed
  driveArdumoto(motorB, forward, reverseSpeed); //motorB foward with 64 speed
  if ((analogRead(leftSensor) < sensorMiddleNumber) && (analogRead(rightSensor) > sensorMiddleNumber)) {//when left seonsr right senso r hits 
  return;//return back to loop
  }
  else {
    reverseDrive(motorA, motorB, forward, reverse);//recuresice back to reversedrive
  }

}
void driveArdumoto(byte motor, byte direction, byte speed) { // driveArdumoto drives motor in direction at speed which is given in the main loop

  if (motor == motorA) { //when motorA is called in the main loop
    digitalWrite(leftMotorDirection, direction);//determins the direction
    analogWrite(speedPwnLeft, speed);//detemins the speed
  }
  else if (motor == motorB) { //when motorB is called in the main loop
    digitalWrite(rightMotorDirection, direction);//detemins the direction
    analogWrite(speedPwnRight, speed);//detemins the speed
  }

}
