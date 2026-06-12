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

// --- FUNÇÕES DE EXCLUSÃO ---

// 1. Exclusão Lógica (Soft Delete)
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
        // Encontrou o aluno e desativa ele
        root->is_active = 0;
        printf("Aluno %s (RA %d) desativado com sucesso. Historico mantido.\n", root->name, root->ra);
    }
}

// Função auxiliar para encontrar o menor valor (usada no Hard Delete)
struct StudentNode* findMin(struct StudentNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// 2. Exclusão Física (Hard Delete)
struct StudentNode* hardDeleteStudent(struct StudentNode* root, int raToFind) {
    if (root == NULL) {
        return root; 
    }

    if (raToFind < root->ra) {
        root->left = hardDeleteStudent(root->left, raToFind);
    } else if (raToFind > root->ra) {
        root->right = hardDeleteStudent(root->right, raToFind);
    } else {
        // Encontrou o nó para deletar fisicamente
        if (root->left == NULL) {
            struct StudentNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct StudentNode* temp = root->left;
            free(root);
            return temp;
        }

        // Caso tenha dois filhos: substitui pelo menor valor à direita
        struct StudentNode* temp = findMin(root->right);
        root->ra = temp->ra;
        strcpy(root->name, temp->name);
        root->is_active = temp->is_active;

        root->right = hardDeleteStudent(root->right, temp->ra);
    }
    return root;
}

// --- FUNÇÃO PARA LIMPAR A ÁRVORE ---

void freeTree(struct StudentNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// --- FUNÇÃO PRINCIPAL ---

int main() {
    struct StudentNode *root = NULL;

    root = insertStudent(root, 500, "Vitor"); 
    insertStudent(root, 300, "Manuela"); 
    insertStudent(root, 700, "Carlos");

    printf("--- BANCO DE DADOS ACADEMICO ---\n");
    inorderTraversal(root);
    printf("\n\n");

    // Testando a exclusão lógica (Soft Delete)
    printf(">> Trancando matricula da Manuela (RA 300)...\n");
    softDeleteStudent(root, 300);
    
    printf("\nAlunos apos exclusao logica:\n");
    inorderTraversal(root);
    printf("\n\n");

    // Testando a exclusão física (Hard Delete)
    printf(">> Removendo definitivamente a Manuela (RA 300)...\n");
    root = hardDeleteStudent(root, 300);

    printf("\nAlunos apos exclusao fisica:\n");
    inorderTraversal(root);
    printf("\n\n");

    // Liberando a memória ao final da execução
    freeTree(root);
    root = NULL; 

    return 0;
}
