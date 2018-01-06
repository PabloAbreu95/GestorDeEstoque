#include <gtk/gtk.h>
#include <sqlite3.h>
#include <string.h>
#include "../cadastroUsuario/cadastroUsuario.h"
#include "../cadastroProduto/cadastroProduto.h"
#include "../dadosUsuario/dadosUsuario.h"
#include "../venderProduto/venderProduto.h"
#include "../venderProduto/janelaDeVenda.h"
#include "../reporEstoque/reporEstoque.h"
#include "../relatorioUsuario/relatorioUsuario.h"

//Criação de widgets
GtkWidget *janela;
GtkWidget *fixo;
GtkWidget *cadastrar_usuario;
GtkWidget *dados_usuario;
GtkWidget *adicionar_produto;
GtkWidget *listar_estoque;
GtkWidget *repor_estoque;
GtkWidget *vender_produto;
GtkWidget *relatorio_usuario;
GtkWidget *alerta;


void abrirMenuPrincipal(){
    
    janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(janela),"Gestor Financeiro");
    gtk_container_set_border_width(GTK_CONTAINER(janela),10);
    gtk_window_set_default_size(GTK_WINDOW(janela), 300, 350);
    gtk_widget_show_all(janela);
    gtk_window_set_position(GTK_WINDOW(janela), GTK_WIN_POS_CENTER);
    //Fixo
    fixo = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(janela),fixo);

    //Cadastrar usuario
    cadastrar_usuario = gtk_button_new_with_label("Cadastrar usuário");
    gtk_fixed_put(GTK_FIXED(fixo), cadastrar_usuario, 70, 20);
    gtk_widget_set_size_request(cadastrar_usuario, 150, 30);
    g_signal_connect (cadastrar_usuario, "clicked", G_CALLBACK (abrirCadastroUsuario), NULL);


    //Dados do usuário
    dados_usuario = gtk_button_new_with_label("Dados do usuário");
    gtk_fixed_put(GTK_FIXED(fixo), dados_usuario, 70, 55);
    gtk_widget_set_size_request(dados_usuario, 150, 30);
    g_signal_connect (dados_usuario, "clicked", G_CALLBACK (abrirDadosUsuario), NULL);


    //Adicionar produto
    adicionar_produto = gtk_button_new_with_label("Cadastrar produto");
    gtk_fixed_put(GTK_FIXED(fixo), adicionar_produto, 70, 90);
    gtk_widget_set_size_request(adicionar_produto, 150, 30);
    g_signal_connect (adicionar_produto, "clicked", G_CALLBACK (abrirCadastroProduto), NULL);

    //Listar Estoque
    listar_estoque = gtk_button_new_with_label("Listar estoque");
    gtk_fixed_put(GTK_FIXED(fixo), listar_estoque, 70, 125);
    gtk_widget_set_size_request(listar_estoque, 150, 30);
    g_signal_connect (listar_estoque, "clicked", G_CALLBACK (abrirVenderProduto), NULL);


    //Repor estoque
    repor_estoque = gtk_button_new_with_label("Repor estoque");
    gtk_fixed_put(GTK_FIXED(fixo), repor_estoque, 70, 160);
    gtk_widget_set_size_request(repor_estoque, 150, 30);  
    g_signal_connect (repor_estoque, "clicked", G_CALLBACK (abrirReporEstoque), NULL);


    //Vender produto
    vender_produto = gtk_button_new_with_label("Vender produto");
    gtk_fixed_put(GTK_FIXED(fixo), vender_produto, 70, 195);
    gtk_widget_set_size_request(vender_produto, 150, 30); 
    g_signal_connect (vender_produto, "clicked", G_CALLBACK (abrirJanelaDeVenda), NULL);
    
    
    //Relatorio usuario
    relatorio_usuario = gtk_button_new_with_label("Relatorio do usuário");
    gtk_fixed_put(GTK_FIXED(fixo), relatorio_usuario, 70, 230);
    gtk_widget_set_size_request(relatorio_usuario, 150, 30);
    g_signal_connect (relatorio_usuario, "clicked", G_CALLBACK (abrirRelatorioUsuario), NULL);


    //Callback pra destruir a janela e finalizar o programa
    g_signal_connect(G_OBJECT(janela), "destroy",
    G_CALLBACK(gtk_main_quit), NULL); //Fecha a janela
    gtk_widget_show_all(janela);
    gtk_main();
}
