#ifndef PROTOTIPOS
#define PROTOTIPOS

// definições das estruturas das informações e das árvores

typedef struct InfoMusica {
    int dado;
} InfoMusica;

typedef struct ArvMusica {
    InfoMusica info;
    struct ArvMusica *esq, *dir;
} ArvMusica;

typedef struct InfoAlbum {
    int dado;
    ArvMusica *musica;
} InfoAlbum;

typedef struct ArvAlbum {
    InfoAlbum info;
    struct ArvAlbum *esq, *dir;
} ArvAlbum;

typedef struct InfoArtista {
    int dado;
    ArvAlbum *album;
} InfoArtista;

typedef struct ArvArtista {
    InfoArtista info;
    struct ArvArtista *esq, *dir;
} ArvArtista;

// declarações das funções de música
InfoMusica lerInfoMusica();
ArvMusica* inicializarArvMus();
ArvMusica* alocarNoMusica(InfoMusica info);
int insereArvMus(ArvMusica **raiz, ArvMusica *novoNo);
void imprimeArvMus(ArvMusica *raiz);
void liberaArvMus(ArvMusica *raiz);
ArvMusica* soUmFilhoMus(ArvMusica *raiz);
int removerMus(ArvMusica **raiz, int valor);

// declarações das funções de álbum
InfoAlbum lerInfoAlbum();

// declarações das funções de artista
InfoArtista lerInfoArtista();


#endif
