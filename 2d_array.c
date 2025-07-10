#include <stdio.h>
#include <stdlib.h>

void isiArray2D(int **arr, int baris, int kolom) {
	int i = 0;
    while (i < baris) {
    	int j = 0;
        while (j < kolom) {
            arr[i][j] = i * kolom + j;
            j++;
        }
        i++;
    }
}

void tampilkanArray2D(int **arr, int baris, int kolom) {
	int i = 0;
    while (i < baris) {
    	int j = 0;
        while (j < kolom) {
            printf("%d ", arr[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

int main() {
    int baris = 3, kolom = 4;

    int **array2D = (int **)malloc(baris * sizeof(int *));
    int i = 0;
    while (i < baris) {
        array2D[i] = (int *)malloc(kolom * sizeof(int));
        i++;
    }

    isiArray2D(array2D, baris, kolom);
    tampilkanArray2D(array2D, baris, kolom);

    i = 0;
    while (i < baris) {
        free(array2D[i]);
        i++;
    }
    free(array2D);

    return 0;
}
