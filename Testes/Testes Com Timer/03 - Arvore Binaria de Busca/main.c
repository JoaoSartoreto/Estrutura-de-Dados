#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvorebb.h"
#include "arquivos.h"

enum { NS_PER_SECOND = 1000000000 };

void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td)
{
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec  = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0)
    {
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0)
    {
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
    }
}

int main(int argc, char *argv[])
{
	Node *rootAntigoPadrao = NULL, *rootNovoPadrao = NULL, *busca;
	int qtd;

    struct timespec tstart, tend, delta;

    FILE *salva;
    salva = fopen("testes.csv", "a");
    if(salva==NULL) return -1;
    
    clock_gettime(CLOCK_REALTIME, &tstart);
	carregamento_arquivo(argc, argv, &rootAntigoPadrao, &rootNovoPadrao);
    clock_gettime(CLOCK_REALTIME, &tend);
    sub_timespec(tstart, tend, &delta);
    fprintf(salva,"%d.%.9ld;", (int)delta.tv_sec, delta.tv_nsec);

	/*
	imprimir_veiculos(rootAntigoPadrao);
	imprimir_veiculos(rootNovoPadrao);
	*/
    clock_gettime(CLOCK_REALTIME, &tstart);
	relatorio_intervaloAnos(rootAntigoPadrao, rootNovoPadrao, 1980, 2022);
    clock_gettime(CLOCK_REALTIME, &tend);
    sub_timespec(tstart, tend, &delta);
    fprintf(salva,"%d.%.9ld;", (int)delta.tv_sec, delta.tv_nsec);

    clock_gettime(CLOCK_REALTIME, &tstart);
	relatorio_porEstado(rootAntigoPadrao, rootNovoPadrao, "SP");
    clock_gettime(CLOCK_REALTIME, &tend);
    sub_timespec(tstart, tend, &delta);
    fprintf(salva,"%d.%.9ld;", (int)delta.tv_sec, delta.tv_nsec);

    clock_gettime(CLOCK_REALTIME, &tstart);
    busca = procurar_veiculo(rootAntigoPadrao, rootNovoPadrao, "MUC9583");
    clock_gettime(CLOCK_REALTIME, &tend);
    sub_timespec(tstart, tend, &delta);
    fprintf(salva,"%d.%.9ld;", (int)delta.tv_sec, delta.tv_nsec);

    clock_gettime(CLOCK_REALTIME, &tstart);
    busca = alterarPlaca(&rootAntigoPadrao, &rootNovoPadrao, "MUC9583");
    clock_gettime(CLOCK_REALTIME, &tend);
    sub_timespec(tstart, tend, &delta);
    fprintf(salva,"%d.%.9ld\n", (int)delta.tv_sec, delta.tv_nsec);

    /*COMO ELA TA SALVANDO NO ARQUIVO CSV*/
    /*carregamento;relatorioAno;relatorioEstado;buscaPlaca;alteraPlaca*/

	qtd = quantidade_de_veiculos(rootAntigoPadrao);
	printf("Padrao antigo: %d\n",qtd);
	qtd = quantidade_de_veiculos(rootNovoPadrao);
	printf("Padrao novo: %d\n",qtd);

	gravacaoBinario(&rootAntigoPadrao, &rootNovoPadrao);

	delete_tree(rootAntigoPadrao);
	delete_tree(rootNovoPadrao);
    
    fclose(salva);

	return 0;
}
