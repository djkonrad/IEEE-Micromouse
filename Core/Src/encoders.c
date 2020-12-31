/*
 * encoders.c
 *
 *  Created on: Nov 12, 2020
 *      Author: Dominic Konrad
 */

#include "main.h"
#include "encoders.h"

/*
 * Returns the right encoder value
 */
int16_t getRightEncoderCounts()
{
	return (int16_t) TIM8->CNT;
}

/*
 * Returns the left encoder value
 */
int16_t getLeftEncoderCounts()
{
	return (int16_t) TIM2->CNT;
}

void resetEncoders()
{
	TIM8->CNT = (int16_t) 0;
	TIM2->CNT = (int16_t) 0;
}
