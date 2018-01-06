#include <gtk/gtk.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include "../../bancodedados/logusuarios/logusuario.h"
#include "relatorioUsuario.h"
//Criação das widgets
GtkWidget *janela;
GtkWidget *fixo;
GtkWidget *lista; //Lista que conterá os produtos
GtkTreeSelection *selecao;//Irá guardar a seleção
void abrirRelatorioUsuario(){
    gerarArquivoRelatorios();//Gera o arquivo com todos os relatorios
    //Janela
    janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(janela),"Relatório");
    gtk_window_set_default_size(GTK_WINDOW(janela), 500, 220);
    gtk_window_set_position(GTK_WINDOW(janela), GTK_WIN_POS_CENTER);

    //Fixo
    fixo = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(janela), fixo);

    //Lista
    lista = gtk_tree_view_new();
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(lista), FALSE);
    gtk_fixed_put(GTK_FIXED(fixo), lista, 0, 0);
    iniciarListaRelatorios(lista);




    //Pega os elementos do arquivo para montar a lista
    FILE *fp;
    fp = fopen("relatorios.txt","r");
    char info[500];
    while(!feof(fp)){
        fgets(info, 100, fp);	
        adicionarElementoNaListaRelatorio(lista,info); // joga o elemento na lista
        //Limpa as variaveis
        memset(info,'\0', 500);
    }
    fclose(fp);






    //Callback pra destruir a janela e finalizar o programa
    g_signal_connect(G_OBJECT(janela), "destroy",
    G_CALLBACK(gtk_main_quit), NULL); //Fecha a janela
    gtk_widget_show_all(janela);
    gtk_main();
}


//Criação da lista de relatorio 
void iniciarListaRelatorios(GtkWidget *lista){
    //Elementos necessários
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;

    //Criar uma célula
    renderer = gtk_cell_renderer_text_new();

    //Criamos um elemento coluna utilizando a célula criada
    column = gtk_tree_view_column_new_with_attributes("RELATORIOS", //Texto Coluna
                                                       renderer,//Celula
                                                        "text", //Tipo de celula
                                                        0,  //Coluna
                                                        NULL); //Indica o fim do atributo
    //Adicionamos a coluna ao elemento
    gtk_tree_view_append_column(GTK_TREE_VIEW(lista), column);

    //Criamos o modelo com uma coluna
    store = gtk_list_store_new(1, G_TYPE_STRING);

    //Estabelecemos o modelo
    gtk_tree_view_set_model(GTK_TREE_VIEW(lista), GTK_TREE_MODEL(store));

    g_object_unref(store);

}

void adicionarElementoNaListaRelatorio(GtkWidget *lista, const gchar *str){
    //Variaveis necessárias
    GtkListStore *store; //Modelo
    GtkTreeIter iter; //Item

    //Obtem o modelo
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(lista)));

    //Adiciona elemento utilizando o modelo
    gtk_list_store_append(store, //Modelo
                        &iter); //Item
    
    //Estabelece o dado na lista
    gtk_list_store_set(store,   //Modelo
                        &iter,  //item
                        0,      //Coluna
                        str, //Texto
                        -1);//Indica finalização
}
