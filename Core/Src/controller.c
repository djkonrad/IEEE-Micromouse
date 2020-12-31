/*
 * controller.c
 *
 *  Created on: Nov 27, 2020
 *      Author: Dominic Konrad
 */

#include "main.h"
#include "controller.h"
#include "pid.h"

/*
 * Move(1) move rats by 1 cell forward.
 */

void move(int8_t n)
{

	setPIDGoalA(0);
	setPIDGoalD(n*640);

	while(PIDdone() != 1)
	{}

	resetPID();

	/*
	 * This function sets the distance and angle goals appropriately for PID by using the setGoal functions in pid.c
	 * Then, it waits until the error becomes sufficiently small and persistent before exiting and resetting all variables in pid.c
	 *
	 */
}

/*
 * We recommend you implement this function so that turn(1) turns your rat 90 degrees in your positive rotation
 * direction and turn(-1) turns the other way.
 */
void turn(int8_t n)
{
	/*
	 * For assignment 3.1: Don't worry about implementing this yet
	 * For assignment 3.2: This function should set the distance and angle goals appropriately for PID (hint: using the setGoal functions in pid.c)
	 * and wait until the error becomes sufficiently small and persistent before exiting. This function should NOT exit before then.
	 *
	 * HINT: Use a while loop to wait until the turn is complete
	 *
	 * You should also call resetPID before exiting this function so your rat is ready for the next instruction.
	 */

	setPIDGoalA(n * 600);
	setPIDGoalD(0);

	while(PIDdone() != 1)
	{}

	resetPID();
}
