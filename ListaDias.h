#ifndef LISTADIAS_H
#define LISTADIAS_H

typedef struct tarefa Tarefa;

typedef struct dia {
    int dia;
    int mes;
    int ano;
    struct dia* prox;
    Tarefa* listaTarefas;
}Data;

void criarListaD(Data** d);
int estaVaziaD(Data* d);
Data* ultimoDia(Data** d);
int validaData(int dia, int mes, int ano);
Data* buscaDia(Data* d, int dia, int mes, int ano);
Data* addDia(Data** d, int dia, int mes, int ano);
void removeDia(Data** d, int dia, int mes, int ano);
void imprimeDia(Data* d);
void lerArquivo(Data** d);
void salvarArquivo(Data* d);

#endif