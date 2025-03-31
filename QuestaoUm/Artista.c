#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

InfoArtista lerInfoArtista() {
    InfoArtista info;

    printf("digite o dado: ");
    scanf("%d", &info.dado);

    info.album = NULL;

    return info;
}
