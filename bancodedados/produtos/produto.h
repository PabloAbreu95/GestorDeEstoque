#ifndef _PRODUTO_H
#define _PRODUTO_H
typedef struct Produto{
    int id;
    char *nome;
    char *foto;
    char *descricao;
    float preco;
    int quantidade;
}Produto;
void gerarArquivoProdutos(sqlite3 *db);
#endif