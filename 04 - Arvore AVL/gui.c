#include "gui.h"


void mensagem(char titulo[], char msg[])
{
    GtkWidget *message_dialog = GTK_WIDGET(gtk_builder_get_object(builder, "mensagem"));
    g_object_set(message_dialog, "text", titulo, "secondary_text", msg, NULL);

    gtk_widget_show(message_dialog);
    gtk_dialog_run(GTK_DIALOG(message_dialog));
    gtk_widget_hide(message_dialog);
}



void on_main_window_destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}


void on_button_buscar_clicked(GtkWidget *widget, gpointer data)
{
	
	GtkEntry *input = GTK_ENTRY(gtk_builder_get_object(builder, "placa_buscar"));
	GtkLabel *lab = GTK_LABEL(gtk_builder_get_object(builder, "labelB"));
	/* limpa o GtkEntry antes de mostrar a tela */
	g_object_set(input, "text", "", NULL);
	gtk_label_set_text(lab, (const gchar*) "Tempo: ");

	gtk_stack_set_visible_child_name(stack,"view_buscar");
}

void on_button_alterar_placa_clicked(GtkWidget *widget, gpointer data)
{
	
	GtkEntry *input = GTK_ENTRY(gtk_builder_get_object(builder, "placa_alterar"));
	GtkLabel *lab = GTK_LABEL(gtk_builder_get_object(builder, "labelA"));
	/* limpa o GtkEntry antes de mostrar a tela */
	g_object_set(input, "text", "", NULL);
	gtk_label_set_text(lab, (const gchar*) "Tempo: ");

	gtk_stack_set_visible_child_name(stack,"view_alterar_placa");
}

void on_buton_relatorio_clicked(GtkWidget *widget, gpointer data)
{

	gtk_stack_set_visible_child_name(stack,"view_relatorio");
	
}

void on_button_buscar_volta_clicked(GtkWidget *widget, gpointer data)
{
	gtk_stack_set_visible_child_name(stack,"view_inicial");
}

void on_button_buscar_procurar_clicked(GtkWidget *widget, gpointer data)
{
	mystruct *info = data;
	Node *buscar;
	int valido = 0;
	struct timespec tstart={0,0}, tend={0,0};
	clock_gettime(CLOCK_MONOTONIC, &tstart);
	char tempo[50];
	
	
	GtkEntry *input = GTK_ENTRY(gtk_builder_get_object(builder, "placa_buscar"));
	GtkLabel *lab = GTK_LABEL(gtk_builder_get_object(builder, "labelB"));
	
	const char *placa = gtk_entry_get_text(input);
	if(placa[4]>='0' && placa[4]<='9')
		valido = 1;
	
	
	buscar = procurar_veiculo((*info->rootAnt), (*info->rootNov), placa);
	
	if(buscar)
	{
		clock_gettime(CLOCK_MONOTONIC, &tend);
		sprintf(tempo, "Tempo: %ld nano segundos",(tend.tv_nsec) - (tstart.tv_nsec));
		gtk_label_set_text(lab, (const gchar*) tempo);
		
			if((valido == 1) && (buscar->veiculo.placa[4]>='A' && buscar->veiculo.placa[4]<='Z'))
			{
				char mensagem_secundaria[500];
				char mensagem_primaria[500];
				sprintf(mensagem_secundaria, "Placa: %s,\nRenavam: %s,\nMarca: %s,\nModelo: %s,\nAno %d,\nCor: %s,\nCategoria: %s,\nEstado: %s,\nCidade: %s",
					buscar->veiculo.placa,buscar->veiculo.renavam,buscar->veiculo.marca,
					buscar->veiculo.modelo,buscar->veiculo.ano,buscar->veiculo.cor,
					buscar->veiculo.categoria,buscar->veiculo.estado,buscar->veiculo.cidade);
				sprintf(mensagem_primaria,"Placa encontrada, ela ja foi atualizada para o novo padrão!");
				
				mensagem(mensagem_primaria,mensagem_secundaria);
			}
			else
			{
				char mensagem_secundaria[500];
				char mensagem_primaria[500];
				sprintf(mensagem_secundaria, "Placa: %s,\nRenavam: %s,\nMarca: %s,\nModelo: %s,\nAno %d,\nCor: %s,\nCategoria: %s,\nEstado: %s,\nCidade: %s",
					buscar->veiculo.placa,buscar->veiculo.renavam,buscar->veiculo.marca,
					buscar->veiculo.modelo,buscar->veiculo.ano,buscar->veiculo.cor,
					buscar->veiculo.categoria,buscar->veiculo.estado,buscar->veiculo.cidade);
				sprintf(mensagem_primaria,"Placa encontrada");
				
				mensagem(mensagem_primaria,mensagem_secundaria);
			}
	}
	else
	{
		clock_gettime(CLOCK_MONOTONIC, &tend);
		sprintf(tempo, "Tempo: %ld nano",(tend.tv_nsec) - (tstart.tv_nsec));
		gtk_label_set_text(lab, (const gchar*) tempo);
		
		char mensagem_secundaria[500];
		char mensagem_primaria[500];
		sprintf(mensagem_secundaria, "Placa não encontrada na base de dados!");
		sprintf(mensagem_primaria,"Sinto muito.");
		
		mensagem(mensagem_primaria,mensagem_secundaria);
	}
	
	g_object_set(input, "text", "", NULL);
}

