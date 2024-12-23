/*�����������������������������������������������������������������������������������������������������������������������ͻ*/
/*�  Instru��es de compila��o e execu��o do c�digo:                                                                       �*/
/*�	  1- Deve-se inicializar o CMD.                                                                                       �*/
/*�	  2- Deve-se, no CMD, selecionar a pasta onde os arquivos est�o armazenados.                                          �*/
/*�   3- Deve-se utilizar a seguinte linha no diret�rio correto no CMD para compilar:                                     �*/
/*�	                                                                                                                      �*/
/*�     gcc Menus.c -o Menus.exe console_v1.5.5.c conio_v3.2.4.c progMenus.c -Wall -pedantic -Wextra -Werror              �*/
/*�                                                                                                                       �*/
/*�	  4- Ap�s a compila��o deve-se executar o arquivo Menus.exe que foi gerado para a execu��o do programa com a          �*/
/*�	  seguinte linha no CMD:                                                                                              �*/
/*�                                                                                                                       �*/
/*�     Menus.exe                                                                                                         �*/
/*�����������������������������������������������������������������������������������������������������������������������ͼ*/
/*�������������������������������������������������������������������������������������������������������������ͻ*/
/*�  Programa: Constru��o de Menus.                                                                             �*/
/*�  Descri��o: Fun��o que cria um menu naveg�vel e modular por meio da entrada de dois arquivos com os         �*/
/*�	 parametros dos menus.                                                                                      �*/
/*�	 Programador: Jo�o Pedro Recalcatti.                                                                        �*/
/*�	 RGM: 49117.                                                                                                �*/
/*�	 Data da �ltima modifica��o: 28/06/2024                                                                     �*/
/*�������������������������������������������������������������������������������������������������������������ͼ*/


/*�������������������������������������������������������������������������������������������������������������ͻ*/
/*�                           IN�CIO DA IMPLEMENTA��O DA BIBLIOTECA Menu.h                                      �*/
/*�������������������������������������������������������������������������������������������������������������ͼ*/
	
#include <stdio.h>	        /* Constante: EOF; NULL; Fun��es: fclose(); fgetc(); fopen(); printf(); */
#include <stdlib.h>         /* Fun��es: atoi(); malloc(); realloc(); */
#include <string.h>         /* Fun��es: strlen(); */
#include "conio_v3.2.4.h"   /* Fun��es: _gettext(); gotoxy(); puttext(); textbackground(); textColor(); */
#include "console_v1.5.5.h" /* Constantes: ENTER; ESC; key_code; LEFT_ALT_PRESSED; PRESSIONADA; RIGHT_ALT_PRESSED; SETA_PARA_BAIXO; 
SETA_PARA_CIMA; SETA_PARA_DIREITA; SETA_PARA_ESQUERDA; Structs: EVENTO; TECLADO; Fun��es: Evento(); hit(); */
#include "progMenus.h"      /* Constantes: ASPASDUPLAS; BAIXO; CIMA; COLUNAINICIODAJANELA; DESTACAR; DISTANCIAMAIUSCULAMINUSCULANATABELA; ESPACOSOPCAO; 
FIMCARACTERMINUSCULO; FIMDOSPARAMETROS; INICIOCARACTERMINUSCULO; LINHAINICIODAJANELA; MENUPRINCIPAL; NAODESTACAR; NAOTEMSUBMENU; PRIMEIRAPOSICAO;
SETALIBERADA; SETAPRESSIONADA; TAMANHOMAXIMOOPCAO; TEMSUBMENU; Enum: PARAMETROSMENUS; CONFIGURACOES; Structs: PARAMETROS; MENUS; Fun��es: alocaConfiguracaoMenus(); 
alocaInfMenus(); calculaPosicaoDosMenus(); destacaLetras(); destacaStrings(); escreveJanelaPrincipal(); escreveLinhaDaTabela(); escreveMenu();
Menu(); quantidadeDeOpcoes(); retornaMaior(); selecionaMenu(); selecionaOpcao(); */


/*�������������������������������������������������������������������������������������������������������������ͻ*/
/*�                                     IN�CIO DAS IMPLEMENTA��ES DAS FUN��ES                                   �*/
/*�������������������������������������������������������������������������������������������������������������͹*/
/*�         REGRA DE ORDENA��O DAS FUN��ES: Elas est�o ordenadas alfabeticamente por nome da fun��o             �*/
/*�������������������������������������������������������������������������������������������������������������ͼ*/


/*
	FUN��O alocaConfiguracaoMenus: A fun��o alocaConfiguracaoMenus � projetada para ler n�meros inteiros de um 
	arquivo de texto e armazen�-los dinamicamente em uma estrutura PARAMETROS. Recebendo como par�metros o nome 
	do arquivo e um ponteiro para a estrutura, a fun��o abre o arquivo para leitura e inicializa uma string auxiliar 
	para armazenar temporariamente os n�meros como strings. Em seguida, ela entra em um loop que l� caracteres 
	do arquivo at� encontrar um delimitador (espa�o, nova linha ou EOF). Cada n�mero lido � convertido de string 
	para inteiro e armazenado no campo parametrosDoMenus da estrutura, com a mem�ria sendo realocada dinamicamente 
	para acomodar novos n�meros. Ap�s processar todo o arquivo, a fun��o fecha o arquivo para liberar os recursos. 
*/	
int alocaConfiguracaoMenus(char nomeArquivo[], PARAMETROS *ptParametros) 
{
	/* Declara��o de um ponteiro para o arquivo. */
    FILE *ptArq; 
	/* Declara��o de uma vari�vel auxiliar para armazenar o dado lido do arquivo.*/	
    char aux[TAMANHOMAXIMOOPCAO];
    /* Declara��o de uma vari�vel de caractere para armazenar o caractere lido do arquivo. */	
    char c; 
    int i, j; 

	/* Abre o arquivo para leitura e associa o ponteiro ao arquivo. */
    ptArq = fopen(nomeArquivo, "r"); 
	
	if(ptArq == NULL)
	{
		return 1;
	}
	
	/* Aloca mem�ria para um inteiro no campo parametrosDoMenus da estrutura ptParametros.*/
    ptParametros->parametrosDoMenus = (int*) malloc(sizeof(int)); 
	/* Inicializa o �ndice i e j com 0. */
    i = PRIMEIRAPOSICAO; 
    j = PRIMEIRAPOSICAO;

    do
    {
		/* L� um caractere do arquivo.*/
        c = fgetc(ptArq); 
		/* Loop enquanto o caractere n�o � um espa�o, nova linha, nulo ou EOF. */
        while((c != ' ' && c != '\n') && (c != '\0' && c != EOF)) 
        {
			/* Armazena o caractere lido no array auxiliar.*/
            aux[i] = c; 
			/* L� o pr�ximo caractere do arquivo. */
            c = fgetc(ptArq); 
			/* Incrementa o �ndice i. */
            i++; 
        }
		/* Se o �ndice i n�o for zero, significa que um n�mero foi lido. */
        if(i != 0) 
        {
			/* Adiciona '\0' ao final da string no array auxiliar.*/
            aux[i] = '\0';
			/* Reseta o �ndice i para 0. */
            i = PRIMEIRAPOSICAO; 
			/* Converte a string em um inteiro e armazena no array parametrosDoMenus. */
            ptParametros->parametrosDoMenus[j] = atoi(aux); 
            j++;
			/* Realoca mem�ria para o pr�ximo inteiro.*/
            ptParametros->parametrosDoMenus = (int*) realloc(ptParametros->parametrosDoMenus, (j + 1) * sizeof(int)); 
        }
    } 
	while(c != EOF); /* Continua o loop at� o final do arquivo. */

	/* Fecha o arquivo.*/
    fclose(ptArq); 
	
	return 0;
}


