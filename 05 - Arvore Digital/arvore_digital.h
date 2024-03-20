#ifndef ARVORE_DIGITAL_H
#define ARVORE_DIGITAL_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 66

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

/*
 The number of children for each node
 We will construct a N-ary tree and make it
 a Trie
 Since we have 26 english letters, we need
 26 children per node
*/


typedef struct node{
    /*
     The Trie Node Structure
     Each node has N children, starting from the root
     and a flag to check if it's a leaf node
    */
    Veiculo *veiculo;
    char data;
    struct node* children[N];
    int is_leaf;
}Node;

Node *make_trienode(char data, Veiculo *v);

int tabela_alfabeto(char a);

Node* inserir_veiculo(Node* root, Veiculo v);

int check_divergence(Node* root, char* word);

char* find_longest_prefix(Node* root, char* word);

int is_leaf_node(Node* root, char* word);

Node* remover_veiculo(Node* node, char placa[]);

Node *buscaPlaca(Node *root, char placa[]);

Node* procurar_veiculo(Node *rootAntigoPadrao, Node *rootNovoPadrao, const char *placa);

void imprimir_veiculos(Node *binary_tree);

void free_trienode(Node* node);

int comparaCategoria(char categoriaAnt[]);

Node* alterarPlaca(Node **rootAntigoPadrao, Node **rootNovoPadrao, const char *placa);

void relatorio_anos(Node *root, int anoInicial, int anoFinal);

void relatorio_intervaloAnos(Node *rootAntigoPadrao, Node *rootNovoPadrao, int anoInicial, int anoFinal);

void relatorio_estado(Node *root, char estado[3], char finalP);

void relatorio_porEstado(Node *rootAntigoPadrao, Node *rootNovoPadrao, char estado[3]);

int quantidade_veiculos(Node *root);

#endif
