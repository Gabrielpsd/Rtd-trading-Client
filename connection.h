#ifndef Connection
#define RTD_WS   "\t\r\n " // whitespaces
#define ESPACE 32 
#define DQUOTES 34
#define BUFFER 940826

struct MemoryStruct {
  char *memory;
  size_t size;
};

#include <curl\curl.h> /* CURLcode */

/* Função realiza a busca de todos as tags encontradas em um arquivo de texto. O valor retornado sera um ponteiro que consiste 
em um vetor de strings onde cada elemento é uma das tags encontradas

 argumentos: 
  -XML_document: trata-se do documento HTML/XML que será realizado a busca
  -qArgumentos: quantidade de argumentos utilizado na filtragem. (1 ou 2)
  -tag: tag que será filtrado. 
  -4º argumento(opcional): caso qArgumentos seja igual a 2 esse argumento pode ser utilizado. Deverá ser 
  uma string que consiste no ID da tag.
*/
char * buscaTag(char * XML_document,int qArgumentos, char * tag,...);

/* funcao que realiza uma requisição Get e retorna o HTML da página para que seja tratado por outras funções 

  Argumentos.
  -URL: URL da página.
  -resposta: uma estrutura do tipo CURLres onde o resultado será gravado
*/
CURLcode realizaGetEmUmaPagina(char * URL, struct MemoryStruct  * resposta);

/* A função realiza uma busca em uma tag e procura o Id da tag e a retorna em formato Char* 

  argumentos:
  -qArgumentos: quantidade de argumentos passados, aceita 1 ou 2.
  -tag: linha contendo o a tag
  -3º argumento (opcional): caso o qArgumentos seja dois esse parametro pode ser utilizado. Consistem em um ponteiro 
  -de inteiro que será preenchido com o tamanho da Id.
*/
char * retornaIdTag(int qArguments,char * tag, ...);

/* A função realiza uma busca em uma tag e procura o nome da tag e a retorna em formato Char* 

  argumentos:
  -qArgumentos: quantidade de argumentos passados, aceita 1 ou 2.
  -tag: linha contendo o a tag
  -3º argumento (opcional): caso o qArgumentos seja dois esse parametro pode ser utilizado. Consistem em um ponteiro 
  de inteiro que será preenchido com o tamanho do nome da tag.
*/
char * retornaNomeTag(int qArguments,char * tag, ...);

/*
  A função retorna uma substring que vai desde a posInicial até a posFinal

  argumentos: 
  -string: texto que sera retirado o subtexto.
  -posInicial: posição inicial do intervalo do texto
  -posFinal: posição final do intervalo do texto
*/
char * substring(char * string, int posInicial, int posFinal);

/* essa função é utilizada na requisição CURL, utilizada para evitar o comportamento padrão de imprimir na tela do CURL*/
static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);

#endif