/*
	FUN��O alocaInfMenus: A fun��o alocaInfMenus faz a leitura e aloca��o din�mica de menus a partir de um arquivo
	de texto. Inicialmente, ela abre o arquivo especificado para leitura e aloca mem�ria para armazenar os menus, 
	utilizando ponteiros e estruturas de dados din�micas. Durante a execu��o, a fun��o percorre o arquivo caracter 
	por caracter, identificando e armazenando os diferentes par�metros de cada menu, como IDs, ordens, op��es e 
	letras. Ela manipula a leitura de caracteres, distinguindo entre espa�os, quebras de linha e aspas, para extrair
	corretamente as informa��es necess�rias. Ao ler cada conjunto de par�metros, os valores s�o convertidos e 
	atribu�dos aos campos correspondentes na estrutura MENUS. 
*/	
MENUS **alocaInfMenus(char nomeArquivo[], PARAMETROS *ptParametros)
{
	/* Declara��o de um ponteiro de ponteiro de MENUS.*/
    MENUS **ptMenus; 
	/* Declara��o de um ponteiro para o arquivo. */
    FILE *ptArq; 
	/* Declara��o de uma vari�vel do tipo PARAMETROSMENUS para iterar sobre a struct MENUS. */
    PARAMETROSMENUS menuPar; 
	/* Declara��o de uma vari�vel de caractere para armazenar o caractere lido do arquivo.*/
    char c; 
	/* Declara��o de uma string auxiliar para armazenar os dados lidos do arquivo. */
    char aux[TAMANHOMAXIMOOPCAO]; 
    int i, j; 

	/* Inicializa o �ndice i e j com 0.*/
    i = PRIMEIRAPOSICAO; 
    j = PRIMEIRAPOSICAO; 
	
	/* Abre o arquivo para leitura e associa o ponteiro ptArq ao arquivo.*/
    ptArq = fopen(nomeArquivo, "r"); 
	
	/* Caso n�o consiga abrir o arquivo */
	if(ptArq == NULL)
	{
		return NULL;
	}
	
	/* Aloca mem�ria inicial para um ponteiro de ponteiro de MENUS.*/
    ptMenus = (MENUS**) malloc(sizeof(MENUS*)); 

    do
    {
		/* Inicializa menuPar com ID_PAI. */
        menuPar = ID_PAI; 
		/* Aloca mem�ria para um novo elemento do tipo MENUS.*/
        ptMenus[j] = (MENUS*) malloc(sizeof(MENUS)); 
		/* Itera enquanto menuPar for menor que FIMDOSPARAMETROS. */
        while(menuPar < FIMDOSPARAMETROS) 
        {
			/* L� um caractere do arquivo. */
            c = fgetc(ptArq); 

			/* Ignora espa�os em branco e novas linhas. */
            while(c == ' ' || c == '\n') 
            {
                c = fgetc(ptArq);
            }
			/* Verifica se o final do arquivo foi alcan�ado.*/
            if(c == EOF) 
            {
                j--;
                break;
            }
			/* L� at� encontrar um espa�o, nova linha, aspas ou EOF. */
            while((c != ' ' && c != '\n') && (c != ASPASDUPLAS && c != EOF)) 
            {	
				/* Armazena o caractere lido na string auxiliar. */
                aux[i] = c; 
                c = fgetc(ptArq);
                i++;
            }
			
			/* Se n�o encontrar aspas, termina a string.*/
            if(c != ASPASDUPLAS) 
            {
                aux[i] = '\0';
                i = PRIMEIRAPOSICAO;
            }
            else 
            {
				/* Se encontrar aspas, l� at� encontrar outra aspa. */
                i = PRIMEIRAPOSICAO;
                c = fgetc(ptArq);

                while(c != ASPASDUPLAS)
                {
                    aux[i] = c;
                    c = fgetc(ptArq);
                    i++;
                }
				/* Fecha a string auxiliar com a string da op��o atual.*/
                aux[i] = '\0';
                i = PRIMEIRAPOSICAO;
            }
			/* Atribui os valores lidos aos campos correspondentes, fazendo as devidas convers�es */
            switch(menuPar) 
            {
                case ID_PAI:
                    ptMenus[j]->Id_pai = atoi(aux);
                    break;

                case ID:
                    ptMenus[j]->Id = atoi(aux);
                    break;

                case ORDEM:
                    ptMenus[j]->Ordem = atoi(aux);
                    break;

                case OPCAO:
                    strcpy(ptMenus[j]->Opcao, aux);
                    break;

                case LETRA:
                    ptMenus[j]->Letra = aux[0];
                    break;
            }
			/* Incrementa menuPar para o pr�ximo par�metro. */
            menuPar++; 
        }

        j++; 
		/* Realoca mem�ria para o pr�ximo elemento.*/
        ptMenus = (MENUS**) realloc(ptMenus, (j + 1) * sizeof(MENUS*)); 
    } 
	while(c != EOF); /* Continua enquanto n�o atingir o final do arquivo. */

	/* Ajusta a aloca��o de mem�ria ao n�mero real de menus. */
    ptMenus = (MENUS**) realloc(ptMenus, (j) * sizeof(MENUS*)); 

	/* Define a quantidade de menus na estrutura ptParametros.*/
    ptParametros->quantidadeDeMenus = j; 
	
	/* Fecha o arquivo.*/
    fclose(ptArq); 

	/* Retorna o ponteiro para o array de menus. */
    return ptMenus; 
}


