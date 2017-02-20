#include "stdafx.h"





//Logger Easing::log = Logger("Easing");


double Easing::linearTween(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return changeInValue * ticksPassed / durationTicks + beginningValue;
}

double Easing::easeInQuadratic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return changeInValue * (ticksPassed /= durationTicks) * ticksPassed + beginningValue;
}

double Easing::easeOutQuadratic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return -changeInValue * (ticksPassed /= durationTicks) * (ticksPassed - 2) + beginningValue;
}

double Easing::easeInOutQuadratic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	if ((ticksPassed /= durationTicks / 2) < 1)
	{
		return changeInValue / 2 * ticksPassed * ticksPassed + beginningValue;
	}
	return -changeInValue / 2 * ((--ticksPassed) * (ticksPassed - 2) - 1) + beginningValue;
}

double Easing::easeInCubic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return changeInValue * (ticksPassed /= durationTicks) * ticksPassed * ticksPassed + beginningValue;
}

double Easing::easeOutCubic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return changeInValue * ((ticksPassed = ticksPassed / durationTicks - 1) * ticksPassed * ticksPassed + 1) + beginningValue;
}

double Easing::easeInOutCubic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	if ((ticksPassed /= durationTicks / 2) < 1)
	{
		return changeInValue / 2 * ticksPassed * ticksPassed * ticksPassed + beginningValue;
	}
	return changeInValue / 2 * ((ticksPassed -= 2) * ticksPassed * ticksPassed + 2) + beginningValue;
}

double Easing::easeInQuartic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return changeInValue * (ticksPassed /= durationTicks) * ticksPassed * ticksPassed * ticksPassed + beginningValue;
}

double Easing::easeOutQuartic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return -changeInValue * ((ticksPassed = ticksPassed / durationTicks - 1) * ticksPassed * ticksPassed * ticksPassed - 1) + beginningValue;
}

double Easing::easeInOutQuartic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	if ((ticksPassed /= durationTicks / 2) < 1)
	{
		return changeInValue / 2 * ticksPassed * ticksPassed * ticksPassed * ticksPassed + beginningValue;
	}
	return -changeInValue / 2 * ((ticksPassed -= 2) * ticksPassed * ticksPassed * ticksPassed - 2) + beginningValue;
}

double Easing::easeInQuintic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return changeInValue * (ticksPassed /= durationTicks) * ticksPassed * ticksPassed * ticksPassed * ticksPassed + beginningValue;
}

double Easing::easeOutQuintic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return changeInValue * ((ticksPassed = ticksPassed / durationTicks - 1) * ticksPassed * ticksPassed * ticksPassed * ticksPassed + 1) + beginningValue;
}

double Easing::easeInOutQuintic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	if ((ticksPassed /= durationTicks / 2) < 1)
	{
		return changeInValue / 2 * ticksPassed * ticksPassed * ticksPassed * ticksPassed * ticksPassed + beginningValue;
	}
	return changeInValue / 2 * ((ticksPassed -= 2) * ticksPassed * ticksPassed * ticksPassed * ticksPassed + 2) + beginningValue;
}

double Easing::easeInSinusoidal(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return -changeInValue * cos(ticksPassed / durationTicks * (M_PI / 2)) + changeInValue + beginningValue;
}

double Easing::easeOutSinusoidal(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return changeInValue * sin(ticksPassed / durationTicks * (M_PI / 2)) + beginningValue;
}

double Easing::easeInOutSinusoidal(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return -changeInValue / 2 * (cos(M_PI * ticksPassed / durationTicks) - 1) + beginningValue;
}

double Easing::easeInExponential(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return (ticksPassed == 0) ? beginningValue : changeInValue * pow(2, 10 * (ticksPassed / durationTicks - 1)) + beginningValue;
}

double Easing::easeOutExponential(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return (ticksPassed == durationTicks) ? beginningValue + changeInValue : changeInValue * (-pow(2, -10 * ticksPassed / durationTicks) + 1) + beginningValue;
}

double Easing::easeInOutExponential(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	if (ticksPassed == 0)
	{
		return beginningValue;
	}
	if (ticksPassed == durationTicks)
	{
		return beginningValue + changeInValue;
	}
	if ((ticksPassed /= durationTicks / 2) < 1)
	{
		return changeInValue / 2 * pow(2, 10 * (ticksPassed - 1)) + beginningValue;
	}
	return changeInValue / 2 * (-pow(2, -10 * --ticksPassed) + 2) + beginningValue;
}

double Easing::easeInCircular(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return -changeInValue * (sqrt(1 - (ticksPassed /= durationTicks) * ticksPassed) - 1) + beginningValue;
}

double Easing::easeOutCircular(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return changeInValue * sqrt(1 - (ticksPassed = ticksPassed / durationTicks - 1) * ticksPassed) + beginningValue;
}

double Easing::easeInOutCircular(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	if ((ticksPassed /= durationTicks / 2) < 1)
	{
		return -changeInValue / 2 * (sqrt(1 - ticksPassed * ticksPassed) - 1) + beginningValue;
	}

	return changeInValue / 2 * (sqrt(1 - (ticksPassed -= 2) * ticksPassed) + 1) + beginningValue;
}

