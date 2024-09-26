#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 40
#define MAX_TELEFONE 15
#define MAX_CELULAR 15
#define MAX_EMAIL 40

typedef struct Data {
    int dia;
    int mes;
} Data;

typedef struct Contato {
    char nome[MAX_NOME];
    char telefone[MAX_TELEFONE];
    char celular[MAX_CELULAR];
    char email[MAX_EMAIL];
    Data dataAniversario;
    struct Contato *prox;
} Contato;

Contato *cria_agenda() {
    return NULL;
}

void insere_contato(Contato **agenda, Contato *novo_contato) {
    Contato *atual = *agenda;
    Contato *anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, novo_contato->nome) < 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL) {
        novo_contato->prox = *agenda;
        *agenda = novo_contato;
    } else {
        anterior->prox = novo_contato;
        novo_contato->prox = atual;
    }
}

void lista_contatos(Contato *agenda) {
    Contato *atual = agenda;

    while (atual != NULL) {
        printf("Nome: %s\n", atual->nome);
        printf("Telefone: %s\n", atual->telefone);
        printf("Celular: %s\n", atual->celular);
        printf("Email: %s\n", atual->email);
        printf("Data de Aniversario: %d/%d\n", atual->dataAniversario.dia, atual->dataAniversario.mes);
        printf("\n");

        atual = atual->prox;
    }
}

Contato *busca_contato(Contato *agenda, char *nome) {
    Contato *atual = agenda;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        atual = atual->prox;
    }

    return atual;
}

void remove_contato(Contato **agenda, char *nome) {
    Contato *atual = *agenda;
    Contato *anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Contato nao encontrado.\n");
        return;
    }

    if (anterior == NULL) {
        *agenda = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
}

void atualiza_contato(Contato *agenda, char *nome) {
    Contato *contato = busca_contato(agenda, nome);

    if (contato == NULL) {
        printf("Contato nao encontrado.\n");
        return;
    }else{
    
    printf("Digite o novo nome: ");
    scanf("%s", contato->nome);

    printf("Digite o novo telefone: ");
    scanf("%s", contato->telefone);

    printf("Digite o novo celular: ");
    scanf("%s", contato->celular);

    printf("Digite o novo email: ");
    scanf("%s", contato->email);

    printf("Digite o novo dia de aniversario: ");
    scanf("%d", &contato->dataAniversario.dia);

    printf("Digite o novo mes de aniversario: ");
    scanf("%d", &contato->dataAniversario.mes);
    }
}

void remove_duplicados(Contato *agenda) {
    Contato *atual = agenda;
    Contato *temp = NULL;

    while (atual != NULL && atual->prox != NULL) {
        if (strcmp(atual->nome, atual->prox->nome) == 0) {
            temp = atual->prox;
            atual->prox = atual->prox->prox;
            free(temp);
        } else {
            atual = atual->prox;
        }
    }
}

void libera_agenda(Contato *agenda) {
    Contato *atual = agenda;
    Contato *temp = NULL;

    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

int main() {
    Contato *agenda = cria_agenda();
    int opcao;
    char nome[MAX_NOME];

    do {
        printf("1. Inserir Contato\n");
        printf("2. Listar Contatos\n");
        printf("3. Buscar Contato\n");
        printf("4. Editar Contato\n");
        printf("5. Remover Contato\n");
        printf("6. Remover Contatos Duplicados\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                {
                    Contato *novo_contato = (Contato *)malloc(sizeof(Contato));
                    printf("Digite o nome do contato: ");
                    scanf("%s", novo_contato->nome);
                    printf("Digite o telefone do contato: ");
                    scanf("%s", novo_contato->telefone);
                    printf("Digite o celular do contato: ");
                    scanf("%s", novo_contato->celular);
                    printf("Digite o email do contato: ");
                    scanf("%s", novo_contato->email);
                    printf("Digite o dia de aniversario do contato: ");
                    scanf("%d", &novo_contato->dataAniversario.dia);
                    printf("Digite o mes de aniversario do contato: ");
                    scanf("%d", &novo_contato->dataAniversario.mes);
                    novo_contato->prox = NULL;

                    insere_contato(&agenda, novo_contato);
                    printf("\n");
                }
                break;
            case 2:
                lista_contatos(agenda);
                printf("\n");
                break;
            case 3:
                printf("Digite o nome do contato: ");
                scanf("%s", nome);
                if (busca_contato(agenda, nome) != NULL) {
                    printf("Contato encontrado.\n");
                    printf("\n");
                } else {
                    printf("Contato nao encontrado.\n");
                    printf("\n");
                }
                break;
            case 4:
                printf("Digite o nome do contato: ");
                scanf("%s", nome);
                atualiza_contato(agenda, nome);
                printf("\n");
                break;
            case 5:
                printf("Digite o nome do contato: ");
                scanf("%s", nome);
                remove_contato(&agenda, nome);
                printf("\n");
                break;
            case 6:
                remove_duplicados(agenda);
                printf("\n");
                break;
            case 7:
                libera_agenda(agenda);
                printf("Programa encerrado.\n");
                printf("\n");
                break;
            default:
                printf("Opcao invalida.\n");
                printf("\n");
        }
    } while (opcao != 7);

    return 0;
}