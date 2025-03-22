#ifndef PROTOTIPOS
#define PROTOTIPOS

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
    int anoLancamento;
    int quantMusicas;
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
    int numAlbuns;
    ArvAlbum *album;
} InfoArtista;

typedef struct ArvArtista {
    InfoArtista info;
    struct ArvArtista *esq, *dir;
} ArvArtista;

// declarações das funções de música
InfoMusica lerInfoMusica();

#endif
