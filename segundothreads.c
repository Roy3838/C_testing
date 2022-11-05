#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdatomic.h>
#include <pthread.h>
#include <omp.h>



 
int main()
{

void correr(){
    int iter = 1000;
    int pos[iter];
    pos[0] = 0;


    for (int i=1; i<iter; i++){
        int r = rand()%3 -1;
        pos[i] = pos[i-1] + r;
    
    }
    //return pos[iter-1];
}
    
    int i;
    pthread_t tid;
    clock_t start, end;
    double cpu_time_used;
    int N = 100;
    int dist[N];
    //static int iter = 1000;


    start = clock();
    for (i = 0; i < N; i++){
        correr();
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds \n",cpu_time_used);

    return 0;
}