#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Padding matriks
int find_nearest_exp(int N)
{
    int exp = 1;
    while(pow(2, exp) < N){
        exp++;
    }
    if(pow(2, exp) > N){
        return pow(2, exp);
    }
    else {
        return N;
    }
}

// Struct untuk mempermudah pembagian matriks menjadi 4 submatriks
typedef struct submatrix
{
    int **A11, **A12, **A21, **A22;
    int **B11, **B12, **B21, **B22;
}extracted_matrix;

// Untuk mengisi matriks dengan angka acak
void fill_matrix(int N, int new_size, int **matrix1, int** matrix2)
{
    for(int i = 0; i < new_size; ++i){
        for(int j = 0; j < new_size; ++j){
            if(j >= N || i >= N){
                matrix1[i][j] = 0;
                matrix2[i][j] = 0;
            }
            else {
                matrix1[i][j] = rand() % 10;
                matrix2[i][j] = rand() % 10;
            }
        }
    }
}

// Menjumlahkan matriks
int** sum_mat(int **mat_A, int **mat_B, int ukuran)
{
    int **hasil_sum = (int**)malloc(ukuran * sizeof(int*));
    for(int i = 0; i < ukuran; ++i){
        hasil_sum[i] = (int*)malloc(ukuran * sizeof(int));
    }

    for(int i = 0; i < ukuran; ++i){
        for(int j = 0; j < ukuran; ++j){
            hasil_sum[i][j] = mat_A[i][j] + mat_B[i][j];
        }
    }
    return hasil_sum;
}

// Menghasilkan selisih matriks A - matriks B
int** subtract_mat(int **mat_A, int **mat_B, int ukuran)
{
    int **hasil_sub = (int**)malloc(ukuran * sizeof(int*));
    for(int i = 0; i < ukuran; ++i){
        hasil_sub[i] = (int*)malloc(ukuran * sizeof(int));
    }

    for(int i = 0; i < ukuran; ++i){
        for(int j = 0; j < ukuran; ++j){
            hasil_sub[i][j] = mat_A[i][j] - mat_B[i][j];
        }
    }
    return hasil_sub;
}

// Membagi matriks menjadi 4 submatriks
extracted_matrix extract_mat(int **matrix1, int **matrix2, int dim)
{
    extracted_matrix submat_temp;
    submat_temp.A11 = (int**)malloc((dim / 2) * sizeof(int*));
    submat_temp.A12 = (int**)malloc((dim / 2) * sizeof(int*));
    submat_temp.A21 = (int**)malloc((dim / 2) * sizeof(int*));
    submat_temp.A22 = (int**)malloc((dim / 2) * sizeof(int*));
    submat_temp.B11 = (int**)malloc((dim / 2) * sizeof(int*));
    submat_temp.B12 = (int**)malloc((dim / 2) * sizeof(int*));
    submat_temp.B21 = (int**)malloc((dim / 2) * sizeof(int*));
    submat_temp.B22 = (int**)malloc((dim / 2) * sizeof(int*));
    for(int i = 0; i < (dim / 2); ++i){
        submat_temp.A11[i] = (int*)malloc((dim / 2) * sizeof(int));
        submat_temp.A12[i] = (int*)malloc((dim / 2) * sizeof(int));
        submat_temp.A21[i] = (int*)malloc((dim / 2) * sizeof(int));
        submat_temp.A22[i] = (int*)malloc((dim / 2) * sizeof(int));
        submat_temp.B11[i] = (int*)malloc((dim / 2) * sizeof(int));
        submat_temp.B12[i] = (int*)malloc((dim / 2) * sizeof(int));
        submat_temp.B21[i] = (int*)malloc((dim / 2) * sizeof(int));
        submat_temp.B22[i] = (int*)malloc((dim / 2) * sizeof(int));
    }

    for(int i = 0; i < dim / 2; ++i){
        for(int j = 0; j < dim / 2; ++j){
            submat_temp.A11[i][j] = matrix1[i][j];
            submat_temp.A12[i][j] = matrix1[i][j + (dim / 2)];
            submat_temp.A21[i][j] = matrix1[i + (dim / 2)][j];
            submat_temp.A22[i][j] = matrix1[i + (dim / 2)][j + (dim / 2)];
            submat_temp.B11[i][j] = matrix2[i][j];
            submat_temp.B12[i][j] = matrix2[i][j + (dim / 2)];
            submat_temp.B21[i][j] = matrix2[i + (dim / 2)][j];
            submat_temp.B22[i][j] = matrix2[i + (dim / 2)][j + (dim / 2)];
        }
    }
    return submat_temp;
}


