# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Reflection

### The effects of the P, I, D components  
- __P (Proportional control)__: The magnitude of this value largely determines the steering, as it is generated directly from the cross track error (cte). After starting with a values of `-0.5`, I found that a lower magnitude helped smooth the car's steering.
- __I (Integral)__: I was expecting to keep this value small to lessen the impact of the growing integral value. It turned out that just keeping this value `0` was the best approach.
- __D (Derivative)__: I expected to use a smaller magnitude value here than the P component, but found that I actually needed to *increase* it to smooth the steering.

### Choosing the final hyperparameters (P, I, D coefficients). 

#### 1.) Manual tuning  
The first approach to choosing the hyperparameters was a manual search using different values experimentaly. [This post](https://robotics.stackexchange.com/questions/167/what-are-good-strategies-for-tuning-pid-loops) was also used to generate ideas for tuning the coefficients. Ultimately the following values were used:
```
P = -0.1
I = -0.000001
D = -2.5
```

See video here:  
[![PID Control](http://img.youtube.com/vi/innwrbbnDlw/0.jpg)](http://www.youtube.com/watch?v=innwrbbnDlw "PID Control")


#### 2.) Twiddle  
After manual tuning, I attempted to optimize the coefficients with Twiddle (coordinate ascent). The implementation stores the cte for a certain number of iterations (e.g., the last 32 cte's) and runs the Twiddle algorithm to reset the P,I,D values.


---
