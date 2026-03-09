#include "Tarefas.h"
#include "ListaDias.h"
#include <stdio.h>
#include <stdlib.h>

void menuAlterarT(Tarefa** t) {
    int opcao = 0, idAltera = 0;
    printf("Informe o ID da tarefa que deseja alterar: ");
    scanf("%d", &idAltera);

    printf("\n======== EDITAR TAREFA ========\n");
    printf("1 - Editar nome\n");
    printf("2 - Editar prioridade\n");
    printf("3 - Voltar\n");
    printf("================================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    printf("\n");


    switch (opcao) {
        case 1: {
            char novoNome[200];
            printf("Informe o novo nome da tarefa: ");
            scanf(" %[^\n]", novoNome);
            alteraNomeId(t, idAltera, novoNome);
            break;
        }
        case 3:
            break;
    }
}

void menuTarefas(Data* dSelecionado) {
    int opcao = 0;
    do {
        printf("\n======== MENU DE TAREFAS ========\n");
        printf("1 - Adicionar tarefa\n");
        printf("2 - Marcar tarefa como concluida\n");
        printf("3 - Remover tarefa\n");
        printf("4 - Listar tarefas do dia\n");
        printf("5 - Editar tarefa\n");
        printf("6 - Voltar\n");
        printf("=================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        #ifdef _WIN32
            system("cls"); // Windows
        #else
            system("clear"); // Linux/Unix
        #endif

        switch (opcao) {
            case 1: {
                char nomeTarefa[200];
                printf("Informe o nome da tarefa:\n");
                scanf(" %[^\n]", nomeTarefa);
                insereNoFim(&(dSelecionado->listaTarefas), nomeTarefa);
                break;
            }
            case 2: {
                int idAltera;
                printf("Informe o ID da tarefa que deseja alterar: ");
                scanf("%d", &idAltera);
                alteraStatusId(&(dSelecionado->listaTarefas), idAltera);
                break;
            }
            case 3: {
                int id = 0;
                printf("Informe o ID da tarefa a ser removida: ");
                scanf("%d", &id);
                removeTarefaId(&(dSelecionado->listaTarefas), id);
                break;
            }
            case 4:
                imprimeT(dSelecionado->listaTarefas);
                break;
            case 5:
                menuAlterarT(&(dSelecionado->listaTarefas));
                break;
            case 6:
                break;
        }

    } while(opcao != 6);
}

int main() {
    Data* calendario = NULL;
    int opcao = 0;
    criarListaD(&calendario);
    lerArquivo(&calendario);

    printf("Bem vindo a aplicacao de lista de tarefas! Para informar nomes, por favor opte por nao utilizar acentos e caracteres especiais. Obrigada!\n");

    do {
        printf("\n======== MENU DE CALENDARIO ========\n");
        printf("1 - Adicionar dia\n");
        printf("2 - Remover dia\n");
        printf("3 - Listar dias existentes\n");
        printf("4 - Selecionar dia\n");
        printf("5 - Sair\n");
        printf("====================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        #ifdef _WIN32
            system("cls"); // Windows
        #else
            system("clear"); // Linux/Unix
        #endif

        switch (opcao) {
            case 1: {
                int confirma = 0, valido = 0, dia = 0, mes = 0, ano = 0;
                    do {
                        printf("Informe o dia (dd): ");
                        scanf("%d", &dia);
                        printf("Informe o mes (mm): ");
                        scanf("%d", &mes);
                        printf("Informe o ano (aaaa): ");
                        scanf("%d", &ano);

                        if (ano < 100) {
                            ano += 2000;
                        }

                        valido = validaData(dia, mes, ano);

                        if (valido == 0) {
                            printf("Digite uma data valida!\n");
                        }
                    } while (valido == 0);

                    Data* novoDia = addDia(&(calendario), dia, mes, ano);

                    if (novoDia != NULL) {             
                        do {
                            printf("Deseja adicionar tarefas ao dia? (0 = SIM, 1 = NAO)\n");
                            scanf("%d", &confirma);
                        } while (confirma != 0 && confirma != 1);
        
                        if (confirma == 0) {
                            menuTarefas(novoDia);
                        }
                    }
                break;
            }
            case 2: {
                int confirma = 0;

                do {
                    printf("Realmente deseja remover um dia? (0 = SIM, 1 = NAO)\n");
                    scanf("%d", &confirma);
                } while (confirma != 0 && confirma != 1);

                if (confirma == 0) {
                    int dia = 0, mes = 0, ano = 0, validacao;
                    do {
                        printf("Informando a data a ser removida:\n");
                        printf("Informe o dia (dd): ");
                        scanf("%d", &dia);
                        printf("Informe o mes (mm): ");
                        scanf("%d", &mes);
                        printf("Informe o ano (aaaa): ");
                        scanf("%d", &ano);

                        if (ano < 100) {
                            ano += 2000;
                        }

                        validacao = validaData(dia, mes, ano);

                        if (validacao == 0) {
                            printf("Digite uma data valida!");
                        }
                        
                    } while (validacao == 0);

                    removeDia(&(calendario), dia, mes, ano);
                    break;
                }
                break;
            }
            case 3:
                imprimeDia(calendario);
                break;
            case 4: {
                int dia = 0, mes = 0, ano = 0, validacao;
                    do {
                        printf("Selecionando a data desejada:\n");
                        printf("Informe o dia (dd): ");
                        scanf("%d", &dia);
                        printf("Informe o mes (mm): ");
                        scanf("%d", &mes);
                        printf("Informe o ano (aaaa): ");
                        scanf("%d", &ano);

                        if (ano < 100) {
                            ano += 2000;
                        }

                        validacao = validaData(dia, mes, ano);

                        if (validacao == 0) {
                            printf("Digite uma data valida!\n");
                        }
                        
                    } while (validacao == 0);

                Data* busca = buscaDia(calendario, dia, mes, ano);
                if (busca == NULL) {
                    printf("Data inexistente na lista. Adicione o dia se quiser definir tarefas.\n");
                }
                else {
                    menuTarefas(busca);
                }
                break;
            }
            case 5:
                salvarArquivo(calendario);
                break;
        }

    } while (opcao != 5);
}