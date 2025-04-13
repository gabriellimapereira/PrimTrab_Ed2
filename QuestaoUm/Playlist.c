#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

InfoPlaylist lerInfoPlaylist() {
    InfoPlaylist info;

    printf("Digite o nome da Playlist: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.nome);

    info.musica = inicializarArvPlaylist();

    return info;
}

ArvPlaylist* inicializarArvPlaylist() {
    return NULL;
}

ArvPlaylist* alocarNoMusica(InfoPlaylist info) {
    ArvPlaylist *novoNo = (ArvPlaylist*) malloc(sizeof(ArvPlaylist));

    if (novoNo != NULL) {
        (*novoNo).info = info;
        (*novoNo).dir = NULL;
        (*novoNo).esq = NULL;
    }

    return novoNo;
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

    return inseriu;
}

void imprimeArvPlaylist(ArvPlaylist *r) {
    if (r != NULL) {
        imprimeArvPlaylist((*r).esq);
        printf("Título da playlist: %s\n", (*r).info.nome);
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

ArvPlaylist** menorDirMus(ArvPlaylist **r) {
    ArvPlaylist **atual = r;

    if ((**r).esq != NULL) while ((**atual).esq != NULL) atual = &((**atual).esq);

    return atual;
}

int removerPlaylist(ArvPlaylist **r, char *titulo) {
    int removeu = 1;

    if (*r != NULL) {
        if (strcmp((**r).info.nome, titulo) == 0) {
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

                    menor = menorDirMus(&((**r).dir)); 

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
    
    return removeu;
}