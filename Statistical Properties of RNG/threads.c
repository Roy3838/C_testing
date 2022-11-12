#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
// Let us create a global variable to change it in threads
int g = 0;
 
// The function to be executed by all threads
void *myThreadFun(void *vargp)
{
    // Store the value argument passed to this thread
    //int *myid = (int *)vargp;

    // Print thread id
    //printf("Thread ID: %d:", *myid);

    int iter = 1000;
    int pos[iter];
    pos[0] = 0;
    for (int i=1; i<iter; i++){
        int r = rand()%3 -1;
        pos[i] = pos[i-1] + r;
    
    }
    
}
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

 
int main()
{
    int i;
    pthread_t tid;
    clock_t start, end;
    double cpu_time_used;
    int N = 100;
    int dist[N];
    //static int iter = 1000;


    start = clock();
    

    for (i = 0; i < N; i++){
        //dist[i] = pthread_create(&tid, NULL, myThreadFun, (void *)&tid);
        // without multi-threading
        dist[i] = correr();
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    //distancia promedio
    // double sum = 0;
    // for (int i=0; i<N; i++){
    //     sum += dist[i];
    // }
    // double prom = sum/N;
    //printf("ke");
    printf("%f \n",cpu_time_used);
    //printf("%f",prom);
    //pthread_exit(NULL);



    return 0;
}