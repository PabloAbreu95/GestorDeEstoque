#include <sqlite3.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include "dadosUsuario.h"
#include "../../bancodedados/banco.h"


//Declarando widgets
GtkWidget *janela;
GtkWidget *fixo;
GtkWidget *tituloLabel;
GtkWidget *fotoUsuario;
GtkWidget *nomeUsuario;
GtkWidget *valorVendidoLabel;
GtkWidget *valorVendido;


void abrirDadosUsuario(int argc, char *argv[]){
    //Pega as variaveis do arquivo
    char nomeRecep[500],loginRecep[500],senhaRecep[500],fotoRecep[500];
    float valorRecep;
    int grupoRecep;
    FILE *fp;
    fp = fopen("usuarioAtual.txt","r");
    fscanf(fp,"%s %s %s %f %s %d",nomeRecep,loginRecep,senhaRecep,&valorRecep,fotoRecep,&grupoRecep);
    fclose(fp);
    gtk_init(&argc, &argv);
    //janela
    janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(janela),"Gestor Financeiro");
    gtk_container_set_border_width(GTK_CONTAINER(janela),10);
    gtk_window_set_default_size(GTK_WINDOW(janela), 300, 350);
    gtk_widget_show_all(janela);
    gtk_window_set_position(GTK_WINDOW(janela), GTK_WIN_POS_CENTER);

    //fixo
    fixo = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(janela),fixo);

    //Titulo
    tituloLabel = gtk_label_new("Dados do Usuário");
    gtk_fixed_put(GTK_FIXED(fixo),tituloLabel,90,0);

    //Foto
    fotoUsuario = gtk_image_new();
    gtk_image_set_from_file (GTK_IMAGE (fotoUsuario), fotoRecep);
    gtk_fixed_put(GTK_FIXED(fixo),fotoUsuario,90,40);

    //Nome
    nomeUsuario = gtk_label_new(nomeRecep);
    gtk_fixed_put(GTK_FIXED(fixo),nomeUsuario,120,170);

 

    //Callback pra destruir a janela e finalizar o programa
    g_signal_connect(G_OBJECT(janela), "destroy",
    G_CALLBACK(gtk_main_quit), NULL); //Fecha a janela
    gtk_widget_show_all(janela);
    gtk_main();

}