
#include <curl\curl.h> /* CURL, CURLCode, curl_easy_setopt , curl_easy_init, curl_easy_strerror, curl_easy_cleanup*/
#include <stdlib.h> /* realloc, malloc, free*/
#include <stdio.h> /* null ,fopen , fprintf*/
#include <string.h> /*strlen, memcpy*/
#include "connection.h" /* FIle */ 

OPCAOB3 alocaOpcoes(char * tag)
{
  int posicoesTds[QUANTIDADETD] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  OPCAOB3 opcao;
  int contador;
  char * ultimatag, *ptr;
  size_t i;

  contador = 0;
  for(ptr = tag;(ultimatag = strstr(ptr,TAGTABELA)); ptr = ultimatag + 1)
  {
    posicoesTds[contador] =  ptr - tag;
    contador++;
  }

    opcao.codigo = substring(tag,posicoesTds[1]+2,posicoesTds[2]-4);
    opcao.preco = atof(substring(tag,posicoesTds[9]+16,posicoesTds[10]-4));

    opcao.vencimento = substring(tag,posicoesTds[7]+15,posicoesTds[8]-4);
  
  return opcao;

}

void buscaTag(char * pagina, OPCOES *opcaoAlocar, int qArgumentos, char * tag, ...)
{
  va_list list; 
  char *id, *auxiliar, *tagAux, *classeAuxiliar, **tags;
  int contador,InicioTag, finalTag, taglen, idLen, qTags, aux;

  // pega o segundo argumento passado para a função caso exista, sendo essa sempre o Id de uma Tag
  if(qArgumentos ==  2){
    va_start(list,tag);
    id = va_arg(list, char *);
    va_end(list);
  }
  else
  {
    classeAuxiliar = malloc(sizeof(char*)*1);
    *classeAuxiliar = '0';
    id = malloc(sizeof(char*)*1);
    *id = '0';
  }


  tags = malloc(sizeof(char*)*QUANTIDADETAGS);
  contador = INICIOTRATAMENTO;
  qTags = 0;

  while(pagina[contador] != EOF)
  {
    if(pagina[contador] == '<' && pagina[contador+1] == '/' && pagina[contador+2] == 'b' && pagina[contador+3] == 'o' && pagina[contador+4] == 'd' && pagina[contador+5] == 'y' && pagina[contador+6] == '>')
      break;

    // abertura de uma tag
    if(pagina[contador] == '<')
    {
      InicioTag = contador;
      while(pagina[contador] != '>') ++contador;

      tagAux = retornaNomeTag(2,substring(pagina,InicioTag+1,contador), &taglen);
      /* printf("Encontrei a tag %s || posi: %d\n",tagAux,contador); */
      if(strcmp(tagAux,tag) == 0)
      {
        // pego a classe da tag caso seja passado para realizar a busca
        if(qArgumentos == 2)
        {
          classeAuxiliar = reotornaClasse(2,substring(pagina,InicioTag+1,contador), &idLen);
        }

        if(strcmp(tagAux,tag) == 0 && (strcmp(id,classeAuxiliar) == 0 || qArgumentos == 1))
        {
          //buscando o fechamento de uma Tag
          while(1)
          {
            if(pagina[contador] == '/' && pagina[contador-1] == '<')
            {
              finalTag = contador;
              while(pagina[contador] != '>') contador++;
              auxiliar = substring(pagina,finalTag+1,contador);
              if(strcmp(retornaNomeTag(1,auxiliar),tag) == 0)
              {
                  auxiliar = substring(pagina,InicioTag,contador);
                  if(contaTags(auxiliar,"td") == 16)
                  {
                    opcaoAlocar->opcoes[opcaoAlocar->quantidade] = alocaOpcoes(auxiliar);
                    opcaoAlocar->quantidade++;
                  }
                  /* tags[qTags] = malloc(sizeof(char) * BUFFER);
                  tags[qTags] = auxiliar;
                  qTags++; */

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


}

int contaTags(char * tag, char * tagBuscar)
{
  int contador, chuteInicial, i;
  char * temp; 

  contador = 0;

  for(temp = tag;*temp;++temp)
  {
    chuteInicial = 1;
    for(i=0;tagBuscar[i];++i)
    {
      if(tagBuscar[i] != temp[i])
        chuteInicial = 0;
    }
    contador += chuteInicial;
  }

  return contador;
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

char * reotornaClasse(int qArguments,char * tag, ...)
{
  int position,strlen, *pstrlen; 
  char * retorno; 
  va_list list;

  retorno = (char *) malloc(BUFFER * sizeof(char));
  position = 0;
  strlen=0;
  
  while (tag[position] != '>' && tag[position] != '\0')
  {
    if(tag[position] == 'c' && tag[position+1] == 'l' && tag[position+2] == 'a' && tag[position+3] == 's' && tag[position+4] == 's' && tag[position+5] == '=') 
    {
      position+=7;
      while(tag[position] != '"' && tag[position] != '\0')
      {
        retorno[strlen] = tag[position];
        position++;
        strlen++;
      }
      break;
    }
    position++;
  }

  if(qArguments == 2 )
  {
    va_start(list,tag);
    pstrlen = va_arg(list, int * );
    va_end(list);

    *pstrlen = strlen; 
  }
  retorno[strlen] = '\0';
  return retorno;
}

char * retornaIdTag(int qArguments,char * tag, ...)
{
  int position,strlen, *pstrlen; 
  char * retorno; 
  va_list list;

  retorno = (char *) malloc(BUFFER * sizeof(char));
  position = 0;
  strlen=0;
  
  while (tag[position] != '>' && tag[position] != '\0')
  {
    if(tag[position] == 'i' && tag[position+1] == 'd' && tag[position+2] == '=')
    {
      position+=4;
      while(tag[position] != '"' && tag[position] != '\0')
      {
        retorno[strlen] = tag[position];
        position++;
        strlen++;
      }
      break;
    }
    position++;
  }

  if(qArguments == 2 )
  {
    va_start(list,tag);
    pstrlen = va_arg(list, int * );
    va_end(list);

    *pstrlen = strlen; 
  }
  retorno[strlen] = '\0';
  return retorno;
}

char * retornaNomeTag(int qArguments,char * tag, ...)
{
    int position,strlen, *pstrlen; 
    char * retorno; 
    va_list list;

    retorno = (char *) malloc(BUFFER * sizeof(char));
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

char * substring(char * string, long int posInicial,long  int posFinal)
{
    char * copia; 
    int contador = 0; 
   copia = (char *) malloc(BUFFER * sizeof(char));
    
    while(posInicial <= posFinal)
    {
      copia[contador] = string[posInicial];
      
      contador++;
      ;
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