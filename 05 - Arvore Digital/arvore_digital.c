#include "arvore_digital.h"

/*
    Função que cria um novo nó
    x -> valor a ser inserido no nó
    Retorna: o endereço do nó criado
*/
Node *make_trienode(char data, Veiculo *v)
{
	/* Allocate memory for a TrieNode */
	Node* node = (Node*)malloc(sizeof(Node));
	Veiculo *veic;
	int i;

	if(node)
	{
		if(v)
		{
			veic = (Veiculo*)malloc(sizeof(Veiculo));
			*veic = *v;
		}
		else
			veic = NULL;
		

		for (i=0; i<N; i++)
			node->children[i] = NULL;
		node->is_leaf = 0;
		node->veiculo = veic;
		node->data = data;
		
		return node;
	}
	else
		printf("Falha ao tentar alocar memória para o nó de caractere: %c\n",data);
	return NULL;
}

int tabela_alfabeto(char a)
{
	int i;

	if(a == 'A')
		i = 0;
	else if(a == 'B')
		i = 1;
	else if(a == 'C')
		i = 2;
	else if(a == 'D')
		i = 3;
	else if(a == 'E')
		i = 4;
	else if(a == 'F')
		i = 5;
	else if(a == 'G')
		i = 6;
	else if(a == 'H')
		i = 7;
	else if(a == 'I')
		i = 8;
	else if(a == 'J')
		i = 9;
	else if(a == 'K')
		i = 10;
	else if(a == 'L')
		i = 11;
	else if(a == 'M')
		i = 12;
	else if(a == 'N')
		i = 13;
	else if(a == 'O')
		i = 14;
	else if(a == 'P')
		i = 15;
	else if(a == 'Q')
		i = 16;
	else if(a == 'R')
		i = 17;
	else if(a == 'S')
		i = 18;
	else if(a == 'T')
		i = 19;
	else if(a == 'U')
		i = 20;
	else if(a == 'V')
		i = 21;
	else if(a == 'W')
		i = 22;
	else if(a == 'X')
		i = 23;
	else if(a == 'Y')
		i = 24;
	else if(a == 'Z')
		i = 25;
	else if(a == '0')
		i = 26;
	else if(a == '1')
		i = 27;
	else if(a == '2')
		i = 28;
	else if(a == '3')
		i = 29;
	else if(a == '4')
		i = 30;
	else if(a == '5')
		i = 31;
	else if(a == '6')
		i = 32;
	else if(a == '7')
		i = 33;
	else if(a == '8')
		i = 34;
	else if(a == '9')
		i = 35;
	
	return i;
}

Node* inserir_veiculo(Node *root, Veiculo v)
{
	/* Inserts the word onto the Trie */
	/* ASSUMPTION: The word only has lower case characters */
	Node* temp = root;
	int i, idx;

	for (i=0; v.placa[i] != '\0'; i++) {
		/* Get the relative position in the alphabet list */
		idx = tabela_alfabeto(v.placa[i]);
		if (temp->children[idx] == NULL) {
		    /* If the corresponding child doesn't exist, */
		    /* simply create that child! */
		    if(v.placa[i+1] == '\0')
		    	temp->children[idx] = make_trienode(v.placa[i], &v);
		    else
		    	temp->children[idx] = make_trienode(v.placa[i], NULL);
		}
		else {
		    /* Do nothing. The node already exists */
		}
		/* Go down a level, to the child referenced by idx */
		/* since we have a prefix match */
		temp = temp->children[idx];
	}
	/* At the end of the word, mark this node as the leaf node */
	temp->is_leaf = 1;
	return root;
}


int check_divergence(Node* root, char* word) {
	/* Checks if there is branching at the last character of word */
	/* and returns the largest position in the word where branching occurs */
	Node* temp = root;
	int len = strlen(word), i, j, position, last_index;


	if (len == 0)
	return 0;
	/* We will return the largest index where branching occurs */
	last_index = 0;
	for (i=0; i < len; i++) {
		position = tabela_alfabeto(word[i]);
		if (temp->children[position]) {
		    /* If a child exists at that position */
		    /* we will check if there exists any other child */
		    /* so that branching occurs */
		    for (j=0; j<N; j++) {
			if (j != position && temp->children[j]) {
			    /* We've found another child! This is a branch. */
			    /* Update the branch position */
			    last_index = i + 1;
			    break;
			}
		    }
		    /* Go to the next child in the sequence */
		    temp = temp->children[position];
		}
	}
	return last_index;
}



