#ifndef TAREFAS_H
#define TAREFAS_H

typedef enum prioridade { /*IMPLEMENTAR ASSIM QUE POSSIVEL*/
    BAIXO, /*0*/
    MEDIO, /*1*/
    ALTO, /*2*/
    URGENTE, /*3*/
} PRIORIDADE;

typedef enum status {
    PENDENTE, /*0*/
    CONCLUIDO, /*1*/
}STATUS;

typedef struct tarefa {
    int id;
    char nome[200];
    STATUS status;
    struct tarefa* prox;
    struct tarefa* ant;
}Tarefa;

void criarListaT(Tarefa** t);
int estaVaziaT(Tarefa* t);
Tarefa* ultimaTarefa(Tarefa** t);
void insereNoFim(Tarefa** t, const char* nomeT); /*ALTERAR P/ PRIORIDADE*/
void insereNoFimArquivo(Tarefa** t, int id, const char* nomeT, int status); /*ALTERAR P/ PRIORIDADE*/
Tarefa* buscaTarefaId(Tarefa* t, int id);
void removeTarefaId(Tarefa** t, int id);
void alteraStatusId(Tarefa** t, int id);
void alteraNomeId(Tarefa** t, int id, const char* novoNome);
/*ADICIONAR FUNCAO P/ ALTERAR PRIORIDADE*/
void imprimeT(Tarefa* t); /*ALTERAR P/ PRIORIDADE*/
void liberarLista(Tarefa** t);

#endif