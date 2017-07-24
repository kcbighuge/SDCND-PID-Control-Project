#include "PID.h"
#include <math.h>
#include <iostream>
#define MIN_STEPS 20

using namespace std;

/*
* TO_DID: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
	Kp = Kp_;
	Ki = Ki_;
	Kd = Kd_;

	p_error = 0;
  i_error = 0;
  d_error = 0;

  dpp = Kp/4;
  dpi = Ki/4;
  dpd = Kd/4;

  tol = 0.75 * (dpp+dpi+dpd);
}

void PID::UpdateError(double cte) {
	d_error = cte - p_error;
	p_error = cte;
	i_error += cte;

	if(num_steps>MIN_STEPS) total_error += pow(cte,2);
	num_steps++;
}

double PID::TotalError() {
	return -Kp*p_error -Ki*i_error -Kd*d_error;
}

void PID::Twiddle() {
	// see: https://github.com/jendrikjoe/UdacityProjects

	double err = total_error / (num_steps - MIN_STEPS);
	int numSteps = num_steps;

	total_error = 0;
	num_steps = 0;
	
	if(best_error > 1e8) {
		best_error = err;
		cout << "New best Kp: " << Kp 
					<< " Kd: " << Kd
					<< " Ki: " << Ki << endl 
					<< " Error: " << best_error << endl 
					<< " Sum dp: " << dpp + dpi + dpd 
					<< endl;
		Kp += dpp;
		return;
	}

	i_error = 0;
	d_error = 0;
	//p_error = 0;

	if(switcher == -1) {
		cout << "Error: " << err << endl; 
		return;
	}
	
	if (err < best_error && numSteps > stepsTwiddle) {

		best_error = err;
		
		if(switcher == 0) dpp *= 1.0 + dp_diff;
		else if(switcher == 1) dpd *= 1.0 + dp_diff;
		else dpi *= 1.0 + dp_diff;
		switcher = (switcher+1) % 3;
		up = true;
		
		cout << "New best Kp: " << Kp 
					<< " Kd: " << Kd << " Ki: " << Ki << endl 
					<< " Error: " << best_error << endl 
					<< " Sum dp: " << dpp + dpi + dpd << endl;

	} else {
		
		cout << "Skipped Kp: " << Kp 
					<< " Kd: " << Kd << " Ki: " << Ki << endl 
					<< " Error: " << err << endl 
					<< " Sum dp: " << dpp + dpi + dpd << endl;
		if(up == true) {
			up = false;
		} else {
			if (switcher == 0) {
				Kp += dpp;
				dpp *= 1.0 - dp_diff;
			}
			else if (switcher == 1) {
				Kd += dpd;
				dpd *= 1.0 - dp_diff;
			}
			else {
				Kd += dpi;
				dpi *= 1.0 - dp_diff;
			}
			switcher = (switcher + 1) % 3;
			up = true;	
		}

	}

	if(switcher == 0) {
		if(up) Kp += dpp;
		else Kp -= 2*dpp;
	}
	if(switcher == 1) {
		if(up) Kd += dpd;
		else Kd -= 2*dpd;
	}
	if(switcher == 2) {
		if(up) Ki += dpi;
		else Ki -= 2*dpi;
	}

	if((dpp+dpi+dpd) < tol) {
		switcher = -1;
		cout << "Done with Twiddle :) " << endl;
	}
}