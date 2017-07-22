#include "PID.h"

using namespace std;

/*
* TODOING: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	PID.Kp = Kp;
	PID.Ki = Ki;
	PID.Kd = Kd;

	PID.total_error = 0;
	PID.best_error = 0;
	PID.tol = 0.2;
}

void PID::UpdateError(double cte) {
	if (PID.best_error = 0) {
		PID.best_error = cte;
	}

	while (PID.total_error > PID.tol) {
		PID.Kp += PID.p_error;
		
		if (cte < PID.best_error) {
			PID.best_error = cte;
			PID.p_error *= 1.1
		} else {
			PID.Kp -= 2 * PID.p_error;
			if cte < PID.best_error {
				PID.best_error = cte;
				PID.p_error *= 1.1;
			} else {
				PID.Kp += PID.p_error;
				PID.p_error *= 0.9;
			}
		}

	}
}

double PID::TotalError(double cte) {
	PID.total_error += cte;
}

