#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLACA_TAM 8
#define MODELO_TAM 50
#define COR_TAM 20

typedef struct Car {
    char placa[PLACA_TAM];
    char modelo[MODELO_TAM];
    char cor[COR_TAM];
    struct Car *prox;
} Carro;

typedef struct {
    Carro *topo;
} Pilha;

void inicializarPilha(Pilha *pilha) {
    pilha->topo = NULL;
}

int pilhaVazia(Pilha *pilha) {
    return (pilha->topo == NULL);
}

Carro* criarCarro(char placa[], char modelo[], char cor[]) {
    Carro *novoCarro = malloc(sizeof(Carro));
    if (novoCarro == NULL) {
        printf("Erro: Não foi possível alocar memória para o novo carro.\n");
        return NULL;
    }
    strcpy(novoCarro->placa, placa);
    strcpy(novoCarro->modelo, modelo);
    strcpy(novoCarro->cor, cor);
    novoCarro->prox = NULL;
    return novoCarro;
}

void inserirCarro(Pilha *pilha, char placa[], char modelo[], char cor[]) {
    Carro *novoCarro = criarCarro(placa, modelo, cor);
    if (novoCarro == NULL)
        return;
    
    novoCarro->prox = pilha->topo;
    pilha->topo = novoCarro;
    printf("Carro estacionado com sucesso: Placa: %s, Modelo: %s, Cor: %s\n", novoCarro->placa, novoCarro->modelo, novoCarro->cor);
}

void removerCarro(Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        printf("Erro:O estacionamento esta vazio.\n");
        return;
    }
    Carro *carroRemovido = pilha->topo;
    pilha->topo = carroRemovido->prox;
    printf("Carro removido do estacionamento: Placa: %s, Modelo: %s, Cor: %s\n", carroRemovido->placa, carroRemovido->modelo, carroRemovido->cor);
    free(carroRemovido);
}

void exibirCarros(Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        printf("Estacionamento vazio.\n");
        return;
    }
    printf("Carros estacionados:\n");
    Carro *atual = pilha->topo;
    while (atual != NULL) {
        printf("Placa: %s, Modelo: %s, Cor: %s\n", atual->placa, atual->modelo, atual->cor);
        atual = atual->prox;
    }
}

int main() {
    Pilha pilhaEstacionamento;
    inicializarPilha(&pilhaEstacionamento);

    int opcao;
    char placa[PLACA_TAM], modelo[MODELO_TAM], cor[COR_TAM];

    do {
        printf("\nMenu:\n");
        printf("1. Estacionar carro\n");
        printf("2. Retirar carro\n");
        printf("3. Exibir carros estacionados\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a placa do carro: ");
                scanf("%s", placa);
                printf("Digite o modelo do carro: ");
                scanf("%s", modelo);
                printf("Digite a cor do carro: ");
                scanf("%s", cor);
                inserirCarro(&pilhaEstacionamento, placa, modelo, cor);
                break;
            case 2:
                removerCarro(&pilhaEstacionamento);
                break;
            case 3:
                exibirCarros(&pilhaEstacionamento);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

