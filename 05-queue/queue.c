#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StudentNode {
    int ra;
    char name[50];
    int is_active; 
    struct StudentNode *left;
    struct StudentNode *right;
};

// --- FUNÇÕES DE CRIAÇÃO E INSERÇÃO ---
struct StudentNode* createStudent(int ra, const char* name) {
    struct StudentNode *newNode = (struct StudentNode*)malloc(sizeof(struct StudentNode));
    newNode->ra = ra;
    strcpy(newNode->name, name);
    newNode->is_active = 1; 
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct StudentNode* insertStudent(struct StudentNode *root, int ra, const char* name) {
    if (root == NULL) return createStudent(ra, name);
    if (ra < root->ra) root->left = insertStudent(root->left, ra, name);
    else if (ra > root->ra) root->right = insertStudent(root->right, ra, name);
    return root;
}

// --- FUNÇÃO DE EXIBIÇÃO ---
void inorderTraversal(struct StudentNode *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        
        if (root->is_active == 1) {
            printf("[RA: %d - %s] ", root->ra, root->name);
        } else {
            printf("[RA: %d - %s (INATIVO)] ", root->ra, root->name);
        }
        
        inorderTraversal(root->right);
    }
}

// --- FUNÇÃO DE LIMPEZA ---
void freeTree(struct StudentNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// --- FUNÇÃO DE REMOÇÃO DA RAIZ (Padrão Slide) ---
struct StudentNode* removerRaiz(struct StudentNode* root) {
    struct StudentNode *p, *q;
    
    if (root == NULL) return NULL; // Proteção extra caso a árvore já esteja vazia

    // Caso 1: Não tem filho à esquerda
    if (root->left == NULL) {
        q = root->right;
        free(root);
        return q;
    }
    // Caso 2: Não tem filho à direita
    if (root->right == NULL) {
        q = root->left;
        free(root);
        return q;
    }
    
    // Caso 3: Tem os dois filhos. Busca o ANTECESSOR.
    p = root;
    q = root->left;
    while (q->right != NULL) {
        p = q;
        q = q->right;
    }
    
    if (p != root) {
        p->right = q->left;
        q->left = root->left;
    }
    
    q->right = root->right;
    free(root);
    
    return q; 
}

// --- FUNÇÃO PRINCIPAL ---
int main() {
    struct StudentNode *root = NULL;

    // Inserindo os alunos. O primeiro a entrar (Vitor, 500) se torna a raiz principal.
    root = insertStudent(root, 500, "Vitor"); 
    insertStudent(root, 300, "Manuela"); 
    insertStudent(root, 700, "Carlos");

    printf("--- BANCO DE DADOS ACADEMICO ---\n");
    printf("Estado inicial da arvore:\n");
    inorderTraversal(root);
    printf("\n\n");

    // Removendo APENAS a raiz principal diretamente
    printf(">> Removendo a raiz principal (RA 500)...\n");
    
    // Como a função removerRaiz devolve o novo topo da árvore, 
    // precisamos atualizar a variável root da main:
    root = removerRaiz(root);

    printf("\nAlunos apos a exclusao da raiz principal:\n");
    inorderTraversal(root);
    printf("\n\n");

    // Limpeza final de memória
    freeTree(root);
    root = NULL; 

    return 0;
}

