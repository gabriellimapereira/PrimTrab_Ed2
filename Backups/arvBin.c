#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct ArvBin {
    int dado;
    struct ArvBin *esq, *dir;
} ArvBin;

ArvBin* criarNo(int dado) {
    ArvBin *novoNo = (ArvBin*) malloc(sizeof(ArvBin));
    if (novoNo != NULL) {
        novoNo->dado = dado;
        novoNo->esq = NULL;
        novoNo->dir = NULL;
    }
    return novoNo;
}

ArvBin* inserirNo(ArvBin *raiz, int dado) {
    if (raiz == NULL) {
        return criarNo(dado);
    }
    if (dado < raiz->dado) {
        raiz->esq = inserirNo(raiz->esq, dado);
    } else if (dado > raiz->dado) {
        raiz->dir = inserirNo(raiz->dir, dado);
    }
    return raiz;
}

void imprimirEmOrdem(ArvBin *raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esq);
        printf("%d ", raiz->dado);
        imprimirEmOrdem(raiz->dir);
    }
}

void liberarArvore(ArvBin *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

ArvBin** menorDir(ArvBin **raiz) {
    ArvBin **atual = *raiz;

    if ((*raiz)->esq != NULL)  
        while ((*atual)->esq != NULL) atual = &((*atual)->esq);

    return atual;
}


int removerNo(ArvBin **raiz, int dado) {
    int removeu = 1;

    if (*raiz != NULL) {
        if ((**raiz).dado == dado) {
            ArvBin *aux, *filho;
            if ((**raiz).dir == NULL && (**raiz).esq == NULL) {
                aux = *raiz;
                *raiz = NULL;
                free(aux);
            } else {
                if ((**raiz).esq == NULL || (**raiz).dir == NULL) {
                    filho = (**raiz).esq ? (**raiz).esq : (**raiz).dir;
                    aux = *raiz;
                    *raiz = filho;
                    free(aux);
                } else {
                    ArvBin **menor;

                    menor = menorDir(&((*raiz)->dir)); // novo

                    (**raiz).dado = (*menor)->dado;
                    aux = (*menor);
                    (*menor) = (*menor)->dir;
                    free(aux);
                }
            }
        } else {
            if ((**raiz).dado > dado) {
                removeu = removerNo(&((**raiz).esq), dado);
            } else {
                removeu = removerNo(&((**raiz).dir), dado);
            }
        }
    } else {
        removeu = 0;
    }
    return removeu;
}

int removerNoAntigo(ArvBin **raiz, int dado) {
    int removeu = 1;

    if (*raiz != NULL) {
        if ((**raiz).dado == dado) {
            ArvBin *aux, *filho;
            if ((**raiz).dir == NULL && (**raiz).esq == NULL) {
                aux = *raiz;
                *raiz = NULL;
                free(aux);
            } else {
                if ((**raiz).esq == NULL || (**raiz).dir == NULL) {
                    filho = (**raiz).esq ? (**raiz).esq : (**raiz).dir;
                    aux = *raiz;
                    *raiz = filho;
                    free(aux);
                } else {
                    ArvBin *menorDir = (**raiz).dir;
                    while ((*menorDir).esq != NULL) menorDir = (*menorDir).esq;

                    ((**raiz)).dado = (*menorDir).dado;
                    removeu = removerNo(&((**raiz).dir), (*menorDir).dado);
                }
            }
        } else {
            if ((**raiz).dado > dado) {
                removeu = removerNoAntigo(&((**raiz).esq), dado);
            } else {
                removeu = removerNoAntigo(&((**raiz).dir), dado);
            }
        }
    } else {
        removeu = 0;
    }

    return removeu;
}


int main() {
    printf("inicializando a main...\n");

    ArvBin *raiz = NULL;

    int valores[] = {1000, 300, 250, 200, 350, 2000, 3000, 3500, 3200, 1500, 1250, 1100, 1200, 1700, 1300, 100};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        raiz = inserirNo(raiz, valores[i]);
    }

    printf("\nárvore em ordem antes da remoção:\n");
    imprimirEmOrdem(raiz);
    printf("\n");

    removerNo(&raiz, 1000);

    printf("\nárvore em ordem depois da remoção do 2000:\n");
    imprimirEmOrdem(raiz);
    printf("\n");

    liberarArvore(raiz);
    return 0;
}
