#include <gtk/gtk.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>
#include "../../bancodedados/produtos/produto.h"
#include "venderProduto.h"

//Criação das widgets
GtkWidget *janela;
GtkWidget *fixo;
GtkWidget *lista; //Lista que conterá os produtos
GtkTreeSelection *selecao;//Irá guardar a seleção

void abrirVenderProduto(int argc, char *argv[]){
    sqlite3 *db;
    gerarArquivoProdutos(db);
    gtk_init(&argc,&argv);//Inicia o gtk
    //Janela
    janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(janela),"Venda de produtos");
    gtk_window_set_default_size(GTK_WINDOW(janela), 300, 250);
    gtk_window_set_position(GTK_WINDOW(janela), GTK_WIN_POS_CENTER);
    //Fixo
    fixo = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(janela), fixo);
    //Lista
    lista = gtk_tree_view_new();
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(lista), FALSE);
    gtk_fixed_put(GTK_FIXED(fixo), lista, 0, 0);
    iniciarListaProdutos(lista);
    //Pega os elementos do arquivo para montar a lista
    FILE *fp;
    fp = fopen("produtos.txt","r");
    char id[500], nome[500],foto[500],descricao[500],preco[500],quantidade[500],elemento[500];
    while(fscanf(fp, "%s %s %s %s %s %s",id,nome,foto,descricao,preco,quantidade)!=EOF){
        strcat(elemento,quantidade);
        strcat(elemento," ");
        strcat(elemento,nome);
        strcat(elemento,"-");
        strcat(elemento," R$: ");
        strcat(elemento,preco);
        adicionarElementoNaLista(lista,elemento); // joga o elemento na lista
        //Limpa as variaveis
        memset(nome,'\0', 500);
        memset(preco,'\0', 500);
        memset(quantidade,'\0', 500);
        memset(elemento,'\0', 500);
    }
    fclose(fp);
    
  
   

    //Callback pra destruir a janela e finalizar o programa
    g_signal_connect(G_OBJECT(janela), "destroy",
    G_CALLBACK(gtk_main_quit), NULL); //Fecha a janela
    gtk_widget_show_all(janela);
    gtk_main();
    
}

void iniciarListaProdutos(GtkWidget *lista){
    //Elementos necessários
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;

    //Criar uma célula
    renderer = gtk_cell_renderer_text_new();

    //Criamos um elemento coluna utilizando a célula criada
    column = gtk_tree_view_column_new_with_attributes("PRODUTOS", //Texto Coluna
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

    //Não faço ideia
    g_object_unref(store);

}

void adicionarElementoNaLista(GtkWidget *lista, const gchar *str){
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
