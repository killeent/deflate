// Original Author: Trevor Killeen (2015)

#ifndef _FREQUENCY_H_
#define _FREQUENCY_H_

/**
 * Calculates the frequencies of each ASCII character in the specified file.
 * Internally this constructs a new long array and stores it in output param
 * freqs, where freqs[i] = count of ASCII character i in file.
 *
 * @param the file to calculate frequencies for.
 * @param freqs output parameter for frequency array.
 *
 * @return 0 on success, otherwise error. 
 */
int calc_frequencies(char *file, unsigned long **freqs);

#endif
