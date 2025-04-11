#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

InfoMusica lerInfoMusica() {
    InfoMusica info;

    printf("Digite o título: ");
    scanf("%s", info.titulo);
    printf("Digite a duração: ");
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

int insereNoMus(ArvMusica **r, ArvMusica *novoNo) {
    int inseriu = 1;

    if (*r == NULL) 
        *r = novoNo;
    else if (strcmp((**r).info.titulo, (*novoNo).info.titulo) < 0) 
        inseriu = insereNoMus(&((**r).dir), novoNo);
    else if (strcmp((**r).info.titulo, (*novoNo).info.titulo) > 0) 
        inseriu = insereNoMus(&((**r).esq), novoNo);
    else 
        inseriu = 0;

    return inseriu;
}

void imprimeArvMus(ArvMusica *r) {
    if (r != NULL) {
        imprimeArvMus((*r).esq);
        printf("Título da música: %s\n", (*r).info.titulo);
        imprimeArvMus((*r).dir);
    }
}

void liberaArvMus(ArvMusica *r) {
    if (r != NULL) {
        liberaArvMus((*r).esq);
        liberaArvMus((*r).dir);
        free(r);
    }
}

ArvMusica* soUmFilhoMus(ArvMusica *r) {
    ArvMusica *filho;

    if ((*r).dir == NULL) {
        filho = (*r).esq;
    } else if ((*r).esq == NULL) {
        filho = (*r).dir;
    } else 
        filho = NULL;

    return filho;
}

ArvMusica** menorDirMus(ArvMusica **r) {
    ArvMusica **atual = r;

    if ((**r).esq != NULL) while ((**atual).esq != NULL) atual = &((**atual).esq);

    return atual;
}

int removerMus(ArvMusica **r, char *titulo) {
    int removeu = 1;

    if (*r != NULL) {
        if (strcmp((**r).info.titulo, titulo) == 0) {
            ArvMusica *aux, *filho;
            if ((**r).dir == NULL && (**r).esq == NULL) {
                aux = *r;
                *r = NULL;
                free(aux);
            } else {
                if ((filho = soUmFilhoMus(*r)) != NULL) {
                    aux = *r;
                    *r = filho;
                    free(aux);
                } else {
                    ArvMusica **menor;

                    menor = menorDirMus(&((**r).dir)); 

                    (**r).info = (**menor).info;
                    aux = (*menor);
                    (*menor) = (**menor).dir;
                    free(aux);
                }
            } 
        } else {
            if (strcmp((**r).info.titulo, titulo) > 0) 
                removeu = removerMus(&((**r).esq), titulo);
             else 
                removeu = removerMus(&((**r).dir), titulo);
        }
    } else 
        removeu = 0;
    
    return removeu;
}