void on_button_alterar_voltar_clicked(GtkWidget *widget, gpointer data)
{
	gtk_stack_set_visible_child_name(stack,"view_inicial");
}

void on_button_alterar_clicked(GtkWidget *widget, gpointer data)
{
	mystruct *info = data;
	Node *alterar;
	struct timespec tstart={0,0}, tend={0,0};
	clock_gettime(CLOCK_MONOTONIC, &tstart);
	char tempo[50];
	
	GtkEntry *input = GTK_ENTRY(gtk_builder_get_object(builder, "placa_alterar"));
	GtkLabel *lab = GTK_LABEL(gtk_builder_get_object(builder, "labelA"));
	
	const char *placa = gtk_entry_get_text(input);
	alterar = alterarPlaca(info->rootAnt, info->rootNov, placa);
	if(alterar)
	{
		clock_gettime(CLOCK_MONOTONIC, &tend);	
		sprintf(tempo, "Tempo: %ld nano segundos",(tend.tv_nsec) - (tstart.tv_nsec));
		gtk_label_set_text(lab, (const gchar*) tempo);
			
		char mensagem_secundaria[500];
		char mensagem_primaria[500];
		sprintf(mensagem_secundaria, "Placa: %s,\nRenavam: %s,\nMarca: %s,\nModelo: %s,\nAno %d,\nCor: %s,\nCategoria: %s,\nEstado: %s,\nCidade: %s",
					alterar->veiculo.placa,alterar->veiculo.renavam,alterar->veiculo.marca,
					alterar->veiculo.modelo,alterar->veiculo.ano,alterar->veiculo.cor,
					alterar->veiculo.categoria,alterar->veiculo.estado,alterar->veiculo.cidade);
		sprintf(mensagem_primaria,"Placa alterada com sucesso!");
				
		mensagem(mensagem_primaria,mensagem_secundaria);
		
		GtkTreeView *view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "tv1"));
		GtkTreeModel *model = gtk_tree_view_get_model(view);
		GtkTreeIter iter;
		g_object_ref(model); /* Make sure the model stays with us after the tree view unrefs it */
		gtk_tree_view_set_model(GTK_TREE_VIEW(view), NULL); /* Detach model from view */
		gtk_list_store_clear(GTK_LIST_STORE(model));
		
		gtk_tree_view_set_model(GTK_TREE_VIEW(view), model); /* Re-attach model to view */
		g_object_unref(model);	
	}
	else
	{
		clock_gettime(CLOCK_MONOTONIC, &tend);
		sprintf(tempo, "Tempo: %ld nano",(tend.tv_nsec) - (tstart.tv_nsec));
		gtk_label_set_text(lab, (const gchar*) tempo);
	
		char mensagem_secundaria[500];
		char mensagem_primaria[500];
		sprintf(mensagem_secundaria, "Placa não encontrada na base de dados!");
		sprintf(mensagem_primaria,"Sinto muito.");
		
		mensagem(mensagem_primaria,mensagem_secundaria);
	}
	
	g_object_set(input, "text", "", NULL);
	
}

