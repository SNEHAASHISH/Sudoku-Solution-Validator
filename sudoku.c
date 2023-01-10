#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int sudoku[9][9] = {
        {6, 2, 4, 5, 3, 9, 1, 8, 7},
        {5, 1, 9, 7, 2, 8, 6, 3, 4},
        {8, 3, 7, 6, 1, 4, 2, 9, 5},
        {1, 4, 3, 8, 6, 5, 7, 2, 9},
        {9, 5, 8, 2, 4, 7, 3, 6, 1},
        {7, 6, 2, 3, 9, 1, 4, 5, 8},
        {3, 7, 1, 9, 5, 6, 8, 4, 2},
        {4, 9, 6, 1, 8, 2, 5, 7, 3},
        {2, 8, 5, 4, 7, 3, 9, 1, 6}
};

bool verification[11]; 
int auxQuadrant = 2; 

typedef struct { 
    int fila;
    int columna;
} parameter;

pthread_t columnas, fila, primer_cuadro, segundo_cuadro, tercer_cuadro,
        cuarto_cuadro, quinto_cuadro, sexto_cuadro, septimo_cuadro, octavo_cuadro, noveno_cuadro;

void *recorrerColumna(void *parameters) {

    parameter *columna = (parameter *) parameters;
    int columnaInicial = columna->columna;
    int filaInicial = columna->fila;

    for (int i = columnaInicial; i < 9; i++) {
        int col[9] = {0}; 
        for (int j = filaInicial; j < 9; j++) {
            int aux = sudoku[i][j];
            if (col[aux - 1] == 0 && aux > 0) { 
                col[aux - 1] = aux;     
            } else if (aux <= 0) {
                verification[0] = 0;
                printf("Lo lamento, en la columna [%d] hay un número no válido.\n", j + 1);
                pthread_exit(0);
            } else {
                verification[0] = 0;
                printf("Lo lamento, en la columna [%d] hay un numero repetido.\n", j + 1);
                pthread_exit(0);
            }
        }
    }
    verification[0] = 1;
    pthread_exit(0);    
}

void *recorrerFilas(void *parameters) {

    parameter *fila = (parameter *) parameters;
    int columnaInicial = fila->columna;
    int filaInicial = fila->fila;

    for (int i = columnaInicial; i < 9; i++) {
        int fil[9] = {0};
        for (int j = filaInicial; j < 9; j++) {
            int aux = sudoku[i][j];
            if (fil[aux - 1] == 0 && aux > 0) {
                fil[aux - 1] = aux;
            } else if (aux <= 0) {
                verification[0] = 0;
                printf("Lo lamento, en la fila [%d] hay un número no válido.\n", i + 1);
                pthread_exit(0);
            } else {
                verification[0] = 0;
                printf("Lo lamento, en la fila [%d] hay un numero repetido.\n", i + 1);
                pthread_exit(0);
            }
        }
    }
    verification[1] = 1;
    pthread_exit(0);
}

void *recorrerCuadrado(void *parameters) {

    parameter *cuadradroW = (parameter *) parameters;
    int filaInicial = cuadradroW->fila;
    int columnaInicial = cuadradroW->columna;
    int square[9] = {0};

    for (int i = filaInicial; i < filaInicial + 3; ++i) {
        for (int j = columnaInicial; j < columnaInicial + 3; ++j) {
            int aux = sudoku[i][j];
            if (square[aux - 1] == 0 && aux > 0) {
                square[aux - 1] = aux;
            }
            else {
                verification[auxQuadrant] = 0;
                auxQuadrant++;
                pthread_exit(0);
            }
        }
    }
    verification[auxQuadrant] = 1;
    auxQuadrant++;
    pthread_exit(0);
}

int main() {

    parameter *verificarFilas = (parameter *) malloc(sizeof(parameter));
    verificarFilas->fila = 0;
    verificarFilas->columna = 0;

    parameter *verificarColumnas = (parameter *) malloc(sizeof(parameter));
    verificarColumnas->fila = 0;
    verificarColumnas->columna = 0;

    parameter *cuadro1 = (parameter *) malloc(sizeof(parameter));
    cuadro1->fila = 0;
    cuadro1->columna = 0;

    parameter *cuadro2 = (parameter *) malloc(sizeof(parameter));
    cuadro2->fila = 0;
    cuadro2->columna = 3;

    parameter *cuadro3 = (parameter *) malloc(sizeof(parameter));
    cuadro3->fila = 0;
    cuadro3->columna = 6;

    parameter *cuadro4 = (parameter *) malloc(sizeof(parameter));
    cuadro4->fila = 3;
    cuadro4->columna = 0;

    parameter *cuadro5 = (parameter *) malloc(sizeof(parameter));
    cuadro5->fila = 3;
    cuadro5->columna = 3;

    parameter *cuadro6 = (parameter *) malloc(sizeof(parameter));
    cuadro6->fila = 3;
    cuadro6->columna = 6;

    parameter *cuadro7 = (parameter *) malloc(sizeof(parameter));
    cuadro7->fila = 6;
    cuadro7->columna = 0;

    parameter *cuadro8 = (parameter *) malloc(sizeof(parameter));
    cuadro8->fila = 6;
    cuadro8->columna = 3;

    parameter *cuadro9 = (parameter *) malloc(sizeof(parameter));
    cuadro9->fila = 6;
    cuadro9->columna = 6;

    pthread_create(&columnas, NULL, recorrerColumna, (void *) verificarColumnas);
    pthread_create(&fila, NULL, recorrerFilas, (void *) verificarFilas);
    pthread_create(&primer_cuadro, NULL, recorrerCuadrado, (void *) cuadro1);
    pthread_create(&segundo_cuadro, NULL, recorrerCuadrado, (void *) cuadro2);
    pthread_create(&tercer_cuadro, NULL, recorrerCuadrado, (void *) cuadro3);
    pthread_create(&cuarto_cuadro, NULL, recorrerCuadrado, (void *) cuadro4);
    pthread_create(&quinto_cuadro, NULL, recorrerCuadrado, (void *) cuadro5);
    pthread_create(&sexto_cuadro, NULL, recorrerCuadrado, (void *) cuadro6);
    pthread_create(&septimo_cuadro, NULL, recorrerCuadrado, (void *) cuadro7);
    pthread_create(&octavo_cuadro, NULL, recorrerCuadrado, (void *) cuadro8);
    pthread_create(&noveno_cuadro, NULL, recorrerCuadrado, (void *) cuadro9);
    
    pthread_join(columnas, NULL);
    pthread_join(fila, NULL);
    pthread_join(primer_cuadro, NULL);
    pthread_join(segundo_cuadro, NULL);
    pthread_join(tercer_cuadro, NULL);
    pthread_join(cuarto_cuadro, NULL);
    pthread_join(quinto_cuadro, NULL);
    pthread_join(sexto_cuadro, NULL);
    pthread_join(septimo_cuadro, NULL);
    pthread_join(octavo_cuadro, NULL);
    pthread_join(noveno_cuadro, NULL);

    for (int k = 0; k < 11; ++k) {
        if (!verification[k]) {
            printf("\nUpss... El Sudoku NO fue resuelto.\n");
            exit(0);
        }
    }
    printf("\nBien!!! Felicitaciones, el Sudoku fue resuelto.\n");
    return 0;
}
