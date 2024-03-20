
#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvore_avl.h"

#define TAM 17476

void inicializar_tabela(Node *tabela[TAM]);

int valor_caractere(char c);

int funcao_hash(char placa[]);

void insere_tabela(Node *tabela[], Veiculo v);

int comparaCategoria(char categoriaAnt[]);

Node* procurar_veiculo(Node *tabelaAntigoPadrao[], Node *tabelaNovoPadrao[], char placa[]);

Node* alterarPlaca(Node *tabelaAntigoPadrao[], Node *tabelaNovoPadrao[], char placa[]);

void relatorio_intervaloAnos(Node *tabelaAntigoPadrao[], Node *tabelaNovoPadrao[], int anoInicial, int anoFinal);

void relatorio_porEstado(Node *tabelaAntigoPadrao[], Node *tabelaNovoPadrao[], char estado[3]);

void imprimir_tabela(Node *tabela[]);

void deleta_tabela(Node *tabela[TAM]);

#endif
