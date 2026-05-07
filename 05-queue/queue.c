#include <stdio.h>
#include <stdlib.h>

// 1. Definição do Nó
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 2. Estrutura da Fila (Guarda o início e o fim)
typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;

// Função para criar uma fila vazia
Queue* create_queue() {
    Queue *q = (Queue*) malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// 3. ENQUEUE (Enfileirar) - Adiciona no FIM
void enqueue(Queue *q, int value) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;

    // Se a fila está vazia, o novo nó é tanto a frente quanto a traseira
    if (q->rear == NULL) {
        q->front = q->rear = new_node;
        return;
    }

    // Adiciona o novo nó no fim e atualiza o ponteiro 'rear'
    q->rear->next = new_node;
    q->rear = new_node;
    printf("Enqueued: %d\n", value);
}

// 4. DEQUEUE (Desenfileirar) - Remove da FRENTE
void dequeue(Queue *q) {
    if (q->front == NULL) {
        printf("Queue Underflow!\n");
        return;
    }

    Node *temp = q->front;
    q->front = q->front->next;

    // Se a frente ficou NULL, a traseira também deve ser NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }

    printf("Dequeued: %d\n", temp->data);
    free(temp); // Limpeza de memória 
}

void display_queue(Queue *q) {
    Node *current = q->front;
    printf("Queue: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    Queue *q = create_queue();

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    display_queue(q);

    dequeue(q);
    display_queue(q);

    return 0;
}