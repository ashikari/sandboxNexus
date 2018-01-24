#include <SPI.h>
#include "Encoder.h"
#include "helper.h"
/*#include <ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Float32.h>


//ros
//10 publishers, 15 subscribers, 128 bytes for input buffer, 256 bytes for output buffer
ros::NodeHandle_ ArduinoInterface;
std_msgs::Float32MultiArray outputVelocity;

ros::Publisher velPub("velPub", &outputVelocity);
ros::Subscriber<std_msgs::Float32MultiArray> velSub("velSub", &callback);

void callback(const std_msgs::Float32Multiarray& inputVelocity){
}*/


motorClass motor1;
motorClass motor2;
motorClass motor3;
//motorClass motor4;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  initEncoders();
  //Serial.println("Encoders Initialized...");
  
  clearEncoderCounts();  
  //Serial.println("Encoders Cleared...");

  //initialize ros
  //ArduinoInterface.initNode();

  //subscribe
  //ArduinoInterface.subscribe(velSub);

  //define message and advertise
  //ArduinoInterface.advertise(velPub);
  
  //Input motor class information, initialize times. 
  motor1.inputKpv(0);
  motor1.inputKiv(0);
  motor1.inputKdv(0);
  motor1.inputpwmPin(0);
  motor1.inputdirPin(0);
  motor1.calc_t();

  motor2.inputKpv(0);
  motor2.inputKiv(0);
  motor2.inputKdv(0);
  motor1.inputpwmPin(0);
  motor1.inputdirPin(0);
  motor2.calc_t();

  motor3.inputKpv(0);
  motor3.inputKiv(0);
  motor3.inputKdv(0);
  motor3.inputpwmPin(0);
  motor3.inputdirPin(0);
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
}
