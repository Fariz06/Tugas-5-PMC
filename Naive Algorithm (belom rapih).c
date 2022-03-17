#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int baris, kolom;
    time_t t;
    scanf("%d %d", &baris, &kolom);
    int **matrix1 = (int**)malloc(sizeof(int*) * baris), **matrix2 = (int**)malloc(sizeof(int*) * baris), **matrix3 = (int**)malloc(sizeof(int*) * baris);
    srand((unsigned) time(&t));

    for (int i=0; i < baris; i++) {
        matrix1[i] = (int*)calloc(baris, sizeof(int));
        matrix2[i] = (int*)calloc(baris, sizeof(int));
        matrix3[i] = (int*)calloc(baris, sizeof(int));
    }

    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            matrix1[i][j] = rand() % 5;
        }
    }

    for (int i = 0; i < baris; i++){
       for (int j = 0; j < kolom; j++){
            printf("%d ", matrix1[i][j]);
       }
        printf("\n");
    }
    printf("=============================\n");

    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            matrix2[i][j] = rand() % 5;
        }
    }

    for (int i = 0; i < baris; i++){
        for (int j = 0; j < kolom; j++){
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }
    printf("=============================\n");

    for (int i = 0; i < baris; i++){
        for (int j = 0; j < kolom; j++){
            matrix3[i][j] = 0;
            for (int k = 0; k < kolom; k++){
                matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    for (int i = 0; i < baris; i++){
        for (int j = 0; j < kolom; j++){
            printf("%d ", matrix3[i][j]);
        }
        printf("\n");
    }

    return 0;
}
