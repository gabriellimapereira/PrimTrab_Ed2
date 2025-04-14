#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

ArvMusP* alocarNoMusP(InfoMusP info) {
    ArvMusP *novoNo = (ArvMusP*) malloc(sizeof(ArvMusP));

    if (novoNo != NULL) {
        (*novoNo).info = info;
        (*novoNo).dir = NULL;
        (*novoNo).esq = NULL;
    }

    return novoNo;
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

int removerMusP(ArvMusP **r, char *titulo) {
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