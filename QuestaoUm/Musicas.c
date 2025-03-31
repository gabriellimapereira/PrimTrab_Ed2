#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

InfoMusica lerInfoMusica() {
    InfoMusica info;

    printf("Digite o dado: ");
    scanf("%d", &info.dado);

    return info;
}

ArvMusica* inicializarArvMus() {
    return NULL;
}

ArvMusica* alocarNoMusica(InfoMusica info) {
    ArvMusica *novoNo = (ArvMusica*) malloc(sizeof(ArvMusica));

    if (novoNo != NULL) {
        (*novoNo).info = info;
        (*novoNo).dir = NULL;
        (*novoNo).esq = NULL;
    }

    return novoNo;
}

int insereNoMus(ArvMusica **raiz, ArvMusica *novoNo) {
    int inseriu = 0;

    if (*raiz == NULL) {
        *raiz = novoNo;
    } else if ((**raiz).info.dado <  (*novoNo).info.dado) {
        inseriu = insereNoMus(&((**raiz).dir), novoNo);
    } else if ((**raiz).info.dado > (*novoNo).info.dado) {
        inseriu = insereNoMus(&((**raiz).esq), novoNo);
    } else {
        inseriu = 1;
    }

    return inseriu;
}

void imprimeArvMus(ArvMusica *raiz) {
    if (raiz != NULL) {
        imprimeArvMus((*raiz).esq);
        printf("Dado: %d\n", (*raiz).info.dado);
        imprimeArvMus((*raiz).dir);
    }
}

void liberaArvMus(ArvMusica *raiz) {
    if (raiz != NULL) {
        liberaArvMus((*raiz).esq);
        liberaArvMus((*raiz).dir);
        free(raiz);
    }
}

ArvMusica* soUmFilhoMus(ArvMusica *raiz) {
    ArvMusica *filho;

    if ((*raiz).dir == NULL) {
        filho = (*raiz).esq;
    } else if ((*raiz).esq == NULL) {
        filho = (*raiz).dir;
    } else {
        filho = NULL;
    }

    return filho;
}

int removerMus(ArvMusica **raiz, int valor) {
    int removeu = 1;

    if (*raiz != NULL) {
        if ((**raiz).info.dado == valor) {
            ArvMusica *aux, *filho;
            if ((**raiz).dir == NULL && (**raiz).esq == NULL) {
                aux = *raiz;
                *raiz = NULL;
                free(aux);
            } else {
                if ((filho = soUmFilhoMus(*raiz)) != NULL) {
                    aux = *raiz;
                    *raiz = filho;
                    free(aux);
                } else {
                    ArvMusica *maiorEsq = (**raiz).esq;
                    while ((*maiorEsq).dir != NULL) maiorEsq = (*maiorEsq).dir;

                    ((**raiz)).info.dado = (*maiorEsq).info.dado;
                    removeu = removerMus(&((**raiz).esq), (*maiorEsq).info.dado);
                }
            } 
        } else {
            if ((**raiz).info.dado > valor) {
                removeu = removerMus(&((**raiz).esq), valor);
            } else {
                removeu = removerMus(&((**raiz).dir), valor);
            }
        }
    } else {
        removeu = 0;
    }
    return removeu;
}