/*
	FUN��O calculaPosicaoDosMenus: A fun��o calculaPosicaoDosMenus calcula as posi��es (X e Y) dos menus, utilizando informa��es 
	armazenadas em estruturas de dados din�micas. Inicialmente, ela verifica se o menu que est� sendo processado � o menu 
	principal, iniciando um loop que percorre todas as op��es desse menu. Para cada op��o v�lida, a fun��o calcula a 
	posi��o horizontal (posicaoX) com base na disposi��o atual e no comprimento das op��es anteriores, al�m de definir a 
	posi��o vertical fixa (posicaoY). Ap�s posicionar os menus principais, a fun��o tamb�m trata dos submenus, ajustando 
	suas posi��es com base nos menus pais. Utilizando recursividade, a fun��o assegura que todos os menus sejam posicionados 
	corretamente de acordo com a hierarquia estabelecida pelos IDs dos menus.  
*/	
void calculaPosicaoDosMenus(MENUS **ptMenus, PARAMETROS *ptParametros, int IdAux)
{
    int i, j;
	/* Vari�vel para controlar a disposi��o horizontal das op��es no menu. */
    int disposicao; 
	/* Contador para acompanhar a ordem das op��es dentro de um menu. */
    int auxDeOrdem; 
	 /* Contador para ajustar a posi��o X com base no comprimento das op��es. */
    int contadorCaracteres;
	/* Vari�vel para armazenar a quantidade de op��es de um determinado menu. */
    int quantOp; 
	int tamanhoMaior;
	
	/* Inicializa as vari�veis com 1. */
    disposicao = 1; 
    auxDeOrdem = 1; 
    contadorCaracteres = 1; 

    /* Verifica se o IdAux � o menu principal */
    if(IdAux == MENUPRINCIPAL)
    {
        /* Loop enquanto houver op��es para processar no menu principal. */
        while(auxDeOrdem <= quantidadeDeOpcoes(ptMenus, ptParametros, MENUPRINCIPAL))
        {
            /* Para cada menu no array de menus */
            for(i = 0; i < ptParametros->quantidadeDeMenus; i++)
            {
                /* Verifica se o menu atual pertence ao menu principal e possui a ordem correta*/
                if(ptMenus[i]->Id_pai == MENUPRINCIPAL && ptMenus[i]->Ordem == auxDeOrdem)
                {
                    /* Define a posi��o X e Y do menu baseado na disposi��o e contagem de caracteres. */
                    ptMenus[i]->posicaoX = disposicao + contadorCaracteres;
                    
					/* Define a posi��o Y fixa para o menu principal. */
                    ptMenus[i]->posicaoY = LINHAINICIODAJANELA ; 

                    /* Incrementa o contador de caracteres com o comprimento da op��o atual */
                    contadorCaracteres+= strlen(ptMenus[i]->Opcao);

                    /* guardamos a última posição X da opção */
                    ptMenus[i]->posicaoXFinal = ptMenus[i]->posicaoX + contadorCaracteres;

                    /* Incrementa a ordem para processar a pr�xima op��o.*/
                    auxDeOrdem++;

                    /* Avan�a a disposi��o horizontal para a pr�xima posi��o de op��o,*/
                    disposicao+= ptParametros->parametrosDoMenus[ESPACAMENTO];

                    /* Chama recursivamente a fun��o para calcular a posi��o dos menus filhos */
                    calculaPosicaoDosMenus(ptMenus, ptParametros, ptMenus[i]->Id);
                }
            }
        }
    }

    /* Verifica se o IdAux n�o � o menu principal */
    if(IdAux != MENUPRINCIPAL)
    {
        /* Obt�m a quantidade de op��es do menu associado ao IdAux */
        quantOp = quantidadeDeOpcoes(ptMenus, ptParametros, IdAux);

        /* Reinicia o contador de ordem das op��es */
        auxDeOrdem = 1;

        /* Verifica se h� op��es a serem processadas para o menu associado ao IdAux */
        if(quantOp > 0)
        {
            /* Para cada menu no array de menus */
            for(i = 0; i < ptParametros->quantidadeDeMenus; i++)
            {
                /* Verifica se o menu atual pertence ao IdAux e possui a ordem correta. */
                if(ptMenus[i]->Id_pai == IdAux && ptMenus[i]->Ordem == auxDeOrdem)
                {
                    /* Para cada menu no array de menus. */
                    for(j = 0; j < ptParametros->quantidadeDeMenus; j++)
                    {
                        /* Verifica se o menu atual tem como pai o Id do menu principal */
                        if(ptMenus[i]->Id_pai == ptMenus[j]->Id && ptMenus[j]->Id_pai == MENUPRINCIPAL)
                        {
							tamanhoMaior = retornaMaior(ptMenus, ptParametros, ptMenus[i]->Id_pai); 
							
							/* Verifica se o menu iria ultrapassar o tamanho da janela. */
							if((ptMenus[j]->posicaoX + ESPACOSOPCAO + tamanhoMaior) > ptParametros->parametrosDoMenus[LARGURA])
							{
								/* Caso fosse ultrapassar, � feita a mudan�a para ser impresso do lado esquerdo da op��o do menu principal. */
								ptMenus[i]->posicaoX = ptMenus[j]->posicaoX - 2 - tamanhoMaior;
								ptMenus[i]->posicaoXFinal = ptMenus[j]->posicaoX-2;
								ptMenus[i]->posicaoY = ptMenus[i]->Ordem + 2;
							}	
							else
							{
								/* Define a posi��o X e Y do menu baseado na posi��o do menu principal */
								ptMenus[i]->posicaoX = ptMenus[j]->posicaoX + 2;
								ptMenus[i]->posicaoXFinal = ptMenus[j]->posicaoX+tamanhoMaior;
								ptMenus[i]->posicaoY = ptMenus[i]->Ordem + 2;
							}

							/* Chama recursivamente a fun��o para calcular a posi��o dos menus filhos */
							calculaPosicaoDosMenus(ptMenus, ptParametros, ptMenus[i]->Id);
                        }
                        else
                        {
                            /* Verifica se o menu atual tem como pai o Id de outro menu */
                            if(ptMenus[i]->Id_pai == ptMenus[j]->Id && ptMenus[j]->Id_pai != MENUPRINCIPAL)
                            {
								tamanhoMaior = retornaMaior(ptMenus, ptParametros, ptMenus[i]->Id_pai); 
								
								/* Verifica se o menu iria ultrapassar o tamanho da janela. */
								if((ptMenus[j]->posicaoX + retornaMaior(ptMenus, ptParametros, ptMenus[j]->Id_pai) + 3 + tamanhoMaior) > ptParametros->parametrosDoMenus[LARGURA])
								{
									/* Caso fosse ultrapassar, � feita a mudan�a para o menu atual ser impresso do lado esquerdo do menu pai. */
									ptMenus[i]->posicaoX = ptMenus[j]->posicaoX - retornaMaior(ptMenus, ptParametros, ptMenus[i]->Id_pai) - 2;
									ptMenus[i]->posicaoXFinal = ptMenus[j]->posicaoX-2;
                                    ptMenus[i]->posicaoY = ptMenus[j]->posicaoY + ptMenus[i]->Ordem;	
								}
								else
								{
									/* Define a posi��o X e Y do menu baseado na posi��o do menu pai */
									ptMenus[i]->posicaoX = ptMenus[j]->posicaoX + retornaMaior(ptMenus, ptParametros, ptMenus[j]->Id_pai) + 2;
									
                                    ptMenus[i]->posicaoY = ptMenus[j]->posicaoY + ptMenus[i]->Ordem;	
								}
                                /* Chama recursivamente a fun��o para calcular a posi��o dos menus filhos */
                                calculaPosicaoDosMenus(ptMenus, ptParametros, ptMenus[i]->Id);
                            }
                        }
                    }
                    /* Incrementa a ordem para processar a pr�xima op��o */
                    auxDeOrdem++;
                    /* Reinicia o �ndice i para percorrer o array de menus desde o in�cio */
                    i = PRIMEIRAPOSICAO;
                }
            }
        }
    }
}


