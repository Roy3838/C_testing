#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>



int main(){

    float f(float x){
        return (x + pow(x,2))*cos(x);
    }

    int puntos = 100;
    float x[puntos];
    int ciclos = 1000;
    float x_n[puntos];

    // genetic algorithm to optimize function
    for(int i=1; i<ciclos; i++){
        //evaluar x[]
        for(int k=0; k<puntos; k++){
            x_n[k]=f(x[k])
        }



    }




    return 1;
}