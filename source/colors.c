/**
 * @file :  colors.c
 * @brief : Colors definitions
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 *
 */

#include "colors.h"

/*
 * @brief : Get the color value for the given color name
 * @param : color - color name
 * @param : brightness - brightness value
 * @return : color value
 */
int get_hex_by_brightness_and_color(brightness_t brightness, color_t color) {
    switch (brightness) {
        case BRIGHTNESS_0_PERCENT:
            return OFF_COLOR_HEX;
        case BRIGHTNESS_25_PERCENT:
            switch (color) {
                case RED_COLOR:
                    return RED_COLOR_50_HEX;
                case GREEN_COLOR:
                    return GREEN_COLOR_50_HEX;
                case BLUE_COLOR:
                    return BLUE_COLOR_50_HEX;
                case WHITE_COLOR:
                    return WHITE_COLOR_50_HEX;
                default:
                    break;
            }
            break;
        case BRIGHTNESS_50_PERCENT:
            switch (color) {
                case RED_COLOR:
                    return RED_COLOR_50_HEX;
                case GREEN_COLOR:
                    return GREEN_COLOR_50_HEX;
                case BLUE_COLOR:
                    return BLUE_COLOR_50_HEX;
                case WHITE_COLOR:
                    return WHITE_COLOR_50_HEX;
                default:
                    break;
            }
            break;
        case BRIGHTNESS_75_PERCENT:
            switch (color) {
                case RED_COLOR:
                    return RED_COLOR_75_HEX;
                case GREEN_COLOR:
                    return GREEN_COLOR_75_HEX;
                case BLUE_COLOR:
                    return BLUE_COLOR_75_HEX;
                case WHITE_COLOR:
                    return WHITE_COLOR_75_HEX;
                default:
                    break;
            }
            break;
        case BRIGHTNESS_100_PERCENT:
            switch (color) {
                case RED_COLOR:
                    return RED_COLOR_100_HEX;
                case GREEN_COLOR:
                    return GREEN_COLOR_100_HEX;
                case BLUE_COLOR:
                    return BLUE_COLOR_100_HEX;
                case WHITE_COLOR:
                    return WHITE_COLOR_100_HEX;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return -1;
}

/*
 * @brief : Get the brightness as an integer for the given brightness
 * @param : brightness - brightness value
 * @return : brightness as an integer
 */
int get_brightness_int(brightness_t brightness) {
    switch (brightness) {
        case BRIGHTNESS_0_PERCENT:
            return 0;
        case BRIGHTNESS_25_PERCENT:
            return 25;
        case BRIGHTNESS_50_PERCENT:
            return 50;
        case BRIGHTNESS_75_PERCENT:
            return 75;
        case BRIGHTNESS_100_PERCENT:
            return 100;
        default:
            return -1;
    }
}
