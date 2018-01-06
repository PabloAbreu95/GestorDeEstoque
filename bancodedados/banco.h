#ifndef _BANCO_H
#define _BANCO_H
#include "usuarios/usuario.h"
#include "produtos/produto.h"
#include "logusuarios/logusuario.h"

static int retornoSelecionar(void *data, int argc, char **argv, char **nomeColuna);
void abrirBanco();
void inserirUsuario(sqlite3 *db, Usuario user);
void inserirProduto(sqlite3 *db, Produto produto);
void inserirLogUsuario(sqlite3 *db, char frase[]);

#endif