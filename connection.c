
#include <curl\curl.h> /*  */
#include <stdlib.h> 
#include <stdio.h> /* null ,fopen, fwrite */

#include "connection.h" /* FIle */


static size_t my_fwrite(void *buffer, size_t size, size_t nmemb,void *stream)
{
  struct File *out = (struct File *)stream;

  if(!out->stream) {
    /* open file for writing */
    out->stream = fopen(out->filename, "wb");
    if(!out->stream)
      return 0;
  }
  return fwrite(buffer, size, nmemb, out->stream);
}