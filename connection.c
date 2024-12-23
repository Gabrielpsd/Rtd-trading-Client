
#include <curl\curl.h> /*  */
#include <stdlib.h> /* realloc, malloc, free*/
#include <stdio.h> /* null ,fopen, fwrite */
#include <string.h> /*strlen, */
#include "connection.h" /* FIle */

char * realizaGetEmUmaPagina(char * URL)
{
  CURL *curl;
  CURLcode res; 

  curl_global_init(CURL_GLOBAL_DEFAULT);
  
  curl = curl_easy_init();

  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, URL);  

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36");

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    curl_easy_setopt(curl, CURLOPT_CA_CACHE_TIMEOUT, 604800L);
 
    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    curl_easy_cleanup(curl);  

  } 
  curl_global_cleanup();
 
  return "res";
}

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
      printf("Comparação entre: %s e %s  == %d ", tagAux,tag,strcmp(tagAux,tag));

      if(strcmp(tagAux,tag) == 0)
      {
        // pego id da tag caso seja passado para realizar a busca
        if(qArgumentos == 2)
          idAux = retornaIdTag(2,substring(auxiliar,taglen,strlen(auxiliar)), &idLen);

        if(strcmp(tagAux,tag) == 0 && (strcmp(id,idAux) == 0 || qArgumentos == 1))
        {
          printf("entrei aqui (0)\n");

          //buscando o fechamento de uma Tag
          while(1)
          {
            if(pagina[contador] == '/' && pagina[contador-1] == '<')
            {
              finalTag = contador;
              while(pagina[contador] != '>') contador++;
              auxiliar = substring(pagina,finalTag+1,contador);
              printf("Auxiliar: %s",auxiliar);
              printf("Tag nome: %s",retornaNomeTag(1,auxiliar));

              if(strcmp(retornaNomeTag(1,auxiliar),tag) == 0)
              {
                  printf("entrei aqui (2)\n");
                  printf("Qtags: %d||",qTags);
                  printf("Auxiliar: %s",auxiliar);
                  printf("tag: %s",tag);

                  qTags++;

                  *tags = (char *) realloc(*tags,(sizeof(char)) * qTags);
                  auxiliar = substring(pagina,InicioTag,finalTag);
                  aux = strlen(auxiliar);
                  printf("Alocado: %s||",auxiliar);
                  printf("StringLen: %d||",aux);
                  tags[qTags-1] = (char *)malloc(sizeof(char *) * aux);
                  tags[qTags-1] == auxiliar;
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
  return "Finalizado";
}

char * retornaIdTag(int qArguments,char * tag, ...)
{
  int position,strlen, *pstrlen; 
  char * retorno; 
  va_list list;

  retorno = (char *) malloc(1 * sizeof(char));
  position = strcspn(tag,"id") + 4;
  strlen=0;
  
  while (tag[position] != DQUOTES && tag[position] != '\0')
  {
    retorno = (char *) realloc( retorno, ((strlen + 1 )* sizeof(char)) );
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
    char retorno[BUFFER], *auxiliar; 
    va_list list;

    strlen=0;
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
/*
  A função retorna uma substring que vai desde a posInicial até a posFinal
*/
char * substring(char * string, int posInicial, int posFinal)
{
    char * copia; 
    int contador = 0; 

    copia = (char *) malloc(1 * sizeof(char));

    
    /* printf("||Posicao inical: %d ||",posInicial);
    printf("||Posicao inical: %d ||",posInicial);
    printf("||String: %s||",string); */

    while(posInicial <= posFinal)
    {
      copia = (char *) realloc( copia, ((contador + 1 )* sizeof(char)) );
      copia[contador] = string[posInicial];
      contador++;
      posInicial++;
    }

    copia[contador] = '\0';
    return copia;
}

/* static size_t my_fwrite(void *buffer, size_t size, size_t nmemb,void *stream)
{
  struct File *out = (struct File *)stream;

  if(!out->stream) {
     open file for writing 
    out->stream = fopen(out->filename, "wb");
    if(!out->stream)
      return 0;
  }
  return fwrite(buffer, size, nmemb, out->stream);
} */