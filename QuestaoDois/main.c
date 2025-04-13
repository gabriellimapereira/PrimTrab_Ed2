#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"

void menuPlaylist(ArvPlaylist **r) {
    int op;
    do {
        printf("\n--- MENU DE PLAYLIST ---\n");
        printf("1 - Criar playlist\n");
        printf("2 - Mostrar dados de uma playlist\n");
        printf("3 - Remover música de uma playlist\n");
        printf("4 - Remover playlist\n");
        printf("5 - Remover música de álbum (se não estiver em nenhuma playlist)\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
        }
    } while (op != 0);
    return;
}

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
    ArvPlaylist *raizPlaylist = NULL;
    char nome[50];
    ArvArtista *art;

    InfoArtista vetorArtista[4] = {
        {"5", "7", "5"},
        {"3", "3", "3"},
        {"2", "7", "2"},
        {"8", "8", "8"},
    };
    
    InfoAlbum vetorAlbum[7] = {
        {"10", 2000, 0},
        {"11", 2001, 0},
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
        printf("9 - Álbuns por ano\n");
        printf("10 - Playlist\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1: 
                int inseriu = insereNoArt(&raizArtista, alocarNoArt(lerInfoArt()));
                if (inseriu) 
                    printf("Artista cadastrado!\n");
                else 
                    printf("Artista já está na árvore. A inserção não foi feita.\n");
                break;
            case 2: 
                printf("Digite o nome do artista: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                art = buscarArtista(raizArtista, nome);
                if (art) {
                    int inseriu = insereNoAlbum(&((*art).info.album), alocarNoAlbum(lerInfoAlbum()));
                    if (inseriu) 
                        printf("Álbum cadastrado!\n");
                    else 
                        printf("Álbum já está na árvore. A inserção não foi feita.\n");
                } else 
                    printf("Artista não encontrado!\n");
                break;
            case 3: 
                printf("Digite o nome do artista: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                ArvArtista *art = buscarArtista(raizArtista, nome);
                if (art) {
                    printf("Digite o nome do álbum: ");
                    setbuf(stdin, NULL);
                    scanf("%[^\n]", nome);
                    ArvAlbum *alb = buscarAlbum((*art).info.album, nome);
                    if (alb) {
                        int inseriu = insereNoMus(&((*alb).info.musica), alocarNoMusica(lerInfoMusica()));
                        if (inseriu) 
                            printf("Música cadastrada!\n");
                        else 
                            printf("Música já está na árvore. A inserção não foi feita.\n");
                    } else 
                    printf("Álbum não encontrado!\n");
                } else 
                    printf("Artista não encontrado!\n");
                break;
            case 4:
                imprimeArvArt(raizArtista);
                break;
            case 5:
                printf("Digite o tipo de artista: \n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                artistaPorTipo(raizArtista, nome);
                break;
            case 6:
                printf("Digite o estilo de artista: \n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                artistaPorEstilo(raizArtista, nome);
                break;
            case 7:
                char estilo[50], tipo[50];
                printf("Digite o estilo de artista: \n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", estilo);
                printf("Digite o tipo de artista: \n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", tipo);
                artistaPorTipoEstilo(raizArtista, tipo, estilo);
                break;
            case 8:
                printf("Digite o nome da música: \n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                int duracao;
                char album[100];

                dadosMusica(raizArtista, nome, &duracao, album);
                break;
            case 9:
                int ano;
                printf("Digite o ano dos álbuns: \n");
                scanf("%d", &ano);
                imprimeAlbumAnoArt(raizArtista, ano);
            case 10:
                menuPlaylist(&raizPlaylist);
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

