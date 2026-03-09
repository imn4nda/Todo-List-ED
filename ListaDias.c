#include "ListaDias.h"
#include "Tarefas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void criarListaD(Data** d) {
    *d = NULL;
}

int estaVaziaD(Data* d) {
    return (d == NULL);
}

Data* ultimoDia(Data** d) {
    if (!estaVaziaD(*d)) {
        Data* aux;
        for (aux = *d; aux->prox != NULL; aux = aux->prox);
        return aux;
    }
    else {
        printf("Listagem de dias vazia.\n");
        return NULL;
    }
}

int validaData(int dia, int mes, int ano) {
    if ((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && (ano >= 2000 && ano <= 2100)) {
        if ((dia == 29 && mes == 2) && (ano % 4) == 0) {
            return 1;
        }
        if (dia <= 28 && mes == 2) {
            return 1;
        }
        if (dia <= 31 && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)) {
            return 1;
        }
        if (dia <= 30 && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

Data* buscaDia(Data* d, int dia, int mes, int ano) {
    Data* aux;
    for (aux = d; aux != NULL && !(aux->dia == dia && aux->mes == mes && aux->ano == ano); aux = aux->prox);
    return aux;
}

Data* addDia(Data** d, int dia, int mes, int ano) {
    Data* novaD = malloc(sizeof(Data));
    int valido;
    if (novaD != NULL) {

        Data* busca = buscaDia(*d, dia, mes, ano);
        if (busca != NULL) {
            printf("Esse dia ja existe na lista!\n");
            free(novaD);
            return busca;
        }
        else {
            novaD->listaTarefas = NULL;
            novaD->dia = dia;
            novaD->mes = mes;
            novaD->ano = ano;
            
            if (!estaVaziaD(*d)) {
                Data* ant = NULL, *p = *d;
                while (p != NULL &&
                (p->ano < novaD->ano ||
                (p->ano == novaD->ano && p->mes < novaD->mes) ||
                (p->ano == novaD->ano && p->mes == novaD->mes && p->dia < novaD->dia))) {
                    ant = p;
                    p = p->prox;
                }
                if (p == NULL) {
                    novaD->prox = NULL;
                    ant->prox = novaD;
                }
                else if (ant == NULL) {
                    novaD->prox = (*d);
                    (*d) = novaD;
                }
                else {
                    novaD->prox = p;
                    ant->prox = novaD;
                }
            }
            else {
                (*d) = novaD;
                novaD->prox = NULL;
            }
            return novaD;
        }
    }
    else {
        printf("Nao foi possivel alocar espaco.\n");
        return NULL;
    }
}

void removeDia(Data** d, int dia, int mes, int ano) {
    if (!estaVaziaD(*d)) {
        Data* aux, *ant = NULL;
        for (aux = *d; aux != NULL && !(aux->dia == dia && aux->mes == mes && aux->ano == ano); aux = aux->prox) {
            ant = aux;
        }
        if (aux == NULL) {
            printf("Data inexistente na lista.\n");
            return;
        }
        else {
            liberarLista(&(aux->listaTarefas));

            if (ant == NULL) {
                (*d) = aux->prox;
            }
            else {
                ant->prox = aux->prox;
            }
            free(aux);
        }
    }
    else {
        printf("Lista vazia");
    }
}

void imprimeDia(Data* d) {
    if (!estaVaziaD(d)) {
        Data* aux;
        for (aux = d; aux != NULL; aux = aux->prox) {
            printf("%02d/%02d/%04d\n", aux->dia, aux->mes, aux->ano);
        }
    }
    else {
        printf("Calendario vazio");
    }
}

void lerArquivo(Data** d) {
    FILE* arquivo = fopen("LeitorTarefas.txt", "r");
    if (arquivo == NULL) {
        return;
    }
    char tipo;
    Data* ultimoDiaCriado = NULL;

    while (fscanf(arquivo, " %c", &tipo) == 1) {
        if (tipo == 'D') {
            int dia, mes, ano;
            fscanf(arquivo, "%02d %02d %04d", &dia, &mes, &ano);
            ultimoDiaCriado = addDia(d, dia, mes, ano);
        }

        else if (tipo == 'T') {
            int id, status;
            char nome[200];

            fscanf(arquivo, "%d  %d ", &id, &status);
            fgets(nome, 200, arquivo);
            nome[strcspn(nome, "\n")] = 0;
            insereNoFimArquivo(&(ultimoDiaCriado->listaTarefas), id, nome, status);
        }
    }

    fclose(arquivo);
}

void salvarArquivo(Data* d) {
    FILE* arquivo = fopen("LeitorTarefas.txt", "w");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }
    Data* data;
    for (data = d; data != NULL; data = data->prox) {
        fprintf(arquivo, "D %02d %02d %04d\n", data->dia, data->mes, data->ano);

        Tarefa* t;
        for (t = data->listaTarefas; t != NULL; t = t->prox) {
            fprintf(arquivo, "T %d %d %s\n", t->id, t->status, t->nome);
        }
    }
    fclose(arquivo);
}
