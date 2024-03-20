#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "arquivos.h"



int main(int argc, char *argv[])
{
	No listaAntigoPadrao[TAM], listaNovoPadrao[TAM], *no;
	char placa[8], estado[3];
	int anoInicio, anoFim,i;
	
	
	inicializar_tabela(listaAntigoPadrao);
	inicializar_tabela(listaNovoPadrao);
	
	carregamento_arquivo(argc, argv, listaAntigoPadrao, listaNovoPadrao);
	
	
	printf("------------------Antigo padrao-------------\n");
	imprimir_tabela(listaAntigoPadrao);
	printf("------------------Novo padrao----------------\n");
	imprimir_tabela(listaNovoPadrao);
	
	/*
	relatorio_porEstado(listaAntigoPadrao, listaNovoPadrao, "SP");
	*/
	
	gravacaoBinario(listaAntigoPadrao, listaNovoPadrao);
	
	deleta_tabela(listaAntigoPadrao);
	deleta_tabela(listaNovoPadrao);
	
	return 0;
}
