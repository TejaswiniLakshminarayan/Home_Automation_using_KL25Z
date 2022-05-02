/**
 * @file :  colors.h
 * @brief : Colors definitions header
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 *
 */

#ifndef COLORS_H_
#define COLORS_H_

// Define brightness percentages
#define ZERO_PERCENT            0
#define TWENTY_FIVE_PERCENT     25
#define FIFTY_PERCENT           50
#define SEVENTY_FIVE_PERCENT    75
#define HUNDRED_PERCENT         100

// Define conversions of color to hexadecimal
#define COLOR_RED_FROM_HEX(hex) (((hex) >> 16) & 0xFF)
#define COLOR_GREEN_FROM_HEX(hex) (((hex) >> 8) & 0xFF)
#define COLOR_BLUE_FROM_HEX(hex) ((hex) & 0xFF)

// Define colors
typedef enum {
    RED_COLOR,
    GREEN_COLOR,
    BLUE_COLOR,
    WHITE_COLOR
} color_t;

// Define color brightness
typedef enum {
    BRIGHTNESS_0_PERCENT,
    BRIGHTNESS_25_PERCENT,
    BRIGHTNESS_50_PERCENT,
    BRIGHTNESS_75_PERCENT,
    BRIGHTNESS_100_PERCENT
} brightness_t;

// Define color hexadecimal values
#define RED_COLOR_25_HEX    0xDE686A
#define GREEN_COLOR_25_HEX  0x4BA145
#define BLUE_COLOR_25_HEX   0x72C4D7
#define WHITE_COLOR_25_HEX  0x404040

#define RED_COLOR_50_HEX    0xCF494B
#define GREEN_COLOR_50_HEX  0x339631
#define BLUE_COLOR_50_HEX   0x50B2C9
#define WHITE_COLOR_50_HEX  0x808080

#define RED_COLOR_75_HEX    0xBF2A2C
#define GREEN_COLOR_75_HEX  0x1F8C1D
#define BLUE_COLOR_75_HEX   0x2DA0BA
#define WHITE_COLOR_75_HEX  0xBFBFBF

#define RED_COLOR_100_HEX   0xB00B0D
#define GREEN_COLOR_100_HEX 0x0B8209
#define BLUE_COLOR_100_HEX  0x0A8DAB
#define WHITE_COLOR_100_HEX 0xFFFFFF

#define OFF_COLOR_HEX       0x000000

/*
 * @brief : Get the color value for the given color name
 * @param : color - color name
 * @param : brightness - brightness value
 * @return : color value
 */
int get_hex_by_brightness_and_color(brightness_t brightness, color_t color);

/*
 * @brief : Get the brightness as an integer for the given brightness
 * @param : brightness - brightness value
 * @return : brightness as an integer
 */
int get_brightness_int(brightness_t brightness);

#endif //COLORS_H_
