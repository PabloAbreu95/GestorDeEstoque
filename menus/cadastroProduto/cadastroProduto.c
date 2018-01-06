#include <sqlite3.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "cadastroProduto.h"
#include "../../bancodedados/banco.h"
#include "../../bancodedados/logusuarios/logusuario.h"


//Criação das widgets
GtkWidget *janela;
GtkWidget *fixo;
GtkWidget *tituloLabel;
GtkWidget *nomeLabel;
GtkWidget *nome;
GtkWidget *descricaoLabel;
GtkWidget *descricao;
GtkWidget *precoLabel;
GtkWidget *preco;
GtkWidget *fotoLabel;
GtkWidget *foto; //Foto de no máximo 128x128;
GtkWidget *quantidadeLabel;
GtkWidget *quantidade;
GtkWidget *fotoBotao;
GtkWidget *salvarProduto;
const char *caminhoFotoProduto = "/";

LogUsuario novoLog;


static void procurarImagemProduto(GtkButton *button, GtkWindow *window){
    //Variaveis
    GtkWidget *dialog;
    gchar *filename;

    dialog = gtk_file_chooser_dialog_new ("Salvar arquivo em...",
                                        window,
                                        GTK_FILE_CHOOSER_ACTION_SAVE,
                                        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                        GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
                                        NULL);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_ACCEPT){
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        caminhoFotoProduto = filename;

        gtk_image_set_from_file (GTK_IMAGE (foto), filename);
    }
    if (result==GTK_RESPONSE_CANCEL){
        g_print("Cancelado");
    }
    gtk_widget_destroy(dialog);
    
}



void salvarProdutoNoBanco(){
    const char *nomeSPB, *descricaoSPB, *precofloat, *quantidadefloat;
    float p;
    int q;
    sqlite3 *db;
    GtkWidget *funcionou;
    Produto produto;
    nomeSPB =  gtk_entry_get_text (GTK_ENTRY(nome));
    descricaoSPB =  gtk_entry_get_text (GTK_ENTRY(descricao));
    precofloat =  gtk_entry_get_text (GTK_ENTRY(preco));
    quantidadefloat = gtk_entry_get_text(GTK_ENTRY(quantidade));
   
    p = atof(precofloat);
    q = atoi(quantidadefloat);
    produto.nome = nomeSPB;
    produto.descricao = descricaoSPB;
    produto.preco = p;
    produto.foto = caminhoFotoProduto;
    produto.quantidade = q;
    inserirProduto(db,produto);
    funcionou = gtk_message_dialog_new(GTK_WINDOW(janela),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK, "Produto cadastrado com sucesso");
        gtk_dialog_run(GTK_DIALOG(funcionou));
        gtk_widget_destroy(funcionou);
        gtk_widget_destroy(janela);

    

    //Variaveis para pegar dados do usuario
    //Pega as variaveis do arquivo
    char nomeRecep[500],loginRecep[500],senhaRecep[500],fotoRecep[500];
    float valorRecep;
    int grupoRecep, idRecep;
     
    FILE *fp;
    fp = fopen("usuarioAtual.txt","r");
    fscanf(fp,"%d %s %s %s %f %s %d",&idRecep, nomeRecep,loginRecep,senhaRecep,&valorRecep,fotoRecep,&grupoRecep);
    fclose(fp);
    gerarRelatorioCadastroProduto(valorRecep); //Gera relatorio e o envia pro database e pro arquivo
}

void abrirCadastroProduto(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    //janela
    janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(janela),"Gestor Financeiro");
    gtk_container_set_border_width(GTK_CONTAINER(janela),10);
    gtk_window_set_default_size(GTK_WINDOW(janela), 300, 400);
    gtk_widget_show_all(janela);
    gtk_window_set_position(GTK_WINDOW(janela), GTK_WIN_POS_CENTER);

    //fixo
    fixo = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(janela),fixo);
    
    //Titulo
    tituloLabel = gtk_label_new("Adicionar Produto");
    gtk_fixed_put(GTK_FIXED(fixo),tituloLabel,90,0);

    //Nome
    nomeLabel = gtk_label_new("Nome");
    gtk_fixed_put(GTK_FIXED(fixo), nomeLabel,10,40);
    nome = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixo), nome,80,30);

    //Descrição
    descricaoLabel = gtk_label_new("Descrição");
    gtk_fixed_put(GTK_FIXED(fixo), descricaoLabel,10,70);
    descricao = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixo), descricao,80,60);

    //Preço
    precoLabel = gtk_label_new("Preço");
    gtk_fixed_put(GTK_FIXED(fixo), precoLabel,10,100);
    preco = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixo), preco,80,90);

    //Foto
    fotoLabel = gtk_label_new("Foto");
    gtk_fixed_put(GTK_FIXED(fixo), fotoLabel, 10,130);
    foto = gtk_image_new();
    gtk_fixed_put(GTK_FIXED(fixo), foto, 90,130);
    fotoBotao = gtk_button_new_with_label("Adicionar foto");
    gtk_fixed_put(GTK_FIXED(fixo), fotoBotao,60,350);
    g_signal_connect(G_OBJECT(fotoBotao), "clicked",G_CALLBACK(procurarImagemProduto),janela);

    //Quantidade
    quantidadeLabel = gtk_label_new("Quantidade");
    gtk_fixed_put(GTK_FIXED(fixo), quantidadeLabel, 10, 310);
    quantidade = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixo), quantidade, 80,300);

    //Salvar produto
    salvarProduto = gtk_button_new_with_label("Salvar");
    gtk_fixed_put(GTK_FIXED(fixo), salvarProduto,190,350);
    g_signal_connect(G_OBJECT(salvarProduto), "clicked",G_CALLBACK(salvarProdutoNoBanco),janela);

    //Callback pra destruir a janela e finalizar o programa
    g_signal_connect(G_OBJECT(janela), "destroy",
    G_CALLBACK(gtk_main_quit), NULL); //Fecha a janela
    gtk_widget_show_all(janela);
    gtk_main();
}

/* Função que gera um relatorio e salva na tabela LogUsuario
*       
* @params nomeDoUsuario, nome do usuario logado no momento
* @params idDoUsuario , id do usuario logado no momento
*
* return, não retorna nada.
*/
void gerarRelatorioCadastroProduto(float val){
    //Setando o novoLog e seus dados
    sqlite3 *db;
    char frase[500] = "Foi cadastrado um produto";
    FILE *fp;
    fp = fopen("relatorio.txt","a");
    fprintf(fp,"%s",frase);
    fclose(fp);
    inserirLogUsuario(db,frase);
}