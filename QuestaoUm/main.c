#include <stdio.h>
#include <stdlib.h>
#include "prototipos.h"

void exibirMenu() {
    ArvArtista *artista = inicializarArvArt();
    int opcao;
    
    do {
        printf("\n---------- Menu ----------\n");
        printf("1. Cadastrar os artistas de teste\n");
        printf("2. Cadastrar os álbuns de teste\n");
        printf("3. Cadastrar as músicas de teste\n");
        printf("4. Mostrar todos os artistas\n");
        printf("5. Mostrar artistas por tipo\n");
        printf("6. Mostrar artistas por estilo musical\n");
        printf("7. Mostrar artistas por estilo e tipo\n");
        printf("8. Mostrar álbuns de um artista\n");
        printf("9. Mostrar álbuns de um determinado ano de um artista\n");
        printf("10. Mostrar músicas de um álbum de um artista\n");
        printf("11. Mostrar álbuns de um determinado ano de todos os artistas\n");
        printf("12. Mostrar dados de uma música\n");
        printf("13. Criar playlist\n");
        printf("14. Mostrar dados de uma playlist\n");
        printf("15. Remover música de uma playlist\n");
        printf("16. Remover playlist\n");
        printf("17. Remover música de um álbum de um artista\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                InfoArtista infoArtistas[17] = {{30000, NULL}, {20000, NULL}, {55000, NULL}, {15000, NULL}, {25000, NULL}, 
                                        {50000, NULL}, {70000, NULL}, {12000, NULL}, {17000, NULL}, {40000, NULL}, 
                                        {53000, NULL}, {80000, NULL}, {10000, NULL}, {35000, NULL}, {45000, NULL}, 
                                        {75000, NULL}, {37000, NULL}};
                int i = 0;
                while (i < 17) {
                    ArvArtista *novoNo = alocarNoArt(infoArtistas[i]);
                    if (novoNo != NULL) {
                        if (insereNoArt(&artista, novoNo)) {
                            printf("Artista %d cadastrado com sucesso!\n", infoArtistas[i].dado);
                        } else {
                            printf("Artista %d já existe!\n", infoArtistas[i].dado);
                            free(novoNo);
                        }
                    }
                    i++;
                }
                break;
            case 2:
                InfoAlbum infoAlbuns[17] = {{3000, NULL}, {2000, NULL}, {5500, NULL}, {1500, NULL}, {25000, NULL}, 
                                        {5000, NULL}, {7000, NULL}, {1200, NULL}, {1700, NULL}, {4000, NULL}, 
                                        {5300, NULL}, {8000, NULL}, {1000, NULL}, {3500, NULL}, {4500, NULL}, 
                                        {7500, NULL}, {3700, NULL}};
                i = 0;
                while (i < 17) {
                    ArvAlbum *novoNo = alocarNoAlbum(infoAlbuns[i]);
                    if (novoNo != NULL) {
                        if (insereNoAlbum(&((*artista).info.album), novoNo)) {
                            printf("Album %d cadastrado com sucesso!\n", infoAlbuns[i].dado);
                        } else {
                            printf("Album %d já existe!\n", infoAlbuns[i].dado);
                            free(novoNo);
                        }
                    }
                    i++;
                }
                break;
            case 3:
                InfoMusica array[17] = {{300}, {200}, {550}, {150}, {2500}, 
                                        {500}, {700}, {120}, {170}, {400}, 
                                        {530}, {800}, {100}, {350}, {450}, 
                                        {750}, {370}};
                i = 0;
                while (i < 17) {
                    ArvMusica *novoNo = alocarNoMusica(array[i]);
                    if (novoNo != NULL) {
                        if (insereNoMus(&((*artista).info.album->info.musica), novoNo)) {
                            printf("Mus %d cadastrado com sucesso!\n", array[i].dado);
                        } else {
                            printf("Mus %d já existe!\n", array[i].dado);
                            free(novoNo);
                        }
                    }
                    i++;
                }
                break;
            case 4:
                imprimeArvArt(artista);
                break;
            case 5:
                printf("Mostrando artistas por tipo...\n");
                break;
            case 6:
                printf("Mostrando artistas por estilo musical...\n");
                break;
            case 7:
                printf("Mostrando artistas por estilo e tipo...\n");
                break;
            case 8:
                printf("Mostrando álbuns de um artista...\n");
                break;
            case 9:
                printf("Mostrando álbuns de um determinado ano de um artista...\n");
                break;
            case 10:
                printf("Mostrando músicas de um álbum de um artista...\n");
                break;
            case 11:
                printf("Mostrando álbuns de um determinado ano de todos os artistas...\n");
                break;
            case 12:
                printf("Mostrando dados de uma música...\n");
                break;
            case 13:
                printf("Criando playlist...\n");
                break;
            case 14:
                printf("Mostrando dados de uma playlist...\n");
                break;
            case 15:
                printf("Removendo música de uma playlist...\n");
                break;
            case 16:
                printf("Removendo playlist...\n");
                break;
            case 17:
                printf("Removendo música de um álbum de um artista...\n");
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

int main() {
    
    exibirMenu();
    return 0;
}
