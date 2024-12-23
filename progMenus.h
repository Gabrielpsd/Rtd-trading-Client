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

#ifndef PROGMENUS_H
#define PROGMENUS_H

	/*�������������������������������������������������������������������������������������������������������������ͻ*/
	/*�                                IN�CIO DAS DECLARA��ES DE DEFINES E CONSTANTES                               �*/
	/*�������������������������������������������������������������������������������������������������������������ͼ*/
	
	/* Defini��o do codigo ASCII para aspas duplas. */
	#define ASPASDUPLAS 34
	
	/* Tipo da linha que deve ser escrita pela fun��o escreveLinhaDaTabela, CIMA para a linha superior, BAIXO para linha inferior. */
	#define BAIXO 1
	#define CIMA 0
	
	/* Posi��o da culuna e linha inicial da janela*/
	#define COLUNAINICIODAJANELA 1
	#define LINHAINICIODAJANELA 1
	
	/* Defini��o da dist�ncia entre um caracter mai�sculo e min�sculo na tabela ASCII.*/
	#define DISTANCIAMAIUSCULAMINUSCULANATABELA 32
	
	/* Serve como paramentro para as fun��es destacaStrings() e destacaLetras() saberem se devem destacar todas as op��es de um menu ou somente uma op��o especifica.*/
	#define DESTACAR 1
	#define NAODESTACAR 0
	
	/* Defini��o do numero de espa�os em branco que uma op��o deve ter.*/
	#define ESPACOSOPCAO 4
	
	/* Defini��o do numero na tabela ASCII da ultima letra min�scula*/
	#define FIMCARACTERMINUSCULO 122
	
	/* Defini��o de uma constante auxiliar para saber onde finalizar a leitura de uma op��o de menu do arquivo.*/
	#define FIMDOSPARAMETROS 5
	
	/* Defini��o do numero na tabela ASCII da primeira letra min�scula*/
	#define INICIOCARACTERMINUSCULO 97 
	
	/* Defini��o de constante auxiliar para a primeira posi��o que um menu deve se encontrar quando for iniciado.*/
	#define INICIOMENU 1
	
	/* Defini��o do numero que identifica o MENU PRINCIPAL.*/
	#define MENUPRINCIPAL 0
	
	/* Defini��o de constante auxiliar para verificar se uma op��o foi selecionada pelo alt dentro da fun��o selecionaMenu. */
	#define OPCAONAOSELECIONADA 0
	
	/* Defini��o da primeira posi��o para indices em C.*/
	#define PRIMEIRAPOSICAO 0
	
	/* Defini��o de constantes auxiliares do while que l� entradas do usu�rio.*/
	#define SAIR 1
	#define CONTINUAR 0
	
	/* Status da forma de leitura do menu, se esta com as setas ativas ou no modo em que a sela��o com alt pode ser utilizado */
	#define SETALIBERADA 0
	#define SETAPRESSIONADA 1
	
	#define TAMANHOMAXIMOOPCAO 40
	
	/* Constantes auxiliares para definir qual op��o ativar na fun��o selecionaOpcao()*/
	#define TEMSUBMENU 1
	#define NAOTEMSUBMENU 0
	
	/* Titulo do programa */
	#define TITULODOCONSOLE "MENU"
	
	/*�������������������������������������������������������������������������������������������������������������ͻ*/
	/*�                                 FIM DAS DECLARA��ES DE DEFINES E CONSTANTES                                 �*/
	/*�������������������������������������������������������������������������������������������������������������ͼ*/
	
	
	
	/*�������������������������������������������������������������������������������������������������������������ͻ*/
	/*�                              IN�CIO DAS DECLARA��ES DE ESTRUTURAS E ENUMERA��ES                             �*/
	/*�������������������������������������������������������������������������������������������������������������ͼ*/
	
	/* 
		enum PARAMETROSMENUS: Este enum � utilizado para representar diferentes par�metros de um menu, atribuindo
		nomes a valores inteiros para facilitar a leitura e a manuten��o do c�digo. � utilizado na fun��o alocaInfMenus 
		para controlar onde cada dado ser� amazenado. 
	*/
	typedef enum
	{
		ID_PAI,
		ID,
		ORDEM,
		OPCAO,
		LETRA
		
	}PARAMETROSMENUS;
	
	
	/* 
		enum CONFIGURACOES: Este enum � utilizado para representar todos os paramentros de configura��es do menu que foram
		recebidos pelo arquivo.
	*/
	typedef enum
	{
		/* Representa a cor de fundo da barra do menu principal. */
		COR1,
		/* Representa a cor das op��es do menu principal, quando n�o est�o selecionadas. */
		COR2,
		/* Representa a cor das op��es do menu principal, quando est�o selecionadas. */
		COR3,
		/* Representa a cor de fundo das op��es do menu principal, quando est�o selecionadas. */
		COR4,
		/* Representa a cor da letra de atalho das op��es do menu principal, quando elas n�o est�o selecionadas. */
		COR5,
		/* Representa a cor da letra de atalho das op��es do menu principal, quando elas est�o selecionadas. */
		COR6,
		/* Representa a cor de fundo das janelas dos submenus. */
		COR7,
		/* Representa a cor das op��es dos submenus, quando n�o est�o selecionadas. */
		COR8,
		/* Representa a cor das op��es dos submenus, quando est�o selecionadas. */
		COR9,
		/* Representa a cor de fundo das op��es dos submenus, quando est�o selecionadas. */
		COR10,
		/* Representa a cor da letra de atalho das op��es dos submenus, quando elas n�o est�o selecionadas. */
		COR11,
		/* Representa a cor da letra de atalho das op��es do menu principal, quando elas est�o selecionadas. */
		COR12,
		/* Representa a cor de fundo da janela principal. */
		COR13,
		/* Representa a cor do texto impresso na janela principal. */
		COR14,
		/* Representa a cor da borda da janela principal. */
		COR15,
		/* Representa a cor de fundo da borda da janela principal. */
		COR16,
		/* Representa a largura (incluindo as bordas) da janela principal. */
		LARGURA,
		/* Representa a altura (incluindo a borda inferior e o menu principal) da janela principal. */
		ALTURA,
		/* Representa a quantidade de espa�amento a ser dado entre as op��es do menu principal. */
		ESPACAMENTO
		
	}CONFIGURACOES;
	
	
	/* 
		STRUCT PARAMETROS: Esta struct serve para armazenar todas as informa��es das configura��es pertinetes a escrita dos menus, 
		como cores, largura, altura, telas, etc.
	*/
	typedef struct parametrosPrimordiais
	{
		/* Quantidade total de op��es (linhas) de menus que foram lidas do arquivo e armazenadas.*/
		int quantidadeDeMenus;
		/* Todas as configura��es que foram passadas pelo arquivo config.txt e est�o representadas pelo enum CONFIGURACOES*/
		int *parametrosDoMenus;
		/* Armazena o status da forma de leitura do menu, se esta com as setas ativas ou no modo em que a sela��o com alt pode ser utilizado */
		int setasSelecionadas;
		/* Armazena a localiza��o atual da op��o selecionada no menu.*/
		int locOpcaoMenu;
		/* Armazena todas as telas que foram passadas ap�s a sele��o de submenus*/
		char **ultimaTelaArmazenada;
		/* Armazena �ndice auxiliar das telas armazenadas.*/
		int indAuxTelas;
		
	}PARAMETROS;
	
	
	/* 
		STRUCT MENUS: Esta struct serve para armazenar todas as informa��es de cada linha lida do arquivo, ou seja, ela 
		armazena os paramentros de cada op��o naveg�vel e selecionavel dos menus.
	*/
	typedef struct informacoesMenus
	{
		/* Um n�mero inteiro n�o negativo, que identifica se a op��o indicada � um submenu ou n�o (0 para menu principal). */
		int Id_pai;
		/* Um n�mero natural, que identifica unicamente a op��o dentro de um determinado menu. */
		int Id;
		/* Um n�mero natural, que indica a ordem em que a op��o deve aparecer no menu ao qual est� vinculada.*/
		int Ordem;
		/* O t�tulo da op��o propriamente dita. Ser� uma string com no m�ximo 30 letras.*/
		char Opcao[TAMANHOMAXIMOOPCAO];
		/* Uma letra presente no t�tulo da pr�pria op��o.*/
		char Letra;
		/* Coordenada x de onde essa op��o de menu deve ser escrita na tela. */
		int posicaoX;
		/*Define a ultima posição X da opção */
		int posicaoXFinal;
		/* Coordenada y de onde essa op��o de menu deve ser escrita na tela. */
		int posicaoY;
		
	}MENUS;
	
	/*�������������������������������������������������������������������������������������������������������������ͻ*/
	/*�                               FIM DAS DECLARA��ES DE ESTRUTURAS E ENUMERA��ES                               �*/
	/*�������������������������������������������������������������������������������������������������������������ͼ*/
	
	
	/*�������������������������������������������������������������������������������������������������������������ͻ*/
	/*�                              IN�CIO DAS DECLARA��ES DOS PROT�TIPOS DAS FUN��ES                              �*/
	/*�������������������������������������������������������������������������������������������������������������͹*/
	/*�         REGRA DE ORDENA��O DOS PROT�TIPOS: Eles est�o ordenados alfabeticamente por nome da fun��o          �*/
	/*�������������������������������������������������������������������������������������������������������������ͼ*/
	
	/*
		FUN��O alocaConfiguracaoMenus: Serve para ler n�meros inteiros de um arquivo texto e os armazena dinamicamente
		em uma estrutura de dados.
		PAR�METROS DE ENTRADA:
			char nomeArquivo[]: String passada para a fun��o Menu, armazena o nome do arquivo que deve ser aberto.
			PARAMETROS *ptParametros: Armazena as vari�veis essenciais para o funcionamento do menu e sua configura��o.
		RETORNO:
			Retorna 1 para indicar erro na abertura do arquivo ou 0 para abertura bem sucedida.
	*/
	int alocaConfiguracaoMenus(char nomeArquivo[], PARAMETROS *ptParametros);
	
	
	/*
		FUN��O alocaInfMenus: Serve para fazer a leitura e aloca��o din�mica das infoma��es dos menus a partir de um arquivo de texto.		
		PAR�METROS DE ENTRADA:
			char nomeArquivo[]: String passada para a fun��o Menu, armazena o nome do arquivo que deve ser aberto.
			PARAMETROS *ptParametros: Armazena as vari�veis essenciais para o funcionamento do menu e sua configura��o.
		RETORNO:
			Retorna o ponteiro para o array de MENUS, contendo todos os menus lidos do arquivo, ou NULL caso 
			tenha ocorrido um erro na leitura do arquivo.
	*/
	MENUS **alocaInfMenus(char nomeArquivo[], PARAMETROS *ptParametros);
	
	
	/*
		FUN��O calculaPosicaoDosMenus: Serve para calcular as posi��es (X e Y) dos menus, utilizando informa��es armazenadas 
		em estruturas de dados din�micas.	
		PAR�METROS DE ENTRADA:
			MENUS **ptMenus: Armazena todas as informa��es de cada menu, incluido a posi��o que devem ficar na tela.
			PARAMETROS *ptParametros: Armazena as vari�veis essenciais para o funcionamento do menu e sua configura��o.
			int IdAux: � um parametro passado para as chamadas recursivas saberem qual o menu atual (Id_pai) que deve ser trabalhado.
		RETORNO:
			SEM RETORNO.
	*/
	void calculaPosicaoDosMenus(MENUS **ptMenus, PARAMETROS *ptParametros, int IdAux);
	
	
	/*
		FUN��O destacaLetras: Serve para real�ar visualmente as letras de atalho espeficadas em cada menu. 	
		PAR�METROS DE ENTRADA:
			MENUS **ptMenus: Armazena todas as informa��es de cada menu, incluido a letra de atalho.
			PARAMETROS *ptParametros: Armazena as vari�veis essenciais para o funcionamento do menu e sua configura��o.
			int menuAtual: Numero do menu atual, ou seja o numero do menu pai que � comum a todas as op��es de um menu.
			int menuDestacado: Id de uma unica op��o do menu que deve ser destacada individulamente.
			int destacado: Identificador que diz se a fun��o deve destacar todas as op��es do menu atual(NAODESTACAR) ou somente 
			uma op��o de um Id especifico(DESTACAR).
			int corLetra: Cor que deve destacar a/ as letras.
		RETORNO:
			SEM RETORNO.
	*/
	void destacaLetras(MENUS **ptMenus, PARAMETROS *ptParametros, int menuAtual, int menuDestacado, int destacado, int corLetra);
	
	
	/*
		FUN��O destacaStrings: Serve para gerenciar o destaque visual das strings de op��o nos menus, quando est�o ou n�o selecionadas.		
		PAR�METROS DE ENTRADA:
			MENUS **ptMenus: Armazena todas as informa��es de cada menu, incluido a string de op��o.
			PARAMETROS *ptParametros: Armazena as vari�veis essenciais para o funcionamento do menu e sua configura��o.
			int menuAtual: Numero do menu atual, ou seja o numero do menu pai que � comum a todas as op��es de um menu.
			int menuDestacado: Id de uma unica op��o do menu que deve ser destacada individulamente.
			int destacado: Identificador que diz se a fun��o deve detacar todas as op��es do menu atual(NAODESTACAR) ou somente 
			uma op��o de um Id especifico(DESTACAR).
		RETORNO:
			SEM RETORNO.
	*/
	void destacaStrings(MENUS **ptMenus, PARAMETROS *ptParametros, int menuAtual, int menuDestacado, int destacado);
	
	
	/*
		FUN��O escreveJanelaPrincipal: Serve para desenhar uma janela na tela usando caracteres especiais, formando uma estrutura de 
		tabela delimitada por linhas verticais e horizontais.		
		PAR�METROS DE ENTRADA:
			PARAMETROS *ptParametros: Armazena as vari�veis essenciais para o funcionamento do menu e sua configura��o.
		RETORNO:
			SEM RETORNO.
	*/
	void escreveJanelaPrincipal(PARAMETROS *ptParametros);
	
	
	/*
		FUN��O escreveLinhaDaTabela: Serve para desenhar uma linha de tabela visualmente estruturada usando caracteres especiais. 		
		PAR�METROS DE ENTRADA:
			int tamanhoDaLinha: Tamanho em caracteres que a largura da tabela deve ter (linha).
			int tipoDaLinha: (CIMA) para a linha superior da tabela ou (BAIXO) para a linha inferior da tabela.
			int corFundo: Cor do fundo da linha que deve ser escrita.
			int corBorda: Cor da linha que deve ser escrita.
		RETORNO:
			SEM RETORNO.
	*/
	void escreveLinhaDaTabela(int tamanhoDaLinha, int tipoDaLinha, int corFundo, int corBorda);
	
	
	/*
		FUN��O escreveMenu: Serve para desenhar um menu completo na tela do programa, incluindo strings, bordas e fundo.
		PAR�METROS DE ENTRADA:
			MENUS **ptMenus: Armazena todas as informa��es de cada menu.
			PARAMETROS *ptParametros: Armazena as vari�veis essenciais para o funcionamento do menu e sua configura��o.
			int menuAtual: Numero do menu atual, ou seja o numero do menu pai que � comum a todas as op��es de um menu.
		RETORNO:
			SEM RETORNO.
	*/
	void escreveMenu(MENUS **ptMenus, PARAMETROS *ptParametros, int menuAtual);
	
	
	/*
		FUN��O Menu: Serve para coordenar a exibi��o e intera��o com os menus do programa, utilizando r�tulos e configura��es 
		fornecidos como argumentos.		
		PAR�METROS DE ENTRADA:
			char rotulos[]: Nome do arquivo que possui todas as informa��es referentes aos menus.
			char configuracoes[]: Nome do arquivo que possui todas as informa��es referente as configura��es dos menus.
		RETORNO:
			Retorna o ID do menu selecionado pela fun��o.
	*/
	int Menu(char rotulos[], char configuracoes[]);
	
	
	/*
		FUN��O quantidadeDeOpcoes: Serve para calcular quantas op��es existem em um menu espec�fico.  		
		PAR�METROS DE ENTRADA:
			MENUS **ptMenus: Armazena todas as informa��es de cada menu.
			PARAMETROS *ptParametros: Armazena as vari�veis essenciais para o funcionamento do menu e sua configura��o.
			int menuAtual: Numero do menu atual, ou seja o numero do menu pai que � comum a todas as op��es de um menu.
		RETORNO:
			Retorna o valor do contador, que representa o n�mero de op��es dispon�veis no menu especificado.	
	*/
	int quantidadeDeOpcoes(MENUS **ptMenus, PARAMETROS *ptParametros, int menuAtual);
	
	
	/*
		FUN��O retornaMaior: Serve para encontrar o comprimento da maior string de op��o em um menu espec�fico.		
		PAR�METROS DE ENTRADA:
			MENUS **ptMenus: Armazena todas as informa��es de cada menu.
			PARAMETROS *ptParametros: Armazena as vari�veis essenciais para o funcionamento do menu e sua configura��o.
			int menuAtual: Numero do menu atual, ou seja o numero do menu pai que � comum a todas as op��es de um menu.
		RETORNO:
			Retorna o comprimento da maior string de op��o encontrada no menu especificado.
	*/
	int retornaMaior(MENUS **ptMenus, PARAMETROS *ptParametros, int menuAtual);
	
	
	/*
		FUN��O selecionaMenu: Serve para gerenciar a intera��o do usu�rio com um menu, permitindo navega��o e sele��o de op��es.		
		PAR�METROS DE ENTRADA:
			MENUS **ptMenus: Armazena todas as informa��es de cada menu.
			PARAMETROS *ptParametros: Armazena as vari�veis essenciais para o funcionamento do menu e sua configura��o.
			int menuAtual: Numero do menu atual, ou seja o numero do menu pai que � comum a todas as op��es de um menu.
		RETORNO:
			Retorna o ID da op��o selecionada pelo usu�rio.
	*/
	int selecionaMenu(MENUS **ptMenus, PARAMETROS *ptParametros, int menuAtual);
	
	
	/*
		FUN��O selecionaOpcao: Serve para gerenciar a sele��o de uma op��o dentro de um menu. 	
		PAR�METROS DE ENTRADA:
			MENUS **ptMenus: Armazena todas as informa��es de cada menu.
			PARAMETROS *ptParametros: Armazena as vari�veis essenciais para o funcionamento do menu e sua configura��o.
			int menuAtual: Numero do menu atual, ou seja o numero do menu pai que � comum a todas as op��es de um menu.
			int keyCode: C�digo da tecla pressionada para selecionar o pr�ximo menu com base no alt + letras de atalho.
		RETORNO:
			Retorna o ID da op��o selecionada pelo usu�rio.
	*/
	int selecionaOpcao(MENUS **ptMenus, PARAMETROS *ptParametros, int menuAtual, int keyCode);
	
	
	/*�������������������������������������������������������������������������������������������������������������ͻ*/
	/*�                               FIM DAS DECLARA��ES DOS PROT�TIPOS DAS FUN��ES                                �*/
	/*�������������������������������������������������������������������������������������������������������������ͼ*/
	
#endif