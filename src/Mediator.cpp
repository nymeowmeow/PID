#include "Mediator.h"
#include <math.h>
#include <iostream>

double
Mediator::getSteerValue()
{
  return prev_;
}

void
Mediator::computeSteerValue(double speed)
{
  //use current speed to adjust the parameter
  double value = -pid_.TotalError(std::max(speed, 0.0));
  //if in brake mode, gradually decrease the steering angle
  //so as not to overshoot
  if (instop_ > 0 && instop_ < 4)
      value *= instop_*0.3;
  //restrict the range of steer value within -1.0 to 1.0
  value = std::max(std::min(value, 1.0), -1.0);
  prev_ = value;
}

double
Mediator::getThrottleValue()
{
  return tprev_;
}

void
Mediator::computeThrottleValue()
{
  double value = tpid_.TotalError(0);
  double angularDiff = fabs(pid_.getDError());
  if (instop_ != 0) {
      //in brake mode, spcial handling throttle setting
      instop_--;
      value = (instop_ == 0)?1.0:0.0;
  } else if (angularDiff > 0.12) {
      //if doing a drastic turn, don't apply throttle for 4 consective
      //time, to allow it to recover
      value = 0.0;
      instop_ = 4;
  } else {
      //normal case, min throttle set to 0.3
      if (value  < 0.3)
	value = 0.3;
  }
  value = std::max(std::min(value, 1.0), 0.0);
  tprev_ = value;
}

void
Mediator::updateError(double cte, double speedcte, double speed)
{
  pid_.UpdateError(cte);
  computeSteerValue(speed);
  tpid_.UpdateError(speedcte);
  computeThrottleValue();
}
