#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <stdlib.h>
#include "logusuario.h"
#include "../banco.h"

static int retornoSelecionarTodosRelatorios(void *data, int argc, char **argv, char **nomeColuna){
   int i;
   //Abrir arquivo para escrita
   FILE *fp;
   fp = fopen("relatorios.txt","a");
   for(i = 0; i < argc; i++){
       fprintf(fp,"%s",argv[i] ? argv[i] : "NULL");
       fprintf(fp,"\n");
   } 
 
   fclose(fp);
   return 0;
}

void gerarArquivoRelatorios(){
    sqlite3 *db;
    sqlite3_open("banco.db", &db);
    char sql[500] = "";
    strcat(sql,"SELECT * FROM logusuarios");                         
    sqlite3_exec(db, sql, retornoSelecionarTodosRelatorios, NULL, NULL);
    sqlite3_close(db);
}
