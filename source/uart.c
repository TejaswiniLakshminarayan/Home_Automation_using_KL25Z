/**
 * @file : uart.c
 * @brief : UART driver
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 * @references : https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/src/UART.c
 *
 */

#include "uart.h"
#include "cbfifo.h"
#include "commandline.h"


#define UART_OVERSAMPLE_RATE    (15)
#define BUS_CLOCK               (24e6)
#define SYS_CLOCK               (24e6)
#define UART_BAUD_RATE          (115200)
#define BUFFER_SIZE             (640)


// Circular buffer for storing sent and received characters
CircularBuffer transfer_buffer;
CircularBuffer receive_buffer;


int __sys_write(int handle, char *buffer, int count) {
    if (buffer == NULL) {
        return -1;
    }
    while (cbfifo_full(&transfer_buffer)) { ;
    }

    if (cbfifo_enqueue(buffer, count, &transfer_buffer) != count)
        return -1;

    if (!(UART0->C2 & UART0_C2_TIE_MASK))
        UART0->C2 |= UART0_C2_TIE(1);

    return 0;
}


int __sys_readc(void) {
    char ch;
    if (cbfifo_dequeue(&ch, 1, &receive_buffer) != 1)
        return -1;
    return ch;
}

/*
 * @brief: Initialization function for the UART0
 */
void init_uart0() {
    uint16_t sbr;

    // clock enable for UART0 and Port A
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

    UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);

    PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
    PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);

    sbr = (uint16_t)((SYS_CLOCK) / (UART_BAUD_RATE * UART_OVERSAMPLE_RATE));
    UART0->BDH &= ~UART0_BDH_SBR_MASK;
    UART0->BDH |= UART0_BDH_SBR(sbr >> 8);
    UART0->BDL = UART0_BDL_SBR(sbr);
    UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE - 1);

    UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(1) | UART0_BDH_LBKDIE(0);

    UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(0) | UART0_C1_PE(0) | UART0_C1_PT(0);

    UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0) | UART0_C3_NEIE(0)
                | UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

    UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

    UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

    // initialize circular transfer and receive buffer
    cbfifo_init(&transfer_buffer);
    cbfifo_init(&receive_buffer);

    //NVIC priority to 2
    NVIC_SetPriority(UART0_IRQn, 2);
    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);

    UART0->C2 |= UART_C2_RIE(1);

    UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

}

/*
 * @brief : Sending string over UART
 * @param : str - String to send over UART
 * @param : count - Number of bytes to store
 */
void send_string(void *str, size_t count) {
    cbfifo_enqueue(str, count, &transfer_buffer);
    if (!(UART0->C2 & UART0_C2_TIE_MASK))
        UART0->C2 |= UART0_C2_TIE(1);
}

/*
 * @brief : Receive data from UART
 * @param : str - String to receive from UART
 * @param : count - Number of bytes to read
 * @return : size_t: Number of read bytes
 */
size_t receive_string(void *str, size_t count) {
    return cbfifo_dequeue(str, count, &receive_buffer);
}

/*
 * @brief : Function to clear UART errors
 */
static void clearUARTErrors(void) {
    UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);
}

/*
 * @brief : Function handle UART0 Interrupt
 */
void UART0_IRQHandler(void) {

    uint8_t ch;

    if (UART0->S1 & (UART_S1_OR_MASK | UART_S1_NF_MASK | UART_S1_FE_MASK | UART_S1_PF_MASK)) {
        clearUARTErrors();
        ch = UART0->D;
    }

    if (UART0->S1 & UART0_S1_RDRF_MASK) {
        // received a character
        ch = UART0->D;
        cbfifo_enqueue(&ch, 1, &receive_buffer);
    }

    if ((UART0->C2 & UART0_C2_TIE_MASK) && // transmitter interrupt enabled
        (UART0->S1 & UART0_S1_TDRE_MASK)) { // transmitter data register empty
        if (cbfifo_dequeue(&ch, 1, &transfer_buffer))
            UART0->D = ch;
        else
            UART0->C2 &= ~UART0_C2_TIE_MASK;  // queue is empty so disable transmitter interrupt

    }
}

/*
 * @brief : Function to check if UART is ready to receive data and receive data
 */
void handling_func() {
    uint8_t temp;
    char buf[BUFFER_SIZE];
    char *ptr = &buf[0];

    while (temp != 0x0D) {
        while (cbfifo_length(&receive_buffer) == 0);
        cbfifo_dequeue(&temp, 1, &receive_buffer);
        putchar(temp);
        if (temp != 0x0D || temp != 0x0A) {
            if (temp != 0x08) {
                *ptr = (char) temp;
                ptr++;
            } else {
                printf(" \b");
                ptr--;
            }
        }
        // transmit if not already transmitting
        if (!(UART0->C2 & UART0_C2_TIE_MASK)) {
            UART0->C2 |= UART0_C2_TIE(1);
        }
        if (temp == '\r') {
            temp = 0x0A;  // '\n'
            printf("\r\n");
            break;
        }

    }
    *ptr = '\0';

    parse_user_input(buf);
}
