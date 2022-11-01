#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// codigo que va a graficar el valor de un dado random a traves del tiempo

int main(){
    int lados_dado=20; //numero de lados del dado
    float probabilidad_dado=1.0/lados_dado; // probabilidad de que salga un numero del dado
    int N=1000; // numero de lanzamientos
    int contador=0; // contador de lanzamientos
    //arreglo en el que se guardan los valores del dado
    int dado[N]; // arreglo en el que se guardan los valores del dado
    //int valor_frecuentista[N]; // arreglo en el que se guardan los esperados del dado
    int valoracumulado[N][lados_dado]; // arreglo en el que se guardan los valores acumulados del dado
    double frecuencia_relativa[N][lados_dado]; // arreglo en el que se guardan los valores acumulados del dado

    //se llena el arreglo con valores random
    for (int i=0; i<N; i++){
        dado[i]= rand()%10 + rand()%10; // se llena el arreglo con valores random
    }

    // acumula la frecuencia relativa de cada lado del dado
    for (int i=0; i<N; i++){
        int caradedado=dado[i]; // se guarda el valor del dado en una variable
        //hacer acumulacion
        for (int j=0; j<lados_dado; j++){
            valoracumulado[i][j]=valoracumulado[i-1][j];
            frecuencia_relativa[i][j]=valoracumulado[i-1][j]/(float)i;
        }
        valoracumulado[i][caradedado]++; // se suma el valor del dado
    }

    //PLOTTING DE LA FRECUENCIA RELATIVA A TRAVES DEL TIEMPO
        FILE *fpPuntos=fopen("puntos_dos_dados.txt","w"); // se crea un archivo de texto para guardar los valores del dado
        for (int i=0; i<lados_dado; i++){
            if (i%1==0){
                fprintf(fpPuntos,"%i %f \n",i,frecuencia_relativa[N-1][i]);
            }
        }
        fclose(fpPuntos);
        FILE *fp = popen("gnuplot -persist", "w");
        fprintf(fp, "plot \"puntos_dos_dados.txt\" with lines\n");   








    //PLOTTING DE LOS VALORES ESPERADOS DE LOS DOS DADOS
    return 0;
}