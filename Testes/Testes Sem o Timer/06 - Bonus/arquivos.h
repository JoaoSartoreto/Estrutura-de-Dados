#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_avl.h"
#include "hash.h"


void carregamentoERNV(Node *tabelaAntigoPadrao[], Node *tabelaNovoPadrao[], char *arquivo);

void carregamentoBinario(Node *tabelaAntigoPadrao[], Node *tabelaNovoPadrao[]);

void carregamento_arquivo(int argc, char *argv[], Node *tabelaAntigoPadrao[], Node *tabelaNovoPadrao[]);

void gravarTree(FILE *file, Node *root);

void gravacaoBinario(Node *tabelaAntigoPadrao[], Node *tabelaNovoPadrao[]);

#endif
