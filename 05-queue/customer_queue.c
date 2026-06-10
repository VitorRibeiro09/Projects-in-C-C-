#include <stdio.h>
#include <stdlib.h>

/**
 * Disciplina: Estrutura de Dados
 * Objetivo: Implementar uma Fila (FIFO) - Sistema de Senhas
 */

// Nó da Fila (Representa a senha de um cliente)
struct Ticket {
    int ticket_id;
    struct Ticket *next;
};

// Estrutura para controlar o Início e o Fim da Fila
struct Queue {
    struct Ticket *front; // Quem vai ser atendido agora
    struct Ticket *rear;  // O último da fila
};

// Função para iniciar a fila vazia
struct Queue* createQueue() {
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

// ENQUEUE: Adiciona um cliente no final da fila
void enqueue(struct Queue *q, int id) {
    struct Ticket *new_ticket = (struct Ticket*)malloc(sizeof(struct Ticket));
    new_ticket->ticket_id = id;
    new_ticket->next = NULL;
    
    // Se a fila estiver vazia, ele é o primeiro e o último
    if (q->rear == NULL) {
        q->front = q->rear = new_ticket;
        printf("Senha [%d] entrou na fila.\n", id);
        return;
    }
    
    // Conecta no fim da fila
    q->rear->next = new_ticket;
    q->rear = new_ticket;
    printf("Senha [%d] entrou na fila.\n", id);
}

// DEQUEUE: Chama o primeiro cliente para atendimento
void dequeue(struct Queue *q) {
    if (q->front == NULL) {
        printf("Fila vazia! Ninguem para atender.\n");
        return;
    }
    
    struct Ticket *temp = q->front;
    q->front = q->front->next; // O início passa a ser o próximo da fila
    
    if (q->front == NULL) {
        q->rear = NULL; // A fila esvaziou totalmente
    }
    
    printf("Senha [%d] chamada para atendimento.\n", temp->ticket_id);
    free(temp); // Libera a memória do cliente atendido
}

// Imprime a fila atual
void printQueue(struct Queue *q) {
    struct Ticket *temp = q->front;
    printf("Fila atual: ");
    while (temp != NULL) {
        printf("[%d] -> ", temp->ticket_id);
        temp = temp->next;
    }
    printf("NULL\n\n");
}

int main() {
    struct Queue *q = createQueue();
    
    // Chegaram 3 pessoas
    enqueue(q, 101);
    enqueue(q, 102);
    enqueue(q, 103);
    printQueue(q);
    
    // O caixa atendeu uma pessoa
    dequeue(q);
    printQueue(q);
    
    return 0;
}