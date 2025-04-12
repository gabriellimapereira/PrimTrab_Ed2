#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

InfoAlbum lerInfoAlbum() {
    InfoAlbum info;

    printf("Digite o título: ");
    scanf("%s", info.titulo);
    printf("Digite o ano de lançamento: ");
    scanf("%d", &info.ano);
    info.quantMus = 0;

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

int insereNoAlbum(ArvAlbum **r, ArvAlbum *novoNo) {
    int inseriu = 1;

    if (*r == NULL) 
        *r = novoNo;
    else if (strcmp((**r).info.titulo, (*novoNo).info.titulo) < 0) 
        inseriu = insereNoAlbum(&((**r).dir), novoNo);
    else if (strcmp((**r).info.titulo, (*novoNo).info.titulo) > 0) 
        inseriu = insereNoAlbum(&((**r).esq), novoNo);
    else 
        inseriu = 0;
    
    return inseriu;
}

void imprimeArvAlbum(ArvAlbum *r) {
    if (r != NULL) {
        imprimeArvAlbum((*r).esq);
        printf("Álbum: %s\n", (*r).info.titulo);
        imprimeArvMus(((*r).info.musica));
        imprimeArvAlbum((*r).dir);
    }
}

void liberaArvAlbum(ArvAlbum *r) {
    if (r != NULL) {
        liberaArvAlbum((*r).esq);
        liberaArvAlbum((*r).dir);
        liberaArvMus((*r).info.musica);
        free(r);
    }
}

ArvAlbum* buscarAlbum(ArvAlbum *r, const char *titulo) {
    ArvAlbum *aux = NULL;
    if (r != NULL) {
        int cmp = strcmp(titulo, (*r).info.titulo);
        if (cmp == 0)
            aux = r;
        else if (cmp < 0)
            aux = buscarAlbum((*r).esq, titulo);
        else
            aux = buscarAlbum((*r).dir, titulo);
    }
    return aux;
}

void albunsArtista(ArvArtista *r, const char *artista) {
    if (r) {
        ArvArtista *art = buscarArtista(r, artista);
        if (art) imprimeArvAlbum((*r).info.album);
    }
}

void imprimeAlbumAno(ArvAlbum *r, int ano) { // tem que verificar por fora e chamar fora tbm
    if (r) {
        imprimeAlbumAno((*r).esq, ano);
        if ((*r).info.ano == ano) printf("%s", (*r).info.titulo);
        imprimeAlbumAno((*r).dir, ano);
    }
}