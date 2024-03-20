#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvorebb.h"


void carregamentoERNV(Node **AntigoPadrao, Node **listaNovoPadrao, char *arquivo);

void carregamentoBinario(Node **rootAntigoPadrao, Node **rootNovoPadrao);

void carregamento_arquivo(int argc, char *argv[], Node **rootAntigoPadrao, Node **rootNovoPadrao);

void gravarTree(FILE *file, Node *root);

void gravacaoBinario(Node **rootAntigoPadrao, Node **rootNovoPadrao);

#endif
