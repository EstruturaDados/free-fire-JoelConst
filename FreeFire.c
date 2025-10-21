#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10

// =========================
// STRUCTS PRINCIPAIS
// =========================

// Estrutura base do item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// =========================
// VARIÁVEIS GLOBAIS
// =========================
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// =========================
// FUNÇÕES DO VETOR
// =========================
void inserirItemVetor(Item mochila[], int *numItens);
void removerItemVetor(Item mochila[], int *numItens);
void listarItensVetor(Item mochila[], int numItens);
int buscarSequencialVetor(Item mochila[], int numItens, char nome[]);
void ordenarVetor(Item mochila[], int numItens);
int buscarBinariaVetor(Item mochila[], int numItens, char nome[]);

// =========================
// FUNÇÕES DA LISTA ENCADEADA
// =========================
No* inserirItemLista(No* inicio);
No* removerItemLista(No* inicio);
void listarItensLista(No* inicio);
No* buscarSequencialLista(No* inicio, char nome[]);

// =========================
// FUNÇÃO AUXILIAR
// =========================
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// =========================
// MENU PRINCIPAL
// =========================
int main() {
    Item mochilaVetor[MAX_ITENS];
    int numItensVetor = 0;
    No* mochilaLista = NULL;

    int opcaoEstrutura, opcaoOperacao;
    char nomeBusca[30];
    clock_t inicio, fim;
    double tempoExecucao;

    do {
        printf("\n=== SISTEMA DE INVENTARIO - COMPARACAO DE ESTRUTURAS ===\n");
        printf("1. Usar Mochila (VETOR)\n");
        printf("2. Usar Mochila (LISTA ENCADEADA)\n");
        printf("0. Sair\n");
        printf("Escolha a estrutura: ");
        scanf("%d", &opcaoEstrutura);
        limparBuffer();

        if (opcaoEstrutura == 1) {
            // -----------------------------
            // MENU DO VETOR
            // -----------------------------
            do {
                printf("\n--- Mochila (VETOR) ---\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar item (Sequencial)\n");
                printf("5. Ordenar e buscar item (Binaria)\n");
                printf("0. Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcaoOperacao);
                limparBuffer();

                switch(opcaoOperacao) {
                    case 1:
                        inserirItemVetor(mochilaVetor, &numItensVetor);
                        break;
                    case 2:
                        removerItemVetor(mochilaVetor, &numItensVetor);
                        break;
                    case 3:
                        listarItensVetor(mochilaVetor, numItensVetor);
                        break;
                    case 4:
                        printf("Nome do item a buscar: ");
                        fgets(nomeBusca, sizeof(nomeBusca), stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        comparacoesSequencial = 0;
                        inicio = clock();
                        buscarSequencialVetor(mochilaVetor, numItensVetor, nomeBusca);
                        fim = clock();
                        tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
                        printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoesSequencial, tempoExecucao);
                        break;
                    case 5:
                        ordenarVetor(mochilaVetor, numItensVetor);
                        printf("Nome do item para busca binaria: ");
                        fgets(nomeBusca, sizeof(nomeBusca), stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        comparacoesBinaria = 0;
                        inicio = clock();
                        buscarBinariaVetor(mochilaVetor, numItensVetor, nomeBusca);
                        fim = clock();
                        tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
                        printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoesBinaria, tempoExecucao);
                        break;
                }

            } while(opcaoOperacao != 0);
        }

        else if (opcaoEstrutura == 2) {
            // -----------------------------
            // MENU DA LISTA ENCADEADA
            // -----------------------------
            do {
                printf("\n--- Mochila (LISTA ENCADEADA) ---\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar item (Sequencial)\n");
                printf("0. Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcaoOperacao);
                limparBuffer();

                switch(opcaoOperacao) {
                    case 1:
                        mochilaLista = inserirItemLista(mochilaLista);
                        break;
                    case 2:
                        mochilaLista = removerItemLista(mochilaLista);
                        break;
                    case 3:
                        listarItensLista(mochilaLista);
                        break;
                    case 4:
                        printf("Nome do item a buscar: ");
                        fgets(nomeBusca, sizeof(nomeBusca), stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        comparacoesSequencial = 0;
                        inicio = clock();
                        buscarSequencialLista(mochilaLista, nomeBusca);
                        fim = clock();
                        tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
                        printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoesSequencial, tempoExecucao);
                        break;
                }
            } while(opcaoOperacao != 0);
        }

    } while(opcaoEstrutura != 0);

    printf("\nEncerrando sistema. Sobreviva bem!\n");
    return 0;
}

// =========================
// IMPLEMENTAÇÃO - VETOR
// =========================
void inserirItemVetor(Item mochila[], int *numItens) {
    if (*numItens >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    Item novo;
    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    limparBuffer();

    mochila[*numItens] = novo;
    (*numItens)++;
    printf("Item adicionado!\n");
}

void removerItemVetor(Item mochila[], int *numItens) {
    char nome[30];
    printf("Nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Item nao encontrado.\n");
        return;
    }

    for (int i = encontrado; i < *numItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    (*numItens)--;
    printf("Item removido!\n");
}

void listarItensVetor(Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    printf("\nItens na mochila:\n");
    for (int i = 0; i < numItens; i++) {
        printf("%d. %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

int buscarSequencialVetor(Item mochila[], int numItens, char nome[]) {
    for (int i = 0; i < numItens; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Item encontrado: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return i;
        }
    }
    printf("Item nao encontrado.\n");
    return -1;
}

void ordenarVetor(Item mochila[], int numItens) {
    Item temp;
    for (int i = 0; i < numItens - 1; i++) {
        for (int j = i + 1; j < numItens; j++) {
            if (strcmp(mochila[i].nome, mochila[j].nome) > 0) {
                temp = mochila[i];
                mochila[i] = mochila[j];
                mochila[j] = temp;
            }
        }
    }
    printf("Itens ordenados por nome!\n");
}

int buscarBinariaVetor(Item mochila[], int numItens, char nome[]) {
    int inicio = 0, fim = numItens - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) {
            printf("Item encontrado: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade);
            return meio;
        } else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    printf("Item nao encontrado.\n");
    return -1;
}

// =========================
// IMPLEMENTAÇÃO - LISTA ENCADEADA
// =========================
No* inserirItemLista(No* inicio) {
    No* novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("Falha na alocacao de memoria.\n");
        return inicio;
    }

    printf("Nome: ");
    fgets(novo->dados.nome, sizeof(novo->dados.nome), stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo->dados.tipo, sizeof(novo->dados.tipo), stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    limparBuffer();

    novo->proximo = inicio;
    printf("Item adicionado!\n");
    return novo;
}

No* removerItemLista(No* inicio) {
    if (!inicio) {
        printf("Mochila vazia!\n");
        return inicio;
    }

    char nome[30];
    printf("Nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No* atual = inicio;
    No* anterior = NULL;

    while (atual && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (!atual) {
        printf("Item nao encontrado.\n");
        return inicio;
    }

    if (!anterior)
        inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("Item removido!\n");
    return inicio;
}

void listarItensLista(No* inicio) {
    if (!inicio) {
        printf("Mochila vazia.\n");
        return;
    }

    No* atual = inicio;
    int i = 1;
    while (atual) {
        printf("%d. %s | Tipo: %s | Quantidade: %d\n",
               i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

No* buscarSequencialLista(No* inicio, char nome[]) {
    No* atual = inicio;
    while (atual) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Item encontrado: %s | Tipo: %s | Quantidade: %d\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            return atual;
        }
        atual = atual->proximo;
    }
    printf("Item nao encontrado.\n");
    return NULL;
}
