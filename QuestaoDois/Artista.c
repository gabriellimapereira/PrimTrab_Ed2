#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

InfoArtista lerInfoArt() {
    InfoArtista info;

    printf("Digite o nome: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.nome);
    printf("Digite o tipo: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.tipo);
    printf("Digite o estilo: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.estilo);
    info.quantAlbum = 0;

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

int insereNoArt(ArvArtista **r, ArvArtista *novoNo) {
    int inseriu = 1;

    if (*r == NULL) 
        *r = novoNo;
    else if (strcmp((**r).info.nome, (*novoNo).info.nome) < 0) 
        inseriu = insereNoArt(&((**r).dir), novoNo);
    else if (strcmp((**r).info.nome, (*novoNo).info.nome) > 0) 
        inseriu = insereNoArt(&((**r).esq), novoNo);
    else 
        inseriu = 0;
    
    return inseriu;
}

void imprimeArvArt(ArvArtista *r) {
    if (r != NULL) {
        imprimeArvArt((*r).esq);
        printf("Nome: %s Tipo: %s Estilo: %s\nÁlbuns: \n", (*r).info.nome, (*r).info.tipo, (*r).info.estilo);
        imprimeArvAlbum(((*r).info.album));
        imprimeArvArt((*r).dir);
    }
}

void liberaArvArt(ArvArtista *r) {
    if (r != NULL) {
        liberaArvArt((*r).esq);
        liberaArvArt((*r).dir);
        liberaArvAlbum((*r).info.album);
        free(r);
    }
}

ArvArtista* soUmFilhoArt(ArvArtista *r) {
    ArvArtista *filho;

    if ((*r).dir == NULL) 
        filho = (*r).esq;
    else if ((*r).esq == NULL) 
        filho = (*r).dir;
    else 
        filho = NULL;
    

    return filho;
}

ArvArtista** menorDirArt(ArvArtista **r) {
    ArvArtista **atual = r;

    if ((**r).esq != NULL) while ((**atual).esq != NULL) atual = &((**atual).esq);

    return atual;
}

int removerArt(ArvArtista **r, char *nome) {
    int removeu = 1;

    if (*r != NULL) {
        if (strcmp((**r).info.nome, nome) == 0) {
            ArvArtista *aux, *filho;
            liberaArvAlbum((**r).info.album);
            if ((**r).dir == NULL && (**r).esq == NULL) {
                aux = *r;
                *r = NULL;
                free(aux);
            } else {
                if ((filho = soUmFilhoArt(*r)) != NULL) {
                    aux = *r;
                    *r = filho;
                    free(aux);
                } else {
                    ArvArtista **menor;

                    menor = menorDirArt(&((**r).dir)); 

                    (**r).info = (**menor).info;
                    aux = (*menor);
                    (*menor) = (**menor).dir;
                    free(aux);
                }
            } 
        } else {
            if (strcmp((**r).info.nome, nome) > 0) {
                removeu = removerArt(&((**r).esq), nome);
            } else {
                removeu = removerArt(&((**r).dir), nome);
            }
        }
    } else {
        removeu = 0;
    }
    return removeu;
}

ArvArtista* buscarArtista(ArvArtista *r, const char *nome) {
    ArvArtista *aux = NULL;
    if (r != NULL) {
        int cmp = strcmp(nome, (*r).info.nome);
        if (cmp == 0)
            aux = r;
        else if (cmp < 0)
            aux = buscarArtista((*r).esq, nome);
        else
            aux = buscarArtista((*r).dir, nome);
    }
    return aux;
}

void artistaPorTipo(ArvArtista *r, const char *tipo) {
    if (r) {
        artistaPorTipo((*r).esq, tipo);
        if (strcmp((*r).info.tipo, tipo) == 0) {
            printf("Nome: %s\n", (*r).info.nome);
            imprimeArvAlbum(((*r).info.album));
        }
        artistaPorTipo((*r).dir, tipo);
    }
}

void artistaPorEstilo(ArvArtista *r, const char *estilo) {
    if (r) {
        artistaPorTipo((*r).esq, estilo);
        if (strcmp((*r).info.estilo, estilo) == 0) {
            printf("Nome: %s\n", (*r).info.nome);
            imprimeArvAlbum(((*r).info.album));
        }
        artistaPorTipo((*r).dir, estilo);
    }
}

void artistaPorTipoEstilo(ArvArtista *r, const char *tipo, const char *estilo) {
    if (r) {
        artistaPorTipoEstilo((*r).esq, tipo, estilo);
        if ((strcmp((*r).info.tipo, tipo) == 0) && (strcmp((*r).info.estilo, estilo) == 0)) {
            printf("Nome: %s\n", (*r).info.nome);
            imprimeArvAlbum(((*r).info.album));
        }
        artistaPorTipoEstilo((*r).dir, tipo, estilo);
    } 
}