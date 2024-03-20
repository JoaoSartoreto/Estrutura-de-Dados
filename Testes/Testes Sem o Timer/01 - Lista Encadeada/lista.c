#include"lista.h"

No* criar_no(Veiculo v)
{
	No *novo = malloc(sizeof(No));
	
	if(novo)
	{
		novo->veiculo = v;
		novo->proximo = NULL;
		return novo;
	}
	else
		printf("Falha ao alocar um novo nó.\n");
	return NULL;
}

void inserir_no_inicio(No **lista, No *novo)
{

	novo->proximo = *lista;
	*lista = novo;
}


No* remover_veiculo(No **lista, char placa[])
{
	No *aux,*remover = NULL;
	
	if(*lista)
	{
		if(strcmp((*lista)->veiculo.placa,placa) == 0)
		{
			remover = *lista;
			*lista = remover->proximo;
		}
		else
		{
			aux = *lista;
			while(aux->proximo &&strcmp(aux->proximo->veiculo.placa,placa) != 0)
				aux = aux->proximo;
			if(aux->proximo)
			{
				remover = aux->proximo;
				aux->proximo = remover->proximo;
			}
		}
	}
	
	
	return remover;
}

int comparaCategoria(char categoriaAnt[])
{
	int id;
	/*IDs
	0 = Mantem o anterior;
	1 = Comercial
	2 = Especiais
	3 = Oficial e Representação
	4 = Diplomático/Consular
	*/
	
	id = 0;
	
	if(strcmp(categoriaAnt, "Aluguel")==0 || strcmp(categoriaAnt, "Aprendizagem")==0)
	{
		return id = 1;
	}
	else if(strcmp(categoriaAnt, "Experiência/Fabricante")==0)
	{
		return id = 2;
	}
	else if(strcmp(categoriaAnt, "Oficial")==0 || strcmp(categoriaAnt, "Representação")==0)
	{
		return id = 3;
	}
	else if(strcmp(categoriaAnt, "Missão Diplomática")==0 || strcmp(categoriaAnt, "Corpo Consular")==0 || strcmp(categoriaAnt, "Corpo Diplomático")==0)
	{
		return id = 4;
	}
	else if(strcmp(categoriaAnt, "Organismo Consular/Internacional")==0 || strcmp(categoriaAnt, "Acordo Cooperação Internacional")==0)
	{
		return id = 4;
	}
	else
		return id;
}


/*
      Procedimento para inserir ordenado
*/
void inserir_ordenado(No **lista, No *novo)
{
	No *aux;


	if(*lista == NULL)
	{ /* a lista está vazia?*/
		novo->proximo = NULL;
		*lista = novo;
	}
	else if(strcmp(novo->veiculo.placa,(*lista)->veiculo.placa)<0)
	{ /* é o menor?*/
		novo->proximo = *lista;
		*lista = novo;
	}
	else
	{ /* inserção no meio ou no final da lista*/
		aux = *lista;
		while(aux->proximo && strcmp(novo->veiculo.placa,aux->proximo->veiculo.placa) >= 0)
		aux = aux->proximo;
		if(strcmp(novo->veiculo.placa,aux->veiculo.placa)!=0)
		{
		    novo->proximo = aux->proximo;
		    aux->proximo = novo;
		}
	}
}

No *buscarPlacaAntiga(No **listaAntigoPadrao, char placa[])
{
	No *no = NULL;

	no = *listaAntigoPadrao;
	while(no)
	{
		if(strcmp(no->veiculo.placa,placa)==0)
		{
			return no;
		}
		
		no = no->proximo;
	}
	
	return no;
}

No *buscarPlacaNova(No **listaNovoPadrao, char placa[])
{
	No *no = NULL;

	no = *listaNovoPadrao;
	while(no)
	{
		if(strcmp(no->veiculo.placa,placa)==0)
		{
			return no;
		}
		
		no = no->proximo;
	}
	
	return no;
}

No* buscaPlaca(No **listaAntigoPadrao, No **listaNovoPadrao, char placa[])
{
	No *no = NULL;
	char placaS[8];
	strcpy(placaS, placa);
	
	if(placaS[4]>='A' && placa[4]<='Z')
	{
		no = buscarPlacaNova(listaNovoPadrao,placaS);
	}
	else
	{
		no = buscarPlacaAntiga(listaAntigoPadrao,placaS);
		if(no==NULL)
		{
			placaS[4] = placaS[4] + 17;
			no = buscarPlacaNova(listaNovoPadrao,placaS);
			
		}
	}
	
	
	return no;
}


