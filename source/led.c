/**
 * @file :  led.c
 * @brief : LED initialization and control functions header
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 * @references : https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_7/PWM_LED/Source/timers.c
 *
 */

#include "led.h"
#include "colors.h"

#define RED_LED_PWM (TPM2->CONTROLS[0].CnV) // Red LED with PWM
#define GREEN_LED_PWM (TPM2->CONTROLS[1].CnV) // Green LED with PWM
#define BLUE_LED_PWM (TPM0->CONTROLS[1].CnV) // Blue LED with PWM

#define RED_LED_PIN (18)
#define GREEN_LED_PIN (19)
#define BLUE_LED_PIN (1)

/*
 * @brief : Function to initialize RGB LEDs with PWM capabilities
 * @return : none
 */
void init_leds() {
    // Enable Clock to Port B and Port D for RGB LEDs
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
    SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM2_MASK;

    // Enable the FlexibleTimer configs that enable PWM capabilities
    PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK; // RED LED
    PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(3);

    PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK; // GREEN LED
    PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(3);

    PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK; // BLUE LED
    PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(4);

    // Configure TPM
    // Setting Clock Source at CPU rate - 48 Mhz
    SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

    TPM0->MOD = PWM_PERIOD - 1;
    TPM2->MOD = PWM_PERIOD - 1;

    // Prescalar set to 1, no division
    TPM0->SC = TPM_SC_PS(0);
    TPM2->SC = TPM_SC_PS(0);

    // Contiunue Operation in Debug Mode
    TPM0->CONF |= TPM_CONF_DBGMODE(3);
    TPM2->CONF |= TPM_CONF_DBGMODE(3);

    // Channel Based Setup to Edge-alligned active-low PWM
    TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
    TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
    TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;

    // Setting Initial Duty cycle to 0
    TPM2->CONTROLS[0].CnV = 0;
    TPM2->CONTROLS[1].CnV = 0;
    TPM0->CONTROLS[1].CnV = 0;

    // Start TPM
    TPM2->SC |= TPM_SC_CMOD(1);
    TPM0->SC |= TPM_SC_CMOD(1);
}


/*
 *  @brief : Function to control HEX Triplet values for RED,GREEN and BLUE LEDs
 *  @param : RED,GREEN and BLUE values for different state transitions
 *  @return : none
 */
void control_leds(int hex) {
    RED_LED_PWM = (COLOR_RED_FROM_HEX(hex) * PWM_PERIOD) / 0xFF;
    GREEN_LED_PWM = (COLOR_GREEN_FROM_HEX(hex) * PWM_PERIOD) / 0xFF;
    BLUE_LED_PWM = (COLOR_BLUE_FROM_HEX(hex) * PWM_PERIOD) / 0xFF;
}
