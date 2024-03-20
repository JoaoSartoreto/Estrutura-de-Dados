#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_digital.h"
#include "arquivos.h"
#include "gui.h"

/*
Compilação: gcc -o main.exe *.c `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
*/

GtkBuilder *builder;
GtkWidget *window;
GtkStack *stack;
GtkLabel *lab;

int main(int argc, char *argv[])
{
	Node *rootAntigoPadrao, *rootNovoPadrao, *altera1, *altera2;
	int qtd;
	mystruct estrutura;
	struct timespec tstart={0,0}, tend={0,0};
	clock_gettime(CLOCK_MONOTONIC, &tstart);
	char tempo[50];
	
	rootAntigoPadrao = make_trienode('\0',NULL);
	rootNovoPadrao = make_trienode('\0',NULL);
	

	
	carregamento_arquivo(argc, argv, &rootAntigoPadrao, &rootNovoPadrao);
	estrutura.rootAnt = &rootAntigoPadrao;
	estrutura.rootNov = &rootNovoPadrao;
	
	clock_gettime(CLOCK_MONOTONIC, &tend);
	sprintf(tempo, "Tempo de Carregamento: %.5f segundos",((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) 
		- ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
	
	gtk_init(&argc, &argv);
	builder = gtk_builder_new_from_file("gui.glade");
	
	gtk_builder_add_callback_symbols(
        builder,
        "on_main_window_destroy", G_CALLBACK(on_main_window_destroy),
        "on_button_buscar_clicked", G_CALLBACK(on_button_buscar_clicked),
        "on_button_alterar_placa_clicked", G_CALLBACK(on_button_alterar_placa_clicked),
        "on_buton_relatorio_clicked", G_CALLBACK(on_buton_relatorio_clicked),
        "on_button_buscar_volta_clicked", G_CALLBACK(on_button_buscar_volta_clicked),
        "on_button_buscar_procurar_clicked", G_CALLBACK(on_button_buscar_procurar_clicked),
        "on_button_alterar_voltar_clicked", G_CALLBACK(on_button_alterar_voltar_clicked),
        "on_button_alterar_clicked", G_CALLBACK(on_button_alterar_clicked),
        "on_button_relatorio_voltar_clicked", G_CALLBACK(on_button_relatorio_voltar_clicked),
        "on_button_relatorio_anos_clicked", G_CALLBACK(on_button_relatorio_anos_clicked),
        "on_button_relatorio_estado_clicked", G_CALLBACK(on_button_relatorio_estado_clicked),
        NULL);
	
	
	
	gtk_builder_connect_signals(builder, &estrutura);


	stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));
	window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
	lab = GTK_LABEL(gtk_builder_get_object(builder, "labelC"));
	gtk_label_set_text(lab, (const gchar*) tempo);
	
	gtk_widget_show_all(window);
	
	
	
	gtk_main();
	
	qtd = quantidade_veiculos(rootAntigoPadrao);
	printf("Quantidade veiculos no antigo padrao: %d\n",qtd);
	qtd = quantidade_veiculos(rootNovoPadrao);
	printf("Quantidade veiculos no novo padrao: %d\n",qtd);
	
	gravacaoBinario(&rootAntigoPadrao, &rootNovoPadrao);

	free_trienode(rootAntigoPadrao);
	free_trienode(rootNovoPadrao);

	return 0;
}
