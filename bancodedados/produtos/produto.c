#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <stdlib.h>
#include "produto.h"
#include "../banco.h"

static int retornoSelecionarTodosProdutos(void *data, int argc, char **argv, char **nomeColuna){
   int i;
   //Abrir arquivo para escrita
   FILE *fp;
   fp = fopen("produtos.txt","a");
   int cont = 0; //Contador que faz a quebra de linha
   for(i = 0; i < argc; i++){
       fprintf(fp,"%s ",argv[i] ? argv[i] : "NULL");
       cont++;
       if(cont>5){
           fprintf(fp,"\n");
           cont = 0;
       }
   } 
   fclose(fp);
   return 0;
}

void gerarArquivoProdutos(sqlite3 *db){
    sqlite3_open("banco.db", &db);
    char sql[500] = "";
    strcat(sql,"SELECT * FROM produtos");                         
    sqlite3_exec(db, sql, retornoSelecionarTodosProdutos, NULL, NULL);
    sqlite3_close(db);
}

