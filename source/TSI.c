/**
 * @file :  TSI.c
 * @brief : Capacitance touch initialization
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 * @references : https://github.com/alexander-g-dean/ESF/blob/master/NXP/Misc/Touch%20Sense/TSI/src/main.c
 * 				 https://github.com/alexander-g-dean/ESF/blob/master/NXP/Misc/Touch%20Sense/TSI_Module_report.docx
 */

#include "TSI.h"
#include "colors.h"


#define TOUCH_OFFSET    550  // offset value to be subtracted
#define TOUCH_DATA      (TSI0->DATA & 0xFFFF)  // macro for extracting the count from data register

// thresholds for a given location
#define ZERO_TOUCH          55
#define TWENTY_FIVE_TOUCH   80
#define FIFTY_TOUCH         150
#define SEVENTY_FIVE_TOUCH  170
#define HUNDRED_TOUCH       200

// thresholds when untouched
#define UNTOUCHED           50

/*
 * @brief: Initializes capacitive touch sensor on the KL25Z4 board
 */
void touch_init() {
    SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;            // enabling the clock to TSI module
    TSI0->GENCS = TSI_GENCS_MODE(0u) |           //operating in non-noise mode
                  TSI_GENCS_REFCHRG(0u) |        //reference oscillator charge and discharge value 500nA
                  TSI_GENCS_DVOLT(0u) |          //oscillator voltage rails set to default
                  TSI_GENCS_EXTCHRG(0u) |        //electrode oscillator charge and discharge value 500nA
                  TSI_GENCS_PS(0u) |             //frequency clock divided by one
                  TSI_GENCS_NSCN(31u) |          //scanning the electrode 32 times
                  TSI_GENCS_TSIEN_MASK |         //enabling the TSI module
                  TSI_GENCS_EOSF_MASK;           // writing one to clear the end of scan flag
}

/*
 * @brief : Used to get the instantaneous touch value of the capcitive touch sensor
 * @return : touch value in int
 */
int touch_scan() {
    unsigned int scan = 0;
    TSI0->DATA = TSI_DATA_TSICH(10u);
    TSI0->DATA |= TSI_DATA_SWTS_MASK;            //software trigger to start the scan
    while (!(TSI0->GENCS & TSI_GENCS_EOSF_MASK)); // waiting for the scan to complete 32 times
    scan = TOUCH_DATA;
    TSI0->GENCS |= TSI_GENCS_EOSF_MASK;          //writing one to clear the end of scan flag
    return scan - TOUCH_OFFSET;
}

/*
 * @brief: Determine the location of the touch using the touch value and use thresholds to determine the brightness
 * @return : brightness value
 */
brightness_t scanned_percentage() {
    int touch_value;
    while (1) {
        int initial_touch_value = touch_scan();
        if (initial_touch_value > UNTOUCHED) {
            touch_value = initial_touch_value;
            break;
        }
    }
    //Returns color intensity percentage
    if (touch_value < ZERO_TOUCH)
        return BRIGHTNESS_0_PERCENT;
    if (touch_value > ZERO_TOUCH && touch_value <= TWENTY_FIVE_TOUCH)
        return BRIGHTNESS_25_PERCENT;
    if (touch_value > TWENTY_FIVE_TOUCH && touch_value <= FIFTY_TOUCH)
        return BRIGHTNESS_50_PERCENT;
    if (touch_value > FIFTY_TOUCH && touch_value <= SEVENTY_FIVE_TOUCH)
        return BRIGHTNESS_75_PERCENT;
    if (touch_value > SEVENTY_FIVE_TOUCH)
        return BRIGHTNESS_100_PERCENT;
    return BRIGHTNESS_100_PERCENT;
}
