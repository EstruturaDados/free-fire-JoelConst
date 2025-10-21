#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10  // Capacidade máxima da mochila

// ---------------------------
// Estrutura principal do item
// ---------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ---------------------------
// Funções do sistema
// ---------------------------
void inserirItem(Item mochila[], int *numItens);
void removerItem(Item mochila[], int *numItens);
void listarItens(Item mochila[], int numItens);
void buscarItem(Item mochila[], int numItens);
int encontrarItem(Item mochila[], int numItens, char nome[]);

// ---------------------------
// Função principal (menu)
// ---------------------------
int main() {
    Item mochila[MAX_ITENS];
    int numItens = 0;
    int opcao;

    do {
        printf("\n===== SISTEMA DE INVENTARIO - MOCHILA DE LOOT =====\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch(opcao) {
            case 1:
                inserirItem(mochila, &numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 4:
                buscarItem(mochila, numItens);
                break;
            case 0:
                printf("\nSaindo do sistema... Boa sorte na sobrevivencia!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while(opcao != 0);

    return 0;
}

// ---------------------------
// Função: Inserir novo item
// ---------------------------
void inserirItem(Item mochila[], int *numItens) {
    if (*numItens >= MAX_ITENS) {
        printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\n=== CADASTRO DE ITEM ===\n");
    printf("Nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remove o \n

    printf("Tipo (ex: arma, municao, cura): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*numItens] = novo;
    (*numItens)++;

    printf("\nItem adicionado com sucesso!\n");
    listarItens(mochila, *numItens);
}

// ---------------------------
// Função: Remover item
// ---------------------------
void removerItem(Item mochila[], int *numItens) {
    if (*numItens == 0) {
        printf("\nMochila vazia! Nenhum item para remover.\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int indice = encontrarItem(mochila, *numItens, nome);

    if (indice == -1) {
        printf("\nItem nao encontrado!\n");
        return;
    }

    // Desloca os itens para preencher o espaço
    for (int i = indice; i < *numItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*numItens)--;

    printf("\nItem removido com sucesso!\n");
    listarItens(mochila, *numItens);
}

// ---------------------------
// Função: Listar itens
// ---------------------------
void listarItens(Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    printf("\n=== ITENS NA MOCHILA ===\n");
    for (int i = 0; i < numItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// ---------------------------
// Função: Buscar item
// ---------------------------
void buscarItem(Item mochila[], int numItens) {
    char nome[30];
    printf("\nDigite o nome do item a buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int indice = encontrarItem(mochila, numItens, nome);

    if (indice == -1) {
        printf("\nItem nao encontrado.\n");
    } else {
        printf("\nItem encontrado!\n");
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[indice].nome, mochila[indice].tipo, mochila[indice].quantidade);
    }
}

// ---------------------------
// Função auxiliar: Busca sequencial
// ---------------------------
int encontrarItem(Item mochila[], int numItens, char nome[]) {
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            return i; // retorna índice do item encontrado
        }
    }
    return -1; // não encontrado
}
