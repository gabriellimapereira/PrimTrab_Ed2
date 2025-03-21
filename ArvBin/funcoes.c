#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>

void alocarNo(ArvBin **no, int valor) {
    ArvBin* novoNo = (ArvBin*) malloc(sizeof(ArvBin));
    *no = novoNo;
    if (*no != NULL) {
        (**no).dir = NULL;
        (**no).esq = NULL;
        (**no).info = valor;
    }
}

int buscaBin(ArvBin *raiz, int valor) {
    int encontrou = 0;

    if (raiz != NULL) {
        if ((*raiz).info == valor) {
            encontrou = 1;
        } else {
            if (valor < (*raiz).info) {
                encontrou = buscaBin((*raiz).esq, valor);
            } else {
                encontrou = buscaBin((*raiz).dir, valor);
            }
        }
    }

    return encontrou;
}

int insereNo(ArvBin **raiz, ArvBin *no) {
    int inseriu = 0;

    if (*raiz == NULL) {
        *raiz = no;
    } else if ((*no).info < (**raiz).info) {
        inseriu = insereNo(&((**raiz).esq), no);
    } else if ((*no).info > (**raiz).info) {
        inseriu = insereNo(&((**raiz).dir), no);
    } else {
        inseriu = 1;
    }

    return inseriu;
}

void preOrdem(ArvBin *raiz) {
    if (raiz != NULL) {
        printf("%d ", (*raiz).info);
        preOrdem((*raiz).esq);
        preOrdem((*raiz).dir);
    }
}

void inOrdem(ArvBin *raiz) {
    if (raiz != NULL) {
        preOrdem((*raiz).esq);
        printf("%d ", (*raiz).info);
        preOrdem((*raiz).dir);
    }
}
void posOrdem(ArvBin *raiz) {
    if (raiz != NULL) {
        preOrdem((*raiz).esq);
        preOrdem((*raiz).dir);
        printf("%d ", (*raiz).info);
    }
}
