/**
 * @file :  home_state.c
 * @brief : State machine to control the home
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 *
 */


#include "TSI.h"
#include "home_state.h"

// Set the initial home state
home_state_t home_state = {
        .color = WHITE_COLOR,
        .brightness = ZERO_PERCENT,
};

/*
 * @brief : Get the color state
 * @return : color state
 */
color_t get_color() {
    return home_state.color;
}

/*
 * @brief : Set the color state
 * @param : New color state
 */
void set_color(color_t color) {
    home_state.color = color;
}

/*
 * @brief : Get the brightness state
 * @return : brightness state
 */
brightness_t get_brightness() {
    return home_state.brightness;
}

/*
 * @brief : Set the brightness state
 * @param : New brightness state
 */
void set_brightness(brightness_t brightness) {
    home_state.brightness = brightness;
}

/*
 * @brief : Adjust the LED color and brightness based on the current state
 */
void adjust_led() {
    int hex = get_hex_by_brightness_and_color(home_state.brightness, home_state.color);
    control_leds(hex);
}
