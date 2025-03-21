#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    ArvBin *raiz = NULL;
    int valores[] = {100, 400, 350, 1000, 50, 700, 250};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        ArvBin *novoNo;
        alocarNo(&novoNo, valores[i]);
        insereNo(&raiz, novoNo);
    }

    printf("\nPré-ordem após inserir: \n");
    preOrdem(raiz);

    printf("\nIn-ordem após inserir: \n");
    inOrdem(raiz);

    printf("\nPós-ordem após inserir: \n");
    posOrdem(raiz);

    printf("\n");

    return 0;
}