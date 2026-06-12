#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pagina {
    char url[150];
    struct Pagina* prox;
} Pagina;

typedef struct Pilha {
    Pagina* topo;
} Pilha;

// Inicializa a pilha vazia
void inicializar(Pilha* p) {
    p->topo = NULL;
}

// Abre uma nova aba (Push)
void abrir_pagina(Pilha* p, const char* url) {
    Pagina* novaPagina = (Pagina*)malloc(sizeof(Pagina));
    strcpy(novaPagina->url, url);
    novaPagina->prox = p->topo;
    p->topo = novaPagina;
    printf("[+] Pagina '%s' aberta.\n", url);
}

void fechar_pagina(Pilha* navegacao, Pilha* historico) {
    if (navegacao->topo == NULL) {
        printf("[-] Nenhuma pagina aberta no momento.\n");
        return;
    }

    // Isola o nó do topo
    Pagina* paginaFechada = navegacao->topo;
    
    // Atualiza o topo da navegação
    navegacao->topo = paginaFechada->prox;

    // Transfere o nó para o histórico
    paginaFechada->prox = historico->topo;
    historico->topo = paginaFechada;

    printf("[-] Pagina '%s' fechada e movida para o historico.\n", paginaFechada->url);
}

void exibir_pilha(Pilha* p, const char* titulo) {
    printf("\n--- %s ---\n", titulo);
    if (p->topo == NULL) {
        printf("(Vazio)\n");
        return;
    }
    
    Pagina* atual = p->topo;
    while (atual != NULL) {
        printf(" -> %s\n", atual->url);
        atual = atual->prox;
    }
    printf("-------------------\n\n");
}

// --- NOVAS FUNÇÕES ---

void excluir_item_historico(Pilha* historico, const char* url_alvo) {
    if (historico->topo == NULL) {
        printf("[-] O historico ja esta vazio.\n");
        return;
    }

    Pagina* atual = historico->topo;
    Pagina* anterior = NULL;

    while (atual != NULL && strcmp(atual->url, url_alvo) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("[-] Pagina '%s' nao encontrada no historico.\n", url_alvo);
        return;
    }

    if (anterior == NULL) {
        historico->topo = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("[!] Pagina '%s' excluida do historico isoladamente.\n", url_alvo);
}

void limpar_historico(Pilha* historico) {
    Pagina* atual = historico->topo;
    Pagina* proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    
    historico->topo = NULL;
    printf("[!] Historico limpo com sucesso.\n");
}

int main() {
    Pilha abas_abertas;
    Pilha historico;

    // 1. Inicializa as pilhas
    inicializar(&abas_abertas);
    inicializar(&historico);

    printf("======= SIMULACAO DE NAVEGADOR =======\n\n");

    // 2. Abre algumas páginas em sequência
    abrir_pagina(&abas_abertas, "kumon.com.br/portal-do-professor");
    abrir_pagina(&abas_abertas, "fatec.edu.br/banco-de-dados");
    abrir_pagina(&abas_abertas, "docs.oracle.com/javafx");
    abrir_pagina(&abas_abertas, "geoguessr.com/mapa-mundi");

    // 4. Fecha três abas
    printf("\n>> Fechando abas...\n");
    fechar_pagina(&abas_abertas, &historico);
    fechar_pagina(&abas_abertas, &historico);
    fechar_pagina(&abas_abertas, &historico);

    // Mostra o histórico inicial
    exibir_pilha(&historico, "ESTADO: HISTORICO ATUAL");

    // 5. Testando a exclusão de um item específico do histórico
    printf(">> Apagando um rastro especifico...\n");
    excluir_item_historico(&historico, "docs.oracle.com/javafx");
    
    exibir_pilha(&historico, "ESTADO: HISTORICO POS-EXCLUSAO ESPECIFICA");

    // 6. Limpando todo o histórico
    printf(">> Limpando todo o historico...\n");
    limpar_historico(&historico);

    exibir_pilha(&historico, "VISAO GERAL: HISTORICO FINAL");

 
    return 0;
}
