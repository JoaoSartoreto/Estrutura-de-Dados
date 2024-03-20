

#ifndef GUI_H
#define GUI_H
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "hash.h"

extern GtkBuilder *builder;
extern GtkWidget *window;
extern GtkStack *stack;
extern GtkListStore *modelo_armazenamento;

typedef struct{
	No listaAnt[TAM];
	No listaNov[TAM];
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

void on_button_relatorio_anos_clicked(GtkWidget *widget, gpointer data);

void on_button_relatorio_estado_clicked(GtkWidget *widget, gpointer data);

#endif