double Easing::easeInElastic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks, double amplitude)
{
	if (ticksPassed == 0)
	{
		return beginningValue;
	}
	if ((ticksPassed /= durationTicks) == 1)
	{
		return beginningValue + changeInValue;
	}

	double period = durationTicks * .3;
	double s = 0;

	if (amplitude < abs(changeInValue))
	{
		amplitude = changeInValue;
		s = period / 4;
	}
	else
	{
		s = period / (2 * M_PI) * asin(changeInValue / amplitude);
	}

	return -(amplitude * pow(2, 10 * (ticksPassed -= 1)) * sin((ticksPassed * durationTicks - s) * (2 * M_PI) / period)) + beginningValue;
}

double Easing::easeOutElastic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks, double amplitude)
{
	if (ticksPassed == 0)
	{
		return beginningValue;
	}
	if ((ticksPassed /= durationTicks) == 1)
	{
		return beginningValue + changeInValue;
	}

	double period = durationTicks * .3;
	double s = 0;

	if (amplitude < abs(changeInValue))
	{
		amplitude = changeInValue;
		s = period / 4;
	}
	else
	{
		s = period / (2 * M_PI) * asin(changeInValue / amplitude);
	}

	return amplitude * pow(2, -10 * ticksPassed) * sin((ticksPassed * durationTicks - s) * (2 * M_PI) / period) + changeInValue + beginningValue;
}

double Easing::easeInOutElastic(double ticksPassed, double beginningValue, double changeInValue, double durationTicks, double amplitude)
{
	if (ticksPassed == 0)
	{
		return beginningValue;
	}
	if ((ticksPassed /= durationTicks / 2) == 2)
	{
		return beginningValue + changeInValue;
	}
	double period = durationTicks * (.3 * 1.5);

	double s = 0;

	if (amplitude < abs(changeInValue))
	{
		amplitude = changeInValue;
		s = period / 4;
	}
	else
	{
		s = period / (2 * M_PI) * asin(changeInValue / amplitude);
	}

	if (ticksPassed < 1)
	{
		return -.5 * (amplitude * pow(2, 10 * (ticksPassed -= 1)) * sin((ticksPassed * durationTicks - s) * (2 * M_PI) / period)) + beginningValue;
	}

	return amplitude * pow(2, -10 * (ticksPassed -= 1)) * sin((ticksPassed * durationTicks - s) * (2 * M_PI) / period) * .5 + changeInValue + beginningValue;
}

double Easing::easeInBackSlingshot(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double overshootAmount = 1.70158;
	return changeInValue * (ticksPassed /= durationTicks) * ticksPassed * ((overshootAmount + 1) * ticksPassed - overshootAmount) + beginningValue;
}

double Easing::easeOutBackOvershoot(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double overshootAmount = 1.70158;
	return changeInValue * ((ticksPassed = ticksPassed / durationTicks - 1) * ticksPassed * ((overshootAmount + 1) * ticksPassed + overshootAmount) + 1) + beginningValue;
}

double Easing::easeInOutBackSlingshotOvershoot(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	double overshootAmount = 1.70158;
	if ((ticksPassed /= durationTicks / 2) < 1)
	{
		return changeInValue / 2 * (ticksPassed * ticksPassed * (((overshootAmount *= (1.525)) + 1) * ticksPassed - overshootAmount)) + beginningValue;
	}
	return changeInValue / 2 * ((ticksPassed -= 2) * ticksPassed * (((overshootAmount *= (1.525)) + 1) * ticksPassed + overshootAmount) + 2) + beginningValue;
}

double Easing::easeInParabolicBounce(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	return changeInValue - easeOutParabolicBounce(durationTicks - ticksPassed, 0, changeInValue, durationTicks) + beginningValue;
}

double Easing::easeOutParabolicBounce(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	if ((ticksPassed /= durationTicks) < (1 / 2.75))
	{
		return changeInValue * (7.5625 * ticksPassed * ticksPassed) + beginningValue;
	}
	else if (ticksPassed < (2 / 2.75))
	{
		return changeInValue * (7.5625 * (ticksPassed -= (1.5 / 2.75)) * ticksPassed + .75) + beginningValue;
	}
	else if (ticksPassed < (2.5 / 2.75))
	{
		return changeInValue * (7.5625 * (ticksPassed -= (2.25 / 2.75)) * ticksPassed + .9375) + beginningValue;
	}
	else
	{
		return changeInValue * (7.5625 * (ticksPassed -= (2.625 / 2.75)) * ticksPassed + .984375) + beginningValue;
	}
}

double Easing::easeInOutParabolicBounce(double ticksPassed, double beginningValue, double changeInValue, double durationTicks)
{
	if (ticksPassed < durationTicks / 2)
	{
		return easeInParabolicBounce(ticksPassed * 2, 0, changeInValue, durationTicks) * .5 + beginningValue;
	}
	return easeOutParabolicBounce(ticksPassed * 2 - durationTicks, 0, changeInValue, durationTicks) * .5 + changeInValue * .5 + beginningValue;
}

