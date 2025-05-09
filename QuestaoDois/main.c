#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"

void menuPlaylist(ArvPlaylist **r, ArvArtista *rArt) {
    int op, inseriu, removeu;
    char nome[50];
    ArvPlaylist *play = NULL; 
    do {
        printf("\n--- MENU DE PLAYLIST ---\n");
        printf("1 - Criar playlist\n");
        printf("2 - Mostrar dados de uma playlist\n");
        printf("3 - Remover música de uma playlist\n");
        printf("4 - Remover playlist\n");
        printf("5 - Imprimir playlists\n");
        printf("6 - Inserir música em uma playlist\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1:
                inseriu = insereNoPlaylist(r, alocarNoPlaylist(lerInfoPlaylist()));
                if (inseriu) 
                    printf("Nova playlist inserida!\n");
                else
                    printf("Há uma playlist de mesmo nome. A inserção não foi feita.\n");
                break;
            case 2:
                printf("Digite o nome da playlist: \n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                play = buscarPlaylist(*r, nome);
                if (play) {
                    printf("Músicas: \n");
                    imprimeArvMusP((*play).info.musica);
                } else 
                    printf("Playlist não encontrada!\n");
                break;
            case 3:
                char mus[50];

                printf("Digite o nome da playlist: \n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                play = buscarPlaylist(*r, nome);
                if (play) {
                    char musica[50];
                    printf("Digite o nome da música: \n");
                    setbuf(stdin, NULL);
                    scanf("%[^\n]", musica);
                    removeu = removerMusP(&((*play).info.musica), musica);
                    if (removeu) 
                        printf("Música removida da playlist!\n");
                    else 
                        printf("Música não encontrada\n");
                } else 
                    printf("Playlist não encontrada!\n");
                break;
            case 4:
                printf("Digite o nome da playlist: \n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                removeu = removerPlaylist(r, nome);
                if (removeu) 
                    printf("Remoção feita com sucesso!\n");
                else 
                    printf("Playlist não encontrada!\n");
                break;
            case 5:
                imprimeArvPlaylist(*r);
                break;
            case 6:
                printf("Digite o nome da playlist: \n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                play = buscarPlaylist(*r, nome);
                if (play) {
                    printf("Digite o nome da artista dessa música: ");
                    setbuf(stdin, NULL);
                    scanf("%[^\n]", nome);
                    ArvArtista *art = buscarArtista(rArt, nome);
                    if (art) {
                        printf("Digite o nome do álbum ao qual a música pertence: ");
                        setbuf(stdin, NULL);
                        scanf("%[^\n]", nome);
                        ArvAlbum *alb = buscarAlbum((*art).info.album, nome);
                        if (alb) {
                            printf("Digite o nome da música: \n");
                            setbuf(stdin, NULL);
                            scanf("%[^\n]", nome);
                            ArvMusica *mus = buscarMusica((*alb).info.musica, nome);
                            if (mus) {
                                
                                int inseriu = insereNoMusP(&((**r).info.musica), alocarNoMusP(copiaDadosMusica(art, alb, mus))); 
                                if (inseriu) 
                                    printf("Inserção feita com sucesso!\n");
                                else 
                                    printf("Música já presente na playlist!\n");
                            } else 
                                printf("Música não encontrada!\n");
                        } else 
                            printf("Álbum não encontrado!\n");
                    } else 
                        printf("Artista não encontrado!\n");
                } else
                    printf("Pĺaylist não encontrada!\n");
                break;
            case 7:
                break;
        }
    } while (op != 0);
    return;
}

int main() {
    ArvArtista *raizArtista = inicializarArvArt();
    ArvPlaylist *raizPlaylist = NULL;
    char nome[50];
    ArvArtista *art = NULL;
    ArvAlbum *alb = NULL;
    int ano;

    int opcao;

    do {
        printf("\n========= MENU =========\n");
        printf("1. Cadastrar Artista\n");
        printf("2. Cadastrar Álbum\n");
        printf("3. Cadastrar Música\n");
        printf("4. Mostrar todos os artistas cadastrados\n");
        printf("5. Mostrar artistas por tipo\n");
        printf("6. Mostrar artistas por estilo musical\n");
        printf("7. Mostrar artistas por estilo musical e tipo\n");
        printf("8. Mostrar álbuns de um artista\n");
        printf("9. Mostrar álbuns de um ano de um artista\n");
        printf("10. Mostrar músicas de um álbum de um artista\n");
        printf("11. Mostrar álbuns de um ano de todos os artistas\n");
        printf("12. Mostrar dados de uma música\n");
        printf("13. Remover música de um álbum de um artista\n");
        printf("14. Menu de Playlist\n");
        printf("0. Sair\n");
        printf("========================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                int inseriu = insereNoArt(&raizArtista, alocarNoArt(lerInfoArt()));
                if (inseriu) 
                    printf("Artista cadastrado!\n");
                else 
                    printf("Artista já está na árvore. A inserção não foi feita!\n");
                break;
            case 2:
                printf("Digite o nome do artista: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                art = buscarArtista(raizArtista, nome);
                if (art) {
                    int inseriu = insereNoAlbum(&((*art).info.album), alocarNoAlbum(lerInfoAlbum()));
                    if (inseriu) {
                        printf("Álbum cadastrado!\n");
                        (*art).info.quantAlbum++;
                    } else 
                        printf("Álbum já está na árvore. A inserção não foi feita!\n");
                } else 
                    printf("Artista não encontrado!\n");
                break;
            case 3:
                printf("Digite o nome do artista: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                art = buscarArtista(raizArtista, nome);
                if (art) {
                    printf("Digite o nome do álbum: ");
                    setbuf(stdin, NULL);
                    scanf("%[^\n]", nome);
                    alb = buscarAlbum((*art).info.album, nome);
                    if (alb) {
                        int inseriu = insereNoMus(&((*alb).info.musica), alocarNoMusica(lerInfoMusica()));
                        if (inseriu) {
                            printf("Música cadastrada!\n");
                            (*alb).info.quantMus++;
                        } else 
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
                printf("Digite o nome do artista: \n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                albunsArtista(raizArtista, nome);
                break;
            case 9:
                printf("Digite o nome do artista: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                art = buscarArtista(raizArtista, nome);
                if (art) {
                    printf("Digite o ano: \n");
                    scanf("%d", &ano);
                    imprimeAlbumAno((*raizArtista).info.album, ano);
                } else 
                    printf("Artista não encontrado!\n");
                break;
            case 10:
                printf("Digite o nome do artista: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                art = buscarArtista(raizArtista, nome);
                if (art) {
                    printf("Digite o nome do álbum: ");
                    setbuf(stdin, NULL);
                    scanf("%[^\n]", nome);
                    alb = buscarAlbum((*art).info.album, nome);
                    if (alb) {
                        imprimeArvMus((*alb).info.musica);
                    } else 
                    printf("Álbum não encontrado!\n");
                } else 
                    printf("Artista não encontrado!\n");
                break;
            case 11:
                if (raizArtista) {
                    printf("Digite o ano: \n");
                    scanf("%d", &ano);
                    imprimeAlbumAno((*raizArtista).info.album, ano);
                } else {
                    printf("Não há nenhum artista cadastrado!\n");
                }
                break;
            case 12:
                printf("Digite o nome da música: \n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                int duracao;
                char album[100];

                dadosMusica(raizArtista, nome, &duracao, album);
                break;
            case 13:
                printf("Digite o nome do artista: \n");
                setbuf(stdin, NULL);
                scanf("%[^\n]", nome);
                art = buscarArtista(raizArtista, nome);
                if (art) {
                    printf("Digite o nome do álbum: \n");
                    setbuf(stdin, NULL);
                    scanf("%[^\n]", nome);
                    ArvAlbum *alb = buscarAlbum((*art).info.album, nome);
                    if (alb) {
                        printf("Digite o nome da música: \n");
                        setbuf(stdin, NULL);
                        scanf("%[^\n]", nome);
                        ArvMusP *musicaExiste = buscaMusicaEmPlaylist(raizPlaylist, nome);
                        if (musicaExiste) {
                            printf("A música está em uma playlist atualmente. Remova ela dessa playlist pra removê-la daqui.\n");
                        } else {
                            int removeu = removerMus(&((*alb).info.musica), nome);
                            if (removeu) 
                                printf("Música removida com sucesso!\n");
                            else 
                                printf("Música não encontrada!\n");
                        }
                    } else 
                        printf("Álbum não encontrado!\n");
                } else 
                    printf("Artista não encontrado!\n");
                break;
            case 14:
                menuPlaylist(&raizPlaylist, raizArtista);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    liberaArvArt(raizArtista);
    return 0;
}
