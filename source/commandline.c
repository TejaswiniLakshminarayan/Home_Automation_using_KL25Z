/**
 * @file :  commandline.c
 * @brief : Commandline implementation
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 *
 */

#include <ctype.h>
#include <stdlib.h>

#include "commandline.h"
#include "home_state.h"
#include "TSI.h"
#include "sht21.h"
#include "i2c.h"
#include "timer_systick.h"


#define CMD_LINE_LIMIT 2048 //command line limit

typedef void (*Command)();  // command function pointer

// commands struct to hold command head and function pointer
typedef struct {
    const char *head;
    Command function;
} Commands;

static int change_light_color_flag = 0;
static int set_light_timer_flag = 0;

/*
 * @brief : Function to turn on light
 */
static void turn_on_light_command() {
    if (get_brightness() == BRIGHTNESS_0_PERCENT) {
        set_brightness(BRIGHTNESS_25_PERCENT);
        adjust_led();
        printf("Light turned on\r\n");
    } else
        printf("Light is already on\r\n");
}

/*
 * @brief : Function to turn off light
 */
static void turn_off_light_command() {
    if (get_brightness() == BRIGHTNESS_0_PERCENT)
        printf("Light is already off\r\n");
    else {
        set_brightness(BRIGHTNESS_0_PERCENT);
        adjust_led();
        printf("Light turned off\r\n");
    }
}

/*
 * @brief : Function to change light color
 */
static void change_light_color_command() {
    change_light_color_flag = 1;
    printf("Okay. Which color would you like?\r\n\t-Red\r\n\t-Blue\r\n\t-Green\r\n\t-White\r\n");
}

/*
 * @brief : Function to change light color to red
 */
static void change_light_color_red_command() {
    if (get_color() == RED_COLOR)
        printf("Light is already red.\r\n");
    else {
        if (get_brightness() == BRIGHTNESS_0_PERCENT)
            set_brightness(BRIGHTNESS_25_PERCENT);  // Turn on light if it is off before changing color
        set_color(RED_COLOR);
        adjust_led();
        printf("Light changed to red.\r\n");
    }
    change_light_color_flag = 0;
}

/*
 * @brief : Function to change light color to green
 */
static void change_light_color_green_command() {
    if (get_color() == GREEN_COLOR)
        printf("Light is already green.\r\n");
    else {
        if (get_brightness() == BRIGHTNESS_0_PERCENT)
            set_brightness(BRIGHTNESS_25_PERCENT);  // Turn on light if it is off before changing color
        set_color(GREEN_COLOR);
        adjust_led();
        printf("Light changed to green.\r\n");
    }
    change_light_color_flag = 0;
}

/*
 * @brief : Function to change light color to blue
 */
static void change_light_color_blue_command() {
    if (get_color() == BLUE_COLOR)
        printf("Light is already blue.\r\n");
    else {
        if (get_brightness() == BRIGHTNESS_0_PERCENT)
            set_brightness(BRIGHTNESS_25_PERCENT);  // Turn on light if it is off before changing color
        set_color(BLUE_COLOR);
        adjust_led();
        printf("Light changed to blue.\r\n");
    }
    change_light_color_flag = 0;
}

/*
 * @brief : Function to change light color to white
 */
static void change_light_color_white_command() {
    if (get_color() == WHITE_COLOR)
        printf("Light is already white.\r\n");
    else {
        if (get_brightness() == BRIGHTNESS_0_PERCENT)
            set_brightness(BRIGHTNESS_25_PERCENT); // Turn on light if it is off before changing color
        set_color(WHITE_COLOR);
        adjust_led();
        printf("Light changed to white.\r\n");
    }
    change_light_color_flag = 0;
}

/*
 * @brief : Function to handle unknown light color
 */
static void change_light_color_unknown_command() {
    printf("Unknown light color. Cannot change light color.\r\n");
    change_light_color_flag = 0;
}

/*
 * @brief : Function to change light color intensity
 */
static void change_light_intensity_command() {
    printf("Sure. Use the touch slider to adjust the intensity?\r\n");
    int scanned_percent = scanned_percentage();
    if (scanned_percent == get_brightness())
        printf("Light intensity is already at %d percent\r\n", get_brightness_int(get_brightness()));
    else {
        set_brightness(scanned_percent);
        adjust_led();
        printf("Light intensity changed to %d percent.\r\n", get_brightness_int(get_brightness()));
    }
}

