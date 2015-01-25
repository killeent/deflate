// Original Author: Trevor Killeen (2015)

#ifndef _BITSTREAM_H_
#define _BITSTREAM_H_

#include <stdio.h>

/**
 * A bitstream is a abstraction layer for bit IO. It allows you to read/write
 * individual bits from/to a file.
 *
 * Because reading and writing from IO has byte-level granularity, a 
 * bitstream works by reading or writing a byte at a time and storing the 
 * individual bits in a buffer.
 * 
 * For example, if we want to read bit-by-bit from a file, we read a whole
 * byte into a buffer and then return the bits one by one. Only once the 
 * bit_count reaches zero do we need to internally read another byte into
 * the buffer.
 *
 * Similarly, if we want to write bit-by-bit to a file, we buffer 8 bits
 * at a time before writing them to the file.
 */

struct bitstream {
  uint8_t bit_count;    // the current number of bits in the buffer
  uint8_t bit_buffer;   // the bit buffer
};

/**
 * Constructs a new bitstream.
 *
 * @return NULL if out of memory, otherwise a pointer to a bitstream.
 */
struct bitstream * bitstream_alloc();

/**
 * Frees the memory associated with the bitstream.
 *
 * @param bs the associated bitstream.
 */
void bitstream_destroy(struct bitstream *bs);

/**
 * Reads the next bit from the file and store it in bit.
 *
 * @param bs the associated bitstream.
 * @param f the file to read from.
 * @param bit output parameter to store the bit read.
 *
 * @return 0 on success, -1 on EOF, otherwise error related to file reading.
 */
int read_bit(struct bitstream *bs, FILE *f, uint8_t *bit);

/**
 * Convenience function to read the next byte from the file. Note that
 * this will not return any bits in the current bit_buffer and will simply
 * read the next aligned byte and the file and clear the buffer.
 *
 * @param bs the associated bitstream.
 * @param f the file to read from.
 * @param byte output parameter to store the byte read.
 *
 * @return 0 on success, otherwise error related to file reading.
 */
int read_byte(struct bitstream *bs, FILE *f, uint8_t *byte);

/**
 * Append the specified bit to the end of the file. Note that the
 * bit is only written once the bit_buffer is full. If you want the
 * bit to be written now, call flush().
 *
 * @param bs the associated bitstream.
 * @param f the file to write to.
 * @param bit the bit to write.
 *
 * @return 0 on success, otherwise error related to file writing.
 */
int write_bit(struct bitstream *bs, FILE *f, uint8_t bit);

/**
 * Append the specified byte to the end of the file. Note that
 * this will not write any of the current bits in the bit_buffer
 * and will simply write the specified byte. The bit_buffer is
 * cleared when write_byte is called.
 *
 * @param bs the associated bitstream.
 * @param f the file to write to.
 * @param bit the byte to write.
 *
 * @return 0 on success, otherwise error related to file writing.
 */
int write_byte(struct bitstream *bs, FILE *f, uint8_t byte);

/**
 * Write the bits in the bit_buffer to the file. If there are 7
 * or fewer bits in the bit_buffer, the remaining bits that make up
 * the byte written will be 0.
 *
 * @param bs the associated bitstream.
 * @param f the file to write to.
 *
 * @return 0 on success, otherwise error related to file writing.
 */
int flush(struct bitstream *bs, FILE *f);

#endif