/*
   FUN��O destacaLetras: A fun��o destacaLetras real�a visualmente letras espec�ficas nos menus. Quando ativado (destacado � verdadeiro), 
   a fun��o localiza a letra destacada dentro da string de op��o do menu destacado e a imprime na tela com a cor especificada, serve 
   para destacar a letra que � selecionada por uma seta. Caso contr�rio, percorre todos os menus associados ao menuAtual, destacando 
   todas as letras do menu, para alt selecionado ou n�o, conforme a cor especificada. 
*/
void destacaLetras(MENUS **ptMenus, PARAMETROS *ptParametros, int menuAtual, int menuDestacado, int destacado, int corLetra)
{
    int i, j;
	/* �ndice da letra a ser destacada dentro da string de op��o. */
    int indLetra; 
	/* Tamanho da string da op��o do menu. */
    int tamanhoStr; 
    
    /* Verifica se o destaque est� ativado, se estiver, destaca somente a letra do menu desejado*/
    if(destacado)
    {
		/* Calcula o tamanho da string de op��o. */
        tamanhoStr = strlen(ptMenus[menuDestacado]->Opcao); 
        
        /* Percorre a string de op��o para encontrar a posi��o da letra a ser destacada */
        for(j = 0; j < tamanhoStr; j++)
        {
            if(ptMenus[menuDestacado]->Opcao[j] == ptMenus[menuDestacado]->Letra)
            {
				/* Armazena o �ndice da letra a ser destacada*/
                indLetra = j;
				/* Sai do loop ao encontrar a letra */
                j = tamanhoStr; 
            }
        }
        
		/* Define a cor do texto conforme o par�metro corLetra */
        textcolor(corLetra);
        /* Posiciona o cursor na posi��o da letra */
        gotoxy(ptMenus[menuDestacado]->posicaoX + indLetra, ptMenus[menuDestacado]->posicaoY); 
		/* Imprime a letra destacada na tela */
        printf("%c", ptMenus[menuDestacado]->Letra);
    }
    else
    {
        /* Caso o destaque n�o esteja ativado, percorre todos os menus associados ao menuAtual*/
        for(i = 0; i < ptParametros->quantidadeDeMenus; i++)
        {
            if(ptMenus[i]->Id_pai == menuAtual)
            {
				/* Calcula o tamanho da string de op��o */
                tamanhoStr = strlen(ptMenus[i]->Opcao); 
                
                /* Percorre a string de op��o para encontrar a posi��o da letra a ser destacada */
                for(j = 0; j < tamanhoStr; j++)
                {
                    if(ptMenus[i]->Opcao[j] == ptMenus[i]->Letra)
                    {
						/* Armazena o �ndice da letra a ser destacada */
                        indLetra = j; 
						/* Sai do loop ao encontrar a letra */
                        j = tamanhoStr; 
                    }
                }
                 /* Define a cor do texto conforme o par�metro corLetra */
                textcolor(corLetra);
                /* Posiciona o cursor na posi��o da letra */
                gotoxy(ptMenus[i]->posicaoX + indLetra, ptMenus[i]->posicaoY); 
				/* Imprime a letra destacada na tela */
                printf("%c", ptMenus[i]->Letra); 
            }	
        }
    }
}


/*
   FUN��O destacaStrings: A fun��o destacaStrings gerencia o destaque visual das strings de op��o nos menus. 
   Quando ativada, ela primeiro desativa qualquer destaque existente chamando recursivamente a si mesma com 
   NAODESTACAR. Em seguida, ela determina a cor do texto e do fundo com base no tipo de menu (MENUPRINCIPAL ou submenu), 
   posiciona o cursor na tela conforme as coordenadas do menu destacado e imprime sua stringde op��o. Al�m disso, se 
   o destaque estiver ativado, ela chama a fun��o destacaLetras para real�ar a letra espec�fica dentro da string de 
   op��o. Caso contr�rio, itera sobre todos os menus associados ao menuAtual, aplicando as mesmas opera��es de 
   posicionamento e impress�o, mas sem o realce visual das letras e mantendo a cor quando as op��es n�o est�o selecionadas. 
*/
void destacaStrings(MENUS **ptMenus, PARAMETROS *ptParametros, int menuAtual, int menuDestacado, int destacado)
{
    int i;

    /* Verifica se o destaque est� ativado, se estiver, destaca a op��o selecionada(menuDestacado) */
    if(destacado)
    {
		/* Chama recursivamente para desativar outros destaques */
        destacaStrings(ptMenus, ptParametros, menuAtual, menuDestacado, NAODESTACAR); 

        /* Verifica se o menu atual � o menu principal */
        if(menuAtual == MENUPRINCIPAL)
        {
			/* Define a cor do texto da op��o do menu principal quando est� selecionada */
            textcolor(ptParametros->parametrosDoMenus[COR3]); 
			/* Define a cor de fundo da op��o do menu principal quando est� selecionada*/
            textbackground(ptParametros->parametrosDoMenus[COR4]); 
			/* Posiciona o cursor na tela */
            gotoxy(ptMenus[menuDestacado]->posicaoX, ptMenus[menuDestacado]->posicaoY); 
			/* Imprime a string de op��o do menu destacado */
            printf("%s", ptMenus[menuDestacado]->Opcao); 
			/* Real�a a letra espec�fica do menu destacado, passando a cor da letra de atalho das op��es do menu principal quando est�o selecionada */
            destacaLetras(ptMenus, ptParametros, menuAtual, menuDestacado, DESTACAR, ptParametros->parametrosDoMenus[COR6]); 
        }
        else
        {
			/* Se o menu atual n�o � o menu principal */
			
			/* Define a cor do texto da op��o do submenu quando est� selecionada*/
            textcolor(ptParametros->parametrosDoMenus[COR9]); 
			/* Define a cor de fundo da op��o do submenu quando est� selecionada*/
            textbackground(ptParametros->parametrosDoMenus[COR10]); 
			/* Posiciona o cursor na tela */
            gotoxy(ptMenus[menuDestacado]->posicaoX, ptMenus[menuDestacado]->posicaoY); 
			/* Imprime a string de op��o do menu destacado */
            printf("%s", ptMenus[menuDestacado]->Opcao); 
			/* Real�a a letra espec�fica do menu destacado, passando a cor da letra de atalho das op��es de um submenu quando est�o selecionada */
            destacaLetras(ptMenus, ptParametros, menuAtual, menuDestacado, DESTACAR, ptParametros->parametrosDoMenus[COR12]); 
        }
        
    }
    else 
    {
		/* Caso o destaque n�o esteja ativado */
		
        /* Itera sobre todos os menus associados ao menuAtual */
        for(i = 0; i < ptParametros->quantidadeDeMenus; i++)
        {
            if(ptMenus[i]->Id_pai == menuAtual)
            {
                /* Verifica se o menu atual � o menu principal */
                if(menuAtual == MENUPRINCIPAL)
                {
					/* Define a cor do texto da op��o do menu principal quando n�o est� selecionada */
                    textcolor(ptParametros->parametrosDoMenus[COR2]); 
					/* Define a cor de fundo da op��o do menu principal quando n�o est� selecionada*/
                    textbackground(ptParametros->parametrosDoMenus[COR1]); 
					/* Posiciona o cursor na tela */
                    gotoxy(ptMenus[i]->posicaoX, ptMenus[i]->posicaoY);
					/* Imprime a string de op��o do menu */
                    printf("%s", ptMenus[i]->Opcao);
					/* Real�a a letra espec�fica do menu destacado, passando a cor da letra de atalho das op��es do menu principal quando n�o est�o selecionada */
                    destacaLetras(ptMenus, ptParametros, menuAtual, menuDestacado, NAODESTACAR, ptParametros->parametrosDoMenus[COR5]); 
                }
                else
                {
					/* Se o menu atual n�o � o menu principal */
					
					/* Define a cor do texto da op��o do submenu quando n�o est� selecionada*/
                    textcolor(ptParametros->parametrosDoMenus[COR8]); 
					/* Define a cor de fundo da op��o do submenu quando n�o est� selecionada*/
                    textbackground(ptParametros->parametrosDoMenus[COR7]);
					/* Posiciona o cursor na tela */
                    gotoxy(ptMenus[i]->posicaoX, ptMenus[i]->posicaoY); 
					/* Imprime a string de op��o do menu */
                    printf("%s", ptMenus[i]->Opcao); 
					/* Real�a a letra espec�fica do menu destacado, passando a cor da letra de atalho das op��es de um submenu quando n�o est�o selecionada */
                    destacaLetras(ptMenus, ptParametros, menuAtual, menuDestacado, NAODESTACAR, ptParametros->parametrosDoMenus[COR11]); 
                }
            
            }
        }
    }
}


