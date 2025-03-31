#include <stdio.h>
#include <stdlib.h>
#include "prototipos.h"

void exibirMenu() {
    int opcao;
    
    do {
        printf("\n---------- Menu ----------\n");
        printf("1. Cadastrar Artista\n");
        printf("2. Cadastrar Álbum\n");
        printf("3. Cadastrar Música\n");
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
                printf("Cadastrando artista...\n");
                break;
            case 2:
                printf("Cadastrando álbum...\n");
                break;
            case 3:
                printf("Cadastrando música...\n");
                break;
            case 4:
                printf("Mostrando todos os artistas...\n");
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
