#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *esq, *dir;
} No;

No* criarNo(int dado) {
    No *novoNo = (No*) malloc(sizeof(No));
    if (novoNo != NULL) {
        novoNo->dado = dado;
        novoNo->esq = NULL;
        novoNo->dir = NULL;
    }
    return novoNo;
}

No* inserirNo(No *raiz, int dado) {
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

void imprimirEmOrdem(No *raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esq);
        printf("%d ", raiz->dado);
        imprimirEmOrdem(raiz->dir);
    }
}

void liberarArvore(No *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

No** menorDir(No *r) {
    No **menor;

    if (r->esq != NULL) {
        if (r->esq->esq != NULL) {
            menor = &(r->esq->esq);
        } else {
            menor = menorDir(r->esq);
        }
    } else {
        menor = &(r);
    }

    return menor;
}

int direitaSemMenor(No *r) {
    int valor;

    if (r->dir->esq == NULL) {
        valor = 1;
    } else {
        valor = 0;
    }
     
    return valor;
}

int removerNo(No **raiz, int dado) {
    int removeu = 1;

    if (*raiz != NULL) {
        if ((**raiz).dado == dado) {
            No *aux, *filho;
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
                    No **menor;

                    if (direitaSemMenor(*raiz)) {
                        menor = &((*raiz)->dir);
                    } else {
                        menor = menorDir((*raiz)->dir);
                    }

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

int main() {
    No *raiz = NULL;
    int valores[] = {1000, 300, 250, 200, 350, 2000, 3000, 3500, 3200, 1500, 1250, 1100, 1200, 1700, 1300, 100};
    
    for (int i = 0; i < 13; i++) {
        raiz = inserirNo(raiz, valores[i]);
    }
    
    printf("\nÁrvore em ordem antes da remoção: ");
    imprimirEmOrdem(raiz);
    printf("\n");
    
    removerNo(&raiz, 1500);

    printf("\nÁrvore em ordem após remover 1000: ");
    imprimirEmOrdem(raiz);
    printf("\n");
    
    liberarArvore(raiz);
    return 0;
}