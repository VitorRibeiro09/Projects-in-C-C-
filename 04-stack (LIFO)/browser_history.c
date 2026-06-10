#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Page {
    char url[100];
    struct Page *next;
};


struct Stack {
    struct Page *top;
};


void initStack(struct Stack *s) {
    s->top = NULL;
}


void push(struct Stack *s, const char* url) {
    struct Page *new_page = (struct Page*)malloc(sizeof(struct Page));
    strcpy(new_page->url, url);
    new_page->next = s->top;
    s->top = new_page;
}


struct Page* pop(struct Stack *s) {
    if (s->top == NULL) return NULL;
    
    struct Page *temp = s->top;
    s->top = s->top->next; 
    temp->next = NULL;     
    
    return temp; /
}


void printStack(struct Stack *s, const char* stack_name) {
    struct Page *current = s->top;
    printf("[%s]: ", stack_name);
    if (current == NULL) {
        printf("Vazia\n");
        return;
    }
    while (current != NULL) {
        printf("%s -> ", current->url);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
  
    struct Stack back_stack;
    struct Stack forward_stack;
    
    initStack(&back_stack);
    initStack(&forward_stack);

    printf("--- NAVEGANDO NA INTERNET ---\n");
    push(&back_stack, "google.com");
    push(&back_stack, "fatec.edu.br");
    push(&back_stack, "github.com"); /
    
    printStack(&back_stack, "Pilha VOLTAR");
    printStack(&forward_stack, "Pilha AVANCAR");

    printf("\n--- APERTOU O BOTAO [VOLTAR] ---\n");
  
    struct Page *page_to_go_back = pop(&back_stack);
    if (page_to_go_back != NULL) {
        printf("Saindo de: %s\n", page_to_go_back->url);
        push(&forward_stack, page_to_go_back->url); 
        free(page_to_go_back); 
    }

    printStack(&back_stack, "Pilha VOLTAR");
    printStack(&forward_stack, "Pilha AVANCAR");

    printf("\n--- APERTOU O BOTAO [AVANCAR] ---\n");
  
    struct Page *page_to_go_forward = pop(&forward_stack);
    if (page_to_go_forward != NULL) {
        printf("Indo para: %s\n", page_to_go_forward->url);
        push(&back_stack, page_to_go_forward->url);
        free(page_to_go_forward);
    }

    printStack(&back_stack, "Pilha VOLTAR");
    printStack(&forward_stack, "Pilha AVANCAR");

    return 0;
}
