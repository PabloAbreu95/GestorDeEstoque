#include <sqlite3.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include "cadastroUsuario.h"
#include "../../bancodedados/banco.h"



//Criação das widgets
GtkWidget *janela;
GtkWidget *fixo;
GtkWidget *cadastro_label;
GtkWidget *nomeLabel;
GtkWidget *nome;
GtkWidget *loginLabel;
GtkWidget *login;
GtkWidget *senhaLabel;
GtkWidget *senha;
GtkWidget *fotoLabel;
GtkWidget *foto; //Foto de no máximo 128x128;
GtkWidget *fotoBotao;
GtkWidget *cadastrar;
const char *caminhoFotoUsuario = "/"; //Variavel que irá guardar uma foto do usuario

/* Função que servirá para procurar uma imagem que terá seu caminho salvo para uso futuro
*
* Após o caminho ser encontrado, ele é salvo na variável caminhoFotoUsuario, para futuramente ser usado pelo programa
*
* @Params button, botão que irá abrir os repositorios para procurar foto
* @Params window, janela em que o programa está rodando
*
*/
static void procurarImagem(GtkButton *button, GtkWindow *window){
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
        caminhoFotoUsuario = filename;

        gtk_image_set_from_file (GTK_IMAGE (foto), filename);
    }
    if (result==GTK_RESPONSE_CANCEL){
        g_print("Cancelado");
    }
    gtk_widget_destroy(dialog);
}
/* Função que salva um elemento no banco de dados
*
* Não há parametros, todos os dados são recuperados de variaveis globais, transferidas para 
* ponteiros de char e adicionados um usuário que em seguida é adicionado no banco de dados, na tabela usuario
*
*/
void salvarUsuarioNoBanco(){
    const char *nomeSUB, *loginSUB, *senhaSUB;
    GtkWidget *funcionou;
    sqlite3 *db;
    nomeSUB =  gtk_entry_get_text (GTK_ENTRY(nome));
    loginSUB =  gtk_entry_get_text (GTK_ENTRY(login));
    senhaSUB =  gtk_entry_get_text (GTK_ENTRY(senha));
    Usuario user;
    user.nome = nomeSUB;
    user.login = loginSUB;
    user.senha = senhaSUB;
    user.valor_vendas = 0;
    user.foto_usuario = caminhoFotoUsuario;
    user.grupo_usuario = 2;
    inserirUsuario(db,user);
    funcionou = gtk_message_dialog_new(GTK_WINDOW(janela),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK, "Usuario adicionado com sucesso!");
        gtk_dialog_run(GTK_DIALOG(funcionou));
        gtk_widget_destroy(funcionou);
        gtk_widget_destroy(janela);
}

/* 
* Função que desenha a janela na tela
*/
void abrirCadastroUsuario(int argc, char *argv[]){
    
    gtk_init(&argc, &argv);
    janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(janela),"Cadastrar usuário");
    gtk_container_set_border_width(GTK_CONTAINER(janela),10);
    gtk_window_set_default_size(GTK_WINDOW(janela), 300, 350);
    gtk_widget_show_all(janela);
    gtk_window_set_position(GTK_WINDOW(janela), GTK_WIN_POS_CENTER);
    //Fixo
    fixo = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(janela),fixo);
    
    //Label inicial
    cadastro_label = gtk_label_new("Cadastro de usuario");
    gtk_fixed_put(GTK_FIXED(fixo),cadastro_label,70,0);

    
    //Nome
    nomeLabel = gtk_label_new("Nome");
    nome = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixo),nomeLabel,10,40);
    gtk_fixed_put(GTK_FIXED(fixo),nome,60,30);

    //Login
    loginLabel = gtk_label_new("Login");
    login = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixo), loginLabel,10,70);
    gtk_fixed_put(GTK_FIXED(fixo),login,60,60);

    //senha
    senhaLabel = gtk_label_new("Senha");
    senha = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixo), senhaLabel,10,100);
    gtk_fixed_put(GTK_FIXED(fixo),senha,60,90);

    //Foto
    fotoLabel = gtk_label_new("Foto");
    foto = gtk_image_new();
    fotoBotao = gtk_button_new_with_label("Abrir foto");
    gtk_fixed_put(GTK_FIXED(fixo), fotoLabel,10,130);
    gtk_fixed_put(GTK_FIXED(fixo),foto,70,120);
    gtk_fixed_put(GTK_FIXED(fixo),fotoBotao,90,260);
    g_signal_connect(G_OBJECT(fotoBotao), "clicked",G_CALLBACK(procurarImagem),janela);

    //Cadastrar
    cadastrar = gtk_button_new_with_label("Salvar");
    gtk_fixed_put(GTK_FIXED(fixo),cadastrar,90,300);
    g_signal_connect(G_OBJECT(cadastrar), "clicked",G_CALLBACK(salvarUsuarioNoBanco),janela);


    //Callback pra destruir a janela e finalizar o programa
    g_signal_connect(G_OBJECT(janela), "destroy",
    G_CALLBACK(gtk_main_quit), NULL); //Fecha a janela
    gtk_widget_show_all(janela);
    gtk_main();
}

