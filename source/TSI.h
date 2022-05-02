/**
 * @file :  TSI.h
 * @brief : Capacitance touch initialisation
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 * @references : https://github.com/alexander-g-dean/ESF/blob/master/NXP/Misc/Touch%20Sense/TSI/src/main.c
 * 				 https://github.com/alexander-g-dean/ESF/blob/master/NXP/Misc/Touch%20Sense/TSI_Module_report.docx
 *
 */

#ifndef TSI_H_
#define TSI_H_

#include "colors.h"
#include "led.h"

/*
 * @brief: Initializes capacitive touch sensor on the KL25Z4 board
 * @return: void
 */
void touch_init();

/*
 * @brief: Used to get the instantaneous touch value of the capcitive
 * touch sensor
 *
 * @return: touch value in int
 */
int touch_scan(void);

/*
 * @brief: This function will use the touch value to determine the region at
 * which a touch was detected on the sensor. Based on defined thresholds it will
 * return the intensity percentage. Based on which the intensity of the particular
 * led changes
 */
brightness_t scanned_percentage();

#endif /* TSI_H_ */


