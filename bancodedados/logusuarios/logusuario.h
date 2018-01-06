#ifndef _LOG_USUARIO_H
#define _LOG_USUARIO_H

typedef struct LogUsuario{ //Struct que guardará o log do usuário
    int id_usuario;
    char *info;
    char *time;
}LogUsuario;
static int retornoSelecionarTodosRelatorios(void *data, int argc, char **argv, char **nomeColuna);
void gerarArquivoRelatorios();
#endif