/*
   FUN��O escreveJanelaPrincipal: A fun��o escreveJanelaPrincipal desenha uma janela na tela usando caracteres especiais, 
   formando uma estrutura de tabela delimitada por linhas verticais e horizontais. Primeiramente, ela define a cor de fundo da janela 
   conforme especificado nos par�metros recebidos. Em seguida, preenche o interior da janela com espa�os em branco, come�ando da terceira 
   linha at� a altura definida. Posteriormente, desenha as bordas verticais esquerda e direita da tabela, utilizando o caractere �. 
   Al�m disso, desenha as linhas superior e inferior da tabela com a fun��o escreveLinhaDaTabela, ajustando as cores de fundo e do texto 
   de acordo com os par�metros recebidos.
*/
void escreveJanelaPrincipal(PARAMETROS *ptParametros)
{
    int i, j;
	
	/* Define a cor de fundo da janela principal */
    textbackground(ptParametros->parametrosDoMenus[COR13]); 
	textcolor(ptParametros->parametrosDoMenus[COR14]); 
	/* Inicializa i com a linha de inicio, ou seja, o menu principal + a largura da borda*/
    i = LINHAINICIODAJANELA + 2;
	
	/* Preenche a �rea da janela com espa�os em branco */
    while(i < ptParametros->parametrosDoMenus[ALTURA])
    {
        for(j = 2; j < ptParametros->parametrosDoMenus[LARGURA]; j++)
        {
            gotoxy(j, i);
            printf(" "); 
        }
		
        i++;	
    }
    
    gotoxy(COLUNAINICIODAJANELA, LINHAINICIODAJANELA + 1);
	/* Escreve a linha superior da tabela com par�metros de largura, tipo de linha (CIMA), cor de fundo e cor do texto */
    escreveLinhaDaTabela(ptParametros->parametrosDoMenus[LARGURA], CIMA, ptParametros->parametrosDoMenus[COR16], ptParametros->parametrosDoMenus[COR15]);
	/* Define a cor de fundo para as bordas verticais da tabela */
    textbackground(ptParametros->parametrosDoMenus[COR16]); 
	/* Define a cor das bordas verticais da tabela */
    textcolor(ptParametros->parametrosDoMenus[COR15]);
    
    for(i = 3; i < ptParametros->parametrosDoMenus[ALTURA]; i++)
    {
		/* Desenha as bordas verticais da tabela, in�cio e fim da linha */
        gotoxy(COLUNAINICIODAJANELA, i);
        printf("�"); 

        gotoxy(ptParametros->parametrosDoMenus[LARGURA], i);
        printf("�"); 
    }
    
    gotoxy(COLUNAINICIODAJANELA, ptParametros->parametrosDoMenus[ALTURA]);
	/* Escreve a linha inferior da tabela com par�metros de largura, tipo de linha (BAIXO), cor de fundo e cor do texto */
    escreveLinhaDaTabela(ptParametros->parametrosDoMenus[LARGURA], BAIXO, ptParametros->parametrosDoMenus[COR16], ptParametros->parametrosDoMenus[COR15]);
}



/*
    FUN��O escreveLinhaDaTabela: A fun��o escreveLinhaDaTabela desenha uma linha de tabela visualmente estruturada usando 
	caracteres especiais, como linhas horizontais e cantos, para formar uma borda ao redor de uma �rea na tela. Ela recebe 
	par�metros que definem o tamanho da linha, o tipo de linha (superior ou inferior), a cor de fundo e a cor das bordas. Durante 
	sua execu��o, a fun��o percorre cada posi��o da linha e decide qual caractere especial deve ser impresso com base na posi��o 
	(in�cio, meio ou fim da linha) e no tipo de linha especificado. 
*/	
void escreveLinhaDaTabela(int tamanhoDaLinha, int tipoDaLinha, int corFundo, int corBorda)
{
    int i;
	
	/* Define a cor de fundo para a linha da tabela */
    textbackground(corFundo); 
	/* Define a cor do texto para as bordas da tabela */
    textcolor(corBorda); 

    /* Loop para percorrer cada caractere da linha */
    for(i = 0; i < tamanhoDaLinha; i++)
    {
        /* Verifica se � o primeiro caractere */
        if(i == 0)
        {
            if(tipoDaLinha == CIMA)
            {
                /* Se sim, escreve o canto esquerdo da borda superior da tabela */
                printf("�"); 
            }
            else
            {
                /* Se n�o, escreve o canto esquerdo da borda inferior da tabela */
                printf("�"); 
            }
        }
        else 
        {
            /* Verifica se � o �ltimo caractere */
            if(i == tamanhoDaLinha - 1)
            {
                if(tipoDaLinha == CIMA)
                {
                    /* Se sim, escreve o canto direito da borda superior da tabela */
                    printf("�"); 
                }
                else
                {
                    /* Se n�o, escreve o canto direito da borda inferior da tabela */
                    printf("�");
                }
            }
            else
            {
                /* Se n�o for nem o primeiro nem o �ltimo, escreve um tra�o horizontal */
                printf("�"); 
            }
        }      
    }
}


