#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdatomic.h>
#include <pthread.h>

int correr(){
    int iter = 1000;
    int pos[iter];
    pos[0] = 0;


    for (int i=1; i<iter; i++){
        int r = rand()%3 -1;
        pos[i] = pos[i-1] + r;
    
    }
    return pos[iter-1];
}

int main(){
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    int N = 1;
    int dist[N];
    for (int i=0; i<N; i++){
        dist[i] = correr();
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    //distancia promedio
    double sum = 0;
    for (int i=0; i<N; i++){
        sum += dist[i];
    }
    double prom = sum/N;
    printf("%f \n",cpu_time_used);
    printf("%f",prom);


    // FILE *fpPuntos=fopen("data/F1_2.txt","w");
    // for (int i=1; i<N; i++){
    //     if (i%1==0){
    //         fprintf(fpPuntos,"%d %d \n",i,dist[i]);
    //     }
    // }
    // fclose(fpPuntos);
    // FILE *fp = popen("gnuplot -persist", "w");
    // fprintf(fp, "set title 'Random walk'\n");
    // fprintf(fp, "set xlabel 'x'\n");
    // fprintf(fp, "set ylabel 'y'\n");
    // fprintf(fp, "set xrange [0:100]\n");    
    // fprintf(fp, "set yrange [-100:100]\n");
    // fprintf(fp, "plot 'data/F1_2.txt' with lines\n");

    return 0;
}