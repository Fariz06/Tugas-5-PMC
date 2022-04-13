#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Mengisi kedua matriks dengan angka acak dengan range [0, 10]
void fill_matrix(int N, int **matrix1, int **matrix2)
{
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            matrix1[i][j] = rand() % 10;
            matrix2[i][j] = rand() % 10;
        }
    }
}

// Mencetak isi matriks
void print_mat(int **mat, int dim)
{
    for(int i = 0; i < dim; ++i){
        for(int j = 0; j < dim; ++j){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Menggeser matriks 1 langkah ke atas
void shift_up(int **mat, int dim)
{
    int* temp = (int*)malloc(dim * sizeof(int));
    for(int i = 0; i < dim; ++i){
        temp[i] = mat[0][i];
    }

    for(int i = 0; i < dim - 1; ++i){
        for(int j = 0; j < dim; ++j){
            mat[i][j] = mat[i + 1][j];
        }
    }

    for(int i = 0; i < dim; ++i){
        mat[dim - 1][i] = temp[i];
    }
    free(temp);
}

// Menggeser matriks 1 langkah ke kiri
void shift_left(int **mat, int dim)
{
    int* temp = (int*)malloc(dim * sizeof(int));
    for(int i = 0; i < dim; ++i){
        temp[i] = mat[i][0];
    }

    for(int i = 0; i < dim; ++i){
        for(int j = 0; j < dim - 1; ++j){
            mat[i][j] = mat[i][j + 1];
        }
    }

    for(int i = 0; i < dim; ++i){
        mat[i][dim - 1] = temp[i];
    }
    free(temp);
}

// Menggeser array ke kiri sebanyak times kali
void shift_left_array(int *arr, int dim, int times)
{
    int* temp = (int*)malloc(times * sizeof(int));
    for(int i = 0; i < times; ++i){
        temp[i] = arr[i];
    }

    for(int i = 0; i < dim - times; ++i){
        arr[i] = arr[i + times];
    }

    for(int i = dim - times; i < dim; ++i){
        arr[i] = temp[i - (dim - times)];
    }
    free(temp);
}

// Menggeser kolom dari matriks dengan indeks id_kol sebanyak times kali
void shift_up_array(int **mat, int dim, int id_kol, int times)
{
    int* temp = (int*)malloc(times * sizeof(int));
    for(int i = 0; i < times; ++i){
        temp[i] = mat[i][id_kol];
    }

    for(int i = 0; i < dim - times; ++i){
        mat[i][id_kol] = mat[i + times][id_kol];
    }

    for(int i = dim - times; i < dim; ++i){
        mat[i][id_kol] = temp[i - (dim - times)];
    }
    free(temp);
}

// Menjumlahkan matriks
void sum_mat(int **mat1, int **mat2, int **mat_res, int dim)
{
    for(int i = 0; i < dim; ++i){
        for(int j = 0; j < dim; ++j){
            mat_res[i][j] += (mat1[i][j] * mat2[i][j]);
        }
    }
}


int main()
{
    int N, i, j;
    clock_t start, end;
    double dura;
    srand(time(0));

    printf("Ukuran matriks : ");
    scanf("%d", &N);

    int** mat_A = (int**)malloc(N * sizeof(int*));
    int** mat_B = (int**)malloc(N * sizeof(int*));
    int** mat_C = (int**)calloc(N, sizeof(int*));

    for(i = 0; i < N; ++i){
        mat_A[i] = (int*)malloc(sizeof(int) * N);
        mat_B[i] = (int*)malloc(sizeof(int) * N);
        mat_C[i] = (int*)calloc(N, sizeof(int));
    }

    fill_matrix(N, mat_A, mat_B);

    // Algoritma Cannon
    start = clock();
    // Inisialisasi posisi
    for(i = 0; i < N - 1; ++i){
        shift_left_array(mat_A[i + 1], N, i + 1);
        shift_up_array(mat_B, N, i + 1, i + 1);
    }
    sum_mat(mat_A, mat_B, mat_C, N);

    for(int i = 0; i < N - 1; ++i){
        shift_left(mat_A, N);
        shift_up(mat_B, N);
        sum_mat(mat_A, mat_B, mat_C, N);
    }
    end = clock();

    // Perhitungan lama algoritma Cannon
    dura = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Lama proses : %lf s\n",dura);

    for(i = 0; i < N; ++i){
        free(mat_A[i]);
        free(mat_B[i]);
        free(mat_C[i]);
    }
    free(mat_A);
    free(mat_B);
    free(mat_C);
}
