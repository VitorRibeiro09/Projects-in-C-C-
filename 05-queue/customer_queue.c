#include <stdio.h>
#include <stdlib.h>


struct Ticket {
    int ticket_id;
    struct Ticket *next;
};


struct Queue {
    struct Ticket *front; 
    struct Ticket *rear;  
};


struct Queue* createQueue() {
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}


void enqueue(struct Queue *q, int id) {
    struct Ticket *new_ticket = (struct Ticket*)malloc(sizeof(struct Ticket));
    new_ticket->ticket_id = id;
    new_ticket->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = new_ticket;
        return;
    }
    
    q->rear->next = new_ticket;
    q->rear = new_ticket;
}


void enqueueNode(struct Queue *q, struct Ticket *ticket) {
    ticket->next = NULL; 
    
    if (q->rear == NULL) {
        q->front = q->rear = ticket;
        return;
    }
    
    q->rear->next = ticket;
    q->rear = ticket;
}


struct Ticket* dequeue(struct Queue *q) {
    if (q->front == NULL) {
        printf("Fila vazia! Ninguem para atender.\n");
        return NULL;
    }
    
    struct Ticket *temp = q->front;
    q->front = q->front->next; 
    
    if (q->front == NULL) {
        q->rear = NULL; 
    }
    
    temp->next = NULL; 
    return temp; 
}

// Imprime a fila
void printQueue(struct Queue *q, const char* nome_fila) {
    struct Ticket *temp = q->front;
    printf("[%s]: ", nome_fila);
    if (temp == NULL) {
        printf("Vazia\n");
        return;
    }
    while (temp != NULL) {
        printf("%d -> ", temp->ticket_id);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    
    struct Queue *fila_espera = createQueue();
    struct Queue *historico_atendimentos = createQueue();
    
    printf("--- SISTEMA DE ATENDIMENTO ---\n\n");
 
    printf(">> Gerando senhas...\n");
    enqueue(fila_espera, 101);
    enqueue(fila_espera, 102);
    enqueue(fila_espera, 103);
    
    printQueue(fila_espera, "Fila de Espera");
    printQueue(historico_atendimentos, "Historico");
    
    printf("\n>> Chamando proxima senha...\n");
  
    struct Ticket *atendido = dequeue(fila_espera);
    if (atendido != NULL) {
        printf("Atendendo senha [%d] no Guiche 1.\n", atendido->ticket_id);
        enqueueNode(historico_atendimentos, atendido); // Salva no banco de dados / painel
    }
    
    printf("\nESTADO ATUAL DO SISTEMA:\n");
    printQueue(fila_espera, "Fila de Espera");
    printQueue(historico_atendimentos, "Historico (Atendidos)");
    
    return 0;
}
