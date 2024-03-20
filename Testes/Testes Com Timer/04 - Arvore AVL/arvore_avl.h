#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	char placa[8];
	char renavam[12];
	char marca[16];
	char modelo[46];
	int ano;
	char cor[10];
	char categoria[35];
	char estado[3];
	char cidade [27];

}Veiculo;

typedef struct node{
	Veiculo veiculo;
	struct node *left_child;
	struct node *right_child;
	int altura;
}Node;

int maior(int a, int b);

int alturaNode(Node *node);

short fatorDeBalanceamento(Node *node);

Node* rotacaoEsquerda(Node *r);

Node* rotacaoDireita(Node *r);

Node* rotacaoEsquerdaDireita(Node *r);

Node* rotacaoDireitaEsquerda(Node *r);

Node* balancear(Node *raiz);

Node *new_node(Veiculo v);

Node* inserir_veiculo(Node* node, Veiculo v);

Node* maxValueNode(Node* no);

Node* remover_veiculo(Node* node, char placa[]);

Node *buscaPlaca(Node *binary_tree, char placa[]);

Node* procurar_veiculo(Node *rootAntigoPadrao, Node *rootNovoPadrao, char placa[]);

Node* buscaVeiculo(Node *rootAntigoPadrao, Node *rootNovoPadrao, char placa[]);

void imprimir_veiculos(Node *binary_tree);

void delete_tree(Node *binary_tree);

int quantidade_de_veiculos(Node *root);

int comparaCategoria(char categoriaAnt[]);

Node* alterarPlaca(Node **rootAntigoPadrao, Node **rootNovoPadrao, char placa[]);

void relatorio_anos(Node *root, int anoInicial, int anoFinal);

void relatorio_intervaloAnos(Node *rootAntigoPadrao, Node *rootNovoPadrao, int anoInicial, int anoFinal);

void relatorio_estado(Node *root, char estado[3], char finalP);

void relatorio_porEstado(Node *rootAntigoPadrao, Node *rootNovoPadrao, char estado[3]);

#endif
