/*
 * pid.c
 *
 *  Created on: Nov 22, 2020
 *      Author: Dominic Konrad
 */

#include "main.h"
#include "motors.h"
#include "encoders.h"

	 /* Creates kPw, kDw, kPx, and kDx variables, also makes variables to store the previous error for use in computing derivative term.
	 */

int goalAngle = 0;
int goalDistance = 0;
int angleError = 0;
int oldAngleError = 0;
float distanceError = 0;
float oldDistanceError = 0;
float kPw = 0.023;	//previous best kPw = 0.5
float kDw = 0;   //previous best kDw = 0.01
float kPx = 0.01;
float kDx = 0.5;

int isDone = 0;

void resetPID()
{
	/*
	 *  This function resets all the variables defined in this file to help with PID to their default
	 *  values. Resets angle and distance goals, angle and distance error, motor speed and encoder counts
	 *
	 */

	goalAngle = 0;
	goalDistance = 0;

	angleError = 0;
	oldAngleError = 0;
	distanceError = 0;
	oldDistanceError = 0;

	isDone = 0;

	resetEncoders();
	resetMotors();
}

void updatePID()
{
	/*
	 * This function will do the heavy lifting PID logic. It does the following: reads encoder counts to determine an error,
	 * uses that error along with some PD constants in order to determine how to set the motor speeds, and then actually
	 * sets the motor speeds.
	 *
	 *
	 * This function calculates distanceError as the difference between goal distance and the average of
	 * left and right encoder counts. AngleError is calculated as the difference between goal angle and the difference between left and
	 * right encoder counts. Refer to pseudocode example document on the google drive for some pointers.
	 */

	float encoderDifference = getRightEncoderCounts() - getLeftEncoderCounts();
	float encoderAverage = ((getRightEncoderCounts() + getLeftEncoderCounts())/2);


	angleError = goalAngle + encoderDifference;
	float angleCorrection = kPw * angleError + kDw * (angleError - oldAngleError);
	oldAngleError = angleError;

	if (angleCorrection > 0.5)
	{
		angleCorrection = 0.5;
	}
	else if (angleCorrection < -0.5)
	{
		angleCorrection = -0.5;
	}

	distanceError = goalDistance - encoderAverage;
	float distanceCorrection = kPx * distanceError + kDx * (distanceError - oldDistanceError);
	oldDistanceError = distanceError;

	if (distanceCorrection > 0.5)
	{
		distanceCorrection = 0.5;
	}
	else if (distanceCorrection < -0.5)
	{
		distanceCorrection = -0.5;
	}

	setMotorLPWM(distanceCorrection + angleCorrection);
	setMotorRPWM(distanceCorrection - angleCorrection);

	if((angleError <= 10 && angleError >= -10) && (distanceError <= 10 && distanceError >= -10))
	{
		isDone = 1;
	}


}

void setPIDGoalD(int16_t distance)
{
	/*
	 * This function should set a variable that stores the goal distance.
	 */

	goalDistance = distance;
}

void setPIDGoalA(int16_t angle)
{
	/*
	 * This function should set a variable that stores the goal angle.
	 */

	goalAngle = angle;

}

int8_t PIDdone(void)
{
	/*
	 * This function should return true if the rat has achieved the set goal.
	 */

	if(isDone == 1)
		return 1;

	return 0;
}
