/**
 * @file - test_cbfifo.c
 * @brief - Test functions for cbfifo
 * @author - Tejaswini Lakshminarayan, tela4318@colorado.edu
 */

#include <assert.h>

#include "test_cbfifo.h"
#include "cbfifo.h"

/*
 * @brief: Tests CBFIFO functionality
 *
 * @return: SUCCESS if the test passes, raises an error otherwise
 */
int test_cbfifo() {
    char var[256] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz\n"
                    "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz\n"
                    "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz\n"
                    "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz\n"
                    "abcdefghijklmnopqrstuvwxyzabcdefghijklmn";
    char buf[256];

    CircularBuffer test_buffer;

    cbfifo_init(&test_buffer);

    // Enqueue when nbytes = 0
    assert(cbfifo_enqueue(&var, 0, &test_buffer) == 0);
    assert(cbfifo_length(&test_buffer) == 0);
    assert(cbfifo_capacity() == CAPACITY);

    // Dequeue when nybtes = 0
    assert(cbfifo_dequeue(&buf, 0, &test_buffer) == 0);
    assert(cbfifo_length(&test_buffer) == 0);
    assert(cbfifo_capacity() == CAPACITY);

    //Enqueue 40 bytes and dequeue 40 bytes
    assert(cbfifo_capacity() == CAPACITY);
    assert(cbfifo_enqueue(&var, 40, &test_buffer) == 40);
    assert(cbfifo_length(&test_buffer) == 40);
    assert(cbfifo_dequeue(&buf, 40, &test_buffer) == 40);
    assert(cbfifo_length(&test_buffer) == 0);

    //Enqueue 40 bytes, Dequeue 20 bytes
    assert(cbfifo_capacity() == CAPACITY);
    assert(cbfifo_enqueue(&var, 40, &test_buffer) == 40);
    assert(cbfifo_length(&test_buffer) == 40);
    assert(cbfifo_dequeue(&buf, 20, &test_buffer) == 20);
    assert(cbfifo_length(&test_buffer) == 20);

    //Enqueue buffer has 20 elements
    //Enqueue till Capacity, Dequeue in steps till capacity
    assert(cbfifo_capacity() == CAPACITY);
    assert(cbfifo_enqueue(&var, 48, &test_buffer) == 48);
    assert(cbfifo_length(&test_buffer) == 68);
    assert(cbfifo_dequeue(&buf, 20, &test_buffer) == 20);
    assert(cbfifo_length(&test_buffer) == 48);
    assert(cbfifo_dequeue(&buf, 10, &test_buffer) == 10);
    assert(cbfifo_length(&test_buffer) == 38);
    assert(cbfifo_dequeue(&buf, 38, &test_buffer) == 38);
    assert(cbfifo_length(&test_buffer) == 0);

    //Enqueue more than capacity
    assert(cbfifo_capacity() == CAPACITY);
    assert(cbfifo_enqueue(&var, CAPACITY, &test_buffer) == CAPACITY);
    assert(cbfifo_length(&test_buffer) == CAPACITY);
    assert(cbfifo_enqueue(&var, 15, &test_buffer) == 0);
    assert(cbfifo_length(&test_buffer) == CAPACITY);

    //Dequeue more than capacity
    assert(cbfifo_capacity() == CAPACITY);
    assert(cbfifo_dequeue(&buf, CAPACITY, &test_buffer) == CAPACITY);
    assert(cbfifo_length(&test_buffer) == 0);
    assert(cbfifo_dequeue(&buf, 15, &test_buffer) == 0);
    assert(cbfifo_length(&test_buffer) == 0);

    // Read < write --> read_counter == write_counter --> nbyte < (CAPACITY - write + read)
    assert(cbfifo_capacity() == CAPACITY);
    assert(cbfifo_enqueue(&var, 45, &test_buffer) == 45);
    assert(cbfifo_length(&test_buffer) == 45);
    assert(cbfifo_dequeue(&buf, 25, &test_buffer) == 25);
    assert(cbfifo_length(&test_buffer) == 20);

    // Read < write --> read_counter == write_counter --> nbyte > (CAPACITY - write + read)
    assert(cbfifo_capacity() == CAPACITY);
    assert(cbfifo_enqueue(&var, 45, &test_buffer) == 45);
    assert(cbfifo_length(&test_buffer) == 65);
    assert(cbfifo_dequeue(&buf, 80, &test_buffer) == 65);
    assert(cbfifo_length(&test_buffer) == 0);

    // Read > write --> write_counter > read_counter --> nbyte < read - write
    assert(cbfifo_capacity() == CAPACITY);
    assert(cbfifo_enqueue(&var, 18, &test_buffer) == 18);
    assert(cbfifo_length(&test_buffer) == 18);
    assert(cbfifo_dequeue(&buf, 9, &test_buffer) == 9);
    assert(cbfifo_length(&test_buffer) == 9);

    // Read > write --> write_counter > read_counter --> nbyte > read - write
    assert(cbfifo_capacity() == CAPACITY);
    assert(cbfifo_enqueue(&var, 20, &test_buffer) == 20);
    assert(cbfifo_length(&test_buffer) == 29);
    assert(cbfifo_dequeue(&buf, 35, &test_buffer) == 29);
    assert(cbfifo_length(&test_buffer) == 0);

    // write > read --> write_counter = read_counter --> nbyte > (write - read)
    assert(cbfifo_capacity() == CAPACITY);
    assert(cbfifo_enqueue(&var, 20, &test_buffer) == 20);
    assert(cbfifo_length(&test_buffer) == 20);
    assert(cbfifo_dequeue(&buf, 30, &test_buffer) == 20);
    assert(cbfifo_length(&test_buffer) == 0);

    // write > read --> write_counter = read_counter --> nbyte < (write - read)
    assert(cbfifo_capacity() == CAPACITY);
    assert(cbfifo_enqueue(&var, 20, &test_buffer) == 20);
    assert(cbfifo_length(&test_buffer) == 20);
    assert(cbfifo_dequeue(&buf, 10, &test_buffer) == 10);
    assert(cbfifo_length(&test_buffer) == 10);

    // write < read --> write_counter > read_counter --> (nbyte > (CAPACITY - read + write))
    assert(cbfifo_capacity() == CAPACITY);
    assert(cbfifo_enqueue(&var, 98, &test_buffer) == 98);
    assert(cbfifo_length(&test_buffer) == 108);
    assert(cbfifo_dequeue(&buf, 120, &test_buffer) == 108);
    assert(cbfifo_length(&test_buffer) == 0);

    // write < read --> write_counter > read_counter --> (nbyte < (CAPACITY - read + write))
    assert(cbfifo_capacity() == CAPACITY);
    assert(cbfifo_enqueue(&var, 110, &test_buffer) == 110);
    assert(cbfifo_length(&test_buffer) == 110);
    assert(cbfifo_dequeue(&buf, 40, &test_buffer) == 40);
    assert(cbfifo_length(&test_buffer) == 70);

    return SUCCESS;
}
