/* 	* Universidad Sergio Arboleda
	* Fecha: 22 de febrero de 2022
	* Materia: Parallel Computing
	* Tema: Benchmark en serie. Implementaciòn en c++
	* $>./ejecutable <MatrixSize>
*/
#include <stdlib.h>
#include <iostream>
#include <random>
#include <chrono>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <math.h>
#include <cstring>

/*Definiciòn de constantes*/
struct timespec inicio, fin;

/**** Lugar de las funciones ****/
//Función clración matriz(doble puntero)
double** crearMatrix(int sizeN){
	int i;
	double **matriz = new double* [sizeN];
	for (i=0; i<sizeN; ++i)//Para el segundo puntero
		matriz[i] = new double[sizeN]();
	return matriz;
}

/*Se cra un doble precisiòn aleatorio*/
float randMM(){
	float min = 0.001, max = 9.999;
	static int first = -1;
	if((first =(first<0)))
		srand(time(NULL)+getpid());
	if(min>max)
		return errno=EDOM, NAN;
	return min + (float)rand()/((float)RAND_MAX/(max-min));
}

//Inicializar matrices
void inicializarMatrix(int sizeN, double** &matriz1, double** &matriz2, double** &matriz3){//& es la dirección **es el puntero que apunta a la direcciòn &
	int i, j;
	for (i=0; i<sizeN; ++i){//filas
		for (j=0; j<sizeN; ++j){//Columnas
			matriz1[i][j] = randMM();
			matriz2[i][j] = randMM();
			matriz3[i][j] = 0;			
		}
	}
}
// Función para imprimir las matrices
void printMatrix(double** &matriz, int sizeN){
	int i, j;
	for (i=0; i<sizeN; ++i){//filas
		for (j=0; j<sizeN; ++j){//Columnas
			printf(" %f ", matriz[i][j]);	
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
}


//Retornamos la memoria al sistema (Destruir las matrices)
void DestruirMatriz(int sizeN, double** &matriz){
	if (matriz){
		int i;
		for (i=0; i<sizeN; ++i){//filas
			delete[] matriz[i];//se borra cada fila
		}
		delete[] matriz;  //se borra todas las filas
		matriz = nullptr; //se entrega MEM al system
	}
}


// Función multiplicación matrices 
//Algoritmo clásico (filas x columnas)
double** productoMatrices(int sizeN, double** &matriz1, double** &matriz2){
	int i, j ,k;
	double** matriz = crearMatrix(sizeN);
	for (i=0; i<sizeN; ++i){//filas
		for (j=0; j<sizeN; ++j){//Columnas
			for (k=0; k<sizeN; ++k){//producto
				matriz[i][j] += matriz1[i][k]*matriz2[k][j];
			}		
		}
	}
	return matriz;
}


/*Inicio: medida de tiempo*/
void SampleStart(){
	clock_gettime(CLOCK_MONOTONIC, &inicio); //& està indicando la direcciòn de inicio
}

/*Fin: medida de tiempo*/
void SampleEnd(){
	clock_gettime(CLOCK_MONOTONIC, &fin); //& està indicando la direcciòn de inicio
	/* Se imprime el tiempo*/
	double tiempoTotal;
	tiempoTotal = (fin.tv_sec - inicio.tv_sec)*1e9;//tv_sec es una funciòn de struct//// 1e9 son macrosegundos
	tiempoTotal = (tiempoTotal + (fin.tv_nsec - inicio.tv_nsec))*1e-9;
	printf(" %f \n", tiempoTotal);
	
}

/**** Función principal ****/
int main(int argc, char *argv[]){
	/*Sección de declaración*/
	int i, j, k;
	int N = atoi(argv[1]); //Dimensión (Size) de las matrices
	//std::cout <<N<<std::endl;

	double** matA = crearMatrix(N);
	double** matB = crearMatrix(N);
	double** matC = crearMatrix(N);
	inicializarMatrix(N, matA, matB, matC);
	//printMatrix(matA, N);
	//printMatrix(matB, N);
	SampleStart();
	matC = productoMatrices(N, matA, matB);
	SampleEnd();
	//printMatrix(matC, N);
	DestruirMatriz(N, matA);
	DestruirMatriz(N, matB);
	DestruirMatriz(N, matC);
	
	return 0;

}