/* 
    FUN��O escreveMenu: A fun��o escreveMenu desenha um menu na tela do programa, utilizando caracteres especiais
	para criar bordas e preencher o fundo com cores espec�ficas definidas pelos par�metros ptParametros. 
	Primeiramente, ela verifica se o menu atual � o menu principal. Se for, remove qualquer destaque 
	das op��es desse menu. Caso contr�rio, define o fundo do menu com a cor especificada em COR7. Em seguida, 
	percorre todos os menus para desenhar a borda superior e inferior, al�m das bordas verticais para cada op��o 
	do menu atual. Ao final, garante que n�o haja nenhum destaque nas op��es do menu, chamando novamente a fun��o 
	destacaStrings.
*/	
void escreveMenu(MENUS **ptMenus, PARAMETROS *ptParametros, int menuAtual)
{
    int i, j, k;
    /* Posi��o atual da op��o */
    int auxDeOrdem;

    auxDeOrdem = 1;

    if(menuAtual == MENUPRINCIPAL)
    {
		/* Define o fundo da barra do menu principal */
        textbackground(ptParametros->parametrosDoMenus[COR1]);
		
		for(i = 1; i <= ptParametros->parametrosDoMenus[LARGURA]; i++)
        {
			gotoxy(i, LINHAINICIODAJANELA);
            printf(" ");
		}
        /* Remove o destaque de todas as op��es do menu principal */
        destacaStrings(ptMenus, ptParametros, menuAtual, 0, NAODESTACAR);
    }
    else
    {       
        /* Define o fundo do menu */
        textbackground(ptParametros->parametrosDoMenus[COR7]);
        
        /* Loop para preencher o fundo do menu com a cor correta e escrever a linha de cima da tabela*/
        for(i = 0; i < ptParametros->quantidadeDeMenus; i++)
        {
            if(ptMenus[i]->Id_pai == menuAtual && ptMenus[i]->Ordem == 1)
            {   
                j = ptMenus[i]->posicaoY;
                
                /* Preenche o fundo do menu com a cor certa, percorrendo as linhas necess�rias */
                while(j < ptMenus[i]->posicaoY + quantidadeDeOpcoes(ptMenus, ptParametros, menuAtual))
                {
                    for(k = ptMenus[i]->posicaoX - 1; k < retornaMaior(ptMenus, ptParametros, menuAtual) + ptMenus[i]->posicaoX + 1; k++)
                    {
                        gotoxy(k, j);
                        printf(" ");
                    }
                    j++;    
                }
                
                /* Desenha a linha superior da tabela acima das op��es do menu */
                gotoxy(ptMenus[i]->posicaoX - 2, ptMenus[i]->posicaoY - 1);
                escreveLinhaDaTabela(retornaMaior(ptMenus, ptParametros, menuAtual) + ESPACOSOPCAO, CIMA, ptParametros->parametrosDoMenus[COR7], ptParametros->parametrosDoMenus[COR8]);
            }
        }
		
        /* Define a cor de fundo para as bordas verticais da tabela */
		textbackground(ptParametros->parametrosDoMenus[COR7]); 
		/* Define a cor das bordas verticais da tabela */
		textcolor(ptParametros->parametrosDoMenus[COR8]);
		
        /* Loop para desenhar as bordas verticais das op��es do menu */
        for(i = 0; i < ptParametros->quantidadeDeMenus; i++)
        {
            if(ptMenus[i]->Id_pai == menuAtual && ptMenus[i]->Ordem == auxDeOrdem)
            {
                /* Desenha a borda esquerda da op��o */
                gotoxy(ptMenus[i]->posicaoX - 2, ptMenus[i]->posicaoY);
                printf("�");
                
                /* Desenha a borda direita da op��o */
                gotoxy(ptMenus[i]->posicaoX + retornaMaior(ptMenus, ptParametros, menuAtual) + 1, ptMenus[i]->posicaoY);
                printf("�");
                
                auxDeOrdem++;
				/* Reinicia o loop para verificar todas as op��es novamente */
                i = 0; 
            }
        }
        
        /* Loop para desenhar a borda inferior do menu */
        for(i = 0; i < ptParametros->quantidadeDeMenus; i++)
        {
            if(ptMenus[i]->Id_pai == menuAtual && ptMenus[i]->Ordem == quantidadeDeOpcoes(ptMenus,ptParametros, menuAtual))
            {   
                /* Desenha a linha inferior da tabela abaixo das op��es do menu */
                gotoxy(ptMenus[i]->posicaoX - 2, ptMenus[i]->posicaoY + 1);
                escreveLinhaDaTabela(retornaMaior(ptMenus, ptParametros, menuAtual) + ESPACOSOPCAO, BAIXO, ptParametros->parametrosDoMenus[COR7], ptParametros->parametrosDoMenus[COR8]);
            }
        }
        
        /* Remove o destaque de todas as op��es do menu atual */
        destacaStrings(ptMenus, ptParametros, menuAtual, 0, NAODESTACAR);
    }
}


/*
	FUN��O Menu: A fun��o Menu coordena a exibi��o e intera��o com os menus do programa, utilizando r�tulos e configura��es 
	fornecidos como argumentos. Ela inicia declarando vari�veis locais, incluindo ponteiros para estruturas e vari�veis de 
	controle. Em seguida, carrega os menus com base nos r�tulos e configura��es fornecidos, aloca espa�o para armazenar 
	informa��es adicionais, calcula as posi��es dos menus na tela principal e desenha essa tela. Ap�s permitir a intera��o 
	do usu�rio com os menus e obter o menu selecionado, libera toda a mem�ria alocada dinamicamente. Por fim, retorna 
	o ID do menu selecionado, concluindo sua fun��o de gerenciamento de menus no programa.
*/
int Menu(char rotulos[], char configuracoes[])
{
	/* Declara��o de vari�veis locais */
	int IDselecionado;
	int i;
	int aux;
	
	/* Ponteiro para o vetor ponteiros de menus */
	MENUS **ptMenus;  
	/* Estrutura que armazena os par�metros do menu.*/
	PARAMETROS parametros;  
	/* Ponteiro para a estrutura de par�metros*/
	PARAMETROS *ptParametros;  

	/* Inicializa��o do ponteiro ptParametros com o endere�o da estrutura parametros */
	ptParametros = &parametros;

	/* Aloca mem�ria e carrega as informa��es dos menus baseado nos r�tulos passados */
	ptMenus = alocaInfMenus(rotulos, ptParametros);

	if(ptMenus == NULL)
	{
		return 0;
	}
	
	/* Carrega as configura��es dos menus baseado no arquivo de configura��es */
	aux = alocaConfiguracaoMenus(configuracoes, ptParametros);
	
	if(aux)
	{
		return 0;
	}

	/* Aloca espa�o inicial para a �ltima tela armazenada e inicializa o �ndice auxiliar */
	ptParametros->ultimaTelaArmazenada = (char **)malloc(sizeof(char*));
	ptParametros->indAuxTelas = PRIMEIRAPOSICAO;

	/* Calcula as posi��es dos menus na tela principal */
	calculaPosicaoDosMenus(ptMenus, ptParametros, MENUPRINCIPAL);

	/* Desenha a janela principal na tela com base nos par�metros configurados */
	escreveJanelaPrincipal(ptParametros);

	/* Permite a intera��o do usu�rio com os menus e retorna o ID do menu selecionado */
	IDselecionado = selecionaMenu(ptMenus, ptParametros, MENUPRINCIPAL);

	/* Libera a mem�ria alocada para cada menu individualmente */
	for(i = 0; i < ptParametros->quantidadeDeMenus; i++)
	{
		free(ptMenus[i]);
	}

	/* Libera a mem�ria alocada para as telas armazenadas */
	for(i = 0; i < ptParametros->indAuxTelas; i++)
	{
		free(ptParametros->ultimaTelaArmazenada[i]);
	}

	/* Libera a mem�ria alocada para o array de par�metros dos menus e para o array de menus */
	free(ptParametros->parametrosDoMenus);
	free(ptParametros->ultimaTelaArmazenada);
	free(ptMenus);

	/* Retorna o ID do menu selecionado */
	return IDselecionado;
}


/*
	FUN��O quantidadeDeOpcoes: A fun��o quantidadeDeOpcoes calcula quantas op��es existem em um menu espec�fico. 
	Ela recebe como par�metros um ponteiro para a matriz de menus (ptMenus), um ponteiro para a estrutura de 
	par�metros do menu (ptParametros), e o ID do menu atual (menuAtual). A fun��o percorre todos os menus e 
	conta quantos t�m o menuAtual como pai, incrementando o contador para cada correspond�ncia encontrada. 
	No final, retorna o valor do contador, que representa o n�mero de op��es dispon�veis no menu especificado.
*/
int quantidadeDeOpcoes(MENUS **ptMenus, PARAMETROS *ptParametros, int menuAtual)
{
    int i;  
	/* Contador para o n�mero de op��es. */
    int contador;   

    /* Inicializa o contador com zero. */
    contador = 0;

    /* Percorre todos os menus para contar quantas op��es pertencem ao menu atual. */
    for(i = 0; i < ptParametros->quantidadeDeMenus; i++)
    {
        /* Verifica se o menu atual � o pai do menu na posi��o i. */
        if(ptMenus[i]->Id_pai == menuAtual)
        {
			/* Incrementa o contador se a condi��o for verdadeira*/
            contador++;  
        }
    }

    /* Retorna o n�mero total de op��es encontradas */
    return contador;
}


