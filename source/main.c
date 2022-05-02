#include <stdio.h>

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"

#include "TSI.h"
#include "timer_systick.h"
#include "uart.h"
#include "sysclock.h"
#include "i2c.h"
#include "test_cbfifo.h"



static void init_peripherals() {
    /* Initializes SysTick Timer present in ARM Cortex SCS */
    init_systick();
    /* TSI Module Initialization */
    touch_init();
    /* RGB LEDs with PWM Initialization */
    init_leds();
    /* System Clock Initialization */
    sysclock_init();
    /* UART Initialization */
    init_uart0();
    /* I2C Initialization */
    i2c_init();
    i2c_set_flags();
}


int main() {
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    /* Initialize peripherals */
    init_peripherals();
    /* Test FIFO */
    test_cbfifo();

    /* Infinite loop */
    printf("Welcome to Home Automation.\r\nWhat would you like to do?\r\n");
    while (1) {
        printf("> ");
        handling_func();
    }
    return 0;
}


