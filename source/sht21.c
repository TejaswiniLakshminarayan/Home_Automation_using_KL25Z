/**
 * @file :  sht21.c
 * @brief : SHT21 sensor interface
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 *
 */

#include "i2c.h"
#include "sht21.h"
#include <stdint.h>

#define SHT21_ADDR  (0x40)  // device address for SHT21
#define TEMPERATURE (0xE3)  // address of the register to get the temperature value
#define HUMIDITY    (0xE5)  // address of the register to get the humidity value

/*
 * @brief : the function returns the temperature in degree Celsius using datasheet formula
 * @return : computed temperature in degree celsius as integers
 */
int16_t get_temperature() {
    int16_t raw_data = i2c_read_bytes(SHT21_ADDR, TEMPERATURE);  // read the temperature register data
    raw_data &= ~0x003;  // clear last 2 bits as per SHT21 datasheet
    return (int16_t)(-46.85 + 175.72 / 65536 * (float) raw_data);  // convert the raw data to celsius
}

/*
 * @brief : the function returns the humidity in percentage using datasheet formula
 * @return : computed humidity in percentage as integers
 */
uint16_t get_humidity() {
    uint16_t raw_data = i2c_read_bytes(SHT21_ADDR, HUMIDITY);  // read the humidity register data
    raw_data &= ~0x003;  // clear last 2 bits as per SHT21 datasheet
    return (uint16_t)(-6.0 + 125.0 / 65536 * (float) raw_data);  // convert the raw data to percentage
}
