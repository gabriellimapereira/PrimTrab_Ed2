#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"

int insercao(ArvArtista *artistas, const char *artista, const char *album, ArvMusica *noMusica) {
    int inseriu = 0;
    if (artistas) {
        ArvArtista *noArtista = buscarArtista(artistas, artista);
        if (noArtista) {
            ArvAlbum *noAlbum = buscarAlbum(noArtista->info.album, album);
            if (noAlbum) 
                inseriu = insereNoMus(&(noAlbum->info.musica), noMusica);
        } 
    } 
    return inseriu;
}

int main() {
    ArvArtista *raizArtista = inicializarArvArt();

    InfoArtista vetorArtista[4] = {
        {"5", "7", "5"},
        {"3", "3", "3"},
        {"2", "7", "2"},
        {"8", "8", "8"},
    };
    
    InfoAlbum vetorAlbum[7] = {
        {"10", 2000, 0},
        {"11", 2000, 0},
        {"12", 2000, 0},
        {"15", 2000, 0},
        {"14", 2000, 0},
        {"16", 2000, 0},
        {"17", 2000, 0}
    };

    InfoMusica vetorMusicas[35] = {
        {"100", 5}, {"101", 5}, {"102", 5}, {"103", 5}, {"104", 5},
        {"105", 5}, {"106", 5}, {"107", 5}, {"108", 5}, {"109", 5},
        {"110", 5}, {"111", 5}, {"112", 5}, {"113", 5}, {"114", 5},
        {"115", 5}, {"116", 5}, {"117", 5}, {"118", 5}, {"119", 5},
        {"120", 5}, {"121", 5}, {"122", 5}, {"123", 5}, {"124", 5},
        {"125", 5}, {"126", 5}, {"127", 5}, {"128", 5}, {"129", 5},
        {"130", 5}, {"131", 5}, {"132", 5}, {"133", 5}, {"134", 5}
    };    
    
    for (int i = 0; i < 3; i++) {
        insereNoArt(&raizArtista, alocarNoArt(vetorArtista[i]));
    }

    insereNoAlbum(&((*raizArtista).info.album), alocarNoAlbum(vetorAlbum[0]));
    insereNoAlbum(&((*raizArtista->esq).info.album), alocarNoAlbum(vetorAlbum[1]));

    int inseriu = insercao(raizArtista, "5", "10", alocarNoMusica(vetorMusicas[0]));
    inseriu = insercao(raizArtista, "3", "11", alocarNoMusica(vetorMusicas[1]));
    if (inseriu) printf("deu certo!\n");

    int op;
    do {
        printf("\n------ MENU ------\n");
        printf("1 - Inserir artista\n");
        printf("2 - Inserir álbum para artista\n");
        printf("3 - Inserir música em álbum\n");
        printf("4 - Imprimir árvore de artistas\n");
        printf("5 - Imprimir artistas por tipo\n");
        printf("6 - Imprimir artistas por estilo\n");
        printf("7 - Imprimir artistas por tipo e estilo\n");
        printf("8 - A proibida...\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1: 

            case 2: 
                break;

            case 3: 
                break;
            case 4:
                imprimeArvArt(raizArtista);
                break;
            case 5:
                artistaPorTipo(raizArtista, "7");
                break;
            case 6:
                artistaPorEstilo(raizArtista, "0");
                break;
            case 7:
                artistaPorTipoEstilo(raizArtista, "7", "5");
                break;
            case 8:
                const char *musica = "101"; 
                int duracao;
                char album[100];

                dadosMusica(raizArtista, musica, &duracao, album);
                break;
            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (op != 0);

    liberaArvArt(raizArtista);
    return 0;
}