No* alterarPlaca(No **listaAntigoPadrao, No **listaNovoPadrao, char placa[])
{
	No *alterar, *novo = NULL;
	Veiculo v;
	int retorno;
	
	alterar = remover_veiculo(listaAntigoPadrao,placa);
	if(alterar)
	{
		strcpy(v.placa,alterar->veiculo.placa);
		strcpy(v.renavam,alterar->veiculo.renavam);
		strcpy(v.marca,alterar->veiculo.marca);
		strcpy(v.modelo,alterar->veiculo.modelo);
		v.ano = alterar->veiculo.ano;
		strcpy(v.cor,alterar->veiculo.cor);
		retorno = comparaCategoria(alterar->veiculo.categoria);
		if(retorno>0)
		{
			if(retorno==1)
			{
				strcpy(v.categoria,"Comercial");
			}
			else if(retorno==2)
			{
				strcpy(v.categoria,"Especiais");
			}
			else if(retorno==3)
			{
				strcpy(v.categoria,"Oficial e Representação");
			}
			else if(retorno==4)
			{
				strcpy(v.categoria,"Diplomático/Consular");
			}
		}
		else
		{
			strcpy(v.categoria,alterar->veiculo.categoria);
		}
		strcpy(v.estado,alterar->veiculo.estado);
		strcpy(v.cidade,alterar->veiculo.cidade);
		
		free(alterar);
		
		v.placa[4] = v.placa[4] + 17;
		
		novo = criar_no(v);
		if(novo)
			inserir_ordenado(listaNovoPadrao,novo);
		else
			printf("Falha ao tentar alocar memoria para a placa: %s\n",v.placa);
		return novo;
	}
	else
		return novo;
}

void relatorio_intervaloAnos(No **listaAntigoPadrao, No **listaNovoPadrao, int anoInicial, int anoFinal)
{
	No *no;
	
	no = *listaAntigoPadrao;
	while(no)
	{
		if(no->veiculo.ano >= anoInicial && no->veiculo.ano <= anoFinal)
		{	
			printf("%s;%s;%s;%s;%d;%s;%s;%s;%s\n",
			no->veiculo.placa,
			no->veiculo.renavam,
			no->veiculo.marca,
			no->veiculo.modelo,
			no->veiculo.ano,
			no->veiculo.cor,
			no->veiculo.categoria,
			no->veiculo.estado,
			no->veiculo.cidade);
		}
		
		no = no->proximo;
	}
	
	no = *listaNovoPadrao;
	while(no)
	{
		if(no->veiculo.ano >= anoInicial && no->veiculo.ano <= anoFinal)
		{	
			printf("%s;%s;%s;%s;%d;%s;%s;%s;%s\n",
			no->veiculo.placa,
			no->veiculo.renavam,
			no->veiculo.marca,
			no->veiculo.modelo,
			no->veiculo.ano,
			no->veiculo.cor,
			no->veiculo.categoria,
			no->veiculo.estado,
			no->veiculo.cidade);
		}
		
		no = no->proximo;
	}
}

void relatorio_porEstado(No **listaAntigoPadrao, No **listaNovoPadrao, char estado[3])
{
	No *no;
	char finalP = '0';
	int i=0;
	
	while(finalP<='9')
	{
		no = *listaAntigoPadrao;
		while(no)
		{
			if(strcmp(no->veiculo.estado,estado)==0 && no->veiculo.placa[6] == finalP)
			{	
				printf("%s;%s;%s;%s;%d;%s;%s;%s;%s\n",
				no->veiculo.placa,
				no->veiculo.renavam,
				no->veiculo.marca,
				no->veiculo.modelo,
				no->veiculo.ano,
				no->veiculo.cor,
				no->veiculo.categoria,
				no->veiculo.estado,
				no->veiculo.cidade);
			}
			
			no = no->proximo;
		}
		
		no = *listaNovoPadrao;
		while(no)
		{
			if(strcmp(no->veiculo.estado,estado)==0 && no->veiculo.placa[6] == finalP)
			{	
				printf("%s;%s;%s;%s;%d;%s;%s;%s;%s\n",
				no->veiculo.placa,
				no->veiculo.renavam,
				no->veiculo.marca,
				no->veiculo.modelo,
				no->veiculo.ano,
				no->veiculo.cor,
				no->veiculo.categoria,
				no->veiculo.estado,
				no->veiculo.cidade);
			}
			
			no = no->proximo;
		}
		
		i++;
		finalP = '0' + i;
	}	
	
}


void imprimir_veiculos(No *lista)
{
	No *no = lista;
	if(no)
	{
		printf("----------------\n");
		while(no!=NULL)
		{
			printf("%s;%s;%s;%s;%d;%s;%s;%s;%s;\n",
			no->veiculo.placa,
			no->veiculo.renavam,
			no->veiculo.marca,
			no->veiculo.modelo,
			no->veiculo.ano,
			no->veiculo.cor,
			no->veiculo.categoria,
			no->veiculo.estado,
			no->veiculo.cidade);

			no = no->proximo;
		}
		printf("\n\n");
	}
}


void libera_lista(No **lista)
{
	No *aux, *remove;
	
	aux = *lista;
	while(aux)
	{
		remove = aux;
		aux = aux->proximo;
		free(remove);
	}
}
