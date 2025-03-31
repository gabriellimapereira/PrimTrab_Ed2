#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

InfoAlbum lerInfoAlbum() {
    InfoAlbum info;

    printf("Digite o dado: ");
    scanf("%d", &info.dado);

    info.musica = NULL;

    return info;
}

ArvAlbum* inicializarArvAlbum() {
    return NULL;
}

ArvAlbum* alocarNoAlbum(InfoAlbum info) {
    ArvAlbum *novoNo = (ArvAlbum*) malloc(sizeof(ArvAlbum));

    if (novoNo != NULL) {
        (*novoNo).info = info;
        (*novoNo).dir = NULL;
        (*novoNo).esq = NULL;
    }

    return novoNo;
}

int insereNoAlbum(ArvAlbum **raiz, ArvAlbum *novoNo) {
    int inseriu = 1;

    if (*raiz == NULL) {
        *raiz = novoNo;
    } else if ((**raiz).info.dado <  (*novoNo).info.dado) {
        inseriu = insereArvAlbum(&((**raiz).dir), novoNo);
    } else if ((**raiz).info.dado > (*novoNo).info.dado) {
        inseriu = insereArvAlbum(&((**raiz).esq), novoNo);
    } else {
        inseriu = 0;
    }

    return inseriu;
}

void imprimeArvAlbum(ArvAlbum *raiz) {
    if (raiz != NULL) {
        imprimeArvAlbum((*raiz).esq);
        printf("Dado: %d\n", (*raiz).info.dado);
        imprimeArvAlbum((*raiz).dir);
    }
}

void liberaArvAlbum(ArvAlbum *raiz) {
    if (raiz != NULL) {
        liberaArvMus((*raiz).esq);
        liberaArvMus((*raiz).dir);
        liberaArvMus((*raiz).info.musica);
        free(raiz);
    }
}

ArvAlbum* soUmFilhoAlbum(ArvAlbum *raiz) {
    ArvAlbum *filho;

    if ((*raiz).dir == NULL) {
        filho = (*raiz).esq;
    } else if ((*raiz).esq == NULL) {
        filho = (*raiz).dir;
    } else {
        filho = NULL;
    }

    return filho;
}

int removerAlbum(ArvAlbum **raiz, int valor) {
    int removeu = 1;

    if (*raiz != NULL) {
        if ((**raiz).info.dado == valor) {
            ArvAlbum *aux, *filho;
            liberaArvMus((**raiz).info.musica);
            if ((**raiz).dir == NULL && (**raiz).esq == NULL) {
                aux = *raiz;
                *raiz = NULL;
                free(aux);
            } else {
                if ((filho = soUmFilhoAlbum(*raiz)) != NULL) {
                    aux = *raiz;
                    *raiz = filho;
                    free(aux);
                } else {
                    ArvAlbum *maiorEsq = (**raiz).esq;
                    while ((*maiorEsq).dir != NULL) maiorEsq = (*maiorEsq).dir;

                    ((**raiz)).info.dado = (*maiorEsq).info.dado;
                    removeu = removerAlbum(&((**raiz).esq), (*maiorEsq).info.dado);
                }
            } 
        } else {
            if ((**raiz).info.dado > valor) {
                removeu = removerAlbum(&((**raiz).esq), valor);
            } else {
                removeu = removerAlbum(&((**raiz).dir), valor);
            }
        }
    } else {
        removeu = 0;
    }
    return removeu;
}

