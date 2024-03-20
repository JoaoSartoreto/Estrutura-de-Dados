#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_avl.h"
#include "arquivos.h"

int main(int argc, char *argv[])
{
	Node *rootAntigoPadrao = NULL, *rootNovoPadrao = NULL, *altera1, *altera2;
	int qtd;

	carregamento_arquivo(argc, argv, &rootAntigoPadrao, &rootNovoPadrao);
	/*
	altera1 = alterarPlaca(&rootAntigoPadrao,  &rootNovoPadrao, "AAA1090");
	altera2 = alterarPlaca(&rootAntigoPadrao,  &rootNovoPadrao, "AAA1096");
	*/
	imprimir_veiculos(rootAntigoPadrao);
	imprimir_veiculos(rootNovoPadrao);
	
	/*
	relatorio_intervaloAnos(rootAntigoPadrao, rootNovoPadrao, 1980, 2020);
	relatorio_porEstado(rootAntigoPadrao, rootNovoPadrao, "SP");*/
	
	
	qtd = quantidade_de_veiculos(rootAntigoPadrao);
	printf("Padrao antigo: %d\n",qtd);
	qtd = quantidade_de_veiculos(rootNovoPadrao);
	printf("Padrao novo: %d\n",qtd);
	/*
	if(altera1)
		printf("placa alterada: %s\n",altera1->veiculo.placa);
	if(altera2)
		printf("placa alterada: %s\n",altera2->veiculo.placa);
	*/
	gravacaoBinario(&rootAntigoPadrao, &rootNovoPadrao);

	delete_tree(rootAntigoPadrao);
	delete_tree(rootNovoPadrao);

	return 0;
}
