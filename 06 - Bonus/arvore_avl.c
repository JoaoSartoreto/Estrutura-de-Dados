#include "arvore_avl.h"

/*
    Função que cria um novo nó
    x -> valor a ser inserido no nó
    Retorna: o endereço do nó criado
*/
Node *new_node(Veiculo v)
{
	Node *novo = (Node *)malloc(sizeof(Node));
	
	if(novo)
	{
		novo->veiculo = v;
		novo->left_child = NULL;
		novo->right_child = NULL;
		novo->altura = 1;	
		
		return novo;
	}
	
	return NULL;
}

/*
    Retorna o maior dentre dois valores
    a, b -> altura de dois nós da árvore
*/
int maior(int a, int b)
{
	return (a > b)? a: b;
}

/*  Retorna a altura de um nó ou -1 caso ele seja null */
int alturaNode(Node *node)
{
	if(node == NULL)
	        return 0;
	else
		return node->altura;
}

short fatorDeBalanceamento(Node *node)
{
	if(node)
	        return (alturaNode(node->right_child) - alturaNode(node->left_child));
	else
        	return 0;
}

/* --------- ROTAÇÕES --------------------------- */

/* função para a rotação à esquerda */
Node* rotacaoEsquerda(Node *r)
{
	Node *y, *f;

    	y = r->right_child;
    	f = y->left_child;

    	y->left_child = r;
    	r->right_child = f;

    	r->altura = maior(alturaNode(r->left_child), alturaNode(r->right_child)) + 1;
    	y->altura = maior(alturaNode(y->left_child), alturaNode(y->right_child)) + 1;

    	return y;
}

/* função para a rotação à direita */
Node* rotacaoDireita(Node *r)
{
	Node *y, *f;

    	y = r->left_child;
    	f = y->right_child;

    	y->right_child = r;
    	r->left_child = f;

    	r->altura = maior(alturaNode(r->left_child), alturaNode(r->right_child)) + 1;
    	y->altura = maior(alturaNode(y->left_child), alturaNode(y->right_child)) + 1;

    	return y;
}

Node* rotacaoEsquerdaDireita(Node *r)
{
	r->left_child = rotacaoEsquerda(r->left_child);
	return rotacaoDireita(r);
}

Node* rotacaoDireitaEsquerda(Node *r)
{
	r->right_child = rotacaoDireita(r->right_child);
	return rotacaoEsquerda(r);
}

/*
    Função para realizar o balanceamento da árvore após uma inserção ou remoção
    Recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento
*/
Node* balancear(Node *node)
{
	short fb = fatorDeBalanceamento(node);

    	/* Rotação à esquerda */
    	if(fb > 1 && fatorDeBalanceamento(node->right_child) >= 0)
        	node = rotacaoEsquerda(node);

    	/* Rotação à direita */
    	else if(fb < -1 && fatorDeBalanceamento(node->left_child) <= 0)
        	node = rotacaoDireita(node);

    	/* Rotação dupla à esquerda */
    	else if(fb < -1 && fatorDeBalanceamento(node->left_child) > 0)
        	node = rotacaoEsquerdaDireita(node);

    	/* Rotação dupla à direita */
    	else if(fb > 1 && fatorDeBalanceamento(node->right_child) < 0)
        	node = rotacaoDireitaEsquerda(node);

    	return node;
}

/*
    Insere um novo nó na árvore
    raiz -> raiz da árvore
    x -> valor a ser inserido
    Retorno: endereço do novo nó ou nova raiz após o balanceamento
*/
Node* inserir_veiculo(Node *node, Veiculo v)
{
	Node *novo;

	if(node == NULL){ /* árvore vazia */
		novo = new_node(v);
		if(novo)
			return novo;
		else
			printf("Falha ao tentar alocar memória para a placa: %s\n",v.placa);
		return NULL;
	}
	else
	{ /* inserção será à esquerda ou à direita */
		if(strcmp(v.placa, node->veiculo.placa) < 0)
			node->left_child = inserir_veiculo(node->left_child, v);
		else if(strcmp(v.placa, node->veiculo.placa) > 0)
			node->right_child = inserir_veiculo(node->right_child, v);
	}

    	/* Recalcula a altura de todos os nós entre a raiz e o novo nó inserido */
	node->altura = maior(alturaNode(node->left_child), alturaNode(node->right_child)) + 1;

    	/* verifica a necessidade de rebalancear a árvore */
    	node = balancear(node);

    	return node;
}

