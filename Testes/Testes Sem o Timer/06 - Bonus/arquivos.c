#include "arquivos.h"

void carregamentoERNV(Node *tabelaAntigoPadrao[], Node *tabelaNovoPadrao[], char *arquivo)
{
	FILE *ptarq;
	Node *busca;
	Veiculo v;
	
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
			busca = procurar_veiculo(tabelaAntigoPadrao, tabelaNovoPadrao, v.placa);
			if(busca == NULL)
			{
				if(v.placa[4]>='A' && v.placa[4]<='Z')
				{
					insere_tabela(tabelaNovoPadrao,v);
				}
				else if(v.placa[4]>='0' && v.placa[4]<='9')
				{
					insere_tabela(tabelaAntigoPadrao,v);
				}
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

void carregamentoBinario(Node *tabelaAntigoPadrao[], Node *tabelaNovoPadrao[])
{
	FILE *ptarq;
	Veiculo v;
	
	ptarq = fopen("antigoPadrao.bin","rb");
	if(ptarq != NULL)
	{
		while(fread(&v, sizeof(Veiculo), 1, ptarq)==1)
		{
			insere_tabela(tabelaAntigoPadrao,v);
		}
			
			
			
		fclose(ptarq);
	}
	else
		printf("Falha ao tentar abrir o arquivo antigoPadrao.bin\n");
	
	ptarq = fopen("novoPadrao.bin","rb");
	if(ptarq != NULL)
	{
		while(fread(&v, sizeof(Veiculo), 1, ptarq)==1)
		{
			insere_tabela(tabelaNovoPadrao,v);
		}
			
			
			
		fclose(ptarq);
	}
	else
		printf("Falha ao tentar abrir o arquivo novoPadrao.bin\n");
	
}

void carregamento_arquivo(int argc, char *argv[], Node *tabelaAntigoPadrao[], Node *tabelaNovoPadrao[])
{
	if(argc<=1)
	{
		carregamentoBinario(tabelaAntigoPadrao,tabelaNovoPadrao);
	}
	else
	{
		carregamentoBinario(tabelaAntigoPadrao,tabelaNovoPadrao);
		carregamentoERNV(tabelaAntigoPadrao,tabelaNovoPadrao, argv[1]);
	}
}

void gravarTree(FILE *file, Node *root)
{

	if(root)
	{
		fwrite(&root->veiculo, sizeof(Veiculo), 1, file);
		gravarTree(file, root->left_child);
		gravarTree(file, root->right_child);
	}
}

void gravacaoBinario(Node *tabelaAntigoPadrao[], Node *tabelaNovoPadrao[])
{
	FILE *ptarq;
	int i;
	
	ptarq = fopen("antigoPadrao.bin","wb");
	if(ptarq != NULL)
	{
		for(i=0;i<TAM;i++)
			gravarTree(ptarq, tabelaAntigoPadrao[i]);


		fclose(ptarq);
	}
	else
		printf("Falha ao tentar abrir o arquivo antigoPadrao.bin\n");
	
	ptarq = fopen("novoPadrao.bin","wb");
	if(ptarq != NULL)
	{		
		for(i=0;i<TAM;i++)
			gravarTree(ptarq, tabelaNovoPadrao[i]);
		
			
		fclose(ptarq);
	}
	else
		printf("Falha ao tentar abrir o arquivo novoPadrao.bin\n");
}
