#include <SPI.h>
#include "Encoder.h"
#include "kinematics.hpp"
#include "helper.h"
#include <ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Float32.h>

motorClass motor1;
motorClass motor2;
motorClass motor3;
//motorClass motor4;

void callback(const std_msgs::Float32MultiArray& inputVelocity){
  
  //Fill in code to set motor controller setpoints
  digitalWrite(10,HIGH -  digitalRead(10)) ;
  
  motor1.setMotorVel( constrain(150*inputVelocity.data[0], -100, 100) );
  motor2.setMotorVel( constrain(150*inputVelocity.data[1], -100, 100) );
  motor3.setMotorVel( constrain(150*inputVelocity.data[2], -100, 100) );
}


//ros
ros::NodeHandle ArduinoInterface;
std_msgs::Float32MultiArray outputVelocity;

//ros::Publisher velPub("vel_topic", &outputVelocity);
ros::Subscriber<std_msgs::Float32MultiArray> velSub("motor_cmd", &callback);




void setup() {

  pinMode(10,OUTPUT);
  // put your setup code here, to run once:
  //Serial.begin(9600);
  initEncoders();
  //Serial.println("Encoders Initialized...");
  
  clearEncoderCounts();  
  //Serial.println("Encoders Cleared...");

  //initialize ros
  ArduinoInterface.initNode();

  //subscribe
  ArduinoInterface.subscribe(velSub);

  //define message and advertise
  //ArduinoInterface.advertise(velPub);
  
  //Input motor class information, initialize times. 
  motor1.inputKpv(1);
  motor1.inputKiv(0);
  motor1.inputKdv(0);
  motor1.inputpwmPin(4);
  motor1.inputdirPin(5);
  motor1.calc_t();

  motor2.inputKpv(1);
  motor2.inputKiv(0);
  motor2.inputKdv(0);
  motor2.inputpwmPin(6);
  motor2.inputdirPin(7);
  motor2.calc_t();

  motor3.inputKpv(1);
  motor3.inputKiv(0);
  motor3.inputKdv(0);
  motor3.inputpwmPin(8);
  motor3.inputdirPin(9);
  motor3.calc_t();

  /*motor4.inputKpv(0);
  motor4.inputKiv(0);
  motor4.inputKdv(0);
  motor4.inputpwmPin(0);
  motor4.inputdirPin(0);
  motor4.calc_t();*/
}


void loop() {
  // put your main code here, to run repeatedly:
  motor1.encodercount = readEncoder(1);
  motor2.encodercount = readEncoder(2);
  motor3.encodercount = readEncoder(3);
  //motor4.encodercount = readEncoder(4);

  //Definitions of closedLoopControl() and storeOldVals in helper.cpp
  motor1.closedLoopController();
  motor2.closedLoopController();
  motor3.closedLoopController();
  //motor4.closedLoopController();
  
  motor1.storeOldVals();
  motor2.storeOldVals();
  motor3.storeOldVals();
  //motor4.storeOldVals();
  ArduinoInterface.spinOnce();
}