/*
    Função para remover um nó da Árvore binária balanceada
    Pode ser necessário rebalancear a árvore e a raiz pode ser alterada
    por isso precisamos retornar a raiz
*/
Node* remover_veiculo(Node *node, char placa[]) {
	if(node == NULL){
	        return NULL;
	}else 
	{ /* procura o nó a remover */
        	if(strcmp(placa, node->veiculo.placa)==0) 
        	{
            	/* remove nós folhas (nós sem filhos) */
            		if(node->left_child == NULL && node->right_child == NULL) 
            		{
                		free(node);
                		return NULL;
            		}
            			else
            			{
					/* remover nós que possuem 2 filhos */
					if(node->left_child != NULL && node->right_child != NULL)
					{
						Node *aux = node->left_child;
						while(aux->right_child != NULL)
							aux = aux->right_child;
					    	node->veiculo = aux->veiculo;
					    	node->left_child = remover_veiculo(node->left_child, aux->veiculo.placa);
					    	return node;
					}
					else
					{
						/* remover nós que possuem apenas 1 filho */
						Node *aux;
						if(node->left_child != NULL)
							aux = node->left_child;
					    	else
							aux = node->right_child;
					    	free(node);
					    	return aux;
					}
				}
			}
			else 
			{
				if(strcmp(placa, node->veiculo.placa) < 0)
					node->left_child = remover_veiculo(node->left_child, placa);
			    	else
					node->right_child = remover_veiculo(node->right_child, placa);
			}

			/* Recalcula a altura de todos os nós entre a raiz e o novo nó inserido */
			node->altura = maior(alturaNode(node->left_child), alturaNode(node->right_child)) + 1;

			/* verifica a necessidade de rebalancear a árvore */
			node = balancear(node);

			return node;
	}
}



Node *buscaPlaca(Node *binary_tree, char placa[]) 
{
	if(!binary_tree) 
	{
		return NULL;
	}
	
	if(strcmp(placa, binary_tree->veiculo.placa)==0) 
	{
		return binary_tree;
	} 
	else if(strcmp(placa, binary_tree->veiculo.placa) < 0) 
	{
		return buscaPlaca(binary_tree->left_child, placa);
	} 
	else if(strcmp(placa, binary_tree->veiculo.placa) > 0)
	{
		return buscaPlaca(binary_tree->right_child, placa);
	}
	return NULL;
}



void relatorio_anos(Node *root, int anoInicial, int anoFinal)
{
	
	if(root)
		relatorio_anos(root->left_child, anoInicial, anoFinal);
		
	if(root && root->veiculo.ano >= anoInicial && root->veiculo.ano <= anoFinal)
	{
		printf("%s;%s;%s;%s;%d;%s;%s;%s;%s;\n",
			root->veiculo.placa,
			root->veiculo.renavam,
			root->veiculo.marca,
			root->veiculo.modelo,
			root->veiculo.ano,
			root->veiculo.cor,
			root->veiculo.categoria,
			root->veiculo.estado,
			root->veiculo.cidade);
	}
	
	if(root)
		relatorio_anos(root->right_child, anoInicial, anoFinal);

}

void relatorio_estado(Node *root, char estado[3], char finalP)
{
	if(root)
		relatorio_estado(root->left_child, estado, finalP);

	if(root && strcmp(root->veiculo.estado,estado)==0 && root->veiculo.placa[6] == finalP)
	{
		printf("%s;%s;%s;%s;%d;%s;%s;%s;%s;\n",
			root->veiculo.placa,
			root->veiculo.renavam,
			root->veiculo.marca,
			root->veiculo.modelo,
			root->veiculo.ano,
			root->veiculo.cor,
			root->veiculo.categoria,
			root->veiculo.estado,
			root->veiculo.cidade);
		
	}
	
	if(root)
		relatorio_estado(root->right_child, estado, finalP);
}

void imprimir_veiculos(Node *binary_tree) 
{
	if(binary_tree) 
	{
		imprimir_veiculos(binary_tree->left_child);
		printf("%s;%s;%s;%s;%d;%s;%s;%s;%s;\n",
			binary_tree->veiculo.placa,
			binary_tree->veiculo.renavam,
			binary_tree->veiculo.marca,
			binary_tree->veiculo.modelo,
			binary_tree->veiculo.ano,
			binary_tree->veiculo.cor,
			binary_tree->veiculo.categoria,
			binary_tree->veiculo.estado,
			binary_tree->veiculo.cidade);
		imprimir_veiculos(binary_tree->right_child);
	}
}


void delete_tree(Node *binary_tree) 
{
	if(binary_tree) 
	{
		delete_tree(binary_tree->left_child);
		delete_tree(binary_tree->right_child);
		free(binary_tree);
	}
}

int quantidade_de_veiculos(Node *root)
{
	int quantidade;

	if(root == NULL)
		return 0;
	
	quantidade = quantidade_de_veiculos(root->left_child) + quantidade_de_veiculos(root->right_child) + 1;
	
	return quantidade;
}

