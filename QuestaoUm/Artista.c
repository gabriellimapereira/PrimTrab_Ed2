#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

InfoArtista lerInfoArtista() {
    InfoArtista info;

    printf("Digite o nome do artista: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.nome);

    printf("Agora informe o tipo de artista: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.tipo);

    printf("Digite o estilo musical desse artista: ");
    etbuf(stdin, NULL);
    scanf("%[^\n]", info.estilo);

    info.numAlbuns = 0;
    info.album = NULL;

    return info;
}