void on_button_relatorio_voltar_clicked(GtkWidget *widget, gpointer data)
{
	gtk_stack_set_visible_child_name(stack,"view_inicial");
	
	GtkEntry *input1 = GTK_ENTRY(gtk_builder_get_object(builder, "relatorio_ano_inicio"));
	GtkEntry *input2 = GTK_ENTRY(gtk_builder_get_object(builder, "relatorio_ano_fim"));
	GtkEntry *input = GTK_ENTRY(gtk_builder_get_object(builder, "relatorio_estado"));
	GtkLabel *lab = GTK_LABEL(gtk_builder_get_object(builder, "labelA"));
	
	g_object_set(input1, "text", "", NULL);
	g_object_set(input2, "text", "", NULL);
	g_object_set(input, "text", "", NULL);
	gtk_label_set_text(lab, (const gchar*) "Tempo: ");
}

int relatorio_anos_gui(Node *root, int anoInicial, int anoFinal, GtkListStore *model, GtkTreeIter *iter)
{
	int m1 = 0;

	if(root)
		m1 = m1 + relatorio_anos_gui(root->left_child, anoInicial, anoFinal, model, iter);
	
	if(root && root->veiculo.ano >= anoInicial && root->veiculo.ano <= anoFinal)
	{
		gtk_list_store_append(model, iter);
		gtk_list_store_set(model, iter,
			0, root->veiculo.placa,
			1, root->veiculo.renavam,
			2, root->veiculo.marca,
			3, root->veiculo.modelo,
			4, root->veiculo.ano,
			5, root->veiculo.cor,
			6, root->veiculo.categoria,
			7, root->veiculo.estado,
			8, root->veiculo.cidade,
			-1);
			m1++;
	}
			
	if(root)
		m1 = m1 + relatorio_anos_gui(root->right_child, anoInicial, anoFinal, model, iter);
		
	return m1;

}

