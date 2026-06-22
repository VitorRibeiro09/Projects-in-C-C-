#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Apenas a estrutura do nó (a Tela do sistema)
typedef struct Tela {
    char nome_arquivo[50];
    struct Tela* prox;
} Tela;

// ==========================================
// PUSH (Inserir): Retorna o novo topo
// ==========================================
Tela* abrir_tela(Tela* topo_atual, const char* arquivo_fxml) {
    // Cria a nova tela dinamicamente
    Tela* nova_tela = (Tela*)malloc(sizeof(Tela));
    strcpy(nova_tela->nome_arquivo, arquivo_fxml);
    
    // O próximo da nova tela é o topo antigo
    nova_tela->prox = topo_atual;
    
    printf("[+] Tela '%s' carregada via Scene Builder.\n", arquivo_fxml);
    
    // Retorna a nova tela, que agora é o topo oficial
    return nova_tela;
}

// ==========================================
// POP (Remover): Retorna o novo topo
// ==========================================
Tela* fechar_tela(Tela* topo_atual) {
    if (topo_atual == NULL) {
        printf("[-] Nenhuma tela para fechar.\n");
        return NULL;
    }
    
    // Isola a tela que está no topo
    Tela* tela_fechada = topo_atual;
    
    // O novo topo passa a ser a tela de baixo
    Tela* novo_topo = topo_atual->prox;
    
    printf("[-] Fechando '%s' e voltando para a tela anterior.\n", tela_fechada->nome_arquivo);
    
    // Libera a memória da tela fechada
    free(tela_fechada);
    
    // Retorna a referência do novo topo
    return novo_topo;
}

// ==========================================
// EXIBIÇÃO
// ==========================================
void listar_telas(Tela* topo) {
    printf("\n=== HISTORICO DE TELAS ===\n");
    Tela* atual = topo;
    
    if (atual == NULL) {
        printf(" (Nenhuma tela aberta)\n");
    }
    
    while (atual != NULL) {
        printf(" -> %s\n", atual->nome_arquivo);
        atual = atual->prox;
    }
    printf("==========================\n\n");
}

int main() {
  
    Tela* pilha_telas = NULL; 


    pilha_telas = abrir_tela(pilha_telas, "Login.fxml");
    pilha_telas = abrir_tela(pilha_telas, "DashboardPrincipal.fxml");
    pilha_telas = abrir_tela(pilha_telas, "GerenciarAlunos.fxml");

    listar_telas(pilha_telas);

    pilha_telas = fechar_tela(pilha_telas);
    
    listar_telas(pilha_telas);

    return 0;
}
