#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

InfoArtista lerInfoArt() {
    InfoArtista info;

    printf("Digite o dado: ");
    scanf("%d", &info.dado);

    info.album = NULL;

    return info;
}

ArvArtista* inicializarArvArt() {
    return NULL;
}

ArvArtista* alocarNoArt(InfoArtista info) {
    ArvArtista *novoNo = (ArvArtista*) malloc(sizeof(ArvArtista));

    if (novoNo != NULL) {
        (*novoNo).info = info;
        (*novoNo).dir = NULL;
        (*novoNo).esq = NULL;
    }

    return novoNo;
}

int insereNoArt(ArvArtista **raiz, ArvArtista *novoNo) {
    int inseriu = 1;

    if (*raiz == NULL) {
        *raiz = novoNo;
    } else if ((**raiz).info.dado <  (*novoNo).info.dado) {
        inseriu = insereNoArt(&((**raiz).dir), novoNo);
    } else if ((**raiz).info.dado > (*novoNo).info.dado) {
        inseriu = insereNoArt(&((**raiz).esq), novoNo);
    } else {
        inseriu = 0;
    }

    return inseriu;
}

void imprimeArvArt(ArvArtista *raiz) {
    if (raiz != NULL) {
        imprimeArvArt((*raiz).esq);
        printf("Dado: %d\n", (*raiz).info.dado);
        imprimeArvArt((*raiz).dir);
    }
}

void liberaArvArt(ArvArtista *raiz) {
    if (raiz != NULL) {
        liberaArvArt((*raiz).esq);
        liberaArvArt((*raiz).dir);
        liberaArvMus((*raiz).info.album);
        free(raiz);
    }
}

ArvArtista* soUmFilhoArt(ArvArtista *raiz) {
    ArvArtista *filho;

    if ((*raiz).dir == NULL) {
        filho = (*raiz).esq;
    } else if ((*raiz).esq == NULL) {
        filho = (*raiz).dir;
    } else {
        filho = NULL;
    }

    return filho;
}

int removerArt(ArvArtista **raiz, int valor) {
    int removeu = 1;

    if (*raiz != NULL) {
        if ((**raiz).info.dado == valor) {
            ArvArtista *aux, *filho;
            liberaArvMus((**raiz).info.album);
            if ((**raiz).dir == NULL && (**raiz).esq == NULL) {
                aux = *raiz;
                *raiz = NULL;
                free(aux);
            } else {
                if ((filho = soUmFilhoArt(*raiz)) != NULL) {
                    aux = *raiz;
                    *raiz = filho;
                    free(aux);
                } else {
                    ArvArtista *maiorEsq = (**raiz).esq;
                    while ((*maiorEsq).dir != NULL) maiorEsq = (*maiorEsq).dir;

                    ((**raiz)).info.dado = (*maiorEsq).info.dado;
                    removeu = removerArt(&((**raiz).esq), (*maiorEsq).info.dado);
                }
            } 
        } else {
            if ((**raiz).info.dado > valor) {
                removeu = removerArt(&((**raiz).esq), valor);
            } else {
                removeu = removerArt(&((**raiz).dir), valor);
            }
        }
    } else {
        removeu = 0;
    }
    return removeu;
}


