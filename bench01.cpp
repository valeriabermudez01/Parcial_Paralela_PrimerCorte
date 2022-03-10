/*Universidad Sergio Arboleda
*Fecha: 03-02-2022
*Materia: Computación Paralela y Distribuida
*Tema: Construcción del Primer Benchmark
*Benchmark: Aplicación de juguete que permite evaluar rendimiento de un aspecto 
*en específico de la computadora
*/

/*Se declaran las interfaces */
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <unistd.h>
#include <math.h>

using namespace std;

/*Definiciòn de constantes*/
struct timespec inicio, fin;

/* ----------------------------- -------Funciones ------------------------------------*/

/* Inicio: medida de tiempo*/
void sampleStart(){
	clock_gettime(CLOCK_MONOTONIC, &inicio);	
}

/*Fin: medida de tiempo*/
void sampleEnd(){
	clock_gettime(CLOCK_MONOTONIC, &fin);	//& està indicando la direcciòn de inicio
	/* Se imprime el tiempo*/
	double totalTime; //tv_sec es una funciòn de struct//// 1e9 son macrosegundos
	totalTime = (fin.tv_sec - inicio.tv_sec)*1e9;
	totalTime = (totalTime + (fin.tv_nsec - inicio.tv_nsec))*1e-9;
	printf(" %f \n", totalTime);
}

/*Se crea un doble precisiòn aleatorio*/
double randNumber(){
    float min = 0.001, max = 9.999;
    static int first = -1;
    if(first = (first < 0)){
       srand(time(NULL) + getpid());
    }
    if(min >= max){
        return errno = EDOM, NAN;
    }
    return min + (float)rand()/((float)RAND_MAX/(max-min));
}

/**** Lugar de las funciones ****/
/*Función declaración matriz(doble puntero) */
vector<vector<double>> matrixInit(int size){
	int i, j;
	vector<vector<double>> MI(size, vector<double> (size,0)); 
    	
	for (i=0; i<size; ++i){
		for (j=0; j<size; ++j){
			MI[i][j] = randNumber();
		}
	}
	return MI;	
}


/* Función multiplicación matrices 
   Algoritmo clásico (filas x columnas) */
void matrixMultiply (vector<vector<double>> MA, vector<vector<double>>MB){
	int i, j, k;
	vector<vector<double>> MT (MA.size(), vector<double> (MA.size(),0));;
	
	for(i = 0; i<MA.size(); ++i){
		for(j = 0; j<MA.size(); ++j){
			for(k = 0; k<MA.size(); ++k){
				MT[i][j] += MA[i][k]*MB[k][j];
			}
		}
	}	
}


int main (int argc, char** argv) {
	int k;
	int N = atoi(argv[1]);
	
	//Se utiliza la clase vector para crear las matrices
	//Matrix of size N con 0
	vector<vector<double>> M1(N, vector<double> (N,0)); 
	vector<vector<double>> M2(N, vector<double> (N,0));
	vector<vector<double>> MR(N, vector<double> (N,0));
	
	M1 = matrixInit(N);
	M2 = matrixInit(N);	
	
	sampleStart();
	matrixMultiply(M1, M2);
	sampleEnd();
	return 0;
}






