#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double total_error = 0;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  /*
  * Twiddle parameters
  */
  double dpp;
  double dpi;
  double dpd;

  double best_error = 1e9;
  double tol;
  int num_steps = 0;
  bool up = true;
  int switcher = 0;
  bool useTwiddle = false;
  const int stepsTwiddle = 60;
  const double dp_diff = 0.1;
  const double accel = 0.6;

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
  void Init(double Kp_, double Ki_, double Kd_);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /*
  * Optimize the P,I,D coeffs.
  */
  void Twiddle();
  int getNumSteps() { return num_steps; }
  void setNumSteps(int num) { num_steps = num; }

};

#endif /* PID_H */
