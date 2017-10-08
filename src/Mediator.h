#ifndef _Mediator_h_
#define _Mediator_h_

#include "PID.h"
#include <uWS/uWS.h>

class Mediator {
public:
    Mediator(PID& pid, PID& tpid) 
          : pid_(pid), tpid_(tpid) {} 
   ~Mediator() {}

    void updateError(double cte, double speedcte, double speed);
    double getSteerValue();
    double getThrottleValue();
private:
   void computeSteerValue(double speed);
   void computeThrottleValue();

   PID& pid_;   //PID for steering
   PID& tpid_;  //PID for throttle

   double calibratedspeed_;
   double prev_ = 0.0;  //previous value
   double tprev_ = 0.0; //previous throttle value
   int instop_ = 0;
};

#endif
