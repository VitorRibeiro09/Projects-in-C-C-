#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *proximo;
} No;

// 1. Função para criar a "Cabeça" (Nó Sentinela)
No* criar_lista() {
    No *cabeca = (No*) malloc(sizeof(No));
    if (cabeca != NULL) {
        cabeca->proximo = NULL; // A lista começa vazia APÓS a cabeça
    }
    return cabeca;
}

// 2. Função de Inserção (Com Cabeça)
// Agora a funcao é void porque não precisamos 
// devolver um novo endereço para o 'main'. O endereço da cabeça é fixo
void inserir_no_inicio_com_cabeca(No* cabeca, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) return;

    novo->dado = valor;
    
    // O novo nó aponta para quem a cabeça apontava antes
    novo->proximo = cabeca->proximo;
    
    // A cabeça agora aponta para o novo nó
    cabeca->proximo = novo;
}

void imprimir_com_cabeca(No* cabeca) {
    // Começa do primeiro nó REAL, que é o próximo depois da cabeça
    No* atual = cabeca->proximo; 
    printf("Lista (com cabeca): ");
    while (atual != NULL) {
        printf("%d -> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

// 4. Função para liberar a lista 
void liberar_lista(No* lista) {
    No* atual = lista;
    while (atual != NULL) {
        No* proximo = atual->proximo; // Salva o ponteiro para o próximo antes de apagar o atual
        free(atual);                  // Libera a memória do nó atual
        atual = proximo;              // Avança para o próximo
    }
}

int main() {
    // Aqui a lista já nasce com um nó alocado
    No *minha_lista = criar_lista();

    inserir_no_inicio_com_cabeca(minha_lista, 10);
    inserir_no_inicio_com_cabeca(minha_lista, 20);
    inserir_no_inicio_com_cabeca(minha_lista, 30);

    imprimir_com_cabeca(minha_lista);

    return 0;
}
