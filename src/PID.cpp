#include "PID.h"

#include <iostream>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd, double KiAlpha, double decay) {
  //set the control parameter
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
  KiAlpha_ = KiAlpha;
  decay_   = decay;

  d_error = 0;
  p_error = 0;
  i_error = 0;
}

void PID::UpdateError(double cte) {
  if (!initialized_) {
    p_error = cte;
    initialized_ = true;
  }
  d_error = cte - p_error;
  i_error = cte + decay_*i_error;
  p_error = cte;
}

double PID::TotalError(double speed) {
  return Kp*p_error + Kd*d_error + (speed*KiAlpha_ + Ki*i_error);
}