/*
	FUN��O retornaMaior: A fun��o retornaMaior encontra o comprimento da maior string de op��o em um menu 
	espec�fico. A fun��o percorre todas as op��es do menu e calcula o comprimento de cada string de op��o. 
	Se uma string de op��o � maior que a maior encontrada at� aquele ponto, a fun��o atualiza o valor 
	de maior com o novo comprimento. No final, retorna o comprimento da maior string de op��o encontrada 
	no menu especificado.
*/
int retornaMaior(MENUS **ptMenus, PARAMETROS *ptParametros, int menuAtual)
{
    int i; 
	/* Armazena o comprimento da maior string de op��o. */
    int maior;   
	/* Armazena o comprimento da string de op��o atual	*/
    int tamanhoStr;  
    
    /* Inicializa a vari�vel maior com zero */
    maior = 0;
    
    /* Para cada op��o do menu */
    for(i = 0; i < ptParametros->quantidadeDeMenus; i++)
    {
        /* Verifica se o menu atual � o pai do menu na posi��o i */
        if(ptMenus[i]->Id_pai == menuAtual)
        {
            /* Calcula o comprimento da string de op��o atual */
            tamanhoStr = strlen(ptMenus[i]->Opcao);
            
            /* Verifica se o comprimento da string atual � maior que o armazenado em 'maior' */
            if(tamanhoStr > maior)
            {
                /* Atualiza 'maior' com o comprimento da string atual */
                maior = strlen(ptMenus[i]->Opcao);
            }
        }
    }
    /* Retorna o comprimento da maior string de op��o */
    return maior;
}


/*
    FUN��O selecionaMenu: A fun��o selecionaMenu gerencia a intera��o do usu�rio com um menu, permitindo navega��o 
	e sele��o de op��es. Inicialmente, ela define a posi��o inicial da op��o do menu e exibe o menu na tela. 
	Em seguida, entra em um loop onde monitora eventos de teclado. Se a tecla ALT � pressionada, a fun��o alterna 
	para um modo onde as letras das op��es s�o destacadas e permite a sele��o de op��es por teclas de atalho. Se 
	uma seta direcional � pressionada, a fun��o ajusta a posi��o da op��o selecionada no menu. Quando a tecla ENTER 
	� pressionada, a fun��o retorna a op��o selecionada. A tecla ESC permite voltar ao menu anterior, restaurando 
	a tela anterior. Ao final, a fun��o retorna o ID da op��o selecionada pelo usu�rio.
*/
int selecionaMenu(MENUS **ptMenus, PARAMETROS *ptParametros, int menuAtual)
{
	/* Declara��o de vari�vel para capturar eventos. */
    EVENTO e;   
	/* Vari�vel de controle para sair do loop de leitura.*/	
    int sair;           
    int i; 
	/* Vari�vel auxiliar para capturar o resultado da sele��o de op��o.*/	
    int opSelecionada;            
    
	/* Inicializa sair com 0 para continuar o loop.*/
    sair = CONTINUAR;     	
	/* Inicializa opSelecionada com 0. */
    opSelecionada = OPCAONAOSELECIONADA;           
    /* Define a localiza��o inicial da op��o do menu como 1.*/
    ptParametros->locOpcaoMenu = INICIOMENU;    
	/* Define as setas como pressionadas inicialmente.*/
    ptParametros->setasSelecionadas = SETAPRESSIONADA;
	/* Escreve o menu atual na tela.*/
    escreveMenu(ptMenus, ptParametros, menuAtual); 
    
    /* Destaca a primeira op��o do menu como padr�o.*/
    for(i = 0; i < ptParametros->quantidadeDeMenus; i++)
    {
        if(ptMenus[i]->Id_pai == menuAtual && ptMenus[i]->Ordem == ptParametros->locOpcaoMenu)
        {
            destacaStrings(ptMenus, ptParametros, menuAtual, i, DESTACAR);
        }        
    }
    
    do
    {
        /* Verifica se houve algum evento */
        if(hit( ALL ))
        {
            /* L� o evento */
            e = Evento();
            /* Verifica se o evento � um evento do teclado */
            if(e.tipo_evento & KEY_EVENT)
            {
                /* Verifica se a tecla ALT est� pressionada */
                if((e.teclado.status_teclas_controle & LEFT_ALT_PRESSED) | (e.teclado.status_teclas_controle & RIGHT_ALT_PRESSED) && e.teclado.status_tecla == PRESSIONADA)
                {
                    /* Define setasSelecionadas para seta liberada, impedindo a sele��o com Enter */
                    ptParametros->setasSelecionadas = SETALIBERADA;

                    /* Redefine a cor de todas as op��es para preto, removendo resqu�cios de sele��o */
                    destacaStrings(ptMenus, ptParametros, menuAtual, 0, NAODESTACAR);

                    /* Destaca as letras do menu */
                    if(menuAtual == MENUPRINCIPAL)
                    {
                        destacaLetras(ptMenus, ptParametros, menuAtual, 0, NAODESTACAR, ptParametros->parametrosDoMenus[COR6]);
                    }
                    else
                    {
                        destacaLetras(ptMenus, ptParametros, menuAtual, 0, NAODESTACAR, ptParametros->parametrosDoMenus[COR12]);
                    }

                    /* Seleciona a op��o com base na tecla pressionada */
                    opSelecionada = selecionaOpcao(ptMenus, ptParametros, menuAtual, e.teclado.key_code);
					
					/* Se uma op��o foi selecionada. */
					if(opSelecionada)  
					{
						sair = SAIR;
						/* Retorna o ID da op��o selecionada. */
						return opSelecionada; 
					}
					
                }
                else  
                {
					/* Se a tecla ALT n�o est� pressionada.*/
					
                    /* Redefine a cor das op��es se as setas est�o liberadas */
                    if(ptParametros->setasSelecionadas == SETALIBERADA)
                    {
                        destacaStrings(ptMenus, ptParametros, menuAtual, 0, NAODESTACAR);
                    }
                }

                /* Verifica se uma das setas de dire��o foi pressionada */
                if((e.teclado.key_code == SETA_PARA_ESQUERDA || e.teclado.key_code == SETA_PARA_DIREITA || e.teclado.key_code == SETA_PARA_CIMA || e.teclado.key_code == SETA_PARA_BAIXO ) && e.teclado.status_tecla == PRESSIONADA)
                {
                    /* Define setasSelecionadas para seta pressionada */
                    ptParametros->setasSelecionadas = SETAPRESSIONADA;

                    /* Move a posi��o do menu de acordo com a seta pressionada at� os limites de cada menu */
                    if(e.teclado.key_code == SETA_PARA_ESQUERDA && menuAtual == MENUPRINCIPAL)
                    {
                        if(ptParametros->locOpcaoMenu > 1)
                        {
                            ptParametros->locOpcaoMenu--;
                        }
                    }
                    else
                    {
                        if(e.teclado.key_code == SETA_PARA_DIREITA && menuAtual == MENUPRINCIPAL)
                        {
                            if(ptParametros->locOpcaoMenu < quantidadeDeOpcoes(ptMenus, ptParametros, menuAtual) )
                            {
                                ptParametros->locOpcaoMenu++;
                            }
                        }
                        else
                        {
                            if(e.teclado.key_code == SETA_PARA_CIMA && menuAtual != MENUPRINCIPAL)
                            {
                                if(ptParametros->locOpcaoMenu > 1)
                                {
                                    ptParametros->locOpcaoMenu--;
                                }
                            }
                            else
                            {
								if(e.teclado.key_code == SETA_PARA_BAIXO && menuAtual != MENUPRINCIPAL)
								{
									if(ptParametros->locOpcaoMenu < quantidadeDeOpcoes(ptMenus, ptParametros, menuAtual) )
									{
										ptParametros->locOpcaoMenu++;
									}
								}
                            }
                        }
                    }

					/* Destaca a nova posi��o selecionada pelo menu */
					for(i = 0; i < ptParametros->quantidadeDeMenus; i++)
					{
						if(ptMenus[i]->Id_pai == menuAtual && ptMenus[i]->Ordem == ptParametros->locOpcaoMenu)
						{
							destacaStrings(ptMenus, ptParametros, menuAtual, i, DESTACAR);
						}		
					}

                }

                /* Verifica se a tecla ENTER foi pressionada */
                if((ptParametros->setasSelecionadas && e.teclado.key_code == ENTER ) && e.teclado.status_tecla == PRESSIONADA)
                {	
					sair = SAIR;
					/* Se foi pressionada, � chamada a fun��o para dar entrada em um novo menu ou retornar o id do menu escolhido.*/
					return selecionaOpcao(ptMenus, ptParametros, menuAtual, e.teclado.key_code);
                }

                /* Verifica se a tecla ESC foi pressionada */
                if((e.teclado.key_code == ESC) && e.teclado.status_tecla == PRESSIONADA)
                {
					
					for(i = 0; i < ptParametros->quantidadeDeMenus; i++)
					{
						if(ptMenus[i]->Id == menuAtual)
						{
							sair = SAIR;
							/* Decrementa o �ndice auxiliar de telas. */
							ptParametros->indAuxTelas--;  
							/* Realoca a mem�ria para diminuir a aloca��o de uma tela(tela extra alocada na fun��o selecionaOpcao()). */
							ptParametros->ultimaTelaArmazenada = (char**) realloc(ptParametros->ultimaTelaArmazenada, (ptParametros->indAuxTelas + 1) * sizeof(char*));  
							/* Restaura a tela anterior.*/
							puttext(COLUNAINICIODAJANELA, LINHAINICIODAJANELA, ptParametros->parametrosDoMenus[LARGURA], ptParametros->parametrosDoMenus[ALTURA], ptParametros->ultimaTelaArmazenada[ptParametros->indAuxTelas]); 
							/* Retorna ao menu pai.*/
							return selecionaMenu(ptMenus, ptParametros, ptMenus[i]->Id_pai);  
						}		
					}

                }
            }
        }
    }	
    while(sair == CONTINUAR);  /* Continua no loop enquanto sair for CONTINUAR(0).*/

	/* Retorna 0 se sair do loop. */
	return 0;  
}


