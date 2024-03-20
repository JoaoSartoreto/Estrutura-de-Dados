#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arquivos.h"



int main(int argc, char *argv[])
{
	No *listaAntigoPadrao = NULL, *listaNovoPadrao = NULL, *no;
	char placa[8], estado[3];
	int anoInicio, anoFim,i;
	
	
	carregamento_arquivo(argc, argv, &listaAntigoPadrao, &listaNovoPadrao);
	imprimir_veiculos(listaAntigoPadrao);
	imprimir_veiculos(listaNovoPadrao);
	
	
	
	
	gravacaoBinario(&listaAntigoPadrao, &listaNovoPadrao);
	
	libera_lista(&listaAntigoPadrao);
	libera_lista(&listaNovoPadrao);
	
	return 0;
}
