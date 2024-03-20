#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvorebb.h"
#include "arquivos.h"

int main(int argc, char *argv[])
{
	Node *rootAntigoPadrao = NULL, *rootNovoPadrao = NULL, *busca;
	int qtd;

	carregamento_arquivo(argc, argv, &rootAntigoPadrao, &rootNovoPadrao);
	
	/*
	imprimir_veiculos(rootAntigoPadrao);
	imprimir_veiculos(rootNovoPadrao);
	*/
	
	relatorio_intervaloAnos(rootAntigoPadrao, rootNovoPadrao, 1980, 2020);
	/*relatorio_porEstado(rootAntigoPadrao, rootNovoPadrao, "SP");*/
	
	
	qtd = quantidade_de_veiculos(rootAntigoPadrao);
	printf("Padrao antigo: %d\n",qtd);
	qtd = quantidade_de_veiculos(rootNovoPadrao);
	printf("Padrao novo: %d\n",qtd);
	
	gravacaoBinario(&rootAntigoPadrao, &rootNovoPadrao);

	delete_tree(rootAntigoPadrao);
	delete_tree(rootNovoPadrao);

	return 0;
}
