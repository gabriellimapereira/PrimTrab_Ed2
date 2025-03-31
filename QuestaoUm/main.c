#include <stdio.h>
#include <stdlib.h>


int main() {
    ArvMusica *raiz = inicializarArvMus();
    InfoMusica info;
    int i, valor;
    
    printf("\n--- INSERINDO 5 VALORES ---\n");
    for (i = 0; i < 5; i++) {
        InfoMusica dado = lerInfoMusica();
        ArvMusica *novoNo = alocarNoMusica(dado);
        if (novoNo)
            insereNoMus(&raiz, novoNo);
    }

    printf("\n--- ÁRVORE APÓS INSERÇÕES ---\n");
    imprimeArvMus(raiz);
    printf("\n");

    printf("\n--- REMOVENDO 5 VALORES ---\n");
    for (i = 0; i < 5; i++) {
        printf("Digite um valor para remover: ");
        scanf("%d", &valor);
        if (removerMus(&raiz, valor)) {
            printf("Valor %d removido!\n", valor);
            imprimeArvMus(raiz);
        } else {
            printf("Valor %d não encontrado.\n", valor);
        }
    }

    printf("\n--- ÁRVORE APÓS REMOÇÕES ---\n");
    imprimeArvMus(raiz);
    printf("\n");

    printf("Raiz: %d\n", (*raiz).info.dado);

    liberaArvMus(raiz);
    return 0;
}
