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

// ==========================================
// CRIAÇÃO DA FILA (COM NÓ CABEÇA)
// ==========================================
struct Queue* createQueue() {
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    
    // Cria o nó cabeça (fantasma). O ID dele não importa, pois nunca será lido.
    struct Ticket *dummy = (struct Ticket*)malloc(sizeof(struct Ticket));
    dummy->ticket_id = -1; 
    dummy->next = NULL;
    
    // Tanto o início quanto o fim apontam para o nó cabeça inicialmente
    q->front = dummy;
    q->rear = dummy;
    
    return q;
}

// ==========================================
// INSERÇÃO (MUITO MAIS SIMPLES AGORA)
// ==========================================
void enqueue(struct Queue *q, int id) {
    struct Ticket *new_ticket = (struct Ticket*)malloc(sizeof(struct Ticket));
    new_ticket->ticket_id = id;
    new_ticket->next = NULL;
    

    q->rear->next = new_ticket;
    q->rear = new_ticket;
}

void enqueueNode(struct Queue *q, struct Ticket *ticket) {
    ticket->next = NULL; 
    
    // Mesma lógica simplificada aqui
    q->rear->next = ticket;
    q->rear = ticket;
}

// ==========================================
// REMOÇÃO
// ==========================================
struct Ticket* dequeue(struct Queue *q) {
    // A fila está vazia se o nó cabeça não aponta para ninguém
    // (ou seja, front e rear apontam para o mesmo lugar)
    if (q->front->next == NULL) {
        printf("Fila vazia! Ninguem para atender.\n");
        return NULL;
    }
    
    // O nó real a ser removido é o que vem DEPOIS da cabeça
    struct Ticket *temp = q->front->next;
    
    // A cabeça agora "pula" o nó que está saindo e aponta para o próximo
    q->front->next = temp->next; 
    
    // Seremover o último elemento real da fila
    // o rear precisa voltar a apontar para a cabeça!
    if (q->front->next == NULL) {
        q->rear = q->front; 
    }
    
    temp->next = NULL; 
    return temp; 
}

// ==========================================
// EXIBIÇÃO
// ==========================================
void printQueue(struct Queue *q, const char* nome_fila) {
    // ler a partir do elemento DEPOIS da cabeça
    struct Ticket *temp = q->front->next;
    
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
        // Salva o nó diretamente na fila de histórico sem alocar nova memória
        enqueueNode(historico_atendimentos, atendido); 
    }
    
    printf("\nESTADO ATUAL DO SISTEMA:\n");
    printQueue(fila_espera, "Fila de Espera");
    printQueue(historico_atendimentos, "Historico (Atendidos)");
    
    return 0;
}

    
    
    
    