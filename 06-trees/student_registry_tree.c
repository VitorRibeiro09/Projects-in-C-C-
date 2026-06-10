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

int main() {
    struct StudentNode *root = NULL;

    root = insertStudent(root, 500, "Vitor"); 
    insertStudent(root, 300, "Manuela"); 
    insertStudent(root, 700, "Carlos");

    printf("--- BANCO DE DADOS ACADEMICO ---\n");
    inorderTraversal(root);
    printf("\n\n");

    printf(">> Trancando matricula da Manuela (RA 300)...\n");
    softDeleteStudent(root, 300);
    
    printf("\nAlunos apos exclusao logica:\n");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
