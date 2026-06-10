#include <stdio.h>
#include <stdlib.h>

// 1. Definição do "molde" do nó, o typedef.
typedef struct No {
    int dado;           // O valor que é guardado
    struct No *proximo; // O "fio" que aponta para o próximo endereço
} No;

// 2. Função para inserir no início (Sem Cabeça)
// Ela recebe a lista atual e o valor, e retorna o novo começo da lista.
No* inserir_no_inicio(No* lista, int valor) {
    // Criando a memória ao sistema para o novo nó
    No *novo = (No*) malloc(sizeof(No));
    
    if (novo == NULL) {
        printf("Erro de memória!\n");
        return lista;
    }

    novo->dado = valor;       // Coloca o valor no nó
    novo->proximo = lista;    // O novo nó aponta para quem era o antigo primeiro
    
    return novo;              // O novo nó agora é o começo da lista
}

// 3. Função para imprimir a lista
void imprimir(No* lista) {
    No* atual = lista;
    printf("Lista: ");
    while (atual != NULL) {   // Percorrem até encontrar o vazio
        printf("%d -> ", atual->dado);
        atual = atual->proximo; // Vai até o proximo endereco
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
    // Começa com a lista vazia 
    No *minha_lista = NULL;

    // Inserindo elementos
    minha_lista = inserir_no_inicio(minha_lista, 10);
    minha_lista = inserir_no_inicio(minha_lista, 20);
    minha_lista = inserir_no_inicio(minha_lista, 30);

    imprimir(minha_lista);


    return 0; 
}

