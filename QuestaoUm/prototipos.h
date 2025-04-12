#pragma once

//alternativas que faltam da questao um: xi até xvii

// definições das estruturas das informações e das árvores
typedef struct InfoMusica {
    char titulo[50];
    int duracao;
} InfoMusica;

typedef struct ArvMusica {
    InfoMusica info;
    struct ArvMusica *esq, *dir;
} ArvMusica;

typedef struct InfoAlbum {
    char titulo[50];
    int ano;
    int quantMus;
    ArvMusica *musica;
} InfoAlbum;

typedef struct ArvAlbum {
    InfoAlbum info;
    struct ArvAlbum *esq, *dir;
} ArvAlbum;

typedef struct InfoArtista {
    char nome[50];
    char tipo[50];
    char estilo[50];
    int quantAlbum;
    struct ArvAlbum *album;
} InfoArtista;

typedef struct ArvArtista {
    InfoArtista info;
    struct ArvArtista *esq, *dir;
} ArvArtista;

// declarações das funções de música
InfoMusica lerInfoMusica();
ArvMusica* inicializarArvMus();
ArvMusica* alocarNoMusica(InfoMusica info);
int insereNoMus(ArvMusica **r, ArvMusica *novoNo);
void imprimeArvMus(ArvMusica *r);
void liberaArvMus(ArvMusica *r);
ArvMusica* soUmFilhoMus(ArvMusica *r);
ArvMusica** menorDirMus(ArvMusica **r);
int removerMus(ArvMusica **r, char *titulo);

// declarações das funções de álbum
InfoAlbum lerInfoAlbum();
ArvAlbum* inicializarArvAlbum();
ArvAlbum* alocarNoAlbum(InfoAlbum info);
int insereNoAlbum(ArvAlbum **r, ArvAlbum *novoNo);
void imprimeArvAlbum(ArvAlbum *r);
void liberaArvAlbum(ArvAlbum *r);
ArvAlbum* buscarAlbum(ArvAlbum *r, const char *titulo);

// declarações das funções de artista
InfoArtista lerInfoArt();
ArvArtista* inicializarArvArt();
ArvArtista* alocarNoArt(InfoArtista info);
int insereNoArt(ArvArtista **r, ArvArtista *novoNo);
void imprimeArvArt(ArvArtista *r);
void liberaArvArt(ArvArtista *r);
ArvArtista* soUmFilhoArt(ArvArtista *r);
ArvArtista** menorDirArt(ArvArtista **r);
int removerArt(ArvArtista **r, char *nome);
ArvArtista* buscarArtista(ArvArtista *r, const char *nome);

// questões de impressão
void artistaPorTipo(ArvArtista *r, const char *tipo);
void artistaPorEstilo(ArvArtista *r, const char *estilo);
void artistaPorTipoEstilo(ArvArtista *r, const char *tipo, const char *estilo);
void albunsArtista(ArvArtista *r, const char *artista);
void imprimeAlbumAno(ArvAlbum *r, int ano);
void musicasEspecificas(ArvArtista *r, const char *artista, const char *album);
void dadosMusica(ArvArtista *r, const char *musica, int *duracao, char *album);