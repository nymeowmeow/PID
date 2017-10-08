#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd, double KiAlpha, double decay);

  double getKp() const { return Kp; }
  double getKd() const { return Kd; }
  double getKi() const { return Ki; }
  double getDError() const { return d_error; }
  double getPError() const { return p_error; }

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError(double speed);
private:
  //Coefficients
  double Kp;
  double Ki;
  double Kd;
  double KiAlpha_;
  double decay_;
  //Errors
  double p_error = 0;
  double d_error = 0;
  double i_error = 0;
  //
  bool initialized_ = false;
};

#endif /* PID_H */
