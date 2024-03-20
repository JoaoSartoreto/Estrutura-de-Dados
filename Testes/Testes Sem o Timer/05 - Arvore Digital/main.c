#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_digital.h"
#include "arquivos.h"

int main(int argc, char *argv[])
{
	Node *rootAntigoPadrao, *rootNovoPadrao, *altera1, *altera2;
	int qtd;
	
	rootAntigoPadrao = make_trienode('\0',NULL);
	rootNovoPadrao = make_trienode('\0',NULL);

	carregamento_arquivo(argc, argv, &rootAntigoPadrao, &rootNovoPadrao);
	
	altera1 = alterarPlaca(&rootAntigoPadrao,  &rootNovoPadrao, "BAU3113");
	altera2 = alterarPlaca(&rootAntigoPadrao,  &rootNovoPadrao, "AAA1096");
	
	printf("-------------Antigo Padrao-------------------\n");
	imprimir_veiculos(rootAntigoPadrao);
	printf("-------------Novo Padrao-------------------\n");
	imprimir_veiculos(rootNovoPadrao);
	
	qtd = quantidade_veiculos(rootAntigoPadrao);
	printf("Quantidade veiculos antigos: %d\n",qtd);
	qtd = quantidade_veiculos(rootNovoPadrao);
	printf("Quantidade veiculos novos: %d\n",qtd);
	
	/*
	relatorio_intervaloAnos(rootAntigoPadrao, rootNovoPadrao, 2000, 2001);
	relatorio_porEstado(rootAntigoPadrao, rootNovoPadrao, "PR");
	*/

	/*
	if(altera1)
		printf("placa alterada: %s\n",altera1->veiculo->placa);
	if(altera2)
		printf("placa alterada: %s\n",altera2->veiculo->placa);
	*/
	gravacaoBinario(&rootAntigoPadrao, &rootNovoPadrao);

	free_trienode(rootAntigoPadrao);
	free_trienode(rootNovoPadrao);

	return 0;
}
