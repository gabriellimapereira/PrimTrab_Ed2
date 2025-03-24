#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

InfoMusica lerInfoMusica() {
    InfoMusica info;

    printf("Digite o título da música: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.titulo);

    printf("Agora informe a duração dela: ");
    scanf("%d", &info.duracao);

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

int insereArvMus(ArvMusica **raiz, ArvMusica *novoNo) {
    int inseriu = 0;

    if (*raiz != NULL) {
        *raiz = novoNo;
    } else if (strcmp((*novoNo).info.titulo, (**raiz).info.titulo) <  0) {
        inseriu = insereArvMus(&((**raiz).esq), novoNo);
    } else if (strcmp((*novoNo).info.titulo, (**raiz).info.titulo) >  0) {
        inseriu = insereArvMus(&((**raiz).dir), novoNo);
    } else {
        inseriu = 1;
    }

    return inseriu;
}

void imprimeArvMusc(ArvMusica *raiz) {
    if (raiz != NULL) {
        imprimeArvMusc((*raiz).esq);
        printf("Título: %s\nDuração: %d\n", (*raiz).info.titulo, (*raiz).info.duracao);
        imprimeArvMusc((*raiz).dir);
    }
}

void liberaArvMus(ArvMusica *raiz) {
    if (raiz != NULL) {
        imprimeArvMus(&(*raiz).esq);
        imprimeArvMus(&(*raiz).dir);
        free(raiz);
    }
}