/*
    FUN��O selecionaOpcao: A fun��o selecionaOpcao � respons�vel por gerenciar a sele��o de uma op��o dentro de um menu. 
	Ela percorre todas as op��es do menu atual e verifica se a tecla pressionada corresponde � letra da op��o ou se a op��o 
	est� selecionada via setas de navega��o. Se a op��o selecionada possui submenus, a fun��o armazena a tela atual, navega 
	para o submenu e chama a fun��o selecionaMenu para gerenciar o novo menu. Se a op��o n�o possui submenus, a fun��o retorna 
	o ID da op��o selecionada. Caso nenhuma op��o seja selecionada, a fun��o retorna 0. 
*/
int selecionaOpcao(MENUS **ptMenus, PARAMETROS *ptParametros, int menuAtual, int key_code)
{
    int i, j;      
	/* Vari�vel auxiliar para verificar a exist�ncia de submenus. */  
    int temSubMenus;
	/* Vari�vel para armazenar a letra da op��o do menu em mai�sculo.*/
    char letraAux; 
	
	/* Inicializa a vari�vel auxiliar com NAOTEMSUBMENU.*/
    temSubMenus = NAOTEMSUBMENU;

    /* Loop para percorrer todas as op��es do menu */
    for(i = 0; i < ptParametros->quantidadeDeMenus; i++)
    {
        /* Verifica se a letra da op��o � min�scula e a converte para mai�scula */
        if(ptMenus[i]->Letra >= INICIOCARACTERMINUSCULO && ptMenus[i]->Letra <= FIMCARACTERMINUSCULO)
        {
            letraAux = ptMenus[i]->Letra - DISTANCIAMAIUSCULAMINUSCULANATABELA;
        }
        else
        {
            letraAux = ptMenus[i]->Letra;
        }

        /* Verifica se a tecla pressionada corresponde � letra da op��o ou se a op��o est� selecionada via setas */
        if((ptMenus[i]->Id_pai == menuAtual && letraAux == key_code) || ((ptMenus[i]->Id_pai == menuAtual && ptMenus[i]->Ordem == ptParametros->locOpcaoMenu) && ptParametros->setasSelecionadas))
        {
            /* Verifica se a op��o selecionada possui submenus */
            for(j = 0; j < ptParametros->quantidadeDeMenus; j++)
            {
                if(ptMenus[j]->Id_pai == ptMenus[i]->Id)
                {
					/* Define temSubMenus como TEMSUBMENU se a op��o possui submenus.*/
                    temSubMenus = TEMSUBMENU; 
                }
            }

            /* Se a op��o possui submenus */
            if(temSubMenus)
            {
                /* Aloca o espa�o e armazena a tela atual antes de mudar para o submenu */
                ptParametros->ultimaTelaArmazenada[ptParametros->indAuxTelas] = (char *) malloc(ptParametros->parametrosDoMenus[LARGURA] * ptParametros->parametrosDoMenus[ALTURA] * 2);
                _gettext(COLUNAINICIODAJANELA, LINHAINICIODAJANELA, ptParametros->parametrosDoMenus[LARGURA], ptParametros->parametrosDoMenus[ALTURA], ptParametros->ultimaTelaArmazenada[ptParametros->indAuxTelas]);
				/* Incrementa o �ndice de telas armazenadas.*/
                ptParametros->indAuxTelas++;  
				/* Aloca o espa�o para um pr�ximo ponteiro que apontara para uma tela. */
                ptParametros->ultimaTelaArmazenada = (char**) realloc(ptParametros->ultimaTelaArmazenada, (ptParametros->indAuxTelas + 1) * sizeof(char*));

                /* Chama a fun��o selecionaMenu para navegar para o submenu */
                return selecionaMenu(ptMenus, ptParametros, ptMenus[i]->Id);
            }
            else
            {
                /* Retorna o ID da op��o selecionada se n�o possuir submenus */
                return ptMenus[i]->Id;
            }
        }
    }
	
	/* Retorna 0 se nenhuma op��o for selecionada.*/
    return OPCAONAOSELECIONADA;  
}

/*�������������������������������������������������������������������������������������������������������������ͻ*/
/*�                                    FIM DAS IMPLEMENTA��ES DAS FUN��ES                                       �*/
/*�������������������������������������������������������������������������������������������������������������ͼ*/
