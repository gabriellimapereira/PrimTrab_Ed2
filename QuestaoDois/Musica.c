#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

InfoMusica lerInfoMusica() {
    InfoMusica info;

    printf("Digite o título: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.titulo);
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

void rotacaoEsqMus(ArvMusica **r) {
    ArvMusica *aux = (**r).dir;
    (**r).dir = (*aux).esq;
    (*aux).esq = (*r);
    (*r) = aux;
}

void rotacaoDirMus(ArvMusica **r) {
    ArvMusica *aux = (**r).esq;
    (**r).esq = (*aux).dir;
    (*aux).dir = (*r);
    (*r) = aux;
}

int alturaArvMus(ArvMusica *raiz) {
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

int fatorBalanceamentoMus(ArvMusica *r) { //esq - dir
    return alturaArvMus((*r).esq) - alturaArvMus((*r).dir);
}

void ajustarAlturaMus(ArvMusica **r) {
    if (*r) {
        ajustarAlturaMus(&((**r).esq));
        ajustarAlturaMus(&((**r).dir));
        (**r).altura = alturaArvMus(*r);
    }
}

void balanceamentoMus(ArvMusica **r) {
    int fb;

    fb = fatorBalanceamentoMus(*r);
    if (fb > 1) {
        int fbEsq = fatorBalanceamentoMus((**r).esq);
        if (fbEsq < 0) rotacaoEsqMus(&((**r).esq));
        rotacaoDirMus(r);
    } else if (fb < -1) {
        int fbDir = fatorBalanceamentoMus((**r).dir);
        if (fbDir > 0) rotacaoDirMus(&((**r).dir));
        rotacaoEsqMus(r);
    }
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

    if (*r && inseriu) {
        balanceamentoMus(r);
        ajustarAlturaMus(r);
    }

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

int removerMus(ArvMusica **r, const char *titulo) {
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

    if (*r && removeu) {
        balanceamentoMus(r);
        ajustarAlturaMus(r);
    }
    
    return removeu;
}

ArvMusica* buscarMusica(ArvMusica *r, const char *nome) {
    ArvMusica *aux = NULL;
    if (r != NULL) {
        int cmp = strcmp(nome, (*r).info.titulo);
        if (cmp == 0)
            aux = r;
        else if (cmp < 0)
            aux = buscarMusica((*r).esq, nome);
        else
            aux = buscarMusica((*r).dir, nome);
    }
    return aux;
}

void musicasEspecificas(ArvArtista *r, const char *artista, const char *album) {
    if (r) {
        ArvArtista *art = buscarArtista(r, artista);
        if (art) {
            ArvAlbum *alb = buscarAlbum((*art).info.album, album);
            if (alb) imprimeArvMus((*alb).info.musica);
        }
    }
}

int nomeAlbum(ArvAlbum *r, const char *musica, int *duracao, char *album) {
    int achou = 1;

    if (r) {
        ArvMusica *noMus = buscarMusica(r->info.musica, musica);
        if (noMus) {
            strcpy(album, r->info.titulo);
            *duracao = (*noMus).info.duracao;
        } else {
            int esq = nomeAlbum(r->esq, musica, duracao, album);
            if (esq != 0) {
                achou = esq;
            } else {
                achou = nomeAlbum(r->dir, musica, duracao, album);
            }
        }
    } else 
        achou = 0;

    return achou;
}

void dadosMusica(ArvArtista *r, const char *musica, int *duracao, char *album) {
    char *nome = NULL;

    if (r) {
        int achou = nomeAlbum((*r).info.album, musica, duracao, album);
        if (achou) {
            printf("Artista: %s Álbum: %s Duração: %d", (*r).info.nome, album, *duracao);
        } else {
            dadosMusica((*r).esq, musica, duracao, album);
            dadosMusica((*r).dir, musica, duracao, album);
        }
    }
}

