#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10

// ============================
// ESTRUTURAS DE DADOS
// ============================

// Estrutura base do item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ============================
// VARIÁVEIS GLOBAIS
// ============================
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ============================
// PROTÓTIPOS DE FUNÇÕES
// ============================

// --- Vetor ---
void inserirItemVetor(Item mochila[], int *numItens);
void removerItemVetor(Item mochila[], int *numItens);
void listarItensVetor(Item mochila[], int numItens);
int buscarSequencialVetor(Item mochila[], int numItens, char nome[]);
int buscarBinariaVetor(Item mochila[], int numItens, char nome[]);
void ordenarBubble(Item mochila[], int numItens);
void ordenarInsertion(Item mochila[], int numItens);
void ordenarSelection(Item mochila[], int numItens);

// --- Lista encadeada ---
No* inserirItemLista(No* inicio);
No* removerItemLista(No* inicio);
void listarItensLista(No* inicio);
No* buscarSequencialLista(No* inicio, char nome[]);

// --- Auxiliares ---
void limparBuffer();
void medirTempo(void (*algoritmo)(Item[], int), Item vetor[], int numItens);
void exibirComparacao(double tempo, int comparacoes, const char *metodo);

// ============================
// FUNÇÃO PRINCIPAL
// ============================
int main() {
    Item mochilaVetor[MAX_ITENS];
    int numItensVetor = 0;
    No* mochilaLista = NULL;

    int opcaoEstrutura, opcaoOperacao, opcaoOrdenacao;
    char nomeBusca[30];

    do {
        printf("\n=== SISTEMA DE INVENTARIO AVANCADO ===\n");
        printf("1. Usar Mochila (VETOR)\n");
        printf("2. Usar Mochila (LISTA ENCADEADA)\n");
        printf("0. Sair\n");
        printf("Escolha a estrutura: ");
        scanf("%d", &opcaoEstrutura);
        limparBuffer();

        if (opcaoEstrutura == 1) {
            do {
                printf("\n--- Mochila (VETOR) ---\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar item (Sequencial)\n");
                printf("5. Ordenar vetor e buscar item (Binaria)\n");
                printf("0. Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcaoOperacao);
                limparBuffer();

                switch(opcaoOperacao) {
                    case 1:
                        inserirItemVetor(mochilaVetor, &numItensVetor);
                        listarItensVetor(mochilaVetor, numItensVetor);
                        break;
                    case 2:
                        removerItemVetor(mochilaVetor, &numItensVetor);
                        listarItensVetor(mochilaVetor, numItensVetor);
                        break;
                    case 3:
                        listarItensVetor(mochilaVetor, numItensVetor);
                        break;
                    case 4: {
                        printf("Nome do item: ");
                        fgets(nomeBusca, sizeof(nomeBusca), stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        comparacoesSequencial = 0;

                        clock_t inicio = clock();
                        buscarSequencialVetor(mochilaVetor, numItensVetor, nomeBusca);
                        clock_t fim = clock();

                        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
                        exibirComparacao(tempo, comparacoesSequencial, "Busca Sequencial");
                        break;
                    }
                    case 5:
                        printf("\nEscolha o método de ordenação:\n");
                        printf("1. Bubble Sort\n");
                        printf("2. Insertion Sort\n");
                        printf("3. Selection Sort\n");
                        printf("Escolha: ");
                        scanf("%d", &opcaoOrdenacao);
                        limparBuffer();

                        switch(opcaoOrdenacao) {
                            case 1: medirTempo(ordenarBubble, mochilaVetor, numItensVetor); break;
                            case 2: medirTempo(ordenarInsertion, mochilaVetor, numItensVetor); break;
                            case 3: medirTempo(ordenarSelection, mochilaVetor, numItensVetor); break;
                            default: printf("Opcao invalida!\n"); continue;
                        }

                        listarItensVetor(mochilaVetor, numItensVetor);

                        printf("\nNome do item para busca binária: ");
                        fgets(nomeBusca, sizeof(nomeBusca), stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                        comparacoesBinaria = 0;
                        clock_t inicio = clock();
                        buscarBinariaVetor(mochilaVetor, numItensVetor, nomeBusca);
                        clock_t fim = clock();

                        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
                        exibirComparacao(tempo, comparacoesBinaria, "Busca Binaria");
                        break;
                }

            } while(opcaoOperacao != 0);
        }
        else if (opcaoEstrutura == 2) {
            int opcaoLista;
            do {
                printf("\n--- Mochila (LISTA ENCADEADA) ---\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar item (Sequencial)\n");
                printf("0. Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcaoLista);
                limparBuffer();

                switch(opcaoLista) {
                    case 1:
                        mochilaLista = inserirItemLista(mochilaLista);
                        listarItensLista(mochilaLista);
                        break;
                    case 2:
                        mochilaLista = removerItemLista(mochilaLista);
                        listarItensLista(mochilaLista);
                        break;
                    case 3:
                        listarItensLista(mochilaLista);
                        break;
                    case 4:
                        printf("Nome do item: ");
                        fgets(nomeBusca, sizeof(nomeBusca), stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                        comparacoesSequencial = 0;
                        clock_t inicio = clock();
                        buscarSequencialLista(mochilaLista, nomeBusca);
                        clock_t fim = clock();

                        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
                        exibirComparacao(tempo, comparacoesSequencial, "Busca Sequencial (Lista)");
                        break;
                }
            } while(opcaoLista != 0);
        }

    } while(opcaoEstrutura != 0);

    printf("\nEncerrando o sistema. Boa sorte na sua jornada!\n");
    return 0;
}

// ============================
// IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES
// ============================

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void medirTempo(void (*algoritmo)(Item[], int), Item vetor[], int numItens) {
    clock_t inicio = clock();
    algoritmo(vetor, numItens);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\nTempo de ordenação: %.6f s\n", tempo);
}

void exibirComparacao(double tempo, int comparacoes, const char *metodo) {
    printf("\n=== RESULTADOS DE DESEMPENHO ===\n");
    printf("Método: %s\n", metodo);
    printf("Tempo de execução: %.6f s\n", tempo);
    printf("Número de comparações: %d\n", comparacoes);
}

// ============================
// IMPLEMENTAÇÃO - VETOR
// ============================
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
        printf("\nMochila vazia.\n");
        return;
    }

    printf("\n=== ITENS NA MOCHILA ===\n");
    for (int i = 0; i < numItens; i++) {
        printf("%d. Nome: %-15s | Tipo: %-10s | Quantidade: %d\n",
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

// --- Algoritmos de Ordenação ---
void ordenarBubble(Item mochila[], int numItens) {
    for (int i = 0; i < numItens - 1; i++) {
        for (int j = 0; j < numItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("Vetor ordenado com Bubble Sort!\n");
}

void ordenarInsertion(Item mochila[], int numItens) {
    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0 && strcmp(mochila[j].nome, chave.nome) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }
    printf("Vetor ordenado com Insertion Sort!\n");
}

void ordenarSelection(Item mochila[], int numItens) {
    for (int i = 0; i < numItens - 1; i++) {
        int min = i;
        for (int j = i + 1; j < numItens; j++) {
            if (strcmp(mochila[j].nome, mochila[min].nome) < 0)
                min = j;
        }
        if (min != i) {
            Item temp = mochila[i];
            mochila[i] = mochila[min];
            mochila[min] = temp;
        }
    }
    printf("Vetor ordenado com Selection Sort!\n");
}

// ============================
// IMPLEMENTAÇÃO - LISTA ENCADEADA
// ============================
No* inserirItemLista(No* inicio) {
    No* novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("Falha de memoria!\n");
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
        printf("\nMochila vazia.\n");
        return;
    }

    printf("\n=== ITENS NA LISTA ===\n");
    No* atual = inicio;
    int i = 1;
    while (atual) {
        printf("%d. Nome: %-15s | Tipo: %-10s | Quantidade: %d\n",
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