// Membebaskan memori alokasi isi struct extracted_matrix
void free_struct(extracted_matrix submat, int dim)
{
    for(int i = 0; i < (dim / 2); ++i){
        free(submat.A11[i]);
        free(submat.A12[i]);
        free(submat.A21[i]);
        free(submat.A22[i]);
        free(submat.B11[i]);
        free(submat.B12[i]);
        free(submat.B21[i]);
        free(submat.B22[i]);
    }
    free(submat.A11);
    free(submat.A12);
    free(submat.A21);
    free(submat.A22);
    free(submat.B11);
    free(submat.B12);
    free(submat.B21);
    free(submat.B22);
}

// Algoritma Strassen
int** Strassen(int **mat1, int **mat2, int dim)
{
    if(dim == 1){
        int** temp = (int**)malloc(sizeof(int*));
        temp[0] = (int*)malloc(sizeof(int));
        temp[0][0] = mat1[0][0] * mat2[0][0];
        return temp;
    }
    else {
        int **C = (int**)malloc(dim * sizeof(int*));
        for(int i = 0; i < dim; ++i){
            C[i] = (int*)malloc(sizeof(int) * dim);
        }
        int **M1, **M2, **M3, **M4, **M5, **M6, **M7;
        int **C11, **C12, **C21, **C22;
        extracted_matrix submat;
        submat = extract_mat(mat1, mat2, dim);
        M1 = Strassen(subtract_mat(submat.A12, submat.A22, dim / 2), sum_mat(submat.B21, submat.B22, dim / 2), dim / 2);
        M2 = Strassen(sum_mat(submat.A11, submat.A22, dim / 2), sum_mat(submat.B11, submat.B22, dim / 2), dim / 2);
        M3 = Strassen(subtract_mat(submat.A11, submat.A21, dim / 2), sum_mat(submat.B11, submat.B12, dim / 2), dim / 2);
        M4 = Strassen(sum_mat(submat.A11, submat.A12, dim / 2), submat.B22, dim / 2);
        M5 = Strassen(submat.A11, subtract_mat(submat.B12, submat.B22, dim / 2), dim / 2);
        M6 = Strassen(submat.A22, subtract_mat(submat.B21, submat.B11, dim / 2), dim / 2);
        M7 = Strassen(sum_mat(submat.A21, submat.A22, dim / 2), submat.B11, dim / 2);

        C11 = subtract_mat(sum_mat(sum_mat(M1, M2, dim / 2), M6, dim / 2), M4, dim / 2);
        C12 = sum_mat(M4, M5, dim / 2);
        C21 = sum_mat(M6, M7, dim / 2);
        C22 = subtract_mat(subtract_mat(sum_mat(M2, M5, dim / 2), M3, dim / 2), M7, dim / 2);

        for(int i = 0; i < dim / 2; ++i){
            for(int j = 0; j < dim / 2; ++j){
                C[i][j] = C11[i][j];
                C[i][j + (dim / 2)] = C12[i][j];
                C[i + (dim / 2)][j] = C21[i][j];
                C[i + (dim / 2)][j + (dim / 2)] = C22[i][j];
            }
        }

        free_struct(submat, dim);
        free(M1);
        free(M2);
        free(M3);
        free(M4);
        free(M5);
        free(M6);
        free(M7);
        free(C11);
        free(C12);
        free(C21);
        free(C22);
        return C;
    }
}

int main()
{
    int N, new_size, i ,j;
    clock_t start, end;
    double dura;
    srand(time(0));

    printf("Ukuran matriks : ");
    scanf("%d", &N);
    new_size = find_nearest_exp(N);

    int** A = (int**)malloc(new_size * sizeof(int*));
    int** B = (int**)malloc(new_size * sizeof(int*));
    int **C;
    for(int i = 0; i < new_size; ++i){
        A[i] = (int*)malloc(sizeof(int) * new_size);
        B[i] = (int*)malloc(sizeof(int) * new_size);
    }

    fill_matrix(N, new_size, A, B);
    start = clock();
    C = Strassen(A, B, new_size);
    end = clock();
    dura = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Lama proses : %lf s\n", dura);

    for(int i = 0; i < new_size; ++i){
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
    return 0;
}
