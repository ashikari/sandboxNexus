// Jerry Ng           - jerryng _mit_ edu,    Jan  2018
// See helper.h for additional notes and comments on the purpose of each variable

#include "helper.h"

#include "Arduino.h"

///////////////////////Helper Functions///////////////////////  

int motorClass::openLoopController(void){
  //set scale factor value for to map from minimum pwm output to maximum pwm output
  currentCommand = desiredMotorVel * 0;//some_scale_factor;
  return currentCommand;
}

void motorClass::storeOldVals(void){
  prevTime = currentTime;
  errorVelPrev = errorVel;
  encodercountPrev = encodercount;
}

void motorClass::calc_t(){
  currentTime = millis();
  dt = currentTime - prevTime;
}

float motorClass::motor_velocity_calc(void){
  calc_t();
  MotorVel = (encodercount-encodercountPrev) * dt;
  storeOldVals();
  return MotorVel; 
}

float motorClass::proportional_control(void){
  errorVel = desiredMotorVel - MotorVel;
  pCommand = Kpv * errorVel;
  return pCommand;
}

float motorClass::derivative_control(void){
  calc_t();
  dCommand = Kdv * (errorVel - errorVelPrev) / dt;
  return dCommand;
}

float motorClass::integral_control(void){
  calc_t();
  integratedVelError = integratedVelError + errorVel*dt;
  
  iCommand = Kiv*integratedVelError;

  //deal with integral windup
  if ( iCommand > MAX_PWM ){
    iCommand = MAX_PWM;
    integratedVelError = 0; //subject to change
  }
  else if ( iCommand < MIN_PWM ){
    iCommand = MIN_PWM;
    integratedVelError = 0;
  }
  return iCommand;
}

int motorClass::closedLoopController(void){
  currentCommand = proportional_control() + derivative_control() + integral_control();
  return currentCommand; 
}


