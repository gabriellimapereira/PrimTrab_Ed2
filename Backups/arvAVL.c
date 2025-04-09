#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct AVL {
    int dado;
    int altura;
    struct AVL *esq, *dir;
} AVL;

AVL* criarNo(int dado) {
    AVL *novoNo = (AVL*) malloc(sizeof(AVL));
    if (novoNo != NULL) {
        novoNo->dado = dado;
        novoNo->esq = NULL;
        novoNo->dir = NULL;
        novoNo->altura = 0;
    }
    return novoNo;
}

int alturaArv(AVL *raiz) {
    int altura, alturaEsq, alturaDir;

    if (raiz) {
        alturaEsq = alturaArv(raiz->esq);
        alturaDir = alturaArv(raiz->dir);
        if (alturaEsq > alturaDir)
            altura = alturaEsq + 1;
        else 
            altura = alturaDir + 1;
    } else 
        altura = -1;

    return altura;
}

AVL* inserirNo(AVL *raiz, int dado) {
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

void imprimirEmOrdem(AVL *raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esq);
        printf("dado: %d altura: %d\n", raiz->dado, raiz->altura);
        imprimirEmOrdem(raiz->dir);
    }
}

void liberarArvore(AVL *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

void rotacaoEsq(AVL **r) {
    AVL *aux = (**r).dir;
    (**r).dir = (*aux).esq;
    (*aux).esq = (*r);
    (*r) = aux;
}

void rotacaoDir(AVL **r) {
    AVL *aux = (**r).esq;
    (**r).esq = (*aux).dir;
    (*aux).dir = (*r);
    (*r) = aux;
}

AVL** menorDir(AVL **raiz) {
    AVL **atual = *raiz;

    if ((*raiz)->esq != NULL)  
        while ((*atual)->esq != NULL) atual = &((*atual)->esq);
    
    return atual;
}

int removerNo(AVL **raiz, int dado) {
    int removeu = 1;

    if (*raiz != NULL) {
        if ((**raiz).dado == dado) {
            AVL *aux, *filho;
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
                    AVL **menor;

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

    } else 
        removeu = 0;
    
    return removeu;
}

int removerNoAntigo(AVL **raiz, int dado) {
    int removeu = 1;

    if (*raiz != NULL) {
        if ((**raiz).dado == dado) {
            AVL *aux, *filho;
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
                    AVL *menorDir = (**raiz).dir;
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
    } else 
        removeu = 0;
    

    return removeu;
}


int main() {
    printf("inicializando a main...\n");

    AVL *raiz = NULL;

    int valores[] = {1000, 300, 250, 200, 350, 2000, 3000, 3500, 3200, 1500, 1250, 1100, 1200, 1700, 1300, 100};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) raiz = inserirNo(raiz, valores[i]);


    printf("\nárvore em ordem antes da remoção:\n");
    imprimirEmOrdem(raiz);
    printf("\n");

    removerNo(&raiz, 2000);

    printf("\nárvore em ordem depois da remoção do 2000:\n");
    imprimirEmOrdem(raiz);
    printf("\n");

    liberarArvore(raiz);
    return 0;
}
