#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int baris, kolom;
    time_t t;
    printf("Masukkan baris matriks : \n");
    scanf("%d", &baris);
    printf("Masukkan kolom matriks : \n");
    scanf("%d",&kolom);

    int **matrix1 = (int**)malloc(sizeof(int*) * baris), **matrix2 = (int**)malloc(sizeof(int*) * baris), **matrix3 = (int**)malloc(sizeof(int*) * baris);
    srand((unsigned) time(&t));

    for (int i=0; i < baris; i++) {
        matrix1[i] = (int*)calloc(baris, sizeof(int));
        matrix2[i] = (int*)calloc(baris, sizeof(int));
        matrix3[i] = (int*)calloc(baris, sizeof(int));
    }

    // Mengisi matriks 1 dengan nilai random, dengan range 0-5
    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            matrix1[i][j] = rand() % 5;
        }
    }

    // Menampilkan isi dari matriks 1 untuk pengecekan manual hasil perkalian
    printf("Isi dari matriks 1 adalah : \n");
    for (int i = 0; i < baris; i++){
       for (int j = 0; j < kolom; j++){
            printf("%d ", matrix1[i][j]);
       }
        printf("\n");
    }
    printf("=============================\n");

    // Mengisi matriks 1 dengan nilai random, dengan range 0-5
    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            matrix2[i][j] = rand() % 5;
        }
    }
    printf("Isi dari matriks 2 adalah : \n");
    // Menampilkan isi dari matriks 1 untuk pengecekan manual hasil perkalian

    for (int i = 0; i < baris; i++){
        for (int j = 0; j < kolom; j++){
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }
    printf("=============================\n");


    // Algoritma perkalian matriks menggunakan naive / iterative algorithm
    for (int i = 0; i < baris; i++){
        for (int j = 0; j < kolom; j++){
            matrix3[i][j] = 0;
            for (int k = 0; k < kolom; k++){
                matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    // Menampilkan matriks hasil perkalian matriks 1 dan matriks 2
    printf("Hasil kali matriks 1 dan matriks 2 adalah \n");
    for (int i = 0; i < baris; i++){
        for (int j = 0; j < kolom; j++){
            printf("%d ", matrix3[i][j]);
        }
        printf("\n");
    }


    // Membebaskan memory yang digunakan
    free(matrix1);
    free(matrix2);
    free(matrix3);

    return 0;
}
