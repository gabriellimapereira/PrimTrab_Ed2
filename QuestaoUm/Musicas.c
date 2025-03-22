#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "prototipos.h"

InfoMusica lerInfoMusica() {
    InfoMusica info;

    printf("Digite o título da música: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", info.titulo);

    printf("Agora informe a duração dela: ");
    scanf("%d", &info.duracao);

    return info;
}

