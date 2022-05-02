/**
 * @file :  i2c.c
 * @brief : I2C controller
 * @author : Tejaswini Lakshminarayan
 * @references : https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/src/i2c.c
 *
 */

#include <stdio.h>

#include "i2c.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

/*
 * @brief : Initialize the clock for I2C1 and PORTE
 */
void i2c_init() {
    SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
}

/*
 * @brief : Sets flags for ICR, MULT and IICEN
 */
void i2c_set_flags() {
    PORTE->PCR[0] |= PORT_PCR_MUX(6);  // setting the I2C1 SDA port
    PORTE->PCR[1] |= PORT_PCR_MUX(6);  // setting the I2C1 SCL port
    I2C1->C1 = 0;  //setting the C1 register as 0 to clear all the bits

    //setting the clock rate by dividing 24MHz by 400KHz baud to get 60KHz and selecting the multiplying factor as 1
    I2C1->F = (I2C_F_ICR(0x11) | I2C_F_MULT(0));

    I2C1->C1 |= (I2C_C1_IICEN_MASK);  //enable the I2C0 by setting the IICEN mask
    I2C1->C2 |= (I2C_C2_HDRS_MASK);  //select high drive mode
}

/*
 * @brief : reads raw data from the I2C bus
 * @param : dev - device address
 * @param : reg - register address
 * @return : returns the raw values of temperature and humidity
 */
uint16_t i2c_read_bytes(uint8_t dev, uint8_t address) {
    uint8_t data_0, data_1;  // two bytes to data to read
    uint16_t result;

    I2C1_TRAN;  // set to transmit mode
    I2C1_M_START;  // send start

    I2C1->D = dev << 1;  //send device address
    TRANS_COMP  // wait for transfer
    I2C1_WAIT  // wait for completion

    I2C1->D = address; // passing the read address
    TRANS_COMP  // wait for transfer
    I2C1_WAIT  // wait for completion

    I2C1_M_RSTART;  // repeated start

    I2C1->D = ((dev << 1) | 0x01); // send dev address (read)
    TRANS_COMP  // wait for transfer
    I2C1_WAIT  // wait for completion

    I2C1_REC;  // set to receive mode
    I2C1_NACK;  // set NACK for read

    data_0 = I2C1->D; // dummy read
    TRANS_COMP  // wait for transfer
    I2C1_WAIT  // wait for completion

    data_0 = I2C1->D;  // read first byte of data
    TRANS_COMP  // wait for transfer
    I2C1_WAIT  // wait for completion

    data_1 = I2C1->D; // read second byte of data

    I2C1_M_STOP;  // send stop

    result = data_0;  // assign first byte
    result = result << 8;  //  making it MSB
    result += data_1;  //  add the second byte

    return result;
}