char* find_longest_prefix(Node* root, char* word) {
	/* Finds the longest common prefix substring of word */
	/* in the Trie */
	int len, i, branch_idx;
	char* longest_prefix;

	if (!word || word[0] == '\0')
		return NULL;
	/* Length of the longest prefix */
	len = strlen(word);

	/* We initially set the longest prefix as the word itself, */
	/* and try to back-tracking from the deepst position to */
	/* a point of divergence, if it exists */
	longest_prefix = (char*) malloc ((len + 1) * sizeof(char));
	for (i=0; word[i] != '\0'; i++)
		longest_prefix[i] = word[i];
	longest_prefix[len] = '\0';

	/* If there is no branching from the root, this */
	/* means that we're matching the original string! */
	/* This is not what we want! */
	branch_idx  = check_divergence(root, longest_prefix) - 1;
	if (branch_idx >= 0) {
		/* There is branching, We must update the position */
		/* to the longest match and update the longest prefix */
		/* by the branch index length */
		longest_prefix[branch_idx] = '\0';
		longest_prefix = (char*) realloc (longest_prefix, (branch_idx + 1) * sizeof(char));
	}

	return longest_prefix;
}


int is_leaf_node(Node* root, char* word) {
    /* Checks if the prefix match of word and root */
    /* is a leaf node */
    Node* temp = root;
    int i;
    
    for (i=0; word[i]; i++) {
        int position = tabela_alfabeto(word[i]);
        if (temp->children[position]) {
            temp = temp->children[position];
        }
    }
    return temp->is_leaf;
}


Node* remover_veiculo(Node *root, char *word) {
	/* Will try to delete the word sequence from the Trie only it */
	/* ends up in a leaf node */
	char* longest_prefix;
	int i, position, len;
	Node *temp, *rm_node;

	if (!root)
		return NULL;
	if (!word || word[0] == '\0')
		return root;
	/* If the node corresponding to the match is not a leaf node, */
	/* we stop */
	if (!is_leaf_node(root, word)) {
		return root;
	}
	temp = root;
	/* Find the longest prefix string that is not the current word */
	longest_prefix = find_longest_prefix(root, word);
	/* printf("Longest Prefix = %s\n", longest_prefix); */
	if (longest_prefix[0] == '\0') {
		free(longest_prefix);
		return root;
	}
	/* Keep track of position in the Trie */
	for (i=0; longest_prefix[i] != '\0'; i++) {
		position = tabela_alfabeto(longest_prefix[i]);
		if (temp->children[position] != NULL) {
		    /* Keep moving to the deepest node in the common prefix */
		    temp = temp->children[position];
		}
		else {
		    /* There is no such node. Simply return. */
		    free(longest_prefix);
		    return root;
		}
	}
	/* Now, we have reached the deepest common node between */
	/* the two strings. We need to delete the sequence */
	/* corresponding to word */
	len = strlen(word);
	for (; i < len; i++) {
		position = tabela_alfabeto(word[i]);
		if (temp->children[position]) {
		    /* Delete the remaining sequence */
		    rm_node = temp->children[position];
		    temp->children[position] = NULL;
		    free_trienode(rm_node);
		}
	}
	free(longest_prefix);
	return root;
}



Node *buscaPlaca(Node *root, char placa[]) 
{
	/* Searches for word in the Trie */
	Node* temp = root;
	int i, position;
	
	for(i=0; placa[i]!='\0'; i++)
	{
		position = tabela_alfabeto(placa[i]);
		if (temp->children[position] == NULL)
			return NULL;
		temp = temp->children[position];
	}
	if (temp != NULL && temp->is_leaf == 1)
		return temp;
	return NULL;
}


Node* procurar_veiculo(Node *rootAntigoPadrao, Node *rootNovoPadrao, const char *placa)
{
	Node *no = NULL;
	char placaS[8];
	strcpy(placaS, placa);
	
	if(placaS[4]>='A' && placaS[4]<='Z')
	{
		no = buscaPlaca(rootNovoPadrao,placaS);
	}
	else
	{
		no = buscaPlaca(rootAntigoPadrao,placaS);
		if(no==NULL)
		{
			placaS[4] = placaS[4] + 17;
			no = buscaPlaca(rootNovoPadrao,placaS);
			
		}
	}
	
	return no;
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

Node* alterarPlaca(Node **rootAntigoPadrao, Node **rootNovoPadrao, const char *placa)
{
	Node *alterar, *novo = NULL;
	Veiculo v;
	int retorno;
	char placaS[8];
	strcpy(placaS, placa);
	
	alterar = buscaPlaca(*rootAntigoPadrao,placaS);
	if(alterar)
	{
		strcpy(v.placa,alterar->veiculo->placa);
		strcpy(v.renavam,alterar->veiculo->renavam);
		strcpy(v.marca,alterar->veiculo->marca);
		strcpy(v.modelo,alterar->veiculo->modelo);
		v.ano = alterar->veiculo->ano;
		strcpy(v.cor,alterar->veiculo->cor);
		retorno = comparaCategoria(alterar->veiculo->categoria);
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
			strcpy(v.categoria,alterar->veiculo->categoria);
		}
		strcpy(v.estado,alterar->veiculo->estado);
		strcpy(v.cidade,alterar->veiculo->cidade);
		
		*rootAntigoPadrao = remover_veiculo(*rootAntigoPadrao, v.placa);
		
		v.placa[4] = v.placa[4] + 17;
		
		*rootNovoPadrao = inserir_veiculo(*rootNovoPadrao,v);
		
		novo = buscaPlaca(*rootNovoPadrao, v.placa);
		return novo;
	}
	else
		return novo;
}

