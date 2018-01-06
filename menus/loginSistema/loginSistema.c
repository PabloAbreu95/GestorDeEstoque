
#include <sqlite3.h>
#include <string.h>
#include <gtk/gtk.h>
#include "loginSistema.h"
#include "../../bancodedados/usuarios/usuario.h"
#include "../menuPrincipal/menuPrincipal.h"
//Criação das widgets
GdkPixbuf *icone;
GtkWidget *fixo;
GtkWidget *login;
GtkWidget *senha;
GtkWidget *botao;
GtkWidget *loginEntry; //Entry do login
GtkWidget *senhaEntry; //Entry da senha
GtkWidget *alerta;//Aviso quando o usuario clicar em autenticar
GtkWidget *janela;


static void autentica_usuario( GtkWidget *w, gpointer *data)
{
    sqlite3 *db;
    const char *entry1,*entry2;
    entry1 = gtk_entry_get_text (GTK_ENTRY(loginEntry));
    entry2 = gtk_entry_get_text (GTK_ENTRY(senhaEntry));
    if(loginUsuario(entry1,entry2,db) == 0){
        g_print("funcinou\n");
        alerta = gtk_message_dialog_new(GTK_WINDOW(janela),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK, "Usuário logado com sucesso");
        gtk_dialog_run(GTK_DIALOG(alerta));
        gtk_widget_destroy(alerta);
        gtk_widget_destroy(janela);
        abrirMenuPrincipal();
    }else{
        g_print("Não funcinou\n");
        alerta = gtk_message_dialog_new(GTK_WINDOW(janela),
        GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK, "Erro ao logar");
        gtk_dialog_run(GTK_DIALOG(alerta));
        gtk_widget_destroy(alerta);
    }  
}

void abrirLoginSistema(int argc, char *argv[]){
    gtk_init(&argc,&argv);//Inicia o gtk
    //Janela
    janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(janela),"Tela de Login");
    gtk_window_set_default_size(GTK_WINDOW(janela), 300, 250);
    gtk_window_set_position(GTK_WINDOW(janela), GTK_WIN_POS_CENTER);
    //Fixo
    fixo = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(janela), fixo);
    //Login
    login = gtk_label_new("Usuario");
    loginEntry = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixo), login, 20, 50);
    gtk_fixed_put(GTK_FIXED(fixo), loginEntry, 80, 50);
    //Senha
    senha = gtk_label_new("Senha");
    senhaEntry = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixo), senha,20, 100);
    gtk_fixed_put(GTK_FIXED(fixo), senhaEntry, 80, 100);
    gtk_entry_set_visibility(GTK_ENTRY(senhaEntry),0); //Deixa os valores escritos na entry invisiveis
    //Botao
    botao = gtk_button_new_with_label("Autenticar");
    gtk_fixed_put(GTK_FIXED(fixo), botao, 110, 160);
    gtk_widget_set_size_request(botao, 80, 30);
    g_signal_connect (botao, "clicked", G_CALLBACK (autentica_usuario), NULL);
    //Callback pra destruir a janela e finalizar o programa
    g_signal_connect(G_OBJECT(janela), "destroy",
    G_CALLBACK(gtk_main_quit), NULL); //Fecha a janela
    //Mostrar widgets contidos na janela
    gtk_widget_show_all(janela);
    //MainLoop
    gtk_main();
}