/*
 * @brief : Function to set light timer
 */
static void set_light_timer_command() {
    if (get_brightness() == BRIGHTNESS_0_PERCENT) /* lights off */
        printf("Lights are off. When would you like to turn them on (in seconds)?\r\n");
    else
        printf("Lights are on. When would you like to turn them off (in seconds)?\r\n");
    set_light_timer_flag = 1;
}

/*
 * @brief : Function to set light timer in seconds
 */
static void set_light_timer_seconds_parser(const char *seconds) {
    int seconds_int = atoi(seconds);  // convert string to int

    if (get_brightness() == BRIGHTNESS_0_PERCENT) /* lights off */
        printf("Lights are currently off. Timer set for %d seconds to turn them on.\r\n", seconds_int);
    else
        printf("Lights are currently on. Timer set for %d seconds to turn them off.\r\n", seconds_int);

    reset_timer();
    delay(seconds_int * 250);
    if (get_brightness() == BRIGHTNESS_0_PERCENT)
        set_brightness(BRIGHTNESS_50_PERCENT);
    else
        set_brightness(BRIGHTNESS_0_PERCENT);

    adjust_led();
    set_light_timer_flag = 0;
}

/*
 * @brief : Function to find temperature and humidity
 */
static void temperature_command() {
    i2c_set_flags();
    int16_t temperature = get_temperature();
    i2c_set_flags();
    uint16_t humidity = get_humidity();
    printf("The current temperature is %d degC with a humidity of %d percent.\r\n", temperature, humidity);
}

/*
 * @brief : Function to handle unknown commands
 */
static void unknown_command() {
    printf("I'm sorry. I do not understand that command. Would you like to do something else?\r\n"
           "Type help to know more about supported commands.\r\n");
}

/*
 * @brief : Function to handle the help command
 */
static void help_command() {
    printf("Command: Turn on light \r\n");
    printf("Command: Turn off light \r\n");
    printf("Command: Change light color \r\n");
    printf("Command: Change light intensity \r\n");
    printf("Command: Set light timer \r\n");
    printf("Command: What is the Temperature \r\n");
}

// Command list
static const Commands base_commands[] = {
        {"change light color",      change_light_color_command},
        {"change light intensity",  change_light_intensity_command},
        {"set light timer",         set_light_timer_command},
        {"what is the temperature", temperature_command},
        {"turn on light",           turn_on_light_command},
        {"turn off light",          turn_off_light_command},
        {"help",                    help_command},
        {"",                        unknown_command}
};
// Color list
static const Commands light_color_commands[] = {
        {"red",   change_light_color_red_command},
        {"blue",  change_light_color_blue_command},
        {"green", change_light_color_green_command},
        {"white", change_light_color_white_command},
        {"",      change_light_color_unknown_command}
};

/*
 * @brief : This function is called when the user types a command.
 * @param : str - the command typed by the user
 */
void parse_user_input(char *str) {
    char arr[CMD_LINE_LIMIT] = {0};
    char *ptr1 = &arr[0];
    char *ptr2 = &str[0];

    while (*ptr2 != '\0') {
        if (*ptr2 == '\r') {
            ptr2++;
            continue;
        }
        *ptr1++ = isspace(*ptr2) ? *ptr2++ : tolower(*ptr2++);
    }
    *ptr1 = '\0';

    if (set_light_timer_flag) {
        set_light_timer_seconds_parser(arr);
        return;
    }

    if (change_light_color_flag) {
        int N = sizeof(light_color_commands) / sizeof(Commands);
        for (int i = 0; i < N - 1; i++) {
            if (strcmp(arr, light_color_commands[i].head) == 0) {
                light_color_commands[i].function();
                return;
            }
        }
        change_light_color_unknown_command();
    } else {
        int N = sizeof(base_commands) / sizeof(Commands);
        for (int i = 0; i < N - 1; i++) {
            if (strcmp(arr, base_commands[i].head) == 0) {
                base_commands[i].function();
                return;
            }
        }
        unknown_command();
    }
    return;
}
