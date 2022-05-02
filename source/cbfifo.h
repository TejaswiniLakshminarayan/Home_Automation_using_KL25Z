/**
 * @file :  cbfifo.h
 * @brief : Circular buffer implementation header
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 *
 */

#ifndef _CBFIFO_H_
#define _CBFIFO_H_

#include <stdlib.h>

#define CAPACITY 256  // circular buffer capacity
#define ERROR ((size_t)-1)  // error value

// circular buffer structure
typedef struct CircularBuffer {
    char buffer[CAPACITY]; // buffer used for read and write
    unsigned int write; // write index
    unsigned int read; // read index
    unsigned int count; // number of bytes that can be dequeued
    unsigned int write_counter; // write loop count
    unsigned int read_counter; // read loop count
} CircularBuffer;


/*
 * @ brief : Initialize the circular buffer
 * @ param : buffer - Pointer to the circular buffer
 */
void cbfifo_init(CircularBuffer *buffer);


/*
 * @ brief : Enqueue data onto the FIFO
 * @ param : buf - Pointer to the data
 * @ param : nbyte - Max number of bytes to enqueue
 * @ param : buffer - Pointer to the circular buffer
 * @ return : The number of bytes actually enqueued, which could be 0.
 *            In case of an error, returns (size_t) -1.
 */
size_t cbfifo_enqueue(void *buf, size_t nbyte, CircularBuffer *buffer);


/*
 * @ brief : Dequeue data from the FIFO
 * @ param : buf - Pointer to the data
 * @ param : nbyte - Max number of bytes to dequeue
 * @ param : buffer - Pointer to the circular buffer
 * @ return : The number of bytes actually dequeued, which could be 0.
 */
size_t cbfifo_dequeue(void *buf, size_t nbyte, CircularBuffer *buffer);


/*
 * @ brief : Returns the number of bytes currently on the FIFO
 * @ param : buffer - Pointer to the circular buffer
 * @ return : Number of bytes currently available to be dequeued from the FIFO
 */
size_t cbfifo_length(CircularBuffer *buffer);


/*
 * @ brief : Returns the FIFO's capacity
 * @ return : The capacity, in bytes, for the FIFO
 */
size_t cbfifo_capacity();


/*
 * @ brief : Returns the status of buffer's fullness
 * @ param : buffer - Pointer to the circular buffer
 * @ return : 1 when buffer is full else 0
 */
int cbfifo_full(CircularBuffer *buffer);


#endif // _CBFIFO_H_
