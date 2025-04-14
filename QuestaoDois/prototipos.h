#pragma once

//alternativas que faltam da questao um: xi até xvii

// definições das estruturas das informações e das árvores
typedef struct InfoMusica {
    char titulo[50];
    int duracao;
} InfoMusica;

typedef struct ArvMusica {
    InfoMusica info;
    int altura;
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
    int altura;
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
    int altura;
    struct ArvArtista *esq, *dir;
} ArvArtista;

typedef struct InfoPlaylist {
    char nome[50];
    struct ArvMusica *musica;
} InfoPlaylist;

typedef struct ArvPlaylist {
    InfoPlaylist info;
    struct ArvPlaylist *esq, *dir;
} ArvPlaylist;
 
// declarações das funções de música
InfoMusica lerInfoMusica();
ArvMusica* inicializarArvMus();
ArvMusica* alocarNoMusica(InfoMusica info);
void rotacaoEsqMus(ArvMusica **r);
void rotacaoDirMus(ArvMusica **r);
int alturaArvMus(ArvMusica *raiz);
int fatorBalanceamentoMus(ArvMusica *r);
void ajustarAlturaMus(ArvMusica **r);
void balanceamentoMus(ArvMusica **r);
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
void rotacaoEsqAlb(ArvAlbum **r);
void rotacaoDirAlb(ArvAlbum **r);
int alturaArvAlb(ArvAlbum *raiz);
int fatorBalanceamentoAlb(ArvAlbum *r);
void ajustarAlturaAlb(ArvAlbum **r);
void balanceamentoAlb(ArvAlbum **r);
int insereNoAlbum(ArvAlbum **r, ArvAlbum *novoNo);
void imprimeArvAlbum(ArvAlbum *r);
void liberaArvAlbum(ArvAlbum *r);
ArvAlbum* buscarAlbum(ArvAlbum *r, const char *titulo);

// declarações das funções de artista
InfoArtista lerInfoArt();
ArvArtista* inicializarArvArt();
ArvArtista* alocarNoArt(InfoArtista info);
void rotacaoEsqArt(ArvArtista **r);
void rotacaoDirArt(ArvArtista **r);
int alturaArvArt(ArvArtista *raiz);
int fatorBalanceamentoArt(ArvArtista *r);
void ajustarAlturaArt(ArvArtista **r);
void balanceamentoArt(ArvArtista **r);
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
void imprimeAlbumAnoArt(ArvArtista *r, int ano);
void musicasEspecificas(ArvArtista *r, const char *artista, const char *album);
void dadosMusica(ArvArtista *r, const char *musica, int *duracao, char *album);

// funções de playlist
