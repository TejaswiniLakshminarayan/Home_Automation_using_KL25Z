/**
 * @file :  sht21.h
 * @brief : SHT21 sensor interface header
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 *
 */

#ifndef SHT21_H_
#define SHT21_H_

/*
 * @brief : the function returns the temperature in degree Celsius using datasheet (formula)
 * @return : computed temperature in degree celsius as integers
 */
int16_t get_temperature();

/*
 * @brief : the function returns the humidity in percentage using datasheet (formula)
 * @return : computed humidity in percentage as integers
 */
uint16_t get_humidity();

#endif /* SHT21_H_ */
