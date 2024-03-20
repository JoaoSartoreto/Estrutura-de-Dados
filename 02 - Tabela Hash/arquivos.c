#include "arquivos.h"

void carregamentoERNV(No listaAntigoPadrao[], No listaNovoPadrao[], char *arquivo)
{
	FILE *ptarq;
	Veiculo v;
	No *novo;
	
	ptarq = fopen(arquivo,"r");
	if(ptarq != NULL)
	{
		
		while(fscanf(ptarq,"%[^;];%[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^;];%[^\n]\n",
			v.placa,
			v.renavam,
			v.marca,
			v.modelo,
			&v.ano,
			v.cor,
			v.categoria,
			v.estado,
			v.cidade)==9)
		{
			novo = buscaPlaca(listaAntigoPadrao, listaNovoPadrao, v.placa);
			if(novo == NULL)
			{
				novo = criar_no(v);
				if(novo)
				{
					if(v.placa[4]>='A' && v.placa[4]<='Z')
					{
						insere_tabela(listaNovoPadrao,novo);
					}
					else if(v.placa[4]>='0' && v.placa[4]<='9')
					{
						insere_tabela(listaAntigoPadrao,novo);
					}
				}
				else
					printf("Falha ao tentar alocar memória para a placa: %s\n",v.placa);
			}
		}
			
			
			
		fclose(ptarq);
	}
	else
	{
		printf("Não foi possivel abrir o arquivo %s\n",arquivo);
		printf("Forma correta de execução: ./main.exe arquivo.ernv\n");
	}
	
}

void carregamentoBinario(No listaAntigoPadrao[], No listaNovoPadrao[])
{
	FILE *ptarq;
	Veiculo v;
	No *novo;
	int i;
	
	
	ptarq = fopen("antigoPadrao.bin","rb");
	if(ptarq != NULL)
	{
		for(i=0;i<TAM;i++)
		{
			while(fread(&v, sizeof(Veiculo), 1, ptarq)==1 && v.placa[0]!='$')
			{
				novo = criar_no(v);
				if(novo)
					inserir_no_inicio(&listaAntigoPadrao[i],novo);
				else
					printf("Falha ao tentar alocar memoria para a placa: %s\n",v.placa);
				
			}
		}
			
			
			
		fclose(ptarq);
	}
	else
		printf("Falha ao tentar abrir o arquivo antigoPadrao.bin\n");
	
	ptarq = fopen("novoPadrao.bin","rb");
	if(ptarq != NULL)
	{
		for(i=0;i<TAM;i++)
		{
			while(fread(&v, sizeof(Veiculo), 1, ptarq)==1 && v.placa[0]!='$')
			{
				novo = criar_no(v);
				if(novo)
					inserir_no_inicio(&listaNovoPadrao[i],novo);
				else
					printf("Falha ao tentar alocar memoria para a placa: %s\n",v.placa);
				
			}
		}
			
			
			
		fclose(ptarq);
	}
	else
		printf("Falha ao tentar abrir o arquivo novoPadrao.bin");
	
}

void carregamento_arquivo(int argc, char *argv[], No listaAntigoPadrao[], No listaNovoPadrao[])
{
	if(argc<=1)
	{
		carregamentoBinario(listaAntigoPadrao,listaNovoPadrao);
	}
	else
	{
		carregamentoBinario(listaAntigoPadrao,listaNovoPadrao);
		carregamentoERNV(listaAntigoPadrao,listaNovoPadrao, argv[1]);
	}
}

No *inverterLista(No **listaOrdenada)
{
	No *no, *aux, *novo;
	No listaInvertida;
	listaInvertida.proximo = NULL;

	if(*listaOrdenada == NULL)
		return NULL;


	no = *listaOrdenada;
	while(no)
	{
		novo = criar_no(no->veiculo);
		if(novo)
			inserir_no_inicio(&listaInvertida,novo);
		else
			printf("Falha ao tentar alocar memoria para a placa: %s\n",no->veiculo.placa);
		aux = no;
		no = no->proximo;
		free(aux);
	}
	
	return listaInvertida.proximo;
}

void gravacaoBinario(No listaAntigoPadrao[], No listaNovoPadrao[])
{
	FILE *ptarq;
	No *no;
	int i;
	Veiculo v;
	
	
	v.placa[0] = '$';
	
	
	ptarq = fopen("antigoPadrao.bin","wb");
	if(ptarq != NULL)
	{
	
		for(i=0;i<TAM;i++)
		{
			listaAntigoPadrao[i].proximo = inverterLista(&listaAntigoPadrao[i].proximo);
			
			no = listaAntigoPadrao[i].proximo;
			while(no)
			{
				fwrite(&no->veiculo, sizeof(Veiculo), 1, ptarq);
				
				no = no->proximo;
				
			}
			fwrite(&v, sizeof(Veiculo), 1, ptarq);
		}
		fclose(ptarq);
	}
	else
		printf("Falha ao tentar abrir o arquivo antigoPadrao.bin\n");

	ptarq = fopen("novoPadrao.bin","wb");
	if(ptarq != NULL)
	{		
	
		for(i=0;i<TAM;i++)
		{
			listaNovoPadrao[i].proximo = inverterLista(&listaNovoPadrao[i].proximo);
			
			no = listaNovoPadrao[i].proximo;
			while(no)
			{
				fwrite(&no->veiculo, sizeof(Veiculo), 1, ptarq);
				
				no = no->proximo;
				
			}
			fwrite(&v, sizeof(Veiculo), 1, ptarq);
		}
		fclose(ptarq);
		
	}
	else
		printf("Falha ao tentar abrir o arquivo novoPadrao.bin\n");
}
