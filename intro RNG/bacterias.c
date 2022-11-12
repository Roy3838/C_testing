#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


int main(){
    int N = 1000;
    // in MATLAB su=[1 randi(2,1,N)]-1
    // in C 
    int su[N];
    for (int i=0; i<N; i++){
        su[i] = rand() % 2;
    }
    // in MATLAB Acc=cumsum(su)
    // in C
    int Acc[N];
    Acc[0] = su[0];
    for (int i=1; i<N; i++){
        Acc[i] = Acc[i-1] + su[i];
    }
    //PLOTTING DE LA FRECUENCIA RELATIVA A TRAVES DEL TIEMPO
    FILE *fpPuntos=fopen("puntos_bac.txt","w"); // se crea un archivo de texto para guardar los valores del dado
    for (int i=0; i<N; i++){
            fprintf(fpPuntos,"%i %i \n", i,Acc[i]);
    }
    fclose(fpPuntos);
    FILE *fp = popen("gnuplot -persist", "w");
    fprintf(fp, "plot \"puntos_bac.txt\" with lines\n");   

    // MATLAB code expValnum = [sum(su(1:100)) sum(su(1:1000)) sum(su(1:10000))];
    // C code
    // int expValnum[3];
    // for (int i=0; i<3; i++){
    //     int sum = 0;
    //     double power=pow(10,i+1);
    //     for (int j=0; j<power; j++){
    //         sum += su[j];
    //     }
    //     expValnum[i] = sum;
    // }


}


