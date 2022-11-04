// Generar numeros aleatorios en distribucion gamma
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double inverse_gamma(){
    return 0;
}

int main(){

    // Definir los numeros aleatorios uniformes
    int N = 1000;
    double numeros[N];
    int val = 100;
    #define RAND_MAX = val;
    for (int i=0; i<N; i++){
        numeros[i] = rand()/val;
    }






    return 0;
}