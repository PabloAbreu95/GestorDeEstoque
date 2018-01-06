#include <gtk/gtk.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include "reporEstoque.h"
//Criação das widgets
GtkWidget *janela;
GtkWidget *fixo;
GtkWidget *nomeLabel;
GtkWidget *nome;
GtkWidget *quantidadeLabel;
GtkWidget *quantidade;
GtkWidget *btnConfirmar;
GtkWidget *alerta;

void abrirReporEstoque(){
    //Janela
    janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(janela),"Repor estoque");
    gtk_window_set_default_size(GTK_WINDOW(janela), 300, 120);
    gtk_window_set_position(GTK_WINDOW(janela), GTK_WIN_POS_CENTER);
    //Fixo
    fixo = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(janela), fixo);

    //Nome
    nomeLabel = gtk_label_new("Nome");
    gtk_fixed_put(GTK_FIXED(fixo), nomeLabel, 20, 20);
    nome = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixo),nome,100,10);

    //Quantidade
    quantidadeLabel = gtk_label_new("Quantidade");
    gtk_fixed_put(GTK_FIXED(fixo), quantidadeLabel,20,55);
    quantidade = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixo), quantidade, 100, 45);

    //Botão de confirmação
    btnConfirmar = gtk_button_new_with_label("Repor");
    gtk_fixed_put(GTK_FIXED(fixo),btnConfirmar,130,90);
    g_signal_connect (btnConfirmar, "clicked", G_CALLBACK (repor), NULL);

    //Callback pra destruir a janela e finalizar o programa
    g_signal_connect(G_OBJECT(janela), "destroy",
    G_CALLBACK(gtk_main_quit), NULL); //Fecha a janela
    gtk_widget_show_all(janela);
    gtk_main();
}
void repor(){
    const char *entry1, *entry2;
    int quantidadeInt; // Guarda o valor da entry2 como inteiro
    entry1 = gtk_entry_get_text (GTK_ENTRY(nome));
    entry2 = gtk_entry_get_text (GTK_ENTRY(quantidade));
    quantidade = atoi(entry2);
    reporProduto(entry1,quantidade);
    alerta = gtk_message_dialog_new(GTK_WINDOW(janela),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK, "Um item foi reposto");
        gtk_dialog_run(GTK_DIALOG(alerta));
        gtk_widget_destroy(alerta);
        gtk_widget_destroy(janela);
    
    
}
void reporProduto(char nomeDoProduto[], int quantidadeRepor){
    //Variaveis usadas para pegar dados do produto
    int quantidadeOficialDoProduto;
    //Variáveis que serão usadas para armazenar os dados coletados do arquivo de texto
    char idProduto[50],  nomeProduto[500],  fotoProduto[500], descricaoProduto[500], precoProduto[500], quantidadeProduto[500];
    //Pegando os dados necessários do arquivo de produtos
    FILE *fp;
    fp = fopen("produtos.txt","r");
    while(fscanf(fp, "%s %s %s %s %s %s",idProduto,nomeProduto,fotoProduto,descricaoProduto,precoProduto,quantidadeProduto)!=EOF){
        
        if(!strcmp(nomeProduto,nomeDoProduto)){ //Se o nome do produto for igual ao nome encontrado no arquivo
            quantidadeOficialDoProduto = atoi(quantidadeProduto);
        }
        
    }
    fclose(fp);
    quantidadeRepor = quantidadeRepor + quantidadeOficialDoProduto;
    
    FILE *fp2;
    fp2 = fopen("produtos.txt","w");
    fclose(fp2);

    //Modificação no banco de dados
    sqlite3 *db;
    char sql[500];
    sprintf(sql,"UPDATE produtos SET QUANTIDADE = %d WHERE NOME='%s'",quantidadeRepor,nomeDoProduto);
    sqlite3_open("banco.db", &db);
    sqlite3_exec(db, sql, retornoSelecionar, 0, 0);
    sqlite3_close(db);
    //Adiciona o repor estoques
    sqlite3_open("banco.db", &db);
    char sql2[500];
    char info[500] = "Um produto foi reposto";
    
    sprintf(sql2,"INSERT INTO logusuarios (INFO) VALUES ('%s')",info);
    sqlite3_exec(db, sql2, retornoSelecionar, 0, 0);
    sqlite3_close(db);
}

static int retornoSelecionar(void *data, int argc, char **argv, char **nomeColuna){
   int i;
   
   for(i = 0; i < argc; i++){
      printf("\n%s = %s", nomeColuna[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}