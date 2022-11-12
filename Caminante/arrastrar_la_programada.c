#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void recursiveIteration(int ciclo, int N, float cara, float cruz){
    if (ciclo<N){
        int r = rand()%2;
        printf("%d", r);
        if (r>1){
            recursiveIteration(++ciclo,N,++cara,cruz);
        }
        else{
            recursiveIteration(++ciclo,N,cara,++cruz);
        }
    }
    else{
        printf("Recursividad acabada\n");
        printf("ciclo %d\n", ciclo);
        printf("cara %d\n", cara);
        printf("cruz %d\n", cruz);
    }
}
int main(){
    //lanzado de moneda a ver que pex 
    //interpretacion clasica
    float Pclasica = 0.5;
    //interpretacion frecuentistica
    int N = 1000;
    recursiveIteration(0,N,0,0);
    return 0;
}
