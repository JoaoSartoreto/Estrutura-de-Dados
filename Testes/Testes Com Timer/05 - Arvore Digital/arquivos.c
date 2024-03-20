#include "arquivos.h"

void carregamentoERNV(Node **rootAntigoPadrao, Node **rootNovoPadrao, char *arquivo)
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
			busca = procurar_veiculo(*rootAntigoPadrao, *rootNovoPadrao, v.placa);
			if(busca == NULL)
			{
				if(v.placa[4]>='A' && v.placa[4]<='Z')
				{
					*rootNovoPadrao = inserir_veiculo(*rootNovoPadrao,v);
				}
				else if(v.placa[4]>='0' && v.placa[4]<='9')
				{
					*rootAntigoPadrao = inserir_veiculo(*rootAntigoPadrao,v);
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

void carregamentoBinario(Node **rootAntigoPadrao, Node **rootNovoPadrao)
{
	FILE *ptarq;
	Veiculo v;
	
	ptarq = fopen("antigoPadrao.bin","rb");
	if(ptarq != NULL)
	{
		while(fread(&v, sizeof(Veiculo), 1, ptarq)==1)
		{
			*rootAntigoPadrao = inserir_veiculo(*rootAntigoPadrao,v);
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
			*rootNovoPadrao = inserir_veiculo(*rootNovoPadrao,v);
		}
			
			
			
		fclose(ptarq);
	}
	else
		printf("Falha ao tentar abrir o arquivo novoPadrao.bin\n");
	
}

void carregamento_arquivo(int argc, char *argv[], Node **rootAntigoPadrao, Node **rootNovoPadrao)
{
	if(argc<=1)
	{
		carregamentoBinario(rootAntigoPadrao,rootNovoPadrao);
	}
	else
	{
		carregamentoBinario(rootAntigoPadrao,rootNovoPadrao);
		carregamentoERNV(rootAntigoPadrao,rootNovoPadrao, argv[1]);
	}
}

void gravarTree(FILE *file, Node *root)
{
	int i;
	Node* temp;

	if (!root)
		return;
	temp = root;
	if(temp->veiculo)
	{
		fwrite(root->veiculo, sizeof(Veiculo), 1, file);
	}		
	for (i=0; i<N; i++) {
		gravarTree(file, temp->children[i]); 
	}

}

void gravacaoBinario(Node **rootAntigoPadrao, Node **rootNovoPadrao)
{
	FILE *ptarq;
	
	ptarq = fopen("antigoPadrao.bin","wb");
	if(ptarq != NULL)
	{
		if(*rootAntigoPadrao)
			gravarTree(ptarq, *rootAntigoPadrao);


		fclose(ptarq);
	}
	else
		printf("Falha ao tentar abrir o arquivo antigoPadrao.bin\n");
	
	ptarq = fopen("novoPadrao.bin","wb");
	if(ptarq != NULL)
	{		
		if(*rootNovoPadrao)
			gravarTree(ptarq, *rootNovoPadrao);
		
			
		fclose(ptarq);
	}
	else
		printf("Falha ao tentar abrir o arquivo novoPadrao.bin\n");
}
