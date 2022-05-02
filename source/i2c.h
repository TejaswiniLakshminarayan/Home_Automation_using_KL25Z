

#ifndef I2C_H_
#define I2C_H_


#include <stdint.h>
#include <stdio.h>

#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#define I2C1_M_START    (I2C1->C1 |= I2C_C1_MST_MASK)   //start signal is generated and master mode is selected
#define I2C1_M_STOP     (I2C1->C1 &= ~I2C_C1_MST_MASK)  //stop signal is generated and slave mode is selected
#define I2C1_M_RSTART   (I2C1->C1 |= I2C_C1_RSTA_MASK)  //setting the Repeat Start bit to generate repeated start condition

#define I2C1_TRAN       (I2C1->C1 |= I2C_C1_TX_MASK)    //transmit mode is selected
#define I2C1_REC        (I2C1->C1 &= ~I2C_C1_TX_MASK)   //receive mode is selected

#define I2C1_NACK       (I2C1->C1 |= I2C_C1_TXAK_MASK)  //no acknowledgment signal is sent to the bus
#define I2C1_ACK        (I2C1->C1 &= ~I2C_C1_TXAK_MASK) //acknowledgment signal is sent to the bus

//wait till getting the interrupt
#define I2C1_WAIT       while((I2C1->S & I2C_S_IICIF_MASK)==0);I2C1->S |= I2C_S_IICIF_MASK;

//check if the transfer of byte and acknowledgment is completed
#define TRANS_COMP      while((I2C1->S & I2C_S_TCF_MASK)==0);


/*
 * @brief : Initialize the clock for I2C1 and PORTE
 */
void i2c_init();

/*
 * @brief : Sets flags for ICR, MULT and IICEN
 */
void i2c_set_flags();

/*
 * @brief : reads raw data from the I2C bus
 * @param : dev - device address
 * @param : reg - register address
 * @return : returns the raw values of temperature and humidity
 */
uint16_t i2c_read_bytes(uint8_t dev, uint8_t address);

#endif /* I2C_H_ */
