#ifndef Connection
#define RTD_WS   "\t\r\n " // whitespaces
#define ESPACE 32 /* codigo ascii do espaco*/
#define DQUOTES 34 /* codigo ascii do aspas duplas*/
#define BUFFER 20000 
#define QUANTIDADETAGS 1500 /* quantidade de tags que será alocado */
#define INICIOTRATAMENTO 500000 /* posição inicial do HTML que será dado inicio na busca das tags*/
#define FIMTRATAMENTO 790000
#define QUANTIDADETD 16
#define TAGTABELA "td"
#define TAMANHOCODIGOOPCAO 10
#define TAMANHOESTILO 5

struct MemoryStruct {
  char *memory;
  size_t size;
};

typedef struct _opcao
{
  char  *codigo;
  char  *vencimento;
  float preco;

}OPCAOB3;

typedef struct _opcoes
{
  OPCAOB3 * opcoes;
  int quantidade;
  char acao[10];
}OPCOES;

#include <curl\curl.h> /* CURLcode */

OPCAOB3 alocaOpcoes(char * tag);

/* Função realiza a busca de todos as tags encontradas em um arquivo de texto. O valor retornado sera um ponteiro que consiste 
em um vetor de strings onde cada elemento é uma das tags encontradas

 argumentos: 
  -XML_document: trata-se do documento HTML/XML que será realizado a busca
  -qArgumentos: quantidade de argumentos utilizado na filtragem. (1 ou 2)
  -tag: tag que será filtrado. 
  -4º argumento(opcional): caso qArgumentos seja igual a 2 esse argumento pode ser utilizado. Deverá ser 
  uma string que consiste na classe da tag.
  -5º argumento(opcional): caso qArgumentos seja igual a 3 esse argumento pode ser utilizado. Deverá ser o Id a ser buscado
*/
void buscaTag(char * XML_document, OPCOES * OpcaoParaAlocar ,int qArgumentos, char * tag,...);

/* Função realiza a contagem de ocorrencias da tag que será buscada no HTML/XML

  argumentos:
  -tag: tag que será buscada
  -tagBuscar: tag que será contada a quantidade de ocorrencias

*/
int contaTags(char * tag, char * tagBuscar);

/*  Funcao responsavel por criar a URL de busca, a funcao realiza a concatenação do codigo da ação com o link da página da B3, a URL da B3 conta um um argumento que 
consiste no codigo da acao, para preencher esse argumento é necessário passar o codigo da ação como parametro

  argumentos:
  -acao: codigo da ação que será monitorada

*/
char * criaURL(char * acao);

/* funcao que realiza uma requisição Get e retorna o HTML da página para que seja tratado por outras funções 

  Argumentos.
  -URL: URL da página.
  -resposta: uma estrutura do tipo CURLres onde o resultado será gravado
*/
CURLcode realizaGetEmUmaPagina(char * URL, struct MemoryStruct  * resposta);

/* Funçao recebe uma Tag e retorna a classe dessa tag

  argumentos:
  -qArgumentos: quantidade de argumentos passados, aceita 1 ou 2.
  -tag: linha contendo o a tag
  -3º argumento (opcional): caso o qArgumentos seja dois esse parametro pode ser utilizado. Consistem em um ponteiro 
  -de inteiro que será preenchido com o tamanho da classe.

*/
char * reotornaClasse(int qArguments,char * tag, ...);

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

/* Função responsavel por salvar as opções dísponiveis no banco de dados

  argumentos:
  -opcoes: estrutura que contem as opções disponiveis

*/
void salvandoNoBancoDeDados(OPCOES opcoes);

/*
  A função retorna uma substring que vai desde a posInicial até a posFinal

  argumentos: 
  -string: texto que sera retirado o subtexto.
  -posInicial: posição inicial do intervalo do texto
  -posFinal: posição final do intervalo do texto
*/
char * substring(char * string, long int posInicial,long int posFinal);

/* essa função é utilizada na requisição CURL, utilizada para evitar o comportamento padrão de imprimir na tela do CURL*/
static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);

#endif