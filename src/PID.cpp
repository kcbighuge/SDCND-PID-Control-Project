#include "PID.h"
#include <iostream>
#include <array>

using namespace std;

/*
* TODOING: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;

	p_error = 0;
  i_error = 0;
  d_error = 0;
	tol = 0.2;
}

void PID::UpdateError(double cte) {
	d_error = cte - p_error;
	p_error = cte;
	i_error += cte;
}

double PID::TotalError() {
	return Kp*p_error + Ki*i_error + Kd*d_error;
}

void PID::Twiddle(double cte) {
	array<double, 3> p = {Kp, Ki, Kd};
	array<double, 3> dp = {1, 1, 1};

	for (int i=0; i<p.size(); ++i) {
		cout << "p is: " << i << " - " << p[i] << endl;

		while ((dp[0]+dp[1]+dp[2]) < tol) {
			p[i] += dp[i];
			cout << "p is now: " << i << " - " << p[i] << endl;
			cout << "Kp is now: " << Kp << endl;
		}
	
	}

}

/*
def twiddle(tol=0.2):

    # Don't forget to call `make_robot` before you call `run`!
    p = [0, 0, 0]
    dp = [1, 1, 1]
    robot = make_robot()
    x_trajectory, y_trajectory, best_err = run(robot, p)
    # TODO: twiddle loop here
    while sum(dp) > tol:
        print(sum(dp))
        for i in range(len(p)):
            p[i] += dp[i]

            robot = make_robot()
            _,_,err = run(robot, p)

            if err < best_err:
                best_err = err
                dp[i] *= 1.1

            else:
                p[i] -= 2*dp[i]
                robot = make_robot()
                _,_,err = run(robot, p)

                if err < best_err:
                    best_err = err
                    dp[i] *= 1.1
                else:
                    p[i] += dp[i]
                    dp[i] *= 0.9

    return p, best_err
*/