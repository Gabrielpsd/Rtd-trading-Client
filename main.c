/*
    Descricao: Programa destinado a monitorar ativos da B3
    Desenvolvedor: Gabriel Dias
    Data de modificação: 27/10/2024



    Instruções para compilação: 
        - abrir o prompt de comando na pasta do arquivo
        - executar a instrucao de compilacao:  gcc main.c console_v1.5.5.c conio_v3.2.4.c rtdConnection.c  sqlite3.c -I include -L lib -o saida.exe -lole32 -loleaut32 -lcurl
        - executar a instrucao de compilacao:  cl main.c console_v1.5.5.c conio_v3.2.4.c rtdConnection.c  sqlite3.c /Fe:saida.exe ole32.lib oleaut32.lib
            cl main.c rtdConnection.c /Fe:saida.exe ole32.lib oleaut32.lib /machine:x64
*/

/* #define CURL_STATICLIB */
/* #include <curl/curl.h>  CURLcode */
#include <stdio.h> 
#include <locale.h> /*Setlocale*/
#include <windows.h>

#include "progMenus.h" /* Constantes: COLUNAINICIODAJANELA; LINHAINICIODAJANELA; TITULODOCONSOLE; Fun��es: Menu(); */
#include "sqlite3.h" /* sqlite3_open(); sqlite3_close(); sqlite3_exec(); sqlite3_stmt; sqlite3_prepare_v2(); sqlite3_step(); sqlite3_column_text(); sqlite3_finalize(); */
#include "rtdConnection.h"


int main(int argc , char **argv)
{   
    /* struct MemoryStruct  resposta = {0};
    char ** tags;
    OPCOES opcoes;
    int contador=0; */
    setlocale(LC_ALL, "Portuguese"); 

    /* artificio para remover warning */
	argc = argc;
	argv = argv;

   /*  Menu("menu.txt","config.txt"); */
    /* resposta.size = 0;

    resposta.memory = (char *) malloc(1);
    opcoes.opcoes = (OPCAOB3 *) malloc(sizeof(OPCAOB3) * QUANTIDADETAGS);
    opcoes.quantidade = 0;

    printf("Digite o codigo da acao que deseja monitorar: ");
    scanf("%s",opcoes.acao);
    realizaGetEmUmaPagina(criaURL(opcoes.acao), &resposta);
    buscaTag(resposta.memory,&opcoes,2,"tr", "GridBovespaItemStyle");

    printf("Quantidade de opcoes: %d\n",opcoes.quantidade);

    for (contador = 0; contador < opcoes.quantidade; contador++)
    {
    printf("Codigo: %s\n",opcoes.opcoes[contador].codigo);
    printf("Vencimento: %s\n",opcoes.opcoes[contador].vencimento);
    printf("Preco strike: %.2f\n",opcoes.opcoes[contador].preco);
    printf("\n");
    }
    
    salvandoNoBancoDeDados(opcoes); */
    if (sizeof(void*) == 4) {
        printf("Running as 32-bit\n");
    } else if (sizeof(void*) == 8) {
        printf("Running as 64-bit\n");
    } else {
        printf("Unknown architecture\n");
    }
    
    requisitaDadosEmTempoReal();

    printf("Execucao finalizada\n");
	return 0;
}