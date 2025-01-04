
#include <curl\curl.h> /* CURL, CURLCode, curl_easy_setopt , curl_easy_init, curl_easy_strerror, curl_easy_cleanup*/
#include <stdlib.h> /* realloc, malloc, free*/
#include <stdio.h> /* null ,fopen , fprintf*/
#include <string.h> /*strlen, memcpy*/
#include "connection.h" /* FIle */

char * buscaTag(char * pagina, int qArgumentos, char * tag, ...)
{
  va_list list; 
  char *id, *auxiliar, *tagAux, *idAux, **tags;
  int contador,InicioTag, finalTag, taglen, idLen, qTags, aux;

  // pega o segundo argumento passado para a função caso exista, sendo essa sempre o Id de uma Tag
  if(qArgumentos ==  2){
    va_start(list,tag);
    id = va_arg(list, char *);
    va_end(list);
  }
  else
  {
    idAux = malloc(sizeof(char*)*1);
    *idAux = '0';
    id = malloc(sizeof(char*)*1);
    *id = '0';
  }

  tags = malloc(sizeof(char*)*1);
  contador = 0; 
  qTags = 0;

  while(pagina[contador] != EOF)
  {
    // abertura de uma tag
    if(pagina[contador] == '<')
    {
      InicioTag = contador;
      while(pagina[contador] != '>') ++contador;

      tagAux = retornaNomeTag(2,substring(pagina,InicioTag+1,contador), &taglen);

      if(strcmp(tagAux,tag) == 0)
      {
        // pego id da tag caso seja passado para realizar a busca
        if(qArgumentos == 2)
        {

          idAux = retornaIdTag(2,substring(pagina,InicioTag+1,contador), &idLen);
        }

        if(strcmp(tagAux,tag) == 0 && (strcmp(id,idAux) == 0 || qArgumentos == 1))
        {

          //buscando o fechamento de uma Tag
          while(1)
          {
            if(pagina[contador] == '/' && pagina[contador-1] == '<')
            {
              finalTag = contador;
              while(pagina[contador] != '>') contador++;
              auxiliar = substring(pagina,finalTag+1,contador);

/*               printf("Comparação entre: %s e %s  == %d \n", retornaNomeTag(1,auxiliar),tag,strcmp(retornaNomeTag(1,auxiliar),tag));
              printf("Contador: %d char: %c \n",contador,pagina[contador]);
 */
              if(strcmp(retornaNomeTag(1,auxiliar),tag) == 0)
              {

                  qTags++;
                  *tags =  realloc(*tags,(sizeof(char*)) * qTags);
                  auxiliar = substring(pagina,InicioTag,contador);
                  tags[qTags] = malloc(sizeof(char) * BUFFER);
                  tags[qTags] = auxiliar;


                  break;
              }
            }
            contador++;
          };

        }
      }
    }
     ++contador;
  }
  for(contador = 1; contador <= qTags; ++contador)
     printf("Reposta final: %s\n",tags[contador]);

  return "Finalizado";
}

CURLcode realizaGetEmUmaPagina(char * URL, struct MemoryStruct  * resposta)
{
  CURL *curl;
  CURLcode res; 

  curl = curl_easy_init();

  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, URL);  

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36");

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    curl_easy_setopt(curl, CURLOPT_CA_CACHE_TIMEOUT, 604800L);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,write_data);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)resposta);
 
    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    curl_easy_cleanup(curl);  

  } 
  return res;
}

char * retornaIdTag(int qArguments,char * tag, ...)
{
  int position,strlen, *pstrlen; 
  char * retorno; 
  va_list list;

  retorno = (char *) malloc(BUFFER * sizeof(char));
  position = strcspn(tag,"id") + 4;
  strlen=0;
  
  while (tag[position] != DQUOTES && tag[position] != '\0')
  {
    retorno[strlen++] = tag[position++];
  }

  if(qArguments == 2 )
  {
    va_start(list,tag);
    pstrlen = va_arg(list, int * );
    va_end(list);

    *pstrlen = strlen; 
    retorno[strlen] = '\0';
  }
  
  return retorno;
}

char * retornaNomeTag(int qArguments,char * tag, ...)
{
    int position,strlen, *pstrlen; 
    char * retorno; 
    va_list list;

    retorno = (char *) malloc(BUFFER * sizeof(char));
    strlen=0;
   /*  printf("Entrei aqui (5)"); */
    while (tag[strlen] != ' ' && tag[strlen] != '\0' && tag[strlen] != '>')
    {
      retorno[strlen] = tag[strlen++];
    }

    if(qArguments == 2)
    {
      va_start(list,tag);
      pstrlen = va_arg(list, int * );
      va_end(list);

      *pstrlen = strlen; 
    }

    retorno[strlen] = '\0';
    return retorno; 
}

char * substring(char * string, int posInicial, int posFinal)
{
    char * copia; 
    int contador = 0; 

    copia = (char *) malloc(BUFFER * sizeof(char));

    while(posInicial <= posFinal)
    {
      copia[contador] = string[posInicial];
      contador++;
      posInicial++;
    }

    copia[contador] = '\0';
    return copia;
}

static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
  size_t tamanhoReal = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  char *ptr;

  ptr = realloc(mem->memory, mem->size + tamanhoReal + 1);

  if(!ptr)
  {
    return 0; /* out of memory*/
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), buffer, tamanhoReal);
  mem->size += tamanhoReal ;
  mem->memory[mem->size] = 0;


  return size * nmemb;
}