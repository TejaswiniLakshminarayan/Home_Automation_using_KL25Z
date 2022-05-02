/**
 * @file :  timer_systick.c
 * @brief : Timing system
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 * @references : https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_7/PWM_LED/Source/timers.c
 *
 */

#include <timer_systick.h>
#include "home_state.h"

/* Loop Count required for 1ms, considering 48MHz as board frequency */
#define COUNT (48076)

/* Global variables for the Timer APIs */
volatile ticktime_t timer_value;
volatile ticktime_t timer_start_value;
volatile ticktime_t timer_offset;

extern volatile ticktime_t Timer_U32;

/*
 * @brief: Initialize the Systick timer
 */
void init_systick(void) {
    SysTick->LOAD = (COUNT);
    NVIC_SetPriority(SysTick_IRQn, 3); // SET Interrupt Priority as 3
    NVIC_ClearPendingIRQ(SysTick_IRQn); // Clear Pending IRq's
    NVIC_EnableIRQ(SysTick_IRQn);
    SysTick->VAL = 0; //force load of reload value

    // Enable Interrupt and Processor CLock
    SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;
    timer_start_value = timer_offset = timer_value = 0;
}

/*
 * @brief : Get the current time in ticks
 */
ticktime_t now() {
    return timer_value - timer_start_value;
}

/*
 * @brief : This function resets the timer
 */
void reset_timer() {
    timer_offset = timer_value;
}

/*
 * @brief : This function returns the time elapsed since the last call to reset_timer()
 */
ticktime_t get_timer() {
    return (timer_value - timer_offset);
}

/*
 * @brief: Function for systick interrupt handler
 */
void SysTick_Handler() {
    timer_value++;
}

/*
 * @brief : This function is used to delay the execution of the program for a specified time
 * @param : milliseconds : time in milliseconds
 */
void delay(uint32_t Ticks) {
    uint32_t CurrentValue;
    CurrentValue = timer_value;
    while ((timer_value - CurrentValue) < Ticks);
}
