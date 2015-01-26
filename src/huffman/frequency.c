// Original Author: Trevor Killeen (2015)

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include "./frequency.h"

#define ARR_SIZE 128

int calc_frequencies(char *file, unsigned long **freqs, unsigned int *len) {
  assert(file != NULL);
  assert(freqs != NULL);
  
  FILE *f;
  int ch, err;

  f = fopen(file, "r");
  if (f == NULL) {
    return errno;
  }  

  *freqs = (unsigned long *)calloc(ARR_SIZE, sizeof(unsigned long));
  if (freqs == NULL) {
    fclose(f);
    return errno;
  }
  *len = ARR_SIZE;

  // count the frequency of the characters in the file
  while ((ch = fgetc(f)) != EOF) {
    *freqs[ch] += 1;
  }
  
  // check and see if an error caused the EOF
  if ((err = ferror(f)) != 0) {
    free(*freqs);
    fclose(f);
    return err; 
  }

  fclose(f);
  return 0;
}
