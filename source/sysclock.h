/**
 * @file - sysclock.h
 * @brief - configuration routines for KL25Z system clock header
 * @author - Howdy Pierce, howdy.pierce@colorado.edu
 * @references - https://learningmicro.wordpress.com/configuring-device-clock-and-using-systick-system-tick-timer-module-to-generate-software-timings/
 * See section 24 of the KL25Z Reference Manual to understand this code
 */

#ifndef _SYSCLOCK_H_
#define _SYSCLOCK_H_

#define SYSCLOCK_FREQUENCY (24000000U)

/*
 * @brief - Initialize the system clock
 */
void sysclock_init();

#endif  // _SYSCLOCK_H_
