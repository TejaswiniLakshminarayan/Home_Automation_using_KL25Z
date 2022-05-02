/**
 * @file :  led.h
 * @brief : LED initialization and control functions header
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 *
 */

#ifndef LED_H_
#define LED_H_

#include "fsl_debug_console.h"

// PWM period
#define PWM_PERIOD (48000)

/*
 * @brief : Function to initialize RGB LEDs with PWM capabilities
 * @return : none
 */
void init_leds();


/*
 *  @brief : Function to control HEX Triplet values for RED,GREEN and BLUE LEDs
 *  @param : RED,GREEN and BLUE values for different state transitions
 *  @return : none
 */
void control_leds(int hex);


#endif /* LED_H_ */
