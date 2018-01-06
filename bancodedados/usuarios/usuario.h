#ifndef _USUARIO_H
#define _USUARIO_H
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

typedef struct Usuario{ //Struct que guardará o uśuário
    char   *nome;
    char   *login;
    char   *senha;
    float  valor_vendas;
    char   *foto_usuario;
    int    grupo_usuario; //1 Para usuário supremo, 2 para funcionário comum
}Usuario;

Usuario usuarioAtual; //Variavel que irá guardar os dados do usuario ativo no momento








static int retornoSelecionarUsuario(void *data, int argc, char **argv, char **nomeColuna);
int loginUsuario(char login[], char senha[], sqlite3 *db);

#endif