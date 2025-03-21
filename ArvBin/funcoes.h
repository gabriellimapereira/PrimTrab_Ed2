#ifndef FUNCOES
#define FUNCOES

typedef struct ArvBin {
    int info;
    struct ArvBin *esq, *dir;
} ArvBin;

void alocarNo(ArvBin **no, int valor);
int insereNo(ArvBin **raiz, ArvBin *no);
int buscaBin(ArvBin *raiz, int valor);
void preOrdem(ArvBin *raiz);
void inOrdem(ArvBin *raiz);
void posOrdem(ArvBin *raiz);

#endif