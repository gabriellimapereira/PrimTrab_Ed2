#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

InfoAlbum lerInfoAlbum() {
    InfoAlbum info;

    printf("Digite o título: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.titulo);
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

void rotacaoEsqAlb(ArvAlbum **r) {
    ArvAlbum *aux = (**r).dir;
    (**r).dir = (*aux).esq;
    (*aux).esq = (*r);
    (*r) = aux;
}

void rotacaoDirAlb(ArvAlbum **r) {
    ArvAlbum *aux = (**r).esq;
    (**r).esq = (*aux).dir;
    (*aux).dir = (*r);
    (*r) = aux;
}

int alturaArvAlb(ArvAlbum *raiz) {
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

int fatorBalanceamentoAlb(ArvAlbum *r) { //esq - dir
    return alturaArvAlb((*r).esq) - alturaArvAlb((*r).dir);
}

void ajustarAlturaAlb(ArvAlbum **r) {
    if (*r) {
        ajustarAlturaAlb(&((**r).esq));
        ajustarAlturaAlb(&((**r).dir));
        (**r).altura = alturaArvAlb(*r);
    }
}

void balanceamentoAlb(ArvAlbum **r) {
    int fb;

    fb = fatorBalanceamentoAlb(*r);
    if (fb > 1) {
        int fbEsq = fatorBalanceamentoAlb((**r).esq);
        if (fbEsq < 0) rotacaoEsqAlb(&((**r).esq));
        rotacaoDirAlb(r);
    } else if (fb < -1) {
        int fbDir = fatorBalanceamentoAlb((**r).dir);
        if (fbDir > 0) rotacaoDirAlb(&((**r).dir));
        rotacaoEsqAlb(r);
    }
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

    if (*r && inseriu) {
        balanceamentoAlb(r);
        ajustarAlturaAlb(r);
    }
    
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
        if ((*r).info.ano == ano) printf("%s\n", (*r).info.titulo);
        imprimeAlbumAno((*r).dir, ano);
    }
}

void imprimeAlbumAnoArt(ArvArtista *r, int ano) {
    if (r) {
        imprimeAlbumAnoArt((*r).esq, ano);
        imprimeAlbumAno((*r).info.album, ano);
        imprimeAlbumAnoArt((*r).dir, ano);
    }
}