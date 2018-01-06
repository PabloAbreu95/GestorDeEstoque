#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <stdlib.h>
#include "usuario.h"
#include "../banco.h"

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

int loginUsuario(char login[], char senha[], sqlite3 *db){
    sqlite3_open("banco.db", &db);
    char sql[500];
    sprintf(sql,"SELECT * FROM usuarios WHERE LOGIN = '%s'",login);
    sqlite3_exec(db, sql, retornoSelecionarUsuario, NULL, NULL);
    if(!strcmp(senha,usuarioAtual.senha)){
        return 0;
    } else{
        return 1;
    }

    sqlite3_close(db);
    
}