/*
 * motors.c
 *
 *  Created on: Nov 10, 2020
 *      Author: Dominic Konrad
 */

#include "motors.h"
/*
 * This function should return PWM_MAX if pwm > PWM_MAX, -PWM_MAX if pwm < -PWM_MAX, and pwm otherwise.
 */
float limitPWM(float pwm)
{
	if (pwm > PWM_MAX){
		return PWM_MAX;
	} else if (pwm < -PWM_MAX){
		return -PWM_MAX;
	} else {
		return (float) pwm;
	}
}

/*
 * This function controls the left motor speed and direction. We do this by setting the timer pulse value for the appropriate channel.
 * All H-bridge inputs use timer 4. TIM4->CCRX = (uint32_t) (limitPWM(pwm) * MAX_TIMER_COUNTS) sets the pulse value for channel x.
 * For the left motor, setting channel 2 makes the wheel spin forward and setting channel 1 makes the wheel spin backwards.
 *
 *
 * IMPORTANT: NEVER SET BOTH THE FORWARD AND BACKWARD CHANNELS TO NON-ZERO VALUES AT THE SAME TIME. As mentioned in lecture, this can
 * destroy your h-bridge. When setting a channel, always set the other channel to zero first.
 *
 * Left wheel spins forward when pwm is >= 0, and spins backward when pwm < 0.
 */
void setMotorLPWM(float pwm)
{
	/*
	 * Channel 2 spins forwards
	 * Channel 1 spins backwards
	 * Inputted pwm is the percentage of max speed to turn the motor [0,1]
	 * Both values can't be nonzero, since it would be requesting two different actions at the same time
	 */
	if (pwm < 0){
		TIM4->CCR1 = (uint32_t) (limitPWM(-pwm) * MAX_TIMER_COUNTS);
		TIM4->CCR2 = (uint32_t) (0);
	} else {
		TIM4->CCR1 = (uint32_t) (0);
		TIM4->CCR2 = (uint32_t) (limitPWM(pwm) * MAX_TIMER_COUNTS);
	}
}

/*
 * This function controls the right motor speed and direction. We do this by setting the timer pulse value for the appropriate channel.
 * All H-bridge inputs use timer 4. TIM4->CCRX = (uint32_t) (limitPWM(pwm) * MAX_TIMER_COUNTS) sets the pulse value for channel x.
 * For the right motor, setting channel 4 makes the wheel spin forward and setting channel 3 makes the wheel spin backwards.
 *
 *
 * IMPORTANT: NEVER SET BOTH THE FORWARD AND BACKWARD CHANNELS TO NON-ZERO VALUES AT THE SAME TIME. This can
 * destroy the h-bridge. When setting a channel, always set the other channel to zero first.
 *
 * Right wheel spins forward when pwm is >= 0, and spins backward when pwm < 0.
 */
void setMotorRPWM(float pwm)
{
	/*
	 *Same implementation as above, just changing the channel assignments
	 *Channel 3 is backwards
	 *Channel 4 is forwards
	 */
	if (pwm < 0){
		TIM4->CCR3 = (uint32_t) (limitPWM(-pwm) * MAX_TIMER_COUNTS);
		TIM4->CCR4 = (uint32_t) (0);
	} else {
		TIM4->CCR3 = (uint32_t) (0);
		TIM4->CCR4 = (uint32_t) (limitPWM(pwm) * MAX_TIMER_COUNTS);
	}
}

/*
 * Sets the PWM for both wheels to zero, effectively stopping them.
 */
void resetMotors()
{
	setMotorRPWM(0);
	setMotorLPWM(0);
}

