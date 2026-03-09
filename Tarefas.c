#include "Tarefas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contReg = 1;

void criarListaT(Tarefa** t) {
    *t = NULL;
}

int estaVaziaT(Tarefa* t) {
    return (t == NULL);
}

Tarefa* ultimaTarefa(Tarefa** t) {
    Tarefa* aux;
    if (!estaVaziaT(*t)) {
        for (aux = *t; aux->prox != NULL; aux = aux->prox);
        return aux;
    }
    else {
        printf("Lista de tarefas vazia.\n");
        return NULL;
    }
}

void insereNoFim(Tarefa** t, const char* nomeT) {
    Tarefa* novaT = malloc(sizeof(Tarefa));
    if (novaT != NULL) {
        novaT->id = contReg++;
        novaT->status = 0; /*PENDENTE*/
        strcpy(novaT->nome, nomeT);

        novaT->prox = NULL;

        if (!estaVaziaT(*t)) {
            Tarefa* aux = ultimaTarefa(t);
            novaT->ant = aux;
            aux->prox = novaT;
        }
        else {
            novaT->ant = NULL;
            (*t) = novaT;
        }
    }
    else {
        printf("Nao foi possivel alocar espaco.\n");
    }
}

void insereNoFimArquivo(Tarefa** t, int id, const char* nomeT, int status) {
    Tarefa* novaT = malloc(sizeof(Tarefa));
    if (novaT == NULL) {
        printf("Erro de memoria!\n");
        return;
    }
    novaT->id = id;
    novaT->status = status;
    strcpy(novaT->nome, nomeT);
    novaT->prox = NULL;
    if (id >= contReg) {
        contReg = id + 1;
    }
    if (!estaVaziaT(*t)) {
        Tarefa* aux = ultimaTarefa(t);
        novaT->ant = aux;
        aux->prox = novaT;
    }
    else {
        novaT->ant = NULL;
        *t = novaT;
    }
}

Tarefa* buscaTarefaId(Tarefa* t, int id) {
    Tarefa* aux = NULL;
    for (aux = t; aux != NULL && aux->id != id; aux = aux->prox);
    return aux;
}

void removeTarefaId(Tarefa** t, int id) {
    if (!estaVaziaT(*t)) {
        Tarefa* busca = buscaTarefaId(*t, id);
        if (busca == NULL) {
            printf("ID nao existe na lista.\n");
        }
        else {
            if (busca->ant == NULL && busca->prox == NULL) {
                (*t) = NULL;
            }
            else if (busca->ant == NULL) {
                (*t) = busca->prox;
                busca->prox->ant = NULL;
            }
            else if (busca->prox == NULL) {
                busca->ant->prox = NULL;
            }
            else {
                busca->ant->prox = busca->prox;
                busca->prox->ant = busca->ant;
            }
            free(busca);
            printf("Tarefa removida com sucesso!\n");
        }
    }
    else {
        printf("Lista vazia");
    }
}

void alteraStatusId(Tarefa** t, int id) {
    if (!estaVaziaT(*t)) {
        Tarefa* busca = buscaTarefaId(*t, id);
        if (busca == NULL) {
            printf("ID nao existe na lista.\n");
        }
        else {
            if (busca->status == 0) {
                busca->status = 1;
            }
            else {
                busca->status = 0;
            }
        }
    }
    else {
        printf("Lista vazia!");
    }
}

void alteraNomeId(Tarefa** t, int id, const char* novoNome) {
    if (!estaVaziaT(*t)) {
        Tarefa* busca = buscaTarefaId(*t, id);
        if (busca == NULL) {
            printf("ID nao existe na lista.\n");
        }
        else {
            strcpy(busca->nome, novoNome);
        }
    }
    else {
        printf("Lista vazia!");
    }
}

void imprimeT(Tarefa* t) {
    if (estaVaziaT(t)) printf("Lista vazia.\n");
    else {
        Tarefa* aux = t;
        printf("ID\tNOME\t\tSTATUS\n");
        while (aux != NULL) {
            if (aux->status == 0) {
                printf("%d\t%s\t\tPendente\n", aux->id, aux->nome);
            }
            else {
                printf("%d\t%s\t\tConcluida\n", aux->id, aux->nome);
            }
            aux = aux->prox;
        }
    }   
}

void liberarLista(Tarefa** t) {
    if (!estaVaziaT(*t)) {
        Tarefa* aux, *temp;
        for (aux = *t; aux != NULL; aux = temp) {
            temp = aux->prox;
            free(aux);
        }
        *t = NULL;
    }
}

