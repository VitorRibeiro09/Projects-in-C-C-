#include <stdio.h>
#include <stdlib.h> // Biblioteca necessária para malloc e free

/**
 * Disciplina: Estrutura de Dados
 * Objetivo: Demonstrar alocação dinâmica de memória em C.
 */

int main() {
    int n;
    int *vetor;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    // Alocação dinâmica: solicitando memória ao sistema operacional
    // O cast (int *) define que o bloco de memória será tratado como inteiros
    vetor = (int *) malloc(n * sizeof(int));

    // Verificação de segurança: a alocação pode falhar se não houver memória
    if (vetor == NULL) {
        printf("Erro: Memoria insuficiente!\n");
        return 1;
    }

    // Preenchendo o vetor (Lógica matemática simples)
    for (int i = 0; i < n; i++) {
        vetor[i] = i * 2; 
        printf("Posicao [%d] - Valor: %d - Endereco: %p\n", i, vetor[i], &vetor[i]);
    }

    //  Tudo que é alocado com malloc deve ser liberado com free
    free(vetor);
    printf("\nMemoria liberada com sucesso.\n");

    return 0;
}