void on_button_relatorio_anos_clicked(GtkWidget *widget, gpointer data)
{
	int anoInicio, anoFim, i=1, qtd = 0;
	struct timespec tstart={0,0}, tend={0,0};
    	clock_gettime(CLOCK_MONOTONIC, &tstart);
    	char tempo[50];
	mystruct *info = data;
	GtkTreeView *view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "tv1"));
	GtkTreeModel *model = gtk_tree_view_get_model(view);
	GtkTreeIter iter;
	g_object_ref(model); /* Make sure the model stays with us after the tree view unrefs it */
	gtk_tree_view_set_model(GTK_TREE_VIEW(view), NULL); /* Detach model from view */
	gtk_list_store_clear(GTK_LIST_STORE(model));
	
	GtkEntry *input1 = GTK_ENTRY(gtk_builder_get_object(builder, "relatorio_ano_inicio"));
	anoInicio = atoi(gtk_entry_get_text(input1));
	
	GtkEntry *input2 = GTK_ENTRY(gtk_builder_get_object(builder, "relatorio_ano_fim"));
	anoFim = atoi(gtk_entry_get_text(input2));
	
	GtkLabel *lab = GTK_LABEL(gtk_builder_get_object(builder, "labelR"));
	
	

	qtd = qtd + relatorio_anos_gui((*info->rootAnt), anoInicio, anoFim, GTK_LIST_STORE(model), &iter);
	qtd = qtd + relatorio_anos_gui((*info->rootNov), anoInicio, anoFim, GTK_LIST_STORE(model), &iter);
	
	clock_gettime(CLOCK_MONOTONIC, &tend);
	sprintf(tempo, "Tempo: %.5f segundos",((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
	gtk_label_set_text(lab, (const gchar*) tempo);
	
	if(qtd == 0)
	{
		char mensagem_secundaria[500];
		char mensagem_primaria[500];
		sprintf(mensagem_secundaria, "Nenhum veiculo encontrado na base de dados!");
		sprintf(mensagem_primaria,"Sinto muito.");
		
		mensagem(mensagem_primaria,mensagem_secundaria);
	}
	
	g_object_set(input1, "text", "", NULL);
	g_object_set(input2, "text", "", NULL);
	
	gtk_tree_view_set_model(GTK_TREE_VIEW(view), model); /* Re-attach model to view */
	g_object_unref(model);	
}

int relatorio_estado_gui(Node *root, const char *estado, char finalP, GtkListStore *model, GtkTreeIter *iter)
{
	int m1;
	m1 = 0;

	if(root)
		m1 = m1 + relatorio_estado_gui(root->left_child, estado, finalP, model, iter);
	
	if(root && strcmp(root->veiculo.estado,estado)==0 && root->veiculo.placa[6] == finalP)
	{
		gtk_list_store_append(model, iter);
		gtk_list_store_set(model, iter,
			0, root->veiculo.placa,
			1, root->veiculo.renavam,
			2, root->veiculo.marca,
			3, root->veiculo.modelo,
			4, root->veiculo.ano,
			5, root->veiculo.cor,
			6, root->veiculo.categoria,
			7, root->veiculo.estado,
			8, root->veiculo.cidade,
			-1);
			m1++;
	}
			
	if(root)
		m1 = m1 + relatorio_estado_gui(root->right_child, estado, finalP, model, iter);
	
	return m1;

}

void on_button_relatorio_estado_clicked(GtkWidget *widget, gpointer data)
{
	mystruct *info = data;
	GtkTreeView *view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "tv1"));
	GtkTreeModel *model = gtk_tree_view_get_model(view);
	GtkTreeIter iter;
	g_object_ref(model); /* Make sure the model stays with us after the tree view unrefs it */
	gtk_tree_view_set_model(GTK_TREE_VIEW(view), NULL); /* Detach model from view */
	gtk_list_store_clear(GTK_LIST_STORE(model));
	struct timespec tstart={0,0}, tend={0,0};
    	clock_gettime(CLOCK_MONOTONIC, &tstart);
    	char tempo[50];
	
	GtkEntry *input = GTK_ENTRY(gtk_builder_get_object(builder, "relatorio_estado"));
	GtkLabel *lab = GTK_LABEL(gtk_builder_get_object(builder, "labelR"));
	const char *estado = gtk_entry_get_text(input);
	char finalP = '0';
	int i=0,  qtd = 0;
	
	
	
	while(finalP<='9')
	{
		qtd = qtd + relatorio_estado_gui((*info->rootAnt), estado, finalP, GTK_LIST_STORE(model), &iter);
		qtd = qtd + relatorio_estado_gui((*info->rootNov), estado, finalP, GTK_LIST_STORE(model), &iter);
		
		i++;
		finalP = '0' + i;
	}
	clock_gettime(CLOCK_MONOTONIC, &tend);
	sprintf(tempo, "Tempo: %.5f segundos",((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
	
	gtk_label_set_text(lab, (const gchar*) tempo);
	if(qtd == 0)
	{
		char mensagem_secundaria[500];
		char mensagem_primaria[500];
		sprintf(mensagem_secundaria, "Nenhum veiculo encontrado na base de dados!");
		sprintf(mensagem_primaria,"Sinto muito.");
		
		mensagem(mensagem_primaria,mensagem_secundaria);
	}

	
	g_object_set(input, "text", "", NULL);
	
	gtk_tree_view_set_model(GTK_TREE_VIEW(view), model); /* Re-attach model to view */
	g_object_unref(model);	

}
