#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

InfoMusP copiaDadosMusica(ArvArtista *art, ArvAlbum *alb, ArvMusica *mus) {
    InfoMusP info;
    strcpy(info.nome, (*mus).info.titulo);
    strcpy(info.album, (*alb).info.titulo);
    strcpy(info.artista, (*art).info.nome);

    return info;
}

ArvMusP* alocarNoMusP(InfoMusP info) {
    ArvMusP *novoNo = (ArvMusP*) malloc(sizeof(ArvMusP));

    if (novoNo != NULL) {
        (*novoNo).info = info;
        (*novoNo).dir = NULL;
        (*novoNo).esq = NULL;
    }

    return novoNo;
}

void rotacaoEsqMusP(ArvMusP **r) {
    ArvMusP *aux = (**r).dir;
    (**r).dir = (*aux).esq;
    (*aux).esq = (*r);
    (*r) = aux;
}

void rotacaoDirMusP(ArvMusP **r) {
    ArvMusP *aux = (**r).esq;
    (**r).esq = (*aux).dir;
    (*aux).dir = (*r);
    (*r) = aux;
}

int alturaArvMusP(ArvMusP *raiz) {
    int altura;

    if (raiz) {
        int alturaEsq = -1, alturaDir = -1;
        if ((*raiz).esq) alturaEsq = (*raiz).esq->altura;
        if ((*raiz).dir) alturaDir = (*raiz).dir->altura;
        if (alturaEsq > alturaDir)
            altura = alturaEsq + 1;
        else 
            altura = alturaDir + 1;
    } else 
        altura = -1;

    return altura;
}

int fatorBalanceamentoMusP(ArvMusP *r) { //esq - dir
    return alturaArvMusP((*r).esq) - alturaArvMusP((*r).dir);
}

void ajustarAlturaMusP(ArvMusP **r) {
    if (*r) {
        ajustarAlturaMusP(&((**r).esq));
        ajustarAlturaMusP(&((**r).dir));
        (**r).altura = alturaArvMusP(*r);
    }
}

void balanceamentoMusP(ArvMusP **r) {
    int fb;

    fb = fatorBalanceamentoMusP(*r);
    if (fb > 1) {
        int fbEsq = fatorBalanceamentoMusP((**r).esq);
        if (fbEsq < 0) rotacaoEsqMusP(&((**r).esq));
        rotacaoDirMusP(r);
    } else if (fb < -1) {
        int fbDir = fatorBalanceamentoMusP((**r).dir);
        if (fbDir > 0) rotacaoDirMusP(&((**r).dir));
        rotacaoEsqMusP(r);
    }
}

int insereNoMusP(ArvMusP **r, ArvMusP *novoNo) {
    int inseriu = 1;

    if (*r == NULL) 
        *r = novoNo;
    else if (strcmp((**r).info.nome, (*novoNo).info.nome) < 0) 
        inseriu = insereNoMusP(&((**r).dir), novoNo);
    else if (strcmp((**r).info.nome, (*novoNo).info.nome) > 0) 
        inseriu = insereNoMusP(&((**r).esq), novoNo);
    else 
        inseriu = 0;

    if (*r && inseriu) {
        balanceamentoMusP(r);
        ajustarAlturaMusP(r);
    }

    return inseriu;
}

void imprimeArvMusP(ArvMusP *r) {
    if (r != NULL) {
        imprimeArvMusP((*r).esq);
        printf("Título da música: %s Artista: %s Álbum: %s\n", (*r).info.nome, (*r).info.artista, (*r).info.nome);
        imprimeArvMusP((*r).dir);
    }
}

void liberaArvMusP(ArvMusP *r) {
    if (r != NULL) {
        liberaArvMusP((*r).esq);
        liberaArvMusP((*r).dir);
        free(r);
    }
}

ArvMusP* soUmFilhoMusP(ArvMusP *r) {
    ArvMusP *filho;

    if ((*r).dir == NULL) {
        filho = (*r).esq;
    } else if ((*r).esq == NULL) {
        filho = (*r).dir;
    } else 
        filho = NULL;

    return filho;
}

ArvMusP** menorDirMusP(ArvMusP **r) {
    ArvMusP **atual = r;

    if ((**r).esq != NULL) while ((**atual).esq != NULL) atual = &((**atual).esq);

    return atual;
}

int removerMusP(ArvMusP **r, const char *titulo) {
    int removeu = 1;

    if (*r != NULL) {
        if (strcmp((**r).info.nome, titulo) == 0) {
            ArvMusP *aux, *filho;
            if ((**r).dir == NULL && (**r).esq == NULL) {
                aux = *r;
                *r = NULL;
                free(aux);
            } else {
                if ((filho = soUmFilhoMusP(*r)) != NULL) {
                    aux = *r;
                    *r = filho;
                    free(aux);
                } else {
                    ArvMusP **menor;

                    menor = menorDirMusP(&((**r).dir)); 

                    (**r).info = (**menor).info;
                    aux = (*menor);
                    (*menor) = (**menor).dir;
                    free(aux);
                }
            } 
        } else {
            if (strcmp((**r).info.nome, titulo) > 0) 
                removeu = removerMusP(&((**r).esq), titulo);
             else 
                removeu = removerMusP(&((**r).dir), titulo);
        }
    } else 
        removeu = 0;
    
        if (*r && removeu) {
            balanceamentoMusP(r);
            ajustarAlturaMusP(r);
        }
    
    return removeu;
}

ArvMusP* buscarMusicaP(ArvMusP *r, const char *nome) {
    ArvMusP *aux = NULL;
    if (r != NULL) {
        int cmp = strcmp(nome, (*r).info.nome);
        if (cmp == 0)
            aux = r;
        else if (cmp < 0)
            aux = buscarMusicaP((*r).esq, nome);
        else
            aux = buscarMusicaP((*r).dir, nome);
    }
    return aux;
}