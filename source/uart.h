/**
 * @file : uart.h
 * @brief : UART driver header
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 *
 */

#ifndef UART_H_
#define UART_H_

#include "MKL25Z4.h"
#include <stdio.h>

/*
 * @brief : Initialization function for the UART0
 */
void init_uart0();

/*
 * @brief : Sending string over UART
 * @param : str - String to send over UART
 * @param : count - Number of bytes to store
 */
void send_string(void *str, size_t count);

/*
 * @brief : Receive data from UART
 * @param : str - String to receive from UART
 * @param : count - Number of bytes to read
 * @return : Number of read bytes
 */
size_t receive_string(void *str, size_t count);

/*
 * @brief : Function to check if UART is ready to receive data and receive data
 */
void handling_func();

#endif /* UART_H_ */