void relatorio_anos(Node *root, int anoInicial, int anoFinal)
{
	int i;
	Node* temp;

	if (!root)
		return;
	temp = root;
	if(temp && temp->veiculo && temp->veiculo->ano >= anoInicial && temp->veiculo->ano <= anoFinal)
	{
		printf("%s;%s;%s;%s;%d;%s;%s;%s;%s;\n",
				temp->veiculo->placa,
				temp->veiculo->renavam,
				temp->veiculo->marca,
				temp->veiculo->modelo,
				temp->veiculo->ano,
				temp->veiculo->cor,
				temp->veiculo->categoria,
				temp->veiculo->estado,
				temp->veiculo->cidade);
	}
			
	for (i=0; i<N; i++) {
		relatorio_anos(temp->children[i], anoInicial, anoFinal); 
	}

}

void relatorio_intervaloAnos(Node *rootAntigoPadrao, Node *rootNovoPadrao, int anoInicial, int anoFinal)
{
	relatorio_anos(rootAntigoPadrao, anoInicial, anoFinal);
	
	relatorio_anos(rootNovoPadrao, anoInicial, anoFinal);
}

void relatorio_estado(Node *root, char estado[3], char finalP)
{
	int i;
	Node* temp;

	if (!root)
		return;
	temp = root;
	if(temp && temp->veiculo && strcmp(temp->veiculo->estado,estado)==0 && temp->veiculo->placa[6] == finalP)
	{
		printf("%s;%s;%s;%s;%d;%s;%s;%s;%s;\n",
				temp->veiculo->placa,
				temp->veiculo->renavam,
				temp->veiculo->marca,
				temp->veiculo->modelo,
				temp->veiculo->ano,
				temp->veiculo->cor,
				temp->veiculo->categoria,
				temp->veiculo->estado,
				temp->veiculo->cidade);
	}
			
	for (i=0; i<N; i++) {
		relatorio_estado(temp->children[i], estado, finalP); 
	}

}

void relatorio_porEstado(Node *rootAntigoPadrao, Node *rootNovoPadrao, char estado[3])
{
	char finalP = '0';
	int i=0;
	
	while(finalP<='9')
	{
		relatorio_estado(rootAntigoPadrao, estado, finalP);
		
		relatorio_estado(rootNovoPadrao, estado, finalP);
		
		i++;
		finalP = '0' + i;
	}	
	
}

void imprimir_veiculos(Node *root) 
{
	/* Prints the nodes of the trie */
	int i;
	Node* temp;

	if (!root)
		return;
	temp = root;
	if(temp->veiculo)
	{
		printf("%s;%s;%s;%s;%d;%s;%s;%s;%s;\n",
				temp->veiculo->placa,
				temp->veiculo->renavam,
				temp->veiculo->marca,
				temp->veiculo->modelo,
				temp->veiculo->ano,
				temp->veiculo->cor,
				temp->veiculo->categoria,
				temp->veiculo->estado,
				temp->veiculo->cidade);
	}		
	for (i=0; i<N; i++) {
		imprimir_veiculos(temp->children[i]); 
	}
}


void free_trienode(Node* node) {
    /* Free the trienode sequence */
    int i;
    
    for(i=0; i<N; i++) {
        if (node->children[i] != NULL) {
            free_trienode(node->children[i]);
        }
        else {
            continue;
        }
    }
    free(node);
}


int quantidade_veiculos(Node *root)
{
	int i, qtd = 0;
	Node* temp;

	if (!root)
		return 0;
	temp = root;
	if(temp->veiculo)
	{
		qtd++;
	}		
	for (i=0; i<N; i++) {
		if(temp->children[i])
			qtd =  quantidade_veiculos(temp->children[i]) + qtd; 
	}
	return qtd;
}
