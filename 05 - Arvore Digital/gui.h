

#ifndef GUI_H
#define GUI_H
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvore_digital.h"
#include <time.h>

extern GtkBuilder *builder;
extern GtkWidget *window;
extern GtkStack *stack;
extern GtkListStore *modelo_armazenamento;

typedef struct{
	Node **rootAnt;
	Node **rootNov;
}mystruct;

void mensagem(char text[100], char secondary_text[100]);

void on_main_window_destroy(GtkWidget *widget, gpointer data);

void on_button_buscar_clicked(GtkWidget *widget, gpointer data);

void on_button_alterar_placa_clicked(GtkWidget *widget, gpointer data);

void on_buton_relatorio_clicked(GtkWidget *widget, gpointer data);

void on_button_buscar_volta_clicked(GtkWidget *widget, gpointer data);

void on_button_buscar_procurar_clicked(GtkWidget *widget, gpointer data);

void on_button_alterar_voltar_clicked(GtkWidget *widget, gpointer data);

void on_button_alterar_clicked(GtkWidget *widget, gpointer data);

void on_button_relatorio_voltar_clicked(GtkWidget *widget, gpointer data);

int relatorio_anos_gui(Node *root, int anoInicial, int anoFinal, GtkListStore *model, GtkTreeIter *iter);

void on_button_relatorio_anos_clicked(GtkWidget *widget, gpointer data);

int relatorio_estado_gui(Node *root, const char *estado, char finalP, GtkListStore *model, GtkTreeIter *iter);

void on_button_relatorio_estado_clicked(GtkWidget *widget, gpointer data);

#endif
