#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

double roy_uniform(double a, double b, double d){
    /*
    Funcion que genera un numero aleatorio uniforme entre "a" y "b"
    con una cantidad de decimales "d".
    */
    b = b*pow(10,d);
    a = a*pow(10,d);
    int r = rand() % (int)(b-a) + a;
    double m=(double)r/pow(10,d);
    return m;
}

int main(){
    static int n = 5;


    // Se tiene esta funcion de optimizacion
    double dist(int n, double x[1][n]){
        double x_sum = 0;

        double c[5] = {0.1, 0.2, 0.2, 0.4, 0.4};
        double A[5][4] = {{4,4,4,4},{1,1,1,1},{8,8,8,8},{6,6,6,6},{3,7,3,7}};

        for(int i = 0; i < 5; i++){
            for(int j = 0; j<n; j++){
                double div = 1/(pow(2,abs(x[0][j]-A[i][j])) + c[i]);
                x_sum += div;
            }
        }
        return -x_sum;
    }

    // Y se crea una funcion que crea un vector vecino a x[]
    void vecindad(int n, double x[1][n]){
        for(int i=1; i<n; i++){   
            x[0][i]=x[0][i]+roy_uniform(-0.1,0.1,5);
        }
    }

    // PARAMETROS DEL METODO RECOCIDO
    double alpha = 0.95;
    int L = 3000;
    double T_0 = 300;
    double T_min = 0.000000001;

    double x[1][n];
    srand(time(NULL));
    clock_t start, end;
    double cpu_time_used;    

    // se genera el x de 0 a n siendo 
    for (int i = 0; i < n; i++){
        x[0][i]=i;
    }
    
    /*
    RECOCIDO SIMULADO BUENO
    */

    // la memoria de las matrices tiene que ser estatica
    double x_0[1][n];
    double x_1[1][n];
    double x_m[1][n];
    double min_x = 20000;
    double eval_0 = 0;
    double eval_1 = 0;
    
    memcpy(x_m, x, sizeof(x));
    double t_i=T_0;
    int iter=0;
    int boltzmann=0;
    start=clock();

    while(T_0 > T_min){
        T_0=alpha*T_0;
        iter++;
        if (iter%10==0){
            printf("iter: %d, T_0: %f, min_dist: %f b_g: %d\n", iter, T_0*1000, min_x, boltzmann);
        }
        //
        memcpy(x_0, x_m, sizeof(x));
        for(int i = 0; i<L; i++){
            memcpy(x_1, x_0, sizeof(x));
            eval_0=dist(n,x_0);
            vecindad(n, x_1);
            eval_1=dist(n,x_1);
            if (eval_1 < eval_0){
                memcpy(x_0, x_1, sizeof(x));
                if (eval_1 < min_x){
                    min_x = eval_1;
                    memcpy(x_m, x_1, sizeof(x));
                }
            }
            else{
                double r = roy_uniform(0,1,2);
                double delta = eval_1 - eval_0;
                double prob = exp(-delta/T_0);
                if (r < prob){ // si el numero aleatorio es menor que e^(-deltaE/T)
                    boltzmann++;
                    memcpy(x_0, x_1, sizeof(x));
                }

                }
            }

            }
    
    
    // IMPRIMIR RESULTADOS
    for(int i=1; i<n; i++){
        printf("x[%d]: %f \n", i, x_m[0][i]);
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("tiempo: %f segundos\n", cpu_time_used);


    return 0;
}