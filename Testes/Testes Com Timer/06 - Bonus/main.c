#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvore_avl.h"
#include "arquivos.h"
#include "hash.h"

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
	Node *tabelaAntigoPadrao[TAM], *tabelaNovoPadrao[TAM], *altera1, *altera2;
	char placa[8], estado[3];
	int anoInicio, anoFim,i, qtd;
	
    struct timespec tstart, tend, delta;

    FILE *salva;
    salva = fopen("testes.csv", "a");
    if(salva==NULL) return -1;    

    clock_gettime(CLOCK_REALTIME, &tstart);
	inicializar_tabela(tabelaAntigoPadrao);
	inicializar_tabela(tabelaNovoPadrao);
	
	carregamento_arquivo(argc, argv, tabelaAntigoPadrao, tabelaNovoPadrao);
    clock_gettime(CLOCK_REALTIME, &tend);
    sub_timespec(tstart, tend, &delta);
    fprintf(salva,"%d.%.9ld;", (int)delta.tv_sec, delta.tv_nsec);
	
	/*printf("------------------Antigo padrao-------------\n");
	imprimir_tabela(tabelaAntigoPadrao);
	printf("------------------Novo padrao----------------\n");
	imprimir_tabela(tabelaNovoPadrao);
	
	
	relatorio_porEstado(listaAntigoPadrao, listaNovoPadrao, "SP");
	*/
    
    clock_gettime(CLOCK_REALTIME, &tstart);
	relatorio_intervaloAnos(tabelaAntigoPadrao, tabelaNovoPadrao, 1980, 2022);
    clock_gettime(CLOCK_REALTIME, &tend);
    sub_timespec(tstart, tend, &delta);
    fprintf(salva,"%d.%.9ld;", (int)delta.tv_sec, delta.tv_nsec);

    clock_gettime(CLOCK_REALTIME, &tstart);
	relatorio_porEstado(tabelaAntigoPadrao, tabelaNovoPadrao, "SP");
    clock_gettime(CLOCK_REALTIME, &tend);
    sub_timespec(tstart, tend, &delta);
    fprintf(salva,"%d.%.9ld;", (int)delta.tv_sec, delta.tv_nsec);

    clock_gettime(CLOCK_REALTIME, &tstart);
    altera1 = procurar_veiculo(tabelaAntigoPadrao, tabelaNovoPadrao, "MUC9583");
    clock_gettime(CLOCK_REALTIME, &tend);
    sub_timespec(tstart, tend, &delta);
    fprintf(salva,"%d.%.9ld;", (int)delta.tv_sec, delta.tv_nsec);

    clock_gettime(CLOCK_REALTIME, &tstart);
    altera2 = alterarPlaca(tabelaAntigoPadrao, tabelaNovoPadrao, "MUC9583");
    clock_gettime(CLOCK_REALTIME, &tend);
    sub_timespec(tstart, tend, &delta);
    fprintf(salva,"%d.%.9ld\n", (int)delta.tv_sec, delta.tv_nsec);

    /*COMO ELA TA SALVANDO NO ARQUIVO CSV*/
    /*carregamento;relatorioAno;relatorioEstado;buscaPlaca;alteraPlaca*/


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

    fclose(salva);

	return 0;
}
