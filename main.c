/*
    Descricao: Programa destinado a monitorar ativos da B3
    Desenvolvedor: Gabriel Dias
    Data de modificação: 27/10/2024



    Instruções para compilação: 
        - abrir o prompt de comando na pasta do arquivo
        - executar a instrucao de compilacao:  gcc main.c console_v1.5.5.c conio_v3.2.4.c connection.c  -I include -L lib -o saida.exe -lcurl
*/

/* #define CURL_STATICLIB */
#include <curl/curl.h> /* CURLcode */
#include <stdio.h> 
#include <locale.h> /*Setlocale*/

#include "conio_v3.2.4.h"   /* Constantes: BLACK; _NOCURSOR; LIGHTGRAY; _NORMALCURSOR;  Fun��es: clrscr(); gotoxy(); 
_setcursortype(); textbackground(); textcolor(); */
#include "console_v1.5.5.h" /* Fun��es: setTituloConsole(); */
#include "connection.h" /*realizaGetEmUmaPagina,  */
#include "progMenus.h" /* Constantes: COLUNAINICIODAJANELA; LINHAINICIODAJANELA; TITULODOCONSOLE; Fun��es: Menu(); */

int main(int argc , char **argv)
{   
    struct MemoryStruct  resposta = {0};
    char ** tags;
    OPCOES opcoes;
    int contador=0;
    const char *url = "https://bvmf.bmfbovespa.com";

    setlocale(LC_ALL, "Portuguese");
    /* artificio para remover warning*/
	argc = argc;
	argv = argv;

    resposta.size = 0;

    resposta.memory = (char *) malloc(1);
    opcoes.opcoes = (OPCAOB3 *) malloc(sizeof(OPCAOB3) * QUANTIDADETAGS);
    opcoes.quantidade = 0;

    realizaGetEmUmaPagina("https://bvmf.bmfbovespa.com.br/cias-listadas/Titulos-Negociaveis/DetalheTitulosNegociaveis.aspx?or=res&cb=PETR&tip=I&idioma=pt-BR", &resposta);
    buscaTag(resposta.memory,&opcoes,2,"tr", "GridBovespaItemStyle");

    printf("Quantidade de opcoes: %d\n",opcoes.quantidade);

    for (contador = 0; contador < opcoes.quantidade; contador++)
    {
        printf("Codigo: %s\n",opcoes.opcoes[contador].codigo);
        printf("Vencimento: %s\n",opcoes.opcoes[contador].vencimento);
        printf("Preco strike: %.2f\n",opcoes.opcoes[contador].preco);
        printf("\n");
    }
    
    printf("Execucao finalizada\n");
	return 0;
}