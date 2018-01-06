#ifndef _JANELA_DE_VENDA_H
#define _JANELA_DE_VENDA_H

void abrirJanelaDeVenda();
void venderItem(char nomeDoUsuario[], char nomeDoProduto[]);
static int retornoSelecionar(void *data, int argc, char **argv, char **nomeColuna);
void comprar();
void geraRelatorioVenda(const char *nomeProduto);
#endif