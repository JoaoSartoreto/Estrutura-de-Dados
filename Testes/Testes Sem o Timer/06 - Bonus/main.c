#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_avl.h"
#include "arquivos.h"
#include "hash.h"

int main(int argc, char *argv[])
{
	Node *tabelaAntigoPadrao[TAM], *tabelaNovoPadrao[TAM], *altera1, *altera2;
	char placa[8], estado[3];
	int anoInicio, anoFim,i, qtd;
	
	
	inicializar_tabela(tabelaAntigoPadrao);
	inicializar_tabela(tabelaNovoPadrao);
	
	carregamento_arquivo(argc, argv, tabelaAntigoPadrao, tabelaNovoPadrao);
	
	
	printf("------------------Antigo padrao-------------\n");
	imprimir_tabela(tabelaAntigoPadrao);
	printf("------------------Novo padrao----------------\n");
	imprimir_tabela(tabelaNovoPadrao);
	
	/*
	relatorio_porEstado(listaAntigoPadrao, listaNovoPadrao, "SP");
	*/
	qtd = 0;
	for(i=0;i<TAM;i++)
		qtd = qtd + quantidade_de_veiculos(tabelaAntigoPadrao[i]);
	printf("Quantidade de veiculos antigos: %d\n",qtd);
	
	qtd = 0;
	for(i=0;i<TAM;i++)
		qtd = qtd + quantidade_de_veiculos(tabelaNovoPadrao[i]);
	printf("Quantidade de veiculos novos: %d\n",qtd);
	
	gravacaoBinario(tabelaAntigoPadrao, tabelaNovoPadrao);
	
	deleta_tabela(tabelaAntigoPadrao);
	deleta_tabela(tabelaNovoPadrao);

	return 0;
}
