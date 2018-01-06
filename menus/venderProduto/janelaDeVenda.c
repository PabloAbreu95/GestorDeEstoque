#include <gtk/gtk.h>
#include <sqlite3.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "janelaDeVenda.h"
#include "../../bancodedados/banco.h"
#include "../../bancodedados/produtos/produto.h"
#include "../../bancodedados/usuarios/usuario.h"

//Criação das widgets
GtkWidget *janela;
GtkWidget *fixo;
GtkWidget *nomeLabel;
GtkWidget *nome;
GtkWidget *botaoVenda;
GtkWidget *alerta;

void abrirJanelaDeVenda(){
    //Janela
    janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(janela),"Venda de produtos");
    gtk_window_set_default_size(GTK_WINDOW(janela), 300, 100);
    gtk_window_set_position(GTK_WINDOW(janela), GTK_WIN_POS_CENTER);
    //Fixo
    fixo = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(janela), fixo);

    //Nome
    nomeLabel = gtk_label_new("Nome do Produto");
    nome = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixo), nomeLabel, 10, 10);
    gtk_fixed_put(GTK_FIXED(fixo), nome, 120, 0);

    //Botão
    botaoVenda = gtk_button_new_with_label("Vender");
    gtk_fixed_put(GTK_FIXED(fixo), botaoVenda,100,50);
    g_signal_connect (botaoVenda, "clicked", G_CALLBACK (comprar), NULL);
   
    //Callback pra destruir a janela e finalizar o programa
    g_signal_connect(G_OBJECT(janela), "destroy",
    G_CALLBACK(gtk_main_quit), NULL); //Fecha a janela
    gtk_widget_show_all(janela);
    gtk_main();
}
/* Função para vender produto
*
* @params nomeDoProduto, nome do produto que está sendo vendido
*
* A função faz uma busca pelo nome do produto e adiciona o valor do mesmo ao valor vendido pelo usuario e 
* decrementa a quantidade do produto em estoque
*
*/
void venderItem(char nomeDoUsuario[], char nomeDoProduto[]){
    sqlite3 *db;
    //Variaveis gerais, que serão usadas na operação da compra
    float valorOficialDoProduto;
    int quantidadeOficialDoProduto;
    float valorOficialDoCliente;
    //Variáveis que serão usadas para armazenar os dados coletados do arquivo de texto
    char idProduto[50],  nomeProduto[500],  fotoProduto[500], descricaoProduto[500], precoProduto[500], quantidadeProduto[500];
    //Abrindo o arquivo para leitura
    
    FILE *fp;
    fp = fopen("produtos.txt","r");
    //Fazendo leitura dos dados
   while(fscanf(fp, "%s %s %s %s %s %s",idProduto,nomeProduto,fotoProduto,descricaoProduto,precoProduto,quantidadeProduto)!=EOF){
        
        if(!strcmp(nomeProduto,nomeDoProduto)){ //Se o nome do produto for igual ao nome encontrado no arquivo
            valorOficialDoProduto = atof(precoProduto);
            quantidadeOficialDoProduto = atoi(quantidadeProduto);
        }
        
    }
    fclose(fp);//Fecha o arquivo

   
    //valor De Vendas do cliente
    char a[500],b[500],c[500],d[500],e[500];
    float vv;
    FILE *fp2;
    fp2 = fopen("usuarioAtual.txt","r");
    //Fazendo a leitura do arquivo
    fscanf(fp2,"%s %s %s %.2f %s %s",a,b,c,vv,d,e); //Recuperando valor de vendas
    fclose(fp2);
    quantidadeOficialDoProduto = quantidadeOficialDoProduto - 1; //Decrementando a quantidade de produtos
    valorOficialDoCliente = vv + valorOficialDoProduto;

    //Reescrita do  usuarioAtual.txt
    sqlite3_open("banco.db", &db);
    char sql3[500];
    sprintf(sql3,"SELECT * FROM usuarios WHERE NOME = '%s'",nomeDoUsuario);
    sqlite3_exec(db, sql3, retornoSelecionarUsuario, NULL, NULL);
    sqlite3_close(db);
    //Fim da reescrita

    sqlite3_open("banco.db", &db);
    char sql[500],sql2[500];
    sprintf(sql,"UPDATE produtos SET QUANTIDADE = %d WHERE NOME = '%s'",quantidadeOficialDoProduto,nomeDoProduto);
    sprintf(sql2,"UPDATE usuarios SET VALOR_VENDAS = %f WHERE NOME = '%s'",valorOficialDoCliente,nomeDoUsuario);
    sqlite3_exec(db, sql, retornoSelecionar, 0, 0);
    sqlite3_exec(db, sql2, retornoSelecionar, 0, 0);
    sqlite3_close(db);
 
    
}
//Função comprar

//Faz a compra do produto assim que o botão é apertado
void comprar(){
    //Variaveis
    char nomeDoUsuarioAtivo[500],a[500],b[500],c[500],d[500],e[500];
    //Abrir arquivo para pegar nome
    FILE *fp;
    fp = fopen("usuarioAtual.txt","r");
    fscanf(fp,"%s %s %s %.2f %s %s",nomeDoUsuarioAtivo,b,c,a,d,e);
    fclose(fp);
    const char *entry1;
    entry1 = gtk_entry_get_text (GTK_ENTRY(nome));
    venderItem(nomeDoUsuarioAtivo,entry1);
    alerta = gtk_message_dialog_new(GTK_WINDOW(janela),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK, "Compra realizada com sucesso");
        gtk_dialog_run(GTK_DIALOG(alerta));
        gtk_widget_destroy(alerta);
        gtk_widget_destroy(janela);
    geraRelatorioVenda(entry1);
}
//Gera um relatorio de venda
void geraRelatorioVenda(const char *nomeProduto){
    sqlite3 *db;
    sqlite3_open("banco.db", &db);
    char sql[500];
    char info[500] = "Um produto foi vendido";
    
    sprintf(sql,"INSERT INTO logusuarios (INFO) VALUES ('%s')",info);
    sqlite3_exec(db, sql, retornoSelecionar, 0, 0);
    sqlite3_close(db);
}

static int retornoSelecionar(void *data, int argc, char **argv, char **nomeColuna){
   int i;
   
   for(i = 0; i < argc; i++){
      printf("\n%s = %s", nomeColuna[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   
}
static int retornoSelecionarUsuario(void *data, int argc, char **argv, char **nomeColuna){

   int idUsuario = atoi(argv[0]);
   usuarioAtual.nome = argv[1];
   usuarioAtual.login = argv[2];
   usuarioAtual.senha = argv[3];
   usuarioAtual.valor_vendas = atof(argv[6]);
   usuarioAtual.foto_usuario = argv[5];
   usuarioAtual.valor_vendas = atoi(argv[4]);
   FILE *fp;
   fp = fopen("usuarioAtual.txt","w");
   fprintf(fp,"%s ",usuarioAtual.nome);
   fprintf(fp,"%s ",usuarioAtual.login);
   fprintf(fp,"%s ",usuarioAtual.senha);
   fprintf(fp,"%.2f ",usuarioAtual.valor_vendas);
   fprintf(fp,"%s ",usuarioAtual.foto_usuario);
   fprintf(fp,"%d ",usuarioAtual.grupo_usuario);
   fclose(fp);
   return 0;
}