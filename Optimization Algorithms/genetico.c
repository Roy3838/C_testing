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
    float y_n[puntos];
    float sum_y = 0;
    float p_n[puntos];

    // genetic algorithm to optimize function
    for(int i=1; i<ciclos; i++){
        //evaluar x[]
        for(int k=0; k<puntos; k++){
            y_n[k]= f(x[k]) + 3.7
            sum_y += y_n[k];
        }
        for(int m=0; m<puntos; m++){
            p_n[m] = y_n[m]/sum_y;
        }
        //seleccionar x[] usando como probabilidades p_n[]
        

        




    }




    return 1;
}