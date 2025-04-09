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

int fatorBalanceamento(AVL *r) { //esq - dir
    int altE = -1, altD = -1;
    if ((*r).dir) {
        altD = (*r).dir->altura;
    } 
    if ((*r).esq) {
        altE = (*r).esq->altura;
    }

    return altE - (altD);
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

void balanceamento(AVL **r) {
    int fb;

    fb = fatorBalanceamento(*r);
    if (fb == 2) {
        int fbEsq = fatorBalanceamento((**r).esq);
        if (fbEsq < 0) rotacaoEsq(&((**r).esq));
        rotacaoDir(r);
    } else if (fb == -2) {
        int fbDir = fatorBalanceamento((**r).dir);
        if (fbDir > 0) rotacaoDir(&((**r).dir));
        rotacaoEsq(r);
    }
}

int insere(AVL **raiz, AVL *novoNo) {
    int inseriu = 1;

    if (*raiz == NULL) {
        *raiz = novoNo;
    } else if ((**raiz).dado <  (*novoNo).dado) {
        inseriu = insere(&((**raiz).dir), novoNo);
    } else if ((**raiz).dado > (*novoNo).dado) {
        inseriu = insere(&((**raiz).esq), novoNo);
    } else 
        inseriu = 0;
    

    if (inseriu) {
        balanceamento(raiz);
        (**raiz).altura = alturaArv((*raiz));
    }

    return inseriu;
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

AVL** menorDir(AVL **raiz) {
    AVL **atual = raiz;

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

    if (*raiz && removeu) {
        balanceamento(raiz);
        (**raiz).altura = alturaArv((*raiz));
    }
    
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

    for (int i = 0; i < n; i++) {
        AVL *novoNo = criarNo(valores[i]);
        if (novoNo != NULL) {
            insere(&raiz, novoNo);
            printf("\ninseriu o %d!", novoNo->dado);
            printf("\nárvore em ordem antes da nova inserção:\n");
            imprimirEmOrdem(raiz);
        }
    }

    printf("\nárvore em ordem antes da remoção:\n");
    imprimirEmOrdem(raiz);
    printf("\n");

    printf("removendo...\n");
    removerNo(&raiz, 350);

    printf("\nárvore em ordem depois da remoção do 350:\n");
    imprimirEmOrdem(raiz);
    printf("\n");

    liberarArvore(raiz);
    return 0;
}