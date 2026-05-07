#include <stdio.h>
#include <stdlib.h>

// 1. Definição do Nó da Pilha
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 2. Operação PUSH (Empilhar)
// É idêntico ao "inserir no início" da lista sem cabeça.
Node* push(Node* top, int value) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL) return top;

    new_node->data = value;
    new_node->next = top; // O novo nó aponta para o antigo topo
    
    printf("Pushed %d to stack\n", value);
    return new_node; // O novo nó agora é o topo
}

// 3. Operação POP (Desempilhar)
// Remove o elemento do topo e libera a memória.
Node* pop(Node* top) {
    if (top == NULL) {
        printf("Stack Underflow! (Stack is empty)\n");
        return NULL;
    }

    Node *temp = top;      // Guarda o endereço do topo atual para liberar depois
    top = top->next;      // O topo agora passa a ser o próximo elemento
    
    printf("Popped %d from stack\n", temp->data);
    free(temp);           // passo importante: liberar a memória manualmente com o free()
    
    return top;
}

void display(Node* top) {
    Node* current = top;
    printf("Current Stack: ");
    while (current != NULL) {
        printf("[%d] -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    Node *stack = NULL; // Pilha começa vazia

    stack = push(stack, 10);
    stack = push(stack, 20);
    stack = push(stack, 30);

    display(stack);

    stack = pop(stack);
    display(stack);

    return 0;
}