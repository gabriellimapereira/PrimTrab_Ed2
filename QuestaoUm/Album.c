#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

InfoAlbum lerInfoAlbum() {
    InfoAlbum info;

    printf("Digite o título do álbum: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.titulo);

    printf("Agora informe o ano de lançamento: ");
    scanf("%d", &info.anoLancamento);

    info.quantMusicas = 0;
    info.musica = NULL;

    return info;
}
