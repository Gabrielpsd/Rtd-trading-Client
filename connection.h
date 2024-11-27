#ifndef Connection

#include <stdio.h> /* FIL, size_t */

struct File {
  const char *filename;
  FILE *stream;
};

static size_t my_fwrite(void *, size_t , size_t ,void *);

#endif