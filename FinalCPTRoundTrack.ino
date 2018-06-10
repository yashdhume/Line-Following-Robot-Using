/**********************Line Following Robot CPT*********************************
  This code is using and Aurdino, aurdomoto and the Pololu QTR Sensor Library.
  It will follow a line on a track made of black tape on a white bristol board.

  Created by: Yash Dhume
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
int turnSpeed = 128; // speed for turning
int reverseSpeed = 64; //speed when the robot reverses
int stopSpeed = 0; //speed of that motor will be stoped
int sensorMiddleNumber = 300; // this is the middle number of white and black that the anolgue sensor senses
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
    driveArdumoto(motorB, forward, fowardSpeed);//MotorB foward at 75 speed
  }
  else if ((analogRead(leftSensor) < sensorMiddleNumber) && (analogRead(rightSensor) > sensorMiddleNumber)) {
    //Robot will turn right once its sensos black
    driveArdumoto(motorA, forward, stopSpeed);//motor A stops
    driveArdumoto(motorB, forward, turnSpeed); //motor b spins 128 speed
  }
  else if ((analogRead(leftSensor) > sensorMiddleNumber) && (analogRead(rightSensor) < sensorMiddleNumber)) {
    //Robot will turn left once its sensos black
    driveArdumoto(motorA, forward, turnSpeed); //motorA spins 128 speed
    driveArdumoto(motorB, forward, stopSpeed);//MotorB stops
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
