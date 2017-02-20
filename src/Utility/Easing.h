#pragma once
#include "bobtypes.h"
class Logger;



//http://www.robertpenner.com/easing/

/*
TERMS OF USE - EASING EQUATIONS

Open source under the BSD License.

Copyright � 2001 Robert Penner
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

   Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
   Neither the name of the author nor the names of contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

class Easing
{
	// simple linear tweening - no easing
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in value, durationTicks: durationTicks
public:
	static double linearTween(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);


	///////////// QUADRATIC EASING: ticksPassed^2 ///////////////////

	// quadratic easing in - accelerating from zero velocity
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in value, durationTicks: durationTicks
	// ticksPassed and durationTicks can be in frames or seconds/milliseconds
	static double easeInQuadratic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// quadratic easing out - decelerating to zero velocity
	static double easeOutQuadratic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// quadratic easing in/out - acceleration until halfway, then deceleration
	static double easeInOutQuadratic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);


	///////////// CUBIC EASING: ticksPassed^3 ///////////////////////

	// cubic easing in - accelerating from zero velocity
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in value, durationTicks: durationTicks
	// ticksPassed and durationTicks can be frames or seconds/milliseconds
	static double easeInCubic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// cubic easing out - decelerating to zero velocity
	static double easeOutCubic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// cubic easing in/out - acceleration until halfway, then deceleration
	static double easeInOutCubic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);


	///////////// QUARTIC EASING: ticksPassed^4 /////////////////////

	// quartic easing in - accelerating from zero velocity
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in value, durationTicks: durationTicks
	// ticksPassed and durationTicks can be frames or seconds/milliseconds
	static double easeInQuartic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// quartic easing out - decelerating to zero velocity
	static double easeOutQuartic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// quartic easing in/out - acceleration until halfway, then deceleration
	static double easeInOutQuartic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);


	///////////// QUINTIC EASING: ticksPassed^5  ////////////////////

	// quintic easing in - accelerating from zero velocity
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in value, durationTicks: durationTicks
	// ticksPassed and durationTicks can be frames or seconds/milliseconds
	static double easeInQuintic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// quintic easing out - decelerating to zero velocity
	static double easeOutQuintic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// quintic easing in/out - acceleration until halfway, then deceleration
	static double easeInOutQuintic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);


	///////////// SINUSOIDAL EASING: sin(ticksPassed) ///////////////

	// sinusoidal easing in - accelerating from zero velocity
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in position, durationTicks: durationTicks
	static double easeInSinusoidal(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// sinusoidal easing out - decelerating to zero velocity
	static double easeOutSinusoidal(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// sinusoidal easing in/out - accelerating until halfway, then decelerating
	static double easeInOutSinusoidal(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);


	///////////// EXPONENTIAL EASING: 2^ticksPassed /////////////////

	// exponential easing in - accelerating from zero velocity
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in position, durationTicks: durationTicks
	static double easeInExponential(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// exponential easing out - decelerating to zero velocity
	static double easeOutExponential(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// exponential easing in/out - accelerating until halfway, then decelerating
	static double easeInOutExponential(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);


	/////////// CIRCULAR EASING: sqrt(1-ticksPassed^2) //////////////

	// circular easing in - accelerating from zero velocity
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in position, durationTicks: durationTicks
	static double easeInCircular(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// circular easing out - decelerating to zero velocity
	static double easeOutCircular(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// circular easing in/out - acceleration until halfway, then deceleration
	static double easeInOutCircular(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);


	/////////// ELASTIC EASING: exponentially decaying sine wave  //////////////

	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in value, durationTicks: durationTicks, a: amplitude (optional), p: period (optional)
	// ticksPassed and durationTicks can be in frames or seconds/milliseconds

	static double easeInElastic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks, double amplitude);

	static double easeOutElastic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks, double amplitude);

	static double easeInOutElastic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks, double amplitude);


	/////////// BACK EASING: overshooting cubic easing: (s+1)*ticksPassed^3 - s*ticksPassed^2  //////////////

	// back easing in - backtracking slightly, then reversing direction and moving to target
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in value, durationTicks: durationTicks, s: overshoot amount (optional)
	// ticksPassed and durationTicks can be in frames or seconds/milliseconds
	// s controls the amount of overshoot: higher s means greater overshoot
	// s has a default value of 1.70158, which produces an overshoot of 10 percent
	// s==0 produces cubic easing with no overshoot
	static double easeInBackSlingshot(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// back easing out - moving towards target, overshooting it slightly, then reversing and coming back to target
	static double easeOutBackOvershoot(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// back easing in/out - backtracking slightly, then reversing direction and moving to target,
	// then overshooting target, reversing, and finally coming back to target
	static double easeInOutBackSlingshotOvershoot(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);


	/////////// BOUNCE EASING: exponentially decaying parabolic bounce  //////////////

	// bounce easing in
	// ticksPassed: current time, beginningValue: beginning value, changeInValue: change in position, durationTicks: durationTicks
	static double easeInParabolicBounce(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// bounce easing out
	static double easeOutParabolicBounce(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);

	// bounce easing in/out
	static double easeInOutParabolicBounce(double ticksPassed, double beginningValue, double changeInValue, double durationTicks);
};

