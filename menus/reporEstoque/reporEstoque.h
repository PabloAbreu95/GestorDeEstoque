#ifndef _REPOR_ESTOQUE_H
#define _REPOR_ESTOQUE_H

void abrirReporEstoque();
void repor();
void reporProduto(char nomeProduto[], int quantidadeRepor);
static int retornoSelecionar(void *data, int argc, char **argv, char **nomeColuna);
#endif