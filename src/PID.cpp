#include "PID.h"
#include <math.h>
#include <iostream>
#define MIN_STEPS 100

using namespace std;

/*
* TODOING: Complete the PID class.
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
					<< " Ki: " << Ki << " Error: " << best_error
					<< " Sum dpi: " << dpp + dpi + dpd 
					<< endl;
		Kp += dpp;
		return;
	}

	i_error = 0;
	d_error = 0;
	p_error = 0;
	
	if (err < best_error && numSteps > 300) {

		best_error = err;
		dpp *= 1.1;
		
		if(switcher == 0) dpp *= 1.1;
		//else if(switchTweeker == 1) dpi *= 1.1;
		else dpd *= 1.1;
		switcher = (switcher+1) % 2;
		up = true;
		
		cout << "New best Kp: " << Kp 
					//<< " Kd: " << Kd << " Ki: " << Ki 
					<< " Error: " << best_error
					<< " Sum dp: " << dpp + dpi + dpd 
					<< endl;

	} else {
		
		std::cout << "Skipped Kp: " << Kp << " Kd: " << Kd
								<< " Ki: " << Ki << " Error: " << err
								<< " Sum dpi: " << dpp + dpi + dpd << std::endl;
		if(up == true) {
			up = false;
		} else {
			if (switcher == 0) {
				Kp += dpp;
				dpp *= 0.9;
			}
			/*else if (switcher == 1) {
				Ki += dpi;
				dpi *= .9;
			}*/
			else {
				Kd += dpd;
				dpd *= .9;
			}
			switcher = (switcher + 1) % 2;
			up = true;
			
		}

	}

	if(switcher == 0) {
		if(up) Kp += dpp;
		else Kp-= 2*dpp;
	}
	/*if(switcher == 1) {
		if(up) Ki += dpi;
		else Ki -= 2*dpi;
	}*/
	if(switcher == 1) {
		if(up) Kd += dpd;
		else Kd-= 2*dpd;
	}

}