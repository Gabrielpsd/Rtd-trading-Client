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

    /* artificio para remover warning*/
	argc = argc;
	argv = argv;

    resposta.size = 0;
    resposta.memory = (char *) malloc(1);

    realizaGetEmUmaPagina("https://bvmf.bmfbovespa.com.br/cias-listadas/Titulos-Negociaveis/DetalheTitulosNegociaveis.aspx?or=res&cb=ITUB&tip=I&idioma=pt-BR", &resposta);

    printf("%s\n",resposta.memory);
    printf("%d\n",resposta.size);

    buscaTag(resposta.memory,2,"table", "ctl00_contentPlaceHolderConteudo_ctl00_grdDados_LoadingTemplate");
    
	return 0;
}