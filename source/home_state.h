/**
 * @file : home_state.h
 * @brief : State machine to handle the home state header
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 *
 */

#ifndef HOME_STATE_H_
#define HOME_STATE_H_

#include "colors.h"

typedef struct {
    color_t color;
    brightness_t brightness;
} home_state_t;

/*
 * @brief : Get the color state
 * @return : color state
 */
color_t get_color();

/*
 * @brief : Set the color state
 * @param : New color state
 */
void set_color(color_t color);

/*
 * @brief : Get the brightness state
 * @return : brightness state
 */
brightness_t get_brightness();

/*
 * @brief : Set the brightness state
 * @param : New brightness state
 */
void set_brightness(brightness_t brightness);

/*
 * @brief : Adjust the LED color and brightness based on the current state
 */
void adjust_led();

#endif
