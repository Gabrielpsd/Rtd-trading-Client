#ifndef Connection
#define RTD_WS   "\t\r\n " // whitespaces
#define ESPACE 32 
#define DQUOTES 34
#define BUFFER 512

#include <stdio.h> /* FIL, size_t */

struct File {
  const char *filename;
  FILE *stream;
};

char * buscaTag(char * XML_document,int qArgumentos, char * tag,...);

char * realizaGetEmUmaPagina(char *);

char * retornaIdTag(int qArguments,char * tag, ...);

char * retornaNomeTag(int qArguments,char * tag, ...);

char * substring(char * string, int posInicial, int posFinal);
/* static size_t my_fwrite(void *, size_t , size_t ,void *);
 */
#endif