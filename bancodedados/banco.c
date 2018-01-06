#include <stdio.h>
#include <sqlite3.h>
#include "usuarios/usuario.h"
#include "produtos/produto.h"
#include "logusuarios/logusuario.h"

/* Função de retorno de seleção, aqui são processados os dados retornados
* @params argc - Quantidade de registros retornados
* @params argv - Vetor com os dados dos registros retornados
* @params nomeColuna - Vetor com os nome das colunas retornadas
*/
static int retornoSelecionar(void *data, int argc, char **argv, char **nomeColuna){
   int i;
   
   for(i = 0; i < argc; i++){
      printf("\n%s = %s", nomeColuna[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}

/* Função que inicia o banco e cria as tabelas
* Sem parâmetros
*/
void abrirBanco(){
    sqlite3 *conexao; //Variavel que irá usar conexão ao banco
    sqlite3_open("banco.db", &conexao); //Abrindo banco de dados
    //Criar tabela usuario
    char *sql;
    /*Criando tabela usuarios */
    sql = "CREATE TABLE usuarios("\
          "ID INTEGER PRIMARY KEY AUTOINCREMENT,"\
          "NOME TEXT NOT NULL,"\
          "LOGIN TEXT NOT NULL,"\
          "SENHA TEXT NOT NULL,"\
          "VALOR_VENDAS REAL NOT NULL,"\
          "FOTO_USUARIO TEXT NOT NULL,"\
          "GRUPO_USUARIO INT NOT NULL);";
          sqlite3_exec(conexao, sql, retornoSelecionar, 0, 0);
    /*Criando a tabela logusuario */
    sql = "CREATE TABLE logusuarios("\
          "INFO TEXT NOT NULL);";
          sqlite3_exec(conexao, sql, retornoSelecionar, 0, 0);
    /*Criando a tabela produtos */
    sql = "CREATE TABLE produtos("\
          "ID INTEGER PRIMARY KEY AUTOINCREMENT,"\
          "NOME TEXT NOT NULL,"\
          "FOTO TEXT NOT NULL,"\
          "DESCRICAO TEXT NOT NULL,"\
          "PRECO REAL NOT NULL,"\
          "QUANTIDADE INTEGER NOT NULL);";
          sqlite3_exec(conexao, sql, retornoSelecionar, 0, 0);
    sqlite3_close(conexao); //Fechando banco de dados
}

/* Função de inserção de usuario no banco de dados
* @params db - Banco de dados
* @params user - Struct de usuario
*/
void inserirUsuario(sqlite3 *db, Usuario user){ //Inseri usuario a tabela usuarios
    /* Abrindo o banco de dados */
    sqlite3_open("banco.db", &db);
    char sql[500];
    /*Inserindo na tabela usuarios */
    sprintf(sql,"INSERT INTO usuarios(NOME,LOGIN,SENHA,VALOR_VENDAS, FOTO_USUARIO, GRUPO_USUARIO) VALUES ('%s','%s','%s','%f','%s','%d')",user.nome,user.login,user.senha,user.valor_vendas,user.foto_usuario,user.grupo_usuario);
    sqlite3_exec(db, sql, retornoSelecionar, 0, 0);
    sqlite3_close(db);
}

/* Função de inserção de produto no banco de dados
* @params db - Banco de dados
* @params produto - Struct de Produto
*/
void inserirProduto(sqlite3 *db, Produto produto){ //Inseir um produto
    /* Abrindo o banco de dados */
    sqlite3_open("banco.db", &db);
    char sql[500];
    sprintf(sql,"INSERT INTO produtos (NOME,FOTO,DESCRICAO,PRECO, QUANTIDADE) VALUES ('%s','%s','%s','%f','%d')",produto.nome,produto.foto,produto.descricao,produto.preco,produto.quantidade);
    sqlite3_exec(db, sql, retornoSelecionar, 0, 0);
    sqlite3_close(db);
}
/* Função de inserção de logusuario no banco de dados
* @params db - Banco de dados
* @params logusuario - Struct de LogUsuario
*/
void inserirLogUsuario(sqlite3 *db, char frase[]){ //Inseir um produto
    /* Abrindo o banco de dados */
    sqlite3_open("banco.db", &db);
    char sql[500];
    sprintf(sql,"INSERT INTO logusuarios (INFO) VALUES ('%s')",frase);
    sqlite3_exec(db, sql, retornoSelecionar, 0, 0);
    sqlite3_close(db);
}

