#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"
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
	No listaAntigoPadrao[TAM], listaNovoPadrao[TAM], *no;
	char placa[8], estado[3];
	int anoInicio, anoFim,i;

    struct timespec tstart, tend, delta;

    FILE *salva;
    salva = fopen("testes.csv", "a");
    if(salva==NULL) return -1;    

    clock_gettime(CLOCK_REALTIME, &tstart);
	inicializar_tabela(listaAntigoPadrao);
	inicializar_tabela(listaNovoPadrao);
	carregamento_arquivo(argc, argv, listaAntigoPadrao, listaNovoPadrao);
    clock_gettime(CLOCK_REALTIME, &tend);
    sub_timespec(tstart, tend, &delta);
    fprintf(salva,"%d.%.9ld;", (int)delta.tv_sec, delta.tv_nsec);
    
    /*1
	printf("------------------Antigo padrao-------------\n");
	imprimir_tabela(listaAntigoPadrao);
	printf("------------------Novo padrao----------------\n");
	imprimir_tabela(listaNovoPadrao);
	*/

 ;  clock_gettime(CLOCK_REALTIME, &tstart);
	relatorio_intervaloAnos(listaAntigoPadrao, listaNovoPadrao, 1980, 2022);
    clock_gettime(CLOCK_REALTIME, &tend);
    sub_timespec(tstart, tend, &delta);
    fprintf(salva,"%d.%.9ld;", (int)delta.tv_sec, delta.tv_nsec);

    clock_gettime(CLOCK_REALTIME, &tstart);
	relatorio_porEstado(listaAntigoPadrao, listaNovoPadrao, "SP");
    clock_gettime(CLOCK_REALTIME, &tend);
    sub_timespec(tstart, tend, &delta);
    fprintf(salva,"%d.%.9ld;", (int)delta.tv_sec, delta.tv_nsec);

    clock_gettime(CLOCK_REALTIME, &tstart);    
    no = buscaPlaca(listaAntigoPadrao, listaNovoPadrao, "MUC9583");
    clock_gettime(CLOCK_REALTIME, &tend);
    sub_timespec(tstart, tend, &delta);
    fprintf(salva,"%d.%.9ld;", (int)delta.tv_sec, delta.tv_nsec);

    clock_gettime(CLOCK_REALTIME, &tstart); 
    no = alterarPlaca(listaAntigoPadrao, listaNovoPadrao, "MUC9583");
    clock_gettime(CLOCK_REALTIME, &tend);
    sub_timespec(tstart, tend, &delta);
    fprintf(salva,"%d.%.9ld\n", (int)delta.tv_sec, delta.tv_nsec);

    /*COMO ELA TA SALVANDO NO ARQUIVO CSV*/
    /*carregamento;relatorioAno;relatorioEstado;buscaPlaca;alteraPlaca*/

	gravacaoBinario(listaAntigoPadrao, listaNovoPadrao);
	
	deleta_tabela(listaAntigoPadrao);
	deleta_tabela(listaNovoPadrao);

    fclose(salva);
	return 0;
}
