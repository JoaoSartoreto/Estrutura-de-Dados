#include "arvorebb.h"

Node *new_node(Veiculo v)
{
	Node *novo = (Node *)malloc(sizeof(Node));
	
	if(novo)
	{
		novo->veiculo = v;
		novo->left_child = NULL;
		novo->right_child = NULL;	
		
		return novo;
	}
	
	return NULL;
}

Node* inserir_veiculo(Node* node, Veiculo v) /* inserting nodes!*/
{
	Node *novo;

	if (node == NULL) 
	{
		novo = new_node(v);
		if(novo)
			return novo;
		else
			printf("Falha ao tentar alocar memória para a placa: %s\n",v.placa);
		return NULL;
	}
	if (strcmp(v.placa, node->veiculo.placa) < 0)
	{
		node->left_child = inserir_veiculo(node->left_child, v);
	}
	else if (strcmp(v.placa, node->veiculo.placa) > 0)
	{
		node->right_child = inserir_veiculo(node->right_child, v);
	}
	return node;
}

Node* maxValueNode(Node* no)
{
    Node* current = no;
  
    /* loop down to find the leftmost leaf */
    while (current && current->right_child != NULL)
        current = current->right_child;
  
    return current;
}

Node* remover_veiculo(Node* root, char placa[])
{
	Node* temp;

    /* base case*/
    if (root == NULL)
        return root;
  
    /*
     If the key to be deleted 
     is smaller than the root's
     key, then it lies in left subtree
    */
    if (strcmp(placa, root->veiculo.placa) < 0)
        root->left_child = remover_veiculo(root->left_child, placa);
  
    /*
     If the key to be deleted 
     is greater than the root's
     key, then it lies in right subtree
    */
    else if (strcmp(placa, root->veiculo.placa) > 0)
        root->right_child = remover_veiculo(root->right_child, placa);
  
    /*
     if key is same as root's key, 
     then This is the node
     to be deleted
    */
    else {
        /* node with only one child or no child*/
        if (root->left_child == NULL) {
            temp = root->right_child;
            free(root);
            return temp;
        }
        else if (root->right_child == NULL) {
            temp = root->left_child;
            free(root);
            return temp;
        }
  
        /*
         node with two children: 
         Get the inorder successor
         (smallest in the right subtree)
        */
        temp = maxValueNode(root->left_child);
  
        /*
         Copy the inorder 
         successor's content to this node
        */
        root->veiculo = temp->veiculo;
  
        /* Delete the inorder successor*/
        root->left_child = remover_veiculo(root->left_child, temp->veiculo.placa);
    }
    return root;
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


Node* procurar_veiculo(Node *rootAntigoPadrao, Node *rootNovoPadrao, char placa[])
{
	Node *no = NULL;
	char placaS[8];
	strcpy(placaS, placa);
	
	if(placaS[4]>='A' && placa[4]<='Z')
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

Node* buscaVeiculo(Node *rootAntigoPadrao, Node *rootNovoPadrao, char placa[])
{
	Node *no = NULL;
	
	if(placa[4]>='A' && placa[4]<='Z')
	{
		no = buscaPlaca(rootNovoPadrao,placa);
	}
	else
	{
		no = buscaPlaca(rootAntigoPadrao,placa);
		if(no==NULL)
		{
			placa[4] = placa[4] + 17;
			no = buscaPlaca(rootNovoPadrao,placa);
			if(no)
			{
				printf("Placa encontrada, ela ja foi atualizada para o novo padrão!\n");
			}
			
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

Node* alterarPlaca(Node **rootAntigoPadrao, Node **rootNovoPadrao, char placa[])
{
	Node *alterar, *novo = NULL;
	Veiculo v;
	int retorno;
	
	alterar = buscaPlaca(*rootAntigoPadrao,placa);
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

void relatorio_intervaloAnos(Node *rootAntigoPadrao, Node *rootNovoPadrao, int anoInicial, int anoFinal)
{
	relatorio_anos(rootAntigoPadrao, anoInicial, anoFinal);
	
	relatorio_anos(rootNovoPadrao, anoInicial, anoFinal);
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

