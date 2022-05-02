/**
 * @file :  timer_systick.h
 * @brief : Timing system
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 * @references : https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_7/PWM_LED/Source/timers.c
 *
 */

#ifndef TIMER_SYSTICK_H_
#define TIMER_SYSTICK_H_


#include "MKL25Z4.h"

typedef uint32_t ticktime_t;

/*
 * @brief : Initialize the systick timer
 */
void init_systick(void);

/*
 * @brief: Function for systick interrupt handler
 */
void SysTick_Handler();


/*
 * @brief : Get the current time in ticks
 */
ticktime_t now();

/*
 * @brief : This function resets the timer
 */
void reset_timer();

/*
 * @brief : This function returns the time elapsed since the last call to reset_timer()
 */
ticktime_t get_timer();

/*
 * @brief : This function is used to delay the execution of the program for a specified time
 * @param : milliseconds : time in milliseconds
 */
void delay(ticktime_t milliseconds);

#endif /* TIMER_SYSTICK_H_ */
