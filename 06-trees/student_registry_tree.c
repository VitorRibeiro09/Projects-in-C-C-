#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StudentNode {
    int ra;
    char name[50];
    struct StudentNode *left;
    struct StudentNode *right;
};

struct StudentNode* createStudent(int ra, const char* name) {
    struct StudentNode *newNode = (struct StudentNode*)malloc(sizeof(struct StudentNode));
    newNode->ra = ra;
    strcpy(newNode->name, name);
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
        printf("[RA: %d - %s] ", root->ra, root->name);
        inorderTraversal(root->right);
    }
}



// Função auxiliar para encontrar o menor valor de uma subrvore
struct StudentNode* minValueNode(struct StudentNode* node) {
    struct StudentNode* current = node;
    // O menor valor sempre estará o mais a esquerda possível
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Função deletar um aluno 
struct StudentNode* deleteStudent(struct StudentNode* root, int raToFind) {
    // Busca 
    if (root == NULL) return root;

    if (raToFind < root->ra) {
        root->left = deleteStudent(root->left, raToFind);
    } else if (raToFind > root->ra) {
        root->right = deleteStudent(root->right, raToFind);
    } 
    //  Encontrado
    else {
        // Caso 1 e 2: Nó com apenas um filho ou nenhum filho
        if (root->left == NULL) {
            struct StudentNode* temp = root->right;
            free(root); // Libera a memória do nó atual
            return temp; // Retorna o filho da direita 
        } else if (root->right == NULL) {
            struct StudentNode* temp = root->left;
            free(root); // Libera a memória do nó atual
            return temp; // Retorna o filho da esquerda
        }

        // Caso 3: Nó com dois filhos
        // Encontra o Sucessor Em-Ordem (o menor valor da subárvore direita)
        struct StudentNode* temp = minValueNode(root->right);

        // Copia os dados do sucessor para este nó
        root->ra = temp->ra;
        strcpy(root->name, temp->name);

        // Deleta o sucessor na subárvore direita (que agora está duplicado)
        root->right = deleteStudent(root->right, temp->ra);
    }
    return root;
}


int main() {
    struct StudentNode *root = NULL;

    // insercoes
    root = insertStudent(root, 500, "Vitor"); 
    insertStudent(root, 300, "Manuela"); // Folha (Caso 1)
    insertStudent(root, 700, "Carlos");
    insertStudent(root, 200, "Ana");
    insertStudent(root, 400, "João");
    insertStudent(root, 600, "Pedro");
    insertStudent(root, 800, "Lucas");

    printf("--- BANCO DE DADOS ACADEMICO ---\n");
    printf("Alunos matriculados (Em-Ordem):\n");
    inorderTraversal(root);
    printf("\n\n");

    // exclusões
    printf(">> Deletando Manuela (RA 300 - Caso com dois filhos no estado atual)...\n");
    root = deleteStudent(root, 300);
    
    printf(">> Deletando Pedro (RA 600 - Caso 1: Folha)...\n");
    root = deleteStudent(root, 600);

    printf("\nAlunos apos as remocoes:\n");
    inorderTraversal(root);
    printf("\n");

    return 0;
}