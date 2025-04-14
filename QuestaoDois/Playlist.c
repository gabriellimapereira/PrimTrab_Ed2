#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

InfoPlaylist lerInfoPlaylist() {
    InfoPlaylist info;

    printf("Digite o nome da playlist: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.nome);

    info.musica = NULL;

    return info;
}

ArvPlaylist* inicializarArvPlaylist() {
    return NULL;
}

ArvPlaylist* alocarNoPlaylist(InfoPlaylist info) {
    ArvPlaylist *novoNo = (ArvPlaylist*) malloc(sizeof(ArvPlaylist));

    if (novoNo != NULL) {
        (*novoNo).info = info;
        (*novoNo).dir = NULL;
        (*novoNo).esq = NULL;
    }

    return novoNo;
}

void rotacaoEsqPlay(ArvPlaylist **r) {
    ArvPlaylist *aux = (**r).dir;
    (**r).dir = (*aux).esq;
    (*aux).esq = (*r);
    (*r) = aux;
}

void rotacaoDirPlay(ArvPlaylist **r) {
    ArvPlaylist *aux = (**r).esq;
    (**r).esq = (*aux).dir;
    (*aux).dir = (*r);
    (*r) = aux;
}

int alturaArvPlay(ArvPlaylist *raiz) {
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

int fatorBalanceamentoPlay(ArvPlaylist *r) { //esq - dir
    return alturaArvPlay((*r).esq) - alturaArvPlay((*r).dir);
}

void ajustarAlturaPlay(ArvPlaylist **r) {
    if (*r) {
        ajustarAlturaPlay(&((**r).esq));
        ajustarAlturaPlay(&((**r).dir));
        (**r).altura = alturaArvPlay(*r);
    }
}

void balanceamentoPlay(ArvPlaylist **r) {
    int fb;

    fb = fatorBalanceamentoPlay(*r);
    if (fb > 1) {
        int fbEsq = fatorBalanceamentoPlay((**r).esq);
        if (fbEsq < 0) rotacaoEsqPlay(&((**r).esq));
        rotacaoDirPlay(r);
    } else if (fb < -1) {
        int fbDir = fatorBalanceamentoPlay((**r).dir);
        if (fbDir > 0) rotacaoDirPlay(&((**r).dir));
        rotacaoEsqPlay(r);
    }
}

int insereNoPlaylist(ArvPlaylist **r, ArvPlaylist *novoNo) {
    int inseriu = 1;

    if (*r == NULL) 
        *r = novoNo;
    else if (strcmp((**r).info.nome, (*novoNo).info.nome) < 0) 
        inseriu = insereNoPlaylist(&((**r).dir), novoNo);
    else if (strcmp((**r).info.nome, (*novoNo).info.nome) > 0) 
        inseriu = insereNoPlaylist(&((**r).esq), novoNo);
    else 
        inseriu = 0;

    if (*r && inseriu) {
        balanceamentoPlay(r);
        ajustarAlturaPlay(r);
    }

    return inseriu;
}

void imprimeArvPlaylist(ArvPlaylist *r) {
    if (r != NULL) {
        imprimeArvPlaylist((*r).esq);
        printf("Título da playlist: %s\nMúsicas: \n", (*r).info.nome);
        imprimeArvMusP((*r).info.musica);
        imprimeArvPlaylist((*r).dir);
    }
}

void liberarArvPlaylist(ArvPlaylist *r) {
    if (r != NULL) {
        liberarArvPlaylist((*r).esq);
        liberarArvPlaylist((*r).dir);
        free(r);
    }
}

ArvPlaylist* soUmFilhoPlay(ArvPlaylist *r) {
    ArvPlaylist *filho;

    if ((*r).dir == NULL) {
        filho = (*r).esq;
    } else if ((*r).esq == NULL) {
        filho = (*r).dir;
    } else 
        filho = NULL;

    return filho;
}

ArvPlaylist** menorDirPlaylist(ArvPlaylist **r) {
    ArvPlaylist **atual = r;

    if ((**r).esq != NULL) while ((**atual).esq != NULL) atual = &((**atual).esq);

    return atual;
}

int removerPlaylist(ArvPlaylist **r, char *titulo) {
    int removeu = 1;

    if (*r != NULL) {
        if (strcmp((**r).info.nome, titulo) == 0) {
            liberaArvMusP((**r).info.musica);
            ArvPlaylist *aux, *filho;
            if ((**r).dir == NULL && (**r).esq == NULL) {
                aux = *r;
                *r = NULL;
                free(aux);
            } else {
                if ((filho = soUmFilhoPlay(*r)) != NULL) {
                    aux = *r;
                    *r = filho;
                    free(aux);
                } else {
                    ArvPlaylist **menor;

                    menor = menorDirPlaylist(&((**r).dir)); 

                    (**r).info = (**menor).info;
                    aux = (*menor);
                    (*menor) = (**menor).dir;
                    free(aux);
                }
            } 
        } else {
            if (strcmp((**r).info.nome, titulo) > 0) 
                removeu = removerPlaylist(&((**r).esq), titulo);
             else 
                removeu = removerPlaylist(&((**r).dir), titulo);
        }
    } else 
        removeu = 0;

    if (*r && removeu) {
        balanceamentoPlay(r);
        ajustarAlturaPlay(r);
    }
    
    
    return removeu;
}

ArvPlaylist* buscarPlaylist(ArvPlaylist *r, const char *nome) {
    ArvPlaylist *aux = NULL;
    if (r != NULL) {
        int cmp = strcmp(nome, (*r).info.nome);
        if (cmp == 0)
            aux = r;
        else if (cmp < 0)
            aux = buscarPlaylist((*r).esq, nome);
        else
            aux = buscarPlaylist((*r).dir, nome);
    }
    return aux;
}

ArvMusP* buscaMusicaEmPlaylist(ArvPlaylist *r, const char *nome) {
    ArvMusP *no = NULL;

    if (r) {
        no  = buscarMusicaP((*r).info.musica, nome);
        if (no == NULL) {
            no = buscaMusicaEmPlaylist((*r).esq, nome);
            if (no == NULL) {
                no = buscaMusicaEmPlaylist((*r).dir, nome);
            }
        }
    } 

    return no;
}