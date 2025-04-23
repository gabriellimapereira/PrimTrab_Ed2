#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "prototipos.h"

int main() {
    srand(time(NULL));
    ArvArtista *arv = NULL;
    clock_t inicio, fim;
    double tempo, tempoMicro;
    double somaTempo = 0.0, somaTempoMicro = 0.0;
    int numInsercoes = 30000;
    char str[15];

    for (int j = 0; j < 30; j++) {
        arv = NULL;

        for (int i = numInsercoes; i >= 1; i--) {
            sprintf(str, "%d", i);  // converte i para string
            InfoArtista info;
            strcpy(info.nome, str);
            ArvArtista *art = alocarNoArt(info);
            insereNoArt(&arv, art);
        }

        // agora cronometrando a última inserção
        sprintf(str, "0");
        InfoArtista ultimaInfo;
        strcpy(ultimaInfo.nome, str);
        ArvArtista *ultimaArt = alocarNoArt(ultimaInfo);

        inicio = clock();
        insereNoArt(&arv, ultimaArt);
        fim = clock();

        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        tempoMicro = tempo * 1000000.0;

        somaTempo += tempo;
        somaTempoMicro += tempoMicro;

        liberaArvArt(arv);
    }

    printf("\n--- MÉDIAS DAS INSERÇÕES ---\n");
    printf("média de tempo em segundos: %.10f segundos\n", somaTempo / 30.0);
    printf("média de tempo em microssegundos: %.2f microssegundos\n", somaTempoMicro / 30.0);

    return 0;
}

