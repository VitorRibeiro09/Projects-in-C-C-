#include <stdio.h>
#include <stdlib.h>

/**
 * Disciplina: Estrutura de Dados
 * Objetivo: Implementar uma Pilha (LIFO) - Histórico de Navegador
 */

// Nó da Pilha (Representa a página acessada)
struct Page {
    int page_id;
    struct Page *next;
};

// PUSH: Adiciona uma nova página no TOPO da pilha
struct Page* push(struct Page *top, int id) {
    struct Page *new_page = (struct Page*)malloc(sizeof(struct Page));
    new_page->page_id = id;
    new_page->next = top; // A nova página aponta para o topo antigo
    
    printf("Acessou a pagina ID [%d].\n", id);
    return new_page; // Retorna o novo topo
}

// POP: Remove a página do TOPO (Ação de "Voltar" no navegador)
struct Page* pop(struct Page *top) {
    if (top == NULL) {
        printf("Historico vazio! Nao e possivel voltar.\n");
        return NULL;
    }
    
    struct Page *temp = top;
    top = top->next; // O topo passa a ser a página de baixo
    
    printf("Apertou Voltar. Pagina ID [%d] fechada.\n", temp->page_id);
    free(temp); // Libera a memória
    return top; // Retorna o novo topo
}

// Imprime o histórico do Topo até a Base
void printStack(struct Page *top) {
    printf("Historico atual (Topo para Base): ");
    while (top != NULL) {
        printf("[%d] -> ", top->page_id);
        top = top->next;
    }
    printf("NULL\n\n");
}

int main() {
    struct Page *history = NULL; // A pilha começa vazia
    
    // Você navegou por 3 páginas
    history = push(history, 50);
    history = push(history, 60);
    history = push(history, 70); // O 70 fica no topo
    printStack(history);
    
    // Você apertou em "Voltar" uma vez
    history = pop(history); // O 70 vai sair
    printStack(history);
    
    return 0;
}