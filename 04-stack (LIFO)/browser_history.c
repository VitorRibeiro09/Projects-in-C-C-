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

    // 3. Mostra como a pilha de abas ficou 
    exibir_pilha(&abas_abertas, "ESTADO: ABAS ATUAIS");

    // 4. Fecha as duas abas do topo 
    printf(">> Fechando abas...\n");
    fechar_pagina(&abas_abertas, &historico);
    fechar_pagina(&abas_abertas, &historico);

    // 5. Mostra os dois cenários separados
    exibir_pilha(&abas_abertas, "ESTADO: ABAS RESTANTES");
    exibir_pilha(&historico, "ESTADO: HISTORICO (RECEM FECHADAS)");

    // 6. Abre mais uma página
    printf(">> Trabalhando no projeto...\n");
    abrir_pagina(&abas_abertas, "github.com/tg-control");

    // 7. Exibição final
    exibir_pilha(&abas_abertas, "VISAO GERAL: ABAS ABERTAS");
    exibir_pilha(&historico, "VISAO GERAL: HISTORICO DE NAVEGACAO");

    return 0;
}
