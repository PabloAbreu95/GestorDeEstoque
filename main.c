#include <stdio.h>
#include <sqlite3.h>
#include "bancodedados/banco.h"
#include "menus/loginSistema/loginSistema.h"
#include "menus/cadastroUsuario/cadastroUsuario.h"
#include "menus/cadastroProduto/cadastroProduto.h"
int main(int argc,char *argv[]){

   //Limpa os dados do arquivo de protudos
    FILE *fp0;
    fp0 = fopen("produtos.txt","w");
    fclose(fp0);
    //Limpa os dados do arquivo de protudos
    FILE *fp1;
    fp1 = fopen("relatorios.txt","w");
    fclose(fp1);

   //Abre o banco
    abrirBanco();
   //Abre o sistema de login
    abrirLoginSistema(argc,argv);
    
    return 0;
}