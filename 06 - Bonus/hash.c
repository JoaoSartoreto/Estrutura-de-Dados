#include"hash.h"

void inicializar_tabela(Node *tabela[TAM])
{
	int i;
	
	for(i = 0; i<TAM; i++)
	{
		tabela[i] = NULL;
	}
}

int valor_caractere(char c)
{
	int r;
	
	if(c == 'A')
		r = 0;
	else if(c == 'B')
		r = 1;
	else if(c == 'C')
		r = 2;
	else if(c == 'D')
		r = 3;
	else if(c == 'E')
		r = 4;
	else if(c == 'F')
		r = 5;
	else if(c == 'G')
		r = 6;
	else if(c == 'H')
		r = 7;
	else if(c == 'I')
		r = 8;
	else if(c == 'J')
		r = 9;
	else if(c == 'K')
		r = 10;
	else if(c == 'L')
		r = 11;
	else if(c == 'M')
		r = 12;
	else if(c == 'N')
		r = 13;
	else if(c == 'O')
		r = 14;
	else if(c == 'P')
		r = 15;
	else if(c == 'Q')
		r = 16;
	else if(c == 'R')
		r = 17;
	else if(c == 'S')
		r = 18;
	else if(c == 'T')
		r = 19;
	else if(c == 'U')
		r = 20;
	else if(c == 'V')
		r = 21;
	else if(c == 'W')
		r = 22;
	else if(c == 'X')
		r = 23;
	else if(c == 'Y')
		r = 24;
	else if(c == 'Z')
		r = 25;
	

	return r;
}

int funcao_hash(char placa[])
{
	int val_char1, val_char2, val_char3, chave = 0;
	
	val_char1 = valor_caractere(placa[0]);
	val_char2 = valor_caractere(placa[1]);
	val_char3 = valor_caractere(placa[2]);
	chave = (val_char1*26*26) + (val_char2*26) + val_char3;
	
	return chave;
}

void insere_tabela(Node *tabela[], Veiculo v)
{
	int chave;
	
	chave = funcao_hash(v.placa);
	
	tabela[chave] = inserir_veiculo(tabela[chave],v);
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



Node* procurar_veiculo(Node *tabelaAntigoPadrao[], Node *tabelaNovoPadrao[], const char *placa)
{
	Node *no = NULL;
	char placaS[8];
	int chave;
	
	strcpy(placaS, placa);
	chave = funcao_hash(placaS);
	if(chave < 0 || chave >= TAM)
		return NULL;
	
	if(placaS[4]>='A' && placaS[4]<='Z')
	{
		no = buscaPlaca(tabelaNovoPadrao[chave],placaS);
	}
	else
	{
		no = buscaPlaca(tabelaAntigoPadrao[chave],placaS);
		if(no==NULL)
		{
			placaS[4] = placaS[4] + 17;
			chave = funcao_hash(placaS);
			if(chave < 0 || chave >= TAM)
				return NULL;
			
			no = buscaPlaca(tabelaNovoPadrao[chave],placaS);
			
		}
	}
	
	
	return no;
}


Node* alterarPlaca(Node *tabelaAntigoPadrao[], Node *tabelaNovoPadrao[], const char *placa)
{
	Node *alterar, *novo = NULL;
	Veiculo v;
	int retorno, chave;
	char placaS[8];
	
	strcpy(placaS, placa);
	chave = funcao_hash(placaS);
	if(chave < 0 || chave >= TAM)
		return NULL;
		
	alterar = buscaPlaca(tabelaAntigoPadrao[chave],placaS);
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
		
		tabelaAntigoPadrao[chave] = remover_veiculo(tabelaAntigoPadrao[chave],placaS);
		
		v.placa[4] = v.placa[4] + 17;
		chave = funcao_hash(v.placa);
		
		tabelaNovoPadrao[chave] = inserir_veiculo(tabelaNovoPadrao[chave],v);
		
		novo = buscaPlaca(tabelaNovoPadrao[chave], v.placa);
		return novo;
	}
	else
		return NULL;
}

void relatorio_intervaloAnos(Node *tabelaAntigoPadrao[], Node *tabelaNovoPadrao[], int anoInicial, int anoFinal)
{
	int i;

	for(i=0;i<TAM;i++)
	{
		relatorio_anos(tabelaAntigoPadrao[i], anoInicial, anoFinal);
	}
	
	for(i=0;i<TAM;i++)
	{
		relatorio_anos(tabelaNovoPadrao[i], anoInicial, anoFinal);
	}
	
}

void relatorio_porEstado(Node *tabelaAntigoPadrao[], Node *tabelaNovoPadrao[], char estado[3])
{
	char finalP = '0';
	int i=0, j;
	
	while(finalP<='9')
	{
		for(j=0;j<TAM;j++)
		{
			relatorio_estado(tabelaAntigoPadrao[j], estado, finalP);
		}
		
		for(j=0;j<TAM;j++)
		{
			relatorio_estado(tabelaNovoPadrao[j], estado, finalP);
		}
		
		i++;
		finalP = '0' + i;
	}	
	
}

void imprimir_tabela(Node *tabela[])
{
	int i;
	
	for(i=0;i<TAM;i++)
	{
		imprimir_veiculos(tabela[i]);
	}
	
}

void deleta_tabela(Node *tabela[TAM])
{
	int i;
	
	for(i = 0; i<TAM; i++)
	{
		delete_tree(tabela[i]);
	}

}
