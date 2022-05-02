/**
 * @file :  cbfifo.c
 * @brief : Circular buffer implementation
 * @author : Tejaswini Lakshminarayan, tela4318@colorado.edu
 *
 */

#include "cbfifo.h"


/*
 * @ brief : Enqueue data onto the FIFO
 * @ param : buf - Pointer to the data
 * @ param : nbyte - Max number of bytes to enqueue
 * @ param : buffer - Pointer to the circular buffer
 * @ return : The number of bytes actually enqueued, which could be 0.
 *            In case of an error, returns (size_t) -1.
 */
size_t cbfifo_enqueue(void *buf, size_t nbyte, CircularBuffer *buffer) {
    // Check for null buffer
    if (buf == NULL)
        return ERROR;

    char *pointer = (char *) buf;
    size_t check_write = 0; // number of bytes enqueued

    // adjusting nbytes based on availability
    if ((nbyte > (CAPACITY - buffer->write + buffer->read)) && (buffer->read_counter == buffer->write_counter))
        nbyte = CAPACITY - buffer->write +
                buffer->read; // needs to be updated based on the write_counter and read_read counter.
    if ((nbyte > (buffer->read - buffer->write)) && (buffer->read_counter < buffer->write_counter))
        nbyte = (buffer->read - buffer->write);

    // enqueuing into the buffer
    for (int i = 0; i < nbyte; i++) {
        buffer->buffer[buffer->write] = *pointer;
        pointer++;
        buffer->write++;
        // handling the overflow condition for right based on CAPACITY
        if (buffer->write >= CAPACITY) {
            buffer->write_counter++;
            buffer->write = 0;
        }
        buffer->count++;
        check_write++;
    }
    return check_write;
}


/*
 * @ brief : Dequeue data from the FIFO
 * @ param : buf - Pointer to the data
 * @ param : nbyte - Max number of bytes to dequeue
 * @ param : buffer - Pointer to the circular buffer
 * @ return : The number of bytes actually dequeued, which could be 0.
 */
size_t cbfifo_dequeue(void *buf, size_t nbyte, CircularBuffer *buffer) {
    char *pointer = (char *) buf;
    size_t check_read = 0; // number of bytes dequeued

    // adjusting nbytes based on the number of bytes available to be dequeued
    if ((nbyte > (CAPACITY - buffer->read + buffer->write)) && (buffer->write_counter > buffer->read_counter))
        nbyte = CAPACITY - buffer->read + buffer->write;
    if ((nbyte > (buffer->write - buffer->read)) && (buffer->write_counter == buffer->read_counter))
        nbyte = (buffer->write - buffer->read);

    //dequeue from the buffer
    for (int i = 0; i < nbyte; i++) {
        pointer[i] = buffer->buffer[buffer->read];
        buffer->read++;
        //handling the overflow condition for read based on the CAPACITY
        if (buffer->read >= CAPACITY) {
            buffer->read_counter++;
            buffer->read = 0;
        }
        buffer->count--;
        check_read++;
    }
    return check_read;
}

/*
 * @ brief : Returns the number of bytes currently on the FIFO
 * @ param : buffer - Pointer to the circular buffer
 * @ return : Number of bytes currently available to be dequeued from the FIFO
 */
size_t cbfifo_length(CircularBuffer *buffer) {
    return buffer->count;
}

/*
 * @ brief : Returns the status of buffer's fullness
 * @ param : buffer - Pointer to the circular buffer
 * @ return : 1 when buffer is full else 0
 */
int cbfifo_full(CircularBuffer *buffer) {
    return (buffer->count == CAPACITY) ? 1 : 0;
}

/*
 * @ brief : Initialize the circular buffer
 * @ param : buffer - Pointer to the circular buffer
 */
void cbfifo_init(CircularBuffer *buffer) {

    buffer->write = 0;
    buffer->read = 0;
    buffer->count = 0;
    buffer->write_counter = 0;
    buffer->read_counter = 0;
}

/*
 * @ brief : Returns the FIFO's capacity
 * @ return : The capacity, in bytes, for the FIFO
 */
size_t cbfifo_capacity() {
    return CAPACITY;
}
