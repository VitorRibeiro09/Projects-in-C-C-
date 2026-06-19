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

// ==========================================
// FUNÇÕES DE CRIAÇÃO E INSERÇÃO
// ==========================================

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

// ==========================================
// FUNÇÕES DE EXIBIÇÃO E LIMPEZA
// ==========================================

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

void freeTree(struct StudentNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// ==========================================
// FUNÇÕES DE EXCLUSÃO
// ==========================================

// 1. Exclusão Lógica (Apenas desativa)
void softDeleteStudent(struct StudentNode* root, int raToFind) {
    if (root == NULL) {
        printf("Erro: RA %d nao encontrado.\n", raToFind);
        return;
    }

    if (raToFind < root->ra) {
        softDeleteStudent(root->left, raToFind);
    } else if (raToFind > root->ra) {
        softDeleteStudent(root->right, raToFind);
    } else {
        root->is_active = 0;
        printf("Aluno %s (RA %d) desativado com sucesso. Historico mantido.\n", root->name, root->ra);
    }
}

// 2. O Executor: Remove um nó específico (tratando-o como raiz)
struct StudentNode* removerRaiz(struct StudentNode* root) {
    struct StudentNode *p, *q;
    
    // Tratativa extra de segurança para raiz nula
    if (root == NULL) return NULL;

    // Caso 1: Nó sem filho à esquerda (cobre o caso do nó único também)
    if (root->left == NULL) {
        q = root->right;
        free(root);
        return q;
    }
    // Caso 2: Nó sem filho à direita
    if (root->right == NULL) {
        q = root->left;
        free(root);
        return q;
    }
    
    // Caso 3: Nó com dois filhos. Busca o ANTECESSOR (maior da esquerda).
    p = root;
    q = root->left;
    while (q->right != NULL) {
        p = q;
        q = q->right;
    }
    
    // Desconecta o antecessor e refaz as ligações
    if (p != root) {
        p->right = q->left;
        q->left = root->left;
    }
    
    q->right = root->right;
    free(root);
    
    return q; // O antecessor vira o novo topo deste pedaço da árvore
}

// 3. O Rastreador: Busca o RA e chama a remoção
struct StudentNode* buscaERemove(struct StudentNode* root, int raToFind) {
    if (root == NULL) {
        return NULL; // Chegou no fundo e não achou
    }
    
    if (raToFind < root->ra) {
        // Desce pra esquerda e costura o retorno
        root->left = buscaERemove(root->left, raToFind);
    } 
    else if (raToFind > root->ra) {
        // Desce pra direita e costura o retorno
        root->right = buscaERemove(root->right, raToFind);
    } 
    else {
        // Achou o nó alvo! Ele vira a raiz da operação de remoção.
        root = removerRaiz(root); 
    }
    
    return root; // Devolve o nó reestruturado
}

// ==========================================
// FUNÇÃO PRINCIPAL
// ==========================================

int main() {
    struct StudentNode *root = NULL;

    // Inserindo dados na nossa Árvore Binária de Busca
    root = insertStudent(root, 500, "Vitor"); 
    insertStudent(root, 300, "Manuela"); 
    insertStudent(root, 700, "Carlos");

    printf("--- BANCO DE DADOS ACADEMICO ---\n");
    printf("ESTADO INICIAL:\n");
    inorderTraversal(root);
    printf("\n\n");

    // Teste 1: Exclusão Lógica
    printf(">> Operacao: Trancar matricula do Carlos (RA 700)...\n");
    softDeleteStudent(root, 700);
    inorderTraversal(root);
    printf("\n\n");

    // Teste 2: Busca e Remoção (O rastreador em ação)
    printf(">> Operacao: Apagar definitivamente a Manuela (RA 300)...\n");
    root = buscaERemove(root, 300);
    inorderTraversal(root);
    printf("\n\n");

    // Teste 3: Remover direto pela raiz principal
    printf(">> Operacao: Apagar definitivamente o Vitor (RA 500 - Raiz Principal)...\n");
    root = removerRaiz(root);
    inorderTraversal(root);
    printf("\n\n");

    // Prevenção de memory leak
    freeTree(root);
    root = NULL; 

    return 0;
}

    
    