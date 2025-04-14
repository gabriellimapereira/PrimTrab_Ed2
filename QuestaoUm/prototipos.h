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

typedef struct InfoMusP {
    char nome[50];
    char artista[50];
    char album[50];
} InfoMusP;

typedef struct ArvMusP {
    InfoMusP info;
    struct ArvMusP *esq, *dir;
} ArvMusP;

typedef struct InfoPlaylist {
    char nome[50];
    struct ArvMusP *musica;
} InfoPlaylist;

typedef struct ArvPlaylist {
    InfoPlaylist info;
    struct ArvPlaylist *esq, *dir;
} ArvPlaylist;
 
// declarações das funções de música
InfoMusica lerInfoMusica();
ArvMusica* alocarNoMusica(InfoMusica info);
int insereNoMus(ArvMusica **r, ArvMusica *novoNo);
void imprimeArvMus(ArvMusica *r);
void liberaArvMus(ArvMusica *r);
ArvMusica* soUmFilhoMus(ArvMusica *r);
ArvMusica** menorDirMus(ArvMusica **r);
int removerMus(ArvMusica **r, const char *titulo);
ArvMusica* buscarMusica(ArvMusica *r, const char *nome);

// declarações das funções de álbum
InfoAlbum lerInfoAlbum();
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
ArvArtista* buscarArtista(ArvArtista *r, const char *nome);

// questões de impressão
void artistaPorTipo(ArvArtista *r, const char *tipo);
void artistaPorEstilo(ArvArtista *r, const char *estilo);
void artistaPorTipoEstilo(ArvArtista *r, const char *tipo, const char *estilo);
void albunsArtista(ArvArtista *r, const char *artista);
void imprimeAlbumAno(ArvAlbum *r, int ano);
void imprimeAlbumAnoArt(ArvArtista *r, int ano);
void musicasEspecificas(ArvArtista *r, const char *artista, const char *album);
void dadosMusica(ArvArtista *r, const char *musica, int *duracao, char *album);

// funções da árvore de música de playlist
InfoMusP copiaDadosMusica(ArvArtista *art, ArvAlbum *alb, ArvMusica *mus);
ArvMusP* alocarNoMusP(InfoMusP info);
int insereNoMusP(ArvMusP **r, ArvMusP *novoNo);
void imprimeArvMusP(ArvMusP *r);
void liberaArvMusP(ArvMusP *r);
ArvMusP* soUmFilhoMusP(ArvMusP *r);
ArvMusP** menorDirMusP(ArvMusP **r);
int removerMusP(ArvMusP **r, const char *titulo);
ArvMusP* buscarMusicaP(ArvMusP *r, const char *nome);

// funções de playlist
InfoPlaylist lerInfoPlaylist();
ArvPlaylist* alocarNoPlaylist(InfoPlaylist info);
int insereNoPlaylist(ArvPlaylist **r, ArvPlaylist *novoNo);
void imprimeArvPlaylist(ArvPlaylist *r);
void liberarArvPlaylist(ArvPlaylist *r);
ArvPlaylist* soUmFilhoPlay(ArvPlaylist *r);
ArvPlaylist** menorDirPlaylist(ArvPlaylist **r);
int removerPlaylist(ArvPlaylist **r, const char *titulo);
ArvPlaylist* buscarPlaylist(ArvPlaylist *r, const char *nome);
ArvMusP* buscaMusicaEmPlaylist(ArvPlaylist *r, const char *nome);